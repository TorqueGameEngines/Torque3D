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

#ifndef _TYPEVALIDATORS_H_
#define _TYPEVALIDATORS_H_

class TypeValidator
{
   public:
   S32 fieldIndex;
   TypeValidator() : fieldIndex(0) {}
   ~TypeValidator() {}
   /// Prints a console error message for the validator.
   ///
   /// The message is prefaced with with:
   /// @code
   /// className objectName (objectId) - invalid value for fieldName: msg
   /// @endcode
   void consoleError(SimObject *object, const char *format, ...);

   /// validateType is called for each assigned value on the field this
   /// validator is attached to.
   virtual void validateType(SimObject *object, void *typePtr) = 0;
};


/// Floating point min/max range validator
class FRangeValidator : public TypeValidator
{
   F32 minV, maxV, mFidelity;
public:
   FRangeValidator(F32 minValue, F32 maxValue, F32 fidelity = 0.0f)
   {
      minV = minValue;
      maxV = maxValue;
      mFidelity = fidelity;
   }
   void validateType(SimObject *object, void *typePtr) override;
   F32 getMin() { return minV; };
   F32 getMax() { return maxV; };
   F32 getFidelity() { return mFidelity; };
};

/// Signed integer min/max range validator
class IRangeValidator : public TypeValidator
{
   S32 minV, maxV, mFidelity;
public:
   IRangeValidator(S32 minValue, S32 maxValue, S32 fidelity = 1)
   {
      minV = minValue;
      maxV = maxValue;
      mFidelity = fidelity;
   }
   void validateType(SimObject *object, void *typePtr) override;
   S32 getMin() { return minV; };
   S32 getMax() { return maxV; };
   S32 getFidelity() { return mFidelity; };
};

/// Scaled integer field validator
///
/// @note This should NOT be used on a field that gets exported -
/// the field is only validated once on initial assignment
class IRangeValidatorScaled : public TypeValidator
{
   S32 minV, maxV;
   S32 factor;
public:
   IRangeValidatorScaled(S32 scaleFactor, S32 minValueScaled, S32 maxValueScaled)
   {
      minV = minValueScaled;
      maxV = maxValueScaled;
      factor = scaleFactor;
   }
   void validateType(SimObject *object, void *typePtr) override;
   S32 getMin() { return minV; };
   S32 getMax() { return maxV; };
   S32 getScaleFactor() { return factor; };
};

/// Vector normalization validator
class Point3NormalizeValidator : public TypeValidator
{
   F32 length;
public:
   Point3NormalizeValidator(F32 normalizeLength = 1.0f) : length(normalizeLength) { }
   void validateType(SimObject *object, void *typePtr) override;
   F32 getLength() { return length; };
};

namespace CommonValidators
{
   // Floats
   extern FRangeValidator F32Range;
   extern FRangeValidator DirFloat;
   extern FRangeValidator NegDefaultF32;   
   extern FRangeValidator PositiveFloat;
   extern FRangeValidator PositiveNonZeroFloat;
   extern FRangeValidator NormalizedFloat;
   extern FRangeValidator F32_8BitPercent;
   extern FRangeValidator F32_16BitPercent;
   extern FRangeValidator ValidSlopeAngle;
   extern FRangeValidator CornerAngle;

   extern IRangeValidator S32Range;
   extern IRangeValidator DirInt;
   extern IRangeValidator NegDefaultInt;
   extern IRangeValidator PositiveInt;
   extern IRangeValidator NaturalNumber;
   extern IRangeValidator MSTickRange;
   extern IRangeValidator S32_8BitCap;
   extern IRangeValidator S32_16BitCap;
   // Other Math Types
   extern Point3NormalizeValidator NormalizedPoint3;

   // orbital mechanics
   extern FRangeValidator DegreeRange;
   extern FRangeValidator PosDegreeRange;
   extern FRangeValidator DegreeRangeHalf;
   extern FRangeValidator PosDegreeRangeHalf;
   extern FRangeValidator DegreeRangeQuarter;
   extern FRangeValidator PosDegreeRangeQuarter;

   extern IRangeValidator S32_DegreeRange;
   extern IRangeValidator S32_PosDegreeRange;
   extern IRangeValidator S32_DegreeRangeHalf;
   extern IRangeValidator S32_PosDegreeRangeHalf;
   extern IRangeValidator S32_DegreeRangeQuarter;
   extern IRangeValidator S32_PosDegreeRangeQuarter;
};

#endif
