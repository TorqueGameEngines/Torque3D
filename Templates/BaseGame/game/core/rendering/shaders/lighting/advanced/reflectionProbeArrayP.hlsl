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

uniform int numProbes;

TORQUE_UNIFORM_SAMPLERCUBEARRAY(specularCubemapAR, 4);
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

uniform float skylightCubemapIdx;

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
      return TORQUE_TEX2D(colorBuffer, IN.uv0.xy);
   }

   float alpha = 1;

#if SKYLIGHT_ONLY == 0
   int i = 0;
   float blendFactor[MAX_PROBES];
   float blendSum = 0;
   float blendFacSum = 0;
   float invBlendSum = 0;
   float probehits = 0;
   //Set up our struct data
   float contribution[MAX_PROBES];

   //if (alpha > 0)
   //{
      //Process prooooobes
      for (i = 0; i < numProbes; ++i)
      {
         contribution[i] = 0;

         if (probeConfigData[i].r == 0) //box
         {
            contribution[i] = defineBoxSpaceInfluence(surface.P, worldToObjArray[i], probeConfigData[i].b);
            if (contribution[i]>0.0)
               probehits++;
         }
         else if (probeConfigData[i].r == 1) //sphere
         {
            contribution[i] = defineSphereSpaceInfluence(surface.P, inProbePosArray[i].xyz, probeConfigData[i].g);
            if (contribution[i]>0.0)
               probehits++;
         }
         else
            continue;

         contribution[i] = max(contribution[i],0);

         blendSum += contribution[i];
         invBlendSum += (1.0f - contribution[i]);
      }
      // Weight0 = normalized NDF, inverted to have 1 at center, 0 at boundary.
	   // And as we invert, we need to divide by Num-1 to stay normalized (else sum is > 1). 
	   // respect constraint B.
	   // Weight1 = normalized inverted NDF, so we have 1 at center, 0 at boundary
	   // and respect constraint A.
      
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
               alpha -= contribution[i];
         }
      }
      else
         alpha -= blendSum;
      
#if DEBUGVIZ_ATTENUATION == 1
      float contribAlpha = 1;
      for (i = 0; i < numProbes; ++i)
      {
         contribAlpha -= contribution[i];
      }

      return float4(1 - contribAlpha, 1 - contribAlpha, 1 - contribAlpha, 1);
#endif

#if DEBUGVIZ_CONTRIB == 1
      float3 finalContribColor = float3(0, 0, 0);
      float contribAlpha = 1;
      for (i = 0; i < numProbes; ++i)
      {
         finalContribColor += contribution[i] *probeContribColors[i].rgb;
         contribAlpha -= contribution[i];
      }

      //Skylight coloration for anything not covered by probes above
      if(skylightCubemapIdx != -1)
         finalContribColor += float3(0.3, 0.3, 0.3) * contribAlpha;

      return float4(finalContribColor, 1);
#endif
   //}
#endif

   float3 irradiance = float3(0, 0, 0);
   float3 specular = float3(0, 0, 0);

   // Radiance (Specular)
#if DEBUGVIZ_SPECCUBEMAP == 0
   float lod = surface.roughness*cubeMips;
#elif DEBUGVIZ_SPECCUBEMAP == 1
   float lod = 0;
#endif

#if SKYLIGHT_ONLY == 0
   alpha = 1;
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
#endif

   if(skylightCubemapIdx != -1 && alpha >= 0.001)
   {
      irradiance += TORQUE_TEXCUBEARRAYLOD(irradianceCubemapAR, surface.R, skylightCubemapIdx, 0).xyz * alpha;
      specular += TORQUE_TEXCUBEARRAYLOD(specularCubemapAR, surface.R, skylightCubemapIdx, lod).xyz * alpha;
   }

#if DEBUGVIZ_SPECCUBEMAP == 1 && DEBUGVIZ_DIFFCUBEMAP == 0
   return float4(specular, 1);
#elif DEBUGVIZ_DIFFCUBEMAP == 1
   return float4(irradiance, 1);
#endif

   float3 F = FresnelSchlickRoughness(surface.NdotV, surface.f0, surface.roughness);

   //energy conservation
   float3 kD = 1.0.xxx - F;
   kD *= 1.0 - surface.metalness;

   //apply brdf
   //Do it once to save on texture samples
   float2 brdf = TORQUE_TEX2DLOD(BRDFTexture, float4(surface.roughness, 1.0-surface.NdotV, 0.0, 0.0)).xy;
   specular *= brdf.x * F + brdf.y;

   //final diffuse color
   float3 diffuse = kD * irradiance * surface.baseColor.rgb;
   float4 finalColor = float4(diffuse + specular * surface.ao, 1.0);

   return finalColor;
}
