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
#include "gfx/bitmap/gBitmap.h"

#include "core/resourceManager.h"
#include "core/stream/fileStream.h"
#include "core/strings/stringFunctions.h"
#include "core/color.h"
#include "gfx/bitmap/bitmapUtils.h"
#include "math/mRect.h"
#include "console/console.h"
#include "platform/profiler.h"
#include "console/engineAPI.h"
#include "gfx/bitmap/ddsFile.h"

using namespace Torque;

// Version 5 switches the on-disk layout to a sequence of self-contained
// per-face blocks (GBitmap::Face::write()/read()), replacing the old
// single-contiguous-buffer-plus-face-offsets layout
const U32 GBitmap::csFileVersion = 5;

Vector<GBitmap::Registration>& GBitmap::getRegistrations()
{
   static Vector<GBitmap::Registration>* regs =
      new Vector<GBitmap::Registration>(__FILE__, __LINE__);

   return *regs;
}

//-----------------------------------------------------------------------------
// GBitmap::Face
//-----------------------------------------------------------------------------

GBitmap::Face::Face()
   : mBits(NULL),
   mByteSize(0),
   mWidth(0),
   mHeight(0),
   mBytesPerPixel(0),
   mNumMipLevels(0)
{
   dMemset(mMipLevelOffsets, 0, sizeof(mMipLevelOffsets));
}

GBitmap::Face::Face(const Face& copy)
   : mBits(NULL),
   mByteSize(copy.mByteSize),
   mWidth(copy.mWidth),
   mHeight(copy.mHeight),
   mBytesPerPixel(copy.mBytesPerPixel),
   mNumMipLevels(copy.mNumMipLevels)
{
   dMemcpy(mMipLevelOffsets, copy.mMipLevelOffsets, sizeof(mMipLevelOffsets));

   if (copy.mBits != NULL)
   {
      mBits = new U8[mByteSize];
      dMemcpy(mBits, copy.mBits, mByteSize);
   }
}

GBitmap::Face::~Face()
{
   delete[] mBits;
}

GBitmap::Face& GBitmap::Face::operator=(const Face& copy)
{
   if (this == &copy)
      return *this;

   delete[] mBits;
   mBits = NULL;

   mByteSize = copy.mByteSize;
   mWidth = copy.mWidth;
   mHeight = copy.mHeight;
   mBytesPerPixel = copy.mBytesPerPixel;
   mNumMipLevels = copy.mNumMipLevels;
   dMemcpy(mMipLevelOffsets, copy.mMipLevelOffsets, sizeof(mMipLevelOffsets));

   if (copy.mBits != NULL)
   {
      mBits = new U8[mByteSize];
      dMemcpy(mBits, copy.mBits, mByteSize);
   }

   return *this;
}

void GBitmap::Face::deleteImage()
{
   delete[] mBits;
   mBits = NULL;
   mByteSize = 0;
   mWidth = 0;
   mHeight = 0;
   mNumMipLevels = 0;
}

void GBitmap::Face::allocate(const U32 in_width, const U32 in_height, const U32 in_numMips, const U32 in_bytesPerPixel)
{
   AssertFatal(in_width != 0 && in_height != 0, "GBitmap::Face::allocate: width or height is 0");

   U8* svBits = mBits;
   U32  svByteSize = mByteSize;

   mWidth = in_width;
   mHeight = in_height;
   mBytesPerPixel = in_bytesPerPixel;

   mNumMipLevels = 1;
   mMipLevelOffsets[0] = 0;

   U32 currWidth = in_width;
   U32 currHeight = in_height;

   // in_numMips == 0 means "build the full pyramid down to 1x1", otherwise
   // build exactly in_numMips levels (fewer if the chain hits 1x1 first).
   while ((currWidth != 1 || currHeight != 1) &&
      (in_numMips == 0 || mNumMipLevels < in_numMips))
   {
      mMipLevelOffsets[mNumMipLevels] = mMipLevelOffsets[mNumMipLevels - 1] +
         (currWidth * currHeight * mBytesPerPixel);
      currWidth >>= 1;
      currHeight >>= 1;
      if (currWidth == 0) currWidth = 1;
      if (currHeight == 0) currHeight = 1;

      mNumMipLevels++;
   }

   AssertFatal(mNumMipLevels <= c_maxMipLevels, "GBitmap::Face::allocate: too many miplevels");

   mByteSize = 0;
   for (U32 mip = 0; mip < mNumMipLevels; mip++)
      mByteSize += getWidth(mip) * getHeight(mip) * mBytesPerPixel;

   mBits = new U8[mByteSize];
   dMemset(mBits, 0xFF, mByteSize);

   if (svBits != NULL)
   {
      dMemcpy(mBits, svBits, getMin(mByteSize, svByteSize));
      delete[] svBits;
   }
}

U32 GBitmap::Face::getWidth(const U32 mipLevel) const
{
   AssertFatal(mipLevel < mNumMipLevels,
      avar("GBitmap::Face::getWidth: mip level out of range: (%d, %d)",
         mipLevel, mNumMipLevels));

   U32 retVal = mWidth >> mipLevel;
   return (retVal != 0) ? retVal : 1;
}

U32 GBitmap::Face::getHeight(const U32 mipLevel) const
{
   AssertFatal(mipLevel < mNumMipLevels,
      avar("GBitmap::Face::getHeight: mip level out of range: (%d, %d)",
         mipLevel, mNumMipLevels));

   U32 retVal = mHeight >> mipLevel;
   return (retVal != 0) ? retVal : 1;
}

const U8* GBitmap::Face::getBits(const U32 mipLevel) const
{
   AssertFatal(mipLevel < mNumMipLevels,
      avar("GBitmap::Face::getBits: mip level out of range: (%d, %d)",
         mipLevel, mNumMipLevels));

   return &mBits[mMipLevelOffsets[mipLevel]];
}

U8* GBitmap::Face::getWritableBits(const U32 mipLevel)
{
   AssertFatal(mipLevel < mNumMipLevels,
      avar("GBitmap::Face::getWritableBits: mip level out of range: (%d, %d)",
         mipLevel, mNumMipLevels));

   return &mBits[mMipLevelOffsets[mipLevel]];
}

U8* GBitmap::Face::getAddress(const S32 x, const S32 y, const U32 mipLevel)
{
   return getWritableBits(mipLevel) + (U64)(((y * getWidth(mipLevel)) + x) * mBytesPerPixel);
}

const U8* GBitmap::Face::getAddress(const S32 x, const S32 y, const U32 mipLevel) const
{
   return getBits(mipLevel) + ((y * getWidth(mipLevel)) + x) * mBytesPerPixel;
}

void GBitmap::Face::convertFormat(GFXFormat oldFmt, GFXFormat newFmt, U32 newBytesPerPixel)
{
   // this is a nasty pointer math hack
   // is there a quick way to calc pixels of a fully mipped bitmap?
   U32 pixels = 0;
   for (U32 i = 0; i < mNumMipLevels; i++)
      pixels += getWidth(i) * getHeight(i);

   if (oldFmt == GFXFormatR8G8B8 && newFmt == GFXFormatR5G5B5A1)
   {
#ifdef _XBOX
      bitmapConvertRGB_to_1555(mBits, pixels);
#else
      bitmapConvertRGB_to_5551(mBits, pixels);
#endif
   }
   else
   {
      bitmapConvertToOutput(&mBits, pixels, oldFmt, newFmt);
   }

   mBytesPerPixel = newBytesPerPixel;

   U32 offset = 0;
   for (U32 j = 0; j < mNumMipLevels; j++)
   {
      mMipLevelOffsets[j] = offset;
      offset += getWidth(j) * getHeight(j) * mBytesPerPixel;
   }
   mByteSize = offset;
}

void GBitmap::Face::chopTopMips(const U32 scalePower)
{
   if (scalePower == 0)
      return;

   AssertFatal(scalePower < mNumMipLevels, "GBitmap::Face::chopTopMips: scalePower out of range");

   U32 newWidth = getMax((U32)1, mWidth >> scalePower);
   U32 newHeight = getMax((U32)1, mHeight >> scalePower);
   U32 newMipCount = mNumMipLevels - scalePower;

   U32 newByteSize = 0;
   for (U32 i = scalePower; i < mNumMipLevels; i++)
      newByteSize += getWidth(i) * getHeight(i) * mBytesPerPixel;

   // Allocate fresh (rather than compacting in place) - since this face
   // owns its own memory independently of every other face there's no
   // cross-face bookkeeping to worry about, and a fresh allocation sidesteps
   // any concern about overlapping src/dest ranges during compaction.
   U8* newBits = new U8[newByteSize];
   U32 newOffsets[c_maxMipLevels];

   U8* dest = newBits;
   for (U32 i = scalePower; i < mNumMipLevels; i++)
   {
      U32 surfaceSize = getWidth(i) * getHeight(i) * mBytesPerPixel;
      dMemcpy(dest, getWritableBits(i), surfaceSize);
      newOffsets[i - scalePower] = dest - newBits;
      dest += surfaceSize;
   }

   delete[] mBits;
   mBits = newBits;
   mByteSize = newByteSize;
   mWidth = newWidth;
   mHeight = newHeight;
   mNumMipLevels = newMipCount;
   dMemcpy(mMipLevelOffsets, newOffsets, sizeof(newOffsets));
}

bool GBitmap::Face::write(Stream& s) const
{
   s.write(mWidth);
   s.write(mHeight);
   s.write(mBytesPerPixel);
   s.write(mNumMipLevels);
   for (U32 i = 0; i < c_maxMipLevels; i++)
      s.write(mMipLevelOffsets[i]);
   s.write(mByteSize);
   s.write(mByteSize, mBits);

   return (s.getStatus() == Stream::Ok);
}

bool GBitmap::Face::read(Stream& s)
{
   s.read(&mWidth);
   s.read(&mHeight);
   s.read(&mBytesPerPixel);
   s.read(&mNumMipLevels);
   for (U32 i = 0; i < c_maxMipLevels; i++)
      s.read(&mMipLevelOffsets[i]);
   s.read(&mByteSize);

   delete[] mBits;
   mBits = new U8[mByteSize];
   s.read(mByteSize, mBits);

   return (s.getStatus() == Stream::Ok);
}

//-----------------------------------------------------------------------------
// GBitmap
//-----------------------------------------------------------------------------

GBitmap::GBitmap()
   : mInternalFormat(GFXFormatR8G8B8),
   mBytesPerPixel(0),
   mHasTransparency(false)
{
   VECTOR_SET_ASSOCIATION(mFaces);
   mFaces.setSize(1); // always at least one (possibly empty) face
}

GBitmap::GBitmap(const GBitmap& rCopy)
   : mInternalFormat(rCopy.mInternalFormat),
   mBytesPerPixel(rCopy.mBytesPerPixel),
   mFaces(rCopy.mFaces),
   mHasTransparency(rCopy.mHasTransparency)
{
   VECTOR_SET_ASSOCIATION(mFaces);
}

GBitmap& GBitmap::operator=(const GBitmap& rCopy)
{
   if (this == &rCopy)
      return *this;

   // NOTE: previously GBitmap had a custom copy constructor but relied
   // on the compiler-generated copy-assignment operator, which did a
   // shallow member-wise copy of the raw mBits pointer - two bitmaps
   // could end up owning (and separately freeing) the same buffer.
   // Now that each Face owns its memory via RAII and Vector<Face> has
   // real copy semantics, a plain member-wise copy here is correct.
   mInternalFormat = rCopy.mInternalFormat;
   mBytesPerPixel = rCopy.mBytesPerPixel;
   mHasTransparency = rCopy.mHasTransparency;
   mFaces = rCopy.mFaces;

   return *this;
}

GBitmap::GBitmap(const U32  in_width,
   const U32  in_height,
   const bool in_extrudeMipLevels,
   const GFXFormat in_format,
   const U32 in_numFaces)
   : mInternalFormat(GFXFormatR8G8B8),
   mBytesPerPixel(0),
   mHasTransparency(false)
{
   VECTOR_SET_ASSOCIATION(mFaces);
   allocateBitmap(in_width, in_height, in_extrudeMipLevels, in_format, in_numFaces);
}

GBitmap::GBitmap(const U32  in_width,
   const U32  in_height,
   const U8* data,
   const U32 in_numFaces)
   : mInternalFormat(GFXFormatR8G8B8),
   mBytesPerPixel(0),
   mHasTransparency(false)
{
   VECTOR_SET_ASSOCIATION(mFaces);
   allocateBitmap(in_width, in_height, false, GFXFormatR8G8B8A8, in_numFaces);

   for (U32 x = 0; x < in_width; x++)
   {
      for (U32 y = 0; y < in_height; y++)
      {
         U32 offset = (x + y * in_width) * 4;

         ColorI color(data[offset],
            data[offset + 1],
            data[offset + 2],
            data[offset + 3]);

         if (color.alpha < 255)
            mHasTransparency = true;

         setColor(x, y, color);
      }
   }
}


//--------------------------------------------------------------------------

GBitmap::~GBitmap()
{
   deleteImage();
}

//--------------------------------------------------------------------------

U32 GBitmap::getFormatBytesPerPixel(GFXFormat fmt)
{
   switch (fmt)
   {
      // 8-bit formats
   case GFXFormatA8:
   case GFXFormatL8:
   case GFXFormatA4L4:
      return 1;

      // 16-bit formats
   case GFXFormatR5G6B5:
   case GFXFormatR5G5B5A1:
   case GFXFormatR5G5B5X1:
   case GFXFormatA8L8:
   case GFXFormatL16:
   case GFXFormatR16F:
   case GFXFormatD16:
      return 2;

      // 24-bit formats
   case GFXFormatR8G8B8:
   case GFXFormatR8G8B8_SRGB:
      return 3;

      // 32-bit formats
   case GFXFormatR8G8B8A8:
   case GFXFormatR8G8B8X8:
   case GFXFormatB8G8R8A8:
   case GFXFormatR8G8B8A8_SRGB:
   case GFXFormatR32F:
   case GFXFormatR10G10B10A2:
   case GFXFormatR11G11B10:
   case GFXFormatD24X8:
   case GFXFormatD24S8:
   case GFXFormatD24FS8:
   case GFXFormatR16G16:
   case GFXFormatR16G16F:
   case GFXFormatR8G8B8A8_LINEAR_FORCE:
      return 4;

      // 64-bit formats
   case GFXFormatR16G16B16A16:
   case GFXFormatR16G16B16A16F:
   case GFXFormatD32FS8X24:
      return 8;

      // 128-bit formats
   case GFXFormatR32G32B32A32F:
      return 16;

   default:
      AssertWarn(false, "getFormatBytesPerPixel() - Unknown or compressed format");
      return 4;
   }
}

//--------------------------------------------------------------------------

void GBitmap::sRegisterFormat(const GBitmap::Registration& reg)
{
   U32 insert = GBitmap::getRegistrations().size();
   for (U32 i = 0; i < GBitmap::getRegistrations().size(); i++)
   {
      if (GBitmap::getRegistrations()[i].priority <= reg.priority)
      {
         insert = i;
         break;
      }
   }

   GBitmap::getRegistrations().insert(insert, reg);
}

const GBitmap::Registration* GBitmap::sFindRegInfo(const String& extension)
{
   for (U32 i = 0; i < GBitmap::getRegistrations().size(); i++)
   {
      const GBitmap::Registration& reg = GBitmap::getRegistrations()[i];
      const Vector<String>& extensions = reg.extensions;

      for (U32 j = 0; j < extensions.size(); ++j)
      {
         if (extensions[j].equal(extension, String::NoCase))
            return &reg;
      }
   }

   return NULL;
}

bool GBitmap::sFindFile(const Path& path, Path* outPath)
{
   PROFILE_SCOPE(GBitmap_sFindFile);

   const String origExt(String::ToLower(path.getExtension()));

   Path tryPath(path);

   for (U32 i = 0; i < GBitmap::getRegistrations().size(); i++)
   {
      const Registration& reg = GBitmap::getRegistrations()[i];
      const Vector<String>& extensions = reg.extensions;

      for (U32 j = 0; j < extensions.size(); ++j)
      {
         // We've already tried this one.
         if (extensions[j] == origExt)
            continue;

         tryPath.setExtension(extensions[j]);
         if (!Torque::FS::IsFile(tryPath))
            continue;

         if (outPath)
            *outPath = tryPath;
         return true;
      }
   }

   return false;
}

bool GBitmap::sFindFiles(const Path& path, Vector<Path>* outFoundPaths)
{
   PROFILE_SCOPE(GBitmap_sFindFiles);

   Path  tryPath(path);

   for (U32 i = 0; i < GBitmap::getRegistrations().size(); i++)
   {
      const GBitmap::Registration& reg = GBitmap::getRegistrations()[i];
      const Vector<String>& extensions = reg.extensions;

      for (U32 j = 0; j < extensions.size(); ++j)
      {
         tryPath.setExtension(extensions[j]);

         if (Torque::FS::IsFile(tryPath))
         {
            if (outFoundPaths)
               outFoundPaths->push_back(tryPath);
            else
               return true;
         }
      }
   }

   return outFoundPaths ? outFoundPaths->size() > 0 : false;
}

String GBitmap::sGetExtensionList()
{
   String list;

   for (U32 i = 0; i < GBitmap::getRegistrations().size(); i++)
   {
      const Registration& reg = GBitmap::getRegistrations()[i];
      for (U32 j = 0; j < reg.extensions.size(); j++)
      {
         list += reg.extensions[j];
         list += " ";
      }
   }

   return list;
}

//--------------------------------------------------------------------------
void GBitmap::deleteImage()
{
   // Collapse back down to the one-empty-face invariant every other
   // method relies on (see mFaces' declaration comment).
   mFaces.setSize(1);
   mFaces[0].deleteImage();
}


//--------------------------------------------------------------------------

void GBitmap::copyRect(const GBitmap* src, const RectI& srcRect, const Point2I& dstPt, const U32 srcMipLevel, const U32 dstMipLevel)
{
   if (src->getFormat() != getFormat())
      return;
   if (srcRect.extent.x + srcRect.point.x > src->getWidth(srcMipLevel) || srcRect.extent.y + srcRect.point.y > src->getHeight(srcMipLevel))
      return;
   if (srcRect.extent.x + dstPt.x > getWidth(dstMipLevel) || srcRect.extent.y + dstPt.y > getHeight(dstMipLevel))
      return;

   for (U32 i = 0; i < srcRect.extent.y; i++)
   {
      dMemcpy(getAddress(dstPt.x, dstPt.y + i, dstMipLevel),
         src->getAddress(srcRect.point.x, srcRect.point.y + i, srcMipLevel),
         mBytesPerPixel * srcRect.extent.x);
   }
}

//--------------------------------------------------------------------------
void GBitmap::allocateBitmap(const U32 in_width, const U32 in_height, const bool in_extrudeMipLevels, const GFXFormat in_format, const U32 in_numFaces)
{
   if (in_extrudeMipLevels == true)
   {
      AssertFatal(isPow2(in_width) == true && isPow2(in_height) == true, "GBitmap::allocateBitmap: in order to extrude mip levels, bitmap w/h must be pow2");
   }

   // A full mip chain (0) if extruding, otherwise just the base level (1).
   allocateBitmapWithMips(in_width, in_height, in_extrudeMipLevels ? 0 : 1, in_format, in_numFaces);

   if (in_extrudeMipLevels == true)
   {
      U32 expectedMips = mFloor(mLog2(mMax(in_width, in_height))) + 1;
      AssertFatal(getNumMipLevels() == expectedMips, "GBitmap::allocateBitmap: mipmap count wrong");
   }
}

//--------------------------------------------------------------------------
void GBitmap::allocateBitmapWithMips(const U32 in_width, const U32 in_height, const U32 in_numMips, const GFXFormat in_format, const U32 in_numFaces)
{
   AssertFatal(in_width != 0 && in_height != 0, "GBitmap::allocateBitmapWithMips: width or height is 0");
   AssertFatal(in_numFaces >= 1, "GBitmap::allocateBitmapWithMips: in_numFaces must be at least 1");

   mInternalFormat = in_format;
   mBytesPerPixel = getFormatBytesPerPixel(mInternalFormat);

   mFaces.setSize(in_numFaces);

   for (U32 i = 0; i < in_numFaces; i++)
      mFaces[i].allocate(in_width, in_height, in_numMips, mBytesPerPixel);
}

//--------------------------------------------------------------------------
void GBitmap::extrudeMipLevels(bool clearBorders)
{
   if (getNumMipLevels() == 1)
      // NOTE: previously this omitted getNumFaces(), so calling
      // extrudeMipLevels() on a cubemap with only 1 mip level would
      // silently reallocate it as a plain 2D (1-face) image.
      allocateBitmap(getWidth(), getHeight(), true, getFormat(), getNumFaces());

   for (U32 faceIndex = 0; faceIndex < getNumFaces(); faceIndex++)
   {
      Face& face = mFaces[faceIndex];
      const U32 numMips = face.getNumMipLevels();

      if (getFormat() == GFXFormatR5G5B5A1)
      {
         for (U32 i = 1; i < numMips; i++)
            bitmapExtrude5551(face.getBits(i - 1), face.getWritableBits(i), face.getHeight(i), face.getWidth(i));
      }
      else
      {
         for (U32 i = 1; i < numMips; i++)
         {
            bitmapResizeToOutput(
               face.getBits(i - 1),
               face.getHeight(i - 1),
               face.getWidth(i - 1),
               face.getWritableBits(i),
               face.getHeight(i),
               face.getWidth(i),
               mBytesPerPixel,
               getFormat()
            );
         }
      }

      if (clearBorders)
      {
         for (U32 i = 1; i < numMips; i++)
         {
            U32 width = face.getWidth(i);
            U32 height = face.getHeight(i);
            if (height < 3 || width < 3)
               // bmp is all borders at this mip level
               dMemset(face.getWritableBits(i), 0, width * height * mBytesPerPixel);
            else
            {
               width *= mBytesPerPixel;
               U8* bytes = face.getWritableBits(i);
               U8* end = bytes + (height - 1) * width - mBytesPerPixel; // end = last row, 2nd column
               // clear first row sans the last pixel
               dMemset(bytes, 0, width - mBytesPerPixel);
               bytes -= mBytesPerPixel;
               while (bytes < end)
               {
                  // clear last pixel of row N-1 and first pixel of row N
                  bytes += width;
                  dMemset(bytes, 0, mBytesPerPixel * 2);
               }
               // clear last row sans the first pixel
               dMemset(bytes + 2 * mBytesPerPixel, 0, width - mBytesPerPixel);
            }
         }
      }
   }
}

//--------------------------------------------------------------------------
void GBitmap::chopTopMips(U32 mipsToChop)
{
   U32 scalePower = getMin(mipsToChop, getNumMipLevels() - 1);

   // Each face now owns its own memory independently, so chopping mips
   // is just a per-face operation - see GBitmap::Face::chopTopMips().
   for (U32 i = 0; i < getNumFaces(); i++)
      mFaces[i].chopTopMips(scalePower);
}

//--------------------------------------------------------------------------
void GBitmap::extrudeMipLevelsDetail()
{
   AssertFatal(getFormat() == GFXFormatR8G8B8, "Error, only handles RGB for now...");

   if (getNumMipLevels() == 1)
      allocateBitmap(getWidth(), getHeight(), true, getFormat(), getNumFaces());

   for (U32 faceIndex = 0; faceIndex < getNumFaces(); faceIndex++)
   {
      Face& face = mFaces[faceIndex];
      const U32 numMips = face.getNumMipLevels();
      U32 i, j;

      for (i = 1; i < numMips; i++) {
         bitmapExtrudeRGB(face.getBits(i - 1), face.getWritableBits(i), face.getHeight(i - 1), face.getWidth(i - 1), mBytesPerPixel);
      }

      // Ok, now that we have the levels extruded, we need to move the lower miplevels
      //  closer to 0.5.
      for (i = 1; i < numMips - 1; i++) {
         U8* pMipBits = face.getWritableBits(i);
         U32 numBytes = face.getWidth(i) * face.getHeight(i) * 3;

         U32 shift = i;
         U32 start = ((1 << i) - 1) * 0x80;

         for (j = 0; j < numBytes; j++) {
            U32 newVal = (start + pMipBits[j]) >> shift;
            AssertFatal(newVal <= 255, "Error, oob");
            pMipBits[j] = U8(newVal);
         }
      }
      AssertFatal(face.getWidth(numMips - 1) == 1 && face.getHeight(numMips - 1) == 1,
         "Error, last miplevel should be 1x1!");
      U8* lastMip = face.getWritableBits(numMips - 1);
      lastMip[0] = 0x80;
      lastMip[1] = 0x80;
      lastMip[2] = 0x80;
   }
}

//--------------------------------------------------------------------------
bool GBitmap::setFormat(GFXFormat fmt)
{
   if (getFormat() == fmt)
      return true;

   PROFILE_SCOPE(GBitmap_setFormat);

   // NOTE: previously this converted mBits as one contiguous buffer
   // sized from a single face's pixel count, so calling setFormat() on
   // a cubemap silently reformatted only the first face and left the
   // other 5 in the old format. Each face now converts independently.
   const GFXFormat oldFmt = mInternalFormat;
   const U32 newBytesPerPixel = getFormatBytesPerPixel(fmt);

   for (U32 i = 0; i < getNumFaces(); i++)
      mFaces[i].convertFormat(oldFmt, fmt, newBytesPerPixel);

   mInternalFormat = fmt;
   mBytesPerPixel = newBytesPerPixel;

   return true;
}

//------------------------------------------------------------------------------

bool GBitmap::checkForTransparency()
{
   mHasTransparency = false;

   if (getFaceByteSize() == 0)
      return false;

   ColorI pixel(255, 255, 255, 255);

   // Only check formats that can *possibly* have alpha.
   switch (mInternalFormat)
   {
   case GFXFormatA8:
   case GFXFormatA4L4:
   case GFXFormatA8L8:
   case GFXFormatR5G5B5A1:
   case GFXFormatR8G8B8A8:
   case GFXFormatB8G8R8A8:
   case GFXFormatR8G8B8A8_SRGB:
   case GFXFormatR10G10B10A2:
   case GFXFormatR16G16B16A16:
   case GFXFormatR16G16B16A16F:
   case GFXFormatR32G32B32A32F:
      break; // alpha-capable
   default:
      return false; // skip formats with no alpha
   }

   // NOTE: this only checks face 0 / mip 0, same as before - a cubemap
   // whose transparency lives only on another face will still be missed.
   // Not addressed here; see getColor()/setColor() for the face-aware
   // convenience overloads if you need to check every face.
   for (U32 x = 0; x < getWidth(); x++)
   {
      for (U32 y = 0; y < getHeight(); y++)
      {
         if (getColor(x, y, pixel))
         {
            if (pixel.alpha < 255)
            {
               mHasTransparency = true;
               break;
            }
         }
      }
   }

   return mHasTransparency;
}

//------------------------------------------------------------------------------
LinearColorF GBitmap::sampleTexel(F32 u, F32 v, bool retAlpha) const
{
   LinearColorF col(0.5f, 0.5f, 0.5f);
   // normally sampling wraps all the way around at 1.0,
   // but locking doesn't support this, and we seem to calc
   // the uv based on a clamped 0 - 1...
   Point2F max((F32)(getWidth() - 1), (F32)(getHeight() - 1));
   Point2F posf;
   posf.x = mClampF(((u)*max.x), 0.0f, max.x);
   posf.y = mClampF(((v)*max.y), 0.0f, max.y);
   Point2I posi((S32)posf.x, (S32)posf.y);

   const U8* buffer = getBits();
   U32 lexelindex = ((posi.y * getWidth()) + posi.x) * mBytesPerPixel;

   if (mBytesPerPixel == 2)
   {
      //U16 *buffer = (U16 *)lockrect->pBits;
   }
   else if (mBytesPerPixel > 2)
   {
      col.red = F32(buffer[lexelindex + 0]) / 255.0f;
      col.green = F32(buffer[lexelindex + 1]) / 255.0f;
      col.blue = F32(buffer[lexelindex + 2]) / 255.0f;
      if (retAlpha)
      {
         if (getHasTransparency())
            col.alpha = F32(buffer[lexelindex + 3]) / 255.0f;
         else
            col.alpha = 1.0f;
      }
   }

   return col;
}

//--------------------------------------------------------------------------
bool GBitmap::getColor(const U32 x, const U32 y, ColorI& rColor, const U32 mipLevel, const U32 face) const
{
   // NOTE: previously these clamps used "getNumMipLevels() < mipLevel" /
   // "getNumFaces() < face", which is off-by-one - passing exactly
   // getNumMipLevels() (or getNumFaces()) as an index fell through
   // unclamped instead of being pulled back to the last valid index.
   const U32 targMip = (mipLevel >= getNumMipLevels()) ? getNumMipLevels() - 1 : mipLevel;
   const U32 targFace = (face >= getNumFaces()) ? getNumFaces() - 1 : face;

   // Bounds-check against the *target mip's* dimensions, not the base
   // (mip 0) width/height - a higher mip level is smaller, so checking
   // against mWidth/mHeight let out-of-range x/y through and read past
   // the end of that mip's surface.
   if (x >= getWidth(targMip) || y >= getHeight(targMip))
      return false;

   const U8* p = getAddress(x, y, targMip, targFace);

   switch (mInternalFormat)
   {
      // --- 8-bit ---
   case GFXFormatA8:
      rColor.set(255, 255, 255, p[0]);
      break;

   case GFXFormatL8:
      rColor.set(p[0], p[0], p[0], 255);
      break;

   case GFXFormatA4L4:
   {
      U8 v = p[0];
      U8 lum = (v & 0x0F) * 17;
      U8 alp = ((v >> 4) & 0x0F) * 17;
      rColor.set(lum, lum, lum, alp);
      break;
   }

   // --- 16-bit ---
   case GFXFormatR5G6B5:
   {
      U16 c = ((U16*)p)[0];
#ifdef TORQUE_BIG_ENDIAN
      c = convertLEndianToHost(c);
#endif
      U8 r = (c >> 11) & 0x1F;
      U8 g = (c >> 5) & 0x3F;
      U8 b = c & 0x1F;
      rColor.set((r << 3) | (r >> 2),
         (g << 2) | (g >> 4),
         (b << 3) | (b >> 2),
         255);
      break;
   }

   case GFXFormatR5G5B5A1:
   {
      U16 c = ((U16*)p)[0];
#ifdef TORQUE_BIG_ENDIAN
      c = convertLEndianToHost(c);
#endif
      U8 r = (c >> 11) & 0x1F;
      U8 g = (c >> 6) & 0x1F;
      U8 b = (c >> 1) & 0x1F;
      U8 a = (c & 0x01) ? 255 : 0;
      rColor.set((r << 3) | (r >> 2),
         (g << 3) | (g >> 2),
         (b << 3) | (b >> 2),
         a);
      break;
   }

   case GFXFormatA8L8:
   {
      U16 c = ((U16*)p)[0];
#ifdef TORQUE_BIG_ENDIAN
      c = convertLEndianToHost(c);
#endif
      U8 l = c & 0xFF;
      U8 a = (c >> 8) & 0xFF;
      rColor.set(l, l, l, a);
      break;
   }

   case GFXFormatL16:
   {
      U16 l = ((U16*)p)[0];
#ifdef TORQUE_BIG_ENDIAN
      l = convertLEndianToHost(l);
#endif
      rColor.set(convert16To8(l), convert16To8(l), convert16To8(l), 255);
      break;
   }
   case GFXFormatR16F:
   {
      const U16* v = (U16*)p;
      rColor.set(
         floatTo8(convertHalfToFloat(v[0])),
         0,
         0,
         255
      );
      break;
   }

   // --- 24-bit ---
   case GFXFormatR8G8B8:
   case GFXFormatR8G8B8_SRGB:
      rColor.set(p[0], p[1], p[2], 255);
      break;

      // --- 32-bit ---
   case GFXFormatR32F:
   {
      const F32* v = (F32*)p;
      rColor.set(
         floatTo8(v[0]), // red
         0,                                      // green
         0,                                      // blue
         255                                     // alpha
      );
      break;
   }
   case GFXFormatR16G16:
   {
      const U16* v = (U16*)p;
#ifdef TORQUE_BIG_ENDIAN
      U16 r = convertLEndianToHost(v[0]);
      U16 g = convertLEndianToHost(v[1]);
#else
      U16 r = v[0];
      U16 g = v[1];
#endif
      rColor.set(
         convert16To8(r),    // red
         convert16To8(g),    // green
         0,             // blue
         255            // alpha
      );
      break;
   }
   case GFXFormatR16G16F:
   {
      const U16* v = (U16*)p;
      rColor.set(
         floatTo8(convertHalfToFloat(v[0])),
         floatTo8(convertHalfToFloat(v[1])),
         0,
         255
      );
      break;
   }

   case GFXFormatR8G8B8A8:
   case GFXFormatR8G8B8A8_SRGB:
   case GFXFormatR8G8B8X8:
      rColor.set(p[0], p[1], p[2], (mInternalFormat == GFXFormatR8G8B8X8) ? 255 : p[3]);
      break;

   case GFXFormatB8G8R8A8:
      rColor.set(p[2], p[1], p[0], p[3]);
      break;

      // --- 64-bit ---
   case GFXFormatR16G16B16A16:
   {
      const U16* v = (U16*)p;
#ifdef TORQUE_BIG_ENDIAN
      rColor.set(
         convert16To8(v[2]),
         convert16To8(v[1]),
         convert16To8(v[0]),
         convert16To8(v[3]));
#else
      rColor.set(
         convert16To8(v[0]),
         convert16To8(v[1]),
         convert16To8(v[2]),
         convert16To8(v[3]));
#endif
      break;
   }

   case GFXFormatR16G16B16A16F:
   {
      const U16* v = (const U16*)p;
      rColor.set(floatTo8(
         convertHalfToFloat(v[0])),
         floatTo8(convertHalfToFloat(v[1])),
         floatTo8(convertHalfToFloat(v[2])),
         floatTo8(convertHalfToFloat(v[3])));
      break;
   }

   // --- 128-bit ---
   case GFXFormatR32G32B32A32F:
   {
      const F32* v = (const F32*)p;
      rColor.set(
         floatTo8(v[0]),
         floatTo8(v[1]),
         floatTo8(v[2]),
         floatTo8(v[3]));
      break;
   }

   default:
      AssertFatal(false, "Bad internal format");
      return false;
   }

   return true;
}


//--------------------------------------------------------------------------


bool GBitmap::setColor(const U32 x, const U32 y, const ColorI& rColor, const U32 mipLevel, const U32 face)
{
   const U32 targMip = (mipLevel >= getNumMipLevels()) ? getNumMipLevels() - 1 : mipLevel;
   const U32 targFace = (face >= getNumFaces()) ? getNumFaces() - 1 : face;

   if (x >= getWidth(targMip) || y >= getHeight(targMip))
      return false;

   U8* p = getAddress(x, y, targMip, targFace);

   switch (mInternalFormat)
   {

      // --- 8-bit ---
   case GFXFormatA8:
      *p = rColor.alpha;
      break;

   case GFXFormatL8:
      *p = rColor.red; // L = R channel
      break;

   case GFXFormatA4L4:
   {
      U8 lum = rColor.red / 17;
      U8 alp = rColor.alpha / 17;
      *p = (alp << 4) | (lum & 0x0F);
      break;
   }

   // --- 16-bit ---
   case GFXFormatR5G6B5:
   {
      U16 r = rColor.red * 31 / 255;
      U16 g = rColor.green * 63 / 255;
      U16 b = rColor.blue * 31 / 255;
#ifdef TORQUE_BIG_ENDIAN
      * (U16*)p = (r << 11) | (g << 5) | b;
#else
      * (U16*)p = (b) | (g << 5) | (r << 11);
#endif
      break;
   }

   case GFXFormatR5G5B5A1:
   {
      U16 r = rColor.red * 31 / 255;
      U16 g = rColor.green * 31 / 255;
      U16 b = rColor.blue * 31 / 255;
      U16 a = (rColor.alpha > 0) ? 1 : 0;
#ifdef TORQUE_BIG_ENDIAN
      * (U16*)p = (a << 15) | (b << 10) | (g << 5) | r;
#else
      * (U16*)p = (r << 11) | (g << 6) | (b << 1) | a;
#endif
      break;
   }

   case GFXFormatA8L8:
   {
      U16 l = rColor.red;
      U16 a = rColor.alpha;
#ifdef TORQUE_BIG_ENDIAN
      * (U16*)p = (a << 8) | l;
#else
      * (U16*)p = (l) | (a << 8);
#endif
      break;
   }

   case GFXFormatL16:
      *(U16*)p = convert8To16(rColor.red);
      break;

   case GFXFormatR16F:
   {
      U16* v = (U16*)p;
      v[0] = convertFloatToHalf(rColor.red / 255.f);
      break;
   }

   // --- 24-bit ---
   case GFXFormatR8G8B8:
   case GFXFormatR8G8B8_SRGB:
      p[0] = rColor.red;
      p[1] = rColor.green;
      p[2] = rColor.blue;
      break;

      // --- 32-bit ---
   case GFXFormatR32F:
   {
      F32* v = (F32*)p;
      v[0] = rColor.red / 255.f;
      break;
   }
   case GFXFormatR16G16:
   {
      U16* v = (U16*)p;
      v[0] = convert8To16(rColor.red);
      v[1] = convert8To16(rColor.green);
      break;
   }
   case GFXFormatR16G16F:
   {
      U16* v = (U16*)p;
      v[0] = convertFloatToHalf(rColor.red / 255.f);
      v[1] = convertFloatToHalf(rColor.green / 255.f);
      break;
   }
   case GFXFormatR8G8B8A8:
   case GFXFormatR8G8B8A8_SRGB:
   case GFXFormatR8G8B8X8:
      p[0] = rColor.red;
      p[1] = rColor.green;
      p[2] = rColor.blue;
      p[3] = (mInternalFormat == GFXFormatR8G8B8X8) ? 255 : rColor.alpha;
      break;

   case GFXFormatB8G8R8A8:
      p[0] = rColor.blue;
      p[1] = rColor.green;
      p[2] = rColor.red;
      p[3] = rColor.alpha;
      break;

      // --- 64-bit ---
   case GFXFormatR16G16B16A16:
   {
      U16* v = (U16*)p;
      v[0] = convert8To16(rColor.red);
      v[1] = convert8To16(rColor.green);
      v[2] = convert8To16(rColor.blue);
      v[3] = convert8To16(rColor.alpha);
      break;
   }

   case GFXFormatR16G16B16A16F:
   {
      U16* v = (U16*)p;
      v[0] = convertFloatToHalf(rColor.red / 255.f);
      v[1] = convertFloatToHalf(rColor.green / 255.f);
      v[2] = convertFloatToHalf(rColor.blue / 255.f);
      v[3] = convertFloatToHalf(rColor.alpha / 255.f);
      break;
   }

   // --- 128-bit ---
   case GFXFormatR32G32B32A32F:
   {
      F32* v = (F32*)p;
      v[0] = rColor.red / 255.f;
      v[1] = rColor.green / 255.f;
      v[2] = rColor.blue / 255.f;
      v[3] = rColor.alpha / 255.f;
      break;
   }

   default:
      AssertFatal(false, "Bad internal format in setColor");
      return false;
   }

   return true;
}

//--------------------------------------------------------------------------
U8 GBitmap::getChanelValueAt(U32 x, U32 y, U32 chan, const U32 mipLevel, const U32 face)
{
   ColorI pixelColor = ColorI(255, 255, 255, 255);
   getColor(x, y, pixelColor, mipLevel, face);
   if (mInternalFormat == GFXFormatL16 || mInternalFormat == GFXFormatL8)
   {
      chan = 0;
   }
   switch (chan) {
   case 0: return pixelColor.red;
   case 1: return pixelColor.green;
   case 2: return pixelColor.blue;
   default: return pixelColor.alpha;
   }
}

//-----------------------------------------------------------------------------

bool GBitmap::combine(const GBitmap* bitmapA, const GBitmap* bitmapB, const TextureOp combineOp)
{
   // combine() resizes/reformats based only on width/height and reads/
   // writes via the default (face 0) accessors, so it silently ignores
   // every other face of a multi-face (cubemap/array) bitmap. Fail
   // loudly instead of returning a bitmap that looks plausible but is
   // only correct on one face.
   if (bitmapA->getNumFaces() > 1 || bitmapB->getNumFaces() > 1)
   {
      Con::errorf("GBitmap::combine - multi-face bitmaps (cubemaps/arrays) are not supported");
      return false;
   }

   // Check bitmapA format
   switch (bitmapA->getFormat())
   {
   case GFXFormatR8G8B8:
   case GFXFormatR8G8B8X8:
   case GFXFormatR8G8B8A8:
      break;

   default:
      Con::errorf("GBitmap::combine - invalid format for bitmapA");
      return false;
   }

   // Check bitmapB format
   switch (bitmapB->getFormat())
   {
   case GFXFormatR8G8B8:
   case GFXFormatR8G8B8X8:
   case GFXFormatR8G8B8A8:
      break;

   default:
      Con::errorf("GBitmap::combine - invalid format for bitmapB");
      return false;
   }

   // Determine format of result texture
   // CodeReview: This is dependent on the order of the GFXFormat enum. [5/11/2007 Pat]
   GFXFormat resFmt = static_cast<GFXFormat>(getMax(bitmapA->getFormat(), bitmapB->getFormat()));
   U32 resWidth = getMax(bitmapA->getWidth(), bitmapB->getWidth());
   U32 resHeight = getMax(bitmapA->getHeight(), bitmapB->getHeight());

   // Adjust size OF bitmap based on the biggest one
   if (bitmapA->getWidth() != bitmapB->getWidth() ||
      bitmapA->getHeight() != bitmapB->getHeight())
   {
      // Delete old bitmap
      deleteImage();

      // Allocate new one
      allocateBitmap(resWidth, resHeight, false, resFmt);
   }

   // Adjust format of result bitmap (if resFmt == getFormat() it will not perform the format convert)
   setFormat(resFmt);

   // Perform combine
   U8* destBits = getWritableBits();
   const U8* aBits = bitmapA->getBits();
   const U8* bBits = bitmapB->getBits();

   for (S32 y = 0; y < getHeight(); y++)
   {
      for (S32 x = 0; x < getWidth(); x++)
      {
         for (S32 _byte = 0; _byte < mBytesPerPixel; _byte++)
         {
            U8 pxA = 0;
            U8 pxB = 0;

            // Get contributions from A and B
            if (y < bitmapA->getHeight() &&
               x < bitmapA->getWidth() &&
               _byte < bitmapA->getBytesPerPixel())
               pxA = *aBits++;

            if (y < bitmapB->getHeight() &&
               x < bitmapB->getWidth() &&
               _byte < bitmapB->getBytesPerPixel())
               pxB = *bBits++;

            // Combine them (clamp values 0-U8_MAX)
            switch (combineOp)
            {
            case Add:
               *destBits++ = getMin(U8(pxA + pxB), U8_MAX);
               break;

            case Subtract:
               *destBits++ = getMax(U8(pxA - pxB), U8(0));
               break;
            default:
               AssertFatal(false, "GBitmap::combine - Invalid combineOp");
               break;
            }
         }
      }
   }

   return true;
}

void GBitmap::fill(const ColorI& rColor)
{
   mHasTransparency = rColor.alpha < 255;

   for (U32 faceIndex = 0; faceIndex < getNumFaces(); faceIndex++)
   {
      Face& face = mFaces[faceIndex];

      // Set the first pixel using the slow but proper (format-aware) method.
      setColor(0, 0, rColor, 0, faceIndex);

      // Now fill the first row of the face by copying the first
      // pixel across the row.
      const U32 stride = face.getWidth() * mBytesPerPixel;
      const U8* src = face.getBits();
      U8* dest = face.getWritableBits() + mBytesPerPixel;
      const U8* end = src + stride;
      for (; dest != end; dest += mBytesPerPixel)
         dMemcpy(dest, src, mBytesPerPixel);

      // Now copy the first row to all the others.
      //
      // TODO: This could adaptively size the copy
      // amount to copy more rows from the source
      // and reduce the total number of memcpy calls.
      //
      dest = face.getWritableBits() + stride;
      end = src + (stride * face.getHeight());
      for (; dest != end; dest += stride)
         dMemcpy(dest, src, stride);
   }
}

void GBitmap::fillWhite()
{
   for (U32 i = 0; i < getNumFaces(); i++)
      dMemset(mFaces[i].getWritableBits(), 255, mFaces[i].getByteSize());
   mHasTransparency = false;
}

GBitmap* GBitmap::createPaddedBitmap() const
{
   if (isPow2(getWidth()) && isPow2(getHeight()))
      return NULL;

   AssertFatal(getNumMipLevels() == 1,
      "Cannot have non-pow2 bitmap with miplevels");

   U32 width = getWidth();
   U32 height = getHeight();

   U32 newWidth = getNextPow2(getWidth());
   U32 newHeight = getNextPow2(getHeight());

   GBitmap* pReturn = new GBitmap(newWidth, newHeight, false, getFormat(), getNumFaces());

   for (U32 faceIndex = 0; faceIndex < getNumFaces(); faceIndex++)
   {
      const Face& srcFace = getFace(faceIndex);
      Face& destFace = pReturn->getFace(faceIndex);

      for (U32 i = 0; i < height; i++)
      {
         U8* pDest = destFace.getAddress(0, i);
         const U8* pSrc = srcFace.getAddress(0, i);

         dMemcpy(pDest, pSrc, width * mBytesPerPixel);

         pDest += width * mBytesPerPixel;
         // set the src pixel to the last pixel in the row
         const U8* pSrcPixel = pDest - mBytesPerPixel;

         for (U32 j = width; j < newWidth; j++)
            for (U32 k = 0; k < mBytesPerPixel; k++)
               *pDest++ = pSrcPixel[k];
      }

      for (U32 i = height; i < newHeight; i++)
      {
         U8* pDest = destFace.getAddress(0, i);
         U8* pSrc = destFace.getAddress(0, height - 1);
         dMemcpy(pDest, pSrc, newWidth * mBytesPerPixel);
      }
   }

   return pReturn;
}

GBitmap* GBitmap::createPow2Bitmap() const
{
   if (isPow2(getWidth()) && isPow2(getHeight()))
      return NULL;

   AssertFatal(getNumMipLevels() == 1,
      "Cannot have non-pow2 bitmap with miplevels");

   U32 width = getWidth();
   U32 height = getHeight();

   U32 newWidth = getNextPow2(getWidth());
   U32 newHeight = getNextPow2(getHeight());

   GBitmap* pReturn = new GBitmap(newWidth, newHeight, false, getFormat(), getNumFaces());

   F32 yCoeff = (F32)height / (F32)newHeight;
   F32 xCoeff = (F32)width / (F32)newWidth;

   for (U32 faceIndex = 0; faceIndex < getNumFaces(); faceIndex++)
   {
      const Face& srcFace = getFace(faceIndex);
      Face& destFace = pReturn->getFace(faceIndex);

      F32 currY = 0.0f;
      for (U32 y = 0; y < newHeight; y++)
      {
         F32 currX = 0.0f;
         for (U32 x = 0; x < newWidth; x++)
         {
            U8* pDest = destFace.getAddress(x, y);
            const U8* pSrc = srcFace.getAddress((S32)currX, (S32)currY);
            for (U32 p = 0; p < mBytesPerPixel; p++)
               pDest[p] = pSrc[p];
            currX += xCoeff;
         }
         currY += yCoeff;
      }
   }

   return pReturn;
}

void GBitmap::copyChannel(U32 index, GBitmap* outBitmap) const
{
   AssertFatal(index < mBytesPerPixel, "GBitmap::copyChannel() - Bad channel offset!");
   AssertFatal(outBitmap, "GBitmap::copyChannel() - Null output bitmap!");
   AssertFatal(outBitmap->getWidth() == getWidth(), "GBitmap::copyChannel() - Width mismatch!");
   AssertFatal(outBitmap->getHeight() == getHeight(), "GBitmap::copyChannel() - Height mismatch!");
   AssertFatal(outBitmap->getNumFaces() == getNumFaces(), "GBitmap::copyChannel() - Face count mismatch!");
   AssertFatal(outBitmap->getNumMipLevels() == getNumMipLevels(), "GBitmap::copyChannel() - Mip level count mismatch!");

   // NOTE: the old implementation walked the *entire* buffer as one
   // linear range (getBits() through getBits()+mByteSize), relying on
   // every face/mip being contiguous in a single allocation to visit
   // every face "for free". That's no longer true - each face now owns
   // independent memory - so this walks faces and mip levels explicitly.
   const U32 outBytesPerPixel = outBitmap->getBytesPerPixel();

   for (U32 faceIndex = 0; faceIndex < getNumFaces(); faceIndex++)
   {
      const Face& srcFace = getFace(faceIndex);
      Face& destFace = outBitmap->getFace(faceIndex);

      for (U32 mip = 0; mip < getNumMipLevels(); mip++)
      {
         const U8* srcBits = srcFace.getBits(mip) + index;
         U8* destBits = destFace.getWritableBits(mip);
         const U32 numPixels = srcFace.getWidth(mip) * srcFace.getHeight(mip);

         for (U32 p = 0; p < numPixels; p++)
         {
            *destBits = *srcBits;
            destBits += outBytesPerPixel;
            srcBits += mBytesPerPixel;
         }
      }
   }
}

//------------------------------------------------------------------------------

bool GBitmap::read(Stream& io_rStream)
{
   PROFILE_SCOPE(GBitmap_Read);

   U32 version;
   io_rStream.read(&version);
   if (version != csFileVersion)
   {
      // This is an internal binary cache format (.dbm alongside a
      // source asset), not a durable file format - any version mismatch
      // (including the pre-Face-refactor v3/v4 layout, which isn't
      // compatible with the new per-face block layout at all) simply
      // fails to load here; the caller (Resource<GBitmap>::create())
      // regenerates the cache from the source asset in that case.
      Con::errorf("GBitmap::read - cache file version (%d) does not match what this build writes (%d); it will be regenerated from source.", version, csFileVersion);
      return false;
   }

   U32 fmt;
   io_rStream.read(&fmt);
   mInternalFormat = GFXFormat(fmt);
   mBytesPerPixel = getFormatBytesPerPixel(mInternalFormat);

   U32 numFaces;
   io_rStream.read(&numFaces);

   mFaces.setSize(numFaces);
   for (U32 i = 0; i < numFaces; i++)
      mFaces[i].read(io_rStream);

   checkForTransparency();

   return (io_rStream.getStatus() == Stream::Ok);
}

bool GBitmap::write(Stream& io_rStream) const
{
   PROFILE_SCOPE(GBitmap_Write);

   io_rStream.write(csFileVersion);
   io_rStream.write(U32(mInternalFormat));
   io_rStream.write(getNumFaces());

   for (U32 i = 0; i < getNumFaces(); i++)
      mFaces[i].write(io_rStream);

   return (io_rStream.getStatus() == Stream::Ok);
}

//------------------------------------------------------------------------------
//-------------------------------------- Persistent I/O
//

bool  GBitmap::readBitmap(const String& bmType, const Torque::Path& path)
{
   PROFILE_SCOPE(ResourceGBitmap_readBitmap);
   const GBitmap::Registration* regInfo = GBitmap::sFindRegInfo(bmType);

   if (regInfo == NULL)
   {
      Con::errorf("[GBitmap::readBitmap] unable to find registration for extension [%s]", bmType.c_str());
      return false;
   }

   return regInfo->readFunc(path, this);
}

bool GBitmap::readBitmapStream(const String& bmType, Stream& ioStream, U32 len)
{
   PROFILE_SCOPE(ResourceGBitmap_readBitmapStream);
   const GBitmap::Registration* regInfo = GBitmap::sFindRegInfo(bmType);

   if (regInfo == NULL)
   {
      Con::errorf("[GBitmap::readBitmap] unable to find registration for extension [%s]", bmType.c_str());
      return false;
   }

   return regInfo->readStreamFunc(ioStream, this, len);
}

bool  GBitmap::writeBitmap(const String& bmType, const Torque::Path& path, U32 compressionLevel)
{
   FileStream stream;
   if (!stream.open(path, Torque::FS::File::Write))
   {
      Con::errorf("GBitmap::writeBitmap failed to open path %s", path.getFullFileName().c_str());
      stream.close();
      return false;
   }

   // free file for stb
   stream.close();

   const GBitmap::Registration* regInfo = GBitmap::sFindRegInfo(bmType);

   if (regInfo == NULL)
   {
      Con::errorf("[GBitmap::writeBitmap] unable to find registration for extension [%s]", bmType.c_str());
      return false;
   }

   return regInfo->writeFunc(path, this, (compressionLevel == U32_MAX) ? regInfo->defaultCompression : compressionLevel);
}

bool GBitmap::writeBitmapStream(const String& bmType, Stream& ioStream, U32 compressionLevel)
{
   const GBitmap::Registration* regInfo = GBitmap::sFindRegInfo(bmType);

   if (regInfo == NULL)
   {
      Con::errorf("[GBitmap::writeBitmap] unable to find registration for extension [%s]", bmType.c_str());
      return false;
   }

   return regInfo->writeStreamFunc(bmType, ioStream, this, (compressionLevel == U32_MAX) ? regInfo->defaultCompression : compressionLevel);
}

template<> void* Resource<GBitmap>::create(const Torque::Path& path)
{
   PROFILE_SCOPE(ResourceGBitmap_create);

#ifdef TORQUE_DEBUG_RES_MANAGER
   Con::printf("Resource<GBitmap>::create - [%s]", path.getFullPath().c_str());
#endif

   GBitmap* bmp = new GBitmap;
   FileStream  stream;

   Torque::Path dbm = path;
   dbm.setExtension("dbm");
   if (Torque::FS::IsFile(dbm))
   {

      Torque::FS::FileNodeRef assetFile = Torque::FS::GetFileNode(path);
      Torque::FS::FileNodeRef compiledFile = Torque::FS::GetFileNode(dbm);

      if (assetFile != NULL && compiledFile != NULL)
      {
         if (compiledFile->getModifiedTime() >= assetFile->getModifiedTime())
         {
#ifdef TORQUE_DEBUG_RES_MANAGER
            Con::printf("Resource<GBitmap>::create - Loading cached image file: %s", dbm.getFullPath().c_str());
#endif
            stream.open(dbm.getFullPath(), Torque::FS::File::Read);
            bmp->read(stream);
            return bmp;
         }
      }
   }

   stream.open(path.getFullPath(), Torque::FS::File::Read);

   if (stream.getStatus() != Stream::Ok)
   {
      Con::errorf("Resource<GBitmap>::create - failed to open '%s'", path.getFullPath().c_str());
      return NULL;
   }

   const String extension = path.getExtension();
   if (!bmp->readBitmap(extension, path))
   {
      // we can only get here if the stream was successful, so attempt to read the stream.
      Con::warnf("Was unable to load as file, going to try the stream instead.");
      if (!bmp->readBitmapStream(extension, stream, stream.getStreamSize()))
      {
         Con::errorf("Resource<GBitmap>::create - error reading '%s'", path.getFullPath().c_str());
         delete bmp;
         bmp = NULL;
      }
   }

   return bmp;
}

template<> ResourceBase::Signature  Resource<GBitmap>::signature()
{
   return MakeFourCC('b', 'i', 't', 'm');
}

Resource<GBitmap> GBitmap::load(const Torque::Path& path)
{
   Resource<GBitmap> ret = _load(path);
   if (ret != NULL)
      return ret;

   // Do a recursive search.
   return _search(path);
}

Resource<GBitmap> GBitmap::_load(const Torque::Path& path)
{
   PROFILE_SCOPE(GBitmap_load);

   if (Torque::FS::IsFile(path))
      return ResourceManager::get().load(path);

   Path foundPath;
   if (GBitmap::sFindFile(path, &foundPath))
   {
      Resource<GBitmap> ret = ResourceManager::get().load(foundPath);
      if (ret != NULL)
         return ret;
   }

   return Resource< GBitmap >(NULL);
}

Resource<GBitmap> GBitmap::_search(const Torque::Path& path)
{
   PROFILE_SCOPE(GBitmap_search);

   // If unable to load texture in current directory
   // look in the parent directory.  But never look in the root.
   Path newPath(path);
   while (true)
   {
      String filePath = newPath.getPath();
      String::SizeType slash = filePath.find('/', filePath.length(), String::Right);

      if (slash == String::NPos)
         break;

      slash = filePath.find('/', filePath.length(), String::Right);
      if (slash == String::NPos)
         break;

      String truncPath = filePath.substr(0, slash);
      newPath.setPath(truncPath);

      Resource<GBitmap> ret = _load(newPath);
      if (ret != NULL)
         return ret;
   }

   return Resource< GBitmap >(NULL);
}

U32 GBitmap::getByteSize() const
{
   U32 total = 0;
   for (U32 i = 0; i < mFaces.size(); i++)
      total += mFaces[i].getByteSize();
   return total;
}

U32 GBitmap::getSurfaceSize(const U32 mipLevel) const
{
   U32 height = getHeight(mipLevel);
   U32 width = getWidth(mipLevel);

   if (mInternalFormat >= GFXFormatBC1 && mInternalFormat <= GFXFormatBC3)
   {
      // From the directX docs:
      // max(1, width / 4) x max(1, height / 4) x 8(DXT1) or 16(DXT2-5)

      U32 sizeMultiple = 0;

      switch (mInternalFormat)
      {
      case GFXFormatBC1:
         sizeMultiple = 8;
         break;
      case GFXFormatBC2:
      case GFXFormatBC3:
         sizeMultiple = 16;
         break;
      default:
         AssertISV(false, "DDSFile::getSurfaceSize - invalid compressed texture format, we only support DXT1-5 right now.");
         break;
      }

      return getMax(U32(1), width / 4) * getMax(U32(1), height / 4) * sizeMultiple;
   }
   else
   {
      return height * width * mBytesPerPixel;
   }
}

DefineEngineFunction(getBitmapInfo, String, (const char* filename), ,
   "Returns image info in the following format: width TAB height TAB bytesPerPixel TAB format. "
   "It will return an empty string if the file is not found.\n"
   "@ingroup Rendering\n")
{
   Resource<GBitmap> image = GBitmap::load(filename);
   if (!image)
      return String::EmptyString;

   return String::ToString("%d\t%d\t%d\t%d", image->getWidth(),
      image->getHeight(),
      image->getBytesPerPixel(),
      image->getFormat());
}

DefineEngineFunction(saveScaledImage, bool, (const char* bitmapSource, const char* bitmapDest, S32 resolutionSize), ("", "", 256),
   "Loads an image from the source path, and scales it down to the target resolution before"
   "Saving it out to the destination path.\n")
{
   bool isDDS = false;
   bool isHDR = false;

   if (bitmapSource == 0 || bitmapSource[0] == '\0' || bitmapDest == 0 || bitmapDest[0] == '\0')
   {
      return false;
   }

   if (!Platform::isFile(bitmapSource))
   {
      return false;
   }

   //First, gotta check the extension, as we have some extra work to do if it's
   //a DDS file
   const char* ret = dStrrchr(bitmapSource, '.');
   if (ret)
   {
      if (String::ToLower(ret) == String(".dds"))
         isDDS = true;

      if (String::ToLower(ret) == String(".hdr"))
         isHDR = true;
   }
   else
   {
      return false; //no extension? bail out
   }

   GBitmap* image = NULL;
   if (isDDS)
   {
      Resource<DDSFile> dds = DDSFile::load(bitmapSource, 0);
      if (dds != NULL)
      {
         image = new GBitmap();
         if (!dds->decompressToGBitmap(image))
         {
            delete image;
            image = NULL;
         }
      }
   }
   else
   {
      Resource<GBitmap> resImage = GBitmap::load(bitmapSource);
      image = new GBitmap(*resImage);
   }

   if (!image)
      return false;
   Torque::Path sourcePath = Torque::Path(bitmapSource);

   if (isPow2(image->getWidth()) && isPow2(image->getHeight()))
      image->extrudeMipLevels();

   image->setFormat(GFXFormatR8G8B8A8);

   U32 mipCount = image->getNumMipLevels();
   U32 targetMips = mFloor(mLog2((F32)(resolutionSize ? resolutionSize : 256))) + 1;

   if (mipCount > targetMips)
   {
      image->chopTopMips(mipCount - targetMips);
   }

   //TODO: support different format targets, for now we just force
   //to png for simplicity
   Torque::Path destinationPath = Torque::Path(bitmapDest);
   destinationPath.setExtension("png");

   if (!image->writeBitmap("png", destinationPath.getFullPath()))
   {
      Con::errorf("saveScaledImage() - Error writing %s !", bitmapDest);
      delete image;
      return false;
   }


   delete image;
   return true;
}
