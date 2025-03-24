//-----------------------------------------------------------------------------
// Copyright (c) 2015 GarageGames, LLC
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

#include "gfx/D3D11/gfxD3D11Cubemap.h"
#include "gfx/gfxCardProfile.h"
#include "gfx/gfxTextureManager.h"
#include "gfx/D3D11/gfxD3D11EnumTranslate.h"
#include "gfx/bitmap/imageUtils.h"

GFXD3D11Cubemap::GFXD3D11Cubemap() : mTexture(NULL), mSRView(NULL), mDSView(NULL), mTexSize(0)
{
	mDynamic = false;
   mAutoGenMips = false;
	mFaceFormat = GFXFormatR8G8B8A8;
   for (U32 i = 0; i < CubeFaces; i++)
	{
         mRTView[i] = NULL;
	}
}

GFXD3D11Cubemap::~GFXD3D11Cubemap()
{
	releaseSurfaces();
}

void GFXD3D11Cubemap::releaseSurfaces()
{
   if (mDynamic)
		GFXTextureManager::removeEventDelegate(this, &GFXD3D11Cubemap::_onTextureEvent);

   for (U32 i = 0; i < CubeFaces; i++)
	{
         SAFE_RELEASE(mRTView[i]);
	}

   SAFE_RELEASE(mDSView);
   SAFE_RELEASE(mSRView);
	SAFE_RELEASE(mTexture);
}

void GFXD3D11Cubemap::_onTextureEvent(GFXTexCallbackCode code)
{
   if (code == GFXZombify)
      releaseSurfaces();
   else if (code == GFXResurrect)
      initDynamic(mTexSize);
}

void GFXD3D11Cubemap::_init(U32 size, GFXFormat format, U32 mipLevels, bool isDynamic, DDSFile* dds, GFXTexHandle* faces) {
   releaseSurfaces();

   mTexSize = size;
   mFaceFormat = format;
   mMipMapLevels = mipLevels;
   mDynamic = isDynamic;
   mAutoGenMips = (mipLevels == 0);
   bool compressed = ImageUtil::isCompressedFormat(mFaceFormat);

   UINT bindFlags = D3D11_BIND_SHADER_RESOURCE;
   UINT miscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
   if (!compressed) {
      bindFlags |= D3D11_BIND_RENDER_TARGET;
      miscFlags |= D3D11_RESOURCE_MISC_GENERATE_MIPS;
   }

   D3D11_TEXTURE2D_DESC desc = {};
   desc.Width = mTexSize;
   desc.Height = mTexSize;
   desc.MipLevels = mAutoGenMips ? 0 : mMipMapLevels;
   desc.ArraySize = CubeFaces;
   desc.Format = GFXD3D11TextureFormat[mFaceFormat];
   desc.SampleDesc.Count = 1;
   desc.Usage = D3D11_USAGE_DEFAULT;
   desc.BindFlags = bindFlags;
   desc.CPUAccessFlags = 0;
   desc.MiscFlags = miscFlags;

   D3D11_SUBRESOURCE_DATA* pData = nullptr;
   if (dds) {
      pData = new D3D11_SUBRESOURCE_DATA[CubeFaces * mMipMapLevels];
      for (U32 i = 0; i < CubeFaces; i++) {
         U32 faceIndex = zUpFaceIndex(i);
         for (U32 mip = 0; mip < mMipMapLevels; mip++) {
            U32 index = faceIndex * mMipMapLevels + mip;
            pData[index].pSysMem = dds->mSurfaces[i]->mMips[mip];
            pData[index].SysMemPitch = dds->getSurfacePitch(mip);
            pData[index].SysMemSlicePitch = 0;
         }
      }
   }

   HRESULT hr = D3D11DEVICE->CreateTexture2D(&desc, pData, &mTexture);
   delete[] pData;
   AssertFatal(SUCCEEDED(hr), "GFXD3D11Cubemap::_init - CreateTexture2D failed");

   if (faces)
   {
      for (U32 i = 0; i < CubeFaces; i++)
      {
         GFXD3D11TextureObject* texObj = static_cast<GFXD3D11TextureObject*>((GFXTextureObject*)faces[i]);
         for (U32 currentMip = 0; currentMip < mMipMapLevels; currentMip++)
         {
            U32 subResource = D3D11CalcSubresource(currentMip, i, mMipMapLevels);
            D3D11DEVICECONTEXT->CopySubresourceRegion(mTexture, subResource, 0, 0, 0, texObj->get2DTex(), currentMip, NULL);
         }
      }
   }

   D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc = {};
   viewDesc.Format = GFXD3D11TextureFormat[mFaceFormat];
   viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
   viewDesc.TextureCube.MipLevels = mAutoGenMips ? -1 : mMipMapLevels;

   hr = D3D11DEVICE->CreateShaderResourceView(mTexture, &viewDesc, &mSRView);
   AssertFatal(SUCCEEDED(hr), "GFXD3D11Cubemap::_init - CreateShaderResourceView failed");

   if (mAutoGenMips && !compressed) {
      D3D11DEVICECONTEXT->GenerateMips(mSRView);
      //get mip level count
      D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;
      mSRView->GetDesc(&viewDesc);
      mMipMapLevels = viewDesc.TextureCube.MipLevels;
   }

   if (isDynamic) {
      for (U32 i = 0; i < CubeFaces; i++) {
         D3D11_RENDER_TARGET_VIEW_DESC rtViewDesc = {};
         rtViewDesc.Format = desc.Format;
         rtViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
         rtViewDesc.Texture2DArray.MipSlice = 0;
         rtViewDesc.Texture2DArray.FirstArraySlice = i;
         rtViewDesc.Texture2DArray.ArraySize = 1;
         hr = D3D11DEVICE->CreateRenderTargetView(mTexture, &rtViewDesc, &mRTView[i]);
         AssertFatal(SUCCEEDED(hr), "GFXD3D11Cubemap::_init - CreateRenderTargetView failed");
      }
   }
}


void GFXD3D11Cubemap::initStatic(GFXTexHandle *faces)
{
   AssertFatal( faces, "GFXD3D11Cubemap::initStatic - Got null GFXTexHandle!" );
	AssertFatal( *faces, "empty texture passed to CubeMap::create" );
  
   _init(faces->getWidth(), faces->getFormat(), faces->getPointer()->getMipLevels(), false, nullptr, faces);

}

void GFXD3D11Cubemap::initStatic(DDSFile *dds)
{
   AssertFatal(dds, "GFXD3D11Cubemap::initStatic - Got null DDS file!");
   AssertFatal(dds->isCubemap(), "GFXD3D11Cubemap::initStatic - Got non-cubemap DDS file!");
   AssertFatal(dds->mSurfaces.size() == 6, "GFXD3D11Cubemap::initStatic - DDS has less than 6 surfaces!");  
   
   _init(dds->getWidth(), dds->getFormat(), dds->getMipLevels(), false, dds, nullptr);
}

void GFXD3D11Cubemap::initDynamic(U32 texSize, GFXFormat faceFormat, U32 mipLevels)
{
   _init(texSize, faceFormat, mipLevels, true);
}

void GFXD3D11Cubemap::generateMipMaps()
{
   //Generate mips
   D3D11DEVICECONTEXT->GenerateMips(mSRView);
   //get mip level count
   D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;
   mSRView->GetDesc(&viewDesc);
   mMipMapLevels = viewDesc.TextureCube.MipLevels;
}

//-----------------------------------------------------------------------------
// Set the cubemap to the specified texture unit num
//-----------------------------------------------------------------------------
void GFXD3D11Cubemap::setToTexUnit(U32 tuNum)
{
   D3D11DEVICECONTEXT->PSSetShaderResources(tuNum, 1, &mSRView);
}

void GFXD3D11Cubemap::zombify()
{
   // Static cubemaps are handled by D3D
   if( mDynamic )
      releaseSurfaces();
}

void GFXD3D11Cubemap::resurrect()
{
   // Static cubemaps are handled by D3D
   if( mDynamic )
      initDynamic( mTexSize, mFaceFormat );
}

ID3D11ShaderResourceView* GFXD3D11Cubemap::getSRView()
{
   return mSRView;
}

ID3D11RenderTargetView* GFXD3D11Cubemap::getRTView(U32 faceIdx)
{
   AssertFatal(faceIdx < CubeFaces, "GFXD3D11Cubemap::getRTView - face index out of bounds");

   return mRTView[faceIdx];
}

ID3D11DepthStencilView* GFXD3D11Cubemap::getDSView()
{
   return mDSView;
}

ID3D11Texture2D* GFXD3D11Cubemap::get2DTex()
{
   return mTexture;
}

//-----------------------------------------------------------------------------
// Cubemap Array
//-----------------------------------------------------------------------------

GFXD3D11CubemapArray::GFXD3D11CubemapArray() : mTexture(NULL), mSRView(NULL)
{
}

GFXD3D11CubemapArray::~GFXD3D11CubemapArray()
{
   SAFE_RELEASE(mSRView);
   SAFE_RELEASE(mTexture);
}

void GFXD3D11CubemapArray::_init(U32 cubemapCount, U32 size, GFXFormat format) {
   SAFE_RELEASE(mSRView);
   SAFE_RELEASE(mTexture);

   mNumCubemaps = cubemapCount;
   mSize = size;
   mFormat = format;

   UINT bindFlags = D3D11_BIND_SHADER_RESOURCE;
   UINT miscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;

   D3D11_TEXTURE2D_DESC desc = {};
   desc.Width = mSize;
   desc.Height = mSize;
   desc.MipLevels = mMipMapLevels;
   desc.ArraySize = CubeFaces * cubemapCount;
   desc.Format = GFXD3D11TextureFormat[mFormat];
   desc.SampleDesc.Count = 1;
   desc.Usage = D3D11_USAGE_DEFAULT;
   desc.BindFlags = bindFlags;
   desc.MiscFlags = miscFlags;
   desc.CPUAccessFlags = 0;

   if (desc.ArraySize > D3D11_REQ_TEXTURE2D_ARRAY_AXIS_DIMENSION)
   {
      AssertFatal(false, avar("CubemapArray size exceeds maximum array size of %d", D3D11_REQ_TEXTURE2D_ARRAY_AXIS_DIMENSION));
      return;
   }

   HRESULT hr = D3D11DEVICE->CreateTexture2D(&desc, NULL, &mTexture);
   AssertFatal(SUCCEEDED(hr), "GFXD3D11CubemapArray::_init - CreateTexture2D failed");

   D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc = {};
   viewDesc.Format = GFXD3D11TextureFormat[mFormat];
   viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBEARRAY;
   viewDesc.TextureCubeArray.MipLevels = mMipMapLevels;
   viewDesc.TextureCubeArray.MostDetailedMip = 0;
   viewDesc.TextureCubeArray.NumCubes = mNumCubemaps;
   viewDesc.TextureCubeArray.First2DArrayFace = 0;

   hr = D3D11DEVICE->CreateShaderResourceView(mTexture, &viewDesc, &mSRView);
   AssertFatal(SUCCEEDED(hr), "GFXD3D11CubemapArray::_init - CreateShaderResourceView failed");
}

//TODO: really need a common private 'init' function to avoid code double up with these init* functions
void GFXD3D11CubemapArray::init(GFXCubemapHandle *cubemaps, const U32 cubemapCount)
{
   AssertFatal(cubemaps, "GFXD3D11CubemapArray::initStatic - Got null GFXCubemapHandle!");
   AssertFatal(*cubemaps, "GFXD3D11CubemapArray::initStatic - Got empty cubemap!");
   setCubeTexSize(cubemaps);

   _init(cubemapCount, cubemaps[0]->getSize(), cubemaps[0]->getFormat());

}

//Just allocate the cubemap array but we don't upload any data
void GFXD3D11CubemapArray::init(const U32 cubemapCount, const U32 cubemapFaceSize, const GFXFormat format)
{
   setCubeTexSize(cubemapFaceSize);

   _init(cubemapCount, cubemapFaceSize, format);
}

void GFXD3D11CubemapArray::updateTexture(const GFXCubemapHandle &cubemap, const U32 slot)
{
   AssertFatal(slot <= mNumCubemaps, "GFXD3D11CubemapArray::updateTexture - trying to update a cubemap texture that is out of bounds!");
   AssertFatal(mFormat == cubemap->getFormat(), "GFXD3D11CubemapArray::updateTexture - Destination format doesn't match");
   AssertFatal(mMipMapLevels == cubemap->getMipMapLevels(), "GFXD3D11CubemapArray::updateTexture - Destination mip levels doesn't match");

   if (mSize != cubemap->getSize() || mFormat != cubemap->getFormat() || mMipMapLevels != cubemap->getMipMapLevels()) {
      _init(mNumCubemaps, cubemap->getSize(), cubemap->getFormat());
   }

   GFXD3D11Cubemap* pCubeObj = static_cast<GFXD3D11Cubemap*>((GFXCubemap*)cubemap);
   ID3D11Resource* pDstRes = pCubeObj->get2DTex();
   for (U32 face = 0; face < CubeFaces; face++) {
      const U32 arraySlice = face + CubeFaces * slot;
      for (U32 currentMip = 0; currentMip < mMipMapLevels; currentMip++) {
         const U32 srcSubResource = D3D11CalcSubresource(currentMip, face, mMipMapLevels);
         const U32 dstSubResource = D3D11CalcSubresource(currentMip, arraySlice, mMipMapLevels);
         D3D11DEVICECONTEXT->CopySubresourceRegion(mTexture, dstSubResource, 0, 0, 0, pDstRes, srcSubResource, NULL);
      }
   }
}

void GFXD3D11CubemapArray::copyTo(GFXCubemapArray* pDstCubemap) {
   AssertFatal(pDstCubemap, "GFXD3D11CubemapArray::copyTo - Got null GFXCubemapArray");

   if (pDstCubemap->getSize() != mSize || pDstCubemap->getFormat() != mFormat || pDstCubemap->getMipMapLevels() != mMipMapLevels) {
      pDstCubemap->init(mNumCubemaps, mSize, mFormat);
   }

   GFXD3D11CubemapArray* pDstCube = static_cast<GFXD3D11CubemapArray*>(pDstCubemap);
   ID3D11Resource* pDstRes = pDstCube->get2DTex();
   for (U32 cubeMap = 0; cubeMap < mNumCubemaps; cubeMap++) {
      for (U32 face = 0; face < CubeFaces; face++) {
         const U32 arraySlice = face + CubeFaces * cubeMap;
         for (U32 currentMip = 0; currentMip < mMipMapLevels; currentMip++) {
            const U32 subResource = D3D11CalcSubresource(currentMip, arraySlice, mMipMapLevels);
            D3D11DEVICECONTEXT->CopySubresourceRegion(pDstRes, subResource, 0, 0, 0, mTexture, subResource, NULL);
         }
      }
   }
}

void GFXD3D11CubemapArray::setToTexUnit(U32 tuNum)
{
   D3D11DEVICECONTEXT->PSSetShaderResources(tuNum, 1, &mSRView);
}

void GFXD3D11CubemapArray::zombify()
{
   // Static cubemaps are handled by D3D
}

void GFXD3D11CubemapArray::resurrect()
{
   // Static cubemaps are handled by D3D
}
