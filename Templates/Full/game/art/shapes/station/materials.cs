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

new Material(Structure_wall)
{
   mapTo = "building01walls";
   diffuseMap[0] = "art/shapes/station/building01walls";
   normalMap[0] = "art/shapes/station/building01walls_n.dds";
   specularMap[0] = "art/shapes/station/building01walls_c.dds";
   effectColor[0] = "InvisibleBlack";
   materialTag0 = "Miscellaneous";
   pixelSpecular0 = "0";
   //emissive[0] = true;
};


new Material(Structure_plate)
{
   mapTo = "plate";
   diffuseMap[0] = "art/shapes/station/plate";
   normalMap[0] = "art/shapes/station/plate_n.dds";
   specularMap[0] = "art/shapes/station/plate_c.dds";
   pixelSpecular0 = "0";
   materialTag0 = "Miscellaneous";
   //emissive[0] = true;
};


new Material(Structure_grid)
{
   mapTo = "grid";
   diffuseMap[0] = "art/shapes/station/grid";
   normalMap[0] = "art/shapes/station/grid_n.dds";
   specularMap[0] = "art/shapes/station/grid_c.dds";
   //emissive[0] = true;
};

