//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "core/rendering/shaders/lighting.hlsl"
#include "core/rendering/shaders/torque.hlsl"

// Features:
// Vert Position
// Diffuse Color
// Deferred RT Lighting
// Visibility
// HDR Output

struct ConnectData
{
   float4 vpos            : SV_Position;
   float3 wsNormal        : TEXCOORD0;
   float3 wsPosition      : TEXCOORD1;
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
              uniform float3    eyePosWorld     : register(C17),
              uniform float4    inLightPos[3] : register(C1),
              uniform float4    inLightInvRadiusSq : register(C4),
              uniform float4    inLightColor[4] : register(C5),
              uniform float4    inLightSpotDir[3] : register(C9),
              uniform float4    inLightSpotAngle : register(C12),
              uniform float4    inLightSpotFalloff : register(C13),
              uniform float     smoothness      : register(C14),
              uniform float     metalness       : register(C15),
              uniform float4    ambient         : register(C18),
              uniform float     visibility      : register(C16)
)
{
   Fragout OUT;

   // Vert Position
   
   // Diffuse Color
   OUT.col = diffuseMaterialColor;
   
   // Deferred RT Lighting
   IN.wsNormal = normalize( half3( IN.wsNormal ) );
   float3 wsView = normalize( eyePosWorld - IN.wsPosition );
   float4 rtShading; float4 specular;
   compute4Lights( wsView, IN.wsPosition, IN.wsNormal, float4( 1, 1, 1, 1 ),
      inLightPos, inLightInvRadiusSq, inLightColor, inLightSpotDir, inLightSpotAngle, inLightSpotFalloff, smoothness, metalness, OUT.col,
      rtShading, specular );
   OUT.col *= float4( rtShading.rgb + ambient.rgb, 1 );
   
   // Visibility
   fizzle( IN.vpos.xy, visibility );
   
   // HDR Output
   OUT.col = hdrEncode( OUT.col );
   

   return OUT;
}
