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
#include "core/postFX/scripts/HDR/HDR_colorUtils.glsl"
#include "shadergen:/autogenConditioners.h"
#line 28
uniform sampler2D inputTex;
uniform vec2 oneOverTargetSize;
uniform int mipId;

out vec4 OUT_col;
 
void main()
{
  vec4 downSample = vec4(0, 0, 0, 0);
  float x = oneOverTargetSize.x;
  float y = oneOverTargetSize.y;
  
  vec3 a = texture(inputTex, vec2(IN_uv0.x - 2 * x, IN_uv0.y + 2 * y)).rgb;
  vec3 b = texture(inputTex, vec2(IN_uv0.x,         IN_uv0.y + 2 * y)).rgb;
  vec3 c = texture(inputTex, vec2(IN_uv0.x + 2 * x, IN_uv0.y + 2 * y)).rgb;

  vec3 d = texture(inputTex, vec2(IN_uv0.x - 2 * x, IN_uv0.y)).rgb;
  vec3 e = texture(inputTex, vec2(IN_uv0.x,         IN_uv0.y)).rgb;
  vec3 f = texture(inputTex, vec2(IN_uv0.x + 2 * x, IN_uv0.y)).rgb;

  vec3 g = texture(inputTex, vec2(IN_uv0.x - 2 * x, IN_uv0.y - 2 * y)).rgb;
  vec3 h = texture(inputTex, vec2(IN_uv0.x,         IN_uv0.y - 2 * y)).rgb;
  vec3 i = texture(inputTex, vec2(IN_uv0.x + 2 * x, IN_uv0.y - 2 * y)).rgb;

  vec3 j = texture(inputTex, vec2(IN_uv0.x - x, IN_uv0.y + y)).rgb;
  vec3 k = texture(inputTex, vec2(IN_uv0.x + x, IN_uv0.y + y)).rgb;
  vec3 l = texture(inputTex, vec2(IN_uv0.x - x, IN_uv0.y - y)).rgb;
  vec3 m = texture(inputTex, vec2(IN_uv0.x + x, IN_uv0.y - y)).rgb;

  vec3 group[5];
  switch (mipId)
  {
	case 0:
		group[0] = (a+b+d+e) * (0.125f/4.0f);
		group[1] = (b+c+e+f) * (0.125f/4.0f);
		group[2] = (d+e+g+h) * (0.125f/4.0f);
		group[3] = (e+f+h+i) * (0.125f/4.0f);
		group[4] = (j+k+l+m) * (0.5f/4.0f);
		group[0] *= KarisAverage(group[0]);
		group[1] *= KarisAverage(group[1]);
		group[2] *= KarisAverage(group[2]);
		group[3] *= KarisAverage(group[3]);
		group[4] *= KarisAverage(group[4]);
		downSample.rgb = group[0]+group[1]+group[2]+group[3]+group[4];
		downSample.a = 1.0;
		break;
		
	default:
		downSample.rgb = e*0.125;
		downSample.rgb += (a+c+g+i)*0.03125;
		downSample.rgb += (b+d+f+h)*0.0625;
		downSample.rgb += (j+k+l+m)*0.125;
		downSample.a = 1.0;
		break;
  }
  
  OUT_col = downSample;
}