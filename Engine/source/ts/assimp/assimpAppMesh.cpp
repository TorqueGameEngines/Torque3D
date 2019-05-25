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
#include "ts/collada/colladaExtensions.h"
#include "ts/assimp/assimpAppMesh.h"
#include "ts/assimp/assimpAppNode.h"

// assimp include files. 
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/types.h>

bool AssimpAppMesh::fixedSizeEnabled = false;
S32 AssimpAppMesh::fixedSize = 2;

//------------------------------------------------------------------------------

AssimpAppMesh::AssimpAppMesh(const struct aiMesh* mesh, AssimpAppNode* node)
   : mMeshData(mesh), appNode(node)
{
   Con::printf("[ASSIMP] Mesh Created: %s", getName());

   // See if it's a skinned mesh
   mIsSkinMesh = false;
   for (U32 b = 0; b < mesh->mNumBones; b++)
      if (mMeshData->mBones[b]->mNumWeights > 0)
      {
         mIsSkinMesh = true;
         break;
      }
}

const char* AssimpAppMesh::getName(bool allowFixed)
{
   // Some exporters add a 'PIVOT' or unnamed node between the mesh and the
   // actual object node. Detect this and return the object node name instead
   // of the pivot node.
   const char* nodeName = appNode->getName();
   if ( dStrEqual(nodeName, "null") || dStrEndsWith(nodeName, "PIVOT") )
      nodeName = appNode->getParentName();

   // If all geometry is being fixed to the same size, append the size
   // to the name
   return allowFixed && fixedSizeEnabled ? avar("%s %d", nodeName, fixedSize) : nodeName;
}

MatrixF AssimpAppMesh::getMeshTransform(F32 time)
{
   return appNode->getNodeTransform(time);
}

void AssimpAppMesh::lockMesh(F32 t, const MatrixF& objOffset)
{
   // After this function, the following are expected to be populated:
   //     points, normals, uvs, primitives, indices
   // There is also colors and uv2s but those don't seem to be required.
   points.reserve(mMeshData->mNumVertices);
   uvs.reserve(mMeshData->mNumVertices);
   normals.reserve(mMeshData->mNumVertices);

   bool flipNormals = ColladaUtils::getOptions().invertNormals;

   bool noUVFound = false;
   for (U32 i = 0; i<mMeshData->mNumVertices; i++)
   {
      // Points and Normals
      aiVector3D pt = mMeshData->mVertices[i];
      aiVector3D nrm;
      if (mMeshData->HasNormals())
         nrm = mMeshData->mNormals[i];
      else
         nrm.Set(0, 0, 0);

      Point3F tmpVert;
      Point3F tmpNormal;

      tmpVert = Point3F(pt.x, pt.y, pt.z);
      tmpNormal = Point3F(nrm.x, nrm.y, nrm.z);
      if (flipNormals)
         tmpNormal *= -1.0f;

      objOffset.mulP(tmpVert);

      points.push_back(tmpVert);

      if (mMeshData->HasTextureCoords(0))
      {
         uvs.push_back(Point2F(mMeshData->mTextureCoords[0][i].x, mMeshData->mTextureCoords[0][i].y));
      }
      else
      {
         // I don't know if there's any solution to this issue.
         // If it's not mapped, it's not mapped.
         noUVFound = true;
         uvs.push_back(Point2F(1, 1));
      }

      // UV2s
      if (mMeshData->HasTextureCoords(1))
      {
         uv2s.push_back(Point2F(mMeshData->mTextureCoords[1][i].x, mMeshData->mTextureCoords[1][i].y));
      }

      // Vertex Colors
      if (mMeshData->HasVertexColors(0))
      {
         LinearColorF vColor(mMeshData->mColors[0][i].r,
            mMeshData->mColors[0][i].g,
            mMeshData->mColors[0][i].b,
            mMeshData->mColors[0][i].a);
         colors.push_back(vColor.toColorI());
      }

      //uvs.push_back(mModel->mVerts[i].texcoord);
      normals.push_back(tmpNormal);
      //edgeVerts.push_back(mModel->mVerts[i].edge);
   }

   U32 numFaces = mMeshData->mNumFaces;
   //primitives.reserve(numFaces);

   //Fetch the number of indices
   U32 indicesCount = 0;
   for (U32 i = 0; i < numFaces; i++)
   {
      indicesCount += mMeshData->mFaces[i].mNumIndices;
   }

   indices.reserve(indicesCount);

   // Create TSMesh primitive
   primitives.increment();
   TSDrawPrimitive& primitive = primitives.last();
   primitive.start = 0;
   primitive.matIndex = (TSDrawPrimitive::Triangles | TSDrawPrimitive::Indexed) | (S32)mMeshData->mMaterialIndex;
   primitive.numElements = indicesCount;

   for ( U32 n = 0; n < mMeshData->mNumFaces; ++n)
   {
      const struct aiFace* face = &mMeshData->mFaces[n];
      if ( face->mNumIndices == 3 )
      {
         U32 indexCount = face->mNumIndices;
         for (U32 ind = 0; ind < indexCount; ind++)
         {
            U32 index = face->mIndices[ind];
            indices.push_back(index);
         }
      } 
      else 
      {
         Con::printf("[ASSIMP] Non-Triangle Face Found. Indices: %d", face->mNumIndices);
      }
   }

   U32 boneCount = mMeshData->mNumBones;
   bones.setSize(boneCount);

   // Count the total number of weights for all of the bones.
   U32 totalWeights = 0;
   U32 nonZeroWeights = 0;
   for (U32 b = 0; b < boneCount; b++)
      totalWeights += mMeshData->mBones[b]->mNumWeights;

   // Assimp gives weights sorted by bone index. We need them in vertex order.
   Vector<F32> tmpWeight;
   Vector<S32> tmpBoneIndex;
   Vector<S32> tmpVertexIndex;
   tmpWeight.setSize(totalWeights);
   tmpBoneIndex.setSize(totalWeights);
   tmpVertexIndex.setSize(totalWeights);

   for (U32 b = 0; b < boneCount; b++)
   {
      String name = mMeshData->mBones[b]->mName.C_Str();
      aiNode* nodePtr = AssimpAppNode::findChildNodeByName(mMeshData->mBones[b]->mName.C_Str(), appNode->mScene->mRootNode);
      if (!nodePtr)
         bones[b] = new AssimpAppNode(appNode->mScene, appNode->mNode);
      else
         bones[b] = new AssimpAppNode(appNode->mScene, nodePtr);

      MatrixF boneTransform;
      AssimpAppNode::assimpToTorqueMat(mMeshData->mBones[b]->mOffsetMatrix, boneTransform);
      Point3F boneScale = boneTransform.getScale();
      Point3F bonePos = boneTransform.getPosition();
      if (boneScale != Point3F::One && ColladaUtils::getOptions().ignoreNodeScale)
      {
         Point3F scaleMult = Point3F::One / boneScale;
         boneTransform.scale(scaleMult);
         bonePos /= scaleMult;
      }

      bonePos *= ColladaUtils::getOptions().unit;
      boneTransform.setPosition(bonePos);

      initialTransforms.push_back(boneTransform);

      //Weights
      U32 numWeights = mMeshData->mBones[b]->mNumWeights;

      for (U32 w = 0; w < numWeights; ++w)
      {
         aiVertexWeight* aiWeight = &mMeshData->mBones[b]->mWeights[w];

         if (aiWeight->mWeight > 0.0f)
         {
            tmpWeight[nonZeroWeights] = aiWeight->mWeight;
            tmpVertexIndex[nonZeroWeights] = aiWeight->mVertexId;
            tmpBoneIndex[nonZeroWeights] = b;
            nonZeroWeights++;
         }
      }
   }

   weight.setSize(nonZeroWeights);
   vertexIndex.setSize(nonZeroWeights);
   boneIndex.setSize(nonZeroWeights);

   // Copy the weights to our vectors in vertex order and
   // normalize vertex weights (force weights for each vert to sum to 1)
   U32 nextWeight = 0;
   for (U32 i = 0; i < mMeshData->mNumVertices; ++i)
   {
      U32 vertStart = nextWeight;
      F32 invTotalWeight = 0;
      for (U32 ind = 0; ind < nonZeroWeights; ++ind)
      {
         if (tmpVertexIndex[ind] == i)
         {
            weight[nextWeight] = tmpWeight[ind];
            invTotalWeight += tmpWeight[ind];
            vertexIndex[nextWeight] = tmpVertexIndex[ind];
            boneIndex[nextWeight] = tmpBoneIndex[ind];
            nextWeight++;
         }
      }

      // Now normalize the vertex weights
      if (invTotalWeight > 0.0)
      {
         invTotalWeight = 1.0f / invTotalWeight;
         for (U32 ind = vertStart; ind < nextWeight; ++ind)
            weight[ind] *= invTotalWeight;
      }
   }

   if ( noUVFound )
      Con::warnf("[ASSIMP] No UV Data for mesh.");
}

void AssimpAppMesh::lookupSkinData()
{  // This function is intentionally left blank. The skin data - bones, weights and indexes are
   // processed in lockMesh() with the rest of the mesh data.
}

F32 AssimpAppMesh::getVisValue(F32 t)
{
   return 1.0f;
}