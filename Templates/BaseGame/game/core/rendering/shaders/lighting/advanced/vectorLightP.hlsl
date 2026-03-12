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
#include "../../torque.hlsl"
#include "../../lighting.hlsl"
#include "../shadowMap/shadowMapIO_HLSL.h"

TORQUE_UNIFORM_SAMPLER2D(deferredBuffer, 0);
TORQUE_UNIFORM_SAMPLER2D(shadowMap, 1);

//contains gTapRotationTex sampler 
#include "softShadow.hlsl"
TORQUE_UNIFORM_SAMPLER2D(colorBuffer, 3);
TORQUE_UNIFORM_SAMPLER2D(matInfoBuffer, 4);

uniform float  lightBrightness;
uniform float3 lightDirection;

uniform float4 lightColor;
uniform float4 lightAmbient;

uniform float shadowSoftness;

uniform float4 atlasXOffset;
uniform float4 atlasYOffset;
uniform float4 zNearFarInvNearFar;
uniform float4 lightMapParams;
uniform float4 farPlaneScalePSSM;
uniform float4 overDarkPSSM;

uniform float2 fadeStartLength;
uniform float2 atlasScale;

uniform float4x4 eyeMat;
uniform float4x4 cameraToWorld;

// Static Shadows
uniform float4x4 worldToLightProj;
uniform float4 scaleX;
uniform float4 scaleY;
uniform float4 offsetX;
uniform float4 offsetY;

float ComputeESMFactor(float cascadeNear, float cascadeFar, int shadowMapResolution, float targetShadow = 0.1)
{
    float delta = (cascadeFar - cascadeNear) / shadowMapResolution;
    float esmFactor = -log(targetShadow) / delta;
    return esmFactor;
}

float4 AL_VectorLightShadowCast(
    TORQUE_SAMPLER2D(sourceShadowMap),
    float2 texCoord,
    float4x4 worldToLightProj,
    float3 worldPos,
    float4 scaleX,
    float4 scaleY,
    float4 offsetX,
    float4 offsetY,
    float4 farPlaneScalePSSM,
    float dotNL)
{
   // Compute shadow map coordinate
   float4 pxlPosLightProj = mul(worldToLightProj, float4(worldPos,1));
   float2 baseShadowCoord = pxlPosLightProj.xy / pxlPosLightProj.w;   
   float distToLight = pxlPosLightProj.z / pxlPosLightProj.w;

   // PSSM split handling
   float4 shadowCoordX = baseShadowCoord.xxxx;
   float4 shadowCoordY = baseShadowCoord.yyyy;
   float4 farPlaneDists = distToLight.xxxx;      
   shadowCoordX *= scaleX;
   shadowCoordY *= scaleY;
   shadowCoordX += offsetX;
   shadowCoordY += offsetY;
   farPlaneDists *= farPlaneScalePSSM;

   const float cascadeBorder = 0.02;
   float4 insideX = step(-1.0 + cascadeBorder, shadowCoordX) * step(shadowCoordX, 1.0 - cascadeBorder);
   float4 insideY = step(-1.0 + cascadeBorder, shadowCoordY) * step(shadowCoordY, 1.0 - cascadeBorder);
   float4 insideZ = step(farPlaneDists, 1.0);

   float4 cascadeValid = insideX * insideY * insideZ;

   float4 finalMask;

   finalMask.x = cascadeValid.x;
   finalMask.y = (1 - finalMask.x) * cascadeValid.y;
   finalMask.z = (1 - finalMask.x - finalMask.y) * cascadeValid.z;
   finalMask.w = 1 - finalMask.x - finalMask.y - finalMask.z;

   float3 debugColor = float3(0,0,0);

#ifdef NO_SHADOW
      debugColor = float3(1.0,1.0,1.0);
#endif

#ifdef PSSM_DEBUG_RENDER
   if ( finalMask.x > 0 )
      debugColor += float3( 1, 0, 0 );
   else if ( finalMask.y > 0 )
      debugColor += float3( 0, 1, 0 );
   else if ( finalMask.z > 0 )
      debugColor += float3( 0, 0, 1 );
   else if ( finalMask.w > 0 )
      debugColor += float3( 1, 1, 0 );
#endif

   // Compute final scale & offset for PSSM atlas
   float2 finalScale;
   finalScale.x = dot(finalMask, scaleX);
   finalScale.y = dot(finalMask, scaleY);
   float2 finalOffset;
   finalOffset.x = dot(finalMask, offsetX);
   finalOffset.y = dot(finalMask, offsetY); 

   float2 shadowCoord = baseShadowCoord * finalScale + finalOffset;

   // Convert to texcoord space and atlas
   shadowCoord = 0.5 *shadowCoord + 0.5;
   shadowCoord.y = 1.0 - shadowCoord.y;
   float2 aOffset;
   aOffset.x = dot(finalMask, atlasXOffset);
   aOffset.y = dot(finalMask, atlasYOffset);
   shadowCoord = shadowCoord * atlasScale + aOffset;

   // Compute atlas tile bounds
   float2 tileMin = aOffset;
   float2 tileMax = aOffset + atlasScale;

   // Convert filter radius to atlas UV space
   float2 filterRadiusUV = shadowSoftness * atlasScale;

   // Adjust for PSSM far plane
   float farPlaneScale = dot(farPlaneScalePSSM, finalMask);
   distToLight *= farPlaneScale;


   // Shadow map resolution per cascade
   int shadowRes = 1024; 
   float cascadeTexel = 1.0 / shadowRes;
   float4 depthBiasPSSM = float4(
      0.2 * cascadeTexel,
      0.3 * cascadeTexel,
      0.7 * cascadeTexel, 
      1.5 * cascadeTexel 
   );

   float shadow_bias = dot(finalMask, depthBiasPSSM);
   distToLight += shadow_bias;
   distToLight = saturate(distToLight);

   // Example cascade ranges 
   float cascadeNear[4] = { 0.0, 0.2, 0.5, 0.75 };
   float cascadeFar[4]  = { 0.2, 0.5, 0.75, 1.0 }; 

   float4 overDarkPSSM; 
   for(int i=0;i<4;i++) 
   { 
      overDarkPSSM[i] = ComputeESMFactor(cascadeNear[i], cascadeFar[i], shadowRes, 0.1);
   }

   return float4(
      debugColor,  
      softShadow_filter(
         TORQUE_SAMPLER2D_MAKEARG(sourceShadowMap),
         texCoord,
         shadowCoord, 
         shadowSoftness,  
         distToLight,  
         dotNL,
         dot(finalMask, overDarkPSSM) // replace this with shadowBias for pcf.
      )
   ); 
}

float4 main(FarFrustumQuadConnectP IN) : SV_TARGET
{
   //unpack normal and linear depth  
   float4 normDepth = TORQUE_DEFERRED_UNCONDITION(deferredBuffer, IN.uv0);
  
   //create surface
   Surface surface = createSurface( normDepth, TORQUE_SAMPLER2D_MAKEARG(colorBuffer),TORQUE_SAMPLER2D_MAKEARG(matInfoBuffer),
                                    IN.uv0, eyePosWorld, IN.wsEyeRay, cameraToWorld);
   if (getFlag(surface.matFlag, 2))
   {
      return surface.baseColor;
   }                        
   //create surface to light                           
   SurfaceToLight surfaceToLight = createSurfaceToLight(surface, -lightDirection);

   //light color might be changed by PSSM_DEBUG_RENDER
   float3 lightingColor = lightColor.rgb;
   
   float shadow = 1.0;
   #ifndef NO_SHADOW
   if (getFlag(surface.matFlag, 0)) //also skip if we don't recieve shadows
   {  
      // Fade out the shadow at the end of the range.
      float4 zDist = (zNearFarInvNearFar.x + zNearFarInvNearFar.y * surface.depth);
      float fadeOutAmt = ( zDist.x - fadeStartLength.x ) * fadeStartLength.y;

      float4 shadowed_colors = AL_VectorLightShadowCast( TORQUE_SAMPLER2D_MAKEARG(shadowMap), IN.uv0.xy, worldToLightProj, surface.P, scaleX, scaleY, offsetX, offsetY,
                                                             farPlaneScalePSSM, surfaceToLight.NdotL);

      shadow = shadowed_colors.a;
	  
      #ifdef PSSM_DEBUG_RENDER
	     lightingColor = shadowed_colors.rgb;
      #endif

      shadow = lerp( shadow, 1.0, saturate( fadeOutAmt ) );

      #ifdef PSSM_DEBUG_RENDER
         if ( fadeOutAmt > 1.0 )
            lightingColor = 1.0;
      #endif
   }
   #endif //NO_SHADOW
   
   #ifdef DIFFUSE_LIGHT_VIZ
      float3 factor = lightingColor.rgb * max(surfaceToLight.NdotL, 0) * shadow * lightBrightness;
      float3 diffuse = BRDF_GetDebugDiffuse(surface,surfaceToLight) * factor;

      float3 final = max(0.0f, diffuse);
      return float4(final, 0);
   #endif

   #ifdef SPECULAR_LIGHT_VIZ
      float3 factor = lightingColor.rgb * max(surfaceToLight.NdotL, 0) * shadow * lightBrightness;
      float3 spec = BRDF_GetDebugSpecular(surface, surfaceToLight) * factor;

      float3 final = max(0.0f, factor);
      return float4(final, 0);
   #endif

   #ifdef DETAIL_LIGHTING_VIZ
      float3 factor = lightingColor.rgb * max(surfaceToLight.NdotL, 0) * shadow * lightBrightness;
      float3 diffuse = BRDF_GetDebugDiffuse(surface,surfaceToLight) * factor;
      float3 spec = BRDF_GetDebugSpecular(surface,surfaceToLight) * factor;

      float3 final = max(0.0f, diffuse + spec);
      return float4(final,0);
   #endif

   //get directional light contribution   
   float3 lighting = getDirectionalLight(surface, surfaceToLight, lightingColor.rgb, lightBrightness, shadow);

   return float4(lighting, 0);
}
