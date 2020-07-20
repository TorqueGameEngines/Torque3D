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

#include "./torque.glsl"
#include "./brdf.glsl"
#ifndef TORQUE_SHADERGEN
#line 26
// These are the uniforms used by most lighting shaders.

uniform vec4 inLightPos[3];
uniform vec4 inLightInvRadiusSq;
uniform vec4 inLightColor[4];

#ifndef TORQUE_BL_NOSPOTLIGHT
   uniform vec4 inLightSpotDir[3];
   uniform vec4 inLightSpotAngle;
   uniform vec4 inLightSpotFalloff;
#endif

uniform vec4 ambient;
#define ambientCameraFactor 0.3
uniform float smoothness;
uniform float metalness;
uniform vec4 albedo;

#endif // !TORQUE_SHADERGEN

#define MAX_PROBES 50
#define MAX_FORWARD_PROBES 4

#define MAX_FORWARD_LIGHT 4

vec3 getDistanceVectorToPlane( vec3 origin, vec3 direction, vec4 plane )
{
   float denum = dot( plane.xyz, direction.xyz );
   float num = dot( plane, vec4( origin, 1.0 ) );
   float t = -num / denum;

   return direction.xyz * t;
}

vec3 getDistanceVectorToPlane( float negFarPlaneDotEye, vec3 direction, vec4 plane )
{
   float denum = dot( plane.xyz, direction.xyz );
   float t = negFarPlaneDotEye / denum;

   return direction.xyz * t;
}

struct Surface
{
	vec3 P;				// world space position
	vec3 N;				// world space normal
	vec3 V;				// world space view vector
	vec4 baseColor;		// base color [0 -> 1] (rgba)
	float metalness;		// metalness [0:dielectric -> 1:metal]
	float roughness;		// roughness: [0:smooth -> 1:rough] (linear)
	float roughness_brdf; // roughness remapped from linear to BRDF
	float depth;         // depth: [0:near -> 1:far] (linear)
	float ao;            // ambient occlusion [0 -> 1]
	float matFlag;       // material flag - use getFlag to retreive 

	float NdotV;			// cos(angle between normal and view vector)
	vec3 f0;				// fresnel value (rgb)
    float f90;
	vec3 albedo;			// diffuse light absorbtion value (rgb)
	vec3 R;				// reflection vector
	vec3 F;				// fresnel term computed from f0, N and V
};

void updateSurface(inout Surface surface)
{
	surface.NdotV = abs(dot(surface.N, surface.V)) + 1e-5f; // avoid artifact

	surface.albedo = surface.baseColor.rgb * (1.0 - surface.metalness);
	surface.f0 = lerp(vec3(0.04f), surface.baseColor.rgb, surface.metalness);
	surface.R = -reflect(surface.V, surface.N);
	surface.f90 = saturate(50.0 * dot(surface.f0, vec3(0.33,0.33,0.33)));
	surface.F = F_Schlick(surface.f0, surface.f90, surface.NdotV);
}

Surface createSurface(vec4 normDepth, sampler2D colorBuffer, sampler2D matInfoBuffer, in vec2 uv, in vec3 wsEyePos, in vec3 wsEyeRay, in mat4 invView)
{
   Surface surface;// = Surface();

   vec4 gbuffer1 = texture(colorBuffer, uv);
   vec4 gbuffer2 = texture(matInfoBuffer, uv);
   surface.depth = normDepth.a;
   surface.P = wsEyePos + wsEyeRay * surface.depth;
   surface.N = tMul(invView, vec4(normDepth.xyz,0)).xyz;
   surface.V = normalize(wsEyePos - surface.P);
   surface.baseColor = gbuffer1;
   const float minRoughness=1e-4;
   surface.roughness = 1.0 - (gbuffer2.b*0.8+0.1999); //t3d uses smoothness, so we convert to roughness.
   surface.roughness_brdf = surface.roughness * surface.roughness;
   surface.metalness = gbuffer2.a;
   surface.ao = gbuffer2.g;
   surface.matFlag = gbuffer2.r;
      updateSurface(surface);
   return surface;
}

Surface createForwardSurface(vec4 baseColor, vec3 normal, vec4 pbrProperties, in vec3 wsPosition, in vec3 wsEyePos, in vec3 wsEyeRay)
{
   Surface surface;// = Surface();

   surface.depth = 0;
   surface.P = wsPosition;
   surface.N = normal;
   surface.V = normalize(wsEyePos - surface.P);
   surface.baseColor = baseColor;
   const float minRoughness=1e-4;
   surface.roughness = 1.0 - (pbrProperties.b*0.8+0.1999); //t3d uses smoothness, so we convert to roughness.
   surface.roughness_brdf = surface.roughness * surface.roughness;
   surface.metalness = pbrProperties.a;
   surface.ao = pbrProperties.g;
   surface.matFlag = pbrProperties.r;

   updateSurface(surface);
   return surface;
}

struct SurfaceToLight
{
	vec3 L;				// surface to light vector
	vec3 Lu;				// un-normalized surface to light vector
	vec3 H;				// half-vector between view vector and light vector
	float NdotL;			// cos(angle between N and L)
	float HdotV;			// cos(angle between H and V) = HdotL = cos(angle between H and L)
	float NdotH;			// cos(angle between N and H)

};

SurfaceToLight createSurfaceToLight(in Surface surface, in vec3 L)
{
	SurfaceToLight surfaceToLight;// = SurfaceToLight();
	surfaceToLight.Lu = L;
	surfaceToLight.L = normalize(L);
	surfaceToLight.H = normalize(surface.V + surfaceToLight.L);
	surfaceToLight.NdotL = saturate(dot(surfaceToLight.L, surface.N));
	surfaceToLight.HdotV = saturate(dot(surfaceToLight.H, surface.V));
	surfaceToLight.NdotH = saturate(dot(surfaceToLight.H, surface.N));
	return surfaceToLight;
}

vec3 BRDF_GetDebugSpecular(in Surface surface, in SurfaceToLight surfaceToLight)
{
   //GGX specular
   vec3 F = F_Schlick(surface.f0, surface.f90, surfaceToLight.HdotV);
   float Vis = V_SmithGGXCorrelated(surface.NdotV, surfaceToLight.NdotL, surface.roughness);
   float D = D_GGX(surfaceToLight.NdotH, surface.roughness);
   vec3 Fr = D * F * Vis;
   return Fr*M_1OVER_PI_F;
}

vec3 BRDF_GetDebugDiffuse(in Surface surface, in SurfaceToLight surfaceToLight)
{
   vec3 Fd = surface.albedo.rgb;
   return Fd*M_1OVER_PI_F;
}

//attenuations functions from "moving frostbite to pbr paper"
//https://seblagarde.files.wordpress.com/2015/07/course_notes_moving_frostbite_to_pbr_v32.pdf
float smoothDistanceAtt ( float squaredDistance , float invSqrAttRadius )
{
   float factor = squaredDistance * invSqrAttRadius ;
   float smoothFactor = saturate (1.0f - factor * factor );
   return sqr(smoothFactor);
}

float getDistanceAtt( vec3 unormalizedLightVector , float invSqrAttRadius )
{
   float sqrDist = dot ( unormalizedLightVector , unormalizedLightVector );
   float attenuation = 1.0 / (max ( sqrDist , 0.01*0.01) );
   attenuation *= smoothDistanceAtt ( sqrDist , invSqrAttRadius );
   return attenuation;
}

 float getSpotAngleAtt( vec3 normalizedLightVector , vec3 lightDir , vec2 lightSpotParams )
 {
   float cd = dot ( lightDir , normalizedLightVector );
   float attenuation = saturate ( ( cd - lightSpotParams.x ) / lightSpotParams.y );
   // smooth the transition
   return sqr(attenuation);
}

vec3 evaluateStandardBRDF(Surface surface, SurfaceToLight surfaceToLight)
{
   //lambert diffuse
   vec3 Fd = surface.albedo.rgb;
    
   //GGX specular
   vec3 F = F_Schlick(surface.f0, surface.f90, surfaceToLight.HdotV);
   float Vis = V_SmithGGXCorrelated(surface.NdotV, surfaceToLight.NdotL, surface.roughness);
   float D = D_GGX(surfaceToLight.NdotH, surface.roughness);
   vec3 Fr = D * F * Vis;

   return (Fd + Fr) * M_1OVER_PI_F;
}

vec3 getDirectionalLight(Surface surface, SurfaceToLight surfaceToLight, vec3 lightColor, float lightIntensity, float shadow)
{
   vec3 factor = lightColor * max(surfaceToLight.NdotL, 0.0f) * shadow * lightIntensity;
   return evaluateStandardBRDF(surface,surfaceToLight) * factor;
}

vec3 getPunctualLight(Surface surface, SurfaceToLight surfaceToLight, vec3 lightColor, float lightIntensity, float radius, float shadow)
{
   float attenuation = getDistanceAtt(surfaceToLight.Lu, radius);
   vec3 factor = lightColor * max(surfaceToLight.NdotL, 0.0f) * shadow * lightIntensity * attenuation;
   return evaluateStandardBRDF(surface,surfaceToLight) * factor;
}

float computeSpecOcclusion( float NdotV , float AO , float roughness )
{
   return saturate (pow( abs(NdotV + AO) , exp2 ( -16.0f * roughness - 1.0f )) - 1.0f + AO );
}

vec4 compute4Lights( Surface surface,
                     vec4 shadowMask,
                     vec4 inLightPos[4],
                     vec4 inLightConfigData[4],
                     vec4 inLightColor[4],
                     vec4 inLightSpotDir[4],
                     vec2 lightSpotParams[4],
                     int hasVectorLight,
                     vec4 vectorLightDirection,
                     vec4 vectorLightingColor,
                     float  vectorLightBrightness )
{
   vec3 finalLighting = vec3(0.0f);

   int i;
   for(i = 0; i < MAX_FORWARD_LIGHT; i++)
   {
      vec3 L = inLightPos[i].xyz - surface.P;
      float dist = length(L);
      float lightRange = inLightConfigData[i].z;
      SurfaceToLight surfaceToLight = createSurfaceToLight(surface, L);
      float shadowed = 1.0;

      vec3 lightCol = inLightColor[i].rgb;

      float lightBrightness = inLightConfigData[i].y;
      float lightInvSqrRange= inLightConfigData[i].a;

      vec3 lighting = vec3(0.0f);

      if(dist < lightRange)
      { 
         if(inLightConfigData[i].x == 0) //point
         {
            //get punctual light contribution   
            lighting = getPunctualLight(surface, surfaceToLight, lightCol, lightBrightness, lightInvSqrRange, shadowed);
         }
         else //spot
         {
               
            //get Punctual light contribution   
            lighting = getPunctualLight(surface, surfaceToLight, lightCol, lightBrightness, lightInvSqrRange, shadowed);
            //get spot angle attenuation
            lighting *= getSpotAngleAtt(-surfaceToLight.L, inLightSpotDir[i].xyz, lightSpotParams[i].xy );
         }
      }
      finalLighting += lighting;
   }

   //Vector light
   if(hasVectorLight == 1)
   {
      SurfaceToLight surfaceToVecLight = createSurfaceToLight(surface, -vectorLightDirection.xyz);

      vec3 vecLighting = getDirectionalLight(surface, surfaceToVecLight, vectorLightingColor.rgb, vectorLightBrightness, 1);
      finalLighting += vecLighting;
   }

   finalLighting *= shadowMask.rgb;

   return vec4(finalLighting,1);
}

//Probe IBL stuff
float defineSphereSpaceInfluence(vec3 wsPosition, vec3 wsProbePosition, float radius)
{
   vec3 L = wsProbePosition.xyz - wsPosition;
   float contribution = 1.0 - length(L) / radius;
   return contribution;
}

float getDistBoxToPoint(vec3 pt, vec3 extents)
{
   vec3 d = max(max(-extents - pt, 0), pt - extents);
   return max(max(d.x, d.y), d.z);
}

float defineBoxSpaceInfluence(vec3 wsPosition, mat4 worldToObj, float attenuation)
{
   vec3 surfPosLS = tMul(worldToObj, vec4(wsPosition, 1.0)).xyz;
   float atten = 1.0 - attenuation;
   float baseVal = 0.25;
   float dist = getDistBoxToPoint(surfPosLS, vec3(baseVal, baseVal, baseVal));
   return saturate(smoothstep(baseVal + 0.0001, atten*baseVal, dist));
}

// Box Projected IBL Lighting
// Based on: http://www.gamedev.net/topic/568829-box-projected-cubemap-environment-mapping/
// and https://seblagarde.wordpress.com/2012/09/29/image-based-lighting-approaches-and-parallax-corrected-cubemap/
vec3 boxProject(vec3 wsPosition, vec3 wsReflectVec, mat4 worldToObj, vec3 refBoxMin, vec3 refBoxMax, vec3 refPosition)
{
   vec3 RayLS = tMul(worldToObj, vec4(wsReflectVec, 0.0)).xyz;
   vec3 PositionLS = tMul(worldToObj, vec4(wsPosition, 1.0)).xyz;

   vec3 unit = refBoxMax.xyz - refBoxMin.xyz;
   vec3 plane1vec = (unit / 2 - PositionLS) / RayLS;
   vec3 plane2vec = (-unit / 2 - PositionLS) / RayLS;
   vec3 furthestPlane = max(plane1vec, plane2vec);
   float dist = min(min(furthestPlane.x, furthestPlane.y), furthestPlane.z);
   vec3 posonbox = wsPosition + wsReflectVec * dist;

   return posonbox - refPosition.xyz;
}

vec4 computeForwardProbes(Surface surface,
    float cubeMips, float numProbes, mat4x4 worldToObjArray[MAX_FORWARD_PROBES], vec4 probeConfigData[MAX_FORWARD_PROBES], 
    vec4 inProbePosArray[MAX_FORWARD_PROBES], vec4 refBoxMinArray[MAX_FORWARD_PROBES], vec4 refBoxMaxArray[MAX_FORWARD_PROBES], vec4 inRefPosArray[MAX_FORWARD_PROBES],
    float skylightCubemapIdx, sampler2D BRDFTexture, 
	samplerCubeArray irradianceCubemapAR, samplerCubeArray specularCubemapAR)
{
   int i = 0;
   float alpha = 1;
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

   vec3 irradiance = vec3(0, 0, 0);
   vec3 specular = vec3(0, 0, 0);

   // Radiance (Specular)
   float lod = surface.roughness*cubeMips;

   for (i = 0; i < numProbes; ++i)
   {
      float contrib = contribution[i];
      if (contrib > 0.0f)
      {
         int cubemapIdx = int(probeConfigData[i].a);
         vec3 dir = boxProject(surface.P, surface.R, worldToObjArray[i], refBoxMinArray[i].xyz, refBoxMaxArray[i].xyz, inRefPosArray[i].xyz);

         irradiance += textureLod(irradianceCubemapAR, vec4(dir, cubemapIdx), 0).xyz * contrib;
         specular += textureLod(specularCubemapAR, vec4(dir, cubemapIdx), lod).xyz * contrib;
         alpha -= contrib;
      }
   }

   if(skylightCubemapIdx != -1 && alpha >= 0.001)
   {
      irradiance = mix(irradiance,textureLod(irradianceCubemapAR, vec4(surface.R, skylightCubemapIdx), 0).xyz, alpha);
      specular = mix(specular,textureLod(specularCubemapAR, vec4(surface.R, skylightCubemapIdx), lod).xyz, alpha);
   }

   //energy conservation
   vec3 kD = 1.0f - surface.F;
   kD *= 1.0f - surface.metalness;

   float dfgNdotV = max( surface.NdotV , 0.0009765625f ); //0.5f/512.0f (512 is size of dfg/brdf lookup tex)
   vec2 envBRDF = textureLod(BRDFTexture, vec2(dfgNdotV, surface.roughness),0).rg;
   specular *= surface.F * envBRDF.x + surface.f90 * envBRDF.y;
   irradiance *= kD * surface.baseColor.rgb;

   //AO
   irradiance *= surface.ao;
   specular *= computeSpecOcclusion(surface.NdotV, surface.ao, surface.roughness);

   return vec4(irradiance + specular, 0);//alpha writes disabled
}
