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
#include "T3D/gameBase/gameConnection.h"

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

F32 RenderProbeMgr::smInteriorSunResidual = 0.1f;
F32 RenderProbeMgr::smCaptureLightFloor = 0.04f;

//A challenger must beat the weakest resident by this much to take its high LOD slot
//Helps keep the high LOD slots from constantly flipping between two probes that are very close in score
static const F32 sProbeSwapMargin = 0.10f;
//Max slot changes (cubemap uploads) per frame
static const S32 sMaxProbeSwapsPerFrame = 2;

static const S32 sMaxHighLodProbes = 16;

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
   mLastPriorityUpdateMS(0)
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
   mLastPriorityUpdateMS = 0;
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
   Con::addVariable("$pref::ReflectionProbes::maxProbeDrawDistance", TypeF32, &RenderProbeMgr::smMaxProbeDrawDistance, "Max distance for reflection probes to render.\n");
   Con::addVariable("$pref::ReflectionProbes::maxHighProbesPerFrame", TypeS32, &RenderProbeMgr::smMaxHighProbesPerFrame, "Max number of Environment Probes that can be rendered per-frame.\n");
   Con::addVariable("$pref::ReflectionProbes::bakeResolution", TypeS32, &RenderProbeMgr::smProbeBakeResolution, "");
   Con::addVariable("$pref::ReflectionProbes::maxHighLODSlots", TypeS32, &RenderProbeMgr::smMaxHighLodSlots, "Size of the high-LOD cubemap slot pool.\n");

   Con::addVariable("$pref::ReflectionProbes::interiorSunResidual", TypeF32, &RenderProbeMgr::smInteriorSunResidual, "How much of the sun is left inside a probe flagged Interior once its shadows have faded out (0 = none, 1 = no effect).\n");
   Con::addVariable("$pref::ReflectionProbes::captureLightFloor", TypeF32, &RenderProbeMgr::smCaptureLightFloor, "How much of a light's diffuse term a probe capture keeps even in full shadow, so shadowed surfaces aren't pitch black in a probe (0 = none). Probes flagged Interior capture with none, so a sealed room can bake dark.\n");
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
      //Flags for the shader: bit 0 = wetness allowed, bit 1 = Interior probe
      probeDataSet->refScaleArray[i].w = (curEntry.mProbeInfo->mCanDamp ? 1.0f : 0.0f) + (curEntry.mProbeInfo->mInterior ? 2.0f : 0.0f);

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
   PROFILE_SCOPE(ProbeManager_UpdateProbePriorities);

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
      return;

   //Captures give lights a small floor in full shadow, except Interior probes so a sealed room can bake dark
   Con::setFloatVariable("$ReflectionProbes::CaptureLightFloor", clientProbe->mProbeInfo.mInterior ? 0.0f : smCaptureLightFloor);

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

   mProbeData = ProbeDataSet(smMaxHighProbesPerFrame);

   getBestProbes(state->getCameraPosition(), &mProbeData);
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

   // Initialize and set the per-frame data
   _setupPerFrameParameters(state);

   // Early out if nothing to draw.
   if (!RenderProbeMgr::smRenderReflectionProbes || (!mHasSkylight && mProbeData.effectiveProbeCount == 0))
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
   mProbeArrayEffect->setShaderConst("$skylightCubemapIdx", (S32)mProbeData.skyLightIdx);
   mProbeArrayEffect->setShaderConst(ShaderGenVars::skylightDamp, mProbeData.skyLightDamp);

   mProbeArrayEffect->setShaderConst("$cubeMips", (float)mPrefilterArray->getMipLevels());

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
   object->preBake();
   if(probe != NULL)
      object->bakeProbe(probe);
   object->postBake();
}

DefineEngineMethod(RenderProbeMgr, bakeProbes, void, (),, "@brief Iterates over all reflection probes in the scene and bakes their cubemaps\n\n.")
{
   object->preBake();
   object->bakeProbes();
   object->postBake();
}
