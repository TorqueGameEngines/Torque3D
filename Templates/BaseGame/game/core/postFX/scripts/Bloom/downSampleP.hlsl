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

//-----------------------------------------------------------------------------
// Data 
//-----------------------------------------------------------------------------

TORQUE_UNIFORM_SAMPLER2D(inputTex, 0);
uniform float2 oneOverTargetSize;
 
//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
float4 main(PFXVertToPix IN) : TORQUE_TARGET0
{
	float x = oneOverTargetSize.x;
	float y = oneOverTargetSize.y;
	float4 a = TORQUE_TEX2D(inputTex, IN.uv0 + float2(-x*2.0f, y*2.0f));
	float4 b = TORQUE_TEX2D(inputTex, IN.uv0 + float2( 0.0f  , y*2.0f));
	float4 c = TORQUE_TEX2D(inputTex, IN.uv0 + float2( x*2.0f, y*2.0f));
																	
	float4 d = TORQUE_TEX2D(inputTex, IN.uv0 + float2(-x*2.0f,   0.0f));
	float4 e = TORQUE_TEX2D(inputTex, IN.uv0);
	float4 f = TORQUE_TEX2D(inputTex, IN.uv0 + float2( x*2.0f,   0.0f));
																	
	float4 g = TORQUE_TEX2D(inputTex, IN.uv0 + float2(-x*2.0f,-y*2.0f));
	float4 h = TORQUE_TEX2D(inputTex, IN.uv0 + float2( 0.0f  ,-y*2.0f));
	float4 i = TORQUE_TEX2D(inputTex, IN.uv0 + float2( x*2.0f,-y*2.0f));
																	
	float4 j = TORQUE_TEX2D(inputTex, IN.uv0 + float2(-x, y));
	float4 k = TORQUE_TEX2D(inputTex, IN.uv0 + float2( x, y));
	float4 l = TORQUE_TEX2D(inputTex, IN.uv0 + float2(-x,-y));
	float4 m = TORQUE_TEX2D(inputTex, IN.uv0 + float2( x,-y));
	
	float4 downSample = e * 0.125f;
	downSample += (a+c+g+i) * 0.03125f;
	downSample += (b+d+f+h) * 0.0625;
	downSample += (j+k+l+m) * 0.125;
	return downSample;
}