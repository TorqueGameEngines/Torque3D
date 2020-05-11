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

#ifndef _GFXCUBEMAP_H_
#define _GFXCUBEMAP_H_

#ifndef _GFXTEXTUREHANDLE_H_
#include "gfx/gfxTextureHandle.h"
#endif

class GFXDevice;
struct DDSFile;

///
class GFXCubemap : public StrongRefBase, public GFXResource
{
   friend class GFXDevice;
   friend class GFXTextureManager;

protected:

   // should only be called by GFXDevice
   virtual void setToTexUnit( U32 tuNum ) = 0;

   /// The path to the cubemap file.
   String mPath;

   /// Sets the cubemap file path.
   void _setPath( const String &path ) { mPath = path; }


   U32 mMipMapLevels;

   bool mInitialized;
public:

   /// Create a static cubemap from a list of 6 face textures.
   virtual void initStatic( GFXTexHandle *faces ) = 0;

   /// Create a static cubemap from a DDS cubemap file.
   virtual void initStatic( DDSFile *dds ) = 0;

   ///create dynamic cubemap. mipLevels 0 is auto create mips, otherwise the value is how many mip levels you wish the cubemap to have
   virtual void initDynamic( U32 texSize, GFXFormat faceFormat = GFXFormatR8G8B8A8, U32 mipLevels = 0 ) = 0;

   void initNormalize(U32 size);
      
   GFXCubemap();
   virtual ~GFXCubemap();

   /// Returns the size of the faces.
   virtual U32 getSize() const = 0;

   /// Returns the face texture format.
   virtual GFXFormat getFormat() const = 0;

   /// Returns if this cubemap has been initialized
   virtual bool isInitialized() { return false; }

   /// Returns the cubemap file path set at creation.
   const String& getPath() const { return mPath; }

   // GFXResource interface
   /// The resource should put a description of itself (number of vertices, size/width of texture, etc.) in buffer
   virtual const String describeSelf() const;

   /// Get the number of mip maps
   const U32 getMipMapLevels() const { return mMipMapLevels; }

   /// Get Z up face index of the cubemap. DDS files will be stored Y up
   static U32 zUpFaceIndex(const U32 index);
};


/// A reference counted handle to a cubemap resource.
class GFXCubemapHandle : public StrongRefPtr<GFXCubemap>
{
public:
   GFXCubemapHandle() {}
   GFXCubemapHandle( GFXCubemap *cubemap ) { StrongRefPtr<GFXCubemap>::set( cubemap ); }
   GFXCubemapHandle( const String &cubemapDDS ) { set( cubemapDDS ); }

   /// Set a cubemap from a DDS cubemap texture file.
   bool set( const String &cubemapDDS );

   /// Releases the texture handle.
   void free() { StrongObjectRef::set( NULL ); }
};

/// Cubemap array - data lives on the GPU only with this class, but the data is not immutable so it can be updated
class GFXCubemapArray : public StrongRefBase, public GFXResource
{
   friend class GFXDevice;
   friend class GFXTextureManager;

protected:
   /// should only be called by GFXDevice
   virtual void setToTexUnit( U32 tuNum ) = 0;
   /// number of cubemaps in the array
   U32 mNumCubemaps;
   /// cubemap face size
   U32 mSize;
   /// number of mip levels
   U32 mMipMapLevels;
   /// format
   GFXFormat mFormat;

public:
   GFXCubemapArray() :mNumCubemaps(0), mSize(0), mMipMapLevels(0), mFormat(GFXFormat_FIRST) {}
   virtual ~GFXCubemapArray() {};
   /// Initialize from an array of cubemaps
   virtual void init(GFXCubemapHandle *cubemaps, const U32 cubemapCount) = 0;
   /// Initialize cubemapCount number of blank cubemaps in the array
   virtual void init(const U32 cubemapCount, const U32 cubemapFaceSize, const GFXFormat format) = 0;
   /// Update cubemap in the array
   virtual void updateTexture(const GFXCubemapHandle &cubemap, const U32 slot) = 0;
   /// Copy this cubemap to another - destination must be same format, same face size & at-least the same size(or larger)
   virtual void copyTo(GFXCubemapArray *pDstCubemap) = 0;
   /// Return number of textures in the array
   const U32 getNumCubemaps() const { return mNumCubemaps; }
   /// Get the number of mip maps
   const U32 getMipMapLevels() const { return mMipMapLevels; }
   /// Returns the size of the faces.
   const U32 getSize() const { return mSize; }
   /// Returns the format
   const GFXFormat getFormat() const { return mFormat; }

   virtual const String describeSelf() const;
};

/// A reference counted handle to a cubemap array resource.
class GFXCubemapArrayHandle : public StrongRefPtr<GFXCubemapArray>
{
public:
   GFXCubemapArrayHandle() {}
   GFXCubemapArrayHandle(GFXCubemapArray *cubemapArray) { StrongRefPtr<GFXCubemapArray>::set(cubemapArray); }

   /// Releases the texture handle.
   void free() { StrongObjectRef::set(NULL); }
};



#endif // GFXCUBEMAP
