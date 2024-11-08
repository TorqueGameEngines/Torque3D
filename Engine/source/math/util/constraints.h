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
template<typename PosDimensions, typename RotDimensions> class Constraint
{
public:
   enum posRangeType
   {
      MinPos = 0,
      MaxPos,
      MinScale,
      MaxScale,
      MaxPosTypes
   };

   enum rotRangeType
   {
      MinRot,
      MaxRot,
      MaxRotTypes
   };

   struct PosRange
   {
      PosDimensions min;
      PosDimensions max;
      PosRange(PosDimensions inMin, PosDimensions inMax) :min(inMin),max(inMax) {};
   };

   struct RotRange
   {
      RotDimensions min;
      RotDimensions max;
      RotRange(RotDimensions inMin, RotDimensions inMax) :min(inMin), max(inMax) {};
   };

   PosDimensions mPosRanges[MaxPosTypes];
   RotDimensions mRotRanges[MaxRotTypes];
   void setPosRange(PosDimensions min, PosDimensions max) { mPosRanges[MinPos] = min; mPosRanges[MaxPos] = max; };
   void setPosRange(PosDimensions inPos[2]) { mPosRanges[MinPos] = inPos[0]; mPosRanges[MaxPos] = inPos[1]; };

   void setRotRange(RotDimensions min, RotDimensions max) { mRotRanges[MinRot] = min; mRotRanges[MinRot] = max; };
   void setRotRange(RotDimensions inRot[2]) { mRotRanges[MinRot] = inRot[0]; mRotRanges[MinRot] = inRot[1]; };

   void setScaleRange(PosDimensions min, PosDimensions max) { mPosRanges[MinScale] = min; mPosRanges[MaxScale] = max; };
   void setScaleRange(PosDimensions inScale[2]) { mPosRanges[MinScale] = inScale[0]; mPosRanges[MaxScale] = inScale[1]; };

   PosRange getPosRange() { return PosRange(mPosRanges[MinPos], mPosRanges[MaxPos]); }
   RotRange getRotRange() { return  RotRange(mRotRanges[MinRot], mRotRanges[MaxRot]); }
   PosRange getScaleRange() { return  PosRange(mPosRanges[MinScale], mPosRanges[MaxScale]); }

   Constraint(PosDimensions inPosRanges[MaxPosTypes], RotDimensions inRotRanges[MaxPosTypes])
   {
      *mPosRanges = *inPosRanges;
      *mRotRanges = *inRotRanges;
   }
   Constraint(PosDimensions inPos[2], RotDimensions inRot[2], PosDimensions inScale[2])
   {
      setPosRange(inPos);
      setRotRange(inRot);
      setScaleRange(inScale);
   }
   Constraint(PosDimensions minPos, PosDimensions maxPos, RotDimensions minRot, RotDimensions maxRot, PosDimensions minScale, PosDimensions maxScale)
   {
      setPosRange(minPos, maxPos);
      setRotRange(minRot, maxRot);
      setScaleRange(minScale, maxScale);
   }

   String toString()
   {
      return String("not implemented");
   }

   Constraint<PosDimensions,RotDimensions> fromString(String inString)
   {
      return Constraint<PosDimensions, RotDimensions>();
   }

   Constraint() = default;
private:
};
#endif
