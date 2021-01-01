#include "gfxD3D11TextureArray.h"

#include <d3d11.h>

#include "gfxD3D11Device.h"
#include "gfxD3D11EnumTranslate.h"
#include "core/util/tVector.h"
#include "gfx/util/screenspace.h"
#include "shaderGen/shaderFeature.h"


void GFXD3D11TextureArray::init()
{
   mTextureArrayDesc.Width = mWidth;
   mTextureArrayDesc.Height = mHeight;
   mTextureArrayDesc.MipLevels = mMipLevels;
   mTextureArrayDesc.ArraySize = mArraySize;
   mTextureArrayDesc.Format = GFXD3D11TextureFormat[mFormat];
   mTextureArrayDesc.SampleDesc.Count = 1;
   mTextureArrayDesc.SampleDesc.Quality = 0;
   mTextureArrayDesc.Usage = D3D11_USAGE_DEFAULT;
   mTextureArrayDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
   mTextureArrayDesc.CPUAccessFlags = 0;
   mTextureArrayDesc.MiscFlags = 0;

   HRESULT hr = D3D11DEVICE->CreateTexture2D(&mTextureArrayDesc, NULL, &mTextureArray);
   AssertFatal(SUCCEEDED(hr), "GFXD3D11TextureArray::init failed to create texture array!");

   //---------------------------------------------------------------------------------------
   //					Create a resource view to the texture array.
   //---------------------------------------------------------------------------------------
   createResourceView(mTextureArrayDesc.Format, mTextureArrayDesc.MipLevels, mTextureArrayDesc.BindFlags);
   //---------------------------------------------------------------------------------------
}

void GFXD3D11TextureArray::_setTexture(const GFXTexHandle& texture, U32 slot)
{
   GFXD3D11TextureObject *texObj = dynamic_cast<GFXD3D11TextureObject*>(texture.getPointer());
   ID3D11Texture2D* tex2d = texObj->get2DTex();
   D3D11_TEXTURE2D_DESC desc;
   tex2d->GetDesc(&desc);
   // for each mipmap level...
   for (UINT j = 0; j < desc.MipLevels; ++j)
   {
      const U32 srcSubResource = D3D11CalcSubresource(j, 0, desc.MipLevels);
      const U32 dstSubResource = D3D11CalcSubresource(j, slot, mTextureArrayDesc.MipLevels);
      D3D11DEVICECONTEXT->CopySubresourceRegion(mTextureArray, dstSubResource, 0, 0, 0, tex2d, srcSubResource, NULL);
   }
}

void GFXD3D11TextureArray::setToTexUnit(U32 tuNum)
{
   D3D11DEVICECONTEXT->PSSetShaderResources(tuNum, 1, &mSRView);
}

void GFXD3D11TextureArray::createResourceView(DXGI_FORMAT format, U32 numMipLevels, U32 usageFlags)
{
   HRESULT hr;
   if (usageFlags & D3D11_BIND_SHADER_RESOURCE)
   {
      D3D11_SHADER_RESOURCE_VIEW_DESC desc;

      if (usageFlags & D3D11_BIND_DEPTH_STENCIL)
         desc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS; // reads the depth
      else
         desc.Format = format;

      desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
      desc.Texture2DArray.MostDetailedMip = 0;
      desc.Texture2DArray.MipLevels = numMipLevels;
      desc.Texture2DArray.FirstArraySlice = 0;
      desc.Texture2DArray.ArraySize = mArraySize;

      hr = D3D11DEVICE->CreateShaderResourceView(mTextureArray, &desc, &mSRView);
      AssertFatal(SUCCEEDED(hr), "GFXD3D11TextureArray::CreateShaderResourceView failed to create view!");
   }

   if (usageFlags & D3D11_BIND_RENDER_TARGET)
   {
      D3D11_RENDER_TARGET_VIEW_DESC desc;
      desc.Format = format;
      desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
      desc.Texture2DArray.MipSlice = 0;
      desc.Texture2DArray.FirstArraySlice = 0;
      desc.Texture2DArray.ArraySize = mArraySize;
      hr = D3D11DEVICE->CreateRenderTargetView(mTextureArray, &desc, &mRTView);
      AssertFatal(SUCCEEDED(hr), "GFXD3D11TextureArray::CreateRenderTargetView failed to create view!");
   }

   if (usageFlags & D3D11_BIND_DEPTH_STENCIL)
   {
      D3D11_DEPTH_STENCIL_VIEW_DESC desc;
      desc.Format = format;
      desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
      desc.Texture2DArray.MipSlice = 0;
      desc.Texture2DArray.FirstArraySlice = 0;
      desc.Texture2DArray.ArraySize = mArraySize;
      desc.Flags = 0;
      hr = D3D11DEVICE->CreateDepthStencilView(mTextureArray, &desc, &mDSView);
      AssertFatal(SUCCEEDED(hr), "GFXD3D11TextureArray::CreateDepthStencilView failed to create view!");
   }
}


void GFXD3D11TextureArray::Release()
{
   SAFE_RELEASE(mSRView)
   SAFE_RELEASE(mRTView)
   SAFE_RELEASE(mDSView)
   SAFE_RELEASE(mTextureArray)

   GFXTextureArray::Release();
}

ID3D11ShaderResourceView* GFXD3D11TextureArray::getSRView()
{
   return mSRView;
}
ID3D11RenderTargetView* GFXD3D11TextureArray::getRTView()
{
   return mRTView;
}
ID3D11DepthStencilView* GFXD3D11TextureArray::getDSView()
{
   return mDSView;
}

ID3D11ShaderResourceView** GFXD3D11TextureArray::getSRViewPtr()
{
   return &mSRView;
}
ID3D11RenderTargetView** GFXD3D11TextureArray::getRTViewPtr()
{
   return &mRTView;
}

ID3D11DepthStencilView** GFXD3D11TextureArray::getDSViewPtr()
{
   return &mDSView;
}

void GFXD3D11TextureArray::zombify()
{
   // Unsupported
}

void GFXD3D11TextureArray::resurrect()
{
   // Unsupported
}
