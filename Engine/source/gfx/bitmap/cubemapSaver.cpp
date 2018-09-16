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

#include "gfx/bitmap/cubemapSaver.h"
#include "platform/platform.h"
#include "gfx/bitmap/ddsFile.h"
#include "gfx/bitmap/imageUtils.h"
#include "gfx/gfxDevice.h"
#include "gfx/gfxTransformSaver.h"
#include "gfx/gfxTextureManager.h"
#include "materials/shaderData.h"
#include "core/stream/fileStream.h"
#include "math/mathUtils.h"
#include "math/mTransform.h"


namespace CubemapSaver
{
   const U32 CubeFaces = 6;

   void _setConstBuffer(GFXShaderConstHandle* handle, GFXShaderConstBuffer *cbuf, const VectorF &vLookatPt, const VectorF &vUpVec)
   {
      VectorF cross = mCross(vUpVec, vLookatPt);
      cross.normalizeSafe();

      MatrixF matView(true);
      matView.setColumn(0, cross);
      matView.setColumn(1, vLookatPt);
      matView.setColumn(2, vUpVec);
      matView.setPosition(VectorF(0.0f, 0.0f, 1.0f));
      matView.inverse();

      if (handle->isValid())
         cbuf->set(handle, matView);
      else
         Con::errorf("CubemapSaver: Failed to set a shader constant handle.");
   }

   bool save(GFXCubemapHandle cubemap, const Torque::Path &path, GFXFormat compressionFormat)
   {
      if (!cubemap.isValid())
      {
         Con::errorf("CubemapSaver: cubemap handle is not valid");
         return false;
      }

      // This can sometimes occur outside a begin/end scene.
      const bool sceneBegun = GFX->canCurrentlyRender();
      if (!sceneBegun)
         GFX->beginScene();

      GFXCubemap *pCubemap = cubemap.getPointer();
      U32 faceSize = pCubemap->getSize();

      ShaderData *shaderData = nullptr;
      GFXShaderRef shader = Sim::findObject("CubemapSaveShader", shaderData) ? shaderData->getShader() : nullptr;
      if (!shader)
      {
         Con::errorf("CubemapSaver::save - could not find CubemapSaveShader");
         return false;
      }

      GFXShaderConstHandle *matHandles[CubeFaces];

      matHandles[0] = shader->getShaderConstHandle("$matrix0");
      matHandles[1] = shader->getShaderConstHandle("$matrix1");
      matHandles[2] = shader->getShaderConstHandle("$matrix2");
      matHandles[3] = shader->getShaderConstHandle("$matrix3");
      matHandles[4] = shader->getShaderConstHandle("$matrix4");
      matHandles[5] = shader->getShaderConstHandle("$matrix5");

      GFXShaderConstBufferRef cbuffer = shader->allocConstBuffer();

      GFXTextureTarget *pTarget = GFX->allocRenderToTextureTarget();
      GFX->pushActiveRenderTarget();

      GFXFormat renderTargetFmt = GFXFormatR8G8B8A8;
      //setup render targets
      GFXTexHandle pTextures[CubeFaces];
      for (U32 i = 0; i < CubeFaces; i++)
      {
         pTextures[i].set(faceSize, faceSize, renderTargetFmt,
            &GFXRenderTargetProfile, avar("%s() - (line %d)", __FUNCTION__, __LINE__),
            1, GFXTextureManager::AA_MATCH_BACKBUFFER);

         pTarget->attachTexture(GFXTextureTarget::RenderSlot(GFXTextureTarget::Color0 + i), pTextures[i]);
      }

      //create stateblock
      GFXStateBlockDesc desc;
      desc.setZReadWrite(false, false);
      desc.samplersDefined = true;
      desc.samplers[0].addressModeU = GFXAddressClamp;
      desc.samplers[0].addressModeV = GFXAddressClamp;
      desc.samplers[0].addressModeW = GFXAddressClamp;
      desc.samplers[0].magFilter = GFXTextureFilterLinear;
      desc.samplers[0].minFilter = GFXTextureFilterLinear;
      desc.samplers[0].mipFilter = GFXTextureFilterLinear;

      //yep funky order and rotations with t3d z up
      _setConstBuffer(matHandles[0], cbuffer, VectorF(0.0f, 1.0f, 0.0f), VectorF(-1.0f, 0.0f, 0.0f));
      _setConstBuffer(matHandles[1], cbuffer, VectorF(0.0f, 1.0f, 0.0f), VectorF(1.0f, 0.0f, 0.0f));
      _setConstBuffer(matHandles[2], cbuffer, VectorF(0.0f, 1.0f, 0.0f), VectorF(0.0f, 0.0f, -1.0f));
      _setConstBuffer(matHandles[3], cbuffer, VectorF(0.0f, 1.0f, 0.0f), VectorF(0.0f, 0.0f, 1.0f));
      _setConstBuffer(matHandles[4], cbuffer, VectorF(0.0f, 0.0f, -1.0f), VectorF(0.0f, -1.0f, 0.0f));
      _setConstBuffer(matHandles[5], cbuffer, VectorF(0.0f, 0.0f, 1.0f), VectorF(0.0f, 1.0f, 0.0f));

      GFXTransformSaver saver;
      GFX->setActiveRenderTarget(pTarget);
      GFX->clear(GFXClearTarget, ColorI(0, 0, 0, 0), 1.0f, 0);
      GFX->setStateBlockByDesc(desc);
      GFX->setWorldMatrix(MatrixF::Identity);
      GFX->setProjectionMatrix(MatrixF::Identity);
      GFX->setCubeTexture(0, pCubemap);
      GFX->setShaderConstBuffer(cbuffer);
      GFX->setShader(shader);
      GFX->drawPrimitive(GFXTriangleList, 0, 3);
      pTarget->resolve();

      GBitmap *pBitmaps[CubeFaces];
      bool error = false;
      const bool compressedFormat = ImageUtil::isCompressedFormat(compressionFormat);
      for (U32 i = 0; i < CubeFaces; i++)
      {
         pBitmaps[i] = new GBitmap(faceSize, faceSize, false, renderTargetFmt);
         bool result = pTextures[i].copyToBmp(pBitmaps[i]);
         if (!result)
         {
            Con::errorf("CubemapSaver: cubemap number %u failed to copy", i);
            error = true;
         }
         //gen mip maps
         pBitmaps[i]->extrudeMipLevels();
      }

      if (!error)
      {
         DDSFile *pDds = DDSFile::createDDSCubemapFileFromGBitmaps(pBitmaps);
         if (pDds)
         {
            // non compressed format needs swizzling
            if (!compressedFormat)
               ImageUtil::swizzleDDS(pDds, Swizzles::bgra);

            if(compressedFormat)
               ImageUtil::ddsCompress(pDds, compressionFormat);

            FileStream  stream;
            stream.open(path, Torque::FS::File::Write);

            if (stream.getStatus() == Stream::Ok)
               pDds->write(stream);
            else
               Con::errorf("CubemapSaver: failed to open file stream for file %s", path.getFullPath().c_str());

            SAFE_DELETE(pDds);
         }
      }

      for (U32 i = 0; i < CubeFaces; i++)
         SAFE_DELETE(pBitmaps[i]);

      //cleaup
      GFX->popActiveRenderTarget();
      GFX->setTexture(0, NULL);
      GFX->setShader(NULL);
      GFX->setShaderConstBuffer(NULL);
      GFX->setVertexBuffer(NULL);

      // End it if we begun it.
      if (!sceneBegun)
         GFX->endScene();


      return true;
   }

   bool getBitmaps(GFXCubemapHandle cubemap, GFXFormat compressionFormat, GBitmap* faceBitmaps[6])
   {
      if (!cubemap.isValid())
      {
         Con::errorf("CubemapSaver: cubemap handle is not valid");
         return false;
      }

      // This can sometimes occur outside a begin/end scene.
      const bool sceneBegun = GFX->canCurrentlyRender();
      if (!sceneBegun)
         GFX->beginScene();

      GFXCubemap *pCubemap = cubemap.getPointer();
      U32 faceSize = pCubemap->getSize();

      ShaderData *shaderData = nullptr;
      GFXShaderRef shader = Sim::findObject("CubemapSaveShader", shaderData) ? shaderData->getShader() : nullptr;
      if (!shader)
      {
         Con::errorf("CubemapSaver::save - could not find CubemapSaveShader");
         return false;
      }

      GFXShaderConstHandle *matHandles[CubeFaces];

      matHandles[0] = shader->getShaderConstHandle("$matrix0");
      matHandles[1] = shader->getShaderConstHandle("$matrix1");
      matHandles[2] = shader->getShaderConstHandle("$matrix2");
      matHandles[3] = shader->getShaderConstHandle("$matrix3");
      matHandles[4] = shader->getShaderConstHandle("$matrix4");
      matHandles[5] = shader->getShaderConstHandle("$matrix5");

      GFXShaderConstBufferRef cbuffer = shader->allocConstBuffer();

      GFXTextureTarget *pTarget = GFX->allocRenderToTextureTarget();
      GFX->pushActiveRenderTarget();

      GFXFormat renderTargetFmt = GFXFormatR8G8B8A8;
      //setup render targets
      GFXTexHandle pTextures[CubeFaces];
      for (U32 i = 0; i < CubeFaces; i++)
      {
         pTextures[i].set(faceSize, faceSize, renderTargetFmt,
            &GFXRenderTargetProfile, avar("%s() - (line %d)", __FUNCTION__, __LINE__),
            1, GFXTextureManager::AA_MATCH_BACKBUFFER);

         pTarget->attachTexture(GFXTextureTarget::RenderSlot(GFXTextureTarget::Color0 + i), pTextures[i]);
      }

      //create stateblock
      GFXStateBlockDesc desc;
      desc.setZReadWrite(false, false);
      desc.samplersDefined = true;
      desc.samplers[0].addressModeU = GFXAddressClamp;
      desc.samplers[0].addressModeV = GFXAddressClamp;
      desc.samplers[0].addressModeW = GFXAddressClamp;
      desc.samplers[0].magFilter = GFXTextureFilterLinear;
      desc.samplers[0].minFilter = GFXTextureFilterLinear;
      desc.samplers[0].mipFilter = GFXTextureFilterLinear;

      //yep funky order and rotations with t3d z up
      _setConstBuffer(matHandles[0], cbuffer, VectorF(0.0f, 1.0f, 0.0f), VectorF(-1.0f, 0.0f, 0.0f));
      _setConstBuffer(matHandles[1], cbuffer, VectorF(0.0f, 1.0f, 0.0f), VectorF(1.0f, 0.0f, 0.0f));
      _setConstBuffer(matHandles[2], cbuffer, VectorF(0.0f, 1.0f, 0.0f), VectorF(0.0f, 0.0f, -1.0f));
      _setConstBuffer(matHandles[3], cbuffer, VectorF(0.0f, 1.0f, 0.0f), VectorF(0.0f, 0.0f, 1.0f));
      _setConstBuffer(matHandles[4], cbuffer, VectorF(0.0f, 0.0f, -1.0f), VectorF(0.0f, -1.0f, 0.0f));
      _setConstBuffer(matHandles[5], cbuffer, VectorF(0.0f, 0.0f, 1.0f), VectorF(0.0f, 1.0f, 0.0f));

      GFXTransformSaver saver;
      GFX->setActiveRenderTarget(pTarget);
      GFX->clear(GFXClearTarget, ColorI(0, 0, 0, 0), 1.0f, 0);
      GFX->setStateBlockByDesc(desc);
      GFX->setWorldMatrix(MatrixF::Identity);
      GFX->setProjectionMatrix(MatrixF::Identity);
      GFX->setCubeTexture(0, pCubemap);
      GFX->setShaderConstBuffer(cbuffer);
      GFX->setShader(shader);
      GFX->drawPrimitive(GFXTriangleList, 0, 3);
      pTarget->resolve();

      bool error = false;
      const bool compressedFormat = ImageUtil::isCompressedFormat(compressionFormat);
      for (U32 i = 0; i < CubeFaces; i++)
      {
         //faceBitmaps[i] = new GBitmap(faceSize, faceSize, false, renderTargetFmt);
         bool result = pTextures[i].copyToBmp(faceBitmaps[i]);
         if (!result)
         {
            Con::errorf("CubemapSaver: cubemap number %u failed to copy", i);
            error = true;
         }
         //gen mip maps
         faceBitmaps[i]->extrudeMipLevels();
      }

      /*if (!error)
      {
         DDSFile *pDds = DDSFile::createDDSCubemapFileFromGBitmaps(pBitmaps);
         if (pDds)
         {
            // non compressed format needs swizzling
            if (!compressedFormat)
               ImageUtil::swizzleDDS(pDds, Swizzles::bgra);

            if (compressedFormat)
               ImageUtil::ddsCompress(pDds, compressionFormat);

            FileStream  stream;
            stream.open(path, Torque::FS::File::Write);

            if (stream.getStatus() == Stream::Ok)
               pDds->write(stream);
            else
               Con::errorf("CubemapSaver: failed to open file stream for file %s", path.getFullPath().c_str());

            SAFE_DELETE(pDds);
         }
      }

      for (U32 i = 0; i < CubeFaces; i++)
         SAFE_DELETE(pBitmaps[i]);*/

      //cleaup
      GFX->popActiveRenderTarget();
      GFX->setTexture(0, NULL);
      GFX->setShader(NULL);
      GFX->setShaderConstBuffer(NULL);
      GFX->setVertexBuffer(NULL);

      // End it if we begun it.
      if (!sceneBegun)
         GFX->endScene();

      if (error)
         return false;

      return true;
   }
}
