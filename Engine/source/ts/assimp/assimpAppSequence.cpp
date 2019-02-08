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

AssimpAppSequence::AssimpAppSequence(aiAnimation *a) :
   mAnim(a)
{
   fps = mAnim->mTicksPerSecond;
}

AssimpAppSequence::~AssimpAppSequence()
{
}

F32 AssimpAppSequence::getStart() const 
{ 
   return 0.0f; 
}
F32 AssimpAppSequence::getEnd() const 
{ 
   return (F32)mAnim->mDuration / fps; 
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

