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

#include "core/strings/stringFunctions.h"
#include "console/consoleTypes.h"
#include "console/console.h"
#include "console/engineAPI.h"
#include "console/propertyParsing.h"
#include "math/mPoint2.h"
#include "math/mPoint3.h"
#include "math/mMatrix.h"
#include "math/mQuat.h"
#include "math/mRect.h"
#include "math/mBox.h"
#include "math/mAngAxis.h"
#include "math/mTransform.h"
#include "math/mathTypes.h"
#include "math/mRandom.h"
#include "math/mEase.h"
#include "math/mathUtils.h"
#include "math/mRotation.h"
#include "core/strings/stringUnit.h"

IMPLEMENT_SCOPE( MathTypes, Math,, "" );

IMPLEMENT_STRUCT( Point2I,
   Point2I, MathTypes,
   "" )

      FIELD( x, x, 1, "X coordinate." )
      FIELD( y, y, 1, "Y coordinate." )

END_IMPLEMENT_STRUCT;
IMPLEMENT_STRUCT( Point2F,
   Point2F, MathTypes,
   "" )

      FIELD( x, x, 1, "X coordinate." )
      FIELD( y, y, 1, "Y coordinate." )

END_IMPLEMENT_STRUCT;
IMPLEMENT_STRUCT( Point3I,
   Point3I, MathTypes,
   "" )

      FIELD( x, x, 1, "X coordinate." )
      FIELD( y, y, 1, "Y coordinate." )
      FIELD( z, z, 1, "Z coordinate." )

END_IMPLEMENT_STRUCT;
IMPLEMENT_STRUCT( Point3F,
   Point3F, MathTypes,
   "" )

      FIELD( x, x, 1, "X coordinate." )
      FIELD( y, y, 1, "Y coordinate." )
      FIELD( z, z, 1, "Z coordinate." )

END_IMPLEMENT_STRUCT;
IMPLEMENT_STRUCT( Point4F,
   Point4F, MathTypes,
   "" )
   
      FIELD( x, x, 1, "X coordinate." )
      FIELD( y, y, 1, "Y coordinate." )
      FIELD( z, z, 1, "Z coordinate." )
      FIELD( w, w, 1, "W coordinate." )
      
END_IMPLEMENT_STRUCT;
IMPLEMENT_STRUCT( RectI,
   RectI, MathTypes,
   "" )

   FIELD( point,  point,  1, "The XY coordinate of the Rect." )
   FIELD( extent, extent, 1, "The width and height of the Rect." )

END_IMPLEMENT_STRUCT;
IMPLEMENT_STRUCT( RectF,
   RectF, MathTypes,
   "" )

   FIELD( point,  point,  1, "The XY coordinate of the Rect.")
   FIELD( extent, extent, 1, "The width and height of the Rect.")

END_IMPLEMENT_STRUCT;
#ifndef USE_TEMPLATE_MATRIX
IMPLEMENT_STRUCT( MatrixF,
   MatrixF, MathTypes,
   "" )

   MatrixFEngineExport::getMatrixField(),

END_IMPLEMENT_STRUCT;
#else
IMPLEMENT_STRUCT(MatrixF,
MatrixF, MathTypes,
"")

MatrixTemplateExport::getMatrixField<F32, 4, 4>(),

END_IMPLEMENT_STRUCT;
#endif
IMPLEMENT_STRUCT( AngAxisF,
   AngAxisF, MathTypes,
   "" )

   FIELD( axis,  axis,  1, "")
   FIELD( angle, angle, 1, "")

END_IMPLEMENT_STRUCT;
IMPLEMENT_STRUCT( TransformF,
   TransformF, MathTypes,
   "" )

   FIELD(mPosition,    position,    1, "")
   FIELD(mOrientation, orientation, 1, "")
   FIELD(mHasRotation, hasRotation, 1, "")

END_IMPLEMENT_STRUCT;
IMPLEMENT_STRUCT( Box3F,
   Box3F, MathTypes,
   "" )

   FIELD(minExtents, minExtents, 1, "Minimum extents of box")
   FIELD(maxExtents, maxExtents, 1, "Maximum extents of box")

END_IMPLEMENT_STRUCT;
IMPLEMENT_STRUCT( EaseF,
   EaseF, MathTypes,
   "" )

   FIELD(mDir, dir, 1, "inout, in, out")
   FIELD(mType, type, 1, "linear, etc...")
   FIELD_AS(F32, mParam, param, 2, "optional params")

END_IMPLEMENT_STRUCT;
IMPLEMENT_STRUCT(RotationF,
   RotationF, MathTypes,
   "")
   FIELD(x, x, 1, "X coordinate.")
   FIELD(y, y, 1, "Y coordinate.")
   FIELD(z, z, 1, "Z coordinate.")
   FIELD(w, w, 1, "W coordinate.")
END_IMPLEMENT_STRUCT;

//-----------------------------------------------------------------------------
// TypePoint2I
//-----------------------------------------------------------------------------
ConsoleType(Point2I, TypePoint2I, Point2I, "")
ImplementConsoleTypeCasters( TypePoint2I, Point2I )

ConsoleGetType( TypePoint2I )
{
   const char* buff = PropertyInfo::FormatProperty<S32, 2>(dptr);
   return buff;
}

ConsoleSetType( TypePoint2I )
{
   if (argc >= 1)
   {
      S32 parsed[2];
      // Combine argv into a single space-separated string if argc > 1
      char buffer[256] = { 0 };

      dStrncpy(buffer, *argv, sizeof(buffer));

      if (PropertyInfo::ParseProperty<S32, 2>(buffer, parsed)) {
         *((Point2I*)dptr) = Point2I(parsed[0], parsed[1]);
         return;
      }
   }

   Con::warnf("Point2I must be set as { x, y } or \"x y\"");
}

//-----------------------------------------------------------------------------
// TypePoint2F
//-----------------------------------------------------------------------------
ConsoleType(Point2F, TypePoint2F, Point2F, "")
ImplementConsoleTypeCasters( TypePoint2F, Point2F )

ConsoleGetType( TypePoint2F )
{
   const char* buff = PropertyInfo::FormatProperty<F32, 2>(dptr);
   return buff;
}

ConsoleSetType( TypePoint2F )
{
   if (argc >= 1)
   {
      F32 parsed[2];
      // Combine argv into a single space-separated string if argc > 1
      char buffer[256] = { 0 };

      dStrncpy(buffer, *argv, sizeof(buffer));

      if (PropertyInfo::ParseProperty<F32, 2>(buffer, parsed)) {
         *((Point2F*)dptr) = Point2F(parsed[0], parsed[1]);
         return;
      }
   }

   Con::warnf("Point2F must be set as { x, y } or \"x y\"");
}

//-----------------------------------------------------------------------------
// TypePoint3I
//-----------------------------------------------------------------------------
ConsoleType(Point3I, TypePoint3I, Point3I, "")
ImplementConsoleTypeCasters(TypePoint3I, Point3I)

ConsoleGetType( TypePoint3I )
{
   const char* buff = PropertyInfo::FormatProperty<S32, 3>(dptr);
   return buff;
}

ConsoleSetType( TypePoint3I )
{
   if (argc >= 1)
   {
      S32 parsed[3];
      // Combine argv into a single space-separated string if argc > 1
      char buffer[256] = { 0 };

      dStrncpy(buffer, *argv, sizeof(buffer));

      if (PropertyInfo::ParseProperty<S32, 3>(buffer, parsed)) {
         *((Point3I*)dptr) = Point3I(parsed[0], parsed[1], parsed[2]);
         return;
      }
   }

   Con::warnf("Point3I must be set as { x, y, z } or \"x y z\"");
}

//-----------------------------------------------------------------------------
// TypePoint3F
//-----------------------------------------------------------------------------
ConsoleType(Point3F, TypePoint3F, Point3F, "")
ImplementConsoleTypeCasters(TypePoint3F, Point3F)

ConsoleGetType( TypePoint3F )
{
   const char* buff = PropertyInfo::FormatProperty<F32, 3>(dptr);
   return buff;
}

ConsoleSetType( TypePoint3F )
{
   if (argc >= 1)
   {
      F32 parsed[3];
      // Combine argv into a single space-separated string if argc > 1
      char buffer[256] = { 0 };

      dStrncpy(buffer, *argv, sizeof(buffer));

      if (PropertyInfo::ParseProperty<F32, 3>(buffer, parsed)) {
         *((Point3F*)dptr) = Point3F(parsed[0], parsed[1], parsed[2]);
         return;
      }
   }

   Con::warnf("Point3F must be set as { x, y, z } or \"x y z\"");
}

//-----------------------------------------------------------------------------
// TypePoint4F
//-----------------------------------------------------------------------------
ConsoleType(Point4F, TypePoint4F, Point4F, "")
ImplementConsoleTypeCasters( TypePoint4F, Point4F )

ConsoleGetType( TypePoint4F )
{
   const char* buff = PropertyInfo::FormatProperty<F32, 4>(dptr);
   return buff;
}

ConsoleSetType( TypePoint4F )
{
   if (argc >= 1)
   {
      F32 parsed[4];
      // Combine argv into a single space-separated string if argc > 1
      char buffer[256] = { 0 };

      dStrncpy(buffer, *argv, sizeof(buffer));

      if (PropertyInfo::ParseProperty<F32, 4>(buffer, parsed)) {
         *((Point4F*)dptr) = Point4F(parsed[0], parsed[1], parsed[2], parsed[3]);
         return;
      }
   }

   Con::warnf("Point4F must be set as { x, y, z, w } or \"x y z w\"");
}

//-----------------------------------------------------------------------------
// TypeRectI
//-----------------------------------------------------------------------------
ConsoleType(RectI, TypeRectI, RectI, "")
ImplementConsoleTypeCasters( TypeRectI, RectI )

ConsoleGetType( TypeRectI )
{
   const char* buff = PropertyInfo::FormatProperty<S32, 4>(dptr);
   return buff;
}

ConsoleSetType( TypeRectI )
{
   if (argc >= 1)
   {
      S32 parsed[4];
      // Combine argv into a single space-separated string if argc > 1
      char buffer[256] = { 0 };

      dStrncpy(buffer, *argv, sizeof(buffer));

      if (PropertyInfo::ParseProperty<S32, 4>(buffer, parsed)) {
         *((RectI*)dptr) = RectI(parsed[0], parsed[1], parsed[2], parsed[3]);
         return;
      }
   }

   Con::warnf("RectI must be set as { x, y, w, h } or \"x y w h\"");
}

//-----------------------------------------------------------------------------
// TypeRectF
//-----------------------------------------------------------------------------
ConsoleType(RectF, TypeRectF, RectF, "")
ImplementConsoleTypeCasters( TypeRectF, RectF )

ConsoleGetType( TypeRectF )
{
   const char* buff = PropertyInfo::FormatProperty<F32, 4>(dptr);
   return buff;
}

ConsoleSetType( TypeRectF )
{
   if (argc >= 1)
   {
      F32 parsed[4];
      // Combine argv into a single space-separated string if argc > 1
      char buffer[256] = { 0 };

      dStrncpy(buffer, *argv, sizeof(buffer));

      if (PropertyInfo::ParseProperty<F32, 4>(buffer, parsed)) {
         *((RectF*)dptr) = RectF(parsed[0], parsed[1], parsed[2], parsed[3]);
         return;
      }
   }

   Con::warnf("RectF must be set as { x, y, w, h } or \"x y w h\"");
}

//-----------------------------------------------------------------------------
// TypeMatrix
//-----------------------------------------------------------------------------
ConsoleType(MatrixF, TypeMatrixF, MatrixF, "")
ImplementConsoleTypeCasters( TypeMatrixF, MatrixF )

// Oh merry confusion.  Torque stores matrices in row-major order yet to TorqueScript
// matrices were passed in column-major order, so we need to stick to this here.

ConsoleGetType( TypeMatrixF )
{
   MatrixF* mat = (MatrixF*)dptr;

   Point3F col0, col1, col2;
   mat->getColumn(0, &col0);
   mat->getColumn(1, &col1);
   mat->getColumn(2, &col2);
   static const U32 bufSize = 256;
   char* buffer = Con::getReturnBuffer(bufSize);

   PropertyInfo::FormatPropertyBuffer<F32, 3>(col0, buffer, bufSize);
   *buffer++ = ' ';
   PropertyInfo::FormatPropertyBuffer<F32, 3>(col1, buffer, bufSize);
   *buffer++ = ' ';
   PropertyInfo::FormatPropertyBuffer<F32, 3>(col2, buffer, bufSize);

   return buffer;
}

ConsoleSetType( TypeMatrixF )
{
   if (argc == 1)
   {
      F32 parsed[9];

      char* buffer = new char[dStrlen(argv[0])];
      dStrcpy(buffer, argv[0], sizeof(buffer));

      if (PropertyInfo::ParseProperty<F32, 9>(buffer, parsed)) {
         MatrixF* mat = (MatrixF*)dptr;

         mat->setColumn(0, Point3F(parsed[0], parsed[1], parsed[2]));
         mat->setColumn(1, Point3F(parsed[3], parsed[4], parsed[5]));
         mat->setColumn(2, Point3F(parsed[6], parsed[7], parsed[8]));
         return;
      }
   }

   Con::warnf("MatrixF must be set as \"c0x c0y c0z c1x c1y c1z c2x c2y c2z\"");
}

//-----------------------------------------------------------------------------
// TypeMatrixPosition
//-----------------------------------------------------------------------------
ConsoleMappedType(MatrixPosition, TypeMatrixPosition, Point3F, MatrixF, "")

ConsoleGetType( TypeMatrixPosition )
{
   F32* col = (F32*)dptr + 3;
   static const U32 bufSize = 256;
   char* returnBuffer = Con::getReturnBuffer(bufSize);
   Point4F pos(col[0], col[4], col[8], col[12]);

   if (col[12] == 1.0f)
      PropertyInfo::FormatPropertyBuffer<F32, 3>(&pos, returnBuffer, bufSize);
   else
      PropertyInfo::FormatPropertyBuffer<F32, 4>(&pos, returnBuffer, bufSize);

   return returnBuffer;
}

ConsoleSetType( TypeMatrixPosition )
{
   if (argc >= 1)
   {
      F32 parsed[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
      // Combine argv into a single space-separated string if argc > 1
      char buffer[256] = { 0 };
      dStrncpy(buffer, *argv, sizeof(buffer));
      // we dont want to hard fail based on the count.
      // this will allow any number of properties to be set.
      PropertyInfo::ParseProperty<F32, 4>(buffer, parsed);
      {
         Point4F temp(parsed[0], parsed[1], parsed[2], parsed[3]);
         MatrixF* mat = (MatrixF*)dptr;
         mat->setColumn(3, temp);
         return;
      }
   }

   Con::warnf("Matrix position must be set as { x, y, z, w } or \"x y z w\"");

}

//-----------------------------------------------------------------------------
// TypeMatrixRotation
//-----------------------------------------------------------------------------
ConsoleMappedType(MatrixRotation, TypeMatrixRotation, AngAxisF, MatrixF, "")

ConsoleGetType( TypeMatrixRotation )
{
   AngAxisF aa(*(MatrixF*)dptr);
   aa.axis.normalize();
   aa.angle = mRadToDeg(aa.angle);
   const char* buff = PropertyInfo::FormatProperty<F32, 4>(&aa);
   return buff;
}

ConsoleSetType( TypeMatrixRotation )
{
   if (argc >= 1)
   {
      F32 parsed[4];
      // Combine argv into a single space-separated string if argc > 1
      char buffer[256] = { 0 };
      dStrncpy(buffer, *argv, sizeof(buffer));

      if (PropertyInfo::ParseProperty<F32, 4>(buffer, parsed))
      {
         AngAxisF aa(Point3F(parsed[0], parsed[1], parsed[2]), mDegToRad(parsed[3]));
         MatrixF temp;
         aa.setMatrix(&temp);

         F32* pDst = *(MatrixF*)dptr;
         const F32* pSrc = temp;
         for (U32 i = 0; i < 3; i++)
            for (U32 j = 0; j < 3; j++)
               pDst[i * 4 + j] = pSrc[i * 4 + j];
         return;
      }
   }

   Con::warnf("Matrix rotation must be set as { x, y, z, angle } or \"x y z angle\"");
}

//-----------------------------------------------------------------------------
// TypeAngAxisF
//-----------------------------------------------------------------------------
ConsoleType(AngAxisF, TypeAngAxisF, AngAxisF, "")
ImplementConsoleTypeCasters( TypeAngAxisF, AngAxisF )

ConsoleGetType( TypeAngAxisF )
{
   AngAxisF* aa = ( AngAxisF* ) dptr;
   aa->angle = mRadToDeg(aa->angle);
   const char* buff = PropertyInfo::FormatProperty<F32, 4>(aa);
   return buff;
}

ConsoleSetType( TypeAngAxisF )
{
   if (argc >= 1)
   {
      F32 parsed[4];
      // Combine argv into a single space-separated string if argc > 1
      char buffer[256] = { 0 };
      dStrncpy(buffer, *argv, sizeof(buffer));

      if(PropertyInfo::ParseProperty<F32, 4>(buffer, parsed))
      {
         AngAxisF* aa = (AngAxisF*)dptr;
         aa->set(Point3F(parsed[0], parsed[1], parsed[2]), mDegToRad(parsed[3]));
         return;
      }
   }

   Con::warnf("AngAxisF must be set as { x, y, z, angle } or \"x y z angle\"");
}


//-----------------------------------------------------------------------------
// TypeTransformF
//-----------------------------------------------------------------------------

const TransformF TransformF::Identity( Point3F::Zero, AngAxisF( Point3F( 0, 0, 1 ), 0) );

ConsoleType(TransformF, TypeTransformF, TransformF, "")
ImplementConsoleTypeCasters( TypeTransformF, TransformF )

ConsoleGetType( TypeTransformF )
{
   const char* buff = PropertyInfo::FormatProperty<F32, 7>(dptr);
   return buff;
}

ConsoleSetType( TypeTransformF )
{
   if(argc >= 1)
   {
      F32 parsed[7];
      // Combine argv into a single space-separated string if argc > 1
      char buffer[256] = { 0 };
      dStrncpy(buffer, *argv, sizeof(buffer));

      if (!PropertyInfo::ParseProperty<F32, 7>(buffer, parsed))
      {
         TransformF* aa = (TransformF*)dptr;
         aa->mPosition.x = parsed[0];
         aa->mPosition.y = parsed[1];
         aa->mPosition.z = parsed[2];
         aa->mOrientation.axis.x = 1.000f;
         aa->mOrientation.axis.y = 0.000f;
         aa->mOrientation.axis.z = 0.000f;
         aa->mOrientation.angle = 0.000f;
         return;
      }
      else
      {
         TransformF* aa = (TransformF*)dptr;
         aa->mPosition.x = parsed[0];
         aa->mPosition.y = parsed[1];
         aa->mPosition.z = parsed[2];
         aa->mOrientation.axis.x = parsed[3];
         aa->mOrientation.axis.y = parsed[4];
         aa->mOrientation.axis.z = parsed[5];
         aa->mOrientation.angle = parsed[6];
         aa->mHasRotation = true;
         return;
      }
   }

   Con::warnf("TransformF must be set as { px, py, pz, x, y, z, angle } or \"px py pz x y z angle\"");
}



//-----------------------------------------------------------------------------
// TypeBox3F
//-----------------------------------------------------------------------------
ConsoleType(Box3F, TypeBox3F, Box3F, "")
ImplementConsoleTypeCasters( TypeBox3F, Box3F )

ConsoleGetType( TypeBox3F )
{
   const char* buff = PropertyInfo::FormatProperty<F32, 6>(dptr);
   return buff;
}

ConsoleSetType( TypeBox3F )
{
   if (argc >= 1)
   {
      F32 parsed[6];
      // Combine argv into a single space-separated string if argc > 1
      char buffer[256] = { 0 };
      dStrncpy(buffer, *argv, sizeof(buffer));

      if (PropertyInfo::ParseProperty<F32, 6>(buffer, parsed))
      {
         Box3F* pDst = (Box3F*)dptr;
         pDst->minExtents.x = parsed[0];
         pDst->minExtents.y = parsed[1];
         pDst->minExtents.z = parsed[2];
         pDst->maxExtents.x = parsed[3];
         pDst->maxExtents.y = parsed[4];
         pDst->maxExtents.z = parsed[5];
         return;
      }
   }

   Con::warnf("Box3F must be set as \"xMin yMin zMin xMax yMax zMax\"");
}


//-----------------------------------------------------------------------------
// TypeEaseF
//-----------------------------------------------------------------------------
ConsoleType(EaseF, TypeEaseF, EaseF, "")
ImplementConsoleTypeCasters( TypeEaseF, EaseF )

ConsoleGetType( TypeEaseF )
{
   static const U32 bufSize = 256;
   char* buffer = Con::getReturnBuffer(bufSize);

   EaseF* pEase = (EaseF*)dptr;
   PropertyInfo::FormatPropertyBuffer<S32, 2>(pEase + 0, buffer, bufSize);
   *buffer++ = ' ';
   PropertyInfo::FormatPropertyBuffer<F32, 2>(pEase + 2, buffer, bufSize);

   return buffer;
}

ConsoleSetType( TypeEaseF )
{
   if (argc >= 1)
   {
      F32 parsed[4];
      parsed[2] = -1.0f;
      parsed[3] = -1.0f;

      // Combine argv into a single space-separated string if argc > 1
      char buffer[256] = { 0 };

      dStrncpy(buffer, *argv, sizeof(buffer));

      // same as matrix do not hard fail based on count!
      PropertyInfo::ParseProperty<F32, 4>(buffer, parsed);
      {
         ((EaseF*)dptr)->set(mRound(parsed[0]), mRound(parsed[1]), parsed[2], parsed[3]);
         return;
      }
   }

   Con::warnf("EaseF must be set as \"dir type [param0 param1]\"");
}

//-----------------------------------------------------------------------------
// TypeRotationF
//-----------------------------------------------------------------------------
ConsoleType(RotationF, TypeRotationF, RotationF, "")
ImplementConsoleTypeCasters( TypeRotationF, RotationF )

ConsoleGetType(TypeRotationF)
{
   RotationF *pt = (RotationF *)dptr;
   static const U32 bufSize = 256;
   char* returnBuffer = Con::getReturnBuffer(bufSize);

   if (pt->mRotationType == RotationF::Euler)
   {
      EulerF out = pt->asEulerF(RotationF::Degrees);
      PropertyInfo::FormatPropertyBuffer<F32, 3>(out, returnBuffer, bufSize);
   }
   else if (pt->mRotationType == RotationF::AxisAngle)
   {
      AngAxisF out = pt->asAxisAngle(RotationF::Degrees);
      PropertyInfo::FormatPropertyBuffer<F32, 4>(&out, returnBuffer, bufSize);
   }

   return returnBuffer;
}

ConsoleSetType(TypeRotationF)
{
   if (argc >= 1)
   {
      // Combine argv into a single space-separated string if argc > 1
      char buffer[256] = { 0 };
      dStrncpy(buffer, *argv, sizeof(buffer));

      U32 elements = StringUnit::getUnitCount(buffer, " \t\n");
      if (elements == 3)
      {
         F32 parsed[3];
         if(PropertyInfo::ParseProperty<F32, 3>(buffer, parsed))
         {
            EulerF in(parsed[0], parsed[1], parsed[2]);
            ((RotationF*)dptr)->set(in, RotationF::Degrees);
            return;
         }
      }
      else if (elements == 4)
      {
         F32 parsed[4];
         if (PropertyInfo::ParseProperty<F32, 4>(buffer, parsed))
         {
            AngAxisF in(Point3F(parsed[0], parsed[1], parsed[2]), parsed[3]);
            ((RotationF*)dptr)->set(in, RotationF::Degrees);
            return;
         }
      }
   }

   Con::warnf("RotationF must be set as { x, y, z, w } or \"x y z w\"");
}

//-----------------------------------------------------------------------------

DefineEngineFunction( VectorAdd, VectorF, ( VectorF a, VectorF b ),,
   "Add two vectors.\n"
   "@param a The first vector.\n"
   "@param b The second vector.\n"
   "@return The vector @a a + @a b.\n\n"
   "@tsexample\n"
      "//-----------------------------------------------------------------------------\n"
      "//\n"
      "// VectorAdd( %a, %b );\n"
      "//\n"
      "// The sum of vector a, (ax, ay, az), and vector b, (bx, by, bz) is:\n"
      "//\n"
      "//     a + b = ( ax + bx, ay + by, az + bz )\n"
      "//\n"
      "//-----------------------------------------------------------------------------\n"
      "%a = \"1 0 0\";\n"
      "%b = \"0 1 0\";\n\n"
      "// %r = \"( 1 + 0, 0 + 1, 0 + 0 )\";\n"
      "// %r = \"1 1 0\";\n"
      "%r = VectorAdd( %a, %b );\n"
   "@endtsexample\n\n"
   "@ingroup Vectors")
{
   return a + b;
}

//-----------------------------------------------------------------------------

DefineEngineFunction( VectorSub, VectorF, ( VectorF a, VectorF b ),,
   "Subtract two vectors.\n"
   "@param a The first vector.\n"
   "@param b The second vector.\n"
   "@return The vector @a a - @a b.\n\n"
   "@tsexample\n"
	"//-----------------------------------------------------------------------------\n"
	"//\n"
	"// VectorSub( %a, %b );\n"
	"//\n"
	"// The difference of vector a, (ax, ay, az), and vector b, (bx, by, bz) is:\n"
	"//\n"
	"//     a - b = ( ax - bx, ay - by, az - bz )\n"
	"//\n"
	"//-----------------------------------------------------------------------------\n\n"

	"%a = \"1 0 0\";\n"
	"%b = \"0 1 0\";\n\n"

	"// %r = \"( 1 - 0, 0 - 1, 0 - 0 )\";\n"
	"// %r = \"1 -1 0\";\n"
	"%r = VectorSub( %a, %b );\n"
   "@endtsexample\n\n"
   "@ingroup Vectors" )
{
   return a - b;
}

//-----------------------------------------------------------------------------

DefineEngineFunction( VectorScale, VectorF, ( VectorF a, F32 scalar ),,
   "Scales a vector by a scalar.\n"
   "@param a The vector to scale.\n"
   "@param scalar The scale factor.\n"
   "@return The vector @a a * @a scalar.\n\n"
   "@tsexample\n"
	"//-----------------------------------------------------------------------------\n"
	"//\n"
	"// VectorScale( %a, %v );\n"
	"//\n"
	"// Scaling vector a, (ax, ay, az), but the scalar, v, is:\n"
	"//\n"
	"//     a * v = ( ax * v, ay * v, az * v )\n"
	"//\n"
	"//-----------------------------------------------------------------------------\n\n"

	"%a = \"1 1 0\";\n"
	"%v = \"2\";\n\n"

	"// %r = \"( 1 * 2, 1 * 2, 0 * 2 )\";\n"
	"// %r = \"2 2 0\";\n"
	"%r = VectorScale( %a, %v );\n"
   "@endtsexample\n\n"
   "@ingroup Vectors" )
{
   return a * scalar;
}
DefineEngineFunction( VectorMul, VectorF, ( VectorF a, VectorF b ),,
   "Multiplies two vectors.\n"
   "@param a The first vector.\n"
   "@param b The second vector.\n"
   "@return The vector @a a * @a b.\n\n"
   "@tsexample\n"
	"//-----------------------------------------------------------------------------\n"
	"//\n"
	"// VectorMul( %a, %b );\n"
	"//\n"
	"// The multiplication of vector a, (ax, ay, az), and vector b, (bx, by, bz) is:\n"
	"//\n"
	"//     a * b = ( ax * bx, ay * by, az * bz )\n"
	"//\n"
	"//-----------------------------------------------------------------------------\n\n"

	"%a = \"1 0 0\";\n"
	"%b = \"0 1 0\";\n\n"

	"// %r = \"( 1 * 0, 0 * 1, 0 * 0 )\";\n"
	"// %r = \"0 0 0\";\n"
	"%r = VectorMul( %a, %b );\n"
   "@endtsexample\n\n"
   "@ingroup Vectors" )
{
   return a * b;
}

DefineEngineFunction( VectorDiv, VectorF, ( VectorF a, VectorF b ),,
   "Divide two vectors.\n"
   "@param a The first vector.\n"
   "@param b The second vector.\n"
   "@return The vector @a a / @a b.\n\n"
   "@tsexample\n"
	"//-----------------------------------------------------------------------------\n"
	"//\n"
	"// VectorDiv( %a, %b );\n"
	"//\n"
	"// The division of vector a, (ax, ay, az), and vector b, (bx, by, bz) is:\n"
	"//\n"
	"//     a * b = ( ax / bx, ay / by, az / bz )\n"
	"//\n"
	"//-----------------------------------------------------------------------------\n\n"

	"%a = \"1 1 1\";\n"
	"%b = \"2 2 2\";\n\n"

	"// %r = \"( 1 / 2, 1 / 2, 1 / 2 )\";\n"
	"// %r = \"0.5 0.5 0.5\";\n"
	"%r = VectorDiv( %a, %b );\n"
   "@endtsexample\n\n"
   "@ingroup Vectors" )
{
   //this is kind of bad, but so is dividing by 0
   if(b.x == 0) b.x = 0.000001f;
   if(b.y == 0) b.y = 0.000001f;
   if(b.z == 0) b.z = 0.000001f;
   
   return a / b;
}

//-----------------------------------------------------------------------------

DefineEngineFunction( VectorNormalize, VectorF, ( VectorF v ),,
   "Brings a vector into its unit form, i.e. such that it has the magnitute 1.\n"
   "@param v The vector to normalize.\n"
   "@return The vector @a v scaled to length 1.\n\n"
   "@tsexample\n"
	"//-----------------------------------------------------------------------------\n"
	"//\n"
	"// VectorNormalize( %a );\n"
	"//\n"
	"// The normalized vector a, (ax, ay, az), is:\n"
	"//\n"
	"//     a^ = a / ||a||\n"
	"//        = ( ax / ||a||, ay / ||a||, az / ||a|| )\n"
	"//\n"
	"//-----------------------------------------------------------------------------\n\n"

	"%a = \"1 1 0\";\n"
	"%l = 1.414;\n\n"

	"// %r = \"( 1 / 1.141, 1 / 1.141, 0 / 1.141 )\";\n"
	"// %r = \"0.707 0.707 0\";\n"
	"%r = VectorNormalize( %a );\n"
   "@endtsexample\n\n"
   "@ingroup Vectors" )
{
   VectorF n( v );
   n.normalizeSafe();
   return n;
}

//-----------------------------------------------------------------------------

DefineEngineFunction( VectorDot, F32, ( VectorF a, VectorF b ),,
   "Compute the dot product of two vectors.\n"
   "@param a The first vector.\n"
   "@param b The second vector.\n"
   "@return The dot product @a a * @a b.\n\n"
   "@tsexample\n"
	"//-----------------------------------------------------------------------------\n"
	"//\n"
	"// VectorDot( %a, %b );\n"
	"//\n"
	"// The dot product between vector a, (ax, ay, az), and vector b, (bx, by, bz), is:\n"
	"//\n"
	"//     a . b = ( ax * bx + ay * by + az * bz )\n"
	"//\n"
	"//-----------------------------------------------------------------------------\n\n"

	"%a = \"1 1 0\";\n"
	"%b = \"2 0 1\";\n\n"

	"// %r = \"( 1 * 2 + 1 * 0 + 0 * 1 )\";\n"
	"// %r = 2;\n"
	"%r = VectorDot( %a, %b );\n"
   "@endtsexample\n\n"
   "@ingroup Vectors" )
{
   return mDot( a, b );
}

//-----------------------------------------------------------------------------

DefineEngineFunction( VectorCross, VectorF, ( VectorF a, VectorF b ),,
   "Calculcate the cross product of two vectors.\n"
   "@param a The first vector.\n"
   "@param b The second vector.\n"
   "@return The cross product @a x @a b.\n\n"
   "@tsexample\n"
	"//-----------------------------------------------------------------------------\n"
	"//\n"
	"// VectorCross( %a, %b );\n"
	"//\n"
	"// The cross product of vector a, (ax, ay, az), and vector b, (bx, by, bz), is\n"
	"//\n"
	"//     a x b = ( ( ay * bz ) - ( az * by ), ( az * bx ) - ( ax * bz ), ( ax * by ) - ( ay * bx ) )\n"
	"//\n"
	"//-----------------------------------------------------------------------------\n\n"

	"%a = \"1 1 0\";\n"
	"%b = \"2 0 1\";\n\n"

	"// %r = \"( ( 1 * 1 ) - ( 0 * 0 ), ( 0 * 2 ) - ( 1 * 1 ), ( 1 * 0 ) - ( 1 * 2 ) )\";\n"
	"// %r = \"1 -1 -2\";\n"
	"%r = VectorCross( %a, %b );\n"
   "@endtsexample\n\n"	
   "@ingroup Vectors" )
{
   VectorF v;
   mCross( a, b, &v );
   return v;
}

//-----------------------------------------------------------------------------

DefineEngineFunction( VectorDist, F32, ( VectorF a, VectorF b ),,
   "Compute the distance between two vectors.\n"
   "@param a The first vector.\n"
   "@param b The second vector.\n"
   "@return The length( @a b - @a a ).\n\n"
   "@tsexample\n"
	"//-----------------------------------------------------------------------------\n"
	"//\n"
	"// VectorDist( %a, %b );\n"
	"//\n"
	"// The distance between vector a, (ax, ay, az), and vector b, (bx, by, bz), is\n"
	"//\n"
	"//     a -> b = ||( b - a )||\n"
	"//            = ||( bx - ax, by - ay, bz - az )||\n"
	"//            = mSqrt( ( bx - ax ) * ( bx - ax ) + ( by - ay ) * ( by - ay ) + ( bz - az ) * ( bz - az ) )\n"
	"//\n"
	"//-----------------------------------------------------------------------------\n\n"

	"%a = \"1 1 0\";\n"
	"%b = \"2 0 1\";\n\n"

	"// %r = mSqrt( ( 2 - 1 ) * ( 2 - 1) + ( 0 - 1 ) * ( 0 - 1 ) + ( 1 - 0 ) * ( 1 - 0 ) );\n"
	"// %r = mSqrt( 3 );\n"
	"%r = VectorDist( %a, %b );\n"
   "@endtsexample\n\n"
   "@ingroup Vectors" )
{
   VectorF v = b - a;
   return v.len();
}

//-----------------------------------------------------------------------------

DefineEngineFunction( VectorMidPoint, VectorF, ( VectorF a, VectorF b ),,
   "Gets the midpoint between the two vectors.\n"
   "@param a The first vector.\n"
   "@param b The second vector.\n"
   "@return The vector (@a a + @a b) / 2.\n\n"
   "@tsexample\n"
      "//-----------------------------------------------------------------------------\n"
      "//\n"
      "// VectorMidPoint( %a, %b );\n"
      "//\n"
      "// The midpoint of vector a, (ax, ay, az), and vector b, (bx, by, bz) is:\n"
      "//\n"
	  "//     (a + b)/2 = ( (ax + bx) /2, ay + by) /2, (az + bz) /2 )\n"
      "//\n"
      "//-----------------------------------------------------------------------------\n"
//      "%a = \"1 0 0\";\n"
//      "%b = \"0 1 0\";\n\n"
//      "// %r = \"( 1 + 0, 0 + 1, 0 + 0 )\";\n"
//      "// %r = \"1 1 0\";\n"
//      "%r = VectorAdd( %a, %b );\n"
   "@endtsexample\n\n"
   "@ingroup Vectors")
{
   return (a + b)/2.0f;
}

//-----------------------------------------------------------------------------

DefineEngineFunction( VectorLen, F32, ( VectorF v ),,
   "Calculate the magnitude of the given vector.\n"
   "@param v A vector.\n"
   "@return The length of vector @a v.\n\n"
   "@tsexample\n"
	"//-----------------------------------------------------------------------------\n"
	"//\n"
	"// VectorLen( %a );\n"
	"//\n"
	"// The length or magnitude of  vector a, (ax, ay, az), is:\n"
	"//\n"
	"//     ||a|| = Sqrt( ax * ax + ay * ay + az * az )\n"
	"//\n"
	"//-----------------------------------------------------------------------------\n\n"

	"%a = \"1 1 0\";\n\n"

	"// %r = mSqrt( 1 * 1 + 1 * 1 + 0 * 0 );\n"
	"// %r = mSqrt( 2 );\n"
	"// %r = 1.414;\n"
	"%r = VectorLen( %a );\n"
   "@endtsexample\n\n"
   "@ingroup Vectors" )
{
   return v.len();
}

//-----------------------------------------------------------------------------

DefineEngineFunction( VectorOrthoBasis, MatrixF, ( AngAxisF aa ),,
   "Create an orthogonal basis from the given vector.\n"
   "@param aaf The vector to create the orthogonal basis from.\n"
   "@return A matrix representing the orthogonal basis.\n"
   "@ingroup Vectors" )
{
   MatrixF mat;
   aa.setMatrix(&mat);
   return mat;
}

DefineEngineFunction(toEuler, VectorF, (MatrixF _in), ,
   "#Brief get the rotation of a matrix\n")
{
   return _in.getForwardVector();
}
//-----------------------------------------------------------------------------

//ConsoleFunction(VectorRot, const char*, 3, 3, "(Vector3F, float) rotate a vector in 2d")
DefineEngineFunction( VectorRot, const char*, (Point3F v, F32 angle), , "(Vector3F, float) rotate a vector in 2d")
{
	//VectorF v(0,0,0);
	//dSscanf(argv[1],"%g %g %g",&v.x,&v.y,&v.z);
	//dSscanf(axeStr,"%g %g %g",&v.x,&v.y,&v.z);

	//float angle = dAtof(argv[2]);
	//float angle = dAtof(angleStr);

	float x = 0, y = 0;

	x = v.x * cos(angle) - v.y * sin(angle);            
	y = v.x * sin(angle) + v.y * cos(angle); 

	char* returnBuffer = Con::getReturnBuffer(256);
	dSprintf(returnBuffer,256,"%g %g %g", x, y, v.z);
	return returnBuffer;
}

DefineEngineFunction( VectorLerp, VectorF, ( VectorF a, VectorF b, F32 t ),,
   "Linearly interpolate between two vectors by @a t.\n"
   "@param a Vector to start interpolation from.\n"
   "@param b Vector to interpolate to.\n"
   "@param t Interpolation factor (0-1).  At zero, @a a is returned and at one, @a b is returned.  In between, an interpolated vector "
      "between @a a and @a b is returned.\n"
   "@return An interpolated vector between @a a and @a b.\n\n"
   "@tsexample\n"
	"//-----------------------------------------------------------------------------\n"
	"//\n"
	"// VectorLerp( %a, %b );\n"
	"//\n"
	"// The point between vector a, (ax, ay, az), and vector b, (bx, by, bz), which is\n"
	"// weighted by the interpolation factor, t, is\n"
	"//\n"
	"//     r = a + t * ( b - a )\n"
	"//       = ( ax + t * ( bx - ax ), ay + t * ( by - ay ), az + t * ( bz - az ) )\n"
	"//\n"
	"//-----------------------------------------------------------------------------\n\n"

	"%a = \"1 1 0\";\n"
	"%b = \"2 0 1\";\n"
	"%v = \"0.25\";\n\n"

	"// %r = \"( 1 + 0.25 * ( 2 - 1 ), 1 + 0.25 * ( 0 - 1 ), 0 + 0.25 * ( 1 - 0 ) )\";\n"
	"// %r = \"1.25 0.75 0.25\";\n"
	"%r = VectorLerp( %a, %b );\n"
   "@endtsexample\n\n"
   "@ingroup Vectors" )
{
   VectorF c;
   c.interpolate( a, b, t );
   
   return c;
}

DefineEngineFunction(VectorReflect, VectorF, (VectorF vec, VectorF normal), ,
   "Compute the reflection of a vector based on a normal.\n"
   "@param a The vector.\n"
   "@param b The normal.\n"
   "@return The reflected vector.\n\n"
   "@ingroup Vectors")
{
   normal.normalize();

   return MathUtils::reflect(vec, normal);
}

//-----------------------------------------------------------------------------

DefineEngineFunction( MatrixCreate, TransformF, ( VectorF position, AngAxisF orientation ),,
   "Create a transform from the given translation and orientation.\n"
   "@param position The translation vector for the transform.\n"
   "@param orientation The axis and rotation that orients the transform.\n"
   "@return A transform based on the given position and orientation.\n"
   "@ingroup Matrices" )
{
   TransformF transform( position, orientation );
   return transform;
}

//-----------------------------------------------------------------------------

DefineEngineFunction( MatrixCreateFromEuler, TransformF, ( Point3F angles ),,
   "@Create a matrix from the given rotations.\n\n"
   "@param Vector3F X, Y, and Z rotation in *radians*.\n"
   "@return A transform based on the given orientation.\n"
   "@ingroup Matrices" )
{
   QuatF rotQ( angles );
   AngAxisF aa;
   aa.set(rotQ);

   return TransformF( Point3F::Zero, aa );
}

//-----------------------------------------------------------------------------

DefineEngineFunction( MatrixMultiply, TransformF, ( TransformF left, TransformF right ),,
   "@brief Multiply the two matrices.\n\n"
   "@param left First transform.\n"
   "@param right Right transform.\n"
   "@return Concatenation of the two transforms.\n"
   "@ingroup Matrices" )
{
   MatrixF m1 = left.getMatrix();
   MatrixF m2 = right.getMatrix();

   m1.mul( m2 );

   return TransformF( m1 );
}

//-----------------------------------------------------------------------------

DefineEngineFunction( MatrixMulVector, VectorF, ( TransformF transform, VectorF vector ),,
   "@brief Multiply the vector by the transform assuming that w=0.\n\n"
   "This function will multiply the given vector by the given transform such that translation will "
   "not affect the vector.\n\n"
   "@param transform A transform.\n"
   "@param vector A vector.\n"
   "@return The transformed vector.\n"
   "@ingroup Matrices")
{
   MatrixF m = transform.getMatrix();
   m.mulV( vector );
   return vector;
}

//-----------------------------------------------------------------------------

DefineEngineFunction( MatrixMulPoint, Point3F, ( TransformF transform, Point3F point ),,
   "@brief Multiply the given point by the given transform assuming that w=1.\n\n"
   "This function will multiply the given vector such that translation with take effect.\n"
   "@param transform A transform.\n"
   "@param point A vector.\n"
   "@return The transformed vector.\n"
   "@ingroup Matrices")
{
   MatrixF m = transform.getMatrix();
   m.mulP( point );
   return point;
}

ConsoleFunctionGroupEnd(MatrixMath);

//------------------------------------------------------------------------------

DefineEngineFunction( getBoxCenter, Point3F, ( Box3F box ),,
   "Get the center point of an axis-aligned box.\n\n"
   "@param b A Box3F, in string format using \"minExtentX minExtentY minExtentZ maxExtentX maxExtentY maxExtentZ\"\n"
   "@return Center of the box.\n"
   "@ingroup Math")
{
   return box.getCenter();
}

//------------------------------------------------------------------------------

DefineEngineFunction( setRandomSeed, void, ( S32 seed ), ( -1 ),
   "Set the current seed for the random number generator.\n"
   "Based on this seed, a repeatable sequence of numbers will be produced by getRandom().\n"
   "@param seed The seed with which to initialize the randon number generator with.  The same seed will always leed to"
      "the same sequence of pseudo-random numbers.\n"
      "If -1, the current timestamp will be used as the seed which is a good basis for randomization.\n"
   "@ingroup Random" )
{
   if( seed == -1 )
      seed = Platform::getRealMilliseconds();

	MRandomLCG::setGlobalRandSeed( seed );
}

//------------------------------------------------------------------------------

DefineEngineFunction( getRandomSeed, S32, (),,
   "Get the current seed used by the random number generator.\n"
   "@return The current random number generator seed value.\n"
   "@ingroup Random" )
{
   return gRandGen.getSeed();
}

//------------------------------------------------------------------------------

S32 mRandI(S32 i1, S32 i2)
{
   return gRandGen.randI(i1, i2);
}

F32 mRandF(F32 f1, F32 f2)
{
   return gRandGen.randF(f1, f2);
}

F32 mRandF()
{
   return gRandGen.randF();
}

DefineEngineFunction(getRandom, F32, (S32 a, S32 b), (S32_MAX, S32_MAX),
   "( int a, int b ) "
   "@brief Returns a random number based on parameters passed in..\n\n"
   "If no parameters are passed in, getRandom() will return a float between 0.0 and 1.0. If one "
   "parameter is passed an integer between 0 and the passed in value will be returned. Two parameters will "
   "return an integer between the specified numbers.\n\n"
   "@param a If this is the only parameter, a number between 0 and a is returned. Elsewise represents the lower bound.\n"
   "@param b Upper bound on the random number.  The random number will be <= @a b.\n"
   "@return A pseudo-random integer between @a a and @a b, between 0 and a, or a "
   "float between 0.0 and 1.1 depending on usage.\n\n"
   "@note All parameters are optional."
   "@see setRandomSeed\n"
   "@ingroup Random" )
{
   if (a != S32_MAX)
   {
      if (b == S32_MAX)
         return F32(gRandGen.randI(0, getMax(a, 0)));
      else
      {
         S32 min = a;
         S32 max = b;
         if (min > max)
         {
            S32 t = min;
            min = max;
            max = t;
         }
         return F32(gRandGen.randI(min, max));
      }
   }
   return gRandGen.randF();
}

DefineEngineFunction(mAddS32, const char *, (S32 v1, S32 v2), , "Add 2 large numbers")
{
   S32 res = v1 + v2;
   char *ret = Con::getReturnBuffer(64);
   dSprintf(ret, 64, "%i", res);

   return ret;
}
DefineEngineFunction(mSubS32, const char *, (S32 v1, S32 v2), , "Subtract 2 large numbers")
{
   S32 res = v1 - v2;
   char *ret = Con::getReturnBuffer(64);
   dSprintf(ret, 64, "%i", res);

   return ret;
}

DefineEngineFunction(mMulS32, const char *, (S32 v1, S32 v2), , "Multiply 2 large numbers")
{
   S32 res = v1 * v2;
   char *ret = Con::getReturnBuffer(64);
   dSprintf(ret, 64, "%i", res);

   return ret;
}

DefineEngineFunction(mDivS32, const char *, (S32 v1, S32 v2), , "Divide 2 large numbers")
{
   S32 res = v1 / v2;
   char *ret = Con::getReturnBuffer(64);
   dSprintf(ret, 64, "%i", res);

   return ret;
}
//------------------------------------------------------------------------------
