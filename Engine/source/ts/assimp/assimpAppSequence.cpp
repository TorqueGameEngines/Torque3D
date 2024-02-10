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

      maxEndTime = getMax(maxEndTime, (F32)maxKeys);
   }

   seqEnd = maxEndTime;

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
   return -1.0f; 
}
