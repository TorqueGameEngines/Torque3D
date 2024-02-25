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

#ifndef _GFXD3D11SHADER_H_
#define _GFXD3D11SHADER_H_

#include <d3dcompiler.h>

#include "core/util/path.h"
#include "core/util/tDictionary.h"
#include "gfx/gfxShader.h"
#include "gfx/gfxResource.h"
#include "gfx/D3D11/gfxD3D11Device.h"

class GFXD3D11Shader;

enum SHADER_STAGE
{
   VERTEX_SHADER,
   PIXEL_SHADER,
   GEOMETRY_SHADER,
   DOMAIN_SHADER,
   HULL_SHADER,
   COMPUTE_SHADER,
   UNKNOWN_STAGE
};


typedef CompoundKey<U32, SHADER_STAGE> BufferKey;

struct BufferRange
{
   U32 mBufMin = U32_MAX;
   U32 mBufMax = 0;

   inline void addSlot(U32 slot)
   {
      mBufMin = getMin(mBufMin, slot);
      mBufMax = getMax(mBufMax, slot);
   }

   inline bool isValid() const { return mBufMin <= mBufMax; }
};

struct ConstantBuffer
{
   U8* data;
   U32 size;
   bool isDirty;
};

class GFXD3D11ShaderConstHandle : public GFXShaderConstHandle
{
   friend class GFXD3D11Shader;
public:

   GFXD3D11ShaderConstHandle(GFXD3D11Shader* shader);
   GFXD3D11ShaderConstHandle(GFXD3D11Shader* shader,
                              const GFXShaderConstDesc& desc);

   virtual ~GFXD3D11ShaderConstHandle();
   void reinit(const GFXShaderConstDesc& desc);
   const String& getName() const { return mDesc.name; }
   GFXShaderConstType getType() const { return mDesc.constType; }
   U32 getArraySize() const { return mDesc.arraySize; }

   U32 getSize() const { return mSize; }
   void setValid(bool valid) { mValid = valid; }
   /// @warning This will always return the value assigned when the shader was
   /// initialized.  If the value is later changed this method won't reflect that.
   S32 getSamplerRegister() const { return (!isSampler() || !mValid) ? -1 : mSampler; }

   // Returns true if this is a handle to a sampler register.
   bool isSampler() const 
   {
      return (getType() >= GFXSCT_Sampler);
   }

   GFXShaderConstDesc mDesc;
   GFXD3D11Shader* mShader;
   U32 mOffset;
   U32 mSize;
   S32 mBinding; // buffer binding point used to map handles to buffers.
   S32 mSampler; // sampler number, will be -1 if not a sampler.
   SHADER_STAGE mStage;
   bool mInstancingConstant;
};

/// The D3D11 implementation of a shader constant buffer.
class GFXD3D11ShaderConstBuffer : public GFXShaderConstBuffer
{
   // Cache device context
   ID3D11DeviceContext* mDeviceContext;

public:
   typedef Map<BufferKey, ConstantBuffer> BufferMap;

   GFXD3D11ShaderConstBuffer(GFXD3D11Shader* shader);

   virtual ~GFXD3D11ShaderConstBuffer();

   /// Called by GFXD3D11Device to activate this buffer.
   /// @param mPrevShaderBuffer The previously active buffer
   void activate(GFXD3D11ShaderConstBuffer *prevShaderBuffer);

   void addBuffer(U32 bufBindingPoint, SHADER_STAGE shaderStage, U32 size);

   /// Called from GFXD3D11Shader when constants have changed and need
   /// to be the shader this buffer references is reloaded.
   void onShaderReload(GFXD3D11Shader *shader);

   // GFXShaderConstBuffer
   virtual GFXShader* getShader();
   virtual void set(GFXShaderConstHandle* handle, const F32 fv);
   virtual void set(GFXShaderConstHandle* handle, const Point2F& fv);
   virtual void set(GFXShaderConstHandle* handle, const Point3F& fv);
   virtual void set(GFXShaderConstHandle* handle, const Point4F& fv);
   virtual void set(GFXShaderConstHandle* handle, const PlaneF& fv);
   virtual void set(GFXShaderConstHandle* handle, const LinearColorF& fv);
   virtual void set(GFXShaderConstHandle* handle, const S32 f);
   virtual void set(GFXShaderConstHandle* handle, const Point2I& fv);
   virtual void set(GFXShaderConstHandle* handle, const Point3I& fv);
   virtual void set(GFXShaderConstHandle* handle, const Point4I& fv);
   virtual void set(GFXShaderConstHandle* handle, const AlignedArray<F32>& fv);
   virtual void set(GFXShaderConstHandle* handle, const AlignedArray<Point2F>& fv);
   virtual void set(GFXShaderConstHandle* handle, const AlignedArray<Point3F>& fv);
   virtual void set(GFXShaderConstHandle* handle, const AlignedArray<Point4F>& fv);
   virtual void set(GFXShaderConstHandle* handle, const AlignedArray<S32>& fv);
   virtual void set(GFXShaderConstHandle* handle, const AlignedArray<Point2I>& fv);
   virtual void set(GFXShaderConstHandle* handle, const AlignedArray<Point3I>& fv);
   virtual void set(GFXShaderConstHandle* handle, const AlignedArray<Point4I>& fv);
   virtual void set(GFXShaderConstHandle* handle, const MatrixF& mat, const GFXShaderConstType matType = GFXSCT_Float4x4);
   virtual void set(GFXShaderConstHandle* handle, const MatrixF* mat, const U32 arraySize, const GFXShaderConstType matrixType = GFXSCT_Float4x4);

   // GFXResource
   virtual const String describeSelf() const;
   virtual void zombify() {}
   virtual void resurrect() {}

protected:
   friend class GFXD3D11Shader;
   /// We keep a weak reference to the shader 
   /// because it will often be deleted.
   WeakRefPtr<GFXD3D11Shader> mShader;
   BufferMap mBufferMap;

   void setMatrix(GFXShaderConstHandle* handle, const U32 inSize, const void* data);
   void internalSet(GFXShaderConstHandle* handle, const U32 inSize, const void* data);
   

   // we probably want this to be GFXDevice and not per shader.
   ID3D11Buffer* mBoundConstantBuffers[16];
};

class gfxD3D11Include;
typedef StrongRefPtr<gfxD3D11Include> gfxD3DIncludeRef;

/////////////////// GFXShader implementation /////////////////////////////

class GFXD3D11Shader : public GFXShader
{
   friend class GFXD3D11Device;
   friend class GFXD3D11ShaderConstBuffer;

public:
   typedef Map<String, GFXD3D11ShaderConstHandle*> HandleMap;
   typedef Map<String, GFXShaderConstDesc> BufferMap;

   GFXD3D11Shader();
   virtual ~GFXD3D11Shader();   

   // GFXShader
   virtual GFXShaderConstBufferRef allocConstBuffer();
   virtual const Vector<GFXShaderConstDesc>& getShaderConstDesc() const;
   virtual GFXShaderConstHandle* getShaderConstHandle(const String& name); 
   virtual GFXShaderConstHandle* findShaderConstHandle(const String& name);
   virtual U32 getAlignmentValue(const GFXShaderConstType constType) const;

   // GFXResource
   virtual void zombify();
   virtual void resurrect();

protected:

   virtual bool _init();

   ID3D11VertexShader *mVertShader;
   ID3D11PixelShader *mPixShader;

   static gfxD3DIncludeRef smD3DInclude;

   HandleMap mHandles;
   BufferMap mBuffers;

   /// Vector of descriptions (consolidated for the getShaderConstDesc call)
   Vector<GFXShaderConstDesc> mShaderConsts;
   Vector<GFXShaderConstDesc> mSamplerDescriptions;

   // These two functions are used when compiling shaders from hlsl
   virtual bool _compileShader( const Torque::Path &filePath, 
                                SHADER_STAGE shaderStage, 
                                const D3D_SHADER_MACRO *defines);

   void _getShaderConstants( ID3D11ShaderReflection* refTable,
                             SHADER_STAGE shaderStage);
  
   // This is used in both cases
   virtual void _buildShaderConstantHandles();
   void _buildInstancingShaderConstantHandles();
};


#endif
