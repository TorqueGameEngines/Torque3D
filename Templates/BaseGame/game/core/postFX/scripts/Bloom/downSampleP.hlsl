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

#define KERNEL_SAMPLES 9
static const float3 KERNEL[9] = {
  float3( 0.0000f, 0.0000f, 0.2500f),
  float3( 1.0000f, 0.0000f, 0.1250f),
  float3( 0.0000f, 1.0000f, 0.1250f),
  float3(-1.0000f, 0.0000f, 0.1250f),
  float3( 0.0000f,-1.0000f, 0.1250f),
  float3( 1.0000f, 1.0000f, 0.0625f),
  float3( 1.0000f,-1.0000f, 0.0625f),
  float3(-1.0000f,-1.0000f, 0.0625f),
  float3(-1.0000f, 1.0000f, 0.0625f)
};

TORQUE_UNIFORM_SAMPLER2D(inputTex, 0);
uniform float2 oneOverTargetSize;
 
float4 main(PFXVertToPix IN) : TORQUE_TARGET0
{
  float4 downSample = float4(0, 0, 0, 0);
  
  [unroll]
  for (int i=0; i<KERNEL_SAMPLES; i++)
  {
    // XY: Sample Offset
    // Z: Sample Weight
    float3 offsetWeight = KERNEL[i];
    float2 offset = offsetWeight.xy * oneOverTargetSize;
    float weight = offsetWeight.z;
    float4 sampleCol = TORQUE_TEX2D(inputTex, IN.uv0 + offset);
    downSample += sampleCol * weight;
  }
  
  return downSample;
}