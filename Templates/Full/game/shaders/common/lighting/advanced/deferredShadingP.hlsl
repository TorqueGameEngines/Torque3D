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

#include "../../postfx/postFx.hlsl"
#include "shaders/common/torque.hlsl"
#include "shaders/common/lighting.hlsl"

TORQUE_UNIFORM_SAMPLER2D(colorBufferTex,0);
TORQUE_UNIFORM_SAMPLER2D(diffuseLightingBuffer,1);
TORQUE_UNIFORM_SAMPLER2D(matInfoTex,2);
TORQUE_UNIFORM_SAMPLER2D(specularLightingBuffer,3);
TORQUE_UNIFORM_SAMPLER2D(deferredTex,4);

uniform float4x4 cameraToWorld;
uniform float3 eyePosWorld;

//TODO add in emission
float4 main( PFXVertToPix IN ) : TORQUE_TARGET0
{
   //sky and editor background check
   float4 normDepth = UnpackDepthNormal(TORQUE_SAMPLER2D_MAKEARG(deferredTex), IN.uv0);
   if (normDepth.a>0.9999)
      return float4(0,0,0,0);
   
   //create surface
   Surface surface = CreateSurface( normDepth, TORQUE_SAMPLER2D_MAKEARG(colorBufferTex),TORQUE_SAMPLER2D_MAKEARG(matInfoTex),
                                    IN.uv0, eyePosWorld, IN.wsEyeRay, cameraToWorld);
	  
   float4 diffuse = TORQUE_TEX2DLOD( diffuseLightingBuffer, float4(IN.uv0,0,0)); 
   float4 specular = TORQUE_TEX2DLOD( specularLightingBuffer, float4(IN.uv0,0,0));

   float3 sceneColor = (surface.albedo * diffuse.rgb) + (surface.F * specular.rgb) * surface.ao;
   
   return float4(sceneColor.rgb, 1.0);
}
