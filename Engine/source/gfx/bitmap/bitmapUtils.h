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

#ifndef _BITMAPUTILS_H_
#define _BITMAPUTILS_H_
#ifndef _PLATFORM_H_
#include "platform/platform.h"
#endif
#ifndef _TORQUE_TYPES_H_
#include "platform/types.h"
#endif
#ifndef _GFXENUMS_H_
#include "gfx/gfxEnums.h"
#endif
#ifndef _MMATHFN_H_
#include "math/mMathFn.h"
#endif

extern void (*bitmapExtrude5551)(const void *srcMip, void *mip, U32 height, U32 width);
extern void (*bitmapExtrudeRGB)(const void *srcMip, void *mip, U32 height, U32 width, U32 bpp);
extern void (*bitmapExtrudeRGBA)(const void *srcMip, void *mip, U32 height, U32 width, U32 bpp);
extern void (*bitmapExtrude16BitRGBA)(const void *srcMip, void *mip, U32 height, U32 width, U32 bpp);
extern void(*bitmapExtrudeFPRGBA)(const void *srcMip, void *mip, U32 height, U32 width, U32 bpp);
extern void(*bitmapExtrudeF32RGBA)(const void *srcMip, void *mip, U32 height, U32 width, U32 bpp);

extern void(*bitmapResizeToOutput)(const void* src, U32 srcHeight, U32 srcWidth, void* out, U32 outHeight, U32 outWidth, U32 bpp, GFXFormat format);
extern bool(*bitmapConvertToOutput)(U8** src, U32 pixels, GFXFormat srcFormat, GFXFormat dstFormat);

extern void (*bitmapConvertRGB_to_5551)(U8 *src, U32 pixels);
extern void (*bitmapConvertRGB_to_1555)(U8 *src, U32 pixels);
extern void (*bitmapConvertRGB_to_RGBX)( U8 **src, U32 pixels );
extern void (*bitmapConvertRGBX_to_RGB)( U8 **src, U32 pixels );
extern void (*bitmapConvertA8_to_RGBA)( U8 **src, U32 pixels );

//-----------------------------------------------------------------------------
// Half <-> Float Conversion Utilities
//-----------------------------------------------------------------------------

inline F32 convertHalfToFloat(U16 h)
{
   U32 sign = (h >> 15) & 0x00000001;
   U32 exp = (h >> 10) & 0x0000001F;
   U32 mant = h & 0x000003FF;

   U32 out;

   if (exp == 0)
   {
      if (mant == 0)
      {
         // Zero
         out = sign;
      }
      else
      {
         // Subnormal number -> normalize
         exp = 127 - 14;
         while ((mant & 0x0400) == 0)
         {
            mant <<= 1;
            exp--;
         }
         mant &= 0x03FF;
         out = sign | (exp << 23) | (mant << 13);
      }
   }
   else if (exp == 31)
   {
      // Inf or NaN
      out = sign | 0x7F800000 | (mant << 13);
   }
   else
   {
      // Normalized
      out = sign | ((exp + (127 - 15)) << 23) | (mant << 13);
   }

   F32 result;
   dMemcpy(&result, &out, sizeof(F32));
   return result;
}

inline U16 convertFloatToHalf(F32 f)
{
   U32 bits;
   dMemcpy(&bits, &f, sizeof(U32));

   U32 sign = (bits >> 16) & 0x8000;
   U32 exp = (bits >> 23) & 0xFF;
   U32 mant = bits & 0x007FFFFF;

   if (exp == 255)
   {
      // Inf or NaN
      if (mant == 0)
         return (U16)(sign | 0x7C00);
      mant >>= 13;
      return (U16)(sign | 0x7C00 | mant | (mant == 0));
   }

   S32 newExp = (S32)exp - 127 + 15;

   if (newExp >= 31)
   {
      // Overflow → Inf
      return (U16)(sign | 0x7C00);
   }
   else if (newExp <= 0)
   {
      // Subnormal or underflow
      if (newExp < -10)
         return (U16)sign;

      mant |= 0x800000;
      U32 shifted = mant >> (1 - newExp);

      // Round to nearest-even
      if (shifted & 0x00001000)
         shifted += 0x00002000;

      return (U16)(sign | (shifted >> 13));
   }

   // Normalized with rounding
   mant += 0x00001000;
   if (mant & 0x00800000)
   {
      mant = 0;
      newExp++;
   }

   if (newExp >= 31)
      return (U16)(sign | 0x7C00);

   return (U16)(sign | (newExp << 10) | (mant >> 13));
}

// Convert a single 16-bit value (0..65535) to 8-bit (0..255)
inline U8 convert16To8(U16 v16)
{
   // Take the top 8 bits as approximation
   return U8(v16 >> 8);
}

// Convert a single 8-bit value (0..255) to 16-bit (0..65535)
inline U16 convert8To16(U8 v8)
{
   // Replicate into high and low byte: 0->0, 255->0xFFFF
   return (U16(v8) << 8) | v8;
}

inline U8 floatTo8(F32 v)
{
   return U8(mClamp(v * 255.f, 0.f, 255.f));
}


#endif //_BITMAPUTILS_H_
