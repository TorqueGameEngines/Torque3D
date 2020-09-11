#include "core/rendering/shaders/postFX/postFx.hlsl"
#include "core/rendering/shaders/torque.hlsl"

TORQUE_UNIFORM_SAMPLER2D(inputTex, 0);

uniform float sharpness;
uniform float2 targetSize;

float4 main( PFXVertToPix IN ) : TORQUE_TARGET0
{
   float2 step = 1.0 / targetSize.xy;

   float3 texA = TORQUE_TEX2D( inputTex, IN.uv0 + float2(-step.x, -step.y) * 1.5 ).rgb;
   float3 texB = TORQUE_TEX2D( inputTex, IN.uv0 + float2( step.x, -step.y) * 1.5 ).rgb;
   float3 texC = TORQUE_TEX2D( inputTex, IN.uv0 + float2(-step.x,  step.y) * 1.5 ).rgb;
   float3 texD = TORQUE_TEX2D( inputTex, IN.uv0 + float2( step.x,  step.y) * 1.5 ).rgb;

   float3 around = 0.25 * (texA + texB + texC + texD);
   float3 center  = TORQUE_TEX2D( inputTex, IN.uv0 ).rgb;

   float3 col = center + (center - around) * sharpness;

   return hdrEncode( float4(col,1.0) );
}
