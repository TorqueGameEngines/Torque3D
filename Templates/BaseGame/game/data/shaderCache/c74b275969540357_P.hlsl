//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Dependencies:
#include "core/rendering/shaders/torque.hlsl"

// Features:
// Paraboloid Vert Transform
// Visibility
// Depth (Out)

struct ConnectData
{
   float4 vpos            : SV_Position;
   float2 posXY           : TEXCOORD0;
   float depth           : TEXCOORD1;
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
   clip( 1.0 - abs(IN.posXY.x) );
   
   // Visibility
   fizzle( IN.vpos.xy, visibility );
   
   // Depth (Out)
   OUT.col = float4( IN.depth, 0, 0, 1 );
   

   return OUT;
}
