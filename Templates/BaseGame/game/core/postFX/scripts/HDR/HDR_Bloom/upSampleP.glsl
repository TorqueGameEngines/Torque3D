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
#include "shadergen:/autogenConditioners.h"

#line 27

#define KERNEL_SAMPLES 9
const vec3 KERNEL[9] = vec3[](
  vec3( 0.0000, 0.0000, 0.5000),
  vec3( 1.0000, 0.0000, 0.0625),
  vec3( 0.0000, 1.0000, 0.0625),
  vec3(-1.0000, 0.0000, 0.0625),
  vec3( 0.0000,-1.0000, 0.0625),
  vec3( 0.7070, 0.7070, 0.0625),
  vec3( 0.7070,-0.7070, 0.0625),
  vec3(-0.7070,-0.7070, 0.0625),
  vec3(-0.7070, 0.7070, 0.0625)
);

uniform sampler2D nxtTex;
uniform sampler2D mipTex;
uniform float filterRadius;
uniform vec2 oneOverTargetSize;

out vec4 OUT_col;

void main()
{
  vec4 upSample = vec4(0, 0, 0, 0);

  for (int i=0; i<KERNEL_SAMPLES; i++)
  {
    // XY: Sample Offset
    // Z: Sample Weight
    vec3 offsetWeight = KERNEL[i];
    vec2 offsetXY = offsetWeight.xy * oneOverTargetSize * filterRadius;
    float weight = offsetWeight.z;
    vec4 sampleCol = texture(mipTex, IN_uv0 + offsetXY);
    upSample += sampleCol * weight;
  }
  
  upSample = texture(nxtTex, IN_uv0) + upSample;
  
  OUT_col = upSample;
}
