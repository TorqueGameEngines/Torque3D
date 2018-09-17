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
TORQUE_UNIFORM_SAMPLERCUBE(cubeMap, 2);
TORQUE_UNIFORM_SAMPLERCUBE(irradianceCubemap, 3);
TORQUE_UNIFORM_SAMPLER2D(BRDFTexture, 4);


uniform float4 rtParams0;

uniform float4 vsFarPlane;

uniform float4x4 invViewMat;

uniform float3 eyePosWorld;

//SHTerms
/*uniform float4 SHTerms0;
uniform float4 SHTerms1;
uniform float4 SHTerms2;
uniform float4 SHTerms3;
uniform float4 SHTerms4;
uniform float4 SHTerms5;
uniform float4 SHTerms6;
uniform float4 SHTerms7;
uniform float4 SHTerms8;

uniform float SHConsts0;
uniform float SHConsts1;
uniform float SHConsts2;
uniform float SHConsts3;
uniform float SHConsts4;

float4 decodeSH(float3 normal)
{
   float x = normal.x;
   float y = normal.y;
   float z = normal.z;

   float3 l00 = SHTerms0.rgb;

   float3 l10 = SHTerms1.rgb;
   float3 l11 = SHTerms2.rgb;
   float3 l12 = SHTerms3.rgb;

   float3 l20 = SHTerms4.rgb;
   float3 l21 = SHTerms5.rgb;
   float3 l22 = SHTerms6.rgb;
   float3 l23 = SHTerms7.rgb;
   float3 l24 = SHTerms8.rgb;

   float3 result = (
         l00 * SHConsts0 +

         l12 * SHConsts1 * x +
         l10 * SHConsts1 * y +
         l11 * SHConsts1 * z +

         l20 * SHConsts2 * x*y +
         l21 * SHConsts2 * y*z +
         l22 * SHConsts3 * (3.0*z*z - 1.0) +
         l23 * SHConsts2 * x*z +
         l24 * SHConsts4 * (x*x - y*y)
      );

    return float4(result,1);
}*/

float3 iblSpecular(float3 v, float3 n, float roughness)
{
	float3 R = reflect(v, n); 
	const float MAX_REFLECTION_LOD = 4.0;
	float3 prefilteredColor = TORQUE_TEXCUBELOD(cubeMap, float4(R, roughness * MAX_REFLECTION_LOD)).rgb;
	float2 envBRDF  = TORQUE_TEX2D(BRDFTexture, float2(max(dot(n, v), 0.0), roughness)).rg;
	return prefilteredColor * (envBRDF.x + envBRDF.y);
   //return prefilteredColor;
 }

struct PS_OUTPUT
{
    float4 diffuse: TORQUE_TARGET0;
    float4 spec: TORQUE_TARGET1;
};

PS_OUTPUT main( ConvexConnectP IN )
{ 
    PS_OUTPUT Output = (PS_OUTPUT)0;

    // Compute scene UV
    float3 ssPos = IN.ssPos.xyz / IN.ssPos.w; 

    //float4 hardCodedRTParams0 = float4(0,0.0277777780,1,0.972222209);
    float2 uvScene = getUVFromSSPos( ssPos, rtParams0 );

    // Matinfo flags
    float4 matInfo = TORQUE_TEX2D( matInfoBuffer, uvScene ); 

    // Sample/unpack the normal/z data
    float4 deferredSample = TORQUE_DEFERRED_UNCONDITION( deferredBuffer, uvScene );
    float3 normal = deferredSample.rgb;
    float depth = deferredSample.a;
    if (depth>0.9999)
        return Output; 

    // Need world-space normal.
    float3 wsNormal = mul(float4(normal, 1), invViewMat).rgb;

    float3 eyeRay = getDistanceVectorToPlane( -vsFarPlane.w, IN.vsEyeDir.xyz, vsFarPlane );

    float3 wsEyeRay = mul(float4(eyeRay, 1), invViewMat).rgb;

    // Use eye ray to get ws pos
    float3 worldPos = float3(eyePosWorld + wsEyeRay * depth);

    float3 reflectionVec = reflect(IN.wsEyeDir, float4(wsNormal,1)).xyz;

    float roughness = 1 - matInfo.b;

    float3 v = normalize(eyePosWorld - worldPos);

    float3 irradiance = TORQUE_TEXCUBE(irradianceCubemap, wsNormal).rgb;

    float3 specular = iblSpecular(wsEyeRay, wsNormal, roughness);


    Output.diffuse = float4(irradiance.rgb, 1);
    Output.spec = float4(specular.rgb, 1);

    return Output;

}
