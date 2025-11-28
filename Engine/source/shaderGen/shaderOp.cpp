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

bool resolveSourceType(LangElement* elem, Var*& outVar, const ShaderTypeInfo*& outInfo)
{
   outVar = nullptr;
   outInfo = nullptr;

   // DIRECT VAR
   if (Var* v = dynamic_cast<Var*>(elem))
   {
      outVar = v;
      outInfo = LangElement::getTypeInfo(LangElement::stringToConstType((const char*)v->type));
      return outInfo != nullptr;
   }

   // INDEX OP: arrVar[index]
   if (IndexOp* idx = dynamic_cast<IndexOp*>(elem))
   {
      Var* arr = idx->arrVar;
      if (!arr)
         return false;

      const ShaderTypeInfo* arrInfo = LangElement::getTypeInfo(LangElement::stringToConstType((const char*)arr->type));
      if (!arrInfo)
         return false;

      // array element type = same as var type but no array dimension
      outVar = arr;
      outInfo = arrInfo;
      return true;
   }

   return false;
}


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
IndexOp::IndexOp( Var* var, U32 index ) : Parent( NULL, NULL )
{
   arrVar = var; // need to keep hold of it for casts.
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
   if (!srcInfo || !dstInfo || (srcInfo->type == dstInfo->type))
   {
      srcElem->print(stream); // print something....
      return;
   }

   bool glsl = (GFX->getAdapterType() == OpenGL);
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
   if (srcSize < dstSize)
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
      LangElement* writeOut = NULL;
      Var* curVar = dynamic_cast<Var*>(mInitialVals[elem]);
      if (curVar) // is a var
      {
         const ShaderTypeInfo* curInfo = getTypeInfo(stringToConstType((const char*)curVar->type));
         if (!curInfo) // no info, cant do it cleanly.
            return;

         const U32 curSize = curInfo->cols;

         // if we are an array
         if (curVar->arraySize > 1)
         {
            for (U32 arr = 0; arr < curVar->arraySize; arr++)
            {
               writeOut = new IndexOp(curVar, arr);
               if (curSize != cols)
               {
                  CastOp* cast = new CastOp(writeOut, (GFXShaderConstType)(GFXSCT_Float + (cols - 1)));
                  cast->print(stream);
                  count += cols;
               }
               else
               {
                  writeOut->print(stream);
                  count += curSize;
               }

               if (count < matSize)
               {
                  WRITESTR(",\r\n");
               }
            }
         }
         else
         {
            if (curSize != cols)
            {
               CastOp* cast = new CastOp(curVar, (GFXShaderConstType)(GFXSCT_Float + (cols - 1)));
               cast->print(stream);
               count += cols;
            }
            else
            {
               curVar->print(stream);
               count += curSize;
            }

            if (count < matSize)
            {
               WRITESTR(",\r\n");
            }
         }
      }
      else
      {
         // Non-var LangElement, assume it produces correct vector
         mInitialVals[elem]->print(stream);
         count += cols;

         if (count < matSize)
            WRITESTR(",\r\n");
      }
   }

   // If not enough elements → pad with zeros
   while (count < matSize)
   {
      WRITESTR("0");
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

