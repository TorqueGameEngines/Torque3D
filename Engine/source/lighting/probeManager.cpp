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

#include "platform/platform.h"
#include "lighting/probeManager.h"

#include "console/console.h"
#include "console/consoleTypes.h"
#include "core/util/safeDelete.h"
#include "console/sim.h"
#include "console/simSet.h"
#include "scene/sceneManager.h"
#include "materials/materialManager.h"
#include "materials/sceneData.h"
#include "lighting/lightInfo.h"
#include "lighting/lightingInterfaces.h"
#include "T3D/gameBase/gameConnection.h"
#include "gfx/gfxStringEnumTranslate.h"
#include "console/engineAPI.h"
#include "renderInstance/renderDeferredMgr.h"
#include "shaderGen/shaderGenVars.h"

#include "math/util/sphereMesh.h"

Signal<void(const char*,bool)> ProbeManager::smActivateSignal;
ProbeManager *ProbeManager::smProbeManager = NULL;

bool ProbeManager::smRenderReflectionProbes = true;

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
   mProbePosOffset(0,0,0),
   numPrims(0)
{
   for (U32 i = 0; i < 5; ++i)
   {
      mSHConstants[i] = 0;
   }
}

ProbeRenderInst::~ProbeRenderInst()
{
   if (mCubemap && !mCubemap->isNull())
   {
      mCubemap->getPointer()->destroySelf();
      mCubemap->free();
   }
   if (mIrradianceCubemap && !mIrradianceCubemap->isNull())
   {
      mIrradianceCubemap->getPointer()->destroySelf();
      mIrradianceCubemap->free();
   }
   if (mBRDFTexture && !mBRDFTexture->isNull())
   {
      mBRDFTexture->getPointer()->destroySelf();
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
   mProbeCubemapSC(NULL)
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

   mInit = true;
}

void ProbeShaderConstants::_onShaderReload()
{
   if (mShader.isValid())
      init(mShader);
}

ProbeManager::ProbeManager()
   :  mSceneManager( NULL ),
      mCullPos( Point3F::Zero )
{ 
   mLastShader = NULL;
   mLastConstants = NULL;

   mSkylightMaterial = nullptr;
   mReflectProbeMaterial = nullptr;
}

ProbeManager::~ProbeManager() 
{
}

ProbeRenderInst* ProbeManager::createProbeInfo(ProbeRenderInst* probe /* = NULL */)
{
   ProbeRenderInst *outProbe = (probe != NULL) ? probe : new ProbeRenderInst;

   /*ProbeManagerMap &ProbeManagers = _getProbeManagers();
   ProbeManagerMap::Iterator iter = ProbeManagers.begin();
   for ( ; iter != ProbeManagers.end(); iter++ )
   {
      ProbeManager *lm = iter->value;
      lm->_addLightInfoEx( outLight );
   }*/

   return outProbe;
}

/*void ProbeManager::initLightFields()
{
   ProbeManagerMap &ProbeManagers = _getProbeManagers();

   ProbeManagerMap::Iterator iter = ProbeManagers.begin();
   for ( ; iter != ProbeManagers.end(); iter++ )
   {
      ProbeManager *lm = iter->value;
      lm->_initLightFields();
   }
}*/

IMPLEMENT_GLOBAL_CALLBACK( onProbeManagerActivate, void, ( const char *name ), ( name ),
   "A callback called by the engine when a light manager is activated.\n"
   "@param name The name of the light manager being activated.\n"
   "@ingroup Lighting\n" );

void ProbeManager::activate( SceneManager *sceneManager )
{
   AssertFatal( sceneManager, "ProbeManager::activate() - Got null scene manager!" );
   //AssertFatal( mIsActive == false, "ProbeManager::activate() - Already activated!" );
   AssertFatal(smProbeManager == NULL, "ProbeManager::activate() - A previous ProbeManager is still active!" );

   mSceneManager = sceneManager;
   smProbeManager = this;
}

IMPLEMENT_GLOBAL_CALLBACK( onProbeManagerDeactivate, void, ( const char *name ), ( name ),
   "A callback called by the engine when a light manager is deactivated.\n"
   "@param name The name of the light manager being deactivated.\n"
   "@ingroup Lighting\n" );

void ProbeManager::deactivate()
{
   //AssertFatal( mIsActive == true, "ProbeManager::deactivate() - Already deactivated!" );
   AssertFatal( smProbeManager == this, "ProbeManager::activate() - This isn't the active light manager!" );

   //if( Sim::getRootGroup() ) // To protect against shutdown.
   //   onProbeManagerDeactivate_callback( getName() );

   //mIsActive = false;
   mSceneManager = NULL;
   smProbeManager = NULL;
}

ProbeShaderConstants* ProbeManager::getProbeShaderConstants(GFXShaderConstBuffer* buffer)
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

void ProbeManager::_update4ProbeConsts(   const SceneData &sgData,
                                          MatrixSet &matSet,
                                          GFXShaderConstHandle *probePositionSC,
                                          GFXShaderConstHandle *probeRadiusSC,
                                          GFXShaderConstHandle *probeBoxMinSC,
                                          GFXShaderConstHandle *probeBoxMaxSC,
                                          GFXShaderConstHandle *probeCubemapSC,
                                          GFXShaderConstHandle *probeIsSphereSC,
                                          GFXShaderConstHandle *probeLocalPosSC,
                                          GFXShaderConstBuffer *shaderConsts )
{
   PROFILE_SCOPE( ProbeManager_Update4ProbeConsts );

   // Skip over gathering lights if we don't have to!
   if (probePositionSC->isValid() ||
      probeRadiusSC->isValid() ||
      probeBoxMinSC->isValid() ||
      probeBoxMaxSC->isValid() ||
      probeCubemapSC->isValid()  && (!ProbeRenderInst::all.empty()))
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

         if (probe->mCubemap && !probe->mCubemap->isNull())
         {
            S32 samplerReg = probeCubemapSC->getSamplerRegister();

            if(samplerReg != -1)
               GFX->setCubeTexture(samplerReg + i, probe->mCubemap->getPointer());
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
      /*if (probe->mCubemap && !probe->mCubemap->isNull())
      {
         GFX->setCubeTexture(1, probe->mCubemap->getPointer());
      }*/
      if (probeCubemapSC->isValid())
      {
         for(U32 i=0; i < 4; ++i)
            GFX->setCubeTexture(probeCubemapSC->getSamplerRegister() + i, NULL);
      }
   }
}

void ProbeManager::setProbeInfo(ProcessedMaterial *pmat,
   const Material *mat,
   const SceneData &sgData,
   const SceneRenderState *state,
   U32 pass,
   GFXShaderConstBuffer *shaderConsts)
{
   
   // Skip this if we're rendering from the deferred bin.
   if ( sgData.binType == SceneData::DeferredBin )
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
   _update4ProbeConsts( sgData,
      matSet,
      psc->mProbePositionSC,
      psc->mProbeRadiusSC,
      psc->mProbeBoxMinSC,
      psc->mProbeBoxMaxSC,
      psc->mProbeCubemapSC,
      psc->mProbeIsSphereSC,
      psc->mProbeLocalPosSC,
      shaderConsts );

   // Static
   /*if (lsm && light->getCastShadows())
   {
      if (psc->mWorldToLightProjSC->isValid())
         shaderConsts->set(psc->mWorldToLightProjSC,
            lsm->getWorldToLightProj(),
            psc->mWorldToLightProjSC->getType());

      if (psc->mViewToLightProjSC->isValid())
      {
         // TODO: Should probably cache these results and
         // not do this mul here on every material that needs
         // this transform.

         shaderConsts->set(psc->mViewToLightProjSC,
            lsm->getWorldToLightProj() * state->getCameraTransform(),
            psc->mViewToLightProjSC->getType());
      }

      shaderConsts->setSafe(psc->mShadowMapSizeSC, 1.0f / (F32)lsm->getTexSize());

      // Do this last so that overrides can properly override parameters previously set
      lsm->setShaderParameters(shaderConsts, psc);
   }
   else
   {
      if (psc->mViewToLightProjSC->isValid())
      {
         // TODO: Should probably cache these results and
         // not do this mul here on every material that needs
         // this transform.
         MatrixF proj;
         light->getWorldToLightProj(&proj);

         shaderConsts->set(psc->mViewToLightProjSC,
            proj * state->getCameraTransform(),
            psc->mViewToLightProjSC->getType());
      }
   }

   // Dynamic
   if (dynamicShadowMap)
   {
      if (psc->mDynamicWorldToLightProjSC->isValid())
         shaderConsts->set(psc->mDynamicWorldToLightProjSC,
            dynamicShadowMap->getWorldToLightProj(),
            psc->mDynamicWorldToLightProjSC->getType());

      if (psc->mDynamicViewToLightProjSC->isValid())
      {
         // TODO: Should probably cache these results and
         // not do this mul here on every material that needs
         // this transform.

         shaderConsts->set(psc->mDynamicViewToLightProjSC,
            dynamicShadowMap->getWorldToLightProj() * state->getCameraTransform(),
            psc->mDynamicViewToLightProjSC->getType());
      }

      shaderConsts->setSafe(psc->mShadowMapSizeSC, 1.0f / (F32)dynamicShadowMap->getTexSize());

      // Do this last so that overrides can properly override parameters previously set
      dynamicShadowMap->setShaderParameters(shaderConsts, psc);
   }
   else
   {
      if (psc->mDynamicViewToLightProjSC->isValid())
      {
         // TODO: Should probably cache these results and
         // not do this mul here on every material that needs
         // this transform.
         MatrixF proj;
         light->getWorldToLightProj(&proj);

         shaderConsts->set(psc->mDynamicViewToLightProjSC,
            proj * state->getCameraTransform(),
            psc->mDynamicViewToLightProjSC->getType());
      }
   }*/
}

/// Allows us to set textures during the Material::setTextureStage call, return true if we've done work.
bool ProbeManager::setTextureStage(const SceneData &sgData,
   const U32 currTexFlag,
   const U32 textureSlot,
   GFXShaderConstBuffer *shaderConsts,
   ShaderConstHandles *handles)
{
   return false;
}

AvailableSLInterfaces* ProbeManager::getSceneLightingInterface()
{
   //if ( !mAvailableSLInterfaces )
   //   mAvailableSLInterfaces = new AvailableSLInterfaces();

   return NULL;
}

void ProbeManager::updateDirtyProbes()
{
	for (U32 i = 0; i < ProbeRenderInst::all.size(); i++)
	{
      ProbeRenderInst* probe = ProbeRenderInst::all[i];

		if (probe->mDirty)
		{
			//make sure we have a fill-out on our primitives, materials, etc 
			//so we don't have to always force an update when it's not needed
			if (probe->mIsSkylight)
			{
				setupSkylightProbe(probe);
			}
			else
			{
				if (probe->mProbeShapeType == ProbeRenderInst::Sphere)
				{
					setupSphereReflectionProbe(probe);
				}
				else if(probe->mProbeShapeType == ProbeRenderInst::Box)
				{
					setupConvexReflectionProbe(probe);
				}
			}

			probe->mDirty = false;
		}
	}
}

ProbeManager::SkylightMaterialInfo* ProbeManager::getSkylightMaterial()
{
	PROFILE_SCOPE(AdvancedLightBinManager_getSkylightMaterial);

	//ReflectProbeMaterialInfo *info = NULL;

	if (!mSkylightMaterial)

		// Now create the material info object.
		mSkylightMaterial = new SkylightMaterialInfo("SklyightMaterial",
			getGFXVertexFormat<GFXVertexPC>());

	return mSkylightMaterial;
}

ProbeManager::ReflectProbeMaterialInfo* ProbeManager::getReflectProbeMaterial()
{
	PROFILE_SCOPE(AdvancedLightBinManager_getReflectProbeMaterial);

	//ReflectProbeMaterialInfo *info = NULL;

	if (!mReflectProbeMaterial)

		// Now create the material info object.
		mReflectProbeMaterial = new ReflectProbeMaterialInfo("ReflectionProbeMaterial",
			getGFXVertexFormat<GFXVertexPC>());

	return mReflectProbeMaterial;
}

void ProbeManager::setupSkylightProbe(ProbeRenderInst *probeInfo)
{
	probeInfo->vertBuffer = getSphereMesh(probeInfo->numPrims, probeInfo->primBuffer);

	if (!mSkylightMaterial)
		mSkylightMaterial = getSkylightMaterial();
}

void ProbeManager::setupSphereReflectionProbe(ProbeRenderInst *probeInfo)
{
	probeInfo->vertBuffer = getSphereMesh(probeInfo->numPrims, probeInfo->primBuffer);

	if (!mReflectProbeMaterial)
		mReflectProbeMaterial = getReflectProbeMaterial();
}

void ProbeManager::setupConvexReflectionProbe(ProbeRenderInst *probeInfo)
{
	static const Point3F cubePoints[8] =
	{
		Point3F(1, -1, -1), Point3F(1, -1,  1), Point3F(1,  1, -1), Point3F(1,  1,  1),
		Point3F(-1, -1, -1), Point3F(-1,  1, -1), Point3F(-1, -1,  1), Point3F(-1,  1,  1)
	};

	/*static const Point3F cubeNormals[6] =
	{
	Point3F(1,  0,  0), Point3F(-1,  0,  0), Point3F(0,  1,  0),
	Point3F(0, -1,  0), Point3F(0,  0,  1), Point3F(0,  0, -1)
	};*/

	/*static const Point2F cubeTexCoords[4] =
	{
	Point2F(0,  0), Point2F(0, -1),
	Point2F(1,  0), Point2F(1, -1)
	};*/

	static const U32 cubeFaces[36][3] =
	{
		{ 3, 0, 3 },{ 0, 0, 0 },{ 1, 0, 1 },
	{ 2, 0, 2 },{ 0, 0, 0 },{ 3, 0, 3 },
	{ 7, 1, 1 },{ 4, 1, 2 },{ 5, 1, 0 },
	{ 6, 1, 3 },{ 4, 1, 2 },{ 7, 1, 1 },
	{ 3, 2, 1 },{ 5, 2, 2 },{ 2, 2, 0 },
	{ 7, 2, 3 },{ 5, 2, 2 },{ 3, 2, 1 },
	{ 1, 3, 3 },{ 4, 3, 0 },{ 6, 3, 1 },
	{ 0, 3, 2 },{ 4, 3, 0 },{ 1, 3, 3 },
	{ 3, 4, 3 },{ 6, 4, 0 },{ 7, 4, 1 },
	{ 1, 4, 2 },{ 6, 4, 0 },{ 3, 4, 3 },
	{ 2, 5, 1 },{ 4, 5, 2 },{ 0, 5, 0 },
	{ 5, 5, 3 },{ 4, 5, 2 },{ 2, 5, 1 }
	};

	// Fill the vertex buffer
	GFXVertexPC *pVert = NULL;

	probeInfo->numVerts = 36;

	probeInfo->vertBuffer.set(GFX, 36, GFXBufferTypeStatic);
	pVert = probeInfo->vertBuffer.lock();

	Point3F halfSize = Point3F(probeInfo->mRadius, probeInfo->mRadius, probeInfo->mRadius);

	for (U32 i = 0; i < 36; i++)
	{
		const U32& vdx = cubeFaces[i][0];
		pVert[i].point = cubePoints[vdx] * halfSize;
	}

	probeInfo->vertBuffer.unlock();

	// Fill the primitive buffer
	U16 *pIdx = NULL;

	probeInfo->primBuffer.set(GFX, 36, 12, GFXBufferTypeStatic);

	probeInfo->primBuffer.lock(&pIdx);

	for (U16 i = 0; i < 36; i++)
		pIdx[i] = i;

	probeInfo->primBuffer.unlock();

	probeInfo->numPrims = 12;

	if (!mReflectProbeMaterial)
		mReflectProbeMaterial = getReflectProbeMaterial();
	//

	// mReflectProbeBin.push_back(pEntry);
}

GFXVertexBufferHandle<GFXVertexPC> ProbeManager::getSphereMesh(U32 &outNumPrimitives, GFXPrimitiveBufferHandle &outPrimitives)
{
	static SphereMesh sSphereMesh;

	if (mSphereGeometry.isNull())
	{
		const SphereMesh::TriangleMesh * sphereMesh = sSphereMesh.getMesh(3);
		S32 numPoly = sphereMesh->numPoly;
		mSpherePrimitiveCount = 0;
		mSphereGeometry.set(GFX, numPoly * 3, GFXBufferTypeStatic);
		mSphereGeometry.lock();
		S32 vertexIndex = 0;

		for (S32 i = 0; i<numPoly; i++)
		{
			mSpherePrimitiveCount++;

			mSphereGeometry[vertexIndex].point = sphereMesh->poly[i].pnt[0];
			mSphereGeometry[vertexIndex].color = ColorI::WHITE;
			vertexIndex++;

			mSphereGeometry[vertexIndex].point = sphereMesh->poly[i].pnt[1];
			mSphereGeometry[vertexIndex].color = ColorI::WHITE;
			vertexIndex++;

			mSphereGeometry[vertexIndex].point = sphereMesh->poly[i].pnt[2];
			mSphereGeometry[vertexIndex].color = ColorI::WHITE;
			vertexIndex++;
		}
		mSphereGeometry.unlock();
	}

	outNumPrimitives = mSpherePrimitiveCount;
	outPrimitives = NULL; // For now
	return mSphereGeometry;
}

//
//
bool ReflectProbeMatInstance::init(const FeatureSet &features, const GFXVertexFormat *vertexFormat)
{
	bool success = Parent::init(features, vertexFormat);

	// If the initialization failed don't continue.
	if (!success || !mProcessedMaterial || mProcessedMaterial->getNumPasses() == 0)
		return false;
	return true;
}

bool ReflectProbeMatInstance::setupPass(SceneRenderState *state, const SceneData &sgData)
{
	// Go no further if the material failed to initialize properly.
	if (!mProcessedMaterial ||
		mProcessedMaterial->getNumPasses() == 0)
		return false;

	bool bRetVal = Parent::setupPass(state, sgData);;

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
		desc.setBlend(true, GFXBlendOne, GFXBlendOne);
		mProjectionState = GFX->createStateBlock(desc);
	}
	// Now override stateblock with our own
	GFX->setStateBlock(mProjectionState);

	return bRetVal;
}

//
//
ProbeManager::ReflectProbeMaterialInfo::ReflectProbeMaterialInfo(const String &matName,
	const GFXVertexFormat *vertexFormat)
	: matInstance(NULL),
	zNearFarInvNearFar(NULL),
	farPlane(NULL),
	vsFarPlane(NULL),
	negFarPlaneDotEye(NULL),
	probeWSPos(NULL),
	attenuation(NULL),
	radius(NULL),
	invViewMat(NULL),
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

	invViewMat = matInstance->getMaterialParameterHandle("$invViewMat");

	useCubemap = matInstance->getMaterialParameterHandle("$useCubemap");

	cubemap = matInstance->getMaterialParameterHandle("$cubeMap");
   cubeMips = matInstance->getMaterialParameterHandle("$cubeMips");

	eyePosWorld = matInstance->getMaterialParameterHandle("$eyePosWorld");
	bbMin = matInstance->getMaterialParameterHandle("$bbMin");
	bbMax = matInstance->getMaterialParameterHandle("$bbMax");

	useSphereMode = matInstance->getMaterialParameterHandle("$useSphereMode");

	for (U32 i = 0; i < 9; i++)
		shTerms[i] = matInstance->getMaterialParameterHandle(String::ToString("$SHTerms%d", i));

	for (U32 i = 0; i < 5; i++)
		shConsts[i] = matInstance->getMaterialParameterHandle(String::ToString("$SHConsts%d", i));
}

ProbeManager::ReflectProbeMaterialInfo::~ReflectProbeMaterialInfo()
{
	SAFE_DELETE(matInstance);
}

void ProbeManager::ReflectProbeMaterialInfo::setViewParameters(const F32 _zNear,
	const F32 _zFar,
	const Point3F &_eyePos,
	const PlaneF &_farPlane,
	const PlaneF &_vsFarPlane, const MatrixF &_inverseViewMatrix)
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

	matParams->setSafe(invViewMat, _inverseViewMatrix);

	Point4F frPlane = *((const Point4F *)&_farPlane);
	Point4F vsFrPlane = *((const Point4F *)&_vsFarPlane);
	Point4F nearFarInvNearFar = Point4F(_zNear, _zFar, 1.0f / _zNear, 1.0f / _zFar);
	const F32 negFarPlaneDotEyeVal = -(mDot(*((const Point3F *)&_farPlane), _eyePos) + _farPlane.d);
}

void ProbeManager::ReflectProbeMaterialInfo::setProbeParameters(const ProbeRenderInst *probeInfo, const SceneRenderState* renderState, const MatrixF &worldViewOnly)
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

	F32 radius = probeInfo->mRadius;

	Point2F attenParams((1.0f / radius) * attenRatio.y,
		(1.0f / (radius * radius)) * attenRatio.z);

	matParams->setSafe(attenuation, attenParams);

	NamedTexTarget* deferredTexTarget = NamedTexTarget::find("deferred");

	GFXTextureObject *deferredTexObject = deferredTexTarget->getTexture();
	if (!deferredTexObject) return;

	GFX->setTexture(0, deferredTexObject);

	NamedTexTarget* matInfoTexTarget = NamedTexTarget::find("matinfo");

	GFXTextureObject *matInfoTexObject = matInfoTexTarget->getTexture();
	if (!matInfoTexObject) return;

	GFX->setTexture(1, matInfoTexObject);

	if (probeInfo->mCubemap && !probeInfo->mCubemap->isNull())
	{
		GFX->setCubeTexture(2, probeInfo->mCubemap->getPointer());
	}
	else
	{
		GFX->setCubeTexture(2, NULL);
	}

	if (probeInfo->mIrradianceCubemap && !probeInfo->mIrradianceCubemap->isNull())
	{
		GFX->setCubeTexture(3, probeInfo->mIrradianceCubemap->getPointer());
	}
	else
	{
		GFX->setCubeTexture(3, NULL);
	}

	if (probeInfo->mBRDFTexture && !probeInfo->mBRDFTexture->isNull())
	{
		GFX->setTexture(4, probeInfo->mBRDFTexture->getPointer());
	}
	else
	{
		GFX->setTexture(4, NULL);
	}

   if (probeInfo->mCubemap->isValid())
      matParams->setSafe(cubeMips, mPow(probeInfo->mCubemap->getPointer()->getMipMapLevels(), 2.0f));
   else
      matParams->setSafe(cubeMips, F32(0.0));

	matParams->setSafe(eyePosWorld, renderState->getCameraPosition());
	matParams->setSafe(bbMin, probeInfo->mBounds.minExtents);
	matParams->setSafe(bbMax, probeInfo->mBounds.maxExtents);

	matParams->setSafe(useSphereMode, probeInfo->mProbeShapeType == ProbeRenderInst::Sphere ? 1.0f : 0.0f);

	//SH Terms
	//static AlignedArray<Point3F> shTermsArray(9, sizeof(Point3F));
	//dMemset(shTermsArray.getBuffer(), 0, shTermsArray.getBufferSize());

	for (U32 i = 0; i < 9; i++)
	{
		matParams->setSafe(shTerms[i], probeInfo->mSHTerms[i]);
	}

	for (U32 i = 0; i < 5; i++)
	{
		matParams->setSafe(shConsts[i], probeInfo->mSHConstants[i]);
	}

   const MatrixF worldToObjectXfm = probeInfo->mTransform;
   MaterialParameterHandle *worldToObjMat = matInstance->getMaterialParameterHandle("$worldToObj");
   matParams->setSafe(worldToObjMat, worldToObjectXfm);
}

//
//
//
ProbeManager::SkylightMaterialInfo::SkylightMaterialInfo(const String &matName,
	const GFXVertexFormat *vertexFormat)
	: ReflectProbeMaterialInfo(matName, vertexFormat)
{
	Material *mat = MATMGR->getMaterialDefinitionByName(matName);
	if (!mat)
		return;

	matInstance = new SkylightMatInstance(*mat);

	const Vector<GFXShaderMacro> &macros = Vector<GFXShaderMacro>();

	for (U32 i = 0; i < macros.size(); i++)
		matInstance->addShaderMacro(macros[i].name, macros[i].value);

	matInstance->init(MATMGR->getDefaultFeatures(), vertexFormat);

	farPlane = matInstance->getMaterialParameterHandle("$farPlane");
	vsFarPlane = matInstance->getMaterialParameterHandle("$vsFarPlane");
	negFarPlaneDotEye = matInstance->getMaterialParameterHandle("$negFarPlaneDotEye");
	zNearFarInvNearFar = matInstance->getMaterialParameterHandle("$zNearFarInvNearFar");

	invViewMat = matInstance->getMaterialParameterHandle("$invViewMat");

	useCubemap = matInstance->getMaterialParameterHandle("$useCubemap");
	cubemap = matInstance->getMaterialParameterHandle("$cubeMap");

	eyePosWorld = matInstance->getMaterialParameterHandle("$eyePosWorld");

	for (U32 i = 0; i < 9; i++)
		shTerms[i] = matInstance->getMaterialParameterHandle(String::ToString("$SHTerms%d", i));

	for (U32 i = 0; i < 5; i++)
		shConsts[i] = matInstance->getMaterialParameterHandle(String::ToString("$SHConsts%d", i));
}

ProbeManager::SkylightMaterialInfo::~SkylightMaterialInfo()
{
	SAFE_DELETE(matInstance);
}

/*bool ProbeManager::lightScene( const char* callback, const char* param )
{
   BitSet32 flags = 0;

   if ( param )
   {
      if ( !dStricmp( param, "forceAlways" ) )
         flags.set( SceneLighting::ForceAlways );
      else if ( !dStricmp(param, "forceWritable" ) )
         flags.set( SceneLighting::ForceWritable );
      else if ( !dStricmp(param, "loadOnly" ) )
         flags.set( SceneLighting::LoadOnly );
   }

   // The SceneLighting object will delete itself 
   // once the lighting process is complete.   
   SceneLighting* sl = new SceneLighting( getSceneLightingInterface() );
   return sl->lightScene( callback, flags );
}*/

/*RenderDeferredMgr* ProbeManager::_findDeferredRenderBin()
{
   RenderPassManager* rpm = getSceneManager()->getDefaultRenderPass();
   for( U32 i = 0; i < rpm->getManagerCount(); i++ )
   {
      RenderBinManager *bin = rpm->getManager( i );
      if( bin->getRenderInstType() == RenderDeferredMgr::RIT_Deferred )
      {
         return ( RenderDeferredMgr* ) bin;
      }
   }

   return NULL;
}*/

DefineEngineFunction( CreateProbeManager, bool, (),,
   "Finds and activates the named light manager.\n"
   "@return Returns true if the light manager is found and activated.\n"
   "@ingroup Lighting\n" )
{
   ProbeManager* probeManager = new ProbeManager();
   
   if (probeManager != nullptr && gClientSceneGraph != nullptr)
   {
      probeManager->activate(gClientSceneGraph);
      return true;
   }

   return false;
}

DefineEngineFunction( resetProbeManager, void, (),,
   "@brief Deactivates and then activates the currently active light manager."
   "This causes most shaders to be regenerated and is often used when global "
   "rendering changes have occured.\n"
   "@ingroup Lighting\n" )
{
   ProbeManager *pm = PROBEMGR;
   if ( !pm)
      return;

   /*SceneManager *sm = lm->getSceneManager();
   lm->deactivate();
   lm->activate( sm );*/
}
