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
#include "console/simPersistID.h"
#include "T3D/gameFunctions.h"
#include "postFx/postEffect.h"
#include "renderInstance/renderProbeMgr.h"
#include "renderInstance/renderProbeMgr.h"

#include "math/util/sphereMesh.h"
#include "materials/materialManager.h"
#include "math/util/matrixSet.h"
#include "gfx/bitmap/cubemapSaver.h"

#include "materials/materialFeatureTypes.h"

#include "gfx/gfxTextureManager.h"
#include "T3D/lighting/IBLUtilities.h"

#include "scene/reflector.h"

extern bool gEditingMission;
extern ColorI gCanvasClearColor;
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
{ ProbeRenderInst::Sphere, "Sphere", "Sphere shaped" },
{ ProbeRenderInst::Box, "Box", "Box shape" }
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
ReflectionProbe::ReflectionProbe() :
   cubeDescId(0),
   reflectorDesc(nullptr),
   mSphereVertCount(0),
   mSpherePrimitiveCount(0)
{
   // Flag this object so that it will always
   // be sent across the network to clients
   mNetFlags.set(Ghostable | ScopeAlways);

   mTypeMask = LightObjectType | MarkerObjectType;

   mProbeShapeType = ProbeRenderInst::Box;

   mReflectionModeType = BakedCubemap;

   mEnabled = true;
   mBake = false;
   mDirty = false;
   mCubemapDirty = false;

   mRadius = 10;
   mObjScale = Point3F::One * 10;
   mProbeRefScale = Point3F::One*10;

   mUseHDRCaptures = true;

   mStaticCubemap = NULL;
   mProbeUniqueID = "";

   mEditorShapeInst = NULL;
   mEditorShape = NULL;

   mRefreshRateMS = 200;
   mDynamicLastBakeMS = 0;

   mMaxDrawDistance = 75;

   mResourcesCreated = false;

   mProbeInfo = nullptr;

   mPrefilterSize = 64;
   mPrefilterMipLevels = mLog2(F32(mPrefilterSize));
   mPrefilterMap = nullptr;
   mIrridianceMap = nullptr;

   mProbeRefOffset = Point3F::Zero;
   mEditPosOffset = false;

   mCaptureMask = REFLECTION_PROBE_CAPTURE_TYPEMASK;
}

ReflectionProbe::~ReflectionProbe()
{
   if (mEditorShapeInst)
      SAFE_DELETE(mEditorShapeInst);

   if (mReflectionModeType == StaticCubemap && mStaticCubemap)
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
   endGroup("Rendering");

   addGroup("Reflection");
      addProtectedField("radius", TypeF32, Offset(mRadius, ReflectionProbe), &_setRadius, &defaultProtectedGetFn, 
         "The name of the material used to render the mesh.");

      addProtectedField("EditPosOffset", TypeBool, Offset(mEditPosOffset, ReflectionProbe),
      &_toggleEditPosOffset, &defaultProtectedGetFn, "Toggle Edit Pos Offset Mode", AbstractClassRep::FieldFlags::FIELD_ComponentInspectors);

	   addField("refOffset", TypePoint3F, Offset(mProbeRefOffset, ReflectionProbe), "");
      addField("refScale", TypePoint3F, Offset(mProbeRefScale, ReflectionProbe), "");

      addProtectedField("ReflectionMode", TypeReflectionModeEnum, Offset(mReflectionModeType, ReflectionProbe), &_setReflectionMode, &defaultProtectedGetFn,
         "The type of mesh data to use for collision queries.");

      addField("StaticCubemap", TypeCubemapName, Offset(mCubemapName, ReflectionProbe), "Cubemap used instead of reflection texture if fullReflect is off.");

      addProtectedField("Bake", TypeBool, Offset(mBake, ReflectionProbe),
         &_doBake, &defaultProtectedGetFn, "Regenerate Voxel Grid", AbstractClassRep::FieldFlags::FIELD_ComponentInspectors);
   endGroup("Reflection");

   Con::addVariable("$Light::renderReflectionProbes", TypeBool, &RenderProbeMgr::smRenderReflectionProbes,
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
   probe->setMaskBits(EnabledMask);

   return true;
}

bool ReflectionProbe::_doBake(void *object, const char *index, const char *data)
{
   ReflectionProbe* probe = reinterpret_cast< ReflectionProbe* >(object);

   probe->bake();
   probe->setMaskBits(StaticDataMask);

   return false;
}

bool ReflectionProbe::_toggleEditPosOffset(void *object, const char *index, const char *data)
{
   ReflectionProbe* probe = reinterpret_cast< ReflectionProbe* >(object);

   probe->mEditPosOffset = !probe->mEditPosOffset;

   return false;
}

bool ReflectionProbe::_setRadius(void *object, const char *index, const char *data)
{
   ReflectionProbe* probe = reinterpret_cast<ReflectionProbe*>(object);

   if (probe->mProbeShapeType != ProbeRenderInst::Sphere)
      return false;

   probe->mObjScale = Point3F(probe->mRadius, probe->mRadius, probe->mRadius);
   probe->setMaskBits(StaticDataMask);
   
   return true;
}

bool ReflectionProbe::_setReflectionMode(void *object, const char *index, const char *data)
{
   ReflectionProbe* probe = reinterpret_cast<ReflectionProbe*>(object);

   if (!dStrcmp(data,"Static Cubemap"))
   {
      probe->mReflectionModeType = StaticCubemap;
   }
   else if (!dStrcmp(data, "Baked Cubemap"))
   {
      //Clear our cubemap if we changed it to be baked, just for cleanliness
      probe->mReflectionModeType = BakedCubemap;
      probe->mCubemapName = "";
   }

   probe->setMaskBits(StaticDataMask);

   return true;
}

bool ReflectionProbe::onAdd()
{
   if (!Parent::onAdd())
      return false;

   mEditPosOffset = false;

   mObjBox.minExtents.set(-0.5, -0.5, -0.5);
   mObjBox.maxExtents.set(0.5, 0.5, 0.5);

   // Skip our transform... it just dirties mask bits.
   Parent::setTransform(mObjToWorld);

   resetWorldBox();

   // Add this object to the scene
   addToScene();

   if (isServerObject())
   {
      if (!mPersistentId)
         mPersistentId = getOrCreatePersistentId();

      mProbeUniqueID = String::ToString(mPersistentId->getUUID().getHash());
   }

   // Refresh this object's material (if any)
   if (isClientObject())
   {
      if (!createClientResources())
         return false;

      updateProbeParams();
   }
  
   setMaskBits(-1);

   return true;
}

void ReflectionProbe::onRemove()
{
   if (isClientObject())
   {
      PROBEMGR->unregisterProbe(mProbeInfo->mProbeIdx);
      mProbeInfo = nullptr;
   }

   // Remove this object from the scene
   removeFromScene();

   Parent::onRemove();
}

void ReflectionProbe::handleDeleteAction()
{
   //we're deleting it?
   //Then we need to clear out the processed cubemaps(if we have them)

   if (mReflectionModeType != StaticCubemap)
   {
      String prefilPath = getPrefilterMapPath();
      if (Platform::isFile(prefilPath))
      {
         Platform::fileDelete(prefilPath);
      }

      String irrPath = getIrradianceMapPath();
      if (Platform::isFile(irrPath))
      {
         Platform::fileDelete(irrPath);
      }
   }

   Parent::handleDeleteAction();
}

void ReflectionProbe::setTransform(const MatrixF & mat)
{
   // Let SceneObject handle all of the matrix manipulation
   if (!mEditPosOffset)
   {
      Parent::setTransform(mat);
      setMaskBits(TransformMask);
   }
   else
   {
      mProbeRefOffset = mat.getPosition();
      setMaskBits(StaticDataMask);
   }

   mDirty = true;
}

const MatrixF& ReflectionProbe::getTransform() const 
{ 
   if (!mEditPosOffset)
      return mObjToWorld; 
   else
   {
      MatrixF transformMat = MatrixF::Identity;
      transformMat.setPosition(mProbeRefOffset);

      return transformMat;
   }
}

void ReflectionProbe::setScale(const VectorF &scale)
{
   if (!mEditPosOffset)
   {
      Parent::setScale(scale);
      setMaskBits(TransformMask);
   }
   else
   {
      mProbeRefScale = scale;
      setMaskBits(StaticDataMask);
   }

   mDirty = true;
}

const VectorF& ReflectionProbe::getScale() const
{ 
   if (!mEditPosOffset)
      return mObjScale;
   else
      return mProbeRefScale;
}

bool ReflectionProbe::writeField(StringTableEntry fieldname, const char *value)
{
   if (fieldname == StringTable->insert("Bake") || fieldname == StringTable->insert("EditPosOffset"))
      return false;

   return Parent::writeField(fieldname, value);
}

U32 ReflectionProbe::packUpdate(NetConnection *conn, U32 mask, BitStream *stream)
{
   // Allow the Parent to get a crack at writing its info
   U32 retMask = Parent::packUpdate(conn, mask, stream);

   // Write our transform information
   if (stream->writeFlag(mask & TransformMask))
   {
      stream->writeFlag(mEditPosOffset);
      mathWrite(*stream, mObjToWorld);
      mathWrite(*stream, mObjScale);
      mathWrite(*stream, mProbeRefOffset);
      mathWrite(*stream, mProbeRefScale);
   }

   if (stream->writeFlag(mask & StaticDataMask))
   {
      stream->write((U32)mProbeShapeType);
      stream->write(mRadius);
      stream->write(mProbeUniqueID);
      stream->write((U32)mReflectionModeType);
      stream->write(mCubemapName);
   }

   if (stream->writeFlag(mask & EnabledMask))
   {
      stream->writeFlag(mEnabled);
   }

   return retMask;
}

void ReflectionProbe::unpackUpdate(NetConnection *conn, BitStream *stream)
{
   // Let the Parent read any info it sent
   Parent::unpackUpdate(conn, stream);

   if (stream->readFlag())  // TransformMask
   {
      mEditPosOffset = stream->readFlag();
      mathRead(*stream, &mObjToWorld);
      mathRead(*stream, &mObjScale);

      Parent::setTransform(mObjToWorld);

      resetWorldBox();

      mathRead(*stream, &mProbeRefOffset);
      mathRead(*stream, &mProbeRefScale);      

      mDirty = true;
   }

   if (stream->readFlag())  // StaticDataMask
   {
      U32 shapeType = ProbeRenderInst::Sphere;
      stream->read(&shapeType);

      mProbeShapeType = (ProbeRenderInst::ProbeShapeType)shapeType;

      stream->read(&mRadius);

      stream->read(&mProbeUniqueID);

      U32 oldReflectModeType = mReflectionModeType;
      U32 reflectModeType = BakedCubemap;
      stream->read(&reflectModeType);
      mReflectionModeType = (ReflectionModeType)reflectModeType;

      String oldCubemapName = mCubemapName;
      stream->read(&mCubemapName);

      if(oldReflectModeType != mReflectionModeType || oldCubemapName != mCubemapName)
         mCubemapDirty = true;

      mDirty = true;
   }

   if (stream->readFlag())  // EnabledMask
   {
      mEnabled = stream->readFlag();

      mDirty = true;
   }

   if (mDirty)
   {
      updateProbeParams();
   }
}

//-----------------------------------------------------------------------------
// Object Rendering
//-----------------------------------------------------------------------------
void ReflectionProbe::updateProbeParams()
{
   if (!mProbeInfo)
      return;

   mProbeInfo->mIsEnabled = mEnabled;

   mProbeInfo->mProbeShapeType = mProbeShapeType;

   if (mProbeShapeType == ProbeRenderInst::Sphere)
      mObjScale.set(mRadius, mRadius, mRadius);

   Box3F bounds;

   if (mProbeShapeType == ProbeRenderInst::Skylight)
   {
      mProbeInfo->mPosition = Point3F::Zero;
      mProbeInfo->mTransform = MatrixF::Identity;

      mProbeInfo->mIsSkylight = true;

      F32 visDist = gClientSceneGraph->getVisibleDistance();
      Box3F skylightBounds = Box3F(visDist * 2);

      skylightBounds.setCenter(Point3F::Zero);

      bounds = skylightBounds;

      setGlobalBounds();

      mProbeInfo->mScore = -1.0f;
   }
   else
   {
      MatrixF transform = getTransform();
      mProbeInfo->mPosition = getPosition();

      transform.scale(getScale());
      mProbeInfo->mTransform = transform.inverse();

      mProbeInfo->mIsSkylight = false;

      bounds = mWorldBox;

      mProbeInfo->mScore = mMaxDrawDistance;
   }

   // Skip our transform... it just dirties mask bits.
   Parent::setTransform(mObjToWorld);

   resetWorldBox();

   mProbeInfo->mBounds = bounds;
   mProbeInfo->mExtents = getScale();
   mProbeInfo->mRadius = mRadius;

   mProbeInfo->mProbeRefOffset = mProbeRefOffset;
   mProbeInfo->mProbeRefScale = mProbeRefScale;

   mProbeInfo->mDirty = true;

   if (mCubemapDirty)
   {
      if (mReflectionModeType == StaticCubemap)
         processStaticCubemap();
      else if (mReflectionModeType == BakedCubemap)
         processBakedCubemap();
      else
         processDynamicCubemap();
   }

   PROBEMGR->updateProbes();
}

void ReflectionProbe::processDynamicCubemap()
{
   //if (!mProbeInfo)
      return;

   mEnabled = false;

   if (mReflectionModeType == DynamicCubemap && !mDynamicCubemap.isNull())
   {
      mProbeInfo->mPrefilterCubemap = mDynamicCubemap;

      //mCubeReflector.registerReflector(this, reflectorDesc); //need to decide how we wanna do the reflectorDesc. static name or a field
   }

   if (mEnabled)
      mProbeInfo->mIsEnabled = true;
   else
      mProbeInfo->mIsEnabled = false;

   mCubemapDirty = false;

   //Update the probe manager with our new texture!
   //if (!mProbeInfo->mIsSkylight && mProbeInfo->mPrefilterCubemap->isInitialized() && mProbeInfo->mIrradianceCubemap->isInitialized())
   //   PROBEMGR->updateProbeTexture(mProbeInfo->mProbeIdx);
}

void ReflectionProbe::processBakedCubemap()
{
   if (!mProbeInfo)
      return;

   mProbeInfo->mIsEnabled = false;

   if ((mReflectionModeType != BakedCubemap) || mProbeUniqueID.isEmpty())
      return;

   String irrPath = getIrradianceMapPath();
   if (Platform::isFile(irrPath))
   {
      mIrridianceMap->setCubemapFile(FileName(irrPath));
      mIrridianceMap->updateFaces();
   }

   if (mIrridianceMap == nullptr || mIrridianceMap->mCubemap.isNull())
   {
      Con::errorf("ReflectionProbe::processDynamicCubemap() - Unable to load baked irradiance map at %s", getIrradianceMapPath().c_str());
      return;
   }

   String prefilPath = getPrefilterMapPath();
   if (Platform::isFile(prefilPath))
   {
      mPrefilterMap->setCubemapFile(FileName(prefilPath));
      mPrefilterMap->updateFaces();
   }

   if (mPrefilterMap == nullptr || mPrefilterMap->mCubemap.isNull())
   {
      Con::errorf("ReflectionProbe::processDynamicCubemap() - Unable to load baked prefilter map at %s", getPrefilterMapPath().c_str());
      return;
   }

   mProbeInfo->mPrefilterCubemap = mPrefilterMap->mCubemap;
   mProbeInfo->mIrradianceCubemap = mIrridianceMap->mCubemap;

   if (mEnabled && mProbeInfo->mPrefilterCubemap->isInitialized() && mProbeInfo->mIrradianceCubemap->isInitialized())
   {
      mProbeInfo->mIsEnabled = true;

      mCubemapDirty = false;

      //Update the probe manager with our new texture!
      PROBEMGR->updateProbeTexture(mProbeInfo);
   }
}

void ReflectionProbe::processStaticCubemap()
{
   if (!mProbeInfo)
      return;

   mProbeInfo->mIsEnabled = false;

   String path = Con::getVariable("$pref::ReflectionProbes::CurrentLevelPath", "levels/");

   char irradFileName[256];
   dSprintf(irradFileName, 256, "%s_Irradiance.dds", path.c_str(), mCubemapName.c_str());

   if (Platform::isFile(irradFileName))
   {
      mIrridianceMap->setCubemapFile(FileName(irradFileName));
      mIrridianceMap->updateFaces();
   }

   if (mIrridianceMap == nullptr || mIrridianceMap->mCubemap.isNull())
   {
      Con::errorf("ReflectionProbe::processStaticCubemap() - Unable to load baked irradiance map at %s", irradFileName);
      return;
   }

   char prefilterFileName[256];
   dSprintf(prefilterFileName, 256, "%s%s_Prefilter.dds", path.c_str(), mCubemapName.c_str());

   if (Platform::isFile(prefilterFileName))
   {
      mPrefilterMap->setCubemapFile(FileName(prefilterFileName));
      mPrefilterMap->updateFaces();
   }

   if (mPrefilterMap == nullptr || mPrefilterMap->mCubemap.isNull())
   {
      Con::errorf("ReflectionProbe::processStaticCubemap() - Unable to load baked prefilter map at %s", prefilterFileName);
      return;
   }

   if (!Platform::isFile(prefilterFileName) || !Platform::isFile(irradFileName))
   {
      //If we are missing either of the files, just re-run the bake
      Sim::findObject(mCubemapName, mStaticCubemap);

      if (!mStaticCubemap)
      {
         Con::errorf("ReflectionProbe::updateMaterial() - unable to find static cubemap file!");
         return;
      }

      if (mStaticCubemap->mCubemap == nullptr)
      {
         mStaticCubemap->createMap();
         mStaticCubemap->updateFaces();
      }

      if (mUseHDRCaptures)
      {
         mIrridianceMap->mCubemap->initDynamic(mPrefilterSize, GFXFormatR16G16B16A16F);
         mPrefilterMap->mCubemap->initDynamic(mPrefilterSize, GFXFormatR16G16B16A16F);
      }
      else
      {
         mIrridianceMap->mCubemap->initDynamic(mPrefilterSize, GFXFormatR8G8B8A8);
         mPrefilterMap->mCubemap->initDynamic(mPrefilterSize, GFXFormatR8G8B8A8);
      }

      GFXTextureTargetRef renderTarget = GFX->allocRenderToTextureTarget(false);

      IBLUtilities::GenerateIrradianceMap(renderTarget, mStaticCubemap->mCubemap, mIrridianceMap->mCubemap);
      IBLUtilities::GeneratePrefilterMap(renderTarget, mStaticCubemap->mCubemap, mPrefilterMipLevels, mPrefilterMap->mCubemap);

      IBLUtilities::SaveCubeMap(irradFileName, mIrridianceMap->mCubemap);
      IBLUtilities::SaveCubeMap(prefilterFileName, mPrefilterMap->mCubemap);
   }

   if ((mIrridianceMap != nullptr || !mIrridianceMap->mCubemap.isNull()) && (mPrefilterMap != nullptr || !mPrefilterMap->mCubemap.isNull()))
   {
      mProbeInfo->mPrefilterCubemap = mPrefilterMap->mCubemap;
      mProbeInfo->mIrradianceCubemap = mIrridianceMap->mCubemap;
   }

   if (mEnabled && mProbeInfo->mPrefilterCubemap->isInitialized() && mProbeInfo->mIrradianceCubemap->isInitialized())
   {
      mProbeInfo->mIsEnabled = true;

      mCubemapDirty = false;

      //Update the probe manager with our new texture!
      PROBEMGR->updateProbeTexture(mProbeInfo);
   }
}

bool ReflectionProbe::createClientResources()
{
   if (mProbeInfo == nullptr)
   {
      mProbeInfo = PROBEMGR->registerProbe();
      if (!mProbeInfo)
         return false;

      mProbeInfo->mIsEnabled = false;
   }

   //irridiance resources
   if (!mIrridianceMap)
   {
      mIrridianceMap = new CubemapData();
      mIrridianceMap->registerObject();

      mIrridianceMap->createMap();
   }

   //
   if (!mPrefilterMap)
   {
      mPrefilterMap = new CubemapData();
      mPrefilterMap->registerObject();

      mPrefilterMap->createMap();
   }

   mResourcesCreated = true;
   mCubemapDirty = true;

   return true;
}

String ReflectionProbe::getPrefilterMapPath()
{
   if (mProbeUniqueID.isEmpty())
   {
      Con::errorf("ReflectionProbe::getPrefilterMapPath() - We don't have a set output path or persistant id, so no valid path can be provided!");
      return "";
   }

   String path = Con::getVariable("$pref::ReflectionProbes::CurrentLevelPath", "levels/");

   char fileName[256];
   dSprintf(fileName, 256, "%s%s_Prefilter.dds", path.c_str(), mProbeUniqueID.c_str());

   return fileName;
}

String ReflectionProbe::getIrradianceMapPath()
{
   if (mProbeUniqueID.isEmpty())
   {
      Con::errorf("ReflectionProbe::getIrradianceMapPath() - We don't have a set output path or persistant id, so no valid path can be provided!");
      return "";
   }

   String path = Con::getVariable("$pref::ReflectionProbes::CurrentLevelPath", "levels/");

   char fileName[256];
   dSprintf(fileName, 256, "%s%s_Irradiance.dds", path.c_str(), mProbeUniqueID.c_str());

   return fileName;
}

void ReflectionProbe::bake()
{
   if (mReflectionModeType != BakedCubemap)
      return;

   PROBEMGR->bakeProbe(this);

   setMaskBits(-1);
}

//-----------------------------------------------------------------------------
//Rendering of editing/debug stuff
//-----------------------------------------------------------------------------
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

void ReflectionProbe::prepRenderImage(SceneRenderState *state)
{
   if (!mEnabled || !RenderProbeMgr::smRenderReflectionProbes)
      return;

   Point3F distVec = getRenderPosition() - state->getCameraPosition();
   F32 dist = distVec.len();

   //Culling distance. Can be adjusted for performance options considerations via the scalar
   if (dist > mMaxDrawDistance * Con::getFloatVariable("$pref::GI::ProbeDrawDistScale", 1.0))
   {
      mProbeInfo->mScore = mMaxDrawDistance;
      return;
   }

   if (mReflectionModeType == DynamicCubemap && mRefreshRateMS < (Platform::getRealMilliseconds() - mDynamicLastBakeMS))
   {
      bake();
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
   //PROBEMGR->registerProbe(mProbeInfoIdx);

   if (ReflectionProbe::smRenderPreviewProbes && gEditingMission && mPrefilterMap != nullptr)
   {
      if(!mEditorShapeInst)
         createGeometry();

      GFXTransformSaver saver;

      // Calculate the distance of this object from the camera
      Point3F cameraOffset;
      getRenderTransform().getColumn(3, &cameraOffset);
      cameraOffset -= state->getDiffuseCameraPosition();
      dist = cameraOffset.len();
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
   if (!RenderProbeMgr::smRenderReflectionProbes)
      return;

   GFXDrawUtil *draw = GFX->getDrawUtil();

   GFXStateBlockDesc desc;
   desc.setZReadWrite(true, false);
   desc.setCullMode(GFXCullNone);
   desc.setBlend(true);
   //desc.fillMode = GFXFillWireframe;

   // Base the sphere color on the light color.
   ColorI color = ColorI(255, 0, 255, 63);

   const MatrixF worldToObjectXfm = mObjToWorld;
   if (mProbeShapeType == ProbeRenderInst::Sphere)
   {
      draw->drawSphere(desc, mRadius, getPosition(), color);
   }
   else
   {
      Point3F tscl = worldToObjectXfm.getScale();

      Box3F projCube(-mObjScale/2, mObjScale / 2);
      projCube.setCenter(getPosition());
      draw->drawCube(desc, projCube, color, &worldToObjectXfm);
   }

   Point3F renderPos = getRenderTransform().getPosition();

   Box3F refCube = Box3F(-mProbeRefScale / 2, mProbeRefScale / 2);
   refCube.setCenter(renderPos + mProbeRefOffset);
   color = ColorI(0, 255, 255, 63);
   draw->drawCube(desc, refCube, color, &worldToObjectXfm);
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

DefineEngineMethod(ReflectionProbe, Bake, void, (), ,
   "@brief returns true if control object is inside the fog\n\n.")
{
   ReflectionProbe *clientProbe = (ReflectionProbe*)object->getClientObject();

   if (clientProbe)
   {
      clientProbe->bake();
   }
}
