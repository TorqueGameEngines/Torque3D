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

singleton Material(tiled_floor)
{
   mapTo = "tiled_floor";


   diffuseColor[0] = "1 1 1 1";
   specular[0] = "0.9 0.9 0.9 1";
   specularPower[0] = "1";

   doubleSided = false;
   translucent = false;
   showFootprints = "0";
   materialTag0 = "urban";
   pixelSpecular[0] = "0";
   useAnisotropic[0] = "0";
   diffuseMap[0] = "art/shapes/yorks/models/tiled_floor_dds.dds";
   useAnisotropic[1] = "0";
   normalMap[0] = "art/shapes/yorks/models/tiled_floor_alpha_nm.dds";
   translucentBlendOp = "None";
   diffuseColor[1] = "1 1 1 1";
   diffuseColor[2] = "1 1 1 1";
   animFlags[2] = "0x00000010";
   sequenceFramePerSec[2] = "5";
   sequenceSegmentSize[2] = "0.5";
   pixelSpecular[2] = "0";
   specularPower[1] = "1";
   emissive[0] = "0";
   emissive[1] = "0";
   specularMap[0] = "art/shapes/yorks/models/tiled_floor_dds.dds";
   diffuseMap[1] = "art/shapes/yorks/models/tiled_floor_alpha.dds";
   specularMap[1] = "art/shapes/yorks/models/tiled_floor_alpha.dds";
   cubemap = "DesertSkyCubemap";
};

singleton Material(brick_rough)
{
   mapTo = "brick_rough";
   diffuseColor[0] = "1 1 1 1";
   diffuseMap[0] = "art/shapes/yorks/models/brick_rough_red.dds";
   normalMap[0] = "art/shapes/yorks/models/brick_rough_nm.png";
   specular[0] = "0.9 0.9 0.9 1";
   specularPower[0] = "10";
   showFootprints = "0";
   materialTag0 = "urban";
   pixelSpecular[0] = "0";
   useAnisotropic[1] = "0";
   diffuseColor[1] = "1 1 1 1";
   emissive[0] = "0";
   emissive[1] = "0";
   specularMap[0] = "art/shapes/yorks/models/brick_rough_red.dds";
   diffuseMap[1] = "art/shapes/yorks/models/brick_rough_envmap.dds";
   normalMap[1] = "art/shapes/yorks/models/brick_rough_nm.png";
   specularMap[1] = "art/shapes/yorks/models/brick_rough_red.dds";
   cubemap = "DesertSkyCubemap";
};

singleton Material(LMA_area5_basecopper_png)
{
   mapTo = "basecopper_png";
   diffuseMap[0] = "art/shapes/yorks/models/tiled_floor.png";
   specular[0] = "0.5 0.5 0.5 1";
   specularPower[0] = "12.5";
   translucentBlendOp = "None";
};

singleton Material(LMA_area5_panel2a_png)
{
   mapTo = "panel2a_png";
   diffuseMap[0] = "art/shapes/yorks/models/brick_rough.png";
   specular[0] = "0.5 0.5 0.5 1";
   specularPower[0] = "12.5";
   translucentBlendOp = "None";
};

singleton Material(LMA_area5_grate2_png)
{
   mapTo = "grate2_png";
   diffuseMap[0] = "art/shapes/yorks/models/tiled_floor.png";
   specular[0] = "0.5 0.5 0.5 1";
   specularPower[0] = "12.5";
   translucentBlendOp = "None";
};

singleton Material(LMA_area5_grate1_png)
{
   mapTo = "grate1_png";
   diffuseMap[0] = "art/shapes/yorks/models/brick_rough.png";
   specular[0] = "0.5 0.5 0.5 1";
   specularPower[0] = "12.5";
   translucentBlendOp = "None";
};

singleton Material(LMA_area5_panel1b_png)
{
   mapTo = "panel1b_png";
   diffuseMap[0] = "art/shapes/yorks/models/tiled_floor.png";
   specular[0] = "0.5 0.5 0.5 1";
   specularPower[0] = "12.5";
   translucentBlendOp = "None";
};

singleton Material(LMA_area5_sign_directs_png)
{
   mapTo = "sign_directs_png";
   diffuseMap[0] = "art/shapes/yorks/models/brick_rough.png";
   specular[0] = "0.5 0.5 0.5 1";
   specularPower[0] = "12.5";
   translucentBlendOp = "None";
};

singleton Material(LMA_area5_panel1a_png)
{
   mapTo = "panel1a_png";
   diffuseMap[0] = "art/shapes/yorks/models/brick_rough.png";
   specular[0] = "0.5 0.5 0.5 1";
   specularPower[0] = "12.5";
   translucentBlendOp = "None";
};

singleton Material(LMA_area5_panel2_png)
{
   mapTo = "panel2_png";
   diffuseMap[0] = "art/shapes/yorks/models/tiled_floor.png";
   specular[0] = "0.5 0.5 0.5 1";
   specularPower[0] = "12.5";
   translucentBlendOp = "None";
};

singleton Material(LMA_area5_panel1_png)
{
   mapTo = "panel1_png";
   diffuseMap[0] = "art/shapes/yorks/models/brick_rough.png";
   specular[0] = "0.5 0.5 0.5 1";
   specularPower[0] = "12.5";
   translucentBlendOp = "None";
};

singleton Material(LMA_area5_tile1blue_png)
{
   mapTo = "tile1blue_png";
   diffuseMap[0] = "art/shapes/yorks/models/tiled_floor.png";
   specular[0] = "0.5 0.5 0.5 1";
   specularPower[0] = "12.5";
   translucentBlendOp = "None";
};

singleton Material(LMA_area5_tile1_afb_png)
{
   mapTo = "tile1_afb_png";
   diffuseMap[0] = "art/shapes/yorks/models/tiled_floor.png";
   specular[0] = "0.996078 0.996078 0.996078 1";
   specularPower[0] = "12.5";
   translucentBlendOp = "None";
   normalMap[0] = "art/shapes/yorks/models/tiled_floor_nm.png";
   specularMap[0] = "art/shapes/yorks/models/tiled_floor_alpha.dds";
   materialTag0 = "Miscellaneous";
   cubemap = "DesertSkyCubemap";
};

singleton Material(LMA_area5_tilelong1_png)
{
   mapTo = "tilelong1_png";
   diffuseMap[0] = "art/shapes/yorks/models/brick_rough.png";
   specular[0] = "0.5 0.5 0.5 1";
   specularPower[0] = "12.5";
   translucentBlendOp = "None";
};

singleton Material(LMA_area5_panel2b_png)
{
   mapTo = "panel2b_png";
   diffuseMap[0] = "art/shapes/yorks/models/brick_rough.png";
   specular[0] = "0.5 0.5 0.5 1";
   specularPower[0] = "12.5";
   translucentBlendOp = "None";
};

singleton Material(LMA_area5_tile1green_png)
{
   mapTo = "tile1green_png";
   diffuseMap[0] = "art/shapes/yorks/models/tiled_floor.png";
   specular[0] = "0.5 0.5 0.5 1";
   specularPower[0] = "12.5";
   translucentBlendOp = "None";
};

singleton Material(LMA_area5_airlockplus_png)
{
   mapTo = "airlockplus_png";
   diffuseMap[0] = "art/shapes/yorks/models/tiled_floor.png";
   specular[0] = "0.5 0.5 0.5 1";
   specularPower[0] = "12.5";
   translucentBlendOp = "None";
};
