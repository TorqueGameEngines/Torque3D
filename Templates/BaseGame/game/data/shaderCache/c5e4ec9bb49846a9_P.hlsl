//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "core/rendering/shaders/torque.hlsl"

// Features:
// Vert Position
// Diffuse Color
// Deferred Shading: Empty Specular
// Deferred Shading: Mat Info Flags
// Eye Space Depth (Out)
// Visibility
// GBuffer Conditioner
// Deferred Material

struct ConnectData
{
   float4 vpos            : SV_Position;
   float4 wsEyeVec        : TEXCOORD0;
   float3 gbNormal        : TEXCOORD1;
};


struct Fragout
{
   float4 col : SV_Target0;
   float4 col1 : SV_Target1;
   float4 col2 : SV_Target2;
};


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
Fragout main( ConnectData IN,
              uniform float4    diffuseMaterialColor : register(C0),
              uniform float     matInfoFlags    : register(C1),
              uniform float3    vEye            : register(C3),
              uniform float4    oneOverFarplane : register(C4),
              uniform float     visibility      : register(C2)
)
{
   Fragout OUT;

   // Vert Position
   
   // Diffuse Color
   OUT.col1 = float4(1.0,1.0,1.0,1.0);
   OUT.col1 = diffuseMaterialColor;
   
   // Deferred Shading: Empty Specular
   OUT.col2.g = 1.0;
   OUT.col2.ba = 0.0;
   
   // Deferred Shading: Mat Info Flags
   OUT.col2.r = matInfoFlags;
   
   // Eye Space Depth (Out)
#ifndef CUBE_SHADOW_MAP
   float eyeSpaceDepth = dot(vEye, (IN.wsEyeVec.xyz / IN.wsEyeVec.w));
#else
   float eyeSpaceDepth = length( IN.wsEyeVec.xyz / IN.wsEyeVec.w ) * oneOverFarplane.x;
#endif
   
   // Visibility
   fizzle( IN.vpos.xy, visibility );
   
   // GBuffer Conditioner
   float4 normal_depth = float4(normalize(IN.gbNormal), eyeSpaceDepth);

   // output buffer format: GFXFormatR16G16B16A16F
   // g-buffer conditioner: float4(normal.X, normal.Y, depth Hi, depth Lo)
   float4 _gbConditionedOutput = float4(sqrt(half(2.0/(1.0 - normal_depth.y))) * half2(normal_depth.xz), 0.0, normal_depth.a);
   
   // Encode depth into hi/lo
   float2 _tempDepth = frac(normal_depth.a * float2(1.0, 65535.0));
   _gbConditionedOutput.zw = _tempDepth.xy - _tempDepth.yy * float2(1.0/65535.0, 0.0);

   OUT.col = _gbConditionedOutput;
   
   // Deferred Material
   

   return OUT;
}
