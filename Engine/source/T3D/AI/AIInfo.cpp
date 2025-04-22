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

#include "AIInfo.h"
#include "AIController.h"

AIInfo::AIInfo(AIController* controller)
{
   mControllerRef = controller;
   mObj = NULL;
   mPosition = mLastPos = Point3F(0.0f, 0.0f, 0.0f);
   mRadius = 0.0f;
   mPosSet = false;
};

AIInfo::AIInfo(AIController* controller, SimObjectPtr<SceneObject> objIn, F32 radIn)
{
   mControllerRef = controller;
   mObj = objIn;
   mPosition = mLastPos = objIn->getPosition();
   mRadius = radIn;
   mPosSet = false;
   if (radIn == 0.0f)
      mRadius = mMax(objIn->getObjBox().len_x(), objIn->getObjBox().len_y()) * 0.5;
};

AIInfo::AIInfo(AIController* controller, Point3F pointIn, F32 radIn)
{
   mControllerRef = controller;
   mObj = NULL;
   mPosition = mLastPos = pointIn;
   mRadius = radIn;
   mPosSet = true;
};

Point3F AIInfo::getPosition(bool doCastray)
{
   Point3F pos = (mObj.isValid()) ? mObj->getPosition() : mPosition;
   if (doCastray)
   {
      RayInfo info;
      if (gServerContainer.castRay(pos, pos - Point3F(0, 0, getCtrl()->mControllerData->mHeightTolerance), StaticShapeObjectType, &info))
      {
         pos = info.point;
      }
   }

   return pos;
}

F32 AIInfo::getDist()
{
   AIInfo* controlObj = getCtrl()->getAIInfo();
   Point3F targPos = getPosition();

   if (mFabs(targPos.z - controlObj->getPosition().z) < getCtrl()->mControllerData->mHeightTolerance)
      targPos.z = controlObj->getPosition().z;

   F32 ret = VectorF(controlObj->getPosition() - targPos).len();
   ret -= controlObj->mRadius + mRadius;
   return ret;
}
