//-----------------------------------------------------------------------------
// Copyright (c) 2020 Alterverse
//-----------------------------------------------------------------------------
#include "core/stream/stream.h"
#include "gfx/bitmap/gBitmap.h"
#include "console/console.h"
#include "gfx/bitmap/imageUtils.h"
#include "math/mMathFn.h"

//NOTE: if upgrading stb_image check stbi__context.buffer_start size, using 128 causes buffer over-run on streams(gFont), we use 16 instead
#define STBI_ONLY_JPEG
#define STBI_ONLY_PNG
#define STBI_ONLY_BMP
#define STBI_ONLY_TGA
#define STBI_NO_STDIO
#define STBI_MALLOC dMalloc
#define STBI_REALLOC dRealloc
#define STBI_FREE dFree
#define STBI_ASSERT(x) AssertFatal(x, "STBI assert")
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STBI_WRITE_NO_STDIO
#define STBIW_MALLOC dMalloc
#define STBIW_REALLOC dRealloc
#define STBIW_FREE dFree
#define STBIW_MEMMOVE dMemmove
#define STBIW_ASSERT(x) AssertFatal(x, "STBW assert")
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

static bool sReadSTB(const String& bmType, Stream& stream, GBitmap* bitmap);
static bool sWriteSTB(const String& bmType, GBitmap *bitmap, Stream &stream, U32 compressionLevel);

static struct _privateRegisterSTB
{
   _privateRegisterSTB()
   {
      GBitmap::Registration reg;

      reg.extensions.push_back("tga");
      reg.extensions.push_back("jpg");
      reg.extensions.push_back("jpeg");
      reg.extensions.push_back("png");
      reg.extensions.push_back("bmp");

      reg.readFunc = sReadSTB;
      reg.writeFunc = sWriteSTB;

      GBitmap::sRegisterFormat(reg);
   }
} sStaticRegisterSTB;

// stb_image callbacks
S32 stbRead(void* user, char* data, S32 size)
{
   Stream* stream = static_cast<Stream*>(user);
   if (stream->read(size, data))
      return size;
   else
      return 0;
}

void stbSkip(void* user, S32 n)
{
   Stream* stream = static_cast<Stream*>(user);
   stream->setPosition(stream->getPosition() + n);
}

S32 stbEof(void* user)
{
   Stream* stream = static_cast<Stream*>(user);
   if (stream->getStatus() == Stream::EOS)
      return 1;
   else
      return 0;
}

static bool sReadSTB(const String& bmType, Stream &stream, GBitmap *bitmap)
{
   PROFILE_SCOPE(sReadSTB);

   //we need to use callbacks so we can use the stream class properly
   stbi_io_callbacks callbacks;
   callbacks.read = &stbRead;
   callbacks.skip = &stbSkip;
   callbacks.eof = &stbEof;

   //store the starting position within the stream
   U32 streamStart = stream.getPosition();
   //get image info
   S32 width, height, bpp;
   if (!stbi_info_from_callbacks(&callbacks, &stream, &width, &height, &bpp))
   {
      Con::errorf("STB failed to get image info: %s", stbi_failure_reason());
      return false;
   }

   //set stream back to starting position
   stream.setPosition(streamStart);

   //load the image
   S32 channels = bpp;
   U8* pImageData = stbi_load_from_callbacks(&callbacks, &stream, &width, &height, &bpp, channels);
   if (!pImageData)
   {
      Con::printf("STB loading failed: %s", stbi_failure_reason());
      return false;
   }

   //work out what format we need to use - todo floating point?
   GFXFormat fmt = GFXFormat_FIRST;
   switch (bpp)
   {
   case 1: fmt = GFXFormatA8; break;
   case 2: fmt = GFXFormatA8L8; break; //todo check this
   case 3: fmt = GFXFormatR8G8B8; break;
   case 4: fmt = GFXFormatR8G8B8A8; break;
   }

   //allocate the bitmap
   bitmap->allocateBitmap(width, height, false, fmt);

   //copy the pixel data
   U8* pDst = bitmap->getWritableBits(0);
   dMemcpy(pDst, pImageData, bitmap->getByteSize());

   //free image data
   stbi_image_free(pImageData);
   //set transparency
   bitmap->setHasTransparency(bpp == 4);
   //happy days :)
   return true;
}

//stbi_write callback
static void stbiWriteFunc(void* context, void* data, int size)
{
   Stream* stream = static_cast<Stream*>(context);
   stream->write(size, data);
}

//compressionLevel is only valid for jpg|jpeg. compressionLevel is between 1 and 100. Higher quality looks better but results in a larger image(storage size).
static bool sWriteSTB(const String& bmType, GBitmap *bitmap, Stream &stream, U32 compressionLevel)
{
   PROFILE_SCOPE(sWriteSTB);

   S32 width = bitmap->getWidth();
   S32 height = bitmap->getHeight();
   const U8* pPixelData = bitmap->getBits();
   S32 channels = bitmap->getBytesPerPixel();

   if (bmType == String("png"))
   {
      if (stbi_write_png_to_func(stbiWriteFunc, &stream, width, height, channels, pPixelData, width * channels))
      {
         return true;
      }
   }
   else if (bmType == String("tga"))
   {
      if (stbi_write_tga_to_func(stbiWriteFunc, &stream, width, height, channels, pPixelData))
      {
         return true;
      }
   }
   else if (bmType == String("jpg") || bmType == String("jpeg"))
   {
      if (stbi_write_jpg_to_func(stbiWriteFunc, &stream, width, height, channels, pPixelData, mClamp((S32)compressionLevel, 1, 100)))
      {
         return true;
      }
   }
   else if (bmType == String("bmp"))
   {
      if (stbi_write_bmp_to_func(stbiWriteFunc, &stream, width, height, channels, pPixelData))
      {
         return true;
      }
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

   const U32 height = getMin(bitmap->getHeight(), rows);
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
