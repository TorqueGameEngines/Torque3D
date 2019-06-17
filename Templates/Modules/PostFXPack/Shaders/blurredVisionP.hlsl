#include "shaders/common/postFx/postFx.hlsl"
#include "shadergen:/autogenConditioners.h"
#include "../../torque.hlsl"

TORQUE_UNIFORM_SAMPLER2D(backBuffer, 0);
uniform float BlurredVisionIntensity;

float4 main(PFXVertToPix IN) : TORQUE_TARGET0
{
   float4 base = TORQUE_TEX2D(backBuffer, IN.uv0);

   base += TORQUE_TEX2D(backBuffer, IN.uv0+(0.001 * BlurredVisionIntensity));
   base += TORQUE_TEX2D(backBuffer, IN.uv0+(0.003 * BlurredVisionIntensity));
   base += TORQUE_TEX2D(backBuffer, IN.uv0+(0.005 * BlurredVisionIntensity));
   base += TORQUE_TEX2D(backBuffer, IN.uv0+(0.007 * BlurredVisionIntensity));
   base += TORQUE_TEX2D(backBuffer, IN.uv0+(0.009 * BlurredVisionIntensity));
   base += TORQUE_TEX2D(backBuffer, IN.uv0+(0.011 * BlurredVisionIntensity));

   base += TORQUE_TEX2D(backBuffer, IN.uv0-(0.001 * BlurredVisionIntensity));
   base += TORQUE_TEX2D(backBuffer, IN.uv0-(0.003 * BlurredVisionIntensity));
   base += TORQUE_TEX2D(backBuffer, IN.uv0-(0.005 * BlurredVisionIntensity));
   base += TORQUE_TEX2D(backBuffer, IN.uv0-(0.007 * BlurredVisionIntensity));
   base += TORQUE_TEX2D(backBuffer, IN.uv0-(0.009 * BlurredVisionIntensity));
   base += TORQUE_TEX2D(backBuffer, IN.uv0-(0.011 * BlurredVisionIntensity));
   
   base = base / 15.0; // 9.5
   
   return base;
}