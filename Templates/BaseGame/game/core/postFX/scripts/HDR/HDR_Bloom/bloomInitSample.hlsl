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
#include "core/rendering/shaders/torque.hlsl"

#define KERNEL_SAMPLES 4
static const float2 KERNEL[4] = {
  float2( 0.5f, 0.5f),
  float2( 0.5f,-0.5f),
  float2(-0.5f,-0.5f),
  float2(-0.5f, 0.5f)
};

TORQUE_UNIFORM_SAMPLER2D(inputTex, 0);
TORQUE_UNIFORM_SAMPLER2D(luminanceTex, 1);
uniform float g_fMiddleGray;
uniform float2 oneOverTargetSize;
 
float4 main(PFXVertToPix IN) : TORQUE_TARGET0
{
   const float weight = 1.0f / KERNEL_SAMPLES;
   float4 downSample = float4(0, 0, 0, 0);
   
   [unroll]
   for (int i=0; i<KERNEL_SAMPLES; i++)
   {
     float2 offset = KERNEL[i] * oneOverTargetSize;
     float4 sampleCol = hdrDecode( TORQUE_TEX2D(inputTex, IN.uv0 + offset) );
     downSample += sampleCol;
   }

   float adaptedLum = TORQUE_TEX2D( luminanceTex, float2( 0.5f, 0.5f ) ).r;
   float lum = (g_fMiddleGray / (adaptedLum + 0.0001f));
   
   return downSample * weight * lum;
}
