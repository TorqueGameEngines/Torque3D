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
#include "core/rendering/shaders/shaderModel.hlsl"

#include "SMAA_Params.hlsl"


TORQUE_UNIFORM_SAMPLER2D(edgesTex, 0);
TORQUE_UNIFORM_SAMPLER2D(areaTex, 1);
TORQUE_UNIFORM_SAMPLER2D(searchTex, 2);


struct v_Blend
{
   float4 hpos       : TORQUE_POSITION;
   float2 uv0        : TEXCOORD0;
   float2 pixcoord   : TEXCOORD1;
   float4 offset[3]  : TEXCOORD2;
};


float4 main( v_Blend IN ) : TORQUE_TARGET0
{   

  return SMAABlendingWeightCalculationPS(IN.uv0, IN.pixcoord, IN.offset, texture_edgesTex, texture_areaTex, texture_searchTex, float4(0,0,0,0));
  
} 

