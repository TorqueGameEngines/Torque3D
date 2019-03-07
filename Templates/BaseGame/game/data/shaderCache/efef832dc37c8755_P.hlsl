//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "core/rendering/shaders/torque.hlsl"

// Features:
// Vert Position
// Diffuse Color
// Diffuse Vertex Color
// Visibility
// Fog
// HDR Output
// Forward Shaded Material
// Translucent

struct ConnectData
{
   float4 vpos            : SV_Position;
   float4 vertColor       : COLOR;
   float3 wsPosition      : TEXCOORD0;
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
              uniform float     visibility      : register(C1),
              uniform float4    fogColor        : register(C2),
              uniform float3    eyePosWorld     : register(C3),
              uniform float3    fogData         : register(C4)
)
{
   Fragout OUT;

   // Vert Position
   
   // Diffuse Color
   OUT.col = diffuseMaterialColor;
   
   // Diffuse Vertex Color
   OUT.col *= IN.vertColor;
   
   // Visibility
   OUT.col.a *= visibility;
   
   // Fog
   float fogAmount = saturate( computeSceneFog( eyePosWorld, IN.wsPosition, fogData.r, fogData.g, fogData.b ) );
   OUT.col.rgb = lerp( fogColor.rgb, OUT.col.rgb, fogAmount );
   
   // HDR Output
   OUT.col = hdrEncode( OUT.col );
   
   // Forward Shaded Material
   
   // Translucent
   

   return OUT;
}
