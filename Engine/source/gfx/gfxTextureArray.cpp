#include "gfxTextureArray.h"


#include "gfxDevice.h"
#include "gfxTextureManager.h"
#include "bitmap/imageUtils.h"
#include "console/console.h"

GFXTextureArray::GFXTextureArray()
   : mFormat(GFXFormat_COUNT),
     mIsCompressed(false),
     mWidth(0),
     mHeight(0),
     mArraySize(0),
     mMipLevels(0)
{
}

void GFXTextureArray::set(U32 width, U32 height, U32 size, GFXFormat format, U32 mipLevels)
{
   if (mipLevels == 0 && width == height && isPow2(width))
   {
      mipLevels = mLog2(static_cast<F32>(width)) + 1;
   }
   if (
      mWidth == width &&
      mHeight == height &&
      mArraySize == size &&
      mFormat == format &&
      mMipLevels == mipLevels
      )
   {
      return;
   }

   Release();

   mWidth = width;
   mHeight = height;
   mArraySize = size;
   mFormat = format;
   mIsCompressed = ImageUtil::isCompressedFormat(mFormat);
   mMipLevels = getMax(mipLevels, static_cast<U32>(1));

   mTextures.setSize(size);

   init();
}

bool GFXTextureArray::fromTextureArray(const Vector<GFXTexHandle>& textureArray, U32 capacity)
{
   PROFILE_SCOPE(GFXTextureArray_fromTextureArray)
   bool success = true;

   // Not initialized, infer it from the given array of textures
   if (mArraySize == 0)
   {
      bool found = false;
      for (const GFXTexHandle& texObj : textureArray)
      {
         if (texObj.isValid())
         {
            if (!found)
            {
               found = true;
               mFormat = texObj.getFormat();
               mWidth = texObj.getWidth();
               mHeight = texObj.getHeight();
               mMipLevels = texObj->getMipLevels();
            }

            if (mFormat != texObj.getFormat() || mWidth != texObj.getWidth() || mHeight != texObj.getHeight())
            {
               AssertWarn(true, "GFXTextureArray::fromTextureArray there was a mismatch in texture formats, defaulting to uncompressed format");
               Con::warnf("GFXTextureArray::fromTextureArray there was a mismatch in texture formats, defaulting to uncompressed format");
               success = false;
               mFormat = GFXFormatR8G8B8A8;
            }
         }
      }

      // One might think this should return false in this case, but the return value is mostly to highlight internal errors not input errors.
      if (!found) return true;


      //---------------------------------------------------------------------------------------
      //	Create the texture array.  Each element in the texture 
      //		array has the same format/dimensions.
      //---------------------------------------------------------------------------------------
      U32 size = capacity;
      if (size == 0)
      {
         size = textureArray.size();
      }
      set(mWidth, mHeight, size, mFormat, mMipLevels);
   }
   //---------------------------------------------------------------------------------------


   //---------------------------------------------------------------------------------------
   //	Copy individual texture elements into texture array.
   //---------------------------------------------------------------------------------------
   // for each texture element...
   for (U32 i = 0; i < textureArray.size(); ++i)
   {
      if (textureArray[i].isValid())
      {
         setTexture(textureArray[i], i);
      }
   }
   //---------------------------------------------------------------------------------------

   return success;
}

void GFXTextureArray::setTexture(const GFXTexHandle& texture, U32 slot)
{
   PROFILE_SCOPE(GFXTextureArray_setTexture)
   GFXTexHandle handle = texture;
   if (texture->getPath().isNotEmpty())
   {
      if (texture.getHeight() != mHeight || texture.getWidth() != mWidth || texture.getFormat() != mFormat || texture->getMipLevels() < mMipLevels)
      {
         if (texture.getHeight() != mHeight || texture.getWidth() != mWidth)
         {
            AssertWarn(true, avar("GFXTextureArray::setTexture all textures should be the same size: %i vs %i", texture.getHeight(), mHeight));
            Con::warnf(avar("GFXTextureArray::setTexture all textures should be the same size: %i vs %i", texture.getHeight(), mHeight));
         }
         else if (texture->getMipLevels() < mMipLevels)
         {
            AssertWarn(true, avar("GFXTextureArray::setTexture all textures should have at least the same number of mips: %i vs %i", texture->getMipLevels(), mMipLevels));
            Con::warnf(avar("GFXTextureArray::setTexture all textures should have at least the same number of mips: %i vs %i", texture->getMipLevels(), mMipLevels));
         }
         else
         {
            AssertWarn(true, "GFXTextureArray::setTexture all textures should have the same format");
            Con::warnf("GFXTextureArray::setTexture all textures should have the same format");
         }

         GBitmap* inBitmap = TEXMGR->loadUncompressedTexture(texture->getPath(), &GFXTexturePersistentProfile, mWidth, mHeight);
         if (!inBitmap->setFormat(mFormat))
         {
            AssertFatal(true, "GFXTextureArray::setTexture all textures must be convertible to GFXFormat " + mFormat);
            Con::errorf("GFXTextureArray::setTexture all textures must be convertible to GFXFormat" + mFormat);
            handle = NULL;
            delete inBitmap;
         }
         else
         {
            handle = TEXMGR->createTexture(inBitmap, "", &GFXStaticTextureProfile, true);
         }
      }
   }
   if (!handle.isValid())
   {
      return;
   }

   if (handle.getHeight() != mHeight || handle.getWidth() != mWidth || handle.getFormat() != mFormat || handle->getMipLevels() < mMipLevels)
   {
      AssertFatal(true, "GFXTextureArray::setTexture all textures must have the same size and format");
      Con::errorf("GFXTextureArray::setTexture all textures must have the same size and format");
      return;
   }

   mTextures[slot] = handle;

   _setTexture(handle, slot);
}

void GFXTextureArray::Release()
{
   for (GFXTexHandle& mTexture : mTextures)
   {
      mTexture = NULL;
   }
}

const String GFXTextureArray::describeSelf() const
{
   // We've got nothing
   return String();
}
