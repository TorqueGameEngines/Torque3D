//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "core/rendering/shaders/torque.hlsl"

// Features:
// Paraboloid Vert Transform
// Visibility
// Depth (Out)
// Single Pass Paraboloid

struct ConnectData
{
   float4 vpos            : SV_Position;
   float isBack          : TEXCOORD0;
   float2 posXY           : TEXCOORD1;
   float depth           : TEXCOORD2;
};


struct Fragout
{
   float4 col : SV_Target0;
};


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
Fragout main( ConnectData IN,
              uniform float     visibility      : register(C0)
)
{
   Fragout OUT;

   // Paraboloid Vert Transform
   clip( abs( IN.isBack ) - 0.999 );
   clip( 1.0 - abs(IN.posXY.x) );
   
   // Visibility
   fizzle( IN.vpos.xy, visibility );
   
   // Depth (Out)
   OUT.col = float4( IN.depth, 0, 0, 1 );
   
   // Single Pass Paraboloid
   

   return OUT;
}
