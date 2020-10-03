//-----------------------------------------------------------------------------
// Copyright (c) 2018 GarageGames, LLC
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

#ifndef BRDF_HLSL
#define BRDF_HLSL

#include "./torque.hlsl"

// BRDF from Frostbite presentation:
// Moving Frostbite to Physically Based Rendering
// S´ebastien Lagarde - Electronic Arts Frostbite
// Charles de Rousiers - Electronic Arts Frostbite
// SIGGRAPH 2014

// BRDF from Frostbite presentation:
// Moving Frostbite to Physically Based Rendering
// S´ebastien Lagarde - Electronic Arts Frostbite
// Charles de Rousiers - Electronic Arts Frostbite
// SIGGRAPH 2014

float3 F_Schlick(float3 f0, float f90, float u)
{
	return f0 + (f90 - f0) * pow(1.f - u, 5.f);
}

float3 FresnelSchlickRoughness(float cosTheta, float3 F0, float roughness)
{
	float3 ret = float3(0.0, 0.0, 0.0);
	float powTheta = pow(1.0 - cosTheta, 5.0);
	float invRough = float(1.0 - roughness);

	ret.x = F0.x + (max(invRough, F0.x) - F0.x) * powTheta;
	ret.y = F0.y + (max(invRough, F0.y) - F0.y) * powTheta;
	ret.z = F0.z + (max(invRough, F0.z) - F0.z) * powTheta;

	return ret;
}

float V_SmithGGXCorrelated(float NdotL, float NdotV, float alphaRoughnessSq)
{
	float GGXV = NdotL * sqrt(NdotV * NdotV * (1.0 - alphaRoughnessSq) + alphaRoughnessSq);
	float GGXL = NdotV * sqrt(NdotL * NdotL * (1.0 - alphaRoughnessSq) + alphaRoughnessSq);

	float GGX = GGXV + GGXL;
	if (GGX > 0.0f)
	{
		return 0.5f / GGX;
	}
	return 0.f;
}

float D_GGX(float NdotH, float alphaRoughnessSq)
{
	float f = (NdotH * alphaRoughnessSq - NdotH) * NdotH + 1;
	return alphaRoughnessSq / (M_PI_F * f * f);
}

#endif
