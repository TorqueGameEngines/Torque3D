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
   mStage = SHADER_STAGE::UNKNOWN_STAGE;
}

GFXD3D11ShaderConstHandle::GFXD3D11ShaderConstHandle(GFXD3D11Shader* shader,
                                                      const GFXShaderConstDesc& desc)
   : mShader(shader),
   mDesc(desc),
   mStage((SHADER_STAGE)desc.shaderStage),
   mOffset(desc.offset),
   mSize(desc.size * desc.arraySize),
   mBinding(desc.bindPoint),
   mSampler(desc.samplerReg),
   mInstancingConstant(false)
{
   if (desc.constType == GFXSCT_ConstBuffer)
      mValid = false;
   else
      mValid = true;
}

GFXD3D11ShaderConstHandle::~GFXD3D11ShaderConstHandle()
{
}

void GFXD3D11ShaderConstHandle::reinit(const GFXShaderConstDesc& desc)
{
   mDesc                = desc;
   mStage               = (SHADER_STAGE)desc.shaderStage;
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

   for (U32 i = 0; i < 16; i++)
   {
      mBoundConstantBuffers[i] = NULL;
   }
}

GFXD3D11ShaderConstBuffer::~GFXD3D11ShaderConstBuffer()
{
   mBufferMap.clear();

   for (U32 i = 0; i < 16; i++)
   {
      SAFE_RELEASE(mBoundConstantBuffers[i]);
   }


   if (mShader)
      mShader->_unlinkBuffer(this);
}

GFXShader* GFXD3D11ShaderConstBuffer::getShader()
{
   return mShader;
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const F32 fv) 
{
   internalSet(handle, fv);
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const Point2F& fv) 
{
   internalSet(handle, fv);
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const Point3F& fv) 
{
   internalSet(handle, fv);
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const Point4F& fv) 
{
   internalSet(handle, fv);
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const PlaneF& fv) 
{
   internalSet(handle, fv);
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const LinearColorF& fv)
{
   internalSet(handle, fv);
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const S32 fv)
{ 
   // This is the only type that is allowed to be used
   // with a sampler shader constant type, but it is only
   // allowed to be set from GLSL.
   //
   // So we ignore it here... all other cases will assert.
   //
   if ( ((GFXD3D11ShaderConstHandle*)handle)->isSampler() )
      return;

   internalSet(handle, fv);
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const Point2I& fv)
{
   internalSet(handle, fv);
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const Point3I& fv)
{
   internalSet(handle, fv);
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const Point4I& fv)
{
   internalSet(handle, fv);
}


template<typename ConstType>
void GFXD3D11ShaderConstBuffer::internalSet(GFXShaderConstHandle* handle, const ConstType& param)
{
   AssertFatal(handle, "GFXD3D11ShaderConstBuffer::internalSet - Handle is NULL!");
   AssertFatal(handle->isValid(), "GFXD3D11ShaderConstBuffer::internalSet - Handle is not valid!");
   AssertFatal(dynamic_cast<GFXD3D11ShaderConstHandle*>(handle), "GFXD3D11ShaderConstBuffer::internalSet - Incorrect const buffer type");

   GFXD3D11ShaderConstHandle* _dxHandle = static_cast<GFXD3D11ShaderConstHandle*>(handle);
   AssertFatal(mShader == _dxHandle->mShader, "GFXD3D11ShaderConstBuffer::internalSet - Should only set handles which are owned by our shader");

   const BufferKey bufDesc(_dxHandle->mBinding, (SHADER_STAGE)_dxHandle->mStage);
   U8* buf = mBufferMap[bufDesc].data + _dxHandle->mOffset;

   if (_dxHandle->mInstancingConstant)
      buf = mInstPtr + _dxHandle->mOffset;

   dMemcpy(buf, &param, sizeof(ConstType));
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const AlignedArray<F32>& fv)
{
   internalSet(handle, fv);
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const AlignedArray<Point2F>& fv)
{
   internalSet(handle, fv);
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const AlignedArray<Point3F>& fv)
{
   internalSet(handle, fv);
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const AlignedArray<Point4F>& fv)
{
   internalSet(handle, fv);
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const AlignedArray<S32>& fv)
{
   internalSet(handle, fv);
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const AlignedArray<Point2I>& fv)
{
   internalSet(handle, fv);
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const AlignedArray<Point3I>& fv)
{
   internalSet(handle, fv);
}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const AlignedArray<Point4I>& fv)
{
   internalSet(handle, fv);
}

template<typename ConstType>
void GFXD3D11ShaderConstBuffer::internalSet(GFXShaderConstHandle* handle, const AlignedArray<ConstType>& fv)
{
   AssertFatal(handle, "GFXD3D11ShaderConstBuffer::internalSet - Handle is NULL!");
   AssertFatal(handle->isValid(), "GFXD3D11ShaderConstBuffer::internalSet - Handle is not valid!");
   AssertFatal(dynamic_cast<GFXD3D11ShaderConstHandle*>(handle), "GFXD3D11ShaderConstBuffer::internalSet - Incorrect const buffer type");

   GFXD3D11ShaderConstHandle* _dxHandle = static_cast<GFXD3D11ShaderConstHandle*>(handle);
   AssertFatal(mShader == _dxHandle->mShader, "GFXD3D11ShaderConstBuffer::internalSet - Should only set handles which are owned by our shader");
   AssertFatal(!_dxHandle->mInstancingConstant, "GFXD3D11ShaderConstBuffer::internalSet - Instancing not supported for array");
   const BufferKey bufDesc(_dxHandle->mBinding, (SHADER_STAGE)_dxHandle->mStage);
   U8* buf = mBufferMap[bufDesc].data;
   const U8* fvBuffer = static_cast<const U8*>(fv.getBuffer());
   for (U32 i = 0; i < fv.size(); ++i)
   {
      dMemcpy(buf + _dxHandle->mOffset + i * sizeof(ConstType), fvBuffer, sizeof(ConstType));
      fvBuffer += fv.getElementSize();
   }

}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const MatrixF& mat, const GFXShaderConstType matrixType) 
{    
   AssertFatal(handle, "Handle is NULL!" );
   AssertFatal(handle->isValid(), "Handle is not valid!" );

   AssertFatal(static_cast<const GFXD3D11ShaderConstHandle*>(handle), "Incorrect const buffer type!"); 
   const GFXD3D11ShaderConstHandle* _dxHandle = static_cast<const GFXD3D11ShaderConstHandle*>(handle);
   AssertFatal(!_dxHandle->isSampler(), "Handle is sampler constant!" );
   AssertFatal(_dxHandle->mShader == mShader, "Mismatched shaders!");
   const BufferKey bufDesc(_dxHandle->mBinding, (SHADER_STAGE)_dxHandle->mStage);
   U8* buf = mBufferMap[bufDesc].data;

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

   if (matrixType == GFXSCT_Float4x4)
   {
      dMemcpy(buf, &transposed, sizeof(MatrixF));
      return;
   }

   U32 csize;
   switch (matrixType)
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
      return;
      break;
   }

   dMemcpy(buf, (const F32*)transposed, csize);

}

void GFXD3D11ShaderConstBuffer::set(GFXShaderConstHandle* handle, const MatrixF* mat, const U32 arraySize, const GFXShaderConstType matrixType)
{
   AssertFatal(handle, "Handle is NULL!");
   AssertFatal(handle->isValid(), "Handle is not valid!");

   AssertFatal(static_cast<const GFXD3D11ShaderConstHandle*>(handle), "Incorrect const buffer type!");
   const GFXD3D11ShaderConstHandle* _dxHandle = static_cast<const GFXD3D11ShaderConstHandle*>(handle);
   AssertFatal(!_dxHandle->isSampler(), "Handle is sampler constant!");
   AssertFatal(_dxHandle->mShader == mShader, "Mismatched shaders!");

   const BufferKey bufDesc(_dxHandle->mBinding, (SHADER_STAGE)_dxHandle->mStage);

   U8* buf = mBufferMap[bufDesc].data;

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

   if (matrixType == GFXSCT_Float4x4)
   {
      dMemcpy(buf + _dxHandle->mOffset, transposed.address(), _dxHandle->getSize());
      return;
   }

   U32 csize;
   switch (matrixType)
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
      return;
      break;
   }

   for (int i = 0; i < arraySize; i++)
   {
      dMemcpy(buf + _dxHandle->mOffset + (i * csize), transposed[i], csize);
   }

}

const String GFXD3D11ShaderConstBuffer::describeSelf() const
{
   String ret;
   ret = String("   GFXD3D11ShaderConstBuffer\n");


   return ret;
}

void GFXD3D11ShaderConstBuffer::addBuffer(U32 bufBindingPoint, SHADER_STAGE shaderStage, U32 size)
{
   const BufferKey bufKey(bufBindingPoint, shaderStage);
   BufferMap::Iterator buffer = mBufferMap.find(bufKey);
   // already added? pass...
   if (buffer != mBufferMap.end())
      return;

   // new buffer with our size.
   mBufferMap[bufKey].data = new U8[size];
   dMemset(mBufferMap[bufKey].data, 0, size);
   // always dirty on new.
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
   hr = D3D11DEVICE->CreateBuffer(&cbDesc, NULL, &mBoundConstantBuffers[bufBindingPoint]);

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

      const ConstantBuffer prevBuffer = prevShaderBuffer->mBufferMap[i->key];

      if (prevBuffer.data && !prevBuffer.isDirty)
      {
         if (prevBuffer.size != thisBuff.size)
         {
            thisBuff.isDirty = true;
         }

         if (dMemcmp(prevBuffer.data, thisBuff.data, thisBuff.size) != 0)
         {
            thisBuff.isDirty = true;
         }
         else
         {
            thisBuff.isDirty = false;
         }
      }
      else
      {
         thisBuff.isDirty = true;
      }

      if (thisBuff.data && thisBuff.isDirty)
      {
         D3D11DEVICECONTEXT->UpdateSubresource(mBoundConstantBuffers[thisBufferDesc.key1], 0, NULL, thisBuff.data, thisBuff.size, 0);
         bufRanges[thisBufferDesc.key2].addSlot(thisBufferDesc.key1);
      }
   }

   if (bufRanges[SHADER_STAGE::ALL_SHADERS].isValid())
   {
      const U32 bufStartSlot = bufRanges[SHADER_STAGE::ALL_SHADERS].mBufMin;
      const U32 numBufs = bufRanges[SHADER_STAGE::ALL_SHADERS].mBufMax - bufRanges[SHADER_STAGE::ALL_SHADERS].mBufMin + 1;
      ID3D11Buffer** globalBuffer = mBoundConstantBuffers + bufStartSlot;

      if(mShader->mVertShader)
         D3D11DEVICECONTEXT->VSSetConstantBuffers(bufStartSlot, numBufs, globalBuffer);
      if(mShader->mPixShader)
         D3D11DEVICECONTEXT->PSSetConstantBuffers(bufStartSlot, numBufs, globalBuffer);
   }

   if (mShader->mVertShader && bufRanges[SHADER_STAGE::VERTEX_SHADER].isValid())
   {
      const U32 bufStartSlot = bufRanges[SHADER_STAGE::VERTEX_SHADER].mBufMin;
      const U32 numBufs = bufRanges[SHADER_STAGE::VERTEX_SHADER].mBufMax - bufRanges[SHADER_STAGE::VERTEX_SHADER].mBufMin + 1;
      ID3D11Buffer** vsBuffers = mBoundConstantBuffers + bufStartSlot;

      D3D11DEVICECONTEXT->VSSetConstantBuffers(bufStartSlot, numBufs, vsBuffers);
   }

   if (mShader->mPixShader && bufRanges[SHADER_STAGE::PIXEL_SHADER].isValid())
   {
      const U32 bufStartSlot = bufRanges[SHADER_STAGE::PIXEL_SHADER].mBufMin;
      const U32 numBufs = bufRanges[SHADER_STAGE::PIXEL_SHADER].mBufMax - bufRanges[SHADER_STAGE::PIXEL_SHADER].mBufMin + 1;
      ID3D11Buffer** psBuffers = mBoundConstantBuffers + bufStartSlot;

      D3D11DEVICECONTEXT->PSSetConstantBuffers(bufStartSlot, numBufs, psBuffers);
   }

   mWasLost = false;
}

void GFXD3D11ShaderConstBuffer::onShaderReload( GFXD3D11Shader *shader )
{
   AssertFatal( shader == mShader, "GFXD3D11ShaderConstBuffer::onShaderReload is hosed!" );

   for (BufferMap::Iterator i = mBufferMap.begin(); i != mBufferMap.end(); i++)
   {
      delete[] i->value.data;
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

   globalAdded = false;
   globalOffset = 0;
   globalSize = 0;
}

//------------------------------------------------------------------------------

GFXD3D11Shader::~GFXD3D11Shader()
{
   mHandles.clear();

   mBuffers.clear();

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
   if (!mVertexFile.isEmpty() && !_compileShader( mVertexFile, SHADER_STAGE::VERTEX_SHADER, d3dMacros) )
      return false;

   if (!mPixelFile.isEmpty() && !_compileShader( mPixelFile, SHADER_STAGE::PIXEL_SHADER, d3dMacros))
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
                                    SHADER_STAGE shaderStage,                                  
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

void GFXD3D11Shader::_getShaderConstants( ID3D11ShaderReflection *refTable,
                                          SHADER_STAGE shaderStage)
{
   PROFILE_SCOPE( GFXD3D11Shader_GetShaderConstants );

   AssertFatal(refTable, "NULL constant table not allowed, is this an assembly shader?");

   D3D11_SHADER_DESC shaderDesc;
   refTable->GetDesc(&shaderDesc);

   bool globalBuffer = false;
   // we loop through and account for the most common data types.
   for (U32 i = 0; i < shaderDesc.BoundResources; i++)
   {
      GFXShaderConstDesc desc;
      D3D11_SHADER_INPUT_BIND_DESC shaderInputBind;
      refTable->GetResourceBindingDesc(i, &shaderInputBind);

      if (shaderInputBind.Type == D3D_SIT_CBUFFER)
      {
         desc.name = String(shaderInputBind.Name);
         if (desc.name.find("$") != 0)
            desc.name = String::ToString("$%s", desc.name.c_str());

         if (String::compare(desc.name, "$Globals") == 0 || String::compare(desc.name, "$Params") == 0)
         {
            globalBuffer = true;
         }

         desc.constType = GFXSCT_ConstBuffer;
         desc.bindPoint = shaderInputBind.BindPoint;
         desc.shaderStage = globalBuffer ? SHADER_STAGE::ALL_SHADERS : shaderStage;
         desc.samplerReg = -1;
         ID3D11ShaderReflectionConstantBuffer* constantBuffer = refTable->GetConstantBufferByName(shaderInputBind.Name);
         D3D11_SHADER_BUFFER_DESC constantBufferDesc;

         constantBuffer->GetDesc(&constantBufferDesc);

#ifdef D3D11_DEBUG_SPEW
         Con::printf("Constant Buffer Name: %s", constantBufferDesc.Name);
#endif 
         // push back our const buffer as a descriptor, this also marks the start of a buffer.
         desc.size = constantBufferDesc.Size;

         globalSize += desc.size;

         if(globalBuffer && !globalAdded)
            mShaderConsts.push_back(desc);
         else if (!globalBuffer)
            mShaderConsts.push_back(desc);

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
            varDesc.offset = globalBuffer ? globalOffset + shaderVarDesc.StartOffset : shaderVarDesc.StartOffset;
            varDesc.arraySize = mMax(shaderTypeDesc.Elements, 1);
            varDesc.size = shaderVarDesc.Size;
            varDesc.shaderStage = globalBuffer ? SHADER_STAGE::ALL_SHADERS : shaderStage;
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

         globalOffset += desc.size;
      }
      else if (shaderInputBind.Type == D3D_SIT_TEXTURE)
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
      GFXShaderConstDesc& desc = mShaderConsts[i];

      if (desc.constType == GFXSCT_ConstBuffer)
      {
         const BufferKey bufKey(desc.bindPoint, (SHADER_STAGE)desc.shaderStage);

         BufferMap::Iterator buffer = mBuffers.find(bufKey);
         // already added? pass...
         if (buffer != mBuffers.end())
            continue;

         Vector<U8> buf;
         buf.setSize(desc.size);

         if (desc.shaderStage == SHADER_STAGE::ALL_SHADERS)
            buf.setSize(globalSize);

         // new buffer with our size.
         mBuffers[bufKey] = buf;

         // do not add to handles..
         continue;
      }

      HandleMap::Iterator handle = mHandles.find(desc.name);
      // already added? reinit just in case..
      // not sure if we need to do anything different with samplers.
      if (handle != mHandles.end())
      {
         handle->value->reinit(desc);
      }
      else
      {
         mHandles[desc.name] = new GFXD3D11ShaderConstHandle(this, desc);
      }
   }

   for (U32 i = 0; i < mSamplerDescriptions.size(); i++)
   {
      GFXShaderConstDesc& desc = mSamplerDescriptions[i];

      AssertFatal(desc.constType == GFXSCT_Sampler ||
         desc.constType == GFXSCT_SamplerCube ||
         desc.constType == GFXSCT_SamplerCubeArray ||
         desc.constType == GFXSCT_SamplerTextureArray,
         "GFXD3D11Shader::_buildShaderConstantHandles - Invalid samplerDescription type!");

      HandleMap::Iterator handle = mHandles.find(desc.name);
      // already added? reinit just in case..
      // not sure if we need to do anything different with samplers.
      if (handle != mHandles.end())
      {
         handle->value->reinit(desc);
      }
      else
      {
         mHandles[desc.name] = new GFXD3D11ShaderConstHandle(this, desc);
      }
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

      if ( j != mHandles.end() )
         handle = j->value; 
      else
      {
         handle = new GFXD3D11ShaderConstHandle(this);
         mHandles[ constName ] = handle;         
      }

      handle->setValid( true );         
      handle->mInstancingConstant = true;
      handle->mOffset = offset;

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
      buffer->addBuffer(i->key.key1,i->key.key2, i->value.size());
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
