#include "shaders/common/postFx/postFx.hlsl"
#include "../../torque.hlsl"

TORQUE_UNIFORM_SAMPLER2D(backBuffer, 0);

float4 main(PFXVertToPix IN) : TORQUE_TARGET0
{
   float4 base = TORQUE_TEX2D(backBuffer, IN.uv0);
   base.a = 0;
   return float4(1.0f, 1.0f, 1.0f, 1.0f) - base;
}