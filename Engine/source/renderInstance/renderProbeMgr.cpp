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

IMPLEMENT_CONOBJECT(RenderProbeMgr);

ConsoleDocClass( RenderProbeMgr, 
   "@brief A render bin which uses object callbacks for rendering.\n\n"
   "This render bin gathers object render instances and calls its delegate "
   "method to perform rendering.  It is used infrequently for specialized "
   "scene objects which perform custom rendering.\n\n"
   "@ingroup RenderBin\n" );

S32 QSORT_CALLBACK AscendingReflectProbeInfluence(const void* a, const void* b)
{
   // Debug Profiling.
   PROFILE_SCOPE(AdvancedLightBinManager_AscendingReflectProbeInfluence);

   // Fetch asset definitions.
   /*const ProbeRenderInst* pReflectProbeA = static_cast<ProbeRenderInst*>(((RenderBinManager::MainSortElem*)(a))->inst);
   const ProbeRenderInst* pReflectProbeB = static_cast<ProbeRenderInst*>(((RenderBinManager::MainSortElem*)(b))->inst);

   // Sort.
   //First, immediate check on if either is a skylight. Skylight always gets the highest priority
   //if (pReflectProbeA->mIsSkylight)
   //   return 1;
   //else if (pReflectProbeB->mIsSkylight)
   //   return -1;
   //No? then sort by score
   if (pReflectProbeA->mScore > pReflectProbeB->mScore)
	   return 1;
   else if (pReflectProbeA->mScore < pReflectProbeB->mScore)
	   return -1;*/
   return  0;
}

RenderProbeMgr::RenderProbeMgr()
: RenderBinManager(RenderPassManager::RIT_Probes, 1.0f, 1.0f)
{
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

//remove
//Con::setIntVariable("lightMetrics::activeReflectionProbes", mReflectProbeBin.size());
//Con::setIntVariable("lightMetrics::culledReflectProbes", 0/*mNumLightsCulled*/);
//

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

   MatrixSet &matrixSet = getRenderPass()->getMatrixSet();
   matrixSet.restoreSceneViewProjection();

   const MatrixF &worldToCameraXfm = matrixSet.getCameraToWorld();

   MatrixF inverseViewMatrix = worldToCameraXfm;

   // Parameters calculated, assign them to the materials
   ProbeManager::SkylightMaterialInfo* skylightMat = PROBEMGR->getSkylightMaterial();

   if (skylightMat != nullptr && skylightMat->matInstance != nullptr)
   {
      skylightMat->setViewParameters(frustum.getNearDist(),
         frustum.getFarDist(),
         frustum.getPosition(),
         farPlane,
         vsFarPlane);
   }

   ProbeManager::ReflectProbeMaterialInfo* reflProbeMat = PROBEMGR->getReflectProbeMaterial();

   if (reflProbeMat != nullptr && reflProbeMat->matInstance != nullptr)
   {
      reflProbeMat->setViewParameters(frustum.getNearDist(),
         frustum.getFarDist(),
         frustum.getPosition(),
         farPlane,
         vsFarPlane);
   }
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

   if (!ProbeManager::smRenderReflectionProbes)
      return;

   GFXTransformSaver saver;

   GFXDEBUGEVENT_SCOPE(RenderProbeMgr_render, ColorI::WHITE);

   NamedTexTargetRef diffuseLightingTarget = NamedTexTarget::find("diffuseLighting");

   if (diffuseLightingTarget.isNull())
      return;

   NamedTexTargetRef specularLightingTarget = NamedTexTarget::find("specularLighting");

   if (specularLightingTarget.isNull())
      return;

   GFXTextureTargetRef probeLightingTargetRef = GFX->allocRenderToTextureTarget();

   if (probeLightingTargetRef.isNull())
      return;

   //Do a quick pass to update our probes if they're dirty
   PROBEMGR->updateDirtyProbes();

   probeLightingTargetRef->attachTexture(GFXTextureTarget::Color0, specularLightingTarget->getTexture());
   probeLightingTargetRef->attachTexture(GFXTextureTarget::Color1, diffuseLightingTarget->getTexture());

   GFX->pushActiveRenderTarget();
   GFX->setActiveRenderTarget(probeLightingTargetRef);

   GFX->setViewport(specularLightingTarget->getViewport());
   //GFX->setViewport(specularLightingTarget->getViewport());

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
   //dQsort(mElementList.address(), mElementList.size(), sizeof(const MainSortElem), AscendingReflectProbeInfluence);

   //Specular
   PROFILE_START(RenderProbeManager_ReflectProbeRender);

   ProbeManager::SkylightMaterialInfo* skylightMat = PROBEMGR->getSkylightMaterial();
   ProbeManager::ReflectProbeMaterialInfo* reflProbeMat = PROBEMGR->getReflectProbeMaterial();

   for (U32 i = 0; i < ProbeRenderInst::all.size(); i++)
   {
      ProbeRenderInst* curEntry = ProbeRenderInst::all[i];

      if (!curEntry->mIsEnabled)
         continue;

      if (curEntry->numPrims == 0)
         continue;

      if (curEntry->mIsSkylight && (!skylightMat || !skylightMat->matInstance))
         continue;

      if (!curEntry->mIsSkylight && (!reflProbeMat || !reflProbeMat->matInstance))
         break;

      //Setup
      MatrixF probeTrans = curEntry->getTransform();

      if (!curEntry->mIsSkylight)
      {
         if (curEntry->mProbeShapeType == ProbeRenderInst::Sphere)
            probeTrans.scale(curEntry->mRadius * 1.01f);
      }
      else
      {
         probeTrans.scale(10); //force it to be big enough to surround the camera
      }

      sgData.objTrans = &probeTrans;

      if(curEntry->mIsSkylight)
         skylightMat->setProbeParameters(curEntry, state, worldToCameraXfm);
      else
         reflProbeMat->setProbeParameters(curEntry, state, worldToCameraXfm);

      // Set geometry
      GFX->setVertexBuffer(curEntry->vertBuffer);
      GFX->setPrimitiveBuffer(curEntry->primBuffer);

      if (curEntry->mIsSkylight)
      {
         while (skylightMat->matInstance->setupPass(state, sgData))
         {
            // Set transforms
            matrixSet.setWorld(*sgData.objTrans);
            skylightMat->matInstance->setTransforms(matrixSet, state);
            skylightMat->matInstance->setSceneInfo(state, sgData);

            GFX->drawPrimitive(GFXTriangleList, 0, curEntry->numPrims);
         }
      }
      else
      {
         while (reflProbeMat->matInstance->setupPass(state, sgData))
         {
            // Set transforms
            matrixSet.setWorld(*sgData.objTrans);
            reflProbeMat->matInstance->setTransforms(matrixSet, state);
            reflProbeMat->matInstance->setSceneInfo(state, sgData);

            GFX->drawPrimitive(GFXTriangleList, 0, curEntry->numPrims);
         }
      }
   }

   probeLightingTargetRef->resolve();
   GFX->popActiveRenderTarget();

   //PROBEMGR->unregisterAllProbes();
   PROFILE_END();

   GFX->setVertexBuffer(NULL);
   GFX->setPrimitiveBuffer(NULL);

   // Fire off a signal to let others know that light-bin rendering is ending now
   //getRenderSignal().trigger(state, this);
}