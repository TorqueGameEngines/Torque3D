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

#include "math/util/relationVec.h"
#include "console/simBase.h"
#include "console/engineAPI.h"
#include "math/mAngAxis.h"
#include "math/mTransform.h"
#include "math/util/matrixVec.h"

IMPLEMENT_CONOBJECT(MatrixVec);
ConsoleDocClass(MatrixVec, "Matrix Relational Vector");

void testMatrixVec()
{
   RelationVec3D tMat;
   tMat.push(-1, MatrixF());
   MatrixF* localMatPtr = tMat.local(0);
   localMatPtr->add(MatrixF::Identity);
   MatrixF* globalMatPtr = tMat.global(0);
   //expected: global is an identity matrix
   localMatPtr->dumpMatrix("local");
   globalMatPtr->dumpMatrix("global");

   localMatPtr->setPosition(Point3F(10, 0, 0));
   tMat.toGLobal();
   localMatPtr->dumpMatrix("local");
   globalMatPtr->dumpMatrix("global");

}


DefineEngineFunction(testMatrixVec, void, (), ,
   "testMatrixVec\n"
   "@ingroup Math")
{
   testMatrixVec();
}

DefineEngineMethod(MatrixVec, push, void, (S32 inRootID, TransformF inTransform), , "")
{
   object->push(inRootID, inTransform.getMatrix());
}

DefineEngineMethod(MatrixVec, dumpVals, void, (), , "")
{
   for (U32 i = 0; i < object->refLocal()->size(); i++)
   {
      object->local(i)->dumpMatrix((String("matL[") + String::ToString(i) + String("]")).c_str());
      object->global(i)->dumpMatrix((String("matG[") + String::ToString(i) + String("]")).c_str());
      Con::printf("\n");
   }
}

DefineEngineMethod(MatrixVec, getTransform, TransformF, (S32 id, bool global), (0, false), "")
{
   MatrixF* space = (global) ? object->global(id) : object->local(id);
   return TransformF(*space);
}

DefineEngineMethod(MatrixVec, getPosition, Point3F, (S32 id, bool global), (0, false), "")
{
   MatrixF* space = (global) ? object->global(id) : object->local(id);
   return space->getPosition();
}

DefineEngineMethod(MatrixVec, getRotation, AngAxisF, (S32 id, bool global), (0, false), "")
{
   MatrixF* space = (global) ? object->global(id) : object->local(id);
   AngAxisF aa(*space);
   aa.axis.normalize();
   return aa;
}

DefineEngineMethod(MatrixVec, getEuler, EulerF, (S32 id, bool global), (0, false), "")
{
   MatrixF* space = (global) ? object->global(id) : object->local(id);
   return space->toEuler();
}


DefineEngineMethod(MatrixVec, setConstraint3DString, void, (S32 id, const char* constraintString), (0, ""), "")
{
   Constraint3D constraint;
   object->setConstraint(id, constraint.fromString(constraintString));
}


DefineEngineMethod(MatrixVec, setConstraint3D, void, (S32 id, Point3F inPosMin, Point3F inPosMax, Point3F inRotMin, Point3F inRotMax, Point3F inScaleMin, Point3F inScaleMax),, "")
{
   Constraint3D constraint;
   object->setConstraint(id, Constraint3D(inPosMin, inPosMax, inRotMin, inRotMax, inScaleMin, inScaleMax));
}

DefineEngineMethod(MatrixVec, getConstraint3D, const char*, (S32 id),, "")
{
   return object->getConstraint(id)->toString().c_str();
}
