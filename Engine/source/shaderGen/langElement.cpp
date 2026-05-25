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
#include "core/util/str.h"
#include "gfx/gfxDevice.h"
#include "shaderGen/shaderOp.h"
#include "langElement.h"

//**************************************************************************
// Language element
//**************************************************************************
Vector<LangElement*> LangElement::elementList( __FILE__, __LINE__ );

static const ShaderTypeInfo ShaderTypes[] =
{
   // ---- FLOATS ----
   { GFXSCT_Float,   "float",  "float",   STC_Scalar, 1, 1 },
   { GFXSCT_Float2,  "vec2",   "float2",  STC_Vector, 1, 2 },
   { GFXSCT_Float3,  "vec3",   "float3",  STC_Vector, 1, 3 },
   { GFXSCT_Float4,  "vec4",   "float4",  STC_Vector, 1, 4 },

   // ---- MATRICES ----
   { GFXSCT_Float2x2, "mat2",    "float2x2", STC_Matrix, 2, 2 },
   { GFXSCT_Float3x3, "mat3",    "float3x3", STC_Matrix, 3, 3 },
   { GFXSCT_Float3x4, "mat3x4",  "float3x4", STC_Matrix, 3, 4 },
   { GFXSCT_Float4x3, "mat4x3",  "float4x3", STC_Matrix, 4, 3 },
   { GFXSCT_Float4x4, "mat4",    "float4x4", STC_Matrix, 4, 4 },

   // ---- INT ----
   { GFXSCT_Int,     "int",     "int",     STC_Scalar, 1, 1 },
   { GFXSCT_Int2,    "ivec2",   "int2",    STC_Vector, 1, 2 },
   { GFXSCT_Int3,    "ivec3",   "int3",    STC_Vector, 1, 3 },
   { GFXSCT_Int4,    "ivec4",   "int4",    STC_Vector, 1, 4 },

   // ---- UINT ----
   { GFXSCT_UInt,    "uint",    "uint",    STC_Scalar, 1, 1 },
   { GFXSCT_UInt2,   "uvec2",   "uint2",   STC_Vector, 1, 2 },
   { GFXSCT_UInt3,   "uvec3",   "uint3",   STC_Vector, 1, 3 },
   { GFXSCT_UInt4,   "uvec4",   "uint4",   STC_Vector, 1, 4 },

   // ---- BOOL ----
   { GFXSCT_Bool,    "bool",    "bool",    STC_Scalar, 1, 1 },
   { GFXSCT_Bool2,   "bvec2",   "bool2",   STC_Vector, 1, 2 },
   { GFXSCT_Bool3,   "bvec3",   "bool3",   STC_Vector, 1, 3 },
   { GFXSCT_Bool4,   "bvec4",   "bool4",   STC_Vector, 1, 4 },

   // ---- SAMPLERS ----
   { GFXSCT_Sampler,             "sampler2D",         "Texture2D",         STC_Sampler, 0, 0 },
   { GFXSCT_SamplerCube,         "samplerCube",       "TextureCube",       STC_Sampler, 0, 0 },
   { GFXSCT_SamplerTextureArray, "sampler2DArray",    "Texture2DArray",    STC_Sampler, 0, 0 },
   { GFXSCT_SamplerCubeArray,    "samplerCubeArray",  "TextureCubeArray",  STC_Sampler, 0, 0 },
};

static HashMap<String, GFXShaderConstType> glslToType;
static HashMap<String, GFXShaderConstType> hlslToType;

void LangElement::buildTypeMaps()
{
   for (auto& info : ShaderTypes)
   {
      glslToType[info.glslName] = info.type;
      hlslToType[info.hlslName] = info.type;
   }
}

const ShaderTypeInfo* LangElement::getTypeInfo(GFXShaderConstType type)
{
   for (auto& info : ShaderTypes)
      if (info.type == type)
         return &info;
   return nullptr;
}

const char* LangElement::constTypeToString(GFXShaderConstType constType, bool sampler, bool matrix)
{
   const ShaderTypeInfo* info = getTypeInfo(constType);
   if (!info)
      return "unknown";

   if (sampler)
   {
      if (!info->isSampler())
      {
         Con::warnf("LangElement::Requested sampler but input const type is not a sampler");
         return "unknown";
      }
   }

   if (matrix)
   {
      if (!info->isMatrix())
      {
         Con::warnf("LangElement::Requested matrix but input const type is not a matrix");
         return "unknown";
      }
   }

   return (GFX->getAdapterType() == OpenGL)
      ? info->glslName
      : info->hlslName;
}

GFXShaderConstType LangElement::stringToConstType(const char* name)
{
   bool glsl = (GFX->getAdapterType() == OpenGL);

   auto& map = glsl ? glslToType : hlslToType;
   auto it = map.find(name);

   if (it != map.end())
      return it->value;

   return GFXSCT_Uknown;
}

bool LangElement::resolveSourceType(LangElement* elem, Var*& outVar, const ShaderTypeInfo*& outInfo)
{
   outVar = nullptr;
   outInfo = nullptr;

   // DIRECT VAR
   if (Var* v = dynamic_cast<Var*>(elem))
   {
      outVar = v;
      outInfo = getTypeInfo(stringToConstType((const char*)v->type));
      return outInfo != nullptr;
   }

   // INDEX OP: arrVar[index]
   if (IndexOp* idx = dynamic_cast<IndexOp*>(elem))
   {
      Var* arr = dynamic_cast<Var*>(idx->mInput[0]);
      if (!arr)
         return false;

      const ShaderTypeInfo* arrInfo = getTypeInfo(stringToConstType((const char*)arr->type));
      if (!arrInfo)
         return false;

      // array element type = same as var type but no array dimension
      outVar = arr;
      outInfo = arrInfo;
      return true;
   }

   // CAST OP: cast var
   if (CastOp* cast = dynamic_cast<CastOp*>(elem))
   {
      Var* castVar = dynamic_cast<Var*>(cast->mInput[0]);
      if (!castVar)
         return false;

      const ShaderTypeInfo* castInfo = getTypeInfo(cast->mTargetType);// get the casts target type.
      if (!castInfo)
         return false;

      outVar = castVar; // we should probably return null as we should just write the castop langelement, not a var.
      outInfo = castInfo;
      return true;
   }

   return false;
}


//--------------------------------------------------------------------------
// Constructor
//--------------------------------------------------------------------------
LangElement::LangElement()
{
   elementList.push_back( this );

   static U32 tempNum = 0;
   dSprintf( (char*)name, sizeof(name), "tempName%d", tempNum++ );
}

//--------------------------------------------------------------------------
// Find element of specified name
//--------------------------------------------------------------------------
LangElement * LangElement::find( const char *name )
{
   for( U32 i=0; i<elementList.size(); i++ )
   {
      if( !String::compare( (char*)elementList[i]->name, name ) )
      {
         return elementList[i];
      }
   }
   
   return NULL;
}

//--------------------------------------------------------------------------
// Delete existing elements
//--------------------------------------------------------------------------
void LangElement::deleteElements()
{
   for( U32 i=0; i<elementList.size(); i++ )
   {
      delete elementList[i];
   }
   
   elementList.setSize( 0 );

}

//--------------------------------------------------------------------------
// Set name
//--------------------------------------------------------------------------
void LangElement::setName(const char* newName )
{
   dStrncpy( ( char* ) name, newName, sizeof( name ) );
   name[ sizeof( name ) - 1 ] = '\0';
}

//**************************************************************************
// Variable
//**************************************************************************
U32 Var::texUnitCount = 0;

Var::Var()
{
   dStrcpy( (char*)type, "float4", 32 );
   structName[0] = '\0';
   connectName[0] = '\0';
   constSortPos = cspUninit;
   constNum = 0;
   texCoordNum = 0;
   uniform = false;
   vertData = false;
   connector = false;
   sampler = false;
   arraySize = 1;
   texture = false;
   rank = 0;
}

Var::Var( const char *inName, const char *inType )
{
   structName[0] = '\0';
   connectName[0] = '\0';
   uniform = false;
   vertData = false;
   connector = false;
   sampler = false;
   texCoordNum = 0;
   constSortPos = cspUninit;
   constNum = 0;
   arraySize = 1;
   texture = false;
   rank = 0;

   setName( inName );
   setType( inType );
}

Var::Var(const char* name, GFXShaderConstType type)
{
   structName[0] = '\0';
   connectName[0] = '\0';
   uniform = false;
   vertData = false;
   connector = false;
   sampler = false;
   texCoordNum = 0;
   constSortPos = cspUninit;
   constNum = 0;
   arraySize = 1;
   texture = false;
   rank = 0;

   setName(name);
   setType(type);
}

void Var::setUniform(const String& constType, const String& constName, ConstantSortPosition sortPos)
{ 
   uniform = true;
   setType(constType.c_str());
   setName(constName.c_str());   
   constSortPos = cspPass;      
}

//--------------------------------------------------------------------------
// Set struct name
//--------------------------------------------------------------------------
void Var::setStructName(const char* newName )
{
   dStrncpy( ( char* ) structName, newName, sizeof( structName ) );
   structName[ sizeof( structName ) - 1 ] = '\0';
}

//--------------------------------------------------------------------------
// Set connect name
//--------------------------------------------------------------------------
void Var::setConnectName(const char* newName )
{
   dStrncpy( ( char* ) connectName, newName, sizeof( connectName ) );
   connectName[ sizeof( connectName ) - 1 ] = '\0';
}

//--------------------------------------------------------------------------
// Set type
//--------------------------------------------------------------------------
void Var::setType(const char *newType )
{
   dStrncpy( ( char* ) type, newType, sizeof( type ) );
   type[ sizeof( type ) - 1 ] = '\0';
}

void Var::setType(GFXShaderConstType constType)
{
   const char* typeStr = "unknown"; // Default unknown type
   typeStr = constTypeToString(constType);
   // Copy the string into type[]
   dStrcpy((char*)type, typeStr, sizeof(type));
   type[sizeof(type) - 1] = '\0';
}
//--------------------------------------------------------------------------
// print
//--------------------------------------------------------------------------
void Var::print( Stream &stream )
{
   if( structName[0] != '\0' )
   {
      stream.write( dStrlen((char*)structName), structName );
      if(GFX->getAdapterType() == OpenGL)
         stream.write( 1, "_" );
      else
      stream.write( 1, "." );
   }

   stream.write( dStrlen((char*)name), name );
}

//--------------------------------------------------------------------------
// Get next available texture unit number
//--------------------------------------------------------------------------
U32 Var::getTexUnitNum(U32 numElements)
{
   U32 ret = texUnitCount;
   texUnitCount += numElements;
   return ret;
}

//--------------------------------------------------------------------------
// Reset
//--------------------------------------------------------------------------
void Var::reset()
{
   texUnitCount = 0;
}

//**************************************************************************
// Multi line statement
//**************************************************************************
void MultiLine::addStatement( LangElement *elem )
{
   AssertFatal( elem, "Attempting to add empty statement" );

   mStatementList.push_back( elem );
}

//--------------------------------------------------------------------------
// Print
//--------------------------------------------------------------------------
void MultiLine::print( Stream &stream )
{
   for( U32 i=0; i<mStatementList.size(); i++ )
   {
      mStatementList[i]->print( stream );
   }
} 
