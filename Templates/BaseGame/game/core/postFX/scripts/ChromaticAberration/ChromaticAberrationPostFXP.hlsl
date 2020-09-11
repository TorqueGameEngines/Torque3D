#include "core/rendering/shaders/postFX/postFx.hlsl"
#include "core/rendering/shaders/torque.hlsl"

TORQUE_UNIFORM_SAMPLER2D(inputTex, 0);
uniform float distCoeff;
uniform float cubeDistort;
uniform float3 colorDistort;

float4 main( PFXVertToPix IN ) : TORQUE_TARGET0
{
   float2 tex = IN.uv0;

    float f = 0;
    float r2 = (tex.x - 0.5) * (tex.x - 0.5) + (tex.y - 0.5) * (tex.y - 0.5);       

    // Only compute the cubic distortion if necessary.
    if ( cubeDistort == 0.0 )
        f = 1 + r2 * distCoeff;
    else
        f = 1 + r2 * (distCoeff + cubeDistort * sqrt(r2));

    // Distort each color channel seperately to get a chromatic distortion effect.
    float3 outColor;
    float3 distort = f.xxx + colorDistort;

   [unroll]
    for ( int i=0; i < 3; i++ )
    {
        float x = distort[i] * ( tex.x - 0.5 ) + 0.5;
        float y = distort[i] * ( tex.y - 0.5 ) + 0.5;
        outColor[i] = TORQUE_TEX2DLOD( inputTex, float4(x,y,0,0) )[i];
    }

    return float4( outColor.rgb, 1 );
}
