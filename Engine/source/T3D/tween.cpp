#include "tween.h"

#include "T3D\gameBase\gameBase.h"

IMPLEMENT_CONOBJECT(Tween);

//-------------------------------------------
// Tween
//-------------------------------------------

Tween::Tween()
{
   mDuration = 0.f;
   mCurrentTime = 0.f;
   mPreviousTime = 0.f;
   mTarget = NULL;
   mValueName = NULL;
   mValueTarget = 0.f;
   mCurrentValue = 0.f;
   mEaseDirection = Ease::InOut;
   mEaseType = Ease::Linear;
   mState = TweenState::Idle;
}

bool Tween::onAdd()
{
   if (!Parent::onAdd())
      return false;
   mEaseCurve = EaseF(mEaseDirection, mEaseType);
   return true;
}

void Tween::initPersistFields()
{
   addField("Duration", TypeF32, Offset(mDuration, Tween), "");
   addField("Target", TYPEID< SimObject >(), Offset(mTarget, Tween), "");
   addField("ValueName", TYPEID<const char*>(), Offset(mValueName, Tween), "");
   addField("ValueTarget", TypeF32, Offset(mValueTarget, Tween), "");
   addField("EaseDirection", TypeS32, Offset(mEaseDirection, Tween), "");
   addField("EaseType", TypeS32, Offset(mEaseType, Tween), "");

   Parent::initPersistFields();
}

bool Tween::setTargetProperty(void* obj, const char* index, const char* value)
{
   if (value == NULL || !value || !value[0])
   {
      Con::errorf("Tween::setDataBlockProperty - Can't unset target on Tween objects");
      return false;
   }

   Tween* object = static_cast<Tween*>(obj);
   SimObject* target;
   if (Sim::findObject(value, target)) {
      object->mTarget = target;
      return true;
   }

   Con::errorf("Tween::setTargetProperty - Could not find target \"%s\"", value);
   return false;
}

void Tween::advanceTime(F32 time)
{
   if (!mTarget || mTarget->isDeleted()) {
      mTarget = NULL;
      return;
   }
   switch (mState)
   {
   case Tween::Idle:
      break;
   case Tween::Playing:
      if (mCurrentTime >= mDuration)
      {
         mCurrentTime = mDuration;
         SetValueByTime(mDuration);
         mState = Tween::Idle;
      }
      else
      {
         SetValueByTime(mClampF(mCurrentTime + time, 0.0, mDuration));
      }
      break;
   case Tween::Paused:
      break;
   case Tween::PlayingReversed:
      if (mCurrentTime <= 0.0f)
      {
         mCurrentTime = 0.0f;
         SetValueByTime(0);
         mState = Tween::Idle;
      }
      else
      {
         SetValueByTime(mClampF(mCurrentTime - time, 0.0, mDuration));
      }
      break;
   default:
      break;
   }
}

void Tween::Play()
{
   mState = TweenState::Playing;
}

void Tween::Pause()
{
   mState = TweenState::Paused;
}

void Tween::Rewind()
{
   mPreviousTime = 0;
   mCurrentTime = 0;
   SetValueByTime(0);
}

void Tween::Reverse()
{
   mState = TweenState::PlayingReversed;
}

void Tween::SetValueByTime(F32 time)
{
   mPreviousTime = mCurrentTime;
   mCurrentTime = time;
   F32 d = mDuration;
   F32 newValue = mEaseCurve.getValue(mCurrentTime, 0, mValueTarget, d);
   F32 deltaValue = newValue - mCurrentValue;
   if (mTarget)
      SetTargetField(deltaValue);
   else
      SetGlobalField(deltaValue);
}

void Tween::SetGlobalField(F32 value)
{
   char buffer[6];
   dSprintf(buffer, sizeof(buffer), "%f", value);
   Con::setVariable(mValueName, buffer);
}

bool Tween::SetTargetField(F32 value)
{
   int size = strlen(mValueName);

   // Syntactic sugar for SceneObjects.
   SceneObject* obj = dynamic_cast<SceneObject*>((SimObject*)mTarget);
   if (obj && SetSceneObjectTargetField(obj, value))
   {
      return true;;
   }

   GuiControl* guiCtrl = dynamic_cast<GuiControl*>((SimObject*)mTarget);
   if (guiCtrl && SetGuiControlTargetField(guiCtrl, value))
   {
      return true;
   }

   F32 oldValue = dAtof(mTarget->getDataField(mValueName, NULL));
   char buffer[18];
   dSprintf(buffer, sizeof(buffer), "%f", oldValue + value);
   if (size <= 0)
   {
      Con::errorf("ValueName not set, pausing Tween %s", getId());
      Pause();
      return true;
   }
   mTarget->setDataField(mValueName, NULL, buffer);
   F32 newValue = dAtof(mTarget->getDataField(mValueName, NULL));

   mCurrentValue = newValue - oldValue;

   return true;
}


bool Tween::SetSceneObjectTargetField(SceneObject* obj, F32 value)
{
   int size = strlen(mValueName);

   switch (mValueName[0])
   {
      // Position BEGIN -----
   case 'x':
   case 'X':
      if (size == 1)
      {
         Point3F pos = obj->getPosition();
         obj->setPosition(Point3F(pos.x + value, pos.y, pos.z));
         mCurrentValue += value;
         return true;
      }
      break;
   case 'y':
   case 'Y':
      if (size == 1)
      {
         Point3F pos = obj->getPosition();
         obj->setPosition(Point3F(pos.x, pos.y + value, pos.z));
         mCurrentValue += value;
         return true;
      }
      break;
   case 'z':
   case 'Z':
      if (size == 1)
      {
         Point3F pos = obj->getPosition();
         obj->setPosition(Point3F(pos.x, pos.y, pos.z + value));
         mCurrentValue += value;
         return true;
      }
      break;
      // Position END -----
      // Rotation BEGIN -----
   case 'R':
   case 'r':
      switch (mValueName[1])
      {
      case 'x':
      case 'X':
         if (size == 2)
         {
            EulerF euler = obj->getTransform().toEuler();
            euler = Point3F(euler.x + value, euler.y, euler.z);
            obj->setTransform(MatrixF(euler));
            mCurrentValue += value;
            return true;
         }
         break;
      case 'y':
      case 'Y':
         if (size == 2)
         {
            EulerF euler = obj->getTransform().toEuler();
            euler = Point3F(euler.x, euler.y + value, euler.z);
            obj->setTransform(MatrixF(euler));
            mCurrentValue += value;
            return true;
         }
         break;
      case 'z':
      case 'Z':
         if (size == 2)
         {
            EulerF euler = obj->getTransform().toEuler();
            euler = Point3F(euler.x, euler.y, euler.z + value);
            obj->setTransform(MatrixF(euler));
            mCurrentValue += value;
            return true;
         }
         break;
      default:
         break;
      }
      break;
      // Rotation END -----
      // Scale BEGIN -----
   case 's':
   case 'S':
      switch (mValueName[1])
      {
      case 'x':
      case 'X':
         if (size == 2)
         {
            VectorF scale = obj->getScale();
            obj->setScale(VectorF(scale.x + value, scale.y, scale.z));
            mCurrentValue += value;
            return true;
         }
         break;
      case 'y':
      case 'Y':
         if (size == 2)
         {
            VectorF scale = obj->getScale();
            obj->setScale(VectorF(scale.x, scale.y + value, scale.z));
            mCurrentValue += value;
            return true;
         }
         break;
      case 'z':
      case 'Z':
         if (size == 2)
         {
            VectorF scale = obj->getScale();
            obj->setScale(VectorF(scale.z, scale.y, scale.z + value));
            mCurrentValue += value;
            return true;
         }
         break;
      default:
         break;
      }
      break;
      // Scale END -----
   default:
      break;
   }

   return false;
}

bool Tween::SetGuiControlTargetField(GuiControl* obj, F32 value)
{
   int size = strlen(mValueName);

   switch (mValueName[0])
   {
      // Position BEGIN -----
   case 'x':
   case 'X':
      if (size == 1)
      {
         obj->setPosition(obj->getPosition().x + static_cast<S32>(value), obj->getPosition().y);
         mCurrentValue += static_cast<S32>(value);
         return true;
      }
      break;
   case 'y':
   case 'Y':
      if (size == 1)
      {
         obj->setPosition(obj->getPosition().x, obj->getPosition().y + static_cast<S32>(value));
         mCurrentValue += static_cast<S32>(value);
         return true;
      }
      break;
      // Scale BEGIN -----
   case 's':
   case 'S':
      switch (mValueName[1])
      {
      case 'x':
      case 'X':
         if (size == 2)
         {
            obj->setExtent(obj->getExtent().x + static_cast<S32>(value), obj->getExtent().y);
            mCurrentValue += static_cast<S32>(value);
            return true;
         }
         break;
      case 'y':
      case 'Y':
         if (size == 2)
         {
            obj->setExtent(obj->getExtent().x, obj->getExtent().y + static_cast<S32>(value));
            mCurrentValue += static_cast<S32>(value);
            return true;
         }
         break;
      default:
         break;
      }
      break;
      // Scale END -----
      // Min Scale BEGIN -----
   case 'm':
   case 'M':
      switch (mValueName[1])
      {
      case 'x':
      case 'X':
         if (size == 2)
         {
            obj->setExtent(obj->getMinExtent().x + static_cast<S32>(value), obj->getMinExtent().y);
            mCurrentValue += static_cast<S32>(value);
            return true;
         }
         break;
      case 'y':
      case 'Y':
         if (size == 2)
         {
            obj->setExtent(obj->getMinExtent().x, obj->getMinExtent().y + static_cast<S32>(value));
            mCurrentValue += static_cast<S32>(value);
            return true;
         }
         break;
      default:
         break;
      }
      break;
      // Min Scale END -----
   default:
      break;
   }

   return false;
}

IMPLEMENT_CALLBACK(Tween, onFinished, void, (), (), "");

DefineEngineMethod(Tween, Play, void, (), , "")
{
   object->Play();
}

DefineEngineMethod(Tween, Pause, void, (), , "")
{
   object->Pause();
}

DefineEngineMethod(Tween, Rewind, void, (), , "")
{
   object->Rewind();
}

DefineEngineMethod(Tween, Reverse, void, (), , "")
{
   object->Reverse();
}
