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
#include "core/rendering/shaders/torque.hlsl"
#include "SMAA_Params.hlsl"
    
                                                                         
TORQUE_UNIFORM_SAMPLER2D(sceneTex, 0);
TORQUE_UNIFORM_SAMPLER2D(blendTex, 1);

struct v_NHBlend
{
   float4 hpos    : TORQUE_POSITION;
   float2 uv0     : TEXCOORD0;
   float4 offset  : TEXCOORD1;
};

            
float4 main( v_NHBlend IN ) : TORQUE_TARGET0
{   
    //return float4(TORQUE_TEX2D(blendTex, IN.uv0));
   return toLinear(SMAANeighborhoodBlendingPS(IN.uv0, IN.offset, texture_sceneTex, texture_blendTex));
} 

