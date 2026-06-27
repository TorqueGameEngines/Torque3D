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

AssimpAppSequence::AssimpAppSequence(aiAnimation* a)
   : seqStart(0.0f), seqEnd(0.0f), mTimeMultiplier(1.0f)
{
   fps = ColladaUtils::getOptions().animFPS;
   // Deep copy animation structure
   mAnim = new aiAnimation(*a);
   mAnim->mChannels = new aiNodeAnim * [a->mNumChannels];
   for (U32 i = 0; i < a->mNumChannels; ++i) {
      mAnim->mChannels[i] = new aiNodeAnim(*a->mChannels[i]);
   }

   mAnim->mMeshChannels = new aiMeshAnim * [a->mNumMeshChannels];
   for (U32 i = 0; i < a->mNumMeshChannels; ++i) {
      mAnim->mMeshChannels[i] = new aiMeshAnim(*a->mMeshChannels[i]);
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
