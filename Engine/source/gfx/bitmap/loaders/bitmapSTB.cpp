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

#include "platform/platform.h"
#include "console/console.h"

#include "core/stream/fileStream.h"
#include "core/stream/memStream.h"
#include "core/strings/stringFunctions.h"
#include "gfx/bitmap/gBitmap.h"
#include "gfx/bitmap/bitmapUtils.h"
#include "gfx/bitmap/imageUtils.h"
#include "gfx/bitmap/loaders/ies/ies_loader.h"
#include "platform/profiler.h"

#ifdef __clang__
#define STBIWDEF static inline
#endif

#pragma warning( push )
#pragma warning( disable : 4505 ) // unreferenced function removed.

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include "gfx/bitmap/loaders/stb/stb_image.h"
#endif

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_STATIC
#include "gfx/bitmap/loaders/stb/stb_image_write.h"

#pragma warning(pop)

static bool sReadSTB(const Torque::Path& path, GBitmap* bitmap);
static bool sReadStreamSTB(Stream& stream, GBitmap* bitmap, U32 len);

static bool sWriteSTB(const Torque::Path& path, GBitmap* bitmap, U32 compressionLevel);
static bool sWriteStreamSTB(const String& bmType, Stream& stream, GBitmap* bitmap, U32 compressionLevel);

static GFXFormat determineFormat(bool isHDR, bool is16Bit, int numChannels)
{
   if (isHDR)
   {
      // we force hdr to 4 channels.
      return GFXFormatR32G32B32A32F;
   }
   else if (is16Bit)
   {
      switch (numChannels)
      {
      case 1: return GFXFormatL16;
      case 2: return GFXFormatA8L8; // No native L16A16, but could add one later
      case 3: return GFXFormatR16G16B16A16;
      case 4: return GFXFormatR16G16B16A16;
      }
   }
   else // 8-bit
   {
      switch (numChannels)
      {
      case 1: return GFXFormatA8;
      case 2: return GFXFormatA8L8;
      case 3: return GFXFormatR8G8B8;
      case 4: return GFXFormatR8G8B8A8;
      }
   }

   // fallback
   return GFXFormatR8G8B8A8;
}

// stbi_write callback / rextimmy.
static void stbiWriteFunc(void* context, void* data, int size)
{
   Stream* stream = static_cast<Stream*>(context);
   stream->write(size);
   stream->write(size, data);
}

static struct _privateRegisterSTB
{
   _privateRegisterSTB()
   {
      GBitmap::Registration reg;
      reg.priority = 100;

      //reg.extensions.push_back("png");
      reg.extensions.push_back("bmp");
      reg.extensions.push_back("jpg");
      reg.extensions.push_back("jpeg");
      reg.extensions.push_back("psd");
      reg.extensions.push_back("hdr");
      reg.extensions.push_back("tga");
      reg.extensions.push_back("ies");

      reg.readFunc = sReadSTB;
      reg.readStreamFunc = sReadStreamSTB;

      reg.writeFunc = sWriteSTB;
      reg.writeStreamFunc = sWriteStreamSTB;

      // for png only.
      reg.defaultCompression = 6;

      GBitmap::sRegisterFormat(reg);

   }
} sStaticRegisterSTB;


bool sReadSTB(const Torque::Path& path, GBitmap* bitmap)
{
   S32 x, y, n, channels;
   String ext = path.getExtension();

   PROFILE_START_IF(sReadSTB_,ext, png)
   else PROFILE_START_IF(sReadSTB_, ext, bmp)
   else PROFILE_START_IF(sReadSTB_, ext, jpg)
   else PROFILE_START_IF(sReadSTB_, ext, jpeg)
   else PROFILE_START_IF(sReadSTB_, ext, psd)
   else PROFILE_START_IF(sReadSTB_, ext, hdr)
   else PROFILE_START_IF(sReadSTB_, ext, tga)
   else PROFILE_START_IF(sReadSTB_, ext, ies)
   else
   {
      PROFILE_START(sReadSTB);
   }
   // if this is an ies profile we need to create a texture for it.
   if (ext.equal("ies"))
   {
      String textureName = path.getFullPath();
      textureName.replace(".ies", ".png");
      x = 256;
      y = 1;
      n = 4;
      channels = 4;
      GFXFormat format = GFXFormatR8G8B8A8;

      if (Torque::FS::IsFile(textureName.c_str()))
      {
         // if the txture already exist, load it.
         unsigned char* data = stbi_load(textureName.c_str(), &x, &y, &n, channels);

         // actually allocate the bitmap space...
         bitmap->allocateBitmap(x, y,
            false,            // don't extrude miplevels...
            format);          // use determined format...

         U8* pBase = (U8*)bitmap->getBits();

         U32 rowBytes = bitmap->getByteSize();

         dMemcpy(pBase, data, rowBytes);

         stbi_image_free(data);
         PROFILE_END();
         return true;
      }
      else
      {
         FileStream* readIes = new FileStream;

         if (!readIes->open(path.getFullPath(), Torque::FS::File::Read))
         {
            Con::printf("Failed to open IES profile:%s", path.getFullFileName().c_str());
            PROFILE_END();
            return false;
         }

         if (readIes->getStatus() != Stream::Ok)
         {
            Con::printf("Failed to open IES profile:%s", path.getFullFileName().c_str());
            PROFILE_END();
            return false;
         }

         U32 buffSize = readIes->getStreamSize();
         char* buffer = new char[buffSize];
         readIes->read(buffSize, buffer);


         IESFileInfo info;
         IESLoadHelper IESLoader;

         if (!IESLoader.load(buffer, buffSize, info))
         {
            Con::printf("Failed to load IES profile:%s \n LoaderError: %s", path.getFullFileName().c_str(), info.error().c_str());
            PROFILE_END();
            return false;
         }

         float* data = new float[x*y*channels];

         if (!IESLoader.saveAs1D(info, data, x, channels))
         {
            Con::printf("Failed to create 2d Texture for IES profile:%s", path.getFullFileName().c_str());
            PROFILE_END();
            return false;
         }

         // use stb function to convert float data to uchar
         unsigned char* dataChar = stbi__hdr_to_ldr(data, x, y, channels);

         bitmap->deleteImage();
         // actually allocate the bitmap space...
         bitmap->allocateBitmap(x, y,
            false,
            format);

         U8* pBase = (U8*)bitmap->getBits();

         U32 rowBytes = x * y * channels;

         dMemcpy(pBase, dataChar, rowBytes);

         stbi_image_free(dataChar);

         sWriteSTB(textureName, bitmap, 10);

         PROFILE_END();
         return true;
      }

   }

   const char* filePath = path.getFullPath().c_str();

   // Detect format
   bool isHDR = stbi_is_hdr(filePath);
   bool is16Bit = stbi_is_16_bit(filePath);

   void* data = nullptr;

   if (isHDR) {
      data = stbi_loadf(filePath, &x, &y, &n, 4);
   }
   else if (is16Bit)
      data = stbi_load_16(filePath, &x, &y, &n, 0);
   else
      data = stbi_load(filePath, &x, &y, &n, 0);

   if (!data)
   {
      PROFILE_END();
      Con::errorf("sReadSTB() - Failed to load %s: %s", filePath, stbi_failure_reason());
      return false;
   }

   // Determine internal GFX format
   GFXFormat format = determineFormat(isHDR, is16Bit, n);

   // Allocate bitmap
   bitmap->deleteImage();
   bitmap->allocateBitmap(x, y, false, format);

   //if (isHDR)
   //{
   //   U16* pBase = (U16*)bitmap->getBits();
   //   const size_t totalPixels = (size_t)x * (size_t)y;
   //   for (size_t i = 0; i < totalPixels * 4; ++i)
   //   {
   //      pBase[i] = convertFloatToHalf(reinterpret_cast<F32*>(data)[i]); // convert F32 -> U16
   //   }
   //}
   //else
   //{
      U8* dst = (U8*)bitmap->getBits();
      U32 byteSize = bitmap->getByteSize();
      dMemcpy(dst, data, byteSize);
   //}

   stbi_image_free(data);

   bitmap->checkForTransparency();

   PROFILE_END();
   return true;
}

bool sReadStreamSTB(Stream& stream, GBitmap* bitmap, U32 len)
{
   PROFILE_SCOPE(sReadStreamSTB);

   Vector<U8> data(len);
   stream.read(len, data.address());

   int x, y, n;
   bool isHDR = stbi_is_hdr_from_memory(data.address(), len);
   bool is16Bit = stbi_is_16_bit_from_memory(data.address(), len);

   void* pixels = nullptr;
   if (isHDR)
      pixels = stbi_loadf_from_memory(data.address(), len, &x, &y, &n, 0);
   else if (is16Bit)
      pixels = stbi_load_16_from_memory(data.address(), len, &x, &y, &n, 0);
   else
      pixels = stbi_load_from_memory(data.address(), len, &x, &y, &n, 0);

   if (!pixels)
   {
      Con::errorf("sReadStreamSTB() - STB load failed: %s", stbi_failure_reason());
      return false;
   }

   GFXFormat format = determineFormat(isHDR, is16Bit, n);
   bitmap->deleteImage();
   bitmap->allocateBitmap(x, y, false, format);
   dMemcpy(bitmap->getWritableBits(0), pixels, bitmap->getByteSize());

   stbi_image_free(pixels);

   bitmap->checkForTransparency();

   return true;
}

/**
 * Write bitmap to an image file.
 *
 * @param[in]       path                        Destination image file path. File name extension determines image format.
 *                                              ".bmp" for Microsoft Bitmap.
 *                                              ".hdr" for High Dynamic Range (HDR).
 *                                              ".jpg" or ".jpeg" for Joint Photographic Experts Group (JPEG).
 *                                              ".png" for Portable Network Graphics (PNG).
 *                                              ".tga" for Truevision TGA (TARGA).
 *
 *
 * @param[in]       bitmap                      Source bitmap to encode image from.
 * @param           compressionLevel            Image format specific compression level.
 *                                              For JPEG sets the quality level percentage, range 0 to 100.
 *                                              Not used for other image formats.
 */
bool sWriteSTB(const Torque::Path& path, GBitmap* bitmap, U32 compressionLevel)
{
   PROFILE_SCOPE(sWriteSTB);

   // get our data to be saved.
   U32 width = bitmap->getWidth();
   U32 height = bitmap->getHeight();
   U32 bytes = bitmap->getBytesPerPixel();
   GFXFormat format = bitmap->getFormat();
   String ext = path.getExtension();

   if (ext.equal("png"))
   {
      stbi_write_png_compression_level = compressionLevel;
      if (stbi_write_png(path.getFullPath().c_str(), width, height, bytes, bitmap->getWritableBits(), 0))
         return true;
   }

   if (ext.equal("tga"))
   {
      if (stbi_write_tga(path.getFullPath().c_str(), width, height, bytes, bitmap->getWritableBits()))
         return true;
   }

   if (ext.equal("bmp"))
   {
      if (stbi_write_bmp(path.getFullPath().c_str(), width, height, bytes, bitmap->getWritableBits()))
         return true;
   }

   if (ext.equal("jpg") || ext.equal("jpeg"))
   {
      if (stbi_write_jpg(path.getFullPath().c_str(), width, height, bytes, bitmap->getWritableBits(), compressionLevel))
         return true;
   }

   if (ext.equal("hdr"))
   {
      if (stbi_write_hdr(path.getFullPath().c_str(), width, height, bytes, (const F32*)bitmap->getWritableBits()))
         return true;
   }

   return false;
}

bool sWriteStreamSTB(const String& bmType, Stream& stream, GBitmap* bitmap, U32 compressionLevel)
{
   PROFILE_SCOPE(sWriteStreamSTB);

   S32 width = bitmap->getWidth();
   S32 height = bitmap->getHeight();
   const U8* pPixelData = bitmap->getBits();
   S32 channels = bitmap->getBytesPerPixel();

   if (bmType == String("png"))
   {
      stbi_write_png_compression_level = compressionLevel;
      if (stbi_write_png_to_func(stbiWriteFunc, &stream, width, height, channels, pPixelData, width * channels))
         return true;
   }
   else if (bmType == String("tga"))
   {
      if (stbi_write_tga_to_func(stbiWriteFunc, &stream, width, height, channels, pPixelData))
         return true;
   }
   else if (bmType == String("bmp"))
   {
      if (stbi_write_bmp_to_func(stbiWriteFunc, &stream, width, height, channels, pPixelData))
         return true;
   }
   else if (bmType == String("jpg") || bmType == String("jpeg"))
   {
      if (stbi_write_jpg_to_func(stbiWriteFunc, &stream, width, height, channels, pPixelData, compressionLevel))
         return true;
   }
   else if (bmType == String("hdr"))
   {
      if (stbi_write_hdr_to_func(stbiWriteFunc, &stream, width, height, channels, (const F32*)pPixelData))
         return true;
   }

   return false;
}
