//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
// Portions Copyright Zefiros
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

#include "./torque.hlsl"
#include "./brdf.hlsl"
#include "./shaderModelAutoGen.hlsl"

#ifndef TORQUE_SHADERGEN

// These are the uniforms used by most lighting shaders.

uniform float4 inLightPos[3];
uniform float4 inLightInvRadiusSq;
uniform float4 inLightColor[4];

#ifndef TORQUE_BL_NOSPOTLIGHT
   uniform float4 inLightSpotDir[3];
   uniform float4 inLightSpotAngle;
   uniform float4 inLightSpotFalloff;
#endif

uniform float4 ambient;
uniform float smoothness;
uniform float metalness;
uniform float4 albedo;

#endif // !TORQUE_SHADERGEN

//deferred lighting output
struct LightTargetOutput
{
    float4 spec: TORQUE_TARGET0;
    float4 diffuse: TORQUE_TARGET1;
};

//TODO fix compute 4 lights
void compute4Lights( float3 wsView, 
                     float3 wsPosition, 
                     float3 wsNormal,
                     float4 shadowMask,

                     #ifdef TORQUE_SHADERGEN
                     
                        float4 inLightPos[3],
                        float4 inLightInvRadiusSq,
                        float4 inLightColor[4],
                        float4 inLightSpotDir[3],
                        float4 inLightSpotAngle,
                        float4 inLightSpotFalloff,
                        float smoothness,
                        float metalness,
                        float4 albedo,

                     #endif // TORQUE_SHADERGEN
                     
                     out float4 outDiffuse,
                     out float4 outSpecular )
{

   outDiffuse = float4(0,0,0,0);
   outSpecular = float4(0,0,0,0);
}

struct Surface
{
	float3 P;				// world space position
	float3 N;				// world space normal
	float3 V;				// world space view vector
	float4 baseColor;		// base color [0 -> 1] (rgba)
	float metalness;		// metalness [0:dielectric -> 1:metal]
	float roughness;		// roughness: [0:smooth -> 1:rough] (linear)
	float roughness_brdf; // roughness remapped from linear to BRDF
   float depth;         // depth: [0:near -> 1:far] (linear)
   float ao;            // ambient occlusion [0 -> 1]
   float matFlag;       // material flag - use getFlag to retreive 

	float NdotV;			// cos(angle between normal and view vector)
	float3 f0;				// fresnel value (rgb)
	float3 albedo;			// diffuse light absorbtion value (rgb)
	float3 R;				// reflection vector
	float3 F;				// fresnel term computed from f0, N and V

	inline void Update()
	{
		NdotV = abs(dot(N, V)) + 1e-5f; // avoid artifact

		albedo = baseColor.rgb * (1.0 - metalness);
		f0 = lerp(float3_splat(0.04), baseColor.rgb, metalness);

		R = -reflect(V, N);
		float f90 = saturate(50.0 * dot(f0, 0.33));
		F = F_Schlick(f0, f90, NdotV);
	}
};

inline Surface CreateSurface(TORQUE_SAMPLER2D(gbufferTex0), TORQUE_SAMPLER2D(gbufferTex1), TORQUE_SAMPLER2D(gbufferTex2), in float2 uv, in float3 wsEyePos, in float3 wsEyeRay, in float4x4 invView)
{
	Surface surface;

   float4 gbuffer0 = UnpackDepthNormal(TORQUE_SAMPLER2D_MAKEARG(gbufferTex0), uv);
   float4 gbuffer1 = TORQUE_TEX2DLOD(gbufferTex1, float4(uv,0,0));
   float4 gbuffer2 = TORQUE_TEX2DLOD(gbufferTex2, float4(uv,0,0));

   surface.depth = gbuffer0.a;
	surface.P = wsEyePos + wsEyeRay * surface.depth;
	surface.N = mul(invView, float4(gbuffer0.xyz,0)).xyz;
	surface.V = normalize(wsEyePos - surface.P);
	surface.baseColor = gbuffer1;
   const float minRoughness=1e-4;
	surface.roughness = clamp(1.0 - gbuffer2.b, minRoughness, 1.0); //torque uses smoothness so we convert to roughness. Should really clamp during gbuffer pass though
	surface.roughness_brdf = surface.roughness * surface.roughness;
	surface.metalness = gbuffer2.a;
   surface.ao = gbuffer2.g;
   surface.matFlag = gbuffer2.r;

	surface.Update();
	return surface;
}

struct SurfaceToLight
{
	float3 L;				// surface to light vector
	float3 H;				// half-vector between view vector and light vector
	float NdotL;			// cos(angle between N and L)
	float HdotV;			// cos(angle between H and V) = HdotL = cos(angle between H and L)
	float NdotH;			// cos(angle between N and H)
};

inline SurfaceToLight CreateSurfaceToLight(in Surface surface, in float3 L)
{
	SurfaceToLight surfaceToLight;

	surfaceToLight.L = normalize(L);
	surfaceToLight.H = normalize(surface.V + surfaceToLight.L);
	surfaceToLight.NdotL = saturate(dot(surfaceToLight.L, surface.N));
	surfaceToLight.HdotV = saturate(dot(surfaceToLight.H, surface.V));
	surfaceToLight.NdotH = saturate(dot(surfaceToLight.H, surface.N));

	return surfaceToLight;
}

float3 BRDF_GetSpecular(in Surface surface, in SurfaceToLight surfaceToLight)
{
	float f90 = saturate(50.0 * dot(surface.f0, 0.33));
	float3 F = F_Schlick(surface.f0, f90, surfaceToLight.HdotV);
	float Vis = V_SmithGGXCorrelated(surface.NdotV, surfaceToLight.NdotL, surface.roughness_brdf);
	float D = D_GGX(surfaceToLight.NdotH, surface.roughness_brdf);
	float3 Fr = D * F * Vis / M_PI_F;
	return Fr;
}

float BRDF_GetDiffuse(in Surface surface, in SurfaceToLight surfaceToLight)
{
   //getting some banding with disney method, using lambert instead - todo do some futher testing
	float Fd = 1.0 / M_PI_F;//Fr_DisneyDiffuse(surface.NdotV, surfaceToLight.NdotL, surfaceToLight.HdotV, surface.roughness) / M_PI_F;
	return Fd;
}

struct LightResult
{
   float3 diffuse;
   float3 spec;
};

inline LightResult GetDirectionalLight(in Surface surface, in SurfaceToLight surfaceToLight, float3 lightColor, float lightIntensity, float shadow)
{
   LightResult result;
   float3 factor = lightColor * max(surfaceToLight.NdotL, 0) * shadow * lightIntensity;
   result.diffuse = BRDF_GetDiffuse(surface,surfaceToLight) * factor;
   result.spec = BRDF_GetSpecular(surface,surfaceToLight) * factor;

   result.diffuse = max(0.0f, result.diffuse);
   result.spec = max(0.0f, result.spec);

   return result;
}
