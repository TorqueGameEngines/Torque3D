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

extern void (*bitmapExtrude5551)(const void *srcMip, void *mip, U32 height, U32 width);
extern void (*bitmapExtrudeRGB)(const void *srcMip, void *mip, U32 height, U32 width, U32 bpp);
extern void (*bitmapExtrudeRGBA)(const void *srcMip, void *mip, U32 height, U32 width, U32 bpp);
extern void (*bitmapExtrude16BitRGBA)(const void *srcMip, void *mip, U32 height, U32 width, U32 bpp);
extern void(*bitmapExtrudeFPRGBA)(const void *srcMip, void *mip, U32 height, U32 width, U32 bpp);
extern void(*bitmapExtrudeF32RGBA)(const void *srcMip, void *mip, U32 height, U32 width, U32 bpp);
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

   U32 outSign = sign << 31;
   U32 outExp, outMant;

   if (exp == 0)
   {
      if (mant == 0)
      {
         // Zero
         outExp = 0;
         outMant = 0;
      }
      else
      {
         // Subnormal number -> normalize
         exp = 1;
         while ((mant & 0x00000400) == 0)
         {
            mant <<= 1;
            exp -= 1;
         }
         mant &= 0x000003FF;
         outExp = (exp + (127 - 15)) << 23;
         outMant = mant << 13;
      }
   }
   else if (exp == 31)
   {
      // Inf or NaN
      outExp = 0xFF << 23;
      outMant = mant ? (mant << 13) : 0;
   }
   else
   {
      // Normalized
      outExp = (exp + (127 - 15)) << 23;
      outMant = mant << 13;
   }

   U32 out = outSign | outExp | outMant;
   F32 result;
   dMemcpy(&result, &out, sizeof(F32));
   return result;
}

inline U16 convertFloatToHalf(F32 f)
{
   U32 bits;
   dMemcpy(&bits, &f, sizeof(U32));

   U32 sign = (bits >> 16) & 0x00008000;
   U32 exp = ((bits >> 23) & 0x000000FF) - (127 - 15);
   U32 mant = bits & 0x007FFFFF;

   if (exp <= 0)
   {
      if (exp < -10)
         return (U16)sign; // Too small => 0
      mant = (mant | 0x00800000) >> (1 - exp);
      return (U16)(sign | (mant >> 13));
   }
   else if (exp == 0xFF - (127 - 15))
   {
      if (mant == 0)
      {
         // Inf
         return (U16)(sign | 0x7C00);
      }
      else
      {
         // NaN
         mant >>= 13;
         return (U16)(sign | 0x7C00 | mant | (mant == 0));
      }
   }
   else
   {
      if (exp > 30)
      {
         // Overflow => Inf
         return (U16)(sign | 0x7C00);
      }
      return (U16)(sign | (exp << 10) | (mant >> 13));
   }
}

#endif //_BITMAPUTILS_H_
