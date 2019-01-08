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

#include "materials/shaderData.h"

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
   const ProbeRenderInst* pReflectProbeA = (*(ProbeRenderInst**)a);
   const ProbeRenderInst* pReflectProbeB = (*(ProbeRenderInst**)b);
   //sort by score
   return  pReflectProbeA->mScore - pReflectProbeB->mScore;
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
   GFXVertexPC verts[4];
   {
      verts[0].point.set(wsFrustumPoints[Frustum::FarTopLeft] - cameraPos);
      //invCam.mulP(wsFrustumPoints[Frustum::FarTopLeft], &verts[0].normal);
      //verts[0].texCoord.set(-1.0, 1.0);
      //verts[0].tangent.set(wsFrustumPoints[Frustum::FarTopLeft] - cameraOffsetPos);

      verts[1].point.set(wsFrustumPoints[Frustum::FarTopRight] - cameraPos);
     // invCam.mulP(wsFrustumPoints[Frustum::FarTopRight], &verts[1].normal);
      //verts[1].texCoord.set(1.0, 1.0);
      //verts[1].tangent.set(wsFrustumPoints[Frustum::FarTopRight] - cameraOffsetPos);

      verts[2].point.set(wsFrustumPoints[Frustum::FarBottomLeft] - cameraPos);
      //invCam.mulP(wsFrustumPoints[Frustum::FarBottomLeft], &verts[2].normal);
     // verts[2].texCoord.set(-1.0, -1.0);
     // verts[2].tangent.set(wsFrustumPoints[Frustum::FarBottomLeft] - cameraOffsetPos);

      verts[3].point.set(wsFrustumPoints[Frustum::FarBottomRight] - cameraPos);
     // invCam.mulP(wsFrustumPoints[Frustum::FarBottomRight], &verts[3].normal);
    //  verts[3].texCoord.set(1.0, -1.0);
    //  verts[3].tangent.set(wsFrustumPoints[Frustum::FarBottomRight] - cameraOffsetPos);
   }

   Point3F norms[4];
   {
      invCam.mulP(wsFrustumPoints[Frustum::FarTopLeft], &norms[0]);
      invCam.mulP(wsFrustumPoints[Frustum::FarTopRight], &norms[1]);
      invCam.mulP(wsFrustumPoints[Frustum::FarBottomLeft], &norms[2]);
      invCam.mulP(wsFrustumPoints[Frustum::FarBottomRight], &norms[3]);
   }

   mFarFrustumQuadVerts.set(GFX, 4);
   dMemcpy(mFarFrustumQuadVerts.lock(), verts, sizeof(verts));
   mFarFrustumQuadVerts.unlock();

   PlaneF farPlane(wsFrustumPoints[Frustum::FarBottomLeft], wsFrustumPoints[Frustum::FarTopLeft], wsFrustumPoints[Frustum::FarTopRight]);
   PlaneF vsFarPlane(norms[0], norms[1], norms[2]);


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

   ProbeManager::ReflectionProbeArrayMaterialInfo* reflProbeArrayMat = PROBEMGR->getReflectProbeArrayMaterial();

   if (reflProbeArrayMat != nullptr && reflProbeArrayMat->matInstance != nullptr)
   {
      reflProbeArrayMat->setViewParameters(frustum.getNearDist(),
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

   NamedTexTargetRef sceneColorTargetRef = NamedTexTarget::find("AL_FormatToken");
   if (sceneColorTargetRef.isNull())
      return;

   GFXTextureTargetRef probeLightingTargetRef = GFX->allocRenderToTextureTarget();

   if (probeLightingTargetRef.isNull())
      return;

   //Do a quick pass to update our probes if they're dirty
   PROBEMGR->updateDirtyProbes();

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

   ProbeManager::SkylightMaterialInfo* skylightMat = PROBEMGR->getSkylightMaterial();
   ProbeManager::ReflectProbeMaterialInfo* reflProbeMat = PROBEMGR->getReflectProbeMaterial();

   /*for (U32 i = 0; i < ProbeRenderInst::all.size(); i++)
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

	   if (curEntry->mIsSkylight)
	   {
		   //Setup
		   MatrixF probeTrans = curEntry->getTransform();

		   // Set geometry
		   GFX->setVertexBuffer(curEntry->vertBuffer);
		   GFX->setPrimitiveBuffer(curEntry->primBuffer);
		   probeTrans.scale(10); //force it to be big enough to surround the camera
		   sgData.objTrans = &probeTrans;
		   skylightMat->setProbeParameters(curEntry, state, worldToCameraXfm);

		   while (skylightMat->matInstance->setupPass(state, sgData))
		   {
			   // Set transforms
			   matrixSet.setWorld(*sgData.objTrans);
			   skylightMat->matInstance->setTransforms(matrixSet, state);
			   skylightMat->matInstance->setSceneInfo(state, sgData);

			   GFX->drawPrimitive(GFXTriangleList, 0, curEntry->numPrims);
		   }
	   }
   }*/

   //Array rendering
   static U32 MAXPROBECOUNT = 50;

   U32 probeCount = PROBEMGR->mRegisteredProbes.size();

   if (probeCount != 0)
   {
      AlignedArray<Point3F> probePositions(MAXPROBECOUNT, sizeof(Point3F));
      dMemset(probePositions.getBuffer(), 0, probePositions.getBufferSize());

      if (reflProbeMat && reflProbeMat->matInstance)
      {
         MaterialParameters *matParams = reflProbeMat->matInstance->getMaterialParameters();

         MaterialParameterHandle *numProbesSC = reflProbeMat->matInstance->getMaterialParameterHandle("$numProbes");
         matParams->setSafe(numProbesSC, (float)probeCount);

         //ProcessedShaderMaterial* processedMat = reflProbeMat->matInstance->getProcessedShaderMaterial();
         //GFXShaderConstBuffer* shaderConsts = processedMat->_getShaderConstBuffer(0);

         //ProbeShaderConstants *psc = PROBEMGR->getProbeShaderConstants(shaderConsts);

         MaterialParameterHandle *probePositionSC = reflProbeMat->matInstance->getMaterialParameterHandle("$inProbePosArray");

         U32 effectiveProbeCount = 0;

         for (U32 i = 0; i < probeCount; i++)
         {
            if (effectiveProbeCount >= MAXPROBECOUNT)
               break;

            ProbeRenderInst* curEntry = ProbeRenderInst::all[PROBEMGR->mRegisteredProbes[i]];

            /*if (!curEntry->mIsEnabled)
               continue;

            if (curEntry->numPrims == 0)
               continue;

            if (curEntry->mIsSkylight && (!skylightMat || !skylightMat->matInstance))
               continue;

            if (!curEntry->mIsSkylight && (!reflProbeMat || !reflProbeMat->matInstance))
               break;*/

               //Setup
            const Point3F &probePos = curEntry->getPosition();
            probePositions[i].x = probePos.x;
            probePositions[i].y = probePos.y;
            probePositions[i].z = probePos.z;

            Point3F test = probePositions[i];

            MatrixF probeTrans = curEntry->getTransform();

            if (!curEntry->mIsSkylight)
            {
               //if (curEntry->mProbeShapeType == ProbeRenderInst::Sphere)
              //    probeTrans.scale(curEntry->mRadius * 1.01f);

               sgData.objTrans = &probeTrans;

               reflProbeMat->setProbeParameters(curEntry, state, worldToCameraXfm);
            }

            effectiveProbeCount++;
         }

         if (effectiveProbeCount != 0)
         {
            Con::printf("Probe aligned position count: %i", probeCount);

            for (U32 p = 0; p < probeCount; p++)
            {
               Point3F prb = probePositions[p];

               Con::printf("Probe %i aligned position is: %g %g %g", p, prb.x, prb.y, prb.z);

               bool tasadfh = true;
            }

            matParams->set(probePositionSC, probePositions);

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
      }
   }
   //
   //
   /*ProbeManager::ReflectionProbeArrayMaterialInfo* reflProbeArrayMat = PROBEMGR->getReflectProbeArrayMaterial();

   for (U32 i = 0; i < ProbeRenderInst::all.size(); i++)
   {
      if (i > 0)
         return;

      ProbeRenderInst* curEntry = ProbeRenderInst::all[i];

      if (!reflProbeArrayMat || !reflProbeArrayMat->matInstance)
         break;

      //Setup
      //MatrixF probeTrans = curEntry->getTransform();

      //if (!curEntry->mIsSkylight)
      {
         //if (curEntry->mProbeShapeType == ProbeRenderInst::Sphere)
         //   probeTrans.scale(curEntry->mRadius * 1.01f);

         //sgData.objTrans = &state-;

         reflProbeArrayMat->setProbeParameters(curEntry, state, worldToCameraXfm);

         // Set geometry
         GFX->setVertexBuffer(mFarFrustumQuadVerts);
         GFX->setPrimitiveBuffer(NULL);
         while (reflProbeArrayMat->matInstance->setupPass(state, sgData))
         {
            // Set transforms
            //matrixSet.setWorld(*sgData.objTrans);
            reflProbeArrayMat->matInstance->setTransforms(matrixSet, state);
            reflProbeArrayMat->matInstance->setSceneInfo(state, sgData);

            GFX->drawPrimitive(GFXTriangleStrip, 0, 2);
         }
      }
   }*/
   //
   //

   GFX->popActiveRenderTarget();

   //PROBEMGR->unregisterAllProbes();
   PROBEMGR->mRegisteredProbes.clear();

   PROFILE_END();

   GFX->setVertexBuffer(NULL);
   GFX->setPrimitiveBuffer(NULL);

   // Fire off a signal to let others know that light-bin rendering is ending now
   //getRenderSignal().trigger(state, this);
}