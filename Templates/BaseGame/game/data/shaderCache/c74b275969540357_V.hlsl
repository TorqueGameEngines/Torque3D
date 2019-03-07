//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "core/rendering/shaders/torque.hlsl"

// Features:
// Paraboloid Vert Transform
// Visibility
// Depth (Out)

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
   float2 posXY           : TEXCOORD0;
   float depth           : TEXCOORD1;
};


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
ConnectData main( VertData IN,
                  uniform float2   atlasScale      : register(C4),
                  uniform float4x4 worldViewOnly   : register(C0),
                  uniform float4   lightParams     : register(C5),
                  uniform float2   atlasXOffset    : register(C6)
)
{
   ConnectData OUT;

   // Paraboloid Vert Transform
   OUT.hpos = mul(worldViewOnly, float4(IN.position.xyz,1)).xzyw;
   float L = length(OUT.hpos.xyz);
   OUT.hpos /= L;
   OUT.hpos.z = OUT.hpos.z + 1.0;
   OUT.hpos.xy /= OUT.hpos.z;
   OUT.hpos.z = L / lightParams.x;
   OUT.hpos.w = 1.0;
   OUT.posXY = OUT.hpos.xy;
   OUT.hpos.xy *= atlasScale.xy;
   OUT.hpos.xy += atlasXOffset;
   
   // Visibility
   
   // Depth (Out)
   OUT.depth = OUT.hpos.z / OUT.hpos.w;
   
   return OUT;
}
