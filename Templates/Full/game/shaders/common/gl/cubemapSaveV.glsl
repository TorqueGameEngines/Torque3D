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

uniform float4x4 matrix0;
uniform float4x4 matrix1;
uniform float4x4 matrix2;
uniform float4x4 matrix3;
uniform float4x4 matrix4;
uniform float4x4 matrix5;

out float3 face_pos_x;
out float3 face_neg_x;
out float3 face_pos_y;
out float3 face_neg_y;
out float3 face_pos_z;
out float3 face_neg_z;

void main()
{
   float4 vertex = float4(float2((gl_VertexID << 1) & 2, gl_VertexID & 2) * float2(2, -2) + float2(-1, 1), 0, 1);
   gl_Position = vertex;
   correctSSP(gl_Position);
   face_pos_x = tMul(matrix0, vertex).xyz;
   face_neg_x = tMul(matrix1, vertex).xyz;
   face_pos_y = tMul(matrix2, vertex).xyz;
   face_neg_y = tMul(matrix3, vertex).xyz;
   face_pos_z = tMul(matrix4, vertex).xyz;
   face_neg_z = tMul(matrix5, vertex).xyz;
}
