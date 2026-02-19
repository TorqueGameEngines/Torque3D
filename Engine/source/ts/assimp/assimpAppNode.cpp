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


#if !defined(TORQUE_DISABLE_MEMORY_MANAGER)
#ifdef new
#undef new
#endif
#endif

// assimp include files. 
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/types.h>

#if !defined(TORQUE_DISABLE_MEMORY_MANAGER)
#  define _new new(__FILE__, __LINE__)
#  define new  _new
#endif


aiAnimation* AssimpAppNode::sActiveSequence = NULL;
F32 AssimpAppNode::sTimeMultiplier = 1.0f;

AssimpAppNode::AssimpAppNode(const aiScene* scene, const aiNode* node, AssimpAppNode* parentNode)
   :  mScene(scene),
      mNode(node ? node : scene->mRootNode),
      mInvertMeshes(false),
      mLastTransformTime(TSShapeLoader::DefaultTime - 1),
      mDefaultTransformValid(false)
{
   appParent = parentNode;
   // Initialize node and parent names.
   mName = dStrdup(mNode->mName.C_Str());
   if ( dStrlen(mName) == 0 )
   {
      const char* defaultName = "null";
      mName = dStrdup(defaultName);
   }
   mParentName = dStrdup(parentNode ? parentNode->mName : "ROOT");
   // Convert transformation matrix
   assimpToTorqueMat(node->mTransformation, mNodeTransform);
   Con::printf("[ASSIMP] Node Created: %s, Parent: %s", mName, mParentName);
}

MatrixF AssimpAppNode::getTransform(F32 time)
{
   // Check if we can use the last computed transform
   if (time == mLastTransformTime)
   {
      return mLastTransform;
   }

   if (appParent) {
      // Get parent node's transform
      mLastTransform = appParent->getTransform(time);
   }
   else {
      // no parent (ie. root level) => scale by global shape <unit>
      mLastTransform.identity();
      mLastTransform.scale(ColladaUtils::getOptions().unit * ColladaUtils::getOptions().formatScaleFactor);
      if (!isBounds())
      {
         MatrixF axisFix = ColladaUtils::getOptions().axisCorrectionMat;
         mLastTransform.mulL(axisFix);
      }
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
   // Convert time `t` (in seconds) to a frame index
   const F32 frameTime = (t * animSeq->mTicksPerSecond + 0.5f) + 1.0f;

   // Loop through animation channels to find the matching node
   for (U32 k = 0; k < animSeq->mNumChannels; ++k)
   {
      const aiNodeAnim* nodeAnim = animSeq->mChannels[k];
      if (dStrcmp(mName, nodeAnim->mNodeName.C_Str()) != 0)
         continue;

      Point3F translation(Point3F::Zero);
      QuatF rotation(QuatF::Identity);
      Point3F scale(Point3F::One);

      // Interpolate Translation Keys
      if (nodeAnim->mNumPositionKeys > 0)
      {
         translation = interpolateVectorKey(nodeAnim->mPositionKeys, nodeAnim->mNumPositionKeys, frameTime);
      }

      // Interpolate Rotation Keys
      if (nodeAnim->mNumRotationKeys > 0)
      {
         rotation = interpolateQuaternionKey(nodeAnim->mRotationKeys, nodeAnim->mNumRotationKeys, frameTime);
      }

      // Interpolate Scaling Keys
      if (nodeAnim->mNumScalingKeys > 0)
      {
         scale = interpolateVectorKey(nodeAnim->mScalingKeys, nodeAnim->mNumScalingKeys, frameTime);
      }

      // Apply the interpolated transform components to the matrix
      rotation.setMatrix(&mat);
      mat.inverse();
      mat.setPosition(translation);
      mat.scale(scale);

      return; // Exit after processing the matching node
   }

   // Default to the static node transformation if no animation data is found
   mat = mNodeTransform;
}

Point3F AssimpAppNode::interpolateVectorKey(const aiVectorKey* keys, U32 numKeys, F32 frameTime)
{
   if (numKeys == 1) // Single keyframe: use it directly
      return Point3F(keys[0].mValue.x, keys[0].mValue.y, keys[0].mValue.z);

   // Clamp frameTime to the bounds of the keyframes
   if (frameTime <= keys[0].mTime) {
      // Before the first keyframe, return the first key
      return Point3F(keys[0].mValue.x, keys[0].mValue.y, keys[0].mValue.z);
   }
   if (frameTime >= keys[numKeys - 1].mTime) {
      // After the last keyframe, return the last key
      return Point3F(keys[numKeys - 1].mValue.x, keys[numKeys - 1].mValue.y, keys[numKeys - 1].mValue.z);
   }

   // Interpolate between the two nearest keyframes
   for (U32 i = 1; i < numKeys; ++i)
   {
      if (frameTime < keys[i].mTime)
      {
         Assimp::Interpolator<aiVectorKey> interp;

         const aiVectorKey& next = keys[i];
         const aiVectorKey& prev = keys[i - 1];

         const F32 factor = (frameTime - keys[i - 1].mTime) / (keys[i].mTime - keys[i - 1].mTime);

         aiVector3D out;
         interp(out, prev, next, factor);
         return Point3F(out.x, out.y, out.z);
      }
   }

   // Default to the last keyframe
   return Point3F(keys[numKeys - 1].mValue.x, keys[numKeys - 1].mValue.y, keys[numKeys - 1].mValue.z);
}

QuatF AssimpAppNode::interpolateQuaternionKey(const aiQuatKey* keys, U32 numKeys, F32 frameTime)
{
   if (numKeys == 1) // Single keyframe: use it directly
      return QuatF(keys[0].mValue.x, keys[0].mValue.y, keys[0].mValue.z, keys[0].mValue.w);

   // Clamp frameTime to the bounds of the keyframes
   if (frameTime <= keys[0].mTime) {
      // Before the first keyframe, return the first key
      return QuatF(keys[0].mValue.x, keys[0].mValue.y, keys[0].mValue.z, keys[0].mValue.w);
   }
   if (frameTime >= keys[numKeys - 1].mTime) {
      // After the last keyframe, return the last key
      return QuatF(keys[numKeys - 1].mValue.x, keys[numKeys - 1].mValue.y, keys[numKeys - 1].mValue.z, keys[numKeys - 1].mValue.w);
   }

   for (U32 i = 1; i < numKeys; ++i)
   {
      if (frameTime < keys[i].mTime)
      {
         const F32 factor = (frameTime - keys[i - 1].mTime) / (keys[i].mTime - keys[i - 1].mTime);
         QuatF start(keys[i - 1].mValue.x, keys[i - 1].mValue.y, keys[i - 1].mValue.z, keys[i - 1].mValue.w);
         QuatF end(keys[i].mValue.x, keys[i].mValue.y, keys[i].mValue.z, keys[i].mValue.w);
         QuatF result;
         result.interpolate(start, end, factor);
         return result;
      }
   }

   // Default to the last keyframe
   return QuatF(keys[numKeys - 1].mValue.x, keys[numKeys - 1].mValue.y, keys[numKeys - 1].mValue.z, keys[numKeys - 1].mValue.w);
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
   return NULL;
}

void AssimpAppNode::addChild(AssimpAppNode* child)
{
   mChildNodes.push_back(child);
}

void AssimpAppNode::addMesh(AssimpAppMesh* child)
{
   mMeshes.push_back(child);
}

void AssimpAppNode::buildMeshList()
{
   for (U32 i = 0; i < mNode->mNumMeshes; i++)
   {
      U32 meshIdx = mNode->mMeshes[i];
      const aiMesh* mesh = mScene->mMeshes[meshIdx];
      AssimpAppMesh* curMesh = new AssimpAppMesh(mesh, this);
      mMeshes.push_back(curMesh);
   }
}

void AssimpAppNode::buildChildList()
{
   for (U32 i = 0; i < mNode->mNumChildren; i++)
   {
      const aiNode* node = mNode->mChildren[i];
      mChildNodes.push_back(new AssimpAppNode(mScene, node, this));
   }
}
