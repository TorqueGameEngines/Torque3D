#include "shaders/common/postFx/postFx.hlsl"
#include "shadergen:/autogenConditioners.h"

uniform float accumTime;
TORQUE_UNIFORM_SAMPLER2D(backBuffer, 0);
uniform float intensity;

float4 main(PFXVertToPix IN) : TORQUE_TARGET0
{
   float2 coords = IN.uv0;
   float2 uv = IN.uv0;
   
   coords = (coords - 0.5) * 2.0;
   
   float coordDot = dot(coords, coords);
   
   float2 uvG = uv - TORQUE_TEX2D(backBuffer, IN.uv0).xy * intensity * coords * coordDot;
   
   float4 base = TORQUE_TEX2D(backBuffer, IN.uv0);
   
   base.g = TORQUE_TEX2D(backBuffer, uvG).g;
   
   return base;
}