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

#include "gfx/gfxStringEnumTranslate.h"
#include "gfx/gfxAPI.h"
#include "console/console.h"

//------------------------------------------------------------------------------

const char *GFXStringTextureFormat[GFXFormat_COUNT];
const char *GFXStringTiledTextureFormat[GFXFormat_COUNT];
const char *GFXStringRenderTargetFormat[GFXFormat_COUNT];
const char *GFXStringTextureFilter[GFXTextureFilter_COUNT];
const char *GFXStringBlend[GFXBlend_COUNT];
const char *GFXStringBlendOp[GFXBlendOp_COUNT];
const char *GFXStringStencilOp[GFXStencilOp_COUNT];
const char *GFXStringCmpFunc[GFXCmp_COUNT];
const char *GFXStringCullMode[GFXCull_COUNT];
const char *GFXStringPrimType[GFXPT_COUNT];
const char *GFXStringTextureAddress[GFXAddress_COUNT];
const char *GFXStringFillMode[GFXFill_COUNT];

//------------------------------------------------------------------------------

const char *defaultStringValueLookup( const U32 &value )
{
   static char retbuffer[256];

   dSprintf( retbuffer, sizeof( retbuffer ), "%d", value );

   return retbuffer;
}

#define _STRING_VALUE_LOOKUP_FXN( table ) \
   const char * table##_lookup( const U32 &value ) { return table[value]; }

_STRING_VALUE_LOOKUP_FXN(GFXStringTextureAddress);
_STRING_VALUE_LOOKUP_FXN(GFXStringTextureFilter);
_STRING_VALUE_LOOKUP_FXN(GFXStringBlend);
_STRING_VALUE_LOOKUP_FXN(GFXStringCmpFunc);
_STRING_VALUE_LOOKUP_FXN(GFXStringStencilOp);
_STRING_VALUE_LOOKUP_FXN(GFXStringCullMode);
_STRING_VALUE_LOOKUP_FXN(GFXStringBlendOp);

//------------------------------------------------------------------------------

#define INIT_LOOKUPTABLE( tablearray, enumprefix, type ) \
   for( S32 i = enumprefix##_FIRST; i < enumprefix##_COUNT; i++ ) \
      tablearray[i] = (type)(uintptr_t)GFX_UNINIT_VAL;
#define INIT_LOOKUPTABLE_EX( tablearray, enumprefix, type, typeTable ) \
   for( S32 i = enumprefix##_FIRST; i < enumprefix##_COUNT; i++ ) \
   {\
      tablearray[i] = (type)(uintptr_t)GFX_UNINIT_VAL;\
      typeTable[i] = &defaultStringValueLookup;\
   }

#define VALIDATE_LOOKUPTABLE( tablearray, enumprefix ) \
   for( S32 i = enumprefix##_FIRST; i < enumprefix##_COUNT; i++ ) \
      if( (intptr_t)tablearray[i] == GFX_UNINIT_VAL ) \
         Con::warnf( "GFXStringEnumTranslate: Unassigned value in " #tablearray ": %i", i ); \
      else if( (intptr_t)tablearray[i] == GFX_UNSUPPORTED_VAL ) \
         Con::warnf( "GFXStringEnumTranslate: Unsupported value in " #tablearray ": %i", i );

//------------------------------------------------------------------------------

#define GFX_STRING_ASSIGN_MACRO( table, indexEnum ) table[indexEnum] = #indexEnum;
#define GFX_STRING_ASSIGN_MACRO_EX( table, indexEnum, typeTable ) table[indexEnum] = #indexEnum; table##ValueLookup[indexEnum] = &typeTable##_lookup;

void GFXStringEnumTranslate::init()
{
   static bool sInitCalled = false;

   if( sInitCalled )
      return;

   sInitCalled = true;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
   INIT_LOOKUPTABLE( GFXStringTextureFormat, GFXFormat, const char * );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatR8G8B8 );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatR8G8B8A8 );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatR8G8B8A8_SRGB);
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatR8G8B8X8 );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatB8G8R8A8 );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatR32F );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatR5G6B5 );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatR5G5B5A1 );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatR5G5B5X1 );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatA4L4 );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatA8L8 );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatA8 );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatL8 );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatBC1 );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatBC2 );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatBC3 );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatBC4 );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatBC5 );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatD32 );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatD24X8 );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatD24S8 );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatD24FS8 );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatD16 );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatD32FS8X24 );

   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatR32G32B32A32F );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatR16G16B16A16F );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatL16 );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatR16G16B16A16 );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatR16G16 );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatR16F );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatR16G16F );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatR10G10B10A2 );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatR11G11B10);

   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatR8G8B8_SRGB );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatR8G8B8A8_LINEAR_FORCE );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatBC1_SRGB );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatBC2_SRGB );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureFormat, GFXFormatBC3_SRGB );
   VALIDATE_LOOKUPTABLE( GFXStringTextureFormat, GFXFormat);

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
   INIT_LOOKUPTABLE( GFXStringBlend, GFXBlend, const char * );
   GFX_STRING_ASSIGN_MACRO( GFXStringBlend, GFXBlendZero );
   GFX_STRING_ASSIGN_MACRO( GFXStringBlend, GFXBlendOne );
   GFX_STRING_ASSIGN_MACRO( GFXStringBlend, GFXBlendSrcColor );
   GFX_STRING_ASSIGN_MACRO( GFXStringBlend, GFXBlendInvSrcColor );
   GFX_STRING_ASSIGN_MACRO( GFXStringBlend, GFXBlendSrcAlpha );
   GFX_STRING_ASSIGN_MACRO( GFXStringBlend, GFXBlendInvSrcAlpha );
   GFX_STRING_ASSIGN_MACRO( GFXStringBlend, GFXBlendDestAlpha );
   GFX_STRING_ASSIGN_MACRO( GFXStringBlend, GFXBlendInvDestAlpha );
   GFX_STRING_ASSIGN_MACRO( GFXStringBlend, GFXBlendDestColor );
   GFX_STRING_ASSIGN_MACRO( GFXStringBlend, GFXBlendInvDestColor );
   GFX_STRING_ASSIGN_MACRO( GFXStringBlend, GFXBlendSrcAlphaSat );
   VALIDATE_LOOKUPTABLE( GFXStringBlend, GFXBlend );
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
   INIT_LOOKUPTABLE( GFXStringBlendOp, GFXBlendOp, const char * );
   GFX_STRING_ASSIGN_MACRO( GFXStringBlendOp, GFXBlendOpAdd );
   GFX_STRING_ASSIGN_MACRO( GFXStringBlendOp, GFXBlendOpSubtract );
   GFX_STRING_ASSIGN_MACRO( GFXStringBlendOp, GFXBlendOpRevSubtract );
   GFX_STRING_ASSIGN_MACRO( GFXStringBlendOp, GFXBlendOpMin );
   GFX_STRING_ASSIGN_MACRO( GFXStringBlendOp, GFXBlendOpMax );
   VALIDATE_LOOKUPTABLE( GFXStringBlendOp, GFXBlendOp );
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
   INIT_LOOKUPTABLE( GFXStringStencilOp, GFXStencilOp, const char * );
   GFX_STRING_ASSIGN_MACRO( GFXStringStencilOp, GFXStencilOpKeep );
   GFX_STRING_ASSIGN_MACRO( GFXStringStencilOp, GFXStencilOpZero );
   GFX_STRING_ASSIGN_MACRO( GFXStringStencilOp, GFXStencilOpReplace );
   GFX_STRING_ASSIGN_MACRO( GFXStringStencilOp, GFXStencilOpIncrSat );
   GFX_STRING_ASSIGN_MACRO( GFXStringStencilOp, GFXStencilOpDecrSat );
   GFX_STRING_ASSIGN_MACRO( GFXStringStencilOp, GFXStencilOpInvert );
   GFX_STRING_ASSIGN_MACRO( GFXStringStencilOp, GFXStencilOpIncr );
   GFX_STRING_ASSIGN_MACRO( GFXStringStencilOp, GFXStencilOpDecr );
   VALIDATE_LOOKUPTABLE( GFXStringStencilOp, GFXStencilOp );
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
   INIT_LOOKUPTABLE( GFXStringCmpFunc, GFXCmp, const char * );
   GFX_STRING_ASSIGN_MACRO( GFXStringCmpFunc, GFXCmpNever );
   GFX_STRING_ASSIGN_MACRO( GFXStringCmpFunc, GFXCmpLess );
   GFX_STRING_ASSIGN_MACRO( GFXStringCmpFunc, GFXCmpEqual );
   GFX_STRING_ASSIGN_MACRO( GFXStringCmpFunc, GFXCmpLessEqual );
   GFX_STRING_ASSIGN_MACRO( GFXStringCmpFunc, GFXCmpGreater );
   GFX_STRING_ASSIGN_MACRO( GFXStringCmpFunc, GFXCmpNotEqual );
   GFX_STRING_ASSIGN_MACRO( GFXStringCmpFunc, GFXCmpGreaterEqual );
   GFX_STRING_ASSIGN_MACRO( GFXStringCmpFunc, GFXCmpAlways );
   VALIDATE_LOOKUPTABLE( GFXStringCmpFunc, GFXCmp );
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
   INIT_LOOKUPTABLE( GFXStringCullMode, GFXCull, const char * );
   GFX_STRING_ASSIGN_MACRO( GFXStringCullMode, GFXCullNone );
   GFX_STRING_ASSIGN_MACRO( GFXStringCullMode, GFXCullCW );
   GFX_STRING_ASSIGN_MACRO( GFXStringCullMode, GFXCullCCW );
   VALIDATE_LOOKUPTABLE( GFXStringCullMode, GFXCull );
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
   INIT_LOOKUPTABLE( GFXStringPrimType, GFXPT, const char * );
   GFX_STRING_ASSIGN_MACRO( GFXStringPrimType, GFXPointList );
   GFX_STRING_ASSIGN_MACRO( GFXStringPrimType, GFXLineList );
   GFX_STRING_ASSIGN_MACRO( GFXStringPrimType, GFXLineStrip );
   GFX_STRING_ASSIGN_MACRO( GFXStringPrimType, GFXTriangleList );
   GFX_STRING_ASSIGN_MACRO( GFXStringPrimType, GFXTriangleStrip );
   VALIDATE_LOOKUPTABLE( GFXStringPrimType, GFXPT );
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
   INIT_LOOKUPTABLE( GFXStringTextureAddress, GFXAddress, const char * );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureAddress, GFXAddressWrap );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureAddress, GFXAddressMirror );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureAddress, GFXAddressClamp );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureAddress, GFXAddressBorder );
   GFX_STRING_ASSIGN_MACRO( GFXStringTextureAddress, GFXAddressMirrorOnce );
   VALIDATE_LOOKUPTABLE(GFXStringTextureAddress, GFXAddress );
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
   INIT_LOOKUPTABLE( GFXStringFillMode, GFXFill, const char * );
   GFX_STRING_ASSIGN_MACRO( GFXStringFillMode, GFXFillPoint );
   GFX_STRING_ASSIGN_MACRO( GFXStringFillMode, GFXFillWireframe );
   GFX_STRING_ASSIGN_MACRO( GFXStringFillMode, GFXFillSolid );
   VALIDATE_LOOKUPTABLE( GFXStringFillMode, GFXFill );
}
