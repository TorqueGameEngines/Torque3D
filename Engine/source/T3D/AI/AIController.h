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
#include "navigation/coverPoint.h"
#include "AIInfo.h"
#include "AIGoal.h"
#include "AIAimTarget.h"
#include "AICover.h"
#include "AINavigation.h"
class AIControllerData;

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
      ModeStuck,                      // AI is stuck, but wants to move.
      ModeSlowing,                    // AI is slowing down as it reaches it's destination.
      ModeMove,                       // AI is currently moving.
      ModeReverse                     // AI is reversing
   };

private:
   AIInfo*mAIInfo;
public:
   void setAIInfo(SimObjectPtr<SceneObject> objIn, F32 rad = 0.0f) { delete(mAIInfo); mAIInfo = new AIInfo(this, objIn, rad); }
   AIInfo* getAIInfo() { return mAIInfo; }
private:
   AIGoal* mGoal;
public:
   void setGoal(AIInfo* targ);
   void setGoal(Point3F loc, F32 rad = 0.0f);
   void setGoal(SimObjectPtr<SceneObject> objIn, F32 rad = 0.0f);
   AIGoal* getGoal() { return mGoal; }
   void clearGoal() { SAFE_DELETE(mGoal); }
private:
   AIAimTarget* mAimTarget;
public:
   void setAim(Point3F loc, F32 rad = 0.0f, Point3F offset = Point3F(0.0f, 0.0f, 0.0f));
   void setAim(SimObjectPtr<SceneObject> objIn, F32 rad = 0.0f, Point3F offset = Point3F(0.0f, 0.0f, 0.0f));
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
      AIController* mControllerRef;
      AIController* getCtrl() { return mControllerRef; };
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
      AIController* mControllerRef;
      AIController* getCtrl() { return mControllerRef; };
      bool mMoveTriggers[MaxTriggerKeys];
      // Trigger sets/gets
      void setMoveTrigger(U32 slot, const bool isSet = true);
      bool getMoveTrigger(U32 slot) const;
      void clearMoveTriggers();
   } mTriggerState;
   bool getAIMove(Move* move);

   static void initPersistFields();
   AIController()
   {
      for (S32 i = 0; i < MaxTriggerKeys; i++)
         mTriggerState.mMoveTriggers[i] = false;

      mMovement.mControllerRef = this;
      mTriggerState.mControllerRef = this;
      mControllerData = NULL;
      mAIInfo = new AIInfo(this);
      mNav = new AINavigation(this);
      mGoal = NULL;
      mAimTarget = NULL;
      mCover = NULL;
      mMovement.mMoveState = ModeStop;
   };
   ~AIController()
   {
      SAFE_DELETE(mAIInfo);
      SAFE_DELETE(mNav);
      clearGoal();
      clearAim();
      clearCover();
   }
   DECLARE_CONOBJECT(AIController);
};

//-----------------------------------------------------------------------------
class AIControllerData : public SimDataBlock {

   typedef SimDataBlock Parent;

public:

   AIControllerData();
   AIControllerData(const AIControllerData&, bool = false);
   ~AIControllerData() {};
   void packData(BitStream* stream) override;
   void unpackData(BitStream* stream) override;
   static void initPersistFields();
   DECLARE_CONOBJECT(AIControllerData);

   F32 mMoveTolerance;                 // Distance from destination point before we stop
   F32 mFollowTolerance;               // Distance from destination object before we stop
   F32 mAttackRadius;                  // Distance to trigger weaponry calcs
   S32 mMoveStuckTestDelay;            // The number of ticks to wait before checking if the AI is stuck
   F32 mMoveStuckTolerance;            // Distance tolerance on stuck check
   F32 mHeightTolerance;               // how high above the navmesh are we before we stop trying to repath
#ifdef TORQUE_NAVIGATION_ENABLED
   struct Flocking {
      U32 mChance;                     // chance of flocking
      F32 mMin;                        // min flocking separation distance
      F32 mMax;                        // max flocking clustering distance
      F32 mSideStep;                   // Distance from destination before we stop moving out of the way
   } mFlocking;

   /// Types of link we can use.
   LinkData mLinkTypes;
   dtQueryFilter mFilter;
   Vector<F32> mAreaCosts;
   AINavigation::NavSize mNavSize;
#endif
   Delegate<void(AIController* obj, Point3F location, Move* movePtr)> resolveYawPtr;
   void resolveYaw(AIController* obj, Point3F location, Move* movePtr);

   Delegate<void(AIController* obj, Point3F location, Move* movePtr)> resolvePitchPtr;
   void resolvePitch(AIController* obj, Point3F location, Move* movePtr) {};

   Delegate<void(AIController* obj, Point3F location, Move* movePtr)> resolveRollPtr;
   void resolveRoll(AIController* obj, Point3F location, Move* movePtr);

   Delegate<void(AIController* obj, Point3F location, Move* movePtr)> resolveSpeedPtr;
   void resolveSpeed(AIController* obj, Point3F location, Move* movePtr);

   Delegate<void(AIController* obj, Move* movePtr)> resolveTriggerStatePtr;
   void resolveTriggerState(AIController* obj, Move* movePtr);

   Delegate<void(AIController* obj)> resolveStuckPtr;
   void resolveStuck(AIController* obj);
};

class AIPlayerControllerData : public AIControllerData
{
   typedef AIControllerData Parent;

public:
   AIPlayerControllerData()
   {
      resolvePitchPtr.bind(this, &AIPlayerControllerData::resolvePitch);
      resolveTriggerStatePtr.bind(this, &AIPlayerControllerData::resolveTriggerState);
   }
   void resolvePitch(AIController* obj, Point3F location, Move* movePtr);
   void resolveTriggerState(AIController* obj, Move* movePtr);
   DECLARE_CONOBJECT(AIPlayerControllerData);
};

class AIWheeledVehicleControllerData : public AIControllerData
{
   typedef AIControllerData Parent;

public:
   AIWheeledVehicleControllerData()
   {
      resolveYawPtr.bind(this, &AIWheeledVehicleControllerData::resolveYaw);
      resolveSpeedPtr.bind(this, &AIWheeledVehicleControllerData::resolveSpeed);
      mHeightTolerance = 2.0f;
   }
   void resolveYaw(AIController* obj, Point3F location, Move* movePtr);
   void resolveSpeed(AIController* obj, Point3F location, Move* movePtr);
   DECLARE_CONOBJECT(AIWheeledVehicleControllerData);
};

class AIFlyingVehicleControllerData : public AIControllerData
{
   typedef AIControllerData Parent;

   F32 mFlightFloor;
   F32 mFlightCeiling;
public:
   AIFlyingVehicleControllerData()
   {
      resolveYawPtr.bind(this, &AIFlyingVehicleControllerData::resolveYaw);
      resolvePitchPtr.bind(this, &AIFlyingVehicleControllerData::resolvePitch);
      resolveSpeedPtr.bind(this, &AIFlyingVehicleControllerData::resolveSpeed);
      mHeightTolerance = 200.0f;
      mFlightCeiling = 200.0f;
      mFlightFloor = 1.0;
   }
   AIFlyingVehicleControllerData(const AIFlyingVehicleControllerData&, bool = false);
   static void initPersistFields();
   void resolveYaw(AIController* obj, Point3F location, Move* movePtr);
   void resolveSpeed(AIController* obj, Point3F location, Move* movePtr);
   void resolvePitch(AIController* obj, Point3F location, Move* movePtr);

   DECLARE_CONOBJECT(AIFlyingVehicleControllerData);
};
#endif //_AICONTROLLER_H_
