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

#include "gfx/D3D11/gfxD3D11Device.h"
#include "gfx/D3D11/gfxD3D11TextureObject.h"
#include "platform/profiler.h"
#include "console/console.h"

#ifdef TORQUE_DEBUG
U32 GFXD3D11TextureObject::mTexCount = 0;
#endif


//	GFXFormatR8G8B8 has now the same behaviour as GFXFormatR8G8B8X8. 
//	This is because 24 bit format are now deprecated by microsoft, for data alignment reason there's no changes beetween 24 and 32 bit formats.
//	DirectX 10-11 both have 24 bit format no longer.
GFXD3D11TextureObject::GFXD3D11TextureObject( GFXDevice * d, GFXTextureProfile *profile, const U32 arraySize) : GFXTextureObject( d, profile )
{
#ifdef D3D11_DEBUG_SPEW
   mTexCount++;
   Con::printf("+ texMake %d %x", mTexCount, this);
#endif
   isManaged = false;
   dMemset(&mLockRect, 0, sizeof(mLockRect));
   dMemset(&mLockBox, 0, sizeof(mLockBox));
   mArraySize = arraySize;
}

GFXD3D11TextureObject::~GFXD3D11TextureObject()
{
   kill();
#ifdef D3D11_DEBUG_SPEW
   mTexCount--;
   Con::printf("+ texkill %d %x", mTexCount, this);
#endif
}

ID3D11Texture2D* GFXD3D11TextureObject::get2DTex() const
{
   ComPtr<ID3D11Texture2D> tex2D;
   if (mD3DTexture) mD3DTexture.As(&tex2D);
   return tex2D.Get();
}

ID3D11Texture3D* GFXD3D11TextureObject::get3DTex() const
{
   ComPtr<ID3D11Texture3D> tex3D;
   if (mD3DTexture) mD3DTexture.As(&tex3D);
   return tex3D.Get();
}

ID3D11Texture2D** GFXD3D11TextureObject::get2DTexPtr()
{
   return reinterpret_cast<ID3D11Texture2D**>(mD3DTexture.GetAddressOf());
}

ID3D11Texture3D** GFXD3D11TextureObject::get3DTexPtr()
{
   return reinterpret_cast<ID3D11Texture3D**>(mD3DTexture.GetAddressOf());
}

ID3D11RenderTargetView** GFXD3D11TextureObject::getCubeFaceRTViewPtr(U32 face)
{
   AssertFatal(isCubeMap(), "Not a cubemap texture!");
   AssertFatal(face < 6, "Invalid cubemap face index!");
   return mCubeRTV[face].GetAddressOf();
}

GFXLockedRect* GFXD3D11TextureObject::lock(U32 mipLevel /*= 0*/, RectI* inRect /*= NULL*/, U32 faceIndex /*= 0*/)
{
   AssertFatal(!mLocked, "GFXD3D11TextureObject::lock - Texture is already locked!");
   AssertFatal(faceIndex < 6 || !isCubeMap(), "Invalid cubemap face index!");

   // Ensure staging texture exists and matches size
   if (!mStagingTex.isValid() ||
      mStagingTex->getWidth() != getWidth() ||
      mStagingTex->getHeight() != getHeight() ||
      mStagingTex->getDepth() != getDepth())
   {
      mStagingTex.set(getWidth(), getHeight(), mFormat, &GFXSystemMemTextureProfile,
         avar("%s() - stagingTex", __FUNCTION__));
   }

   D3D11_MAPPED_SUBRESOURCE mapInfo;

   mLockedSubresource = D3D11CalcSubresource(mipLevel, faceIndex, getMipLevels());
   GFXD3D11TextureObject* staging = (GFXD3D11TextureObject*)&(*mStagingTex);

   HRESULT hr = D3D11DEVICECONTEXT->Map(staging->getResource(), mLockedSubresource, D3D11_MAP_WRITE, 0, &mapInfo);
   if (FAILED(hr))
      AssertFatal(false, "GFXD3D11TextureObject:lock - failed to map render target resource!");

   const bool is3D = mStagingTex->getDepth() != 0;
   const U32 width = mTextureSize.x >> mipLevel;
   const U32 height = mTextureSize.y >> mipLevel;
   const U32 depth = is3D ? mTextureSize.z >> mipLevel : 1;
   U32 offset = 0;

   if (inRect)
   {
      AssertFatal(inRect->point.x + inRect->extent.x <= width, "GFXD3D11TextureObject::lock - Invalid lock rect width!");
      AssertFatal(inRect->point.y + inRect->extent.y <= height, "GFXD3D11TextureObject::lock - Invalid lock rect height!");

      mLockBox.top = inRect->point.y;
      mLockBox.left = inRect->point.x;
      mLockBox.right = inRect->point.x + inRect->extent.x;
      mLockBox.bottom = inRect->point.y + inRect->extent.y;
      mLockBox.back = depth;
      mLockBox.front = 0;

      //calculate offset
      offset = inRect->point.x * getFormatByteSize() + inRect->point.y * mapInfo.RowPitch;
   }
   else
   {
      mLockBox.top = 0;
      mLockBox.left = 0;
      mLockBox.right = width;
      mLockBox.bottom = height;
      mLockBox.back = depth;
      mLockBox.front = 0;

   }

   mLocked = true;
   mLockRect.pBits = static_cast<U8*>(mapInfo.pData) + offset;
   mLockRect.Pitch = mapInfo.RowPitch;

   return reinterpret_cast<GFXLockedRect*>(&mLockRect);
}

void GFXD3D11TextureObject::unlock(U32 mipLevel /*= 0*/, U32 faceIndex /*= 0*/)
{
   AssertFatal(mLocked, "GFXD3D11TextureObject::unlock - Texture is not locked!");
   AssertFatal(faceIndex < 6 || !isCubeMap(), "Invalid cubemap face index!");

   PROFILE_START(GFXD3D11TextureObject_unlock);

   GFXD3D11TextureObject* staging = (GFXD3D11TextureObject*)&(*mStagingTex);

   D3D11DEVICECONTEXT->Unmap(staging->getResource(), mLockedSubresource);

   // Copy from staging back to GPU texture
   D3D11DEVICECONTEXT->CopySubresourceRegion(
      mD3DTexture.Get(),
      mLockedSubresource,
      0, 0, 0,
      staging->getResource(),
      mLockedSubresource,
      &mLockBox
   );

   mLockedSubresource = 0;
   mLocked = false;
   
   PROFILE_END();
}

void GFXD3D11TextureObject::release()
{
   mSRView.Reset();
   mRTView.Reset();
   mDSView.Reset();
   mD3DTexture.Reset();
   mD3DSurface.Reset();

   for (auto& faceRTV : mCubeRTV)
      faceRTV.Reset();
}

void GFXD3D11TextureObject::zombify()
{
   // Managed textures are managed by D3D
   AssertFatal(!mLocked, "GFXD3D11TextureObject::zombify - Cannot zombify a locked texture!");
   if(isManaged)
      return;
   release();
}

void GFXD3D11TextureObject::resurrect()
{
	// Managed textures are managed by D3D
   if(isManaged)
      return;

   static_cast<GFXD3D11TextureManager*>(TEXMGR)->refreshTexture(this);
}

bool GFXD3D11TextureObject::copyToBmp(GBitmap* bmp)
{
   if (!bmp)
      return false;

   AssertFatal(mFormat == GFXFormatR16G16B16A16F || mFormat == GFXFormatR8G8B8A8 ||
      mFormat == GFXFormatR8G8B8A8_LINEAR_FORCE || mFormat == GFXFormatR8G8B8A8_SRGB ||
      mFormat == GFXFormatR8G8B8,
      "GFXD3D11TextureObject::copyToBmp - Unsupported source format.");

   PROFILE_START(GFXD3D11TextureObject_copyToBmp);

   AssertFatal(bmp->getWidth() == getWidth(), "Width mismatch between texture and bitmap.");
   AssertFatal(bmp->getHeight() == getHeight(), "Height mismatch between texture and bitmap.");

   const U32 mipLevels = getMipLevels();
   bmp->setHasTransparency(mHasTransparency);

   // Figure out bytes per pixel
   const bool isFP16 = (bmp->getFormat() == GFXFormatR16G16B16A16F);
   const U32 destBpp = (bmp->getFormat() == GFXFormatR8G8B8 ? 3 :
      bmp->getFormat() == GFXFormatR16G16B16A16F ? 8 : 4);
   const U32 srcBpp = (mFormat == GFXFormatR16G16B16A16F ? 8 : 4);

   // --- Create staging texture ---
   D3D11_TEXTURE2D_DESC desc = {};
   reinterpret_cast<ID3D11Texture2D*>(mD3DTexture.Get())->GetDesc(&desc);
   desc.BindFlags = 0;
   desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
   desc.Usage = D3D11_USAGE_STAGING;
   desc.MiscFlags = 0;

   ComPtr<ID3D11Texture2D> stagingTex;
   HRESULT hr = D3D11DEVICE->CreateTexture2D(&desc, nullptr, stagingTex.GetAddressOf());
   if (FAILED(hr))
   {
      Con::errorf("GFXD3D11TextureObject::copyToBmp - Failed to create staging texture (0x%X)", hr);
      return false;
   }

   // --- Copy texture (handle cubemap or 2D) ---
   const U32 faceCount = isCubeMap() && bmp->getNumFaces() == 6 ? 6 : 1;

   for (U32 face = 0; face < faceCount; ++face)
   {
      for (U32 mip = 0; mip < mipLevels; ++mip)
      {
         const U32 srcSubRes = D3D11CalcSubresource(mip, face, mipLevels);
         // Always map mip-level 0..mipLevels-1 on *slice 0* of the staging texture
         const U32 dstSubRes = D3D11CalcSubresource(mip, face, mipLevels);

         D3D11DEVICECONTEXT->CopySubresourceRegion(
            stagingTex.Get(), dstSubRes, 0, 0, 0,
            mD3DTexture.Get(), srcSubRes, nullptr);

         D3D11_MAPPED_SUBRESOURCE mapped = {};
         hr = D3D11DEVICECONTEXT->Map(stagingTex.Get(), dstSubRes, D3D11_MAP_READ, 0, &mapped);
         if (FAILED(hr))
         {
            Con::errorf("GFXD3D11TextureObject::copyToBmp - Failed to map staging texture (0x%X)", hr);
            return false;
         }

         const U8* src = static_cast<const U8*>(mapped.pData);
         U8* dst = bmp->getWritableBits(mip, face);

         const U32 width = bmp->getWidth(mip);
         const U32 height = bmp->getHeight(mip);

         for (U32 y = 0; y < height; ++y)
         {
            const U8* srcRow = src;
            U8* dstRow = dst;

            for (U32 x = 0; x < width; ++x)
            {
               if (isFP16)
               {
                  dMemcpy(dstRow, srcRow, sizeof(U16) * 4);
               }
               else
               {
                  // Convert BGRA → RGB(A)
                  dstRow[0] = srcRow[2];
                  dstRow[1] = srcRow[1];
                  dstRow[2] = srcRow[0];
                  if (destBpp == 4)
                     dstRow[3] = srcRow[3];
               }
               srcRow += srcBpp;
               dstRow += destBpp;
            }

            src += mapped.RowPitch;
            dst += width * destBpp;
         }

         D3D11DEVICECONTEXT->Unmap(stagingTex.Get(), dstSubRes);
      }
   }

   PROFILE_END();
   return true;
}

void GFXD3D11TextureObject::generateMipMaps()
{
   //Generate mips
   D3D11DEVICECONTEXT->GenerateMips(mSRView.Get());
   //get mip level count
   D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;
   mSRView->GetDesc(&viewDesc);
   mMipLevels = viewDesc.TextureCube.MipLevels;
}

void GFXD3D11TextureObject::updateTextureSlot(const GFXTexHandle& texHandle, const U32 slot, const S32 faceIdx /*=-1*/)
{
   AssertFatal(slot < getArraySize(), "updateTextureSlot - destination slot out of bounds");
   AssertFatal(mFormat == texHandle->getFormat(), "updateTextureSlot - format mismatch");
   AssertFatal(getMipLevels() == texHandle->getMipLevels(), "updateTextureSlot - mip level mismatch");

   GFXD3D11TextureObject* srcTex = static_cast<GFXD3D11TextureObject*>(texHandle.getPointer());

   ID3D11Resource* dstRes = get2DTex();
   ID3D11Resource* srcRes = srcTex->get2DTex();

   const UINT mipLevels = getMipLevels();

   const bool dstIsCube = isCubeMap();
   const bool srcIsCube = srcTex->isCubeMap();

   const UINT dstArraySize = getArraySize();
   const UINT srcArraySize = srcTex->getArraySize();

   // Determine number of faces to copy
   const UINT faceCount = srcIsCube ? 6 : 1;
   const UINT startFace = (faceIdx >= 0) ? faceIdx : 0;
   const UINT endFace = (faceIdx >= 0) ? faceIdx + 1 : faceCount;

   for (UINT face = startFace; face < endFace; ++face)
   {
      // Compute source slice
      const UINT srcSlice = srcIsCube
         ? (srcArraySize > 1 ? face + slot * 6 : face)   // only add slot*6 if it's a cubemap array
         : (srcArraySize > 1 ? face + slot : 0);        // otherwise, single 2D texture or 2D array

      const UINT dstSlice = dstIsCube
         ? (dstArraySize > 1 ? face + slot * 6 : face)  // only add slot*6 if it's a cubemap array
         : (dstArraySize > 1 ? face + slot : 0);        // otherwise, single 2D texture or 2D array

      for (UINT mip = 0; mip < mipLevels; ++mip)
      {
         const UINT srcSubresource = D3D11CalcSubresource(mip, srcSlice, mipLevels);
         const UINT dstSubresource = D3D11CalcSubresource(mip, dstSlice, mipLevels);

         D3D11DEVICECONTEXT->CopySubresourceRegion(dstRes, dstSubresource, 0, 0, 0, srcRes, srcSubresource, nullptr);
      }
   }
}

void GFXD3D11TextureObject::copyTo(GFXTextureObject* dstTex)
{
   AssertFatal(dstTex, "GFXD3D11TextureObject::copyTo - destination is null");

   GFXD3D11TextureObject* pDstTex = static_cast<GFXD3D11TextureObject*>(dstTex);

   ID3D11Texture2D* srcTex = (ID3D11Texture2D*)mD3DTexture.Get();
   ID3D11Texture2D* dstTex2D = pDstTex->get2DTex();

   D3D11_TEXTURE2D_DESC srcDesc, dstDesc;
   srcTex->GetDesc(&srcDesc);
   dstTex2D->GetDesc(&dstDesc);

   // Sanity check – sizes and formats must match for a full copy.
   AssertFatal(srcDesc.Width == dstDesc.Width && srcDesc.Height == dstDesc.Height,
      "GFXD3D11TextureObject::copyTo - Mismatched texture dimensions");
   AssertFatal(srcDesc.Format == dstDesc.Format,
      "GFXD3D11TextureObject::copyTo - Mismatched formats");

   UINT srcMipLevels = srcDesc.MipLevels ? srcDesc.MipLevels : 1;
   UINT dstMipLevels = dstDesc.MipLevels ? dstDesc.MipLevels : 1;
   UINT mipLevels = getMin(srcMipLevels, dstMipLevels);

   UINT srcArraySize = srcDesc.ArraySize;
   UINT dstArraySize = dstDesc.ArraySize;
   UINT arraySize = getMin(srcArraySize, dstArraySize);

   // Handle cube maps and cube map arrays
   bool isCubeSrc = (srcDesc.MiscFlags & D3D11_RESOURCE_MISC_TEXTURECUBE) != 0;

   // In cubemaps, ArraySize is always 6 * numCubes
   if (isCubeSrc) arraySize = srcArraySize; // 6 or 6*nCubes

   for (UINT arraySlice = 0; arraySlice < arraySize; ++arraySlice)
   {
      for (UINT mip = 0; mip < mipLevels; ++mip)
      {
         UINT srcSubresource = D3D11CalcSubresource(mip, arraySlice, srcMipLevels);
         UINT dstSubresource = D3D11CalcSubresource(mip, arraySlice, dstMipLevels);

         D3D11DEVICECONTEXT->CopySubresourceRegion(
            dstTex2D, dstSubresource,
            0, 0, 0,
            srcTex, srcSubresource,
            nullptr);
      }
   }
}
