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

#include "shaderModel.hlsl"

struct Conn
{
   float4 hpos : TORQUE_POSITION;
   float3 face_pos_x : TEXCOORD0;
   float3 face_neg_x : TEXCOORD1;
   float3 face_pos_y : TEXCOORD2;
   float3 face_neg_y : TEXCOORD3;
   float3 face_pos_z : TEXCOORD4;
   float3 face_neg_z : TEXCOORD5;
};

uniform float4x4 matrix0;
uniform float4x4 matrix1;
uniform float4x4 matrix2;
uniform float4x4 matrix3;
uniform float4x4 matrix4;
uniform float4x4 matrix5;

Conn main(uint id: SV_VertexID)
{
   Conn Out;
   float4 vertex = float4(float2((id << 1) & 2, id & 2) * float2(2, -2) + float2(-1, 1), 0, 1);
   Out.hpos = vertex;
   Out.face_pos_x = mul(matrix0, vertex).xyz;
   Out.face_neg_x = mul(matrix1, vertex).xyz;
   Out.face_pos_y = mul(matrix2, vertex).xyz;
   Out.face_neg_y = mul(matrix3, vertex).xyz;
   Out.face_pos_z = mul(matrix4, vertex).xyz;
   Out.face_neg_z = mul(matrix5, vertex).xyz;

   return Out;
}
