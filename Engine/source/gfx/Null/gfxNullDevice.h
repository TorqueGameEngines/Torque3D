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

#ifndef _GFXNullDevice_H_
#define _GFXNullDevice_H_

#include "platform/platform.h"

//-----------------------------------------------------------------------------

#include "gfx/gfxDevice.h"
#include "gfx/gfxInit.h"
#include "gfx/gfxFence.h"

class GFXNullWindowTarget : public GFXWindowTarget
{
public:
   bool present() override
   {
      return true;
   }

   const Point2I getSize() override
   {
      // Return something stupid.
      return Point2I(1,1);
   }

   GFXFormat getFormat() override { return GFXFormatR8G8B8A8; }

   void resetMode() override
   {

   }

   void zombify() override {};
   void resurrect() override {};

};

class GFXNullDevice : public GFXDevice
{
public:
   GFXNullDevice();
   virtual ~GFXNullDevice();

   static GFXDevice *createInstance( U32 adapterIndex );

   static void enumerateAdapters( Vector<GFXAdapter*> &adapterList );

   void init( const GFXVideoMode &mode, PlatformWindow *window = NULL ) override;

   virtual void activate() { };
   virtual void deactivate() { };
   GFXAdapterType getAdapterType() override { return NullDevice; };

   /// @name Debug Methods
   /// @{
   void enterDebugEvent(ColorI color, const char *name) override { };
   void leaveDebugEvent() override { };
   void setDebugMarker(ColorI color, const char *name) override { };
   /// @}

   /// Enumerates the supported video modes of the device
   void enumerateVideoModes() override { };

   /// Sets the video mode for the device
   virtual void setVideoMode( const GFXVideoMode &mode ) { };
protected:
   static GFXAdapter::CreateDeviceInstanceDelegate mCreateDeviceInstance; 

   /// Called by GFXDevice to create a device specific stateblock
   GFXStateBlockRef createStateBlockInternal(const GFXStateBlockDesc& desc) override;
   /// Called by GFXDevice to actually set a stateblock.
   void setStateBlockInternal(GFXStateBlock* block, bool force) override { };
   /// @}

   /// Called by base GFXDevice to actually set a const buffer
   void setShaderConstBufferInternal(GFXShaderConstBuffer* buffer) override { };

   void setTextureInternal(U32 textureUnit, const GFXTextureObject*texture) override { };


   /// @name State Initalization.
   /// @{

   /// State initalization. This MUST BE CALLED in setVideoMode after the device
   /// is created.
   void initStates() override { };

   GFXVertexBuffer *allocVertexBuffer(  U32 numVerts, 
                                                const GFXVertexFormat *vertexFormat, 
                                                U32 vertSize, 
                                                GFXBufferType bufferType,
                                                void* data = NULL ) override;
   GFXPrimitiveBuffer *allocPrimitiveBuffer(  U32 numIndices, 
                                                      U32 numPrimitives, 
                                                      GFXBufferType bufferType,
                                                      void* data = NULL ) override;

   GFXVertexDecl* allocVertexDecl( const GFXVertexFormat *vertexFormat ) override { return NULL; }
   void setVertexDecl( const GFXVertexDecl *decl ) override {  }
   void setVertexStream( U32 stream, GFXVertexBuffer *buffer ) override { }
   void setVertexStreamFrequency( U32 stream, U32 frequency ) override { }

public:
   GFXCubemap * createCubemap() override;
   GFXCubemapArray *createCubemapArray() override;
   GFXTextureArray *createTextureArray() override;

   F32 getFillConventionOffset() const override { return 0.0f; };

   ///@}

   GFXTextureTarget *allocRenderToTextureTarget(bool genMips=true) override{return NULL;};
   GFXWindowTarget *allocWindowTarget(PlatformWindow *window) override
   {
      return new GFXNullWindowTarget();
   };

   void _updateRenderTargets() override{};

   F32 getPixelShaderVersion() const override { return 0.0f; };
   void setPixelShaderVersion( F32 version ) override { };
   U32 getNumSamplers() const override { return 0; };
   U32 getNumRenderTargets() const override { return 0; };

   GFXShader* createShader() override { return NULL; };

   void copyResource(GFXTextureObject *pDst, GFXCubemap *pSrc, const U32 face) override { };
   void clear( U32 flags, const LinearColorF& color, F32 z, U32 stencil ) override { };
   void clearColorAttachment(const U32 attachment, const LinearColorF& color) override { };
   bool beginSceneInternal() override { return true; };
   void endSceneInternal() override { };

   void drawPrimitive( GFXPrimitiveType primType, U32 vertexStart, U32 primitiveCount ) override { };
   void drawIndexedPrimitive(  GFXPrimitiveType primType, 
                                       U32 startVertex, 
                                       U32 minIndex, 
                                       U32 numVerts, 
                                       U32 startIndex, 
                                       U32 primitiveCount ) override { };

   void setClipRect( const RectI &rect ) override { };
   const RectI &getClipRect() const override { return clip; };

   void preDestroy() override { Parent::preDestroy(); };

   U32 getMaxDynamicVerts() override { return 16384; };
   U32 getMaxDynamicIndices() override { return 16384; };

   GFXFormat selectSupportedFormat(  GFXTextureProfile *profile, 
                                             const Vector<GFXFormat> &formats, 
                                             bool texture, 
                                             bool mustblend, 
                                             bool mustfilter ) override { return GFXFormatR8G8B8A8; };

   GFXFence *createFence() override { return new GFXGeneralFence( this ); }
   GFXOcclusionQuery* createOcclusionQuery() override { return NULL; }
   
private:
   typedef GFXDevice Parent;
   RectI clip;
};

#endif
