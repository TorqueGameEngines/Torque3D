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
#ifndef _TransformVec2D_H_
#define _TransformVec2D_H_
#include "math/util/relationVec.h"
typedef Constraint<Point2F> Constraint2D; //pos xy + rotation
typedef RelationVec<Point3F, Point2F> RelationVec2D;

template<> inline String Constraint2D::toString()
{
   String retval = String::ToString("%g %g", mRanges[0].x, mRanges[0].y);
   for (U32 i = 1; i < MaxTypes; i++)
   {
      retval += String::ToString(" %g %g", mRanges[i].x, mRanges[i].y);
   }
   return retval;
};

template<> inline Constraint2D Constraint2D::fromString(String inString)
{
   Point2F outval[MaxTypes];
   Vector<String> elements;
   inString.split(" ", elements);
   AssertWarn(elements.size() == 3 * MaxTypes, avar("fromString got %d entries, expected 3x%d", elements.size(), MaxTypes));
   U32 offset = 0;
   for (U32 i = 0; i < 3 * MaxTypes; i += 3)
   {
      Point2F range;
      range.x = dAtof(elements[i].c_str());
      range.y = dAtof(elements[i + 1].c_str());
      outval[offset] = range;
      offset++;
   };
   return Constraint(outval);
};

template<> inline void RelationVec2D::setPosition(S32 id, Point2F pos)
{
   mLocal[id] = Point3F(pos.x, pos.y, mLocal[id].z);
   mCachedResult = false;
};
#endif
