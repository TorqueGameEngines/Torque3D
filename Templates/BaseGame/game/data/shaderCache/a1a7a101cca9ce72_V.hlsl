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

struct VertData
{
   float3 position        : POSITION;
   float3 normal          : NORMAL;
   float2 texCoord        : TEXCOORD0;
};


struct ConnectData
{
   float4 hpos            : SV_Position;
   float3 reflectVec      : TEXCOORD0;
};


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
ConnectData main( VertData IN,
                  uniform float4x4 modelview       : register(C0),
                  uniform float4x4 objTrans        : register(C4),
                  uniform float3   eyePosWorld     : register(C8)
)
{
   ConnectData OUT;

   // Vert Position
   OUT.hpos = mul(modelview, float4(IN.position.xyz,1));
   
   // skybox
   
   // Diffuse Color
   
   // Reflect Cube
   float3 cubeVertPos = mul(objTrans, float4(IN.position,1)).xyz;
   float3 cubeNormal = ( mul( (objTrans),  float4(IN.normal, 0) ) ).xyz;
   cubeNormal = bool(length(cubeNormal)) ? normalize(cubeNormal) : cubeNormal;
   float3 eyeToVert = cubeVertPos - eyePosWorld;
   OUT.reflectVec = reflect(eyeToVert, cubeNormal);
   
   // HDR Output
   
   return OUT;
}
