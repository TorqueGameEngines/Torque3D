#include "../../shaderModelAutoGen.hlsl"

#include "farFrustumQuad.hlsl"
#include "../../lighting.hlsl"
#include "../../torque.hlsl"

struct ConvexConnectP
{
   float4 pos : TORQUE_POSITION;
   float4 wsEyeDir : TEXCOORD0;
   float4 ssPos : TEXCOORD1;
   float4 vsEyeDir : TEXCOORD2;
};

TORQUE_UNIFORM_SAMPLER2D(deferredBuffer, 0);
TORQUE_UNIFORM_SAMPLER2D(matInfoBuffer, 1);
TORQUE_UNIFORM_SAMPLER2D(colorBuffer, 2);
TORQUE_UNIFORM_SAMPLERCUBE(cubeMap, 3);
TORQUE_UNIFORM_SAMPLERCUBE(irradianceCubemap, 4);
TORQUE_UNIFORM_SAMPLER2D(BRDFTexture, 5);

uniform float4 rtParams0;
uniform float4 vsFarPlane;
uniform float4x4 cameraToWorld;
uniform float3 eyePosWorld;

float3 iblSpecular(in Surface surface, float3 F)
{
	const float MAX_REFLECTION_LOD = 4.0;
	float3 prefilteredColor = TORQUE_TEXCUBELOD(cubeMap, float4(surface.R, surface.roughness * MAX_REFLECTION_LOD)).rgb;
	float2 envBRDF  = TORQUE_TEX2D(BRDFTexture, float2(surface.NdotV, surface.roughness)).rg;
	return prefilteredColor * (F * envBRDF.x + envBRDF.y);
}

float4 main( ConvexConnectP IN ) : SV_TARGET
{ 
   // Compute scene UV
   float3 ssPos = IN.ssPos.xyz / IN.ssPos.w; 
   float2 uvScene = getUVFromSSPos( ssPos, rtParams0 );

   //eye ray WS/LS
   float3 vsEyeRay = getDistanceVectorToPlane( -vsFarPlane.w, IN.vsEyeDir.xyz, vsFarPlane );
   float3 wsEyeRay = mul(cameraToWorld, float4(vsEyeRay, 0)).xyz;
   
   //unpack normal and linear depth 
   float4 normDepth = TORQUE_DEFERRED_UNCONDITION(deferredBuffer, uvScene);
   
   //create surface
   Surface surface = createSurface( normDepth, TORQUE_SAMPLER2D_MAKEARG(colorBuffer),TORQUE_SAMPLER2D_MAKEARG(matInfoBuffer),
                                    uvScene, eyePosWorld, wsEyeRay, cameraToWorld);

   float3 F = FresnelSchlickRoughness(surface.NdotV, surface.f0, surface.roughness);
   float3 irradiance = TORQUE_TEXCUBELOD(irradianceCubemap, float4(surface.N,0)).rgb;
   float3 specular = iblSpecular(surface, F);
   //energy conservation
	float3 kD = 1.0.xxx - F;
	kD *= 1.0 - surface.metalness;
   //final diffuse color
   float3 diffuse = kD * irradiance * surface.baseColor.rgb;

   return float4(diffuse + specular * surface.ao, 0);
}
