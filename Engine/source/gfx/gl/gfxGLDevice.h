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

#ifndef _GFXGLDEVICE_H_
#define _GFXGLDEVICE_H_

#include "platform/platform.h"

#include "gfx/gfxDevice.h"
#include "gfx/gfxInit.h"

#include "gfx/gl/tGL/tGL.h"

#include "windowManager/platformWindow.h"
#include "gfx/gfxFence.h"
#include "gfx/gfxResource.h"
#include "gfx/gl/gfxGLStateBlock.h"

class GFXGLTextureArray;
class GFXGLVertexBuffer;
class GFXGLPrimitiveBuffer;
class GFXGLTextureTarget;
class GFXGLCubemap;
class GFXGLCubemapArray;
class GFXGLStateCache;
class GFXGLVertexDecl;
class GFXGLShaderConstBuffer;

class GFXGLDevice : public GFXDevice
{

public:
   struct GLCapabilities
   {
      bool anisotropicFiltering;
      bool bufferStorage;
      bool textureStorage;
      bool copyImage;
      bool vertexAttributeBinding;
      bool khrDebug;
      bool extDebugMarker;
   };
   GLCapabilities mCapabilities;

   // UBO map
   typedef Map<String, GLuint> DeviceBufferMap;
   // grab device buffer.
   GLuint getDeviceBuffer(const GFXShaderConstDesc desc);

   void zombify();
   void resurrect();
   GFXGLDevice(U32 adapterIndex);
   virtual ~GFXGLDevice();

   static void enumerateAdapters( Vector<GFXAdapter*> &adapterList );
   static GFXDevice *createInstance( U32 adapterIndex );

   void init( const GFXVideoMode &mode, PlatformWindow *window = NULL ) override;

   virtual void activate() { }
   virtual void deactivate() { }
   GFXAdapterType getAdapterType() override { return OpenGL; }

   void enterDebugEvent(ColorI color, const char *name) override;
   void leaveDebugEvent() override;
   void setDebugMarker(ColorI color, const char *name) override;

   void enumerateVideoModes() override;

   virtual U32 getTotalVideoMemory_GL_EXT();
   virtual U32 getTotalVideoMemory();

   GFXCubemap * createCubemap() override;
   GFXCubemapArray *createCubemapArray() override;
   GFXTextureArray *createTextureArray() override;

   F32 getFillConventionOffset() const override { return 0.0f; }


   ///@}

   /// @name Render Target functions
   /// @{

   ///
   GFXTextureTarget *allocRenderToTextureTarget(bool genMips = true) override;
   GFXWindowTarget *allocWindowTarget(PlatformWindow *window) override;
   void _updateRenderTargets() override;

   ///@}

   /// @name Shader functions
   /// @{
   F32 getPixelShaderVersion() const override { return mPixelShaderVersion; }
   void  setPixelShaderVersion( F32 version ) override { mPixelShaderVersion = version; }

   void setShader(GFXShader *shader, bool force = false) override;

   /// @attention GL cannot check if the given format supports blending or filtering!
   GFXFormat selectSupportedFormat(GFXTextureProfile *profile,
	   const Vector<GFXFormat> &formats, bool texture, bool mustblend, bool mustfilter) override;

   /// Returns the number of texture samplers that can be used in a shader rendering pass
   U32 getNumSamplers() const override;

   /// Returns the number of simultaneous render targets supported by the device.
   U32 getNumRenderTargets() const override;

   GFXShader* createShader() override;
   //TODO: implement me!
   void copyResource(GFXTextureObject *pDst, GFXCubemap *pSrc, const U32 face) override;
   void clear( U32 flags, const LinearColorF& color, F32 z, U32 stencil ) override;
   void clearColorAttachment(const U32 attachment, const LinearColorF& color) override;
   bool beginSceneInternal() override;
   void endSceneInternal() override;

   void drawPrimitive( GFXPrimitiveType primType, U32 vertexStart, U32 primitiveCount ) override;

   void drawIndexedPrimitive(  GFXPrimitiveType primType,
                                       U32 startVertex,
                                       U32 minIndex,
                                       U32 numVerts,
                                       U32 startIndex,
                                       U32 primitiveCount ) override;

   void setClipRect( const RectI &rect ) override;
   const RectI &getClipRect() const override { return mClip; }

   void preDestroy() override { Parent::preDestroy(); }

   U32 getMaxDynamicVerts() override { return GFX_MAX_DYNAMIC_VERTS; }
   U32 getMaxDynamicIndices() override { return GFX_MAX_DYNAMIC_INDICES; }

   GFXFence *createFence() override;

   GFXOcclusionQuery* createOcclusionQuery() override;

   GFXGLStateBlockRef getCurrentStateBlock() { return mCurrentGLStateBlock; }

   void setupGenericShaders( GenericShaderType type = GSColor ) override;

   ///
   bool supportsAnisotropic() const { return mCapabilities.anisotropicFiltering; }

   GFXGLStateCache* getOpenglCache() { return mOpenglStateCache; }

   GFXTextureObject* getDefaultDepthTex() const;

   /// Returns the number of vertex streams supported by the device.
   const U32 getNumVertexStreams() const { return mNumVertexStream; }

   bool glUseMap() const { return mUseGlMap; }
   const char* interpretDebugResult(long result) override { return "Not Implemented"; };
protected:
   /// Called by GFXDevice to create a device specific stateblock
   GFXStateBlockRef createStateBlockInternal(const GFXStateBlockDesc& desc) override;
   /// Called by GFXDevice to actually set a stateblock.
   void setStateBlockInternal(GFXStateBlock* block, bool force) override;

   /// Called by base GFXDevice to actually set a const buffer
   void setShaderConstBufferInternal(GFXShaderConstBuffer* buffer) override;

   void setTextureInternal(U32 textureUnit, const GFXTextureObject*texture) override;
   virtual void setCubemapInternal(U32 textureUnit, const GFXGLCubemap* texture);
   virtual void setCubemapArrayInternal(U32 textureUnit, const GFXGLCubemapArray* texture);
   virtual void setTextureArrayInternal(U32 textureUnit, const GFXGLTextureArray* texture);

   /// @name State Initalization.
   /// @{

   /// State initalization. This MUST BE CALLED in setVideoMode after the device
   /// is created.
   void initStates() override { }

   GFXVertexBuffer *allocVertexBuffer(  U32 numVerts,
                                                const GFXVertexFormat *vertexFormat,
                                                U32 vertSize,
                                                GFXBufferType bufferType,
                                                void* data = NULL) override;
   GFXPrimitiveBuffer *allocPrimitiveBuffer( U32 numIndices, U32 numPrimitives, GFXBufferType bufferType, void* data = NULL ) override;

   // NOTE: The GL device doesn't need a vertex declaration at
   // this time, but we need to return something to keep the system
   // from retrying to allocate one on every call.
   GFXVertexDecl* allocVertexDecl( const GFXVertexFormat *vertexFormat ) override;

   void setVertexDecl( const GFXVertexDecl *decl ) override;

   void setVertexStream( U32 stream, GFXVertexBuffer *buffer ) override;
   void setVertexStreamFrequency( U32 stream, U32 frequency ) override;
   StrongRefPtr<GFXGLShaderConstBuffer> mCurrentConstBuffer;
   DeviceBufferMap mDeviceBufferMap;

private:
   typedef GFXDevice Parent;

   friend class GFXGLTextureObject;
   friend class GFXGLCubemap;
   friend class GFXGLCubemapArray;
   friend class GFXGLTextureArray;
   friend class GFXGLWindowTarget;
   friend class GFXGLPrimitiveBuffer;
   friend class GFXGLVertexBuffer;

   static GFXAdapter::CreateDeviceInstanceDelegate mCreateDeviceInstance;

   U32 mAdapterIndex;

   StrongRefPtr<GFXGLVertexBuffer> mCurrentVB[VERTEX_STREAM_COUNT];
   U32 mCurrentVB_Divisor[VERTEX_STREAM_COUNT];
   bool mNeedUpdateVertexAttrib;
   StrongRefPtr<GFXGLPrimitiveBuffer> mCurrentPB;
   U32 mDrawInstancesCount;

   GFXShader* mCurrentShader;
   GFXShaderRef mGenericShader[GS_COUNT];
   GFXShaderConstBufferRef mGenericShaderBuffer[GS_COUNT];
   GFXShaderConstHandle *mModelViewProjSC[GS_COUNT];

   /// Since GL does not have separate world and view matrices we need to track them
   MatrixF m_mCurrentWorld;
   MatrixF m_mCurrentView;

   void* mContext;
   void* mPixelFormat;

   F32 mPixelShaderVersion;

   U32 mNumVertexStream;

   U32 mMaxShaderTextures;
   U32 mMaxFFTextures;

   U32 mMaxTRColors;

   RectI mClip;

   GFXGLStateBlockRef mCurrentGLStateBlock;

   GLenum mActiveTextureType[GFX_TEXTURE_STAGE_COUNT];

   Vector< StrongRefPtr<GFXGLVertexBuffer> > mVolatileVBs; ///< Pool of existing volatile VBs so we can reuse previously created ones
   Vector< StrongRefPtr<GFXGLPrimitiveBuffer> > mVolatilePBs; ///< Pool of existing volatile PBs so we can reuse previously created ones

   GLsizei primCountToIndexCount(GFXPrimitiveType primType, U32 primitiveCount);
   void preDrawPrimitive();
   void postDrawPrimitive(U32 primitiveCount);

   GFXVertexBuffer* findVolatileVBO(U32 numVerts, const GFXVertexFormat *vertexFormat, U32 vertSize); ///< Returns an existing volatile VB which has >= numVerts and the same vert flags/size, or creates a new VB if necessary
   GFXPrimitiveBuffer* findVolatilePBO(U32 numIndices, U32 numPrimitives); ///< Returns an existing volatile PB which has >= numIndices, or creates a new PB if necessary

   void vsyncCallback(); ///< Vsync callback

   void initGLState(); ///< Guaranteed to be called after all extensions have been loaded, use to init card profiler, shader version, max samplers, etc.

   GFXFence* _createPlatformSpecificFence(); ///< If our platform (e.g. OS X) supports a fence extenstion (e.g. GL_APPLE_fence) this will create one, otherwise returns NULL

   void setPB(GFXGLPrimitiveBuffer* pb); ///< Sets mCurrentPB

   GFXGLStateCache *mOpenglStateCache;

   GFXWindowTargetRef *mWindowRT;

   bool mUseGlMap;
};

#define GFXGL static_cast<GFXGLDevice*>(GFXDevice::get())
#endif
