//-----------------------------------------------------------------------------
// Copyright (c) 2015 GarageGames, LLC
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

#ifndef _TORQUE_SHADERMODEL_
#define _TORQUE_SHADERMODEL_

// Portability helpers for different shader models
#define TORQUE_POSITION SV_Position
#define TORQUE_DEPTH SV_Depth
#define TORQUE_VPOS SV_Position //note float4 compared to SM 3 where it is a float2
#define TORQUE_TARGET0 SV_Target0
#define TORQUE_TARGET1 SV_Target1
#define TORQUE_TARGET2 SV_Target2
#define TORQUE_TARGET3 SV_Target3
#define TORQUE_TARGET4 SV_Target4
#define TORQUE_TARGET5 SV_Target5
// Sampler uniforms
//1D is emulated to a 2D for now
#define TORQUE_UNIFORM_SAMPLER1D(tex,regist) uniform Texture2D texture_##tex : register(T##regist); uniform SamplerState tex : register(S##regist)
#define TORQUE_UNIFORM_SAMPLER2D(tex,regist) uniform Texture2D texture_##tex : register(T##regist); uniform SamplerState tex : register(S##regist)
#define TORQUE_UNIFORM_SAMPLER2DCMP(tex,regist) uniform Texture2D texture_##tex : register(T##regist); uniform SamplerComparisonState tex : register(S##regist)
#define TORQUE_UNIFORM_SAMPLER3D(tex,regist) uniform Texture3D texture_##tex : register(T##regist); uniform SamplerState tex : register(S##regist)
#define TORQUE_UNIFORM_SAMPLERCUBE(tex,regist) uniform TextureCube texture_##tex : register(T##regist); uniform SamplerState tex : register(S##regist)
#define TORQUE_UNIFORM_SAMPLERCUBEARRAY(tex,regist) uniform TextureCubeArray texture_##tex : register(T##regist); uniform SamplerState tex : register(S##regist)
// Sampling functions
#define TORQUE_TEX1D(tex,coords) texture_##tex.Sample(tex,coords)
#define TORQUE_TEX2D(tex,coords) texture_##tex.Sample(tex,coords)
#define TORQUE_TEX2DPROJ(tex,coords) texture_##tex.Sample(tex,coords.xy / coords.w)
#define TORQUE_TEX3D(tex,coords) texture_##tex.Sample(tex,coords)
#define TORQUE_TEXCUBE(tex,coords) texture_##tex.Sample(tex,coords)
#define TORQUE_TEXCUBEARRAY(tex,coords) texture_##tex.Sample(tex,coords)
// The mipmap LOD is specified in coord.w
#define TORQUE_TEX2DLOD(tex,coords) texture_##tex.SampleLevel(tex,coords.xy,coords.w)
#define TORQUE_TEXCUBELOD(tex,coords) texture_##tex.SampleLevel(tex,coords.xyz,coords.w)
#define TORQUE_TEXCUBEARRAYLOD(tex,coords,id,lod) texture_##tex.SampleLevel(tex,float4(coords.xyz,id),lod)
// Tex2d comparison
#define TORQUE_TEX2DCMP(tex,coords,compare) texture_##tex.SampleCmpLevelZero(tex,coords,compare)

#define TORQUE_TEX2DGATHER(tex,coords,compare,offset) texture_##tex.GatherCmp(tex,coords,compare,offset)

//helper if you want to pass sampler/texture in a function
//2D
#define TORQUE_SAMPLER2D(tex) Texture2D texture_##tex, SamplerState tex
#define TORQUE_SAMPLER2D_MAKEARG(tex) texture_##tex, tex
// Sampler comparison state - use above MAKEARG with this
#define TORQUE_SAMPLER2DCMP(tex) Texture2D texture_##tex, SamplerComparisonState tex
//Cube
#define TORQUE_SAMPLERCUBE(tex) TextureCube texture_##tex, SamplerState tex
#define TORQUE_SAMPLERCUBE_MAKEARG(tex) texture_##tex, tex
#define TORQUE_SAMPLERCUBEARRAY(tex) TextureCubeArray texture_##tex, SamplerState tex
#define TORQUE_SAMPLERCUBEARRAY_MAKEARG(tex) texture_##tex, tex

#endif // _TORQUE_SHADERMODEL_

