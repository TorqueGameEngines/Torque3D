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

#include "core/rendering/shaders/gl/hlslCompat.glsl"
#include "core/rendering/shaders/postFX/gl/postFx.glsl"
#include "core/rendering/shaders/gl/torque.glsl"
#include "shadergen:/autogenConditioners.h"

#define KERNEL_SAMPLES 4
const vec2 KERNEL[9] = vec2[](
  vec2( 0.5, 0.5),
  vec2( 0.5,-0.5),
  vec2(-0.5,-0.5),
  vec2(-0.5, 0.5)
);

uniform sampler2D inputTex;
uniform sampler2D luminanceTex;
uniform float g_fMiddleGray;
uniform vec2 oneOverTargetSize;

out vec4 OUT_col;
 
void main()
{
   const float weight = 1.0 / KERNEL_SAMPLES;
   vec4 downSample = vec4(0, 0, 0, 0);
   
   for (int i=0; i<KERNEL_SAMPLES; i++)
   {
     vec2 offset = KERNEL[i] * oneOverTargetSize;
     vec4 sampleCol = hdrDecode( texture(inputTex, IN_uv0 + offset) );
     downSample += sampleCol;
   }

   float adaptedLum = texture( luminanceTex, vec2( 0.5, 0.5 ) ).r;
   float lum = (g_fMiddleGray / (adaptedLum + 0.0001));
   
   return downSample * weight * lum;
}
