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
//TORQUE_UNIFORM_SAMPLERCUBE(cubeMapAR, 4);
//TORQUE_UNIFORM_SAMPLERCUBE(irradianceCubemapAR, 5);
uniform float4    inProbePosArray[MAX_PROBES];
uniform float4x4  worldToObjArray[MAX_PROBES];
uniform float4    bbMinArray[MAX_PROBES];
uniform float4    bbMaxArray[MAX_PROBES];
uniform float4     probeConfigData[MAX_PROBES];   //r,g,b/mode,radius,atten

#if DEBUGVIZ_CONTRIB
uniform float4    probeContribColors[MAX_PROBES];
#endif

// Box Projected IBL Lighting
// Based on: http://www.gamedev.net/topic/568829-box-projected-cubemap-environment-mapping/
// and https://seblagarde.wordpress.com/2012/09/29/image-based-lighting-approaches-and-parallax-corrected-cubemap/
float3 boxProject(float3 wsPosition, float3 wsEyeRay, float3 reflectDir, float3 boxWSPos, float3 boxMin, float3 boxMax)
{ 
   //float3 rayLS = mul(worldToObjArray[id], float4(wsEyeRay, 1.0)).xyz;
   //float3 reflCameraLS = mul(worldToObjArray[id], float4(reflectDir), 1.0)).xyz;

   float3 nrdir = reflectDir;
	float3 offset = wsPosition;
   float3 plane1vec = (boxMax - offset) / nrdir;
   float3 plane2vec = (boxMin - offset) / nrdir;
	
	float3 furthestPlane = max(plane1vec, plane2vec);
	float dist = min(min(furthestPlane.x, furthestPlane.y), furthestPlane.z);
   float3 posonbox = offset + nrdir * dist;

   return posonbox - boxWSPos;
}

float3 iblBoxDiffuse( Surface surface, int id)
{
   float3 cubeN = boxProject(surface.P, surface.V, surface.R, inProbePosArray[id].xyz, bbMinArray[id].xyz, bbMaxArray[id].xyz);
   cubeN.z *=-1;
   return TORQUE_TEXCUBEARRAYLOD(irradianceCubemapAR,cubeN,id,0).xyz;
}

float3 iblBoxSpecular(Surface surface, TORQUE_SAMPLER2D(brdfTexture), int id)
{
    // BRDF
   float2 brdf = TORQUE_TEX2DLOD(brdfTexture, float4(surface.roughness, surface.NdotV,0.0,0.0)).xy;

    // Radiance (Specular)
#if DEBUGVIZ_SPECCUBEMAP == 0
   float lod = surface.roughness*cubeMips;
#elif DEBUGVIZ_SPECCUBEMAP == 1
   float lod = 0;
#endif

   float3 cubeR = boxProject(surface.P, surface.V, surface.R, inProbePosArray[id].xyz, bbMinArray[id].xyz, bbMaxArray[id].xyz);

   float3 radiance = TORQUE_TEXCUBEARRAYLOD(cubeMapAR,cubeR,id,lod).xyz * (brdf.x + brdf.y);
    
   return radiance;
}

float defineBoxSpaceInfluence(Surface surface, int id)
{
    float3 surfPosLS = mul( worldToObjArray[id], float4(surface.P,1.0)).xyz;

    float3 boxMinLS = inProbePosArray[id].xyz-(float3(1,1,1)*probeConfigData[id].g);
    float3 boxMaxLS = inProbePosArray[id].xyz+(float3(1,1,1)*probeConfigData[id].g);

    float boxOuterRange = length(boxMaxLS - boxMinLS);
    float boxInnerRange = boxOuterRange / probeConfigData[id].b;

    float3 localDir = float3(abs(surfPosLS.x), abs(surfPosLS.y), abs(surfPosLS.z));
    localDir = (localDir - boxInnerRange) / (boxOuterRange - boxInnerRange);

    return max(localDir.x, max(localDir.y, localDir.z)) * -1;
}

float4 main( PFXVertToPix IN ) : SV_TARGET
{
   //unpack normal and linear depth 
   float4 normDepth = TORQUE_DEFERRED_UNCONDITION(deferredBuffer, IN.uv0.xy);

   //create surface
   Surface surface = createSurface( normDepth, TORQUE_SAMPLER2D_MAKEARG(colorBuffer),TORQUE_SAMPLER2D_MAKEARG(matInfoBuffer),
                                    IN.uv0.xy, eyePosWorld, IN.wsEyeRay, cameraToWorld);

   //early out if emissive
   if (getFlag(surface.matFlag, 0))
   {   
      discard;
   }     

   int i = 0;

   float blendVal[MAX_PROBES];
   float blendSum = 0;
   float invBlendSum = 0;

   for (i = 0; i < numProbes; i++)
   {
      if (probeConfigData[i].r)
      {
         float3 L = inProbePosArray[i].xyz - surface.P;
         blendVal[i] = 1.0 - length(L) / probeConfigData[i].g;
         blendVal[i] = max(0, blendVal[i]);
      }
      else
      {
         blendVal[i] = defineBoxSpaceInfluence(surface, i);
         blendVal[i] = max(0, blendVal[i]);
      }
      blendSum += blendVal[i];
      invBlendSum += (1.0f - blendVal[i]);
   }

   // Weight0 = normalized NDF, inverted to have 1 at center, 0 at boundary.
   // And as we invert, we need to divide by Num-1 to stay normalized (else sum is > 1). 
   // respect constraint B.
   // Weight1 = normalized inverted NDF, so we have 1 at center, 0 at boundary
   // and respect constraint A.

   //This is what's cross-contaminating between probe's influence areas. 
   //Need to review this logic before we utilize it again
   /*for (i = 0; i < numProbes; i++)
   {
      blendVal[i] = (1.0f - (blendVal[i] / blendSum)) / (numProbes - 1);
      blendVal[i] *= ((1.0f - blendVal[i]) / invBlendSum);
      blendSum += blendVal[i];
   }*/

   // Normalize blendVal
#if DEBUGVIZ_ATTENUATION == 0 //this can likely be removed when we fix the above normalization behavior
   if (blendSum == 0.0f) // Possible with custom weight
   {
      blendSum = 1.0f;
   }
#endif

   float invBlendSumWeighted = 1.0f / blendSum;
   for (i = 0; i < numProbes; ++i)
   {
      blendVal[i] *= invBlendSumWeighted;
   }

   //return float4(blendVal[0], blendVal[0], blendVal[0], 1);
   
#if DEBUGVIZ_ATTENUATION == 1
   return float4(blendSum, blendSum, blendSum, 1);
#endif

#if DEBUGVIZ_CONTRIB == 1

   float3 finalContribColor = float3(0, 0, 0);
   for (i = 0; i < numProbes; ++i)
   {
      if (blendVal[i] == 0)
         continue;

      finalContribColor += blendVal[i] * probeContribColors[i].rgb;
   }

   return float4(finalContribColor, 1);
#endif

#if DEBUGVIZ_SPECCUBEMAP == 0 && DEBUGVIZ_DIFFCUBEMAP == 0
    
   float3 irradiance = float3(0,0,0);
   float3 specular = float3(0,0,0);
   float3 F = FresnelSchlickRoughness(surface.NdotV, surface.f0, surface.roughness);
   
   //energy conservation
   float3 kD = 1.0.xxx - F;
   kD *= 1.0 - surface.metalness;
   for (i = 0; i < numProbes; ++i)
   {
      if (blendVal[i] == 0)
         continue;

      irradiance += blendVal[i]*iblBoxDiffuse(surface, i);
      
      specular += blendVal[i]*F*iblBoxSpecular(surface, TORQUE_SAMPLER2D_MAKEARG(BRDFTexture),i);
   }

   //final diffuse color
   float3 diffuse = kD * irradiance * surface.baseColor.rgb;
	float4 finalColor = float4(diffuse + specular * surface.ao, blendSum);

    return finalColor;

#elif DEBUGVIZ_SPECCUBEMAP == 1 && DEBUGVIZ_DIFFCUBEMAP == 0
   float3 cubeColor = float3(0, 0, 0);
   for (i = 0; i < numProbes; ++i)
   {
      cubeColor += blendVal[i] * iblBoxSpecular(surface, TORQUE_SAMPLER2D_MAKEARG(BRDFTexture), i);
   }

   return float4(cubeColor,1);
#elif DEBUGVIZ_DIFFCUBEMAP == 1
   float3 cubeColor = float3(0, 0, 0);
   for (i = 0; i < numProbes; ++i)
   {
      cubeColor += blendVal[i] * iblBoxDiffuse(surface, i);
   }

   return float4(cubeColor, 1);
#endif
}
