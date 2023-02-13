#include "gfxGLTextureArray.h"

#include "gfxGLTextureObject.h"
#include "gfxGLUtils.h"
#include "core/util/tVector.h"

GFXGLTextureArray::GFXGLTextureArray()
{
   mTextureArray = 0;
}

void GFXGLTextureArray::init()
{
   PRESERVE_2D_TEXTURE_ARRAY();
   glGenTextures(1, &mTextureArray);
   glBindTexture(GL_TEXTURE_2D_ARRAY, mTextureArray);
   glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_LEVEL, mMin(mMipLevels - 1, 1));
   glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

   glTexStorage3D(GL_TEXTURE_2D_ARRAY, mMipLevels, GFXGLTextureInternalFormat[mFormat], mWidth, mHeight, mArraySize);
}

void GFXGLTextureArray::_setTexture(const GFXTexHandle& texture, U32 slot)
{
   PRESERVE_2D_TEXTURE_ARRAY();
   glBindTexture(GL_TEXTURE_2D_ARRAY, mTextureArray);

   GFXGLTextureObject* texObj = dynamic_cast<GFXGLTextureObject*>(texture.getPointer());
   for (U32 mip = 0; mip < mMipLevels; ++mip)
   {
      U8* buf = texObj->getTextureData(mip);
      const U32 mipWidth = getMax(U32(1), mWidth >> mip);
      const U32 mipHeight = getMax(U32(1), mHeight >> mip);
      if (mIsCompressed)
      {
         glCompressedTexSubImage3D(
            GL_TEXTURE_2D_ARRAY,
            mip, 0, 0,
            slot, mipWidth, mipHeight, 1,
            GFXGLTextureFormat[mFormat], GFXGLTextureType[mFormat], buf
         );
      }
      else
      {
         glTexSubImage3D(
            GL_TEXTURE_2D_ARRAY,
            mip, 0, 0,
            slot, mipWidth, mipHeight, 1,
            GFXGLTextureFormat[mFormat], GFXGLTextureType[mFormat], buf
         );
      }
      delete[] buf;
   }
}

void GFXGLTextureArray::setToTexUnit(U32 tuNum)
{
   dynamic_cast<GFXGLDevice*>(getOwningDevice())->setTextureArrayInternal(tuNum, this);
}

void GFXGLTextureArray::Release()
{
   glDeleteTextures(1, &mTextureArray);
   mTextureArray = 0;

   GFXTextureArray::Release();
}

void GFXGLTextureArray::bind(U32 textureUnit) const
{
   glActiveTexture(GL_TEXTURE0 + textureUnit);
   glBindTexture(GL_TEXTURE_2D_ARRAY, mTextureArray);

   dynamic_cast<GFXGLDevice*>(getOwningDevice())->getOpenglCache()->setCacheBindedTex(textureUnit, GL_TEXTURE_2D_ARRAY, mTextureArray);

   GFXGLStateBlockRef sb = dynamic_cast<GFXGLDevice*>(GFX)->getCurrentStateBlock();
   AssertFatal(sb, "GFXGLTextureArray::bind - No active stateblock!");
   if (!sb)
      return;

   const GFXSamplerStateDesc& ssd = sb->getDesc().samplers[textureUnit];
   glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, minificationFilter(ssd.minFilter, ssd.mipFilter, 0));
   glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GFXGLTextureFilter[ssd.magFilter]);
   glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_LEVEL, mMin(mMipLevels - 1, 1));
   glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GFXGLTextureAddress[ssd.addressModeU]);
   glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GFXGLTextureAddress[ssd.addressModeV]);
}

void GFXGLTextureArray::zombify()
{
}

void GFXGLTextureArray::resurrect()
{
}
