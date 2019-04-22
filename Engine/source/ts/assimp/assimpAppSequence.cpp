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

   // From: http://sir-kimmi.de/assimp/lib_html/data.html#anims
   // An aiAnimation has a duration. The duration as well as all time stamps are given in ticks.
   // To get the correct timing, all time stamp thus have to be divided by aiAnimation::mTicksPerSecond.
   // Beware, though, that certain combinations of file format and exporter don't always store this
   // information in the exported file. In this case, mTicksPerSecond is set to 0 to indicate the lack of knowledge.
   fps = (mAnim->mTicksPerSecond > 0) ? mAnim->mTicksPerSecond : 30.0f;

   F32 maxEndTime = 0;
   F32 minFrameTime = 1000.0f;
   // Detect the frame rate (minimum time between keyframes) and max sequence time
   for (U32 i = 0; i < mAnim->mNumChannels; ++i)
   {
      aiNodeAnim *nodeAnim = mAnim->mChannels[i];
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

   fps = (minFrameTime > 0.0f) ? 1.0f / minFrameTime : fps;
   fps = mClamp(fps, TSShapeLoader::MinFrameRate, TSShapeLoader::MaxFrameRate);
   seqEnd = maxEndTime;
}

AssimpAppSequence::~AssimpAppSequence()
{
}

void AssimpAppSequence::setActive(bool active)
{
   if (active)
      AssimpAppNode::sActiveSequence = mAnim;
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