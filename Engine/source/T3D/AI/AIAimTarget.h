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
#ifndef _AIAIMTARGET_H_
#define _AIAIMTARGET_H_

#include "AIInfo.h"
struct AIAimTarget : public AIInfo
{
   typedef AIInfo Parent;
   Point3F mAimOffset;
   bool mTargetInLOS;                  // Is target object visible?
   Point3F getPosition() { return ((mObj.isValid()) ? mObj->getPosition() : mPosition) + mAimOffset; }
   bool checkInLos(SceneObject* target = NULL, bool _useMuzzle = false, bool _checkEnabled = false);
   bool checkInFoV(SceneObject* target = NULL, F32 camFov = 45.0f, bool _checkEnabled = false);
   F32 getTargetDistance(SceneObject* target, bool _checkEnabled);
   AIAimTarget() = delete;
   AIAimTarget(AIController* controller) : Parent(controller) { mTargetInLOS = false; };
   AIAimTarget(AIController* controller, SimObjectPtr<SceneObject> objIn, F32 radIn) : Parent(controller, objIn, radIn) { mTargetInLOS = false; };
   AIAimTarget(AIController* controller, Point3F pointIn, F32 radIn) : Parent(controller, pointIn, radIn) { mTargetInLOS = false; };
};

#endif
