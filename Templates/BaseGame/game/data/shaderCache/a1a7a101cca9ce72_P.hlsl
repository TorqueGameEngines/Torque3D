//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "core/rendering/shaders/torque.hlsl"

// Features:
// Vert Position
// skybox
// Diffuse Color
// Reflect Cube
// HDR Output

struct ConnectData
{
   float4 vpos            : SV_Position;
   float3 reflectVec      : TEXCOORD0;
};


struct Fragout
{
   float4 col : SV_Target0;
};


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
Fragout main( ConnectData IN,
              uniform float4    diffuseMaterialColor : register(C0),
              uniform SamplerState cubeMap         : register(S0),
              uniform TextureCube cubeMapTex      : register(T0)
)
{
   Fragout OUT;

   // Vert Position
   
   // skybox
   
   // Diffuse Color
   OUT.col = diffuseMaterialColor;
   
   // Reflect Cube
   OUT.col *= cubeMapTex.Sample( cubeMap, IN.reflectVec );
   
   // HDR Output
   OUT.col = hdrEncode( OUT.col );
   

   return OUT;
}
