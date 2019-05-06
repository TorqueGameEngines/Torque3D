//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "core/rendering/shaders/lighting.hlsl"
#include "core/rendering/shaders/torque.hlsl"

// Features:
// Vert Position
// Base Texture
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
};


struct ConnectData
{
   float4 hpos            : SV_Position;
   float2 out_texCoord    : TEXCOORD0;
   float4 screenspacePos  : TEXCOORD1;
};


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
ConnectData main( VertData IN,
                  uniform float4x4 modelview       : register(C0)
)
{
   ConnectData OUT;

   // Vert Position
   OUT.hpos = mul(modelview, float4(IN.position.xyz,1));
   
   // Base Texture
   OUT.out_texCoord = (float2)IN.texCoord;
   
   // Deferred RT Lighting
   OUT.screenspacePos = OUT.hpos;
   
   // Visibility
   
   // HDR Output
   
   return OUT;
}
