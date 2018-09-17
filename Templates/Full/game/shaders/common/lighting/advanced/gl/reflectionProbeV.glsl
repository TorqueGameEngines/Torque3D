#include "shadergen:/autogenConditioners.h"
#include "../../torque.hlsl"

// This is the shader input
struct Vert
{
   float4 position : POSITION;
   float2 uv0      : TEXCOORD0;
   float3 wsEyeRay : TEXCOORD1;
};

// This is the shader output data.
struct Conn
{
   float4 position : POSITION;
   float2 uv0      : TEXCOORD0;
   float3 wsEyeRay : TEXCOORD1;
};

// Render Target Paramaters
float4 rtParams0;

Conn main(Vert IN,
          uniform float4x4 modelView : register(C0))	         
{
   Conn OUT;   
   OUT.position = IN.position;
   OUT.uv0 = viewportCoordToRenderTarget( IN.uv0, rtParams0 );
   OUT.wsEyeRay = IN.wsEyeRay;
   return OUT;
}

