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

   bool save(GFXCubemapHandle cubemap, const Torque::Path &path, GFXFormat compressionFormat)
   {
      if (!cubemap.isValid())
      {
         Con::errorf("CubemapSaver: cubemap handle is not valid");
         return false;
      }


      GFXCubemap *pCubemap = cubemap.getPointer();
      const U32 faceSize = pCubemap->getSize();
      const U32 mipLevels = pCubemap->getMipMapLevels();

      GFXFormat targetFmt = pCubemap->getFormat();
      //setup render targets
      GFXTexHandle pTextures[CubeFaces];

      for (U32 face = 0; face < CubeFaces; face++)
      {
         pTextures[face].set(faceSize, faceSize, targetFmt,
            &GFXStaticTextureProfile, avar("%s() - (line %d)", __FUNCTION__, __LINE__),
            mipLevels, GFXTextureManager::AA_MATCH_BACKBUFFER);

         // yep t3d has funky z up, need to change the face order
         GFX->copyResource(pTextures[face], pCubemap, GFXCubemap::zUpFaceIndex(face) );
      }

      GBitmap *pBitmaps[CubeFaces];
      bool error = false;
      const bool compressedFormat = ImageUtil::isCompressedFormat(compressionFormat);
      const bool hasMips = mipLevels > 1 ? true : false;
      for (U32 i = 0; i < CubeFaces; i++)
      {
         pBitmaps[i] = new GBitmap(faceSize, faceSize, hasMips, targetFmt);
         bool result = pTextures[i].copyToBmp(pBitmaps[i]);
         if (!result)
         {
            Con::errorf("CubemapSaver: cubemap number %u failed to copy", i);
            error = true;
         }
      }

      if (!error)
      {
         DDSFile *pDds = DDSFile::createDDSCubemapFileFromGBitmaps(pBitmaps);
         if (pDds)
         {
            // compressed and floating point don't need swizzling
            if (!compressedFormat && targetFmt != GFXFormatR16G16B16A16F)
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

      //cleanup
      for (U32 i = 0; i < CubeFaces; i++)
         SAFE_DELETE(pBitmaps[i]);


      return true;
   }

   bool getBitmaps(GFXCubemapHandle cubemap, GFXFormat compressionFormat, GBitmap* faceBitmaps[6])
   {
      if (!cubemap.isValid())
      {
         Con::errorf("CubemapSaver: cubemap handle is not valid");
         return false;
      }

      return false;
   }
}
