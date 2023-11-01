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

#ifndef _CONSTRAINTS_H_
#define _CONSTRAINTS_H_
template<typename Dimensions> class Constraint
{
public:
   enum rangeType
   {
      MinPos = 0,
      MaxPos,
      MinRot,
      MaxRot,
      MinScale,
      MaxScale,
      MaxTypes
   };

   struct Range
   {
      Dimensions min;
      Dimensions max;
      Range(Dimensions inMin, Dimensions inMax) :min(inMin),max(inMax) {};
   };

   Dimensions mRanges[MaxTypes];
   void setPosRange(Dimensions min, Dimensions max) { mRanges[MinPos] = min; mRanges[MaxPos] = max; };
   void setPosRange(Dimensions inPos[2]) { mRanges[MinPos] = inPos[0]; mRanges[MaxPos] = inPos[1]; };

   void setRotRange(Dimensions min, Dimensions max) { mRanges[MinRot] = min; mRanges[MinRot] = max; };
   void setRotRange(Dimensions inRot[2]) { mRanges[MinRot] = inRot[0]; mRanges[MinRot] = inRot[1]; };

   void setScaleRange(Dimensions min, Dimensions max) { mRanges[MinScale] = min; mRanges[MaxScale] = max; };
   void setScaleRange(Dimensions inScale[2]) { mRanges[MinScale] = inScale[0]; mRanges[MaxScale] = inScale[1]; };

   Range getPosRange() { return Range(mRanges[MinPos], mRanges[MaxPos]); }
   Range getRotRange() { return  Range(mRanges[MinRot], mRanges[MaxRot]); }
   Range getScaleRange() { return  Range(mRanges[MinScale], mRanges[MaxScale]); }

   Constraint(Dimensions inRanges[MaxTypes])
   {
      *mRanges = *inRanges;
   }
   Constraint(Dimensions inPos[2], Dimensions inRot[2], Dimensions inScale[2])
   {
      setPosRange(inPos);
      setRotRange(inRot);
      setScaleRange(inScale);
   }
   Constraint(Dimensions minPos, Dimensions maxPos, Dimensions minRot, Dimensions maxRot, Dimensions minScale, Dimensions maxScale)
   {
      setPosRange(minPos, maxPos);
      setRotRange(minRot, maxRot);
      setScaleRange(minScale, maxScale);
   }

   String toString()
   {
      return String("not implemented");
   }

   Constraint<Dimensions> fromString(String inString)
   {
      return Constraint<Dimensions>();
   }

   Constraint() = default;
private:
};
#endif
