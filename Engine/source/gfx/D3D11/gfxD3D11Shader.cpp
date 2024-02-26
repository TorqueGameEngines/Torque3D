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

#include "platform/platform.h"
#include "gfx/D3D11/gfxD3D11Shader.h"
#include "core/frameAllocator.h"
#include "core/stream/fileStream.h"
#include "core/util/safeDelete.h"
#include "console/console.h"

extern bool gDisassembleAllShaders;

#pragma comment(lib, "d3dcompiler.lib")

gfxD3DIncludeRef GFXD3D11Shader::smD3DInclude = NULL;

class gfxD3D11Include : public ID3DInclude, public StrongRefBase
{
private:

   Vector<String> mLastPath;

public:

   void setPath(const String &path)
   {
      mLastPath.clear();
      mLastPath.push_back(path);
   }

   gfxD3D11Include() {}
   virtual ~gfxD3D11Include() {}

   STDMETHOD(Open)(THIS_ D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData, UINT *pBytes);
   STDMETHOD(Close)(THIS_ LPCVOID pData);
};

HRESULT gfxD3D11Include::Open(THIS_ D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData, UINT *pBytes)
{
   using namespace Torque;
   // First try making the path relative to the parent.
   Torque::Path path = Torque::Path::Join( mLastPath.last(), '/', pFileName );
   path = Torque::Path::CompressPath( path );

   if ( !Torque::FS::ReadFile( path, (void *&)*ppData, *pBytes, true ) )
   {
      // Ok... now try using the path as is.
      path = String( pFileName );
      path = Torque::Path::CompressPath( path );

      if ( !Torque::FS::ReadFile( path, (void *&)*ppData, *pBytes, true ) )
      {
         AssertISV(false, avar( "Failed to open include '%s'.", pFileName));
         return E_FAIL;
      }
   }

   // If the data was of zero size then we cannot recurse
   // into this file and DX won't call Close() below.
   //
   // So in this case don't push on the path.
   if ( *pBytes > 0 )
      mLastPath.push_back( path.getRootAndPath() );

   return S_OK;
}

HRESULT gfxD3D11Include::Close( THIS_ LPCVOID pData )
{
   // Free the data file and pop its path off the stack.
   delete [] (U8*)pData;
   mLastPath.pop_back();

   return S_OK;
}

GFXD3D11ShaderConstHandle::GFXD3D11ShaderConstHandle(GFXD3D11Shader* shader)
   : mShader(shader),
   mOffset(0),
   mSize(0),
   mBinding(-1),
   mSampler(-1),
   mInstancingConstant(false)
{
   dMemset(&mDesc, 0, sizeof(mDesc));
   mValid = false;
   mStageFlags = 0;
}

GFXD3D11ShaderConstHandle::GFXD3D11ShaderConstHandle(GFXD3D11Shader* shader,
                                                      const GFXShaderConstDesc& desc)
   : mShader(shader),
   mDesc(desc),
   
   mOffset(desc.offset),
   mSize(desc.size),
   mBinding(desc.bindPoint),
   mSampler(desc.samplerReg),
   mInstancingConstant(false)
{
   if (desc.constType == GFXSCT_ConstBuffer)
      mValid = false;
   else
      mValid = true;

   mStageFlags = desc.shaderStage;
}

GFXD3D11ShaderConstHandle::~GFXD3D11ShaderConstHandle()
{
}

void GFXD3D11ShaderConstHandle::reinit(const GFXShaderConstDesc& desc)
{
   mDesc                = desc;
   mStageFlags          = desc.shaderStage;
   mOffset              = desc.offset;
   mSize                = desc.size * desc.arraySize;
   mBinding             = desc.bindPoint;
   mSampler             = desc.samplerReg;
   mInstancingConstant  = false;

   if (desc.constType == GFXSCT_ConstBuffer)
      mValid = false;
   else
      mValid = true;
}

//------------------------------------------------------------------------------

GFXD3D11ShaderConstBuffer::GFXD3D11ShaderConstBuffer( GFXD3D11Shader* shader)
{
   mShader = shader;
   mDeviceContext = D3D11DEVICECONTEXT;

   for (U32 i = 0; i < 6; i++)
   {
      for (U32 j = 0; j < 16; j++)
      {
         mBoundConstantBuffers[i][j] = NULL;
      }
   }

}

GFXD3D11ShaderConstBuffer::~GFXD3D11ShaderConstBuffer()
{
   for (U32 i = 0; i < 6; i++)
   {
      for (U32 j = 0; j < 16; j++)
      {
         SAFE_RELEASE(mBoundConstantBuffers[i][j]);
      }
   }

   if (mShader)
      mShader->_unlinkBuffer(this);
}

GFXShader* GFXD3D11ShaderConstBuffer::getShader()
{
   return mShader;
}

void GFXD3D11ShaderConstBuffer::setMatrix(GFXShaderConstHandle* handle, const U32 inSize, const void* data, U8* basePointer)
{
   AssertFatal(handle, "GFXD3D11ShaderConstBuffer::internalSet - Handle is NULL!");
   AssertFatal(handle->isValid(), "GFXD3D11ShaderConstBuffer::internalSet - Handle is not valid!");
   AssertFatal(dynamic_cast<GFXD3D11ShaderConstHandle*>(handle), "GFXD3D11ShaderConstBuffer::internalSet - Incorrect const buffer type");

   GFXD3D11ShaderConstHandle* _dxHandle = static_cast<GFXD3D11ShaderConstHandle*>(handle);
   AssertFatal(mShader == _dxHandle->mShader, "GFXD3D11ShaderConstBuffer::internalSet - Should only set handles which are owned by our shader");

   U8* buf = basePointer;

   if (_dxHandle->mDesc.constType == GFXSCT_Float4x4)
   {
      // Special case, we can just blast this guy.
      if (dMemcmp(buf + _dxHandle->mDesc.offset, data, inSize) != 0)
      {
         dMemcpy(buf + _dxHandle->mDesc.offset, data, inSize);
      }

      return;
   }
   else
   {
      PROFILE_SCOPE(GFXD3D11ConstBufferLayout_setMatrix_not4x4);

      // Figure out how big of a chunk we are copying.  We're going to copy 4 columns by N rows of data
      U32 csize;
      switch (_dxHandle->mDesc.constType)
      {
      case GFXSCT_Float2x2:
         csize = 24; //this takes up 16+8
         break;
      case GFXSCT_Float3x3:
         csize = 44; //This takes up 16+16+12
         break;
      case GFXSCT_Float4x3:
         csize = 48;
         break;
      default:
         AssertFatal(false, "Unhandled case!");
         return;
         break;
      }

      // Loop through and copy 
      bool ret = false;
      U8* currDestPointer = buf + _dxHandle->mDesc.offset;
      const U8* currSourcePointer = static_cast<const U8*>(data);
      const U8* endData = currSourcePointer + inSize;
      while (currSourcePointer < endData)
      {
         if (dMemcmp(currDestPointer, currSourcePointer, csize) != 0)
         {
            dMemcpy(currDestPointer, currSourcePointer, csize);
            ret = true;
         }

         currDestPointer += csize;
         currSourcePointer += sizeof(MatrixF);
      }
   }
}

void GFXD3D11ShaderConstBuffer::internalSet(GFXShaderConstHandle* handle, const U32 inSize, const void* data)
{
   AssertFatal(handle, "GFXD3D11ShaderConstBuffer::internalSet - Handle is NULL!");
   AssertFatal(handle->isValid(), "GFXD3D11ShaderConstBuffer::internalSet - Handle is not valid!");
   AssertFatal(dynamic_cast<GFXD3D11ShaderConstHandle*>(handle), "GFXD3D11ShaderConstBuffer::internalSet - Incorrect const buffer type");

   GFXD3D11ShaderConstHandle* _dxHandle = static_cast<GFXD3D11ShaderConstHandle*>(handle);
   AssertFatal(mShader == _dxHandle->mShader, "GFXD3D11ShaderConstBuffer::internalSet - Should only set handles which are owned by our shader");
   S32 size = inSize;

   for (U32 i = VERTEX_SHADER; i <= COMPUTE_SHADER; i = GFXShaderStage(i << 1))
   {
      if (_dxHandle->mStageFlags & i)
      {
         BufferKey bufDesc(_dxHandle->mBinding, (GFXShaderStage)i);
         U8* basePointer = mBufferMap[bufDesc].data;

         if (_dxHandle->mInstancingConstant)
         {
            dMemcpy(mInstPtr + _dxHandle->mOffset, data, size);
            return;
         }

         switch (_dxHandle->mDesc.constType)
         {
         case GFXSCT_Float2x2:
         case GFXSCT_Float3x3:
         case GFXSCT_Float4x3:
         case GFXSCT_Float4x4:
            setMatrix(handle, size, data, basePointer);
            return;
            break;
            // TODO add other AlignedVector here
         case GFXSCT_Float2:
            if (size > sizeof(Point2F))
               size = _dxHandle->mDesc.size;
               break;
         default:
            break;
         }

         if (dMemcmp(basePointer + _dxHandle->mDesc.offset, data, size) != 0)
         {
            dMemcpy(basePointer + _dxHandle->mDesc.offset, data, size);
         }
      }
   }
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const F32 fv)
{
   internalSet(handle, sizeof(F32), &fv);
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const Point2F& fv)
{
   internalSet(handle, sizeof(Point2F), &fv);
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const Point3F& fv)
{
   internalSet(handle, sizeof(Point3F), &fv);
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const Point4F& fv)
{
   internalSet(handle, sizeof(Point4F), &fv);
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const PlaneF& fv)
{
   internalSet(handle, sizeof(PlaneF), &fv);
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const LinearColorF& fv)
{
   internalSet(handle, sizeof(Point4F), &fv);
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const S32 fv)
{
   // This is the only type that is allowed to be used
   // with a sampler shader constant type, but it is only
   // allowed to be set from GLSL.
   //
   // So we ignore it here... all other cases will assert.
   //
   if (((GFXD3D11ShaderConstHandle*)handle)->isSampler())
      return;

   internalSet(handle, sizeof(S32), &fv);
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const Point2I& fv)
{
   internalSet(handle, sizeof(Point2I), &fv);
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const Point3I& fv)
{
   internalSet(handle, sizeof(Point3I), &fv);
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const Point4I& fv)
{
   internalSet(handle, sizeof(Point4I), &fv);
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const AlignedArray<F32>& fv)
{
   internalSet(handle, fv.getElementSize() * fv.size(), fv.getBuffer());
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const AlignedArray<Point2F>& fv)
{
   internalSet(handle, fv.getElementSize() * fv.size(), fv.getBuffer());
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const AlignedArray<Point3F>& fv)
{
   internalSet(handle, fv.getElementSize() * fv.size(), fv.getBuffer());
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const AlignedArray<Point4F>& fv)
{
   internalSet(handle, fv.getElementSize() * fv.size(), fv.getBuffer());
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const AlignedArray<S32>& fv)
{
   internalSet(handle, fv.getElementSize() * fv.size(), fv.getBuffer());
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const AlignedArray<Point2I>& fv)
{
   internalSet(handle, fv.getElementSize() * fv.size(), fv.getBuffer());
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const AlignedArray<Point3I>& fv)
{
   internalSet(handle, fv.getElementSize() * fv.size(), fv.getBuffer());
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const AlignedArray<Point4I>& fv)
{
   internalSet(handle, fv.getElementSize() * fv.size(), fv.getBuffer());
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const MatrixF& mat, const GFXShaderConstType matrixType)
{
   AssertFatal(handle, "Handle is NULL!");
   AssertFatal(handle->isValid(), "Handle is not valid!");

   AssertFatal(static_cast<const GFXD3D11ShaderConstHandle*>(handle), "Incorrect const buffer type!");
   const GFXD3D11ShaderConstHandle* _dxHandle = static_cast<const GFXD3D11ShaderConstHandle*>(handle);
   AssertFatal(!_dxHandle->isSampler(), "Handle is sampler constant!");
   AssertFatal(_dxHandle->mShader == mShader, "Mismatched shaders!");

   MatrixF transposed;
   if (matrixType == GFXSCT_Float4x3)
   {
      transposed = mat;
   }
   else
   {
      mat.transposeTo(transposed);
   }

   if (_dxHandle->mInstancingConstant)
   {
      if (matrixType == GFXSCT_Float4x4)
         dMemcpy(mInstPtr + _dxHandle->mOffset, mat, sizeof(mat));

      // TODO: Support 3x3 and 2x2 matricies?      
      return;
   }

   internalSet(handle, sizeof(MatrixF), &transposed);
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const MatrixF* mat, const U32 arraySize, const GFXShaderConstType matrixType)
{
   AssertFatal(handle, "Handle is NULL!");
   AssertFatal(handle->isValid(), "Handle is not valid!");

   AssertFatal(static_cast<const GFXD3D11ShaderConstHandle*>(handle), "Incorrect const buffer type!");
   const GFXD3D11ShaderConstHandle* _dxHandle = static_cast<const GFXD3D11ShaderConstHandle*>(handle);
   AssertFatal(!_dxHandle->isSampler(), "Handle is sampler constant!");
   AssertFatal(_dxHandle->mShader == mShader, "Mismatched shaders!");

   static Vector<MatrixF> transposed;
   if (arraySize > transposed.size())
      transposed.setSize(arraySize);

   if (matrixType == GFXSCT_Float4x3)
   {
      dMemcpy(transposed.address(), mat, arraySize * sizeof(MatrixF));
   }
   else
   {
      for (U32 i = 0; i < arraySize; i++)
         mat[i].transposeTo(transposed[i]);
   }

   // TODO: Maybe support this in the future?
   if (_dxHandle->mInstancingConstant)
      return;

   internalSet(handle, sizeof(MatrixF) * arraySize, transposed.begin());
}

const String GFXD3D11ShaderConstBuffer::describeSelf() const
{
   String ret;
   ret = String("   GFXD3D11ShaderConstBuffer\n");


   return ret;
}

void GFXD3D11ShaderConstBuffer::addBuffer(U32 bufBindingPoint, GFXShaderStage shaderStage, U32 size)
{
   const BufferKey bufKey(bufBindingPoint, shaderStage);
   // doesnt matter if its already added.
   U8* buf = new U8[size];
   dMemset(buf, 0, size);
   mBufferMap[bufKey].data = buf;
   mBufferMap[bufKey].size = size;
   mBufferMap[bufKey].isDirty = true;

   D3D11_BUFFER_DESC cbDesc;
   cbDesc.ByteWidth = size;
   cbDesc.Usage = D3D11_USAGE_DEFAULT;
   cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
   cbDesc.CPUAccessFlags = 0;
   cbDesc.MiscFlags = 0;
   cbDesc.StructureByteStride = 0;

   HRESULT hr;
   hr = D3D11DEVICE->CreateBuffer(&cbDesc, NULL, &mBoundConstantBuffers[shaderStage][bufBindingPoint]);

   if (FAILED(hr))
   {
      AssertFatal(false, "can't create constant buffer");
   }
}

void GFXD3D11ShaderConstBuffer::activate( GFXD3D11ShaderConstBuffer *prevShaderBuffer )
{
   PROFILE_SCOPE(GFXD3D11ShaderConstBuffer_activate);

   if (prevShaderBuffer == NULL)
      return;

   BufferRange bufRanges[6];

   for (BufferMap::Iterator i = mBufferMap.begin(); i != mBufferMap.end(); ++i)
   {
      const BufferKey thisBufferDesc = i->key;
      ConstantBuffer thisBuff = i->value;

      if (prevShaderBuffer != this)
      {
         if (prevShaderBuffer)
         {
            const ConstantBuffer prevBuffer = prevShaderBuffer->mBufferMap[i->key];

            if (prevBuffer.data && !prevBuffer.isDirty)
            {
               if (prevBuffer.size != thisBuff.size)
               {
                  thisBuff.isDirty = true;
               }
               else
               {
                  if (dMemcmp(prevBuffer.data, thisBuff.data, thisBuff.size) != 0)
                  {
                     thisBuff.isDirty = true;
                  }
                  else
                  {
                     thisBuff.isDirty = false;
                  }
               }
            }
            else
            {
               thisBuff.isDirty = true;
            }
         }
         else
         {
            thisBuff.isDirty = true;
         }
      }

      if (thisBuff.data && thisBuff.isDirty)
      {
         D3D11DEVICECONTEXT->UpdateSubresource(mBoundConstantBuffers[thisBufferDesc.key2][thisBufferDesc.key1], 0, NULL, thisBuff.data, thisBuff.size, 0);
         bufRanges[thisBufferDesc.key2].addSlot(thisBufferDesc.key1);
      }
   }

   if (mShader->mVertShader && bufRanges[GFXShaderStage::VERTEX_SHADER].isValid())
   {
      const U32 bufStartSlot = bufRanges[GFXShaderStage::VERTEX_SHADER].mBufMin;
      const U32 numBufs = bufRanges[GFXShaderStage::VERTEX_SHADER].mBufMax - bufRanges[GFXShaderStage::VERTEX_SHADER].mBufMin + 1;
      ID3D11Buffer** vsBuffers = mBoundConstantBuffers[GFXShaderStage::VERTEX_SHADER] + bufStartSlot;

      D3D11DEVICECONTEXT->VSSetConstantBuffers(bufStartSlot, numBufs, vsBuffers);
   }

   if (mShader->mPixShader && bufRanges[GFXShaderStage::PIXEL_SHADER].isValid())
   {
      const U32 bufStartSlot = bufRanges[GFXShaderStage::PIXEL_SHADER].mBufMin;
      const U32 numBufs = bufRanges[GFXShaderStage::PIXEL_SHADER].mBufMax - bufRanges[GFXShaderStage::PIXEL_SHADER].mBufMin + 1;
      ID3D11Buffer** psBuffers = mBoundConstantBuffers[GFXShaderStage::PIXEL_SHADER] + bufStartSlot;

      D3D11DEVICECONTEXT->PSSetConstantBuffers(bufStartSlot, numBufs, psBuffers);
   }

   mWasLost = false;
}

void GFXD3D11ShaderConstBuffer::onShaderReload( GFXD3D11Shader *shader )
{
   AssertFatal( shader == mShader, "GFXD3D11ShaderConstBuffer::onShaderReload is hosed!" );

   for (U32 i = 0; i < 6; i++)
   {
      for (U32 j = 0; j < 16; j++)
      {
         SAFE_RELEASE(mBoundConstantBuffers[i][j]);
      }
   }

   for (GFXD3D11Shader::BufferMap::Iterator i = shader->mBuffers.begin(); i != shader->mBuffers.end(); ++i)
   {
      // add our buffer descriptions to the full const buffer.
      this->addBuffer(i->value.bindPoint, i->value.shaderStage, i->value.size);
   }

   // Set the lost state.
   mWasLost = true;
}

//------------------------------------------------------------------------------

GFXD3D11Shader::GFXD3D11Shader()
{
   VECTOR_SET_ASSOCIATION( mShaderConsts );

   AssertFatal(D3D11DEVICE, "Invalid device for shader.");
   mVertShader = NULL;
   mPixShader = NULL;

   if( smD3DInclude == NULL )
      smD3DInclude = new gfxD3D11Include;
}

//------------------------------------------------------------------------------

GFXD3D11Shader::~GFXD3D11Shader()
{
   for (HandleMap::Iterator i = mHandles.begin(); i != mHandles.end(); i++)
      delete i->value;

   // release shaders
   SAFE_RELEASE(mVertShader);
   SAFE_RELEASE(mPixShader);
   //maybe add SAFE_RELEASE(mVertexCode) ?
}

bool GFXD3D11Shader::_init()
{
   PROFILE_SCOPE( GFXD3D11Shader_Init );

   SAFE_RELEASE(mVertShader);
   SAFE_RELEASE(mPixShader);

   // Create the macro array including the system wide macros.
   const U32 macroCount = smGlobalMacros.size() + mMacros.size() + 2;
   FrameTemp<D3D_SHADER_MACRO> d3dMacros( macroCount );

   for ( U32 i=0; i < smGlobalMacros.size(); i++ )
   {
      d3dMacros[i].Name = smGlobalMacros[i].name.c_str();
      d3dMacros[i].Definition = smGlobalMacros[i].value.c_str();
   }

   for ( U32 i=0; i < mMacros.size(); i++ )
   {
      d3dMacros[i+smGlobalMacros.size()].Name = mMacros[i].name.c_str();
      d3dMacros[i+smGlobalMacros.size()].Definition = mMacros[i].value.c_str();
   }

   d3dMacros[macroCount - 2].Name = "TORQUE_SM";
   d3dMacros[macroCount - 2].Definition = D3D11->getShaderModel().c_str();

   memset(&d3dMacros[macroCount - 1], 0, sizeof(D3D_SHADER_MACRO));

   mShaderConsts.clear();
   mSamplerDescriptions.clear();
   if (!mVertexFile.isEmpty() && !_compileShader( mVertexFile, GFXShaderStage::VERTEX_SHADER, d3dMacros) )
      return false;

   if (!mPixelFile.isEmpty() && !_compileShader( mPixelFile, GFXShaderStage::PIXEL_SHADER, d3dMacros))
      return false;

   _buildShaderConstantHandles();

   // Notify any existing buffers that the buffer 
   // layouts have changed and they need to update.
   Vector<GFXShaderConstBuffer*>::iterator biter = mActiveBuffers.begin();
   for ( ; biter != mActiveBuffers.end(); biter++ )
      ((GFXD3D11ShaderConstBuffer*)(*biter))->onShaderReload( this );

   return true;
}

bool GFXD3D11Shader::_compileShader( const Torque::Path &filePath, 
                                    GFXShaderStage shaderStage,
                                    const D3D_SHADER_MACRO *defines)
{
   PROFILE_SCOPE( GFXD3D11Shader_CompileShader );

   using namespace Torque;

   HRESULT res = E_FAIL;
   ID3DBlob* code = NULL;
   ID3DBlob* errorBuff = NULL;
   ID3D11ShaderReflection* reflectionTable = NULL;

#ifdef TORQUE_GFX_VISUAL_DEBUG //for use with NSight, GPU Perf studio, VS graphics debugger
   U32 flags = D3DCOMPILE_DEBUG | D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_PREFER_FLOW_CONTROL | D3DCOMPILE_SKIP_OPTIMIZATION;
#elif defined(TORQUE_DEBUG) //debug build
   U32 flags = D3DCOMPILE_DEBUG | D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_WARNINGS_ARE_ERRORS;
#else //release build
   U32 flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_OPTIMIZATION_LEVEL3;
#endif

#ifdef D3D11_DEBUG_SPEW
   Con::printf( "Compiling Shader: '%s'", filePath.getFullPath().c_str() );
#endif

   // Is it an HLSL shader?
   if(filePath.getExtension().equal("hlsl", String::NoCase))   
   {
      // Set this so that the D3DInclude::Open will have this 
      // information for relative paths.
      smD3DInclude->setPath(filePath.getRootAndPath());

      FileStream s;
      if (!s.open(filePath, Torque::FS::File::Read))
      {
         AssertISV(false, avar("GFXD3D11Shader::initShader - failed to open shader '%s'.", filePath.getFullPath().c_str()));

         if ( smLogErrors )
            Con::errorf( "GFXD3D11Shader::_compileShader - Failed to open shader file '%s'.", filePath.getFullPath().c_str() );

         return false;
      }

      // Convert the path which might have virtualized
      // mount paths to a real file system path.
      Torque::Path realPath;
      if (!FS::GetFSPath( filePath, realPath))
         realPath = filePath;

      U32 bufSize = s.getStreamSize();

      FrameAllocatorMarker fam;
      char *buffer = NULL;

      buffer = (char*)fam.alloc(bufSize + 1);
      s.read(bufSize, buffer);
      buffer[bufSize] = 0;

      String target;

      switch (shaderStage)
      {
      case VERTEX_SHADER:
         target = D3D11->getVertexShaderTarget();
         break;
      case PIXEL_SHADER:
         target = D3D11->getPixelShaderTarget();
         break;
      case GEOMETRY_SHADER:
         break;
      case DOMAIN_SHADER:
         break;
      case HULL_SHADER:
         break;
      case COMPUTE_SHADER:
         break;
      default:
         break;
      }

      res = D3DCompile(buffer, bufSize, realPath.getFullPath().c_str(), defines, smD3DInclude, "main", target, flags, 0, &code, &errorBuff);
   }

   if(errorBuff)
   {
      // remove \n at end of buffer
      U8 *buffPtr = (U8*) errorBuff->GetBufferPointer();
      U32 len = dStrlen( (const char*) buffPtr );
      buffPtr[len-1] = '\0';

      if(FAILED(res))
      {
         if(smLogErrors)
          Con::errorf("failed to compile shader: %s", buffPtr);
      }
      else
      {
         if(smLogWarnings)
            Con::errorf("shader compiled with warning(s): %s", buffPtr);
      }
   }
   else if (code == NULL && smLogErrors)
      Con::errorf( "GFXD3D11Shader::_compileShader - no compiled code produced; possibly missing file '%s'.", filePath.getFullPath().c_str() );

   AssertISV(SUCCEEDED(res), "Unable to compile shader!");

   if(code != NULL)
   {
      switch (shaderStage)
      {
      case VERTEX_SHADER:
         res = D3D11DEVICE->CreateVertexShader(code->GetBufferPointer(), code->GetBufferSize(), NULL, &mVertShader);
         break;
      case PIXEL_SHADER:
         res = D3D11DEVICE->CreatePixelShader(code->GetBufferPointer(), code->GetBufferSize(), NULL, &mPixShader);
         break;
      case GEOMETRY_SHADER:
         break;
      case DOMAIN_SHADER:
         break;
      case HULL_SHADER:
         break;
      case COMPUTE_SHADER:
         break;
      default:
         break;
      }
         
      if (FAILED(res))
      {
         AssertFatal(false, "D3D11Shader::_compilershader- failed to create shader");
      }

      if(res == S_OK)
      {
         HRESULT reflectionResult = D3DReflect(code->GetBufferPointer(), code->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&reflectionTable);
      if(FAILED(reflectionResult))
         AssertFatal(false, "D3D11Shader::_compilershader - Failed to get shader reflection table interface");
      }

     if(res == S_OK)
      _getShaderConstants(reflectionTable, shaderStage);

      if(FAILED(res) && smLogErrors)
         Con::errorf("GFXD3D11Shader::_compileShader - Unable to create shader for '%s'.", filePath.getFullPath().c_str());
   }

   //bool result = code && SUCCEEDED(res) && HasValidConstants;
   bool result = code && SUCCEEDED(res);

#ifdef TORQUE_DEBUG
   String shader;
   switch (shaderStage)
   {
   case VERTEX_SHADER:
      shader = mVertexFile.getFileName();
      mVertShader->SetPrivateData(WKPDID_D3DDebugObjectName, shader.size(), shader.c_str());
      break;
   case PIXEL_SHADER:
      shader = mPixelFile.getFileName();
      mPixShader->SetPrivateData(WKPDID_D3DDebugObjectName, shader.size(), shader.c_str());
      break;
   case GEOMETRY_SHADER:
      break;
   case DOMAIN_SHADER:
      break;
   case HULL_SHADER:
      break;
   case COMPUTE_SHADER:
      break;
   default:
      break;
   }
#endif
  
   SAFE_RELEASE(code); 
   SAFE_RELEASE(reflectionTable);
   SAFE_RELEASE(errorBuff);

   return result;
}

void GFXD3D11Shader::_getShaderConstants( ID3D11ShaderReflection* refTable,
                                          GFXShaderStage shaderStage)
{
   PROFILE_SCOPE(GFXD3D11Shader_GetShaderConstants);

   AssertFatal(refTable, "NULL constant table not allowed, is this an assembly shader?");

   D3D11_SHADER_DESC shaderDesc;
   if (refTable->GetDesc(&shaderDesc) != S_OK)
   {
      AssertFatal(false, "Shader Reflection table unable to be created");
   }
   // we loop through and account for the most common data types.
   bool foundGlobals = false;
   for (U32 i = 0; i < shaderDesc.ConstantBuffers; i++)
   {
      GFXShaderConstDesc desc;
      ID3D11ShaderReflectionConstantBuffer* constantBuffer = refTable->GetConstantBufferByIndex(i);
      D3D11_SHADER_BUFFER_DESC constantBufferDesc;
      
      if (constantBuffer->GetDesc(&constantBufferDesc) == S_OK)
      {
         desc.name = String(constantBufferDesc.Name);
         desc.size = constantBufferDesc.Size;
         desc.constType = GFXSCT_ConstBuffer;
         desc.shaderStage = shaderStage;
         desc.samplerReg = -1;
         // get our binding point.
         D3D11_SHADER_INPUT_BIND_DESC shaderInputBind;
         refTable->GetResourceBindingDescByName(constantBufferDesc.Name, &shaderInputBind);
         desc.bindPoint = shaderInputBind.BindPoint;
         if (String::compare(desc.name, "$Globals") == 0 || String::compare(desc.name, "$Params") == 0)
         {
            desc.name = desc.name + String::ToString((U32)shaderStage);

            if (foundGlobals)
               desc.bindPoint += 1;

            foundGlobals = true;
         }

         BufferMap::Iterator buffer = mBuffers.find(desc.name);
         // already added?
         if (buffer == mBuffers.end())
         {
            mBuffers[desc.name] = desc;
         }

         // now loop vars and add them to mShaderConsts.
         for (U32 j = 0; j < constantBufferDesc.Variables; j++)
         {
            GFXShaderConstDesc varDesc;
            ID3D11ShaderReflectionVariable* bufferVar = constantBuffer->GetVariableByIndex(j);
            D3D11_SHADER_VARIABLE_DESC shaderVarDesc;
            bufferVar->GetDesc(&shaderVarDesc);

            D3D11_SHADER_TYPE_DESC shaderTypeDesc;
            bufferVar->GetType()->GetDesc(&shaderTypeDesc);

            varDesc.name = String(shaderVarDesc.Name);
            if (varDesc.name.find("$") != 0)
               varDesc.name = String::ToString("$%s", varDesc.name.c_str());

            // set the bind point to the same as the const buffer.
            varDesc.bindPoint = desc.bindPoint;
            varDesc.offset = shaderVarDesc.StartOffset;
            varDesc.arraySize = mMax(shaderTypeDesc.Elements, 1);
            varDesc.size = shaderVarDesc.Size;
            varDesc.shaderStage = shaderStage;
            varDesc.samplerReg = -1;

#ifdef D3D11_DEBUG_SPEW
            Con::printf("Variable Name %s:, offset: %d, size: %d, constantDesc.Elements: %d", varDesc.name.c_str(), varDesc.StartOffset, varDesc.Size, varDesc.arraySize);
#endif   

            if (shaderTypeDesc.Class == D3D_SVC_SCALAR || shaderTypeDesc.Class == D3D_SVC_VECTOR)
            {
               switch (shaderTypeDesc.Type)
               {
               case D3D_SVT_BOOL:
                  varDesc.constType = (GFXShaderConstType)((U32)GFXSCT_Bool + shaderTypeDesc.Columns - 1);
                  break;
               case D3D_SVT_INT:
                  varDesc.constType = (GFXShaderConstType)((U32)GFXSCT_Int + shaderTypeDesc.Columns - 1);
                  break;
               case D3D_SVT_FLOAT:
                  varDesc.constType = (GFXShaderConstType)((U32)GFXSCT_Float + shaderTypeDesc.Columns - 1);
                  break;
               case D3D_SVT_UINT:
                  varDesc.constType = (GFXShaderConstType)((U32)GFXSCT_UInt + shaderTypeDesc.Columns - 1);
                  break;
               default:
                  AssertFatal(false, "Unknown shader constant class enum, maybe you could add it?");
                  break;
               }
            }
            else if (shaderTypeDesc.Class == D3D_SVC_MATRIX_COLUMNS || shaderTypeDesc.Class == D3D_SVC_MATRIX_ROWS)
            {
               if (shaderTypeDesc.Type != D3D_SVT_FLOAT)
               {
                  AssertFatal(false, "Only Float matrices are supported for now. Support for other types needs to be added.");
               }

               switch (shaderTypeDesc.Rows)
               {
               case 3:
                  varDesc.constType = shaderTypeDesc.Columns == 4 ? GFXSCT_Float3x4 : GFXSCT_Float3x3;
                  break;
               case 4:
                  varDesc.constType = shaderTypeDesc.Columns == 3 ? GFXSCT_Float3x3 : GFXSCT_Float4x4;
                  break;
               }
            }
            else if (shaderTypeDesc.Class == D3D_SVC_STRUCT)
            {
               // we gotta loop through its variables =/ add support in future. for now continue so it skips.
               continue;
            }

            mShaderConsts.push_back(varDesc);
         }
         
      }
      else
      {
         AssertFatal(false, "Unable to get shader constant description! (may need more elements of constantDesc");
      }

   }

   for (U32 i = 0; i < shaderDesc.BoundResources; i++)
   {
      GFXShaderConstDesc desc;
      D3D11_SHADER_INPUT_BIND_DESC shaderInputBind;
      refTable->GetResourceBindingDesc(i, &shaderInputBind);

      if (shaderInputBind.Type == D3D_SIT_TEXTURE)
      {
         /*switch (shaderInputBind.Dimension)
         {
         case D3D_SRV_DIMENSION::D3D_SRV_DIMENSION_TEXTURE1D:
            break;
         case D3D_SRV_DIMENSION::D3D_SRV_DIMENSION_TEXTURE1DARRAY:
            break;
         case D3D_SRV_DIMENSION::D3D_SRV_DIMENSION_TEXTURE2D:
            break;
         case D3D_SRV_DIMENSION::D3D_SRV_DIMENSION_TEXTURE2DARRAY:
            break;
         case D3D_SRV_DIMENSION::D3D_SRV_DIMENSION_TEXTURE2DMS:
            break;
         case D3D_SRV_DIMENSION::D3D_SRV_DIMENSION_TEXTURE2DMSARRAY:
            break;
         case D3D_SRV_DIMENSION::D3D_SRV_DIMENSION_TEXTURE3D:
            break;
         case D3D_SRV_DIMENSION::D3D_SRV_DIMENSION_TEXTURECUBE:
            break;
         case D3D_SRV_DIMENSION::D3D_SRV_DIMENSION_TEXTURECUBEARRAY:
            break;
         case D3D_SRV_DIMENSION::D3D_SRV_DIMENSION_BUFFER:
            break;
         case D3D_SRV_DIMENSION::D3D_SRV_DIMENSION_BUFFEREX:
            break;
         default:
            break;
         }*/
      }
      else if (shaderInputBind.Type == D3D_SIT_SAMPLER)
      {
         // Prepend a "$" if it doesn't exist.  Just to make things consistent.
         desc.name = String(shaderInputBind.Name);
         if (desc.name.find("$") != 0)
            desc.name = String::ToString("$%s", desc.name.c_str());
         desc.constType = GFXSCT_Sampler;
         desc.samplerReg = shaderInputBind.BindPoint;
         desc.bindPoint = -1;
         desc.shaderStage = shaderStage;
         desc.arraySize = shaderInputBind.BindCount;
         mSamplerDescriptions.push_back(desc);
      }
      else if (shaderInputBind.Type == D3D_SIT_UAV_RWTYPED              ||
               shaderInputBind.Type == D3D_SIT_UAV_RWSTRUCTURED         ||
               shaderInputBind.Type == D3D_SIT_UAV_RWBYTEADDRESS        ||
               shaderInputBind.Type == D3D_SIT_UAV_APPEND_STRUCTURED    ||
               shaderInputBind.Type == D3D_SIT_UAV_CONSUME_STRUCTURED   ||
               shaderInputBind.Type == D3D_SIT_UAV_RWSTRUCTURED_WITH_COUNTER)
      {
         // these should return an unorderedAccessViews and add them to shaderResources.
         /*switch (shaderInputBind.Dimension)
         {
         case D3D_SRV_DIMENSION::D3D_SRV_DIMENSION_TEXTURE1D:
            break;
         case D3D_SRV_DIMENSION::D3D_SRV_DIMENSION_TEXTURE1DARRAY:
            break;
         case D3D_SRV_DIMENSION::D3D_SRV_DIMENSION_TEXTURE2D:
            break;
         case D3D_SRV_DIMENSION::D3D_SRV_DIMENSION_TEXTURE2DARRAY:
            break;
         case D3D_SRV_DIMENSION::D3D_SRV_DIMENSION_TEXTURE2DMS:
            break;
         case D3D_SRV_DIMENSION::D3D_SRV_DIMENSION_TEXTURE2DMSARRAY:
            break;
         case D3D_SRV_DIMENSION::D3D_SRV_DIMENSION_TEXTURE3D:
            break;
         case D3D_SRV_DIMENSION::D3D_SRV_DIMENSION_TEXTURECUBE:
            break;
         case D3D_SRV_DIMENSION::D3D_SRV_DIMENSION_TEXTURECUBEARRAY:
            break;
         case D3D_SRV_DIMENSION::D3D_SRV_DIMENSION_BUFFER:
            break;
         case D3D_SRV_DIMENSION::D3D_SRV_DIMENSION_BUFFEREX:
            break;
         default:
            break;
         }*/
      }
      else if (shaderInputBind.Type == D3D_SIT_STRUCTURED ||
               shaderInputBind.Type == D3D_SIT_BYTEADDRESS)
      {
         // these should return shaderResourceViews and add them to shaderResources.
      }
   }
}

void GFXD3D11Shader::_buildShaderConstantHandles()
{
   // Mark all existing handles as invalid.
   // Those that are found when parsing the descriptions will then be marked valid again.
   for (HandleMap::Iterator iter = mHandles.begin(); iter != mHandles.end(); ++iter)
      (iter->value)->setValid(false);

   // loop through all constants, add them to the handle map
   // and add the const buffers to the buffer map.
   for (U32 i = 0; i < mShaderConsts.size(); i++)
   {
      GFXD3D11ShaderConstHandle* handle;
      GFXShaderConstDesc& desc = mShaderConsts[i];
      HandleMap::Iterator j = mHandles.find(desc.name);
      // already added? reinit just in case..
      // not sure if we need to do anything different with samplers.
      if (j != mHandles.end())
      {
         handle = j->value;
         handle->mShader = this;
         if((handle->mStageFlags & desc.shaderStage) == 0)
             handle->mStageFlags |= (U32)desc.shaderStage;

         handle->setValid(true);
      }
      else
      {
         handle = new GFXD3D11ShaderConstHandle(this, desc);
         mHandles[desc.name] = handle;
      }
   }

   for (U32 j = 0; j < mSamplerDescriptions.size(); j++)
   {
      const GFXShaderConstDesc& desc = mSamplerDescriptions[j];

      AssertFatal(desc.constType == GFXSCT_Sampler ||
         desc.constType == GFXSCT_SamplerCube ||
         desc.constType == GFXSCT_SamplerCubeArray ||
         desc.constType == GFXSCT_SamplerTextureArray,
         "GFXD3D11Shader::_buildShaderConstantHandles - Invalid samplerDescription type!");

      GFXD3D11ShaderConstHandle* handle;
      HandleMap::Iterator k = mHandles.find(desc.name);
      // already added? reinit just in case..
      // not sure if we need to do anything different with samplers.
      if (k != mHandles.end())
      {
         handle = k->value;
      }
      else
      {
         handle = new GFXD3D11ShaderConstHandle(this, desc);
         mHandles[desc.name] = handle;
      }

      handle->mShader = this;
      handle->setValid(true);
   }

   _buildInstancingShaderConstantHandles();
}

void GFXD3D11Shader::_buildInstancingShaderConstantHandles()
{
   // If we have no instancing than just return
   if (!mInstancingFormat)
      return;

   U32 offset = 0;
   for ( U32 i=0; i < mInstancingFormat->getElementCount(); i++ )
   {
      const GFXVertexElement &element = mInstancingFormat->getElement( i );
      
      String constName = String::ToString( "$%s", element.getSemantic().c_str() );

      GFXD3D11ShaderConstHandle *handle;
      HandleMap::Iterator j = mHandles.find( constName );
      GFXShaderConstDesc desc;

      desc.name = constName;
      desc.offset = offset;
      switch (element.getType())
      {
      case GFXDeclType_Float4:
         desc.constType = GFXSCT_Float4;
         break;

      default:
         desc.constType = GFXSCT_Float;
         break;
      }
      desc.shaderStage = GFXShaderStage::PIXEL_SHADER;
      desc.samplerReg = -1;
      desc.size = 0;
      desc.arraySize = 1;

      if ( j != mHandles.end() )
         handle = j->value; 
      else
      {
         handle = new GFXD3D11ShaderConstHandle(this, desc);
         mHandles[ constName ] = handle;         
      }

      handle->mShader = this;
      handle->setValid( true );         
      handle->mInstancingConstant = true;

      // If this is a matrix we will have 2 or 3 more of these
      // semantics with the same name after it.
      for ( ; i < mInstancingFormat->getElementCount(); i++ )
      {
         const GFXVertexElement &nextElement = mInstancingFormat->getElement( i );
         if ( nextElement.getSemantic() != element.getSemantic() )
         {
            i--;
            break;
         }
         offset += nextElement.getSizeInBytes();
      }
   }
}

GFXShaderConstBufferRef GFXD3D11Shader::allocConstBuffer()
{
   GFXD3D11ShaderConstBuffer* buffer = new GFXD3D11ShaderConstBuffer(this);

   for (BufferMap::Iterator i = mBuffers.begin(); i != mBuffers.end(); ++i)
   {
      // add our buffer descriptions to the full const buffer.
      buffer->addBuffer(i->value.bindPoint, i->value.shaderStage, i->value.size);
   }

   mActiveBuffers.push_back( buffer );
   buffer->registerResourceWithDevice(getOwningDevice());
   return buffer;
}

/// Returns a shader constant handle for name, if the variable doesn't exist NULL is returned.
GFXShaderConstHandle* GFXD3D11Shader::getShaderConstHandle(const String& name)
{
   HandleMap::Iterator i = mHandles.find(name);   
   if ( i != mHandles.end() )
   {
      return i->value;
   } 
   else 
   {     
      GFXD3D11ShaderConstHandle *handle = new GFXD3D11ShaderConstHandle(this);
      handle->setValid( false );
      mHandles[name] = handle;

      return handle;      
   }      
}

GFXShaderConstHandle* GFXD3D11Shader::findShaderConstHandle(const String& name)
{
   HandleMap::Iterator i = mHandles.find(name);
   if(i != mHandles.end())
      return i->value;
   else
   {
      return NULL;
   }
}

const Vector<GFXShaderConstDesc>& GFXD3D11Shader::getShaderConstDesc() const
{
   return mShaderConsts;
}

U32 GFXD3D11Shader::getAlignmentValue(const GFXShaderConstType constType) const
{   
   const U32 mRowSizeF = 16;
   const U32 mRowSizeI = 16;

   switch (constType)
   {
      case GFXSCT_Float :
      case GFXSCT_Float2 :
      case GFXSCT_Float3 : 
      case GFXSCT_Float4 :
         return mRowSizeF;
         break;
         // Matrices
      case GFXSCT_Float2x2 :
         return mRowSizeF * 2;
         break;
      case GFXSCT_Float3x3 : 
         return mRowSizeF * 3;
         break;
      case GFXSCT_Float4x3:
         return mRowSizeF * 3;
         break;
      case GFXSCT_Float4x4 :
         return mRowSizeF * 4;
         break;   
      //// Scalar
      case GFXSCT_Int :
      case GFXSCT_Int2 :
      case GFXSCT_Int3 : 
      case GFXSCT_Int4 :
         return mRowSizeI;
         break;
      default:
         AssertFatal(false, "Unsupported type!");
         return 0;
         break;
   }
}

void GFXD3D11Shader::zombify()
{
   // Shaders don't need zombification
}

void GFXD3D11Shader::resurrect()
{
   // Shaders are never zombies, and therefore don't have to be brought back.
}
