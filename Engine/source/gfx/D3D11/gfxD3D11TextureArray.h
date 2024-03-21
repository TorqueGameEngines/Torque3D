#ifndef _GFXD3D11TEXTUREARRAY_H_
#define _GFXD3D11TEXTUREARRAY_H_

#include <dxgiformat.h>


#include "gfx/gfxTextureArray.h"
#include "gfx/gfxTextureManager.h"
#include "core/util/safeRelease.h"
#include "gfxD3D11TextureManager.h"

class GFXD3D11TextureArray : public GFXTextureArray
{
public:
   GFXD3D11TextureArray()
      : mSRView( NULL ),
        mRTView( NULL ),
        mDSView( NULL ),
        mTextureArray( NULL )
   {
   }

   ~GFXD3D11TextureArray() { Release();  };

   void init() override;
   void setToTexUnit(U32 tuNum) override;

   void createResourceView(DXGI_FORMAT format, U32 numMipLevels, U32 usageFlags);

   // GFXResource interface
   void zombify() override;
   void resurrect() override;
   void Release() override;


   ID3D11ShaderResourceView* getSRView();
   ID3D11RenderTargetView* getRTView();
   ID3D11DepthStencilView* getDSView();

   ID3D11ShaderResourceView** getSRViewPtr();
   ID3D11RenderTargetView** getRTViewPtr();
   ID3D11DepthStencilView** getDSViewPtr();

protected:
   void _setTexture(const GFXTexHandle& texture, U32 slot) override;

private:
   ID3D11ShaderResourceView* mSRView; // for shader resource input
   ID3D11RenderTargetView* mRTView; // for render targets
   ID3D11DepthStencilView* mDSView; //render target view for depth stencil
   ID3D11Texture2D* mTextureArray;
   D3D11_TEXTURE2D_DESC mTextureArrayDesc;
};


#endif
