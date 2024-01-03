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

#include "core/stream/fileStream.h"
#include "core/stream/memStream.h"
#include "core/strings/stringFunctions.h"
#include "gfx/bitmap/gBitmap.h"

#ifdef __clang__
#define STBIWDEF static inline
#endif

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_STATIC
#include "stb_image_write.h"

static bool sReadSTB(const Torque::Path& path, GBitmap* bitmap);
static bool sWriteSTB(const Torque::Path& path, GBitmap* bitmap, U32 compressionLevel);

static struct _privateRegisterSTB
{
   _privateRegisterSTB()
   {
      GBitmap::Registration reg;
      reg.priority = 100;

      reg.extensions.push_back("png");
      reg.extensions.push_back("bmp");
      reg.extensions.push_back("jpg");
      reg.extensions.push_back("jpeg");
      reg.extensions.push_back("psd");
      reg.extensions.push_back("hdr");
      reg.extensions.push_back("tga");

      reg.readFunc = sReadSTB;

      reg.writeFunc = sWriteSTB;

      // for png only.
      reg.defaultCompression = 6;

      GBitmap::sRegisterFormat(reg);

   }
} sStaticRegisterSTB;

bool sReadSTB(const Torque::Path& path, GBitmap* bitmap)
{
   PROFILE_SCOPE(sReadSTB);

   S32 x, y, n, channels;
   String ext = path.getExtension();

   U32 prevWaterMark = FrameAllocator::getWaterMark();

   if (!stbi_info(path.getFullPath().c_str(), &x, &y, &channels))
   {
      FrameAllocator::setWaterMark(prevWaterMark);
      return false;
   }

   // do this to map 2 channels to 4, 2 channel not supported by gbitmap yet..
   if (channels == 2)
      channels = 4;
   if (!ext.equal("png"))
   {
      if (stbi_is_16_bit(path.getFullPath().c_str()))
      {
         U16* data = stbi_load_16(path.getFullPath().c_str(), &x, &y, &n, channels);

         // if succesful deal make the bitmap, else try other loaders.
         if (data)
         {
            GFXFormat format;
            if (n == 1)
               format = GFXFormatL16;
            else
               format = GFXFormatR16G16B16A16; // not sure if this is correct.

            bitmap->deleteImage();

            // actually allocate the bitmap space...
            bitmap->allocateBitmap(x, y,
               false,            // don't extrude miplevels...
               format);          // use determined format...

            U16* pBase = (U16*)bitmap->getBits();

            U32 rowBytes = bitmap->getByteSize();

            dMemcpy(pBase, data, rowBytes);

            stbi_image_free(data);

            FrameAllocator::setWaterMark(prevWaterMark);

            return true;
         }
      }
   }

   if (ext.equal("hdr"))
   {
      // force load to 4 channel.
      float* data = stbi_loadf(path.getFullPath().c_str(), &x, &y, &n, 4);

      unsigned char* dataChar = stbi__hdr_to_ldr(data, x, y, 4);
      bitmap->deleteImage();
      // actually allocate the bitmap space...
      bitmap->allocateBitmap(x, y,
         false,
         GFXFormatR8G8B8A8);

      U8* pBase = (U8*)bitmap->getBits();

      U32 rowBytes = x * y * 4;

      dMemcpy(pBase, dataChar, rowBytes);

      stbi_image_free(dataChar);

      FrameAllocator::setWaterMark(prevWaterMark);

      return true;
   }

   unsigned char* data = stbi_load(path.getFullPath().c_str(), &x, &y, &n, channels);

   bitmap->deleteImage();

   GFXFormat format;

   switch (channels) {
   case  1:
      format = GFXFormatA8;
      break;
   case 2:
      format = GFXFormatA8L8;
      break;
   case 3:
      format = GFXFormatR8G8B8;
      break;
   case 4:
      format = GFXFormatR8G8B8A8;
      break;
   default:
      FrameAllocator::setWaterMark(prevWaterMark);
      return false;
   }

   // actually allocate the bitmap space...
   bitmap->allocateBitmap(x, y,
      false,            // don't extrude miplevels...
      format);          // use determined format...

   U8* pBase = (U8*)bitmap->getBits();

   U32 rowBytes = bitmap->getByteSize();

   dMemcpy(pBase, data, rowBytes);

   stbi_image_free(data);
   // Check this bitmap for transparency
   if (channels == 4)
      bitmap->checkForTransparency();

   FrameAllocator::setWaterMark(prevWaterMark);

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



   U32 stride = width * bytes;
   // we always have at least 1
   U32 comp = 1;

   if (format == GFXFormatR8G8B8)
   {
      comp = 3;
   }
   else if (format == GFXFormatR8G8B8A8 || format == GFXFormatR8G8B8X8 || format == GFXFormatR8G8B8A8_LINEAR_FORCE)
   {
      comp = 4;
   }

   if (ext.equal("png"))
   {
      stbi_write_png_compression_level = compressionLevel;
      if (stbi_write_png(path.getFullPath().c_str(), width, height, comp, bitmap->getWritableBits(), 0))
         return true;
   }

   if (ext.equal("tga"))
   {
      if (stbi_write_tga(path.getFullPath().c_str(), width, height, comp, bitmap->getWritableBits()))
         return true;
   }

   if (ext.equal("bmp"))
   {
      if (stbi_write_bmp(path.getFullPath().c_str(), width, height, comp, bitmap->getWritableBits()))
         return true;
   }

   if (ext.equal("jpg") || ext.equal("jpeg"))
   {
      if (stbi_write_jpg(path.getFullPath().c_str(), width, height, comp, bitmap->getWritableBits(), compressionLevel))
         return true;
   }

   if (ext.equal("hdr"))
   {
      if (stbi_write_hdr(path.getFullPath().c_str(), width, height, comp, (const F32*)bitmap->getWritableBits()))
         return true;
   }

   return false;
}
