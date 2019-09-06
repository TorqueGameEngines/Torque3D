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
// Dependencies:
#include "../../../../core/rendering/shaders/lighting.hlsl"
#include "../../../../core/rendering/shaders/torque.hlsl"


struct VertData
{
   float3 position        : POSITION;
   float3 normal     : NORMAL;
   float3 binormal   : BINORMAL;
   float3 tangent    : TANGENT;
   float2 uv0        : TEXCOORD0;
};


struct ConnectData
{
   float4 hpos            : SV_Position;
   float2 out_texCoord    : TEXCOORD0;
   float3 outWsPosition   : TEXCOORD1;
};


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
ConnectData main( VertData IN,
                  uniform float4x4 modelview       : register(C0),
                  uniform float4x4 worldToObj      : register(C4),
                  uniform float4x4 objTrans        : register(C8)
)
{
   ConnectData OUT;

   // Vert Position
   OUT.hpos = mul(modelview, float4(IN.position.xyz,1));
   
   // Base Texture
   OUT.out_texCoord = (float2)IN.uv0;
   
   // Deferred RT Lighting
   OUT.outWsPosition = mul( objTrans, float4( IN.position.xyz, 1 ) ).xyz;
   
   return OUT;
}
