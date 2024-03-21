#pragma once
#ifndef _MMATH_H_
#include "math/mMath.h"
#endif
#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif
#ifndef _TSSHAPE_H_
#include "ts/tsShape.h"
#endif
#ifndef _APPNODE_H_
#include "ts/loader/appNode.h"
#endif
#ifndef _APPMESH_H_
#include "ts/loader/appMesh.h"
#endif
#ifndef _APPSEQUENCE_H_
#include "ts/loader/appSequence.h"
#endif

#include <assimp/scene.h>

class AssimpAppSequence : public AppSequence
{
   String   mSequenceName;
   F32      seqStart;
   F32      seqEnd;
   F32      mTimeMultiplier; // The factor needed to convert the sequence data timestamp to seconds

public:

   AssimpAppSequence(aiAnimation *a);
   ~AssimpAppSequence();

   aiAnimation *mAnim;

   void setActive(bool active) override;

   S32 getNumTriggers() const override { return 0; }
   void getTrigger(S32 index, TSShape::Trigger& trigger) const override { trigger.state = 0; }

   const char* getName() const override { return mSequenceName.c_str(); }

   F32 getStart() const override { return seqStart; }
   F32 getEnd() const override { return seqEnd; }
   void setEnd(F32 end) { seqEnd = end; }

   U32 getFlags() const override;
   F32 getPriority() const override;
   F32 getBlendRefTime() const override;
};
