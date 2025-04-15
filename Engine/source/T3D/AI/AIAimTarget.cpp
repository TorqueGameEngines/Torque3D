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

bool AIAimTarget::checkInLos(GameBase* target, bool _useMuzzle, bool _checkEnabled)
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
