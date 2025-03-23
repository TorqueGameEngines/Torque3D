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
#include "langElement.h"

//**************************************************************************
// Language element
//**************************************************************************
Vector<LangElement*> LangElement::elementList( __FILE__, __LINE__ );

const char* LangElement::constTypeToString(GFXShaderConstType constType)
{
   // Determine shader language based on GFXAdapterAPI
   if (GFX->getAdapterType() == OpenGL)
   {
      switch (constType)
      {
      case GFXSCT_Float:       return "float"; break;
      case GFXSCT_Float2:      return "vec2"; break;
      case GFXSCT_Float3:      return "vec3"; break;
      case GFXSCT_Float4:      return "vec4"; break;
      case GFXSCT_Float2x2:    return "mat2"; break;
      case GFXSCT_Float3x3:    return "mat3"; break;
      case GFXSCT_Float3x4:    return "mat3x4"; break;
      case GFXSCT_Float4x3:    return "mat4x3"; break;
      case GFXSCT_Float4x4:    return "mat4"; break;
      case GFXSCT_Int:         return "int"; break;
      case GFXSCT_Int2:        return "ivec2"; break;
      case GFXSCT_Int3:        return "ivec3"; break;
      case GFXSCT_Int4:        return "ivec4"; break;
      case GFXSCT_UInt:        return "uint"; break;
      case GFXSCT_UInt2:       return "uvec2"; break;
      case GFXSCT_UInt3:       return "uvec3"; break;
      case GFXSCT_UInt4:       return "uvec4"; break;
      case GFXSCT_Bool:        return "bool"; break;
      case GFXSCT_Bool2:       return "bvec2"; break;
      case GFXSCT_Bool3:       return "bvec3"; break;
      case GFXSCT_Bool4:       return "bvec4"; break;
      default:                 return "unknown"; break;
      }
   }
   else // Assume DirectX/HLSL
   {
      switch (constType)
      {
      case GFXSCT_Float:       return "float"; break;
      case GFXSCT_Float2:      return "float2"; break;
      case GFXSCT_Float3:      return "float3"; break;
      case GFXSCT_Float4:      return "float4"; break;
      case GFXSCT_Float2x2:    return "float2x2"; break;
      case GFXSCT_Float3x3:    return "float3x3"; break;
      case GFXSCT_Float3x4:    return "float3x4"; break;
      case GFXSCT_Float4x3:    return "float4x3"; break;
      case GFXSCT_Float4x4:    return "float4x4"; break;
      case GFXSCT_Int:         return "int"; break;
      case GFXSCT_Int2:        return "int2"; break;
      case GFXSCT_Int3:        return "int3"; break;
      case GFXSCT_Int4:        return "int4"; break;
      case GFXSCT_UInt:        return "uint"; break;
      case GFXSCT_UInt2:       return "uint2"; break;
      case GFXSCT_UInt3:       return "uint3"; break;
      case GFXSCT_UInt4:       return "uint4"; break;
      case GFXSCT_Bool:        return "bool"; break;
      case GFXSCT_Bool2:       return "bool2"; break;
      case GFXSCT_Bool3:       return "bool3"; break;
      case GFXSCT_Bool4:       return "bool4"; break;
      default:                 return "unknown"; break;
      }
   }

   return "";
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
