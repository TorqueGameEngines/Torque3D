#include "shaders/common/postFx/postFx.hlsl"
#include "shadergen:/autogenConditioners.h"

TORQUE_UNIFORM_SAMPLER2D(backBuffer, 0);
uniform float redLevel;
uniform float greenLevel;
uniform float blueLevel;

float4 main(PFXVertToPix IN) : TORQUE_TARGET0
{
   float4 base = TORQUE_TEX2D(backBuffer, IN.uv0);
   base.r *= redLevel;
   base.g *= greenLevel;
   base.b *= blueLevel;
   return base;
}