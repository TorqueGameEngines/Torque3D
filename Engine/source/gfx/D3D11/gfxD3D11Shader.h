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

typedef CompoundKey<U32, U32> BufferKey;

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
   typedef Map<GFXShaderStage, GFXShaderConstDesc> DescMap;

   GFXD3D11ShaderConstHandle(GFXD3D11Shader* shader);
   GFXD3D11ShaderConstHandle(GFXD3D11Shader* shader,
                              const GFXShaderConstDesc& desc);

   virtual ~GFXD3D11ShaderConstHandle();
   void addDesc(GFXShaderStage stage, const GFXShaderConstDesc& desc);
   const GFXShaderConstDesc getDesc(GFXShaderStage stage);
   const String& getName() const override { return mDesc.name; }
   GFXShaderConstType getType() const override { return mDesc.constType; }
   U32 getArraySize() const override { return mDesc.arraySize; }

   U32 getSize() const { return mDesc.size; }
   void setValid(bool valid) { mValid = valid; }
   /// @warning This will always return the value assigned when the shader was
   /// initialized.  If the value is later changed this method won't reflect that.
   S32 getSamplerRegister() const override { return (!isSampler() || !mValid) ? -1 : mDesc.samplerReg; }

   // Returns true if this is a handle to a sampler register.
   bool isSampler() const
   {
      return (getType() >= GFXSCT_Sampler);
   }

   /// Restore to uninitialized state.
   void clear()
   {
      mShader = NULL;
      mInstancingConstant = false;
      mValid = false;
   }

   GFXShaderConstDesc mDesc;
   GFXD3D11Shader* mShader;
   DescMap mDescMap;
   U32 mStageFlags;
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

   void addBuffer(const GFXShaderConstDesc desc);

   /// Called from GFXD3D11Shader when constants have changed and need
   /// to be the shader this buffer references is reloaded.
   void onShaderReload(GFXD3D11Shader *shader);

   // GFXShaderConstBuffer
   GFXShader* getShader() override;
   void set(GFXShaderConstHandle* handle, const F32 fv) override;
   void set(GFXShaderConstHandle* handle, const Point2F& fv) override;
   void set(GFXShaderConstHandle* handle, const Point3F& fv) override;
   void set(GFXShaderConstHandle* handle, const Point4F& fv) override;
   void set(GFXShaderConstHandle* handle, const PlaneF& fv) override;
   void set(GFXShaderConstHandle* handle, const LinearColorF& fv) override;
   void set(GFXShaderConstHandle* handle, const S32 f) override;
   void set(GFXShaderConstHandle* handle, const Point2I& fv) override;
   void set(GFXShaderConstHandle* handle, const Point3I& fv) override;
   void set(GFXShaderConstHandle* handle, const Point4I& fv) override;
   void set(GFXShaderConstHandle* handle, const AlignedArray<F32>& fv) override;
   void set(GFXShaderConstHandle* handle, const AlignedArray<Point2F>& fv) override;
   void set(GFXShaderConstHandle* handle, const AlignedArray<Point3F>& fv) override;
   void set(GFXShaderConstHandle* handle, const AlignedArray<Point4F>& fv) override;
   void set(GFXShaderConstHandle* handle, const AlignedArray<S32>& fv) override;
   void set(GFXShaderConstHandle* handle, const AlignedArray<Point2I>& fv) override;
   void set(GFXShaderConstHandle* handle, const AlignedArray<Point3I>& fv) override;
   void set(GFXShaderConstHandle* handle, const AlignedArray<Point4I>& fv) override;
   void set(GFXShaderConstHandle* handle, const MatrixF& mat, const GFXShaderConstType matType = GFXSCT_Float4x4) override;
   void set(GFXShaderConstHandle* handle, const MatrixF* mat, const U32 arraySize, const GFXShaderConstType matrixType = GFXSCT_Float4x4) override;

   // GFXResource
   const String describeSelf() const override;
   void zombify() override {}
   void resurrect() override {}

protected:
   friend class GFXD3D11Shader;
   /// We keep a weak reference to the shader
   /// because it will often be deleted.
   WeakRefPtr<GFXD3D11Shader> mShader;
   BufferMap mBufferMap;

   void setMatrix(const GFXShaderConstDesc& handle, const U32 inSize, const void* data, U8* basePointer);
   void internalSet(GFXShaderConstHandle* handle, const U32 inSize, const void* data);

   ID3D11Buffer* mBoundBuffers[6][16];
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
   GFXShaderConstBufferRef allocConstBuffer() override;
   const Vector<GFXShaderConstDesc>& getShaderConstDesc() const override;
   GFXShaderConstHandle* getShaderConstHandle(const String& name) override;
   GFXShaderConstHandle* findShaderConstHandle(const String& name) override;
   U32 getAlignmentValue(const GFXShaderConstType constType) const override;

   // GFXResource
   void zombify() override;
   void resurrect() override;

protected:

   bool _init() override;

   ID3D11VertexShader *mVertShader;
   ID3D11PixelShader *mPixShader;
   ID3D11GeometryShader *mGeoShader;

   static gfxD3DIncludeRef smD3DInclude;

   HandleMap mHandles;
   BufferMap mBuffers;

   /// Vector of descriptions (consolidated for the getShaderConstDesc call)
   Vector<GFXShaderConstDesc> mShaderConsts;
   Vector<GFXShaderConstDesc> mSamplerDescriptions;

   // These two functions are used when compiling shaders from hlsl
   virtual bool _compileShader( const Torque::Path &filePath,
                                 GFXShaderStage shaderStage,
                                const D3D_SHADER_MACRO *defines);

   void _getShaderConstants( ID3D11ShaderReflection* refTable,
                              GFXShaderStage shaderStage);

   // This is used in both cases
   virtual void _buildShaderConstantHandles();
   void _buildInstancingShaderConstantHandles();

   GFXShaderConstType convertConstType(D3D11_SHADER_TYPE_DESC typeDesc);

};


#endif
