//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "core/rendering/shaders/torque.hlsl"

// Features:
// Vert Position
// Base Texture
// Diffuse Color
// Deferred Shading: Empty Specular
// Deferred Shading: Mat Info Flags
// Eye Space Depth (Out)
// Visibility
// GBuffer Conditioner
// Deferred Material

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
   float4 wsEyeVec        : TEXCOORD1;
   float3 gbNormal        : TEXCOORD2;
};


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
ConnectData main( VertData IN,
                  uniform float4x4 modelview       : register(C0),
                  uniform float4x4 objTrans        : register(C4),
                  uniform float3   eyePosWorld     : register(C12),
                  uniform float4x4 worldViewOnly   : register(C8)
)
{
   ConnectData OUT;

   // Vert Position
   OUT.hpos = mul(modelview, float4(IN.position.xyz,1));
   
   // Base Texture
   OUT.out_texCoord = (float2)IN.texCoord;
   
   // Diffuse Color
   
   // Deferred Shading: Empty Specular
   
   // Deferred Shading: Mat Info Flags
   
   // Eye Space Depth (Out)
   float3 depthPos = mul( objTrans, float4( IN.position.xyz, 1 ) ).xyz;
   OUT.wsEyeVec = float4( depthPos.xyz - eyePosWorld, 1 );
   
   // Visibility
   
   // GBuffer Conditioner
   OUT.gbNormal = mul(worldViewOnly, float4( normalize(IN.normal), 0.0 ) ).xyz;
   
   // Deferred Material
   
   return OUT;
}
