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


IMPLEMENT_CONOBJECT(AIController);

//-----------------------------------------------------------------------------
void AIController::throwCallback(const char* name)
{
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

#ifdef TORQUE_NAVIGATION_ENABLED
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

#ifdef TORQUE_NAVIGATION_ENABLED
   if (sbo->getDamageState() == ShapeBase::Enabled)
   {
      if (mMovement.mMoveState != ModeStop)
         getNav()->updateNavMesh();
      if (getGoal() && !getGoal()->mObj.isNull())
      {
         if (getNav()->mPathData.path.isNull())
         {
            if (getGoal()->getDist() > mControllerData->mFollowTolerance)
               getNav()->followObject(getGoal()->mObj, mControllerData->mFollowTolerance);
         }
         else
         {
            if (getGoal()->getDist() > mControllerData->mFollowTolerance)
               getNav()->repath();

            if (getGoal()->getDist() < mControllerData->mFollowTolerance)
            {
               getNav()->clearPath();
               mMovement.mMoveState = ModeStop;
               throwCallback("onTargetInRange");
            }
            else if (getGoal()->getDist() < mControllerData->mAttackRadius)
            {
               throwCallback("onTargetInFiringRange");
            }
         }
      }
   }
#endif // TORQUE_NAVIGATION_ENABLED

   // Orient towards the aim point, aim object, or towards
   // our destination.
   if (getAim() || mMovement.mMoveState != ModeStop)
   {
      // Update the aim position if we're aiming for an object or explicit position
      if (getAim())
         mMovement.mAimLocation = getAim()->getPosition();
      else
         mMovement.mAimLocation = getNav()->mMoveDestination;

      mControllerData->resolveYaw(this, location, movePtr);
      mControllerData->resolvePitch(this, location, movePtr);
      mControllerData->resolveRoll(this, location, movePtr);
      mControllerData->resolveSpeed(this, location, movePtr);
      mControllerData->resolveStuck(this);
   }

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

   /*
   // Replicate the trigger state into the move so that
   // triggers can be controlled from scripts.
   for (U32 i = 0; i < MaxTriggerKeys; i++)
      movePtr->trigger[i] = getImageTriggerState(i);
   */

#ifdef TORQUE_NAVIGATION_ENABLED
   if (getNav()->mJump == AINavigation::Now)
   {
      movePtr->trigger[2] = true;
      getNav()->mJump = AINavigation::None;
   }
   else if (getNav()->mJump == AINavigation::Ledge)
   {
      // If we're not touching the ground, jump!
      RayInfo info;
      if (!getAIInfo()->mObj->getContainer()->castRay(getAIInfo()->getPosition(), getAIInfo()->getPosition() - Point3F(0, 0, 0.4f), StaticShapeObjectType, &info))
      {
         movePtr->trigger[2] = true;
         getNav()->mJump = AINavigation::None;
      }
   }
#endif // TORQUE_NAVIGATION_ENABLED

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
   mControllerRef->getNav()->clearPath();
   mControllerRef->clearCover();
   mControllerRef->getNav()->clearFollow();
#endif
}
void AIController::Movement::onStuck()
{
   mControllerRef->throwCallback("onMoveStuck");
#ifdef TORQUE_NAVIGATION_ENABLED
   if (!mControllerRef->getNav()->getPath().isNull())
      mControllerRef->getNav()->repath();
#endif
}

DefineEngineMethod(AIController, setMoveSpeed, void, (F32 speed), ,
   "@brief Sets the move speed for an AI object.\n\n"

   "@param speed A speed multiplier between 0.0 and 1.0.  "
   "This is multiplied by the AIPlayer's base movement rates (as defined in "
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
   "@brief Tells the AIPlayer to stop moving.\n\n")
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
   // Move towards the destination
   if (obj->mMovement.mMoveState != AIController::ModeStop)
   {
      F32 xDiff = obj->getNav()->mMoveDestination.x - location.x;
      F32 yDiff = obj->getNav()->mMoveDestination.y - location.y;
      Point3F rotation = obj->getAIInfo()->mObj->getTransform().toEuler();

      // Check if we should mMove, or if we are 'close enough'
      if (mFabs(xDiff) < mMoveTolerance && mFabs(yDiff) < mMoveTolerance)
      {
         obj->mMovement.mMoveState = AIController::ModeStop;
         obj->getNav()->onReachDestination();
      }
      else
      {
         // Build move direction in world space
         if (mIsZero(xDiff))
            movePtr->y = (location.y > obj->getNav()->mMoveDestination.y) ? -1.0f : 1.0f;
         else
            if (mIsZero(yDiff))
               movePtr->x = (location.x > obj->getNav()->mMoveDestination.x) ? -1.0f : 1.0f;
            else
               if (mFabs(xDiff) > mFabs(yDiff))
               {
                  F32 value = mFabs(yDiff / xDiff);
                  movePtr->y = (location.y > obj->getNav()->mMoveDestination.y) ? -value : value;
                  movePtr->x = (location.x > obj->getNav()->mMoveDestination.x) ? -1.0f : 1.0f;
               }
               else
               {
                  F32 value = mFabs(xDiff / yDiff);
                  movePtr->x = (location.x > obj->getNav()->mMoveDestination.x) ? -value : value;
                  movePtr->y = (location.y > obj->getNav()->mMoveDestination.y) ? -1.0f : 1.0f;
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

            obj->mMovement.mMoveState = AIController::ModeSlowing;
         }
         else
         {
            movePtr->x *= obj->mMovement.mMoveSpeed;
            movePtr->y *= obj->mMovement.mMoveSpeed;

            obj->mMovement.mMoveState = AIController::ModeMove;
         }
      }
   }
}

void AIControllerData::resolveStuck(AIController* obj)
{
   if (obj->mMovement.mMoveState == AIController::ModeStop) return;
   ShapeBase* sbo = dynamic_cast<ShapeBase*>(obj->getAIInfo()->mObj.getPointer());
   // Don't check for ai stuckness if animation during
   // an anim-clip effect override.
   if (sbo->getDamageState() == ShapeBase::Enabled && !(sbo->anim_clip_flags & ShapeBase::ANIM_OVERRIDDEN) && !sbo->isAnimationLocked())
   {
      if (obj->mMovement.mMoveStuckTestCountdown > 0)
         --obj->mMovement.mMoveStuckTestCountdown;
      else
      {
         // We should check to see if we are stuck...
         F32 locationDelta = (obj->getAIInfo()->getPosition() - obj->getAIInfo()->mLastPos).len();
         if (locationDelta < mMoveStuckTolerance)
         {
            // If we are slowing down, then it's likely that our location delta will be less than
            // our move stuck tolerance. Because we can be both slowing and stuck
            // we should TRY to check if we've moved. This could use better detection.
            if (obj->mMovement.mMoveState != AIController::ModeSlowing || locationDelta == 0)
            {
               obj->mMovement.mMoveState = AIController::ModeStuck;
               obj->mMovement.onStuck();
               obj->throwCallback("onStuck");
            }
         }
      }
      obj->getAIInfo()->mLastPos = obj->getAIInfo()->getPosition();
   }
}

void AIControllerData::initPersistFields()
{
   docsURL;
   addGroup("AI");

   addFieldV("moveTolerance", TypeRangedF32, Offset(mMoveTolerance, AIControllerData), &CommonValidators::PositiveFloat,
      "@brief Distance from destination before stopping.\n\n"
      "When the AIPlayer is moving to a given destination it will move to within "
      "this distance of the destination and then stop.  By providing this tolerance "
      "it helps the AIPlayer from never reaching its destination due to minor obstacles, "
      "rounding errors on its position calculation, etc.  By default it is set to 0.25.\n");

   addFieldV("followTolerance", TypeRangedF32, Offset(mFollowTolerance, AIControllerData), &CommonValidators::PositiveFloat,
      "@brief Distance from destination before stopping.\n\n"
      "When the AIPlayer is moving to a given destination it will move to within "
      "this distance of the destination and then stop.  By providing this tolerance "
      "it helps the AIPlayer from never reaching its destination due to minor obstacles, "
      "rounding errors on its position calculation, etc.  By default it is set to 0.25.\n");

   addFieldV("moveStuckTolerance", TypeRangedF32, Offset(mMoveStuckTolerance, AIControllerData), &CommonValidators::PositiveFloat,
      "@brief Distance tolerance on stuck check.\n\n"
      "When the AIPlayer is moving to a given destination, if it ever moves less than "
      "this tolerance during a single tick, the AIPlayer is considered stuck.  At this point "
      "the onMoveStuck() callback is called on the datablock.\n");

   addFieldV("moveStuckTestDelay", TypeRangedS32, Offset(mMoveStuckTestDelay, AIControllerData), &CommonValidators::PositiveInt,
      "@brief The number of ticks to wait before testing if the AIPlayer is stuck.\n\n"
      "When the AIPlayer is asked to move, this property is the number of ticks to wait "
      "before the AIPlayer starts to check if it is stuck.  This delay allows the AIPlayer "
      "to accelerate to full speed without its initial slow start being considered as stuck.\n"
      "@note Set to zero to have the stuck test start immediately.\n");

   addFieldV("AttackRadius", TypeRangedF32, Offset(mAttackRadius, AIControllerData), &CommonValidators::PositiveFloat,
      "@brief Distance considered in firing range for callback purposes.");

   endGroup("AI");

#ifdef TORQUE_NAVIGATION_ENABLED
   addGroup("Pathfinding");

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

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
IMPLEMENT_CO_DATABLOCK_V1(AIPlayerControllerData);
void AIPlayerControllerData::resolvePitch(AIController* obj, Point3F location, Move* movePtr)
{
   Player* po = dynamic_cast<Player*>(obj->getAIInfo()->mObj.getPointer());
   if (!po) return;//not a player

   if (obj->getAim()->mObj || obj->getAim()->mPosSet || obj->mMovement.mMoveState != AIController::ModeStop)
   {
      // Next do pitch.
      if (!obj->getAim()->mObj && !obj->getAim()->mPosSet)
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
#endif //_AICONTROLLER_H_
