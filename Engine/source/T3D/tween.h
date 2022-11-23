#ifndef TWEEN_ENGINE_H
#define TWEEN_ENGINE_H

#include "platform/platform.h"
#include "console/consoleTypes.h"
#include "console/engineAPI.h"
#include "console/simObject.h"
#include "core\iTickable.h"
#include "math/mEase.h"
#include "scene/sceneObject.h"

class Tween : public SimObject, public ITickable
{
   typedef SimObject Parent;

   enum TweenState {
      Idle,
      Playing,
      Paused,
      PlayingReversed
   };

public:
   Tween();
   void SetValueByTime(F32 time);
   bool SetTargetField(F32 value);
   bool SetSceneObjectTargetField(SceneObject* obj, F32 value);
   bool SetGuiControlTargetField(GuiControl* obj, F32 value);
   void SetGlobalField(F32 value);

   static bool setTargetProperty(void* obj, const char* index, const char* db);

   void Play();
   void Reverse();
   void Rewind();
   void Pause();

   //-------------------------------------------
   // SimObject
   //-------------------------------------------
   virtual bool onAdd();
   static void initPersistFields();

   //-------------------------------------------
   // ITickable
   //-------------------------------------------
   virtual void interpolateTick(F32 delta) {};
   virtual void processTick() {};
   virtual void advanceTime(F32 timeDelta);

   // Fields ------------------------------------
   F32 mDuration;
   F32 mCurrentTime;
   F32 mPreviousTime;
   SimObject* mTarget;
   const char* mValueName;
   F32 mValueTarget;
   F32 mCurrentValue;
   Ease::enumDirection mEaseDirection;
   Ease::enumType mEaseType;
   EaseF mEaseCurve;
   TweenState mState;

   DECLARE_CALLBACK(void, onFinished, ());
   DECLARE_CONOBJECT(Tween);
};

#endif // TWEEN_ENGINE_H
