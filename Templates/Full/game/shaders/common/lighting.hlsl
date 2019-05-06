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

#define MAX_PROBES 50
#define MAX_FORWARD_PROBES 4

inline float3 getDistanceVectorToPlane( float3 origin, float3 direction, float4 plane )
{
   float denum = dot( plane.xyz, direction.xyz );
   float num = dot( plane, float4( origin, 1.0 ) );
   float t = -num / denum;

   return direction.xyz * t;
}

inline float3 getDistanceVectorToPlane( float negFarPlaneDotEye, float3 direction, float4 plane )
{
   float denum = dot( plane.xyz, direction.xyz );
   float t = negFarPlaneDotEye / denum;

   return direction.xyz * t;
}

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
		f0 = lerp(0.04.xxx, baseColor.rgb, metalness);

		R = -reflect(V, N);
		float f90 = saturate(50.0 * dot(f0, 0.33));
		F = F_Schlick(f0, f90, NdotV);
	}
};

inline Surface createSurface(float4 gbuffer0, TORQUE_SAMPLER2D(gbufferTex1), TORQUE_SAMPLER2D(gbufferTex2), in float2 uv, in float3 wsEyePos, in float3 wsEyeRay, in float4x4 invView)
{
	Surface surface = (Surface)0;

   float4 gbuffer1 = TORQUE_TEX2DLOD(gbufferTex1, float4(uv,0,0));
   float4 gbuffer2 = TORQUE_TEX2DLOD(gbufferTex2, float4(uv,0,0));

   surface.depth = gbuffer0.a;
	surface.P = wsEyePos + wsEyeRay * surface.depth;
	surface.N = mul(invView, float4(gbuffer0.xyz,0)).xyz; //TODO move t3d to use WS normals
	surface.V = normalize(wsEyePos - surface.P);
	surface.baseColor = gbuffer1;
   const float minRoughness=1e-4;
	surface.roughness = clamp(1.0 - gbuffer2.b, minRoughness, 1.0); //t3d uses smoothness, so we convert to roughness.
	surface.roughness_brdf = surface.roughness * surface.roughness;
	surface.metalness = gbuffer2.a;
   surface.ao = gbuffer2.g;
   surface.matFlag = gbuffer2.r;

	surface.Update();
	return surface;
}

inline Surface createForwardSurface(float4 baseColor, float3 normal, float4 pbrProperties, in float2 uv, 
                            in float3 wsPosition, in float3 wsEyePos, in float3 wsEyeRay)
{
	Surface surface = (Surface)0;

  surface.depth = 0;
	surface.P = wsPosition;
	surface.N = normal;
	surface.V = normalize(wsEyePos - surface.P);
	surface.baseColor = baseColor;
  const float minRoughness=1e-4;
	surface.roughness = clamp(1.0 - pbrProperties.b, minRoughness, 1); //t3d uses smoothness, so we convert to roughness.
	surface.roughness_brdf = surface.roughness * surface.roughness;
	surface.metalness = pbrProperties.a;
  surface.ao = pbrProperties.g;
  surface.matFlag = pbrProperties.r;

	surface.Update();
	return surface;
}

struct SurfaceToLight
{
	float3 L;				// surface to light vector
   float3 Lu;				// un-normalized surface to light vector
	float3 H;				// half-vector between view vector and light vector
	float NdotL;			// cos(angle between N and L)
	float HdotV;			// cos(angle between H and V) = HdotL = cos(angle between H and L)
	float NdotH;			// cos(angle between N and H)
};

inline SurfaceToLight createSurfaceToLight(in Surface surface, in float3 L)
{
	SurfaceToLight surfaceToLight = (SurfaceToLight)0;
   surfaceToLight.Lu = L;
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

float3 BRDF_GetDiffuse(in Surface surface, in SurfaceToLight surfaceToLight)
{
   //getting some banding with disney method, using lambert instead - todo futher testing
	float Fd = 1.0 / M_PI_F;
   //energy conservation - remove this if reverting back to disney method
   float3 kD = 1.0.xxx - surface.F;
	kD *= 1.0 - surface.metalness;
   float3 diffuse = kD * surface.baseColor.rgb * Fd;
	return diffuse;
}

//attenuations functions from "moving frostbite to pbr paper"
//https://seblagarde.files.wordpress.com/2015/07/course_notes_moving_frostbite_to_pbr_v32.pdf
float smoothDistanceAtt ( float squaredDistance , float invSqrAttRadius )
{
   float factor = squaredDistance * invSqrAttRadius ;
   float smoothFactor = saturate (1.0f - factor * factor );
   return sqr(smoothFactor);
}

float getDistanceAtt( float3 unormalizedLightVector , float invSqrAttRadius )
{
   float sqrDist = dot ( unormalizedLightVector , unormalizedLightVector );
   float attenuation = 1.0 / (max ( sqrDist , 0.01*0.01) );
   attenuation *= smoothDistanceAtt ( sqrDist , invSqrAttRadius );
   return attenuation;
}

 float getSpotAngleAtt( float3 normalizedLightVector , float3 lightDir , float2 lightSpotParams )
 {
   float cd = dot ( lightDir , normalizedLightVector );
   float attenuation = saturate ( ( cd - lightSpotParams.x ) / lightSpotParams.y );
   // smooth the transition
   return sqr(attenuation);
}

inline float3 getDirectionalLight(in Surface surface, in SurfaceToLight surfaceToLight, float3 lightColor, float lightIntensity, float shadow)
{
   float3 factor = lightColor * max(surfaceToLight.NdotL, 0) * shadow * lightIntensity;
   float3 diffuse = BRDF_GetDiffuse(surface,surfaceToLight) * factor;
   float3 spec = BRDF_GetSpecular(surface,surfaceToLight) * factor;

   float3 final = max(0.0f, diffuse + spec * surface.ao);
   return final;
}

inline float3 getPunctualLight(in Surface surface, in SurfaceToLight surfaceToLight, float3 lightColor, float lightIntensity, float radius, float shadow)
{
   float attenuation = getDistanceAtt(surfaceToLight.Lu, radius);
   float3 factor = lightColor * max(surfaceToLight.NdotL, 0) * shadow * lightIntensity * attenuation;

   float3 diffuse = BRDF_GetDiffuse(surface,surfaceToLight) * factor;
   float3 spec = BRDF_GetSpecular(surface,surfaceToLight) * factor;

   float3 final = max(0.0f, diffuse + spec * surface.ao * surface.F);
   return final;
}

//Probe IBL stuff
float defineSphereSpaceInfluence(float3 wsPosition, float3 wsProbePosition, float radius)
{
   float3 L = wsProbePosition.xyz - wsPosition;
   float contribution = 1.0 - length(L) / radius;
   return contribution;
}

float getDistBoxToPoint(float3 pt, float3 extents)
{
   float3 d = max(max(-extents - pt, 0), pt - extents);
   return max(max(d.x, d.y), d.z);
}

float defineBoxSpaceInfluence(float3 wsPosition, float4x4 worldToObj, float attenuation)
{
   float3 surfPosLS = mul(worldToObj, float4(wsPosition, 1.0)).xyz;
   float atten = 1.0 - attenuation;
   float baseVal = 0.25;
   float dist = getDistBoxToPoint(surfPosLS, float3(baseVal, baseVal, baseVal));
   return saturate(smoothstep(baseVal + 0.0001, atten*baseVal, dist));
}

// Box Projected IBL Lighting
// Based on: http://www.gamedev.net/topic/568829-box-projected-cubemap-environment-mapping/
// and https://seblagarde.wordpress.com/2012/09/29/image-based-lighting-approaches-and-parallax-corrected-cubemap/
float3 boxProject(float3 wsPosition, float3 wsReflectVec, float4x4 worldToObj, float3 bbMin, float3 bbMax, float3 refPosition)
{
   float3 RayLS = mul(worldToObj, float4(wsReflectVec, 0.0)).xyz;
   float3 PositionLS = mul(worldToObj, float4(wsPosition, 1.0)).xyz;

   float3 unit = bbMax.xyz - bbMin.xyz;
   float3 plane1vec = (unit / 2 - PositionLS) / RayLS;
   float3 plane2vec = (-unit / 2 - PositionLS) / RayLS;
   float3 furthestPlane = max(plane1vec, plane2vec);
   float dist = min(min(furthestPlane.x, furthestPlane.y), furthestPlane.z);
   float3 posonbox = wsPosition + wsReflectVec * dist;

   return posonbox - refPosition.xyz;
}

float4 computeForwardProbes(Surface surface,
    float cubeMips, float numProbes, float4x4 worldToObjArray[MAX_FORWARD_PROBES], float4 probeConfigData[MAX_FORWARD_PROBES], 
    float4 inProbePosArray[MAX_FORWARD_PROBES], float4 bbMinArray[MAX_FORWARD_PROBES], float4 bbMaxArray[MAX_FORWARD_PROBES], float4 inRefPosArray[MAX_FORWARD_PROBES],
    float hasSkylight, TORQUE_SAMPLER2D(BRDFTexture), 
	TORQUE_SAMPLERCUBE(skylightIrradMap), TORQUE_SAMPLERCUBE(skylightSpecularMap),
	TORQUE_SAMPLERCUBEARRAY(irradianceCubemapAR), TORQUE_SAMPLERCUBEARRAY(specularCubemapAR))
{
  int i = 0;
   float blendFactor[MAX_FORWARD_PROBES];
   float blendSum = 0;
   float blendFacSum = 0;
   float invBlendSum = 0;
   float probehits = 0;
   //Set up our struct data
   float contribution[MAX_FORWARD_PROBES];
  for (i = 0; i < numProbes; ++i)
  {
      contribution[i] = 0;

      if (probeConfigData[i].r == 0) //box
      {
         contribution[i] = defineBoxSpaceInfluence(surface.P, worldToObjArray[i], probeConfigData[i].b);
         if (contribution[i] > 0.0)
            probehits++;
      }
      else if (probeConfigData[i].r == 1) //sphere
      {
         contribution[i] = defineSphereSpaceInfluence(surface.P, inProbePosArray[i].xyz, probeConfigData[i].g);
         if (contribution[i] > 0.0)
            probehits++;
      }

      contribution[i] = max(contribution[i], 0);

      blendSum += contribution[i];
      invBlendSum += (1.0f - contribution[i]);
   }

   if (probehits > 1.0)
   {
      for (i = 0; i < numProbes; i++)
      {
         blendFactor[i] = ((contribution[i] / blendSum)) / probehits;
         blendFactor[i] *= ((contribution[i]) / invBlendSum);
         blendFactor[i] = saturate(blendFactor[i]);
         blendFacSum += blendFactor[i];
      }

      // Normalize blendVal
      if (blendFacSum == 0.0f) // Possible with custom weight
      {
         blendFacSum = 1.0f;
      }

      float invBlendSumWeighted = 1.0f / blendFacSum;
      for (i = 0; i < numProbes; ++i)
      {
         blendFactor[i] *= invBlendSumWeighted;
         contribution[i] *= blendFactor[i];
      }
   }

   float3 irradiance = float3(0, 0, 0);
   float3 specular = float3(0, 0, 0);

   // Radiance (Specular)
   float lod = surface.roughness*cubeMips;

   float alpha = 1;
   for (i = 0; i < numProbes; ++i)
   {
      float contrib = contribution[i];
      if (contrib != 0)
      {
         int cubemapIdx = probeConfigData[i].a;
         float3 dir = boxProject(surface.P, surface.R, worldToObjArray[i], bbMinArray[i].xyz, bbMaxArray[i].xyz, inRefPosArray[i].xyz);

         irradiance += TORQUE_TEXCUBEARRAYLOD(irradianceCubemapAR, dir, cubemapIdx, 0).xyz * contrib;
         specular += TORQUE_TEXCUBEARRAYLOD(specularCubemapAR, dir, cubemapIdx, lod).xyz * contrib;
         alpha -= contrib;
      }
   }

   if (hasSkylight && alpha > 0.001)
   {
      irradiance += TORQUE_TEXCUBELOD(skylightIrradMap, float4(surface.R, 0)).xyz;
      specular = TORQUE_TEXCUBELOD(skylightSpecularMap, float4(surface.R, lod)).xyz;
   }

   float3 F = FresnelSchlickRoughness(surface.NdotV, surface.f0, surface.roughness);

   //energy conservation
   float3 kD = 1.0.xxx - F;
   kD *= 1.0 - surface.metalness;

   //apply brdf
   //Do it once to save on texture samples
   float2 brdf = TORQUE_TEX2DLOD(BRDFTexture,float4(surface.roughness, 1.0-surface.NdotV, 0.0, 0.0)).xy;
   specular *= brdf.x * F + brdf.y;

   //final diffuse color
   float3 diffuse = kD * irradiance * surface.baseColor.rgb;
   float4 finalColor = float4(diffuse + specular, 1); 
//finalColor.rgb += abs(surface.N);
   return finalColor;
}