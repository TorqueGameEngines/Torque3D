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
   if (sbo->getDamageState() == ShapeBase::Enabled && getGoal())
   {
      if (mMovement.mMoveState != ModeStop)
         getNav()->updateNavMesh();

      if (getNav()->mPathData.path.isNull())
      {
         if (getGoal()->getDist() > mControllerData->mFollowTolerance)
         {
            if (getGoal()->mObj.isValid())
               getNav()->followObject(getGoal()->mObj, mControllerData->mFollowTolerance);
            else if (getGoal()->mPosSet)
               getNav()->setPathDestination(getGoal()->getPosition());
         }
      }
      else
      {
         if (getGoal()->getDist() > mControllerData->mFollowTolerance)
         {
            F32 raylength = 2.0; //for vehicles
            SceneObject* obj = getAIInfo()->mObj->getObjectMount();
            if (!obj)
            {
               obj = getAIInfo()->mObj;
               raylength = 0.001f; //for jumping
            }

            RayInfo info;
            if (obj->getContainer()->castRay(obj->getPosition(), obj->getPosition() - Point3F(0, 0, raylength), StaticShapeObjectType, &info))
            {
               getNav()->repath();
            }
            getGoal()->mInRange = false;
         }
         if (getGoal()->getDist() < mControllerData->mFollowTolerance && !getGoal()->mInRange)
         {
            getNav()->clearPath();
            mMovement.mMoveState = ModeStop;
            getGoal()->mInRange = true;
            throwCallback("onTargetInRange");
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
            else
               getGoal()->mInFiringRange = false;
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

      mControllerData->resolveYawPtr(this, location, movePtr);
      mControllerData->resolvePitchPtr(this, location, movePtr);
      mControllerData->resolveRollPtr(this, location, movePtr);

      if (mMovement.mMoveState != AIController::ModeStop)
      {
         F32 xDiff = getNav()->mMoveDestination.x - location.x;
         F32 yDiff = getNav()->mMoveDestination.y - location.y;
         if (mFabs(xDiff) < mControllerData->mMoveTolerance && mFabs(yDiff) < mControllerData->mMoveTolerance)
         {
            mMovement.mMoveState = AIController::ModeStop;
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
   F32 xDiff = obj->getNav()->mMoveDestination.x - location.x;
   F32 yDiff = obj->getNav()->mMoveDestination.y - location.y;
   Point3F rotation = obj->getAIInfo()->mObj->getTransform().toEuler();

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
   if (obj->mMovement.mMoveState == AIController::ModeStop) return;
   if (!obj->getGoal()) return;
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

IMPLEMENT_CO_DATABLOCK_V1(AIWheeledVehicleControllerData);

// Build a Triangle .. calculate angle of rotation required to meet target..
// man there has to be a better way! >:)
F32 AIWheeledVehicleControllerData::getSteeringAngle(AIController* obj, Point3F location)
{
   WheeledVehicle* wvo = dynamic_cast<WheeledVehicle*>(obj->getAIInfo()->mObj.getPointer());
   if (!wvo)
   {
      //cover the case of a connection controling an object in turn controlling another
      if (obj->getAIInfo()->mObj->getObjectMount())
         wvo = dynamic_cast<WheeledVehicle*>(obj->getAIInfo()->mObj->getObjectMount());
   }
   if (!wvo) return 0;//not a WheeledVehicle

   DrivingState steerState = SteerNull;

   // What is our target
   Point3F desired;
   desired = obj->getNav()->mMoveDestination;

   MatrixF mat = wvo->getTransform();
   Point3F center, front;
   Point3F wFront;
   Box3F box = wvo->getObjBox();

   box.getCenter(&center);
   front = center;
   front.y = box.maxExtents.y; // should be true for all these objects

   obj->getAIInfo()->mObj->getWorldBox().getCenter(&center);
   front = center + front;

   Point3F objFront = front;
   Point3F offset = front - center;
   EulerF rot;
   rot = mat.toEuler();
   MatrixF transform(rot);
   transform.mulV(offset, &wFront);
   front = wFront + center;

   Point3F ftoc;
   ftoc.x = mFabs(front.x - center.x);
   ftoc.y = mFabs(front.y - center.y);
   ftoc.z = mFabs(front.z - center.z);
   F32 fToc = mSqrt((ftoc.x * ftoc.x) + (ftoc.y * ftoc.y));

   Point3F ltoc;
   ltoc.x = mFabs(desired.x - center.x);
   ltoc.y = mFabs(desired.y - center.y);
   ltoc.z = mFabs(desired.z - center.z);
   F32 lToc = mSqrt((ltoc.x * ltoc.x) + (ltoc.y * ltoc.y));

   Point3F ftol;
   ftol.x = mFabs(front.x - desired.x);
   ftol.y = mFabs(front.y - desired.y);
   ftol.z = mFabs(front.z - desired.z);
   F32 fTol = mSqrt((ftol.x * ftol.x) + (ftol.y * ftol.y));

   F32 myAngle = mAcos(((lToc * lToc) + (fToc * fToc) - (fTol * fTol)) / (2 * lToc * fToc));

   F32 finalYaw = mRadToDeg(myAngle);

   F32 maxSteeringAngle = 0;

   VehicleData* vd = (VehicleData*)(wvo->getDataBlock());
   maxSteeringAngle = vd->maxSteeringAngle;

   Point2F steering = wvo->getSteering();

   if (finalYaw < 5 && steering.x != 0.0f)
      steerState = Straight;
   else if (finalYaw < 5)
      steerState = SteerNull;
   else
   {// Quickly Hack out left or right turn info
      Point3F rotData = objFront - desired;
      MatrixF leftM(-rot);
      Point3F leftP;
      leftM.mulV(rotData, &leftP);
      leftP = leftP + desired;

      if (leftP.x < desired.x)
         steerState = Right;
      else
         steerState = Left;
   }

   F32 turnAdjust = myAngle - steering.x;

   F32 throttle = wvo->getThrottle();
   if (throttle < 0.0f)
   {
      F32 reverseReduction = 0.25f;
      if (steerState == Left)
         steerState = Right;
      else if (steerState == Right)
         steerState = Left;
      turnAdjust *= reverseReduction;
      myAngle *= reverseReduction;
   }

   F32 steer = 0;
   switch (steerState)
   {
   case Left:
      steer = myAngle < maxSteeringAngle ? -turnAdjust : -maxSteeringAngle - steering.x;
      break;
   case Right:
      steer = myAngle < maxSteeringAngle ? turnAdjust : maxSteeringAngle - steering.x;
      break;
   case Straight:
      steer = -steering.x;
      break;
   default:
      break;
   };

   //   Con::printf("AI Steering : %f", steer);
   return steer;
}


void AIWheeledVehicleControllerData::resolveYaw(AIController* obj, Point3F location, Move* movePtr)
{
   WheeledVehicle* wvo = dynamic_cast<WheeledVehicle*>(obj->getAIInfo()->mObj.getPointer());
   if (!wvo)
   {
      //cover the case of a connection controling an object in turn controlling another
      if (obj->getAIInfo()->mObj->getObjectMount())
         wvo = dynamic_cast<WheeledVehicle*>(obj->getAIInfo()->mObj->getObjectMount());
   }
   if (!wvo) return;//not a WheeledVehicle

   // Orient towards our destination.
   if (obj->mMovement.mMoveState == AIController::ModeMove || obj->mMovement.mMoveState == AIController::ModeReverse) {
      movePtr->yaw = getSteeringAngle(obj, location);
   }
};
void AIWheeledVehicleControllerData::resolveTriggerState(AIController* obj, Move* movePtr) {};
#endif //_AICONTROLLER_H_
