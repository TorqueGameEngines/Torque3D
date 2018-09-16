//-----------------------------------------------------------------------------
// Copyright (c) 2016 GarageGames, LLC
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

#include "hlslCompat.glsl"
#include "torque.glsl"

uniform samplerCube cubemapTex;

in float3 face_pos_x;
in float3 face_neg_x;
in float3 face_pos_y;
in float3 face_neg_y;
in float3 face_pos_z;
in float3 face_neg_z;

out float4 target0;
out float4 target1;
out float4 target2;
out float4 target3;
out float4 target4;
out float4 target5;
//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
void main()
{
   target0 = texture(cubemapTex, face_pos_x);
   target1 = texture(cubemapTex, face_neg_x);
   target2 = texture(cubemapTex, face_pos_y);
   target3 = texture(cubemapTex, face_neg_y);
   target4 = texture(cubemapTex, face_pos_z);
   target5 = texture(cubemapTex, face_neg_z);
}
