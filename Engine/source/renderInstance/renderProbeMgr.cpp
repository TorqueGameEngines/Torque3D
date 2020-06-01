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
#include "console/consoleTypes.h"
#include "scene/sceneObject.h"
#include "materials/materialManager.h"
#include "scene/sceneRenderState.h"
#include "math/util/sphereMesh.h"
#include "math/util/matrixSet.h"
#include "materials/processedMaterial.h"
#include "renderInstance/renderDeferredMgr.h"
#include "math/mPolyhedron.impl.h"
#include "gfx/gfxTransformSaver.h"
#include "lighting/advanced/advancedLightBinManager.h" //for ssao
#include "gfx/gfxDebugEvent.h"
#include "shaderGen/shaderGenVars.h"
#include "materials/shaderData.h"

#include "gfx/gfxTextureManager.h"
#include "scene/reflectionManager.h"

#include "postFx/postEffect.h"
#include "T3D/lighting/reflectionProbe.h"
#include "T3D/lighting/IBLUtilities.h"

//For our cameraQuery setup
#include "T3D/gameTSCtrl.h"

#define TORQUE_GFX_VISUAL_DEBUG //renderdoc debugging

IMPLEMENT_CONOBJECT(RenderProbeMgr);

ConsoleDocClass( RenderProbeMgr, 
   "@brief A render bin which uses object callbacks for rendering.\n\n"
   "This render bin gathers object render instances and calls its delegate "
   "method to perform rendering.  It is used infrequently for specialized "
   "scene objects which perform custom rendering.\n\n"
   "@ingroup RenderBin\n" );

RenderProbeMgr *RenderProbeMgr::smProbeManager = NULL;

bool RenderProbeMgr::smRenderReflectionProbes = true;

S32 QSORT_CALLBACK AscendingReflectProbeInfluence(const void* a, const void* b)
{
   // Debug Profiling.
   PROFILE_SCOPE(AdvancedLightBinManager_AscendingReflectProbeInfluence);

   // Fetch asset definitions.
   const ProbeRenderInst* pReflectProbeA = (*(ProbeRenderInst**)a);
   const ProbeRenderInst* pReflectProbeB = (*(ProbeRenderInst**)b);
   //sort by score
   return  pReflectProbeA->mScore - pReflectProbeB->mScore;
}

//
//
ProbeRenderInst::ProbeRenderInst() :
   mIsEnabled(true),
   mTransform(true),
   mDirty(false),
   mPriority(1.0f),
   mScore(0.0f),
   mPrefilterCubemap(NULL),
   mIrradianceCubemap(NULL),
   mRadius(1.0f),
   mProbeRefOffset(0, 0, 0),
   mProbeRefScale(1,1,1),
   mAtten(0.0),
   mCubemapIndex(0),
   mIsSkylight(false),
   mProbeIdx(0),
   mProbeShapeType(Box)
{
}

ProbeRenderInst::~ProbeRenderInst()
{
   if (mPrefilterCubemap && mPrefilterCubemap.isValid())
   {
      mPrefilterCubemap.free();
   }
   if (mIrradianceCubemap && mIrradianceCubemap.isValid())
   {
      mIrradianceCubemap.free();
   }
}

void ProbeRenderInst::set(const ProbeRenderInst *probeInfo)
{
   mTransform = probeInfo->mTransform;
   mPrefilterCubemap = probeInfo->mPrefilterCubemap;
   mIrradianceCubemap = probeInfo->mIrradianceCubemap;
   mRadius = probeInfo->mRadius;
   mProbeShapeType = probeInfo->mProbeShapeType;
   mBounds = probeInfo->mBounds;
   mIsSkylight = probeInfo->mIsSkylight;
   mScore = probeInfo->mScore;
   mAtten = probeInfo->mAtten;
}

//
//
ProbeShaderConstants::ProbeShaderConstants()
   : mInit(false),
   mShader(NULL),
   mProbePositionSC(NULL),
   mProbeRefPosSC(NULL),
   mRefBoxMinSC(NULL),
   mRefBoxMaxSC(NULL),
   mProbeConfigDataSC(NULL),
   mProbeSpecularCubemapSC(NULL),
   mProbeIrradianceCubemapSC(NULL),
   mProbeCountSC(NULL),
   mBRDFTextureMap(NULL),
   mSkylightCubemapIdxSC(NULL),
   mWorldToObjArraySC(NULL)
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
   mProbePositionSC = shader->getShaderConstHandle(ShaderGenVars::probePosition);
   mProbeRefPosSC = shader->getShaderConstHandle(ShaderGenVars::probeRefPos);
   mRefBoxMinSC = shader->getShaderConstHandle(ShaderGenVars::refBoxMin);
   mRefBoxMaxSC = shader->getShaderConstHandle(ShaderGenVars::refBoxMax);
   mWorldToObjArraySC = shader->getShaderConstHandle(ShaderGenVars::worldToObjArray);
   mProbeConfigDataSC = shader->getShaderConstHandle(ShaderGenVars::probeConfigData);
   mProbeSpecularCubemapSC = shader->getShaderConstHandle(ShaderGenVars::specularCubemapAR);
   mProbeIrradianceCubemapSC = shader->getShaderConstHandle(ShaderGenVars::irradianceCubemapAR);
   mProbeCountSC = shader->getShaderConstHandle(ShaderGenVars::probeCount);

   mBRDFTextureMap = shader->getShaderConstHandle(ShaderGenVars::BRDFTextureMap);

   mSkylightCubemapIdxSC = shader->getShaderConstHandle(ShaderGenVars::skylightCubemapIdx);

   mInit = true;
}

bool ProbeShaderConstants::isValid()
{
   if (mProbePositionSC->isValid() ||
      mProbeConfigDataSC->isValid() ||
      mRefBoxMinSC->isValid() ||
      mRefBoxMaxSC->isValid() ||
      mProbeSpecularCubemapSC->isValid() ||
      mProbeIrradianceCubemapSC->isValid())
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
	mProbesDirty(false),
   mHasSkylight(false),
   mSkylightCubemapIdx(-1),
   mCubeMapCount(0),
   mDefaultSkyLight(nullptr)
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
   mDefaultSkyLight = nullptr;
   mEffectiveProbeCount = 0;
   mHasSkylight = false;
   mSkylightCubemapIdx = -1;
   mLastConstants = nullptr;
   mMipCount = 0;
   mProbesDirty = false;
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

   //pre-allocate a few slots
   mIrradianceArray->init(PROBE_ARRAY_SLOT_BUFFER_SIZE, PROBE_IRRAD_SIZE, PROBE_FORMAT);
   mPrefilterArray->init(PROBE_ARRAY_SLOT_BUFFER_SIZE, PROBE_PREFILTER_SIZE, PROBE_FORMAT);
   mCubeSlotCount = PROBE_ARRAY_SLOT_BUFFER_SIZE;

   //create our own default default skylight
   mDefaultSkyLight = new ProbeRenderInst;
   mDefaultSkyLight->mProbeShapeType = ProbeRenderInst::Skylight;
   mDefaultSkyLight->mIsEnabled = false;

   String defaultIrradMapPath = GFXTextureManager::getDefaultIrradianceCubemapPath();
   if (!mDefaultSkyLight->mIrradianceCubemap.set(defaultIrradMapPath))
   {
      Con::errorf("RenderProbeMgr::onAdd: Failed to load default irradiance cubemap");
      return false;
   }

   String defaultPrefilterPath = GFXTextureManager::getDefaultPrefilterCubemapPath();
   if (!mDefaultSkyLight->mPrefilterCubemap.set(defaultPrefilterPath))
   {
      Con::errorf("RenderProbeMgr::onAdd: Failed to load default prefilter cubemap");
      return false;
   }

   String brdfTexturePath = GFXTextureManager::getBRDFTexturePath();
   if (!mBRDFTexture.set(brdfTexturePath, &GFXTexturePersistentSRGBProfile, "BRDFTexture"))
   {
      Con::errorf("RenderProbeMgr::onAdd: Failed to load BRDF Texture");
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
   Parent::initPersistFields();
}

void RenderProbeMgr::addElement(RenderInst *inst)
{
   // If this instance is translucent handle it in RenderTranslucentMgr
   //if (inst->translucentSort)
      return;

   //AssertFatal(inst->defaultKey != 0, "RenderMeshMgr::addElement() - Got null sort key... did you forget to set it?");

   /*internalAddElement(inst);

   ProbeRenderInst* probeInst = static_cast<ProbeRenderInst*>(inst);

   if (probeInst->mIsSkylight)
   {
      addSkylightProbe(probeInst);
   }
   else
   {
      if (probeInst->mProbeShapeType == ProbeInfo::Sphere)
         addSphereReflectionProbe(probeInst);
      else
         addConvexReflectionProbe(probeInst);
   }*/
}

ProbeRenderInst* RenderProbeMgr::registerProbe()
{
   mRegisteredProbes.increment();
   ProbeRenderInst* newProbe = &mRegisteredProbes.last();

   newProbe->mProbeIdx = mRegisteredProbes.size() - 1;

   const U32 cubeIndex = _findNextEmptyCubeSlot();
   if (cubeIndex == INVALID_CUBE_SLOT)
   {
      Con::warnf("RenderProbeMgr::addProbe: Invalid cubemap slot.");
      return nullptr;
   }

   //check if we need to resize the cubemap array
   if (cubeIndex >= mCubeSlotCount)
   {
      //alloc temp array handles
      GFXCubemapArrayHandle irr = GFXCubemapArrayHandle(GFX->createCubemapArray());
      GFXCubemapArrayHandle prefilter = GFXCubemapArrayHandle(GFX->createCubemapArray());

      irr->init(mCubeSlotCount + PROBE_ARRAY_SLOT_BUFFER_SIZE, PROBE_IRRAD_SIZE, PROBE_FORMAT);
      prefilter->init(mCubeSlotCount + PROBE_ARRAY_SLOT_BUFFER_SIZE, PROBE_PREFILTER_SIZE, PROBE_FORMAT);

      mIrradianceArray->copyTo(irr);
      mPrefilterArray->copyTo(prefilter);

      //assign the temp handles to the new ones, this will destroy the old ones as well
      mIrradianceArray = irr;
      mPrefilterArray = prefilter;

      mCubeSlotCount += PROBE_ARRAY_SLOT_BUFFER_SIZE;
   }

   newProbe->mCubemapIndex = cubeIndex;
   //mark cubemap slot as taken
   mCubeMapSlots[cubeIndex] = true;
   mCubeMapCount++;

#ifdef TORQUE_DEBUG
   Con::warnf("RenderProbeMgr::registerProbe: Registered probe %u to cubeIndex %u", newProbe->mProbeIdx, cubeIndex);
#endif

   mProbesDirty = true;

   return newProbe;
}

void RenderProbeMgr::unregisterProbe(U32 probeIdx)
{
   //Mostly for consolidation, but also lets us sanity check or prep any other data we need for rendering this in one place at time of flagging for render
   if (probeIdx >= mRegisteredProbes.size())
      return;

   if (mRegisteredProbes[probeIdx].mCubemapIndex == INVALID_CUBE_SLOT)
      return;

   //mark cubemap slot as available now
   mCubeMapSlots[mRegisteredProbes[probeIdx].mCubemapIndex] = false;
   mCubeMapCount--;

   mRegisteredProbes.erase(probeIdx);

   //recalculate all the probe's indicies just to be sure
   for (U32 i = 0; i < mRegisteredProbes.size(); i++)
   {
      mRegisteredProbes[i].mProbeIdx = i;
   }

   //rebuild our probe data
   mProbesDirty = true;
}

//
//
PostEffect* RenderProbeMgr::getProbeArrayEffect()
{
   if (!mProbeArrayEffect)
   {
      mProbeArrayEffect = dynamic_cast<PostEffect*>(Sim::findObject("reflectionProbeArrayPostFX"));

      if (!mProbeArrayEffect)
         return nullptr;
   }
   return mProbeArrayEffect;
}

//remove
//Con::setIntVariable("lightMetrics::activeReflectionProbes", mReflectProbeBin.size());
//Con::setIntVariable("lightMetrics::culledReflectProbes", 0/*mNumLightsCulled*/);
//

void RenderProbeMgr::updateProbes()
{
	mProbesDirty = true;
}

void RenderProbeMgr::_setupStaticParameters()
{
   //Array rendering
   U32 probeCount = mRegisteredProbes.size();

   mEffectiveProbeCount = 0;
   mMipCount = 1;

   mHasSkylight = false;
   mSkylightCubemapIdx = -1;

   if (probePositionsData.size() != MAXPROBECOUNT)
   {
      probePositionsData.setSize(MAXPROBECOUNT);
      probeRefPositionsData.setSize(MAXPROBECOUNT);
      probeWorldToObjData.setSize(MAXPROBECOUNT);
      refBoxMinData.setSize(MAXPROBECOUNT);
      refBoxMaxData.setSize(MAXPROBECOUNT);
      probeConfigData.setSize(MAXPROBECOUNT);
   }

   probePositionsData.fill(Point4F::Zero);
   probeRefPositionsData.fill(Point4F::Zero);
   probeWorldToObjData.fill(MatrixF::Identity);
   refBoxMinData.fill(Point4F::Zero);
   refBoxMaxData.fill(Point4F::Zero);
   probeConfigData.fill(Point4F(-1,0,0,0));

   for (U32 i = 0; i < probeCount; i++)
   {
      if (mEffectiveProbeCount >= MAXPROBECOUNT)
         break;

      const ProbeRenderInst& curEntry = mRegisteredProbes[i];
      if (!curEntry.mIsEnabled)
         continue;

      U32 mips = mRegisteredProbes[i].mPrefilterCubemap.getPointer()->getMipMapLevels();
      mMipCount = mips != 0 && mips >= mMipCount ? mips : 0;

      if (curEntry.mIsSkylight)
      {
         mSkylightCubemapIdx = curEntry.mCubemapIndex;
         continue;
      }

      //Setup
      Point3F probePos = curEntry.getPosition();
      Point3F refPos = curEntry.getPosition() +curEntry.mProbeRefOffset;
      probePositionsData[mEffectiveProbeCount] = Point4F(probePos.x, probePos.y, probePos.z,0);
      probeRefPositionsData[mEffectiveProbeCount] = Point4F(refPos.x, refPos.y, refPos.z, 0);

      probeWorldToObjData[mEffectiveProbeCount] = curEntry.getTransform();
      Point3F bbMin = refPos - curEntry.mProbeRefScale/2 * curEntry.getTransform().getScale();
      Point3F bbMax = refPos + curEntry.mProbeRefScale/2 * curEntry.getTransform().getScale();
      refBoxMinData[mEffectiveProbeCount] = Point4F(bbMin.x, bbMin.y, bbMin.z, 0);
      refBoxMaxData[mEffectiveProbeCount] = Point4F(bbMax.x, bbMax.y, bbMax.z, 0);

      probeConfigData[mEffectiveProbeCount] = Point4F(curEntry.mProbeShapeType, 
         curEntry.mRadius,
         curEntry.mAtten,
         curEntry.mCubemapIndex);

      mEffectiveProbeCount++;
   }

   mProbesDirty = false;
}

void RenderProbeMgr::updateProbeTexture(ProbeRenderInst* probeInfo)
{
   if (probeInfo->mIrradianceCubemap.isNull() || !probeInfo->mIrradianceCubemap->isInitialized())
   {
      Con::errorf("RenderProbeMgr::updateProbeTexture() - tried to update a probe's texture with an invalid or uninitialized irradiance map!");
      return;
   }

   if (probeInfo->mPrefilterCubemap.isNull() || !probeInfo->mPrefilterCubemap->isInitialized())
   {
      Con::errorf("RenderProbeMgr::updateProbeTexture() - tried to update a probe's texture with an invalid or uninitialized specular map!");
      return;
   }

   const U32 cubeIndex = probeInfo->mCubemapIndex;
   mIrradianceArray->updateTexture(probeInfo->mIrradianceCubemap, cubeIndex);
   mPrefilterArray->updateTexture(probeInfo->mPrefilterCubemap, cubeIndex);

#ifdef TORQUE_DEBUG
   Con::warnf("UpdatedProbeTexture - probeIdx: %u on cubeIndex %u, Irrad validity: %d, Prefilter validity: %d", probeInfo->mProbeIdx, cubeIndex,
      probeInfo->mIrradianceCubemap->isInitialized(), probeInfo->mPrefilterCubemap->isInitialized());
#endif
}

void RenderProbeMgr::reloadTextures()
{
   U32 probeCount = mRegisteredProbes.size();
   for (U32 i = 0; i < probeCount; i++)
   {
      updateProbeTexture(&mRegisteredProbes[i]);
   }

   mProbesDirty = true;
}

void RenderProbeMgr::_setupPerFrameParameters(const SceneRenderState *state)
{
   PROFILE_SCOPE(RenderProbeMgr_SetupPerFrameParameters);
}

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

void RenderProbeMgr::_update4ProbeConsts(const SceneData &sgData,
   MatrixSet &matSet,
   ProbeShaderConstants *probeShaderConsts,
   GFXShaderConstBuffer *shaderConsts)
{
   PROFILE_SCOPE(ProbeManager_Update4ProbeConsts);

   return;

   // Skip over gathering lights if we don't have to!
   //if (probeShaderConsts->isValid())
   {
      PROFILE_SCOPE(ProbeManager_Update4ProbeConsts_setProbes);

      const U32 MAX_FORWARD_PROBES = 4;
      ProbeDataSet probeSet(MAX_FORWARD_PROBES);

      matSet.restoreSceneViewProjection();

      getBestProbes(sgData.objTrans->getPosition(), &probeSet);

      shaderConsts->setSafe(probeShaderConsts->mProbeCountSC, (S32)probeSet.effectiveProbeCount);

      shaderConsts->setSafe(probeShaderConsts->mProbePositionSC, probeSet.probePositionArray);
      shaderConsts->setSafe(probeShaderConsts->mProbeRefPosSC, probeSet.probeRefPositionArray);

      if(probeShaderConsts->isValid())
         shaderConsts->set(probeShaderConsts->mWorldToObjArraySC, probeSet.probeWorldToObjArray.address(), probeSet.effectiveProbeCount, GFXSCT_Float4x4);

      shaderConsts->setSafe(probeShaderConsts->mRefBoxMinSC, probeSet.refBoxMinArray);
      shaderConsts->setSafe(probeShaderConsts->mRefBoxMaxSC, probeSet.refBoxMaxArray);
      shaderConsts->setSafe(probeShaderConsts->mProbeConfigDataSC, probeSet.probeConfigArray);

      shaderConsts->setSafe(probeShaderConsts->mSkylightCubemapIdxSC, (float)probeSet.skyLightIdx);

      if(probeShaderConsts->mBRDFTextureMap->getSamplerRegister() != -1 && mBRDFTexture.isValid())
         GFX->setTexture(probeShaderConsts->mBRDFTextureMap->getSamplerRegister(), mBRDFTexture);

      if(probeShaderConsts->mProbeSpecularCubemapSC->getSamplerRegister() != -1)
         GFX->setCubeArrayTexture(probeShaderConsts->mProbeSpecularCubemapSC->getSamplerRegister(), mPrefilterArray);
      if(probeShaderConsts->mProbeIrradianceCubemapSC->getSamplerRegister() != -1)
         GFX->setCubeArrayTexture(probeShaderConsts->mProbeIrradianceCubemapSC->getSamplerRegister(), mIrradianceArray);
   }
}

void RenderProbeMgr::getBestProbes(const Point3F& objPosition, ProbeDataSet* probeDataSet)
{
   PROFILE_SCOPE(ProbeManager_getBestProbes);

   // Skip over gathering lights if we don't have to!
   //if (probeShaderConsts->isValid())
   {
      //Array rendering
      U32 probeCount = mRegisteredProbes.size();

      Vector<S8> bestPickProbes;

      probeDataSet->effectiveProbeCount = 0;
      for (U32 i = 0; i < probeCount; i++)
      {
         const ProbeRenderInst& curEntry = mRegisteredProbes[i];
         if (!curEntry.mIsEnabled)
            continue;

         if (!curEntry.mIsSkylight)
         {
            F32 dist = Point3F(objPosition - curEntry.getPosition()).len();

            if (dist > curEntry.mRadius || dist > curEntry.mExtents.len())
               continue;

            S32 bestPickIndex = -1;
            for (U32 p = 0; p < bestPickProbes.size(); p++)
            {
               if (p > probeDataSet->MAX_PROBE_COUNT)
                  break;

               if (bestPickProbes[p] == -1 || (Point3F(objPosition - mRegisteredProbes[bestPickProbes[p]].mPosition).len() > dist))
                  bestPickIndex = p;
            }

            //Can't have over our max count. Otherwise, if we haven't found a good slot for our best pick, insert it
            //if we have a best pick slot, update it
            if (bestPickIndex == -1 || bestPickProbes.size() >= probeDataSet->MAX_PROBE_COUNT)
               bestPickProbes.push_back(i);
            else
               bestPickProbes[bestPickIndex] = i;
         }
         else
         {
            probeDataSet->skyLightIdx = curEntry.mCubemapIndex;
         }
      }

      //Grab our best probe picks
      for (U32 i = 0; i < bestPickProbes.size(); i++)
      {
         if (bestPickProbes[i] == -1)
            continue;

         const ProbeRenderInst& curEntry = mRegisteredProbes[bestPickProbes[i]];

         probeDataSet->probePositionArray[probeDataSet->effectiveProbeCount] = curEntry.getPosition();
         probeDataSet->probeRefPositionArray[probeDataSet->effectiveProbeCount] = curEntry.mProbeRefOffset;
         probeDataSet->probeWorldToObjArray[probeDataSet->effectiveProbeCount] = curEntry.getTransform();

         Point3F refPos = curEntry.getPosition() + curEntry.mProbeRefOffset;
         Point3F refBoxMin = refPos - curEntry.mProbeRefScale * curEntry.getTransform().getScale();
         Point3F refBoxMax = refPos + curEntry.mProbeRefScale * curEntry.getTransform().getScale();

         probeDataSet->refBoxMinArray[probeDataSet->effectiveProbeCount] = Point4F(refBoxMin.x, refBoxMin.y, refBoxMin.z, 0);
         probeDataSet->refBoxMaxArray[probeDataSet->effectiveProbeCount] = Point4F(refBoxMax.x, refBoxMax.y, refBoxMax.z, 0);
         probeDataSet->probeConfigArray[probeDataSet->effectiveProbeCount] = Point4F(curEntry.mProbeShapeType,
            curEntry.mRadius,
            curEntry.mAtten,
            curEntry.mCubemapIndex);

         probeDataSet->effectiveProbeCount++;
      }
   }
}

void RenderProbeMgr::getProbeTextureData(ProbeTextureArrayData* probeTextureSet)
{
   probeTextureSet->BRDFTexture = mBRDFTexture;
   probeTextureSet->prefilterArray = mPrefilterArray;
   probeTextureSet->irradianceArray = mIrradianceArray;
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

   // if (mRegisteredProbes.empty())
   //    return;

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

//-----------------------------------------------------------------------------
// render objects
//-----------------------------------------------------------------------------
void RenderProbeMgr::render( SceneRenderState *state )
{
   if (getProbeArrayEffect() == nullptr)
      return;

   if (mProbesDirty)
	   _setupStaticParameters();

   // Early out if nothing to draw.
   if (!RenderProbeMgr::smRenderReflectionProbes || (!state->isDiffusePass() && !state->isReflectPass()) || (mEffectiveProbeCount == 0 && mSkylightCubemapIdx == -1))
   {
      getProbeArrayEffect()->setSkip(true);
      return;
   }

   GFXTransformSaver saver;

   GFXDEBUGEVENT_SCOPE(RenderProbeMgr_render, ColorI::WHITE);

   // Initialize and set the per-frame parameters after getting
   // the vector light material as we use lazy creation.
   //_setupPerFrameParameters(state);

   //Visualization
   String useDebugAtten = Con::getVariable("$Probes::showAttenuation", "0");
   mProbeArrayEffect->setShaderMacro("DEBUGVIZ_ATTENUATION", useDebugAtten);

   String useDebugSpecCubemap = Con::getVariable("$Probes::showSpecularCubemaps", "0");
   mProbeArrayEffect->setShaderMacro("DEBUGVIZ_SPECCUBEMAP", useDebugSpecCubemap);

   String useDebugDiffuseCubemap = Con::getVariable("$Probes::showDiffuseCubemaps", "0");
   mProbeArrayEffect->setShaderMacro("DEBUGVIZ_DIFFCUBEMAP", useDebugDiffuseCubemap);

   String useDebugContrib = Con::getVariable("$Probes::showProbeContrib", "0");
   mProbeArrayEffect->setShaderMacro("DEBUGVIZ_CONTRIB", useDebugContrib);

   if(mSkylightCubemapIdx != -1 && mEffectiveProbeCount == 0)
      mProbeArrayEffect->setShaderMacro("SKYLIGHT_ONLY", "1");
   else
      mProbeArrayEffect->setShaderMacro("SKYLIGHT_ONLY", "0");

   //ssao mask
   if (AdvancedLightBinManager::smUseSSAOMask)
   {
      //find ssaoMask
      NamedTexTargetRef ssaoTarget = NamedTexTarget::find("ssaoMask");
      GFXTextureObject* pTexObj = ssaoTarget->getTexture();
      if (pTexObj)
      {
         mProbeArrayEffect->setShaderMacro("USE_SSAO_MASK");
         mProbeArrayEffect->setTexture(6, pTexObj);
         
      }
   }
   else
   {
      mProbeArrayEffect->setTexture(6, GFXTexHandle(NULL)); 
   }
   
   mProbeArrayEffect->setTexture(3, mBRDFTexture);
   mProbeArrayEffect->setCubemapArrayTexture(4, mPrefilterArray);
   mProbeArrayEffect->setCubemapArrayTexture(5, mIrradianceArray);

   mProbeArrayEffect->setShaderConst("$numProbes", (S32)mEffectiveProbeCount);
   mProbeArrayEffect->setShaderConst("$skylightCubemapIdx", (S32)mSkylightCubemapIdx);

   mProbeArrayEffect->setShaderConst("$cubeMips", (float)mMipCount);

   //also set up some colors
   Vector<Point4F> contribColors;

   contribColors.setSize(MAXPROBECOUNT);

   if (mEffectiveProbeCount != 0)
   {
      if (useDebugContrib == String("1"))
      {
         MRandomLCG RandomGen;
         RandomGen.setSeed(mEffectiveProbeCount);

         for (U32 i = 0; i < mEffectiveProbeCount; i++)
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

   mProbeArrayEffect->setShaderConst("$inProbePosArray", probePositionsData);
   mProbeArrayEffect->setShaderConst("$inRefPosArray", probeRefPositionsData);
   mProbeArrayEffect->setShaderConst("$worldToObjArray", probeWorldToObjData);
   mProbeArrayEffect->setShaderConst("$refBoxMinArray", refBoxMinData);
   mProbeArrayEffect->setShaderConst("$refBoxMaxArray", refBoxMaxData);
   mProbeArrayEffect->setShaderConst("$probeConfigData", probeConfigData);

   // Make sure the effect is gonna render.
   getProbeArrayEffect()->setSkip(false);

   //PROFILE_END();
}

void RenderProbeMgr::bakeProbe(ReflectionProbe *probe)
{
   GFXDEBUGEVENT_SCOPE(RenderProbeMgr_Bake, ColorI::WHITE);

   Con::warnf("RenderProbeMgr::bakeProbe() - Beginning bake!");
   U32 startMSTime = Platform::getRealMilliseconds();

   String path = Con::getVariable("$pref::ReflectionProbes::CurrentLevelPath", "levels/");
   U32 resolution = Con::getIntVariable("$pref::ReflectionProbes::BakeResolution", 64);
   U32 prefilterMipLevels = mLog2(F32(resolution));
   bool renderWithProbes = Con::getIntVariable("$pref::ReflectionProbes::RenderWithProbes", false);

   ReflectionProbe *clientProbe = static_cast<ReflectionProbe*>(probe->getClientObject());

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
   reflDesc.detailAdjust = 1;
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
      (F32)resolution / (F32)resolution,
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

   if (clientProbe->mUseHDRCaptures)
      reflectFormat = GFXFormatR16G16B16A16F;
   else
      reflectFormat = GFXFormatR8G8B8A8;
   const GFXFormat oldRefFmt = REFLECTMGR->getReflectFormat();
   REFLECTMGR->setReflectFormat(reflectFormat);
   cubeRefl.updateReflection(reflParams);

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

   cubeRefl.unregisterReflector();

   U32 endMSTime = Platform::getRealMilliseconds();
   F32 diffTime = F32(endMSTime - startMSTime);

   probe->setMaskBits(-1);

   Con::warnf("RenderProbeMgr::bake() - Finished bake! Took %g milliseconds", diffTime);
   REFLECTMGR->setReflectFormat(oldRefFmt);
}

void RenderProbeMgr::bakeProbes()
{
   //TODO: make this just find every probe in the current missionGroup and run the bake on it automagically
}

DefineEngineMethod(RenderProbeMgr, bakeProbe, void, (ReflectionProbe* probe), (nullAsType< ReflectionProbe*>()),
   "@brief returns true if control object is inside the fog\n\n.")
{
   if(probe != nullptr)
      object->bakeProbe(probe);
}
