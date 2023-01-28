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
#include "core/postFX/scripts/HDR/HDR_colorUtils.hlsl"

TORQUE_UNIFORM_SAMPLER2D(inputTex, 0);
uniform float2 oneOverTargetSize;
uniform int mipId;
 
float4 main(PFXVertToPix IN) : TORQUE_TARGET0
{
  float4 downSample = float4(0, 0, 0, 0);
  float x = oneOverTargetSize.x;
  float y = oneOverTargetSize.y;
  
  float3 a = TORQUE_TEX2D(inputTex, float2(IN.uv0.x - 2 * x, IN.uv0.y + 2*y)).rgb;
  float3 b = TORQUE_TEX2D(inputTex, float2(IN.uv0.x		   , IN.uv0.y + 2*y)).rgb;
  float3 c = TORQUE_TEX2D(inputTex, float2(IN.uv0.x + 2 * x, IN.uv0.y + 2*y)).rgb;
  
  float3 d = TORQUE_TEX2D(inputTex, float2(IN.uv0.x - 2 * x, IN.uv0.y)).rgb;
  float3 e = TORQUE_TEX2D(inputTex, float2(IN.uv0.x		   , IN.uv0.y)).rgb;
  float3 f = TORQUE_TEX2D(inputTex, float2(IN.uv0.x + 2 * x, IN.uv0.y)).rgb;
  
  float3 g = TORQUE_TEX2D(inputTex, float2(IN.uv0.x - 2 * x, IN.uv0.y - 2*y)).rgb;
  float3 h = TORQUE_TEX2D(inputTex, float2(IN.uv0.x		   , IN.uv0.y - 2*y)).rgb;
  float3 i = TORQUE_TEX2D(inputTex, float2(IN.uv0.x + 2 * x, IN.uv0.y - 2*y)).rgb;
  
  float3 j = TORQUE_TEX2D(inputTex, float2(IN.uv0.x - x, IN.uv0.y + y)).rgb;
  float3 k = TORQUE_TEX2D(inputTex, float2(IN.uv0.x + x, IN.uv0.y + y)).rgb;
  float3 l = TORQUE_TEX2D(inputTex, float2(IN.uv0.x - x, IN.uv0.y - y)).rgb;
  float3 m = TORQUE_TEX2D(inputTex, float2(IN.uv0.x + x, IN.uv0.y - y)).rgb;
  
  float3 group[5];
  switch (mipId)
  {
	case 0:
		group[0] = (a+b+d+e) * (0.125f/4.0f);
		group[1] = (b+c+e+f) * (0.125f/4.0f);
		group[2] = (d+e+g+h) * (0.125f/4.0f);
		group[3] = (e+f+h+i) * (0.125f/4.0f);
		group[4] = (j+k+l+m) * (0.5f/4.0f);
		group[0] *= KarisAverage(group[0]);
		group[1] *= KarisAverage(group[1]);
		group[2] *= KarisAverage(group[2]);
		group[3] *= KarisAverage(group[3]);
		group[4] *= KarisAverage(group[4]);
		downSample.rgb = group[0]+group[1]+group[2]+group[3]+group[4];
		downSample.a = 1.0;
		break;
		
	default:
		downSample.rgb = e*0.125;
		downSample.rgb += (a+c+g+i)*0.03125;
		downSample.rgb += (b+d+f+h)*0.0625;
		downSample.rgb += (j+k+l+m)*0.125;
		downSample.a = 1.0;
		break;
  }
  
  return downSample;
}