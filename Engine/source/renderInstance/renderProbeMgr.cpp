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

#include "gfx/gfxDebugEvent.h"
#include "shaderGen/shaderGenVars.h"
#include "materials/shaderData.h"

#include "gfx/gfxTextureManager.h"

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
ProbeRenderInst::ProbeRenderInst() : SystemInterface(),
   mTransform(true),
   mDirty(false),
   mPriority(1.0f),
   mScore(0.0f),
   mCubemap(NULL),
   mIrradianceCubemap(NULL),
   mRadius(1.0f),
   mProbeRefOffset(0, 0, 0),
   mProbeRefScale(1,1,1)
{
}

ProbeRenderInst::~ProbeRenderInst()
{
   if (mCubemap && mCubemap.isValid())
   {
      mCubemap.free();
   }
   if (mIrradianceCubemap && mIrradianceCubemap.isValid())
   {
      mIrradianceCubemap.free();
   }
}

void ProbeRenderInst::set(const ProbeRenderInst *probeInfo)
{
   mTransform = probeInfo->mTransform;
   mCubemap = probeInfo->mCubemap;
   mIrradianceCubemap = probeInfo->mIrradianceCubemap;
   mRadius = probeInfo->mRadius;
   mProbeShapeType = probeInfo->mProbeShapeType;
   mBounds = probeInfo->mBounds;
   mIsSkylight = probeInfo->mIsSkylight;
   mScore = probeInfo->mScore;
}

//
//
ProbeShaderConstants::ProbeShaderConstants()
   : mInit(false),
   mShader(NULL),
   mProbeParamsSC(NULL),
   mProbePositionSC(NULL),
   mProbeRadiusSC(NULL),
   mProbeBoxMinSC(NULL),
   mProbeBoxMaxSC(NULL),
   mProbeIsSphereSC(NULL),
   mProbeLocalPosSC(NULL),
   mProbeCubemapSC(NULL),
   mProbeCountSC(NULL)
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

   mProbeParamsSC = shader->getShaderConstHandle("$probeParams");

   //Reflection Probes
   mProbePositionSC = shader->getShaderConstHandle(ShaderGenVars::probePosition);
   mProbeRadiusSC = shader->getShaderConstHandle(ShaderGenVars::probeRadius);
   mProbeBoxMinSC = shader->getShaderConstHandle(ShaderGenVars::probeBoxMin);
   mProbeBoxMaxSC = shader->getShaderConstHandle(ShaderGenVars::probeBoxMax);
   mProbeIsSphereSC = shader->getShaderConstHandle(ShaderGenVars::probeIsSphere);
   mProbeLocalPosSC = shader->getShaderConstHandle(ShaderGenVars::probeLocalPos);
   mProbeCubemapSC = shader->getShaderConstHandle(ShaderGenVars::probeCubemap);
   mProbeCountSC = shader->getShaderConstHandle(ShaderGenVars::probeCount);

   mInit = true;
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
   mLastConstants(nullptr)
{
   mEffectiveProbeCount = 0;
   mMipCount = 0;

   mProbeArrayEffect = nullptr;

   smProbeManager = this;
}

RenderProbeMgr::RenderProbeMgr(RenderInstType riType, F32 renderOrder, F32 processAddOrder)
 : RenderBinManager(riType, renderOrder, processAddOrder)
{  
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

void RenderProbeMgr::registerProbe(U32 probeIdx)
{
   //Mostly for consolidation, but also lets us sanity check or prep any other data we need for rendering this in one place at time of flagging for render
   if (probeIdx >= ProbeRenderInst::all.size())
      return;

   mRegisteredProbes.push_back_unique(probeIdx);

   //rebuild our probe data
   _setupStaticParameters();
}

void RenderProbeMgr::unregisterProbe(U32 probeIdx)
{
   //Mostly for consolidation, but also lets us sanity check or prep any other data we need for rendering this in one place at time of flagging for render
   if (probeIdx >= ProbeRenderInst::all.size())
      return;

   mRegisteredProbes.remove(probeIdx);

   //rebuild our probe data
   _setupStaticParameters();
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
	_setupStaticParameters();
}

void RenderProbeMgr::_setupStaticParameters()
{
   //Array rendering
   U32 probeCount = ProbeRenderInst::all.size();

   mEffectiveProbeCount = 0;
   mMipCount = 0;

   if (probePositionsData.size() != MAXPROBECOUNT)
   {
      probePositionsData.setSize(MAXPROBECOUNT);
      probeRefPositionsData.setSize(MAXPROBECOUNT);
      probeWorldToObjData.setSize(MAXPROBECOUNT);
      probeBBMinData.setSize(MAXPROBECOUNT);
      probeBBMaxData.setSize(MAXPROBECOUNT);
      probeConfigData.setSize(MAXPROBECOUNT);
   }

   probePositionsData.fill(Point4F::Zero);
   probeRefPositionsData.fill(Point4F::Zero);
   probeWorldToObjData.fill(MatrixF::Identity);
   probeBBMinData.fill(Point4F::Zero);
   probeBBMaxData.fill(Point4F::Zero);
   probeConfigData.fill(Point4F::Zero);

   cubeMaps.clear();
   irradMaps.clear();

   //This should probably ultimately be a per-probe value, but for now, global for testing/adjustability
   F32 attenuation = Con::getFloatVariable("$pref::ReflectionProbes::AttenuationStrength", 3.5);

   for (U32 i = 0; i < probeCount; i++)
   {
      if (mEffectiveProbeCount >= MAXPROBECOUNT)
         break;

      const ProbeRenderInst& curEntry = *ProbeRenderInst::all[i];
      if (!curEntry.mIsEnabled)
         continue;

      if (curEntry.mCubemap.isNull() || curEntry.mIrradianceCubemap.isNull())
         continue;

      if (!curEntry.mCubemap->isInitialised())
         continue;

      if (!curEntry.mIrradianceCubemap->isInitialised())
         continue;

      //if (curEntry.mIsSkylight)
      //   continue;

	   mMipCount = curEntry.mCubemap.getPointer()->getMipMapLevels();

      //Setup
      Point3F probePos = curEntry.getPosition();
      Point3F refPos = curEntry.getPosition() +curEntry.mProbeRefOffset;
      probePositionsData[mEffectiveProbeCount] = Point4F(probePos.x, probePos.y, probePos.z,0);
      probeRefPositionsData[mEffectiveProbeCount] = Point4F(refPos.x, refPos.y, refPos.z, 0);

      probeWorldToObjData[mEffectiveProbeCount] = curEntry.getTransform();
      Point3F bbMin = refPos - curEntry.mProbeRefScale/2;
      Point3F bbMax = refPos + curEntry.mProbeRefScale/2;
      probeBBMinData[mEffectiveProbeCount] = Point4F(bbMin.x, bbMin.y, bbMin.z, 0);
      probeBBMaxData[mEffectiveProbeCount] = Point4F(bbMax.x, bbMax.y, bbMax.z, 0);

      probeConfigData[mEffectiveProbeCount] = Point4F(curEntry.mProbeShapeType, 
         curEntry.mRadius,
         attenuation,
         1);

      cubeMaps.push_back(curEntry.mCubemap);
      irradMaps.push_back(curEntry.mIrradianceCubemap);

      mEffectiveProbeCount++;
   }

   if (mEffectiveProbeCount != 0)
   {
      mCubemapArray = GFXCubemapArrayHandle(GFX->createCubemapArray());
      mIrradArray = GFXCubemapArrayHandle(GFX->createCubemapArray());

      mCubemapArray->initStatic(cubeMaps.address(), cubeMaps.size());
      mIrradArray->initStatic(irradMaps.address(), irradMaps.size());
   }
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

   // Make sure that our current lighting constants are initialized
   if (mLastConstants && !mLastConstants->mInit)
      mLastConstants->init(shader);

   return mLastConstants;
}

void RenderProbeMgr::_update4ProbeConsts(const SceneData &sgData,
   MatrixSet &matSet,
   GFXShaderConstHandle *probePositionSC,
   GFXShaderConstHandle *probeRadiusSC,
   GFXShaderConstHandle *probeBoxMinSC,
   GFXShaderConstHandle *probeBoxMaxSC,
   GFXShaderConstHandle *probeCubemapSC,
   GFXShaderConstHandle *probeIsSphereSC,
   GFXShaderConstHandle *probeLocalPosSC,
   GFXShaderConstBuffer *shaderConsts)
{
   PROFILE_SCOPE(ProbeManager_Update4ProbeConsts);

   // Skip over gathering lights if we don't have to!
   if (probePositionSC->isValid() ||
      probeRadiusSC->isValid() ||
      probeBoxMinSC->isValid() ||
      probeBoxMaxSC->isValid() ||
      probeCubemapSC->isValid()/* && (!ProbeRenderInst::all.empty())*/)
   {
      PROFILE_SCOPE(ProbeManager_Update4ProbeConsts_setProbes);

      static AlignedArray<Point3F> probePositions(4, sizeof(Point3F));
      static AlignedArray<F32> probeRadius(4, sizeof(F32));
      static AlignedArray<Point3F> probeBoxMins(4, sizeof(Point3F));
      static AlignedArray<Point3F> probeBoxMaxs(4, sizeof(Point3F));
      static AlignedArray<Point3F> probeLocalPositions(4, sizeof(Point3F));
      static AlignedArray<F32> probeIsSphere(4, sizeof(F32));
      //static AlignedArray<CubemapData> probeCubemap(4, sizeof(CubemapData));
      //F32 range;

      // Need to clear the buffers so that we don't leak
      // lights from previous passes or have NaNs.
      dMemset(probePositions.getBuffer(), 0, probePositions.getBufferSize());
      dMemset(probeRadius.getBuffer(), 0, probeRadius.getBufferSize());
      dMemset(probeBoxMins.getBuffer(), 0, probeBoxMins.getBufferSize());
      dMemset(probeBoxMaxs.getBuffer(), 0, probeBoxMaxs.getBufferSize());
      dMemset(probeLocalPositions.getBuffer(), 0, probeLocalPositions.getBufferSize());
      dMemset(probeIsSphere.getBuffer(), 0, probeRadius.getBufferSize());
      //dMemset(probeCubemap.getBuffer(), 0, probeCubemap.getBufferSize());

      matSet.restoreSceneViewProjection();

      //const MatrixF &worldToCameraXfm = matSet.getWorldToCamera();

      // Gather the data for the first 4 probes.
      /*const ProbeRenderInst *probe;
      for (U32 i = 0; i < 4; i++)
      {
         if (i >= ProbeRenderInst::all.size())
            break;

         probe = ProbeRenderInst::all[i];

         if (!probe)
            continue;

         if (!probe->mIsEnabled)
            continue;

         // The light positions and spot directions are 
         // in SoA order to make optimal use of the GPU.
         const Point3F &probePos = probe->getPosition();
         probePositions[i].x = probePos.x;
         probePositions[i].y = probePos.y;
         probePositions[i].z = probePos.z;

         probeRadius[i] = probe->mRadius;

         const Point3F &minExt = probe->mBounds.minExtents;
         probeBoxMins[i].x = minExt.x;
         probeBoxMins[i].y = minExt.y;
         probeBoxMins[i].z = minExt.z;

         const Point3F &maxExt = probe->mBounds.maxExtents;
         probeBoxMaxs[i].x = maxExt.x;
         probeBoxMaxs[i].y = maxExt.y;
         probeBoxMaxs[i].z = maxExt.z;

         probeIsSphere[i] = probe->mProbeShapeType == ProbeRenderInst::Sphere ? 1.0 : 0.0;

         Point3F localProbePos;
         worldToCameraXfm.mulP(probe->getPosition(), &localProbePos);

         probeLocalPositions[i].x = localProbePos.x;
         probeLocalPositions[i].y = localProbePos.y;
         probeLocalPositions[i].z = localProbePos.z;

         if (probe->mCubemap && !probe->mCubemap.isNull())
         {
            S32 samplerReg = probeCubemapSC->getSamplerRegister();

            if (samplerReg != -1)
               GFX->setCubeTexture(samplerReg + i, probe->mCubemap.getPointer());
         }
      }*/

      for (U32 i = 0; i < 4; i++)
      {
         probePositions[i].x = 0;
         probePositions[i].y = 0;
         probePositions[i].z = 0;

         probeRadius[i] = 0;

         probeBoxMins[i].x = 0;
         probeBoxMins[i].y = 0;
         probeBoxMins[i].z = 0;

         probeBoxMaxs[i].x = 0;
         probeBoxMaxs[i].y = 0;
         probeBoxMaxs[i].z = 0;

         probeIsSphere[i] = 0;

         probeLocalPositions[i].x = 0;
         probeLocalPositions[i].y = 0;
         probeLocalPositions[i].z = 0;

         S32 samplerReg = probeCubemapSC->getSamplerRegister();

         GFX->setCubeTexture(samplerReg + i, nullptr);
      }

      shaderConsts->setSafe(probePositionSC, probePositions);
      shaderConsts->setSafe(probeRadiusSC, probeRadius);
      shaderConsts->setSafe(probeBoxMinSC, probeBoxMins);
      shaderConsts->setSafe(probeBoxMaxSC, probeBoxMaxs);
      shaderConsts->setSafe(probeLocalPosSC, probeLocalPositions);
      shaderConsts->setSafe(probeIsSphereSC, probeIsSphere);
   }
   else
   {
      if (probeCubemapSC->isValid())
      {
         for (U32 i = 0; i < 4; ++i)
            GFX->setCubeTexture(probeCubemapSC->getSamplerRegister() + i, NULL);
      }
   }
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
   _update4ProbeConsts(sgData,
      matSet,
      psc->mProbePositionSC,
      psc->mProbeRadiusSC,
      psc->mProbeBoxMinSC,
      psc->mProbeBoxMaxSC,
      psc->mProbeCubemapSC,
      psc->mProbeIsSphereSC,
      psc->mProbeLocalPosSC,
      shaderConsts);
}

//-----------------------------------------------------------------------------
// render objects
//-----------------------------------------------------------------------------
void RenderProbeMgr::render( SceneRenderState *state )
{
   //PROFILE_SCOPE(RenderProbeMgr_render);
   if (getProbeArrayEffect() == nullptr)
      return;

   //updateProbes();

   // Early out if nothing to draw.
   if (!ProbeRenderInst::all.size() || !RenderProbeMgr::smRenderReflectionProbes || mEffectiveProbeCount == 0
	   || !state->isDiffusePass() || cubeMaps.empty() || irradMaps.empty())
   {
	   getProbeArrayEffect()->setSkip(true);
	   return;
   }

   GFXTransformSaver saver;

   GFXDEBUGEVENT_SCOPE(RenderProbeMgr_render, ColorI::WHITE);

   // Initialize and set the per-frame parameters after getting
   // the vector light material as we use lazy creation.
   //_setupPerFrameParameters(state);
   
   //Array rendering
   //U32 probeCount = ProbeRenderInst::all.size();

   if (mEffectiveProbeCount != 0)
   {
      mProbeArrayEffect->setCubemapArrayTexture(4, mCubemapArray);
      mProbeArrayEffect->setCubemapArrayTexture(5, mIrradArray);

      String useDebugAtten = Con::getVariable("$Probes::showAttenuation", "0");
      mProbeArrayEffect->setShaderMacro("DEBUGVIZ_ATTENUATION", useDebugAtten);

      String useDebugSpecCubemap = Con::getVariable("$Probes::showSpecularCubemaps", "0");
      mProbeArrayEffect->setShaderMacro("DEBUGVIZ_SPECCUBEMAP", useDebugSpecCubemap);

      String useDebugDiffuseCubemap = Con::getVariable("$Probes::showDiffuseCubemaps", "0");
      mProbeArrayEffect->setShaderMacro("DEBUGVIZ_DIFFCUBEMAP", useDebugDiffuseCubemap);

      String useDebugContrib = Con::getVariable("$Probes::showProbeContrib", "0");
      mProbeArrayEffect->setShaderMacro("DEBUGVIZ_CONTRIB", useDebugContrib);

      if (useDebugContrib == String("1"))
      {
         MRandomLCG RandomGen;
         RandomGen.setSeed(mEffectiveProbeCount);

         //also set up some colors
         Vector<Point4F> contribColors;

         contribColors.setSize(MAXPROBECOUNT);

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
               contribColors[i] = Point4F(RandomGen.randF(0, 1), RandomGen.randF(0, 1), RandomGen.randF(0, 1),1);
         }

         mProbeArrayEffect->setShaderConst("$probeContribColors", contribColors);
      }

      mProbeArrayEffect->setShaderConst("$cubeMips", (float)mMipCount);
      
      mProbeArrayEffect->setShaderConst("$numProbes", (float)mEffectiveProbeCount);
      mProbeArrayEffect->setShaderConst("$inProbePosArray", probePositionsData);
      mProbeArrayEffect->setShaderConst("$inRefPosArray", probeRefPositionsData);
      mProbeArrayEffect->setShaderConst("$worldToObjArray", probeWorldToObjData);
      mProbeArrayEffect->setShaderConst("$bbMinArray", probeBBMinData);
      mProbeArrayEffect->setShaderConst("$bbMaxArray", probeBBMaxData);
      mProbeArrayEffect->setShaderConst("$probeConfigData", probeConfigData);
   }

   // Make sure the effect is gonna render.
   getProbeArrayEffect()->setSkip(false);

   //PROFILE_END();
}

void RenderProbeMgr::bakeProbe(ReflectionProbe *probe)
{
   GFXDEBUGEVENT_SCOPE(RenderProbeMgr_Bake, ColorI::WHITE);

   bool serverObj = probe->isServerObject();

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
   reflDesc.objectTypeMask = -1;

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

   cubeRefl.updateReflection(reflParams);

   //Now, save out the maps
   //create irridiance cubemap
   if (cubeRefl.getCubemap())
   {
      //Just to ensure we're prepped for the generation
      clientProbe->createClientResources();

      //Prep it with whatever resolution we've dictated for our bake
      if (clientProbe->mUseHDRCaptures)
      {
         clientProbe->mIrridianceMap->mCubemap->initDynamic(resolution, GFXFormatR16G16B16A16F);
         clientProbe->mPrefilterMap->mCubemap->initDynamic(resolution, GFXFormatR16G16B16A16F);
      }
      else
      {
         clientProbe->mIrridianceMap->mCubemap->initDynamic(resolution, GFXFormatR8G8B8A8);
         clientProbe->mPrefilterMap->mCubemap->initDynamic(resolution, GFXFormatR8G8B8A8);
      }

      GFXTextureTargetRef renderTarget = GFX->allocRenderToTextureTarget(false);

      IBLUtilities::GenerateIrradianceMap(renderTarget, cubeRefl.getCubemap(), clientProbe->mIrridianceMap->mCubemap);
      IBLUtilities::GeneratePrefilterMap(renderTarget, cubeRefl.getCubemap(), prefilterMipLevels, clientProbe->mPrefilterMap->mCubemap);

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

   Con::warnf("RenderProbeMgr::bake() - Finished bake! Took %g milliseconds", diffTime);
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