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

//------------------------------------------------------------------------------

AssimpAppMesh::AssimpAppMesh(const struct aiMesh* mesh, AssimpAppNode* node)
   : mMeshData(mesh), appNode(node)
{
   Con::printf("[ASSIMP] Mesh Created: %s", getName());
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
   //return allowFixed && fixedSizeEnabled ? avar("%s %d", nodeName, fixedSize) : nodeName;
   return nodeName;
}

MatrixF AssimpAppMesh::getMeshTransform(F32 time)
{
   return appNode->getNodeTransform(time);
}

void AssimpAppMesh::lockMesh(F32 t, const MatrixF& objectOffset)
{
   // After this function, the following are expected to be populated:
   //     points, normals, uvs, primitives, indices
   // There is also colors and uv2s but those don't seem to be required.

   points.reserve(mMeshData->mNumVertices);
   uvs.reserve(mMeshData->mNumVertices);
   normals.reserve(mMeshData->mNumVertices);

   bool noUVFound = false;
   for (U32 i = 0; i<mMeshData->mNumVertices; i++)
   {
      // Points and Normals
      aiVector3D pt = mMeshData->mVertices[i];
      aiVector3D nrm = mMeshData->mNormals[i];

      Point3F tmpVert;
      Point3F tmpNormal;

      if (Con::getBoolVariable("$Assimp::SwapYZ", false))
      {
         tmpVert = Point3F(pt.x, pt.z, pt.y);
         tmpNormal = Point3F(nrm.x, nrm.z, nrm.y);
      }
      else
      {
         tmpVert = Point3F(pt.x, pt.y, pt.z);
         tmpNormal = Point3F(nrm.x, nrm.y, nrm.z);
      }

      //objectOffset.mulP(tmpVert);

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
   U32 primCount = 0;
   primitives.reserve(numFaces);

   //Fetch the number of indices
   U32 indicesCount = 0;
   for (U32 i = 0; i < numFaces; i++)
   {
      indicesCount += mMeshData->mFaces[i].mNumIndices;
   }

   indices.reserve(indicesCount);

   /*U32 idxCount = 0;

   for (U32 j = 0; j<mModel->mMaterials.size(); j++)
   {
      MikuModel::Material &mat = mModel->mMaterials[j];
      U32 nextIdxCount = idxCount + mat.numIndices;

      primitives.increment();

      TSDrawPrimitive& primitive = primitives.last();
      primitive.start = indices.size();
      primitive.matIndex = (TSDrawPrimitive::Triangles | TSDrawPrimitive::Indexed) | j;
      primitive.numElements = mat.numIndices;

      for (U32 i = idxCount; i<nextIdxCount; i++)
      {
         indices.push_back(mModel->mIndices[i]);
      }

      idxCount = nextIdxCount;
   }*/

   for ( U32 n = 0; n < mMeshData->mNumFaces; ++n)
   {
      const struct aiFace* face = &mMeshData->mFaces[n];
      if ( face->mNumIndices == 3 )
      {
         // Create TSMesh primitive
         primitives.increment();
         TSDrawPrimitive& primitive = primitives.last();
         primitive.start = indices.size();
         primitive.matIndex = (TSDrawPrimitive::Triangles | TSDrawPrimitive::Indexed) | (S32)mMeshData->mMaterialIndex;
         //primitive.numElements = face->mNumIndices;//3;
         primitive.numElements = 3;

         if (Con::getBoolVariable("$Assimp::FlipNormals", true))
         {
            U32 indexCount = face->mNumIndices;
            for (S32 ind = indexCount - 1; ind >= 0; ind--)
            {
               U32 index = face->mIndices[ind];
               indices.push_back(index);
            }
         }
         else
         {
            U32 indexCount = face->mNumIndices;
            for (U32 ind = 0; ind < indexCount; ind++)
            {
               U32 index = face->mIndices[ind];
               indices.push_back(index);
            }
         }

         // Load the indices in.
         //indices.push_back(face->mIndices[0]);
         //indices.push_back(face->mIndices[1]);
         //indices.push_back(face->mIndices[2]);
      } 
      else 
      {
         Con::printf("[ASSIMP] Non-Triangle Face Found. Indices: %d", face->mNumIndices);
      }
   }

   U32 boneCount = mMeshData->mNumBones;

   bones.setSize(boneCount);

   for (U32 b = 0; b < boneCount; b++)
   {
      String name = mMeshData->mBones[b]->mName.C_Str();

      MatrixF boneTransform;

      for (U32 m = 0; m < 16; ++m)
      {
         boneTransform[m] = *mMeshData->mBones[b]->mOffsetMatrix[m];
      }

      //initialTransforms.push_back(boneTransform);
      initialTransforms.push_back(MatrixF::Identity);

      //Weights
      U32 numWeights = mMeshData->mBones[b]->mNumWeights;

      weight.setSize(numWeights);
      vertexIndex.setSize(numWeights);

      for (U32 w = 0; w < numWeights; ++w)
      {
         aiVertexWeight* aiWeight = mMeshData->mBones[b]->mWeights;

         weight[w] = aiWeight->mWeight;
         vertexIndex[w] = aiWeight->mVertexId;
         boneIndex[w] = b;
         //vertWeight. = aiWeight->
      }
      //= mNumWeights
   }

   if ( noUVFound )
      Con::warnf("[ASSIMP] No UV Data for mesh.");
}

void AssimpAppMesh::lookupSkinData()
{

}

F32 AssimpAppMesh::getVisValue(F32 t)
{
   return 1.0f;
}