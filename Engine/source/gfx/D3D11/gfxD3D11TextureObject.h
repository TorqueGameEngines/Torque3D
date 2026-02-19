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

#ifndef _GFXD3D11TEXTUREOBJECT_H_
#define _GFXD3D11TEXTUREOBJECT_H_

#include "gfx/D3D11/gfxD3D11Device.h"
#include "gfx/gfxTextureHandle.h"
#include "gfx/gfxTextureManager.h"

#include <wrl/client.h>
using Microsoft::WRL::ComPtr;

class GFXD3D11TextureObject : public GFXTextureObject
{
protected:
   static U32 mTexCount;

   GFXTexHandle mStagingTex;
   DXGI_MAPPED_RECT mLockRect;
   D3D11_BOX mLockBox;
   bool mLocked = false;

   U32 mLockedSubresource = 0;

   // Main GPU texture resource (2D / 3D / Cubemap)
   ComPtr<ID3D11Resource> mD3DTexture;

   // Used for Z-targets
   ComPtr<ID3D11Texture2D> mD3DSurface;

   // Views
   ComPtr<ID3D11ShaderResourceView> mSRView; // Shader resource
   ComPtr<ID3D11RenderTargetView>   mRTView; // Render target
   ComPtr<ID3D11DepthStencilView>   mDSView; // Depth stencil

   // Cubemap face render target views (optional)
   ComPtr<ID3D11RenderTargetView>   mCubeRTV[6];
public:

   GFXD3D11TextureObject( GFXDevice * d, GFXTextureProfile *profile, const U32 arraySize = 1);
   ~GFXD3D11TextureObject();

   // Accessors
   ID3D11Resource* getResource() const { return mD3DTexture.Get(); }
   ID3D11Texture2D* get2DTex() const;
   ID3D11Texture3D* get3DTex() const;
   ID3D11Texture2D** get2DTexPtr();
   ID3D11Texture3D** get3DTexPtr();

   ID3D11ShaderResourceView* getSRView() const { return mSRView.Get(); }
   ID3D11RenderTargetView* getRTView() const { return mRTView.Get(); }
   ID3D11DepthStencilView* getDSView() const { return mDSView.Get(); }

   ID3D11ShaderResourceView** getSRViewPtr() { return mSRView.GetAddressOf(); }
   ID3D11RenderTargetView** getRTViewPtr() { return mRTView.GetAddressOf(); }
   ID3D11DepthStencilView** getDSViewPtr() { return mDSView.GetAddressOf(); }

   // Cubemap face RTV access (for render-to-cubemap)
   ID3D11RenderTargetView* getCubeFaceRTView(U32 face) const
   {
      AssertFatal(isCubeMap(), "Not a cubemap texture!");
      AssertFatal(face < 6, "Invalid cubemap face index!");
      return mCubeRTV[face].Get();
   }

   ID3D11RenderTargetView** getCubeFaceRTViewPtr(U32 face);

   void release();

   bool isManaged; //setting to true tells this texture not to be released from being zombify

   GFXLockedRect* lock(U32 mipLevel = 0, RectI* inRect = NULL, U32 faceIndex = 0) override;
   void unlock(U32 mipLevel = 0, U32 faceIndex = 0) override;

   bool			copyToBmp(GBitmap* bmp) override;
   void generateMipMaps() override;
   void updateTextureSlot(const GFXTexHandle& texHandle, const U32 slot, const S32 face = -1) override;
   void copyTo(GFXTextureObject* dstTex) override;
   ID3D11Texture2D*		getSurface() {return mD3DSurface.Get();}
   ID3D11Texture2D**	getSurfacePtr() {return mD3DSurface.GetAddressOf();}

   // GFXResource
   void zombify() override;
   void resurrect() override;

#ifdef TORQUE_DEBUG
   void pureVirtualCrash() override {};
#endif
};


#endif
