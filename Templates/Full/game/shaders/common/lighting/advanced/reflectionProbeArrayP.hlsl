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
uniform float4     useSphereMode[MAX_PROBES];
uniform float4     radius[MAX_PROBES];
uniform float4    attenuation[MAX_PROBES];

// Box Projected IBL Lighting
// Based on: http://www.gamedev.net/topic/568829-box-projected-cubemap-environment-mapping/
// and https://seblagarde.wordpress.com/2012/09/29/image-based-lighting-approaches-and-parallax-corrected-cubemap/
float3 boxProject(float3 wsPosition, float3 reflectDir, float3 boxWSPos, float3 boxMin, float3 boxMax)
{ 
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
   float3 cubeN = boxProject(surface.P, surface.N, inProbePosArray[id].xyz, bbMinArray[id].xyz, bbMaxArray[id].xyz);
   cubeN.z *=-1;
   return TORQUE_TEXCUBEARRAYLOD(irradianceCubemapAR,cubeN,id,0).xyz;
   //return TORQUE_TEXCUBELOD(irradianceCubemapAR,float4(cubeN,0)).xyz;
}

float3 iblBoxSpecular(Surface surface, float3 surfToEye, TORQUE_SAMPLER2D(brdfTexture), int id)
{
   float ndotv = clamp(dot(surface.N, surfToEye), 0.0, 1.0);

    // BRDF
   float2 brdf = TORQUE_TEX2DLOD(brdfTexture, float4(surface.roughness, ndotv,0.0,0.0)).xy;

    // Radiance (Specular)
   float lod = surface.roughness*cubeMips;
   float3 r = reflect(surfToEye, surface.N);
   float3 cubeR = normalize(r);
   cubeR = boxProject(surface.P, surface.N, inProbePosArray[id].xyz, bbMinArray[id].xyz, bbMaxArray[id].xyz);
	
   float3 radiance = TORQUE_TEXCUBEARRAYLOD(cubeMapAR,cubeR,id,lod).xyz * (brdf.x + brdf.y);
   //float3 radiance = TORQUE_TEXCUBELOD(cubeMapAR,float4(cubeR,lod)).xyz * (brdf.x + brdf.y);
    
   return radiance;
}

float defineBoxSpaceInfluence(Surface surface, int id)
{
    float tempAttenVal = 3.5; //replace with per probe atten
    float3 surfPosLS = mul( worldToObjArray[id], float4(surface.P,1.0)).xyz;

    float3 boxMinLS = inProbePosArray[id].xyz-(float3(1,1,1)*radius[0].x);
    float3 boxMaxLS = inProbePosArray[id].xyz+(float3(1,1,1)*radius[0].x);

    float boxOuterRange = length(boxMaxLS - boxMinLS);
    float boxInnerRange = boxOuterRange / tempAttenVal;

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
	
   float blendVal[MAX_PROBES];
   float3 surfToEye = normalize(surface.P - eyePosWorld);

   int i = 0;
   float blendSum = 0;
   float invBlendSum = 0;
      
   for(i=0; i < numProbes; i++)
   {
        float3 probeWS = inProbePosArray[i].xyz;
        float3 L = probeWS - surface.P;
      
        /*if(useSphereMode[i])
        {
            float3 L = inProbePosArray[i].xyz - surface.P;
            blendVal[i] = 1.0-length(L)/radius[i];
            blendVal[i] = max(0,blendVal[i]);
        }
        else
        {*/
            blendVal[i] = defineBoxSpaceInfluence(surface, i);
            blendVal[i] = max(0,blendVal[i]);		
        //}
		blendSum += blendVal[i];
        invBlendSum +=(1.0f - blendVal[i]);
   }
	
   // Weight0 = normalized NDF, inverted to have 1 at center, 0 at boundary.
   // And as we invert, we need to divide by Num-1 to stay normalized (else sum is > 1). 
   // respect constraint B.
   // Weight1 = normalized inverted NDF, so we have 1 at center, 0 at boundary
   // and respect constraint A.
   for(i=0; i < numProbes; i++)
   {
      blendVal[i] = (1.0f - ( blendVal[i] / blendSum)) / (numProbes - 1);
      blendVal[i] *= ((1.0f - blendVal[i]) / invBlendSum);
      blendSum += blendVal[i];
   }

   float finalSum = blendSum;

    //return TORQUE_TEX2D(colorBuffer, IN.uv0.xy);
    //return float4(surface.N,1);
   //return float4(1,1,1, 1);
   //return float4(finalSum,finalSum,finalSum, 1);

    // Normalize blendVal
   if (blendSum == 0.0f) // Possible with custom weight
   {
      //blendSum = 1.0f;
   }

   float invBlendSumWeighted = 1.0f / blendSum;
   for (i = 0; i < numProbes; ++i)
   {
      blendVal[i] *= invBlendSumWeighted;
   }
    
   float3 irradiance = float3(0,0,0);
   float3 specular = float3(0,0,0);
   float3 F = FresnelSchlickRoughness(surface.NdotV, surface.f0, surface.roughness);
   
   //energy conservation
   float3 kD = 1.0.xxx - F;
   kD *= 1.0 - surface.metalness;
   for (i = 0; i < numProbes; ++i)
   {
      irradiance += blendVal[i]*iblBoxDiffuse(surface,i);
      
      specular += blendVal[i]*F*iblBoxSpecular(surface, surfToEye, TORQUE_SAMPLER2D_MAKEARG(BRDFTexture),i);
   }
   //final diffuse color
   float3 diffuse = kD * irradiance * surface.baseColor.rgb;
	float4 finalColor = float4(diffuse + specular * surface.ao, 1);

    return finalColor;
}
