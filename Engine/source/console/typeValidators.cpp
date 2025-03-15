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

#include "platform/platform.h"
#include "console/console.h"
#include "console/consoleObject.h"
#include "console/typeValidators.h"
#include "console/simBase.h"
#include "math/mPoint3.h"
#include <stdarg.h>

void TypeValidator::consoleError(SimObject *object, const char *format, ...)
{
   char buffer[1024];
   va_list argptr;
   va_start(argptr, format);
   dVsprintf(buffer, sizeof(buffer), format, argptr);
   va_end(argptr);

   AbstractClassRep *rep = object->getClassRep();
   AbstractClassRep::Field &fld = rep->mFieldList[fieldIndex];
   const char *objectName = object->getName();
   if(!objectName)
      objectName = "unnamed";


   Con::warnf("%s - %s(%d) - invalid value for %s: %s",
      rep->getClassName(), objectName, object->getId(), fld.pFieldname, buffer);
}

void FRangeValidator::validateType(SimObject *object, void *typePtr)
{
   F32 *v = (F32 *) typePtr;
   if(*v < minV || *v > maxV)
   {
      consoleError(object, "=(%g). Must be between %g and %g", *v, minV, maxV);
      if(*v < minV)
         *v = minV;
      else if(*v > maxV)
         *v = maxV;
   }
}

void IRangeValidator::validateType(SimObject *object, void *typePtr)
{
   S32 *v = (S32 *) typePtr;
   if(*v < minV || *v > maxV)
   {
      consoleError(object, "=(%d). Must be between %d and %d", *v, minV, maxV);
      if(*v < minV)
         *v = minV;
      else if(*v > maxV)
         *v = maxV;
   }
}

void IRangeValidatorScaled::validateType(SimObject *object, void *typePtr)
{
   S32 *v = (S32 *) typePtr;
   *v /= factor;
   if(*v < minV || *v > maxV)
   {
      consoleError(object, "=(%d). Scaled value must be between %d and %d", *v, minV, maxV);
      if(*v < minV)
         *v = minV;
      else if(*v > maxV)
         *v = maxV;
   }
}

void Point3NormalizeValidator::validateType(SimObject *object, void *typePtr)
{
   Point3F *v = (Point3F *) typePtr;
   const F32 len = v->len();
   if(!mIsEqual(len, 1.0f))
   {
      consoleError(object, "=(%g). Vector length must be %g", len, length);
      *v *= length / len;
   }
}

namespace CommonValidators
{
   FRangeValidator F32Range(F32_MIN, F32_MAX, F32_MAX);
   FRangeValidator DirFloat(-1.0f, 1.0f);
   FRangeValidator NegDefaultF32(-1.0f, F32_MAX, F32_MAX);
   FRangeValidator PositiveFloat(0.0f, F32_MAX, F32_MAX);
   FRangeValidator PositiveNonZeroFloat((F32)POINT_EPSILON, F32_MAX);
   FRangeValidator NormalizedFloat(0.0f, 1.0f);

   FRangeValidator F32_8BitPercent(0.0f, 1.0f, 1 << 8);
   FRangeValidator F32_16BitPercent(0.0f, 1.0f, 1 << 16);
   FRangeValidator ValidSlopeAngle(0.0f, 89.9f, 89.9f);
   FRangeValidator CornerAngle(0.0f, 90.0f, 90.0f);

   IRangeValidator S32Range(S32_MIN, S32_MAX);
   IRangeValidator DirInt(-1,1);
   IRangeValidator NegDefaultInt(-1, S32_MAX);
   IRangeValidator PositiveInt(0, S32_MAX);
   IRangeValidator NaturalNumber(1, S32_MAX);
   //see "T3D/gameBase/processList.h" for TickMs = 32
   IRangeValidator MSTickRange(32, S32_MAX);

   IRangeValidator S32_8BitCap(0, 1 << 8);
   IRangeValidator S32_16BitCap(0, 1 << 16);
   Point3NormalizeValidator NormalizedPoint3(1.0f);

   FRangeValidator DegreeRange(-360.0f, 360.0f, 720.0f);
   FRangeValidator PosDegreeRange(0.0f, 360.0f, 360.0f);
   FRangeValidator DegreeRangeHalf(-180.0f, 180.0f, 360.0f);
   FRangeValidator PosDegreeRangeHalf(0.0f, 180.0f, 180.0f);
   FRangeValidator DegreeRangeQuarter(-90.0f, 90.0f, 180.0f);
   FRangeValidator PosDegreeRangeQuarter(0.0f, 90.0f, 90.0f);

   IRangeValidator S32_DegreeRange(-360, 360);
   IRangeValidator S32_PosDegreeRange(0, 360);
   IRangeValidator S32_DegreeRangeHalf(-180, 180);
   IRangeValidator S32_PosDegreeRangeHalf(0, 180);
   IRangeValidator S32_DegreeRangeQuarter(-90, 90);
   IRangeValidator S32_PosDegreeRangeQuarter(0, 90);
};

