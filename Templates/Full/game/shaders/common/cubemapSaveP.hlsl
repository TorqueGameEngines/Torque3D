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

struct Fragout
{
   float4 target0 : TORQUE_TARGET0;
   float4 target1 : TORQUE_TARGET1;
   float4 target2 : TORQUE_TARGET2;
   float4 target3 : TORQUE_TARGET3;
   float4 target4 : TORQUE_TARGET4;
   float4 target5 : TORQUE_TARGET5;
};

TORQUE_UNIFORM_SAMPLERCUBE(cubemapTex, 0);

//-----------------------------------------------------------------------------
// Main                                                                        
//-----------------------------------------------------------------------------
Fragout main(Conn In)
{
   Fragout Out;

   Out.target0 = TORQUE_TEXCUBE(cubemapTex, In.face_pos_x);
   Out.target1 = TORQUE_TEXCUBE(cubemapTex, In.face_neg_x);
   Out.target2 = TORQUE_TEXCUBE(cubemapTex, In.face_pos_y);
   Out.target3 = TORQUE_TEXCUBE(cubemapTex, In.face_neg_y);
   Out.target4 = TORQUE_TEXCUBE(cubemapTex, In.face_pos_z);
   Out.target5 = TORQUE_TEXCUBE(cubemapTex, In.face_neg_z);

   return Out;
}
