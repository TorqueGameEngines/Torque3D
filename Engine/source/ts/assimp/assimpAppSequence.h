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

   virtual void setActive(bool active);

   virtual S32 getNumTriggers() const { return 0; }
   virtual void getTrigger(S32 index, TSShape::Trigger& trigger) const { trigger.state = 0; }

   virtual const char* getName() const { return mSequenceName.c_str(); }

   F32 getStart() const { return seqStart; }
   F32 getEnd() const { return seqEnd; }
   void setEnd(F32 end) { seqEnd = end; }

   virtual U32 getFlags() const;
   virtual F32 getPriority() const;
   virtual F32 getBlendRefTime() const;
};
