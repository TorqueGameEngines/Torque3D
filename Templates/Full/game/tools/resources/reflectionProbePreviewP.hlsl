#include "shaders/common/shaderModelAutoGen.hlsl"

#include "shaders/common/lighting/advanced/farFrustumQuad.hlsl"
#include "shaders/common/lighting/advanced/lightingUtils.hlsl"
#include "shaders/common/lighting.hlsl"
#include "shaders/common/torque.hlsl"

struct ConvexConnectP
{
   float4 pos : TORQUE_POSITION;
   float4 wsEyeDir : TEXCOORD0;
   float4 ssPos : TEXCOORD1;
   float4 vsEyeDir : TEXCOORD2;
};

TORQUE_UNIFORM_SAMPLER2D(deferredBuffer, 0);
TORQUE_UNIFORM_SAMPLERCUBE(cubeMap, 1);

uniform float4 rtParams0;

uniform float4x4 invViewMat;

float4 main( ConvexConnectP IN ) : TORQUE_TARGET0
{ 
    // Compute scene UV
    float3 ssPos = IN.ssPos.xyz / IN.ssPos.w;
    float2 uvScene = getUVFromSSPos( ssPos, rtParams0 );

    //float3 eyeRay = IN.vsEyeDir.xyz;

    // Sample/unpack the normal/z data
    float4 deferredSample = TORQUE_DEFERRED_UNCONDITION( deferredBuffer, uvScene );
    float3 normal = deferredSample.rgb;
    float depth = deferredSample.a;
    if (depth>0.9999)
        return float4(0,0,0,0);

    // Need world-space normal.
    float3 wsNormal = mul(float4(normal, 1), invViewMat).rgb;

    float3 reflectionVec = reflect(IN.wsEyeDir, float4(normalize(wsNormal),1)).rgb;

    float4 color = TORQUE_TEXCUBE(cubeMap, reflectionVec);

    //simple visibility testing
    //float4 color = float4(1,0,0,1);

    return float4(color.rgb, 1);
}
