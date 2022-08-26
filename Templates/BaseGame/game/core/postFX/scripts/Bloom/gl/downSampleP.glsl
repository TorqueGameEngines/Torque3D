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

#include "core/rendering/shaders/gl/hlslCompat.glsl"
#include "shadergen:/autogenConditioners.h"

#define KERNEL_SAMPLES 9
const float3 KERNEL[9] = float3[](
	float3( 0.0000, 0.0000, 0.2500),
	float3( 1.0000, 0.0000, 0.1250),
	float3( 0.0000, 1.0000, 0.1250),
	float3(-1.0000, 0.0000, 0.1250),
	float3( 0.0000,-1.0000, 0.1250),
	float3( 1.0000, 1.0000, 0.0625),
	float3( 1.0000,-1.0000, 0.0625),
	float3(-1.0000,-1.0000, 0.0625),
	float3(-1.0000, 1.0000, 0.0625)
);

uniform sampler2D inputTex;
uniform float2 oneOverTargetSize;

in float2 uv0;

out float4 OUT_col;
 
void main()
{
	float4 downSample = float4(0, 0, 0, 0);
	
	for (int i=0; i<KERNEL_SAMPLES; i++)
	{
		// XY: Sample Offset
		// Z: Sample Weight
		float3 offsetWeight = KERNEL[i];
		float2 offsetXY = offsetWeight.xy * oneOverTargetSize;
		float weight = offsetWeight.z;
		float4 sampleCol = tex2D(inputTex, uv0 + offsetXY);
		downSample += sampleCol * weight;
	}
	
	OUT_col = downSample;
}