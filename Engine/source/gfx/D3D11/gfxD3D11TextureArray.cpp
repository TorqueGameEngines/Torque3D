#include "gfxD3D11TextureArray.h"

#include <d3d11.h>

#include "gfxD3D11Device.h"
#include "gfxD3D11EnumTranslate.h"
#include "core/util/tVector.h"
#include "gfx/gfxDebugEvent.h"
#include "gfx/bitmap/imageUtils.h"
#include "gfx/util/screenspace.h"
#include "shaderGen/shaderFeature.h"


bool GFXD3D11TextureArray::fromTextureArray(const Vector<GFXTexHandle> &textureArray)
{
   bool success = true;
   Vector<ID3D11Texture2D*> texture2Ds;
   texture2Ds.setSize(textureArray.size());
   Vector<GFXTexHandle> tmpHandles;

   mArraySize = textureArray.size();

   //---------------------------------------------------------------------------------------
   //	Create the texture array.  Each element in the texture 
   //		array has the same format/dimensions.
   //---------------------------------------------------------------------------------------
   D3D11_TEXTURE2D_DESC texElementDesc;
   GFXFormat format;
   bool found = false;
   for (U32 idx = 0; idx < mArraySize; ++idx)
   {
      GFXTexHandle texObj = textureArray[idx];
      if (texObj.isValid())
      {
         if (!found)
         {
            dynamic_cast<GFXD3D11TextureObject*>(texObj.getPointer())->get2DTex()->GetDesc(&texElementDesc);
            found = true;
            format = texObj.getFormat();
         }

         if (format != texObj.getFormat() || texElementDesc.Width != texObj.getWidth() || texElementDesc.Height != texObj.getHeight())
         {
            AssertWarn(true, "GFXGLTextureArray::fromTextureArray there was a mismatch in texture formats, defaulting to uncompressed format");
            Con::warnf("GFXGLTextureArray::fromTextureArray there was a mismatch in texture formats, defaulting to uncompressed format");
            success = false;
            format = GFXFormatR8G8B8A8;
         }
      }
   }

   // One might think this should return false in this case, but the return value is mostly to highlight internal errors not input errors.
   if (!found) return true;

   for (U32 idx = 0; idx < mArraySize; ++idx)
   {
      texture2Ds[idx] = NULL;

      if(textureArray[idx].isValid())
      {
         GFXTexHandle handle = textureArray[idx];
         if (textureArray[idx]->getPath().isNotEmpty())
         {
            D3D11_TEXTURE2D_DESC desc;
            ID3D11Texture2D* tex = dynamic_cast<GFXD3D11TextureObject*>(textureArray[idx].getPointer())->get2DTex();
            tex->GetDesc(&desc);
            if (desc.Height != texElementDesc.Height || desc.Width != texElementDesc.Width || textureArray[idx].getFormat() != format)
            {
               if (desc.Height != texElementDesc.Height || desc.Width != texElementDesc.Width)
               {
                  AssertWarn(true, "GFXD3D11TextureArray::fromTextureArray all textures should be the same size");
                  Con::warnf("GFXD3D11TextureArray::fromTextureArray all textures should be the same size");
               }
               else
               {
                  AssertWarn(true, "GFXD3D11TextureArray::fromTextureArray all textures should have the same format");
                  Con::warnf("GFXD3D11TextureArray::fromTextureArray all textures should have the same format");
               }

               GBitmap* inBitmap = TEXMGR->loadUncompressedTexture(textureArray[idx]->getPath(), &GFXTexturePersistentProfile, texElementDesc.Width, texElementDesc.Height);
               if (!inBitmap->setFormat(format))
               {
                  AssertWarn(true, "GFXD3D11TextureArray::fromTextureArray all textures must be convertible to GFXFormatR8G8B8A8");
                  Con::errorf("GFXD3D11TextureArray::fromTextureArray all textures must be convertible to GFXFormatR8G8B8A8");
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
            D3D11_TEXTURE2D_DESC desc;
            ID3D11Texture2D* tex = dynamic_cast<GFXD3D11TextureObject*>(handle.getPointer())->get2DTex();
            tex->GetDesc(&desc);
            if (desc.Height != texElementDesc.Height || desc.Width != texElementDesc.Width || handle.getFormat() != format)
            {
               AssertWarn(true, "GFXD3D11TextureArray::fromTextureArray all textures must have the same size and format");
               Con::errorf("GFXD3D11TextureArray::fromTextureArray all textures must have the same size and format");
               success = false;
            }
            texture2Ds[idx] = dynamic_cast<GFXD3D11TextureObject*>(handle.getPointer())->get2DTex();
         }
      }
   }

   D3D11_TEXTURE2D_DESC texArrayDesc;
   texArrayDesc.Width = texElementDesc.Width;
   texArrayDesc.Height = texElementDesc.Height;
   texArrayDesc.MipLevels = texElementDesc.MipLevels;
   texArrayDesc.ArraySize = mArraySize;
   texArrayDesc.Format = GFXD3D11TextureFormat[format];
   texArrayDesc.SampleDesc.Count = 1;
   texArrayDesc.SampleDesc.Quality = 0;
   texArrayDesc.Usage = D3D11_USAGE_DEFAULT;
   texArrayDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
   texArrayDesc.CPUAccessFlags = 0;
   texArrayDesc.MiscFlags = 0;

   HRESULT hr = D3D11DEVICE->CreateTexture2D(&texArrayDesc, NULL, &mTextureArray);
   AssertFatal(SUCCEEDED(hr), "GFXD3D11TextureArray::_createTextureArray failed to create texture array!");
   //---------------------------------------------------------------------------------------


   //---------------------------------------------------------------------------------------
   //	Copy individual texture elements into texture array.
   //---------------------------------------------------------------------------------------
   // for each texture element...
   for (UINT i = 0; i < mArraySize; ++i)
   {
      if (texture2Ds[i] == NULL)
      {
         continue;
      }
      D3D11_TEXTURE2D_DESC desc;
      texture2Ds[i]->GetDesc(&desc);
      // for each mipmap level...
      for (UINT j = 0; j < desc.MipLevels; ++j)
      {
         const U32 srcSubResource = D3D11CalcSubresource(j, 0, desc.MipLevels);
         const U32 dstSubResource = D3D11CalcSubresource(j, i, texArrayDesc.MipLevels);
         D3D11DEVICECONTEXT->CopySubresourceRegion(mTextureArray, dstSubResource, 0, 0, 0, texture2Ds[i], srcSubResource, NULL);
      }
   }

   // Clean temporary textures
   for (GFXTexHandle handle : tmpHandles)
   {
      handle.free();
   }
   //---------------------------------------------------------------------------------------


   //---------------------------------------------------------------------------------------
   //					Create a resource view to the texture array.
   //---------------------------------------------------------------------------------------
   createResourceView(texArrayDesc.Format, texArrayDesc.MipLevels, texArrayDesc.BindFlags);
   //---------------------------------------------------------------------------------------

   return success;
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
