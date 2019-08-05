
//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~//
// Arcane-FX - PIXEL SHADER
//
// afxZodiac_Polysoup_P.hlsl
//   This is the pixel shader for rendering zodiacs on polysoup models.
//   
// Copyright (C) Faust Logic, Inc.
//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~//

#include "../common/shaderModel.hlsl"

struct ConnectData
{
   float4 hpos         : TORQUE_POSITION;
   float2 texCoord     : TEXCOORD0;
};

TORQUE_UNIFORM_SAMPLER2D(zodiacMap,0);
uniform float4    zodiacColor;

float4 main( ConnectData IN ) : TORQUE_TARGET0
{
   float4 outColor = zodiacColor*TORQUE_TEX2D(zodiacMap, IN.texCoord);   
   return outColor;
}

//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~//
