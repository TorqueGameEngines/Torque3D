#include "shaders/common/postFx/postFx.hlsl"
#include "shadergen:/autogenConditioners.h"
#include "../../torque.hlsl"

TORQUE_UNIFORM_SAMPLER2D(backBuffer, 0);
uniform float DreamViewIntensity;

float4 main(PFXVertToPix IN) : TORQUE_TARGET0
{
   float4 base = TORQUE_TEX2D(backBuffer, IN.uv0);

   base += TORQUE_TEX2D(backBuffer, IN.uv0+(0.001 * DreamViewIntensity));
   base += TORQUE_TEX2D(backBuffer, IN.uv0+(0.003 * DreamViewIntensity));
   base += TORQUE_TEX2D(backBuffer, IN.uv0+(0.005 * DreamViewIntensity));
   base += TORQUE_TEX2D(backBuffer, IN.uv0+(0.007 * DreamViewIntensity));
   base += TORQUE_TEX2D(backBuffer, IN.uv0+(0.009 * DreamViewIntensity));
   base += TORQUE_TEX2D(backBuffer, IN.uv0+(0.011 * DreamViewIntensity));

   base += TORQUE_TEX2D(backBuffer, IN.uv0-(0.001 * DreamViewIntensity));
   base += TORQUE_TEX2D(backBuffer, IN.uv0-(0.003 * DreamViewIntensity));
   base += TORQUE_TEX2D(backBuffer, IN.uv0-(0.005 * DreamViewIntensity));
   base += TORQUE_TEX2D(backBuffer, IN.uv0-(0.007 * DreamViewIntensity));
   base += TORQUE_TEX2D(backBuffer, IN.uv0-(0.009 * DreamViewIntensity));
   base += TORQUE_TEX2D(backBuffer, IN.uv0-(0.011 * DreamViewIntensity));
   
   base.rgb = (base.r + base.g + base.b)/3.0;
   base = base / 9.5;
   
   return base;
}