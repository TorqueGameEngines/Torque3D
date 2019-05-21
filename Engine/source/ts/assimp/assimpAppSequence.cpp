#include "ts/assimp/assimpShapeLoader.h"

#include "console/console.h"
#include "core/stream/fileStream.h" 
#include "core/stringTable.h"
#include "math/mathIO.h"
#include "ts/tsShape.h"
#include "ts/tsShapeInstance.h"
#include "materials/materialManager.h"
#include "console/persistenceManager.h"
#include "ts/assimp/assimpAppMaterial.h"
#include "ts/assimp/assimpAppSequence.h"
#include "ts/assimp/assimpAppNode.h"

AssimpAppSequence::AssimpAppSequence(aiAnimation *a) :
   seqStart(0.0f),
   mAnim(a)
{
   mSequenceName = mAnim->mName.C_Str();
   if (mSequenceName.isEmpty())
      mSequenceName = "ambient";
   Con::printf("\n[Assimp] Adding %s animation", mSequenceName.c_str());

   fps = (mAnim->mTicksPerSecond > 0) ? mAnim->mTicksPerSecond : 30.0f;

   U32 maxKeys = 0;
   F32 maxEndTime = 0;
   F32 minFrameTime = 100000.0f;
   // Detect the frame rate (minimum time between keyframes) and max sequence time
   for (U32 i = 0; i < mAnim->mNumChannels; ++i)
   {
      aiNodeAnim *nodeAnim = mAnim->mChannels[i];
      maxKeys = getMax(maxKeys, nodeAnim->mNumPositionKeys);
      maxKeys = getMax(maxKeys, nodeAnim->mNumRotationKeys);
      maxKeys = getMax(maxKeys, nodeAnim->mNumScalingKeys);

      if (nodeAnim->mNumPositionKeys)
         maxEndTime = getMax(maxEndTime, (F32) nodeAnim->mPositionKeys[nodeAnim->mNumPositionKeys-1].mTime);
      if (nodeAnim->mNumRotationKeys)
         maxEndTime = getMax(maxEndTime, (F32) nodeAnim->mRotationKeys[nodeAnim->mNumRotationKeys-1].mTime);
      if (nodeAnim->mNumScalingKeys)
         maxEndTime = getMax(maxEndTime, (F32) nodeAnim->mScalingKeys[nodeAnim->mNumScalingKeys-1].mTime);

      for (U32 key = 1; key < nodeAnim->mNumPositionKeys; ++key)
      {
         F32 deltaT = nodeAnim->mPositionKeys[key].mTime - nodeAnim->mPositionKeys[key-1].mTime;
         minFrameTime = getMin(minFrameTime, deltaT);
      }
      for (U32 key = 1; key < nodeAnim->mNumRotationKeys; ++key)
      {
         F32 deltaT = nodeAnim->mRotationKeys[key].mTime - nodeAnim->mRotationKeys[key-1].mTime;
         minFrameTime = getMin(minFrameTime, deltaT);
      }
      for (U32 key = 1; key < nodeAnim->mNumScalingKeys; ++key)
      {
         F32 deltaT = nodeAnim->mScalingKeys[key].mTime - nodeAnim->mScalingKeys[key-1].mTime;
         minFrameTime = getMin(minFrameTime, deltaT);
      }
   }

   S32 timeFactor = ColladaUtils::getOptions().animTiming;
   S32 fpsRequest = ColladaUtils::getOptions().animFPS;
   if (timeFactor == 0)
   {  // Timing specified in frames
      fps = mClamp(fpsRequest, 5 /*TSShapeLoader::MinFrameRate*/, TSShapeLoader::MaxFrameRate);
      maxKeys = getMax(maxKeys, (U32)maxEndTime);  // Keys won't be assigned for every frame.
      seqEnd = maxKeys / fps;
      mTimeMultiplier = 1.0f / fps;
   }
   else
   {  // Timing specified in seconds or ms depending on format
      if (maxEndTime > 1000.0f || mAnim->mDuration > 1000.0f)
         timeFactor = 1000.0f;   // If it's more than 1000 seconds, assume it's ms.

      timeFactor = mClamp(timeFactor, 1, 1000);
      minFrameTime /= (F32)timeFactor;
      maxEndTime /= (F32)timeFactor;
      fps = (minFrameTime > 0.0f) ? 1.0f / minFrameTime : fps;
      fps = mClamp(fpsRequest, 5 /*TSShapeLoader::MinFrameRate*/, TSShapeLoader::MaxFrameRate);
      seqEnd = maxEndTime;
      mTimeMultiplier = 1.0f / timeFactor;
   }
}

AssimpAppSequence::~AssimpAppSequence()
{
}

void AssimpAppSequence::setActive(bool active)
{
   if (active)
   {
      AssimpAppNode::sActiveSequence = mAnim;
      AssimpAppNode::sTimeMultiplier = mTimeMultiplier;
   }
   else
   {
      if (AssimpAppNode::sActiveSequence == mAnim)
         AssimpAppNode::sActiveSequence = NULL;
   }
}

U32 AssimpAppSequence::getFlags() const 
{ 
   return TSShape::Blend;
}
F32 AssimpAppSequence::getPriority() const 
{ 
   return 5; 
}
F32 AssimpAppSequence::getBlendRefTime() const 
{ 
   return -1.0f; 
}