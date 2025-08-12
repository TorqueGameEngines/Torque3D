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

#include "core/rendering/shaders/postFX/postFx.hlsl"

TORQUE_UNIFORM_SAMPLER2D(hdrbloomDown, 0);
uniform float filterRadius;
uniform float2 oneOverTargetSize;
uniform int mipCount0;

float4 main(PFXVertToPix IN) : TORQUE_TARGET0
{
  float4 upSample = float4(0, 0, 0, 0);
  float4 finalOut = float4(0, 0, 0, 0);
  for (int mipId = 0; mipId<mipCount0; mipId++)
  {
    float x = filterRadius*oneOverTargetSize.x*pow(0.5, mipId);
    float y = filterRadius*oneOverTargetSize.y*pow(0.5, mipId);
  
    float3 a = TORQUE_TEX2DLOD(hdrbloomDown, float4(IN.uv0.x - x, IN.uv0.y + y, 0, mipId)).rgb;
    float3 b = TORQUE_TEX2DLOD(hdrbloomDown, float4(IN.uv0.x,     IN.uv0.y + y, 0, mipId)).rgb;
    float3 c = TORQUE_TEX2DLOD(hdrbloomDown, float4(IN.uv0.x + x, IN.uv0.y + y, 0, mipId)).rgb;
  
    float3 d = TORQUE_TEX2DLOD(hdrbloomDown, float4(IN.uv0.x - x, IN.uv0.y, 0, mipId)).rgb;
    float3 e = TORQUE_TEX2DLOD(hdrbloomDown, float4(IN.uv0.x,     IN.uv0.y, 0, mipId)).rgb;
    float3 f = TORQUE_TEX2DLOD(hdrbloomDown, float4(IN.uv0.x + x, IN.uv0.y, 0, mipId)).rgb;

    float3 g = TORQUE_TEX2DLOD(hdrbloomDown, float4(IN.uv0.x - x, IN.uv0.y - y, 0, mipId)).rgb;
    float3 h = TORQUE_TEX2DLOD(hdrbloomDown, float4(IN.uv0.x,     IN.uv0.y - y, 0, mipId)).rgb;
    float3 i = TORQUE_TEX2DLOD(hdrbloomDown, float4(IN.uv0.x + x, IN.uv0.y - y, 0, mipId)).rgb;
  
    upSample.rgb = e*4.0;
    upSample.rgb += (b+d+f+h)*2.0;
    upSample.rgb += (a+c+g+i);
    finalOut += upSample;
 } 
 finalOut /= mipCount0;
 finalOut.a = 1.0;
   
  return float4(finalOut.rgb,1);
}
