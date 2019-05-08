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

struct VertData
{
   float3 position        : POSITION;
   float3 normal          : NORMAL;
   float3 T               : TANGENT;
   float3 B               : BINORMAL;
   float2 texCoord        : TEXCOORD0;
   float2 texCoord2       : TEXCOORD1;
};


struct ConnectData
{
   float4 hpos            : SV_Position;
   float3 wsNormal        : TEXCOORD0;
   float3 outWsPosition   : TEXCOORD1;
};


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
ConnectData main( VertData IN,
                  uniform float4x4 modelview       : register(C0),
                  uniform float4x4 objTrans        : register(C4)
)
{
   ConnectData OUT;

   // Vert Position
   OUT.hpos = mul(modelview, float4(IN.position.xyz,1));
   
   // Diffuse Color
   
   // Deferred RT Lighting
   OUT.wsNormal = mul( objTrans, float4( normalize( IN.normal ), 0.0 ) ).xyz;
   OUT.outWsPosition = mul( objTrans, float4( IN.position.xyz, 1 ) ).xyz;
   
   // Visibility
   
   // HDR Output
   
   return OUT;
}
