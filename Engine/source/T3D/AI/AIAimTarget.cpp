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

#include "AIAimTarget.h"
#include "AIController.h"

static U32 sAILoSMask = TerrainObjectType | StaticShapeObjectType | StaticObjectType;

F32 AIAimTarget::getTargetDistance(SceneObject* target, bool _checkEnabled)
{
   if (!target)
   {
      target = mObj.getPointer();
      if (!target)
         return F32_MAX;
   }

   if (_checkEnabled)
   {
      if (target->getTypeMask() & ShapeBaseObjectType)
      {
         ShapeBase* shapeBaseCheck = static_cast<ShapeBase*>(target);
         if (shapeBaseCheck)
            if (shapeBaseCheck->getDamageState() != ShapeBase::Enabled) return false;
      }
      else
         return F32_MAX;
   }

   return (getPosition() - target->getPosition()).len();
}

bool AIAimTarget::checkInLos(SceneObject* target, bool _useMuzzle, bool _checkEnabled)
{
   ShapeBase* sbo = dynamic_cast<ShapeBase*>(getCtrl()->getAIInfo()->mObj.getPointer());
   if (!target)
   {
      target = dynamic_cast<ShapeBase*>(mObj.getPointer());
      if (!target)
         return false;
   }
   if (_checkEnabled)
   {
      if (target->getTypeMask() & ShapeBaseObjectType)
      {
         ShapeBase* shapeBaseCheck = static_cast<ShapeBase*>(target);
         if (shapeBaseCheck)
            if (shapeBaseCheck->getDamageState() != ShapeBase::Enabled) return false;
      }
      else
         return false;
   }

   RayInfo ri;

   sbo->disableCollision();

   S32 mountCount = target->getMountedObjectCount();
   for (S32 i = 0; i < mountCount; i++)
   {
      target->getMountedObject(i)->disableCollision();
   }

   Point3F checkPoint;
   if (_useMuzzle)
      sbo->getMuzzlePoint(0, &checkPoint);
   else
   {
      MatrixF eyeMat;
      sbo->getEyeTransform(&eyeMat);
      eyeMat.getColumn(3, &checkPoint);
   }

   bool hit = !gServerContainer.castRay(checkPoint, target->getBoxCenter(), sAILoSMask, &ri);
   sbo->enableCollision();

   for (S32 i = 0; i < mountCount; i++)
   {
      target->getMountedObject(i)->enableCollision();
   }
   return hit;
}

bool AIAimTarget::checkInFoV(SceneObject* target, F32 camFov, bool _checkEnabled)
{
   ShapeBase* sbo = dynamic_cast<ShapeBase*>(getCtrl()->getAIInfo()->mObj.getPointer());
   if (!target)
   {
      target = dynamic_cast<ShapeBase*>(mObj.getPointer());
      if (!target)
         return false;
   }
   if (_checkEnabled)
   {
      if (target->getTypeMask() & ShapeBaseObjectType)
      {
         ShapeBase* shapeBaseCheck = static_cast<ShapeBase*>(target);
         if (shapeBaseCheck)
            if (shapeBaseCheck->getDamageState() != ShapeBase::Enabled) return false;
      }
      else
         return false;
   }

   MatrixF cam = sbo->getTransform();
   Point3F camPos;
   VectorF camDir;

   cam.getColumn(3, &camPos);
   cam.getColumn(1, &camDir);

   camFov = mDegToRad(camFov) / 2;

   Point3F shapePos = target->getBoxCenter();
   VectorF shapeDir = shapePos - camPos;
   // Test to see if it's within our viewcone, this test doesn't
   // actually match the viewport very well, should consider
   // projection and box test.
   shapeDir.normalize();
   F32 dot = mDot(shapeDir, camDir);
   return (dot > mCos(camFov));
}

DefineEngineMethod(AIController, setAimLocation, void, (Point3F target), ,
   "@brief Tells the AIPlayer to aim at the location provided.\n\n"

   "@param target An \"x y z\" position in the game world to target.\n\n"

   "@see getAimLocation()\n")
{
   object->setAim(target);
}

DefineEngineMethod(AIController, getAimLocation, Point3F, (), ,
   "@brief Returns the point the AIPlayer is aiming at.\n\n"

   "This will reflect the position set by setAimLocation(), "
   "or the position of the object that the bot is now aiming at.  "
   "If the bot is not aiming at anything, this value will "
   "change to whatever point the bot's current line-of-sight intercepts."

   "@return World space coordinates of the object AI is aiming at. Formatted as \"X Y Z\".\n\n"

   "@see setAimLocation()\n"
   "@see setAimObject()\n")
{
   return object->getAim()->getPosition();
}

DefineEngineMethod(AIController, setAimObject, void, (const char* objName, Point3F offset), (Point3F::Zero), "( GameBase obj, [Point3F offset] )"
   "Sets the bot's target object. Optionally set an offset from target location."
   "@hide")
{
   // Find the target
   SceneObject* targetObject;
   if (Sim::findObject(objName, targetObject))
   {

      object->setAim(targetObject, 0.0f, offset);
   }
   else
      object->setAim(0, 0.0f, offset);
}

DefineEngineMethod(AIController, clearAim, void, (), , "clears the bot's target.")
{
      object->clearAim();
}

DefineEngineMethod(AIController, getAimObject, S32, (), ,
   "@brief Gets the object the AIPlayer is targeting.\n\n"

   "@return Returns -1 if no object is being aimed at, "
   "or the SimObjectID of the object the AIPlayer is aiming at.\n\n"

   "@see setAimObject()\n")
{
   SceneObject* obj = dynamic_cast<GameBase*>(object->getAim()->mObj.getPointer());
   return obj ? obj->getId() : -1;
}


DefineEngineMethod(AIController, getTargetDistance, F32, (SceneObject* obj, bool checkEnabled), (nullAsType<SceneObject*>(), false),
   "@brief The distance to a given target.\n"
   "@obj Object to check. (If blank, it will check the current target).\n"
   "@checkEnabled check whether the object can take damage and if so is still alive.(Defaults to false)\n")
{
   return object->getAim()->getTargetDistance(obj, checkEnabled);
}

DefineEngineMethod(AIController, checkInLos, bool, (SceneObject* obj, bool useMuzzle, bool checkEnabled), (nullAsType<ShapeBase*>(), false, false),
   "@brief Check whether an object is in line of sight.\n"
   "@obj Object to check. (If blank, it will check the current target).\n"
   "@useMuzzle Use muzzle position. Otherwise use eye position. (defaults to false).\n"
   "@checkEnabled check whether the object can take damage and if so is still alive.(Defaults to false)\n")
{
   return object->getAim()->checkInLos(obj, useMuzzle, checkEnabled);
}

DefineEngineMethod(AIController, checkInFoV, bool, (SceneObject* obj, F32 fov, bool checkEnabled), (nullAsType<ShapeBase*>(), 45.0f, false),
   "@brief Check whether an object is within a specified veiw cone.\n"
   "@obj Object to check. (If blank, it will check the current target).\n"
   "@fov view angle in degrees.(Defaults to 45)\n"
   "@checkEnabled check whether the object can take damage and if so is still alive.(Defaults to false)\n")
{
   return object->getAim()->checkInFoV(obj, fov, checkEnabled);
}
