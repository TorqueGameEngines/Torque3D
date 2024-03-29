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

#ifdef SHADOW_CUBE

   float3 decodeShadowCoord( float3 shadowCoord )
   {
      return shadowCoord;
   }

   float4 shadowSample( TORQUE_SAMPLERCUBE(shadowMap), float3 shadowCoord )
   {
      return TORQUE_TEXCUBE( shadowMap, shadowCoord );
   }
  
#else

   float3 decodeShadowCoord( float3 paraVec )
   {
      // Flip y and z
      paraVec = paraVec.xzy;
      
      #ifndef SHADOW_PARABOLOID

         bool calcBack = (paraVec.z < 0.0);
         if ( calcBack )
         {
            paraVec.z = paraVec.z * -1.0;
            
            #ifdef SHADOW_DUALPARABOLOID
               paraVec.x = -paraVec.x;
            #endif
         }

      #endif

      float3 shadowCoord;
      shadowCoord.x = (paraVec.x / (2*(1 + paraVec.z))) + 0.5;
      shadowCoord.y = 1-((paraVec.y / (2*(1 + paraVec.z))) + 0.5);
      shadowCoord.z = 0;
      
      // adjust the co-ordinate slightly if it is near the extent of the paraboloid
      // this value was found via experementation
      // NOTE: this is wrong, it only biases in one direction, not towards the uv 
      // center ( 0.5 0.5 ).
      float offsetVal = 0.95;
      shadowCoord.xy *= offsetVal;
      shadowCoord.xy += (1.0-offsetVal).xx / 2.0;

      #ifndef SHADOW_PARABOLOID

         // If this is the back, offset in the atlas
         if ( calcBack )
            shadowCoord.x += 1.0;
         
         // Atlasing front and back maps, so scale
         shadowCoord.x *= 0.5;

      #endif

      return shadowCoord;
   }

#endif

TORQUE_UNIFORM_SAMPLER2D(deferredBuffer, 0);
#ifdef SHADOW_CUBE
TORQUE_UNIFORM_SAMPLERCUBE(shadowMap, 1);
#else
TORQUE_UNIFORM_SAMPLER2D(shadowMap, 1);
#endif
//contains gTapRotationTex sampler 
#include "softShadow.hlsl"
TORQUE_UNIFORM_SAMPLER2D(colorBuffer, 3);
TORQUE_UNIFORM_SAMPLER2D(matInfoBuffer, 4);

/// The texture for cookie rendering.
#ifdef SHADOW_CUBE
TORQUE_UNIFORM_SAMPLERCUBE(cookieMap, 5);
#else
TORQUE_UNIFORM_SAMPLER2D(cookieMap, 5);
#endif

#ifdef UES_PHOTOMETRIC_MASK
TORQUE_UNIFORM_SAMPLER1D(iesProfile, 6);
#endif

uniform float4 rtParams0;
uniform float4 lightColor;

uniform float  lightBrightness;
uniform float3 lightPosition;
uniform float3 lightDirection;

uniform float4 lightMapParams;
uniform float4 vsFarPlane;
uniform float4 lightParams;

uniform float lightRange;
uniform float lightInvSqrRange;
uniform float shadowSoftness;
uniform float4x4 worldToCamera;
uniform float3x3 worldToLightProj;

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
      float distToLight = dist / lightRange;
      SurfaceToLight surfaceToLight = createSurfaceToLight(surface, L);
      float3 lightCol = lightColor.rgb;
      float shadow = 1.0;
   #ifndef NO_SHADOW
   if (getFlag(surface.matFlag, 0)) //also skip if we don't recieve shadows
   {
      #ifdef SHADOW_CUBE

         // TODO: We need to fix shadow cube to handle soft shadows!
         float occ = TORQUE_TEXCUBE( shadowMap, mul( worldToLightProj, -surfaceToLight.L ) ).r;
         shadow = saturate( exp( lightParams.y * ( occ - distToLight ) ) );

      #else
         float2 shadowCoord = decodeShadowCoord( mul( worldToLightProj, -surfaceToLight.L ) ).xy;
         shadow = softShadow_filter(TORQUE_SAMPLER2D_MAKEARG(shadowMap), ssPos.xy, shadowCoord, shadowSoftness, distToLight, surfaceToLight.NdotL, lightParams.y);
      #endif
   }
   #endif // !NO_SHADOW
   #ifdef USE_COOKIE_TEX
      // Lookup the cookie sample.
      #ifdef SHADOW_CUBE
      float4 cookie = TORQUE_TEXCUBE(cookieMap, mul(worldToLightProj, -surfaceToLight.L));
      #else
      float2 cookieCoord = decodeShadowCoord( mul( worldToLightProj, -surfaceToLight.L ) ).xy;
      float4 cookie = TORQUE_TEX2D(cookieMap, cookieCoord);
      #endif
      // Multiply the light with the cookie tex.
      lightCol *= cookie.rgb;
      // Use a maximum channel luminance to attenuate 
      // the lighting else we get specular in the dark
      // regions of the cookie texture.
      lightCol *= max(cookie.r, max(cookie.g, cookie.b));
   #endif
   #ifdef DIFFUSE_LIGHT_VIZ
      float attenuation = getDistanceAtt(surfaceToLight.Lu, radius);
      float3 factor = lightColor * max(surfaceToLight.NdotL, 0) * shadow * lightIntensity * attenuation;

      float3 diffuse = BRDF_GetDebugDiffuse(surface,surfaceToLight) * factor;
      float3 final = max(0.0f, diffuse);
      return float4(final, 0);
   #endif

   #ifdef SPECULAR_LIGHT_VIZ
      float attenuation = getDistanceAtt(surfaceToLight.Lu, radius);
      float3 factor = lightColor * max(surfaceToLight.NdotL, 0) * shadow * lightIntensity * attenuation;

      float3 diffuse = BRDF_GetDebugSpecular(surface,surfaceToLight) * factor;
      float3 final = max(0.0f, diffuse);
      return float4(final, 0);
   #endif

   #ifdef DETAIL_LIGHTING_VIZ
      float attenuation = getDistanceAtt(surfaceToLight.Lu, radius);
      float3 factor = lightColor * max(surfaceToLight.NdotL, 0) * shadow * lightIntensity * attenuation;

      float3 diffuse = BRDF_GetDiffuse(surface,surfaceToLight) * factor;
      float3 spec = BRDF_GetSpecular(surface,surfaceToLight) * factor;

      float3 final = max(float3(0.0f), diffuse + spec * surface.F);
      return final;
   #endif

   #ifdef UES_PHOTOMETRIC_MASK
      // Lookup the cookie sample.d
      float cosTheta = dot(-surfaceToLight.L, lightDirection); 
      float angle = acos(cosTheta) * ( M_1OVER_PI_F); 
      float iesMask = TORQUE_TEX1D(iesProfile, angle).r;
      // Multiply the light with the iesMask tex.
      shadow *= iesMask;
   #endif
   
      //get punctual light contribution   
      lighting = getPunctualLight(surface, surfaceToLight, lightCol, lightBrightness, lightInvSqrRange, shadow);

   }
   

   return float4(lighting, 0);
}
