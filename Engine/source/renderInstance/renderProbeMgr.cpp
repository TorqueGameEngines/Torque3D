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
   mAmbient(0.0f, 0.0f, 0.0f, 1.0f),
   mPriority(1.0f),
   mScore(0.0f),
   mDebugRender(false),
   mCubemap(NULL),
   mIrradianceCubemap(NULL),
   mBRDFTexture(NULL),
   mRadius(1.0f),
   mIntensity(1.0f),
   mProbePosOffset(0, 0, 0),
   numPrims(0)
{
   for (U32 i = 0; i < 5; ++i)
   {
      mSHConstants[i] = 0;
   }
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
   if (mBRDFTexture && mBRDFTexture->isValid())
   {
      mBRDFTexture->free();
   }
}

void ProbeRenderInst::set(const ProbeRenderInst *probeInfo)
{
   mTransform = probeInfo->mTransform;
   mAmbient = probeInfo->mAmbient;
   mCubemap = probeInfo->mCubemap;
   mIrradianceCubemap = probeInfo->mIrradianceCubemap;
   mBRDFTexture = probeInfo->mBRDFTexture;
   mRadius = probeInfo->mRadius;
   mIntensity = probeInfo->mIntensity;
   mProbeShapeType = probeInfo->mProbeShapeType;
   numPrims = probeInfo->numPrims;
   numVerts = probeInfo->numVerts;
   numIndicesForPoly = probeInfo->numIndicesForPoly;
   mBounds = probeInfo->mBounds;
   mIsSkylight = probeInfo->mIsSkylight;
   mScore = probeInfo->mScore;

   for (U32 i = 0; i < 9; i++)
   {
      mSHTerms[i] = probeInfo->mSHTerms[i];
   }

   for (U32 i = 0; i < 5; i++)
   {
      mSHConstants[i] = probeInfo->mSHConstants[i];
   }
}

void ProbeRenderInst::getWorldToLightProj(MatrixF *outMatrix) const
{
   *outMatrix = getTransform();
   outMatrix->inverse();
}

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
bool ReflectProbeMatInstance::init(const FeatureSet &features, const GFXVertexFormat *vertexFormat)
{
   mShaderMat = nullptr;

   bool success = Parent::init(features, vertexFormat);

   // If the initialization failed don't continue.
   if (!success || !mProcessedMaterial || mProcessedMaterial->getNumPasses() == 0)
      return false;

   mShaderMat = static_cast<ProcessedShaderMaterial*>(getShaderMaterial());
   mShaderMat->init(features, vertexFormat, mFeaturesDelegate);

   //mShaderMat->setMaterialParameters(mDefaultParameters, 0);

   return true;
}

bool ReflectProbeMatInstance::setupPass(SceneRenderState *state, const SceneData &sgData)
{
   if (!Parent::setupPass(state, sgData))
      return false;

   AssertFatal(mProcessedMaterial->getNumPasses() > 0, "No passes created! Ohnoes");
   const RenderPassData *rpd = mProcessedMaterial->getPass(0);
   AssertFatal(rpd, "No render pass data!");
   AssertFatal(rpd->mRenderStates[0], "No render state 0!");

   if (!mProjectionState)
   {
      GFXStateBlockDesc desc;
      desc.setZReadWrite(false);
      desc.zWriteEnable = false;
      desc.setCullMode(GFXCullNone);
      desc.setBlend(true, GFXBlendSrcAlpha, GFXBlendInvDestAlpha, GFXBlendOpAdd);
      mProjectionState = GFX->createStateBlock(desc);
   }
   // Now override stateblock with our own
   GFX->setStateBlock(mProjectionState);

   return true;
}

//
//
RenderProbeMgr::RenderProbeMgr()
: RenderBinManager(RenderPassManager::RIT_Probes, 1.0f, 1.0f),
   mReflectProbeMaterial(nullptr),
   mSceneManager(nullptr),
   mLastShader(nullptr),
   mLastConstants(nullptr)
{
   String brdfPath = Con::getVariable("$Core::BRDFTexture", "core/art/pbr/brdfTexture.dds");
   mBrdfTexture = TEXMGR->createTexture(brdfPath, &GFXTexturePersistentProfile);

   probePositions.setSize(MAXPROBECOUNT);
   probePositions.fill(Point3F::Zero);

   probeWorldToObj.setSize(MAXPROBECOUNT);
   probeWorldToObj.fill(MatrixF::Identity);

   probeBBMin.setSize(MAXPROBECOUNT);
   probeBBMin.fill(Point3F::Zero);

   probeBBMax.setSize(MAXPROBECOUNT);
   probeBBMax.fill(Point3F::Zero);

   probeUseSphereMode.setSize(MAXPROBECOUNT);
   probeUseSphereMode.fill(0.0f);

   probeRadius.setSize(MAXPROBECOUNT);
   probeRadius.fill(0.0f);

   probeAttenuation.setSize(MAXPROBECOUNT);
   probeAttenuation.fill(0.0f);

   cubeMaps.setSize(MAXPROBECOUNT);
   cubeMaps.fill(NULL);

   irradMaps.setSize(MAXPROBECOUNT);
   irradMaps.fill(NULL);
}

RenderProbeMgr::RenderProbeMgr(RenderInstType riType, F32 renderOrder, F32 processAddOrder)
 : RenderBinManager(riType, renderOrder, processAddOrder)
{  
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
}

//
//
PostEffect* RenderProbeMgr::getProbeArrayEffect()
{
   if (!mProbeArrayEffect)
      mProbeArrayEffect = dynamic_cast<PostEffect*>(Sim::findObject("reflectionProbeArrayPostFX"));

   return mProbeArrayEffect;
}

//remove
//Con::setIntVariable("lightMetrics::activeReflectionProbes", mReflectProbeBin.size());
//Con::setIntVariable("lightMetrics::culledReflectProbes", 0/*mNumLightsCulled*/);
//

void RenderProbeMgr::_setupStaticParameters()
{

}

void RenderProbeMgr::_setupPerFrameParameters(const SceneRenderState *state)
{
   PROFILE_SCOPE(RenderProbeMgr_SetupPerFrameParameters);
   const Frustum &frustum = state->getCameraFrustum();

   MatrixF invCam(frustum.getTransform());
   invCam.inverse();

   const Point3F *wsFrustumPoints = frustum.getPoints();
   const Point3F& cameraPos = frustum.getPosition();

   // Perform a camera offset.  We need to manually perform this offset on the sun (or vector) light's
   // polygon, which is at the far plane.
   Point3F cameraOffsetPos = cameraPos;

   // Now build the quad for drawing full-screen vector light
   // passes.... this is a volatile VB and updates every frame.
   FarFrustumQuadVert verts[4];
   {
      verts[0].point.set(wsFrustumPoints[Frustum::FarTopLeft] - cameraPos);
      invCam.mulP(wsFrustumPoints[Frustum::FarTopLeft], &verts[0].normal);
      verts[0].texCoord.set(-1.0, 1.0);
      verts[0].tangent.set(wsFrustumPoints[Frustum::FarTopLeft] - cameraOffsetPos);

      verts[1].point.set(wsFrustumPoints[Frustum::FarTopRight] - cameraPos);
      invCam.mulP(wsFrustumPoints[Frustum::FarTopRight], &verts[1].normal);
      verts[1].texCoord.set(1.0, 1.0);
      verts[1].tangent.set(wsFrustumPoints[Frustum::FarTopRight] - cameraOffsetPos);

      verts[2].point.set(wsFrustumPoints[Frustum::FarBottomLeft] - cameraPos);
      invCam.mulP(wsFrustumPoints[Frustum::FarBottomLeft], &verts[2].normal);
      verts[2].texCoord.set(-1.0, -1.0);
      verts[2].tangent.set(wsFrustumPoints[Frustum::FarBottomLeft] - cameraOffsetPos);

      verts[3].point.set(wsFrustumPoints[Frustum::FarBottomRight] - cameraPos);
      invCam.mulP(wsFrustumPoints[Frustum::FarBottomRight], &verts[3].normal);
      verts[3].texCoord.set(1.0, -1.0);
      verts[3].tangent.set(wsFrustumPoints[Frustum::FarBottomRight] - cameraOffsetPos);
   }

   mFarFrustumQuadVerts.set(GFX, 4);
   dMemcpy(mFarFrustumQuadVerts.lock(), verts, sizeof(verts));
   mFarFrustumQuadVerts.unlock();

   PlaneF farPlane(wsFrustumPoints[Frustum::FarBottomLeft], wsFrustumPoints[Frustum::FarTopLeft], wsFrustumPoints[Frustum::FarTopRight]);
   PlaneF vsFarPlane(verts[0].normal, verts[1].normal, verts[2].normal);

   ReflectProbeMaterialInfo* reflProbeMat = getReflectProbeMaterial();

   if (reflProbeMat != nullptr && reflProbeMat->matInstance != nullptr)
   {
      reflProbeMat->setViewParameters(frustum.getNearDist(),
         frustum.getFarDist(),
         frustum.getPosition(),
         farPlane,
         vsFarPlane);
   }
}

RenderProbeMgr::ReflectProbeMaterialInfo* RenderProbeMgr::getReflectProbeMaterial()
{
   PROFILE_SCOPE(AdvancedLightBinManager_getReflectProbeMaterial);

   //ReflectProbeMaterialInfo *info = NULL;

   if (!mReflectProbeMaterial)

      // Now create the material info object.
      mReflectProbeMaterial = new ReflectProbeMaterialInfo("ReflectionProbeMaterial",
         getGFXVertexFormat<GFXVertexPC>());

   return mReflectProbeMaterial;
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

   mLastConstants = new ProbeShaderConstants();

   // Make sure that our current lighting constants are initialized
   if (!mLastConstants->mInit)
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
      probeCubemapSC->isValid() && (!ProbeRenderInst::all.empty()))
   {
      PROFILE_SCOPE(ProbeManager_Update4ProbeConsts_setProbes);

      static AlignedArray<Point3F> probePositions(4, sizeof(Point3F));
      static AlignedArray<F32> probeRadius(4, sizeof(F32));
      static AlignedArray<Point3F> probeBoxMins(4, sizeof(Point3F));
      static AlignedArray<Point3F> probeBoxMaxs(4, sizeof(Point3F));
      static AlignedArray<Point3F> probeLocalPositions(4, sizeof(Point3F));
      static AlignedArray<F32> probeIsSphere(4, sizeof(F32));
      //static AlignedArray<CubemapData> probeCubemap(4, sizeof(CubemapData));
      F32 range;

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

      const MatrixF &worldToCameraXfm = matSet.getWorldToCamera();

      // Gather the data for the first 4 probes.
      const ProbeRenderInst *probe;
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
      }

      shaderConsts->setSafe(probePositionSC, probePositions);
      shaderConsts->setSafe(probeRadiusSC, probeRadius);
      shaderConsts->setSafe(probeBoxMinSC, probeBoxMins);
      shaderConsts->setSafe(probeBoxMaxSC, probeBoxMaxs);
      shaderConsts->setSafe(probeLocalPosSC, probeLocalPositions);
      shaderConsts->setSafe(probeIsSphereSC, probeIsSphere);

      //

      //shaderConsts->setSafe(lightSpotAngleSC, lightSpotAngle);
      //shaderConsts->setSafe(lightSpotFalloffSC, lightSpotFalloff);
   }
   else
   {
      /*if (probe->mCubemap && !probe->mCubemap.isNull())
      {
         GFX->setCubeTexture(1, probe->mCubemap.getPointer());
      }*/
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

   //ProbeInfo *probe;
   //probe = mRegisteredProbes[0];

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
   PROFILE_SCOPE(RenderProbeMgr_render);

   // Early out if nothing to draw.
   if (!ProbeRenderInst::all.size())
      return;

   if (!RenderProbeMgr::smRenderReflectionProbes)
      return;

   GFXTransformSaver saver;

   GFXDEBUGEVENT_SCOPE(RenderProbeMgr_render, ColorI::WHITE);

   NamedTexTargetRef sceneColorTargetRef = NamedTexTarget::find("AL_FormatToken");
   if (sceneColorTargetRef.isNull())
      return;

   GFXTextureTargetRef probeLightingTargetRef = GFX->allocRenderToTextureTarget();

   if (probeLightingTargetRef.isNull())
      return;

   //Do a quick pass to update our probes if they're dirty
   //PROBEMGR->updateDirtyProbes();

   probeLightingTargetRef->attachTexture(GFXTextureTarget::Color0, sceneColorTargetRef->getTexture(0));

   GFX->pushActiveRenderTarget();
   GFX->setActiveRenderTarget(probeLightingTargetRef);

   GFX->setViewport(sceneColorTargetRef->getViewport());
    
   // Restore transforms
   MatrixSet &matrixSet = getRenderPass()->getMatrixSet();
   matrixSet.restoreSceneViewProjection();

   const MatrixF &worldToCameraXfm = matrixSet.getWorldToCamera();

   // Set up the SG Data
   SceneData sgData;
   sgData.init(state);

   // Initialize and set the per-frame parameters after getting
   // the vector light material as we use lazy creation.
   _setupPerFrameParameters(state);

   //Order the probes by size, biggest to smallest
   //dQsort(ProbeRenderInst::all.address(), ProbeRenderInst::all.size(), sizeof(const ProbeRenderInst*), AscendingReflectProbeInfluence);

   //Specular
   PROFILE_START(RenderProbeManager_ReflectProbeRender);

   ReflectProbeMaterialInfo* reflProbeMat = getReflectProbeMaterial();

   if (reflProbeMat == nullptr || reflProbeMat->matInstance == nullptr)
      return;

   MaterialParameters *matParams = reflProbeMat->matInstance->getMaterialParameters();

   MaterialParameterHandle *numProbesSC = reflProbeMat->matInstance->getMaterialParameterHandle("$numProbes");

   MaterialParameterHandle *probePositionSC = reflProbeMat->matInstance->getMaterialParameterHandle("$inProbePosArray");
   MaterialParameterHandle *probeWorldToObjSC = reflProbeMat->matInstance->getMaterialParameterHandle("$worldToObjArray");
   MaterialParameterHandle *probeBBMinSC = reflProbeMat->matInstance->getMaterialParameterHandle("$bbMinArray");
   MaterialParameterHandle *probeBBMaxSC = reflProbeMat->matInstance->getMaterialParameterHandle("$bbMaxArray");
   MaterialParameterHandle *probeUseSphereModeSC = reflProbeMat->matInstance->getMaterialParameterHandle("$useSphereMode");
   MaterialParameterHandle *probeRadiusSC = reflProbeMat->matInstance->getMaterialParameterHandle("$radius");
   MaterialParameterHandle *probeAttenuationSC = reflProbeMat->matInstance->getMaterialParameterHandle("$attenuation");

   //Array rendering
   U32 probeCount = ProbeRenderInst::all.size();

   if (probeCount == 0)
      return;
   MatrixF trans = MatrixF::Identity;
   sgData.objTrans = &trans;
   
   U32 effectiveProbeCount = 0;

   for (U32 i = 0; i < probeCount; i++)
   {
      if (effectiveProbeCount >= MAXPROBECOUNT)
         break;

      ProbeRenderInst* curEntry = ProbeRenderInst::all[i];
      if (!curEntry->mIsEnabled)
         continue;

      if (curEntry->mCubemap.isNull() || curEntry->mIrradianceCubemap.isNull())
         continue;

      if (!curEntry->mCubemap->isInitialised())
         continue;

      if (curEntry->mIsSkylight)
         continue;

      //Setup
      const Point3F &probePos = curEntry->getPosition();
      probePositions[i] = probePos + curEntry->mProbePosOffset;

      MatrixF trans = curEntry->getTransform();
      trans.inverse();

      probeWorldToObj[i]=trans;

      probeBBMin[i] = curEntry->mBounds.minExtents;
      probeBBMax[i] = curEntry->mBounds.maxExtents;

      probeUseSphereMode[i] = curEntry->mProbeShapeType == ProbeRenderInst::Sphere ? 1 : 0;

      probeRadius[i] = curEntry->mRadius;
      probeAttenuation[i] = 1;

      cubeMaps[i] = curEntry->mCubemap;
      irradMaps[i] = curEntry->mIrradianceCubemap;

      effectiveProbeCount++;
   }

   if (effectiveProbeCount != 0)
   {
      U32 count = effectiveProbeCount;
      matParams->setSafe(numProbesSC, (float)effectiveProbeCount);

      mCubemapArray = GFXCubemapArrayHandle(GFX->createCubemapArray());
      mIrradArray = GFXCubemapArrayHandle(GFX->createCubemapArray());

      mCubemapArray->initStatic(cubeMaps.address(), count);
      mIrradArray->initStatic(irradMaps.address(), count);

      NamedTexTarget *deferredTarget = NamedTexTarget::find(RenderDeferredMgr::BufferName);
      if (deferredTarget)
         GFX->setTexture(0, deferredTarget->getTexture());
      else
         GFX->setTexture(0, NULL);

      NamedTexTarget *colorTarget = NamedTexTarget::find(RenderDeferredMgr::ColorBufferName);
      if (colorTarget)
         GFX->setTexture(1, colorTarget->getTexture());
      else
         GFX->setTexture(1, NULL);

      NamedTexTarget *matinfoTarget = NamedTexTarget::find(RenderDeferredMgr::MatInfoBufferName);
      if (matinfoTarget)
         GFX->setTexture(2, matinfoTarget->getTexture());
      else
         GFX->setTexture(2, NULL);

      if (mBrdfTexture)
      {
         GFX->setTexture(3, mBrdfTexture);
      }
      else
         GFX->setTexture(3, NULL);

      //GFX->setCubeArrayTexture(4, mCubemapArray);
      //GFX->setCubeArrayTexture(5, mIrradArray);

      ProbeRenderInst* curEntry = ProbeRenderInst::all[0];
      count = MAXPROBECOUNT;
      //Final packing
      AlignedArray<Point4F> _probePositions(count, sizeof(Point4F), (U8*)probePositions.address(), false);
      AlignedArray<Point4F> _probeBBMin(count, sizeof(Point4F), (U8*)probeBBMin.address(), false);
      AlignedArray<Point4F> _probeBBMax(count, sizeof(Point4F), (U8*)probeBBMax.address(), false);
      AlignedArray<float> _probeUseSphereMode(count, sizeof(float), (U8*)probeUseSphereMode.address(), false);
      AlignedArray<float> _probeRadius(count, sizeof(float), (U8*)probeRadius.address(), false);
      AlignedArray<float> _probeAttenuation(count, sizeof(float), (U8*)probeAttenuation.address(), false);

      matParams->set(probePositionSC, _probePositions);
      matParams->set(probeWorldToObjSC, probeWorldToObj.address(), count);
      matParams->set(probeBBMinSC, _probeBBMin);
      matParams->set(probeBBMaxSC, _probeBBMax);
      matParams->set(probeUseSphereModeSC, _probeUseSphereMode);
      matParams->set(probeRadiusSC, _probeRadius);
      matParams->set(probeAttenuationSC, _probeAttenuation);

      // Set geometry
      GFX->setVertexBuffer(mFarFrustumQuadVerts);
      GFX->setPrimitiveBuffer(NULL);

      while (reflProbeMat->matInstance->setupPass(state, sgData))
      {
         // Set transforms
         matrixSet.setWorld(*sgData.objTrans);
         reflProbeMat->matInstance->setTransforms(matrixSet, state);
         reflProbeMat->matInstance->setSceneInfo(state, sgData);

          GFX->drawPrimitive(GFXTriangleStrip, 0, 2);
      }
   }

   GFX->popActiveRenderTarget();

   //PROBEMGR->unregisterAllProbes();
   //PROBEMGR->mRegisteredProbes.clear();

   PROFILE_END();

   GFX->setVertexBuffer(NULL);
   GFX->setPrimitiveBuffer(NULL);

   // Fire off a signal to let others know that light-bin rendering is ending now
   //getRenderSignal().trigger(state, this);
}

//
//
RenderProbeMgr::ReflectProbeMaterialInfo::ReflectProbeMaterialInfo(const String &matName,
   const GFXVertexFormat *vertexFormat)
   : matInstance(NULL),
   zNearFarInvNearFar(NULL),
   farPlane(NULL),
   vsFarPlane(NULL),
   negFarPlaneDotEye(NULL),
   probeWSPos(NULL),
   attenuation(NULL),
   radius(NULL),
   cubeMips(NULL)
{
   Material *mat = MATMGR->getMaterialDefinitionByName(matName);
   if (!mat)
      return;

   matInstance = new ReflectProbeMatInstance(*mat);

   const Vector<GFXShaderMacro> &macros = Vector<GFXShaderMacro>();

   for (U32 i = 0; i < macros.size(); i++)
      matInstance->addShaderMacro(macros[i].name, macros[i].value);

   matInstance->init(MATMGR->getDefaultFeatures(), vertexFormat);

   attenuation = matInstance->getMaterialParameterHandle("$attenuation");
   radius = matInstance->getMaterialParameterHandle("$radius");
   probeLSPos = matInstance->getMaterialParameterHandle("$probeLSPos");
   probeWSPos = matInstance->getMaterialParameterHandle("$probeWSPos");
   farPlane = matInstance->getMaterialParameterHandle("$farPlane");
   vsFarPlane = matInstance->getMaterialParameterHandle("$vsFarPlane");
   negFarPlaneDotEye = matInstance->getMaterialParameterHandle("$negFarPlaneDotEye");
   zNearFarInvNearFar = matInstance->getMaterialParameterHandle("$zNearFarInvNearFar");

   useCubemap = matInstance->getMaterialParameterHandle("$useCubemap");

   cubemap = matInstance->getMaterialParameterHandle("$cubeMap");
   cubeMips = matInstance->getMaterialParameterHandle("$cubeMips");

   eyePosWorld = matInstance->getMaterialParameterHandle("$eyePosWorld");
   bbMin = matInstance->getMaterialParameterHandle("$bbMin");
   bbMax = matInstance->getMaterialParameterHandle("$bbMax");

   useSphereMode = matInstance->getMaterialParameterHandle("$useSphereMode");

   probeCount = matInstance->getMaterialParameterHandle("$numProbes");

   for (U32 i = 0; i < 9; i++)
      shTerms[i] = matInstance->getMaterialParameterHandle(String::ToString("$SHTerms%d", i));

   for (U32 i = 0; i < 5; i++)
      shConsts[i] = matInstance->getMaterialParameterHandle(String::ToString("$SHConsts%d", i));
}

RenderProbeMgr::ReflectProbeMaterialInfo::~ReflectProbeMaterialInfo()
{
   SAFE_DELETE(matInstance);
}

void RenderProbeMgr::ReflectProbeMaterialInfo::setViewParameters(const F32 _zNear,
   const F32 _zFar,
   const Point3F &_eyePos,
   const PlaneF &_farPlane,
   const PlaneF &_vsFarPlane)
{
   MaterialParameters *matParams = matInstance->getMaterialParameters();

   matParams->setSafe(farPlane, *((const Point4F *)&_farPlane));

   matParams->setSafe(vsFarPlane, *((const Point4F *)&_vsFarPlane));

   if (negFarPlaneDotEye->isValid())
   {
      // -dot( farPlane, eyePos )
      const F32 negFarPlaneDotEyeVal = -(mDot(*((const Point3F *)&_farPlane), _eyePos) + _farPlane.d);
      matParams->set(negFarPlaneDotEye, negFarPlaneDotEyeVal);
   }

   matParams->setSafe(zNearFarInvNearFar, Point4F(_zNear, _zFar, 1.0f / _zNear, 1.0f / _zFar));

   Point4F frPlane = *((const Point4F *)&_farPlane);
   Point4F vsFrPlane = *((const Point4F *)&_vsFarPlane);
   Point4F nearFarInvNearFar = Point4F(_zNear, _zFar, 1.0f / _zNear, 1.0f / _zFar);
   const F32 negFarPlaneDotEyeVal = -(mDot(*((const Point3F *)&_farPlane), _eyePos) + _farPlane.d);
}

void RenderProbeMgr::ReflectProbeMaterialInfo::setProbeParameters(const ProbeRenderInst *probeInfo, const SceneRenderState* renderState, const MatrixF &worldViewOnly)
{
   //Set up the params
   MaterialParameters *matParams = matInstance->getMaterialParameters();

   matParams->setSafe(radius, probeInfo->mRadius);

   Point3F probePos = probeInfo->getPosition() + probeInfo->mProbePosOffset;
   //worldViewOnly.mulP(probeInfo->getPosition(), &probePos);
   matParams->setSafe(probeWSPos, probePos);

   worldViewOnly.mulP(probeInfo->getPosition(), &probePos);
   matParams->setSafe(probeLSPos, probePos);

   // Get the attenuation falloff ratio and normalize it.
   Point3F attenRatio = Point3F(0.0f, 1.0f, 1.0f);
   F32 total = attenRatio.x + attenRatio.y + attenRatio.z;
   if (total > 0.0f)
      attenRatio /= total;

   F32 probeRadius = probeInfo->mRadius;

   Point2F attenParams((1.0f / probeRadius) * attenRatio.y,
      (1.0f / (probeRadius * probeRadius)) * attenRatio.z);

   matParams->setSafe(attenuation, attenParams);

   NamedTexTarget* deferredTexTarget = NamedTexTarget::find("deferred");
   NamedTexTarget* matInfoTexTarget = NamedTexTarget::find("matinfo");
   NamedTexTarget* colorTexTarget = NamedTexTarget::find("color");

   if (!deferredTexTarget || !matInfoTexTarget || !colorTexTarget)
   {
      Con::errorf("ProbeManager::ReflectProbeMaterialInfo::setProbeParameters: Could not retrieve gbuffer");
      return;
   }

   //set textures
   GFX->setTexture(0, deferredTexTarget->getTexture());
   GFX->setTexture(1, colorTexTarget->getTexture());
   GFX->setTexture(2, matInfoTexTarget->getTexture());

   //Add some safety catches in the event the cubemaps aren't fully initialized yet
   if (probeInfo->mCubemap == nullptr || probeInfo->mCubemap.isNull())
   {
      GFX->setCubeTexture(3, nullptr);
      matParams->setSafe(cubeMips, 2.0f);
   }
   else
   {
      GFX->setCubeTexture(3, probeInfo->mCubemap.getPointer());
      matParams->setSafe(cubeMips, mPow(probeInfo->mCubemap.getPointer()->getMipMapLevels(), 2.0f));
   }

   if (probeInfo->mIrradianceCubemap == nullptr || probeInfo->mIrradianceCubemap.isNull())
      GFX->setCubeTexture(4, nullptr);
   else
      GFX->setCubeTexture(4, probeInfo->mIrradianceCubemap.getPointer());

   GFX->setTexture(5, probeInfo->mBRDFTexture->getPointer());

   //set material params
   matParams->setSafe(eyePosWorld, renderState->getCameraPosition());
   matParams->setSafe(bbMin, probeInfo->mBounds.minExtents);
   matParams->setSafe(bbMax, probeInfo->mBounds.maxExtents);
   matParams->setSafe(useSphereMode, probeInfo->mProbeShapeType == ProbeRenderInst::Sphere ? 1.0f : 0.0f);
}