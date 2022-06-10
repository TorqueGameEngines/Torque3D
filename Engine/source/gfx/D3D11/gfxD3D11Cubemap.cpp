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
      for(U32 j=0; j < MaxMipMaps; j++)
         mRTView[i][j] = NULL;
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
      for (U32 j = 0; j < MaxMipMaps; j++)
         SAFE_RELEASE(mRTView[i][j]);
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

void GFXD3D11Cubemap::initStatic(GFXTexHandle *faces)
{
   AssertFatal( faces, "GFXD3D11Cubemap::initStatic - Got null GFXTexHandle!" );
	AssertFatal( *faces, "empty texture passed to CubeMap::create" );
  
	// NOTE - check tex sizes on all faces - they MUST be all same size
	mTexSize = faces->getWidth();
	mFaceFormat = faces->getFormat();
   bool compressed = ImageUtil::isCompressedFormat(mFaceFormat);

   UINT bindFlags = D3D11_BIND_SHADER_RESOURCE;
   UINT miscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
   if (!compressed)
   {
      bindFlags |= D3D11_BIND_RENDER_TARGET;
      miscFlags |= D3D11_RESOURCE_MISC_GENERATE_MIPS;
   }

   mMipMapLevels = faces->getPointer()->getMipLevels();
   if (mMipMapLevels < 1 && !compressed)
      mAutoGenMips = true;

	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
	desc.Width = mTexSize;
	desc.Height = mTexSize;
   desc.MipLevels = mAutoGenMips ? 0 : mMipMapLevels;
	desc.ArraySize = CubeFaces;
	desc.Format = GFXD3D11TextureFormat[mFaceFormat];
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = bindFlags;
	desc.MiscFlags = miscFlags;
	desc.CPUAccessFlags = 0;

	HRESULT hr = D3D11DEVICE->CreateTexture2D(&desc, NULL, &mTexture);

	if (FAILED(hr))
	{
		AssertFatal(false, "GFXD3D11Cubemap:initStatic(GFXTexhandle *faces) - CreateTexture2D failure");
	}
   
   for (U32 i = 0; i < CubeFaces; i++)
   {
      GFXD3D11TextureObject *texObj = static_cast<GFXD3D11TextureObject*>((GFXTextureObject*)faces[i]);
      for (U32 currentMip = 0; currentMip < mMipMapLevels; currentMip++)
      {
         U32 subResource = D3D11CalcSubresource(currentMip, i, mMipMapLevels);
         D3D11DEVICECONTEXT->CopySubresourceRegion(mTexture, subResource, 0, 0, 0, texObj->get2DTex(), currentMip, NULL);
      }
   }
   
	D3D11_SHADER_RESOURCE_VIEW_DESC SMViewDesc;
	SMViewDesc.Format = GFXD3D11TextureFormat[mFaceFormat];
	SMViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
   SMViewDesc.TextureCube.MipLevels = mAutoGenMips ? -1 : mMipMapLevels;
	SMViewDesc.TextureCube.MostDetailedMip = 0;

	hr = D3D11DEVICE->CreateShaderResourceView(mTexture, &SMViewDesc, &mSRView);
	if (FAILED(hr))
	{
		AssertFatal(false, "GFXD3D11Cubemap::initStatic(GFXTexHandle *faces) - texcube shader resource view  creation failure");
	} 

   //Generate mips
   if (mAutoGenMips && !compressed)
   {
      D3D11DEVICECONTEXT->GenerateMips(mSRView);
      //get mip level count
      D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;
      mSRView->GetDesc(&viewDesc);
      mMipMapLevels = viewDesc.TextureCube.MipLevels;
   }

}

void GFXD3D11Cubemap::initStatic(DDSFile *dds)
{
   AssertFatal(dds, "GFXD3D11Cubemap::initStatic - Got null DDS file!");
   AssertFatal(dds->isCubemap(), "GFXD3D11Cubemap::initStatic - Got non-cubemap DDS file!");
   AssertFatal(dds->mSurfaces.size() == 6, "GFXD3D11Cubemap::initStatic - DDS has less than 6 surfaces!");  
   
   // NOTE - check tex sizes on all faces - they MUST be all same size
   mTexSize = dds->getWidth();
   mFaceFormat = dds->getFormat();
   mMipMapLevels = dds->getMipLevels();

	D3D11_TEXTURE2D_DESC desc;

	desc.Width = mTexSize;
	desc.Height = mTexSize;
   desc.MipLevels = mMipMapLevels;
	desc.ArraySize = CubeFaces;
	desc.Format = GFXD3D11TextureFormat[mFaceFormat];
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_IMMUTABLE;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;

	D3D11_SUBRESOURCE_DATA* pData = new D3D11_SUBRESOURCE_DATA[CubeFaces * mMipMapLevels];
   for (U32 currentFace = 0; currentFace < CubeFaces; currentFace++)
	{
		if (!dds->mSurfaces[currentFace])
			continue;

      // convert to Z up
      const U32 faceIndex = zUpFaceIndex(currentFace);

		for(U32 currentMip = 0; currentMip < mMipMapLevels; currentMip++)
		{
         const U32 dataIndex = faceIndex * mMipMapLevels + currentMip;
			pData[dataIndex].pSysMem = dds->mSurfaces[currentFace]->mMips[currentMip];
			pData[dataIndex].SysMemPitch = dds->getSurfacePitch(currentMip);
         pData[dataIndex].SysMemSlicePitch = 0;
		}

	}

   HRESULT hr = D3D11DEVICE->CreateTexture2D(&desc, pData, &mTexture);
   if (FAILED(hr))
   {
      AssertFatal(false, "GFXD3D11Cubemap::initStatic(DDSFile *dds) - CreateTexture2D failure");
   }

	delete [] pData;

	D3D11_SHADER_RESOURCE_VIEW_DESC SMViewDesc;
	SMViewDesc.Format = GFXD3D11TextureFormat[mFaceFormat];
	SMViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
	SMViewDesc.TextureCube.MipLevels = mMipMapLevels;
	SMViewDesc.TextureCube.MostDetailedMip = 0;

	hr = D3D11DEVICE->CreateShaderResourceView(mTexture, &SMViewDesc, &mSRView);

	if(FAILED(hr)) 
	{
		AssertFatal(false, "GFXD3D11Cubemap::initStatic(DDSFile *dds) - CreateTexture2D call failure");
	}
}

void GFXD3D11Cubemap::initDynamic(U32 texSize, GFXFormat faceFormat, U32 mipLevels)
{
	if(!mDynamic)
		GFXTextureManager::addEventDelegate(this, &GFXD3D11Cubemap::_onTextureEvent);

	mDynamic = true;
	mTexSize = texSize;
	mFaceFormat = faceFormat;
    if (!mipLevels)
       mAutoGenMips = true;

    mMipMapLevels = mipLevels;

   bool compressed = ImageUtil::isCompressedFormat(mFaceFormat);

   UINT bindFlags = D3D11_BIND_SHADER_RESOURCE;
   UINT miscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
   if (!compressed)
   {
      bindFlags |= D3D11_BIND_RENDER_TARGET;
      miscFlags |= D3D11_RESOURCE_MISC_GENERATE_MIPS;
   }

	D3D11_TEXTURE2D_DESC desc;

	desc.Width = mTexSize;
	desc.Height = mTexSize;
	desc.MipLevels = mMipMapLevels;
	desc.ArraySize = 6;
	desc.Format = GFXD3D11TextureFormat[mFaceFormat];
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
   desc.BindFlags = bindFlags;
	desc.CPUAccessFlags = 0;
   desc.MiscFlags = miscFlags;


	HRESULT hr = D3D11DEVICE->CreateTexture2D(&desc, NULL, &mTexture);

	D3D11_SHADER_RESOURCE_VIEW_DESC SMViewDesc;
	SMViewDesc.Format = GFXD3D11TextureFormat[mFaceFormat];
	SMViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
   SMViewDesc.TextureCube.MipLevels = mAutoGenMips ? -1 : mMipMapLevels;
	SMViewDesc.TextureCube.MostDetailedMip = 0;

	hr = D3D11DEVICE->CreateShaderResourceView(mTexture, &SMViewDesc, &mSRView);


	if(FAILED(hr)) 
	{
		AssertFatal(false, "GFXD3D11Cubemap::initDynamic - CreateTexture2D call failure");
	}

   //Generate mips
   if (mAutoGenMips && !compressed)
   {
      D3D11DEVICECONTEXT->GenerateMips(mSRView);
      //get mip level count
      D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;
      mSRView->GetDesc(&viewDesc);
      mMipMapLevels = viewDesc.TextureCube.MipLevels;
   }

   D3D11_RENDER_TARGET_VIEW_DESC viewDesc;
	viewDesc.Format = desc.Format;
	viewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
	viewDesc.Texture2DArray.ArraySize = 1;

   for (U32 i = 0; i < CubeFaces; i++)
   {
	  viewDesc.Texture2DArray.FirstArraySlice = i;
      for (U32 j = 0; j < mMipMapLevels; j++)
      {
         viewDesc.Texture2DArray.MipSlice = j;
         hr = D3D11DEVICE->CreateRenderTargetView(mTexture, &viewDesc, &mRTView[i][j]);

         if (FAILED(hr))
         {
            AssertFatal(false, "GFXD3D11Cubemap::initDynamic - CreateRenderTargetView call failure");
         }
      }
   }

   D3D11_TEXTURE2D_DESC depthTexDesc;
   depthTexDesc.Width = mTexSize;
   depthTexDesc.Height = mTexSize;
   depthTexDesc.MipLevels = 1;
   depthTexDesc.ArraySize = 1;
   depthTexDesc.SampleDesc.Count = 1;
   depthTexDesc.SampleDesc.Quality = 0;
   depthTexDesc.Format = DXGI_FORMAT_D32_FLOAT;
   depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
   depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
   depthTexDesc.CPUAccessFlags = 0;
   depthTexDesc.MiscFlags = 0;

   ID3D11Texture2D* depthTex = 0;
   hr = D3D11DEVICE->CreateTexture2D(&depthTexDesc, 0, &depthTex);

	if(FAILED(hr)) 
	{
		AssertFatal(false, "GFXD3D11Cubemap::initDynamic - CreateTexture2D for depth stencil call failure");
	}

   // Create the depth stencil view for the entire cube
   D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
   dsvDesc.Format = depthTexDesc.Format; //The format must match the depth texture we created above
   dsvDesc.Flags  = 0;
   dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
   dsvDesc.Texture2D.MipSlice = 0;
   hr = D3D11DEVICE->CreateDepthStencilView(depthTex, &dsvDesc, &mDSView);

	if(FAILED(hr)) 
	{
      AssertFatal(false, "GFXD3D11Cubemap::initDynamic - CreateDepthStencilView call failure");
	}

   SAFE_RELEASE(depthTex);

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

ID3D11RenderTargetView* GFXD3D11Cubemap::getRTView(U32 faceIdx, U32 mipIndex)
{
   AssertFatal(faceIdx < CubeFaces, "GFXD3D11Cubemap::getRTView - face index out of bounds");

   return mRTView[faceIdx][mipIndex];
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

//TODO: really need a common private 'init' function to avoid code double up with these init* functions
void GFXD3D11CubemapArray::init(GFXCubemapHandle *cubemaps, const U32 cubemapCount)
{
   AssertFatal(cubemaps, "GFXD3D11CubemapArray::initStatic - Got null GFXCubemapHandle!");
   AssertFatal(*cubemaps, "GFXD3D11CubemapArray::initStatic - Got empty cubemap!");

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

   //create texture object
   UINT bindFlags = D3D11_BIND_SHADER_RESOURCE;
   UINT miscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;

   D3D11_TEXTURE2D_DESC desc;
   ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
   desc.Width = mSize;
   desc.Height = mSize;
   desc.MipLevels = mMipMapLevels;
   desc.ArraySize = CubeFaces * cubemapCount;
   desc.Format = GFXD3D11TextureFormat[mFormat];
   desc.SampleDesc.Count = 1;
   desc.SampleDesc.Quality = 0;
   desc.Usage = D3D11_USAGE_DEFAULT;
   desc.BindFlags = bindFlags;
   desc.MiscFlags = miscFlags;
   desc.CPUAccessFlags = 0;

   HRESULT hr = D3D11DEVICE->CreateTexture2D(&desc, NULL, &mTexture);

   if (FAILED(hr))
      AssertFatal(false, "GFXD3D11CubemapArray::initStatic - CreateTexture2D failure");

   for (U32 i = 0; i < cubemapCount; i++)
   {
      GFXD3D11Cubemap *cubeObj = static_cast<GFXD3D11Cubemap*>((GFXCubemap*)cubemaps[i]);
      //yes checking the first one(cubemap at index 0) is pointless but saves a further if statement
      if (cubemaps[i]->getSize() != mSize || cubemaps[i]->getFormat() != mFormat || cubemaps[i]->getMipMapLevels() != mMipMapLevels)
      {
         Con::printf("Trying to add an invalid Cubemap to a CubemapArray");
         //destroy array here first
         AssertFatal(false, "GFXD3D11CubemapArray::initStatic - invalid cubemap");
      }

      for (U32 face = 0; face < CubeFaces; face++)
      {
         const U32 arraySlice = face + CubeFaces * i;
         for (U32 currentMip = 0; currentMip < mMipMapLevels; currentMip++)
         {
            const U32 srcSubResource = D3D11CalcSubresource(currentMip, face, mMipMapLevels);
            const U32 dstSubResource = D3D11CalcSubresource(currentMip, arraySlice, mMipMapLevels);
            D3D11DEVICECONTEXT->CopySubresourceRegion(mTexture, dstSubResource, 0, 0, 0, cubeObj->get2DTex(), srcSubResource, NULL);
         }
      }
   }

   //create shader resource view
   D3D11_SHADER_RESOURCE_VIEW_DESC SMViewDesc;
   SMViewDesc.Format = GFXD3D11TextureFormat[mFormat];
   SMViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBEARRAY;
   SMViewDesc.TextureCubeArray.MipLevels = mMipMapLevels;
   SMViewDesc.TextureCubeArray.MostDetailedMip = 0;
   SMViewDesc.TextureCubeArray.NumCubes = mNumCubemaps;
   SMViewDesc.TextureCubeArray.First2DArrayFace = 0;

   hr = D3D11DEVICE->CreateShaderResourceView(mTexture, &SMViewDesc, &mSRView);
   if (FAILED(hr))
      AssertFatal(false, "GFXD3D11CubemapArray::initStatic - shader resource view  creation failure");

}

//Just allocate the cubemap array but we don't upload any data
void GFXD3D11CubemapArray::init(const U32 cubemapCount, const U32 cubemapFaceSize, const GFXFormat format)
{
   U32 downscalePower = GFXTextureManager::smTextureReductionLevel;
   U32 scaledSize = cubemapFaceSize;

   if (downscalePower != 0)
   {
      scaledSize >>= downscalePower;
   }

   mSize = scaledSize;
   mMipMapLevels = ImageUtil::getMaxMipCount(cubemapFaceSize, cubemapFaceSize) - downscalePower;
   mNumCubemaps = cubemapCount;
   mFormat = format;

   //create texture object
   UINT bindFlags = D3D11_BIND_SHADER_RESOURCE;
   UINT miscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;

   D3D11_TEXTURE2D_DESC desc;
   ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
   desc.Width = mSize;
   desc.Height = mSize;
   desc.MipLevels = mMipMapLevels;
   desc.ArraySize = CubeFaces * cubemapCount;
   desc.Format = GFXD3D11TextureFormat[mFormat];
   desc.SampleDesc.Count = 1;
   desc.SampleDesc.Quality = 0;
   desc.Usage = D3D11_USAGE_DEFAULT;
   desc.BindFlags = bindFlags;
   desc.MiscFlags = miscFlags;
   desc.CPUAccessFlags = 0;

   HRESULT hr = D3D11DEVICE->CreateTexture2D(&desc, NULL, &mTexture);

   if (FAILED(hr))
      AssertFatal(false, "GFXD3D11CubemapArray::initStatic - CreateTexture2D failure");

   //create shader resource view
   D3D11_SHADER_RESOURCE_VIEW_DESC SMViewDesc;
   SMViewDesc.Format = GFXD3D11TextureFormat[mFormat];
   SMViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBEARRAY;
   SMViewDesc.TextureCubeArray.MipLevels = mMipMapLevels;
   SMViewDesc.TextureCubeArray.MostDetailedMip = 0;
   SMViewDesc.TextureCubeArray.NumCubes = mNumCubemaps;
   SMViewDesc.TextureCubeArray.First2DArrayFace = 0;

   hr = D3D11DEVICE->CreateShaderResourceView(mTexture, &SMViewDesc, &mSRView);
   if (FAILED(hr))
      AssertFatal(false, "GFXD3D11CubemapArray::initStatic - shader resource view  creation failure");

}

void GFXD3D11CubemapArray::updateTexture(const GFXCubemapHandle &cubemap, const U32 slot)
{
   AssertFatal(slot <= mNumCubemaps, "GFXD3D11CubemapArray::updateTexture - trying to update a cubemap texture that is out of bounds!");
   AssertFatal(mFormat == cubemap->getFormat(), "GFXD3D11CubemapArray::updateTexture - Destination format doesn't match");
   AssertFatal(mSize == cubemap->getSize(), "GFXD3D11CubemapArray::updateTexture - Destination size doesn't match");
   AssertFatal(mMipMapLevels == cubemap->getMipMapLevels(), "GFXD3D11CubemapArray::updateTexture - Destination mip levels doesn't match");

   GFXD3D11Cubemap *pCubeObj = static_cast<GFXD3D11Cubemap*>((GFXCubemap*)cubemap);
   ID3D11Resource *pDstRes = pCubeObj->get2DTex();
   for (U32 face = 0; face < CubeFaces; face++)
   {
      const U32 arraySlice = face + CubeFaces * slot;
      for (U32 currentMip = 0; currentMip < mMipMapLevels; currentMip++)
      {
         const U32 srcSubResource = D3D11CalcSubresource(currentMip, face, mMipMapLevels);
         const U32 dstSubResource = D3D11CalcSubresource(currentMip, arraySlice, mMipMapLevels);
         D3D11DEVICECONTEXT->CopySubresourceRegion(mTexture, dstSubResource, 0, 0, 0, pDstRes, srcSubResource, NULL);
      }
   }
}

void GFXD3D11CubemapArray::copyTo(GFXCubemapArray *pDstCubemap)
{
   AssertFatal(pDstCubemap, "GFXD3D11CubemapArray::copyTo - Got null GFXCubemapArray");
   AssertFatal(pDstCubemap->getNumCubemaps() > mNumCubemaps, "GFXD3D11CubemapArray::copyTo - Destination too small");
   AssertFatal(pDstCubemap->getFormat() == mFormat, "GFXD3D11CubemapArray::copyTo - Destination format doesn't match");
   AssertFatal(pDstCubemap->getSize() == mSize, "GFXD3D11CubemapArray::copyTo - Destination size doesn't match");
   AssertFatal(pDstCubemap->getMipMapLevels() == mMipMapLevels, "GFXD3D11CubemapArray::copyTo - Destination mip levels doesn't match");

   GFXD3D11CubemapArray *pDstCube = static_cast<GFXD3D11CubemapArray*>(pDstCubemap);
   ID3D11Resource *pDstRes = pDstCube->get2DTex();
   for (U32 cubeMap = 0; cubeMap < mNumCubemaps; cubeMap++)
   {
      for (U32 face = 0; face < CubeFaces; face++)
      {
         const U32 arraySlice = face + CubeFaces * cubeMap;
         for (U32 currentMip = 0; currentMip < mMipMapLevels; currentMip++)
         {
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
