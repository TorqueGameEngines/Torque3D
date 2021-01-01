#include "gfxGLTextureArray.h"

#include "gfxGLTextureObject.h"
#include "gfxGLUtils.h"
#include "core/util/tVector.h"
#include "gfx/bitmap/imageUtils.h"


GFXGLTextureArray::GFXGLTextureArray()
{
   mTextureArray = NULL;
}

GFXGLTextureArray::~GFXGLTextureArray()
{
   glDeleteTextures(1, &mTextureArray);
}

bool GFXGLTextureArray::fromTextureArray(const Vector<GFXTexHandle> &textureArray)
{
   bool success = true;

   if (textureArray.empty())
   {
      return true;
   }

   bool found = false;
   U32 baseWidth = 0, baseHeight = 0;
   bool isCompressed = false;
   mArraySize = textureArray.size();

   for (GFXTexHandle texObj : textureArray)
   {
      if (texObj.isValid())
      {
         if (!found)
         {
            baseWidth = texObj.getWidth();
            baseHeight = texObj.getHeight();
            mMipMapLevels = getMax((U32)1, texObj->mMipLevels);
            found = true;
            mFormat = texObj.getFormat();
            isCompressed = ImageUtil::isCompressedFormat(mFormat);
         }

         if (mFormat != texObj.getFormat() || baseWidth != texObj.getWidth() || baseHeight != texObj.getHeight())
         {
            AssertWarn(true, "GFXGLTextureArray::fromTextureArray there was a mismatch in texture format, defaulting to uncompressed format");
            Con::warnf("GFXGLTextureArray::fromTextureArray there was a mismatch in texture format, defaulting to uncompressed format");
            success = false;
            mFormat = GFXFormatR8G8B8A8;
            isCompressed = false;
         }
      }
   }

   // One might think this should return false in this case, but the return value is mostly to highlight internal errors not input errors.
   if (!found) return true;

   Vector <GFXGLTextureObject*> texture2Ds;
   texture2Ds.setSize(textureArray.size());
   Vector<GFXTexHandle> tmpHandles;

   for (U32 idx = 0; idx < mArraySize; ++idx)
   {
      texture2Ds[idx] = NULL;
      GFXTexHandle texObj = textureArray[idx];

      if (texObj.isValid())
      {
         GFXTexHandle handle = textureArray[idx];
         if (texObj->getPath().isNotEmpty())
         {
            if (texObj.getHeight() != baseHeight|| texObj.getWidth() != baseWidth || texObj.getFormat() != mFormat)
            {
               if (texObj.getHeight() != baseHeight || texObj.getWidth() != baseWidth)
               {
                  AssertWarn(true, "GFXGLTextureArray::fromTextureArray all textures should be the same size");
                  Con::warnf("GFXGLTextureArray::fromTextureArray all textures should be the same size");
               }
               else
               {
                  AssertWarn(true, "GFXGLTextureArray::fromTextureArray all textures should have the same format");
                  Con::warnf("GFXGLTextureArray::fromTextureArray all textures should have the same format");
               }

               GBitmap* inBitmap = TEXMGR->loadUncompressedTexture(textureArray[idx]->getPath(), &GFXTexturePersistentProfile, baseWidth, baseHeight);
               if (!inBitmap->setFormat(mFormat))
               {
                  AssertWarn(true, "GFXGLTextureArray::fromTextureArray all textures must be convertible to GFXFormatR8G8B8A8");
                  Con::errorf("GFXGLTextureArray::fromTextureArray all textures must be convertible to GFXFormatR8G8B8A8");
                  success = false;
                  handle = NULL;
                  delete inBitmap;
               }
               else
               {
                  handle = TEXMGR->createTexture(inBitmap, "", &GFXStaticTextureProfile, true);
                  tmpHandles.push_back(handle);
               }
            }
         }
         if (handle.isValid())
         {
            if (handle.getHeight() != baseHeight || handle.getWidth()!= baseWidth || handle.getFormat() != mFormat)
            {
               AssertWarn(true, "GFXGLTextureArray::fromTextureArray all textures must have the same size and format");
               Con::errorf("GFXGLTextureArray::fromTextureArray all textures must have the same size and format");
               success = false;
            }
            texture2Ds[idx] = dynamic_cast<GFXGLTextureObject*>(handle.getPointer());
            tmpHandles.push_back(handle);
         }
      }
   }

   glGenTextures(1, &mTextureArray);
   PRESERVE_2D_TEXTURE_ARRAY();
   glBindTexture(GL_TEXTURE_2D_ARRAY, mTextureArray);
   glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_LEVEL, mMin(mMipMapLevels - 1, 1));
   glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

   glTexStorage3D(GL_TEXTURE_2D_ARRAY, mMipMapLevels, GL_RGBA8, baseWidth, baseHeight, textureArray.size());

   for (U32 idx = 0; idx < texture2Ds.size(); ++idx)
   {
      if (texture2Ds[idx] == NULL)
      {
         continue;
      }
      GFXGLTextureObject* texObj = texture2Ds[idx];
      for (U32 mip = 0; mip < mMipMapLevels; ++mip)
      {
         U8* buf = texObj->getTextureData(mip);
         const U32 mipWidth = getMax(U32(1), baseWidth >> mip);
         const U32 mipHeight = getMax(U32(1), baseHeight >> mip);
         glBindTexture(GL_TEXTURE_2D_ARRAY, mTextureArray);
         if (isCompressed)
         {
            glCompressedTexSubImage3D(
               GL_TEXTURE_2D_ARRAY,
               mip, 0, 0,
               idx, mipWidth, mipHeight, 1,
               GFXGLTextureFormat[mFormat], GFXGLTextureType[mFormat], buf
            );
         }
         else
         {
            glTexSubImage3D(
               GL_TEXTURE_2D_ARRAY,
               mip, 0, 0,
               idx, mipWidth, mipHeight, 1,
               GFXGLTextureFormat[mFormat], GFXGLTextureType[mFormat], buf
            );
         }
         glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
         delete[] buf;
      }
   }

   if (!isCompressed)
      glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

   // Clean temporary textures
   for (GFXTexHandle handle : tmpHandles)
   {
      handle.free();
   }

   return success;
}

void GFXGLTextureArray::setToTexUnit(U32 tuNum)
{
   dynamic_cast<GFXGLDevice*>(getOwningDevice())->setTextureArrayInternal(tuNum, this);
}


void GFXGLTextureArray::Release()
{
   glDeleteTextures(1, &mTextureArray);
   mTextureArray = 0;
}


void GFXGLTextureArray::bind(U32 textureUnit) const
{
   glActiveTexture(GL_TEXTURE0 + textureUnit);
   glBindTexture(GL_TEXTURE_2D_ARRAY, mTextureArray);
   dynamic_cast<GFXGLDevice*>(getOwningDevice())->getOpenglCache()->setCacheBindedTex(textureUnit, GL_TEXTURE_2D_ARRAY, mTextureArray);

   GFXGLStateBlockRef sb = static_cast<GFXGLDevice*>(GFX)->getCurrentStateBlock();
   AssertFatal(sb, "GFXGLTextureArray::bind - No active stateblock!");
   if (!sb)
      return;

   const GFXSamplerStateDesc& ssd = sb->getDesc().samplers[textureUnit];
   glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, minificationFilter(ssd.minFilter, ssd.mipFilter, 0));
   glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GFXGLTextureFilter[ssd.magFilter]);
   glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_LEVEL, mMin(mMipMapLevels - 1, 1));
   glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GFXGLTextureAddress[ssd.addressModeU]);
   glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GFXGLTextureAddress[ssd.addressModeV]);
}

void GFXGLTextureArray::zombify()
{
}

void GFXGLTextureArray::resurrect()
{
}
