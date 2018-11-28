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

#ifndef IBL_UTILS_H_
#define IBL_UTILS_H_

#ifndef _GFXTARGET_H_
#include "gfx/gfxTarget.h"
#endif

#ifndef _GFXCUBEMAP_H_
#include "gfx/gfxCubemap.h"
#endif

#ifndef _COLOR_H_
#include "core/color.h"
#endif


namespace IBLUtilities
{
   void GenerateIrradianceMap(GFXTextureTargetRef renderTarget, GFXCubemapHandle cubemap, GFXCubemapHandle &cubemapOut);
   void GenerateAndSaveIrradianceMap(String outputPath, S32 resolution, GFXCubemapHandle cubemap, GFXCubemapHandle &cubemapOut);

   void GeneratePrefilterMap(GFXTextureTargetRef renderTarget, GFXCubemapHandle cubemap, U32 mipLevels, GFXCubemapHandle &cubemapOut);
   void GenerateAndSavePrefilterMap(String outputPath, S32 resolution, GFXCubemapHandle cubemap, U32 mipLevels, GFXCubemapHandle &cubemapOut);

   void SaveCubeMap(String outputPath, GFXCubemapHandle &cubemap);

   void bakeReflection(String outputPath, S32 resolution);

   LinearColorF decodeSH(Point3F normal, const LinearColorF SHTerms[9], const F32 SHConstants[5]);

   MatrixF getSideMatrix(U32 side);

   F32 harmonics(U32 termId, Point3F normal);

   LinearColorF sampleSide(GBitmap* cubeFaceBitmaps[6], const U32& cubemapResolution, const U32& termindex, const U32& sideIndex);

   //
   //SH Calculations
   // From http://sunandblackcat.com/tipFullView.php?l=eng&topicid=32&topic=Spherical-Harmonics-From-Cube-Texture
   // With shader decode logic from https://github.com/nicknikolov/cubemap-sh
   void calculateSHTerms(GFXCubemapHandle cubemap, LinearColorF SHTerms[9], F32 SHConstants[5]);

   F32 texelSolidAngle(F32 aU, F32 aV, U32 width, U32 height);

   F32 areaElement(F32 x, F32 y);
};

#endif