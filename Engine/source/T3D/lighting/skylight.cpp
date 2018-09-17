//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#include "T3D/lighting/Skylight.h"
#include "math/mathIO.h"
#include "scene/sceneRenderState.h"
#include "console/consoleTypes.h"
#include "core/stream/bitStream.h"
#include "materials/baseMatInstance.h"
#include "console/engineAPI.h"
#include "gfx/gfxDrawUtil.h"
#include "gfx/gfxDebugEvent.h"
#include "gfx/gfxTransformSaver.h"
#include "math/mathUtils.h"
#include "gfx/bitmap/gBitmap.h"
#include "core/stream/fileStream.h"
#include "core/fileObject.h"
#include "core/resourceManager.h"
#include "console/simPersistId.h"
#include <string>
#include "T3D/gameFunctions.h"
#include "postFx/postEffect.h"
#include "renderInstance/renderProbeMgr.h"
#include "lighting/probeManager.h"

#include "math/util/sphereMesh.h"
#include "materials/materialManager.h"
#include "math/util/matrixSet.h"
#include "gfx/bitmap/cubemapSaver.h"

#include "materials/materialFeatureTypes.h"

#include "materials/shaderData.h"
#include "gfx/gfxTextureManager.h"

#include "gfx/bitmap/imageUtils.h"

#include "T3D/lighting/IBLUtilities.h"

extern bool gEditingMission;
extern ColorI gCanvasClearColor;
bool Skylight::smRenderSkylights = true;
bool Skylight::smRenderPreviewProbes = true;

IMPLEMENT_CO_NETOBJECT_V1(Skylight);

ConsoleDocClass(Skylight,
   "@brief An example scene object which renders a mesh.\n\n"
   "This class implements a basic SceneObject that can exist in the world at a "
   "3D position and render itself. There are several valid ways to render an "
   "object in Torque. This class implements the preferred rendering method which "
   "is to submit a MeshRenderInst along with a Material, vertex buffer, "
   "primitive buffer, and transform and allow the RenderMeshMgr handle the "
   "actual setup and rendering for you.\n\n"
   "See the C++ code for implementation details.\n\n"
   "@ingroup Examples\n");

ImplementEnumType(SkylightReflectionModeEnum,
   "Type of mesh data available in a shape.\n"
   "@ingroup gameObjects")
{ Skylight::StaticCubemap, "Static Cubemap", "Uses a static CubemapData" },
{ Skylight::BakedCubemap, "Baked Cubemap", "Uses a cubemap baked from the probe's current position" },
   EndImplementEnumType;

//-----------------------------------------------------------------------------
// Object setup and teardown
//-----------------------------------------------------------------------------
Skylight::Skylight()
{
   // Flag this object so that it will always
   // be sent across the network to clients
   mNetFlags.set(Ghostable | ScopeAlways);

   mTypeMask = LightObjectType | MarkerObjectType;

   mReflectionModeType = StaticCubemap;

   mEnabled = true;
   mBake = false;
   mDirty = false;

   mCubemap = NULL;
   mReflectionPath = "";
   mProbeUniqueID = "";

   mEditorShapeInst = NULL;
   mEditorShape = NULL;

   mIrridianceMap = NULL;
   mPrefilterMap = NULL;
   mBrdfTexture = NULL;
   mResourcesCreated = false;
   mPrefilterSize = 512;
   mPrefilterMipLevels = 6;

   mProbeInfo = new ProbeInfo();
}

Skylight::~Skylight()
{
   if (mEditorShapeInst)
      SAFE_DELETE(mEditorShapeInst);

   if (mReflectionModeType != StaticCubemap && mCubemap)
      mCubemap->deleteObject();
}

//-----------------------------------------------------------------------------
// Object Editing
//-----------------------------------------------------------------------------
void Skylight::initPersistFields()
{
   addGroup("Rendering");
      addProtectedField("enabled", TypeBool, Offset(mEnabled, Skylight),
         &_setEnabled, &defaultProtectedGetFn, "Regenerate Voxel Grid");
   endGroup("Rendering");

   addGroup("Reflection");
      //addField("ReflectionMode", TypeSkylightReflectionModeEnum, Offset(mReflectionModeType, Skylight),
      //   "The type of mesh data to use for collision queries.");

      //addField("reflectionPath", TypeImageFilename, Offset(mReflectionPath, Skylight),
      //   "The type of mesh data to use for collision queries.");

      addField("StaticCubemap", TypeCubemapName, Offset(mCubemapName, Skylight), "Cubemap used instead of reflection texture if fullReflect is off.");

      //addProtectedField("Bake", TypeBool, Offset(mBake, Skylight),
      //   &_doBake, &defaultProtectedGetFn, "Regenerate Voxel Grid", AbstractClassRep::FieldFlags::FIELD_ComponentInspectors);
   endGroup("Reflection");

   Con::addVariable("$Light::renderSkylights", TypeBool, &Skylight::smRenderSkylights,
      "Toggles rendering of light frustums when the light is selected in the editor.\n\n"
      "@note Only works for shadow mapped lights.\n\n"
      "@ingroup Lighting");

   Con::addVariable("$Light::renderPreviewProbes", TypeBool, &Skylight::smRenderPreviewProbes,
      "Toggles rendering of light frustums when the light is selected in the editor.\n\n"
      "@note Only works for shadow mapped lights.\n\n"
      "@ingroup Lighting");

   // SceneObject already handles exposing the transform
   Parent::initPersistFields();
}

void Skylight::inspectPostApply()
{
   Parent::inspectPostApply();

   mDirty = true;

   // Flag the network mask to send the updates
   // to the client object
   setMaskBits(-1);
}

bool Skylight::_setEnabled(void *object, const char *index, const char *data)
{
   Skylight* probe = reinterpret_cast< Skylight* >(object);

   probe->mEnabled = dAtob(data);
   probe->setMaskBits(-1);

   return true;
}

bool Skylight::_doBake(void *object, const char *index, const char *data)
{
   Skylight* probe = reinterpret_cast< Skylight* >(object);

   if (probe->mDirty)
      probe->bake(probe->mReflectionPath, 256);

   return false;
}

bool Skylight::onAdd()
{
   if (!Parent::onAdd())
      return false;

   mObjBox.minExtents.set(-1, -1, -1);
   mObjBox.maxExtents.set(1, 1, 1);

   // Skip our transform... it just dirties mask bits.
   Parent::setTransform(mObjToWorld);

   resetWorldBox();

   // Add this object to the scene
   addToScene();

   if (isServerObject())
   {
      if (!mPersistentId)
         mPersistentId = getOrCreatePersistentId();

      mProbeUniqueID = std::to_string(mPersistentId->getUUID().getHash()).c_str();
   }

   // Refresh this object's material (if any)
   if (isClientObject())
      updateMaterial();
  
   setMaskBits(-1);

   return true;
}

void Skylight::onRemove()
{
   // Remove this object from the scene
   removeFromScene();

   Parent::onRemove();
}

void Skylight::setTransform(const MatrixF & mat)
{
   // Let SceneObject handle all of the matrix manipulation
   Parent::setTransform(mat);

   mDirty = true;

   // Dirty our network mask so that the new transform gets
   // transmitted to the client object
   setMaskBits(TransformMask);
}

U32 Skylight::packUpdate(NetConnection *conn, U32 mask, BitStream *stream)
{
   // Allow the Parent to get a crack at writing its info
   U32 retMask = Parent::packUpdate(conn, mask, stream);

   if (stream->writeFlag(mask & InitialUpdateMask))
   {
      //initial work, just in case?
   }

   // Write our transform information
   if (stream->writeFlag(mask & TransformMask))
   {
      mathWrite(*stream, getTransform());
      mathWrite(*stream, getScale());
   }

   /*if (stream->writeFlag(mask & BakeInfoMask))
   {
      stream->write(mReflectionPath);
      stream->write(mProbeUniqueID);
   }*/

   if (stream->writeFlag(mask & EnabledMask))
   {
      stream->writeFlag(mEnabled);
   }

   /*if (stream->writeFlag(mask & ModeMask))
   {
      stream->write((U32)mReflectionModeType);
   }*/

   if (stream->writeFlag(mask & CubemapMask))
   {
      stream->write(mCubemapName);
   }

   return retMask;
}

void Skylight::unpackUpdate(NetConnection *conn, BitStream *stream)
{
   // Let the Parent read any info it sent
   Parent::unpackUpdate(conn, stream);

   if (stream->readFlag())
   {
      //some initial work?
      createGeometry();
   }

   if (stream->readFlag())  // TransformMask
   {
      mathRead(*stream, &mObjToWorld);
      mathRead(*stream, &mObjScale);

      setTransform(mObjToWorld);
   }

   /*if (stream->readFlag())  // BakeInfoMask
   {
      stream->read(&mReflectionPath);
      stream->read(&mProbeUniqueID);
   }*/

   if (stream->readFlag())  // EnabledMask
   {
      mEnabled = stream->readFlag();
   }

   bool isMaterialDirty = false;

   /*if (stream->readFlag())  // ModeMask
   {
      U32 reflectModeType = StaticCubemap;
      stream->read(&reflectModeType);
      mReflectionModeType = (ReflectionModeType)reflectModeType;

      isMaterialDirty = true;
   }*/

   if (stream->readFlag())  // CubemapMask
   {
      stream->read(&mCubemapName);

      isMaterialDirty = true;
   }

   updateProbeParams();

   if(isMaterialDirty)
      updateMaterial();
}

void Skylight::createGeometry()
{
   // Clean up our previous shape
   if (mEditorShapeInst)
      SAFE_DELETE(mEditorShapeInst);
   
   mEditorShape = NULL;
   
   String shapeFile = "tools/resources/ReflectProbeSphere.dae";
   
   // Attempt to get the resource from the ResourceManager
   mEditorShape = ResourceManager::get().load(shapeFile);
   if (mEditorShape)
   {
      mEditorShapeInst = new TSShapeInstance(mEditorShape, isClientObject());
   }
}

//-----------------------------------------------------------------------------
// Object Rendering
//-----------------------------------------------------------------------------

void Skylight::updateProbeParams()
{
   if (mProbeInfo == nullptr)
      return;

   mProbeInfo->mIntensity = 1;

   mProbeInfo->mAmbient = LinearColorF(0, 0, 0, 0);

   mProbeInfo->mProbeShapeType = ProbeInfo::Sphere;

   mProbeInfo->setPosition(getPosition());

   //Update the bounds
   mObjBox.minExtents.set(-1, -1, -1);
   mObjBox.maxExtents.set(1, 1, 1);

   // Skip our transform... it just dirties mask bits.
   Parent::setTransform(mObjToWorld);

   resetWorldBox();

   F32 visDist = gClientSceneGraph->getVisibleDistance();
   Box3F skylightBounds = Box3F(visDist * 2);

   skylightBounds.setCenter(Point3F::Zero);

   mProbeInfo->setPosition(Point3F::Zero);

   mProbeInfo->mBounds = skylightBounds;

   setGlobalBounds();

   mProbeInfo->mIsSkylight = true; 
   mProbeInfo->mScore = -1.0f; //sky comes first
}

bool Skylight::createClientResources()
{
   //irridiance resources
   mIrridianceMap = GFX->createCubemap();
   mIrridianceMap->initDynamic(128, GFXFormatR16G16B16A16F, 1);

   //prefilter resources - we share the irridiance stateblock
   mPrefilterMap = GFX->createCubemap();
   mPrefilterMap->initDynamic(mPrefilterSize, GFXFormatR16G16B16A16F, mPrefilterMipLevels);

   //brdf lookup resources
   //make the brdf lookup texture the same size as the prefilter texture
   mBrdfTexture = TEXMGR->createTexture(mPrefilterSize, mPrefilterSize, GFXFormatR16G16B16A16F, &GFXRenderTargetProfile, 1, 0);

   mResourcesCreated = true;

   return true;
}

void Skylight::updateMaterial()
{
   if ((mReflectionModeType == BakedCubemap) && !mProbeUniqueID.isEmpty())
   {
      bool validCubemap = true;

      char fileName[256];
      dSprintf(fileName, 256, "%s%s.DDS", mReflectionPath.c_str(), mProbeUniqueID.c_str());

      Vector<FileName> fileNames;

      if (Platform::isFile(fileName))
      {
         if (!mCubemap)
         {
            mCubemap = new CubemapData();
            mCubemap->registerObject();
         }

         mCubemap->setCubemapFile(FileName(fileName));
      }
      else
      {
         validCubemap = false;
      }

      if (validCubemap)
      {
         if (mCubemap->mCubemap)
            mCubemap->updateFaces();
         else
            mCubemap->createMap();

         mDirty = false;

         mProbeInfo->mCubemap = &mCubemap->mCubemap;
      }

      /*for (U32 i = 0; i < 6; ++i)
      {
         char faceFile[256];
         dSprintf(faceFile, sizeof(faceFile), "%s%s_%i.png", mReflectionPath.c_str(),
            mProbeUniqueID.c_str(), i);

         if (Platform::isFile(faceFile))
         {
            fileNames.push_back(FileName(faceFile));
         }
         else
         {
            validCubemap = false;
            break;
         }
      }

      if (validCubemap)
      {
         if (!mCubemap)
         {
            mCubemap = new CubemapData();
            mCubemap->registerObject();
         }

         for(U32 i=0; i < 6; i++)
            mCubemap->setCubeFaceFile(i, fileNames[i]);

         mCubemap->createMap();
         mCubemap->updateFaces();

         mProbeInfo->mCubemap = &mCubemap->mCubemap;
      }*/
   }
   else if (mReflectionModeType == StaticCubemap && !mCubemapName.isEmpty())
   {
      Sim::findObject(mCubemapName, mCubemap);

      if (!mCubemap)
         return;

      if (mCubemap->mCubemap)
         mCubemap->updateFaces();
      else
         mCubemap->createMap();

      mProbeInfo->mCubemap = &mCubemap->mCubemap;
   }

   //calculateSHTerms();

   generateTextures();

   //Now that the work is done, assign the relevent maps
   if (mPrefilterMap.isValid())
   {
      mProbeInfo->mCubemap = &mPrefilterMap;
      mProbeInfo->mIrradianceCubemap = &mIrridianceMap;
      mProbeInfo->mBRDFTexture = &mBrdfTexture;
   }
}

void Skylight::generateTextures()
{
   if (!mCubemap)
      return;

   if (!mResourcesCreated)
   {
      if (!createClientResources())
      {
         Con::errorf("SkyLight::createIrridianceMap: Failed to create resources");
         return;
      }
   }

   //GFXTransformSaver saver;

   GFXTextureTargetRef renderTarget = GFX->allocRenderToTextureTarget(false);

   IBLUtilities::GenerateIrradianceMap(renderTarget, mCubemap->mCubemap, mIrridianceMap);

   //Write it out
   char fileName[256];
   dSprintf(fileName, 256, "levels/test/irradiance.DDS");

   CubemapSaver::save(mIrridianceMap, fileName);

   if (!Platform::isFile(fileName))
   {
      Con::errorf("Failed to properly save out the skylight baked irradiance!");
   }

   //create prefilter cubemap (radiance)
   IBLUtilities::GeneratePrefilterMap(renderTarget, mCubemap->mCubemap, mPrefilterMipLevels, mPrefilterMap);

   //Write it out
   fileName[256];
   dSprintf(fileName, 256, "levels/test/prefilter.DDS");

   CubemapSaver::save(mPrefilterMap, fileName);

   if (!Platform::isFile(fileName))
   {
      Con::errorf("Failed to properly save out the skylight baked irradiance!");
   }

   //create brdf lookup
   IBLUtilities::GenerateBRDFTexture(mBrdfTexture);

   /*FileStream fs;
   if (fs.open("levels/test/brdf.DDS", Torque::FS::File::Write))
   {
      // Read back the render target, dxt compress it, and write it to disk.
      GBitmap brdfBmp(mBrdfTexture.getHeight(), mBrdfTexture.getWidth(), false, GFXFormatR8G8B8A8);
      mBrdfTexture.copyToBmp(&brdfBmp);

      brdfBmp.extrudeMipLevels();

      DDSFile *brdfDDS = DDSFile::createDDSFileFromGBitmap(&brdfBmp);
      ImageUtil::ddsCompress(brdfDDS, GFXFormatBC1);

      // Write result to file stream
      brdfDDS->write(fs);

      delete brdfDDS;
   }
   fs.close();*/
}

void Skylight::prepRenderImage(SceneRenderState *state)
{
   if (!mEnabled || !Skylight::smRenderSkylights)
      return;

   Point3F distVec = getPosition() - state->getCameraPosition();
   F32 dist = distVec.len();

   //special hook-in for skylights
   Point3F camPos = state->getCameraPosition();
   mProbeInfo->mBounds.setCenter(camPos);

   mProbeInfo->setPosition(camPos);

   //Submit our probe to actually do the probe action
   // Get a handy pointer to our RenderPassmanager
   //RenderPassManager *renderPass = state->getRenderPass();

   PROBEMGR->registerSkylight(mProbeInfo, this);

   if (Skylight::smRenderPreviewProbes && gEditingMission && mEditorShapeInst && mCubemap != nullptr)
   {
      GFXTransformSaver saver;

      // Calculate the distance of this object from the camera
      Point3F cameraOffset;
      getRenderTransform().getColumn(3, &cameraOffset);
      cameraOffset -= state->getDiffuseCameraPosition();
      F32 dist = cameraOffset.len();
      if (dist < 0.01f)
         dist = 0.01f;

      // Set up the LOD for the shape
      F32 invScale = (1.0f / getMax(getMax(mObjScale.x, mObjScale.y), mObjScale.z));

      mEditorShapeInst->setDetailFromDistance(state, dist * invScale);

      // Make sure we have a valid level of detail
      if (mEditorShapeInst->getCurrentDetail() < 0)
         return;

      BaseMatInstance* probePrevMat = mEditorShapeInst->getMaterialList()->getMaterialInst(0);

      setPreviewMatParameters(state, probePrevMat);

      // GFXTransformSaver is a handy helper class that restores
      // the current GFX matrices to their original values when
      // it goes out of scope at the end of the function

      // Set up our TS render state      
      TSRenderState rdata;
      rdata.setSceneState(state);
      rdata.setFadeOverride(1.0f);

      // We might have some forward lit materials
      // so pass down a query to gather lights.
      LightQuery query;
      query.init(getWorldSphere());
      rdata.setLightQuery(&query);

      // Set the world matrix to the objects render transform
      MatrixF mat = getRenderTransform();
      mat.scale(Point3F(1, 1, 1));
      GFX->setWorldMatrix(mat);

      // Animate the the shape
      mEditorShapeInst->animate();

      // Allow the shape to submit the RenderInst(s) for itself
      mEditorShapeInst->render(rdata);

      saver.restore();
   }

   // If the light is selected or light visualization
   // is enabled then register the callback.
   const bool isSelectedInEditor = (gEditingMission && isSelected());
   if (isSelectedInEditor)
   {
   }
}

void Skylight::setPreviewMatParameters(SceneRenderState* renderState, BaseMatInstance* mat)
{
   if (!mat->getFeatures().hasFeature(MFT_isDeferred))
      return;

   //Set up the params
   MaterialParameters *matParams = mat->getMaterialParameters();

   //Get the deferred render target
   NamedTexTarget* deferredTexTarget = NamedTexTarget::find("deferred");

   GFXTextureObject *deferredTexObject = deferredTexTarget->getTexture();
   if (!deferredTexObject) 
      return;

   GFX->setTexture(0, deferredTexObject);

   //Set the cubemap
   GFX->setCubeTexture(1, mCubemap->mCubemap);

   //Set the invViewMat
   MatrixSet &matrixSet = renderState->getRenderPass()->getMatrixSet();
   const MatrixF &worldToCameraXfm = matrixSet.getWorldToCamera();

   MaterialParameterHandle *invViewMat = mat->getMaterialParameterHandle("$invViewMat");

   matParams->setSafe(invViewMat, worldToCameraXfm);
}

DefineEngineMethod(Skylight, postApply, void, (), ,
   "A utility method for forcing a network update.\n")
{
   object->inspectPostApply();
}

void Skylight::bake(String outputPath, S32 resolution)
{
   GFXDEBUGEVENT_SCOPE(Skylight_Bake, ColorI::WHITE);

   PostEffect *preCapture = dynamic_cast<PostEffect*>(Sim::findObject("AL_PreCapture"));
   PostEffect *deferredShading = dynamic_cast<PostEffect*>(Sim::findObject("AL_DeferredShading"));
   if (preCapture)
      preCapture->enable();
   if (deferredShading)
      deferredShading->disable();

   //if (mReflectionModeType == StaticCubemap || mReflectionModeType == BakedCubemap || mReflectionModeType == SkyLight)
   {
      if (!mCubemap)
      {
         mCubemap = new CubemapData();
         mCubemap->registerObject();
      }
   }

   if (mReflectionModeType == BakedCubemap)
   {
      if (mReflectionPath.isEmpty() || !mPersistentId)
      {
         if (!mPersistentId)
            mPersistentId = getOrCreatePersistentId();

         mReflectionPath = outputPath.c_str();

         mProbeUniqueID = std::to_string(mPersistentId->getUUID().getHash()).c_str();
      }
   }

   bool validCubemap = true;

   // Save the current transforms so we can restore
   // it for child control rendering below.
   GFXTransformSaver saver;

   //bool saveEditingMission = gEditingMission;
   //gEditingMission = false;

   //Set this to true to use the prior method where it goes through the SPT_Reflect path for the bake
   bool probeRenderState = Skylight::smRenderSkylights;
   Skylight::smRenderSkylights = false;
   for (U32 i = 0; i < 6; ++i)
   {
      GFXTexHandle blendTex;
      blendTex.set(resolution, resolution, GFXFormatR8G8B8A8, &GFXRenderTargetProfile, "");

      GFXTextureTargetRef mBaseTarget = GFX->allocRenderToTextureTarget();

      GFX->clearTextureStateImmediate(0);
      mBaseTarget->attachTexture(GFXTextureTarget::Color0, blendTex);

      // Standard view that will be overridden below.
      VectorF vLookatPt(0.0f, 0.0f, 0.0f), vUpVec(0.0f, 0.0f, 0.0f), vRight(0.0f, 0.0f, 0.0f);

      switch (i)
      {
         case 0: // D3DCUBEMAP_FACE_POSITIVE_X:
            vLookatPt = VectorF(1.0f, 0.0f, 0.0f);
            vUpVec = VectorF(0.0f, 1.0f, 0.0f);
            break;
         case 1: // D3DCUBEMAP_FACE_NEGATIVE_X:
            vLookatPt = VectorF(-1.0f, 0.0f, 0.0f);
            vUpVec = VectorF(0.0f, 1.0f, 0.0f);
            break;
         case 2: // D3DCUBEMAP_FACE_POSITIVE_Y:
            vLookatPt = VectorF(0.0f, 1.0f, 0.0f);
            vUpVec = VectorF(0.0f, 0.0f, -1.0f);
            break;
         case 3: // D3DCUBEMAP_FACE_NEGATIVE_Y:
            vLookatPt = VectorF(0.0f, -1.0f, 0.0f);
            vUpVec = VectorF(0.0f, 0.0f, 1.0f);
            break;
         case 4: // D3DCUBEMAP_FACE_POSITIVE_Z:
            vLookatPt = VectorF(0.0f, 0.0f, 1.0f);
            vUpVec = VectorF(0.0f, 1.0f, 0.0f);
            break;
         case 5: // D3DCUBEMAP_FACE_NEGATIVE_Z:
            vLookatPt = VectorF(0.0f, 0.0f, -1.0f);
            vUpVec = VectorF(0.0f, 1.0f, 0.0f);
            break;
      }

      // create camera matrix
      VectorF cross = mCross(vUpVec, vLookatPt);
      cross.normalizeSafe();

      MatrixF matView(true);
      matView.setColumn(0, cross);
      matView.setColumn(1, vLookatPt);
      matView.setColumn(2, vUpVec);
      matView.setPosition(getPosition());
      matView.inverse();

      // set projection to 90 degrees vertical and horizontal
      F32 left, right, top, bottom;
      F32 nearPlane = 100.f;
      F32 farDist = 10000.f;

      MathUtils::makeFrustum(&left, &right, &top, &bottom, M_HALFPI_F, 1.0f, nearPlane);
      Frustum frustum(false, left, right, top, bottom, nearPlane, farDist);

      renderFrame(&mBaseTarget, matView, frustum, StaticObjectType | StaticShapeObjectType & EDITOR_RENDER_TYPEMASK, ColorI::RED);

      mBaseTarget->resolve();

      mCubemap->setCubeFaceTexture(i, blendTex);

      char fileName[256];
      dSprintf(fileName, 256, "%s%s_%i.png", mReflectionPath.c_str(),
         mProbeUniqueID.c_str(), i);

      FileStream stream;
      if (!stream.open(fileName, Torque::FS::File::Write))
      {
         Con::errorf("ReflectionProbe::bake(): Couldn't open cubemap face file fo writing " + String(fileName));
         if (preCapture)
            preCapture->disable();
         if (deferredShading)
            deferredShading->enable();
         return;
      }

      GBitmap bitmap(blendTex->getWidth(), blendTex->getHeight(), false, GFXFormatR8G8B8);
      blendTex->copyToBmp(&bitmap);
      bitmap.writeBitmap("png", stream);

      if (Platform::isFile(fileName) && mCubemap)
      {
         mCubemap->setCubeFaceFile(i, FileName(fileName));
      }
      else
      {
         validCubemap = false;
         break;
      }

      bitmap.deleteImage();
   }

   if (validCubemap)
   {
      if (mCubemap->mCubemap)
         mCubemap->updateFaces();
      else
         mCubemap->createMap();

      char fileName[256];
      dSprintf(fileName, 256, "%s%s.DDS", mReflectionPath.c_str(), mProbeUniqueID.c_str());

      CubemapSaver::save(mCubemap->mCubemap, fileName);

      if (!Platform::isFile(fileName))
      {
         validCubemap = false; //if we didn't save right, just 
         Con::errorf("Failed to properly save out the skylight baked cubemap!");
      }
   }

   if (validCubemap)
   {
      mDirty = false;

      //remove the temp files
      for (U32 i = 0; i < 6; i++)
      {
         char fileName[256];
         dSprintf(fileName, 256, "%s%s_%i.png", mReflectionPath.c_str(),
            mProbeUniqueID.c_str(), i);

         Platform::fileDelete(fileName);
      }
   }

   //calculateSHTerms();

   Skylight::smRenderSkylights = probeRenderState;
   setMaskBits(-1);

   if (preCapture)
      preCapture->disable();

   if (deferredShading)
      deferredShading->enable();
}

DefineEngineMethod(Skylight, Bake, void, (String outputPath, S32 resolution), ("", 256),
   "@brief returns true if control object is inside the fog\n\n.")
{
   object->bake(outputPath, resolution);
}