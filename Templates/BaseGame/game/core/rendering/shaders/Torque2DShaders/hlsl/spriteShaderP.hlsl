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

#include "../../shaderModel.hlsl"

struct Conn
{
   float4 HPOS             : TORQUE_VPOS;
   float4 color            : COLOR;
   float2 texCoord         : TEXCOORD0;
};

struct Fragout
{
	float4 col : TORQUE_TARGET0;
};

TORQUE_UNIFORM_SAMPLER2D(diffuseMap, 0);
TORQUE_UNIFORM_SAMPLER2D(normalMap, 1);

uniform float3 worldPos;
uniform float4 ambientColor;
uniform float4 inLightPos[4];
uniform float4 inLightConfigData[4];
uniform float4 inLightColor[4];

Fragout main( Conn IN )
{
	Fragout OUT;
	
	float4 col = TORQUE_TEX2D(diffuseMap, IN.texCoord);
	float3 nor = TORQUE_TEX2D(normalMap, IN.texCoord).rgb;
	
	float3 Sum = 0.0.xxx;
	int i;
	for(i = 0; i < 4; i++)
	{
		float4 lightPosNorm = inLightPos[i];
		float3 LightDir = float3(lightPosNorm.xy - worldPos.xy, 0.5);
		float D = length(LightDir);
		float3 N = normalize(nor * 2.0 - 1.0);
		float3 L = normalize(LightDir);
		float sqrDist = dot(LightDir, LightDir);
		
		float NDotL = max(dot(N, L), 0.0);
		float3 Diffuse = (inLightColor[i].rgb * inLightColor[i].a) * NDotL;
		
		float factor = sqrDist * inLightConfigData[i].a;
		float smoothFactor = saturate(1.0f - factor * factor);
		float Attenuation = 1.0 / (max(sqrDist, 0.01 * 0.01));
		Attenuation *= sqrt(smoothFactor);
		
		float3 Intensity = (ambientColor.rgb * ambientColor.a) + Diffuse * Attenuation;
		float3 FinalColor = col.rgb * Intensity;
		Sum += FinalColor;
	}

	OUT.col = IN.color * float4(Sum, col.a);
	return OUT;
}