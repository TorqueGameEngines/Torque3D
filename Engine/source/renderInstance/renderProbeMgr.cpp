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
#include "lighting/shadowMap/lightShadowMap.h"
#include "lighting/shadowMap/pssmLightShadowMap.h"
#include "lighting/shadowMap/shadowMapPass.h"
#include "lighting/lightManager.h"
#include "gfx/gfxDebugEvent.h"
#include "shaderGen/shaderGenVars.h"
#include "materials/shaderData.h"
#include "scene/reflectionManager.h"

#include "postFx/postEffect.h"
#include "T3D/lighting/reflectionProbe.h"
#include "T3D/lighting/IBLUtilities.h"
#include "T3D/Scene.h"
#include "T3D/assets/LevelAsset.h"
#include "assets/assetPtr.h"
#include "T3D/lighting/skylight.h"
#include "T3D/gameBase/gameConnection.h"
#include "core/volume.h"
#include "core/stream/fileStream.h"
#include "gfx/bitmap/ddsFile.h"

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

bool RenderProbeMgr::smBakeReflectionProbes = false;

// This variable defines the maximum draw distance of a probe.
F32 RenderProbeMgr::smMaxProbeDrawDistance = 100;

// This variable defines the maximum number of probes that can be rendered in a single frame in deferred
S32 RenderProbeMgr::smMaxHighProbesPerFrame = 8;

S32 RenderProbeMgr::smProbeBakeResolution = 64;

S32 RenderProbeMgr::smMaxHighLodSlots = RenderProbeMgr::DefaultMaxHighLodSlots;
S32 RenderProbeMgr::smBakeProgressIntervalMS = 250;
S32 RenderProbeMgr::smMaxLowLodProbes = 50;

F32 RenderProbeMgr::smMaxLowLodProbeDrawDistance = 1000.0f;

F32 RenderProbeMgr::smInteriorSunResidual = 0.1f;
F32 RenderProbeMgr::smCaptureLightFloor = 0.04f;

//A challenger must beat the weakest resident by this much to take its high LOD slot
//Helps keep the high LOD slots from constantly flipping between two probes that are very close in score
static const F32 sProbeSwapMargin = 0.10f;
//Max slot changes (cubemap uploads) per frame
static const S32 sMaxProbeSwapsPerFrame = 2;

static const S32 sMaxHighLodProbes = 16;
static const S32 sMaxLowLodProbes = 50;

//Fraction of the draw distance where a high LOD probe starts easing to its ambient color
static const F32 sProbeHighLodFadeStart = 0.5f;
//Fraction of the low LOD draw distance where a low LOD probe starts fading out
static const F32 sLowLodFadeStart = 0.8f;

//Rows the low LOD atlas holds
static const U32 sLowLodAtlasRows = 4096;

//How far toward the sun's shadow fade distance the interior sun darkening starts (1 = only once shadows fade)
static const F32 sInteriorSunFadeStart = 0.5f;

//
//
ProbeRenderInst::ProbeRenderInst() :
   mCubemapIndex(0),
   mProbeInfo(NULL),
   mPriorityScore(-1.0f)
{
}

ProbeRenderInst::~ProbeRenderInst()
{
}

void ProbeRenderInst::set(const ProbeRenderInst *probe)
{
   mCubemapIndex = probe->mCubemapIndex;
   mProbeInfo = probe->mProbeInfo;
   mPriorityScore = probe->mPriorityScore;
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
   mLastShader(NULL),
   mLastConstants(NULL),
   mHasSkylight(false),
   mSkylightCubemapIdx(-1),
   mSkylightDamp(true),
   mCubeMapCount(0),
   mUseHDRCaptures(true),
   mBakeState(BakeIdle),
   mBakeWaitStartMS(0),
   mLastPriorityUpdateMS(0),
   mLowLodAtlasDirty(true),
   mLowLodAtlasRootBase(0)
{
   mEffectiveProbeCount = 0;
   mMipCount = 0;

   mProbeArrayEffect = NULL;

   smProbeManager = this;

   mCubeMapCount = 0;
}

RenderProbeMgr::RenderProbeMgr(RenderInstType riType, F32 renderOrder, F32 processAddOrder)
 : RenderBinManager(riType, renderOrder, processAddOrder)
{
   mCubeMapCount = 0;
   mEffectiveProbeCount = 0;
   mHasSkylight = false;
   mSkylightCubemapIdx = -1;
   mSkylightDamp = true;
   mLastConstants = NULL;
   mMipCount = 0;
   mUseHDRCaptures = true;
   mBakeState = BakeIdle;
   mBakeWaitStartMS = 0;
   mLastPriorityUpdateMS = 0;
   mLowLodAtlasDirty = true;
   mLowLodAtlasRootBase = 0;
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

   mIrradianceArray.free();
   mPrefilterArray.free();
   mLowLodAtlas.free();
}

bool RenderProbeMgr::onAdd()
{
   if (!Parent::onAdd())
      return false;

   if (smMaxHighLodSlots <= 0)
      smMaxHighLodSlots = DefaultMaxHighLodSlots;

   mCubeMapSlots.setSize(smMaxHighLodSlots);
   mCubeMapSlots.fill(false);

   U32 scaledSize = getProbeTexSize();
   mIrradianceArray.set(scaledSize, scaledSize, (GFXFormat)ProbeFormat, &GFXCubemapStaticTextureProfile, "RenderProbeMgr::mIrradianceArray", 0,0, smMaxHighLodSlots);
   mPrefilterArray.set(scaledSize, scaledSize, (GFXFormat)ProbeFormat, &GFXCubemapStaticTextureProfile, "RenderProbeMgr::mPrefilterArray", 0,0, smMaxHighLodSlots);

   String brdfTexturePath = GFXTextureManager::getBRDFTexturePath();
   if (!mBRDFTexture.set(brdfTexturePath, &GFXTexturePersistentSRGBProfile, "BRDFTexture"))
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

   GFXDevice::getDeviceEventSignal().notify(this, &RenderProbeMgr::handleGFXEvent);
   return true;
}

void RenderProbeMgr::onRemove()
{
   GFXDevice::getDeviceEventSignal().remove(this, &RenderProbeMgr::handleGFXEvent);
   mLowLodAtlas.free();

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
   Con::addVariable("$pref::ReflectionProbes::maxProbeDrawDistance", TypeF32, &RenderProbeMgr::smMaxProbeDrawDistance, "Max distance for reflection probes to render.\n");
   Con::addVariable("$pref::ReflectionProbes::maxHighProbesPerFrame", TypeS32, &RenderProbeMgr::smMaxHighProbesPerFrame, "Max number of Environment Probes that can be rendered per-frame.\n");
   Con::addVariable("$pref::ReflectionProbes::bakeResolution", TypeS32, &RenderProbeMgr::smProbeBakeResolution, "");
   Con::addVariable("$pref::ReflectionProbes::maxHighLODSlots", TypeS32, &RenderProbeMgr::smMaxHighLodSlots, "Size of the high-LOD cubemap slot pool.\n");
   Con::addVariable("$pref::ReflectionProbes::bakeProgressIntervalMS", TypeS32, &RenderProbeMgr::smBakeProgressIntervalMS, "How often a bake reports progress to script, in milliseconds. The progress callback is where the editor redraws, so a smaller value keeps the progress bar smoother and slows the bake down a little more.\n");

   Con::addVariable("$pref::ReflectionProbes::maxLowLODProbes", TypeS32, &RenderProbeMgr::smMaxLowLodProbes, "Max number of low LOD probes (lit from their baked ambient color) rendered per frame, in addition to the high LOD ones.\n");
   Con::addVariable("$pref::ReflectionProbes::maxLowLODProbeDrawDistance", TypeF32, &RenderProbeMgr::smMaxLowLodProbeDrawDistance, "Distance past which low LOD probes fade out completely.\n");

   Con::addVariable("$pref::ReflectionProbes::interiorSunResidual", TypeF32, &RenderProbeMgr::smInteriorSunResidual, "How much of the sun is left inside a probe flagged Interior once its shadows have faded out (0 = none, 1 = no effect).\n");
   Con::addVariable("$pref::ReflectionProbes::captureLightFloor", TypeF32, &RenderProbeMgr::smCaptureLightFloor, "How much light is guaranteed to be applied in a probe capture when you hae a sun/ambient. Interior bakes ignore this so they can potentially be fully dark/local lit.\n");
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

      //Candidates without a high-LOD slot have nothing to sample, so skip them
      if (curEntry.mCubemapIndex == RenderProbeMgr::InvalidCubeSlot)
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
   probeDataSet->renderedProbes.clear();
   for (U32 i = 0; i < bestPickProbes.size(); i++)
   {
      if (bestPickProbes[i] == -1)
         continue;

      const ProbeRenderInst& curEntry = mActiveProbes[bestPickProbes[i]];
      probeDataSet->renderedProbes.push_back(curEntry.mProbeInfo);
      probeDataSet->probeConfigArray[i] = Point4F(curEntry.mProbeInfo->mProbeShapeType,
         curEntry.mProbeInfo->mRadius,
         curEntry.mProbeInfo->mAtten,
         curEntry.mCubemapIndex);

      MatrixF p2A = curEntry.mProbeInfo->mTransform;
      probeDataSet->probeWorldToObjArray[i] = p2A;
      p2A.inverse();
      probeDataSet->refScaleArray[i] = curEntry.mProbeInfo->mProbeRefScale / (p2A.getScale()*2);
      //Flags for the shader: bit 0 = wetness allowed, bit 1 = Interior probe
      probeDataSet->refScaleArray[i].w = (curEntry.mProbeInfo->mCanDamp ? 1.0f : 0.0f) + (curEntry.mProbeInfo->mInterior && AdvancedLightBinManager::smUseProbeInteriorMask ? 2.0f : 0.0f);

      Point3F probePos = curEntry.mProbeInfo->mObject->getPosition();
      Point3F refPos = curEntry.mProbeInfo->mProbeRefOffset;

      probeDataSet->probePositionArray[i] = Point4F(probePos.x, probePos.y, probePos.z, 0);
      probeDataSet->probeRefPositionArray[i] = Point4F(refPos.x, refPos.y, refPos.z, 0);
   }
}

void RenderProbeMgr::registerProbe(ReflectionProbe::ProbeInfo* newProbe)
{
   if (findProbeInst(newProbe) != NULL)
      return;

   ProbeRenderInst newProbeRenderInst;
   newProbeRenderInst.mProbeInfo = newProbe;
   newProbeRenderInst.mCubemapIndex = InvalidCubeSlot;

   mRegisteredProbes.push_back(newProbeRenderInst);
}

void RenderProbeMgr::unregisterProbe(ReflectionProbe::ProbeInfo* probeInfo)
{
   ProbeRenderInst* probe = findProbeInst(probeInfo);
   if (probe == NULL)
      return;

   releaseSlot(probeInfo);

   mRegisteredProbes.erase(probe);
}

bool RenderProbeMgr::acquireSlot(ReflectionProbe::ProbeInfo* probeInfo)
{
   ProbeRenderInst* probe = findProbeInst(probeInfo);
   if (probe == NULL)
      return false;

   if (probe->mCubemapIndex != InvalidCubeSlot)
      return true; //already resident

   U32 slot = findNextEmptyCubeSlot();

   if (slot == InvalidCubeSlot)
   {
      //Pool is full, so evict the worst resident that's not a skylight.
      ProbeRenderInst* worstProbe = NULL;
      for (U32 i = 0; i < mRegisteredProbes.size(); i++)
      {
         ProbeRenderInst& residentProbe = mRegisteredProbes[i];
         if (residentProbe.mCubemapIndex == InvalidCubeSlot || residentProbe.mProbeInfo->mProbeShapeType == ReflectionProbe::ProbeInfo::Skylight)
            continue;

         if (worstProbe == NULL || residentProbe.mProbeInfo->mScore > worstProbe->mProbeInfo->mScore)
            worstProbe = &residentProbe;
      }

      const bool candidateIsSkylight = probeInfo->mProbeShapeType == ReflectionProbe::ProbeInfo::Skylight;
      if (worstProbe == NULL || (!candidateIsSkylight && probeInfo->mScore >= worstProbe->mProbeInfo->mScore))
         return false; //nothing evictable, or candidate isn't good enough to take over

      slot = worstProbe->mCubemapIndex;
      worstProbe->mCubemapIndex = InvalidCubeSlot;
   }

   probe->mCubemapIndex = slot;
   mCubeMapSlots[slot] = true;
   mCubeMapCount++;

   //Upload its cubemaps now that it has a slot. Through the object, as probeInfo's handles may have been cleared
   if (probeInfo->mObject != NULL)
      probeInfo->mObject->submitCubemaps();

#ifdef TORQUE_DEBUG
   Con::warnf("RenderProbeMgr::acquireSlot() - Promoted probe %u to cubeIndex %u", probeInfo->mObject->getId(), slot);
#endif

   return true;
}

void RenderProbeMgr::releaseSlot(ReflectionProbe::ProbeInfo* probeInfo)
{
   ProbeRenderInst* probe = findProbeInst(probeInfo);
   if (probe == NULL || probe->mCubemapIndex == InvalidCubeSlot)
      return;

   mCubeMapSlots[probe->mCubemapIndex] = false;
   mCubeMapCount--;

   probe->mCubemapIndex = InvalidCubeSlot;
}

//Editor previews and object views render through this bin with their own cameras, and must not drive slot changes
bool RenderProbeMgr::isPrimaryView(const SceneRenderState* state)
{
   GameConnection* connection = GameConnection::getConnectionToServer();

   MatrixF controlTransform;
   if (connection == NULL || !connection->getControlCameraTransform(0.032f, &controlTransform))
      return true;

   constexpr F32 tolerance = 1.0f;
   return (state->getCameraPosition() - controlTransform.getPosition()).lenSquared() < tolerance;
}

bool RenderProbeMgr::updateProbeScores(const SceneRenderState* state)
{
   PROFILE_SCOPE(ProbeManager_UpdateProbeScores);

   //Several render bins can call this in one frame, so only do it once
   const U32 nowMS = Platform::getRealMilliseconds();
   if (nowMS == mLastPriorityUpdateMS)
      return false;

   if (!isPrimaryView(state))
      return false;

   mLastPriorityUpdateMS = nowMS;

   const Point3F& cameraPosition = state->getCameraPosition();

   //mScore sorts ascending (lower = better); everything here reads it as "base minus priority"
   const F32 scoreBase = 100.0f;

   for (U32 i = 0; i < mRegisteredProbes.size(); i++)
   {
      ProbeRenderInst& probe = mRegisteredProbes[i];
      ReflectionProbe::ProbeInfo* info = probe.mProbeInfo;

      //The skylight is global and always wanted
      if (info->mProbeShapeType == ReflectionProbe::ProbeInfo::Skylight)
      {
         probe.mPriorityScore = 1000.0f;
         info->mScore = -scoreBase;
         continue;
      }

      probe.mPriorityScore = 0.0f;

      if (info->mIsEnabled)
      {
         //Distance to the probe's volume rather than its center, so being inside a big probe counts as right on top of it
         probe.mPriorityScore = mClampF(1.0f - info->mBounds.getDistanceToPoint(cameraPosition) / smMaxProbeDrawDistance, 0.0f, 1.0f);
      }

      info->mScore = scoreBase - probe.mPriorityScore;
   }

   return true;
}

void RenderProbeMgr::updateHighLodSlots()
{
   PROFILE_SCOPE(ProbeManager_UpdateHighLodSlots);

   for (U32 i = 0; i < mRegisteredProbes.size(); i++)
   {
      ProbeRenderInst& probe = mRegisteredProbes[i];
      //Make sure we give skylight a slot if doesn't have one already
      if (probe.mProbeInfo->mProbeShapeType == ReflectionProbe::ProbeInfo::Skylight && probe.mCubemapIndex == InvalidCubeSlot)
         acquireSlot(probe.mProbeInfo);
   }

   //Give slots to the best probes without one. With a full pool it has to beat the weakest resident by the swap margin
   for (S32 swapsLeft = getMax(sMaxProbeSwapsPerFrame, 1); swapsLeft > 0; swapsLeft--)
   {
      ProbeRenderInst* bestPick = NULL;
      for (U32 i = 0; i < mRegisteredProbes.size(); i++)
      {
         ProbeRenderInst& probe = mRegisteredProbes[i];
         if (probe.mCubemapIndex != InvalidCubeSlot || probe.mProbeInfo->mProbeShapeType == ReflectionProbe::ProbeInfo::Skylight)
            continue;

         if (probe.mPriorityScore > 0.0f && (bestPick == NULL || probe.mPriorityScore > bestPick->mPriorityScore))
            bestPick = &probe;
      }

      if (bestPick == NULL)
         break;

      if (findNextEmptyCubeSlot() == InvalidCubeSlot)
      {
         ProbeRenderInst* weakest = NULL;
         for (U32 i = 0; i < mRegisteredProbes.size(); i++)
         {
            ProbeRenderInst& resident = mRegisteredProbes[i];
            if (resident.mCubemapIndex == InvalidCubeSlot || resident.mProbeInfo->mProbeShapeType == ReflectionProbe::ProbeInfo::Skylight)
               continue;

            if (weakest == NULL || resident.mPriorityScore < weakest->mPriorityScore)
               weakest = &resident;
         }

         //Nothing evictable, or the challenger isn't clearly better; the rest are weaker still
         if (weakest == NULL || (weakest->mPriorityScore > 0.0f && bestPick->mPriorityScore < weakest->mPriorityScore + sProbeSwapMargin))
            break;

         releaseSlot(weakest->mProbeInfo);
      }

      if (!acquireSlot(bestPick->mProbeInfo))
         break;
   }

   //Mirror the slots onto this frame's submitted copies so getBestProbes()/shader consts see the current ones
   for (U32 i = 0; i < mActiveProbes.size(); i++)
   {
      ProbeRenderInst* probe = findProbeInst(mActiveProbes[i].mProbeInfo);
      mActiveProbes[i].mCubemapIndex = probe != NULL ? probe->mCubemapIndex : InvalidCubeSlot;
   }
}

U32 RenderProbeMgr::getMaxHighLodProbes()
{
   return mClamp(smMaxHighProbesPerFrame, 1, sMaxHighLodProbes);
}

void RenderProbeMgr::submitProbe(ReflectionProbe::ProbeInfo* probe)
{
   ProbeRenderInst* probeInst = findProbeInst(probe);
   if (probeInst == NULL)
      return;

   mActiveProbes.push_back(*probeInst);
}

PostEffect* RenderProbeMgr::getProbeArrayEffect()
{
   if (!mProbeArrayEffect)
   {
      mProbeArrayEffect = dynamic_cast<PostEffect*>(Sim::findObject("reflectionProbeArrayPostFX"));

      if (!mProbeArrayEffect)
         return NULL;

      mProbeArrayEffect->setShaderConst("$numProbes", (S32)0);
      mProbeArrayEffect->setShaderConst("$numLowLodProbes", (S32)0);
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
   if (probe == NULL)
      return;

   //The probe doesn't currently hold a high-LOD slot - nothing to upload to
   if (probe->mCubemapIndex == InvalidCubeSlot)
      return;

   U32 scaledSize = getProbeTexSize();
   //Some basic sanity checking that we have valid cubemaps to work with
   if (probeInfo->mIrradianceCubemap.isNull() || probeInfo->mIrradianceCubemap->getWidth() != scaledSize)
   {
      Con::errorf("RenderProbeMgr::updateProbeTexture() - tried to update a probe's texture with an invalid or uninitialized irradiance map!");
      return;
   }

   if (probeInfo->mPrefilterCubemap.isNull() || probeInfo->mPrefilterCubemap->getWidth() != scaledSize)
   {
      Con::errorf("RenderProbeMgr::updateProbeTexture() - tried to update a probe's texture with an invalid or uninitialized specular map!");
      return;
   }

   //Run the update on the array pair with the probe's cubemaps and index
   const U32 cubeIndex = probe->mCubemapIndex;
   mIrradianceArray->updateTextureSlot(probeInfo->mIrradianceCubemap, cubeIndex);

   mPrefilterArray->updateTextureSlot(probeInfo->mPrefilterCubemap, cubeIndex);

#ifdef TORQUE_DEBUG
   Con::warnf("UpdatedProbeTexture - probe id: %u on cubeIndex %u, Irrad validity: %d, Prefilter validity: %d", probeInfo->mObject->getId(), cubeIndex,
      probeInfo->mIrradianceCubemap.isValid(), probeInfo->mPrefilterCubemap.isValid());
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
   RenderProbeMgr::smBakeReflectionProbes = true;
   Con::setBoolVariable("$ReflectionProbes::Capturing", RenderProbeMgr::smBakeReflectionProbes);
}

void RenderProbeMgr::postBake()
{
   RenderProbeMgr::smBakeReflectionProbes = false;
   Con::setBoolVariable("$ReflectionProbes::Capturing", RenderProbeMgr::smBakeReflectionProbes);
}

void RenderProbeMgr::bakeProbe(ReflectionProbe* probe)
{
   GFXDEBUGEVENT_SCOPE(RenderProbeMgr_Bake, ColorI::WHITE);

   Con::warnf("RenderProbeMgr::bakeProbe() - Beginning bake!");
   U32 startMSTime = Platform::getRealMilliseconds();

   String path = Con::getVariable("$pref::ReflectionProbes::CurrentLevelPath", "levels/");
   U32 resolution = Con::getIntVariable("$pref::ReflectionProbes::BakeResolution", 64);
   U32 prefilterMipLevels = mLog2(F32(resolution)) + 1;
   bool renderWithProbes = Con::getIntVariable("$pref::ReflectionProbes::RenderWithProbes", false);

   ReflectionProbe* clientProbe = NULL;

   if (probe->isServerObject())
      clientProbe = static_cast<ReflectionProbe*>(probe->getClientObject());
   else
      return;

   if (clientProbe == NULL)
   {
      Con::warnf("RenderProbeMgr::bakeProbe() - probe %u has no client ghost yet, skipping its bake", probe->getId());
      return;
   }

   //Captures give lights a small floor in full shadow, except Interior probes so a sealed room can bake dark
   Con::setFloatVariable("$ReflectionProbes::CaptureLightFloor", clientProbe->mProbeInfo.mInterior ? 0.0f : smCaptureLightFloor);

   //Clear the old ambient color so a failed re-bake can't leave a stale one in the atlas
   clientProbe->mProbeInfo.mHasAmbient = false;

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
   cubeRefl.mGenerateShadows = true;
   cubeRefl.registerReflector(probe, &reflDesc);

   ReflectParams reflParams;

   MatrixF camTrans = clientProbe->getTransform();
   camTrans.setPosition(clientProbe->getTransform().getPosition() + clientProbe->mProbeRefOffset);
   //need to get the query somehow. Likely do some sort of get function to fetch from the guiTSControl that's active
   CameraQuery query; //need to get the last cameraQuery
   query.fov = 90; //90 degree slices for each of the 6 sides
   query.nearPlane = 0.0001f;
   query.farPlane = farPlane;
   query.headMatrix = MatrixF();
   query.cameraMatrix = camTrans;

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
      clientProbe->mIrridianceMap->mCubemap.set(resolution, resolution, reflectFormat, &GFXCubemapRenderTargetProfile, "ReflectionProbe::mIrridianceMap", 0);
      clientProbe->mPrefilterMap->mCubemap.set(resolution, resolution, reflectFormat, &GFXCubemapRenderTargetProfile, "ReflectionProbe::mPrefilterMap", 0);

      GFXTextureTargetRef renderTarget = GFX->allocRenderToTextureTarget(false);
      clientProbe->mPrefilterMap->mCubemap = cubeRefl.getCubemap();

      IBLUtilities::GenerateIrradianceMap(renderTarget, cubeRefl.getCubemap(), clientProbe->mIrridianceMap->mCubemap);
      //IBLUtilities::GeneratePrefilterMap(renderTarget, cubeRefl.getCubemap(), prefilterMipLevels, clientProbe->mPrefilterMap->mCubemap);

      clientProbe->mProbeInfo.mHasAmbient = IBLUtilities::calculateAverageColor(cubeRefl.getCubemap(), clientProbe->mProbeInfo.mAmbientColor);
      if (!clientProbe->mProbeInfo.mHasAmbient)
      {
         Con::warnf("RenderProbeMgr::bakeProbe() - probe %u: ambient color calculation failed; it will be left out of the probe atlas", probe->getId());
      }

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


   cubeRefl.unregisterReflector();

   //Hand the probe its new cubemaps. This enables it if it was unbaked, and uploads them if it has a slot
   clientProbe->refreshBakedCubemaps();

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

      if (mBRDFTexture.isValid() && probeShaderConsts->mBRDFTextureMap->getSamplerRegister() != -1)
         GFX->setTexture(probeShaderConsts->mBRDFTextureMap->getSamplerRegister(), mBRDFTexture);

      if (mWetnessTexture.isValid() && probeShaderConsts->mWetnessTextureMap->getSamplerRegister() != -1)
         GFX->setTexture(probeShaderConsts->mWetnessTextureMap->getSamplerRegister(), mWetnessTexture);

      shaderConsts->setSafe(probeShaderConsts->mSkylightCubemapIdxSC, (float)probeSet.skyLightIdx);
      shaderConsts->setSafe(probeShaderConsts->mSkylightDampSC, (int)probeSet.skyLightDamp);

      if (probeShaderConsts->mProbeSpecularCubemapArraySC->getSamplerRegister() != -1)
         GFX->setTexture(probeShaderConsts->mProbeSpecularCubemapArraySC->getSamplerRegister(), mPrefilterArray);
      if (probeShaderConsts->mProbeIrradianceCubemapArraySC->getSamplerRegister() != -1)
         GFX->setTexture(probeShaderConsts->mProbeIrradianceCubemapArraySC->getSamplerRegister(), mIrradianceArray);

      shaderConsts->setSafe(probeShaderConsts->mMaxProbeDrawDistanceSC, smMaxProbeDrawDistance);
   }
}

//=============================================================================
// Deferred Rendering Functions
//=============================================================================
void RenderProbeMgr::_setupPerFrameParameters(const SceneRenderState* state)
{
   PROFILE_SCOPE(RenderProbeMgr_SetupPerFrameParameters);

   const U32 maxHighProbes = getMaxHighLodProbes();
   mProbeData = ProbeDataSet(maxHighProbes);

   getBestProbes(state->getCameraPosition(), &mProbeData);

   mProbeData.highLodAtlasRow.setSize(maxHighProbes);
   for (U32 i = 0; i < maxHighProbes; i++)
      mProbeData.highLodAtlasRow[i] = Point4F(-1.0f, 0.0f, 0.0f, 0.0f);

   applyHighLodSwitch(state->getCameraPosition(), &mProbeData);
   gatherLowLodProbes(state, &mProbeData);

   mProbeData.probePositionArray.setSize(maxHighProbes);
   mProbeData.probeRefPositionArray.setSize(maxHighProbes);
   mProbeData.refScaleArray.setSize(maxHighProbes);
   mProbeData.probeConfigArray.setSize(maxHighProbes);
   mProbeData.probeWorldToObjArray.setSize(maxHighProbes);

   for (U32 i = mProbeData.effectiveProbeCount; i < maxHighProbes; i++)
   {
      mProbeData.probePositionArray[i] = Point4F::Zero;
      mProbeData.probeRefPositionArray[i] = Point4F::Zero;
      mProbeData.refScaleArray[i] = Point4F::Zero;
      mProbeData.probeConfigArray[i] = Point4F::Zero;
      mProbeData.probeWorldToObjArray[i].identity();
   }

   const U32 maxLowProbes = getMaxLowLodProbes();
   const U32 usedLowSlots = mProbeData.lowLodList.size();

   mProbeData.lowLodList.setSize(maxLowProbes);
   for (U32 i = usedLowSlots; i < maxLowProbes; i++)
      mProbeData.lowLodList[i] = Point4F::Zero;
}

void RenderProbeMgr::render( SceneRenderState *state )
{
   if (getProbeArrayEffect() == NULL)
   {
      mActiveProbes.clear();
      return;
   }

   GFXDEBUGEVENT_SCOPE(RenderProbeMgr_render, ColorI::WHITE);

   //Only the main view drives probe priorities and slot changes, other passes reuse the last result
   const bool updatedScores = state->isDiffusePass() && updateProbeScores(state);

   //Sort the active probes
   mActiveProbes.sort(_probeScoreCmp);

   //Promote/demote candidates in the high-LOD slot pool for this frame
   if (updatedScores)
      updateHighLodSlots();

   //The low LOD atlas only changes when the roster set does
   if (mLowLodAtlasDirty || mLowLodAtlas.isNull())
      buildLowLodAtlas();

   // Initialize and set the per-frame data
   _setupPerFrameParameters(state);

   // Early out if nothing to draw.
   if (!RenderProbeMgr::smRenderReflectionProbes || (!mHasSkylight && mProbeData.effectiveProbeCount + mProbeData.lowLodProbeCount == 0))
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

   String useDebugLod = Con::getVariable("$Probes::showLOD", "0");
   mProbeArrayEffect->setShaderMacro("DEBUGVIZ_LOD", useDebugLod);

   if(mHasSkylight && mProbeData.effectiveProbeCount + mProbeData.lowLodProbeCount == 0)
      mProbeArrayEffect->setShaderMacro("SKYLIGHT_ONLY", "1");
   else
      mProbeArrayEffect->setShaderMacro("SKYLIGHT_ONLY", "0");

   String probePerFrame = String::ToString("%u", getMaxHighLodProbes());
   mProbeArrayEffect->setShaderMacro("MAX_PROBES", probePerFrame);

   //Interior sun darkening goes in the light buffer's alpha, and the sun is scaled by 1 - alpha.
   LightInfo* sunLight = LIGHTMGR != NULL ? LIGHTMGR->getSpecialLight(LightManager::slSunLightType, false) : NULL;
   const bool sunAlpha = AdvancedLightBinManager::smUseProbeInteriorMask && sunLight != NULL;
   mProbeArrayEffect->setShaderMacro("INTERIOR_SUN_ALPHA", sunAlpha ? "1" : "0");
   if (sunAlpha)
   {
      //Without sun shadows it applies at every distance. With them it starts part way to the shadow fade and is fully in
      //once they've faded, so it doesn't pop
      Point4F sunFade(-1.0f, 1000.0f, 0.0f, 0.0f);

      ShadowMapParams* shadowParams = sunLight->getExtended<ShadowMapParams>();
      if (sunLight->getCastShadows() && !ShadowMapPass::smDisableShadows && shadowParams != NULL)
      {
         //Hold it off until the sun's shadow map exists to give a fade distance
         sunFade.set(1000.0f, 0.0f, 0.0f, 0.0f);

         PSSMLightShadowMap* shadowMap = dynamic_cast<PSSMLightShadowMap*>(shadowParams->getShadowMap());
         if (shadowMap != NULL)
         {
            const Point2F fadeStartLength = shadowMap->getFadeStartLength();
            const F32 start = fadeStartLength.x * sInteriorSunFadeStart;
            const F32 length = (fadeStartLength.x - start) + 1.0f / mMax(fadeStartLength.y, 0.0001f);
            sunFade.set(start, 1.0f / mMax(length, 0.0001f), 0.0f, 0.0f);
         }
      }

      const Frustum& frustum = state->getCameraFrustum();
      mProbeArrayEffect->setShaderConst("$interiorSunResidual", mClampF(smInteriorSunResidual, 0.0f, 1.0f));
      mProbeArrayEffect->setShaderConst("$interiorSunFade", sunFade);
      mProbeArrayEffect->setShaderConst("$zNearFar", Point4F(frustum.getNearDist(), frustum.getFarDist(), 0.0f, 0.0f));
   }

   //The probe arrays only hold high LOD probes. Low LOD probes are a list of atlas rows
   const U32 maxLowLodProbes = getMaxLowLodProbes();
   mProbeArrayEffect->setShaderMacro("TOTAL_PROBES", String::ToString("%u", getMaxHighLodProbes() + maxLowLodProbes));
   mProbeArrayEffect->setShaderMacro("MAX_LOWLOD_PROBES", String::ToString("%u", maxLowLodProbes));

   mProbeArrayEffect->setTexture(3, mBRDFTexture);
   mProbeArrayEffect->setTexture(4, mPrefilterArray);
   mProbeArrayEffect->setTexture(5, mIrradianceArray);
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
   mProbeArrayEffect->setShaderConst("$numLowLodProbes", (S32)mProbeData.lowLodProbeCount);

   mProbeArrayEffect->setTexture(8, mLowLodAtlas);
   mProbeArrayEffect->setShaderConst("$probeLowLodList", mProbeData.lowLodList);
   mProbeArrayEffect->setShaderConst("$probeAtlasRow", mProbeData.highLodAtlasRow);

   mProbeArrayEffect->setShaderConst("$skylightCubemapIdx", (S32)mProbeData.skyLightIdx);
   mProbeArrayEffect->setShaderConst(ShaderGenVars::skylightDamp, mProbeData.skyLightDamp);

   mProbeArrayEffect->setShaderConst("$cubeMips", (float)mPrefilterArray->getMipLevels());

   mProbeArrayEffect->setShaderConst("$probePosArray", mProbeData.probePositionArray);
   mProbeArrayEffect->setShaderConst("$refPosArray", mProbeData.probeRefPositionArray);
   mProbeArrayEffect->setShaderConst("$worldToObjArray", mProbeData.probeWorldToObjArray);
   mProbeArrayEffect->setShaderConst("$refScaleArray", mProbeData.refScaleArray);
   mProbeArrayEffect->setShaderConst("$probeConfigData", mProbeData.probeConfigArray);
   mProbeArrayEffect->setShaderConst("$maxProbeDrawDistance", smMaxProbeDrawDistance);

   // Make sure the effect is gonna render.
   getProbeArrayEffect()->setSkip(false);
}

void RenderProbeMgr::fillProbeAtlasRecord(ProbeAtlasRecord& record, ReflectionProbe* clientProbe)
{
   ReflectionProbe::ProbeInfo* info = clientProbe->getProbeInfo();

   record.persistentProbeId = clientProbe->getProbeUniqueId().getHashCaseSensitive();

   dMemcpy(record.worldToObj, (const F32*)info->mTransform, sizeof(record.worldToObj));

   record.position = info->mPosition;
   record.refOffset = info->mProbeRefOffset;
   record.refScale = info->mProbeRefScale;

   record.shapeType = (F32)info->mProbeShapeType;
   record.radius = info->mRadius;
   record.atten = info->mAtten;
   record.flags = (info->mCanDamp ? ProbeAtlasRecord::CanDamp : 0) | (info->mInterior ? ProbeAtlasRecord::Interior : 0);

   Box3F bounds = info->mBounds;
   if (info->mProbeShapeType == ReflectionProbe::ProbeInfo::Sphere)
   {
      bounds.minExtents = info->mPosition - Point3F(info->mRadius, info->mRadius, info->mRadius);
      bounds.maxExtents = info->mPosition + Point3F(info->mRadius, info->mRadius, info->mRadius);
   }

   record.boundsMin = bounds.minExtents;
   record.boundsMax = bounds.maxExtents;

   for (U32 channel = 0; channel < 3; channel++)
      record.ambient[channel] = info->mAmbientColor[channel];
}

String RenderProbeMgr::rootAtlasPath() const
{
   //The client is given the level asset id by loadLevelAtlas(), the server gets it from the scene
   StringTableEntry assetId = mLevelAssetId;
   if (assetId == NULL || assetId[0] == '\0')
   {
      Scene* rootScene = Scene::getRootScene();
      if (rootScene != NULL)
         assetId = rootScene->getLevelAsset();
   }

   if (assetId != NULL && assetId[0] != '\0')
   {
      AssetPtr<LevelAsset> levelAsset = assetId;
      if (levelAsset.notNull())
      {
         String path = levelAsset->getProbeAtlasPath();
         if (path.isNotEmpty())
            return path;
      }
   }

   //No asset (a scene that isn't backed by a level asset), so fall back to the pref convention
   return Con::getVariable("$pref::ReflectionProbes::CurrentLevelPath", "levels/") + String("ProbeAtlas.dds");
}

bool RenderProbeMgr::readProbeAtlasFile(const String& path, Vector<ProbeAtlasRecord>& outRoster, ProbeAtlasHeader* outHeader)
{
   outRoster.clear();

   if (path.isEmpty() || !Torque::FS::IsFile(path))
      return false;

   Resource<DDSFile> atlas = DDSFile::load(path, 0);
   if (!atlas)
   {
      Con::warnf("RenderProbeMgr::readProbeAtlasFile() - failed to load %s", path.c_str());
      return false;
   }

   if (atlas->mFormat != GFXFormatR32G32B32A32F || atlas->mWidth != sProbeAtlasRowTexels || atlas->mHeight < 1)
   {
      Con::warnf("RenderProbeMgr::readProbeAtlasFile() - %s is not a valid probe atlas (older layout?), re-bake the probes", path.c_str());
      return false;
   }

   const U8* data = atlas->mSurfaces[0]->mMips[0];

   ProbeAtlasHeader header;
   dMemcpy(&header, data, sizeof(header));

   if (header.fileId != sProbeAtlasFileId)
   {
      Con::warnf("RenderProbeMgr::readProbeAtlasFile() - %s is not a probe atlas file", path.c_str());
      return false;
   }

   if (header.version != sProbeAtlasVersion)
   {
      Con::warnf("RenderProbeMgr::readProbeAtlasFile() - %s is atlas version %u but this build reads version %u, re-bake the probes",
         path.c_str(), header.version, sProbeAtlasVersion);
      return false;
   }

   if (header.count != atlas->mHeight - 1)
   {
      Con::warnf("RenderProbeMgr::readProbeAtlasFile() - %s header says %u probes but the file has %u rows, re-bake the probes",
         path.c_str(), header.count, atlas->mHeight - 1);
      return false;
   }

   outRoster.setSize(header.count);
   if (header.count > 0)
      dMemcpy(&outRoster[0], data + sProbeAtlasRowBytes, sProbeAtlasRowBytes * header.count);

   if (outHeader != NULL)
      *outHeader = header;

   return true;
}

void RenderProbeMgr::writeProbeAtlasFile(const String& path, const Vector<ProbeAtlasRecord>& records)
{
   if (path.isEmpty())
      return;

   if (records.empty())
   {
      if (Torque::FS::IsFile(path))
         Torque::FS::Remove(path);
      return;
   }

   const U32 count = records.size();
   const U32 rowCount = count + 1; //row 0 is the header

   //new U8[]: DDSFile::SurfaceData frees its mips with delete[]
   U8* buffer = new U8[sProbeAtlasRowBytes * rowCount];
   dMemset(buffer, 0, sProbeAtlasRowBytes * rowCount);

   ProbeAtlasHeader header;
   header.fileId = sProbeAtlasFileId;
   header.version = sProbeAtlasVersion;
   header.bakeStamp = Platform::getTime();
   header.count = count;
   dMemcpy(buffer, &header, sizeof(header));

   //The rows are the records as they are
   dMemcpy(buffer + sProbeAtlasRowBytes, &records[0], sProbeAtlasRowBytes * count);

   //Wrap the buffer in a DDSFile so it can be written and reloaded straight into a GFXTexHandle
   DDSFile ddsFile;
   ddsFile.mFormat = GFXFormatR32G32B32A32F;
   ddsFile.mBytesPerPixel = sizeof(F32) * 4;
   ddsFile.mHeight = rowCount;
   ddsFile.mWidth = sProbeAtlasRowTexels;
   ddsFile.mMipMapCount = 1;
   ddsFile.mSurfaces.push_back(new DDSFile::SurfaceData);
   ddsFile.mSurfaces.last()->mMips.push_back(buffer); //ddsFile now owns buffer

   FileStream* stream = FileStream::createAndOpen(path, Torque::FS::File::Write);
   if (stream == NULL)
   {
      Con::errorf("RenderProbeMgr::writeProbeAtlasFile() - failed to open %s for writing", path.c_str());
      return;
   }

   ddsFile.write(*stream);
   stream->close();
   delete stream;

   Con::printf("RenderProbeMgr::writeProbeAtlasFile() - Wrote %u probes to %s", count, path.c_str());
}

void RenderProbeMgr::collectAtlasProbes(Vector<ReflectionProbe*>& outRootProbes, Map<SubScene*, Vector<ReflectionProbe*> >& outPartitions)
{
   Scene* rootScene = Scene::getRootScene();
   if (rootScene == NULL)
      return;

   Vector<ReflectionProbe*> probes;
   rootScene->findObjectByType<ReflectionProbe>(probes);

   for (U32 i = 0; i < probes.size(); i++)
   {
      if (probes[i]->isClientObject() || dynamic_cast<Skylight*>(probes[i]) != NULL)
         continue;

      SubScene* owner = rootScene->findOwningSubScene(probes[i]);
      if (owner != NULL)
         outPartitions[owner].push_back(probes[i]);
      else
         outRootProbes.push_back(probes[i]);
   }
}

const ProbeAtlasRecord* RenderProbeMgr::findAtlasRecord(const Vector<ProbeAtlasRecord>& records, U32 persistentProbeId)
{
   for (U32 i = 0; i < records.size(); i++)
   {
      if (records[i].persistentProbeId == persistentProbeId)
         return &records[i];
   }

   return NULL;
}

U32 RenderProbeMgr::buildAtlasPartitionRecords(const String& path, const Vector<ReflectionProbe*>& serverProbes, Vector<ProbeAtlasRecord>& outRecords)
{
   Vector<ProbeAtlasRecord> existing;
   readProbeAtlasFile(path, existing);

   U32 skippedCount = 0;

   for (U32 i = 0; i < serverProbes.size(); i++)
   {
      ReflectionProbe* serverProbe = serverProbes[i];
      ReflectionProbe* clientProbe = static_cast<ReflectionProbe*>(serverProbe->getClientObject());

      const U32 id = serverProbe->getProbeUniqueId().getHashCaseSensitive();
      const ProbeAtlasRecord* existingRecord = findAtlasRecord(existing, id);

      //Without a client ghost there is nothing to bake from, so an existing row is carried over as it is
      if (clientProbe == NULL)
      {
         if (existingRecord != NULL)
         {
            Con::warnf("RenderProbeMgr::buildAtlasPartitionRecords() - probe %u has no client ghost; kept its existing atlas row without verifying it", serverProbe->getId());
            outRecords.push_back(*existingRecord);
         }
         else
         {
            Con::warnf("RenderProbeMgr::buildAtlasPartitionRecords() - probe %u left out of the atlas: no client ghost", serverProbe->getId());
            skippedCount++;
         }
         continue;
      }

      ReflectionProbe::ProbeInfo* info = clientProbe->getProbeInfo();

      if (info->mHasAmbient)
      {
         //The ambient color comes from the scene capture, so in these modes it won't match the probe's own cubemap
         if (clientProbe->getReflectionMode() != ReflectionProbe::BakedCubemap)
         {
            Con::warnf("RenderProbeMgr::serializeProbeAtlas() - probe %u uses a non-baked reflection mode (%d); its atlas ambient color comes from the scene capture, not its own cubemap",
               serverProbe->getId(), (S32)clientProbe->getReflectionMode());
         }

         ProbeAtlasRecord record;
         fillProbeAtlasRecord(record, clientProbe);
         outRecords.push_back(record);
         continue;
      }

      if (existingRecord != NULL)
      {
         //Not baked this session, so we just keep the row from the last bake
         outRecords.push_back(*existingRecord);
         continue;
      }

      Con::warnf("RenderProbeMgr::buildAtlasPartitionRecords() - probe %u left out of the atlas: no ambient color (not baked yet, or the calculation failed)", serverProbe->getId());
      skippedCount++;
   }

   return skippedCount;
}

void RenderProbeMgr::serializeProbeAtlas()
{
   Scene* rootScene = Scene::getRootScene();
   if (rootScene == NULL)
      return;

   Vector<ReflectionProbe*> rootProbes;
   Map<SubScene*, Vector<ReflectionProbe*> > partitions;
   collectAtlasProbes(rootProbes, partitions);

   U32 skippedCount = 0;

   String rootPath = rootAtlasPath();
   Vector<ProbeAtlasRecord> rootRecords;
   skippedCount += buildAtlasPartitionRecords(rootPath, rootProbes, rootRecords);
   writeProbeAtlasFile(rootPath, rootRecords);

   //Each SubScene has its own atlas. Unloaded ones are skipped, as they'd look like all their probes were deleted
   const U32 subSceneCount = rootScene->getSubSceneCount();
   for (U32 i = 0; i < subSceneCount; i++)
   {
      SubScene* subScene = rootScene->getSubScene(i);
      if (!subScene->isLoaded())
         continue;

      const String path = subScene->getProbeAtlasPath();

      Vector<ReflectionProbe*> subSceneProbes; //stays empty if this SubScene has no probes
      partitions.tryGetValue(subScene, subSceneProbes);

      Vector<ProbeAtlasRecord> records;
      skippedCount += buildAtlasPartitionRecords(path, subSceneProbes, records);
      writeProbeAtlasFile(path, records);
   }

   //Anything left out is a hole in the low LOD coverage
   if (skippedCount != 0)
      Con::warnf("RenderProbeMgr::serializeProbeAtlas() - %u probe(s) were left out of the atlas bake", skippedCount);

   //Re-read the rosters so we hav up to date data
   loadLevelAtlas();

   Vector<SubScene*> loadedSubScenes;
   for (Map<SubScene*, Vector<ProbeAtlasRecord> >::Iterator itr = mSubSceneAtlasRosters.begin(); itr != mSubSceneAtlasRosters.end(); itr++)
      loadedSubScenes.push_back(itr->key);

   //Plus every SubScene loaded on the client, so one with no atlas until now picks up its first
   rootScene = Scene::getRootScene();
   if (rootScene != NULL)
   {
      for (U32 i = 0; i < rootScene->getSubSceneCount(); i++)
      {
         SubScene* serverSubScene = rootScene->getSubScene(i);
         SubScene* clientSubScene = serverSubScene != NULL ? dynamic_cast<SubScene*>(serverSubScene->getClientObject()) : NULL;
         //Only SubScenes loaded on the client have a probe data we care about
         if (clientSubScene != NULL && clientSubScene->isLoadedOnClient() && !loadedSubScenes.contains(clientSubScene))
            loadedSubScenes.push_back(clientSubScene);
      }
   }

   for (U32 i = 0; i < loadedSubScenes.size(); i++)
      loadSubSceneAtlas(loadedSubScenes[i]);
}

bool RenderProbeMgr::loadLevelAtlas(const char* levelAssetId)
{
   if (levelAssetId != NULL && levelAssetId[0] != '\0')
      mLevelAssetId = StringTable->insert(levelAssetId);

   String path = rootAtlasPath();
   ProbeAtlasHeader header;
   bool loaded = readProbeAtlasFile(path, mRootAtlasRoster, &header);
   markLowLodAtlasDirty();

   if (loaded)
      Con::printf("RenderProbeMgr::loadLevelAtlas() - loaded %u probes from %s", mRootAtlasRoster.size(), path.c_str());
   return loaded;
}

bool RenderProbeMgr::loadSubSceneAtlas(SubScene* subScene)
{
   if (subScene == NULL)
      return false;

   String path = subScene->getProbeAtlasPath();

   Vector<ProbeAtlasRecord> roster;
   ProbeAtlasHeader header;
   bool loaded = readProbeAtlasFile(path, roster, &header);

   if (roster.empty())
      mSubSceneAtlasRosters.erase(subScene);
   else
      mSubSceneAtlasRosters[subScene] = roster;

   markLowLodAtlasDirty();

   return loaded;
}

void RenderProbeMgr::unloadSubSceneAtlas(SubScene* subScene)
{
   mSubSceneAtlasRosters.erase(subScene);
   markLowLodAtlasDirty();
}

U32 RenderProbeMgr::getAtlasRosterCount()
{
   U32 count = mRootAtlasRoster.size();

   for (Map<SubScene*, Vector<ProbeAtlasRecord> >::Iterator itr = mSubSceneAtlasRosters.begin(); itr != mSubSceneAtlasRosters.end(); itr++)
      count += itr->value.size();

   return count;
}

IMPLEMENT_CALLBACK(RenderProbeMgr, onProbeBakeProgress, void, (U32 done, U32 total), (done, total),
   "@brief Called after each probe of an async bake (startBakeProbes) has been baked.\n\n"
   "@param done Number of probes handled so far.\n"
   "@param total Number of probes in the bake.\n");

IMPLEMENT_CALLBACK(RenderProbeMgr, onProbeBakeComplete, void, (bool success), (success),
   "@brief Called when an async bake (startBakeProbes) has finished or was cancelled.\n\n"
   "@param success False if the bake was cancelled or could not start.\n");

class ProbeBakeRunEvent : public SimEvent
{
public:
   void process(SimObject* object) override
   {
      RenderProbeMgr* manager = dynamic_cast<RenderProbeMgr*>(object);
      if (manager != NULL)
         manager->runBake();
   }
};

U32 RenderProbeMgr::pendingGhostCount()
{
   Scene* rootScene = Scene::getRootScene();
   if (rootScene == NULL)
      return 0;

   U32 pending = 0;
   SimGroup* clientGroup = Sim::getClientGroup();
   for (SimGroup::iterator itr = clientGroup->begin(); itr != clientGroup->end(); itr++)
   {
      NetConnection* conn = dynamic_cast<NetConnection*>(*itr);
      if (conn != NULL)
         pending += rootScene->getUnghostedObjectCount(conn);
   }

   return pending;
}

void RenderProbeMgr::beginBakeRun()
{
   Con::printf("RenderProbeMgr::beginBakeRun() - scene reports everything ghosted after %u ms; baking %u probe(s)", Platform::getRealMilliseconds() - mBakeWaitStartMS, mBakeProbes.size());

   //Just past the frame's target time, so the loop starts on a later frame
   mBakeState = BakeReady;
   const U32 nextFrameTime = getMax(Sim::getCurrentTime(), Sim::getTargetTime()) + 1;
   Sim::postEvent(this, new ProbeBakeRunEvent, nextFrameTime);
}

bool RenderProbeMgr::startBakeProbes()
{
   if (mBakeState != BakeIdle)
   {
      Con::warnf("RenderProbeMgr::startBakeProbes() - a bake is already running");
      return false;
   }

   Scene* rootScene = Scene::getRootScene();
   if (rootScene == NULL)
   {
      Con::warnf("RenderProbeMgr::startBakeProbes() - there is no scene to bake");
      return false;
   }

   mBakeProbes.clear();

   //Load every SubScene so its probes exist to bake. Their client ghosts follow once the network has sent them
   const U32 subSceneCount = rootScene->getSubSceneCount();
   for (U32 i = 0; i < subSceneCount; i++)
   {
      if (!rootScene->loadSubScene(i))
      {
         SubScene* subScene = rootScene->getSubScene(i);
         Con::warnf("RenderProbeMgr::startBakeProbes() - SubScene %s did not load (frozen loading, a failing load condition, "
            "or a load error), so its probes are not baked", subScene != NULL ? subScene->getName() : "<unknown>");
      }
   }

   Vector<ReflectionProbe*> probes;
   rootScene->findObjectByType<ReflectionProbe>(probes);

   for (U32 i = 0; i < probes.size(); i++)
   {
      if (!probes[i]->isClientObject())
         mBakeProbes.push_back(probes[i]);
   }

   mBakeState = BakeWaitingForGhosts;
   mBakeWaitStartMS = Platform::getRealMilliseconds();

   //Subscribe before checking the count so the signal can't be missed. Ghosting that never finishes has no signal,
   //so cancelBake() is the way out of that
   rootScene->getServerGhostingDoneSignal().notify(this, &RenderProbeMgr::onSceneGhostingDone);

   //Nothing to ghost means no signal is coming
   if (pendingGhostCount() == 0)
      beginBakeRun();

   return true;
}

void RenderProbeMgr::onSceneGhostingDone(NetConnection* conn)
{
   if (mBakeState != BakeWaitingForGhosts)
      return;

   //The signal is per client; carry on only once nothing is left pending for any of them
   if (pendingGhostCount() == 0)
      beginBakeRun();
}

void RenderProbeMgr::runBake()
{
   //A cancel or a newer bake may have come in since this was posted
   if (mBakeState != BakeReady)
      return;

   //Probes stop rendering for the duration of the capture
   preBake();
   mBakeState = BakeRunning;

   //Real time, as the sim clock is stopped during the loop. The progress callback is where the editor redraws
   U32 lastProgressMS = Platform::getRealMilliseconds();

   for (U32 i = 0; i < mBakeProbes.size(); i++)
   {
      ReflectionProbe* probe = mBakeProbes[i];
      if (probe != NULL)
         bakeProbe(probe);

      const U32 nowMS = Platform::getRealMilliseconds();
      if (nowMS - lastProgressMS >= (U32)getMax(smBakeProgressIntervalMS, 0))
      {
         onProbeBakeProgress_callback(i + 1, mBakeProbes.size());

         if (mBakeState != BakeRunning)
            return;

         lastProgressMS = Platform::getRealMilliseconds();
      }
   }

   onProbeBakeProgress_callback(mBakeProbes.size(), mBakeProbes.size());

   serializeProbeAtlas();
   finishBake(true);
}

void RenderProbeMgr::finishBake(bool success)
{
   Scene* rootScene = Scene::getRootScene();

   if (rootScene != NULL)
   {
      rootScene->getServerGhostingDoneSignal().remove(this, &RenderProbeMgr::onSceneGhostingDone);

      const U32 subSceneCount = rootScene->getSubSceneCount();
      for (U32 i = 0; i < subSceneCount; i++)
         rootScene->releaseSubScene(i);
   }

   if (mBakeState == BakeRunning)
      postBake();

   mBakeState = BakeIdle;
   mBakeProbes.clear();

   onProbeBakeComplete_callback(success);
}

void RenderProbeMgr::cancelBake()
{
   if (mBakeState == BakeIdle)
      return;

   finishBake(false);
}

S32 QSORT_CALLBACK RenderProbeMgr::lowLodCandidateCmp(const LowLodProbeCandidate* a, const LowLodProbeCandidate* b)
{
   const F32 diff = a->distance - b->distance;
   return diff > 0 ? 1 : diff < 0 ? -1 : 0;
}

void RenderProbeMgr::gatherLowLodProbes(const SceneRenderState* state, ProbeDataSet* probeDataSet)
{
   PROFILE_SCOPE(RenderProbeMgr_GatherLowLodProbes);

   probeDataSet->lowLodProbeCount = 0;

   if (getAtlasRosterCount() == 0 || mLowLodAtlas.isNull())
      return;

   const Point3F cameraPosition = state->getCameraPosition();
   const Frustum& viewFrustum = state->getCullingFrustum();

   //Probes already drawn from their cubemaps this frame don't also get lit from the atlas
   Vector<U32> renderedIds;
   for (U32 i = 0; i < probeDataSet->renderedProbes.size(); i++)
   {
      ReflectionProbe* object = probeDataSet->renderedProbes[i]->mObject;
      if (object != NULL)
         renderedIds.push_back(object->getProbeUniqueId().getHashCaseSensitive());
   }

   Vector<LowLodProbeCandidate> candidates;

   for (U32 i = 0; i <= mSubSceneAtlasRosters.size(); i++)
   {
      //Pass 0 is the root scene's roster, then one pass per loaded SubScene's roster
      const Vector<ProbeAtlasRecord>* roster = &mRootAtlasRoster;
      U32 rosterBase = mLowLodAtlasRootBase;
      if (i > 0)
      {
         Map<SubScene*, Vector<ProbeAtlasRecord> >::Iterator itr = mSubSceneAtlasRosters.begin();
         for (U32 skip = 1; skip < i; skip++)
            ++itr;
         roster = &itr->value;

         Map<SubScene*, U32>::Iterator baseItr = mLowLodAtlasSubSceneBase.find(itr->key);
         if (baseItr == mLowLodAtlasSubSceneBase.end())
            continue;

         rosterBase = baseItr->value;
      }

      for (U32 r = 0; r < roster->size(); r++)
      {
         const ProbeAtlasRecord& record = (*roster)[r];

         bool alreadyRendered = false;
         for (U32 i = 0; i < renderedIds.size() && !alreadyRendered; i++)
            alreadyRendered = (renderedIds[i] == record.persistentProbeId);

         if (alreadyRendered)
            continue;

         const Box3F probeBounds = record.getBounds();

         const F32 distance = probeBounds.getDistanceToPoint(cameraPosition);
         if (distance > smMaxLowLodProbeDrawDistance)
            continue;

         //Skip anything outside the view frustum
         if (viewFrustum.isCulled(probeBounds))
            continue;

         //If it can't fit in the atlas, skip it
         if (rosterBase + r >= mLowLodAtlas->getHeight())
            continue;

         LowLodProbeCandidate candidate;
         candidate.row = rosterBase + r;
         candidate.distance = distance;
         candidates.push_back(candidate);
      }
   }

   if (candidates.empty())
      return;

   candidates.sort(lowLodCandidateCmp);

   const U32 count = getMin(getMaxLowLodProbes(), (U32)candidates.size());

   //Each entry is just its row and the distance fade
   probeDataSet->lowLodList.setSize(count);
   for (U32 k = 0; k < count; k++)
      probeDataSet->lowLodList[k] = Point4F((F32)candidates[k].row, lowLodDistanceFade(candidates[k].distance), 0.0f, 0.0f);

   probeDataSet->lowLodProbeCount = count;
}

const ProbeAtlasRecord* RenderProbeMgr::findRosterRecord(U32 persistentProbeId) const
{
   for (U32 i = 0; i < mRootAtlasRoster.size(); i++)
   {
      if (mRootAtlasRoster[i].persistentProbeId == persistentProbeId)
         return &mRootAtlasRoster[i];
   }

   for (Map<SubScene*, Vector<ProbeAtlasRecord> >::ConstIterator itr = mSubSceneAtlasRosters.begin(); itr != mSubSceneAtlasRosters.end(); itr++)
   {
      const Vector<ProbeAtlasRecord>& roster = itr->value;
      for (U32 i = 0; i < roster.size(); i++)
      {
         if (roster[i].persistentProbeId == persistentProbeId)
            return &roster[i];
      }
   }

   return NULL;
}

S32 RenderProbeMgr::findRosterRow(U32 persistentProbeId) const
{
   for (U32 i = 0; i < mRootAtlasRoster.size(); i++)
   {
      if (mRootAtlasRoster[i].persistentProbeId == persistentProbeId)
         return mLowLodAtlasRootBase + i;
   }

   for (Map<SubScene*, Vector<ProbeAtlasRecord> >::ConstIterator itr = mSubSceneAtlasRosters.begin(); itr != mSubSceneAtlasRosters.end(); itr++)
   {
      Map<SubScene*, U32>::ConstIterator baseItr = mLowLodAtlasSubSceneBase.find(itr->key);
      if (baseItr == mLowLodAtlasSubSceneBase.end())
         continue;

      const Vector<ProbeAtlasRecord>& roster = itr->value;
      for (U32 i = 0; i < roster.size(); i++)
      {
         if (roster[i].persistentProbeId == persistentProbeId)
            return baseItr->value + i;
      }
   }

   return -1;
}

U32 RenderProbeMgr::copyRosterRows(const Vector<ProbeAtlasRecord>& roster, U8* data, U32 firstRow, U32 capacity)
{
   const U32 count = getMin((U32)roster.size(), capacity - firstRow);
   if (count > 0)
      dMemcpy(data + firstRow * sProbeAtlasRowBytes, &roster[0], count * sProbeAtlasRowBytes);

   return count;
}

void RenderProbeMgr::buildLowLodAtlas()
{
   PROFILE_SCOPE(RenderProbeMgr_BuildLowLodAtlas);

   mLowLodAtlasDirty = false;
   mLowLodAtlas.free();
   mLowLodAtlasSubSceneBase.clear();
   mLowLodAtlasRootBase = 0;

   U32 totalRows = mRootAtlasRoster.size();

   for (Map<SubScene*, Vector<ProbeAtlasRecord> >::Iterator itr = mSubSceneAtlasRosters.begin(); itr != mSubSceneAtlasRosters.end(); itr++)
      totalRows += itr->value.size();

   if (totalRows > sLowLodAtlasRows)
   {
      Con::warnf("RenderProbeMgr::buildLowLodAtlas() - Total rows: %u, Max rows: %u. Using only up to Max row count.",
         totalRows, sLowLodAtlasRows);

      totalRows = sLowLodAtlasRows;
   }

   const U32 rowCount = getMax(totalRows, (U32)1);

   //new U8[]: DDSFile::SurfaceData frees its mips with delete[]
   U8* buffer = new U8[sProbeAtlasRowBytes * rowCount];
   dMemset(buffer, 0, sProbeAtlasRowBytes * rowCount);

   U32 nextRow = 0;

   mLowLodAtlasRootBase = nextRow;
   nextRow += copyRosterRows(mRootAtlasRoster, buffer, nextRow, rowCount);

   for (Map<SubScene*, Vector<ProbeAtlasRecord> >::Iterator itr = mSubSceneAtlasRosters.begin(); itr != mSubSceneAtlasRosters.end(); itr++)
   {
      mLowLodAtlasSubSceneBase[itr->key] = nextRow;
      nextRow += copyRosterRows(itr->value, buffer, nextRow, rowCount);
   }

   DDSFile* ddsFile = new DDSFile;
   ddsFile->mFormat = GFXFormatR32G32B32A32F;
   ddsFile->mBytesPerPixel = sizeof(F32) * 4;
   ddsFile->mHeight = rowCount;
   ddsFile->mWidth = sProbeAtlasRowTexels;
   ddsFile->mMipMapCount = 1;
   ddsFile->mSurfaces.push_back(new DDSFile::SurfaceData);
   ddsFile->mSurfaces.last()->mMips.push_back(buffer);

   //Now set the sucker
   mLowLodAtlas.set(ddsFile, &GFXTexturePersistentProfile, true, "RenderProbeMgr::mLowLodAtlas");
}

bool RenderProbeMgr::handleGFXEvent(GFXDevice::GFXDeviceEventType event)
{
   //On the off chance the device changes, we do a rebuild
   if (event == GFXDevice::deDestroy || event == GFXDevice::deInit)
   {
      mLowLodAtlas.free();
      markLowLodAtlasDirty();
   }

   return true;
}

void RenderProbeMgr::applyHighLodSwitch(const Point3F& cameraPosition, ProbeDataSet* probeDataSet)
{
   PROFILE_SCOPE(RenderProbeMgr_ApplyHighLodSwitch);

   const F32 range = mMax(smMaxProbeDrawDistance, 0.001f);

   for (U32 i = 0; i < probeDataSet->renderedProbes.size() && i < probeDataSet->effectiveProbeCount; i++)
   {
      ReflectionProbe::ProbeInfo* info = probeDataSet->renderedProbes[i];

      //No atlas row to hand over to, so keep the plain distance falloff. .w < 0 on the
      //position tells the shader and refPos.w is the cubemap share. 1 = cubemaps only
      probeDataSet->probePositionArray[i].w = -1.0f;
      probeDataSet->probeRefPositionArray[i].w = 1.0f;
      probeDataSet->highLodAtlasRow[i] = Point4F(-1.0f, 0.0f, 0.0f, 0.0f);

      if (info->mObject == NULL)
         continue;

      const U32 probeId = info->mObject->getProbeUniqueId().getHashCaseSensitive();
      const ProbeAtlasRecord* record = findRosterRecord(probeId);
      const S32 row = findRosterRow(probeId);
      if (record == NULL || row < 0)
         continue;

      //Ease from cubemaps to the atlas ambient color toward the draw distance, keeping its weight continuous
      const F32 closeness = 1.0f - (record->position - cameraPosition).len() / range;
      const F32 cubemapShare = mClampF(closeness / (1.0f - sProbeHighLodFadeStart), 0.0f, 1.0f);
      probeDataSet->probePositionArray[i].w = lowLodDistanceFade(record->getBounds().getDistanceToPoint(cameraPosition));
      probeDataSet->probeRefPositionArray[i].w = cubemapShare;
      probeDataSet->highLodAtlasRow[i] = Point4F((F32)row, 0.0f, 0.0f, 0.0f);
   }
}

U32 RenderProbeMgr::getMaxLowLodProbes()
{
   return mClamp(smMaxLowLodProbes, 1, sMaxLowLodProbes);
}

F32 RenderProbeMgr::lowLodDistanceFade(F32 distance)
{
   const F32 fadeStart = smMaxLowLodProbeDrawDistance * sLowLodFadeStart;
   return 1.0f - mClampF((distance - fadeStart) / mMax(smMaxLowLodProbeDrawDistance - fadeStart, 0.001f), 0.0f, 1.0f);
}

void RenderProbeMgr::dumpProbeAtlasRow(ReflectionProbe* probe)
{
   if (probe == NULL)
      return;

   const ProbeAtlasRecord* found = findRosterRecord(probe->getProbeUniqueId().getHashCaseSensitive());
   if (found == NULL)
   {
      Con::warnf("RenderProbeMgr::dumpProbeAtlasRow() - probe %u has no row in the loaded probe atlases. Either not baked yet, or its scene isn't loaded", probe->getId());
      return;
   }

   const ProbeAtlasRecord& record = *found;

   MatrixF worldToObj(true);
   dMemcpy((F32*)worldToObj, record.worldToObj, sizeof(record.worldToObj));

   Con::printf("Probe %u atlas row:", probe->getId());
   Con::printf("persistentProbeId: %u", record.persistentProbeId);
   Con::printf("position: %g %g %g", record.position.x, record.position.y, record.position.z);
   Con::printf("refOffset: %g %g %g  refScale: %g %g %g", record.refOffset.x, record.refOffset.y, record.refOffset.z,
      record.refScale.x, record.refScale.y, record.refScale.z);
   Con::printf("shapeType: %g  radius: %g  atten: %g  flags: %u", record.shapeType, record.radius, record.atten, record.flags);
   Con::printf("bounds: [%g %g %g] - [%g %g %g]", record.boundsMin.x, record.boundsMin.y, record.boundsMin.z,
      record.boundsMax.x, record.boundsMax.y, record.boundsMax.z);
   Con::printf("worldToObj position: %g %g %g", worldToObj.getPosition().x, worldToObj.getPosition().y, worldToObj.getPosition().z);

   Con::printf("ambient: %g %g %g", record.ambient[0], record.ambient[1], record.ambient[2]);

   Con::printf("flags: canDamp %d, interior %d", (record.flags & ProbeAtlasRecord::CanDamp) != 0,
      (record.flags & ProbeAtlasRecord::Interior) != 0);
}

//=============================================================================
// Console functions
//=============================================================================
DefineEngineMethod(RenderProbeMgr, bakeProbe, void, (ReflectionProbe* probe), (nullAsType< ReflectionProbe*>()),
   "@brief Bakes the cubemaps for a reflection probe\n\n.")
{
   object->preBake();
   if(probe != NULL)
   {
      object->bakeProbe(probe);

      //Keep the atlas in step with the cubemaps: merges this probe's new row into the existing atlas
      object->serializeProbeAtlas();
   }
   object->postBake();
}

DefineEngineMethod(RenderProbeMgr, dumpProbeAtlasRow, void, (ReflectionProbe* probe), (nullAsType<ReflectionProbe*>()),
   "@brief Prints a probe's row from the loaded probe atlases (root scene or SubScene)\n\n"
   "@param probe The reflection probe to look up.\n")
{
   object->dumpProbeAtlasRow(probe);
}

DefineEngineMethod(RenderProbeMgr, loadLevelAtlas, bool, (const char* levelAssetId), (""),
   "@brief Loads the root level's own probe atlas into the runtime roster\n\n"
   "@param levelAssetId The LevelAsset id the server told this client about. The atlas path is resolved from that asset.\n")
{
   return object->loadLevelAtlas(levelAssetId);
}

DefineEngineMethod(RenderProbeMgr, loadSubSceneAtlas, bool, (SubScene* subScene), (nullAsType<SubScene*>()),
   "@brief Loads a SubScene's own probe atlas into the runtime roster\n\n.")
{
   return object->loadSubSceneAtlas(subScene);
}

DefineEngineMethod(RenderProbeMgr, unloadSubSceneAtlas, void, (SubScene* subScene), (nullAsType<SubScene*>()),
   "@brief Unloads a SubScene's probe atlas roster entries\n\n.")
{
   object->unloadSubSceneAtlas(subScene);
}

DefineEngineMethod(RenderProbeMgr, clearLevelAtlas, void, (), ,
   "@brief Drops the root level's probe atlas roster and the level asset it was resolved from\n\n.")
{
   object->clearLevelAtlas();
}

DefineEngineMethod(RenderProbeMgr, startBakeProbes, bool, (), ,
   "@brief Bakes every reflection probe in the scene, and every SubScene, by loading and waiting for subScenes to ghost first.\n"
   "Once everything is loaded, everything is baked and rendered to IBL files/atlases.\n\n"
   "@return False if a bake was already running or there is no scene.\n")
{
   return object->startBakeProbes();
}

DefineEngineMethod(RenderProbeMgr, cancelBake, void, (), ,
   "@brief Stops a bake currently running. Probes already baked stay baked.\n")
{
   object->cancelBake();
}

DefineEngineMethod(RenderProbeMgr, isBaking, bool, (), ,
   "@brief True while a bake is running.\n")
{
   return object->isBaking();
}

DefineEngineMethod(RenderProbeMgr, bakeProbes, void, (),, "@brief Iterates over all reflection probes in the scene and bakes their cubemaps\n\n.")
{
   object->preBake();
   object->bakeProbes();
   object->postBake();
}
