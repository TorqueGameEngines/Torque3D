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

#line 28

uniform sampler2D inputTex;
uniform sampler2D dirtTex;
uniform float strength;
// XY: Dirt Texture Size/Scale
// Z: Dirt Effect Strength
uniform vec3 dirtParams;
// XY: Edge Min & Max Distance
// Z: Edge Min Value
uniform vec3 edgeParams;
uniform vec2 oneOverTargetSize;

out vec4 OUT_col;
  
void main()
{
  #ifdef USE_DIRT
    float edge = distance(IN_uv0, vec2(0.5, 0.5));
    edge = max(smoothstep(edgeParams.x, edgeParams.y, edge), edgeParams.z);
    vec3 dirt = texture(dirtTex, IN_uv0 / (dirtParams.xy * oneOverTargetSize)).rgb * dirtParams.z * edge;
  #endif
  
  vec4 upSample = texture(inputTex, IN_uv0) * (strength+1.0);
  
  #ifdef USE_DIRT
    upSample.rgb += upSample.rgb * dirt;
  #endif
  
  OUT_col = max(upSample, 0.0)/M_PI_F;
}
