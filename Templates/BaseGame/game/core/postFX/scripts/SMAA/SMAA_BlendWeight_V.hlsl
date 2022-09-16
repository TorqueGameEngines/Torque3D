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

#include "core/rendering/shaders/torque.hlsl"
#include "core/rendering/shaders/postFX/postFx.hlsl"


#include "SMAA_Params.hlsl"

uniform float4 rtParams0;


// (2)
struct v_Blend
{
   float4 hpos       : TORQUE_POSITION;
   float2 uv0        : TEXCOORD0;
   float2 pixcoord     : TEXCOORD1;
   float4 offset[3]  : TEXCOORD2;
};


                    
v_Blend main( PFXVert IN )
{
  
   v_Blend OUT;
  	
   OUT.hpos = float4(IN.pos,1.0f);
   OUT.uv0 = viewportCoordToRenderTarget( IN.uv, rtParams0 );
     
   SMAABlendingWeightCalculationVS(OUT.uv0, OUT.pixcoord, OUT.offset);   
   
   return OUT;
}
