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
#include "ts/loader/appSequence.h"
#include "ts/assimp/assimpAppNode.h"
#include "ts/assimp/assimpAppMesh.h"

// assimp include files. 
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/types.h>

AssimpAppNode::AssimpAppNode(const struct aiScene* scene, const struct aiNode* node, AssimpAppNode* parent)
{
   mScene = scene;
   mNode = node;
   appParent = parent;

   mName = dStrdup(mNode->mName.C_Str());
   if ( dStrlen(mName) == 0 )
   {
      const char* defaultName = "null";
      mName = dStrdup(defaultName);
   }

   mParentName = dStrdup(parent ? parent->getName() : "ROOT");
   Con::printf("[ASSIMP] Node Created: %s", mName);
}

// Get all child nodes
void AssimpAppNode::buildChildList()
{
   if (!mNode)
   {
      mNode = mScene->mRootNode;
   }

   for (U32 n = 0; n < mNode->mNumChildren; ++n) {
      mChildNodes.push_back(new AssimpAppNode(mScene, mNode->mChildren[n], this));
   }
}

// Get all geometry attached to this node
void AssimpAppNode::buildMeshList()
{
   for (U32 n = 0; n < mNode->mNumMeshes; ++n)
   {
      const struct aiMesh* mesh = mScene->mMeshes[mNode->mMeshes[n]];
      mMeshes.push_back(new AssimpAppMesh(mesh, this));
   }
}

MatrixF AssimpAppNode::getTransform(F32 time)
{
   // Translate from assimp matrix to torque matrix.
   // They're both row major, I wish I could just cast
   // but that doesn't seem to be an option.

   // Note: this should be cached, it doesn't change
   //       at this level. This is base transform.

   // Y and Z and optionally swapped.

   MatrixF mat(false);
   mat.setRow(0, Point4F((F32)mNode->mTransformation.a1,
       (F32)mNode->mTransformation.a3,
       (F32)mNode->mTransformation.a2,
       (F32)mNode->mTransformation.a4)
   );

   // Check for Y Z Swap
   if ( Con::getBoolVariable("$Assimp::SwapYZ", false) )
   {
      mat.setRow(1, Point4F((F32)mNode->mTransformation.c1,
          (F32)mNode->mTransformation.c3,
          (F32)mNode->mTransformation.c2,
          (F32)mNode->mTransformation.c4)
      );
      mat.setRow(2, Point4F((F32)mNode->mTransformation.b1,
          (F32)mNode->mTransformation.b3,
          (F32)mNode->mTransformation.b2,
          (F32)mNode->mTransformation.b4)
      );
   } 
   else 
   {
      mat.setRow(1, Point4F((F32)mNode->mTransformation.b1,
          (F32)mNode->mTransformation.b3,
          (F32)mNode->mTransformation.b2,
          (F32)mNode->mTransformation.b4)
      );
      mat.setRow(2, Point4F((F32)mNode->mTransformation.c1,
          (F32)mNode->mTransformation.c3,
          (F32)mNode->mTransformation.c2,
          (F32)mNode->mTransformation.c4)
      );
   }

   mat.setRow(3, Point4F((F32)mNode->mTransformation.d1,
       (F32)mNode->mTransformation.d3,
       (F32)mNode->mTransformation.d2,
       (F32)mNode->mTransformation.d4)
   );

   // Node transformations are carried down the hiearchy
   // so we need all of our parents transforms to make 
   // this work.
   /*if ( appParent != 0 )
   {
      MatrixF parentMat = appParent->getNodeTransform(time);
      mat.mul(parentMat);
   }*/

   return mat;
}

bool AssimpAppNode::animatesTransform(const AppSequence* appSeq)
{
   return false;
}

/// Get the world transform of the node at the specified time
MatrixF AssimpAppNode::getNodeTransform(F32 time)
{
   return getTransform(time);
}