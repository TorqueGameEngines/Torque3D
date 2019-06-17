#include "shaders/common/postFx/postFx.hlsl"
#include "../../torque.hlsl"

TORQUE_UNIFORM_SAMPLER2D(backBuffer, 0);

float4 main(PFXVertToPix IN) : TORQUE_TARGET0
{
   float4 base = TORQUE_TEX2D(backBuffer, IN.uv0);
   base.a = 1.0f;
   
   base.rgb = (base.r + base.g + base.b) / 3.0f;
   
   if (base.r < 0.5)
      base.r = 0.0f;
   else
      base.r = 1.0f;
      
   base.gb = base.r;
   
   return base;
}