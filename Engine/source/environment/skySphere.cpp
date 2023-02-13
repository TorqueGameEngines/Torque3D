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
#include "environment/skySphere.h"

#include "console/consoleTypes.h"
#include "console/engineAPI.h"
#include "scene/sceneRenderState.h"
#include "renderInstance/renderPassManager.h"
#include "gfx/primBuilder.h"
#include "gfx/gfxTransformSaver.h"
#include "core/stream/fileStream.h"
#include "core/stream/bitStream.h"
#include "materials/materialManager.h"
#include "materials/materialFeatureTypes.h"
#include "materials/sceneData.h"
#include "T3D/gameFunctions.h"
#include "renderInstance/renderBinManager.h"
#include "materials/processedMaterial.h"
#include "gfx/gfxDebugEvent.h"
#include "math/util/matrixSet.h"

IMPLEMENT_CO_NETOBJECT_V1(SkySphere);

ConsoleDocClass(SkySphere,
   "@brief Represents the sky with an artist-created spherical map.\n\n"

   "SkySphere is not a directional light and should be used in conjunction with a Sun object.\n\n"

   "@ingroup Atmosphere"
);

SkySphere::SkySphere()
{
   mTypeMask |= EnvironmentObjectType | StaticObjectType;
   mNetFlags.set(Ghostable | ScopeAlways);

   INIT_ASSET(Material);
   mMatInstance = NULL;

   mIsVBDirty = false;
   mPrimCount = 0;
   mFogBandHeight = 0;
   mFogPrimCount = 0;

   mMatrixSet = reinterpret_cast<MatrixSet*>(dMalloc_aligned(sizeof(MatrixSet), 16));
   constructInPlace(mMatrixSet);

   mFogBandMat = NULL;
   mFogBandMatInst = NULL;
}

SkySphere::~SkySphere()
{
   dFree_aligned(mMatrixSet);

   if (mMatInstance)
      SAFE_DELETE(mMatInstance);

   SAFE_DELETE(mFogBandMatInst);

   if (mFogBandMat)
   {
      mFogBandMat->deleteObject();
      mFogBandMat = NULL;
   }
}

bool SkySphere::onAdd()
{
   if (!Parent::onAdd())
      return false;

   setGlobalBounds();
   resetWorldBox();

   addToScene();

   if (isClientObject())
   {
      _initRender();
      _updateMaterial();
   }

   return true;
}

void SkySphere::onRemove()
{
   removeFromScene();
   Parent::onRemove();
}

void SkySphere::initPersistFields()
{
   docsURL;
   addGroup("Sky Sphere");

   INITPERSISTFIELD_MATERIALASSET(Material, SkySphere, "The name of a cubemap material for the sky box.");

   addField("fogBandHeight", TypeF32, Offset(mFogBandHeight, SkySphere),
      "The height (0-1) of the fog band from the horizon to the top of the SkySphere.");

   endGroup("Sky Sphere");

   Parent::initPersistFields();
}

void SkySphere::inspectPostApply()
{
   Parent::inspectPostApply();
   _updateMaterial();
}

U32 SkySphere::packUpdate(NetConnection* conn, U32 mask, BitStream* stream)
{
   U32 retMask = Parent::packUpdate(conn, mask, stream);

   PACK_ASSET(conn, Material);

   stream->write(mFogBandHeight);

   return retMask;
}

void SkySphere::unpackUpdate(NetConnection* conn, BitStream* stream)
{
   Parent::unpackUpdate(conn, stream);

   StringTableEntry oldMatName = getMaterial();
   UNPACK_ASSET(conn, Material);
   if (oldMatName != getMaterial())
   {
      _updateMaterial();
   }

   F32 bandHeight = 0;
   stream->read(&bandHeight);

   // If this flag has changed
   // we need to update the vertex buffer.
   if ( bandHeight != mFogBandHeight)
   {
      mFogBandHeight = bandHeight;
      mIsVBDirty = true;
      _initRender();
   }
}

void SkySphere::prepRenderImage(SceneRenderState* state)
{
   PROFILE_SCOPE(SkySphere_prepRenderImage);

   if (state->isShadowPass() ||
      mVB.isNull() ||
      mFogBandVB.isNull() ||
      !mMatInstance)
      return;

   mMatrixSet->setSceneView(GFX->getWorldMatrix());
   mMatrixSet->setSceneProjection(GFX->getProjectionMatrix());

   ObjectRenderInst* ri = state->getRenderPass()->allocInst<ObjectRenderInst>();
   ri->renderDelegate.bind(this, &SkySphere::_renderObject);
   ri->type = RenderPassManager::RIT_Sky;
   ri->defaultKey = 9;
   ri->defaultKey2 = 0;
   state->getRenderPass()->addInst(ri);
}

void SkySphere::_renderObject(ObjectRenderInst* ri, SceneRenderState* state, BaseMatInstance* mi)
{
   GFXDEBUGEVENT_SCOPE(SkySphere_RenderObject, ColorI::WHITE);

   GFXTransformSaver saver;
   GFX->setVertexBuffer(mVB);

   MatrixF worldMat = MatrixF::Identity;
   worldMat.setPosition(Point3F(
      state->getCameraPosition().x,
      state->getCameraPosition().y,
      state->getCameraPosition().z));

   SceneData sgData;
   sgData.init(state);
   sgData.objTrans = &worldMat;

   mMatrixSet->restoreSceneViewProjection();
   mMatrixSet->setWorld(worldMat);
   if (state->isReflectPass())
      mMatrixSet->setProjection(state->getSceneManager()->getNonClipProjection());

   while (mMatInstance->setupPass(state, sgData))
   {
      mMatInstance->setTransforms(*mMatrixSet, state);
      mMatInstance->setSceneInfo(state, sgData);

      GFX->drawPrimitive(GFXTriangleList, 0, mPrimCount);
   }

   // Draw render band.
   if (mFogBandHeight > 0 && mFogBandMatInst)
   {
      const FogData& fog = state->getSceneManager()->getFogData();
      if (mLastFogColor != fog.color)
      {
         mLastFogColor = fog.color;
         _initRender();
      }

      // Just need it to follow the camera... no rotation.
      MatrixF camPosMat(MatrixF::Identity);
      camPosMat.setPosition(worldMat.getPosition());
      sgData.objTrans = &camPosMat;
      mMatrixSet->setWorld(*sgData.objTrans);

      while (mFogBandMatInst->setupPass(state, sgData))
      {
         mFogBandMatInst->setTransforms(*mMatrixSet, state);
         mFogBandMatInst->setSceneInfo(state, sgData);

         GFX->setVertexBuffer(mFogBandVB);
         GFX->drawPrimitive(GFXTriangleList, 0, mFogPrimCount);
      }
   }
}

void SkySphere::clearVectors()
{
   tmpVertices.clear();
   finalFogVertex.clear();
   tempFogVertex.clear();
   colVec.clear();
   fogVerts.clear();
   vertsVec.clear();
   normsVec.clear();
   texCoordVec.clear();
   finalVertData.clear();
}

void SkySphere::addVertex(Point3F vert)
{
   vertsVec.push_back(vert.x);
   vertsVec.push_back(vert.y);
   vertsVec.push_back(vert.z);
}

void SkySphere::addNormal(Point3F nor)
{
   normsVec.push_back(nor.x);
   normsVec.push_back(nor.y);
   normsVec.push_back(nor.z);
}

void SkySphere::addTexcoord(F32 s, F32 t)
{
   texCoordVec.push_back(s);
   texCoordVec.push_back(t);
}

void SkySphere::addColor(ColorI col)
{
   colVec.push_back(col);
}

void SkySphere::BuildFinalVert()
{
   U32 count = vertsVec.size();
   U32 i, j;
   for (i = 0, j = 0; i < count; i += 3, j += 2)
   {
      FinalVertexData temp;
      temp.pos.set(Point3F(vertsVec[i], vertsVec[i + 1], vertsVec[i + 2]));
      temp.nor.set(Point3F(normsVec[i], normsVec[i + 1], normsVec[i + 2]));
      temp.s = texCoordVec[j];
      temp.t = texCoordVec[j+1];

      finalVertData.push_back(temp);
   }
}

void SkySphere::BuildFinalFogVert()
{
   U32 count = vertsVec.size();
   U32 i, j;
   for (i = 0, j = 0; i < count; i+=3, j++ )
   {
      FogVertex temp;
      temp.pos.set(Point3F(vertsVec[i], vertsVec[i + 1], vertsVec[i + 2]));
      temp.col = colVec[j];

      finalFogVertex.push_back(temp);
   }
}

void SkySphere::_initRender()
{
   U32 rings = 32;
   U32 height = 16;
   U32 radius = 1;

   F32 x, y, z, xy;                              // vertex position
   F32 nx, ny, nz, lengthInv = 1.0f / radius;       // normal
   F32 s, t;                                     // texCoord

   F32 ringStep = M_2PI / rings;
   F32 heightStep = M_PI / height; // M_HALFPI for dome.
   F32 ringAng, heightAng;

   //clear vecs
   clearVectors();

   for (U32 i = 0; i <= height; ++i)
   {
      heightAng = M_PI / 2 - (F32)i * heightStep;
      F32 xy = radius * mCos(heightAng);
      F32 z = radius * mSin(heightAng);

      for (U32 j = 0; j <= rings; ++j)
      {
         SphereVertex vert;
         ringAng = j * ringStep;
         x = xy * mCos(ringAng);
         y = xy * mSin(ringAng);
         vert.pos.set(Point3F(x,y,z));

         nx = x * lengthInv;
         ny = y * lengthInv;
         nz = z * lengthInv;
         vert.nor.set(Point3F(nx, ny, nz));

         s = (F32)j / rings;
         t = (F32)i / height;
         vert.s = s;
         vert.t = t;

         tmpVertices.push_back(vert);
      }
   }

   SphereVertex v1, v2, v3, v4;
   U32 vi1, vi2 = 0;

   for (U32 i = 0; i < height; ++i)
   {
      vi1 = i * (rings + 1);
      vi2 = (i + 1) * (rings + 1);

      for (U32 j = 0; j < rings; ++j, ++vi1, ++vi2)
      {
         v1 = tmpVertices[vi1];
         v2 = tmpVertices[vi2];
         v3 = tmpVertices[vi1 + 1];
         v4 = tmpVertices[vi2 + 1];

         // 1st = triangle.
         if (i == 0)
         {
            // verts for tri.
            addVertex(v1.pos);
            addVertex(v2.pos);
            addVertex(v4.pos);

            // texcoords for tri.
            addTexcoord(v1.s, v1.t);
            addTexcoord(v2.s, v2.t);
            addTexcoord(v4.s, v4.t);

            // normals for tri.
            addNormal(v1.nor);
            addNormal(v2.nor);
            addNormal(v4.nor);
         }
         else if (i == (height - 1))
         {
            // verts for tri.
            addVertex(v1.pos);
            addVertex(v2.pos);
            addVertex(v3.pos);

            // texcoords for tri.
            addTexcoord(v1.s, v1.t);
            addTexcoord(v2.s, v2.t);
            addTexcoord(v3.s, v3.t);

            // normals for quad.
            addNormal(v1.nor);
            addNormal(v2.nor);
            addNormal(v3.nor);
         }
         else
         {
            // verts for quad.
            addVertex(v1.pos);
            addVertex(v2.pos);
            addVertex(v3.pos);

            addVertex(v3.pos);
            addVertex(v4.pos);
            addVertex(v2.pos);

            // texcoords for quad.
            addTexcoord(v1.s, v1.t);
            addTexcoord(v2.s, v2.t);
            addTexcoord(v3.s, v3.t);

            addTexcoord(v3.s, v3.t);
            addTexcoord(v4.s, v4.t);
            addTexcoord(v2.s, v2.t);

            // normals for quad.
            addNormal(v1.nor);
            addNormal(v2.nor);
            addNormal(v3.nor);

            addNormal(v3.nor);
            addNormal(v4.nor);
            addNormal(v2.nor);
         }
      }
   }

   BuildFinalVert();

   GFXVertexPNT* tmpVerts = NULL;
   U32 vertCount = finalVertData.size();
   tmpVerts = new GFXVertexPNT[(vertCount)];
   mPrimCount = vertCount / 3;

   for (U32 i = 0; i < vertCount; i++)
   {
      tmpVerts[i].point.set(finalVertData[i].pos);
      tmpVerts[i].normal.set(finalVertData[i].nor);
      tmpVerts[i].texCoord.set(finalVertData[i].s, finalVertData[i].t);
   }

   if (mVB.isNull() || mIsVBDirty)
   {
      mVB.set(GFX, vertCount, GFXBufferTypeStatic);
      mIsVBDirty = false;
   }

   GFXVertexPNT* vertPtr = mVB.lock();
   if (!vertPtr)
   {
      delete[] tmpVerts;
      return;
   }

   dMemcpy(vertPtr, tmpVerts, sizeof(GFXVertexPNT) * vertCount);

   mVB.unlock();

   // Clean up temp verts.
   delete[] tmpVerts;

   // Grab the fog color.
   ColorI fogColor(mLastFogColor.red * 255, mLastFogColor.green * 255, mLastFogColor.blue * 255);
   ColorI fogColorAlpha(mLastFogColor.red * 255, mLastFogColor.green * 255, mLastFogColor.blue * 255, 0);

   clearVectors();

   U32 stepCount = 16;
   F32 cylStep = M_2PI / stepCount;
   F32 cylAngle;
   F32 cylRadius = 10;

   for (U32 i = 0; i <= stepCount; ++i)
   {
      cylAngle = (F32)i * cylStep;
      fogVerts.push_back(mCos(cylAngle));
      fogVerts.push_back(mSin(cylAngle));
   }

   for (U32 i = 0; i < 2; ++i)
   {
      for (U32 j = 0, k = 0; j <= stepCount; ++j, k += 2)
      {
         FogVertex temp;
         F32 ux = fogVerts[k];
         F32 uy = fogVerts[k+1];

         if (i > 0)
         {
            temp.pos.set(Point3F((ux * cylRadius), (uy * cylRadius), mFogBandHeight));
            temp.col = fogColorAlpha;
         }
         else
         {
            temp.pos.set(Point3F((ux * cylRadius), (uy * cylRadius), -mFogBandHeight));
            temp.col = fogColor;
         }

         tempFogVertex.push_back(temp);
      }
   }

   FogVertex f1, f2, f3, f4;
   U32 k1 = 0;
   U32 k2 = stepCount + 1;

   for (U32 i = 0; i < stepCount; ++i, ++k1, ++k2)
   {
      f1 = tempFogVertex[k1];
      f2 = tempFogVertex[k1 + 1];
      f3 = tempFogVertex[k2];
      f4 = tempFogVertex[k2 + 1];
      addVertex(f3.pos);
      addVertex(f2.pos);
      addVertex(f4.pos);
      addColor(f3.col);
      addColor(f2.col);
      addColor(f4.col);
      addVertex(f1.pos);
      addVertex(f2.pos);
      addVertex(f3.pos);
      addColor(f1.col);
      addColor(f2.col);
      addColor(f3.col);
   }

   BuildFinalFogVert();

   U32 fogVertCount = finalFogVertex.size();
   mFogPrimCount = fogVertCount / 3;

   if (mFogBandVB.isNull())
      mFogBandVB.set(GFX, fogVertCount, GFXBufferTypeStatic);

   GFXVertexPC* bandVertPtr = mFogBandVB.lock();
   if (!bandVertPtr) return;
      
   for (U32 i = 0; i < fogVertCount; i++)
   {
      bandVertPtr[i].point.set(finalFogVertex[i].pos);
      bandVertPtr[i].color.set(finalFogVertex[i].col);
   }

   mFogBandVB.unlock();

   SAFE_DELETE(mFogBandMatInst);
   if (mFogBandMat)
   {
      mFogBandMat->deleteObject();
      mFogBandMat = NULL;
   }

   // Setup the material for this imposter.
   mFogBandMat = MATMGR->allocateAndRegister(String::EmptyString);
   mFogBandMat->mAutoGenerated = true;
   mFogBandMat->mTranslucent = true;
   mFogBandMat->mVertColor[0] = true;
   mFogBandMat->mDoubleSided = true;
   mFogBandMat->mReceiveShadows[0] = false;

   FeatureSet features = MATMGR->getDefaultFeatures();
   features.addFeature(MFT_isBackground);
   mFogBandMatInst = mFogBandMat->createMatInstance();
   mFogBandMatInst->init(features, getGFXVertexFormat<GFXVertexPC>());
}

void SkySphere::onStaticModified(const char* slotName, const char* newValue)
{
   Parent::onStaticModified(slotName, newValue);

   if (dStricmp(slotName, "material") == 0)
      setMaskBits(0xFFFFFFFF);
}

void SkySphere::_initMaterial()
{
   if (mMatInstance)
      SAFE_DELETE(mMatInstance);

   if (mMaterial)
      mMatInstance = mMaterial->createMatInstance();
   else
      mMatInstance = MATMGR->createMatInstance("WarningMaterial");

   // We want to disable culling and z write.
   GFXStateBlockDesc desc;
   desc.setCullMode(GFXCullNone);
   desc.setBlend(true);
   desc.setZReadWrite(true, false);
   desc.zFunc = GFXCmpLessEqual;
   mMatInstance->addStateBlockDesc(desc);

   // Also disable lighting on the skysphere material by default.
   FeatureSet features = MATMGR->getDefaultFeatures();
   features.removeFeature(MFT_RTLighting);
   features.removeFeature(MFT_Visibility);
   features.removeFeature(MFT_ReflectionProbes);
   features.addFeature(MFT_isBackground);

   // Now initialize the material.
   mMatInstance->init(features, getGFXVertexFormat<GFXVertexPNT>());
}

void SkySphere::_updateMaterial()
{
   if (!getMaterialResource().isValid())
   {
      //If our materialDef isn't valid, try setting it
      _setMaterial(getMaterial());
   }

   if (getMaterialResource().isValid())
   {
      _initMaterial();
   }
}

BaseMatInstance* SkySphere::_getMaterialInstance()
{
   if (!mMaterial || !mMatInstance || mMatInstance->getMaterial() != mMaterial)
      _initMaterial();

   if (!mMatInstance)
      return NULL;

   return mMatInstance;
}

DefineEngineMethod(SkySphere, postApply, void, (), , "")
{
   object->inspectPostApply();
}
