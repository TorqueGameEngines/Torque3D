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
   const ProbeRenderInst* pReflectProbeA = static_cast<ProbeRenderInst*>(((RenderBinManager::MainSortElem*)(a))->inst);
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
	   return -1;
   return  0;
}

RenderProbeMgr::RenderProbeMgr()
: RenderBinManager(RenderPassManager::RIT_Probes, 1.0f, 1.0f)
{
   mReflectProbeMaterial = nullptr;
   mSkylightMaterial = nullptr;
}

RenderProbeMgr::RenderProbeMgr(RenderInstType riType, F32 renderOrder, F32 processAddOrder)
 : RenderBinManager(riType, renderOrder, processAddOrder)
{  
   mReflectProbeMaterial = nullptr;
   mSkylightMaterial = nullptr;
}

void RenderProbeMgr::initPersistFields()
{
   Parent::initPersistFields();
}

void RenderProbeMgr::addElement(RenderInst *inst)
{
   // If this instance is translucent handle it in RenderTranslucentMgr
   if (inst->translucentSort)
      return;

   //AssertFatal(inst->defaultKey != 0, "RenderMeshMgr::addElement() - Got null sort key... did you forget to set it?");

   internalAddElement(inst);

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
   }
}

//remove
//Con::setIntVariable("lightMetrics::activeReflectionProbes", mReflectProbeBin.size());
//Con::setIntVariable("lightMetrics::culledReflectProbes", 0/*mNumLightsCulled*/);
//

GFXVertexBufferHandle<GFXVertexPC> RenderProbeMgr::getSphereMesh(U32 &outNumPrimitives, GFXPrimitiveBufferHandle &outPrimitives)
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

void RenderProbeMgr::addSkylightProbe(ProbeRenderInst *probeInfo)
{
   probeInfo->vertBuffer = getSphereMesh(probeInfo->numPrims, probeInfo->primBuffer);

   if (!mSkylightMaterial)
      mSkylightMaterial = _getSkylightMaterial();
}

void RenderProbeMgr::addSphereReflectionProbe(ProbeRenderInst *probeInfo)
{
   probeInfo->vertBuffer = getSphereMesh(probeInfo->numPrims, probeInfo->primBuffer);

   if (!mReflectProbeMaterial)
      mReflectProbeMaterial = _getReflectProbeMaterial();
}

void RenderProbeMgr::addConvexReflectionProbe(ProbeRenderInst *probeInfo)
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
      mReflectProbeMaterial = _getReflectProbeMaterial();
   //

  // mReflectProbeBin.push_back(pEntry);
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

   MatrixSet &matrixSet = getRenderPass()->getMatrixSet();
   matrixSet.restoreSceneViewProjection();

   const MatrixF &worldToCameraXfm = matrixSet.getWorldToCamera();

   MatrixF inverseViewMatrix = worldToCameraXfm;
   //inverseViewMatrix.fullInverse();
   //inverseViewMatrix.transpose();

   //inverseViewMatrix = MatrixF::Identity;

   // Parameters calculated, assign them to the materials
   if (mSkylightMaterial != nullptr && mSkylightMaterial->matInstance != nullptr)
   {
      mSkylightMaterial->setViewParameters(frustum.getNearDist(),
         frustum.getFarDist(),
         frustum.getPosition(),
         farPlane,
         vsFarPlane, inverseViewMatrix);
   }

   if (mReflectProbeMaterial != nullptr && mReflectProbeMaterial->matInstance != nullptr)
   {
      mReflectProbeMaterial->setViewParameters(frustum.getNearDist(),
         frustum.getFarDist(),
         frustum.getPosition(),
         farPlane,
         vsFarPlane, inverseViewMatrix);
   }
}

//-----------------------------------------------------------------------------
// render objects
//-----------------------------------------------------------------------------
void RenderProbeMgr::render( SceneRenderState *state )
{
   PROFILE_SCOPE(RenderProbeMgr_render);

   // Early out if nothing to draw.
   if(!mElementList.size())
      return;

   GFXTransformSaver saver;

   NamedTexTargetRef diffuseLightingTarget = NamedTexTarget::find("diffuseLighting");

   if (diffuseLightingTarget.isNull())
      return;

   NamedTexTargetRef specularLightingTarget = NamedTexTarget::find("specularLighting");

   if (specularLightingTarget.isNull())
      return;

   GFXTextureTargetRef probeLightingTargetRef = GFX->allocRenderToTextureTarget();

   if (probeLightingTargetRef.isNull())
      return;

   probeLightingTargetRef->attachTexture(GFXTextureTarget::Color0, diffuseLightingTarget->getTexture());
   probeLightingTargetRef->attachTexture(GFXTextureTarget::Color1, specularLightingTarget->getTexture());

   GFX->pushActiveRenderTarget();
   GFX->setActiveRenderTarget(probeLightingTargetRef);

   GFX->setViewport(diffuseLightingTarget->getViewport());
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
   dQsort(mElementList.address(), mElementList.size(), sizeof(const MainSortElem), AscendingReflectProbeInfluence);

   //Specular
   PROFILE_START(RenderProbeManager_ReflectProbeRender);

   for (U32 i = 0; i<mElementList.size(); i++)
   {
      ProbeRenderInst *curEntry = static_cast<ProbeRenderInst*>(mElementList[i].inst);

      if (curEntry->numPrims == 0)
         continue;

      if (curEntry->mIsSkylight && (!mSkylightMaterial || !mSkylightMaterial->matInstance))
         continue;

      if (!curEntry->mIsSkylight && (!mReflectProbeMaterial || !mReflectProbeMaterial->matInstance))
         break;

      //Setup
      MatrixF probeTrans = curEntry->getTransform();

      if (!curEntry->mIsSkylight)
      {
         if (curEntry->mProbeShapeType == ProbeInfo::Sphere)
            probeTrans.scale(curEntry->mRadius * 1.01f);
      }
      else
      {
         probeTrans.scale(10); //force it to be big enough to surround the camera
      }

      sgData.objTrans = &probeTrans;

      if(curEntry->mIsSkylight)
         mSkylightMaterial->setSkylightParameters(curEntry, state, worldToCameraXfm);
      else
         mReflectProbeMaterial->setProbeParameters(curEntry, state, worldToCameraXfm);

      // Set geometry
      GFX->setVertexBuffer(curEntry->vertBuffer);
      GFX->setPrimitiveBuffer(curEntry->primBuffer);

      if (curEntry->mIsSkylight)
      {
         while (mSkylightMaterial->matInstance->setupPass(state, sgData))
         {
            // Set transforms
            matrixSet.setWorld(*sgData.objTrans);
            mSkylightMaterial->matInstance->setTransforms(matrixSet, state);
            mSkylightMaterial->matInstance->setSceneInfo(state, sgData);

            GFX->drawPrimitive(GFXTriangleList, 0, curEntry->numPrims);
         }
      }
      else
      {
         while (mReflectProbeMaterial->matInstance->setupPass(state, sgData))
         {
            // Set transforms
            matrixSet.setWorld(*sgData.objTrans);
            mReflectProbeMaterial->matInstance->setTransforms(matrixSet, state);
            mReflectProbeMaterial->matInstance->setSceneInfo(state, sgData);

            GFX->drawPrimitive(GFXTriangleList, 0, curEntry->numPrims);
         }
      }
   }

   probeLightingTargetRef->resolve();
   GFX->popActiveRenderTarget();

   PROBEMGR->unregisterAllProbes();
   PROFILE_END();

   GFX->setVertexBuffer(NULL);
   GFX->setPrimitiveBuffer(NULL);

   // Fire off a signal to let others know that light-bin rendering is ending now
   //getRenderSignal().trigger(state, this);
}

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
   invViewMat(NULL)
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

   for(U32 i=0; i < 9; i++)
      shTerms[i] = matInstance->getMaterialParameterHandle(String::ToString("$SHTerms%d",i));

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

   if(probeInfo->mCubemap->isValid())
      matParams->setSafe(cubeMips, mPow(probeInfo->mCubemap->getPointer()->getMipMapLevels(),2.0f));
   else
      matParams->setSafe(cubeMips, F32(0.0));

   matParams->setSafe(eyePosWorld, renderState->getCameraPosition());
   matParams->setSafe(bbMin, probeInfo->mBounds.minExtents);
   matParams->setSafe(bbMax, probeInfo->mBounds.maxExtents);

   matParams->setSafe(useSphereMode, probeInfo->mProbeShapeType == ProbeInfo::Sphere ? 1.0f : 0.0f);
   
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
}


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
	   desc.setBlend(true, GFXBlendSrcAlpha, GFXBlendOne);
	   mProjectionState = GFX->createStateBlock(desc);
   }
   // Now override stateblock with our own
   GFX->setStateBlock(mProjectionState);

   return bRetVal;
}

RenderProbeMgr::ReflectProbeMaterialInfo* RenderProbeMgr::_getReflectProbeMaterial()
{
   PROFILE_SCOPE(AdvancedLightBinManager_getReflectProbeMaterial);

   //ReflectProbeMaterialInfo *info = NULL;

   if (!mReflectProbeMaterial)

      // Now create the material info object.
      mReflectProbeMaterial = new ReflectProbeMaterialInfo("ReflectionProbeMaterial",
         getGFXVertexFormat<GFXVertexPC>());

   return mReflectProbeMaterial;
}

//
RenderProbeMgr::SkylightMaterialInfo::SkylightMaterialInfo(const String &matName,
   const GFXVertexFormat *vertexFormat)
   : matInstance(NULL),
   zNearFarInvNearFar(NULL),
   farPlane(NULL),
   vsFarPlane(NULL),
   negFarPlaneDotEye(NULL),
   invViewMat(NULL)
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

RenderProbeMgr::SkylightMaterialInfo::~SkylightMaterialInfo()
{
   SAFE_DELETE(matInstance);
}

void RenderProbeMgr::SkylightMaterialInfo::setViewParameters(const F32 _zNear,
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

void RenderProbeMgr::SkylightMaterialInfo::setSkylightParameters(const ProbeRenderInst *probeInfo, const SceneRenderState* renderState, const MatrixF &worldViewOnly)
{
   //Set up the params
   MaterialParameters *matParams = matInstance->getMaterialParameters();

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

   matParams->setSafe(eyePosWorld, renderState->getCameraPosition());

   for (U32 i = 0; i < 9; i++)
   {
      matParams->setSafe(shTerms[i], probeInfo->mSHTerms[i]);
   }

   for (U32 i = 0; i < 5; i++)
   {
      matParams->setSafe(shConsts[i], probeInfo->mSHConstants[i]);
   }
}


bool SkylightMatInstance::init(const FeatureSet &features, const GFXVertexFormat *vertexFormat)
{
   bool success = Parent::init(features, vertexFormat);

   // If the initialization failed don't continue.
   if (!success || !mProcessedMaterial || mProcessedMaterial->getNumPasses() == 0)
      return false;

   return true;
}

bool SkylightMatInstance::setupPass(SceneRenderState *state, const SceneData &sgData)
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

RenderProbeMgr::SkylightMaterialInfo* RenderProbeMgr::_getSkylightMaterial()
{
   PROFILE_SCOPE(AdvancedLightBinManager_getSkylightMaterial);

   //ReflectProbeMaterialInfo *info = NULL;

   if (!mSkylightMaterial)

      // Now create the material info object.
      mSkylightMaterial = new SkylightMaterialInfo("SklyightMaterial",
         getGFXVertexFormat<GFXVertexPC>());

   return mSkylightMaterial;
}

//
//
ProbeRenderInst::ProbeRenderInst()
   : mTransform(true),
   mAmbient(0.0f, 0.0f, 0.0f, 1.0f),
   mPriority(1.0f),
   mScore(0.0f),
   mDebugRender(false),
   mCubemap(NULL),
   mRadius(1.0f),
   mIntensity(1.0f)
{
}

ProbeRenderInst::~ProbeRenderInst()
{
   SAFE_DELETE(mCubemap);
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
   mScore = probeInfo->mScore;
   mIsSkylight = probeInfo->mIsSkylight;

   for (U32 i = 0; i < 9; i++)
   {
      mSHTerms[i] = probeInfo->mSHTerms[i];
   }

   for (U32 i = 0; i < 5; i++)
   {
      mSHConstants[i] = probeInfo->mSHConstants[i];
   }
}

void ProbeRenderInst::set(const ProbeInfo *probeInfo)
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
   mScore = probeInfo->mScore;
   mIsSkylight = probeInfo->mIsSkylight;

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
