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

struct Conn
{
	float4 hpos : TORQUE_POSITION;
  float2 texCoord : TEXCOORD0;
};

TORQUE_UNIFORM_SAMPLER2D(inputTex0, 0);
TORQUE_UNIFORM_SAMPLER2D(inputTex1, 1);
//uniform float filterRadius;

float4 main( Conn V_IN ) : TORQUE_TARGET0
{
	float x = 1.0f;
	float y = 1.0f;
	
	float4 a = TORQUE_TEX2D( inputTex0, V_IN.texCoord + float2(-x, y));
	float4 b = TORQUE_TEX2D( inputTex0, V_IN.texCoord + float2( 0, y));
	float4 c = TORQUE_TEX2D( inputTex0, V_IN.texCoord + float2( x, y));
	
	float4 d = TORQUE_TEX2D( inputTex0, V_IN.texCoord + float2(-x, 0));
	float4 e = TORQUE_TEX2D( inputTex0, V_IN.texCoord);
	float4 f = TORQUE_TEX2D( inputTex0, V_IN.texCoord + float2( x, 0));
	
	float4 g = TORQUE_TEX2D( inputTex0, V_IN.texCoord + float2(-x,-y));
	float4 h = TORQUE_TEX2D( inputTex0, V_IN.texCoord + float2( 0,-y));
	float4 i = TORQUE_TEX2D( inputTex0, V_IN.texCoord + float2( x,-y));
	
	float4 sample = e * 4.0f;
	sample += (b+d+f+h) * 2.0f;
	sample += (a+c+g+i);
	sample *= 1.0f / 16.0f;
	return sample * 0.75f + TORQUE_TEX2D(inputTex1, V_IN.texCoord) * 0.25f;
}
