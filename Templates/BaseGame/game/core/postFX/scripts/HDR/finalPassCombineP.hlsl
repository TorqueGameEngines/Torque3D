//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#include "core/rendering/shaders/torque.hlsl"
#include "core/rendering/shaders/postFX/postFx.hlsl"
#include "core/rendering/shaders/shaderModelAutoGen.hlsl"

TORQUE_UNIFORM_SAMPLER2D(sceneTex, 0);
TORQUE_UNIFORM_SAMPLER2D(luminanceTex, 1);
TORQUE_UNIFORM_SAMPLER2D(bloomTex, 2);

uniform float2 texSize0;
uniform float2 texSize2;

uniform float g_fEnableToneMapping;
uniform float g_fMiddleGray;
uniform float g_fWhiteCutoff;
uniform float g_fEnableBlueShift;

uniform float g_fEnableAutoExposure;
uniform float g_fTonemapMode;

uniform float3 g_fBlueShiftColor;
uniform float g_fBloomScale;
uniform float g_fOneOverGamma;
uniform float Brightness;
uniform float Contrast;

// uncharted 2 tonemapper see: http://filmicgames.com/archives/75
float3 Uncharted2Tonemap(const float3 x)
{
   const float A = 0.15;
   const float B = 0.50;
   const float C = 0.10;
   const float D = 0.20;
   const float E = 0.02;
   const float F = 0.30;
   return ((x*(A*x + C*B) + D*E) / (x*(A*x + B) + D*F)) - E / F;
}

float3 ACESFilm( float3 x )
{
    const float a = 2.51;
    const float b = 0.03;
    const float c = 2.43;
    const float d = 0.59;
    const float e = 0.14;
    return saturate((x*(a*x+b))/(x*(c*x+d)+e));
}

float3 tonemap(float3 color)
{
   if(g_fTonemapMode == 1.0)
   {
      const float W = 11.2;
      float ExposureBias = 2.0f;
      //float ExposureAdjust = 1.5f;
      //c *= ExposureAdjust;
      color = Uncharted2Tonemap(ExposureBias*color);
      color = color * (1.0f / Uncharted2Tonemap(W));
   }
   else if(g_fTonemapMode == 2.0)
   {
      color = ACESFilm(color);
   }

   return color;
}

float4 main( PFXVertToPix IN ) : TORQUE_TARGET0
{
   float4 sample = hdrDecode( TORQUE_TEX2D( sceneTex, IN.uv0 ) );
   float adaptedLum = TORQUE_TEX2D( luminanceTex, float2( 0.5f, 0.5f ) ).r;
   float4 bloom = TORQUE_TEX2D( bloomTex, IN.uv0 );

   // For very low light conditions, the rods will dominate the perception
   // of light, and therefore color will be desaturated and shifted
   // towards blue.
   if ( g_fEnableBlueShift > 0.0f )
   {
      const float3 LUMINANCE_VECTOR = float3(0.2125f, 0.7154f, 0.0721f);

      // Define a linear blending from -1.5 to 2.6 (log scale) which
      // determines the lerp amount for blue shift
      float coef = 1.0f - ( adaptedLum + 1.5 ) / 4.1;
      coef = saturate( coef * g_fEnableBlueShift );

      // Lerp between current color and blue, desaturated copy
      float3 rodColor = dot( sample.rgb, LUMINANCE_VECTOR ) * g_fBlueShiftColor;
      sample.rgb = lerp( sample.rgb, rodColor, coef );
	  
      rodColor = dot( bloom.rgb, LUMINANCE_VECTOR ) * g_fBlueShiftColor;
      bloom.rgb = lerp( bloom.rgb, rodColor, coef );
   }

   // Add the bloom effect.
   sample += saturate(g_fBloomScale * bloom);

   // Apply contrast
   sample.rgb = ((sample.rgb - 0.5f) * Contrast) + 0.5f;

   // Apply brightness
   //sample.rgb += Brightness;

   //tonemapping - TODO fix up eye adaptation
   if ( g_fEnableToneMapping > 0.0f )
   {
      float adapation = 1;

      if( g_fEnableAutoExposure > 0.0f )
         adapation = (g_fMiddleGray / (adaptedLum + 0.0001)) * hdrLuminance( sample.rgb );

      sample.rgb = tonemap(sample.rgb * adapation);
   }

   return sample;
}
