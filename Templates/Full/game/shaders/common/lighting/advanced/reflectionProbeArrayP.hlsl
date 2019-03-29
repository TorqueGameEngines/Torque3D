#include "../../postFx/postFx.hlsl"
#include "../../shaderModel.hlsl"
#include "../../shaderModelAutoGen.hlsl"
#include "../../lighting.hlsl"

TORQUE_UNIFORM_SAMPLER2D(deferredBuffer, 0);
TORQUE_UNIFORM_SAMPLER2D(colorBuffer, 1);
TORQUE_UNIFORM_SAMPLER2D(matInfoBuffer, 2);
TORQUE_UNIFORM_SAMPLER2D(BRDFTexture, 3);

uniform float4 rtParams0;
uniform float4 vsFarPlane;
uniform float4x4 cameraToWorld;
uniform float3 eyePosWorld;

//cubemap arrays require all the same size. so shared mips# value
uniform float cubeMips;
#define MAX_PROBES 50

uniform float numProbes;
TORQUE_UNIFORM_SAMPLERCUBEARRAY(cubeMapAR, 4);
TORQUE_UNIFORM_SAMPLERCUBEARRAY(irradianceCubemapAR, 5);

uniform float4    inProbePosArray[MAX_PROBES];
uniform float4    inRefPosArray[MAX_PROBES];
uniform float4x4  worldToObjArray[MAX_PROBES];
uniform float4    bbMinArray[MAX_PROBES];
uniform float4    bbMaxArray[MAX_PROBES];
uniform float4    probeConfigData[MAX_PROBES];   //r,g,b/mode,radius,atten

#if DEBUGVIZ_CONTRIB
uniform float4    probeContribColors[MAX_PROBES];
#endif

TORQUE_UNIFORM_SAMPLERCUBE(skylightPrefilterMap, 6);
TORQUE_UNIFORM_SAMPLERCUBE(skylightIrradMap, 7);
uniform float hasSkylight;

//Probe IBL stuff
float defineSphereSpaceInfluence(Surface surface, int ID)
{
   float3 L = inProbePosArray[ID].xyz.xyz - surface.P;
   float contribution = 1.0 - length(L) / probeConfigData[ID].g;
   return contribution;
}

float getDistBoxToPoint(float3 pt, float3 extents)
{
   float3 d = max(max(-extents - pt, 0), pt - extents);
   return max(max(d.x, d.y), d.z);
}

float defineBoxSpaceInfluence(Surface surface, int ID)
{
   float3 surfPosLS = mul(worldToObjArray[ID], float4(surface.P, 1.0)).xyz;
   float atten = 1.0-probeConfigData[ID].b;
   float baseVal = 0.25;
   float dist = getDistBoxToPoint(surfPosLS,float3(baseVal,baseVal,baseVal));
   return saturate(smoothstep(baseVal+0.0001,atten*baseVal,dist));
}

// Box Projected IBL Lighting
// Based on: http://www.gamedev.net/topic/568829-box-projected-cubemap-environment-mapping/
// and https://seblagarde.wordpress.com/2012/09/29/image-based-lighting-approaches-and-parallax-corrected-cubemap/
float3 boxProject(Surface surface, int ID)
{
   float3 RayLS = mul(worldToObjArray[ID], float4(surface.R, 0.0)).xyz;
   float3 PositionLS = mul(worldToObjArray[ID], float4(surface.P, 1.0)).xyz;

   float3 unit = bbMaxArray[ID].xyz - bbMinArray[ID].xyz;
   float3 plane1vec = (unit / 2 - PositionLS) / RayLS;
   float3 plane2vec = (-unit / 2 - PositionLS) / RayLS;
   float3 furthestPlane = max(plane1vec, plane2vec);
   float dist = min(min(furthestPlane.x, furthestPlane.y), furthestPlane.z);
   float3 posonbox = surface.P + surface.R * dist;

   return posonbox - inRefPosArray[ID].xyz;
}

float3 iblBoxDiffuse(Surface surface, int ID)
{
   float3 dir = boxProject(surface, ID);

   float3 color = TORQUE_TEXCUBEARRAYLOD(irradianceCubemapAR, dir, probeConfigData[ID].a, 0).xyz;
   return color;
}

float3 iblBoxSpecular(Surface surface, int ID)
{
   // BRDF
   //float2 brdf = TORQUE_TEX2DLOD(BRDFTexture, float4(surface.roughness, surface.NdotV, 0.0, 0.0)).xy;

   float3 dir = boxProject(surface, ID);

   // Radiance (Specular)
#if DEBUGVIZ_SPECCUBEMAP == 0
   float lod = surface.roughness*cubeMips;
#elif DEBUGVIZ_SPECCUBEMAP == 1
   float lod = 0;
#endif

   float3 color = TORQUE_TEXCUBEARRAYLOD(cubeMapAR, dir, probeConfigData[ID].a, lod).xyz;
   return color;
}

float3 iblSkylightDiffuse(Surface surface)
{
   float3 color = TORQUE_TEXCUBELOD(skylightIrradMap, float4(surface.R, 0)).xyz;
   return color;
}

float3 iblSkylightSpecular(Surface surface)
{
   // BRDF
   //float2 brdf = TORQUE_TEX2DLOD(BRDFTexture, float4(surface.roughness, surface.NdotV, 0.0, 0.0)).xy;

   // Radiance (Specular)
#if DEBUGVIZ_SPECCUBEMAP == 0
   float lod = surface.roughness*cubeMips;
#elif DEBUGVIZ_SPECCUBEMAP == 1
   float lod = 0;
#endif

   float3 color = TORQUE_TEXCUBELOD(skylightPrefilterMap, float4(surface.R, lod)).xyz;
   return color;
}

float4 main(PFXVertToPix IN) : SV_TARGET
{
   //unpack normal and linear depth 
   float4 normDepth = TORQUE_DEFERRED_UNCONDITION(deferredBuffer, IN.uv0.xy);

   //create surface
   Surface surface = createSurface(normDepth, TORQUE_SAMPLER2D_MAKEARG(colorBuffer),TORQUE_SAMPLER2D_MAKEARG(matInfoBuffer),
      IN.uv0.xy, eyePosWorld, IN.wsEyeRay, cameraToWorld);

   //early out if emissive
   if (getFlag(surface.matFlag, 0))
   {
      discard;
   }

   float alpha = 1;

   int i = 0;
   float blendFactor[MAX_PROBES];
   float blendSum = 0;
   float blendFacSum = 0;
   float invBlendSum = 0;
   float probehits = 0;
   //Set up our struct data
   float contribution[MAX_PROBES];
   if (alpha > 0)
   {
      //Process prooooobes
      for (i = 0; i < numProbes; ++i)
      {
         contribution[i] = 0;

         if (probeConfigData[i].r == 0) //box
         {
            contribution[i] = defineBoxSpaceInfluence(surface, i);
            if (contribution[i]>0.0)
               probehits++;
         }
         else if (probeConfigData[i].r == 1) //sphere
         {
            contribution[i] = defineSphereSpaceInfluence(surface, i);
            if (contribution[i]>0.0)
               probehits++;
         }

         contribution[i] = max(contribution[i],0);

         blendSum += contribution[i];
         invBlendSum += (1.0f - contribution[i]);
      }
      // Weight0 = normalized NDF, inverted to have 1 at center, 0 at boundary.
	   // And as we invert, we need to divide by Num-1 to stay normalized (else sum is > 1). 
	   // respect constraint B.
	   // Weight1 = normalized inverted NDF, so we have 1 at center, 0 at boundary
	   // and respect constraint A.
      
      if (probehits>1.0)
	   {
         for (i = 0; i < numProbes; i++)
         {
            blendFactor[i] = ((contribution[i] / blendSum)) / probehits;
	         blendFactor[i] *= ((contribution[i]) / invBlendSum);
            blendFactor[i] = saturate(blendFactor[i]);
	         blendFacSum += blendFactor[i];
	      }

      // Normalize blendVal
#if DEBUGVIZ_ATTENUATION == 0 //this can likely be removed when we fix the above normalization behavior
      if (blendFacSum == 0.0f) // Possible with custom weight
      {
         blendFacSum = 1.0f;
      }
#endif

		  float invBlendSumWeighted = 1.0f / blendFacSum;
		  for (i = 0; i < numProbes; ++i)
		  {
		     blendFactor[i] *= invBlendSumWeighted;
		     contribution[i] *= blendFactor[i];
           alpha -= contribution[i];
		  }
   }
   else
      alpha -= blendSum;
      
#if DEBUGVIZ_ATTENUATION == 1
      float attenVis = 0;
		for (i = 0; i < numProbes; ++i)
		{
		  attenVis += contribution[i];
		}

		//return float4(attenVis, attenVis, attenVis, 1);
      return float4(blendSum, blendSum, blendSum, 1);
#endif

#if DEBUGVIZ_CONTRIB == 1
      float3 finalContribColor = float3(0, 0, 0);
      for (i = 0; i < numProbes; ++i)
      {
         finalContribColor += contribution[i] *probeContribColors[i].rgb;
      }

      return float4(finalContribColor, 1);
#endif
   }

#if DEBUGVIZ_SPECCUBEMAP == 0 && DEBUGVIZ_DIFFCUBEMAP == 0

   float3 irradiance = float3(0, 0, 0);
   float3 specular = float3(0, 0, 0);

   float contrib = 0;
   for (i = 0; i < numProbes; ++i)
   {
      if (contribution[i] == 0)
         continue;

      irradiance += iblBoxDiffuse(surface, i) * contribution[i];
      specular += iblBoxSpecular(surface, i) * contribution[i];
      contrib +=contribution[i];
   }
   
   if (hasSkylight && alpha != 0)
   {
      irradiance = lerp(irradiance, iblSkylightDiffuse(surface), alpha);
      specular = lerp(specular, iblSkylightSpecular(surface), alpha);
   }

   float3 F = FresnelSchlickRoughness(surface.NdotV, surface.f0, surface.roughness);

   //energy conservation
   float3 kD = 1.0.xxx - F;
   kD *= 1.0 - surface.metalness;

   //apply brdf
   //Do it once to save on texture samples
   float2 brdf = TORQUE_TEX2DLOD(BRDFTexture, float4(surface.roughness, surface.NdotV, 0.0, 0.0)).xy;
   specular *= (brdf.x + brdf.y)* F;

   //final diffuse color
   float3 diffuse = kD * irradiance * surface.baseColor.rgb;
   float4 finalColor = float4(diffuse + specular * surface.ao, 1.0);

   return finalColor;

#elif DEBUGVIZ_SPECCUBEMAP == 1 && DEBUGVIZ_DIFFCUBEMAP == 0

   float3 cubeColor = float3(0, 0, 0);
   for (i = 0; i < numProbes; ++i)
   {
      if (probeConfigData[i].r == 2) //skylight
      {
         cubeColor += iblSkylightSpecular(surface, i);
      }
      else
      {
         cubeColor += iblBoxSpecular(surface, i);
      }
   }

   return float4(cubeColor, 1);

#elif DEBUGVIZ_DIFFCUBEMAP == 1

   float3 cubeColor = float3(0, 0, 0);
   for (i = 0; i < numProbes; ++i)
   {
      if (probeConfigData[i].r == 2) //skylight
      {
         cubeColor += iblSkylightDiffuse(surface);
      }
      else
      {
         cubeColor += iblBoxDiffuse(surface);
      }
   }

   return float4(cubeColor, 1);

#endif
}
