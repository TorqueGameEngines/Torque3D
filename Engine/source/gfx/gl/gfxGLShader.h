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

#ifndef _GFXGLSHADER_H_
#define _GFXGLSHADER_H_

#include "core/util/refBase.h"
#include "gfx/gfxShader.h"
#include "gfx/gl/tGL/tGL.h"
#include "core/util/tSignal.h"
#include "core/util/tDictionary.h"

class FileStream;
class GFXGLDevice;
class GFXGLShader;

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
   GLuint bufHandle;
   U8* data;
   U32 size;
   bool isDirty;
};

class GFXGLShaderConstHandle : public GFXShaderConstHandle
{
   friend class GFXGLShader;

public:
   // DX side needs the description map as the same uniform can exist across stages. for gl it is program wide.
   GFXGLShaderConstHandle(GFXGLShader* shader);
   GFXGLShaderConstHandle(GFXGLShader* shader,
      const GFXShaderConstDesc& desc);

   void reinit(const GFXShaderConstDesc& desc);

   virtual ~GFXGLShaderConstHandle();
   const GFXShaderConstDesc getDesc();
   const String& getName() const { return mDesc.name; }
   GFXShaderConstType getType() const { return mDesc.constType; }
   U32 getArraySize() const { return mDesc.arraySize; }

   U32 getSize() const { return mDesc.size; }
   void setValid(bool valid) { mValid = valid; }
   /// @warning This will always return the value assigned when the shader was
   /// initialized.  If the value is later changed this method won't reflect that.
   S32 getSamplerRegister() const { return (!isSampler() || !mValid) ? -1 : mDesc.samplerReg; }

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
   GFXGLShader* mShader;
   bool mUBOUniform;
   bool mInstancingConstant;
};

class GFXGLShaderConstBuffer : public GFXShaderConstBuffer
{
public:
   // -1 is the global buffer.
   typedef Map<S32, ConstantBuffer> BufferMap;

   GFXGLShaderConstBuffer(GFXGLShader* shader);
   ~GFXGLShaderConstBuffer();

   /// Called by GFXGLDevice to activate this buffer.
   void activate(GFXGLShaderConstBuffer* prevShaderBuffer);

   void addBuffer(const GFXShaderConstDesc desc);

   /// Called when the shader this buffer references is reloaded.
   void onShaderReload(GFXGLShader* shader);

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

private:

   friend class GFXGLShader;

   WeakRefPtr<GFXGLShader> mShader;
   BufferMap mBufferMap;

   template<typename ConstType>
   void internalSet(GFXShaderConstHandle* handle, const ConstType& param);

   template<typename ConstType>
   void internalSet(GFXShaderConstHandle* handle, const AlignedArray<ConstType>& fv);
};

class GFXGLShader : public GFXShader
{
   friend class GFXGLShaderConstBuffer;
   friend class GFXGLShaderConstHandle;
public:
   typedef Map<String, GFXGLShaderConstHandle*> HandleMap;
   typedef Map<String, GFXShaderConstDesc> BufferMap;

   GFXGLShader(GFXGLDevice* device);
   virtual ~GFXGLShader();

   /// @name GFXShader interface
   /// @{
   virtual GFXShaderConstHandle* getShaderConstHandle(const String& name);
   virtual GFXShaderConstHandle* findShaderConstHandle(const String& name);

   /// Returns our list of shader constants, the material can get this and just set the constants it knows about
   virtual const Vector<GFXShaderConstDesc>& getShaderConstDesc() const;

   /// Returns the alignment value for constType
   virtual U32 getAlignmentValue(const GFXShaderConstType constType) const;

   virtual GFXShaderConstBufferRef allocConstBuffer();

   /// @}

   /// @name GFXResource interface
   /// @{
   virtual void zombify();
   virtual void resurrect() { reload(); }
   virtual const String describeSelf() const;
   /// @}

   /// Activates this shader in the GL context.
   void useProgram();

protected:
   virtual bool _init();

   bool initShader(const Torque::Path& file,
      GFXShaderStage stage,
      const Vector<GFXShaderMacro>& macros);

   void clearShaders();

   void initConstantDescs();
   void initHandles();
   void setConstantsFromBuffer(U8* buffer);

   static char* _handleIncludes(const Torque::Path& path, FileStream* s);

   static bool _loadShaderFromStream(GLuint shader,
      const Torque::Path& path,
      FileStream* s,
      const Vector<GFXShaderMacro>& macros);

   /// @name Internal GL handles
   /// @{
   GLuint mVertexShader;
   GLuint mPixelShader;
   GLuint mGeometryShader;
   GLuint mProgram;
   /// @}

   U8* mGlobalConstBuffer;

   Vector<GFXShaderConstDesc> mShaderConsts;

   HandleMap mHandles;
   BufferMap mBuffers;

   GFXGLDevice* mDevice;

   GFXShaderConstType convertConstType(GLenum constType);
};

#endif // _GFXGLSHADER_H_
