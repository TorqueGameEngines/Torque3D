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

#include "platform/platform.h"
#include "gfx/gl/gfxGLShader.h"
#include "gfx/gl/gfxGLVertexAttribLocation.h"
#include "gfx/gl/gfxGLDevice.h"

#include "core/frameAllocator.h"
#include "core/stream/fileStream.h"
#include "core/strings/stringFunctions.h"
#include "math/mPoint2.h"
#include "gfx/gfxStructs.h"
#include "console/console.h"

#define CHECK_AARG(pos, name) static StringTableEntry attr_##name = StringTable->insert(#name); if (argName == attr_##name) { glBindAttribLocation(mProgram, pos, attr_##name); continue; }

GFXGLShaderConstHandle::GFXGLShaderConstHandle(GFXGLShader* shader)
   : mShader(shader),
   mUBOUniform(false),
   mInstancingConstant(false)
{
   dMemset(&mDesc, 0, sizeof(mDesc));
   mValid = false;
}

GFXGLShaderConstHandle::GFXGLShaderConstHandle(GFXGLShader* shader,
   const GFXShaderConstDesc& desc)
   : mShader(shader),
   mDesc(desc),
   mUBOUniform(false),
   mInstancingConstant(false)
{
   if (desc.constType == GFXSCT_ConstBuffer)
      mValid = false;
   else
      mValid = true;
}

void GFXGLShaderConstHandle::reinit(const GFXShaderConstDesc& desc)
{
   mDesc = desc;
   mValid = true;
}

GFXGLShaderConstHandle::~GFXGLShaderConstHandle()
{
}

const GFXShaderConstDesc GFXGLShaderConstHandle::getDesc()
{
   return mDesc;
}

static U32 shaderConstTypeSize(GFXShaderConstType type)
{
   switch (type)
   {
   case GFXSCT_Float:
   case GFXSCT_Int:
   case GFXSCT_UInt:
   case GFXSCT_Bool:
   case GFXSCT_Sampler:
   case GFXSCT_SamplerCube:
   case GFXSCT_SamplerCubeArray:
   case GFXSCT_SamplerTextureArray:
      return 4;
   case GFXSCT_Float2:
   case GFXSCT_Int2:
   case GFXSCT_UInt2:
   case GFXSCT_Bool2:
      return 8;
   case GFXSCT_Float3:
   case GFXSCT_Int3:
   case GFXSCT_UInt3:
   case GFXSCT_Bool3:
      return 12;
   case GFXSCT_Float4:
   case GFXSCT_Int4:
   case GFXSCT_UInt4:
   case GFXSCT_Bool4:
      return 16;
   case GFXSCT_Float2x2:
      return 16;
   case GFXSCT_Float3x3:
      return 36;
   case GFXSCT_Float4x3:
      return 48;
   case GFXSCT_Float4x4:
      return 64;
   default:
      AssertFatal(false, "shaderConstTypeSize - Unrecognized constant type");
      return 0;
   }
}

GFXGLShaderConstBuffer::GFXGLShaderConstBuffer(GFXGLShader* shader)
{
   mShader = shader;
   mWasLost = true;
}

GFXGLShaderConstBuffer::~GFXGLShaderConstBuffer()
{
   if (mShader)
      mShader->_unlinkBuffer(this);
}

template<typename ConstType>
void GFXGLShaderConstBuffer::internalSet(GFXShaderConstHandle* handle, const ConstType& param)
{
   AssertFatal(handle, "GFXGLShaderConstBuffer::internalSet - Handle is NULL!");
   AssertFatal(handle->isValid(), "GFXGLShaderConstBuffer::internalSet - Handle is not valid!");
   AssertFatal(dynamic_cast<GFXGLShaderConstHandle*>(handle), "GFXGLShaderConstBuffer::set - Incorrect const buffer type");

   GFXGLShaderConstHandle* _glHandle = static_cast<GFXGLShaderConstHandle*>(handle);
   AssertFatal(mShader == _glHandle->mShader, "GFXGLShaderConstBuffer::set - Should only set handles which are owned by our shader");

   U8* basePointer;
   if (!_glHandle->mUBOUniform)
   {
      basePointer = mBufferMap[-1].data;
   }
   else
   {
      basePointer = mBufferMap[_glHandle->mDesc.bindPoint].data;
   }

   U8* buf = basePointer + _glHandle->mDesc.offset;

   if (_glHandle->mInstancingConstant)
      buf = mInstPtr + _glHandle->mDesc.offset;

   dMemcpy(buf, &param, sizeof(ConstType));
}

GFXShader* GFXGLShaderConstBuffer::getShader()
{
   return mShader;
}

void GFXGLShaderConstBuffer::set(GFXShaderConstHandle* handle, const F32 fv)
{
   internalSet(handle, fv);
}

void GFXGLShaderConstBuffer::set(GFXShaderConstHandle* handle, const Point2F& fv)
{
   internalSet(handle, fv);
}

void GFXGLShaderConstBuffer::set(GFXShaderConstHandle* handle, const Point3F& fv)
{
   internalSet(handle, fv);
}

void GFXGLShaderConstBuffer::set(GFXShaderConstHandle* handle, const Point4F& fv)
{
   internalSet(handle, fv);
}

void GFXGLShaderConstBuffer::set(GFXShaderConstHandle* handle, const PlaneF& fv)
{
   internalSet(handle, fv);
}

void GFXGLShaderConstBuffer::set(GFXShaderConstHandle* handle, const LinearColorF& fv)
{
   internalSet(handle, fv);
}

void GFXGLShaderConstBuffer::set(GFXShaderConstHandle* handle, const S32 fv)
{
   internalSet(handle, fv);
}

void GFXGLShaderConstBuffer::set(GFXShaderConstHandle* handle, const Point2I& fv)
{
   internalSet(handle, fv);
}

void GFXGLShaderConstBuffer::set(GFXShaderConstHandle* handle, const Point3I& fv)
{
   internalSet(handle, fv);
}

void GFXGLShaderConstBuffer::set(GFXShaderConstHandle* handle, const Point4I& fv)
{
   internalSet(handle, fv);
}

template<typename ConstType>
void GFXGLShaderConstBuffer::internalSet(GFXShaderConstHandle* handle, const AlignedArray<ConstType>& fv)
{
   AssertFatal(handle, "GFXGLShaderConstBuffer::internalSet - Handle is NULL!");
   AssertFatal(handle->isValid(), "GFXGLShaderConstBuffer::internalSet - Handle is not valid!");
   AssertFatal(dynamic_cast<GFXGLShaderConstHandle*>(handle), "GFXGLShaderConstBuffer::set - Incorrect const buffer type");

   GFXGLShaderConstHandle* _glHandle = static_cast<GFXGLShaderConstHandle*>(handle);
   AssertFatal(mShader == _glHandle->mShader, "GFXGLShaderConstBuffer::set - Should only set handles which are owned by our shader");
   AssertFatal(!_glHandle->mInstancingConstant, "GFXGLShaderConstBuffer::set - Instancing not supported for array");

   U8* basePointer;
   if (!_glHandle->mUBOUniform)
   {
      basePointer = mBufferMap[-1].data;
   }
   else
   {
      basePointer = mBufferMap[_glHandle->mDesc.bindPoint].data;
   }

   const U8* fvBuffer = static_cast<const U8*>(fv.getBuffer());
   for (U32 i = 0; i < fv.size(); ++i)
   {
      dMemcpy(basePointer + _glHandle->mDesc.offset + i * sizeof(ConstType), fvBuffer, sizeof(ConstType));
      fvBuffer += fv.getElementSize();
   }
}

void GFXGLShaderConstBuffer::set(GFXShaderConstHandle* handle, const AlignedArray<F32>& fv)
{
   internalSet(handle, fv);
}

void GFXGLShaderConstBuffer::set(GFXShaderConstHandle* handle, const AlignedArray<Point2F>& fv)
{
   internalSet(handle, fv);
}

void GFXGLShaderConstBuffer::set(GFXShaderConstHandle* handle, const AlignedArray<Point3F>& fv)
{
   internalSet(handle, fv);
}

void GFXGLShaderConstBuffer::set(GFXShaderConstHandle* handle, const AlignedArray<Point4F>& fv)
{
   internalSet(handle, fv);
}

void GFXGLShaderConstBuffer::set(GFXShaderConstHandle* handle, const AlignedArray<S32>& fv)
{
   internalSet(handle, fv);
}

void GFXGLShaderConstBuffer::set(GFXShaderConstHandle* handle, const AlignedArray<Point2I>& fv)
{
   internalSet(handle, fv);
}

void GFXGLShaderConstBuffer::set(GFXShaderConstHandle* handle, const AlignedArray<Point3I>& fv)
{
   internalSet(handle, fv);
}

void GFXGLShaderConstBuffer::set(GFXShaderConstHandle* handle, const AlignedArray<Point4I>& fv)
{
   internalSet(handle, fv);
}

void GFXGLShaderConstBuffer::set(GFXShaderConstHandle* handle, const MatrixF& mat, const GFXShaderConstType matType)
{
   AssertFatal(handle, "GFXGLShaderConstBuffer::set - Handle is NULL!");
   AssertFatal(handle->isValid(), "GFXGLShaderConstBuffer::set - Handle is not valid!");
   AssertFatal(dynamic_cast<GFXGLShaderConstHandle*>(handle), "GFXGLShaderConstBuffer::set - Incorrect const buffer type");

   GFXGLShaderConstHandle* _glHandle = static_cast<GFXGLShaderConstHandle*>(handle);
   AssertFatal(mShader == _glHandle->mShader, "GFXGLShaderConstBuffer::set - Should only set handles which are owned by our shader");
   AssertFatal(!_glHandle->mInstancingConstant || matType == GFXSCT_Float4x4, "GFXGLShaderConstBuffer::set - Only support GFXSCT_Float4x4 for instancing");

   U8* basePointer;
   if (!_glHandle->mUBOUniform)
   {
      basePointer = mBufferMap[-1].data;
   }
   else
   {
      basePointer = mBufferMap[_glHandle->mDesc.bindPoint].data;
   }

   switch (matType)
   {
   case GFXSCT_Float2x2:
      reinterpret_cast<F32*>(basePointer + _glHandle->mDesc.offset)[0] = mat[0];
      reinterpret_cast<F32*>(basePointer + _glHandle->mDesc.offset)[1] = mat[1];
      reinterpret_cast<F32*>(basePointer + _glHandle->mDesc.offset)[2] = mat[4];
      reinterpret_cast<F32*>(basePointer + _glHandle->mDesc.offset)[3] = mat[5];
      break;
   case GFXSCT_Float3x3:
      reinterpret_cast<F32*>(basePointer + _glHandle->mDesc.offset)[0] = mat[0];
      reinterpret_cast<F32*>(basePointer + _glHandle->mDesc.offset)[1] = mat[1];
      reinterpret_cast<F32*>(basePointer + _glHandle->mDesc.offset)[2] = mat[2];
      reinterpret_cast<F32*>(basePointer + _glHandle->mDesc.offset)[3] = mat[4];
      reinterpret_cast<F32*>(basePointer + _glHandle->mDesc.offset)[4] = mat[5];
      reinterpret_cast<F32*>(basePointer + _glHandle->mDesc.offset)[5] = mat[6];
      reinterpret_cast<F32*>(basePointer + _glHandle->mDesc.offset)[6] = mat[8];
      reinterpret_cast<F32*>(basePointer + _glHandle->mDesc.offset)[7] = mat[9];
      reinterpret_cast<F32*>(basePointer + _glHandle->mDesc.offset)[8] = mat[10];
      break;
   case GFXSCT_Float4x3:
      dMemcpy(basePointer + _glHandle->mDesc.offset, (const F32*)mat, (sizeof(F32) * 12));// matrix with end row chopped off
      break;
   case GFXSCT_Float4x4:
   {
      if (_glHandle->mInstancingConstant)
      {
         MatrixF transposed;
         mat.transposeTo(transposed);
         dMemcpy(mInstPtr + _glHandle->mDesc.offset, (const F32*)transposed, sizeof(MatrixF));
         return;
      }

      dMemcpy(basePointer + _glHandle->mDesc.offset, (const F32*)mat, sizeof(MatrixF));
      break;
   }
   default:
      AssertFatal(false, "GFXGLShaderConstBuffer::set - Invalid matrix type");
      break;
   }
}

void GFXGLShaderConstBuffer::set(GFXShaderConstHandle* handle, const MatrixF* mat, const U32 arraySize, const GFXShaderConstType matrixType)
{
   AssertFatal(handle, "GFXGLShaderConstBuffer::set - Handle is NULL!");
   AssertFatal(handle->isValid(), "GFXGLShaderConstBuffer::set - Handle is not valid!");

   GFXGLShaderConstHandle* _glHandle = static_cast<GFXGLShaderConstHandle*>(handle);
   AssertFatal(mShader == _glHandle->mShader, "GFXGLShaderConstBuffer::set - Should only set handles which are owned by our shader");
   AssertFatal(!_glHandle->mInstancingConstant, "GFXGLShaderConstBuffer::set - Instancing not supported for matrix arrays");

   U8* basePointer;
   if (!_glHandle->mUBOUniform)
   {
      basePointer = mBufferMap[-1].data;
   }
   else
   {
      basePointer = mBufferMap[_glHandle->mDesc.bindPoint].data;
   }

   switch (matrixType) {
   case GFXSCT_Float4x3:
      // Copy each item with the last row chopped off
      for (int i = 0; i < arraySize; i++)
      {
         dMemcpy(basePointer + _glHandle->mDesc.offset + (i * (sizeof(F32) * 12)), (F32*)(mat + i), sizeof(F32) * 12);
      }
      break;
   case GFXSCT_Float4x4:
      dMemcpy(basePointer + _glHandle->mDesc.offset, (F32*)mat, _glHandle->getSize());
      break;
   default:
      AssertFatal(false, "GFXGLShaderConstBuffer::set - setting array of non 4x4 matrices!");
      break;
   }
}

void GFXGLShaderConstBuffer::activate(GFXGLShaderConstBuffer* prevShaderBuffer)
{
   PROFILE_SCOPE(GFXGLShaderConstBuffer_activate);

   for (BufferMap::Iterator i = mBufferMap.begin(); i != mBufferMap.end(); ++i)
   {
      const S32 thisBufferDesc = i->key;

      // set the global buffer differently
      if (thisBufferDesc == -1)
      {
         mShader->setConstantsFromBuffer(mBufferMap[-1].data);
         continue;
      }

      ConstantBuffer thisBuff = i->value;

      if (prevShaderBuffer && prevShaderBuffer != this)
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

      if (thisBuff.data && thisBuff.isDirty)
      {
         glBindBuffer(GL_UNIFORM_BUFFER, thisBuff.bufHandle);
         glBufferData(GL_UNIFORM_BUFFER, thisBuff.size, thisBuff.data, GL_DYNAMIC_DRAW);
         glBindBufferBase(GL_UNIFORM_BUFFER, thisBufferDesc, thisBuff.bufHandle);
      }
   }

   mWasLost = false;
}

void GFXGLShaderConstBuffer::addBuffer(const GFXShaderConstDesc desc)
{
   // if this is the global buffer set it to the highest.
   if (desc.bindPoint == -1)
   {
      // we dont create a bufferhandle for this one.
      U8* buf = new U8[desc.size];
      dMemset(buf, 0, desc.size);
      mBufferMap[-1].data = buf;
      mBufferMap[-1].size = desc.size;
      mBufferMap[-1].isDirty = true;
   }
   else
   {
      U8* buf = new U8[desc.size];
      dMemset(buf, 0, desc.size);
      mBufferMap[desc.bindPoint].data = buf;
      mBufferMap[desc.bindPoint].size = desc.size;
      mBufferMap[desc.bindPoint].isDirty = true;

      mBufferMap[desc.bindPoint].bufHandle = GFXGL->getDeviceBuffer(desc);
   }
}

const String GFXGLShaderConstBuffer::describeSelf() const
{
   return String();
}

void GFXGLShaderConstBuffer::onShaderReload(GFXGLShader* shader)
{
   AssertFatal(shader == mShader, "GFXGLShaderConstBuffer::onShaderReload, mismatched shaders!");

   for (auto& pair : mBufferMap) {
      delete[] pair.value.data;
   }
   mBufferMap.clear(); // Clear the map

   for (GFXGLShader::BufferMap::Iterator i = shader->mBuffers.begin(); i != shader->mBuffers.end(); ++i)
   {
      // add our buffer descriptions to the full const buffer.
      this->addBuffer(i->value);
   }

   mWasLost = true;
}

GFXGLShader::GFXGLShader(GFXGLDevice* device) :
   mVertexShader(0),
   mPixelShader(0),
   mGeometryShader(0),
   mProgram(0),
   mDevice(device),
   mGlobalConstBuffer(NULL)
{
}

GFXGLShader::~GFXGLShader()
{
   clearShaders();
   for (auto& pair : mHandles) {
      if (pair.value != nullptr) {
         delete pair.value;
         pair.value = nullptr;
      }
   }
   mHandles.clear();

   if (mGlobalConstBuffer)
      delete[] mGlobalConstBuffer;
}

void GFXGLShader::clearShaders()
{
   glDeleteProgram(mProgram);
   glDeleteShader(mVertexShader);
   glDeleteShader(mPixelShader);
   glDeleteShader(mGeometryShader);

   mProgram = 0;
   mVertexShader = 0;
   mPixelShader = 0;
   mGeometryShader = 0;
}

bool GFXGLShader::_init()
{
   PROFILE_SCOPE(GFXGLShader_Init);
   // Don't initialize empty shaders.
   if (mVertexFile.isEmpty() && mPixelFile.isEmpty())
      return false;

   clearShaders();

   mProgram = glCreateProgram();

   // Set the macros and add the global ones.
   Vector<GFXShaderMacro> macros;
   macros.merge(mMacros);
   macros.merge(smGlobalMacros);

   macros.increment();
   macros.last().name = "TORQUE_SM";
   macros.last().value = 40;
   macros.increment();
   macros.last().name = "TORQUE_VERTEX_SHADER";
   macros.last().value = "";

   // Default to true so we're "successful" if a vertex/pixel shader wasn't specified.
   bool compiledVertexShader = true;
   bool compiledPixelShader = true;
   bool compiledGeometryShader = true;

   // Compile the vertex and pixel shaders if specified.
   if (!mVertexFile.isEmpty())
   {
      compiledVertexShader = initShader(mVertexFile, GFXShaderStage::VERTEX_SHADER, macros);
      if (!compiledVertexShader)
         return false;
   }

   if (!mPixelFile.isEmpty())
   {
      macros.last().name = "TORQUE_PIXEL_SHADER";
      compiledPixelShader = initShader(mPixelFile, GFXShaderStage::PIXEL_SHADER, macros);
      if (!compiledPixelShader)
         return false;
   }

   if (!mGeometryFile.isEmpty())
   {
      macros.last().name = "TORQUE_GEOMETRY_SHADER";
      compiledGeometryShader = initShader(mGeometryFile, GFXShaderStage::GEOMETRY_SHADER, macros);
      if (!compiledGeometryShader)
         return false;
   }

   // Link it!
   glLinkProgram(mProgram);

   GLint activeAttribs = 0;
   glGetProgramiv(mProgram, GL_ACTIVE_ATTRIBUTES, &activeAttribs);

   GLint maxLength;
   glGetProgramiv(mProgram, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);

   FrameTemp<GLchar> tempData(maxLength + 1);
   *tempData.address() = '\0';
   // Check atributes
   for (U32 i = 0; i < activeAttribs; i++)
   {
      GLint size;
      GLenum type;

      glGetActiveAttrib(mProgram, i, maxLength + 1, NULL, &size, &type, tempData.address());

      StringTableEntry argName = StringTable->insert(tempData.address());

      CHECK_AARG(Torque::GL_VertexAttrib_Position, vPosition);
      CHECK_AARG(Torque::GL_VertexAttrib_Normal, vNormal);
      CHECK_AARG(Torque::GL_VertexAttrib_Color, vColor);
      CHECK_AARG(Torque::GL_VertexAttrib_Tangent, vTangent);
      CHECK_AARG(Torque::GL_VertexAttrib_TangentW, vTangentW);
      CHECK_AARG(Torque::GL_VertexAttrib_Binormal, vBinormal);
      CHECK_AARG(Torque::GL_VertexAttrib_TexCoord0, vTexCoord0);
      CHECK_AARG(Torque::GL_VertexAttrib_TexCoord1, vTexCoord1);
      CHECK_AARG(Torque::GL_VertexAttrib_TexCoord2, vTexCoord2);
      CHECK_AARG(Torque::GL_VertexAttrib_TexCoord3, vTexCoord3);
      CHECK_AARG(Torque::GL_VertexAttrib_TexCoord4, vTexCoord4);
      CHECK_AARG(Torque::GL_VertexAttrib_TexCoord5, vTexCoord5);
      CHECK_AARG(Torque::GL_VertexAttrib_TexCoord6, vTexCoord6);
      CHECK_AARG(Torque::GL_VertexAttrib_TexCoord7, vTexCoord7);
      CHECK_AARG(Torque::GL_VertexAttrib_TexCoord8, vTexCoord8);
      CHECK_AARG(Torque::GL_VertexAttrib_TexCoord9, vTexCoord9);
   }

   //always have OUT_col
   glBindFragDataLocation(mProgram, 0, "OUT_col");
   // Check OUT_colN
   for (U32 i = 1; i < 4; i++)
   {
      char buffer[10];
      dSprintf(buffer, sizeof(buffer), "OUT_col%u", i);
      GLint location = glGetFragDataLocation(mProgram, buffer);
      if (location > 0)
         glBindFragDataLocation(mProgram, i, buffer);

   }

   // Link it again!
   glLinkProgram(mProgram);

   GLint linkStatus;
   glGetProgramiv(mProgram, GL_LINK_STATUS, &linkStatus);

   // Dump the info log to the console
   U32 logLength = 0;
   glGetProgramiv(mProgram, GL_INFO_LOG_LENGTH, (GLint*)&logLength);
   if (logLength)
   {
      FrameAllocatorMarker fam;
      char* log = (char*)fam.alloc(logLength);
      glGetProgramInfoLog(mProgram, logLength, NULL, log);

      if (linkStatus == GL_FALSE)
      {
         if (smLogErrors)
         {
            Con::errorf("GFXGLShader::init - Error linking shader!");
            Con::errorf("Program %s / %s: %s",
               mVertexFile.getFullPath().c_str(), mPixelFile.getFullPath().c_str(), log);
         }
      }
      else if (smLogWarnings)
      {
         Con::warnf("Program %s / %s: %s",
            mVertexFile.getFullPath().c_str(), mPixelFile.getFullPath().c_str(), log);
      }
   }


   // If we failed to link, bail.
   if (linkStatus == GL_FALSE)
      return false;

   initConstantDescs();
   initHandles();

   // Notify Buffers we might have changed in size.
   // If this was our first init then we won't have any activeBuffers
   // to worry about unnecessarily calling.
   Vector<GFXShaderConstBuffer*>::iterator biter = mActiveBuffers.begin();
   for (; biter != mActiveBuffers.end(); biter++)
      ((GFXGLShaderConstBuffer*)(*biter))->onShaderReload(this);

   return true;
}

void GFXGLShader::initConstantDescs()
{
   // clear our vectors.
   mShaderConsts.clear();

   GLint maxNameLength;
   glGetProgramiv(mProgram, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxNameLength);

   if (!maxNameLength)
      return;
   maxNameLength++;

   FrameTemp<GLchar> uniformName(maxNameLength);

   // parse ubos first and add them to our table, same as in dx
   // this is required so that in the other uniform loop we dont add
   // a uniform that exists in a ubo again.
   GLint numUBOS;
   glGetProgramiv(mProgram, GL_ACTIVE_UNIFORM_BLOCKS, &numUBOS);
   for (U32 i = 0; i < numUBOS; i++) {
      GFXShaderConstDesc desc;
      GLint uboNameLen;
      glGetActiveUniformBlockiv(mProgram, i, GL_UNIFORM_BLOCK_NAME_LENGTH, &uboNameLen);
      if (!uboNameLen)
         return;
      uboNameLen++;

      // get the name of the ubo for getting required data.
      FrameTemp<GLchar> uboName(uboNameLen);
      glGetActiveUniformBlockName(mProgram, i, uboNameLen, NULL, uboName);
      GLint uboBinding;
      glGetActiveUniformBlockiv(mProgram, i, GL_UNIFORM_BLOCK_BINDING, &uboBinding);
      GLint uboSize;
      glGetActiveUniformBlockiv(mProgram, i, GL_UNIFORM_BLOCK_DATA_SIZE, &uboSize);
      GLint numUboUniforms;
      glGetActiveUniformBlockiv(mProgram, i, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &numUboUniforms);
      GLint* indices = new GLint[numUboUniforms];
      glGetActiveUniformBlockiv(mProgram, i, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, indices);

      // fill out ubo desc.
      desc.name = String((char*)uboName);
      desc.bindPoint = uboBinding;
      desc.size = uboSize;
      desc.constType = GFXSCT_ConstBuffer;
      desc.samplerReg = -1;

      mBuffers[desc.name] = desc;

      // loop uniforms in the ubo.
      for (U32 j = 0; j < numUboUniforms; j++)
      {
         GFXShaderConstDesc varDesc;

         GLint uniformIndex = indices[j];
         GLint size;
         GLenum type;
         GLint offset;
         glGetActiveUniformsiv(mProgram, 1, (const GLuint*)&uniformIndex, GL_UNIFORM_OFFSET, &offset);
         glGetActiveUniform(mProgram, uniformIndex, maxNameLength, NULL, &size, &type, uniformName);

         varDesc.name = String((char*)uniformName);
         // remove array brackets.
         varDesc.name = varDesc.name.substr(0, varDesc.name.find('['));
         // Insert $ to match D3D behavior of having a $ prepended to parameters to main.
         varDesc.name.insert(0, '$');
         varDesc.bindPoint = desc.bindPoint; // just set to the buffer bindpoint for uniforms in a ubo.
         varDesc.offset = offset;
         varDesc.arraySize = size;
         varDesc.constType = convertConstType(type);
         varDesc.size = shaderConstTypeSize(varDesc.constType) * size;
         varDesc.samplerReg = -1;

#ifdef OPENGL_DEBUG_SPEW
         Con::printf("Variable Name %s:, offset: %d, size: %d, constantDesc.Elements: %d", varDesc.name.c_str(), varDesc.offset, varDesc.size, varDesc.arraySize);
#endif
         mShaderConsts.push_back(varDesc);
      }
   }

   GLint numUniforms;
   glGetProgramiv(mProgram, GL_ACTIVE_UNIFORMS, &numUniforms);

   for (U32 i = 0; i < numUniforms; i++)
   {
      // skip if this uniform is inside a ubo.
      GLint blk;
      glGetActiveUniformsiv(mProgram, 1, (GLuint*)&i, GL_UNIFORM_BLOCK_INDEX, &blk);
      if (blk != -1)
      {
         continue;
      }

      GLint size;
      GLenum type;
      glGetActiveUniform(mProgram, i, maxNameLength, NULL, &size, &type, uniformName);

      GFXShaderConstDesc desc;
      desc.name = String((char*)uniformName);
      // Remove array brackets from the name
      desc.name = desc.name.substr(0, desc.name.find('['));
      // Insert $ to match D3D behavior of having a $ prepended to parameters to main.
      desc.name.insert(0, '$');

      desc.bindPoint = -1;
      desc.arraySize = size;
      desc.constType = convertConstType(type);
      desc.size = shaderConstTypeSize(desc.constType) * size;
      desc.samplerReg = -1;
      mShaderConsts.push_back(desc);
   }
}

GFXShaderConstType GFXGLShader::convertConstType(GLenum constType)
{
   switch (constType)
   {
   case GL_FLOAT:
      return GFXSCT_Float;
      break;
   case GL_FLOAT_VEC2:
      return GFXSCT_Float2;
      break;
   case GL_FLOAT_VEC3:
      return GFXSCT_Float3;
      break;
   case GL_FLOAT_VEC4:
      return GFXSCT_Float4;
      break;
   case GL_INT:
      return GFXSCT_Int;
      break;
   case GL_INT_VEC2:
      return GFXSCT_Int2;
      break;
   case GL_INT_VEC3:
      return GFXSCT_Int3;
      break;
   case GL_INT_VEC4:
      return GFXSCT_Int4;
      break;
   case GL_UNSIGNED_INT:
      return GFXSCT_UInt;
      break;
   case GL_UNSIGNED_INT_VEC2:
      return GFXSCT_UInt2;
      break;
   case GL_UNSIGNED_INT_VEC3:
      return GFXSCT_UInt3;
      break;
   case GL_UNSIGNED_INT_VEC4:
      return GFXSCT_UInt4;
      break;
   case GL_BOOL:
      return GFXSCT_Bool;
      break;
   case GL_BOOL_VEC2:
      return GFXSCT_Bool2;
      break;
   case GL_BOOL_VEC3:
      return GFXSCT_Bool3;
      break;
   case GL_BOOL_VEC4:
      return GFXSCT_Bool4;
      break;
   case GL_FLOAT_MAT2:
      return GFXSCT_Float2x2;
      break;
   case GL_FLOAT_MAT3:
      return GFXSCT_Float3x3;
      break;
   case GL_FLOAT_MAT4:
      return GFXSCT_Float4x4;
      break;
   case GL_FLOAT_MAT4x3: // jamesu - columns, rows
      return GFXSCT_Float4x3;
      break;
   case GL_SAMPLER_1D:
   case GL_SAMPLER_2D:
   case GL_SAMPLER_3D:
   case GL_SAMPLER_1D_SHADOW:
   case GL_SAMPLER_2D_SHADOW:
      return GFXSCT_Sampler;
      break;
   case GL_SAMPLER_CUBE:
      return GFXSCT_SamplerCube;
      break;
   case GL_SAMPLER_CUBE_MAP_ARRAY_ARB:
      return GFXSCT_SamplerCubeArray;
      break;
   case GL_SAMPLER_2D_ARRAY:
      return GFXSCT_SamplerTextureArray;
      break;
   default:
      AssertFatal(false, "Unknown shader constant class enum, maybe you could add it?");
      // If we don't recognize the constant don't add its description.
      break;
   }

   return GFXSCT_Uknown;
}

void GFXGLShader::initHandles()
{
   // Mark all existing handles as invalid.
   // Those that are found when parsing the descriptions will then be marked valid again.
   for (HandleMap::Iterator iter = mHandles.begin(); iter != mHandles.end(); ++iter)
      (iter->value)->setValid(false);

   // Loop through constants that exist in ubos.
   for (U32 i = 0; i < mShaderConsts.size(); i++)
   {
      GFXShaderConstDesc& desc = mShaderConsts[i];

      // Index element 1 of the name to skip the '$' we inserted earier.
      GLint loc = glGetUniformLocation(mProgram, &desc.name.c_str()[1]);

      AssertFatal(loc != -1, avar("uniform %s in shader file Vert: (%s) Frag: (%s)", &desc.name.c_str()[1], mVertexFile.getFullPath().c_str(), mPixelFile.getFullPath().c_str()));

      HandleMap::Iterator handle = mHandles.find(desc.name);
      S32 sampler = -1;
      if (desc.constType == GFXSCT_Sampler ||
         desc.constType == GFXSCT_SamplerCube ||
         desc.constType == GFXSCT_SamplerCubeArray ||
         desc.constType == GFXSCT_SamplerTextureArray)
      {
         S32 idx = mSamplerNamesOrdered.find_next(desc.name);
         AssertFatal(idx != -1, "");
         sampler = idx; //assignedSamplerNum++;
         desc.samplerReg = idx;
      }

      if (handle != mHandles.end())
      {
         if (desc.bindPoint == -1)
         {
            desc.bindPoint = loc;
            mHandles[desc.name]->mUBOUniform = false;
         }
         else
         {
            mHandles[desc.name]->mUBOUniform = true;
         }

         handle->value->reinit(desc);
      }
      else
      {
         if (desc.bindPoint == -1)
         {
            desc.bindPoint = loc;
            mHandles[desc.name] = new GFXGLShaderConstHandle(this, desc);
            mHandles[desc.name]->mUBOUniform = false;
         }
         else
         {
            mHandles[desc.name] = new GFXGLShaderConstHandle(this, desc);
            mHandles[desc.name]->mUBOUniform = true;
         }
      }
   }


   // we have a global const buffer, set it up and add it.
   U32 constBufferSize = 0;

   if (mGlobalConstBuffer)
      delete[] mGlobalConstBuffer;

   for (HandleMap::Iterator iter = mHandles.begin(); iter != mHandles.end(); ++iter)
   {
      GFXGLShaderConstHandle* handle = iter->value;
      if (handle->isValid() && !handle->mUBOUniform)
      {
         handle->mDesc.offset = constBufferSize;
         constBufferSize += handle->getSize();
      }
   }

   if (constBufferSize > 0)
   {
      GFXShaderConstDesc desc;
      // fill out ubo desc.
      desc.name = "Global";
      desc.bindPoint = -1;
      desc.size = constBufferSize;
      desc.constType = GFXSCT_ConstBuffer;
      desc.samplerReg = -1;

      mBuffers[desc.name] = desc;

      mGlobalConstBuffer = new U8[constBufferSize];
      dMemset(mGlobalConstBuffer, 0, constBufferSize);
   }

   // Set our program so uniforms are assigned properly.
   mDevice->setShader(this, false);

   // Iterate through uniforms to set sampler numbers.
   for (HandleMap::Iterator iter = mHandles.begin(); iter != mHandles.end(); ++iter)
   {
      GFXGLShaderConstHandle* handle = iter->value;
      if (handle->isValid() &&
         (handle->getType() == GFXSCT_Sampler ||
            handle->getType() == GFXSCT_SamplerCube ||
            handle->getType() == GFXSCT_SamplerCubeArray ||
            handle->getType() == GFXSCT_SamplerTextureArray))
      {
         // Set sampler number on our program.
         glUniform1i(handle->mDesc.bindPoint, handle->mDesc.samplerReg);
         // Set sampler in constant buffer so it does not get unset later.
         dMemcpy(mGlobalConstBuffer + handle->mDesc.offset, &handle->mDesc.samplerReg, handle->getSize());
      }
   }

   //instancing
   if (!mInstancingFormat)
      return;

   U32 offset = 0;

   for (U32 i = 0; i < mInstancingFormat->getElementCount(); i++)
   {
      const GFXVertexElement& element = mInstancingFormat->getElement(i);

      String constName = String::ToString("$%s", element.getSemantic().c_str());

      HandleMap::Iterator handle = mHandles.find(constName);
      if (handle != mHandles.end())
      {
         AssertFatal(0, "");
      }
      else
      {
         GFXShaderConstDesc desc;
         desc.name = constName;
         desc.arraySize = 1;
         switch (element.getType())
         {
         case GFXDeclType_Float4:
            desc.constType = GFXSCT_Float4;
            break;

         default:
            desc.constType = GFXSCT_Float;
            break;
         }

         GFXGLShaderConstHandle* h = new GFXGLShaderConstHandle(this, desc);
         h->mInstancingConstant = true;
         h->mDesc.offset = offset;
         h->mUBOUniform = false;
         mHandles[constName] = h;

         offset += element.getSizeInBytes();
         ++i;

         // If this is a matrix we will have 2 or 3 more of these
         // semantics with the same name after it.
         for (; i < mInstancingFormat->getElementCount(); i++)
         {
            const GFXVertexElement& nextElement = mInstancingFormat->getElement(i);
            if (nextElement.getSemantic() != element.getSemantic())
            {
               i--;
               break;
            }
            ++desc.arraySize;
            if (desc.arraySize == 4 && desc.constType == GFXSCT_Float4)
            {
               desc.arraySize = 1;
               desc.constType = GFXSCT_Float4x4;
            }
            offset += nextElement.getSizeInBytes();
         }
      }

   }
}

GFXShaderConstHandle* GFXGLShader::getShaderConstHandle(const String& name)
{
   HandleMap::Iterator i = mHandles.find(name);
   if (i != mHandles.end())
      return i->value;
   else
   {
      GFXGLShaderConstHandle* handle = new GFXGLShaderConstHandle(this);
      handle->setValid(false);
      mHandles[name] = handle;

      return handle;
   }
}

GFXShaderConstHandle* GFXGLShader::findShaderConstHandle(const String& name)
{
   HandleMap::Iterator i = mHandles.find(name);
   if (i != mHandles.end())
      return i->value;
   else
   {
      return NULL;
   }
}

void GFXGLShader::setConstantsFromBuffer(U8* buffer)
{
   for (HandleMap::Iterator i = mHandles.begin(); i != mHandles.end(); ++i)
   {
      GFXGLShaderConstHandle* handle = i->value;
      AssertFatal(handle, "GFXGLShader::setConstantsFromBuffer - Null handle");
      // skip ubo uniforms.
      if (handle->mUBOUniform || !handle->isValid())
         continue;

      if (handle->mInstancingConstant)
         continue;

      // Don't set if the value has not be changed.
      if (dMemcmp(mGlobalConstBuffer + handle->mDesc.offset, buffer + handle->mDesc.offset, handle->getSize()) == 0)
         continue;

      // Copy new value into our const buffer and set in GL.
      dMemcpy(mGlobalConstBuffer + handle->mDesc.offset, buffer + handle->mDesc.offset, handle->getSize());

      switch (handle->mDesc.constType)
      {
      case GFXSCT_Float:
         glUniform1fv(handle->mDesc.bindPoint, handle->mDesc.arraySize, (GLfloat*)(mGlobalConstBuffer + handle->mDesc.offset));
         break;
      case GFXSCT_Float2:
         glUniform2fv(handle->mDesc.bindPoint, handle->mDesc.arraySize, (GLfloat*)(mGlobalConstBuffer + handle->mDesc.offset));
         break;
      case GFXSCT_Float3:
         glUniform3fv(handle->mDesc.bindPoint, handle->mDesc.arraySize, (GLfloat*)(mGlobalConstBuffer + handle->mDesc.offset));
         break;
      case GFXSCT_Float4:
         glUniform4fv(handle->mDesc.bindPoint, handle->mDesc.arraySize, (GLfloat*)(mGlobalConstBuffer + handle->mDesc.offset));
         break;
      case GFXSCT_Sampler:
      case GFXSCT_SamplerCube:
      case GFXSCT_SamplerCubeArray:
      case GFXSCT_SamplerTextureArray:
         // Set sampler number on our program.
         glUniform1i(handle->mDesc.bindPoint, handle->mDesc.samplerReg);
         break;
      case GFXSCT_Int:
         glUniform1iv(handle->mDesc.bindPoint, handle->mDesc.arraySize, (GLint*)(mGlobalConstBuffer + handle->mDesc.offset));
         break;
      case GFXSCT_Int2:
         glUniform2iv(handle->mDesc.bindPoint, handle->mDesc.arraySize, (GLint*)(mGlobalConstBuffer + handle->mDesc.offset));
         break;
      case GFXSCT_Int3:
         glUniform3iv(handle->mDesc.bindPoint, handle->mDesc.arraySize, (GLint*)(mGlobalConstBuffer + handle->mDesc.offset));
         break;
      case GFXSCT_Int4:
         glUniform4iv(handle->mDesc.bindPoint, handle->mDesc.arraySize, (GLint*)(mGlobalConstBuffer + handle->mDesc.offset));
         break;
      case GFXSCT_Float2x2:
         glUniformMatrix2fv(handle->mDesc.bindPoint, handle->mDesc.arraySize, true, (GLfloat*)(mGlobalConstBuffer + handle->mDesc.offset));
         break;
      case GFXSCT_Float3x3:
         glUniformMatrix3fv(handle->mDesc.bindPoint, handle->mDesc.arraySize, true, (GLfloat*)(mGlobalConstBuffer + handle->mDesc.offset));
         break;
      case GFXSCT_Float4x3:
         // NOTE: To save a transpose here we could store the matrix transposed (i.e. column major) in the constant buffer.
         // See _mesa_uniform_matrix in the mesa source for the correct transpose algorithm for a 4x3 matrix.
         glUniformMatrix4x3fv(handle->mDesc.bindPoint, handle->mDesc.arraySize, true, (GLfloat*)(mGlobalConstBuffer + handle->mDesc.offset));
         break;
      case GFXSCT_Float4x4:
         glUniformMatrix4fv(handle->mDesc.bindPoint, handle->mDesc.arraySize, true, (GLfloat*)(mGlobalConstBuffer + handle->mDesc.offset));
         break;
      default:
         AssertFatal(0, "");
         break;
      }

   }
}

GFXShaderConstBufferRef GFXGLShader::allocConstBuffer()
{
   GFXGLShaderConstBuffer* buffer = new GFXGLShaderConstBuffer(this);
   for (BufferMap::Iterator i = mBuffers.begin(); i != mBuffers.end(); ++i)
   {
      // add our buffer descriptions to the full const buffer.
      buffer->addBuffer(i->value);
   }

   buffer->registerResourceWithDevice(getOwningDevice());
   mActiveBuffers.push_back(buffer);
   return buffer;
}

void GFXGLShader::useProgram()
{
   glUseProgram(mProgram);
}

void GFXGLShader::zombify()
{
   clearShaders();
}

char* GFXGLShader::_handleIncludes(const Torque::Path& path, FileStream* s)
{
   // TODO:  The #line pragma on GLSL takes something called a
   // "source-string-number" which it then never explains.
   //
   // Until i resolve this mystery i disabled this.
   //
   //String linePragma = String::ToString( "#line 1 \r\n");
   //U32 linePragmaLen = linePragma.length();

   U32 shaderLen = s->getStreamSize();
   char* buffer = (char*)dMalloc(shaderLen + 1);
   //dStrncpy( buffer, linePragma.c_str(), linePragmaLen );
   s->read(shaderLen, buffer);
   buffer[shaderLen] = 0;

   char* p = dStrstr(buffer, "#include");
   while (p)
   {
      char* q = p;
      p += 8;
      if (dIsspace(*p))
      {
         U32 n = 0;
         while (dIsspace(*p)) ++p;
         AssertFatal(*p == '"', "Bad #include directive");
         ++p;
         static char includeFile[256];
         while (*p != '"')
         {
            AssertFatal(*p != 0, "Bad #include directive");
            includeFile[n++] = *p++;
            AssertFatal(n < sizeof(includeFile), "#include directive too long");
         }
         ++p;
         includeFile[n] = 0;

         // First try it as a local file.
         Torque::Path includePath = Torque::Path::Join(path.getPath(), '/', includeFile);
         includePath = Torque::Path::CompressPath(includePath);

         FileStream includeStream;

         if (!includeStream.open(includePath, Torque::FS::File::Read))
         {
            // Try again assuming the path is absolute
            // and/or relative.
            includePath = String(includeFile);
            includePath = Torque::Path::CompressPath(includePath);
            if (!includeStream.open(includePath, Torque::FS::File::Read))
            {
               AssertISV(false, avar("failed to open include '%s'.", includePath.getFullPath().c_str()));

               if (smLogErrors)
                  Con::errorf("GFXGLShader::_handleIncludes - Failed to open include '%s'.",
                     includePath.getFullPath().c_str());

               // Fail... don't return the buffer.
               dFree(buffer);
               return NULL;
            }
         }

         char* includedText = _handleIncludes(includePath, &includeStream);

         // If a sub-include fails... cleanup and return.
         if (!includedText)
         {
            dFree(buffer);
            return NULL;
         }

         // TODO: Disabled till this is fixed correctly.
         //
         // Count the number of lines in the file
         // before the include.
         /*
         U32 includeLine = 0;
         {
            char* nl = dStrstr( buffer, "\n" );
            while ( nl )
            {
               includeLine++;
               nl = dStrstr( nl, "\n" );
               if(nl) ++nl;
            }
         }
         */

         String manip(buffer);
         manip.erase(q - buffer, p - q);
         String sItx(includedText);

         // TODO: Disabled till this is fixed correctly.
         //
         // Add a new line pragma to restore the proper
         // file and line number after the include.
         //sItx += String::ToString( "\r\n#line %d \r\n", includeLine );

         dFree(includedText);
         manip.insert(q - buffer, sItx);
         char* manipBuf = dStrdup(manip.c_str());
         p = manipBuf + (q - buffer);
         dFree(buffer);
         buffer = manipBuf;
      }
      p = dStrstr(p, "#include");
   }

   return buffer;
}

bool GFXGLShader::_loadShaderFromStream(GLuint shader,
   const Torque::Path& path,
   FileStream* s,
   const Vector<GFXShaderMacro>& macros)
{
   Vector<char*> buffers;
   Vector<U32> lengths;

   // The GLSL version declaration must go first!
   const char* versionDecl = "#version 330\n";
   buffers.push_back(dStrdup(versionDecl));
   lengths.push_back(dStrlen(versionDecl));

   //Required extensions. These are already checked when creating the GFX adapter, if we make it this far it's supported
   const char* cubeArrayExt = "#extension GL_ARB_texture_cube_map_array : enable\n";
   buffers.push_back(dStrdup(cubeArrayExt));
   lengths.push_back(dStrlen(cubeArrayExt));

   const char* gpuShader5Ext = "#extension GL_ARB_gpu_shader5 : enable\n";
   buffers.push_back(dStrdup(gpuShader5Ext));
   lengths.push_back(dStrlen(gpuShader5Ext));

   const char* newLine = "\r\n";
   buffers.push_back(dStrdup(newLine));
   lengths.push_back(dStrlen(newLine));

   // Now add all the macros.
   for (U32 i = 0; i < macros.size(); i++)
   {
      if (macros[i].name.isEmpty())  // TODO OPENGL
         continue;

      String define = String::ToString("#define %s %s\n", macros[i].name.c_str(), macros[i].value.c_str());
      buffers.push_back(dStrdup(define.c_str()));
      lengths.push_back(define.length());
   }

   // Now finally add the shader source.
   U32 shaderLen = s->getStreamSize();
   char* buffer = _handleIncludes(path, s);
   if (!buffer)
      return false;

   buffers.push_back(buffer);
   lengths.push_back(shaderLen);

   glShaderSource(shader, buffers.size(), (const GLchar**)const_cast<const char**>(buffers.address()), NULL);

#if defined(TORQUE_DEBUG) && defined(TORQUE_DEBUG_GFX)
   FileStream stream;
   if (!stream.open(path.getFullPath() + "_DEBUG", Torque::FS::File::Write))
   {
      AssertISV(false, avar("GFXGLShader::initShader - failed to write debug shader '%s'.", path.getFullPath().c_str()));
   }

   for (int i = 0; i < buffers.size(); ++i)
      stream.writeText(buffers[i]);
#endif

   // Cleanup the shader source buffer.
   for (U32 i = 0; i < buffers.size(); i++)
      dFree(buffers[i]);

   glCompileShader(shader);

   return true;
}

bool GFXGLShader::initShader(const Torque::Path& file,
   GFXShaderStage stage,
   const Vector<GFXShaderMacro>& macros)
{
   PROFILE_SCOPE(GFXGLShader_CompileShader);

   GLuint activeShader = 0;

   switch (stage)
   {
   case VERTEX_SHADER:
      activeShader = glCreateShader(GL_VERTEX_SHADER);
      mVertexShader = activeShader;
      break;
   case PIXEL_SHADER:
      activeShader = glCreateShader(GL_FRAGMENT_SHADER);
      mPixelShader = activeShader;
      break;
   case GEOMETRY_SHADER:
      activeShader = glCreateShader(GL_GEOMETRY_SHADER);
      mGeometryShader = activeShader;
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

   glAttachShader(mProgram, activeShader);

   // Ok it's not in the shader gen manager, so ask Torque for it
   FileStream stream;
   if (!stream.open(file, Torque::FS::File::Read))
   {
      AssertISV(false, avar("GFXGLShader::initShader - failed to open shader '%s'.", file.getFullPath().c_str()));

      if (smLogErrors)
         Con::errorf("GFXGLShader::initShader - Failed to open shader file '%s'.",
            file.getFullPath().c_str());

      return false;
   }

   if (!_loadShaderFromStream(activeShader, file, &stream, macros))
   {
      if (smLogErrors)
         Con::errorf("GFXGLShader::initShader - unable to load shader from stream: '%s'.", file.getFullPath().c_str());
      return false;
   }
   GLint compile;
   glGetShaderiv(activeShader, GL_COMPILE_STATUS, &compile);

   // Dump the info log to the console
   U32 logLength = 0;
   glGetShaderiv(activeShader, GL_INFO_LOG_LENGTH, (GLint*)&logLength);

   if (logLength)
   {
      FrameAllocatorMarker fam;
      char* log = (char*)fam.alloc(logLength);
      glGetShaderInfoLog(activeShader, logLength, NULL, log);

      if (compile == GL_FALSE)
      {
         if (smLogErrors)
         {
            Con::errorf("GFXGLShader::initShader - Error compiling shader!");
            Con::errorf("Program %s: %s", file.getFullPath().c_str(), log);
         }
      }
      else if (smLogWarnings)
         Con::warnf("Program %s: %s", file.getFullPath().c_str(), log);
   }

   return compile != GL_FALSE;
}

/// Returns our list of shader constants, the material can get this and just set the constants it knows about
const Vector<GFXShaderConstDesc>& GFXGLShader::getShaderConstDesc() const
{
   PROFILE_SCOPE(GFXGLShader_GetShaderConstants);
   return mShaderConsts;
}

/// Returns the alignment value for constType
U32 GFXGLShader::getAlignmentValue(const GFXShaderConstType constType) const
{
   // Alignment is the same thing as size for us.
   return shaderConstTypeSize(constType);
}

const String GFXGLShader::describeSelf() const
{
   String ret;
   ret = String::ToString("   Program: %i", mProgram);
   ret += String::ToString("   Vertex Path: %s", mVertexFile.getFullPath().c_str());
   ret += String::ToString("   Pixel Path: %s", mPixelFile.getFullPath().c_str());

   return ret;
}
