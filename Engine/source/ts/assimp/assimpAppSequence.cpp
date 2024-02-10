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
   seqEnd(0.0f)
{
   mAnim = new aiAnimation(*a);
   // Deep copy channels
   mAnim->mChannels = new aiNodeAnim * [a->mNumChannels];
   for (U32 i = 0; i < a->mNumChannels; ++i) {
      mAnim->mChannels[i] = new aiNodeAnim(*a->mChannels[i]);
   }

   // Deep copy meshes
   mAnim->mMeshChannels = new aiMeshAnim * [a->mNumMeshChannels];
   for (U32 i = 0; i < a->mNumMeshChannels; ++i) {
      mAnim->mMeshChannels[i] = new aiMeshAnim(*a->mMeshChannels[i]);
   }

   // Deep copy name
   mAnim->mName = a->mName;

   mSequenceName = mAnim->mName.C_Str();
   if (mSequenceName.isEmpty())
      mSequenceName = "ambient";
   Con::printf("\n[Assimp] Adding %s animation", mSequenceName.c_str());

   fps = (a->mTicksPerSecond > 0) ? a->mTicksPerSecond : 30.0f;

   if (a->mDuration > 0)
   {
      // torques seqEnd is in seconds, this then gets generated into frames in generateSequences()
      seqEnd = (F32)a->mDuration / fps;
   }
   else
   {
      for (U32 i = 0; i < a->mNumChannels; ++i)
      {
         aiNodeAnim* nodeAnim = a->mChannels[i];
         // Determine the maximum keyframe time for this animation
         F32 maxKeyTime = 0.0f;
         for (U32 k = 0; k < nodeAnim->mNumPositionKeys; k++) {
            maxKeyTime = getMax(maxKeyTime, (F32)nodeAnim->mPositionKeys[k].mTime);
         }
         for (U32 k = 0; k < nodeAnim->mNumRotationKeys; k++) {
            maxKeyTime = getMax(maxKeyTime, (F32)nodeAnim->mRotationKeys[k].mTime);
         }
         for (U32 k = 0; k < nodeAnim->mNumScalingKeys; k++) {
            maxKeyTime = getMax(maxKeyTime, (F32)nodeAnim->mScalingKeys[k].mTime);
         }

         seqEnd = getMax(seqEnd, maxKeyTime);
      }
   }

   mTimeMultiplier = 1.0f;

   S32 timeFactor = ColladaUtils::getOptions().animTiming;
   S32 fpsRequest = (S32)a->mTicksPerSecond;
   if (timeFactor == 0)
   {  // Timing specified in frames
      fps = mClamp(fpsRequest, 5 /*TSShapeLoader::MinFrameRate*/, TSShapeLoader::MaxFrameRate);
      mTimeMultiplier = 1.0f / fps;
   }
   else
   {  // Timing specified in seconds or ms depending on format
      if (seqEnd > 1000.0f || a->mDuration > 1000.0f)
         timeFactor = 1000.0f;   // If it's more than 1000 seconds, assume it's ms.

      timeFactor = mClamp(timeFactor, 1, 1000);
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
   return TSShape::Cyclic;
}
F32 AssimpAppSequence::getPriority() const 
{ 
   return 5; 
}
F32 AssimpAppSequence::getBlendRefTime() const 
{ 
   return 0.0f; 
}
