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

#include "../../shaderModel.hlsl"
#include "../../shaderModelAutoGen.hlsl"

#include "farFrustumQuad.hlsl"
#include "../../lighting.hlsl"
#include "../shadowMap/shadowMapIO_HLSL.h"
#include "softShadow.hlsl"
#include "../../torque.hlsl"

struct ConvexConnectP
{
   float4 pos : TORQUE_POSITION;
   float4 wsEyeDir : TEXCOORD0;
   float4 ssPos : TEXCOORD1;
   float4 vsEyeDir : TEXCOORD2;
};

TORQUE_UNIFORM_SAMPLER2D(deferredBuffer, 0);
TORQUE_UNIFORM_SAMPLER2D(shadowMap, 1);
TORQUE_UNIFORM_SAMPLER2D(dynamicShadowMap,2);

#ifdef USE_COOKIE_TEX

/// The texture for cookie rendering.
TORQUE_UNIFORM_SAMPLER2D(cookieMap, 3);

#endif
TORQUE_UNIFORM_SAMPLER2D(colorBuffer, 5);
TORQUE_UNIFORM_SAMPLER2D(matInfoBuffer, 6);

uniform float4 rtParams0;

uniform float  lightBrightness;
uniform float3 lightPosition;

uniform float4 lightColor;

uniform float  lightRange;
uniform float3 lightDirection;

uniform float4 lightSpotParams;
uniform float4 lightMapParams;
uniform float4 vsFarPlane;
uniform float4x4 worldToLightProj;
uniform float4 lightParams;

uniform float shadowSoftness;
uniform float3 eyePosWorld;

uniform float4x4 cameraToWorld;

float4 main(   ConvexConnectP IN ) : SV_TARGET
{   
   // Compute scene UV
   float3 ssPos = IN.ssPos.xyz / IN.ssPos.w;
   float2 uvScene = getUVFromSSPos(ssPos, rtParams0);

   //unpack normal and linear depth 
   float4 normDepth = TORQUE_DEFERRED_UNCONDITION(deferredBuffer, uvScene);
      
   //eye ray WS/VS
   float3 vsEyeRay = getDistanceVectorToPlane( -vsFarPlane.w, IN.vsEyeDir.xyz, vsFarPlane );
   float3 wsEyeRay = mul(cameraToWorld, float4(vsEyeRay, 0)).xyz;

   //create surface
   Surface surface = CreateSurface( normDepth, TORQUE_SAMPLER2D_MAKEARG(colorBuffer),TORQUE_SAMPLER2D_MAKEARG(matInfoBuffer),
                                    uvScene, eyePosWorld, wsEyeRay, cameraToWorld);

   //early out if emissive
   if (getFlag(surface.matFlag, 0))
   {   
      return 0.0.xxxx;
	}
 
   float3 L = lightPosition - surface.P;
   float dist = length(L);
   float3 result = 0.0.xxx;
   [branch]
	if (dist < lightRange)
	{     
      float distToLight = dist / lightRange;
      float spotFactor = dot(L, lightDirection);
		float spotCutOff = lightSpotParams.x;
      [branch]
		//if (spotFactor > spotCutOff)
		{
			SurfaceToLight surfaceToLight = CreateSurfaceToLight(surface, L); 
         float shadowed = 1.0;
         float3 lightcol = lightColor.rgb;
         //get spot light contribution   
         result = GetSpotLight(surface, surfaceToLight, lightcol, lightBrightness, dist, lightRange, shadowed);
         //result = float3(1.0,0,0);
      }
   }
   
   return float4(result, 0);
}
