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
#include "renderProbeMgr.h"
#include "math/util/sphereMesh.h"
#include "math/util/matrixSet.h"
#include "renderInstance/renderDeferredMgr.h"
#include "math/mPolyhedron.impl.h"
#include "gfx/gfxTransformSaver.h"
#include "lighting/advanced/advancedLightBinManager.h" //for ssao
#include "gfx/gfxDebugEvent.h"
#include "shaderGen/shaderGenVars.h"
#include "materials/shaderData.h"
#include "scene/reflectionManager.h"

#include "postFx/postEffect.h"
#include "T3D/lighting/reflectionProbe.h"
#include "T3D/lighting/IBLUtilities.h"
#include "T3D/Scene.h"

//For our cameraQuery setup
#include "T3D/gameTSCtrl.h"


#define TORQUE_GFX_VISUAL_DEBUG //renderdoc debugging

IMPLEMENT_CONOBJECT(RenderProbeMgr);

ConsoleDocClass( RenderProbeMgr, 
   "@brief This render bin handles the rendering of reflection probes to provide IBL\n"
   "lighting for PBR\n\n"
   "Probes when added to the scene, are registered to the Manager, and then during the steps\n"
   "leading up to the frame being rendered, the probes submit to the Manager that they are ready to be rendered\n"
   "resulting in them being added to the active list.\n"
   "When the manager is invoked to render, it processes the active probe list and finds the best probes based on\n"
   "settings like max probes per frame, probe score, etc to get the final list of probes to be submitted to the shader.\n\n"
   "@ingroup RenderBin\n" );

RenderProbeMgr *RenderProbeMgr::smProbeManager = NULL;

// This variable is a global toggle on if reflection probes should be rendered or not
bool RenderProbeMgr::smRenderReflectionProbes = true;

// This variable defines the maximum draw distance of a probe.
F32 RenderProbeMgr::smMaxProbeDrawDistance = 100;

// This variable defines the maximum number of probes that can be rendered in a single frame in deferred
S32 RenderProbeMgr::smMaxProbesPerFrame = 8;

S32 RenderProbeMgr::smProbeBakeResolution = 64;

//
//
ProbeRenderInst::ProbeRenderInst() :
   mCubemapIndex(0),
   mProbeInfo(nullptr)
{
}

ProbeRenderInst::~ProbeRenderInst()
{
}

void ProbeRenderInst::set(const ProbeRenderInst *probe)
{
   mCubemapIndex = probe->mCubemapIndex;
   mProbeInfo = probe->mProbeInfo;
}

//
//
ProbeShaderConstants::ProbeShaderConstants()
   : mInit(false),
   mShader(NULL),
   mProbePositionArraySC(NULL),
   mProbeRefPosArraySC(NULL),
   mRefScaleArraySC(NULL),
   mProbeConfigDataArraySC(NULL),
   mProbeSpecularCubemapArraySC(NULL),
   mProbeIrradianceCubemapArraySC(NULL),
   mProbeCountSC(NULL),
   mBRDFTextureMap(NULL),
   mWetnessTextureMap(NULL),   
   mSkylightCubemapIdxSC(NULL),
   mSkylightDampSC(NULL),
   mWorldToObjArraySC(NULL),
   mMaxProbeDrawDistanceSC(NULL)
{
}

ProbeShaderConstants::~ProbeShaderConstants()
{
   if (mShader.isValid())
   {
      mShader->getReloadSignal().remove(this, &ProbeShaderConstants::_onShaderReload);
      mShader = NULL;
   }
}

void ProbeShaderConstants::init(GFXShader* shader)
{
   if (mShader.getPointer() != shader)
   {
      if (mShader.isValid())
         mShader->getReloadSignal().remove(this, &ProbeShaderConstants::_onShaderReload);

      mShader = shader;
      mShader->getReloadSignal().notify(this, &ProbeShaderConstants::_onShaderReload);
   }
   
   //Reflection Probes
   mProbePositionArraySC = shader->getShaderConstHandle(ShaderGenVars::probePositionArray);
   mProbeRefPosArraySC = shader->getShaderConstHandle(ShaderGenVars::probeRefPosArray);
   mRefScaleArraySC = shader->getShaderConstHandle(ShaderGenVars::refScaleArray);
   mWorldToObjArraySC = shader->getShaderConstHandle(ShaderGenVars::worldToObjArray);
   mProbeConfigDataArraySC = shader->getShaderConstHandle(ShaderGenVars::probeConfigDataArray);
   mProbeSpecularCubemapArraySC = shader->getShaderConstHandle(ShaderGenVars::specularCubemapAR);
   mProbeIrradianceCubemapArraySC = shader->getShaderConstHandle(ShaderGenVars::irradianceCubemapAR);
   mProbeCountSC = shader->getShaderConstHandle(ShaderGenVars::probeCount);

   mBRDFTextureMap = shader->getShaderConstHandle(ShaderGenVars::BRDFTextureMap);
   mWetnessTextureMap = shader->getShaderConstHandle(ShaderGenVars::WetnessTextureMap);

   mSkylightCubemapIdxSC = shader->getShaderConstHandle(ShaderGenVars::skylightCubemapIdx);   
   mSkylightDampSC = shader->getShaderConstHandle(ShaderGenVars::skylightDamp);

   mMaxProbeDrawDistanceSC = shader->getShaderConstHandle(ShaderGenVars::maxProbeDrawDistance);

   mInit = true;
}

bool ProbeShaderConstants::isValid()
{
   if (mProbePositionArraySC->isValid() &&
      mProbeConfigDataArraySC->isValid() &&
      mRefScaleArraySC->isValid() &&
      mProbeSpecularCubemapArraySC->isValid() &&
      mProbeIrradianceCubemapArraySC->isValid())
      return true;

   return false;
}

void ProbeShaderConstants::_onShaderReload()
{
   if (mShader.isValid())
      init(mShader);
}

//
//
RenderProbeMgr::RenderProbeMgr()
: RenderBinManager(RenderPassManager::RIT_Probes, 1.0f, 1.0f),
   mLastShader(nullptr),
   mLastConstants(nullptr),
   mHasSkylight(false),
   mSkylightCubemapIdx(-1),
   mSkylightDamp(true),
   mCubeMapCount(0),
   mUseHDRCaptures(true)
{
   mEffectiveProbeCount = 0;
   mMipCount = 0;

   mProbeArrayEffect = nullptr;

   smProbeManager = this;

   mCubeMapCount = 0;
   mCubeSlotCount = PROBE_ARRAY_SLOT_BUFFER_SIZE;

   for (U32 i = 0; i < PROBE_MAX_COUNT; i++)
   {
      mCubeMapSlots[i] = false;
   }
}

RenderProbeMgr::RenderProbeMgr(RenderInstType riType, F32 renderOrder, F32 processAddOrder)
 : RenderBinManager(riType, renderOrder, processAddOrder)
{
   mCubeMapCount = 0;
   dMemset(mCubeMapSlots, false, sizeof(mCubeMapSlots));
   mCubeSlotCount = PROBE_ARRAY_SLOT_BUFFER_SIZE;
   mEffectiveProbeCount = 0;
   mHasSkylight = false;
   mSkylightCubemapIdx = -1;
   mSkylightDamp = true;
   mLastConstants = nullptr;
   mMipCount = 0;
   mUseHDRCaptures = true;
}

RenderProbeMgr::~RenderProbeMgr()
{
   mLastShader = NULL;
   mLastConstants = NULL;

   for (ProbeConstantMap::Iterator i = mConstantLookup.begin(); i != mConstantLookup.end(); i++)
   {
      if (i->value)
         SAFE_DELETE(i->value);
   }
   mConstantLookup.clear();
}

bool RenderProbeMgr::onAdd()
{
   if (!Parent::onAdd())
      return false;

   mIrradianceArray = GFXCubemapArrayHandle(GFX->createCubemapArray());
   mPrefilterArray = GFXCubemapArrayHandle(GFX->createCubemapArray());

   U32 scaledSize = getProbeTexSize();
   //pre-allocate a few slots
   mIrradianceArray->init(PROBE_ARRAY_SLOT_BUFFER_SIZE, scaledSize, PROBE_FORMAT);
   mPrefilterArray->init(PROBE_ARRAY_SLOT_BUFFER_SIZE, scaledSize, PROBE_FORMAT);
   mCubeSlotCount = PROBE_ARRAY_SLOT_BUFFER_SIZE;

   String brdfTexturePath = GFXTextureManager::getBRDFTexturePath();
   if (!mBRDFTexture.set(brdfTexturePath, &GFXTexturePersistentProfile, "BRDFTexture"))
   {
      Con::errorf("RenderProbeMgr::onAdd: Failed to load BRDF Texture");
      return false;
   } 

   String wetnessTexturePath = GFXTextureManager::getWetnessTexturePath();
   if (!mWetnessTexture.set(wetnessTexturePath, &GFXTexturePersistentProfile, "WetnessTexture"))
   {
      Con::errorf("RenderProbeMgr::onAdd: Failed to load Wetness Texture");
      return false;
   }
   return true;
}

void RenderProbeMgr::onRemove()
{
   Parent::onRemove();
}

void RenderProbeMgr::initPersistFields()
{
   docsURL;
   Parent::initPersistFields();
}

void RenderProbeMgr::consoleInit()
{
   Parent::consoleInit();

   // Vars for debug rendering while the RoadEditor is open, only used if smEditorOpen is true.
   Con::addVariable("$pref::maxProbeDrawDistance", TypeF32, &RenderProbeMgr::smMaxProbeDrawDistance, "Max distance for reflection probes to render.\n");
   Con::addVariable("$pref::MaxProbesPerFrame", TypeS32, &RenderProbeMgr::smMaxProbesPerFrame, "Max number of Environment Probes that can be rendered per-frame.\n");
   Con::addVariable("$pref::ReflectionProbes::BakeResolution", TypeS32, &RenderProbeMgr::smProbeBakeResolution, "");
   
}

//=============================================================================
// Utility functions for processing and setting up the probes for rendering
//=============================================================================
S32 QSORT_CALLBACK RenderProbeMgr::_probeScoreCmp(const ProbeRenderInst* a, const  ProbeRenderInst* b)
{
   F32 diff = a->mProbeInfo->mScore - b->mProbeInfo->mScore;
   return diff > 0 ? 1 : diff < 0 ? -1 : 0;
}
void RenderProbeMgr::getBestProbes(const Point3F& objPosition, ProbeDataSet* probeDataSet)
{
   PROFILE_SCOPE(ProbeManager_getBestProbes);

   //Array rendering
   U32 probeCount = mActiveProbes.size();

   Vector<S8> bestPickProbes;
   bestPickProbes.setSize(probeDataSet->maxProbeCount);
   bestPickProbes.fill(-1);

   mHasSkylight = false;
   probeDataSet->skyLightIdx = -1;

   probeDataSet->effectiveProbeCount = 0;
   for (U32 i = 0; i < probeCount; i++)
   {
      //Check if we've already got a skylight. If we do and we've otherwise filled to our max amounto of probes alloewed, then bail
      if (mHasSkylight && probeDataSet->effectiveProbeCount >= probeDataSet->maxProbeCount)
         break;

      const ProbeRenderInst& curEntry = mActiveProbes[i];

      //Obviously, if the probe is marked as not enabled, we skip
      if (!curEntry.mProbeInfo->mIsEnabled)
         continue;

      if (curEntry.mProbeInfo->mProbeShapeType != ReflectionProbe::ProbeInfo::Skylight)
      {
         if (probeDataSet->effectiveProbeCount < probeDataSet->maxProbeCount)
         {
            bestPickProbes[probeDataSet->effectiveProbeCount] = i;
            probeDataSet->effectiveProbeCount++;
         }
      }
      else
      {
         probeDataSet->skyLightIdx = curEntry.mCubemapIndex;
         probeDataSet->skyLightDamp = curEntry.mProbeInfo->mCanDamp;
         mHasSkylight = true;
      }
   }

   //If we, for whatever reason, have nothing, bail now
   if (mHasSkylight == false && probeDataSet->effectiveProbeCount == 0)
      return;

   //Grab our best probe picks
   for (U32 i = 0; i < bestPickProbes.size(); i++)
   {
      if (bestPickProbes[i] == -1)
         continue;

      const ProbeRenderInst& curEntry = mActiveProbes[bestPickProbes[i]];
      probeDataSet->probeConfigArray[i] = Point4F(curEntry.mProbeInfo->mProbeShapeType,
         curEntry.mProbeInfo->mRadius,
         curEntry.mProbeInfo->mAtten,
         curEntry.mCubemapIndex);

      MatrixF p2A = curEntry.mProbeInfo->mTransform;
      probeDataSet->probeWorldToObjArray[i] = p2A;
      p2A.inverse();
      probeDataSet->refScaleArray[i] = curEntry.mProbeInfo->mProbeRefScale / (p2A.getScale()*2);
      probeDataSet->refScaleArray[i].w = curEntry.mProbeInfo->mCanDamp? 1.0 : 0.0;

      Point3F probePos = curEntry.mProbeInfo->mObject->getPosition();
      Point3F refPos = probePos + curEntry.mProbeInfo->mProbeRefOffset * probeDataSet->refScaleArray[i].asPoint3F();

      probeDataSet->probePositionArray[i] = Point4F(probePos.x, probePos.y, probePos.z, 0);
      probeDataSet->probeRefPositionArray[i] = Point4F(refPos.x, refPos.y, refPos.z, 0);
   }
}

void RenderProbeMgr::registerProbe(ReflectionProbe::ProbeInfo* newProbe)
{
   //Can't have over the probe limit
   if (mRegisteredProbes.size() + 1 >= PROBE_MAX_COUNT)
      return;

   ProbeRenderInst newProbeRenderInst;
   newProbeRenderInst.mProbeInfo = newProbe;

   const U32 cubeIndex = _findNextEmptyCubeSlot();
   if (cubeIndex == INVALID_CUBE_SLOT)
   {
      Con::warnf("RenderProbeMgr::registerProbe() - Invalid cubemap slot.");
      return;
   }

   //check if we need to resize the cubemap array
   if (cubeIndex >= mCubeSlotCount)
   {
      //alloc temp array handles
      GFXCubemapArrayHandle irr = GFXCubemapArrayHandle(GFX->createCubemapArray());
      GFXCubemapArrayHandle prefilter = GFXCubemapArrayHandle(GFX->createCubemapArray());

      U32 scaledSize = getProbeTexSize();
      irr->init(mCubeSlotCount + PROBE_ARRAY_SLOT_BUFFER_SIZE, scaledSize, PROBE_FORMAT);
      prefilter->init(mCubeSlotCount + PROBE_ARRAY_SLOT_BUFFER_SIZE, scaledSize, PROBE_FORMAT);

      mIrradianceArray->copyTo(irr);
      mPrefilterArray->copyTo(prefilter);

      //assign the temp handles to the new ones, this will destroy the old ones as well
      mIrradianceArray = irr;
      mPrefilterArray = prefilter;

      mCubeSlotCount += PROBE_ARRAY_SLOT_BUFFER_SIZE;
   }

   newProbeRenderInst.mCubemapIndex = cubeIndex;
   //mark cubemap slot as taken
   mCubeMapSlots[cubeIndex] = true;
   mCubeMapCount++;

   mRegisteredProbes.push_back(newProbeRenderInst);

#ifdef TORQUE_DEBUG
   Con::warnf("RenderProbeMgr::registerProbe() - Registered probe %u to cubeIndex %u", newProbe->mObject->getId(), cubeIndex);
#endif
}

void RenderProbeMgr::unregisterProbe(ReflectionProbe::ProbeInfo* probeInfo)
{
   ProbeRenderInst* probe = findProbeInst(probeInfo);
   if (probe == nullptr)
      return;

   if (probe->mCubemapIndex == INVALID_CUBE_SLOT)
      return;

   //mark cubemap slot as available now
   mCubeMapSlots[probe->mCubemapIndex] = false;
   mCubeMapCount--;

   mRegisteredProbes.erase(probe);
}

void RenderProbeMgr::submitProbe(ReflectionProbe::ProbeInfo* probe)
{
   ProbeRenderInst* probeInst = findProbeInst(probe);
   mActiveProbes.push_back(*probeInst);
}

PostEffect* RenderProbeMgr::getProbeArrayEffect()
{
   if (!mProbeArrayEffect)
   {
      mProbeArrayEffect = dynamic_cast<PostEffect*>(Sim::findObject("reflectionProbeArrayPostFX"));

      if (!mProbeArrayEffect)
         return nullptr;

      mProbeArrayEffect->setShaderConst("$numProbes", (S32)0);
      mProbeArrayEffect->setShaderConst("$skylightCubemapIdx", (S32)-1);
      mProbeArrayEffect->setShaderConst(ShaderGenVars::skylightDamp, (S32)true);
      mProbeArrayEffect->setShaderConst("$cubeMips", (float)0);
      mProbeArrayEffect->setShaderConst("$maxProbeDrawDistance", smMaxProbeDrawDistance);

   }
   return mProbeArrayEffect;
}

U32 RenderProbeMgr::getProbeTexSize()
{
   U32 scaledSize = RenderProbeMgr::smProbeBakeResolution;
   U32 downscalePower = 0;// GFXTextureManager::smTextureReductionLevel;
   if (downscalePower != 0)
   {
      // Otherwise apply the appropriate scale...
      scaledSize >>= downscalePower;
   }
   return scaledSize;
}

void RenderProbeMgr::updateProbeTexture(ReflectionProbe::ProbeInfo* probeInfo)
{
   //If we don't have a registered probe, there's no point in updating the cubemap array for it
   ProbeRenderInst* probe = findProbeInst(probeInfo);
   if (probe == nullptr)
      return;
   U32 scaledSize = getProbeTexSize();
   //Some basic sanity checking that we have valid cubemaps to work with
   if (probeInfo->mIrradianceCubemap.isNull() || !probeInfo->mIrradianceCubemap->isInitialized() ||
      probeInfo->mIrradianceCubemap->getSize() != scaledSize)
   {
      Con::errorf("RenderProbeMgr::updateProbeTexture() - tried to update a probe's texture with an invalid or uninitialized irradiance map!");
      return;
   }

   if (probeInfo->mPrefilterCubemap.isNull() || !probeInfo->mPrefilterCubemap->isInitialized() ||
      probeInfo->mPrefilterCubemap->getSize() != scaledSize)
   {
      Con::errorf("RenderProbeMgr::updateProbeTexture() - tried to update a probe's texture with an invalid or uninitialized specular map!");
      return;
   }

   //Run the update on the array pair with the probe's cubemaps and index
   const U32 cubeIndex = probe->mCubemapIndex;
   mIrradianceArray->updateTexture(probeInfo->mIrradianceCubemap, cubeIndex);
   mPrefilterArray->updateTexture(probeInfo->mPrefilterCubemap, cubeIndex);

#ifdef TORQUE_DEBUG
   Con::warnf("UpdatedProbeTexture - probe id: %u on cubeIndex %u, Irrad validity: %d, Prefilter validity: %d", probeInfo->mObject->getId(), cubeIndex,
      probeInfo->mIrradianceCubemap->isInitialized(), probeInfo->mPrefilterCubemap->isInitialized());
#endif
}

void RenderProbeMgr::reloadTextures()
{
   U32 probeCount = mRegisteredProbes.size();
   for (U32 i = 0; i < probeCount; i++)
   {
      updateProbeTexture(mRegisteredProbes[i].mProbeInfo);
   }
}

void RenderProbeMgr::preBake()
{
   Con::setVariable("$Probes::Capturing", "1");
   mRenderMaximumNumOfLights = AdvancedLightBinManager::smMaximumNumOfLights;
   mRenderUseLightFade = AdvancedLightBinManager::smUseLightFade;

   AdvancedLightBinManager::smMaximumNumOfLights = -1;
   AdvancedLightBinManager::smUseLightFade = false;
}
void RenderProbeMgr::postBake()
{
   Con::setVariable("$Probes::Capturing", "0");
   AdvancedLightBinManager::smMaximumNumOfLights = mRenderMaximumNumOfLights;
   AdvancedLightBinManager::smUseLightFade = mRenderUseLightFade;
}
void RenderProbeMgr::bakeProbe(ReflectionProbe* probe)
{
   GFXDEBUGEVENT_SCOPE(RenderProbeMgr_Bake, ColorI::WHITE);

   Con::warnf("RenderProbeMgr::bakeProbe() - Beginning bake!");
   U32 startMSTime = Platform::getRealMilliseconds();

   preBake();

   String path = Con::getVariable("$pref::ReflectionProbes::CurrentLevelPath", "levels/");
   U32 resolution = Con::getIntVariable("$pref::ReflectionProbes::BakeResolution", 64);
   U32 prefilterMipLevels = mLog2(F32(resolution)) + 1;
   bool renderWithProbes = Con::getIntVariable("$pref::ReflectionProbes::RenderWithProbes", false);

   ReflectionProbe* clientProbe = nullptr;

   if (probe->isServerObject())
      clientProbe = static_cast<ReflectionProbe*>(probe->getClientObject());
   else
      return;

   if (clientProbe == nullptr)
      return;

   String probePrefilterPath = clientProbe->getPrefilterMapPath();
   String probeIrradPath = clientProbe->getIrradianceMapPath();

   if (clientProbe->mReflectionModeType != ReflectionProbe::DynamicCubemap)
   {
      //Prep our bake path
      if (probePrefilterPath.isEmpty() || probeIrradPath.isEmpty())
      {
         Con::errorf("RenderProbeMgr::bake() - Unable to bake our captures because probe doesn't have a path set");
         return;
   }
   }

   // Save the current transforms so we can restore
   // it for child control rendering below.
   GFXTransformSaver saver;

   bool probeRenderState = RenderProbeMgr::smRenderReflectionProbes;

   F32 farPlane = 1000.0f;

   ReflectorDesc reflDesc;
   reflDesc.texSize = resolution;
   reflDesc.farDist = farPlane;
   reflDesc.detailAdjust = (F32)resolution;
   reflDesc.objectTypeMask = probe->mCaptureMask;

   CubeReflector cubeRefl;
   cubeRefl.registerReflector(probe, &reflDesc);

   ReflectParams reflParams;

   //need to get the query somehow. Likely do some sort of get function to fetch from the guiTSControl that's active
   CameraQuery query; //need to get the last cameraQuery
   query.fov = 90; //90 degree slices for each of the 6 sides
   query.nearPlane = 0.1f;
   query.farPlane = farPlane;
   query.headMatrix = MatrixF();
   query.cameraMatrix = clientProbe->getTransform();

   Frustum culler;
   culler.set(false,
      query.fov,
      1.0f,
      query.nearPlane,
      query.farPlane,
      query.cameraMatrix);

   S32 stereoTarget = GFX->getCurrentStereoTarget();

   Point2I maxRes(2048, 2048); //basically a boundary so we don't go over this and break stuff

   reflParams.culler = culler;
   reflParams.eyeId = stereoTarget;
   reflParams.query = &query;
   reflParams.startOfUpdateMs = startMSTime;
   reflParams.viewportExtent = maxRes;

   if (!renderWithProbes)
      RenderProbeMgr::smRenderReflectionProbes = false;

   GFXFormat reflectFormat;

   if (mUseHDRCaptures)
      reflectFormat = GFXFormatR16G16B16A16F;
   else
      reflectFormat = GFXFormatR8G8B8A8;
   const GFXFormat oldRefFmt = REFLECTMGR->getReflectFormat();
   REFLECTMGR->setReflectFormat(reflectFormat);

   cubeRefl.updateReflection(reflParams, clientProbe->getTransform().getPosition() + clientProbe->mProbeRefOffset);

   //Now, save out the maps
   //create irridiance cubemap
   if (cubeRefl.getCubemap())
   {
      //Just to ensure we're prepped for the generation
      clientProbe->createClientResources();

      //Prep it with whatever resolution we've dictated for our bake
      clientProbe->mIrridianceMap->mCubemap->initDynamic(resolution, reflectFormat);
      clientProbe->mPrefilterMap->mCubemap->initDynamic(resolution, reflectFormat);

      GFXTextureTargetRef renderTarget = GFX->allocRenderToTextureTarget(false);

      IBLUtilities::GenerateIrradianceMap(renderTarget, cubeRefl.getCubemap(), clientProbe->mIrridianceMap->mCubemap);
      IBLUtilities::GeneratePrefilterMap(renderTarget, cubeRefl.getCubemap(), prefilterMipLevels, clientProbe->mPrefilterMap->mCubemap);

      U32 endMSTime = Platform::getRealMilliseconds();
      F32 diffTime = F32(endMSTime - startMSTime);
      Con::warnf("RenderProbeMgr::bake() - Finished Capture! Took %g milliseconds", diffTime);
      Con::warnf("RenderProbeMgr::bake() - Beginning save now!");

      IBLUtilities::SaveCubeMap(clientProbe->getIrradianceMapPath(), clientProbe->mIrridianceMap->mCubemap);
      IBLUtilities::SaveCubeMap(clientProbe->getPrefilterMapPath(), clientProbe->mPrefilterMap->mCubemap);
   }
   else
   {
      Con::errorf("RenderProbeMgr::bake() - Didn't generate a valid scene capture cubemap, unable to generate prefilter and irradiance maps!");
   }

   if (!renderWithProbes)
      RenderProbeMgr::smRenderReflectionProbes = probeRenderState;

   postBake();

   cubeRefl.unregisterReflector();

   U32 endMSTime = Platform::getRealMilliseconds();
   F32 diffTime = F32(endMSTime - startMSTime);

   probe->setMaskBits(-1);

   Con::warnf("RenderProbeMgr::bake() - Finished bake! Took %g milliseconds", diffTime);
   REFLECTMGR->setReflectFormat(oldRefFmt);
}

void RenderProbeMgr::bakeProbes()
{
   Vector<ReflectionProbe*> probes;

   Scene::getRootScene()->findObjectByType<ReflectionProbe>(probes);

   for (U32 i = 0; i < probes.size(); i++)
   {
      if (probes[i]->isClientObject())
         continue;

      bakeProbe(probes[i]);
   }
}

//=============================================================================
// Forward Rendering functions
//=============================================================================
ProbeShaderConstants* RenderProbeMgr::getProbeShaderConstants(GFXShaderConstBuffer* buffer)
{
   if (!buffer)
      return NULL;

   PROFILE_SCOPE(ProbeManager_GetProbeShaderConstants);

   GFXShader* shader = buffer->getShader();

   // Check to see if this is the same shader, we'll get hit repeatedly by
   // the same one due to the render bin loops.
   if (mLastShader.getPointer() != shader)
   {
      ProbeConstantMap::Iterator iter = mConstantLookup.find(shader);
      if (iter != mConstantLookup.end())
      {
         mLastConstants = iter->value;
      }
      else
      {
         ProbeShaderConstants* psc = new ProbeShaderConstants();
         mConstantLookup[shader] = psc;

         mLastConstants = psc;
      }

      // Set our new shader
      mLastShader = shader;
   }

   /*if (mLastConstants == nullptr)
   {
      ProbeShaderConstants* psc = new ProbeShaderConstants();
      mConstantLookup[shader] = psc;

      mLastConstants = psc;
   }*/

   // Make sure that our current lighting constants are initialized
   if (mLastConstants && !mLastConstants->mInit)
      mLastConstants->init(shader);

   return mLastConstants;
}

void RenderProbeMgr::setProbeInfo(ProcessedMaterial *pmat,
   const Material *mat,
   const SceneData &sgData,
   const SceneRenderState *state,
   U32 pass,
   GFXShaderConstBuffer *shaderConsts)
{
   // Skip this if we're rendering from the deferred bin.
   if (sgData.binType == SceneData::DeferredBin)
      return;

   PROFILE_SCOPE(ProbeManager_setProbeInfo);

   ProbeShaderConstants *psc = getProbeShaderConstants(shaderConsts);

   // NOTE: If you encounter a crash from this point forward
   // while setting a shader constant its probably because the
   // mConstantLookup has bad shaders/constants in it.
   //
   // This is a known crash bug that can occur if materials/shaders
   // are reloaded and the light manager is not reset.
   //
   // We should look to fix this by clearing the table.
   MatrixSet matSet = state->getRenderPass()->getMatrixSet();

   // Update the forward shading light constants.
   _update4ProbeConsts(sgData, matSet, psc, shaderConsts);
}

void RenderProbeMgr::setupSGData(SceneData& data, const SceneRenderState* state, LightInfo* light)
{
   //ensure they're sorted for forward rendering
   mActiveProbes.sort(_probeScoreCmp);
}

void RenderProbeMgr::_update4ProbeConsts(const SceneData& sgData,
   MatrixSet& matSet,
   ProbeShaderConstants* probeShaderConsts,
   GFXShaderConstBuffer* shaderConsts)
{
   PROFILE_SCOPE(ProbeManager_Update4ProbeConsts);

   // Skip over gathering lights if we don't have to!
   if (probeShaderConsts->isValid())
   {
      PROFILE_SCOPE(ProbeManager_Update4ProbeConsts_setProbes);

      const U32 MAX_FORWARD_PROBES = 4;
      ProbeDataSet probeSet(MAX_FORWARD_PROBES);

      matSet.restoreSceneViewProjection();

      getBestProbes(sgData.objTrans->getPosition(), &probeSet);

      static AlignedArray<Point4F> probePositionAlignedArray(probeSet.maxProbeCount, sizeof(Point4F));
      static AlignedArray<Point4F> refScaleAlignedArray(probeSet.maxProbeCount, sizeof(Point4F));
      static AlignedArray<Point4F> probeRefPositionAlignedArray(probeSet.maxProbeCount, sizeof(Point4F));
      static AlignedArray<Point4F> probeConfigAlignedArray(probeSet.maxProbeCount, sizeof(Point4F));

      for (U32 i = 0; i < probeSet.maxProbeCount; i++)
      {
         probePositionAlignedArray[i] = probeSet.probePositionArray[i];
         probeRefPositionAlignedArray[i] = probeSet.probeRefPositionArray[i];
         refScaleAlignedArray[i] = probeSet.refScaleArray[i];
         probeConfigAlignedArray[i] = probeSet.probeConfigArray[i];
      }

      if (probeSet.effectiveProbeCount != 0)
      {
      shaderConsts->setSafe(probeShaderConsts->mProbeCountSC, (S32)probeSet.effectiveProbeCount);

         shaderConsts->setSafe(probeShaderConsts->mProbePositionArraySC, probePositionAlignedArray);
         shaderConsts->setSafe(probeShaderConsts->mProbeRefPosArraySC, probeRefPositionAlignedArray);

         if (probeShaderConsts->isValid())
            shaderConsts->set(probeShaderConsts->mWorldToObjArraySC, probeSet.probeWorldToObjArray.address(), probeSet.probeWorldToObjArray.size(), GFXSCT_Float4x4);

         shaderConsts->setSafe(probeShaderConsts->mRefScaleArraySC, refScaleAlignedArray);
         shaderConsts->setSafe(probeShaderConsts->mProbeConfigDataArraySC, probeConfigAlignedArray);
      }

      if (mBRDFTexture.isValid(), probeShaderConsts->mBRDFTextureMap->getSamplerRegister() != -1)
         GFX->setTexture(probeShaderConsts->mBRDFTextureMap->getSamplerRegister(), mBRDFTexture);

      if (mWetnessTexture.isValid() && probeShaderConsts->mWetnessTextureMap->getSamplerRegister() != -1)
         GFX->setTexture(probeShaderConsts->mWetnessTextureMap->getSamplerRegister(), mWetnessTexture);

      shaderConsts->setSafe(probeShaderConsts->mSkylightCubemapIdxSC, (float)probeSet.skyLightIdx);
      shaderConsts->setSafe(probeShaderConsts->mSkylightDampSC, (int)probeSet.skyLightDamp);

      if (probeShaderConsts->mProbeSpecularCubemapArraySC->getSamplerRegister() != -1)
         GFX->setCubeArrayTexture(probeShaderConsts->mProbeSpecularCubemapArraySC->getSamplerRegister(), mPrefilterArray);
      if (probeShaderConsts->mProbeIrradianceCubemapArraySC->getSamplerRegister() != -1)
         GFX->setCubeArrayTexture(probeShaderConsts->mProbeIrradianceCubemapArraySC->getSamplerRegister(), mIrradianceArray);

      shaderConsts->setSafe(probeShaderConsts->mMaxProbeDrawDistanceSC, smMaxProbeDrawDistance);
   }
}

//=============================================================================
// Deferred Rendering Functions
//=============================================================================
void RenderProbeMgr::_setupPerFrameParameters(const SceneRenderState* state)
{
   PROFILE_SCOPE(RenderProbeMgr_SetupPerFrameParameters);

   mProbeData = ProbeDataSet(smMaxProbesPerFrame);

   getBestProbes(state->getCameraPosition(), &mProbeData);
}

void RenderProbeMgr::render( SceneRenderState *state )
{
   if (getProbeArrayEffect() == nullptr)
   {
      mActiveProbes.clear();
      return;
   }

   GFXDEBUGEVENT_SCOPE(RenderProbeMgr_render, ColorI::WHITE);

   //Sort the active probes
   mActiveProbes.sort(_probeScoreCmp);

   // Initialize and set the per-frame data
   _setupPerFrameParameters(state);

   // Early out if nothing to draw.
   if ((!RenderProbeMgr::smRenderReflectionProbes && !dStrcmp(Con::getVariable("$Probes::Capturing", "0"), "1")) || (!mHasSkylight && mProbeData.effectiveProbeCount == 0))
   {
      getProbeArrayEffect()->setSkip(true);
      mActiveProbes.clear();
      return;
   }

   GFXTransformSaver saver;

   //Visualization
   String useDebugAtten = Con::getVariable("$Probes::showAttenuation", "0");
   mProbeArrayEffect->setShaderMacro("DEBUGVIZ_ATTENUATION", useDebugAtten);

   String useDebugSpecCubemap = Con::getVariable("$Probes::showSpecularCubemaps", "0");
   mProbeArrayEffect->setShaderMacro("DEBUGVIZ_SPECCUBEMAP", useDebugSpecCubemap);

   String useDebugDiffuseCubemap = Con::getVariable("$Probes::showDiffuseCubemaps", "0");
   mProbeArrayEffect->setShaderMacro("DEBUGVIZ_DIFFCUBEMAP", useDebugDiffuseCubemap);

   String useDebugContrib = Con::getVariable("$Probes::showProbeContrib", "0");
   mProbeArrayEffect->setShaderMacro("DEBUGVIZ_CONTRIB", useDebugContrib);

   if(mHasSkylight && mProbeData.effectiveProbeCount == 0)
      mProbeArrayEffect->setShaderMacro("SKYLIGHT_ONLY", "1");
   else
      mProbeArrayEffect->setShaderMacro("SKYLIGHT_ONLY", "0");

   String probePerFrame = Con::getVariable("$pref::MaxProbesPerFrame", "8");
   mProbeArrayEffect->setShaderMacro("MAX_PROBES", probePerFrame);

   String probeCapturing = Con::getVariable("$Probes::Capturing", "0");
   mProbeArrayEffect->setShaderMacro("CAPTURING", probeCapturing);
   
   mProbeArrayEffect->setTexture(3, mBRDFTexture);
   mProbeArrayEffect->setCubemapArrayTexture(4, mPrefilterArray);
   mProbeArrayEffect->setCubemapArrayTexture(5, mIrradianceArray);
   mProbeArrayEffect->setTexture(6, mWetnessTexture);
   //ssao mask
   if (AdvancedLightBinManager::smUseSSAOMask)
   {
      //find ssaoMask
      NamedTexTargetRef ssaoTarget = NamedTexTarget::find("ssaoMask");
      GFXTextureObject* pTexObj = ssaoTarget->getTexture();
      if (pTexObj)
      {
         mProbeArrayEffect->setShaderMacro("USE_SSAO_MASK");
         mProbeArrayEffect->setTexture(7, pTexObj);
      }
   }
   else
   {
      mProbeArrayEffect->setTexture(7, GFXTexHandle(NULL));
   }
   mProbeArrayEffect->setShaderConst("$numProbes", (S32)mProbeData.effectiveProbeCount);
   mProbeArrayEffect->setShaderConst("$skylightCubemapIdx", (S32)mProbeData.skyLightIdx);
   mProbeArrayEffect->setShaderConst(ShaderGenVars::skylightDamp, mProbeData.skyLightDamp);

   mProbeArrayEffect->setShaderConst("$cubeMips", (float)mPrefilterArray->getMipMapLevels());

   //also set up some colors
   Vector<Point4F> contribColors;

   contribColors.setSize(mProbeData.effectiveProbeCount);

   if (mProbeData.effectiveProbeCount != 0)
   {
      if (useDebugContrib == String("1"))
      {
         MRandomLCG RandomGen;
         RandomGen.setSeed(mProbeData.effectiveProbeCount);

         for (U32 i = 0; i < mProbeData.effectiveProbeCount; i++)
         {
            //we're going to cheat here a little for consistent debugging behavior. The first 3 probes will always have R G and then B for their colors, every other will be random
            if (i == 0)
               contribColors[i] = Point4F(1, 0, 0, 1);
            else if (i == 1)
               contribColors[i] = Point4F(0, 1, 0, 1);
            else if (i == 2)
               contribColors[i] = Point4F(0, 0, 1, 1);
            else
               contribColors[i] = Point4F(RandomGen.randF(0, 1), RandomGen.randF(0, 1), RandomGen.randF(0, 1), 1);
         }
      }
   }

   mProbeArrayEffect->setShaderConst("$probeContribColors", contribColors);

   mProbeArrayEffect->setShaderConst("$probePosArray", mProbeData.probePositionArray);
   mProbeArrayEffect->setShaderConst("$refPosArray", mProbeData.probeRefPositionArray);
   mProbeArrayEffect->setShaderConst("$worldToObjArray", mProbeData.probeWorldToObjArray);
   mProbeArrayEffect->setShaderConst("$refScaleArray", mProbeData.refScaleArray);
   mProbeArrayEffect->setShaderConst("$probeConfigData", mProbeData.probeConfigArray);
   mProbeArrayEffect->setShaderConst("$maxProbeDrawDistance", smMaxProbeDrawDistance);

   // Make sure the effect is gonna render.
   getProbeArrayEffect()->setSkip(false);
}

//=============================================================================
// Console functions
//=============================================================================



DefineEngineMethod(RenderProbeMgr, bakeProbe, void, (ReflectionProbe* probe), (nullAsType< ReflectionProbe*>()),
   "@brief Bakes the cubemaps for a reflection probe\n\n.")
{
   if(probe != nullptr)
      object->bakeProbe(probe);
}

DefineEngineMethod(RenderProbeMgr, bakeProbes, void, (),, "@brief Iterates over all reflection probes in the scene and bakes their cubemaps\n\n.")
{
   object->bakeProbes();
}
