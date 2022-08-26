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
#include "shadergen:/autogenConditioners.h"

uniform sampler2D inputTex;
uniform sampler2D dirtTex;
uniform float strength;
// XY: Dirt Texture Size/Scale
// Z: Dirt Effect Strength
uniform float3 dirtParams;
// XY: Edge Min & Max Distance
// Z: Edge Min Value
uniform float3 edgeParams;
uniform float2 oneOverTargetSize;

in float2 uv0;

out float4 OUT_col;

void main()
{
	#if defined(USE_DIRT)
		float edge = distance(uv0, float2(0.5f, 0.5f));
		edge = max(smoothstep(edgeParams.x, edgeParams.y, edge), edgeParams.z);
		float3 dirt = tex2D(dirtTex, uv0 / (dirtParams.xy * oneOverTargetSize)).rgb * dirtParams.z * edge;
	#endif
	
	float4 upSample = tex2D(inputTex, uv0) * strength;
	
	#if defined(USE_DIRT)
		upSample.rgb += upSample.rgb * dirt;
	#endif
	
	OUT_col = upSample;
}
