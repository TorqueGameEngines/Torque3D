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

Signal<void(const char*,bool)> ProbeManager::smActivateSignal;
ProbeManager *ProbeManager::smProbeManager = NULL;


//
//
ProbeInfo::ProbeInfo()
   : mTransform(true),
   mAmbient(0.0f, 0.0f, 0.0f, 1.0f),
   mPriority(1.0f),
   mScore(0.0f),
   mDebugRender(false),
   mCubemap(NULL),
   mIrradianceCubemap(NULL),
   mBRDFTexture(NULL),
   mRadius(1.0f),
   mIntensity(1.0f)
{
   for (U32 i = 0; i < 5; ++i)
   {
      mSHConstants[i] = 0;
   }
}

ProbeInfo::~ProbeInfo()
{
   SAFE_DELETE(mCubemap);
}

void ProbeInfo::set(const ProbeInfo *probeInfo)
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

void ProbeInfo::getWorldToLightProj(MatrixF *outMatrix) const
{
   *outMatrix = getTransform();
   outMatrix->inverse();
}


void ProbeInfoList::registerProbe(ProbeInfo *light)
{
   if (!light)
      return;
   // just add the light, we'll try to scan for dupes later...
   push_back(light);
}

void ProbeInfoList::unregisterProbe(ProbeInfo *light)
{
   // remove all of them...
   ProbeInfoList &list = *this;
   for (U32 i = 0; i<list.size(); i++)
   {
      if (list[i] != light)
         continue;

      // this moves last to i, which allows
      // the search to continue forward...
      list.erase_fast(i);
      // want to check this location again...
      i--;
   }
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
   :  mDefaultProbe( NULL ),
      mSceneManager( NULL ),
      mCullPos( Point3F::Zero )
{ 
   dMemset( &mSpecialProbes, 0, sizeof(mSpecialProbes) );

   mLastShader = NULL;
   mLastConstants = NULL;
}

ProbeManager::~ProbeManager() 
{
}

ProbeInfo* ProbeManager::createProbeInfo(ProbeInfo* probe /* = NULL */)
{
   ProbeInfo *outProbe = (probe != NULL) ? probe : new ProbeInfo;

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

   // Just in case... make sure we're all clear.
   unregisterAllProbes();
}

ProbeInfo* ProbeManager::getDefaultLight()
{
   // The sun is always our default light when
   // when its registered.
   if ( mSpecialProbes[ ProbeManager::SkylightProbeType ] )
      return mSpecialProbes[ ProbeManager::SkylightProbeType ];

   // Else return a dummy special light.
   //if ( !mDefaultLight )
   //   mDefaultLight = createLightInfo();
   return NULL;
}

ProbeInfo* ProbeManager::getSpecialProbe( ProbeManager::SpecialProbeTypesEnum type, bool useDefault )
{
   //if ( mSpecialLights[type] )
   //   return mSpecialLights[type];

   if ( useDefault )
      return getDefaultLight();

   return NULL;
}

void ProbeManager::setSpecialProbe( ProbeManager::SpecialProbeTypesEnum type, ProbeInfo *probe )
{
   if (probe && type == SkylightProbeType )
   {
      // The sun must be specially positioned and ranged
      // so that it can be processed like a point light 
      // in the stock light shader used by Basic Lighting.
      
      probe->setPosition( mCullPos - (probe->getDirection() * 10000.0f ) );
      probe->mRadius = 2000000.0f;
   }

   mSpecialProbes[type] = probe;
   registerProbe(probe, NULL );
}

void ProbeManager::registerProbes( const Frustum *frustum, bool staticLighting )
{
   PROFILE_SCOPE( ProbeManager_RegisterProbes );

   // TODO: We need to work this out...
   //
   // 1. Why do we register and unregister lights on every 
   //    render when they don't often change... shouldn't we
   //    just register once and keep them?
   // 
   // 2. If we do culling of lights should this happen as part
   //    of registration or somewhere else?
   //

   // Grab the lights to process.
   Vector<SceneObject*> activeLights;
   const U32 lightMask = LightObjectType;
   
   if ( staticLighting || !frustum )
   {
      // We're processing static lighting or want all the lights
      // in the container registerd...  so no culling.
      getSceneManager()->getContainer()->findObjectList( lightMask, &activeLights );
   }
   else
   {
      // Cull the lights using the frustum.
      getSceneManager()->getContainer()->findObjectList( *frustum, lightMask, &activeLights );
      /* supress light culling filter until we can sort out why that's misbehaving with dynamic cube mapping
      for (U32 i = 0; i < activeLights.size(); ++i)
      {
         if (!getSceneManager()->mRenderedObjectsList.contains(activeLights[i]))
         {
            activeLights.erase(i);
            --i;
         }
      }
      */
      // Store the culling position for sun placement
      // later... see setSpecialLight.
      mCullPos = frustum->getPosition();

      // HACK: Make sure the control object always gets 
      // processed as lights mounted to it don't change
      // the shape bounds and can often get culled.

      GameConnection *conn = GameConnection::getConnectionToServer();
      if ( conn->getControlObject() )
      {
         GameBase *conObject = conn->getControlObject();
         activeLights.push_back_unique( conObject );
      }
   }

   // Let the lights register themselves.
   /*for ( U32 i = 0; i < activeLights.size(); i++ )
   {
      ISceneLight *lightInterface = dynamic_cast<ISceneLight*>( activeLights[i] );
      if ( lightInterface )
         lightInterface->submitLights( this, staticLighting );
   }*/
}

void ProbeManager::registerSkylight(ProbeInfo *probe, SimObject *obj)
{
   mSkylight = probe;

   if (String("Advanced Lighting").equal(LIGHTMGR->getName(), String::NoCase))
   {
      SceneRenderState* state = mSceneManager->getCurrentRenderState();

      RenderPassManager *renderPass = state->getRenderPass();

      // Allocate an MeshRenderInst so that we can submit it to the RenderPassManager
      ProbeRenderInst *probeInst = renderPass->allocInst<ProbeRenderInst>();

      probeInst->set(probe);

      probeInst->type = RenderPassManager::RIT_Probes;

      // Submit our RenderInst to the RenderPassManager
      state->getRenderPass()->addInst(probeInst);
   }
}

void ProbeManager::registerProbe(ProbeInfo *probe, SimObject *obj )
{
  // AssertFatal( !mRegisteredProbes.contains(probe),
      //"ProbeManager::registerGlobalLight - This light is already registered!" );

   if (!mRegisteredProbes.contains(probe))
      mRegisteredProbes.push_back(probe);

   if (String("Advanced Lighting").equal(LIGHTMGR->getName(), String::NoCase))
   {
      SceneRenderState* state = mSceneManager->getCurrentRenderState();

      RenderPassManager *renderPass = state->getRenderPass();

      // Allocate an MeshRenderInst so that we can submit it to the RenderPassManager
      ProbeRenderInst *probeInst = renderPass->allocInst<ProbeRenderInst>();

      probeInst->set(probe);

      probeInst->type = RenderPassManager::RIT_Probes;

      // Submit our RenderInst to the RenderPassManager
      state->getRenderPass()->addInst(probeInst);
   }
}

void ProbeManager::unregisterProbe(ProbeInfo *probe )
{
   mRegisteredProbes.unregisterProbe(probe);

   // If this is the sun... clear the special light too.
   if (probe == mSpecialProbes[SkylightProbeType] )
      dMemset(mSpecialProbes, 0, sizeof(mSpecialProbes) );
}

void ProbeManager::unregisterAllProbes()
{
   //dMemset(mSpecialProbes, 0, sizeof(mSpecialProbes) );
   mRegisteredProbes.clear();

   mSkylight = nullptr;
}

void ProbeManager::getAllUnsortedProbes( Vector<ProbeInfo*> *list ) const
{
   list->merge( mRegisteredProbes );
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
      probeCubemapSC->isValid()  && (!mRegisteredProbes.empty() || mSkylight))
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
      const ProbeInfo *probe;
      for (U32 i = 0; i < 4; i++)
      {
         if (i >= mRegisteredProbes.size())
            break;

         if (i == 0 && mSkylight)
         {
            //quickly try and see if we have a skylight, and set that to always be probe 0
            probe = mSkylight;
         }
         else
         {
            probe = mRegisteredProbes[i];
         }

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

         probeIsSphere[i] = probe->mProbeShapeType == ProbeInfo::Sphere ? 1.0 : 0.0;

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
