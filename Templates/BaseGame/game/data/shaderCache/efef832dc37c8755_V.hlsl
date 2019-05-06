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

struct VertData
{
   float3 position        : POSITION;
   float4 diffuse         : COLOR;
};


struct ConnectData
{
   float4 hpos            : SV_Position;
   float4 vertColor       : COLOR;
   float3 outWsPosition   : TEXCOORD0;
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
   
   // Diffuse Vertex Color
   OUT.vertColor = IN.diffuse;
   
   // Visibility
   
   // Fog
   OUT.outWsPosition = mul( objTrans, float4( IN.position.xyz, 1 ) ).xyz;
   
   // HDR Output
   
   // Forward Shaded Material
   
   // Translucent
   
   return OUT;
}
