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

#include "T3D/lighting/reflectionProbe.h"
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

#include "gfx/gfxTextureManager.h"
#include "T3D/lighting/IBLUtilities.h"

extern bool gEditingMission;
extern ColorI gCanvasClearColor;
bool ReflectionProbe::smRenderReflectionProbes = true;
bool ReflectionProbe::smRenderPreviewProbes = true;

IMPLEMENT_CO_NETOBJECT_V1(ReflectionProbe);

ConsoleDocClass(ReflectionProbe,
   "@brief An example scene object which renders a mesh.\n\n"
   "This class implements a basic SceneObject that can exist in the world at a "
   "3D position and render itself. There are several valid ways to render an "
   "object in Torque. This class implements the preferred rendering method which "
   "is to submit a MeshRenderInst along with a Material, vertex buffer, "
   "primitive buffer, and transform and allow the RenderMeshMgr handle the "
   "actual setup and rendering for you.\n\n"
   "See the C++ code for implementation details.\n\n"
   "@ingroup Examples\n");

ImplementEnumType(ReflectProbeType,
   "Type of mesh data available in a shape.\n"
   "@ingroup gameObjects")
{ ProbeInfo::Sphere, "Sphere", "Sphere shaped" },
{ ProbeInfo::Box, "Box", "Box shape" }
EndImplementEnumType;

ImplementEnumType(IndrectLightingModeEnum,
   "Type of mesh data available in a shape.\n"
   "@ingroup gameObjects")
{ ReflectionProbe::NoIndirect, "No Lighting", "This probe does not provide any local indirect lighting data" },
{ ReflectionProbe::AmbientColor, "Ambient Color", "Adds a flat color to act as the local indirect lighting" },
{ ReflectionProbe::SphericalHarmonics, "Spherical Harmonics", "Creates spherical harmonics data based off the reflection data" },
   EndImplementEnumType;

ImplementEnumType(ReflectionModeEnum,
   "Type of mesh data available in a shape.\n"
   "@ingroup gameObjects")
{ ReflectionProbe::NoReflection, "No Reflections", "This probe does not provide any local reflection data"},
{ ReflectionProbe::StaticCubemap, "Static Cubemap", "Uses a static CubemapData" },
{ ReflectionProbe::BakedCubemap, "Baked Cubemap", "Uses a cubemap baked from the probe's current position" },
//{ ReflectionProbe::DynamicCubemap, "Dynamic Cubemap", "Uses a cubemap baked from the probe's current position, updated at a set rate" },
   EndImplementEnumType;

//-----------------------------------------------------------------------------
// Object setup and teardown
//-----------------------------------------------------------------------------
ReflectionProbe::ReflectionProbe()
{
   // Flag this object so that it will always
   // be sent across the network to clients
   mNetFlags.set(Ghostable | ScopeAlways);

   mTypeMask = LightObjectType | MarkerObjectType;

   mProbeShapeType = ProbeInfo::Box;

   mIndrectLightingModeType = NoIndirect;

   mReflectionModeType = BakedCubemap;

   mEnabled = true;
   mBake = false;
   mDirty = false;

   mRadius = 10;

   mUseCubemap = false;
   mStaticCubemap = NULL;
   mReflectionPath = "";
   mProbeUniqueID = "";

   mEditorShapeInst = NULL;
   mEditorShape = NULL;

   mRefreshRateMS = 200;
   mDynamicLastBakeMS = 0;

   mMaxDrawDistance = 75;

   mResourcesCreated = false;

   mProbeInfo = new ProbeInfo();

   mPrefilterSize = 64;
   mPrefilterMipLevels = mLog2(F32(mPrefilterSize));
   mPrefilterMap = nullptr;
   mIrridianceMap = nullptr;

   mProbePosOffset = Point3F::Zero;
   mEditPosOffset = false;
}

ReflectionProbe::~ReflectionProbe()
{
   if (mEditorShapeInst)
      SAFE_DELETE(mEditorShapeInst);

   if (mReflectionModeType != StaticCubemap && mStaticCubemap)
      mStaticCubemap->deleteObject();
}

//-----------------------------------------------------------------------------
// Object Editing
//-----------------------------------------------------------------------------
void ReflectionProbe::initPersistFields()
{
   addGroup("Rendering");
      addProtectedField("enabled", TypeBool, Offset(mEnabled, ReflectionProbe),
         &_setEnabled, &defaultProtectedGetFn, "Regenerate Voxel Grid");

      addField("ProbeShape", TypeReflectProbeType, Offset(mProbeShapeType, ReflectionProbe),
         "The type of mesh data to use for collision queries.");
      addField("radius", TypeF32, Offset(mRadius, ReflectionProbe), "The name of the material used to render the mesh.");
	  addField("posOffset", TypePoint3F, Offset(mProbePosOffset, ReflectionProbe), "");

     //addProtectedField("EditPosOffset", TypeBool, Offset(mEditPosOffset, ReflectionProbe),
     //   &_toggleEditPosOffset, &defaultProtectedGetFn, "Toggle Edit Pos Offset Mode", AbstractClassRep::FieldFlags::FIELD_ComponentInspectors);
   endGroup("Rendering");

   addGroup("Reflection");
      addField("ReflectionMode", TypeReflectionModeEnum, Offset(mReflectionModeType, ReflectionProbe),
         "The type of mesh data to use for collision queries.");

      addField("reflectionPath", TypeImageFilename, Offset(mReflectionPath, ReflectionProbe),
         "The type of mesh data to use for collision queries.");

      addField("StaticCubemap", TypeCubemapName, Offset(mCubemapName, ReflectionProbe), "Cubemap used instead of reflection texture if fullReflect is off.");

      addProtectedField("Bake", TypeBool, Offset(mBake, ReflectionProbe),
         &_doBake, &defaultProtectedGetFn, "Regenerate Voxel Grid", AbstractClassRep::FieldFlags::FIELD_ComponentInspectors);
   endGroup("Reflection");

   Con::addVariable("$Light::renderReflectionProbes", TypeBool, &ReflectionProbe::smRenderReflectionProbes,
      "Toggles rendering of light frustums when the light is selected in the editor.\n\n"
      "@note Only works for shadow mapped lights.\n\n"
      "@ingroup Lighting");

   Con::addVariable("$Light::renderPreviewProbes", TypeBool, &ReflectionProbe::smRenderPreviewProbes,
      "Toggles rendering of light frustums when the light is selected in the editor.\n\n"
      "@note Only works for shadow mapped lights.\n\n"
      "@ingroup Lighting");

   // SceneObject already handles exposing the transform
   Parent::initPersistFields();
}

void ReflectionProbe::inspectPostApply()
{
   Parent::inspectPostApply();

   mDirty = true;

   // Flag the network mask to send the updates
   // to the client object
   setMaskBits(-1);
}

bool ReflectionProbe::_setEnabled(void *object, const char *index, const char *data)
{
   ReflectionProbe* probe = reinterpret_cast< ReflectionProbe* >(object);

   probe->mEnabled = dAtob(data);
   probe->setMaskBits(-1);

   return true;
}

bool ReflectionProbe::_doBake(void *object, const char *index, const char *data)
{
   ReflectionProbe* probe = reinterpret_cast< ReflectionProbe* >(object);

   //if (probe->mDirty)
   //   probe->bake(probe->mReflectionPath, 256);

   ReflectionProbe *clientProbe = (ReflectionProbe*)probe->getClientObject();

   if (clientProbe)
   {
      clientProbe->bake(clientProbe->mReflectionPath, 64);
   }

   return false;
}

bool ReflectionProbe::_toggleEditPosOffset(void *object, const char *index, const char *data)
{
   ReflectionProbe* probe = reinterpret_cast< ReflectionProbe* >(object);

   probe->mEditPosOffset = !probe->mEditPosOffset;

   //if (probe->mDirty)
   //   probe->bake(probe->mReflectionPath, 256);

   return false;
}

bool ReflectionProbe::onAdd()
{
   if (!Parent::onAdd())
      return false;

   mEditPosOffset = false;

   mObjBox.minExtents.set(-1, -1, -1);
   mObjBox.maxExtents.set(1, 1, 1);
   //mObjScale.set(mRadius/2, mRadius/2, mRadius/2);

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
   {
      //createClientResources();
      //updateMaterial();
      createGeometry();
      updateProbeParams();
   }
  
   setMaskBits(-1);

   return true;
}

void ReflectionProbe::onRemove()
{
   // Remove this object from the scene
   removeFromScene();

   Parent::onRemove();
}

void ReflectionProbe::setTransform(const MatrixF & mat)
{
   // Let SceneObject handle all of the matrix manipulation
   if (!mEditPosOffset)
      Parent::setTransform(mat);
   else
      mProbePosOffset = mat.getPosition();

   mDirty = true;

   // Dirty our network mask so that the new transform gets
   // transmitted to the client object
   setMaskBits(TransformMask);
}

U32 ReflectionProbe::packUpdate(NetConnection *conn, U32 mask, BitStream *stream)
{
   // Allow the Parent to get a crack at writing its info
   U32 retMask = Parent::packUpdate(conn, mask, stream);

   // Write our transform information
   if (stream->writeFlag(mask & TransformMask))
   {
      mathWrite(*stream, getTransform());
      mathWrite(*stream, getScale());
      mathWrite(*stream, mProbePosOffset);
   }

   if (stream->writeFlag(mask & ShapeTypeMask))
   {
      stream->write((U32)mProbeShapeType);
   }

   if (stream->writeFlag(mask & UpdateMask))
   {
      stream->write(mRadius);
   }

   if (stream->writeFlag(mask & BakeInfoMask))
   {
      stream->write(mReflectionPath);
      stream->write(mProbeUniqueID);
   }

   if (stream->writeFlag(mask & EnabledMask))
   {
      stream->writeFlag(mEnabled);
   }

   if (stream->writeFlag(mask & ModeMask))
   {
      stream->write((U32)mIndrectLightingModeType);
      stream->write((U32)mReflectionModeType);
   }

   if (stream->writeFlag(mask & CubemapMask))
   {
      stream->writeFlag(mUseCubemap);
      stream->write(mCubemapName);
   }

   return retMask;
}

void ReflectionProbe::unpackUpdate(NetConnection *conn, BitStream *stream)
{
   // Let the Parent read any info it sent
   Parent::unpackUpdate(conn, stream);

   if (stream->readFlag())  // TransformMask
   {
      mathRead(*stream, &mObjToWorld);
      mathRead(*stream, &mObjScale);

      setTransform(mObjToWorld);

      mathRead(*stream, &mProbePosOffset);
   }

   if (stream->readFlag())  // ShapeTypeMask
   {
      U32 shapeType = ProbeInfo::Sphere;
      stream->read(&shapeType);

      mProbeShapeType = (ProbeInfo::ProbeShapeType)shapeType;
      createGeometry();
   }

   if (stream->readFlag())  // UpdateMask
   {
      stream->read(&mRadius);
   }

   if (stream->readFlag())  // BakeInfoMask
   {
      stream->read(&mReflectionPath);
      stream->read(&mProbeUniqueID);
   }

   if (stream->readFlag())  // EnabledMask
   {
      mEnabled = stream->readFlag();
   }

   bool isMaterialDirty = false;

   if (stream->readFlag())  // ModeMask
   {
      U32 indirectModeType = AmbientColor;
      stream->read(&indirectModeType);
      mIndrectLightingModeType = (IndrectLightingModeType)indirectModeType;

      U32 reflectModeType = BakedCubemap;
      stream->read(&reflectModeType);
      mReflectionModeType = (ReflectionModeType)reflectModeType;

      isMaterialDirty = true;
   }

   if (stream->readFlag())  // CubemapMask
   {
      mUseCubemap = stream->readFlag();

      stream->read(&mCubemapName);

      isMaterialDirty = true;
   }

   updateProbeParams();

   if (isMaterialDirty)
   {
      updateMaterial();
   }
}

void ReflectionProbe::createGeometry()
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

void ReflectionProbe::updateProbeParams()
{
   if (mProbeInfo == nullptr)
      return;

   updateMaterial();

   mProbeInfo->mAmbient = LinearColorF(0, 0, 0, 0);

   mProbeInfo->mProbeShapeType = mProbeShapeType;

   mProbeInfo->setPosition(getPosition());

   //Update the bounds
   //mObjBox.minExtents.set(-1, -1, -1);
   //mObjBox.maxExtents.set(1, 1, 1);

   //mObjScale.set(mRadius / 2, mRadius / 2, mRadius / 2);

   // Skip our transform... it just dirties mask bits.
   Parent::setTransform(mObjToWorld);

   resetWorldBox();

   mProbeInfo->mBounds = mWorldBox;
   mProbeInfo->mRadius = mRadius;

   mProbeInfo->mIsSkylight = false;

   mProbeInfo->mProbePosOffset = mProbePosOffset;
}

void ReflectionProbe::updateMaterial()
{
   createClientResources();

   if (mReflectionModeType != DynamicCubemap)
   {
      if ((mReflectionModeType == BakedCubemap) && !mProbeUniqueID.isEmpty())
      {
         if (mPrefilterMap != nullptr && mPrefilterMap->mCubemap.isValid())
         {
            mProbeInfo->mCubemap = &mPrefilterMap->mCubemap;
         }
         if (mIrridianceMap != nullptr && mIrridianceMap->mCubemap.isValid())
         {
            mProbeInfo->mIrradianceCubemap = &mIrridianceMap->mCubemap;
         }
         if (mBrdfTexture.isValid())
         {
            mProbeInfo->mBRDFTexture = &mBrdfTexture;
         }
      }
      else if (mReflectionModeType == StaticCubemap && !mCubemapName.isEmpty())
      {
         Sim::findObject(mCubemapName, mStaticCubemap);

         mProbeInfo->mCubemap = &mStaticCubemap->mCubemap;
      }
   }
   else if (mReflectionModeType == DynamicCubemap && !mDynamicCubemap.isNull())
   {
      mProbeInfo->mCubemap = &mDynamicCubemap;
   }
}

bool ReflectionProbe::createClientResources()
{
   //irridiance resources
   if (!mIrridianceMap)
   {
      mIrridianceMap = new CubemapData();
      mIrridianceMap->registerObject();

      mIrridianceMap->createMap();
   }

   String irrPath = getIrradianceMapPath();
   if (Platform::isFile(irrPath))
   {
      mIrridianceMap->setCubemapFile(FileName(irrPath));
      mIrridianceMap->updateFaces();
   }

   if(mIrridianceMap->mCubemap.isNull())
      Con::errorf("ReflectionProbe::createClientResources() - Unable to load baked irradiance map at %s", getIrradianceMapPath().c_str());

   //
   if (!mPrefilterMap)
   {
      mPrefilterMap = new CubemapData();
      mPrefilterMap->registerObject();

      mPrefilterMap->createMap();
   }

   String prefilPath = getPrefilterMapPath();
   if (Platform::isFile(prefilPath))
   {
      mPrefilterMap->setCubemapFile(FileName(prefilPath));
      mPrefilterMap->updateFaces();
   }

   if (mPrefilterMap->mCubemap.isNull())
      Con::errorf("ReflectionProbe::createClientResources() - Unable to load baked prefilter map at %s", getPrefilterMapPath().c_str());

   //brdf lookup resources
   //make the brdf lookup texture the same size as the prefilter texture
   
   String brdfPath = Con::getVariable("$Core::BRDFTexture", "core/art/brdfTexture.DDS");

   mBrdfTexture = TEXMGR->createTexture(brdfPath, &GFXTexturePersistentProfile);// TEXMGR->createTexture(mPrefilterSize, mPrefilterSize, GFXFormatR16G16B16A16F, &GFXRenderTargetProfile, 1, 0);

   if (!mBrdfTexture)
   {
      mBrdfTexture = IBLUtilities::GenerateAndSaveBRDFTexture(brdfPath, 512);
   }

   mResourcesCreated = true;

   return true;
}

void ReflectionProbe::generateTextures()
{
}

void ReflectionProbe::prepRenderImage(SceneRenderState *state)
{
   if (!mEnabled || !ReflectionProbe::smRenderReflectionProbes)
      return;

   Point3F distVec = getRenderPosition() - state->getCameraPosition();
   F32 dist = distVec.len();

   //Culling distance. Can be adjusted for performance options considerations via the scalar
   if (dist > mMaxDrawDistance * Con::getFloatVariable("$pref::GI::ProbeDrawDistScale", 1.0))
      return;

   if (mReflectionModeType == DynamicCubemap && mRefreshRateMS < (Platform::getRealMilliseconds() - mDynamicLastBakeMS))
   {
      bake("", 32);
      mDynamicLastBakeMS = Platform::getRealMilliseconds();
   }

   //Submit our probe to actually do the probe action
   // Get a handy pointer to our RenderPassmanager
   //RenderPassManager *renderPass = state->getRenderPass();

   //Update our score based on our radius, distance
   mProbeInfo->mScore = mProbeInfo->mRadius/mMax(dist,1.0f);

   Point3F vect = distVec;
   vect.normalizeSafe();

   mProbeInfo->mScore *= mMax(mAbs(mDot(vect, state->getCameraTransform().getForwardVector())),0.001f);

   //Register
   PROBEMGR->registerProbe(mProbeInfo, this);

   if (ReflectionProbe::smRenderPreviewProbes && gEditingMission && mEditorShapeInst && mPrefilterMap != nullptr)
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

      if(mReflectionModeType != DynamicCubemap)
         rdata.setCubemap(mPrefilterMap->mCubemap);
      else
         rdata.setCubemap(mDynamicCubemap);

      // We might have some forward lit materials
      // so pass down a query to gather lights.
      LightQuery query;
      query.init(getWorldSphere());
      rdata.setLightQuery(&query);

      // Set the world matrix to the objects render transform
      MatrixF mat = getRenderTransform();
      mat.scale(Point3F(1, 1, 1));
      
      Point3F centerPos = mat.getPosition();
      centerPos += mProbePosOffset;
      mat.setPosition(centerPos);

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
      ObjectRenderInst *ri = state->getRenderPass()->allocInst<ObjectRenderInst>();
      ri->renderDelegate.bind(this, &ReflectionProbe::_onRenderViz);
      ri->type = RenderPassManager::RIT_Editor;
      state->getRenderPass()->addInst(ri);
   }
}

void ReflectionProbe::_onRenderViz(ObjectRenderInst *ri,
   SceneRenderState *state,
   BaseMatInstance *overrideMat)
{
   if (!ReflectionProbe::smRenderReflectionProbes)
      return;

   GFXDrawUtil *draw = GFX->getDrawUtil();

   GFXStateBlockDesc desc;
   desc.setZReadWrite(true, false);
   desc.setCullMode(GFXCullNone);
   desc.setBlend(true);

   // Base the sphere color on the light color.
   ColorI color = ColorI::WHITE;
   color.alpha = 25;

   if (mProbeShapeType == ProbeInfo::Sphere)
   {
      draw->drawSphere(desc, mRadius, getPosition(), color);
   }
   else
   {
	  const MatrixF worldToObjectXfm = getTransform();

      Box3F cube(-Point3F(mRadius, mRadius, mRadius),Point3F(mRadius, mRadius, mRadius));
      cube.setCenter(getPosition()+mProbePosOffset);
      draw->drawCube(desc, cube, color, &worldToObjectXfm);
   }
}

void ReflectionProbe::setPreviewMatParameters(SceneRenderState* renderState, BaseMatInstance* mat)
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
   GFX->setCubeTexture(1, mPrefilterMap->mCubemap);

   //Set the invViewMat
   MatrixSet &matrixSet = renderState->getRenderPass()->getMatrixSet();
   const MatrixF &worldToCameraXfm = matrixSet.getWorldToCamera();

   MaterialParameterHandle *invViewMat = mat->getMaterialParameterHandle("$invViewMat");

   matParams->setSafe(invViewMat, worldToCameraXfm);
}

DefineEngineMethod(ReflectionProbe, postApply, void, (), ,
   "A utility method for forcing a network update.\n")
{
   object->inspectPostApply();
}

String ReflectionProbe::getPrefilterMapPath()
{
   if (mReflectionPath.isEmpty() || mProbeUniqueID.isEmpty())
   {
      Con::errorf("ReflectionProbe::getPrefilterMapPath() - We don't have a set output path or persistant id, so no valid path can be provided!");
      return "";
   }

   char fileName[256];
   dSprintf(fileName, 256, "%s%s_Prefilter.DDS", mReflectionPath.c_str(), mProbeUniqueID.c_str());

   return fileName;
}

String ReflectionProbe::getIrradianceMapPath()
{
   if (mReflectionPath.isEmpty() || mProbeUniqueID.isEmpty())
   {
      Con::errorf("ReflectionProbe::getIrradianceMapPath() - We don't have a set output path or persistant id, so no valid path can be provided!");
      return "";
   }

   char fileName[256];
   dSprintf(fileName, 256, "%s%s_Irradiance.DDS", mReflectionPath.c_str(), mProbeUniqueID.c_str());

   return fileName;
}

void ReflectionProbe::bake(String outputPath, S32 resolution)
{
   GFXDEBUGEVENT_SCOPE(ReflectionProbe_Bake, ColorI::WHITE);

   Con::warnf("ReflectionProbe::bake() - Beginning bake!");

   U32 startMSTime = Platform::getRealMilliseconds();

   PostEffect *preCapture = dynamic_cast<PostEffect*>(Sim::findObject("AL_PreCapture"));
   PostEffect *deferredShading = dynamic_cast<PostEffect*>(Sim::findObject("AL_DeferredShading"));
   if (preCapture)
   {
	   preCapture->setShaderConst("$radius",String::ToString(mRadius));
	   preCapture->setShaderConst("$captureRez", String::ToString(F32(resolution)));
	   preCapture->enable();
   }
   if (deferredShading)
      deferredShading->disable();

   GFXCubemapHandle sceneCaptureCubemap;

   if (mReflectionModeType == DynamicCubemap && mDynamicCubemap.isNull())
   {
      //mCubemap->createMap();
      mDynamicCubemap = GFX->createCubemap();
      mDynamicCubemap->initDynamic(resolution, GFXFormatB8G8R8A8);

      sceneCaptureCubemap = mDynamicCubemap;
   }
   else if (mReflectionModeType != DynamicCubemap)
   {
      //Prep our bake path
      if (mReflectionPath.isEmpty())
      {
         Con::errorf("ReflectionProbe::bake() - Unable to bake our captures because probe doesn't have a path set");
         return;
      }

      if (mProbeUniqueID.isEmpty())
      {
         Con::errorf("ReflectionProbe::bake() - Unable to bake our captures because probe doesn't have a unique ID set");
         return;
      }

      sceneCaptureCubemap = GFX->createCubemap();
      sceneCaptureCubemap->initDynamic(resolution, GFXFormatR8G8B8A8);
      //sceneCaptureCubemap->initDynamic(resolution, GFXFormatR16G16B16A16F);
   }

   bool validCubemap = true;

   // Save the current transforms so we can restore
   // it for child control rendering below.
   GFXTransformSaver saver;

   //bool saveEditingMission = gEditingMission;
   //gEditingMission = false;

   //Set this to true to use the prior method where it goes through the SPT_Reflect path for the bake
   bool probeRenderState = ReflectionProbe::smRenderReflectionProbes;
   ReflectionProbe::smRenderReflectionProbes = false;
   for (U32 i = 0; i < 6; ++i)
   {
      GFXTexHandle blendTex;
      blendTex.set(resolution, resolution, GFXFormatR16G16B16A16, &GFXRenderTargetProfile, "");

      GFXTextureTargetRef baseTarget = GFX->allocRenderToTextureTarget();

      GFX->clearTextureStateImmediate(0);
      
      baseTarget->attachTexture(GFXTextureTarget::Color0, sceneCaptureCubemap, i);

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
      matView.setPosition(getPosition()+mProbePosOffset);
      matView.inverse();

      // set projection to 90 degrees vertical and horizontal
      F32 left, right, top, bottom;
      F32 nearPlane = 0.01f;
      F32 farDist = 1000.f;

      MathUtils::makeFrustum(&left, &right, &top, &bottom, M_HALFPI_F, 1.0f, nearPlane);
      Frustum frustum(false, left, right, top, bottom, nearPlane, farDist);

      renderFrame(&baseTarget, matView, frustum, StaticObjectType | StaticShapeObjectType & EDITOR_RENDER_TYPEMASK, gCanvasClearColor);

      baseTarget->resolve();

      //mStaticCubemap->setCubeFaceTexture(i, blendTex);
   }

      /*if (mReflectionModeType != DynamicCubemap)
      {
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
            mCubemap->setCubeFaceFile(i, FileName(fileName));
         else
            validCubemap = false;

         bitmap.deleteImage();
      }
   }*/

   if (sceneCaptureCubemap.isValid())
   {
      validCubemap = true;
      mDirty = false;
   }
   else
   {
      validCubemap = false;
   }

   /*if (mReflectionModeType != DynamicCubemap && validCubemap)
   {
      if (mStaticCubemap->mCubemap)
         mStaticCubemap->updateFaces();
      else
         mStaticCubemap->createMap();

      if (mStaticCubemap->mCubemap.isNull())
         validCubemap = false;

      mDirty = false;
   }*/

   //Now, save out the maps
   //create irridiance cubemap
   if (validCubemap)
   {
      bool se = isServerObject();

      //Just to ensure we're prepped for the generation
      createClientResources();

      //Prep it with whatever resolution we've dictated for our bake
      mIrridianceMap->mCubemap->initDynamic(resolution, GFXFormatR8G8B8A8);
      mPrefilterMap->mCubemap->initDynamic(resolution, GFXFormatR8G8B8A8);

      //IBLUtilities::GenerateAndSaveIrradianceMap(getIrradianceMapPath(), resolution, sceneCaptureCubemap, mIrridianceMap->mCubemap);
      //IBLUtilities::GenerateAndSavePrefilterMap(getPrefilterMapPath(), resolution, sceneCaptureCubemap, mPrefilterMipLevels, mPrefilterMap->mCubemap);

      GFXTextureTargetRef renderTarget = GFX->allocRenderToTextureTarget(false);

      IBLUtilities::GenerateIrradianceMap(renderTarget, sceneCaptureCubemap, mIrridianceMap->mCubemap);
      IBLUtilities::GeneratePrefilterMap(renderTarget, sceneCaptureCubemap, mPrefilterMipLevels, mPrefilterMap->mCubemap);

      IBLUtilities::SaveCubeMap(getIrradianceMapPath(), mIrridianceMap->mCubemap);
      IBLUtilities::SaveCubeMap(getPrefilterMapPath(), mPrefilterMap->mCubemap);
   }
   else
   {
      Con::errorf("ReflectionProbe::bake() - Didn't generate a valid scene capture cubemap, unable to generate prefilter and irradiance maps!");
   }

   ReflectionProbe::smRenderReflectionProbes = probeRenderState;
   setMaskBits(-1);

   if (preCapture)
      preCapture->disable();
   if (deferredShading)
      deferredShading->enable();

   U32 endMSTime = Platform::getRealMilliseconds();
   F32 diffTime = F32(endMSTime - startMSTime);

   Con::warnf("ReflectionProbe::bake() - Finished bake! Took %g milliseconds", diffTime);
}

DefineEngineMethod(ReflectionProbe, Bake, void, (String outputPath, S32 resolution), ("", 256),
   "@brief returns true if control object is inside the fog\n\n.")
{
   ReflectionProbe *clientProbe = (ReflectionProbe*)object->getClientObject();

   if (clientProbe)
   {
      clientProbe->bake(outputPath, resolution);
   }
   //object->bake(outputPath, resolution);
}