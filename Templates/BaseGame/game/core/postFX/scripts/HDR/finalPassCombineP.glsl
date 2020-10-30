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

#include "core/rendering/shaders/gl/torque.glsl"
#include "core/rendering/shaders/gl/hlslCompat.glsl"
#include "core/rendering/shaders/postFX/gl/postFx.glsl"
#include "shadergen:/autogenConditioners.h"

uniform sampler2D sceneTex;
uniform sampler2D luminanceTex;
uniform sampler2D bloomTex;

uniform vec2 texSize0;
uniform vec2 texSize2;

uniform float g_fEnableToneMapping;
uniform float g_fMiddleGray;
uniform float g_fWhiteCutoff;

uniform float g_fEnableAutoExposure;
uniform float g_fTonemapMode;

uniform float g_fEnableBlueShift;
uniform vec3 g_fBlueShiftColor; 

uniform float g_fBloomScale;

uniform float g_fOneOverGamma;
uniform float Brightness;
uniform float Contrast;

out vec4 OUT_col;

// uncharted 2 tonemapper see: http://filmicgames.com/archives/75
vec3 Uncharted2Tonemap(vec3 x)
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

vec3 tonemap(vec3 c)
{
   vec3 colorOut = c;
    
   if(g_fTonemapMode == 1.0)
   {
      const float W = 11.2;
      float ExposureBias = 2.0f;
      //float ExposureAdjust = 1.5f;
      //c *= ExposureAdjust;
      colorOut = Uncharted2Tonemap(ExposureBias*colorOut);
      colorOut = colorOut * (1.0f / Uncharted2Tonemap(vec3(W,W,W)));
   }
   else if(g_fTonemapMode == 2.0)
   {
      colorOut = ACESFilm(colorOut);
   }

   return colorOut;
}

void main()
{
   vec4 _sample = hdrDecode( texture( sceneTex, IN_uv0 ) );
   float adaptedLum = texture( luminanceTex, vec2( 0.5f, 0.5f ) ).r;
   vec4 bloom = texture( bloomTex, IN_uv0 );

   // For very low light conditions, the rods will dominate the perception
   // of light, and therefore color will be desaturated and shifted
   // towards blue.
   if ( g_fEnableBlueShift > 0.0f )
   {
      const vec3 LUMINANCE_VECTOR = vec3(0.2125f, 0.7154f, 0.0721f);

      // Define a linear blending from -1.5 to 2.6 (log scale) which
      // determines the mix amount for blue shift
      float coef = 1.0f - ( adaptedLum + 1.5 ) / 4.1;
      coef = saturate( coef * g_fEnableBlueShift );

      // Lerp between current color and blue, desaturated copy
      vec3 rodColor = dot( _sample.rgb, LUMINANCE_VECTOR ) * g_fBlueShiftColor;
      _sample.rgb = mix( _sample.rgb, rodColor, coef );
	  
      rodColor = dot( bloom.rgb, LUMINANCE_VECTOR ) * g_fBlueShiftColor;
      bloom.rgb = mix( bloom.rgb, rodColor, coef );
   }

   // Add the bloom effect.
   _sample.rgb += clamp(vec3(g_fBloomScale,g_fBloomScale,g_fBloomScale) * bloom.rgb, vec3(0,0,0), vec3(1.0,1.0,1.0));

   // Apply contrast
   _sample.rgb = ((_sample.rgb - 0.5f) * Contrast) + 0.5f;

   // Apply brightness
   //_sample.rgb += Brightness;

   //tonemapping - TODO fix up eye adaptation
   if ( g_fEnableToneMapping > 0.0f )
   {
      float adapation = 1;

      if ( g_fEnableAutoExposure > 0.0f )
         adapation = (g_fMiddleGray / (adaptedLum + 0.0001)) * hdrLuminance( _sample.rgb );

      _sample.rgb = tonemap(_sample.rgb * adapation);
   }

   OUT_col = _sample;
}
