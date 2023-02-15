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
//contains gTapRotationTex sampler 
#include "softShadow.hlsl"
TORQUE_UNIFORM_SAMPLER2D(colorBuffer, 3);
TORQUE_UNIFORM_SAMPLER2D(matInfoBuffer, 4);
#ifdef USE_COOKIE_TEX
/// The texture for cookie rendering.
TORQUE_UNIFORM_SAMPLER2D(cookieMap, 5);

#endif
uniform float4 rtParams0;

uniform float  lightBrightness;
uniform float3 lightPosition;

uniform float4 lightColor;

uniform float lightRange;
uniform float lightInvSqrRange;
uniform float3 lightDirection;

uniform float2 lightSpotParams;
uniform float4 lightMapParams;
uniform float4 vsFarPlane;
uniform float4x4 worldToLightProj;
uniform float4 lightParams;

uniform float shadowSoftness;

uniform float4x4 cameraToWorld;
uniform float4x4 worldToCamera;

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
   Surface surface = createSurface( normDepth, TORQUE_SAMPLER2D_MAKEARG(colorBuffer),TORQUE_SAMPLER2D_MAKEARG(matInfoBuffer),
                                    uvScene, eyePosWorld, wsEyeRay, cameraToWorld);
   if (getFlag(surface.matFlag, 2))
   {
      return surface.baseColor;
   } 
   float3 L = lightPosition - surface.P;
   float dist = length(L);
   float3 lighting = 0.0.xxx;
   [branch]
	if(dist < lightRange)
	{     
      SurfaceToLight surfaceToLight = createSurfaceToLight(surface, L);
      float3 lightCol = lightColor.rgb;
         
      float shadow = 1.0; 
      #ifndef NO_SHADOW      
      if (getFlag(surface.matFlag, 0)) //also skip if we don't recieve shadows
      {  
         // Get the shadow texture coordinate
         float4 pxlPosLightProj = mul( worldToLightProj, float4( surface.P, 1 ) );
         float2 shadowCoord = ( ( pxlPosLightProj.xy / pxlPosLightProj.w ) * 0.5 ) + float2( 0.5, 0.5 );
         shadowCoord.y = 1.0f - shadowCoord.y;
         //distance to light in shadow map space
         float distToLight = pxlPosLightProj.z / lightRange;
         shadow = softShadow_filter(TORQUE_SAMPLER2D_MAKEARG(shadowMap), ssPos.xy, shadowCoord, shadowSoftness, distToLight, surfaceToLight.NdotL, lightParams.y);
         #ifdef USE_COOKIE_TEX
            // Lookup the cookie sample.
            float4 cookie = TORQUE_TEX2D(cookieMap, shadowCoord);
            // Multiply the light with the cookie tex.
            lightCol *= cookie.rgb;
            // Use a maximum channel luminance to attenuate 
            // the lighting else we get specular in the dark
            // regions of the cookie texture.
            lightCol *= max(cookie.r, max(cookie.g, cookie.b));
         #endif
      }
      #endif

   #ifdef DIFFUSE_LIGHT_VIZ
      float attenuation = getDistanceAtt(surfaceToLight.Lu, radius);
      float3 factor = lightColor * max(surfaceToLight.NdotL, 0) * shadow * lightIntensity * attenuation;

      float3 diffuse = BRDF_GetDebugDiffuse(surface,surfaceToLight) * factor;
      float3 final = max(0.0f, diffuse) * getSpotAngleAtt(-surfaceToLight.L, lightDirection, lightSpotParams );
      return float4(final, 0);
   #endif

   #ifdef SPECULAR_LIGHT_VIZ
   float attenuation = getDistanceAtt(surfaceToLight.Lu, radius);
      float3 factor = lightColor * max(surfaceToLight.NdotL, 0) * shadow * lightIntensity * attenuation;

      float3 diffuse = BRDF_GetDebugSpecular(surface,surfaceToLight) * factor;
      float3 final = max(0.0f, diffuse) * getSpotAngleAtt(-surfaceToLight.L, lightDirection, lightSpotParams );
      return float4(final, 0);
   #endif

   #ifdef DETAIL_LIGHTING_VIZ
      float attenuation = getDistanceAtt(surfaceToLight.Lu, radius);
      float3 factor = lightColor * max(surfaceToLight.NdotL, 0) * shadow * lightIntensity * attenuation;

      float3 diffuse = BRDF_GetDiffuse(surface,surfaceToLight) * factor;
      float3 spec = BRDF_GetSpecular(surface,surfaceToLight) * factor;

      vec3 final = max(float3(0.0f), diffuse + spec * surface.F) * getSpotAngleAtt(-surfaceToLight.L, lightDirection, lightSpotParams );
      return final;
   #endif

      //get Punctual light contribution   
      lighting = getPunctualLight(surface, surfaceToLight, lightCol, lightBrightness, lightInvSqrRange, shadow);
      //get spot angle attenuation
      lighting *= getSpotAngleAtt(-surfaceToLight.L, lightDirection, lightSpotParams );
   }
   
   return float4(lighting, 0);
}
