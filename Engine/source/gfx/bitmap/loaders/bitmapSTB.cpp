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
#include "gfx/bitmap/imageUtils.h"
#include "gfx/bitmap/loaders/ies/ies_loader.h"

#ifdef __clang__
#define STBIWDEF static inline
#endif

#pragma warning( push )
#pragma warning( disable : 4505 ) // unreferenced function removed.

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_STATIC
#include "stb_image_write.h"

#pragma warning(pop)

static bool sReadSTB(const Torque::Path& path, GBitmap* bitmap);
static bool sReadStreamSTB(Stream& stream, GBitmap* bitmap, U32 len);

static bool sWriteSTB(const Torque::Path& path, GBitmap* bitmap, U32 compressionLevel);
static bool sWriteStreamSTB(const String& bmType, Stream& stream, GBitmap* bitmap, U32 compressionLevel);

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

      reg.extensions.push_back("png");
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
   PROFILE_SCOPE(sReadSTB);

   S32 x, y, n, channels;
   String ext = path.getExtension();

   U32 prevWaterMark = FrameAllocator::getWaterMark();

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

         FrameAllocator::setWaterMark(prevWaterMark);

         return true;
      }
      else
      {
         FileStream* readIes = new FileStream;

         if (!readIes->open(path.getFullPath(), Torque::FS::File::Read))
         {
            Con::printf("Failed to open IES profile:%s", path.getFullFileName().c_str());
            return false;
         }

         if (readIes->getStatus() != Stream::Ok)
         {
            Con::printf("Failed to open IES profile:%s", path.getFullFileName().c_str());
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
            return false;
         }

         float* data = new float[x*y*channels];

         if (!IESLoader.saveAs1D(info, data, x, channels))
         {
            Con::printf("Failed to create 2d Texture for IES profile:%s", path.getFullFileName().c_str());
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

         FrameAllocator::setWaterMark(prevWaterMark);

         sWriteSTB(textureName, bitmap, 10);

         return true;
      }

   }

   if (!stbi_info(path.getFullPath().c_str(), &x, &y, &channels))
   {
      FrameAllocator::setWaterMark(prevWaterMark);
      const char* stbErr = stbi_failure_reason();

      if (!stbErr)
         stbErr = "Unknown Error!";

      Con::errorf("STB get file info: %s", stbErr);
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
      float* data = stbi_loadf(path.getFullPath().c_str(), &x, &y, &n, 0);

      unsigned char* dataChar = stbi__hdr_to_ldr(data, x, y, n);
      bitmap->deleteImage();
      // actually allocate the bitmap space...
      bitmap->allocateBitmap(x, y,
         false,
         GFXFormatR8G8B8);

      U8* pBase = (U8*)bitmap->getBits();

      U32 rowBytes = x * y * n;

      dMemcpy(pBase, dataChar, rowBytes);

      //stbi_image_free(data);
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

bool sReadStreamSTB(Stream& stream, GBitmap* bitmap, U32 len)
{
   PROFILE_SCOPE(sReadStreamSTB);
   // only used for font at the moment.

   U8* data = new U8[len];
   stream.read(len, data);

   S32 width, height, comp = 0;

   unsigned char* pixelData = stbi_load_from_memory((const U8*)data, (int)len, &width, &height, &comp, 0);

   if (!pixelData)
   {
      const char* stbErr = stbi_failure_reason();

      if (!stbErr)
         stbErr = "Unknown Error!";

      Con::errorf("sReadStreamSTB Error: %s", stbErr);
      return false;
   }
   bitmap->deleteImage();

   //work out what format we need to use - todo floating point?
   GFXFormat fmt = GFXFormat_FIRST;
   switch (comp)
   {
   case 1: fmt = GFXFormatA8; break;
   case 2: fmt = GFXFormatA8L8; break; //todo check this
   case 3: fmt = GFXFormatR8G8B8; break;
   case 4: fmt = GFXFormatR8G8B8A8; break;
   }

   bitmap->allocateBitmap(width, height, false, fmt);

   U8* pBase = bitmap->getWritableBits(0);
   U32 rowBytes = bitmap->getByteSize();
   dMemcpy(pBase, pixelData, rowBytes);

   dFree(data);
   dFree(pixelData);

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

struct DeferredPNGWriterData
{
   S32 width = 0;
   S32 height = 0;
   S32 channels = 0;
   dsize_t offset = 0;
   U8* pPixelData = NULL;
   GFXFormat format;
   Stream* pStream = NULL;
};

DeferredPNGWriter::DeferredPNGWriter() :
   mData(NULL),
   mActive(false)
{
   mData = new DeferredPNGWriterData();
}

DeferredPNGWriter::~DeferredPNGWriter()
{
   if (mData)
   {
      SAFE_DELETE_ARRAY(mData->pPixelData);
   }

   SAFE_DELETE(mData);
}

bool DeferredPNGWriter::begin(GFXFormat format, S32 width, S32 height, Stream& stream)
{
   // ONLY RGB bitmap writing supported at this time!
   AssertFatal(format == GFXFormatR8G8B8 ||
      format == GFXFormatR8G8B8A8 ||
      format == GFXFormatR8G8B8X8 ||
      format == GFXFormatA8 ||
      format == GFXFormatR5G6B5, "DeferredPNGWriter::begin: ONLY RGB bitmap writing supported at this time.");

   if (format != GFXFormatR8G8B8 &&
      format != GFXFormatR8G8B8A8 &&
      format != GFXFormatR8G8B8X8 &&
      format != GFXFormatA8 &&
      format != GFXFormatR5G6B5)
   {
      return false;
   }

   mData->pStream = &stream;
   mData->width = width;
   mData->height = height;
   mData->format = format;

   const size_t dataSize = GFXFormat_getByteSize(format) * width * height;
   mData->pPixelData = new U8[dataSize];

   mActive = true;

   return true;
}

void DeferredPNGWriter::append(GBitmap* bitmap, U32 rows)
{
   AssertFatal(mActive, "Cannot append to an inactive DeferredPNGWriter!");

   if (mData->channels == 0)
   {
      mData->channels = bitmap->getBytesPerPixel();
   }

   const dsize_t dataChuckSize = bitmap->getByteSize();

   const U8* pSrcData = bitmap->getBits();
   U8* pDstData = mData->pPixelData + mData->offset;
   dMemcpy(pDstData, pSrcData, dataChuckSize);
   mData->offset += dataChuckSize;
}

void DeferredPNGWriter::end()
{
   AssertFatal(mActive, "Cannot end an inactive DeferredPNGWriter!");

   stbi_write_png_to_func(stbiWriteFunc, mData->pStream, mData->width, mData->height, mData->channels, mData->pPixelData, mData->width * mData->channels);

   mActive = false;
}
