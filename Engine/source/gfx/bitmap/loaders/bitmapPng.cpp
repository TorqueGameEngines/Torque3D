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
#include "gfx/bitmap/pngUtils.h"

#define PNG_INTERNAL 1
#include <time.h>
#include "lpng/png.h"
#include "zlib/zlib.h"

#ifdef NULL
#undef NULL
#define NULL 0
#endif


/// Compression levels for PNGs range from 0-9.
/// A value outside that range will cause the write routine to look for the best compression for a given PNG.  This can be slow.
static bool sReadPNG(const Torque::Path& path, GBitmap* bitmap);
static bool sReadStreamPNG(Stream& stream, GBitmap* bitmap, U32 len);
static bool sWritePNG(const Torque::Path& path, GBitmap* bitmap, U32 compressionLevel);
static bool sWriteStreamPNG(const String& bmType, Stream& stream, GBitmap* bitmap, U32 compressionLevel);

// Internal functions used.
static bool _readStreamPNG(Stream& stream, GBitmap* bitmap, U32 len, const char* filename);
static bool _writePNG(GBitmap *bitmap, Stream &stream, U32 compressionLevel, U32 strategy, U32 filter, const char* filename = "unknown");

static struct _privateRegisterPNG
{
   _privateRegisterPNG()
   {
      GBitmap::Registration reg;

      reg.priority = 100;
      reg.extensions.push_back( "png" );

      reg.readFunc = sReadPNG;
      reg.readStreamFunc = sReadStreamPNG;

      reg.writeFunc = sWritePNG;
      reg.writeStreamFunc = sWriteStreamPNG;

      reg.defaultCompression = 6;

      GBitmap::sRegisterFormat( reg );
   }
} sStaticRegisterPNG;

//-----------------------------------------------------------------------------
// PNG context passed to libpng for error reporting
//-----------------------------------------------------------------------------
struct PngContext
{
   const char* filename;
   explicit PngContext(const char* f) : filename(f) {}
};

//-----------------------------------------------------------------------------
// libpng callbacks
//-----------------------------------------------------------------------------
static void pngReadDataFn(png_structp png_ptr, png_bytep data, png_size_t length)
{
   Stream* strm = (Stream*)png_get_io_ptr(png_ptr);
   AssertFatal(strm, "pngReadDataFn - No stream.");
   if (!strm->read(length, data))
      Con::errorf("pngReadDataFn - Failed to read %u bytes from stream.", (U32)length);
}

static void pngWriteDataFn(png_structp png_ptr, png_bytep data, png_size_t length)
{
   Stream* strm = (Stream*)png_get_io_ptr(png_ptr);
   AssertFatal(strm, "pngWriteDataFn - No stream.");
   if (!strm->write(length, data))
      Con::errorf("pngWriteDataFn - Failed to write %u bytes to stream.", (U32)length);
}

static void pngFlushDataFn(png_structp /*png_ptr*/) {}

static png_voidp pngMallocFn(png_structp /*png_ptr*/, png_size_t size) { return FrameAllocator::alloc(size); }
static void      pngFreeFn(png_structp /*png_ptr*/, png_voidp  /*mem*/) {}

static png_voidp pngRealMallocFn(png_structp /*png_ptr*/, png_size_t size) { return (png_voidp)dMalloc(size); }
static void      pngRealFreeFn(png_structp /*png_ptr*/, png_voidp mem) { dFree(mem); }

static void pngFatalErrorFn(png_structp png_ptr, png_const_charp pMessage)
{
   const char* filename = "unknown";
   if (png_ptr)
   {
      PngContext* ctx = (PngContext*)png_get_error_ptr(png_ptr);
      if (ctx && ctx->filename)
         filename = ctx->filename;
   }
   Con::errorf("pngFatalErrorFn - Fatal error in '%s': %s", filename, pMessage);
   AssertISV(false, avar("libpng fatal error in '%s':\n%s", filename, pMessage));
}

static void pngWarningFn(png_structp png_ptr, png_const_charp pMessage)
{
#if TORQUE_DEBUG
   const char* filename = "unknown";
   if (png_ptr)
   {
      PngContext* ctx = (PngContext*)png_get_error_ptr(png_ptr);
      if (ctx && ctx->filename)
         filename = ctx->filename;
   }
   Con::warnf("pngWarningFn - Warning in '%s': %s", filename, pMessage);
#endif
}

//-----------------------------------------------------------------------------
// RAII guards for png read/write structs
//-----------------------------------------------------------------------------
struct PngReadGuard
{
   png_structp png_ptr = nullptr;
   png_infop   info_ptr = nullptr;
   png_infop   end_info = nullptr;
   PngContext  ctx;

   explicit PngReadGuard(const char* filename) : ctx(filename) {}

   bool init()
   {
      png_ptr = png_create_read_struct_2(PNG_LIBPNG_VER_STRING,
         &ctx, pngFatalErrorFn, pngWarningFn,
         NULL, pngRealMallocFn, pngRealFreeFn);
      if (!png_ptr)
      {
         Con::errorf("PngReadGuard - png_create_read_struct_2 failed for '%s'.", ctx.filename);
         return false;
      }

      info_ptr = png_create_info_struct(png_ptr);
      if (!info_ptr)
      {
         Con::errorf("PngReadGuard - png_create_info_struct (info) failed for '%s'.", ctx.filename);
         return false;
      }

      end_info = png_create_info_struct(png_ptr);
      if (!end_info)
      {
         Con::errorf("PngReadGuard - png_create_info_struct (end) failed for '%s'.", ctx.filename);
         return false;
      }

      return true;
   }

   ~PngReadGuard()
   {
      if (png_ptr)
         png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
   }
};

struct PngWriteGuard
{
   png_structp png_ptr = nullptr;
   png_infop   info_ptr = nullptr;
   PngContext  ctx;

   explicit PngWriteGuard(const char* filename) : ctx(filename) {}

   bool init(bool useFrameAllocator = true)
   {
      png_ptr = png_create_write_struct_2(PNG_LIBPNG_VER_STRING,
         &ctx, pngFatalErrorFn, pngWarningFn,
         NULL,
         useFrameAllocator ? pngMallocFn : pngRealMallocFn,
         useFrameAllocator ? pngFreeFn : pngRealFreeFn);
      if (!png_ptr)
      {
         Con::errorf("PngWriteGuard - png_create_write_struct_2 failed for '%s'.", ctx.filename);
         return false;
      }

      info_ptr = png_create_info_struct(png_ptr);
      if (!info_ptr)
      {
         Con::errorf("PngWriteGuard - png_create_info_struct failed for '%s'.", ctx.filename);
         return false;
      }

      return true;
   }

   ~PngWriteGuard()
   {
      if (png_ptr)
         png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
   }
};

//-----------------------------------------------------------------------------
// Shared helpers
//-----------------------------------------------------------------------------
static GFXFormat _determineReadFormat(png_structp png_ptr, png_infop info_ptr, bool& transAlpha)
{
   S32 bit_depth, color_type;
   png_uint_32 width, height;
   png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, NULL, NULL, NULL);

   transAlpha = false;
   GFXFormat format = GFXFormatR8G8B8;

   if (bit_depth == 16 && color_type != PNG_COLOR_TYPE_GRAY)
      png_set_strip_16(png_ptr);

   if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
   {
      png_set_expand(png_ptr);
      transAlpha = true;
   }

   switch (color_type)
   {
   case PNG_COLOR_TYPE_PALETTE:
      png_set_expand(png_ptr);
      format = transAlpha ? GFXFormatR8G8B8A8 : GFXFormatR8G8B8;
      break;
   case PNG_COLOR_TYPE_GRAY:
      png_set_expand(png_ptr);
      format = (bit_depth == 16) ? GFXFormatR5G6B5 : GFXFormatA8;
      break;
   case PNG_COLOR_TYPE_GRAY_ALPHA:
      png_set_expand(png_ptr);
      png_set_gray_to_rgb(png_ptr);
      format = GFXFormatR8G8B8A8;
      break;
   case PNG_COLOR_TYPE_RGB:
      png_set_expand(png_ptr);
      format = transAlpha ? GFXFormatR8G8B8A8 : GFXFormatR8G8B8;
      break;
   case PNG_COLOR_TYPE_RGB_ALPHA:
      png_set_expand(png_ptr);
      format = GFXFormatR8G8B8A8;
      break;
   default:
      Con::errorf("_determineReadFormat - Unrecognised color_type %d.", color_type);
      break;
   }

   return format;
}

static bool _validateRowBytes(const char* filename, GFXFormat format, U32 rowBytes, U32 width)
{
   const U32 expected =
      (format == GFXFormatR8G8B8) ? width * 3 :
      (format == GFXFormatR8G8B8A8) ? width * 4 :
      (format == GFXFormatR5G6B5) ? width * 2 : 0;

   if (expected && rowBytes != expected)
   {
      Con::errorf("_validateRowBytes - '%s': rowBytes %d != expected %d for format %d.",
         filename, rowBytes, expected, format);
      return false;
   }
   return true;
}

static void _applyWriteIHDR(png_structp png_ptr, png_infop info_ptr, GFXFormat format, U32 width, U32 height)
{
   switch (format)
   {
   case GFXFormatR8G8B8:
      png_set_IHDR(png_ptr, info_ptr, width, height, 8,
         PNG_COLOR_TYPE_RGB, NULL, NULL, NULL);
      break;
   case GFXFormatR8G8B8A8:
   case GFXFormatR8G8B8X8:
   case GFXFormatR8G8B8A8_LINEAR_FORCE:
      png_set_IHDR(png_ptr, info_ptr, width, height, 8,
         PNG_COLOR_TYPE_RGB_ALPHA, NULL, NULL, NULL);
      break;
   case GFXFormatA8:
      png_set_IHDR(png_ptr, info_ptr, width, height, 8,
         PNG_COLOR_TYPE_GRAY, NULL, NULL, NULL);
      break;
   case GFXFormatR5G6B5:
   {
      png_set_IHDR(png_ptr, info_ptr, width, height, 16,
         PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE,
         PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
      png_color_8_struct sigBit = { 0 };
      sigBit.gray = 16;
      png_set_sBIT(png_ptr, info_ptr, &sigBit);
      png_set_swap(png_ptr);
      break;
   }
   default:
      break;
   }
}

static bool _isSupportedWriteFormat(GFXFormat format)
{
   switch (format)
   {
   case GFXFormatR8G8B8:
   case GFXFormatR8G8B8A8:
   case GFXFormatR8G8B8X8:
   case GFXFormatR8G8B8A8_LINEAR_FORCE:
   case GFXFormatA8:
   case GFXFormatR5G6B5:
      return true;
   default:
      return false;
   }
}

//-----------------------------------------------------------------------------
// Core read / write
//-----------------------------------------------------------------------------
static bool _readStreamPNG(Stream& stream, GBitmap* bitmap, U32 /*len*/, const char* filename = "unknown")
{
   PROFILE_SCOPE(sReadPNG);

   static const U32 cs_headerBytesChecked = 8;
   U8 header[cs_headerBytesChecked];
   stream.read(cs_headerBytesChecked, header);

   if (!png_check_sig(header, cs_headerBytesChecked))
   {
      Con::errorf("_readStreamPNG - '%s' does not have a valid PNG signature.", filename);
      return false;
   }

   U32 prevWaterMark = FrameAllocator::getWaterMark();

   PngReadGuard guard(filename);
   if (!guard.init())
   {
      FrameAllocator::setWaterMark(prevWaterMark);
      return false;
   }

   png_set_read_fn(guard.png_ptr, &stream, pngReadDataFn);
   png_set_sig_bytes(guard.png_ptr, cs_headerBytesChecked);
   png_read_info(guard.png_ptr, guard.info_ptr);

   bool transAlpha = false;
   GFXFormat format = _determineReadFormat(guard.png_ptr, guard.info_ptr, transAlpha);

   png_uint_32 number_of_passes = png_set_interlace_handling(guard.png_ptr);
   png_read_update_info(guard.png_ptr, guard.info_ptr);

   png_uint_32 width = png_get_image_width(guard.png_ptr, guard.info_ptr);
   png_uint_32 height = png_get_image_height(guard.png_ptr, guard.info_ptr);
   png_uint_32 rowBytes = png_get_rowbytes(guard.png_ptr, guard.info_ptr);

   if (!_validateRowBytes(filename, format, rowBytes, width))
   {
      FrameAllocator::setWaterMark(prevWaterMark);
      return false;
   }

   bitmap->deleteImage();
   bitmap->allocateBitmap(width, height, false, format);

   png_bytep* rowPointers = new png_bytep[height];
   U8* pBase = (U8*)bitmap->getBits();
   for (U32 i = 0; i < height; i++)
      rowPointers[i] = pBase + (i * rowBytes);

   png_read_image(guard.png_ptr, rowPointers);
   delete[] rowPointers;

   png_read_end(guard.png_ptr, NULL);

   bitmap->checkForTransparency();
   FrameAllocator::setWaterMark(prevWaterMark);
   return true;
}

static bool _writePNG(GBitmap* bitmap, Stream& stream, U32 compressionLevel, U32 strategy, U32 filter, const char* filename)
{
   GFXFormat format = bitmap->getFormat();

   if (!_isSupportedWriteFormat(format))
   {
      Con::errorf("_writePNG - '%s': Unsupported format %d.", filename, format);
      return false;
   }

   PngWriteGuard guard(filename);
   if (!guard.init(true))
      return false;

   png_set_write_fn(guard.png_ptr, &stream, pngWriteDataFn, pngFlushDataFn);
   png_set_compression_window_bits(guard.png_ptr, 15);
   png_set_compression_level(guard.png_ptr, compressionLevel);
   png_set_filter(guard.png_ptr, 0, filter);

   _applyWriteIHDR(guard.png_ptr, guard.info_ptr, format, bitmap->getWidth(), bitmap->getHeight());
   png_write_info(guard.png_ptr, guard.info_ptr);

   FrameAllocatorMarker marker;
   const U32 height = bitmap->getHeight();
   png_bytep* rowPointers = (png_bytep*)marker.alloc(height * sizeof(png_bytep));
   for (U32 i = 0; i < height; i++)
      rowPointers[i] = const_cast<png_bytep>(bitmap->getAddress(0, i));

   png_write_image(guard.png_ptr, rowPointers);
   png_write_end(guard.png_ptr, guard.info_ptr);
   return true;
}

//-----------------------------------------------------------------------------
// Public interface
//-----------------------------------------------------------------------------
static bool sReadPNG(const Torque::Path& path, GBitmap* bitmap)
{
   FileStream readPng;
   if (!readPng.open(path.getFullPath(), Torque::FS::File::Read))
   {
      Con::errorf("sReadPNG - Failed to open '%s'.", path.getFullPath().c_str());
      return false;
   }

   bool result = _readStreamPNG(readPng, bitmap, U32_MAX, path.getFullPath().c_str());
   if (!result)
      Con::errorf("sReadPNG - Failed to decode '%s'.", path.getFullPath().c_str());

   readPng.close();
   return result;
}

static bool sWriteStreamPNG(const String& /*bmType*/, Stream& stream, GBitmap* bitmap, U32 compressionLevel)
{
   U32 waterMark = FrameAllocator::getWaterMark();

   if (compressionLevel < 10)
   {
      bool retVal = _writePNG(bitmap, stream, compressionLevel, 0, PNG_ALL_FILTERS);
      FrameAllocator::setWaterMark(waterMark);
      return retVal;
   }

   // check all our methods of compression to find the best one and use it
   U8* buffer = new U8[1 << 22]; // 4 Megs.  Should be enough...
   MemStream* pMemStream = new MemStream(1 << 22, buffer, false, true);

   const U32 zStrategies[] = { Z_DEFAULT_STRATEGY, Z_FILTERED };
   const U32 pngFilters[] = { PNG_FILTER_NONE, PNG_FILTER_SUB, PNG_FILTER_UP,
                                PNG_FILTER_AVG, PNG_FILTER_PAETH, PNG_ALL_FILTERS };

   U32 minSize = U32_MAX, bestCLevel = 0, bestStrategy = 0, bestFilter = 0;

   for (U32 cl = 0; cl <= 9; cl++)
   {
      for (U32 zs = 0; zs < 2; zs++)
      {
         for (U32 pf = 0; pf < 6; pf++)
         {
            pMemStream->setPosition(0);
            U32 waterMarkInner = FrameAllocator::getWaterMark();

            if (!_writePNG(bitmap, *pMemStream, cl, zStrategies[zs], pngFilters[pf]))
            {
               Con::errorf("sWriteStreamPNG - Compression search failed at cl=%d zs=%d pf=%d.", cl, zs, pf);
               FrameAllocator::setWaterMark(waterMarkInner);
               continue;
            }

            FrameAllocator::setWaterMark(waterMarkInner);

            if (pMemStream->getPosition() < minSize)
            {
               minSize = pMemStream->getPosition();
               bestCLevel = cl; bestStrategy = zs; bestFilter = pf;
            }
         }
      }
   }

   delete pMemStream;
   delete[] buffer;

   if (minSize == U32_MAX)
   {
      Con::errorf("sWriteStreamPNG - No valid compression result found.");
      FrameAllocator::setWaterMark(waterMark);
      return false;
   }

   bool retVal = _writePNG(bitmap, stream, bestCLevel, zStrategies[bestStrategy], pngFilters[bestFilter]);
   FrameAllocator::setWaterMark(waterMark);
   return retVal;
}

static bool sWritePNG(const Torque::Path& path, GBitmap* bitmap, U32 compressionLevel)
{
   FileStream writePng;
   if (!writePng.open(path.getFullPath(), Torque::FS::File::Write))
   {
      Con::errorf("sWritePNG - Failed to open '%s' for writing.", path.getFullPath().c_str());
      return false;
   }

   bool retVal = sWriteStreamPNG("png", writePng, bitmap, compressionLevel);
   if (!retVal)
      Con::errorf("sWritePNG - Failed to encode '%s'. Format: %d, Size: %dx%d.",
         path.getFullPath().c_str(), bitmap->getFormat(), bitmap->getWidth(), bitmap->getHeight());

   writePng.close();
   return retVal;
}

static bool sReadStreamPNG(Stream& stream, GBitmap* bitmap, U32 len)
{
   return _readStreamPNG(stream, bitmap, len, "unknown (stream only)");
}

//-----------------------------------------------------------------------------
// DeferredPNGWriter
//-----------------------------------------------------------------------------
struct DeferredPNGWriterData
{
   PngWriteGuard guard;
   U32 width = 0;
   U32 height = 0;

   explicit DeferredPNGWriterData(const char* filename) : guard(filename) {}
};

DeferredPNGWriter::DeferredPNGWriter() : mData(nullptr), mActive(false) {}

DeferredPNGWriter::~DeferredPNGWriter()
{
   delete mData;
}

bool DeferredPNGWriter::begin(GFXFormat format, S32 width, S32 height, Stream& stream, U32 compressionLevel)
{
   if (!_isSupportedWriteFormat(format))
   {
      Con::errorf("DeferredPNGWriter::begin - Unsupported format %d.", format);
      return false;
   }

   mData = new DeferredPNGWriterData("DeferredPNGWriter");

   if (!mData->guard.init(false))
   {
      Con::errorf("DeferredPNGWriter::begin - Failed to init PNG write structs. Format: %d, Size: %dx%d.", format, width, height);
      return false;
   }

   mData->width = width;
   mData->height = height;

   png_set_write_fn(mData->guard.png_ptr, &stream, pngWriteDataFn, pngFlushDataFn);
   png_set_compression_window_bits(mData->guard.png_ptr, 15);
   png_set_compression_level(mData->guard.png_ptr, compressionLevel);
   png_set_filter(mData->guard.png_ptr, 0, PNG_ALL_FILTERS);

   _applyWriteIHDR(mData->guard.png_ptr, mData->guard.info_ptr, format, width, height);
   png_write_info(mData->guard.png_ptr, mData->guard.info_ptr);

   mActive = true;
   return true;
}

void DeferredPNGWriter::append(GBitmap* bitmap, U32 rows)
{
   AssertFatal(mActive, "DeferredPNGWriter::append - Writer is not active.");

   U32 height = getMin(bitmap->getHeight(), rows);
   FrameAllocatorMarker marker;
   png_bytep* row_pointers = (png_bytep*)marker.alloc(height * sizeof(png_bytep));
   for (U32 i = 0; i < height; i++)
      row_pointers[i] = const_cast<png_bytep>(bitmap->getAddress(0, i));

   png_write_rows(mData->guard.png_ptr, row_pointers, height);
}

void DeferredPNGWriter::end()
{
   AssertFatal(mActive, "DeferredPNGWriter::end - Writer is not active.");

   png_write_end(mData->guard.png_ptr, mData->guard.info_ptr);
   mActive = false;
}
