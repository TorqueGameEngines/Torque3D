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

#include "gfx/bitmap/bitmapUtils.h"

#include "platform/platform.h"


void bitmapExtrude5551_c(const void *srcMip, void *mip, U32 srcHeight, U32 srcWidth)
{
   const U16 *src = (const U16 *) srcMip;
   U16 *dst = (U16 *) mip;
   U32 stride = srcHeight != 1 ? srcWidth : 0;

   U32 width  = srcWidth  >> 1;
   U32 height = srcHeight >> 1;
   if (width  == 0) width  = 1;
   if (height == 0) height = 1;

   if (srcWidth != 1)
   {
      for(U32 y = 0; y < height; y++)
      {
         for(U32 x = 0; x < width; x++)
         {
            U32 a = src[0];
            U32 b = src[1];
            U32 c = src[stride];
            U32 d = src[stride+1];
#if defined(TORQUE_BIG_ENDIAN)
            dst[x] = (((  (a >> 10) + (b >> 10) + (c >> 10) + (d >> 10)) >> 2) << 10) |
                     ((( ((a >> 5) & 0x1F) + ((b >> 5) & 0x1F) + ((c >> 5) & 0x1F) + ((d >> 5) & 0x1F)) >> 2) << 5) |
                     ((( ((a >> 0) & 0x1F) + ((b >> 0) & 0x1F) + ((c >> 0) & 0x1F) + ((d >> 0) & 0x1F)) >> 2) << 0);
#else
            dst[x] = (((  (a >> 11) + (b >> 11) + (c >> 11) + (d >> 11)) >> 2) << 11) |
                     ((( ((a >> 6) & 0x1F) + ((b >> 6) & 0x1F) + ((c >> 6) & 0x1F) + ((d >> 6) & 0x1F)) >> 2) << 6) |
                     ((( ((a >> 1) & 0x1F) + ((b >> 1) & 0x1F) + ((c >> 1) & 0x1F) + ((d >> 1) & 0x1F)) >> 2) << 1);
#endif
            src += 2;
         }
         src += stride;
         dst += width;
      }
   }
   else
   {
      for(U32 y = 0; y < height; y++)
      {
         U32 a = src[0];
         U32 c = src[stride];
#if defined(TORQUE_BIG_ENDIAN)
            dst[y] = ((( (a >> 10) + (c >> 10)) >> 1) << 10) |
                     ((( ((a >> 5) & 0x1F) + ((c >> 5) & 0x1f)) >> 1) << 5) |
                     ((( ((a >> 0) & 0x1F) + ((c >> 0) & 0x1f)) >> 1) << 0);
#else
            dst[y] = ((( (a >> 11) + (c >> 11)) >> 1) << 11) |
                     ((( ((a >> 6) & 0x1f) + ((c >> 6) & 0x1f)) >> 1) << 6) |
                     ((( ((a >> 1) & 0x1F) + ((c >> 1) & 0x1f)) >> 1) << 1);
#endif
         src += 1 + stride;
      }
   }
}

//--------------------------------------------------------------------------

template <typename T>
void bitmapExtrudeGeneric(
   const T* src, T* dst,
   U32 srcWidth, U32 srcHeight,
   U32 channels, U32 bpp)
{
   U32 srcRowStride = srcHeight != 1 ? (srcWidth * bpp) / sizeof(T) : 0;
   U32 dstWidth = srcWidth > 1 ? srcWidth / 2 : 1;
   U32 dstHeight = srcHeight > 1 ? srcHeight / 2 : 1;
   U32 dstRowStride = dstHeight != 1 ? (dstWidth * bpp) / sizeof(T) : 0;

   for (U32 y = 0; y < dstHeight; ++y)
   {
      for (U32 x = 0; x < dstWidth; ++x)
      {
         for (U32 c = 0; c < channels; ++c)
         {
            U32 x0 = x * 2;
            U32 y0 = y * 2;
            U32 x1 = (x0 + 1 < srcWidth) ? x0 + 1 : x0;
            U32 y1 = (y0 + 1 < srcHeight) ? y0 + 1 : y0;

            if constexpr (std::is_floating_point_v<T>)
            {
               T sum = 0;
               sum += src[y0 * srcRowStride + x0 * channels + c];
               sum += src[y0 * srcRowStride + x1 * channels + c];
               sum += src[y1 * srcRowStride + x0 * channels + c];
               sum += src[y1 * srcRowStride + x1 * channels + c];

               dst[y * dstRowStride + x * channels + c] = sum * 0.25f;
            }
            else
            {
               U32 sum = 0;
               sum += src[y0 * srcRowStride + x0 * channels + c];
               sum += src[y0 * srcRowStride + x1 * channels + c];
               sum += src[y1 * srcRowStride + x0 * channels + c];
               sum += src[y1 * srcRowStride + x1 * channels + c];
               dst[y * dstRowStride + x * channels + c] = T((sum + 2) >> 2);
            }
         }
      }
   }
}

// 8-bit RGBA
auto bitmapExtrudeU8_RGBA = [](const void* src, void* dst, U32 h, U32 w, U32 bpp) {
   bitmapExtrudeGeneric((const U8*)src, (U8*)dst, w, h, 4, bpp);
};

// 16-bit RGBA (U16 / F32 stored as U16)
auto bitmapExtrudeU16_RGBA = [](const void* src, void* dst, U32 h, U32 w, U32 bpp) {
   bitmapExtrudeGeneric((const U16*)src, (U16*)dst, w, h, 4, bpp);
};

// 32-bit float RGBA
auto bitmapExtrudeF32_RGBA = [](const void* src, void* dst, U32 h, U32 w, U32 bpp) {
   bitmapExtrudeGeneric((const F32*)src, (F32*)dst, w, h, 4, bpp);
};

// RGB U8
auto bitmapExtrudeU8_RGB = [](const void* src, void* dst, U32 h, U32 w, U32 bpp) {
   bitmapExtrudeGeneric((const U8*)src, (U8*)dst, w, h, 3, bpp);
};

void (*bitmapExtrude5551)(const void* srcMip, void* mip, U32 height, U32 width) = bitmapExtrude5551_c;
void (*bitmapExtrudeRGB)(const void* srcMip, void* mip, U32 srcHeight, U32 srcWidth, U32 bpp) = bitmapExtrudeU8_RGB;
void (*bitmapExtrudeRGBA)(const void* srcMip, void* mip, U32 srcHeight, U32 srcWidth, U32 bpp) = bitmapExtrudeU8_RGBA;
void (*bitmapExtrude16BitRGBA)(const void* srcMip, void* mip, U32 srcHeight, U32 srcWidth, U32 bpp) = bitmapExtrudeU16_RGBA;
void (*bitmapExtrudeFPRGBA)(const void* srcMip, void* mip, U32 srcHeight, U32 srcWidth, U32 bpp) = bitmapExtrudeU16_RGBA;
void (*bitmapExtrudeF32RGBA)(const void* srcMip, void* mip, U32 srcHeight, U32 srcWidth, U32 bpp) = bitmapExtrudeF32_RGBA;

//--------------------------------------------------------------------------

void bitmapConvertRGB_to_1555_c(U8 *src, U32 pixels)
{
   U16 *dst = (U16 *)src;
   for(U32 j = 0; j < pixels; j++)
   {
      U32 r = src[0] >> 3;
      U32 g = src[1] >> 3;
      U32 b = src[2] >> 3;

#if defined(TORQUE_BIG_ENDIAN)
      *dst++ = 0x8000 | (b << 10) | (g << 5) | (r << 0);
#else
      *dst++ = b | (g << 5) | (r << 10) | 0x8000;
#endif
      src += 3;
   }
}

void (*bitmapConvertRGB_to_1555)(U8 *src, U32 pixels) = bitmapConvertRGB_to_1555_c;

//------------------------------------------------------------------------------

void bitmapConvertRGB_to_5551_c(U8 *src, U32 pixels)
{
   U16 *dst = (U16 *)src;
   for(U32 j = 0; j < pixels; j++)
   {
      U32 r = src[0] >> 3;
      U32 g = src[1] >> 3;
      U32 b = src[2] >> 3;

#if defined(TORQUE_BIG_ENDIAN)
      *dst++ = (1 << 15) | (b << 10) | (g << 5) | (r << 0);
#else
      *dst++ = (b << 1) | (g << 6) | (r << 11) | 1;
#endif
      src += 3;
   }
}



void (*bitmapConvertRGB_to_5551)(U8 *src, U32 pixels) = bitmapConvertRGB_to_5551_c;

//------------------------------------------------------------------------------

void bitmapConvertRGB_to_RGBX_c( U8 **src, U32 pixels )
{
   const U8 *oldBits = *src;
   U8 *newBits = new U8[pixels * 4];
   dMemset( newBits, 0xFF, pixels * 4 ); // This is done to set alpha values -patw

   // Copy the bits over to the new memory
   for( U32 i = 0; i < pixels; i++ )
      dMemcpy( &newBits[i * 4], &oldBits[i * 3], sizeof(U8) * 3 );

   // Now hose the old bits
   delete [] *src;
   *src = newBits;
}

void (*bitmapConvertRGB_to_RGBX)( U8 **src, U32 pixels ) = bitmapConvertRGB_to_RGBX_c;

//------------------------------------------------------------------------------

void bitmapConvertRGBX_to_RGB_c( U8 **src, U32 pixels )
{
   const U8 *oldBits = *src;
   U8 *newBits = new U8[pixels * 3];

   // Copy the bits over to the new memory
   for( U32 i = 0; i < pixels; i++ )
      dMemcpy( &newBits[i * 3], &oldBits[i * 4], sizeof(U8) * 3 );

   // Now hose the old bits
   delete [] *src;
   *src = newBits;
}

void (*bitmapConvertRGBX_to_RGB)( U8 **src, U32 pixels ) = bitmapConvertRGBX_to_RGB_c;

//------------------------------------------------------------------------------

void bitmapConvertA8_to_RGBA_c( U8 **src, U32 pixels )
{
   const U8 *oldBits = *src;
   U8 *newBits = new U8[pixels * 4];

   // Zero new bits
   dMemset( newBits, 0, pixels * 4 );

   // Copy Alpha values
   for( U32 i = 0; i < pixels; i++ )      
      newBits[i * 4 + 3] = oldBits[i];

   // Now hose the old bits
   delete [] *src;
   *src = newBits;
}

void (*bitmapConvertA8_to_RGBA)( U8 **src, U32 pixels ) = bitmapConvertA8_to_RGBA_c;
