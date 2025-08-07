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
uniform int mipCount0;

out vec4 OUT_col;
 
void main()
{
  vec4 downSample = vec4(0, 0, 0, 0);
  vec4 finalOut = float4(0, 0, 0, 0);

  for (int mipId = 0; mipId<mipCount0; mipId++)
  {
    float mipWeight = float(mipId)/float(mipCount0);
    float mipIDf = float(mipId);
    float x = oneOverTargetSize.x*pow(0.5, mipId);
    float y = oneOverTargetSize.y*pow(0.5, mipId);
  
    vec3 a = textureLod(inputTex, vec2(IN_uv0.x - 2 * x, IN_uv0.y + 2 * y), mipIDf).rgb;
    vec3 b = textureLod(inputTex, vec2(IN_uv0.x,         IN_uv0.y + 2 * y), mipIDf).rgb;
    vec3 c = textureLod(inputTex, vec2(IN_uv0.x + 2 * x, IN_uv0.y + 2 * y), mipIDf).rgb;

    vec3 d = textureLod(inputTex, vec2(IN_uv0.x - 2 * x, IN_uv0.y), mipIDf).rgb;
    vec3 e = textureLod(inputTex, vec2(IN_uv0.x,         IN_uv0.y), mipIDf).rgb;
    vec3 f = textureLod(inputTex, vec2(IN_uv0.x + 2 * x, IN_uv0.y), mipIDf).rgb;

    vec3 g = textureLod(inputTex, vec2(IN_uv0.x - 2 * x, IN_uv0.y - 2 * y), mipIDf).rgb;
    vec3 h = textureLod(inputTex, vec2(IN_uv0.x,         IN_uv0.y - 2 * y), mipIDf).rgb;
    vec3 i = textureLod(inputTex, vec2(IN_uv0.x + 2 * x, IN_uv0.y - 2 * y), mipIDf).rgb;

    vec3 j = textureLod(inputTex, vec2(IN_uv0.x - x, IN_uv0.y + y), mipIDf).rgb;
    vec3 k = textureLod(inputTex, vec2(IN_uv0.x + x, IN_uv0.y + y), mipIDf).rgb;
    vec3 l = textureLod(inputTex, vec2(IN_uv0.x - x, IN_uv0.y - y), mipIDf).rgb;
    vec3 m = textureLod(inputTex, vec2(IN_uv0.x + x, IN_uv0.y - y), mipIDf).rgb;

    vec3 group[5];
    switch (mipId)
    {
        case 0:
            group[0] = (a+b+d+e) * (0.125/4.0);
            group[1] = (b+c+e+f) * (0.125/4.0);
            group[2] = (d+e+g+h) * (0.125/4.0);
            group[3] = (e+f+h+i) * (0.125/4.0);
            group[4] = (j+k+l+m) * (0.5/4.0);
            group[0] *= KarisAverage(group[0]);
            group[1] *= KarisAverage(group[1]);
            group[2] *= KarisAverage(group[2]);
            group[3] *= KarisAverage(group[3]);
            group[4] *= KarisAverage(group[4]);
            downSample.rgb = group[0]+group[1]+group[2]+group[3]+group[4];
            downSample.a = 1.0;
            break;
		
        default:
            downSample.rgb = e*mipWeight;
            downSample.rgb += (a+c+g+i)*mipWeight*0.125;
            downSample.rgb += (b+d+f+h)*mipWeight*0.25;
            downSample.rgb += (j+k+l+m)*mipWeight*0.5;
            downSample.a = 1.0;
            break;
    }
    finalOut += downSample*(1.0-mipWeight);
  }
  OUT_col = finalOut;
}