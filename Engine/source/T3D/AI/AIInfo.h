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
#ifndef _AIINFO_H_
#define _AIINFO_H_

#ifndef _SCENEOBJECT_H_
#include "scene/sceneObject.h"
#endif

class AIController;
struct AIInfo
{
   AIController* mControllerRef;
   AIController* getCtrl() { return mControllerRef; };
   void setCtrl(AIController* controller) { mControllerRef = controller; };
   SimObjectPtr<SceneObject> mObj;
   Point3F mPosition, mLastPos;
   bool mPosSet;
   F32 mRadius;
   Point3F getPosition(bool doCastray = false);
   F32 getDist();
   AIInfo() = delete;
   AIInfo(AIController* controller);
   AIInfo(AIController* controller, SimObjectPtr<SceneObject> objIn, F32 radIn = 0.0f);
   AIInfo(AIController* controller,Point3F pointIn, F32 radIn = 0.0f);
};
#endif
