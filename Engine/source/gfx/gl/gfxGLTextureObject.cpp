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

#include "console/console.h"
#include "gfx/gl/tGL/tGL.h"
#include "math/mRect.h"
#include "gfx/gl/gfxGLTextureObject.h"
#include "gfx/gfxDevice.h"
#include "gfx/gl/gfxGLEnumTranslate.h"
#include "gfx/gl/gfxGLTextureManager.h"
#include "gfx/gl/gfxGLUtils.h"
#include "gfx/gfxCardProfile.h"


GFXGLTextureObject::GFXGLTextureObject(GFXDevice * aDevice, GFXTextureProfile *profile) :
   GFXTextureObject(aDevice, profile),
   mIsNPoT2(false),
   mBinding(GL_TEXTURE_2D),
   mBytesPerTexel(4),
   mLockedRectRect(0, 0, 0, 0),
   mGLDevice(static_cast<GFXGLDevice*>(mDevice)),
   mIsZombie(false),
   mZombieCache(NULL),
   mNeedInitSamplerState(true),
   mFrameAllocatorMark(0),
   mFrameAllocatorPtr(NULL)
{

#ifdef TORQUE_DEBUG
   mFrameAllocatorMarkGuard = FrameAllocator::getWaterMark();
#endif

   dMemset(&mLockedRect, 0, sizeof(mLockedRect));

   AssertFatal(dynamic_cast<GFXGLDevice*>(mDevice), "GFXGLTextureObject::GFXGLTextureObject - Invalid device type, expected GFXGLDevice!");
   glGenTextures(1, &mHandle);
   glGenBuffers(1, &mBuffer);
}

GFXGLTextureObject::~GFXGLTextureObject()
{
   glDeleteTextures(1, &mHandle);
   glDeleteBuffers(1, &mBuffer);
   delete[] mZombieCache;
   kill();
}

GFXLockedRect* GFXGLTextureObject::lock(U32 mipLevel /*= 0*/, RectI* inRect /*= NULL*/, U32 faceIndex /*= 0*/)
{
   //AssertFatal(mBinding != GL_TEXTURE_3D, "GFXGLTextureObject::lock - We don't support locking 3D textures yet");
   U32 width = mTextureSize.x >> mipLevel;
   U32 height = mTextureSize.y >> mipLevel;

   if(inRect)
   {
      if((inRect->point.x + inRect->extent.x > width) || (inRect->point.y + inRect->extent.y > height))
         AssertFatal(false, "GFXGLTextureObject::lock - Rectangle too big!");

      mLockedRectRect = *inRect;
   }
   else
   {
      mLockedRectRect = RectI(0, 0, width, height);
   }

   mLockedRect.pitch = mLockedRectRect.extent.x * mBytesPerTexel;

   // CodeReview [ags 12/19/07] This one texel boundary is necessary to keep the clipmap code from crashing.  Figure out why.
   U32 size = (mLockedRectRect.extent.x + 1) * (mLockedRectRect.extent.y + 1) * getDepth() * mBytesPerTexel;
   AssertFatal(!mFrameAllocatorMark && !mFrameAllocatorPtr, "");
   mFrameAllocatorMark = FrameAllocator::getWaterMark();
   mFrameAllocatorPtr = (U8*)FrameAllocator::alloc( size );
   mLockedRect.bits = mFrameAllocatorPtr;
#ifdef TORQUE_DEBUG
   mFrameAllocatorMarkGuard = FrameAllocator::getWaterMark();
#endif

   if( !mLockedRect.bits )
      return NULL;

   return &mLockedRect;
}

void GFXGLTextureObject::unlock(U32 mipLevel /*= 0*/, U32 faceIndex /*= 0*/)
{
   if(!mLockedRect.bits)
      return;

   // I know this is in unlock, but in GL we actually do our submission in unlock.
   PROFILE_SCOPE(GFXGLTextureObject_lockRT);

   PRESERVE_TEXTURE(mBinding);
   glBindTexture(mBinding, mHandle);
   glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBuffer);
   glBufferData(GL_PIXEL_UNPACK_BUFFER, (mLockedRectRect.extent.x + 1) * (mLockedRectRect.extent.y + 1) * mBytesPerTexel, mFrameAllocatorPtr, GL_STREAM_DRAW);
   S32 z = getDepth();
   if (mBinding == GL_TEXTURE_3D)
      glTexSubImage3D(mBinding, mipLevel, mLockedRectRect.point.x, mLockedRectRect.point.y, z,
      mLockedRectRect.extent.x, mLockedRectRect.extent.y, z, GFXGLTextureFormat[mFormat], GFXGLTextureType[mFormat], NULL);
   else if(mBinding == GL_TEXTURE_2D)
	   glTexSubImage2D(mBinding, mipLevel, mLockedRectRect.point.x, mLockedRectRect.point.y,
		  mLockedRectRect.extent.x, mLockedRectRect.extent.y, GFXGLTextureFormat[mFormat], GFXGLTextureType[mFormat], NULL);
   else if(mBinding == GL_TEXTURE_1D)
		glTexSubImage1D(mBinding, mipLevel, (mLockedRectRect.point.x > 1 ? mLockedRectRect.point.x : mLockedRectRect.point.y),
		  (mLockedRectRect.extent.x > 1 ? mLockedRectRect.extent.x : mLockedRectRect.extent.y), GFXGLTextureFormat[mFormat], GFXGLTextureType[mFormat], NULL);

   glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

   mLockedRect.bits = NULL;
#if TORQUE_DEBUG
   AssertFatal(mFrameAllocatorMarkGuard == FrameAllocator::getWaterMark(), "");
#endif
   FrameAllocator::setWaterMark(mFrameAllocatorMark);
   mFrameAllocatorMark = 0;
   mFrameAllocatorPtr = NULL;
}

void GFXGLTextureObject::release()
{
   glDeleteTextures(1, &mHandle);
   glDeleteBuffers(1, &mBuffer);

   mHandle = 0;
   mBuffer = 0;
}

void GFXGLTextureObject::reInit()
{
   AssertFatal(!mHandle && !mBuffer,"Must release before reInit");
   glGenTextures(1, &mHandle);
   glGenBuffers(1, &mBuffer);
}

bool GFXGLTextureObject::copyToBmp(GBitmap * bmp)
{
   if (!bmp)
      return false;

   // check format limitations
   // at the moment we only support RGBA for the source (other 4 byte formats should
   // be easy to add though)
   AssertFatal(mFormat == GFXFormatR16G16B16A16F || mFormat == GFXFormatR8G8B8A8 || mFormat == GFXFormatR8G8B8A8_LINEAR_FORCE || mFormat == GFXFormatR8G8B8A8_SRGB, "copyToBmp: invalid format");
   if (mFormat != GFXFormatR16G16B16A16F && mFormat != GFXFormatR8G8B8A8 && mFormat != GFXFormatR8G8B8A8_LINEAR_FORCE && mFormat != GFXFormatR8G8B8A8_SRGB)
	   return false;

   AssertFatal(bmp->getWidth() == getWidth(), avar("GFXGLTextureObject::copyToBmp - Width mismatch: %i vs %i", bmp->getWidth(), getWidth()));
   AssertFatal(bmp->getHeight() == getHeight(), avar("GFXGLTextureObject::copyToBmp - Height mismatch: %i vs %i", bmp->getHeight(), getHeight()));

   PROFILE_SCOPE(GFXGLTextureObject_copyToBmp);

   PRESERVE_TEXTURE(mBinding);
   glBindTexture(mBinding, mHandle);

   U8 dstBytesPerPixel = GFXFormat_getByteSize( bmp->getFormat() );
   U8 srcBytesPerPixel = GFXFormat_getByteSize( mFormat );

   FrameAllocatorMarker mem;

   const bool isCubemap = (mBinding == GL_TEXTURE_CUBE_MAP);
   const U32 numFaces = isCubemap ? 6 : 1;

   for (U32 mip = 0; mip < getMipLevels(); mip++)
   {
      U32 width = getWidth() >> mip;
      U32 height = getHeight() >> mip;
      if (width == 0) width = 1;
      if (height == 0) height = 1;

      // Check if multisampled
      GLint samples = 0;
      GLenum target = mBinding;
      if (mBinding == GL_TEXTURE_CUBE_MAP)
         target = GL_TEXTURE_CUBE_MAP_POSITIVE_X;

      glGetTexLevelParameteriv(target, mip, GL_TEXTURE_SAMPLES, &samples);
      if (samples > 0)
      {
         Con::warnf("GFXGLTextureObject::copyToBmp - Texture is multisampled (%d samples) at mip %d; resolve first.", samples, mip);
         return false;
      }

      for (U32 face = 0; face < numFaces; face++)
      {
         GLenum faceTarget = isCubemap ? GFXGLFaceType[face] : mBinding;

         U32 pixelCount = width * height;
         U8* srcPixels = (U8*)mem.alloc(pixelCount * srcBytesPerPixel);
         U8* dest = bmp->getWritableBits(mip, face);

         if (!dest)
         {
            Con::errorf("GFXGLTextureObject::copyToBmp - No destination bits for mip=%u face=%u", mip, face);
            continue;
         }

         // Read texture data
         glGetTexImage(faceTarget, mip, GFXGLTextureFormat[mFormat], GFXGLTextureType[mFormat], srcPixels);

         if (mFormat == GFXFormatR16G16B16A16F)
         {
            dMemcpy(dest, srcPixels, pixelCount * srcBytesPerPixel);
         }
         else
         {
            // Simple 8-bit per channel copy (RGBA)
            U8* src = srcPixels;
            for (U32 i = 0; i < pixelCount; ++i)
            {
               dest[0] = src[0];
               dest[1] = src[1];
               dest[2] = src[2];
               if (dstBytesPerPixel == 4)
                  dest[3] = src[3];

               src += srcBytesPerPixel;
               dest += dstBytesPerPixel;
            }
         }
      } // face
   } // mip

   glBindTexture(mBinding, 0);
   return true;
}

void GFXGLTextureObject::updateTextureSlot(const GFXTexHandle& texHandle, const U32 slot, const S32 face)
{
   if (!texHandle.isValid())
      return;

   GFXGLTextureObject* srcTex = static_cast<GFXGLTextureObject*>(texHandle.getPointer());
   if (!srcTex || srcTex->getHandle() == 0)
      return;

   const GLenum dstTarget = mBinding;             // destination binding (this)
   const GLenum srcTarget = srcTex->getBinding(); // source binding
   const bool srcIsCube = (srcTarget == GL_TEXTURE_CUBE_MAP || srcTarget == GL_TEXTURE_CUBE_MAP_ARRAY);

   // Determine list of faces to copy from source
   U32 firstFace = 0;
   U32 faceCount = 1;
   if (face >= 0)
   {
      firstFace = (U32)face;
      faceCount = 1;
   }
   else if (srcIsCube)
   {
      firstFace = 0;
      faceCount = 6;
   }
   else
   {
      firstFace = 0;
      faceCount = 1;
   }

   // Ensure textures are valid
   if (!glIsTexture(mHandle) || !glIsTexture(srcTex->getHandle()))
   {
      Con::errorf("updateTextureSlot: invalid GL texture handle src=%u dst=%u", srcTex->getHandle(), mHandle);
      return;
   }

   // If copyImage supported, prefer that. We'll copy face-by-face (one-layer depth = 1)
   if (GFXGL->mCapabilities.copyImage)
   {
      for (U32 mip = 0; mip < getMipLevels(); ++mip)
      {
         const GLsizei mipW = getMax(1u, srcTex->getWidth() >> mip);
         const GLsizei mipH = getMax(1u, srcTex->getHeight() >> mip);

         for (U32 f = firstFace; f < firstFace + faceCount; ++f)
         {
            // Compute source z offset (for cube arrays it's layer index; for cubemap it's face index)
            GLint srcZ = 0;
            if (srcTarget == GL_TEXTURE_CUBE_MAP_ARRAY)
            {
               srcZ = f;
            }
            else if (srcTarget == GL_TEXTURE_CUBE_MAP)
            {
               srcZ = f;
            }
            else
            {
               srcZ = 0; // 2D source
            }

            // Compute destination layer (z offset) depending on destination type
            GLint dstZ = 0;
            if (dstTarget == GL_TEXTURE_CUBE_MAP_ARRAY)
            {
               // each slot is a whole cubemap => slot * 6 + faceIndex
               dstZ = (GLint)(slot * 6 + f);
            }
            else if (dstTarget == GL_TEXTURE_2D_ARRAY)
            {
               dstZ = (GLint)slot; // each slot is a single layer
            }
            else if (dstTarget == GL_TEXTURE_CUBE_MAP)
            {
               dstZ = (GLint)f;
            }
            else
            {
               dstZ = 0; // 2D texture target
            }

            // Copy single layer/face at this mip
            glCopyImageSubData(
               srcTex->getHandle(), srcTarget, mip, 0, 0, srcZ,
               mHandle, dstTarget, mip, 0, 0, dstZ,
               mipW, mipH, 1
            );

            GLenum err = glGetError();
            if (err != GL_NO_ERROR)
               Con::errorf("glCopyImageSubData failed with 0x%X (mip=%u face=%u)", err, mip, f);
         }
      }

      return;
   }

   // Fallback: CPU-side copy using glGetTexImage + glTexSubImage
   for (U32 mip = 0; mip < getMipLevels() && mip < srcTex->getMipLevels(); ++mip)
   {
      const GLsizei mipW = getMax(1u, srcTex->getWidth() >> mip);
      const GLsizei mipH = getMax(1u, srcTex->getHeight() >> mip);
      const U32 pixelSize = GFXFormat_getByteSize(mFormat); // assuming same fmt for src/dst
      const U32 dataSize = mipW * mipH * pixelSize;

      FrameAllocatorMarker mem;
      U8* buffer = (U8*)mem.alloc(dataSize);

      glBindTexture(srcTarget, srcTex->getHandle());
      glBindTexture(dstTarget, mHandle);

      for (U32 f = firstFace; f < firstFace + faceCount; ++f)
      {
         GLenum srcFaceTarget = srcTarget;
         if (srcTarget == GL_TEXTURE_CUBE_MAP)
            srcFaceTarget = GFXGLFaceType[f];

         // read pixels from source
         glGetTexImage(srcFaceTarget, mip, GFXGLTextureFormat[mFormat], GFXGLTextureType[mFormat], buffer);

         GLint dstLayer = 0;
         if (dstTarget == GL_TEXTURE_CUBE_MAP_ARRAY)
            dstLayer = (GLint)(slot * 6 + f);
         else if (dstTarget == GL_TEXTURE_2D_ARRAY)
            dstLayer = (GLint)slot;
         else if (dstTarget == GL_TEXTURE_CUBE_MAP)
            dstLayer = (GLint)f;
         else
            dstLayer = 0;

         if (dstTarget == GL_TEXTURE_CUBE_MAP)
         {
            GLenum dstFaceTarget = GFXGLFaceType[f];
            glTexSubImage2D(dstFaceTarget, mip, 0, 0, mipW, mipH,
               GFXGLTextureFormat[mFormat], GFXGLTextureType[mFormat], buffer);
         }
         else if (dstTarget == GL_TEXTURE_2D)
         {
            glTexSubImage2D(GL_TEXTURE_2D, mip, 0, 0, mipW, mipH,
               GFXGLTextureFormat[mFormat], GFXGLTextureType[mFormat], buffer);
         }
         else if (dstTarget == GL_TEXTURE_2D_ARRAY || dstTarget == GL_TEXTURE_CUBE_MAP_ARRAY)
         {
            glTexSubImage3D(dstTarget, mip, 0, 0, dstLayer, mipW, mipH, 1,
               GFXGLTextureFormat[mFormat], GFXGLTextureType[mFormat], buffer);
         }
      }

      glBindTexture(dstTarget, 0);
      glBindTexture(srcTarget, 0);
   }
}

void GFXGLTextureObject::copyTo(GFXTextureObject* dstTex)
{
}

void GFXGLTextureObject::initSamplerState(const GFXSamplerStateDesc &ssd)
{
   glTexParameteri(mBinding, GL_TEXTURE_MIN_FILTER, minificationFilter(ssd.minFilter, ssd.mipFilter, mMipLevels));
   glTexParameteri(mBinding, GL_TEXTURE_MAG_FILTER, GFXGLTextureFilter[ssd.magFilter]);
   glTexParameteri(mBinding, GL_TEXTURE_WRAP_S, !mIsNPoT2 ? GFXGLTextureAddress[ssd.addressModeU] : GL_CLAMP_TO_EDGE);
   glTexParameteri(mBinding, GL_TEXTURE_WRAP_T, !mIsNPoT2 ? GFXGLTextureAddress[ssd.addressModeV] : GL_CLAMP_TO_EDGE);
   if(mBinding == GL_TEXTURE_3D)
      glTexParameteri(mBinding, GL_TEXTURE_WRAP_R, GFXGLTextureAddress[ssd.addressModeW]);
   if(static_cast< GFXGLDevice* >( GFX )->supportsAnisotropic() )
      glTexParameterf(mBinding, GL_TEXTURE_MAX_ANISOTROPY_EXT, ssd.maxAnisotropy);
  
   mNeedInitSamplerState = false;
   mSampler = ssd;
}

void GFXGLTextureObject::bind(U32 textureUnit)
{
   glActiveTexture(GL_TEXTURE0 + textureUnit);
   glBindTexture(mBinding, mHandle);
   GFXGL->getOpenglCache()->setCacheBindedTex(textureUnit, mBinding, mHandle);
}

U8* GFXGLTextureObject::getTextureData( U32 mip )
{
   AssertFatal( mMipLevels, "");
   mip = (mip < mMipLevels) ? mip : 0;

   const U32 dataSize = ImageUtil::isCompressedFormat(mFormat)
       ? getCompressedSurfaceSize( mFormat, mTextureSize.x, mTextureSize.y, mip )
       : (mTextureSize.x >> mip) * (mTextureSize.y >> mip) * mBytesPerTexel;

   U8* data = new U8[dataSize];
   PRESERVE_TEXTURE(mBinding);
   glBindTexture(mBinding, mHandle);

   if( ImageUtil::isCompressedFormat(mFormat) )
      glGetCompressedTexImage( mBinding, mip, data );
   else
      glGetTexImage(mBinding, mip, GFXGLTextureFormat[mFormat], GFXGLTextureType[mFormat], data);
   return data;
}

void GFXGLTextureObject::copyIntoCache()
{
   PRESERVE_TEXTURE(mBinding);
   glBindTexture(mBinding, mHandle);
   U32 cacheSize = mTextureSize.x * mTextureSize.y;
   if(mBinding == GL_TEXTURE_3D)
      cacheSize *= mTextureSize.z;

   cacheSize *= mBytesPerTexel;
   mZombieCache = new U8[cacheSize];

   glGetTexImage(mBinding, 0, GFXGLTextureFormat[mFormat], GFXGLTextureType[mFormat], mZombieCache);
}

void GFXGLTextureObject::reloadFromCache()
{
   if(!mZombieCache)
      return;

   if(mBinding == GL_TEXTURE_3D)
   {
      static_cast<GFXGLTextureManager*>(TEXMGR)->_loadTexture(this, mZombieCache);
      delete[] mZombieCache;
      mZombieCache = NULL;
      return;
   }

   PRESERVE_TEXTURE(mBinding);
   glBindTexture(mBinding, mHandle);

   if(mBinding == GL_TEXTURE_2D)
		glTexSubImage2D(mBinding, 0, 0, 0, mTextureSize.x, mTextureSize.y, GFXGLTextureFormat[mFormat], GFXGLTextureType[mFormat], mZombieCache);
   else if(mBinding == GL_TEXTURE_1D)
		glTexSubImage1D(mBinding, 0, 0, (mTextureSize.x > 1 ? mTextureSize.x : mTextureSize.y), GFXGLTextureFormat[mFormat], GFXGLTextureType[mFormat], mZombieCache);

   if(mMipLevels != 1)
      glGenerateMipmap(mBinding);

   delete[] mZombieCache;
   mZombieCache = NULL;
   mIsZombie = false;
}

void GFXGLTextureObject::zombify()
{
   if(mIsZombie)
      return;

   mIsZombie = true;
   if(!mProfile->doStoreBitmap() && !mProfile->isRenderTarget() && !mProfile->isDynamic() && !mProfile->isZTarget())
      copyIntoCache();

   release();
}

void GFXGLTextureObject::resurrect()
{
   if(!mIsZombie)
      return;

   glGenTextures(1, &mHandle);
   glGenBuffers(1, &mBuffer);
}

F32 GFXGLTextureObject::getMaxUCoord() const
{
   return mBinding == GL_TEXTURE_2D ? 1.0f : (F32)getWidth();
}

F32 GFXGLTextureObject::getMaxVCoord() const
{
   return mBinding == GL_TEXTURE_2D ? 1.0f : (F32)getHeight();
}

const String GFXGLTextureObject::describeSelf() const
{
   String ret = Parent::describeSelf();
   ret += String::ToString("   GL Handle: %i", mHandle);

   return ret;
}
