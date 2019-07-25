
//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~//
// Arcane-FX - VERTEX SHADER
//
// afxZodiac_Interior_P.hlsl
//   This is the pixel shader for rendering zodiacs on interiors.
//   
// Copyright (C) Faust Logic, Inc.
//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~//

#include "../common/shaderModel.hlsl"
struct VertData
{
   float3 position        : POSITION;
   float4 color           : COLOR0;
   float2 texCoord        : TEXCOORD0;
};

struct ConnectData
{
   float4 hpos         : TORQUE_POSITION;
   float2 texCoord     : TEXCOORD0;
};

//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
ConnectData main( VertData IN,
                  uniform float4x4 modelView : register(C0)
                  )
{
   ConnectData OUT;

   OUT.hpos = mul(modelView, float4(IN.position,1.0)); 
   OUT.texCoord = IN.texCoord;
    
   return OUT;
}

//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~//
