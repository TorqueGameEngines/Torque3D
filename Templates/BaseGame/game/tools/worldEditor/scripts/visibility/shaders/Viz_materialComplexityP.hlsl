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

#include "../../../../core/rendering/shaders/lighting.hlsl"
#include "../../../../core/rendering/shaders/torque.hlsl"

struct ConnectData
{
   float4 hpos            : SV_Position;
   float2 out_texCoord    : TEXCOORD0;
   float3 outWsPosition   : TEXCOORD1;
};

uniform float materialComplexity;
uniform float minComplexity;
uniform float maxComplexity;


float4 main( ConnectData IN ) : TORQUE_TARGET0
{     
    float complexity = (materialComplexity-minComplexity)/(maxComplexity-minComplexity);

    float3 green = float3(0,1,0);
    float3 yellow = float3(1,1,0);
    float3 red = float3(1,0,0);

    float a = complexity * 2;
    float3 finalColor = lerp (green, yellow, a);
    a -= 1;
    finalColor = lerp (finalColor, red, a);

    return float4(finalColor, 1.0);   
}
