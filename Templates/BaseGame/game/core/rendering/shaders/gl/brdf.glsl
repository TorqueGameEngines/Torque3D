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

#include "./torque.glsl"

// BRDF from Frostbite presentation:
// Moving Frostbite to Physically Based Rendering
// S´ebastien Lagarde - Electronic Arts Frostbite
// Charles de Rousiers - Electronic Arts Frostbite
// SIGGRAPH 2014

vec3 F_Schlick(vec3 F0, float cosTheta)
{
	return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

vec3 FresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness)
{
	// Compute the Fresnel-Schlick term for the given cosine of the angle
    float powTheta = pow(1.0 - cosTheta, 5.0);
    
    // Adjust the reflectance based on roughness: The roughness scales the contrast of the Fresnel term.
    vec3 fresnel = F0 + (vec3(1.0, 1.0, 1.0) - F0) * powTheta;
    
    // Modulate the fresnel term by roughness, reducing the effect at higher roughness
    fresnel *= (1.0 - roughness); // Adjust based on roughness

    return fresnel;
}

float GeometrySchlickGGX(float NdotV, float roughness) { 
    float r = (roughness + 1.0); 
    float k = (r * r) / 8.0;
    return NdotV / (NdotV * (1.0 - k) + k);
}

float V_SmithGGXCorrelated(float NdotL, float NdotV, float roughness) {
    float r = roughness * roughness;
    float ggx1 = NdotV / (NdotV * (1.0 - r) + r);
    float ggx2 = NdotL / (NdotL * (1.0 - r) + r);
    return ggx1 * ggx2;
}

float D_GGX(float NdotH, float roughnessSq)
{
	float f = (NdotH * NdotH * (roughnessSq - 1.0) + 1.0);
	return roughnessSq / (M_PI_F * f * f);
}

// The Cook-Torrance BRDF for specular reflection
vec3 CookTorrance(vec3 normal, vec3 viewDir, float roughness, vec3 F)
{
    vec3 H = normalize(viewDir + reflect(-viewDir, normal)); 
    float NdotH = max(dot(normal, H), 0.0001);
    float VdotH = max(dot(viewDir, H), 0.0001);
    float NdotV = clamp( dot(normal, viewDir), 0.0009765625f,0.9990234375f);
    float NdotL = NdotH; // Approximate light angle

    // Normal Distribution Function (GGX)
    float D = D_GGX(NdotH, roughness);

    // Geometry Term (Smith GGX)
    float G = V_SmithGGXCorrelated(NdotL, NdotV, roughness);

    // Final BRDF (Rebalanced Energy)
    return (F * D * G) / max(4.0 * NdotV * NdotL, 0.0001);
}


vec3 OrenNayarDiffuse(vec3 albedo, vec3 N, vec3 V, vec3 L, float roughnessSq) {
    float NdotL = max(dot(N, L), 0.0);
    float NdotV = max(dot(N, V), 0.0);

    float alpha2 = roughnessSq * roughnessSq;
    float A = 1.0 + (alpha2 / (alpha2 + 0.33));
    float B = 0.45 * (alpha2 / (alpha2 + 0.09));

    float alpha = max(NdotL, NdotV);
    float beta = min(NdotL, NdotV);

    return albedo * (A + B * max(0.0, dot(V - N * NdotV, L - N * NdotL)) * alpha * beta) * M_1OVER_PI_F;
}

vec3 Fr_DisneyDiffuse(vec3 F0, float NdotV, float NdotL, float LdotH, float linearRoughness)
{
	float energyBias = lerp (0 , 0.5 , linearRoughness );
	float energyFactor = lerp (1.0 , 1.0 / 1.51 , linearRoughness );
	float fd90 = energyBias + 2.0 * LdotH * LdotH * linearRoughness ;
	vec3 lightScatter = F_Schlick( F0 , fd90 );
	vec3 viewScatter = F_Schlick(F0 , fd90); 

	return lightScatter * viewScatter * energyFactor ;
}
#endif
