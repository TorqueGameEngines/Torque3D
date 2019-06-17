#include "shaders/common/postFx/postFx.hlsl"
#include "shadergen:/autogenConditioners.h"

TORQUE_UNIFORM_SAMPLER2D(backBuffer, 0);
uniform float radiusX;
uniform float radiusY;

float4 main(PFXVertToPix IN) : TORQUE_TARGET0
{
   float4 base = TORQUE_TEX2D(backBuffer, IN.uv0);
   float dist = distance(IN.uv0, float2(0.5,0.5));
   base.rgb *= smoothstep(radiusX, radiusY, dist);
   return base;
}