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
#ifndef _MATRIXVEC_H_
#define _MATRIXVEC_H_
#include "math/util/relationVec.h"

#ifndef _MMATRIX_H_
#include "math/mMatrix.h"
#endif

#ifndef _CONSOLEOBJECT_H_
#include "console/simObject.h"
#endif

#ifndef _MQUAT_H_
#include "math/mQuat.h"
#endif

#ifndef _MANGAXIS_H_
#include "math/mAngAxis.h"
#endif

#ifndef _CONSTRAINTS_H_
#include "math/util/constraints.h"
#endif

#ifndef _MMATHFN_H_
#include "math/mMathFn.h"
#endif

typedef Constraint<Point3F> Constraint3D;
typedef RelationVec<MatrixF, Point3F> RelationVec3D;

template<> inline String Constraint3D::toString()
{
   String retval = String::ToString("%g %g %g", mRanges[0].x, mRanges[0].y, mRanges[0].z);
   for (U32 i = 1; i < MaxTypes; i++)
   {
      retval += String::ToString(" %g %g %g", mRanges[i].x, mRanges[i].y, mRanges[i].z);
   }
   return retval;
};

template<> inline Constraint3D Constraint3D::fromString(String inString)
{
   Point3F outval[MaxTypes];
   Vector<String> elements;
   inString.split(" ", elements);
   AssertWarn(elements.size() == 3 * MaxTypes, avar("fromString got %d entries, expected 3x%d", elements.size(), MaxTypes));
   U32 offset = 0;
   for (U32 i = 0; i < 3 * MaxTypes; i+=3)
   {
      Point3F range;
      range.x = dAtof(elements[i].c_str());
      range.y = dAtof(elements[i + 1].c_str());
      range.z = dAtof(elements[i + 2].c_str());
      outval[offset] = range;
      offset++;
   };
   return Constraint(outval);
};


template<> inline void RelationVec3D::toGLobal()
{
   //first, allocate a copy of local size for global space
   if (mGlobal.size() < mLocal.size())
      mGlobal.setSize(mLocal.size());

   //next, itterate throughout the vector, multiplying matricies down the root/branch chains to shift those to worldspace
   for (U32 id = 0; id < mLocal.size(); id++)
   {
      MatrixF curMat = copyLocal(id);
      RelationNode* node = relation(id);

      // multiply transforms...
      if (node->mRoot < 0)
         setGlobal(id, curMat);
      else
      {
         curMat.mul(copyGlobal(node->mRoot), copyLocal(id));
         setGlobal(id, curMat);
      }
   }
   mCachedResult = true;
};

template<> inline void RelationVec3D::setPosition(S32 id, Point3F pos)
{
   mLocal[id].setPosition(pos);
   mCachedResult = false;
};

template<> inline void RelationVec3D::setRotation(S32 id, Point3F rot)
{
   Point3F pos = mLocal[id].getPosition();
   mLocal[id].set(rot, pos);
   mCachedResult = false;
};

template<> inline void RelationVec3D::setScale(S32 id, Point3F scale)
{
   mLocal[id].normalize();
   mLocal[id].scale(scale);
   mCachedResult = false;
};

template<> inline Point3F RelationVec3D::getPosition(S32 id)
{
   return global(id)->getPosition();
};
template<> inline Point3F RelationVec3D::getRotation(S32 id)
{
   return global(id)->getForwardVector();
};
template<> inline Point3F RelationVec3D::getScale(S32 id)
{
   return global(id)->getScale();
};

template<> inline void RelationVec3D::translate(S32 id, Point3F posDelta)
{
   Point3F endPos = mClamp3D(mLocal[id].getPosition() + posDelta, getConstraint(id)->getPosRange().min, getConstraint(id)->getPosRange().max);
   mLocal[id].setPosition(endPos);
   mCachedResult = false;
};

template<> inline void RelationVec3D::scale(S32 id, Point3F scaleDelta)
{
   Point3F endcale = mClamp3D(mLocal[id].getScale() * scaleDelta, getConstraint(id)->getScaleRange().min, getConstraint(id)->getScaleRange().max);
   mLocal[id].normalize();
   mLocal[id].scale(endcale);
   mCachedResult = false;
};

template<> inline void RelationVec3D::rotate(S32 id, U32 axis, F32 radianDelta)
{
   Point3F pos = mLocal[id].getPosition();
   Point3F scale = mLocal[id].getScale();
   VectorF curVec;
   VectorF delta;

   switch (axis)
   {
   case 0:
   {
      curVec = mLocal[id].getRightVector();
      delta = VectorF(radianDelta, 0, 0);
   }break;
   case 1:
   {
      curVec = mLocal[id].getForwardVector();
      delta = VectorF(0, radianDelta, 0);

   }break;
   case 2:
   {
      curVec = mLocal[id].getUpVector();
      delta = VectorF(0, 0, radianDelta);

   }break;
   default://bad axis
      return;
   }
   Point3F endRot = mClamp3D(curVec + delta, getConstraint(id)->getRotRange().min, getConstraint(id)->getRotRange().max);
   mLocal[id].set(endRot, pos);
   mLocal[id].scale(scale);
   mCachedResult = false;
};

template<> inline void RelationVec3D::orbit(S32 id, U32 axis, F32 radianDelta)
{
   VectorF curVec;
   VectorF delta;

   switch (axis)
   {
   case 0:
   {
      curVec = mLocal[id].getRightVector();
      delta = VectorF(radianDelta, 0, 0);
   }break;
   case 1:
   {
      curVec = mLocal[id].getForwardVector();
      delta = VectorF(0, radianDelta, 0);

   }break;
   case 2:
   {
      curVec = mLocal[id].getUpVector();
      delta = VectorF(0, 0, radianDelta);

   }break;
   default://bad axis
      return;
   }
   Point3F endRot = mClamp3D(curVec + delta, getConstraint(id)->getRotRange().min, getConstraint(id)->getRotRange().max);
   MatrixF temp = MatrixF(endRot);
   mLocal[id].mul(temp);
   mCachedResult = false;
};

class MatrixVec : public RelationVec3D, public SimObject
{
   typedef SimObject Parent;
public:

   //type specific I/O
   void setTransform(S32 id, AngAxisF trans) { setCached(false); };
   void constrain(S32 id) { setCached(false); };

   MatrixVec() {};
   DECLARE_CONOBJECT(MatrixVec);
};
#endif
