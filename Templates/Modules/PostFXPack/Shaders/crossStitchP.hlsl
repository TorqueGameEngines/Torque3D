#include "shaders/common/postFx/postFx.hlsl"
#include "shadergen:/autogenConditioners.h"

TORQUE_UNIFORM_SAMPLER2D(backBuffer, 0);
uniform float time;
uniform float sizeX; // rt_w
uniform float sizeY; // rt_h
uniform float stitching_size = 6.0;
uniform int invert = 0;

float4 main(PFXVertToPix IN) : TORQUE_TARGET0
{
   float4 base = float4(0.0, 0.0, 0.0, 0.0);
   float size = stitching_size;
   float2 cPos = IN.uv0 * float2(sizeX, sizeY);
   float2 tlPos = floor(cPos / float2(size, size));
   tlPos *= size;
   int remX = int(cPos.x % size);
   int remY = int(cPos.y % size);
   if (remX == 0 && remY == 0)
      tlPos = cPos;
   float2 blPos = tlPos;
   blPos.y += (size - 1.0);
   if ((remX == remY) || (((int(cPos.x) - int(blPos.x)) == (int(blPos.y) - int(cPos.y)))))
   {
     if (invert == 1)
       base = float4(0.2, 0.15, 0.05, 1.0);
     else
       base = TORQUE_TEX2D(backBuffer, tlPos * float2(1.0/sizeX, 1.0/sizeY)) * 1.4;
   }
   else
   {
     if (invert == 1)
       base = TORQUE_TEX2D(backBuffer, tlPos * float2(1.0/sizeX, 1.0/sizeY)) * 1.4;
     else
       base = float4(0.0, 0.0, 0.0, 1.0);
   }
   return base;
}