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

#ifndef _GBITMAP_H_
#define _GBITMAP_H_

#ifndef __RESOURCE_H__
#include "core/resource.h"
#endif

#ifndef _SWIZZLE_H_
#include "core/util/swizzle.h"
#endif

#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif

#ifndef _GFXENUMS_H_
#include "gfx/gfxEnums.h" // For the format
#endif

#ifndef _PROFILER_H_
#include "platform/profiler.h"
#endif
//-------------------------------------- Forward decls.
class Stream;
class RectI;
class Point2I;
class ColorI;
class LinearColorF;

//------------------------------------------------------------------------------
//-------------------------------------- GBitmap

class GBitmap
{
public:
   enum Constants
   {
      /// The maximum mipmap levels we support.  The current
      /// value lets us support up to 8192 x 8192 images.
      c_maxMipLevels = 14
   };

   enum TextureOp
   {
      Add,
      Subtract
   };

   /// Names for the six faces of a cubemap. A GBitmap allocated with
   /// in_numFaces == Face_COUNT is a cubemap; any other in_numFaces
   /// (including 1, for a plain 2D image) is just a flat list of faces -
   /// see the Face class and GBitmap::getFace(), which are also the
   /// building block for texture arrays (N faces of identical
   /// width/height/format with no cube-specific meaning).
   enum CubeFace
   {
      Face_PosX = 0,
      Face_NegX,
      Face_PosY,
      Face_NegY,
      Face_PosZ,
      Face_NegZ,

      Face_COUNT ///< Number of faces in a cubemap (6).
   };

   /// A single face (or array slice) of a bitmap: owns its own pixel
   /// buffer and mip chain independently of every other face. A plain 2D
   /// bitmap is just a GBitmap with exactly one Face; a cubemap has 6;
   /// this is also the natural building block for texture arrays (N
   /// faces of identical width/height/format).
   ///
   /// Face owns its pixel memory - copying a Face deep-copies its
   /// buffer, and destroying one frees it. All faces of a given GBitmap
   /// share the same pixel format, so Face itself doesn't know about
   /// GFXFormat - it only knows the byte size of one pixel
   /// (bytesPerPixel), which GBitmap passes in at allocation/format-
   /// conversion time. Format-aware pixel access (getColor()/setColor(),
   /// which need to know the channel layout, not just the byte size)
   /// stays on GBitmap.
   class Face
   {
   public:
      Face();
      Face(const Face& copy);
      ~Face();

      Face& operator=(const Face& copy);

      /// Allocates (or reallocates, preserving as many old bytes as
      /// fit) in_numMips levels at the given size. Pass in_numMips == 0
      /// to build a full mip chain down to 1x1.
      void allocate(const U32 in_width, const U32 in_height, const U32 in_numMips, const U32 in_bytesPerPixel);

      /// Frees this face's pixel data and resets it to an empty state.
      void deleteImage();

      U32 getWidth(const U32 mipLevel = 0) const;
      U32 getHeight(const U32 mipLevel = 0) const;
      U32 getNumMipLevels() const { return mNumMipLevels; }
      U32 getByteSize() const { return mByteSize; }
      U32 getBytesPerPixel() const { return mBytesPerPixel; }

      const U8* getBits(const U32 mipLevel = 0) const;
      U8* getWritableBits(const U32 mipLevel = 0);

      const U8* getAddress(const S32 x, const S32 y, const U32 mipLevel = 0) const;
      U8* getAddress(const S32 x, const S32 y, const U32 mipLevel = 0);

      /// Reformats this face's pixel data in place from oldFmt to
      /// newFmt (newBytesPerPixel is the new format's pixel byte size -
      /// GBitmap::getFormatBytesPerPixel(newFmt)) and recomputes the mip
      /// layout for the new pixel size.
      void convertFormat(GFXFormat oldFmt, GFXFormat newFmt, U32 newBytesPerPixel);

      /// Discards the top scalePower mip levels, keeping the smaller
      /// ones. Unlike the old single-buffer implementation, this simply
      /// allocates a fresh, smaller buffer and copies into it - since
      /// each face now owns independent memory there's no cross-face (or
      /// even in-place-overlap-within-a-face) bookkeeping needed.
      void chopTopMips(const U32 scalePower);

      bool read(Stream& s);
      bool write(Stream& s) const;

   private:
      U8* mBits;
      U32  mByteSize;
      U32  mWidth;
      U32  mHeight;
      U32  mBytesPerPixel;
      U32  mNumMipLevels;
      U32  mMipLevelOffsets[c_maxMipLevels];
   };

   struct Registration
   {
      /// The read functions prototype.
      typedef bool(*ReadFunc)(const Torque::Path& path, GBitmap* bitmap);
      typedef bool(*ReadStreamFunc)(Stream& stream, GBitmap* bitmap, U32 len);
      /// The write functions prototype.  Compression levels are image-specific - see their registration declaration for details.
      typedef bool(*WriteFunc)(const Torque::Path& path, GBitmap* bitmap, U32 compressionLevel);
      typedef bool(*WriteStreamFunc)(const String& bmType, Stream& stream, GBitmap* bitmap, U32 compressionLevel);

      /// Used to sort the registrations so that 
      /// lookups occur in a fixed order.
      U32 priority;
      Vector<String>   extensions;     ///< the list of file extensions for this bitmap type [these should be lower case]

      ReadFunc    readFunc;            ///< the read function to read from a file.
      WriteFunc   writeFunc;           ///< the write function to write to a file.
      ReadStreamFunc readStreamFunc;   ///< the read function to read from a stream.
      WriteStreamFunc writeStreamFunc; ///< the write function to write to a stream.

      U32 defaultCompression;          ///< the default compression level [levels are image-specific - see their registration declaration for details]

      Registration()
      {
         readFunc = NULL;
         writeFunc = NULL;
         readStreamFunc = NULL;
         writeStreamFunc = NULL;
         defaultCompression = 0;
         priority = 0;
         VECTOR_SET_ASSOCIATION(extensions);
      }
   };

   /// Load the given bitmap file.  It will try known file
   /// extensions if one is not specified.  If all else fails
   /// it will look up the folder hierarchy for a match.
   ///
   /// Important: Don't do something like this...
   ///
   /// @code
   ///    GBitmap* bitmap; // WRONG TYPE!
   ///    bitmap = GBitmap::load( filename );
   /// @endcode
   ///
   /// Resources are reference-counted and the smart pointer conversion will
   /// release the bitmap and thus render the resulting bitmap pointer invalid!
   /// The right way is like this:
   ///
   /// @code
   ///    Resource<GBitmap> bitmap; // Correct!
   ///    bitmap = GBitmap::load( filename );
   /// @endcode
   ///
   static Resource<GBitmap> load(const Torque::Path& path);

protected:

   static Resource<GBitmap> _load(const Torque::Path& path);
   static Resource<GBitmap> _search(const Torque::Path& path);

public:
   GBitmap();
   GBitmap(const GBitmap&);
   GBitmap& operator=(const GBitmap&);

   GBitmap(const U32  in_width,
      const U32  in_height,
      const bool in_extrudeMipLevels = false,
      const GFXFormat in_format = GFXFormatR8G8B8,
      const U32 in_numFaces = 1);

   // This builds a GBitmap with the R8G8B8A8 format using the passed in
   // data (assumes that there is width * height * 4 U8's in data)
   GBitmap(const U32  in_width,
      const U32  in_height,
      const U8* data,
      const U32 in_numFaces = 1);

   virtual ~GBitmap();


   static void sRegisterFormat(const Registration& reg);
   static const Registration* sFindRegInfo(const String& extension);

   /// Find the first file matching the registered extensions 
   /// skipping the original.
   static bool sFindFile(const Torque::Path& path, Torque::Path* outPath);

   /// Given a path to a file, try all known extensions.  If the file exists on disk, fill in path
   /// with the correct extension and return true.  Otherwise, return false.
   static bool sFindFiles(const Torque::Path& path, Vector<Torque::Path>* outFoundPaths);

   /// Returns a space separated string of all registered extensions.
   static String sGetExtensionList();

   /// Allocates a bitmap with either a single mip level, or (if
   /// in_extrudeMipLevels is true) a full mip chain down to 1x1.
   /// This is a thin convenience wrapper around allocateBitmapWithMips().
   void allocateBitmap(const U32  in_width,
      const U32  in_height,
      const bool in_extrudeMipLevels = false,
      const GFXFormat in_format = GFXFormatR8G8B8,
      const U32 in_numFaces = 1);

   /// Allocates a bitmap with an explicit number of mip levels.
   /// Pass in_numMips == 0 to build a full mip chain down to 1x1.
   /// in_numFaces must be at least 1; every face shares the same
   /// width/height/mip layout. in_numFaces == Face_COUNT (6) makes
   /// isCubemap() true; any other count is just a flat array of faces
   /// (e.g. for texture arrays) with no cube-specific meaning.
   void allocateBitmapWithMips(const U32  in_width,
      const U32  in_height,
      const U32  in_numMips,
      const GFXFormat in_format = GFXFormatR8G8B8,
      const U32 in_numFaces = 1);

   /// Generates the mip chain for every face of the bitmap (1 face for a
   /// plain 2D image, 6 for a cubemap, N for a texture array) by
   /// successively downsampling from mip 0. Allocates a full mip chain
   /// first if the bitmap doesn't have one yet.
   void extrudeMipLevels(bool clearBorders = false);

   /// Discards the top mipsToChop mip levels of every face, keeping the
   /// smaller ones.
   void chopTopMips(U32 mipsToChop);

   /// Detail-map variant of extrudeMipLevels() (RGB only) - also
   /// operates on every face.
   void extrudeMipLevelsDetail();

   U32   getNumMipLevels() const { return mFaces[0].getNumMipLevels(); }

   /// Pads every face of a non-power-of-2 bitmap up to the next power of
   /// 2 by extending the edge pixels. Returns NULL if already pow2.
   /// Not valid on a bitmap with more than one mip level.
   GBitmap* createPaddedBitmap() const;

   /// Resizes every face of a non-power-of-2 bitmap up to the next power
   /// of 2. Returns NULL if already pow2. Not valid on a bitmap with more
   /// than one mip level.
   GBitmap* createPow2Bitmap() const;

   /// Copies a color channel by index into the first channel 
   /// of the output bitmap.  The output bitmap must be the same
   /// dimensions, face count, and mip level count as the source.
   void copyChannel(U32 index, GBitmap* outBitmap) const;

   void copyRect(const GBitmap* in, const RectI& srcRect, const Point2I& dstPoint, const U32 srcMipLevel = 0, const U32 dstMipLevel = 0);

   GFXFormat   getFormat() const { return mInternalFormat; }
   bool        setFormat(GFXFormat fmt);

   U32         getWidth(const U32 in_mipLevel = 0) const;
   U32         getHeight(const U32 in_mipLevel = 0) const;
   U32         getDepth(const U32 in_mipLevel = 0) const;

   U8* getAddress(const S32 in_x, const S32 in_y, const U32 mipLevel = 0, const U32 face = 0);
   const U8* getAddress(const S32 in_x, const S32 in_y, const U32 mipLevel = 0, const U32 face = 0) const;
   /// Convenience overloads for cubemaps: face is required (no default),
   /// mipLevel is optional. e.g. bmp.getAddress(x, y, Face_PosZ).
   U8* getAddress(const S32 in_x, const S32 in_y, const CubeFace face, const U32 mipLevel = 0);
   const U8* getAddress(const S32 in_x, const S32 in_y, const CubeFace face, const U32 mipLevel = 0) const;

   const U8* getBits(const U32 in_mipLevel = 0, const U32 face = 0) const;
   U8* getWritableBits(const U32 in_mipLevel = 0, const U32 face = 0);
   /// Convenience overloads for cubemaps: face is required (no default),
   /// mipLevel is optional. e.g. bmp.getWritableBits(Face_PosZ).
   const U8* getBits(const CubeFace face, const U32 in_mipLevel = 0) const;
   U8* getWritableBits(const CubeFace face, const U32 in_mipLevel = 0);

   /// Returns a reference to the given face. Works on any bitmap, not
   /// just cubemaps - getFace(Face_PosX) (face 0) is valid on a plain 2D
   /// image too. The plain-U32 overload is for texture-array-style
   /// access beyond the 6 named cube faces.
   Face& getFace(const CubeFace face) { return mFaces[(U32)face]; }
   const Face& getFace(const CubeFace face) const { return mFaces[(U32)face]; }
   Face& getFace(const U32 face) { return mFaces[face]; }
   const Face& getFace(const U32 face) const { return mFaces[face]; }

   U32         getByteSize() const;
   U32         getBytesPerPixel() const { return mBytesPerPixel; }
   U32         getFormatBytesPerPixel(GFXFormat fmt);

   U32         getSurfaceSize(const U32 mipLevel) const;

   /// Use these functions to set and get the mHasTransparency value
   /// This is used to indicate that this bitmap has pixels that have
   /// an alpha value less than 255 (used by the auto-Material mapper)
   bool        getHasTransparency() const { return mHasTransparency; }
   void        setHasTransparency(bool hasTransparency) { mHasTransparency = hasTransparency; }

   /// In general you will want to use this function if there is not a
   /// good spot in the bitmap loader(s) to check the alpha value of
   /// the pixels. This function uses the texture format to loop over
   /// the bitmap bits and to check for alpha values less than 255
   bool        checkForTransparency();

   LinearColorF      sampleTexel(F32 u, F32 v, bool retAlpha = false) const;

   bool        getColor(const U32 x, const U32 y, ColorI& rColor, const U32 mipLevel = 0, const U32 face = 0) const;
   /// Convenience overload for cubemaps: face is required (no default),
   /// mipLevel is optional. e.g. bmp.getColor(x, y, color, Face_PosZ).
   bool        getColor(const U32 x, const U32 y, ColorI& rColor, const CubeFace face, const U32 mipLevel = 0) const;

   /// mipLevel/face were added alongside cubemap support; existing
   /// call sites that only pass (x, y, rColor) are unaffected and
   /// continue to write to mip 0 / face 0 as before.
   bool        setColor(const U32 x, const U32 y, const ColorI& rColor, const U32 mipLevel = 0, const U32 face = 0);
   /// Convenience overload for cubemaps: face is required (no default),
   /// mipLevel is optional. e.g. bmp.setColor(x, y, color, Face_PosZ).
   bool        setColor(const U32 x, const U32 y, const ColorI& rColor, const CubeFace face, const U32 mipLevel = 0);

   U8          getChanelValueAt(U32 x, U32 y, U32 chan, const U32 mipLevel = 0, const U32 face = 0);
   /// Convenience overload for cubemaps: face is required (no default),
   /// mipLevel is optional.
   U8          getChanelValueAt(U32 x, U32 y, U32 chan, const CubeFace face, const U32 mipLevel = 0);

   U32         getNumFaces() const { return mFaces.size(); }

   /// Returns true if this bitmap is a cubemap (6 faces), as opposed
   /// to a plain 2D image (1 face) or an N-face texture array.
   bool        isCubemap() const { return mFaces.size() == Face_COUNT; }

   /// Returns the byte size of a single face (covering all its mip
   /// levels). Useful when caching or streaming individual faces.
   U32         getFaceByteSize() const { return mFaces.empty() ? 0 : mFaces[0].getByteSize(); }

   /// This method will combine bitmapA and bitmapB using the operation specified
   /// by combineOp. The result will be stored in the bitmap that this method is
   /// called on. The size of the resulting bitmap will be the larger of A and B.
   /// The format of the resulting bitmap will be the format of A or B, whichever
   /// has a larger byte size.
   ///
   /// @note There are some restrictions on ops and formats that will probably change
   /// based on how we use this function.
   /// @note Multi-face bitmaps are not supported - bitmapA/bitmapB must
   /// both have exactly one face (getNumFaces() == 1).
   bool combine(const GBitmap* bitmapA, const GBitmap* bitmapB, const TextureOp combineOp);

   /// Fills every face's first mip level with the specified color.
   void fill(const ColorI& rColor);

   /// An optimized version of fill().
   void fillWhite();

   //-------------------------------------- Internal data/operators

   void deleteImage();

   //-------------------------------------- Input/Output interface

   /// Read a bitmap from a file
   /// @param bmType This is a file extension to describe the type of the data [i.e. "png" for PNG file, etc]
   /// @param ioStream The stream to read from
   bool readBitmap(const String& bmType, const Torque::Path& path);

   /// Sane as above but reads from a stream.
   bool readBitmapStream(const String& bmType, Stream& ioStream, U32 len);

   /// Write a bitmap to a file
   /// @param bmType This is a file extension to describe the type of the data [i.e. "png" for PNG file, etc]
   /// @param ioStream The stream to read from
   /// @param compressionLevel Image format specific compression level. For JPEG sets the quality level percentage, range 0 to 100.
   /// For PNG compression level is 0 - 10
   /// Not used for other image formats.
   bool writeBitmap(const String& bmType, const Torque::Path& path, U32 compressionLevel = U32_MAX);

   /// Sane as above but writes to a stream.
   bool writeBitmapStream(const String& bmType, Stream& ioStream, U32 compressionLevel = U32_MAX);

   bool readMNG(Stream& io_rStream);               // located in bitmapMng.cc
   bool writeMNG(Stream& io_rStream) const;

   /// Reads/writes this GBitmap's internal binary cache format (used for
   /// the .dbm cache alongside a source asset). Simply loops over
   /// getNumFaces() and calls Face::read()/Face::write() directly - each
   /// face is a fully self-contained block, so this generalizes to any
   /// face count (2D image, cubemap, or texture array) automatically.
   bool read(Stream& io_rStream);
   bool write(Stream& io_rStream) const;

   template<class T, dsize_t mapLength>
   void swizzle(const Swizzle<T, mapLength>* s);

   static Vector<Registration>& getRegistrations();

private:
   GFXFormat mInternalFormat;
   U32 mBytesPerPixel;

   /// One entry per face - 1 for a plain 2D image, 6 for a cubemap, N
   /// for a texture array. Always has at least one element (an empty
   /// Face for a freshly-constructed/deleteImage()'d bitmap) - see
   /// deleteImage(). All faces share mInternalFormat/mBytesPerPixel.
   Vector<Face> mFaces;

   bool mHasTransparency;

   static const U32 csFileVersion;
};

//------------------------------------------------------------------------------
//-------------------------------------- Inlines
//

inline U32 GBitmap::getWidth(const U32 in_mipLevel) const
{
   return mFaces[0].getWidth(in_mipLevel);
}

inline U32 GBitmap::getHeight(const U32 in_mipLevel) const
{
   return mFaces[0].getHeight(in_mipLevel);
}

inline const U8* GBitmap::getBits(const U32 in_mipLevel, const U32 face) const
{
   return mFaces[face].getBits(in_mipLevel);
}

inline U8* GBitmap::getWritableBits(const U32 in_mipLevel, const U32 face)
{
   return mFaces[face].getWritableBits(in_mipLevel);
}

inline U8* GBitmap::getAddress(const S32 in_x, const S32 in_y, const U32 mipLevel, const U32 face)
{
   return mFaces[face].getAddress(in_x, in_y, mipLevel);
}

inline const U8* GBitmap::getAddress(const S32 in_x, const S32 in_y, const U32 mipLevel, const U32 face) const
{
   return mFaces[face].getAddress(in_x, in_y, mipLevel);
}

//-------------------------------------- CubeFace convenience overloads
// These simply forward to the U32-face versions above, existing purely
// so cubemap call sites can write e.g. getAddress(x, y, Face_PosZ)
// instead of getAddress(x, y, 0, 4).

inline const U8* GBitmap::getBits(const CubeFace face, const U32 in_mipLevel) const
{
   return getBits(in_mipLevel, (U32)face);
}

inline U8* GBitmap::getWritableBits(const CubeFace face, const U32 in_mipLevel)
{
   return getWritableBits(in_mipLevel, (U32)face);
}

inline U8* GBitmap::getAddress(const S32 in_x, const S32 in_y, const CubeFace face, const U32 mipLevel)
{
   return getAddress(in_x, in_y, mipLevel, (U32)face);
}

inline const U8* GBitmap::getAddress(const S32 in_x, const S32 in_y, const CubeFace face, const U32 mipLevel) const
{
   return getAddress(in_x, in_y, mipLevel, (U32)face);
}

inline bool GBitmap::getColor(const U32 x, const U32 y, ColorI& rColor, const CubeFace face, const U32 mipLevel) const
{
   return getColor(x, y, rColor, mipLevel, (U32)face);
}

inline bool GBitmap::setColor(const U32 x, const U32 y, const ColorI& rColor, const CubeFace face, const U32 mipLevel)
{
   return setColor(x, y, rColor, mipLevel, (U32)face);
}

inline U8 GBitmap::getChanelValueAt(U32 x, U32 y, U32 chan, const CubeFace face, const U32 mipLevel)
{
   return getChanelValueAt(x, y, chan, mipLevel, (U32)face);
}

template<class T, dsize_t mapLength>
void GBitmap::swizzle(const Swizzle<T, mapLength>* s)
{
   const U32 memSize = getWidth() * getHeight() * mBytesPerPixel;

   void* b = dMalloc(memSize);

   s->ToBuffer(b, getWritableBits(), memSize);

   dMemcpy(getWritableBits(), b, memSize);

   dFree(b);
}

#endif //_GBITMAP_H_
