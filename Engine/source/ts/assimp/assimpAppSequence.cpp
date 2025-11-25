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
   // Set fps from the file or use default
   fps = (a->mTicksPerSecond > 0) ? a->mTicksPerSecond : 30.0f;

   if (fps >= 1000.0f) { // Indicates milliseconds (GLTF or similar formats)
      mTimeMultiplier = 1.0f / 1000.0f; // Convert milliseconds to seconds
      Con::printf("[Assimp] Detected milliseconds timing (FPS >= 1000). Time Multiplier: %f", mTimeMultiplier);
   }
   else if (fps > 0.0f) { // Standard FPS
      fps = mClamp(fps, 5 /*TSShapeLoader::MinFrameRate*/, TSShapeLoader::MaxFrameRate);
      mTimeMultiplier = 1.0f / fps;
      Con::printf("[Assimp] Standard FPS detected. Time Multiplier: %f", mTimeMultiplier);
   }
   else {
      // Fall back to 30 FPS as default
      mTimeMultiplier = 1.0f / 30.0f;
      Con::printf("[Assimp] FPS not specified. Using default 30 FPS. Time Multiplier: %f", mTimeMultiplier);
   }


}

void AssimpAppSequence::calculateSequenceEnd(aiAnimation* a)
{
   for (U32 i = 0; i < a->mNumChannels; ++i) {
      aiNodeAnim* nodeAnim = a->mChannels[i];
      F32 maxKeyTime = 0.0f;

      // Calculate the maximum time across all keyframes for this channel
      for (U32 k = 0; k < nodeAnim->mNumPositionKeys; ++k) {
         maxKeyTime = getMax(maxKeyTime, (F32)nodeAnim->mPositionKeys[k].mTime);
      }
      for (U32 k = 0; k < nodeAnim->mNumRotationKeys; ++k) {
         maxKeyTime = getMax(maxKeyTime, (F32)nodeAnim->mRotationKeys[k].mTime);
      }
      for (U32 k = 0; k < nodeAnim->mNumScalingKeys; ++k) {
         maxKeyTime = getMax(maxKeyTime, (F32)nodeAnim->mScalingKeys[k].mTime);
      }

      // Use the multiplier to convert to real sequence time
      seqEnd = mTimeMultiplier * getMax(seqEnd, maxKeyTime);
   }

   Con::printf("[Assimp] Sequence End Time: %f seconds", seqEnd);
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
