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

static const int KERNEL_SAMPLES = 9;
static const float3 KERNEL[9] = {
	float3( 0.0000, 0.0000, 0.2500),
	float3( 1.0000, 0.0000, 0.1250),
	float3( 0.0000, 1.0000, 0.1250),
	float3(-1.0000, 0.0000, 0.1250),
	float3( 0.0000,-1.0000, 0.1250),
	float3( 0.7070, 0.7070, 0.0625),
	float3( 0.7070,-0.7070, 0.0625),
	float3(-0.7070,-0.7070, 0.0625),
	float3(-0.7070, 0.7070, 0.0625)
};

TORQUE_UNIFORM_SAMPLER2D(nxtTex, 0);
TORQUE_UNIFORM_SAMPLER2D(mipTex, 1);
uniform float filterRadius;
uniform float2 oneOverTargetSize;

float4 main(PFXVertToPix IN) : TORQUE_TARGET0
{
	float4 upSample = float4(0, 0, 0, 0);
	
	[unroll]
	for (int i=0; i<KERNEL_SAMPLES; i++)
	{
		// XY: Sample Offset
		// Z: Sample Weight
		float3 offsetWeight = KERNEL[i];
		float2 offset = offsetWeight.xy * oneOverTargetSize * filterRadius;
		float weight = offsetWeight.z;
		float4 sampleCol = TORQUE_TEX2D(mipTex, IN.uv0 + offset);
		upSample += sampleCol * weight;
	}
	
	upSample = TORQUE_TEX2D(nxtTex, IN.uv0) + upSample;
	upSample.a = saturate(upSample.a);
	
	return upSample;
	
	//float x = filterRadius * oneOverTargetSize.x;
	//float y = filterRadius * oneOverTargetSize.y;
	//
	//float4 a = TORQUE_TEX2D(mipTex, IN.uv0 + float2(-x, y));
	//float4 b = TORQUE_TEX2D(mipTex, IN.uv0 + float2( 0, y));
	//float4 c = TORQUE_TEX2D(mipTex, IN.uv0 + float2( x, y));
	//
	//float4 d = TORQUE_TEX2D(mipTex, IN.uv0 + float2(-x, 0));
	//float4 e = TORQUE_TEX2D(mipTex, IN.uv0 + float2( 0, 0));
	//float4 f = TORQUE_TEX2D(mipTex, IN.uv0 + float2( x, 0));
	//
	//float4 g = TORQUE_TEX2D(mipTex, IN.uv0 + float2(-x,-y));
	//float4 h = TORQUE_TEX2D(mipTex, IN.uv0 + float2( 0,-y));
	//float4 i = TORQUE_TEX2D(mipTex, IN.uv0 + float2( x,-y));
	//
	//float4 upSample = e * 4.0f;
	//upSample += (b+d+f+h) * 2.0f;
	//upSample += (a+c+g+i);
	//upSample *= 1.0f / 16.0f;
	//
	//upSample = TORQUE_TEX2D(nxtTex, IN.uv0) + upSample;
	//upSample.a = saturate(upSample.a);
	
	//return upSample;
}
