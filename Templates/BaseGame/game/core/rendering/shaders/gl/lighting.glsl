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

uniform float maxProbeDrawDistance;

#ifndef TORQUE_SHADERGEN
#line 27
// These are the uniforms used by most lighting shaders.

uniform vec4 inLightPos[4];
uniform vec4 inLightConfigData[4];
uniform vec4 inLightColor[4];

#ifndef TORQUE_BL_NOSPOTLIGHT
   uniform vec4 inLightSpotDir[4];
   uniform vec4 inLightSpotAngle;
   uniform vec4 inLightSpotFalloff;
#endif

uniform vec4 ambient;
uniform float roughness;
uniform float metalness;
uniform vec4 albedo;

#endif // !TORQUE_SHADERGEN

#ifndef MAX_PROBES
#define MAX_PROBES 8
#endif

#define MAX_FORWARD_PROBES 4

#define MAX_FORWARD_LIGHT 4

#ifndef CAPTURING
#define CAPTURING 0
#endif

#ifndef DEBUGVIZ_ATTENUATION
#define DEBUGVIZ_ATTENUATION 0
#endif

#ifndef DEBUGVIZ_CONTRIB
#define DEBUGVIZ_CONTRIB 0
#endif

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
	float roughness;		// material roughness: [0:smooth -> 1:rough] 
	float linearRoughness; // linear roughness (roughness^2)
   float linearRoughnessSq; // (linearRoughness^2)
	float depth;         // depth: [0:near -> 1:far] (linear)
	float ao;            // ambient occlusion [0 -> 1]
	float matFlag;       // material flag - use getFlag to retreive 

	float NdotV;			// cos(angle between normal and view vector)
	vec3 f0;				// fresnel value (rgb)
	vec3 albedo;			// diffuse light absorbtion value (rgb)
	vec3 R;				// reflection vector
	vec3 F;				// fresnel term computed from f0, N and V
   float f90;

};

void updateSurface(inout Surface surface)
{
	surface.NdotV = clamp( dot(surface.N, surface.V), 0.0009765625f,0.9990234375f);  //0.5f/512.0f (512 is size of dfg/brdf lookup tex)

    surface.linearRoughness = surface.roughness * surface.roughness;
    surface.linearRoughnessSq = surface.linearRoughness * surface.linearRoughness;

	surface.albedo = surface.baseColor.rgb * (1.0f - surface.metalness);
	surface.f0 = mix(vec3(0.04f,0.04f,0.04f), surface.baseColor.rgb, surface.metalness);

	surface.R = -reflect(surface.V, surface.N);
	surface.f90 = saturate(50.0 * dot(surface.f0, vec3(0.33,0.33,0.33)));
	surface.F = F_Schlick(surface.f0, surface.f90, surface.NdotV);
}

Surface createSurface(vec4 gbuffer0, sampler2D gbufferTex1, sampler2D gbufferTex2, in vec2 uv, in vec3 wsEyePos, in vec3 wsEyeRay, in mat4 invView)
{
   Surface surface;// = Surface();

   vec4 gbuffer1 = texture(gbufferTex1, uv);
   vec4 gbuffer2 = texture(gbufferTex2, uv);
   surface.depth = gbuffer0.a;
   surface.P = wsEyePos + wsEyeRay * surface.depth;
   surface.N = tMul(invView, vec4(gbuffer0.xyz,0)).xyz;
   surface.V = normalize(wsEyePos - surface.P);
   surface.baseColor = gbuffer1;
   surface.roughness = gbuffer2.b*0.92f+0.04f;
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
   surface.roughness = pbrProperties.b*0.92f+0.04f;
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
   float Vis = V_SmithGGXCorrelated(surface.NdotV, surfaceToLight.NdotL, surface.linearRoughnessSq);
   float D = D_GGX(surfaceToLight.NdotH, surface.linearRoughnessSq);
   vec3 Fr = D * F * Vis * M_1OVER_PI_F;
   return Fr;
}

vec3 BRDF_GetDebugDiffuse(in Surface surface, in SurfaceToLight surfaceToLight)
{
   return surface.albedo.rgb * M_1OVER_PI_F;
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
   vec3 Fd = surface.albedo.rgb * M_1OVER_PI_F;
    
   //GGX specular
   vec3 F = F_Schlick(surface.f0, surface.f90, surfaceToLight.HdotV);
   float Vis = V_SmithGGXCorrelated(surface.NdotV, surfaceToLight.NdotL, surface.linearRoughnessSq);
   float D = D_GGX(surfaceToLight.NdotH, surface.linearRoughnessSq);
   vec3 Fr = D * F * Vis;

#if CAPTURING == 1
   return saturate(mix(Fd + Fr,surface.f0,surface.metalness));
#else
   return saturate(Fd + Fr);
#endif

}

vec3 getDirectionalLight(Surface surface, SurfaceToLight surfaceToLight, vec3 lightColor, float lightIntensity, float shadow)
{
   vec3 factor = lightColor * max(surfaceToLight.NdotL * shadow * lightIntensity, 0.0f);
   return evaluateStandardBRDF(surface,surfaceToLight) * factor;
}

vec3 getPunctualLight(Surface surface, SurfaceToLight surfaceToLight, vec3 lightColor, float lightIntensity, float radius, float shadow)
{
   float attenuation = getDistanceAtt(surfaceToLight.Lu, radius);
   vec3 factor = lightColor * max(surfaceToLight.NdotL * shadow * lightIntensity * attenuation, 0.0f);
   return evaluateStandardBRDF(surface,surfaceToLight) * factor;
}

float computeSpecOcclusion( float NdotV , float AO , float roughness )
{
   return saturate (pow( abs(NdotV + AO) , exp2 ( -16.0f * roughness - 1.0f )) - 1.0f + AO );
}

float roughnessToMipLevel(float roughness, float numMips)
{	
   return roughness * numMips;
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
   if (getFlag(surface.matFlag, 2))
   {
      return surface.baseColor;
   } 
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
   return saturate(contribution);
}

float getDistBoxToPoint(vec3 pt, vec3 extents)
{
   vec3 d = max(max(-extents - pt, 0), pt - extents);
   return max(max(d.x, d.y), d.z);
}

float defineBoxSpaceInfluence(vec3 wsPosition, mat4 worldToObj, float attenuation)
{
   vec3 surfPosLS = tMul(worldToObj, vec4(wsPosition, 1.0)).xyz;
   float baseVal = 0.25;
   float dist = getDistBoxToPoint(surfPosLS, vec3(baseVal, baseVal, baseVal));
   return saturate(smoothstep(baseVal, (baseVal-attenuation/2), dist));
}

// Box Projected IBL Lighting
// Based on: http://www.gamedev.net/topic/568829-box-projected-cubemap-environment-mapping/
// and https://seblagarde.wordpress.com/2012/09/29/image-based-lighting-approaches-and-parallax-corrected-cubemap/
vec3 boxProject(vec3 wsPosition, vec3 wsReflectVec, mat4 worldToObj, vec3 refScale, vec3 refPosition)
{
   vec3 RayLS = tMul(worldToObj, vec4(wsReflectVec, 0.0)).xyz;
   vec3 PositionLS = tMul(worldToObj, vec4(wsPosition, 1.0)).xyz;

   vec3 unit = refScale;
   vec3 plane1vec = (unit - PositionLS) / RayLS;
   vec3 plane2vec = (-unit - PositionLS) / RayLS;
   vec3 furthestPlane = max(plane1vec, plane2vec);
   float dist = min(min(furthestPlane.x, furthestPlane.y), furthestPlane.z);
   vec3 posonbox = wsPosition + wsReflectVec * dist;

   return posonbox - refPosition.xyz;
}

void dampen(inout Surface surface, sampler2D WetnessTexture, float accumTime, float degree)
{   
   if (degree<=0.0) return;
   vec3 n = abs(surface.N);

   float grav = 2.0-pow(dot(float3(0,0,-1),surface.N),3);
   if (grav<0) grav*=-1.0;
   
   float speed = accumTime*(1.0-surface.roughness)*grav;
   vec2 wetoffset = vec2(speed,speed/2)*0.1; 
      
   float wetness = texture(WetnessTexture, vec2(surface.P.xy*0.2+wetoffset)).b;
   wetness = lerp(wetness,texture(WetnessTexture,vec2(surface.P.zx*0.2+wetoffset)).b,n.y);
   wetness = lerp(wetness,texture(WetnessTexture,vec2(surface.P.zy*0.2+wetoffset)).b,n.x);
   wetness = pow(wetness,3)*degree;
   
   surface.roughness = lerp(surface.roughness,(1.0-pow(wetness,2))*surface.roughness*0.92f+0.04f,degree);
   surface.baseColor.rgb = lerp(surface.baseColor.rgb,surface.baseColor.rgb*(2.0-wetness)/2,degree); 
   updateSurface(surface);
}

vec4 computeForwardProbes(Surface surface,
    float cubeMips, int numProbes, mat4x4 inWorldToObjArray[MAX_FORWARD_PROBES], vec4 inProbeConfigData[MAX_FORWARD_PROBES], 
    vec4 inProbePosArray[MAX_FORWARD_PROBES], vec4 inRefScaleArray[MAX_FORWARD_PROBES], vec4 inRefPosArray[MAX_FORWARD_PROBES],
    vec3 wsEyePos, float skylightCubemapIdx, int SkylightDamp, sampler2D BRDFTexture, sampler2D WetnessTexture, float accumTime, float dampness,
	samplerCubeArray irradianceCubemapAR, samplerCubeArray specularCubemapAR)
{
   int i = 0;
   float alpha = 1;
   float wetAmmout = 0;
   float blendFactor[MAX_FORWARD_PROBES];
   float blendSum = 0;
   float blendFacSum = 0;
   float invBlendSum = 0;
   float probehits = 0;
   //Set up our struct data
   float contribution[MAX_FORWARD_PROBES];
   float blendCap = 0;
  for (i = 0; i < numProbes; i++)
  {
      contribution[i] = 0;
      float atten = 1.0-(length(wsEyePos-inProbePosArray[i].xyz)/maxProbeDrawDistance);
      if (inProbeConfigData[i].r == 0) //box
      {
         contribution[i] = defineBoxSpaceInfluence(surface.P, inWorldToObjArray[i], inProbeConfigData[i].b)*atten;
      }
      else if (inProbeConfigData[i].r == 1) //sphere
      {
         contribution[i] = defineSphereSpaceInfluence(surface.P, inProbePosArray[i].xyz, inProbeConfigData[i].g)*atten;
      }

      if (contribution[i]>0.0)
         probehits++;
      else
         contribution[i] = 0.0;

      if (inRefScaleArray[i].w>0)
         wetAmmout += contribution[i];
      else
         wetAmmout -= contribution[i];
         
      blendSum += contribution[i];
      blendCap = max(contribution[i],blendCap);
   }
   if (wetAmmout<0) wetAmmout =0;

   if (probehits > 0.0)
   {
      invBlendSum = (probehits - blendSum)/probehits; //grab the remainder 
      for (i = 0; i < numProbes; i++)
      {
         blendFactor[i] = contribution[i]/blendSum; //what % total is this instance
         blendFactor[i] *= blendFactor[i]/invBlendSum;  //what should we add to sum to 1
         blendFacSum += blendFactor[i]; //running tally of results
      }

      for (i = 0; i < numProbes; i++)
      {
         //normalize, but in the range of the highest value applied
         //to preserve blend vs skylight
         contribution[i] = blendFactor[i]/blendFacSum*blendCap;
      }
   }

#if (DEBUGVIZ_ATTENUATION == 1)
      float contribAlpha = 1;
      for (i = 0; i < numProbes; i++)
      {
         contribAlpha -= contribution[i];
      }

      return vec4(1 - contribAlpha, 1 - contribAlpha, 1 - contribAlpha, 1);
#endif

#if (DEBUGVIZ_CONTRIB == 1)
   vec3 probeContribColors[4];
   probeContribColors[0] = vec3(1,0,0);
   probeContribColors[1] = vec3(0,1,0);
   probeContribColors[2] = vec3(0,0,1);
   probeContribColors[3] = vec3(1,1,0);

   vec3 finalContribColor = vec3(0, 0, 0);
   float contribAlpha = 1;
   for (i = 0; i < numProbes; i++)
   {
      finalContribColor += contribution[i] *probeContribColors[i].rgb;
      contribAlpha -= contribution[i];
   }

   //Skylight coloration for anything not covered by probes above
   if(skylightCubemapIdx != -1)
      finalContribColor += vec3(0.3, 0.3, 0.3) * contribAlpha;

   return vec4(finalContribColor, 1);
#endif

   vec3 irradiance = vec3(0, 0, 0);
   vec3 specular = vec3(0, 0, 0);

   for (i = 0; i < numProbes; i++)
   {
      float contrib = contribution[i];
      if (contrib > 0.0f)
      {
         alpha -= contrib;
      }
   }
   if (SkylightDamp>0)
      wetAmmout += alpha;
   dampen(surface, WetnessTexture, accumTime, wetAmmout*dampness);
      
   // Radiance (Specular)
   float lod = roughnessToMipLevel(surface.roughness, cubeMips);

   for (i = 0; i < numProbes; i++)
   {
      float contrib = contribution[i];
      if (contrib > 0.0f)
      {
         int cubemapIdx = int(inProbeConfigData[i].a);
         vec3 dir = boxProject(surface.P, surface.R, inWorldToObjArray[i], inRefScaleArray[i].xyz, inRefPosArray[i].xyz);

         irradiance += textureLod(irradianceCubemapAR, vec4(dir, cubemapIdx), 0).xyz * contrib;
         specular += textureLod(specularCubemapAR, vec4(dir, cubemapIdx), lod).xyz * contrib;
      }
   }
      
   if(skylightCubemapIdx != -1 && alpha >= 0.001)
   {
      irradiance = mix(irradiance,textureLod(irradianceCubemapAR, vec4(surface.R, skylightCubemapIdx), 0).xyz, alpha);
      specular = mix(specular,textureLod(specularCubemapAR, vec4(surface.R, skylightCubemapIdx), lod).xyz, alpha);
   }
   
   //energy conservation
   vec3 F = FresnelSchlickRoughness(surface.NdotV, surface.f0, surface.roughness);
   vec3 kD = 1.0f - F;
   kD *= 1.0f - surface.metalness;

   //float dfgNdotV = max( surface.NdotV , 0.0009765625f ); //0.5f/512.0f (512 is size of dfg/brdf lookup tex)
   vec2 envBRDF = textureLod(BRDFTexture, vec2(surface.NdotV, surface.roughness),0).rg;
   specular *= F * envBRDF.x + surface.f90 * envBRDF.y;
   irradiance *= kD * surface.baseColor.rgb;

   //AO
   irradiance *= surface.ao;
   specular *= computeSpecOcclusion(surface.NdotV, surface.ao, surface.roughness);

   //http://marmosetco.tumblr.com/post/81245981087
   float horizonOcclusion = 1.3;
   float horizon = saturate( 1 + horizonOcclusion * dot(surface.R, surface.N));
   horizon *= horizon;
#if CAPTURING == 1
    return vec4(mix((irradiance + specular* horizon),surface.baseColor.rgb,surface.metalness),0);
#else
   return vec4((irradiance + specular* horizon) , 0);//alpha writes disabled
#endif
}

vec4 debugVizForwardProbes(Surface surface,
    float cubeMips, int numProbes, mat4 inWorldToObjArray[MAX_FORWARD_PROBES], vec4 inProbeConfigData[MAX_FORWARD_PROBES], 
    vec4 inProbePosArray[MAX_FORWARD_PROBES], vec4 inRefScaleArray[MAX_FORWARD_PROBES], vec4 inRefPosArray[MAX_FORWARD_PROBES],
    float skylightCubemapIdx, sampler2D BRDFTexture, 
	 samplerCubeArray irradianceCubemapAR, samplerCubeArray specularCubemapAR, int showAtten, int showContrib, int showSpec, int showDiff)
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
  for (i = 0; i < numProbes; i++)
  {
      contribution[i] = 0;

      if (inProbeConfigData[i].r == 0) //box
      {
         contribution[i] = defineBoxSpaceInfluence(surface.P, inWorldToObjArray[i], inProbeConfigData[i].b);
         if (contribution[i] > 0.0)
            probehits++;
      }
      else if (inProbeConfigData[i].r == 1) //sphere
      {
         contribution[i] = defineSphereSpaceInfluence(surface.P, inProbePosArray[i].xyz, inProbeConfigData[i].g);
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
      for (i = 0; i < numProbes; i++)
      {
         blendFactor[i] *= invBlendSumWeighted;
         contribution[i] *= blendFactor[i];
      }
   }

   if(showAtten == 1)
   {
      float contribAlpha = 1;
      for (i = 0; i < numProbes; i++)
      {
         contribAlpha -= contribution[i];
      }

      return vec4(1 - contribAlpha, 1 - contribAlpha, 1 - contribAlpha, 1);
   }

   if(showContrib == 1)
   {
      vec3 probeContribColors[4];
      probeContribColors[0] = vec3(1,0,0);
      probeContribColors[1] = vec3(0,1,0);
      probeContribColors[2] = vec3(0,0,1);
      probeContribColors[3] = vec3(1,1,0);

      vec3 finalContribColor = vec3(0, 0, 0);
      float contribAlpha = 1;
      for (i = 0; i < numProbes; i++)
      {
         finalContribColor += contribution[i] *probeContribColors[i].rgb;
         contribAlpha -= contribution[i];
      }

      //Skylight coloration for anything not covered by probes above
      if(skylightCubemapIdx != -1)
         finalContribColor += vec3(0.3, 0.3, 0.3) * contribAlpha;

      return vec4(finalContribColor, 1);
   }

   vec3 irradiance = vec3(0, 0, 0);
   vec3 specular = vec3(0, 0, 0);

   // Radiance (Specular)
   float lod = roughnessToMipLevel(surface.roughness, cubeMips);

   if(showSpec == 1)
   {
      lod = 0;
   }

   for (i = 0; i < numProbes; i++)
   {
      float contrib = contribution[i];
      if (contrib > 0.0f)
      {
         float cubemapIdx = inProbeConfigData[i].a;
         vec3 dir = boxProject(surface.P, surface.R, inWorldToObjArray[i], inRefScaleArray[i].xyz, inRefPosArray[i].xyz);

         irradiance += textureLod(irradianceCubemapAR, vec4(dir, cubemapIdx), 0).xyz * contrib;
         specular += textureLod(specularCubemapAR, vec4(dir, cubemapIdx), lod).xyz * contrib;
         alpha -= contrib;
      }
   }

   if(skylightCubemapIdx != -1 && alpha >= 0.001)
   {
      irradiance = mix(irradiance,textureLod(irradianceCubemapAR, vec4(surface.R, skylightCubemapIdx), 0).xyz,alpha);
      specular = mix(specular,textureLod(specularCubemapAR, vec4(surface.R, skylightCubemapIdx), lod).xyz,alpha);
   }

   if(showSpec == 1)
   {
      return vec4(specular, 0);
   }

   if(showDiff == 1)
   {
      return vec4(irradiance, 0);
   }

   //energy conservation
   vec3 F = FresnelSchlickRoughness(surface.NdotV, surface.f0, surface.roughness);
   vec3 kD = 1.0f - F;
   kD *= 1.0f - surface.metalness;

   vec2 envBRDF = textureLod(BRDFTexture, vec2(surface.NdotV, surface.roughness),0).rg;
   specular *= F * envBRDF.x + surface.f90 * envBRDF.y;
   irradiance *= kD * surface.baseColor.rgb;

   //AO
   irradiance *= surface.ao;
   specular *= computeSpecOcclusion(surface.NdotV, surface.ao, surface.roughness);

   //http://marmosetco.tumblr.com/post/81245981087
   float horizonOcclusion = 1.3;
   float horizon = saturate( 1 + horizonOcclusion * dot(surface.R, surface.N));
   horizon *= horizon;

   return vec4((irradiance + specular* horizon) , 0);//alpha writes disabled
}
