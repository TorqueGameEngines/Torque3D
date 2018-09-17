#pragma once

namespace IBLUtilities
{
   void GenerateIrradianceMap(GFXTextureTargetRef renderTarget, GFXCubemapHandle cubemap, GFXCubemapHandle &cubemapOut);

   void GeneratePrefilterMap(GFXTextureTargetRef renderTarget, GFXCubemapHandle cubemap, U32 mipLevels, GFXCubemapHandle &cubemapOut);

   void GenerateBRDFTexture(GFXTexHandle &textureOut);

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