#include "shaders/common/postFx/postFx.hlsl"
#include "../../torque.hlsl"

TORQUE_UNIFORM_SAMPLER2D(backBuffer, 0);

float4 main(PFXVertToPix IN) : TORQUE_TARGET0
{
   float4 base = TORQUE_TEX2D(backBuffer, IN.uv0);
   
   base.rgb = (base.r + base.g + base.b) / 3.0f;
   
   return base;
}