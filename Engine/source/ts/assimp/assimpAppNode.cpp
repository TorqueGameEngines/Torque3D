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

aiAnimation* AssimpAppNode::sActiveSequence = NULL;
F32 AssimpAppNode::sTimeMultiplier = 1.0f;

AssimpAppNode::AssimpAppNode(const struct aiScene* scene, const struct aiNode* node, AssimpAppNode* parent)
:  mInvertMeshes(false),
   mLastTransformTime(TSShapeLoader::DefaultTime - 1),
   mDefaultTransformValid(false)
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
   assimpToTorqueMat(node->mTransformation, mNodeTransform);
   Con::printf("[ASSIMP] Node Created: %s, Parent: %s", mName, mParentName);
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
   // Check if we can use the last computed transform
   if (time == mLastTransformTime)
      return mLastTransform;

   if (appParent) {
      // Get parent node's transform
      mLastTransform = appParent->getTransform(time);
   }
   else {
      // no parent (ie. root level) => scale by global shape <unit>
      mLastTransform.identity();
      mLastTransform.scale(ColladaUtils::getOptions().unit);
      if (!isBounds())
         convertMat(mLastTransform);
   }

   // If this node is animated in the active sequence, fetch the animated transform
   MatrixF mat(true);
   if (sActiveSequence)
      getAnimatedTransform(mat, time, sActiveSequence);
   else
      mat = mNodeTransform;

   // Remove node scaling?
   Point3F nodeScale = mat.getScale();
   if (nodeScale != Point3F::One && appParent && ColladaUtils::getOptions().ignoreNodeScale)
   {
      nodeScale.x = nodeScale.x ? (1.0f / nodeScale.x) : 0;
      nodeScale.y = nodeScale.y ? (1.0f / nodeScale.y) : 0;
      nodeScale.z = nodeScale.z ? (1.0f / nodeScale.z) : 0;
      mat.scale(nodeScale);
   }

   mLastTransform.mul(mat);

   mLastTransformTime = time;
   return mLastTransform;
}

void AssimpAppNode::getAnimatedTransform(MatrixF& mat, F32 t, aiAnimation* animSeq)
{
   // Find the channel for this node
   for (U32 i = 0; i < animSeq->mNumChannels; ++i)
   {
      if (strcmp(mName, animSeq->mChannels[i]->mNodeName.C_Str()) == 0)
      {
         aiNodeAnim *nodeAnim = animSeq->mChannels[i];
         Point3F trans(Point3F::Zero);
         Point3F scale(Point3F::One);
         QuatF rot;
         rot.identity();

         // Transform
         if (nodeAnim->mNumPositionKeys == 1)
            trans.set(nodeAnim->mPositionKeys[0].mValue.x, nodeAnim->mPositionKeys[0].mValue.y, nodeAnim->mPositionKeys[0].mValue.z);
         else
         {
            Point3F curPos, lastPos;
            F32 lastT = 0.0;
            for (U32 key = 0; key < nodeAnim->mNumPositionKeys; ++key)
            {
               F32 curT = sTimeMultiplier * (F32)nodeAnim->mPositionKeys[key].mTime;
               curPos.set(nodeAnim->mPositionKeys[key].mValue.x, nodeAnim->mPositionKeys[key].mValue.y, nodeAnim->mPositionKeys[key].mValue.z);
               if ((curT > t) && (key > 0))
               {
                  F32 factor = (t - lastT) / (curT - lastT);
                  trans.interpolate(lastPos, curPos, factor);
                  break;
               }
               else if ((curT >= t) || (key == nodeAnim->mNumPositionKeys - 1))
               {
                  trans = curPos;
                  break;
               }

               lastT = curT;
               lastPos = curPos;
            }
         }

         // Rotation
         if (nodeAnim->mNumRotationKeys == 1)
            rot.set(nodeAnim->mRotationKeys[0].mValue.x, nodeAnim->mRotationKeys[0].mValue.y,
               nodeAnim->mRotationKeys[0].mValue.z, nodeAnim->mRotationKeys[0].mValue.w);
         else
         {
            QuatF curRot, lastRot;
            F32 lastT = 0.0;
            for (U32 key = 0; key < nodeAnim->mNumRotationKeys; ++key)
            {
               F32 curT = sTimeMultiplier * (F32)nodeAnim->mRotationKeys[key].mTime;
               curRot.set(nodeAnim->mRotationKeys[key].mValue.x, nodeAnim->mRotationKeys[key].mValue.y,
                  nodeAnim->mRotationKeys[key].mValue.z, nodeAnim->mRotationKeys[key].mValue.w);
               if ((curT > t) && (key > 0))
               {
                  F32 factor = (t - lastT) / (curT - lastT);
                  rot.interpolate(lastRot, curRot, factor);
                  break;
               }
               else if ((curT >= t) || (key == nodeAnim->mNumRotationKeys - 1))
               {
                  rot = curRot;
                  break;
               }

               lastT = curT;
               lastRot = curRot;
            }
         }

         // Scale
         if (nodeAnim->mNumScalingKeys == 1)
            scale.set(nodeAnim->mScalingKeys[0].mValue.x, nodeAnim->mScalingKeys[0].mValue.y, nodeAnim->mScalingKeys[0].mValue.z);
         else
         {
            Point3F curScale, lastScale;
            F32 lastT = 0.0;
            for (U32 key = 0; key < nodeAnim->mNumScalingKeys; ++key)
            {
               F32 curT = sTimeMultiplier * (F32)nodeAnim->mScalingKeys[key].mTime;
               curScale.set(nodeAnim->mScalingKeys[key].mValue.x, nodeAnim->mScalingKeys[key].mValue.y, nodeAnim->mScalingKeys[key].mValue.z);
               if ((curT > t) && (key > 0))
               {
                  F32 factor = (t - lastT) / (curT - lastT);
                  scale.interpolate(lastScale, curScale, factor);
                  break;
               }
               else if ((curT >= t) || (key == nodeAnim->mNumScalingKeys - 1))
               {
                  scale = curScale;
                  break;
               }

               lastT = curT;
               lastScale = curScale;
            }
         }

         rot.setMatrix(&mat);
         mat.inverse();
         mat.setPosition(trans);
         mat.scale(scale);
         return;
      }
   }

   // Node not found in the animation channels
   mat = mNodeTransform;
}

bool AssimpAppNode::animatesTransform(const AppSequence* appSeq)
{
   return false;
}

/// Get the world transform of the node at the specified time
MatrixF AssimpAppNode::getNodeTransform(F32 time)
{
   // Avoid re-computing the default transform if possible
   if (mDefaultTransformValid && time == TSShapeLoader::DefaultTime)
   {
      return mDefaultNodeTransform;
   }
   else
   {
      MatrixF nodeTransform = getTransform(time);

      // Check for inverted node coordinate spaces => can happen when modelers
      // use the 'mirror' tool in their 3d app. Shows up as negative <scale>
      // transforms in the collada model.
      if (m_matF_determinant(nodeTransform) < 0.0f)
      {
         // Mark this node as inverted so we can mirror mesh geometry, then
         // de-invert the transform matrix
         mInvertMeshes = true;
         nodeTransform.scale(Point3F(1, 1, -1));
      }

      // Cache the default transform
      if (time == TSShapeLoader::DefaultTime)
      {
         mDefaultTransformValid = true;
         mDefaultNodeTransform = nodeTransform;
      }

      return nodeTransform;
   }
}

void AssimpAppNode::assimpToTorqueMat(const aiMatrix4x4& inAssimpMat, MatrixF& outMat)
{
   outMat.setRow(0, Point4F((F32)inAssimpMat.a1, (F32)inAssimpMat.a2,
      (F32)inAssimpMat.a3, (F32)inAssimpMat.a4));

   outMat.setRow(1, Point4F((F32)inAssimpMat.b1, (F32)inAssimpMat.b2,
      (F32)inAssimpMat.b3, (F32)inAssimpMat.b4));

   outMat.setRow(2, Point4F((F32)inAssimpMat.c1, (F32)inAssimpMat.c2,
      (F32)inAssimpMat.c3, (F32)inAssimpMat.c4));

   outMat.setRow(3, Point4F((F32)inAssimpMat.d1, (F32)inAssimpMat.d2,
      (F32)inAssimpMat.d3, (F32)inAssimpMat.d4));
}

void AssimpAppNode::convertMat(MatrixF& outMat)
{
   MatrixF rot(true);

   switch (ColladaUtils::getOptions().upAxis)
   {
   case UPAXISTYPE_X_UP:
      // rotate 90 around Y-axis, then 90 around Z-axis
      rot(0, 0) = 0.0f;  rot(1, 0) = 1.0f;
      rot(1, 1) = 0.0f;	rot(2, 1) = 1.0f;
      rot(0, 2) = 1.0f;	rot(2, 2) = 0.0f;

      // pre-multiply the transform by the rotation matrix
      outMat.mulL(rot);
      break;

   case UPAXISTYPE_Y_UP:
      // rotate 180 around Y-axis, then 90 around X-axis
      rot(0, 0) = -1.0f;
      rot(1, 1) = 0.0f;	rot(2, 1) = 1.0f;
      rot(1, 2) = 1.0f;	rot(2, 2) = 0.0f;

      // pre-multiply the transform by the rotation matrix
      outMat.mulL(rot);
      break;

   case UPAXISTYPE_Z_UP:
   default:
      // nothing to do
      break;
   }
}

aiNode* AssimpAppNode::findChildNodeByName(const char* nodeName, aiNode* rootNode)
{
   aiNode* retNode = NULL;
   if (strcmp(nodeName, rootNode->mName.C_Str()) == 0)
      return rootNode;

   for (U32 i = 0; i < rootNode->mNumChildren; ++i)
   {
      retNode = findChildNodeByName(nodeName, rootNode->mChildren[i]);
      if (retNode)
         return retNode;
   }
   return nullptr;
}