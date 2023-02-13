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
#line 26
uniform sampler2D nxtTex;
uniform sampler2D mipTex;
uniform float filterRadius;
uniform vec2 oneOverTargetSize;

out vec4 OUT_col;

void main()
{
  vec4 upSample = vec4(0, 0, 0, 0);
  float x = filterRadius*oneOverTargetSize.x;
  float y = filterRadius*oneOverTargetSize.y;

  vec3 a = texture(mipTex, vec2(IN_uv1.x - x, IN_uv1.y + y)).rgb;
  vec3 b = texture(mipTex, vec2(IN_uv1.x,     IN_uv1.y + y)).rgb;
  vec3 c = texture(mipTex, vec2(IN_uv1.x + x, IN_uv1.y + y)).rgb;

  vec3 d = texture(mipTex, vec2(IN_uv1.x - x, IN_uv1.y)).rgb;
  vec3 e = texture(mipTex, vec2(IN_uv1.x,     IN_uv1.y)).rgb;
  vec3 f = texture(mipTex, vec2(IN_uv1.x + x, IN_uv1.y)).rgb;

  vec3 g = texture(mipTex, vec2(IN_uv1.x - x, IN_uv1 - y)).rgb;
  vec3 h = texture(mipTex, vec2(IN_uv1.x,     IN_uv1 - y)).rgb;
  vec3 i = texture(mipTex, vec2(IN_uv1.x + x, IN_uv1 - y)).rgb;

  upSample.rgb = e*4.0;
  upSample.rgb += (b+d+f+h)*2.0;
  upSample.rgb += (a+c+g+i);
  upSample.rgb *= 1.0 / 16.0; 
  upSample.a = 1.0;
  
  upSample = texture(nxtTex, IN_uv0) + upSample;
  
  OUT_col = upSample;
}
