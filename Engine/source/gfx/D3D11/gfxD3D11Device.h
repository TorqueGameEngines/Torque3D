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

#ifndef _GFXD3D11DEVICE_H_
#define _GFXD3D11DEVICE_H_

#include <d3d11_1.h>

#include "platform/tmm_off.h"
#include "platformWin32/platformWin32.h"
#include "gfx/D3D11/gfxD3D11Shader.h"
#include "gfx/D3D11/gfxD3D11StateBlock.h"
#include "gfx/D3D11/gfxD3D11TextureManager.h"
#include "gfx/D3D11/gfxD3D11Cubemap.h"
#include "gfx/D3D11/gfxD3D11PrimitiveBuffer.h"
#include "gfx/gfxInit.h"
#include "gfx/gfxResource.h"
#include "platform/tmm_on.h"

#define D3D11 static_cast<GFXD3D11Device*>(GFX)
#define D3D11DEVICE D3D11->getDevice()
#define D3D11DEVICECONTEXT D3D11->getDeviceContext()

class PlatformWindow;
class GFXD3D11ShaderConstBuffer;
class OculusVRHMDDevice;
class D3D11OculusTexture;

//------------------------------------------------------------------------------

class GFXD3D11Device : public GFXDevice
{
public:
   typedef Map<U32, ID3D11SamplerState*> SamplerMap;
   typedef Map<String, ID3D11Buffer*> DeviceBufferMap;
private:

   friend class GFXResource;
   friend class GFXD3D11PrimitiveBuffer;
   friend class GFXD3D11VertexBuffer;
   friend class GFXD3D11TextureObject;
   friend class GFXD3D11TextureTarget;
   friend class GFXD3D11WindowTarget;
	friend class OculusVRHMDDevice;
	friend class D3D11OculusTexture;

   GFXFormat selectSupportedFormat(GFXTextureProfile *profile,
   const Vector<GFXFormat> &formats, bool texture, bool mustblend, bool mustfilter) override;

   void enumerateVideoModes() override;

   GFXWindowTarget *allocWindowTarget(PlatformWindow *window) override;
   GFXTextureTarget *allocRenderToTextureTarget(bool genMips = true) override;

   void enterDebugEvent(ColorI color, const char *name) override;
   void leaveDebugEvent() override;
   void setDebugMarker(ColorI color, const char *name) override;

protected:

   class D3D11VertexDecl : public GFXVertexDecl
   {
   public:
      D3D11VertexDecl() :decl(NULL) {}
      virtual ~D3D11VertexDecl()
      {
         SAFE_RELEASE( decl );
      }

      ID3D11InputLayout *decl;
   };

   void initStates() override { };

   static GFXAdapter::CreateDeviceInstanceDelegate mCreateDeviceInstance;

   MatrixF mTempMatrix;    ///< Temporary matrix, no assurances on value at all
   RectI mClipRect;

   typedef StrongRefPtr<GFXD3D11VertexBuffer> RPGDVB;
   Vector<RPGDVB> mVolatileVBList;

   /// Used to lookup a vertex declaration for the vertex format.
   /// @see allocVertexDecl
   typedef Map<String,D3D11VertexDecl*> VertexDeclMap;
   VertexDeclMap mVertexDecls;

   /// Used to lookup sampler state for a given hash key
   SamplerMap mSamplersMap;
   DeviceBufferMap mDeviceBufferMap;

   ID3D11RenderTargetView* mDeviceBackBufferView;
   ID3D11DepthStencilView* mDeviceDepthStencilView;

   ID3D11Texture2D *mDeviceBackbuffer;
   ID3D11Texture2D *mDeviceDepthStencil;

   /// The stream 0 vertex buffer used for volatile VB offseting.
   GFXD3D11VertexBuffer *mVolatileVB;

   //-----------------------------------------------------------------------
   StrongRefPtr<GFXD3D11PrimitiveBuffer> mDynamicPB;
   GFXD3D11PrimitiveBuffer *mCurrentPB;

   ID3D11VertexShader *mLastVertShader;
   ID3D11PixelShader *mLastPixShader;
   ID3D11GeometryShader *mLastGeoShader;

   S32 mCreateFenceType;

   IDXGISwapChain *mSwapChain;
   ID3D11Device* mD3DDevice;
   ID3D11DeviceContext* mD3DDeviceContext;

   GFXShaderRef mGenericShader[GS_COUNT];
   GFXShaderConstBufferRef mGenericShaderBuffer[GS_COUNT];
   GFXShaderConstHandle *mModelViewProjSC[GS_COUNT];

   U32  mAdapterIndex;

   F32 mPixVersion;

   D3D_FEATURE_LEVEL mFeatureLevel;
   // Shader Model targers
   String mVertexShaderTarget;
   String mPixelShaderTarget;
   String mGeometryShaderTarget;
   // String for use with shader macros in the form of shader model version * 10
   String mShaderModel;
   bool mDebugLayers;

   DXGI_SAMPLE_DESC mMultisampleDesc;

   bool mOcclusionQuerySupported;

   U32 mDrawInstancesCount;

   /// To manage creating and re-creating of these when device is aquired
   void reacquireDefaultPoolResources();

   /// To release all resources we control from D3DPOOL_DEFAULT
   void releaseDefaultPoolResources();

   virtual GFXD3D11VertexBuffer* findVBPool( const GFXVertexFormat *vertexFormat, U32 numVertsNeeded );
   virtual GFXD3D11VertexBuffer* createVBPool( const GFXVertexFormat *vertexFormat, U32 vertSize );

   // State overrides
   // {

   ///
   void setTextureInternal(U32 textureUnit, const GFXTextureObject* texture) override;

   /// Called by GFXDevice to create a device specific stateblock
   GFXStateBlockRef createStateBlockInternal(const GFXStateBlockDesc& desc) override;
   /// Called by GFXDevice to actually set a stateblock.
   void setStateBlockInternal(GFXStateBlock* block, bool force) override;

   /// Track the last const buffer we've used.  Used to notify new constant buffers that
   /// they should send all of their constants up
   StrongRefPtr<GFXD3D11ShaderConstBuffer> mCurrentConstBuffer;
   /// Called by base GFXDevice to actually set a const buffer
   void setShaderConstBufferInternal(GFXShaderConstBuffer* buffer) override;

   // }

   // Index buffer management
   // {
   virtual void _setPrimitiveBuffer( GFXPrimitiveBuffer *buffer );
   void drawIndexedPrimitive(  GFXPrimitiveType primType,
                                       U32 startVertex,
                                       U32 minIndex,
                                       U32 numVerts,
                                       U32 startIndex,
                                       U32 primitiveCount ) override;
   // }

   GFXShader* createShader() override;

   /// Device helper function
   virtual DXGI_SWAP_CHAIN_DESC setupPresentParams( const GFXVideoMode &mode, const HWND &hwnd );

   String _createTempShaderInternal(const GFXVertexFormat *vertexFormat);
   // Supress any debug layer messages we don't want to see
   void _suppressDebugMessages();

public:

   static GFXDevice *createInstance( U32 adapterIndex );

   static void enumerateAdapters( Vector<GFXAdapter*> &adapterList );

   ID3D11DepthStencilView* getDepthStencilView() { return mDeviceDepthStencilView; }
   ID3D11RenderTargetView* getRenderTargetView() { return mDeviceBackBufferView; }
   ID3D11Texture2D* getBackBufferTexture() { return mDeviceBackbuffer; }

   /// Constructor
   /// @param   d3d   Direct3D object to instantiate this device with
   /// @param   index   Adapter index since D3D can use multiple graphics adapters
   GFXD3D11Device( U32 index );
   virtual ~GFXD3D11Device();

   // Activate/deactivate
   // {
   void init( const GFXVideoMode &mode, PlatformWindow *window = NULL ) override;

   void preDestroy() override { GFXDevice::preDestroy(); if(mTextureManager) mTextureManager->kill(); }

   GFXAdapterType getAdapterType() override{ return Direct3D11; }

   U32 getAdaterIndex() const { return mAdapterIndex; }

   GFXCubemap *createCubemap() override;
   GFXCubemapArray *createCubemapArray() override;
   GFXTextureArray* createTextureArray() override;

   F32  getPixelShaderVersion() const override { return mPixVersion; }
   void setPixelShaderVersion( F32 version ) override{ mPixVersion = version;}

   void setShader(GFXShader *shader, bool force = false) override;
   U32  getNumSamplers() const override { return 16; }
   U32  getNumRenderTargets() const override { return 8; }
   // }

   // Copy methods
   // {
   void copyResource(GFXTextureObject *pDst, GFXCubemap *pSrc, const U32 face) override;
   // }

   // Misc rendering control
   // {
   void clear( U32 flags, const LinearColorF& color, F32 z, U32 stencil ) override;
   void clearColorAttachment(const U32 attachment, const LinearColorF& color) override;

   bool beginSceneInternal() override;
   void endSceneInternal() override;

   void setClipRect( const RectI &rect ) override;
   const RectI& getClipRect() const override { return mClipRect; }

   // }



   /// @name Render Targets
   /// @{
   void _updateRenderTargets() override;
   /// @}

   // Vertex/Index buffer management
   // {
   GFXVertexBuffer* allocVertexBuffer(  U32 numVerts,
                                                const GFXVertexFormat *vertexFormat,
                                                U32 vertSize,
                                                GFXBufferType bufferType,
                                                void* data = NULL) override;

   GFXPrimitiveBuffer *allocPrimitiveBuffer(  U32 numIndices,
                                                      U32 numPrimitives,
                                                      GFXBufferType bufferType,
                                                      void* data = NULL) override;

   GFXVertexDecl* allocVertexDecl( const GFXVertexFormat *vertexFormat ) override;
   void setVertexDecl( const GFXVertexDecl *decl ) override;

   void setVertexStream( U32 stream, GFXVertexBuffer *buffer ) override;
   void setVertexStreamFrequency( U32 stream, U32 frequency ) override;
   // }

   U32 getMaxDynamicVerts() override { return GFX_MAX_DYNAMIC_VERTS; }
   U32 getMaxDynamicIndices() override { return GFX_MAX_DYNAMIC_INDICES; }

   inline U32 primCountToIndexCount(GFXPrimitiveType primType, U32 primitiveCount);

   // Rendering
   // {
   void drawPrimitive( GFXPrimitiveType primType, U32 vertexStart, U32 primitiveCount ) override;
   // }

   ID3D11DeviceContext* getDeviceContext(){ return mD3DDeviceContext; }
   ID3D11Device* getDevice(){ return mD3DDevice; }
   //IDXGISwapChain* getSwapChain() { return mSwapChain; }

   /// Reset
   //void reset( DXGI_SWAP_CHAIN_DESC &d3dpp );
   void beginReset();
   void endReset(GFXD3D11WindowTarget* windowTarget);

   void setupGenericShaders( GenericShaderType type  = GSColor ) override;

   inline F32 getFillConventionOffset() const override { return 0.0f; }
   void doParanoidStateCheck() override {};

   GFXFence *createFence() override;

   GFXOcclusionQuery* createOcclusionQuery() override;

   // Default multisample parameters
   DXGI_SAMPLE_DESC getMultisampleType() const { return mMultisampleDesc; }

   // Get feature level this gfx device supports
   D3D_FEATURE_LEVEL getFeatureLevel() const { return mFeatureLevel; }
   // Shader Model targers
   const String &getVertexShaderTarget() const { return mVertexShaderTarget; }
   const String &getPixelShaderTarget() const { return mPixelShaderTarget; }
   const String &getGeometryShaderTarget() const { return mGeometryShaderTarget; }
   const String &getShaderModel() const { return mShaderModel; }

   // grab the sampler map
   const SamplerMap &getSamplersMap() const { return mSamplersMap; }
   SamplerMap &getSamplersMap(){ return mSamplersMap; }
   const char* interpretDebugResult(long result) override;

   // grab device buffer.
   ID3D11Buffer* getDeviceBuffer(const GFXShaderConstDesc desc);
};

#endif
