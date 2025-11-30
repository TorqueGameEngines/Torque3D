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
#include <stdarg.h>
#include "gfx/gfxDevice.h"

#include "shaderOp.h"

//**************************************************************************
// Shader Operations
//**************************************************************************
ShaderOp::ShaderOp( LangElement *in1, LangElement *in2 )
{
   mInput[0] = in1;
   mInput[1] = in2;
}

//**************************************************************************
// Declaration Operation - for variables
//**************************************************************************
DecOp::DecOp( Var *in1 ) : Parent( in1, NULL )
{
   mInput[0] = in1;
}

//--------------------------------------------------------------------------
// Print
//--------------------------------------------------------------------------
void DecOp::print( Stream &stream )
{
   Var *var = dynamic_cast<Var*>( mInput[0] );

   WRITESTR( (char*)var->type );
   WRITESTR( " " );

   mInput[0]->print( stream );
}

//**************************************************************************
// Echo operation - deletes incoming statement!
//**************************************************************************
EchoOp::EchoOp( const char * statement ) : Parent( NULL, NULL )
{
   mStatement = statement;
}

//--------------------------------------------------------------------------
// Destructor
//--------------------------------------------------------------------------
EchoOp::~EchoOp()
{
   delete [] mStatement;
}

//--------------------------------------------------------------------------
// Print
//--------------------------------------------------------------------------
void EchoOp::print( Stream &stream )
{
   WRITESTR( mStatement );
}

//**************************************************************************
// Index operation
//**************************************************************************
IndexOp::IndexOp( Var* var, U32 index ) : Parent(var, NULL )
{
   mInput[0] = var;
   mIndex = index;
}

//--------------------------------------------------------------------------
// Print
//--------------------------------------------------------------------------
void IndexOp::print( Stream &stream )
{
   Var* var = dynamic_cast<Var*>(mInput[0]);

   mInput[0]->print(stream);
   if (var->arraySize > 1)
   {
      WRITESTR(String::ToString("[%d]", mIndex));
   }
}


//**************************************************************************
// General operation
//**************************************************************************
GenOp::GenOp( const char * statement, ... ) : Parent( NULL, NULL )
{
   VECTOR_SET_ASSOCIATION( mElemList );

   va_list args;
   va_start(args, statement);

   char* lastEntry = (char*)statement;

   while( 1 )
   {
      // search 'statement' for @ symbol
      char * str = dStrstr( lastEntry, (char *)"@" );

      if( !str )
      {
         // not found, handle end of line
         str = (char*)&statement[ dStrlen( (char*)statement ) ];

         U32 diff = str - lastEntry + 1;
         if( diff == 1 ) break;

         char * newStr = new char[diff];

         dMemcpy( (void*)newStr, lastEntry, diff );

         mElemList.push_back( new EchoOp( newStr ) );

         break;
      }

      // create and store statement fragment
      U32 diff = str - lastEntry + 1;

      if( diff == 1 )
      {
         // store langElement
         LangElement *elem = va_arg(args, LangElement* );
         AssertFatal( elem, "NULL arguement." );
         mElemList.push_back( elem );
         lastEntry++;
         continue;
      }

      char * newStr = new char[diff];

      dMemcpy( (void*)newStr, lastEntry, diff );
      newStr[diff-1] = '\0';

      lastEntry = str + 1;

      mElemList.push_back( new EchoOp( newStr ) );

      // store langElement
      LangElement *elem = va_arg(args, LangElement* );
      AssertFatal( elem, "NULL argument." );
      mElemList.push_back( elem );
   }

   va_end( args );
}

//--------------------------------------------------------------------------
// Print
//--------------------------------------------------------------------------
void GenOp::print( Stream &stream )
{
   for( U32 i=0; i<mElemList.size(); i++ )
   {
      mElemList[i]->print( stream );
   }
}

//----------------------------------------------------------------------------
// TYPE OPERATION
//----------------------------------------------------------------------------

TypeOp::TypeOp(GFXShaderConstType type) : Parent(NULL, NULL)
{
   mType = type;
}

TypeOp::~TypeOp()
{
}

//----------------------------------------------------------------------------
// Print
//----------------------------------------------------------------------------

void TypeOp::print(Stream& stream)
{
   WRITESTR(LangElement::constTypeToString(mType));
}

//----------------------------------------------------------------------------
// CAST OPERATION
//----------------------------------------------------------------------------

CastOp::CastOp(LangElement* srcVar, GFXShaderConstType type, const char* swizzleStr, const char* fillStr) : Parent(srcVar, NULL)
{
   mInput[0] = srcVar;
   mTargetType = type;
   parseStringList(swizzleStr, mSwizzle);
   parseStringList(fillStr, mFillValues);
}

void CastOp::print(Stream& stream)
{
   LangElement* srcElem = mInput[0];

   Var* srcVar = nullptr;
   const ShaderTypeInfo* srcInfo = nullptr;

   if (!resolveSourceType(srcElem, srcVar, srcInfo))
   {
      // fallback: at least print something
      srcElem->print(stream);
      return;
   }

   const ShaderTypeInfo* dstInfo = getTypeInfo(mTargetType);

   // no info? types match? nothing to do.
   if (!srcInfo || !dstInfo)
   {
      srcElem->print(stream); // print something....
      return;
   }

   const bool glsl = (GFX->getAdapterType() == OpenGL);
   const char* dstName = glsl ? dstInfo->glslName : dstInfo->hlslName;

   U32 srcSize = srcInfo->cols;
   U32 dstSize = dstInfo->cols;

   // scalar -> vector
   if (srcSize == 1 && dstSize > 1)
   {
      WRITESTR(dstName);
      WRITESTR("(");
      srcElem->print(stream);

      for (U32 i = 1; i < dstSize; i++)
      {
         WRITESTR(", ");
         WRITESTR(mFillValues[i].c_str());
      }

      WRITESTR(")");
      return;
   }

   // vector -> scalar
   if (srcSize > 1 && dstSize == 1)
   {
      srcElem->print(stream);
      WRITESTR(".");
      WRITESTR(mSwizzle[0].c_str());
      return;
   }

   // vector -> vector narrowing
   if (srcSize > dstSize)
   {
      WRITESTR(dstName);
      WRITESTR("(");
      srcElem->print(stream);
      WRITESTR(".");

      for (U32 i = 0; i < dstSize; i++)
      {
         WRITESTR(mSwizzle[i].c_str());
      }

      WRITESTR(")");
      return;
   }

   // vector -> vector widening
   if (srcSize <= dstSize)
   {
      WRITESTR(dstName);
      WRITESTR("(");
      srcElem->print(stream);
      if (mSwizzle.size() < srcSize)
      {
         WRITESTR(".");

         for (U32 i = 0; i < mSwizzle.size(); i++)
         {
            WRITESTR(mSwizzle[i].c_str());
         }
      }

      for (U32 i = getMin((U32)mSwizzle.size(), srcSize); i < dstSize; i++)
      {
         WRITESTR(", ");
         WRITESTR(mFillValues[i].c_str());
      }

      WRITESTR(")");
      return;
   }

   // fallback
   srcElem->print(stream);
}

//----------------------------------------------------------------------------
// MATRIX INITIALIZE OPERATION
//----------------------------------------------------------------------------

void MatrixInitializeOp::print(Stream& stream)
{
   Var* matVar = dynamic_cast<Var*>(mInput[0]);
   if (!matVar)
      return;

   const ShaderTypeInfo* matInfo = getTypeInfo(stringToConstType((const char*)matVar->type));
   if (!matInfo || !matInfo->isMatrix())
      return;

   // full size of the mat.
   const bool glsl = (GFX->getAdapterType() == OpenGL);
   const U32 rows = matInfo->rows;
   const U32 cols = matInfo->cols;
   const U32 matSize = rows * cols;

   if (glsl)
   {
      WRITESTR(matInfo->glslName);
      WRITESTR("(\r\n");
   }
   else
   {
      WRITESTR("{\r\n");
   }

   U32 count = 0;
   for (U32 elem = 0; elem < mInitialVals.size(); elem++)
   {
      LangElement* initElem = mInitialVals[elem];
      Var* initVar = nullptr;
      const ShaderTypeInfo* initInfo = nullptr;

      if (!resolveSourceType(initElem, initVar, initInfo))
      {
         return;
      }

      if (dynamic_cast<IndexOp*>(initElem) || dynamic_cast<CastOp*>(initElem)) // if we are a cast or index, write out.
      {
         count += initInfo->cols;
         initElem->print(stream);
      }
      else if(dynamic_cast<Var*>(initElem)) // we are a var (hopefully)
      {
         const U32 varSize = initInfo->cols;
         const bool cast = cols != varSize;

         if (initVar->arraySize > 1)
         {
            for (U32 arr = 0; arr < initVar->arraySize; arr++)
            {
               initElem = new IndexOp(initVar, arr);
               if (cast)
               {
                  CastOp* cast = new CastOp(initElem, (GFXShaderConstType)(GFXSCT_Float + (cols - 1)));
                  cast->print(stream);
                  count += cols;
               }
               else
               {
                  initElem->print(stream);
                  count += varSize;
               }

               if (count < matSize)
               {
                  WRITESTR(",\r\n");
               }
            }
         }
         else
         {
            if (cast)
            {
               CastOp* cast = new CastOp(initElem, (GFXShaderConstType)(GFXSCT_Float + (cols - 1)));
               cast->print(stream);
               count += cols;
            }
            else
            {
               initElem->print(stream);
               count += varSize;
            }

            if (count < matSize)
            {
               WRITESTR(",\r\n");
            }
         }
      }
   }

   // If not enough elements → pad with identity
   while (count < matSize)
   {
      U32 row = count / cols;
      U32 col = count % cols;

      if (row == col)
      {
         WRITESTR("1");
      }
      else
      {
         WRITESTR("0");
      }

      count++;

      if (count < matSize)
      {
         WRITESTR(",\r\n");
      }
   }


   if (glsl)
   {
      WRITESTR(")\r\n");
   }
   else
   {
      WRITESTR("}\r\n");
   }
}

MatrixMultiplyOp::MatrixMultiplyOp(LangElement* left, LangElement* right) : Parent(left, right)
{
   mInput[0] = left;
   mInput[1] = right;
}

void MatrixMultiplyOp::print(Stream& stream)
{
   LangElement* leftElem = mInput[0];
   Var* leftVar = nullptr;
   const ShaderTypeInfo* leftInfo = nullptr;

   if (!resolveSourceType(leftElem, leftVar, leftInfo))
   {
      return;
   }

   LangElement* rightElem = mInput[1];
   Var* rightVar = nullptr;
   const ShaderTypeInfo* rightInfo = nullptr;

   if (!resolveSourceType(rightElem, rightVar, rightInfo))
   {
      return;
   }

   if (leftInfo->isMatrix() && rightInfo->isVector())
   {
      if (rightInfo->cols != leftInfo->cols)
      {
         rightElem = new CastOp(rightVar, (GFXShaderConstType)(GFXSCT_Float + (leftInfo->cols - 1)));
      }
   }

   if (leftInfo->isVector() && rightInfo->isMatrix())
   {
      if (rightInfo->cols != leftInfo->cols)
      {
         leftElem = new CastOp(leftVar, (GFXShaderConstType)(GFXSCT_Float + (rightInfo->cols - 1)));
      }
   }

   else if (leftInfo->isMatrix() && rightInfo->isMatrix())
   {
      if (leftInfo->cols != rightInfo->rows)
         Con::warnf("MatrixMultiplyOp: incompatible matrices: (%dx%d) × (%dx%d)",
            leftInfo->rows, leftInfo->cols,
            rightInfo->rows, rightInfo->cols);
   }

   const bool glsl = (GFX->getAdapterType() == OpenGL);

   if (!glsl)
   {
      WRITESTR("mul(");
      leftElem->print(stream);
      WRITESTR(", ");
      rightElem->print(stream);
      WRITESTR(")");
   }
   else
   {
      leftElem->print(stream);
      WRITESTR(" * ");
      rightElem->print(stream);
   }

}
