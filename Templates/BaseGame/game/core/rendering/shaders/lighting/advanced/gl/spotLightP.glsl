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
#include "farFrustumQuad.glsl"
#include "../../shadowMap/shadowMapIO_GLSL.h"
#include "shadergen:/autogenConditioners.h"
#include "../../../gl/lighting.glsl"
#include "../../../gl/torque.glsl"

in vec4 wsEyeDir;
in vec4 ssPos;
in vec4 vsEyeDir;
in vec4 color;

uniform sampler2D deferredBuffer;
uniform sampler2D shadowMap;
//contains gTapRotationTex sampler 
#include "softShadow.glsl"
uniform sampler2D colorBuffer;
uniform sampler2D matInfoBuffer;
#ifdef USE_COOKIE_TEX
/// The texture for cookie rendering.
uniform sampler2D cookieMap;
#endif

uniform vec4 rtParams0;

uniform float  lightBrightness;
uniform vec3 lightPosition;
uniform vec4 lightColor;

uniform float  lightRange;
uniform float lightInvSqrRange;
uniform vec3 lightDirection;
uniform vec2 lightSpotParams;
uniform vec4 lightMapParams;

uniform vec4 vsFarPlane;
uniform mat4 worldToLightProj;
uniform vec4 lightParams;
uniform float shadowSoftness;
uniform vec3 eyePosWorld;

uniform mat4 cameraToWorld;
uniform mat4 worldToCamera;

out vec4 OUT_col;
void main()
{   
   // Compute scene UV
   vec2 uvScene = getUVFromSSPos(ssPos.xyz/ssPos.w, rtParams0);

   //unpack normal and linear depth 
   vec4 normDepth = deferredUncondition(deferredBuffer, uvScene);
      
   //eye ray WS/VS
   vec3 vsEyeRay = getDistanceVectorToPlane( -vsFarPlane.w, vsEyeDir.xyz, vsFarPlane );
   vec3 wsEyeRay = tMul(cameraToWorld, vec4(vsEyeRay, 0)).xyz;

   //create surface
   Surface surface = createSurface( normDepth, colorBuffer,matInfoBuffer,
                                    uvScene, eyePosWorld, wsEyeRay, cameraToWorld);
   if (getFlag(surface.matFlag, 2))
   { 
      OUT_col = surface.baseColor;
      return;
   } 
   vec3 L = lightPosition - surface.P;
   float dist = length(L);
   vec3 lighting = vec3(0.0);
	if(dist < lightRange)
   {
      SurfaceToLight surfaceToLight = createSurfaceToLight(surface, L);
      vec3 lightCol = lightColor.rgb;
      
      float shadow = 1.0;
      #ifndef NO_SHADOW
      if (getFlag(surface.matFlag, 0)) //also skip if we don't recieve shadows
      {
         // Get the shadow texture coordinate
         vec4 pxlPosLightProj = tMul( worldToLightProj, vec4( surface.P, 1 ) );
         vec2 shadowCoord = ( ( pxlPosLightProj.xy / pxlPosLightProj.w ) * 0.5 ) + vec2( 0.5, 0.5 );
         shadowCoord.y = 1.0f - shadowCoord.y;

         //distance to light in shadow map space
         float distToLight = pxlPosLightProj.z / lightRange;
         shadow = softShadow_filter(shadowMap, ssPos.xy/ssPos.w, shadowCoord, shadowSoftness, distToLight, surfaceToLight.NdotL, lightParams.y);
         #ifdef USE_COOKIE_TEX
            // Lookup the cookie sample.
            vec4 cookie = texture(cookieMap, shadowCoord);
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
      vec3 factor = lightColor * max(surfaceToLight.NdotL, 0) * shadow * lightIntensity * attenuation;

      vec3 diffuse = BRDF_GetDebugDiffuse(surface,surfaceToLight) * factor;
      vec3 final = max(0.0f, diffuse) * getSpotAngleAtt(-surfaceToLight.L, lightDirection, lightSpotParams );
      
      OUT_col = vec4(final, 0);
      return;
   #endif

   #ifdef SPECULAR_LIGHT_VIZ
   float attenuation = getDistanceAtt(surfaceToLight.Lu, radius);
      float3 factor = lightColor * max(surfaceToLight.NdotL, 0) * shadow * lightIntensity * attenuation;

      vec3 diffuse = BRDF_GetDebugSpecular(surface,surfaceToLight) * factor;
      vec3 final = max(0.0f, diffuse) * getSpotAngleAtt(-surfaceToLight.L, lightDirection, lightSpotParams );
      
      OUT_col = vec4(final, 0);
      return;
   #endif

   #ifdef DETAIL_LIGHTING_VIZ
      float attenuation = getDistanceAtt(surfaceToLight.Lu, radius);
      vec3 factor = lightColor * max(surfaceToLight.NdotL, 0) * shadow * lightIntensity * attenuation;

      vec3 diffuse = BRDF_GetDiffuse(surface,surfaceToLight) * factor;
      vec3 spec = BRDF_GetSpecular(surface,surfaceToLight) * factor;

      vec3 final = max(vec3(0.0f), diffuse + spec * surface.F) * getSpotAngleAtt(-surfaceToLight.L, lightDirection, lightSpotParams );
      
      OUT_col = vec4(final, 0);
      return;
   #endif

      //get Punctual light contribution   
      lighting = getPunctualLight(surface, surfaceToLight, lightCol, lightBrightness, lightInvSqrRange, shadow);
      //get spot angle attenuation
      lighting *= getSpotAngleAtt(-surfaceToLight.L, lightDirection, lightSpotParams );
   }

   OUT_col = vec4(lighting, 0);
}
