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

#ifndef _TORQUE_SHADERMODEL_AUTOGEN_
#define _TORQUE_SHADERMODEL_AUTOGEN_

#include "shadergen:/autogenConditioners.h"
#include "./shaderModel.hlsl"

// Portability helpers for autogenConditioners

//todo deprecate this function
#define TORQUE_DEFERRED_UNCONDITION(tex, coords) deferredUncondition(tex, texture_##tex, coords)

inline float4 UnpackDepthNormal(TORQUE_SAMPLER2D(tex), float2 screenUVVar)
{
   // Sampler g-buffer
   float4 bufferSample = TORQUE_TEX2DLOD(tex,float4(screenUVVar,0,0));
   // g-buffer unconditioner: float4(normal.X, normal.Y, depth Hi, depth Lo)
   float2 _inpXY = bufferSample.xy;
   float _xySQ = dot(_inpXY, _inpXY);
   float4 _gbUnconditionedInput = float4( sqrt(half(1.0 - (_xySQ / 4.0))) * _inpXY, -1.0 + (_xySQ / 2.0), bufferSample.a).xzyw;
   
   // Decode depth
   _gbUnconditionedInput.w = dot( bufferSample.zw, float2(1.0, 1.0/65535.0));

   return _gbUnconditionedInput;
}

#endif //_TORQUE_SHADERMODEL_AUTOGEN_
