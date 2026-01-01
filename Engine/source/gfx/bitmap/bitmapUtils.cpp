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

#ifndef STB_IMAGE_RESIZE2_IMPLEMENTATION
#define STB_IMAGE_RESIZE2_IMPLEMENTATION
#define STBIR_PROFILE
#include "gfx/bitmap/loaders/stb/stb_image_resize2.h"
#endif // !STB_IMAGE_RESIZE2_IMPLEMENTATION

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

struct StbResizeDesc
{
   stbir_datatype datatype;
   stbir_pixel_layout layout;
   U32 bytesPerPixel;
};

inline bool getStbResizeDesc(GFXFormat fmt, StbResizeDesc& out)
{
   switch (fmt)
   {
      // ---- 1 channel ----
   case GFXFormatA8:
   case GFXFormatL8:
      out = { STBIR_TYPE_UINT8, STBIR_1CHANNEL, 1 };
      return true;

   case GFXFormatL16:
      out = { STBIR_TYPE_UINT16, STBIR_1CHANNEL, 2 };
      return true;

   case GFXFormatR16F:
      out = { STBIR_TYPE_HALF_FLOAT, STBIR_1CHANNEL, 2 };
      return true;

   case GFXFormatR32F:
      out = { STBIR_TYPE_FLOAT, STBIR_1CHANNEL, 4 };
      return true;

      // ---- 2 channel ----
   case GFXFormatA8L8:
      out = { STBIR_TYPE_UINT8, STBIR_2CHANNEL, 2 };
      return true;

   case GFXFormatR16G16:
      out = { STBIR_TYPE_UINT16, STBIR_2CHANNEL, 4 };
      return true;

   case GFXFormatR16G16F:
      out = { STBIR_TYPE_HALF_FLOAT, STBIR_2CHANNEL, 4 };
      return true;

      // ---- RGB ----
   case GFXFormatR8G8B8:
      out = { STBIR_TYPE_UINT8, STBIR_RGB, 3 };
      return true;

   case GFXFormatR8G8B8_SRGB:
      out = { STBIR_TYPE_UINT8_SRGB, STBIR_RGB, 3 };
      return true;

      // ---- RGBA / RGBX ----
   case GFXFormatR8G8B8A8:
   case GFXFormatR8G8B8X8:
      out = { STBIR_TYPE_UINT8, STBIR_RGBA, 4 };
      return true;

   case GFXFormatR8G8B8A8_SRGB:
      out = { STBIR_TYPE_UINT8_SRGB_ALPHA, STBIR_RGBA, 4 };
      return true;

   case GFXFormatB8G8R8A8:
      out = { STBIR_TYPE_UINT8, STBIR_BGRA, 4 };
      return true;

      // ---- 16-bit RGBA ----
   case GFXFormatR16G16B16A16:
      out = { STBIR_TYPE_UINT16, STBIR_RGBA, 8 };
      return true;

   case GFXFormatR16G16B16A16F:
      out = { STBIR_TYPE_HALF_FLOAT, STBIR_RGBA, 8 };
      return true;

      // ---- 32-bit RGBA ----
   case GFXFormatR32G32B32A32F:
      out = { STBIR_TYPE_FLOAT, STBIR_RGBA, 16 };
      return true;

   default:
      return false;
   }
}

void bitmapStbResizeToOutput(const void* src, U32 srcHeight, U32 srcWidth, void* out, U32 outHeight, U32 outWidth, U32 bpp, GFXFormat format)
{
   StbResizeDesc desc;
   if (!getStbResizeDesc(format, desc))
   {
      return;
   }

   const int srcStride = srcWidth * bpp;
   const int dstStride = outWidth * bpp;

   stbir_resize(
      src,
      srcWidth,
      srcHeight,
      srcStride,
      out,
      outWidth,
      outHeight,
      dstStride,
      desc.layout,
      desc.datatype,
      STBIR_EDGE_CLAMP,
      STBIR_FILTER_MITCHELL);
}

void(*bitmapResizeToOutput)(const void* src, U32 srcHeight, U32 srcWidth, void* out, U32 outHeight, U32 outWidth, U32 bpp, GFXFormat format) = bitmapStbResizeToOutput;

//--------------------------------------------------------------------------------
// Format description

//--------------------------------------------------------------------------------
// Channel semantics
enum ChannelSemantic : U8
{
   CH_NONE,
   CH_L,
   CH_A,
   CH_R,
   CH_G,
   CH_B
};

struct PackedChannelDesc
{
   ChannelSemantic semantic;
   U8 bits;
   U8 shift;
};

//--------------------------------------------------------------------------------
// Bitmap format descriptor
struct GBitmapFormatDesc
{
   U8 channels;
   ChannelSemantic semantic[4]; // per-channel meaning
   stbir_datatype datatype;
   bool srgb;
   bool premultiplied;
   bool isFloat;
   U8 bytesPerChannel;
   bool isPacked = false;
   U8 bytesPerPixel = 0;
   PackedChannelDesc packed[4] = {};
   bool is8()  const { return !isFloat && bytesPerChannel == 1; }
   bool is16() const { return !isFloat && bytesPerChannel == 2; }
};

//--------------------------------------------------------------------------------
// Table mapping GFXFormat -> descriptor
GBitmapFormatDesc getFormatDesc(GFXFormat fmt)
{
   switch (fmt)
   {
      // 8-bit formats
   case GFXFormatA8:
      return { 1, {CH_A, CH_NONE, CH_NONE, CH_NONE}, STBIR_TYPE_UINT8, false, false, false, 1 };
   case GFXFormatL8:
      return { 1, {CH_L, CH_NONE, CH_NONE, CH_NONE}, STBIR_TYPE_UINT8, false, false, false, 1 };
   case GFXFormatA4L4:
      return { 2, {CH_L, CH_A, CH_NONE, CH_NONE}, STBIR_TYPE_UINT8, false, false, false, 0, true, 1,
         {
            { CH_L, 4, 0 }, // CH_L must be declared before CH_A
            { CH_A, 4, 4 }
         }
      };

      // 16-bit formats
   case GFXFormatR5G6B5:
      return { 3, {CH_R, CH_G, CH_B, CH_NONE}, STBIR_TYPE_UINT8, false, false, false, 0, true, 2,
         {
            { CH_R, 5, 11 },
            { CH_G, 6, 5  },
            { CH_B, 5, 0  }
         }
      };
   case GFXFormatR5G5B5A1:
      return { 4, {CH_R, CH_G, CH_B, CH_A}, STBIR_TYPE_UINT8, false, false, false, 0, true, 2,
         {
            { CH_R, 5, 11 },
            { CH_G, 5, 6  },
            { CH_B, 5, 1  },
            { CH_A, 1, 0  }
         }
      };
   case GFXFormatR5G5B5X1:
      return { 4, {CH_R, CH_G, CH_B, CH_NONE}, STBIR_TYPE_UINT8, false, false, false, 0, true, 2,
         {
            { CH_R, 5, 11 },
            { CH_G, 5, 6  },
            { CH_B, 5, 1  },
            { CH_A, 1, 0  }
         }
      };
   case GFXFormatA8L8:
      return { 2, {CH_L, CH_A, CH_NONE, CH_NONE}, STBIR_TYPE_UINT8, false, false, false, 0, true, 2,
         {
            { CH_L, 8, 0 }, // CH_L must be declared before CH_A
            { CH_A, 8, 8 }
         }
      };
   case GFXFormatL16:
      return { 1, {CH_L, CH_NONE, CH_NONE, CH_NONE}, STBIR_TYPE_UINT16, false, false, false, 2 };
   case GFXFormatR16F:
      return { 1, {CH_R, CH_NONE, CH_NONE, CH_NONE}, STBIR_TYPE_HALF_FLOAT, false, false, true, 2 };
   case GFXFormatD16:
      return { 1, {CH_L, CH_NONE, CH_NONE, CH_NONE}, STBIR_TYPE_UINT16, false, false, false, 2 };

      // 24-bit formats
   case GFXFormatR8G8B8:
      return { 3, {CH_R, CH_G, CH_B, CH_NONE}, STBIR_TYPE_UINT8, false, false, false, 1 };
   case GFXFormatR8G8B8_SRGB:
      return { 3, {CH_R, CH_G, CH_B, CH_NONE}, STBIR_TYPE_UINT8_SRGB, true, false, false, 1 };

      // 32-bit formats
   case GFXFormatR8G8B8A8:
   case GFXFormatR8G8B8X8:
      return { 4, {CH_R, CH_G, CH_B, CH_A}, STBIR_TYPE_UINT8, false, false, false, 1 };
   case GFXFormatB8G8R8A8:
      return { 4, {CH_B, CH_G, CH_R, CH_A}, STBIR_TYPE_UINT8, false, false, false, 1 };
   case GFXFormatR8G8B8A8_SRGB:
      return { 4, {CH_R, CH_G, CH_B, CH_A}, STBIR_TYPE_UINT8_SRGB_ALPHA, true, false, false, 1 };
   case GFXFormatR16G16:
      return { 2, {CH_R, CH_G, CH_NONE, CH_NONE}, STBIR_TYPE_UINT16, false, false, false, 2 };
   case GFXFormatR16G16F:
      return { 2, {CH_R, CH_G, CH_NONE, CH_NONE}, STBIR_TYPE_HALF_FLOAT, false, false, true, 2 };

      // 64-bit formats
   case GFXFormatR16G16B16A16:
      return { 4, {CH_R, CH_G, CH_B, CH_A}, STBIR_TYPE_UINT16, false, false, false, 2 };
   case GFXFormatR16G16B16A16F:
      return { 4, {CH_R, CH_G, CH_B, CH_A}, STBIR_TYPE_HALF_FLOAT, false, false, true, 2 };

      // 128-bit formats
   case GFXFormatR32G32B32A32F:
      return { 4, {CH_R, CH_G, CH_B, CH_A}, STBIR_TYPE_FLOAT, false, false, true, 4 };

   default: // fallback
      return { 1, {CH_L, CH_NONE, CH_NONE, CH_NONE}, STBIR_TYPE_UINT8, false, false, false, 1 };
   }
}

//--------------------------------------------------------------------------------
// Conversion plan
struct ConversionPlan
{
   bool bitDepthChange;
   bool channelRepack;
   bool colorspaceChange;
};

ConversionPlan decideConversion(const GBitmapFormatDesc& src, const GBitmapFormatDesc& dst)
{
   ConversionPlan plan = {};
   plan.bitDepthChange = src.bytesPerChannel != dst.bytesPerChannel || src.isFloat != dst.isFloat;
   plan.channelRepack = src.channels != dst.channels || dMemcmp(src.semantic, dst.semantic, sizeof(src.semantic)) != 0;
   plan.colorspaceChange = src.srgb != dst.srgb;
   return plan;
}

//--------------------------------------------------------------------------------
// Linear representation
struct LinearPixel
{
   float r = 0.f, g = 0.f, b = 0.f, a = 1.f;
};

inline float srgbToLinear(float c)
{
   return (c <= 0.04045f) ? c / 12.92f : powf((c + 0.055f) / 1.055f, 2.4f);
}

inline float linearToSrgb(float c)
{
   return (c <= 0.0031308f) ? c * 12.92f : 1.055f * powf(c, 1.f / 2.4f) - 0.055f;
}

static inline LinearPixel loadPackedPixel(
   const void* src,
   const GBitmapFormatDesc& fmt,
   U32 index)
{
   LinearPixel p;
   p.r = p.g = p.b = 0.f;
   p.a = 1.f;

   const U8* base = (const U8*)src + index * fmt.bytesPerPixel;

   U32 raw = 0;
   dMemcpy(&raw, base, fmt.bytesPerPixel);

#ifdef TORQUE_BIG_ENDIAN
   if (fmt.bytesPerPixel == 2)
      raw = convertLEndianToHost((U16)raw);
   else if (fmt.bytesPerPixel == 4)
      raw = convertLEndianToHost((U32)raw);
#endif

   for (U32 i = 0; i < fmt.channels; ++i)
   {
      const PackedChannelDesc& ch = fmt.packed[i];

      U32 mask = (1u << ch.bits) - 1u;
      U32 v = (raw >> ch.shift) & mask;

      // Expand to 8-bit exactly like GBitmap getColor code
      U8 expanded8;
      if (ch.bits == 5)
         expanded8 = (v << 3) | (v >> 2);
      else if (ch.bits == 6)
         expanded8 = (v << 2) | (v >> 4);
      else if (ch.bits == 4)
         expanded8 = v * 17;
      else if (ch.bits == 1)
         expanded8 = v ? 255 : 0;
      else // 8-bit
         expanded8 = (U8)v;

      float f = expanded8 / 255.f;

      switch (ch.semantic)
      {
      case CH_R: p.r = f; break;
      case CH_G: p.g = f; break;
      case CH_B: p.b = f; break;
      case CH_A: p.a = f; break;
      case CH_L:
         p.r = p.g = p.b = f;
         break;
      default:
         break;
      }
   }

   return p;
}

//--------------------------------------------------------------------------------
// Load a pixel from src format into LinearPixel
static inline LinearPixel loadPixel(const void* src, const GBitmapFormatDesc& fmt, U32 index)
{
   if (fmt.isPacked)
      return loadPackedPixel(src, fmt, index);

   LinearPixel p;
   const U8* base = (const U8*)src + index * fmt.channels * fmt.bytesPerChannel;

   for (U32 c = 0; c < fmt.channels; ++c)
   {
      float v = 0.f;
      if (fmt.is8())
         v = float(base[c]) / 255.f;
      else if (fmt.is16())
         v = float(convert16To8(*(const U16*)(base + c * 2))) / 255.f;
      else if (fmt.isFloat)
      {
         if (fmt.bytesPerChannel == 2) // half float
            v = convertHalfToFloat(*(const U16*)(base + c * 2));
         else // full float
            v = *(const float*)(base + c * 4);
      }

      if (fmt.srgb && fmt.semantic[c] != CH_A)
         v = srgbToLinear(v);

      switch (fmt.semantic[c])
      {
      case CH_R: p.r = v; break;
      case CH_G: p.g = v; break;
      case CH_B: p.b = v; break;
      case CH_A: p.a = v; break;
      case CH_L: p.r = p.g = p.b = v; break;
      default: break;
      }
   }
   return p;
}

static inline void storePackedPixel(
   void* dst,
   const GBitmapFormatDesc& fmt,
   U32 index,
   const LinearPixel& p)
{
   U32 raw = 0;

   for (U32 i = 0; i < fmt.channels; ++i)
   {
      const PackedChannelDesc& ch = fmt.packed[i];

      float v = 0.f;
      switch (ch.semantic)
      {
      case CH_R: v = p.r; break;
      case CH_G: v = p.g; break;
      case CH_B: v = p.b; break;
      case CH_A: v = p.a; break;
      case CH_L: v = p.r; break; // legacy behavior
      default:  continue;
      }

      // Clamp
      v = mClamp(v, 0.f, 1.f);

      // Canonical float → U8
      U32 expanded8 = U32(v * 255.f + 0.5f);

      // Contract to bit depth EXACTLY like Gbitmap setColor code
      U32 maxv = (1u << ch.bits) - 1u;
      U32 iv;

      if (ch.bits == 8)
         iv = expanded8;
      else
         iv = expanded8 * maxv / 255;

      raw |= (iv & maxv) << ch.shift;
   }

#ifdef TORQUE_BIG_ENDIAN
   if (fmt.bytesPerPixel == 2)
   {
      U16 v = convertLEndianToHost((U16)raw);
      dMemcpy((U8*)dst + index * fmt.bytesPerPixel, &v, 2);
   }
   else if (fmt.bytesPerPixel == 4)
   {
      U32 v = convertLEndianToHost(raw);
      dMemcpy((U8*)dst + index * fmt.bytesPerPixel, &v, 4);
   }
#else
   dMemcpy((U8*)dst + index * fmt.bytesPerPixel, &raw, fmt.bytesPerPixel);
#endif
}
//--------------------------------------------------------------------------------
// Store a LinearPixel into dst format
static inline void storePixel(void* dst, const GBitmapFormatDesc& fmt, U32 index, const LinearPixel& p)
{
   if (fmt.isPacked)
   {
      storePackedPixel(dst, fmt, index, p);
      return;
   }

   U8* base = (U8*)dst + index * fmt.channels * fmt.bytesPerChannel;
   for (U32 c = 0; c < fmt.channels; ++c)
   {
      float v = 0.f;
      switch (fmt.semantic[c])
      {
      case CH_R: v = p.r; break;
      case CH_G: v = p.g; break;
      case CH_B: v = p.b; break;
      case CH_A: v = p.a; break;
      case CH_L: v = p.r; break;
      default: break;
      }

      if (fmt.srgb && fmt.semantic[c] != CH_A)
         v = linearToSrgb(v);

      if (fmt.is8())
         base[c] = uint8_t(mClamp(v * 255.f, 0.f, 255.f));
      else if (fmt.is16())
         *(U16*)(base + c * 2) = convert8To16(uint8_t(mClamp(v * 255.f, 0.f, 255.f)));
      else if (fmt.isFloat)
      {
         if (fmt.bytesPerChannel == 2) // half float
            *(U16*)(base + c * 2) = convertFloatToHalf(v);
         else
            *(float*)(base + c * 4) = v;
      }
   }
}

//--------------------------------------------------------------------------------
// Main generalized converter
bool bitmapConvertFormat(U8** srcBuffer, U32 pixels, const GBitmapFormatDesc& srcFmt, const GBitmapFormatDesc& dstFmt)
{
   ConversionPlan plan = decideConversion(srcFmt, dstFmt);
   if (!plan.bitDepthChange && !plan.channelRepack && !plan.colorspaceChange)
      return true; // nothing to do

   void* dstBuffer = *srcBuffer;

   if (plan.bitDepthChange || plan.channelRepack)
      dstBuffer = new U8[pixels * dstFmt.channels * dstFmt.bytesPerChannel];

   for (U32 i = 0; i < pixels; ++i)
   {
      LinearPixel p = loadPixel(*srcBuffer, srcFmt, i);
      storePixel(dstBuffer, dstFmt, i, p);
   }

   if (dstBuffer != *srcBuffer)
   {
      delete[](U8*)* srcBuffer;
      *srcBuffer = (U8*)dstBuffer;
   }

   return true;
}

//--------------------------------------------------------------------------------
// Entry point for GBitmap::setFormat
bool bitmapALLConvertToOutput(U8** src, U32 pixels, GFXFormat srcFormat, GFXFormat dstFormat)
{
   const GBitmapFormatDesc& srcFmt = getFormatDesc(srcFormat);
   const GBitmapFormatDesc& dstFmt = getFormatDesc(dstFormat);
   return bitmapConvertFormat(src, pixels, srcFmt, dstFmt);
}

bool(*bitmapConvertToOutput)(U8** src, U32 pixels, GFXFormat srcFormat, GFXFormat dstFormat) = bitmapALLConvertToOutput;

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
