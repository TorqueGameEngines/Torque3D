//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#include "AIController.h"
#include "T3D/player.h"
#include "T3D/rigidShape.h"
#include "T3D/vehicles/wheeledVehicle.h"
#include "T3D/vehicles/flyingVehicle.h"


IMPLEMENT_CONOBJECT(AIController);

//-----------------------------------------------------------------------------
void AIController::throwCallback(const char* name)
{
   //Con::warnf("throwCallback: %s", name);
   Con::executef(mControllerData, name, getIdString()); //controller data callbacks

   GameBase* gbo = dynamic_cast<GameBase*>(getAIInfo()->mObj.getPointer());
   if (!gbo) return;
   Con::executef(gbo->getDataBlock(), name, getAIInfo()->mObj->getIdString()); //legacy support for object db callbacks
}

void AIController::initPersistFields()
{
   addProtectedField("ControllerData", TYPEID< AIControllerData >(), Offset(mControllerData, AIController),
      &setControllerDataProperty, &defaultProtectedGetFn,
      "Script datablock used for game objects.");
   addFieldV("MoveSpeed", TypeRangedF32, Offset(mMovement.mMoveSpeed, AIController), &CommonValidators::PositiveFloat,
      "@brief default move sepeed.");
}

bool AIController::setControllerDataProperty(void* obj, const char* index, const char* db)
{
   if (db == NULL || !db[0])
   {
      Con::errorf("AIController::setControllerDataProperty - Can't unset ControllerData on AIController objects");
      return false;
   }

   AIController* object = static_cast<AIController*>(obj);
   AIControllerData* data;
   if (Sim::findObject(db, data))
   {
      object->mControllerData = data;
      return true;
   }
   Con::errorf("AIController::setControllerDataProperty - Could not find ControllerData \"%s\"", db);
   return false;
}

void AIController::setGoal(AIInfo* targ)
{
   if (mGoal) { delete(mGoal); mGoal = NULL; }

   if (targ->mObj.isValid())
   {
      delete(mGoal);
      mGoal = new AIGoal(this, targ->mObj, targ->mRadius);
   }
   else if (targ->mPosSet)
   {
      delete(mGoal);
      mGoal = new AIGoal(this, targ->mPosition, targ->mRadius);
   }
}

void AIController::setGoal(Point3F loc, F32 rad)
{
   if (mGoal) delete(mGoal);
   mGoal = new AIGoal(this, loc, rad);
}

void AIController::setGoal(SimObjectPtr<SceneObject> objIn, F32 rad)
{
   if (mGoal) delete(mGoal);
   mGoal = new AIGoal(this, objIn, rad);
}

void AIController::setAim(Point3F loc, F32 rad, Point3F offset)
{
   if (mAimTarget) delete(mAimTarget);
   mAimTarget = new AIAimTarget(this, loc, rad);
   mAimTarget->mAimOffset = offset;
}

void AIController::setAim(SimObjectPtr<SceneObject> objIn, F32 rad, Point3F offset)
{
   if (mAimTarget) delete(mAimTarget);
   mAimTarget = new AIAimTarget(this, objIn, rad);
   mAimTarget->mAimOffset = offset;
}

bool AIController::getAIMove(Move* movePtr)
{
   *movePtr = NullMove;
   ShapeBase* sbo = dynamic_cast<ShapeBase*>(getAIInfo()->mObj.getPointer());
   if (!sbo) return false;

   // Use the eye as the current position.
   MatrixF eye;
   sbo->getEyeTransform(&eye);
   Point3F location = eye.getPosition();
   Point3F rotation = sbo->getTransform().toEuler();

   // Test for target location in sight if it's an object. The LOS is
   // run from the eye position to the center of the object's bounding,
   // which is not very accurate.
   if (getAim() && getAim()->mObj)
   {
      GameBase* gbo = dynamic_cast<GameBase*>(getAIInfo()->mObj.getPointer());
      if (getAim()->checkInLos(gbo))
      {
         if (!getAim()->mTargetInLOS)
         {
            throwCallback("onTargetEnterLOS");
            getAim()->mTargetInLOS = true;
         }
      }
      else if (getAim()->mTargetInLOS)
      {
         throwCallback("onTargetExitLOS");
         getAim()->mTargetInLOS = false;
      }
   }

   if (sbo->getDamageState() == ShapeBase::Enabled && getGoal())
   {
#ifdef TORQUE_NAVIGATION_ENABLED
      if (mMovement.mMoveState != ModeStop)
         getNav()->updateNavMesh();

      if (getNav()->mPathData.path.isNull())
      {
         if (getGoal()->getDist() > mControllerData->mFollowTolerance)
         {
            if (getGoal()->mObj.isValid())
               getNav()->followObject(getGoal()->mObj, mControllerData->mFollowTolerance);
            else if (getGoal()->mPosSet)
               getNav()->setPathDestination(getGoal()->getPosition(true));
         }
      }
      else
      {
         if (getGoal()->getDist() > mControllerData->mFollowTolerance)
         {
            SceneObject* obj = getAIInfo()->mObj->getObjectMount();
            if (!obj)
            {
               obj = getAIInfo()->mObj;
            }
            
            Point3F start = obj->getPosition();
            Point3F end = start;
            start.z = obj->getBoxCenter().z;
            end.z -= mControllerData->mHeightTolerance;

            obj->disableCollision();
            // Only repath if not already adjusted and on risky ground
            RayInfo info;
            if (obj->getContainer()->castRay(start, end, StaticShapeObjectType, &info))
            {
               getNav()->repath();
            }
            obj->enableCollision();
            getGoal()->mInRange = false;
         }
         if (getGoal()->getDist() < mControllerData->mFollowTolerance )
         {
            getNav()->clearPath();
            mMovement.mMoveState = ModeStop;

            if (!getGoal()->mInRange)
            {
               getGoal()->mInRange = true;
               throwCallback("onTargetInRange");
            }
            else getGoal()->mInRange = false;
         }
         else
         {
            if (getGoal()->getDist() < mControllerData->mAttackRadius )
            {
               if (!getGoal()->mInFiringRange)
               {
                  getGoal()->mInFiringRange = true;
                  throwCallback("onTargetInFiringRange");
               }
            }
            else getGoal()->mInFiringRange = false;
         }
      }
#else
      if (getGoal()->getDist() > mControllerData->mFollowTolerance)
      {
         if (getGoal()->mObj.isValid())
            getNav()->followObject(getGoal()->mObj, mControllerData->mFollowTolerance);
         else if (getGoal()->mPosSet)
            getNav()->setPathDestination(getGoal()->getPosition(true));

         getGoal()->mInRange = false;
      }
      if (getGoal()->getDist() < mControllerData->mFollowTolerance)
      {
         mMovement.mMoveState = ModeStop;

         if (!getGoal()->mInRange)
         {
            getGoal()->mInRange = true;
            throwCallback("onTargetInRange");
         }
         else getGoal()->mInRange = false;
      }
      else
      {
         if (getGoal()->getDist() < mControllerData->mAttackRadius)
         {
            if (!getGoal()->mInFiringRange)
            {
               getGoal()->mInFiringRange = true;
               throwCallback("onTargetInFiringRange");
            }
         }
         else getGoal()->mInFiringRange = false;
      }
#endif // TORQUE_NAVIGATION_ENABLED
   }
   // Orient towards the aim point, aim object, or towards
   // our destination.
   if (getAim() || mMovement.mMoveState != ModeStop)
   {
      // Update the aim position if we're aiming for an object or explicit position
      if (getAim())
         mMovement.mAimLocation = getAim()->getPosition();
      else
         mMovement.mAimLocation = getNav()->getMoveDestination();

      mControllerData->resolveYawPtr(this, location, movePtr);
      mControllerData->resolvePitchPtr(this, location, movePtr);
      mControllerData->resolveRollPtr(this, location, movePtr);

      if (mMovement.mMoveState != AIController::ModeStop)
      {
         F32 xDiff = getNav()->getMoveDestination().x - location.x;
         F32 yDiff = getNav()->getMoveDestination().y - location.y;
         if (mFabs(xDiff) < mControllerData->mMoveTolerance && mFabs(yDiff) < mControllerData->mMoveTolerance)
         {
            getNav()->onReachDestination();
         }
         else
         {
            mControllerData->resolveSpeedPtr(this, location, movePtr);
            mControllerData->resolveStuckPtr(this);
         }
      }
   }

   mControllerData->resolveTriggerStatePtr(this, movePtr);

   getAIInfo()->mLastPos = getAIInfo()->getPosition();
   return true;
}

void AIController::clearCover()
{
   // Notify cover that we are no longer on our way.
   if (getCover() && !getCover()->mCoverPoint.isNull())
      getCover()->mCoverPoint->setOccupied(false);
   SAFE_DELETE(mCover);
}

void AIController::Movement::stopMove()
{
   mMoveState = ModeStop;
#ifdef TORQUE_NAVIGATION_ENABLED
   getCtrl()->getNav()->clearPath();
   getCtrl()->clearCover();
   getCtrl()->getNav()->clearFollow();
#endif
}
void AIController::Movement::onStuck()
{
   mMoveState = AIController::ModeStuck;
   getCtrl()->throwCallback("onMoveStuck");
#ifdef TORQUE_NAVIGATION_ENABLED
   if (!getCtrl()->getNav()->getPath().isNull())
      getCtrl()->getNav()->repath();
#endif
}

DefineEngineMethod(AIController, setMoveSpeed, void, (F32 speed), ,
   "@brief Sets the move speed for an AI object.\n\n"

   "@param speed A speed multiplier between 0.0 and 1.0.  "
   "This is multiplied by the AIController controlled object's base movement rates (as defined in "
   "its PlayerData datablock)\n\n"

   "@see getMoveDestination()\n")
{
   object->mMovement.setMoveSpeed(speed);
}

DefineEngineMethod(AIController, getMoveSpeed, F32, (), ,
   "@brief Gets the move speed of an AI object.\n\n"

   "@return A speed multiplier between 0.0 and 1.0.\n\n"

   "@see setMoveSpeed()\n")
{
   return object->mMovement.getMoveSpeed();
}

DefineEngineMethod(AIController, stop, void, (), ,
   "@brief Tells the AIController controlled object to stop moving.\n\n")
{
   object->mMovement.stopMove();
}


/**
 * Set the state of a movement trigger.
 *
 * @param slot The trigger slot to set
 * @param isSet set/unset the trigger
 */
void AIController::TriggerState::setMoveTrigger(U32 slot, const bool isSet)
{
   if (slot >= MaxTriggerKeys)
   {
      Con::errorf("Attempting to set an invalid trigger slot (%i)", slot);
   }
   else
   {
      mMoveTriggers[slot] = isSet;   // set the trigger
      mControllerRef->getAIInfo()->mObj->setMaskBits(ShapeBase::NoWarpMask);         // force the client to updateMove
   }
}

DefineEngineMethod(AIController, setMoveTrigger, void, (U32 slot, bool state), (true),
   "@brief Sets a movement trigger on an AI object.\n\n"
   "@param slot The trigger slot to set.\n"
   "@see getMoveTrigger()\n"
   "@see clearMoveTrigger()\n"
   "@see clearMoveTriggers()\n")
{
   object->mTriggerState.setMoveTrigger(slot, state);
}

/**
 * Get the state of a movement trigger.
 *
 * @param slot The trigger slot to query
 * @return True if the trigger is set, false if it is not set
 */
bool AIController::TriggerState::getMoveTrigger(U32 slot) const
{
   if (slot >= MaxTriggerKeys)
   {
      Con::errorf("Attempting to get an invalid trigger slot (%i)", slot);
      return false;
   }
   else
   {
      return mMoveTriggers[slot];
   }
}

/**
 * Clear the trigger state for all movement triggers.
 */
void AIController::TriggerState::clearMoveTriggers()
{
   for (U32 i = 0; i < MaxTriggerKeys; i++)
      setMoveTrigger(i, false);
}

//-----------------------------------------------------------------------------

IMPLEMENT_CO_DATABLOCK_V1(AIControllerData);
void AIControllerData::resolveYaw(AIController* obj, Point3F location, Move* move)
{
   F32 xDiff = obj->mMovement.mAimLocation.x - location.x;
   F32 yDiff = obj->mMovement.mAimLocation.y - location.y;
   Point3F rotation = obj->getAIInfo()->mObj->getTransform().toEuler();

   if (!mIsZero(xDiff) || !mIsZero(yDiff))
   {
      // First do Yaw
      // use the cur yaw between -Pi and Pi
      F32 curYaw = rotation.z;
      while (curYaw > M_2PI_F)
         curYaw -= M_2PI_F;
      while (curYaw < -M_2PI_F)
         curYaw += M_2PI_F;

      // find the yaw offset
      F32 newYaw = mAtan2(xDiff, yDiff);
      F32 yawDiff = newYaw - curYaw;

      // make it between 0 and 2PI
      if (yawDiff < 0.0f)
         yawDiff += M_2PI_F;
      else if (yawDiff >= M_2PI_F)
         yawDiff -= M_2PI_F;

      // now make sure we take the short way around the circle
      if (yawDiff > M_PI_F)
         yawDiff -= M_2PI_F;
      else if (yawDiff < -M_PI_F)
         yawDiff += M_2PI_F;

      move->yaw = yawDiff;
   }
}


void AIControllerData::resolveRoll(AIController* obj, Point3F location, Move* movePtr)
{
}

void AIControllerData::resolveSpeed(AIController* obj, Point3F location, Move* movePtr)
{
   F32 xDiff = obj->getNav()->getMoveDestination().x - location.x;
   F32 yDiff = obj->getNav()->getMoveDestination().y - location.y;
   Point3F rotation = obj->getAIInfo()->mObj->getTransform().toEuler();

   // Build move direction in world space
   if (mIsZero(xDiff))
      movePtr->y = (location.y > obj->getNav()->getMoveDestination().y) ? -1.0f : 1.0f;
   else
   {
      if (mIsZero(yDiff))
         movePtr->x = (location.x > obj->getNav()->getMoveDestination().x) ? -1.0f : 1.0f;
      else
      {
         if (mFabs(xDiff) > mFabs(yDiff))
         {
            F32 value = mFabs(yDiff / xDiff);
            movePtr->y = (location.y > obj->getNav()->getMoveDestination().y) ? -value : value;
            movePtr->x = (location.x > obj->getNav()->getMoveDestination().x) ? -1.0f : 1.0f;
         }
         else
         {
            F32 value = mFabs(xDiff / yDiff);
            movePtr->x = (location.x > obj->getNav()->getMoveDestination().x) ? -value : value;
            movePtr->y = (location.y > obj->getNav()->getMoveDestination().y) ? -1.0f : 1.0f;
         }
      }
   }
   // Rotate the move into object space (this really only needs
   // a 2D matrix)
   Point3F newMove;
   MatrixF moveMatrix;
   moveMatrix.set(EulerF(0.0f, 0.0f, -(rotation.z + movePtr->yaw)));
   moveMatrix.mulV(Point3F(movePtr->x, movePtr->y, 0.0f), &newMove);
   movePtr->x = newMove.x;
   movePtr->y = newMove.y;

   // Set movement speed.  We'll slow down once we get close
   // to try and stop on the spot...
   if (obj->mMovement.mMoveSlowdown)
   {
      F32 speed = obj->mMovement.mMoveSpeed;
      F32 dist = mSqrt(xDiff * xDiff + yDiff * yDiff);
      F32 maxDist = mMoveTolerance * 2;
      if (dist < maxDist)
         speed *= dist / maxDist;
      movePtr->x *= speed;
      movePtr->y *= speed;
   }
   else
   {
      movePtr->x *= obj->mMovement.mMoveSpeed;
      movePtr->y *= obj->mMovement.mMoveSpeed;
   }
}

void AIControllerData::resolveTriggerState(AIController* obj, Move* movePtr)
{
   //check for scripted overides
   for (U32 slot = 0; slot < MaxTriggerKeys; slot++)
   {      
      movePtr->trigger[slot] = obj->mTriggerState.mMoveTriggers[slot];
   }
}

void AIControllerData::resolveStuck(AIController* obj)
{
   if (obj->mMovement.mMoveState < AIController::ModeSlowing) return;
   if (!obj->getGoal()) return;
   ShapeBase* sbo = dynamic_cast<ShapeBase*>(obj->getAIInfo()->mObj.getPointer());
   // Don't check for ai stuckness if animation during
   // an anim-clip effect override.
   if (sbo->getDamageState() == ShapeBase::Enabled && !(sbo->anim_clip_flags & ShapeBase::ANIM_OVERRIDDEN) && !sbo->isAnimationLocked())
   {
      // We should check to see if we are stuck...
      F32 locationDelta = (obj->getAIInfo()->getPosition() - obj->getAIInfo()->mLastPos).len();
      if (locationDelta < mMoveStuckTolerance)
      {
         if (obj->mMovement.mMoveStuckTestCountdown > 0)
            --obj->mMovement.mMoveStuckTestCountdown;
         else
         {
            // If we are slowing down, then it's likely that our location delta will be less than
            // our move stuck tolerance. Because we can be both slowing and stuck
            // we should TRY to check if we've moved. This could use better detection.
            if (obj->mMovement.mMoveState != AIController::ModeSlowing || locationDelta == 0)
            {
               obj->mMovement.onStuck();
               obj->mMovement.mMoveStuckTestCountdown = obj->mControllerData->mMoveStuckTestDelay;
            }
         }
      }
   }
}

AIControllerData::AIControllerData()
{
   mMoveTolerance = 0.25f;
   mAttackRadius = 2.0f;
   mMoveStuckTolerance = 0.01f;
   mMoveStuckTestDelay = 30;
   mHeightTolerance = 0.1f;
   mFollowTolerance = 1.0f;

#ifdef TORQUE_NAVIGATION_ENABLED
   mLinkTypes = LinkData(AllFlags);
   mFilter.setIncludeFlags(mLinkTypes.getFlags());
   mFilter.setExcludeFlags(0);
   mAreaCosts.setSize(PolyAreas::NumAreas);
   mAreaCosts.fill(1.0f);
   mNavSize = AINavigation::Regular;
   mFlocking.mChance = 90;
   mFlocking.mMin = 1.0f;
   mFlocking.mMax = 3.0f;
   mFlocking.mSideStep = 0.01f;
#endif
   resolveYawPtr.bind(this, &AIControllerData::resolveYaw);
   resolvePitchPtr.bind(this, &AIControllerData::resolvePitch);
   resolveRollPtr.bind(this, &AIControllerData::resolveRoll);
   resolveSpeedPtr.bind(this, &AIControllerData::resolveSpeed);
   resolveTriggerStatePtr.bind(this, &AIControllerData::resolveTriggerState);
   resolveStuckPtr.bind(this, &AIControllerData::resolveStuck);
}

AIControllerData::AIControllerData(const AIControllerData& other, bool temp_clone) : SimDataBlock(other, temp_clone)
{
   mMoveTolerance = other.mMoveTolerance;
   mAttackRadius = other.mAttackRadius;
   mMoveStuckTolerance = other.mMoveStuckTolerance;
   mMoveStuckTestDelay = other.mMoveStuckTestDelay;
   mHeightTolerance = other.mHeightTolerance;
   mFollowTolerance = other.mFollowTolerance;

#ifdef TORQUE_NAVIGATION_ENABLED
   mLinkTypes = other.mLinkTypes;
   mFilter = other.mFilter;
   mAreaCosts = other.mAreaCosts;
   mNavSize = other.mNavSize;
   mFlocking.mChance = other.mFlocking.mChance;
   mFlocking.mMin = other.mFlocking.mMin;
   mFlocking.mMax = other.mFlocking.mMax;
   mFlocking.mSideStep = other.mFlocking.mSideStep;
#endif

   resolveYawPtr.bind(this, &AIControllerData::resolveYaw);
   resolvePitchPtr.bind(this, &AIControllerData::resolvePitch);
   resolveRollPtr.bind(this, &AIControllerData::resolveRoll);
   resolveSpeedPtr.bind(this, &AIControllerData::resolveSpeed);
   resolveTriggerStatePtr.bind(this, &AIControllerData::resolveTriggerState);
   resolveStuckPtr.bind(this, &AIControllerData::resolveStuck);
}

void AIControllerData::initPersistFields()
{
   docsURL;
   addGroup("AI");

   addFieldV("moveTolerance", TypeRangedF32, Offset(mMoveTolerance, AIControllerData), &CommonValidators::PositiveFloat,
      "@brief Distance from destination before stopping.\n\n"
      "When the AIController controlled object is moving to a given destination it will move to within "
      "this distance of the destination and then stop.  By providing this tolerance "
      "it helps the AIController controlled object from never reaching its destination due to minor obstacles, "
      "rounding errors on its position calculation, etc.  By default it is set to 0.25.\n");

   addFieldV("followTolerance", TypeRangedF32, Offset(mFollowTolerance, AIControllerData), &CommonValidators::PositiveFloat,
      "@brief Distance from destination before stopping.\n\n"
      "When the AIController controlled object is moving to a given destination it will move to within "
      "this distance of the destination and then stop.  By providing this tolerance "
      "it helps the AIController controlled object from never reaching its destination due to minor obstacles, "
      "rounding errors on its position calculation, etc.  By default it is set to 0.25.\n");

   addFieldV("AttackRadius", TypeRangedF32, Offset(mAttackRadius, AIControllerData), &CommonValidators::PositiveFloat,
      "@brief Distance considered in firing range for callback purposes.");

   addFieldV("moveStuckTolerance", TypeRangedF32, Offset(mMoveStuckTolerance, AIControllerData), &CommonValidators::PositiveFloat,
      "@brief Distance tolerance on stuck check.\n\n"
      "When the AIController controlled object controlled object is moving to a given destination, if it ever moves less than "
      "this tolerance during a single tick, the AIController controlled object is considered stuck.  At this point "
      "the onMoveStuck() callback is called on the datablock.\n");

   addFieldV("HeightTolerance", TypeRangedF32, Offset(mHeightTolerance, AIControllerData), &CommonValidators::PositiveFloat,
      "@brief Distance from destination before stopping.\n\n"
      "When the AIController controlled object is moving to a given destination it will move to within "
      "this distance of the destination and then stop.  By providing this tolerance "
      "it helps the AIController controlled object from never reaching its destination due to minor obstacles, "
      "rounding errors on its position calculation, etc.  By default it is set to 0.25.\n");
   
   addFieldV("moveStuckTestDelay", TypeRangedS32, Offset(mMoveStuckTestDelay, AIControllerData), &CommonValidators::PositiveInt,
      "@brief The number of ticks to wait before testing if the AIController controlled object is stuck.\n\n"
      "When the AIController controlled object is asked to move, this property is the number of ticks to wait "
      "before the AIController controlled object starts to check if it is stuck.  This delay allows the AIController controlled object "
      "to accelerate to full speed without its initial slow start being considered as stuck.\n"
      "@note Set to zero to have the stuck test start immediately.\n");
   endGroup("AI");

#ifdef TORQUE_NAVIGATION_ENABLED
   addGroup("Pathfinding");
   addFieldV("FlockChance", TypeRangedS32, Offset(mFlocking.mChance, AIControllerData), &CommonValidators::S32Percent,
      "@brief chance of flocking.");
   addFieldV("FlockMin", TypeRangedF32, Offset(mFlocking.mMin, AIControllerData), &CommonValidators::PositiveFloat,
      "@brief min flocking separation distance.");
   addFieldV("FlockMax", TypeRangedF32, Offset(mFlocking.mMax, AIControllerData), &CommonValidators::PositiveFloat,
      "@brief max flocking clustering distance.");
   addFieldV("FlockSideStep", TypeRangedF32, Offset(mFlocking.mSideStep, AIControllerData), &CommonValidators::PositiveFloat,
      "@brief Distance from destination before we stop moving out of the way.");

   addField("areaCosts", TypeF32Vector, Offset(mAreaCosts, AIControllerData),
      "Vector of costs for each PolyArea.");
   addField("allowWalk", TypeBool, Offset(mLinkTypes.walk, AIControllerData),
      "Allow the character to walk on dry land.");
   addField("allowJump", TypeBool, Offset(mLinkTypes.jump, AIControllerData),
      "Allow the character to use jump links.");
   addField("allowDrop", TypeBool, Offset(mLinkTypes.drop, AIControllerData),
      "Allow the character to use drop links.");
   addField("allowSwim", TypeBool, Offset(mLinkTypes.swim, AIControllerData),
      "Allow the character to move in water.");
   addField("allowLedge", TypeBool, Offset(mLinkTypes.ledge, AIControllerData),
      "Allow the character to jump ledges.");
   addField("allowClimb", TypeBool, Offset(mLinkTypes.climb, AIControllerData),
      "Allow the character to use climb links.");
   addField("allowTeleport", TypeBool, Offset(mLinkTypes.teleport, AIControllerData),
      "Allow the character to use teleporters.");

   endGroup("Pathfinding");
#endif // TORQUE_NAVIGATION_ENABLED

   Parent::initPersistFields();
}

void AIControllerData::packData(BitStream* stream)
{
   Parent::packData(stream);
   stream->write(mMoveTolerance);
   stream->write(mAttackRadius);
   stream->write(mMoveStuckTolerance);
   stream->write(mMoveStuckTestDelay);
   stream->write(mHeightTolerance);
   stream->write(mFollowTolerance);

#ifdef TORQUE_NAVIGATION_ENABLED
   //enums
   stream->write(mAreaCosts.size());
   for (U32 i = 0; i < mAreaCosts.size(); i++) {
      stream->write(mAreaCosts[i]);
   }
   stream->write(mLinkTypes.getFlags());
   stream->write((U32)mNavSize);
   // end enums
   stream->write(mFlocking.mChance);
   stream->write(mFlocking.mMin);
   stream->write(mFlocking.mMax);
   stream->write(mFlocking.mSideStep);
#endif // TORQUE_NAVIGATION_ENABLED
};

void AIControllerData::unpackData(BitStream* stream)
{
   Parent::unpackData(stream);

   stream->read(&mMoveTolerance);
   stream->read(&mAttackRadius);
   stream->read(&mMoveStuckTolerance);
   stream->read(&mMoveStuckTestDelay);
   stream->read(&mHeightTolerance);
   stream->read(&mFollowTolerance);

#ifdef TORQUE_NAVIGATION_ENABLED
   U32 num;
   stream->read(&num);
   mAreaCosts.setSize(num);
   for (U32 i = 0; i < num; i++)
   {
      stream->read(&mAreaCosts[i]);
   }
   //enums
   U16 linkFlags;
   stream->read(&linkFlags);
   mLinkTypes = LinkData(linkFlags);
   mFilter.setIncludeFlags(mLinkTypes.getFlags());
   mFilter.setExcludeFlags(mLinkTypes.getExcludeFlags());
   for (U32 i = 0; i < PolyAreas::NumAreas; i++)
   {
      mFilter.setAreaCost((PolyAreas)i, mAreaCosts[i]);
   }
   U32 navSize;
   stream->read(&navSize);
   mNavSize = (AINavigation::NavSize)(navSize);   
   // end enums
   stream->read(&(mFlocking.mChance));
   stream->read(&(mFlocking.mMin));
   stream->read(&(mFlocking.mMax));
   stream->read(&(mFlocking.mSideStep));
#endif // TORQUE_NAVIGATION_ENABLED
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
IMPLEMENT_CO_DATABLOCK_V1(AIPlayerControllerData);
void AIPlayerControllerData::resolvePitch(AIController* obj, Point3F location, Move* movePtr)
{
   Player* po = dynamic_cast<Player*>(obj->getAIInfo()->mObj.getPointer());
   if (!po) return;//not a player

   if (obj->getAim() || obj->mMovement.mMoveState != AIController::ModeStop)
   {
      // Next do pitch.
      if (!obj->getAim())
      {
         // Level out if were just looking at our next way point.
         Point3F headRotation = po->getHeadRotation();
         movePtr->pitch = -headRotation.x;
      }
      else
      {
         F32 xDiff = obj->mMovement.mAimLocation.x - location.x;
         F32 yDiff = obj->mMovement.mAimLocation.y - location.y;
         // This should be adjusted to run from the
         // eye point to the object's center position. Though this
         // works well enough for now.
         F32 vertDist = obj->mMovement.mAimLocation.z - location.z;
         F32 horzDist = mSqrt(xDiff * xDiff + yDiff * yDiff);
         F32 newPitch = mAtan2(horzDist, vertDist) - (M_PI_F / 2.0f);
         if (mFabs(newPitch) > 0.01f)
         {
            Point3F headRotation = po->getHeadRotation();
            movePtr->pitch = newPitch - headRotation.x;
         }
      }
   }
   else
   {
      // Level out if we're not doing anything else
      Point3F headRotation = po->getHeadRotation();
      movePtr->pitch = -headRotation.x;
   }
}

void AIPlayerControllerData::resolveTriggerState(AIController* obj, Move* movePtr)
{
   Parent::resolveTriggerState(obj, movePtr);
#ifdef TORQUE_NAVIGATION_ENABLED
   if (obj->getNav()->mJump == AINavigation::Now)
   {
      movePtr->trigger[2] = true;
      obj->getNav()->mJump = AINavigation::None;
   }
   else if (obj->getNav()->mJump == AINavigation::Ledge)
   {
      // If we're not touching the ground, jump!
      RayInfo info;
      if (!obj->getAIInfo()->mObj->getContainer()->castRay(obj->getAIInfo()->getPosition(), obj->getAIInfo()->getPosition() - Point3F(0, 0, 0.4f), StaticShapeObjectType, &info))
      {
         movePtr->trigger[2] = true;
         obj->getNav()->mJump = AINavigation::None;
      }
   }
#endif // TORQUE_NAVIGATION_ENABLED
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
IMPLEMENT_CO_DATABLOCK_V1(AIWheeledVehicleControllerData);

void AIWheeledVehicleControllerData::resolveYaw(AIController* obj, Point3F location, Move* movePtr)
{
   if (obj->mMovement.mMoveState < AIController::ModeSlowing) return;
   WheeledVehicle* wvo = dynamic_cast<WheeledVehicle*>(obj->getAIInfo()->mObj.getPointer());
   if (!wvo)
   {
      //cover the case of a connection controling an object in turn controlling another
      if (obj->getAIInfo()->mObj->getObjectMount())
         wvo = dynamic_cast<WheeledVehicle*>(obj->getAIInfo()->mObj->getObjectMount());
   }
   if (!wvo) return;//not a WheeledVehicle

   F32 lastYaw = wvo->getSteering().x;

   Point3F right = wvo->getTransform().getRightVector();
   right.normalize();
   Point3F aimLoc = obj->mMovement.mAimLocation;

   // Get the AI to Target vector and normalize it.
   Point3F toTarg = (location + wvo->getVelocity() * TickSec) - aimLoc;
   toTarg.normalize();

   F32 dotYaw = -mDot(right, toTarg);
   movePtr->yaw = -lastYaw;

   VehicleData* vd = (VehicleData*)(wvo->getDataBlock());
   F32 maxSteeringAngle = vd->maxSteeringAngle;

   if (mFabs(dotYaw) > maxSteeringAngle*1.5f)
      dotYaw *= -1.0f;

   if (dotYaw > maxSteeringAngle) dotYaw = maxSteeringAngle;
   if (dotYaw < -maxSteeringAngle) dotYaw = -maxSteeringAngle;

   if (mFabs(dotYaw) > 0.05f)
      movePtr->yaw = dotYaw - lastYaw;
};

void AIWheeledVehicleControllerData::resolveSpeed(AIController* obj, Point3F location, Move* movePtr)
{
   if (obj->mMovement.mMoveState < AIController::ModeSlowing) return;
   WheeledVehicle* wvo = dynamic_cast<WheeledVehicle*>(obj->getAIInfo()->mObj.getPointer());
   if (!wvo)
   {
      //cover the case of a connection controling an object in turn controlling another
      if (obj->getAIInfo()->mObj->getObjectMount())
         wvo = dynamic_cast<WheeledVehicle*>(obj->getAIInfo()->mObj->getObjectMount());
   }
   if (!wvo) return;//not a WheeledVehicle

   Parent::resolveSpeed(obj, location, movePtr);

   VehicleData* db =  static_cast<VehicleData *>(wvo->getDataBlock());
   movePtr->x = 0;
   movePtr->y *= mMax((db->maxSteeringAngle-mFabs(movePtr->yaw) / db->maxSteeringAngle),0.75f);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

IMPLEMENT_CO_DATABLOCK_V1(AIFlyingVehicleControllerData);

void AIFlyingVehicleControllerData::initPersistFields()
{
   docsURL;
   addGroup("AI");

   addFieldV("FlightFloor", TypeRangedF32, Offset(mFlightFloor, AIFlyingVehicleControllerData), &CommonValidators::F32Range,
      "@brief Min height we can target.");

   addFieldV("FlightCeiling", TypeRangedF32, Offset(mFlightCeiling, AIFlyingVehicleControllerData), &CommonValidators::F32Range,
      "@brief Max height we can target.");

   endGroup("AI");

   Parent::initPersistFields();
}

AIFlyingVehicleControllerData::AIFlyingVehicleControllerData(const AIFlyingVehicleControllerData& other, bool temp_clone) : AIControllerData(other, temp_clone)
{
   mFlightCeiling = other.mFlightCeiling;
   mFlightFloor = other.mFlightFloor;
   resolveYawPtr.bind(this, &AIFlyingVehicleControllerData::resolveYaw);
   resolvePitchPtr.bind(this, &AIFlyingVehicleControllerData::resolvePitch);
   resolveSpeedPtr.bind(this, &AIFlyingVehicleControllerData::resolveSpeed);
}

void AIFlyingVehicleControllerData::resolveYaw(AIController* obj, Point3F location, Move* movePtr)
{
   if (obj->mMovement.mMoveState < AIController::ModeSlowing) return;
   FlyingVehicle* fvo = dynamic_cast<FlyingVehicle*>(obj->getAIInfo()->mObj.getPointer());
   if (!fvo)
   {
      //cover the case of a connection controling an object in turn controlling another
      if (obj->getAIInfo()->mObj->getObjectMount())
         fvo = dynamic_cast<FlyingVehicle*>(obj->getAIInfo()->mObj->getObjectMount());
   }
   if (!fvo) return;//not a FlyingVehicle

   Point3F right = fvo->getTransform().getRightVector();
   right.normalize();

   // Get the Target to AI vector and normalize it.
   Point3F aimLoc = obj->mMovement.mAimLocation;
   aimLoc.z = mClampF(aimLoc.z, mFlightFloor, mFlightCeiling);
   Point3F toTarg = (location + fvo->getVelocity() * TickSec) - aimLoc;
   toTarg.normalize();

   movePtr->yaw = 0;
   F32 dotYaw = -mDot(right, toTarg);
   if (mFabs(dotYaw) > 0.05f)
      movePtr->yaw = dotYaw;
};

void AIFlyingVehicleControllerData::resolvePitch(AIController* obj, Point3F location, Move* movePtr)
{
   if (obj->mMovement.mMoveState < AIController::ModeSlowing) return;
   FlyingVehicle* fvo = dynamic_cast<FlyingVehicle*>(obj->getAIInfo()->mObj.getPointer());
   if (!fvo)
   {
      //cover the case of a connection controling an object in turn controlling another
      if (obj->getAIInfo()->mObj->getObjectMount())
         fvo = dynamic_cast<FlyingVehicle*>(obj->getAIInfo()->mObj->getObjectMount());
   }
   if (!fvo) return;//not a FlyingVehicle

   Point3F up = fvo->getTransform().getUpVector();
   up.normalize();


   // Get the Target to AI vector and normalize it.
   Point3F aimLoc = obj->mMovement.mAimLocation;
   aimLoc.z = mClampF(aimLoc.z, mFlightFloor, mFlightCeiling);
   Point3F toTarg = (location + fvo->getVelocity() * TickSec) - aimLoc;
   toTarg.normalize();

   movePtr->pitch = 0.0f;
   F32 dotPitch = mDot(up, toTarg);
   if (mFabs(dotPitch) > 0.05f)
         movePtr->pitch = dotPitch * M_2PI_F;
         
}

void AIFlyingVehicleControllerData::resolveSpeed(AIController* obj, Point3F location, Move* movePtr)
{
   if (obj->mMovement.mMoveState < AIController::ModeSlowing) return;
   FlyingVehicle* fvo = dynamic_cast<FlyingVehicle*>(obj->getAIInfo()->mObj.getPointer());
   if (!fvo)
   {
      //cover the case of a connection controling an object in turn controlling another
      if (obj->getAIInfo()->mObj->getObjectMount())
         fvo = dynamic_cast<FlyingVehicle*>(obj->getAIInfo()->mObj->getObjectMount());
   }
   if (!fvo) return;//not a FlyingVehicle

   movePtr->x = 0;
   movePtr->y = obj->mMovement.mMoveSpeed;
}
