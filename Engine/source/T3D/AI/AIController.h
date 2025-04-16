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
#ifndef _AICONTROLLER_H_
#define _AICONTROLLER_H_
#ifdef TORQUE_NAVIGATION_ENABLED
#include "navigation/coverPoint.h"
#include "AIInfo.h"
#include "AIGoal.h"
#include "AIAimTarget.h"
#include "AICover.h"
#include "AINavigation.h"
class AIControllerData;
class AIController;

//-----------------------------------------------------------------------------
class AIController : public SimObject {

   typedef SimObject Parent;

public:
   AIControllerData* mControllerData;
protected:
   static bool setControllerDataProperty(void* object, const char* index, const char* data);
public:
   enum MoveState {
      ModeStop,                       // AI has stopped moving.
      ModeMove,                       // AI is currently moving.
      ModeStuck,                      // AI is stuck, but wants to move.
      ModeSlowing,                    // AI is slowing down as it reaches it's destination.
   };

private:
   AIInfo*mAIInfo;
public:
   void setAIInfo(SimObjectPtr<SceneObject> objIn, F32 rad = 0.0f) { delete(mAIInfo); mAIInfo = new AIInfo(this, objIn, rad); }
   AIInfo* getAIInfo() { return mAIInfo; }
private:
   AIGoal* mGoal;
public:
   void setGoal(AIInfo* targ) { mGoal = (targ) ? new AIGoal(this, targ->getPosition(), targ->mRadius) : NULL; }
   void setGoal(Point3F loc, F32 rad = 0.0f) { delete(mGoal); mGoal = new AIGoal(this, loc, rad); }
   void setGoal(SimObjectPtr<SceneObject> objIn, F32 rad = 0.0f) { delete(mGoal); mGoal = new AIGoal(this, objIn, rad); }
   AIGoal* getGoal() { return mGoal; }
   void clearGoal() { SAFE_DELETE(mGoal); }
private:
   AIAimTarget* mAimTarget;
public:
   void setAim(Point3F loc, F32 rad = 0.0f, Point3F offset = Point3F(0.0f,0.0f,0.0f)) { delete(mAimTarget);  mAimTarget = new AIAimTarget(this, loc, rad); mAimTarget->mAimOffset = offset; }
   void setAim(SimObjectPtr<SceneObject> objIn, F32 rad = 0.0f, Point3F offset = Point3F(0.0f, 0.0f, 0.0f)) { delete(mAimTarget); mAimTarget = new AIAimTarget(this, objIn, rad); mAimTarget->mAimOffset = offset; }
   AIAimTarget* getAim() { return mAimTarget; }
   void clearAim() { SAFE_DELETE(mAimTarget); }
private:
   AICover* mCover;
public:
   void setCover(Point3F loc, F32 rad = 0.0f) { delete(mCover); mCover = new AICover(this, loc, rad); }
   void setCover(SimObjectPtr<SceneObject> objIn, F32 rad = 0.0f) { delete(mCover); mCover = new AICover(this, objIn, rad); }
   AICover* getCover() { return mCover; }
   bool findCover(const Point3F& from, F32 radius);
   void clearCover();

   // Utility Methods
   void throwCallback(const char* name);
   AINavigation* mNav;
   AINavigation* getNav() { return mNav; };
   struct Movement
   {
      MoveState mMoveState;
      F32 mMoveSpeed = 1.0;
      void setMoveSpeed(F32 speed) { mMoveSpeed = speed; };
      F32 getMoveSpeed() { return mMoveSpeed; };
      bool mMoveSlowdown;                 // Slowdown as we near the destination
      Point3F mLastLocation;              // For stuck check
      S32 mMoveStuckTestCountdown;        // The current countdown until at AI starts to check if it is stuck
      Point3F mAimLocation;
      // move triggers
      bool mMoveTriggers[MaxTriggerKeys];
      void stopMove();
      void onStuck();
   } mMovement;

   struct TriggerState
   {
      // Trigger sets/gets
      void setMoveTrigger(U32 slot, const bool isSet = true);
      bool getMoveTrigger(U32 slot) const;
      void clearMoveTriggers();
   } mTriggerState;
   bool getAIMove(Move* move);

   static void initPersistFields();
   AIController()
   {
      mControllerData = NULL;
      mAIInfo = new AIInfo(this);
      mGoal = new AIGoal(this);
      mAimTarget = new AIAimTarget(this);
      mCover = new AICover(this);
      mNav = new AINavigation(this);
   };

   DECLARE_CONOBJECT(AIController);
};

//-----------------------------------------------------------------------------
class AIControllerData : public SimDataBlock {

   typedef SimDataBlock Parent;

public:

   AIControllerData() { mMoveTolerance = 0.25; mFollowTolerance = 1.0; mAttackRadius = 2.0; mMoveStuckTolerance = 0.01f; mMoveStuckTestDelay = 30;};
   ~AIControllerData() {};

   static void initPersistFields();
   DECLARE_CONOBJECT(AIControllerData);

   F32 mMoveTolerance;                 // Distance from destination point before we stop
   F32 mFollowTolerance;               // Distance from destination object before we stop
   F32 mAttackRadius;                  // Distance to trigger weaponry calcs
   F32 mMoveStuckTolerance;            // Distance tolerance on stuck check
   S32 mMoveStuckTestDelay;            // The number of ticks to wait before checking if the AI is stuck
   /// Types of link we can use.
   LinkData mLinkTypes;

   void resolveYaw(AIController* obj, Point3F location, Move* movePtr);
   void resolvePitch(AIController* obj, Point3F location, Move* movePtr) {};
   void resolveRoll(AIController* obj, Point3F location, Move* movePtr);
   void resolveSpeed(AIController* obj, Point3F location, Move* movePtr);
   void resolveStuck(AIController* obj);
};

class AIPlayerControllerData : public AIControllerData
{
   typedef AIControllerData Parent;

public:
   void resolvePitch(AIController* obj, Point3F location, Move* movePtr);
   DECLARE_CONOBJECT(AIPlayerControllerData);
};
#endif // TORQUE_NAVIGATION_ENABLED
#endif //_AICONTROLLER_H_
