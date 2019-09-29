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

#include "gfx/gl/gfxGLDevice.h"
#include "gfx/gl/gfxGLTextureObject.h"
#include "gfx/gl/gfxGLEnumTranslate.h"
#include "gfx/gl/gfxGLUtils.h"
#include "gfx/gl/gfxGLCubemap.h"
#include "gfx/gfxTextureManager.h"
#include "gfx/gfxCardProfile.h"
#include "gfx/bitmap/ddsFile.h"
#include "gfx/bitmap/imageUtils.h"


static GLenum faceList[6] = 
{ 
   GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
   GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
   GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
};

GFXGLCubemap::GFXGLCubemap() :
      mCubemap(0), 
      mDynamicTexSize(0),
      mFaceFormat( GFXFormatR8G8B8A8 )
{
   for(U32 i = 0; i < 6; i++)
      mTextures[i] = NULL;
   
   GFXTextureManager::addEventDelegate( this, &GFXGLCubemap::_onTextureEvent );
}

GFXGLCubemap::~GFXGLCubemap()
{
   glDeleteTextures(1, &mCubemap);
   GFXTextureManager::removeEventDelegate( this, &GFXGLCubemap::_onTextureEvent );
}

GLenum GFXGLCubemap::getEnumForFaceNumber(U32 face)
{ 
   return faceList[face];
}

void GFXGLCubemap::fillCubeTextures(GFXTexHandle* faces)
{
   AssertFatal( faces, "");
   AssertFatal( faces[0]->mMipLevels > 0, "");

   PRESERVE_CUBEMAP_TEXTURE();
   glBindTexture(GL_TEXTURE_CUBE_MAP, mCubemap);
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, faces[0]->mMipLevels - 1 );
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
   
   U32 reqWidth = faces[0]->getWidth();
   U32 reqHeight = faces[0]->getHeight();
   GFXFormat regFaceFormat = faces[0]->getFormat();
   const bool isCompressed = ImageUtil::isCompressedFormat(regFaceFormat);
   mWidth = reqWidth;
   mHeight = reqHeight;
   mFaceFormat = regFaceFormat;
   mMipMapLevels = getMax( (U32)1, faces[0]->mMipLevels);
   AssertFatal(reqWidth == reqHeight, "GFXGLCubemap::fillCubeTextures - Width and height must be equal!");
   
   for(U32 i = 0; i < 6; i++)
   {
      AssertFatal(faces[i], avar("GFXGLCubemap::fillCubeFaces - texture %i is NULL!", i));
      AssertFatal((faces[i]->getWidth() == reqWidth) && (faces[i]->getHeight() == reqHeight), "GFXGLCubemap::fillCubeFaces - All textures must have identical dimensions!");
      AssertFatal(faces[i]->getFormat() == regFaceFormat, "GFXGLCubemap::fillCubeFaces - All textures must have identical formats!");
      
      mTextures[i] = faces[i];
      GFXFormat faceFormat = faces[i]->getFormat();

        GFXGLTextureObject* glTex = static_cast<GFXGLTextureObject*>(faces[i].getPointer());
        if( isCompressed )
        {
            for( U32 mip = 0; mip < mMipMapLevels; ++mip )
            {
                const U32 mipWidth  = getMax( U32(1), faces[i]->getWidth() >> mip );
                const U32 mipHeight = getMax( U32(1), faces[i]->getHeight() >> mip );
                const U32 mipDataSize = getCompressedSurfaceSize( mFaceFormat, mWidth, mHeight, mip );

                U8* buf = glTex->getTextureData( mip );
                glCompressedTexImage2D(faceList[i], mip, GFXGLTextureInternalFormat[mFaceFormat], mipWidth, mipHeight, 0, mipDataSize, buf);
                delete[] buf;
            }
        }
        else
        {
            U8* buf = glTex->getTextureData();
            glTexImage2D(faceList[i], 0, GFXGLTextureInternalFormat[faceFormat], mWidth, mHeight, 
                0, GFXGLTextureFormat[faceFormat], GFXGLTextureType[faceFormat], buf);
            delete[] buf;
        }
   }
   
    if( !isCompressed )
        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
}

void GFXGLCubemap::initStatic(GFXTexHandle* faces)
{
   if(mCubemap)
      return;
      
   if(faces)
   {
      AssertFatal(faces[0], "GFXGLCubemap::initStatic - empty texture passed");
      glGenTextures(1, &mCubemap);
      fillCubeTextures(faces);
   }
   mInitialized = true;
}

void GFXGLCubemap::initStatic( DDSFile *dds )
{
   if(mCubemap)
      return;
      
   AssertFatal( dds, "GFXGLCubemap::initStatic - Got null DDS file!" );
   AssertFatal( dds->isCubemap(), "GFXGLCubemap::initStatic - Got non-cubemap DDS file!" );
   AssertFatal( dds->mSurfaces.size() == 6, "GFXGLCubemap::initStatic - DDS has less than 6 surfaces!" );

   mWidth = dds->getWidth();
   mHeight = dds->getHeight();
   mFaceFormat = dds->getFormat();
   mMipMapLevels = dds->getMipLevels();
   const bool isCompressed = ImageUtil::isCompressedFormat(mFaceFormat);
   glGenTextures(1, &mCubemap);

   PRESERVE_CUBEMAP_TEXTURE();
   glBindTexture(GL_TEXTURE_CUBE_MAP, mCubemap);
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, mMipMapLevels - 1);
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

   AssertFatal(mWidth == mHeight, "GFXGLCubemap::initStatic - Width and height must be equal!");
   
   for(U32 i = 0; i < 6; i++)
   {
      if ( !dds->mSurfaces[i] )
      {
         // TODO: The DDS can skip surfaces, but i'm unsure what i should
         // do here when creating the cubemap.  Ignore it for now.
         continue;
      }

      // convert to Z up
      const U32 faceIndex = zUpFaceIndex(i);

      // Now loop thru the mip levels!
      for (U32 mip = 0; mip < mMipMapLevels; ++mip)
      {
         const U32 mipWidth  = getMax( U32(1), mWidth >> mip );
         const U32 mipHeight = getMax( U32(1), mHeight >> mip );
         if (isCompressed)
            glCompressedTexImage2D(faceList[faceIndex], mip, GFXGLTextureInternalFormat[mFaceFormat], mipWidth, mipHeight, 0, dds->getSurfaceSize(mip), dds->mSurfaces[i]->mMips[mip]);
         else
            glTexImage2D(faceList[faceIndex], mip, GFXGLTextureInternalFormat[mFaceFormat], mipWidth, mipHeight, 0,
               GFXGLTextureFormat[mFaceFormat], GFXGLTextureType[mFaceFormat], dds->mSurfaces[i]->mMips[mip]);
      }
   }
   mInitialized = true;
}

void GFXGLCubemap::initDynamic(U32 texSize, GFXFormat faceFormat, U32 mipLevels)
{
   mDynamicTexSize = texSize;
   mFaceFormat = faceFormat;
   const bool isCompressed = ImageUtil::isCompressedFormat(faceFormat);
   mMipMapLevels = getMax( (U32)1, getMaxMipmaps( texSize, texSize, 1 ) );

   glGenTextures(1, &mCubemap);
   PRESERVE_CUBEMAP_TEXTURE();
   glBindTexture(GL_TEXTURE_CUBE_MAP, mCubemap);
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, mMipMapLevels - 1);
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
   mWidth = texSize;
   mHeight = texSize;

    for(U32 i = 0; i < 6; i++)
    {
        if( ImageUtil::isCompressedFormat(faceFormat) )
        {
            for( U32 mip = 0; mip < mMipMapLevels; ++mip )
            {
                const U32 mipSize = getMax( U32(1), texSize >> mip );
                const U32 mipDataSize = getCompressedSurfaceSize( mFaceFormat, texSize, texSize, mip );
                glCompressedTexImage2D(faceList[i], mip, GFXGLTextureInternalFormat[mFaceFormat], mipSize, mipSize, 0, mipDataSize, NULL);
            }
        }
        else
        {
            glTexImage2D( faceList[i], 0, GFXGLTextureInternalFormat[faceFormat], texSize, texSize, 
                0, GFXGLTextureFormat[faceFormat], GFXGLTextureType[faceFormat], NULL);
        }
    }

    if( !isCompressed )
        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    mInitialized = true;
}

void GFXGLCubemap::zombify()
{
   glDeleteTextures(1, &mCubemap);
   mCubemap = 0;
}

void GFXGLCubemap::resurrect()
{
   // Handled in tmResurrect
}

void GFXGLCubemap::tmResurrect()
{
   if(mDynamicTexSize)
      initDynamic(mDynamicTexSize,mFaceFormat);
   else
   {
      if ( mDDSFile )
         initStatic( mDDSFile );
      else
         initStatic( mTextures );
   }
}

void GFXGLCubemap::setToTexUnit(U32 tuNum)
{
   static_cast<GFXGLDevice*>(getOwningDevice())->setCubemapInternal(tuNum, this);
}

void GFXGLCubemap::bind(U32 textureUnit) const
{
   glActiveTexture(GL_TEXTURE0 + textureUnit);
   glBindTexture(GL_TEXTURE_CUBE_MAP, mCubemap);
   static_cast<GFXGLDevice*>(getOwningDevice())->getOpenglCache()->setCacheBindedTex(textureUnit, GL_TEXTURE_CUBE_MAP, mCubemap);
   
   GFXGLStateBlockRef sb = static_cast<GFXGLDevice*>(GFX)->getCurrentStateBlock();
   AssertFatal(sb, "GFXGLCubemap::bind - No active stateblock!");
   if (!sb)
      return;   
      
   const GFXSamplerStateDesc& ssd = sb->getDesc().samplers[textureUnit];
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, minificationFilter(ssd.minFilter, ssd.mipFilter, 0));   
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GFXGLTextureFilter[ssd.magFilter]);   
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GFXGLTextureAddress[ssd.addressModeU]);
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GFXGLTextureAddress[ssd.addressModeV]);
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GFXGLTextureAddress[ssd.addressModeW]);
}

void GFXGLCubemap::_onTextureEvent( GFXTexCallbackCode code )
{
   if ( code == GFXZombify )
      zombify();
   else
      tmResurrect();
}

U8* GFXGLCubemap::getTextureData(U32 face, U32 mip)
{
   AssertFatal(mMipMapLevels, "");
   mip = (mip < mMipMapLevels) ? mip : 0;
   const U32 bytesPerTexel = 8; //TODO make work with more formats!!!!!
   const U32 dataSize = ImageUtil::isCompressedFormat(mFaceFormat)
      ? getCompressedSurfaceSize(mFaceFormat, mWidth, mHeight, mip)
      : (mWidth >> mip) * (mHeight >> mip) * bytesPerTexel;

   U8* data = new U8[dataSize];
   PRESERVE_TEXTURE(GL_TEXTURE_CUBE_MAP);
   glBindTexture(GL_TEXTURE_CUBE_MAP, mCubemap);

   if (ImageUtil::isCompressedFormat(mFaceFormat))
      glGetCompressedTexImage(faceList[face], mip, data);
   else
      glGetTexImage(faceList[face], mip, GFXGLTextureFormat[mFaceFormat], GFXGLTextureType[mFaceFormat], data);

   return data;
}

//-----------------------------------------------------------------------------
// Cubemap Array
//-----------------------------------------------------------------------------

GFXGLCubemapArray::GFXGLCubemapArray()
{
}

GFXGLCubemapArray::~GFXGLCubemapArray()
{
   glDeleteTextures(1, &mCubemap);
}

//TODO: really need a common private 'init' function to avoid code double up with these init* functions
void GFXGLCubemapArray::init(GFXCubemapHandle *cubemaps, const U32 cubemapCount)
{
   AssertFatal(cubemaps, "GFXGLCubemapArray- Got null GFXCubemapHandle!");
   AssertFatal(*cubemaps, "GFXGLCubemapArray - Got empty cubemap!");

   U32 downscalePower = GFXTextureManager::smTextureReductionLevel;
   U32 scaledSize = cubemaps[0]->getSize();

   if (downscalePower != 0)
   {
      // Otherwise apply the appropriate scale...
      scaledSize >>= downscalePower;
   }

   //all cubemaps must be the same size,format and number of mipmaps. Grab the details from the first cubemap
   mSize = scaledSize;
   mFormat = cubemaps[0]->getFormat();
   mMipMapLevels = cubemaps[0]->getMipMapLevels() - downscalePower;
   mNumCubemaps = cubemapCount;
   const bool isCompressed = ImageUtil::isCompressedFormat(mFormat);

   glGenTextures(1, &mCubemap);
   PRESERVE_CUBEMAP_ARRAY_TEXTURE();
   glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, mCubemap);
   glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MAX_LEVEL, mMin(mMipMapLevels - 1, 1));
   glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

   for (U32 i = 0; i < cubemapCount; i++)
   {
      GFXGLCubemap* glTex = static_cast<GFXGLCubemap*>(cubemaps[i].getPointer());
      for (U32 face = 0; face < 6; face++)
      {
         for (U32 currentMip = 0; currentMip < mMipMapLevels; currentMip++)
         {
            U8 *pixelData = glTex->getTextureData(face, currentMip);

            glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, mCubemap);
            const U32 mipSize = getMax(U32(1), mSize >> currentMip);
            if (isCompressed)
            {
               const U32 mipDataSize = getCompressedSurfaceSize(mFormat, mSize, mSize, currentMip);
               glCompressedTexSubImage3D(GL_TEXTURE_CUBE_MAP_ARRAY, currentMip, 0, 0, i * 6 + face, mipSize, mipSize, 1, GFXGLTextureFormat[mFormat], GFXGLTextureType[mFormat], pixelData);
            }
            else
            {
               glTexSubImage3D(GL_TEXTURE_CUBE_MAP_ARRAY, currentMip, 0, 0, i * 6 + face, mipSize, mipSize, 1, GFXGLTextureFormat[mFormat], GFXGLTextureType[mFormat], pixelData);
            }
            glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, 0);

            delete[] pixelData;
         }
      }
   }
}

//Just allocate the cubemap array but we don't upload any data
void GFXGLCubemapArray::init(const U32 cubemapCount, const U32 cubemapFaceSize, const GFXFormat format)
{
   U32 downscalePower = GFXTextureManager::smTextureReductionLevel;
   U32 scaledSize = cubemapFaceSize;

   if (downscalePower != 0)
   {
      // Otherwise apply the appropriate scale...
      scaledSize >>= downscalePower;
   }

   //all cubemaps must be the same size,format and number of mipmaps. Grab the details from the first cubemap
   mSize = scaledSize;
   mFormat = format;
   mMipMapLevels = ImageUtil::getMaxMipCount(scaledSize, scaledSize);
   mNumCubemaps = cubemapCount;
   const bool isCompressed = ImageUtil::isCompressedFormat(mFormat);

   glGenTextures(1, &mCubemap);
   PRESERVE_CUBEMAP_ARRAY_TEXTURE();
   glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, mCubemap);

   for (U32 i = 0; i < mMipMapLevels; i++)
   {
      const U32 mipSize = getMax(U32(1), mSize >> i);
      glTexImage3D(GL_TEXTURE_CUBE_MAP_ARRAY, i, GFXGLTextureInternalFormat[mFormat], mipSize, mipSize, cubemapCount * 6, 0, GFXGLTextureFormat[mFormat], GFXGLTextureType[mFormat], NULL);
   }

   glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MAX_LEVEL, mMipMapLevels - 1);
   glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void GFXGLCubemapArray::updateTexture(const GFXCubemapHandle &cubemap, const U32 slot)
{
   AssertFatal(slot <= mNumCubemaps, "GFXD3D11CubemapArray::updateTexture - trying to update a cubemap texture that is out of bounds!");
   if (!cubemap->isInitialized())
      return;
   const bool isCompressed = ImageUtil::isCompressedFormat(mFormat);

   GFXGLCubemap* glTex = static_cast<GFXGLCubemap*>(cubemap.getPointer());
   for (U32 face = 0; face < 6; face++)
   {
      for (U32 currentMip = 0; currentMip < mMipMapLevels; currentMip++)
      {
         U8 *pixelData = glTex->getTextureData(face, currentMip);

         glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, mCubemap);
         const U32 mipSize = getMax(U32(1), mSize >> currentMip);
         if (isCompressed)
         {
            const U32 mipDataSize = getCompressedSurfaceSize(mFormat, mSize, mSize, currentMip);
            glCompressedTexSubImage3D(GL_TEXTURE_CUBE_MAP_ARRAY, currentMip, 0, 0, slot * 6 + face, mipSize, mipSize, 1, GFXGLTextureFormat[mFormat], GFXGLTextureType[mFormat], pixelData);
         }
         else
         {                                          
            glTexSubImage3D(GL_TEXTURE_CUBE_MAP_ARRAY, currentMip, 0, 0, slot * 6 + face, mipSize, mipSize, 1, GFXGLTextureFormat[mFormat], GFXGLTextureType[mFormat], pixelData);
         }
         glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, 0);

         delete[] pixelData;
      }
   }
}

void GFXGLCubemapArray::copyTo(GFXCubemapArray *pDstCubemap)
{
   AssertFatal(pDstCubemap, "GFXGLCubemapArray::copyTo - Got null GFXCubemapArray");

   const U32 dstCount = pDstCubemap->getNumCubemaps();
   const GFXFormat dstFmt = pDstCubemap->getFormat();
   const U32 dstSize = pDstCubemap->getSize();
   const U32 dstMips = pDstCubemap->getMipMapLevels();

   AssertFatal(dstCount > mNumCubemaps, "GFXGLCubemapArray::copyTo - Destination too small");
   AssertFatal(dstFmt == mFormat, "GFXGLCubemapArray::copyTo - Destination format doesn't match");
   AssertFatal(dstSize == mSize, "GFXGLCubemapArray::copyTo - Destination size doesn't match");
   AssertFatal(dstMips == mMipMapLevels, "GFXGLCubemapArray::copyTo - Destination mip levels doesn't match");

   GFXGLCubemapArray* pDstCube = static_cast<GFXGLCubemapArray*>(pDstCubemap);

   for (U32 cubeMap = 0; cubeMap < mNumCubemaps; cubeMap++)
   {
      for (U32 face = 0; face < CubeFaces; face++)
      {
         for (U32 currentMip = 0; currentMip < mMipMapLevels; currentMip++)
         //U32 currentMip = 0;
         {
            //U8 *pixelData = pDstCube->get->getTextureData(face, currentMip);
            const U32 mipSize = getMax(U32(1), mSize >> currentMip);
            /*if (isCompressed)
            {
               const U32 mipDataSize = getCompressedSurfaceSize(mFormat, mSize, mSize, currentMip);
               glCompressedTexImage2D(faceList[face], currentMip, GFXGLTextureInternalFormat[mFormat], mipSize, mipSize, 0, mipDataSize, pixelData);
            }
            else
            {*/                                                      //TODO figure out xyzOffsets
            glCopyImageSubData(mCubemap, GL_TEXTURE_CUBE_MAP_ARRAY, currentMip, 0, 0, cubeMap * face, pDstCube->mCubemap, GL_TEXTURE_CUBE_MAP_ARRAY, currentMip, 0, 0, cubeMap * face, mipSize, mipSize, 6);
            //glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, mCubemap);
            //glTexSubImage3D(GL_TEXTURE_CUBE_MAP_ARRAY, currentMip, 0, 0, 0, mipSize, mipSize, CubeFaces, GFXGLTextureFormat[mFormat], GFXGLTextureType[mFormat], pixelData);
            //}
            //delete[] pixelData;
         }
      }
   }
}


void GFXGLCubemapArray::setToTexUnit(U32 tuNum)
{
   static_cast<GFXGLDevice*>(getOwningDevice())->setCubemapArrayInternal(tuNum, this);
}

void GFXGLCubemapArray::bind(U32 textureUnit) const
{
   glActiveTexture(GL_TEXTURE0 + textureUnit);
   glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, mCubemap);
   static_cast<GFXGLDevice*>(getOwningDevice())->getOpenglCache()->setCacheBindedTex(textureUnit, GL_TEXTURE_CUBE_MAP_ARRAY, mCubemap);

   GFXGLStateBlockRef sb = static_cast<GFXGLDevice*>(GFX)->getCurrentStateBlock();
   AssertFatal(sb, "GFXGLCubemap::bind - No active stateblock!");
   if (!sb)
      return;

   const GFXSamplerStateDesc& ssd = sb->getDesc().samplers[textureUnit];
   glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MIN_FILTER, minificationFilter(ssd.minFilter, ssd.mipFilter, 0));
   glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MAG_FILTER, GFXGLTextureFilter[ssd.magFilter]);
   glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_S, GFXGLTextureAddress[ssd.addressModeU]);
   glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_T, GFXGLTextureAddress[ssd.addressModeV]);
   glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_R, GFXGLTextureAddress[ssd.addressModeW]);
}
