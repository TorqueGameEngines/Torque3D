#include "ts/tsShapeInstance.h"

/// All ik solving happens to the global transform then is converted to localspace
/// mNodeTransforms is the global transform vector
/// smNodeLocalTransform is the local transform vector
/// we do our solving after animateNodes so animations can change bone lengths
/// but our fabrik solver does not!
/// The book C++ Game Animation Programming 2nd Edition was used as reference.

Vector<F32>       TSShapeInstance::smFabrikBoneLengths(__FILE__, __LINE__);
Vector<Point3F>   TSShapeInstance::smFabrikPositions(__FILE__, __LINE__);
Vector<S32>       TSShapeInstance::smIKChainNodes(__FILE__, __LINE__);

//-------------------------------------------------------------------
// FABRIK FUNCTIONS
//-------------------------------------------------------------------

void TSShapeInstance::updateChildWorldTransforms(S32 node)
{
   for (S32 child = mShape->nodes[node].firstChild; child != -1; child = mShape->nodes[child].nextSibling)
   {
      // world[child] = world[parent] * local[child]
      mNodeTransforms[child].mul(mNodeTransforms[node], smNodeLocalTransforms[child]);

      // recurse
      updateChildWorldTransforms(child);
   }
}

bool TSShapeInstance::calculateFabrikBoneLengths()
{
   const S32 count = smIKChainNodes.size();

   // not enough for fabrik.
   if (count < 2)
      return false;

   smFabrikBoneLengths.clear();
   smFabrikBoneLengths.setSize(count - 1);

   for (S32 i = 0; i < count - 1; i++)
   {
      const Point3F p0 = mNodeTransforms[smIKChainNodes[i]].getPosition();
      const Point3F p1 = mNodeTransforms[smIKChainNodes[i + 1]].getPosition();
      smFabrikBoneLengths[i] = (p1 - p0).magnitudeSafe();
   }
   return true;
}

void TSShapeInstance::applyFabrik(TSShape::IKChain& chain)
{
   const U32 count = smFabrikPositions.size();
   if (count < 2)
      return;

   for (S32 i = count - 1; i > 0; i--)
   {
      S32 nodeIdx = smIKChainNodes[i];
      S32 nextNodeIdx = smIKChainNodes[i-1];

      // Current joint global rotation & position
      QuatF curWorldRot;
      curWorldRot.set(mNodeTransforms[nodeIdx]);
      const Point3F curPos = mNodeTransforms[nodeIdx].getPosition();
      const Point3F nextPos = mNodeTransforms[nextNodeIdx].getPosition();

      // Direction vectors
      VectorF toNext = nextPos - curPos;
      toNext.normalizeSafe();

      VectorF toDesired = smFabrikPositions[i - 1] - smFabrikPositions[i];
      toDesired.normalizeSafe();

      // Rotation direction -> target direction
      QuatF rotToTarget;
      rotToTarget.computeRotationFromTo(toDesired, toNext);

      QuatF parentWorldRot;
      S32 parentIdx = mShape->nodes[nodeIdx].parentIndex;
      if (parentIdx >= 0)
         parentWorldRot.set(mNodeTransforms[parentIdx]);
      else
         parentWorldRot.identity();

      QuatF curRotLocal = smNodeCurrentRotations[nodeIdx];
      QuatF newRotLocal = parentWorldRot * rotToTarget * parentWorldRot.conjugate();

      QuatF blendedRot;

      TSTransform::interpolate(curRotLocal, curRotLocal * newRotLocal, chain.weight, &blendedRot);

      // Update local rotation & matrix
      smNodeCurrentRotations[nodeIdx] = blendedRot;
      TSTransform::setMatrix(blendedRot, smNodeCurrentTranslations[nodeIdx], &smNodeLocalTransforms[nodeIdx]);

      // Update world transform for this node
      if (parentIdx >= 0)
         mNodeTransforms[nodeIdx].mul(mNodeTransforms[parentIdx], smNodeLocalTransforms[nodeIdx]);
      else
         mNodeTransforms[nodeIdx] = smNodeLocalTransforms[nodeIdx];

      // Propagate world transform to children
      updateChildWorldTransforms(nodeIdx);
   }
}

void TSShapeInstance::solveFabrikForward(const Point3F& target)
{
   const U32 count = smFabrikPositions.size();
   if (count < 2)
      return;

   smFabrikPositions[0] = target;

   for (S32 i = 1; i < count; i++)
   {
      VectorF direction = (smFabrikPositions[i] - smFabrikPositions[i - 1]);
      direction.normalizeSafe();

      Point3F offset = direction * smFabrikBoneLengths[i - 1];

      smFabrikPositions[i] = smFabrikPositions[i - 1] + offset;
   }
}

void TSShapeInstance::solveFabrikBackward(const Point3F& root)
{
   const U32 count = smFabrikPositions.size();
   if (count < 2)
      return;

   smFabrikPositions[count - 1] = root;

   for (S32 i = count-2; i > 0; i--)
   {
      VectorF direction = (smFabrikPositions[i] - smFabrikPositions[i + 1]);
      direction.normalizeSafe();

      Point3F offset = direction * smFabrikBoneLengths[i];

      smFabrikPositions[i] = smFabrikPositions[i + 1] + offset;
   }

}

//-------------------------------------------------------------------
// FABRIK FUNCTIONS END
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// MAIN SOLVER ENTRY FUNCTIONS
//-------------------------------------------------------------------

bool TSShapeInstance::solveCCD(TSShape::IKChain& chain)
{
   PROFILE_SCOPE(TSShapeInstance_solveCCD);

   if (!chain.enabled)
      return false;

   // safety.
   smIKChainNodes.clear();
   smIKChainNodes = chain.nodes;

   const U32 count = smIKChainNodes.size();
   if (count == 0) return false;

   const S32 endNode = smIKChainNodes.first();
   const F32 threshold = chain.threshold;
   const U32 maxIterations = chain.maxIterations;
   const Point3F targetPos = mNodeTransforms[chain.targetIndex].getPosition();

   for (U32 iter = 0; iter < maxIterations; iter++)
   {
      Point3F endPos = mNodeTransforms[endNode].getPosition();

      // Early exit if the end effector is close enough
      if ((targetPos - endPos).magnitudeSafe() < threshold)
         return true;

      // Iterate joints from the one before the end effector -> root
      // (exclude the end effector itself)
      for (S32 i = 1; i < count; i++)
      {
         S32 nodeIdx = smIKChainNodes[i];

         // Current joint global rotation & position
         QuatF curWorldRot;
         curWorldRot.set(mNodeTransforms[nodeIdx]);
         const Point3F curPos = mNodeTransforms[nodeIdx].getPosition();

         // Direction vectors
         VectorF toEnd = endPos - curPos;
         VectorF toTarget = targetPos - curPos;

         toEnd.normalizeSafe();
         toTarget.normalizeSafe();

         // Rotation direction -> target direction
         QuatF rotToTarget;
         rotToTarget.computeRotationFromTo(toTarget, toEnd);

         QuatF parentWorldRot;
         S32 parentIdx = mShape->nodes[nodeIdx].parentIndex;
         if (parentIdx >= 0)
            parentWorldRot.set(mNodeTransforms[parentIdx]);
         else
            parentWorldRot.identity();

         QuatF curRotLocal = smNodeCurrentRotations[nodeIdx];
         QuatF newRotLocal = parentWorldRot * rotToTarget * parentWorldRot.conjugate();

         QuatF blendedRot;

         TSTransform::interpolate(curRotLocal, curRotLocal * newRotLocal, chain.weight, &blendedRot);

         // Update local rotation & matrix
         smNodeCurrentRotations[nodeIdx] = blendedRot;
         TSTransform::setMatrix(blendedRot, smNodeCurrentTranslations[nodeIdx], &smNodeLocalTransforms[nodeIdx]);

         // Update world transform for this node
         if (parentIdx >= 0)
            mNodeTransforms[nodeIdx].mul(mNodeTransforms[parentIdx], smNodeLocalTransforms[nodeIdx]);
         else
            mNodeTransforms[nodeIdx] = smNodeLocalTransforms[nodeIdx];

         // Propagate world transform to children
         updateChildWorldTransforms(nodeIdx);

         // Check updated end effector
         endPos = mNodeTransforms[endNode].getPosition();
         if ((targetPos - endPos).magnitudeSafe() < threshold)
            return true;
      }
   }
   return false;
}

bool TSShapeInstance::solveFrabrik(TSShape::IKChain& chain)
{
   PROFILE_SCOPE(TSShapeInstance_solveFabrik);
   if (!chain.enabled)
      return false;

   // safety.
   smIKChainNodes.clear();

   smIKChainNodes = chain.nodes;
   const U32 count = smIKChainNodes.size();

   // not enough for fabrik.
   if (count < 2)
      return false;

   // Resize working position buffer
   smFabrikPositions.setSize(count);

   // Fill initial global positions
   for (U32 i = 0; i < count; i++)
      smFabrikPositions[i] = mNodeTransforms[smIKChainNodes[i]].getPosition();

   if (!calculateFabrikBoneLengths())
      return false;

   const S32 endNode = smIKChainNodes.first();
   const Point3F rootPos = smFabrikPositions[count-1];
   const Point3F targetPos = mNodeTransforms[chain.targetIndex].getPosition();
   const F32 threshold = chain.threshold;
   const U32 maxIterations = chain.maxIterations;

   for (U32 i = 0; i < maxIterations; i++)
   {
      Point3F endPos = smFabrikPositions[0];
      // Early exit if the end effector is close enough
      if ((targetPos - endPos).magnitudeSafe() < threshold)
      {
         applyFabrik(chain);
         return true;
      }

      solveFabrikForward(targetPos);
      solveFabrikBackward(rootPos);
   }

   applyFabrik(chain);

   Point3F endPos = mNodeTransforms[endNode].getPosition();
   if ((targetPos - endPos).magnitudeSafe() < threshold)
      return true;

   return false;
}
