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

#ifndef _GFXTEXTUREARRAY_H_
#define _GFXTEXTUREARRAY_H_

#ifndef _REFBASE_H_
#include "core/util/refBase.h"
#endif
#ifndef _GFXRESOURCE_H_
#include "gfx/gfxResource.h"
#endif
#ifndef _GFXENUMS_H_
#include "gfxEnums.h"
#endif
#ifndef _GFXTEXTUREHANDLE_H_
#include "gfxTextureHandle.h"
#endif
#include "core/util/tVector.h"


class GFXTextureProfile;
class GFXTextureObject;

class GFXTextureArray : public StrongRefBase, public GFXResource
{
public:
   GFXTextureArray();

   virtual void init() = 0;
   virtual void set(U32 width, U32 height, U32 size, GFXFormat format, U32 mipLevels = 0);
   virtual bool fromTextureArray(const Vector<GFXTexHandle> &textureArray, U32 capacity = 0);
   virtual void setTexture(const GFXTexHandle &texture, U32 slot);
   virtual void setToTexUnit(U32 tuNum) = 0;


   // GFXResource interface
   void zombify() override = 0;
   void resurrect() override = 0;
   virtual void Release();

   const String describeSelf() const override;

   GFXFormat mFormat;
   bool mIsCompressed;
   U32 mWidth;
   U32 mHeight;
   U32 mArraySize;
   U32 mMipLevels;

   Vector<GFXTexHandle> mTextures;

protected:
   virtual void _setTexture(const GFXTexHandle& texture, U32 slot) = 0;
};


/// A reference counted handle to a texture array resource.
class GFXTextureArrayHandle : public StrongRefPtr<GFXTextureArray>
{
public:
   GFXTextureArrayHandle() {}
   GFXTextureArrayHandle(GFXTextureArray* textureArray) { StrongRefPtr<GFXTextureArray>::set(textureArray); }

   /// Releases the texture handle.
   void free() { StrongObjectRef::set(NULL); }
};

#endif // _GFXTEXTUREARRAY_H_
