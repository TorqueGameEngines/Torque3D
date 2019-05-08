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

#include "../../../gl/hlslCompat.glsl"
#include "shadergen:/autogenConditioners.h"
#include "farFrustumQuad.glsl"
#include "../../../gl/torque.glsl"
#include "../../../gl/lighting.glsl"
#include "../../shadowMap/shadowMapIO_GLSL.h"
#include "softShadow.glsl"
#line 30
in vec4 hpos;
in vec2 uv0;
in vec3 wsEyeRay;
in vec3 vsEyeRay;

uniform sampler2D deferredBuffer;
uniform sampler2D shadowMap;
uniform sampler2D dynamicShadowMap;

#ifdef USE_SSAO_MASK
uniform sampler2D ssaoMask ;
uniform vec4 rtParams3;
#endif

uniform sampler2D colorBuffer;
uniform sampler2D matInfoBuffer;             
uniform float  lightBrightness;
uniform vec3 lightDirection;
uniform vec4 lightColor;
uniform vec4 lightAmbient; 

uniform float shadowSoftness;
uniform vec3 eyePosWorld; 

uniform vec4 atlasXOffset;
uniform vec4 atlasYOffset;
uniform vec4 zNearFarInvNearFar;
uniform vec4 lightMapParams;
uniform vec4 farPlaneScalePSSM;
uniform vec4 overDarkPSSM;

uniform vec2 fadeStartLength;
uniform vec2 atlasScale;

uniform mat4 eyeMat;
uniform mat4 cameraToWorld;

//static shadowMap
uniform mat4 worldToLightProj;
uniform vec4 scaleX;
uniform vec4 scaleY;
uniform vec4 offsetX;
uniform vec4 offsetY;

//dynamic shadowMap
uniform mat4 dynamicWorldToLightProj;
uniform vec4 dynamicScaleX;
uniform vec4 dynamicScaleY;
uniform vec4 dynamicOffsetX;
uniform vec4 dynamicOffsetY;
uniform vec4 dynamicFarPlaneScalePSSM;

vec4 AL_VectorLightShadowCast( sampler2D _sourceShadowMap,
                                vec2 _texCoord,
                                mat4 _worldToLightProj,
                                vec3 _worldPos,
                                vec4 _scaleX,
                                vec4 _scaleY,
                                vec4 _offsetX,
                                vec4 _offsetY,
                                vec4 _farPlaneScalePSSM,
                                float _dotNL)
{

      // Compute shadow map coordinate
      vec4 pxlPosLightProj = tMul(_worldToLightProj, vec4(_worldPos,1));
      vec2 baseShadowCoord = pxlPosLightProj.xy / pxlPosLightProj.w;   

      // Distance to light, in shadowmap space
      float distToLight = pxlPosLightProj.z / pxlPosLightProj.w;
         
      // Figure out which split to sample from.  Basically, we compute the shadowMap sample coord
      // for all of the splits and then check if its valid.  
      vec4 shadowCoordX = baseShadowCoord.xxxx;
      vec4 shadowCoordY = baseShadowCoord.yyyy;
      vec4 farPlaneDists = vec4(distToLight);      
      shadowCoordX *= _scaleX;
      shadowCoordY *= _scaleY;
      shadowCoordX += _offsetX;
      shadowCoordY += _offsetY;
      farPlaneDists *= _farPlaneScalePSSM;
      
      // If the shadow sample is within -1..1 and the distance 
      // to the light for this pixel is less than the far plane 
      // of the split, use it.
      vec4 finalMask;
      if (  shadowCoordX.x > -0.99 && shadowCoordX.x < 0.99 && 
            shadowCoordY.x > -0.99 && shadowCoordY.x < 0.99 &&
            farPlaneDists.x < 1.0 )
         finalMask = vec4(1, 0, 0, 0);

      else if (   shadowCoordX.y > -0.99 && shadowCoordX.y < 0.99 &&
                  shadowCoordY.y > -0.99 && shadowCoordY.y < 0.99 && 
                  farPlaneDists.y < 1.0 )
         finalMask = vec4(0, 1, 0, 0);

      else if (   shadowCoordX.z > -0.99 && shadowCoordX.z < 0.99 && 
                  shadowCoordY.z > -0.99 && shadowCoordY.z < 0.99 && 
                  farPlaneDists.z < 1.0 )
         finalMask = vec4(0, 0, 1, 0);
         
      else
         finalMask = vec4(0, 0, 0, 1);
         
      vec3 debugColor = vec3(0,0,0);
   
      #ifdef NO_SHADOW
         debugColor = vec3(1.0,1.0,1.0);
      #endif

      #ifdef PSSM_DEBUG_RENDER
         if ( finalMask.x > 0 )
            debugColor += vec3( 1, 0, 0 );
         else if ( finalMask.y > 0 )
            debugColor += vec3( 0, 1, 0 );
         else if ( finalMask.z > 0 )
            debugColor += vec3( 0, 0, 1 );
         else if ( finalMask.w > 0 )
            debugColor += vec3( 1, 1, 0 );
      #endif

      // Here we know what split we're sampling from, so recompute the _texCoord location
      // Yes, we could just use the result from above, but doing it this way actually saves
      // shader instructions.
      vec2 finalScale;
      finalScale.x = dot(finalMask, _scaleX);
      finalScale.y = dot(finalMask, _scaleY);

      vec2 finalOffset;
      finalOffset.x = dot(finalMask, _offsetX);
      finalOffset.y = dot(finalMask, _offsetY);

      vec2 shadowCoord;                  
      shadowCoord = baseShadowCoord * finalScale;      
      shadowCoord += finalOffset;

      // Convert to texcoord space
      shadowCoord = 0.5 * shadowCoord + vec2(0.5, 0.5);
      shadowCoord.y = 1.0f - shadowCoord.y;

      // Move around inside of atlas 
      vec2 aOffset;
      aOffset.x = dot(finalMask, atlasXOffset);
      aOffset.y = dot(finalMask, atlasYOffset);

      shadowCoord *= atlasScale;
      shadowCoord += aOffset;
              
      // Each split has a different far plane, take this into account.
      float farPlaneScale = dot( _farPlaneScalePSSM, finalMask );
      distToLight *= farPlaneScale;
      
      return vec4(debugColor,
                  softShadow_filter(  _sourceShadowMap,
                  _texCoord,
                  shadowCoord,
                  farPlaneScale * shadowSoftness,
                  distToLight,
                  _dotNL,
                  dot( finalMask, overDarkPSSM ) ) );
}

out vec4 OUT_col;
void main()             
{
   //unpack normal and linear depth  
   vec4 normDepth = deferredUncondition(deferredBuffer, uv0);
  
   //create surface
   Surface surface = createSurface( normDepth, colorBuffer, matInfoBuffer,
                                    uv0, eyePosWorld, wsEyeRay, cameraToWorld);
   
   //early out if emissive
   if (getFlag(surface.matFlag, 0))
   {
      OUT_col = vec4(0);
	  return;
	}
	
   //create surface to light                           
   SurfaceToLight surfaceToLight = createSurfaceToLight(surface, -lightDirection);

   //light color might be changed by PSSM_DEBUG_RENDER
   vec3 lightingColor = lightColor.rgb;
   
   #ifdef NO_SHADOW
      float shadow = 1.0;
   #else

      // Fade out the shadow at the end of the range.
      vec4 zDist = vec4(zNearFarInvNearFar.x + zNearFarInvNearFar.y * surface.depth);
      float fadeOutAmt = ( zDist.x - fadeStartLength.x ) * fadeStartLength.y;

      vec4 static_shadowed_colors = AL_VectorLightShadowCast( shadowMap, uv0.xy, worldToLightProj, surface.P, scaleX, scaleY, offsetX, offsetY,
                                                             farPlaneScalePSSM, surfaceToLight.NdotL);

      vec4 dynamic_shadowed_colors = AL_VectorLightShadowCast( dynamicShadowMap, uv0.xy, dynamicWorldToLightProj, surface.P, dynamicScaleX,
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
      surface.ao *= 1.0 - texture( ssaoMask, viewportCoordToRenderTarget( uv0.xy, rtParams3 ) ).r;
   #endif

   //get directional light contribution   
   vec3 lighting = getDirectionalLight(surface, surfaceToLight, lightingColor.rgb, lightBrightness, shadow);

   OUT_col = vec4(lighting, 0);
}
