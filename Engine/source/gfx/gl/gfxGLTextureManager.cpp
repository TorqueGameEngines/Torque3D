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
#include "gfx/gl/gfxGLTextureManager.h"
#include "gfx/gl/gfxGLEnumTranslate.h"
#include "gfx/gfxCardProfile.h"
#include "core/util/safeDelete.h"
#include "gfx/gl/gfxGLUtils.h"

#include <squish.h>

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
GFXGLTextureManager::GFXGLTextureManager()
{
}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
GFXGLTextureManager::~GFXGLTextureManager()
{
   SAFE_DELETE_ARRAY( mHashTable );
}

//-----------------------------------------------------------------------------
// createTexture
//-----------------------------------------------------------------------------
GFXTextureObject *GFXGLTextureManager::_createTextureObject(   U32 height, 
                                                               U32 width,
                                                               U32 depth,
                                                               GFXFormat format, 
                                                               GFXTextureProfile *profile, 
                                                               U32 numMipLevels,
                                                               bool forceMips,
                                                               S32 antialiasLevel,
                                                               U32 arraySize,   
                                                               GFXTextureObject *inTex )
{
   AssertFatal(format >= 0 && format < GFXFormat_COUNT, "GFXGLTextureManager::_createTexture - invalid format!");

   GFXGLTextureObject *retTex;
   if ( inTex )
   {
      AssertFatal( dynamic_cast<GFXGLTextureObject*>( inTex ), "GFXGLTextureManager::_createTexture() - Bad inTex type!" );
      retTex = static_cast<GFXGLTextureObject*>( inTex );
      retTex->release();
      retTex->reInit();
   }      
   else
   {
      retTex = new GFXGLTextureObject( GFX, profile );
      retTex->registerResourceWithDevice( GFX );
   }

   innerCreateTexture(retTex, height, width, depth, format, profile, numMipLevels, forceMips, arraySize);

   return retTex;
}

//-----------------------------------------------------------------------------
// innerCreateTexture
//-----------------------------------------------------------------------------
// This just creates the texture, no info is actually loaded to it.  We do that later.
void GFXGLTextureManager::innerCreateTexture( GFXGLTextureObject *retTex, 
                                               U32 height, 
                                               U32 width, 
                                               U32 depth,
                                               GFXFormat format, 
                                               GFXTextureProfile *profile, 
                                               U32 numMipLevels,
                                               bool forceMips,
                                               U32 arraySize)
{
   // No 24 bit formats.  They trigger various oddities because hardware (and Apple's drivers apparently...) don't natively support them.
   if (format == GFXFormatR8G8B8)
      format = GFXFormatR8G8B8A8;
   else if (format == GFXFormatR8G8B8_SRGB)
      format = GFXFormatR8G8B8A8_SRGB;

   retTex->mProfile = profile;
   retTex->mFormat = format;
   retTex->mIsZombie = false;
   retTex->mIsNPoT2 = false;
   
   const bool isCube = profile->isCubeMap();
   GLenum binding;

   if (isCube)
   {
      binding = (arraySize > 1) ? GL_TEXTURE_CUBE_MAP_ARRAY : GL_TEXTURE_CUBE_MAP;
   }
   else
   {
      const bool is3D = (depth > 1);
      const bool is1D = (height == 1 && width > 1);

      if (is3D)
         binding = GL_TEXTURE_3D;
      else if (is1D)
         binding = (arraySize > 1) ? GL_TEXTURE_1D_ARRAY : GL_TEXTURE_1D;
      else
         binding = (arraySize > 1) ? GL_TEXTURE_2D_ARRAY : GL_TEXTURE_2D;
   }

   if((profile->testFlag(GFXTextureProfile::RenderTarget) || profile->testFlag(GFXTextureProfile::ZTarget)) && (!isPow2(width) || !isPow2(height)) && !depth)
      retTex->mIsNPoT2 = true;
   retTex->mBinding = binding;
   
   // Bind it
   PRESERVE_TEXTURE(binding);
   glBindTexture(retTex->getBinding(), retTex->getHandle());
   
   // Create it
   // @todo OPENGL - Creating mipmaps for compressed formats. Not supported on OpenGL ES and bugged on AMD. We use mipmaps present on file.
   if( forceMips && !retTex->mIsNPoT2 && !ImageUtil::isCompressedFormat(format) )
   {
      retTex->mMipLevels = numMipLevels > 1 ? numMipLevels : 0;
   }
   else if(profile->testFlag(GFXTextureProfile::NoMipmap) || numMipLevels == 1)
   {
      retTex->mMipLevels = 1;
   }
   else if (profile->testFlag(GFXTextureProfile::RenderTarget))
   {
         if (numMipLevels == 0) //auto
            numMipLevels = mFloor(mLog2(mMax(width, height))) + 1;
         else if (numMipLevels > 1) //capped
            numMipLevels = mMin(numMipLevels, mFloor(mLog2(mMax(width, height))) + 1);
         retTex->mMipLevels = mClampF(numMipLevels, 1, 13);
   }
   else
   {
      retTex->mMipLevels = numMipLevels;
   }

   // @todo OPENGL - OpenGL ES2 not support mipmaps on NPOT textures
#if 0
   if(!retTex->mIsNPoT2)
   {
      if(!isPow2(width))
         width = getNextPow2(width);
      if(!isPow2(height))
         height = getNextPow2(height);
      if(depth && !isPow2(depth))
         depth = getNextPow2(depth);
   }
#endif
   
   AssertFatal(GFXGLTextureInternalFormat[format] != GL_ZERO, "GFXGLTextureManager::innerCreateTexture - invalid internal format");
   AssertFatal(GFXGLTextureFormat[format] != GL_ZERO, "GFXGLTextureManager::innerCreateTexture - invalid format");
   AssertFatal(GFXGLTextureType[format] != GL_ZERO, "GFXGLTextureManager::innerCreateTexture - invalid type");

   //calculate num mipmaps
   if(retTex->mMipLevels == 0)
      retTex->mMipLevels = getMaxMipmaps(width, height, 1);

    glTexParameteri(binding, GL_TEXTURE_MAX_LEVEL, retTex->mMipLevels-1 );

    bool hasTexStorage = false;
    // not supported when creating these.
    if (arraySize > 1 || isCube || profile->isDynamic())
       hasTexStorage = false;

    const bool isCompressed = ImageUtil::isCompressedFormat(format);

    // --- Allocation by binding ---
    if (binding == GL_TEXTURE_CUBE_MAP)
    {
       // Single cubemap: prefer glTexStorage2D if available, else per-face texImage2D
       if (hasTexStorage)
       {
          // Some drivers accept texStorage2D with GL_TEXTURE_CUBE_MAP
          glTexStorage2D(GL_TEXTURE_CUBE_MAP, retTex->mMipLevels, GFXGLTextureInternalFormat[format], width, height);
       }
       else
       {
          // Explicitly allocate each face/level
          for (U32 face = 0; face < 6; ++face)
          {
             for (U32 mip = 0; mip < retTex->mMipLevels; ++mip)
             {
                U32 mipW = getMax(1u, width >> mip);
                U32 mipH = getMax(1u, height >> mip);

                if (isCompressed)
                {
                   U32 size = getCompressedSurfaceSize(format, width, height, mip);
                   glCompressedTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, mip, GFXGLTextureInternalFormat[format], mipW, mipH, 0, size, nullptr);
                }
                else
                {
                   glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, mip, GFXGLTextureInternalFormat[format], mipW, mipH, 0, GFXGLTextureFormat[format], GFXGLTextureType[format], nullptr);
                }
             }
          }
       }
    }
    else if (binding == GL_TEXTURE_CUBE_MAP_ARRAY)
    {
       // cube-map array: layers = arraySize * 6
       U32 layers = getMax(1u, arraySize) * 6u;
       if (hasTexStorage)
       {
          glTexStorage3D(GL_TEXTURE_CUBE_MAP_ARRAY, retTex->mMipLevels, GFXGLTextureInternalFormat[format], width, height, layers);
       }
       else
       {
          // fallback to glTexImage3D with NULL data
          for (U32 mip = 0; mip < retTex->mMipLevels; ++mip)
          {
             U32 mipW = getMax(1u, width >> mip);
             U32 mipH = getMax(1u, height >> mip);
             glTexImage3D(GL_TEXTURE_CUBE_MAP_ARRAY, mip, GFXGLTextureInternalFormat[format], mipW, mipH, layers, 0, GFXGLTextureFormat[format], GFXGLTextureType[format], NULL);
          }
       }
    }
    else if (binding == GL_TEXTURE_2D_ARRAY)
    {
       // 2D texture array: depth = arraySize (layers)
       U32 layers = getMax(1u, arraySize);
       if (hasTexStorage)
       {
          glTexStorage3D(GL_TEXTURE_2D_ARRAY, retTex->mMipLevels, GFXGLTextureInternalFormat[format], width, height, layers);
       }
       else
       {
          for (U32 mip = 0; mip < retTex->mMipLevels; ++mip)
          {
             U32 mipW = getMax(1u, width >> mip);
             U32 mipH = getMax(1u, height >> mip);
             glTexImage3D(GL_TEXTURE_2D_ARRAY, mip, GFXGLTextureInternalFormat[format], mipW, mipH, layers, 0, GFXGLTextureFormat[format], GFXGLTextureType[format], NULL);
          }
       }
    }
    else if (binding == GL_TEXTURE_1D_ARRAY)
    {
       // 1D array stored as GL_TEXTURE_1D_ARRAY. glTexStorage2D can be used for 1D arrays with height=layers on many drivers.
       U32 layers = getMax(1u, arraySize);
       if (hasTexStorage)
       {
          // glTexStorage2D works for GL_TEXTURE_1D_ARRAY (width, layers)
          glTexStorage2D(GL_TEXTURE_1D_ARRAY, retTex->mMipLevels, GFXGLTextureInternalFormat[format], getMax(width, height), layers);
       }
       else
       {
          // fallback: allocate as 2D where the "height" dimension is layers via glTexImage2D? Not ideal.
          // Safer: use glTexImage2D with target GL_TEXTURE_1D_ARRAY is invalid; instead use glTexImage3D with depth=layers
          for (U32 mip = 0; mip < retTex->mMipLevels; ++mip)
          {
             U32 mipW = getMax(1u, getMax(width, height) >> mip);
             glTexImage3D(GL_TEXTURE_1D_ARRAY, mip, GFXGLTextureInternalFormat[format], mipW, layers, 1, 0, GFXGLTextureFormat[format], GFXGLTextureType[format], NULL);
          }
       }
    }
    else if (binding == GL_TEXTURE_1D)
    {
       if (hasTexStorage)
          glTexStorage1D(GL_TEXTURE_1D, retTex->mMipLevels, GFXGLTextureInternalFormat[format], getMax(width, height));
       else
       {
          for (U32 mip = 0; mip < retTex->mMipLevels; ++mip)
          {
             U32 mipW = getMax(1u, getMax(width, height) >> mip);
             glTexImage1D(GL_TEXTURE_1D, mip, GFXGLTextureInternalFormat[format], mipW, 0, GFXGLTextureFormat[format], GFXGLTextureType[format], NULL);
          }
       }
    }
    else if (binding == GL_TEXTURE_3D)
    {
       if (hasTexStorage)
          glTexStorage3D(GL_TEXTURE_3D, retTex->mMipLevels, GFXGLTextureInternalFormat[format], width, height, depth);
       else
       {
          for (U32 mip = 0; mip < retTex->mMipLevels; ++mip)
          {
             U32 mipW = getMax(1u, width >> mip);
             U32 mipH = getMax(1u, height >> mip);
             U32 mipD = getMax(1u, depth >> mip);
             glTexImage3D(GL_TEXTURE_3D, mip, GFXGLTextureInternalFormat[format], mipW, mipH, mipD, 0, GFXGLTextureFormat[format], GFXGLTextureType[format], NULL);
          }
       }
    }
    else // GL_TEXTURE_2D (default)
    {
       if (hasTexStorage)
          glTexStorage2D(GL_TEXTURE_2D, retTex->mMipLevels, GFXGLTextureInternalFormat[format], width, height);
       else
       {
          for (U32 mip = 0; mip < retTex->mMipLevels; ++mip)
          {
             U32 mipW = getMax(1u, width >> mip);
             U32 mipH = getMax(1u, height >> mip);

             if (isCompressed)
             {
                U32 size = getCompressedSurfaceSize(format, width, height, mip);
                glCompressedTexImage2D(GL_TEXTURE_2D, mip, GFXGLTextureInternalFormat[format], mipW, mipH, 0, size, nullptr);
             }
             else
             {
                glTexImage2D(GL_TEXTURE_2D, mip, GFXGLTextureInternalFormat[format], mipW, mipH, 0, GFXGLTextureFormat[format], GFXGLTextureType[format], NULL);
             }
          }
       }
    }

   
   // Complete the texture
   // Complete the texture - this does get changed later but we need to complete the texture anyway

   if(retTex->mMipLevels == 1)
      glTexParameteri(binding, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   else
      glTexParameteri(binding, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(binding, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(binding, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(binding, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   if(binding == GL_TEXTURE_3D)
      glTexParameteri(binding, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

   if(GFXGLTextureSwizzle[format])         
      glTexParameteriv(binding, GL_TEXTURE_SWIZZLE_RGBA, GFXGLTextureSwizzle[format]);   
   
   GLint texHeight = 0, texWidth = 0, texDepth = 0;

   GLenum queryTarget = binding;
   if (binding == GL_TEXTURE_CUBE_MAP)
   {
      // Query a specific face, e.g. +X
      queryTarget = GL_TEXTURE_CUBE_MAP_POSITIVE_X;
   }

   glGetTexLevelParameteriv(queryTarget, 0, GL_TEXTURE_WIDTH, &texWidth);
   glGetTexLevelParameteriv(queryTarget, 0, GL_TEXTURE_HEIGHT, &texHeight);
   if (binding == GL_TEXTURE_3D)
      glGetTexLevelParameteriv(GL_TEXTURE_3D, 0, GL_TEXTURE_DEPTH, &texDepth);

   retTex->mTextureSize.set(texWidth, texHeight, texDepth);
}

//-----------------------------------------------------------------------------
// loadTexture - GBitmap
//-----------------------------------------------------------------------------

static void _textureUpload(const S32 width, const S32 height,const S32 bytesPerPixel,const GFXGLTextureObject* texture, const GFXFormat fmt, const U8* data,const S32 mip=0, const U32 face = 0, Swizzle<U8, 4> *pSwizzle = NULL)
{
   glBindBuffer(GL_PIXEL_UNPACK_BUFFER, texture->getBuffer());
   U32 bufSize = width * height * bytesPerPixel;
   glBufferData(GL_PIXEL_UNPACK_BUFFER, bufSize, NULL, GL_STREAM_DRAW);

   if(pSwizzle)
   {
      PROFILE_SCOPE(Swizzle32_Upload);
      U8* pboMemory = (U8*)dMalloc(bufSize);
      pSwizzle->ToBuffer(pboMemory, data, bufSize);
      glBufferSubData(GL_PIXEL_UNPACK_BUFFER, 0, bufSize, pboMemory);
      dFree(pboMemory);
   }
   else
   {
      PROFILE_SCOPE(SwizzleNull_Upload);
      glBufferSubData(GL_PIXEL_UNPACK_BUFFER, 0, bufSize, data);
   }

   if(texture->getBinding() == GL_TEXTURE_CUBE_MAP)
      glTexSubImage2D(GFXGLFaceType[face], mip, 0, 0, width, height, GFXGLTextureFormat[fmt], GFXGLTextureType[fmt], NULL);
   else if (texture->getBinding() == GL_TEXTURE_2D)
      glTexSubImage2D(texture->getBinding(), mip, 0, 0, width, height, GFXGLTextureFormat[fmt], GFXGLTextureType[fmt], NULL);
   else
      glTexSubImage1D(texture->getBinding(), mip, 0, (width > 1 ? width : height), GFXGLTextureFormat[fmt], GFXGLTextureType[fmt], NULL);

   glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
}

bool GFXGLTextureManager::_loadTexture(GFXTextureObject *aTexture, GBitmap *pDL)
{
   PROFILE_SCOPE(GFXGLTextureManager_loadTextureGBitmap);
   GFXGLTextureObject *texture = static_cast<GFXGLTextureObject*>(aTexture);

   const GLenum target = texture->getBinding();

   AssertFatal(target == GL_TEXTURE_1D || target == GL_TEXTURE_2D || target == GL_TEXTURE_CUBE_MAP,
      "GFXGLTextureManager::_loadTexture(GBitmap) - This method can only be used with 1D/2D and CubeMap textures");
      
   if(texture->getBinding() == GL_TEXTURE_3D)
      return false;
   //      
   //// No 24bit formats.
   //if(pDL->getFormat() == GFXFormatR8G8B8)
   //   pDL->setFormat(GFXFormatR8G8B8A8);
   //else if (pDL->getFormat() == GFXFormatR8G8B8_SRGB)
   //   pDL->setFormat(GFXFormatR8G8B8A8_SRGB);

   // Bind to edit
   PRESERVE_TEXTURE(texture->getBinding());
   glBindTexture(texture->getBinding(), texture->getHandle());

   const U32 mipLevels = texture->getMipLevels();
   const bool isCubemap = (target == GL_TEXTURE_CUBE_MAP) && pDL->getNumFaces() > 1;
   U32 faceCount = isCubemap ? 6 : 1;

   for (U32 mip = 0; mip < mipLevels; mip++)
   {
      const GLsizei width = getMax(1u, pDL->getWidth(mip));
      const GLsizei height = getMax(1u, pDL->getHeight(mip));
      for (U32 face = 0; face < faceCount; ++face)
      {
         _textureUpload(width, height, pDL->getBytesPerPixel(), texture, pDL->getFormat(), pDL->getBits(mip,face), mip, face);
      }
   }

   if(!ImageUtil::isCompressedFormat(pDL->getFormat()))
      glGenerateMipmap(texture->getBinding());

   glBindTexture(target, 0);
   return true;
}

bool GFXGLTextureManager::_loadTexture(GFXTextureObject *aTexture, DDSFile *dds)
{
	PROFILE_SCOPE(GFXGLTextureManager_loadTextureDDS);
   GFXGLTextureObject* texture = static_cast<GFXGLTextureObject*>(aTexture);

   const GLenum target = texture->getBinding();

   const bool isCube = texture->getBinding() == GL_TEXTURE_CUBE_MAP && dds->isCubemap();
   const bool isCompressed = ImageUtil::isCompressedFormat(texture->mFormat);

   AssertFatal(target == GL_TEXTURE_1D || target == GL_TEXTURE_2D || target == GL_TEXTURE_CUBE_MAP,
	   "GFXGLTextureManager::_loadTexture(DDS) - This method can only be used with 1D/2D and CubeMap textures");

   if (texture->getBinding() == GL_TEXTURE_3D)
	   return false;

   PRESERVE_TEXTURE(target);
   glBindTexture(target, texture->getHandle());

   const U32 numFaces = isCube ? 6 : 1;
   const U32 numMips = dds->mSurfaces[0]->mMips.size();
   const GFXFormat fmt = texture->mFormat;

   for (U32 face = 0; face < numFaces; ++face)
   {
      // Skip empty surfaces
      if (!dds->mSurfaces[face])
         continue;

      for (U32 mip = 0; mip < numMips; ++mip)
      {
         const U32 mipWidth = getMax(1u, dds->getWidth(mip));
         const U32 mipHeight = getMax(1u, dds->getHeight(mip));

			GLenum uploadTarget = target;
         if (isCube)
            uploadTarget = GFXGLFaceType[face];

         if (isCompressed)
         {
            // Handle NPOT workaround
            if ((!isPow2(mipWidth) || !isPow2(mipHeight)) && GFX->getCardProfiler()->queryProfile("GL::Workaround::noCompressedNPoTTextures"))
            {
               U8* uncompressedTex = new U8[mipWidth * mipHeight * 4];
               ImageUtil::decompress(dds->mSurfaces[face]->mMips[mip], uncompressedTex, mipWidth, mipHeight, fmt);
               glTexSubImage2D(uploadTarget,
                  mip, 0, 0, mipWidth, mipHeight, GL_RGBA, GL_UNSIGNED_BYTE, uncompressedTex
               );
               delete[] uncompressedTex;
            }
            else
            {
               glCompressedTexImage2D(uploadTarget,
                  mip, GFXGLTextureInternalFormat[fmt], mipWidth, mipHeight, 0,
                  dds->getSurfaceSize(mip), dds->mSurfaces[face]->mMips[mip]
               );
            }
         }
         else
         {
            Swizzle<U8, 4>* pSwizzle = nullptr;
            if (fmt == GFXFormatR8G8B8A8 || fmt == GFXFormatR8G8B8X8 || fmt == GFXFormatR8G8B8A8_SRGB ||
               fmt == GFXFormatR8G8B8A8_LINEAR_FORCE || fmt == GFXFormatB8G8R8A8)
               pSwizzle = &Swizzles::bgra;

            _textureUpload(
               mipWidth, mipHeight, dds->mBytesPerPixel, texture, fmt,
               dds->mSurfaces[face]->mMips[mip], mip, face, pSwizzle);
         }

      }
   }

   if (numMips != 1 && !isCompressed)
      glGenerateMipmap(texture->getBinding());

   glBindTexture(target, 0);
   return true;
}

bool GFXGLTextureManager::_loadTexture(GFXTextureObject *aTexture, void *raw)
{
   PROFILE_SCOPE(GFXGLTextureManager_loadTextureRaw);
   if(aTexture->getDepth() < 1)
      return false;
   
   GFXGLTextureObject* texture = static_cast<GFXGLTextureObject*>(aTexture);
   
   PRESERVE_3D_TEXTURE();
   glBindTexture(texture->getBinding(), texture->getHandle());
   glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, 0, texture->getWidth(), texture->getHeight(), texture->getDepth(), GFXGLTextureFormat[texture->mFormat], GFXGLTextureType[texture->mFormat], raw);
   
   return true;
}

bool GFXGLTextureManager::_freeTexture(GFXTextureObject *texture, bool zombify /*= false*/)
{
   if(zombify)
      static_cast<GFXGLTextureObject*>(texture)->zombify();
   else
      static_cast<GFXGLTextureObject*>(texture)->release();
      
   return true;
}

bool GFXGLTextureManager::_refreshTexture(GFXTextureObject *texture)
{
   U32 usedStrategies = 0;
   GFXGLTextureObject* realTex = static_cast<GFXGLTextureObject*>(texture);
      
   if(texture->mProfile->doStoreBitmap())
   {
      if(realTex->isZombie())
      {
         realTex->resurrect();
         innerCreateTexture(realTex, texture->getHeight(), texture->getWidth(), texture->getDepth(), texture->mFormat, texture->mProfile, texture->mMipLevels);
      }
      if(texture->mBitmap)
         _loadTexture(texture, texture->mBitmap);
      
      if(texture->mDDS)
         return false;
      
      usedStrategies++;
   }
   
   if(texture->mProfile->isRenderTarget() || texture->mProfile->isDynamic() || texture->mProfile->isZTarget() || !usedStrategies)
   {
      realTex->release();
      realTex->resurrect();
      innerCreateTexture(realTex, texture->getHeight(), texture->getWidth(), texture->getDepth(), texture->mFormat, texture->mProfile, texture->mMipLevels);
      realTex->reloadFromCache();
      usedStrategies++;
   }
   
   AssertFatal(usedStrategies < 2, "GFXGLTextureManager::_refreshTexture - Inconsistent profile flags (store bitmap and dynamic/target");
   
   return true;
}
