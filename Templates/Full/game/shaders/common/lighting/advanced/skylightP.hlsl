#include "../../shaderModelAutoGen.hlsl"

#include "farFrustumQuad.hlsl"
#include "lightingUtils.hlsl"
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

float3 iblSpecular(float3 v, float3 n, float roughness)
{
	float3 R = reflect(v, n); 
	const float MAX_REFLECTION_LOD = 4.0;
	float3 prefilteredColor = TORQUE_TEXCUBELOD(cubeMap, float4(R, roughness * MAX_REFLECTION_LOD)).rgb;
	float2 envBRDF  = TORQUE_TEX2D(BRDFTexture, float2(max(dot(n, v), 0.0), roughness)).rg;
	return prefilteredColor * (envBRDF.x + envBRDF.y);
}

LightTargetOutput main( ConvexConnectP IN )
{ 
   LightTargetOutput Output = (LightTargetOutput)0;

   // Compute scene UV
   float3 ssPos = IN.ssPos.xyz / IN.ssPos.w; 
   float2 uvScene = getUVFromSSPos( ssPos, rtParams0 );

   //eye ray WS/LS
   float3 vsEyeRay = getDistanceVectorToPlane( -vsFarPlane.w, IN.vsEyeDir.xyz, vsFarPlane );
   float3 wsEyeRay = mul(cameraToWorld, float4(vsEyeRay, 0)).xyz;
   
   //sky and editor background check
   float4 normDepth = UnpackDepthNormal(TORQUE_SAMPLER2D_MAKEARG(deferredBuffer), uvScene);
   if (normDepth.a>0.9999)
      return Output;
   
   //create surface
   Surface surface = CreateSurface( normDepth, TORQUE_SAMPLER2D_MAKEARG(colorBuffer),TORQUE_SAMPLER2D_MAKEARG(matInfoBuffer),
                                    uvScene, eyePosWorld, wsEyeRay, cameraToWorld);

   float3 diffuse = TORQUE_TEXCUBELOD(irradianceCubemap, float4(surface.N,0)).rgb;
   float3 specular = iblSpecular(wsEyeRay, surface.N, surface.roughness);

	float blendVal = 0.0001;// ?????

   Output.diffuse = float4(diffuse, blendVal);
   Output.spec = float4(specular, blendVal);
   return Output;

}
