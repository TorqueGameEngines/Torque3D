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
#include "softShadow.hlsl"

TORQUE_UNIFORM_SAMPLER2D(deferredBuffer, 0);
TORQUE_UNIFORM_SAMPLER2D(shadowMap, 1);
TORQUE_UNIFORM_SAMPLER2D(dynamicShadowMap, 2);

#ifdef USE_SSAO_MASK
TORQUE_UNIFORM_SAMPLER2D(ssaoMask, 3);
uniform float4 rtParams3;
#endif

TORQUE_UNIFORM_SAMPLER2D(colorBuffer, 6);
TORQUE_UNIFORM_SAMPLER2D(matInfoBuffer, 7);

uniform float  lightBrightness;
uniform float3 lightDirection;

uniform float4 lightColor;
uniform float4 lightAmbient;

uniform float shadowSoftness;
uniform float3 eyePosWorld;

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
// Dynamic Shadows
uniform float4x4 dynamicWorldToLightProj;
uniform float4 dynamicScaleX;
uniform float4 dynamicScaleY;
uniform float4 dynamicOffsetX;
uniform float4 dynamicOffsetY;
uniform float4 dynamicFarPlaneScalePSSM;

float4 AL_VectorLightShadowCast( TORQUE_SAMPLER2D(sourceShadowMap),
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

      // Distance to light, in shadowmap space
      float distToLight = pxlPosLightProj.z / pxlPosLightProj.w;
         
      // Figure out which split to sample from.  Basically, we compute the shadowmap sample coord
      // for all of the splits and then check if its valid.  
      float4 shadowCoordX = baseShadowCoord.xxxx;
      float4 shadowCoordY = baseShadowCoord.yyyy;
      float4 farPlaneDists = distToLight.xxxx;      
      shadowCoordX *= scaleX;
      shadowCoordY *= scaleY;
      shadowCoordX += offsetX;
      shadowCoordY += offsetY;
      farPlaneDists *= farPlaneScalePSSM;
      
      // If the shadow sample is within -1..1 and the distance 
      // to the light for this pixel is less than the far plane 
      // of the split, use it.
      float4 finalMask;
      if (  shadowCoordX.x > -0.99 && shadowCoordX.x < 0.99 && 
            shadowCoordY.x > -0.99 && shadowCoordY.x < 0.99 &&
            farPlaneDists.x < 1.0 )
         finalMask = float4(1, 0, 0, 0);

      else if (   shadowCoordX.y > -0.99 && shadowCoordX.y < 0.99 &&
                  shadowCoordY.y > -0.99 && shadowCoordY.y < 0.99 && 
                  farPlaneDists.y < 1.0 )
         finalMask = float4(0, 1, 0, 0);

      else if (   shadowCoordX.z > -0.99 && shadowCoordX.z < 0.99 && 
                  shadowCoordY.z > -0.99 && shadowCoordY.z < 0.99 && 
                  farPlaneDists.z < 1.0 )
         finalMask = float4(0, 0, 1, 0);
         
      else
         finalMask = float4(0, 0, 0, 1);
         
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

      // Here we know what split we're sampling from, so recompute the texcoord location
      // Yes, we could just use the result from above, but doing it this way actually saves
      // shader instructions.
      float2 finalScale;
      finalScale.x = dot(finalMask, scaleX);
      finalScale.y = dot(finalMask, scaleY);

      float2 finalOffset;
      finalOffset.x = dot(finalMask, offsetX);
      finalOffset.y = dot(finalMask, offsetY);

      float2 shadowCoord;                  
      shadowCoord = baseShadowCoord * finalScale;      
      shadowCoord += finalOffset;

      // Convert to texcoord space
      shadowCoord = 0.5 * shadowCoord + float2(0.5, 0.5);
      shadowCoord.y = 1.0f - shadowCoord.y;

      // Move around inside of atlas 
      float2 aOffset;
      aOffset.x = dot(finalMask, atlasXOffset);
      aOffset.y = dot(finalMask, atlasYOffset);

      shadowCoord *= atlasScale;
      shadowCoord += aOffset;
              
      // Each split has a different far plane, take this into account.
      float farPlaneScale = dot( farPlaneScalePSSM, finalMask );
      distToLight *= farPlaneScale;

      return float4(debugColor, softShadow_filter(  TORQUE_SAMPLER2D_MAKEARG(sourceShadowMap), texCoord, shadowCoord, farPlaneScale * shadowSoftness,
                                distToLight, dotNL, dot( finalMask, overDarkPSSM ) ) );
};


float4 main(FarFrustumQuadConnectP IN) : SV_TARGET
{
   //unpack normal and linear depth  
   float4 normDepth = TORQUE_DEFERRED_UNCONDITION(deferredBuffer, IN.uv0);
  
   //create surface
   Surface surface = createSurface( normDepth, TORQUE_SAMPLER2D_MAKEARG(colorBuffer),TORQUE_SAMPLER2D_MAKEARG(matInfoBuffer),
                                    IN.uv0, eyePosWorld, IN.wsEyeRay, cameraToWorld);
                                    
   //early out if emissive
   if (getFlag(surface.matFlag, 0))
   {   
      return 0.0.xxxx;
	}
   
   //create surface to light                           
   SurfaceToLight surfaceToLight = createSurfaceToLight(surface, -lightDirection);

   //light color might be changed by PSSM_DEBUG_RENDER
   float3 lightingColor = lightColor.rgb;
   
   #ifdef NO_SHADOW
      float shadow = 1.0;
   #else

      // Fade out the shadow at the end of the range.
      float4 zDist = (zNearFarInvNearFar.x + zNearFarInvNearFar.y * surface.depth);
      float fadeOutAmt = ( zDist.x - fadeStartLength.x ) * fadeStartLength.y;

      float4 static_shadowed_colors = AL_VectorLightShadowCast( TORQUE_SAMPLER2D_MAKEARG(shadowMap), IN.uv0.xy, worldToLightProj, surface.P, scaleX, scaleY, offsetX, offsetY,
                                                             farPlaneScalePSSM, surfaceToLight.NdotL);

      float4 dynamic_shadowed_colors = AL_VectorLightShadowCast( TORQUE_SAMPLER2D_MAKEARG(dynamicShadowMap), IN.uv0.xy, dynamicWorldToLightProj, surface.P, dynamicScaleX,
                                                              dynamicScaleY, dynamicOffsetX, dynamicOffsetY, dynamicFarPlaneScalePSSM, surfaceToLight.NdotL);

      float static_shadowed = static_shadowed_colors.a;
      float dynamic_shadowed = dynamic_shadowed_colors.a;
	  
      #ifdef PSSM_DEBUG_RENDER
	     lightingColor = static_shadowed_colors.rgb*0.5+dynamic_shadowed_colors.rgb*0.5;
      #endif

      static_shadowed = lerp( static_shadowed, 1.0, saturate( fadeOutAmt ) );
      dynamic_shadowed = lerp( dynamic_shadowed, 1.0, saturate( fadeOutAmt ) );

      float shadow = min(static_shadowed, dynamic_shadowed);

      #ifdef PSSM_DEBUG_RENDER
         if ( fadeOutAmt > 1.0 )
            lightingColor = 1.0;
      #endif

   #endif //NO_SHADOW
   // Sample the AO texture.
   #ifdef USE_SSAO_MASK
      surface.ao *= 1.0 - TORQUE_TEX2D( ssaoMask, viewportCoordToRenderTarget( IN.uv0.xy, rtParams3 ) ).r;
   #endif
   
   //get directional light contribution   
   float3 lighting = getDirectionalLight(surface, surfaceToLight, lightingColor.rgb, lightBrightness, shadow);

   return float4(lighting, 0);
}
