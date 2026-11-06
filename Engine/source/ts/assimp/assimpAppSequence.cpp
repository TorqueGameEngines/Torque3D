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

// aiNodeAnim/aiMeshAnim have no copy constructor, so simply doing a new doesn't fully copy the whole
// structure. Using this guarantees the clones have their own memory which is then safe to delete 
// on it's own later
static aiNodeAnim* cloneNodeAnim(const aiNodeAnim* src)
{
   aiNodeAnim* dst = new aiNodeAnim();
   dst->mNodeName = src->mNodeName;
   dst->mPreState = src->mPreState;
   dst->mPostState = src->mPostState;

   dst->mNumPositionKeys = src->mNumPositionKeys;
   dst->mPositionKeys = src->mNumPositionKeys ? new aiVectorKey[src->mNumPositionKeys] : nullptr;
   for (U32 i = 0; i < src->mNumPositionKeys; i++)
      dst->mPositionKeys[i] = src->mPositionKeys[i];

   dst->mNumRotationKeys = src->mNumRotationKeys;
   dst->mRotationKeys = src->mNumRotationKeys ? new aiQuatKey[src->mNumRotationKeys] : nullptr;
   for (U32 i = 0; i < src->mNumRotationKeys; i++)
      dst->mRotationKeys[i] = src->mRotationKeys[i];

   dst->mNumScalingKeys = src->mNumScalingKeys;
   dst->mScalingKeys = src->mNumScalingKeys ? new aiVectorKey[src->mNumScalingKeys] : nullptr;
   for (U32 i = 0; i < src->mNumScalingKeys; i++)
      dst->mScalingKeys[i] = src->mScalingKeys[i];

   return dst;
}

static aiMeshAnim* cloneMeshAnim(const aiMeshAnim* src)
{
   aiMeshAnim* dst = new aiMeshAnim();
   dst->mName = src->mName;
   dst->mNumKeys = src->mNumKeys;
   dst->mKeys = src->mNumKeys ? new aiMeshKey[src->mNumKeys] : nullptr;
   for (U32 i = 0; i < src->mNumKeys; i++)
      dst->mKeys[i] = src->mKeys[i];
   return dst;
}

AssimpAppSequence::AssimpAppSequence(aiAnimation* a)
   : seqStart(0.0f), seqEnd(0.0f), mTimeMultiplier(1.0f)
{
   fps = ColladaUtils::getOptions().animFPS;
   // Deep copy animation structure
   mAnim = new aiAnimation(*a);

   //We don't currently support morphs, so just init to blank for now.
   mAnim->mMorphMeshChannels = nullptr;
   mAnim->mNumMorphMeshChannels = 0;

   mAnim->mChannels = new aiNodeAnim * [a->mNumChannels];
   for (U32 i = 0; i < a->mNumChannels; ++i) {
      mAnim->mChannels[i] = cloneNodeAnim(a->mChannels[i]);
   }

   mAnim->mMeshChannels = new aiMeshAnim * [a->mNumMeshChannels];
   for (U32 i = 0; i < a->mNumMeshChannels; ++i) {
      mAnim->mMeshChannels[i] = cloneMeshAnim(a->mMeshChannels[i]);
   }

   mAnim->mName = a->mName;
   mSequenceName = mAnim->mName.C_Str();
   if (mSequenceName.isEmpty())
      mSequenceName = "ambient";

   Con::printf("\n[Assimp] Adding animation: %s", mSequenceName.c_str());

   // Determine the FPS and Time Multiplier
   determineTimeMultiplier(a);

   // Calculate sequence end time based on keyframes and multiplier
   calculateSequenceEnd(a);
}

AssimpAppSequence::~AssimpAppSequence()
{
   if (mAnim)
   {
      if (mAnim->mChannels)
      {
         for (unsigned i = 0; i < mAnim->mNumChannels; i++)
            SAFE_DELETE(mAnim->mChannels[i]);

         SAFE_DELETE_ARRAY(mAnim->mChannels);
      }

      if (mAnim->mMeshChannels)
      {
         for (unsigned i = 0; i < mAnim->mNumMeshChannels; i++)
            SAFE_DELETE(mAnim->mMeshChannels[i]);

         SAFE_DELETE_ARRAY(mAnim->mMeshChannels);
      }

      SAFE_DELETE(mAnim)
   }
}

void AssimpAppSequence::determineTimeMultiplier(aiAnimation* a)
{
   const ColladaUtils::ImportOptions& opts = ColladaUtils::getOptions();

   switch (opts.animTiming)
   {
   case ColladaUtils::ImportOptions::Seconds:
      mTimeMultiplier = 1.0f;
      break;

   case ColladaUtils::ImportOptions::Milliseconds:
      mTimeMultiplier = 1.0f / 1000.0f;
      break;

   case ColladaUtils::ImportOptions::FrameCount:
   default:
   {
      const float ticksPerSecond =
         (a->mTicksPerSecond > 0.0)
         ? (float)a->mTicksPerSecond
         : (float)ColladaUtils::getOptions().animFPS; // safe fallback
      mTimeMultiplier = 1.0f / ticksPerSecond;
      break;
   }
   }

   Con::printf(
      "[Assimp] TicksPerSecond: %f, Time Multiplier: %f",
      (a->mTicksPerSecond > 0.0) ? (float)a->mTicksPerSecond : (float)ColladaUtils::getOptions().animFPS,
      mTimeMultiplier
   );
}

void AssimpAppSequence::calculateSequenceEnd(aiAnimation* a)
{
   // mDuration is in ticks
   seqEnd = (F32)a->mDuration * mTimeMultiplier;

   Con::printf(
      "[Assimp] Sequence End Time: %f seconds (Duration ticks: %f)",
      seqEnd,
      (F32)a->mDuration
   );
}

void AssimpAppSequence::setActive(bool active)
{
   if (active)
   {
      AssimpAppNode::sActiveSequence = mAnim;
      AssimpAppNode::sTimeMultiplier = mTimeMultiplier;
      Con::printf("[Assimp] Activating sequence: %s with Time Multiplier: %f", mSequenceName.c_str(), mTimeMultiplier);
   }
   else
   {
      if (AssimpAppNode::sActiveSequence == mAnim)
      {
         AssimpAppNode::sActiveSequence = NULL;
         Con::printf("[Assimp] Deactivating sequence: %s", mSequenceName.c_str());
      }
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
