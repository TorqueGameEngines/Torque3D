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
#include "../../../gl/lighting.glsl"
#include "../../shadowMap/shadowMapIO_GLSL.h"
#include "softShadow.glsl"
#include "../../../gl/torque.glsl"
#line 31

in vec4 wsEyeDir;
in vec4 ssPos;
in vec4 vsEyeDir;
in vec4 color;

#ifdef USE_COOKIE_TEX

/// The texture for cookie rendering.
uniform samplerCube cookieMap;

#endif


#ifdef SHADOW_CUBE

   vec3 decodeShadowCoord( vec3 shadowCoord )
   {
      return shadowCoord;
   }

   vec4 shadowSample( samplerCube shadowMap, vec3 shadowCoord )
   {
      return texture( shadowMap, shadowCoord );
   }
  
#else

   vec3 decodeShadowCoord( vec3 paraVec )
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

      vec3 shadowCoord;
      shadowCoord.x = (paraVec.x / (2*(1 + paraVec.z))) + 0.5;
      shadowCoord.y = 1-((paraVec.y / (2*(1 + paraVec.z))) + 0.5);
      shadowCoord.z = 0;
      
      // adjust the co-ordinate slightly if it is near the extent of the paraboloid
      // this value was found via experementation
      // NOTE: this is wrong, it only biases in one direction, not towards the uv 
      // center ( 0.5 0.5 ).
      float offsetVal = 0.95;
      shadowCoord.xy *= offsetVal;
      shadowCoord.xy += vec2(1.0-offsetVal) / 2.0;

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

uniform sampler2D deferredBuffer;

#ifdef SHADOW_CUBE
	uniform samplerCube shadowMap;
#else
	uniform sampler2D shadowMap;
	uniform sampler2D dynamicShadowMap;
#endif

uniform sampler2D lightBuffer;
uniform sampler2D colorBuffer;
uniform sampler2D matInfoBuffer;

uniform vec4 rtParams0;

uniform vec3 lightPosition;
uniform vec4 lightColor;
uniform float  lightBrightness;
uniform float  lightRange;
uniform vec4 lightMapParams;
uniform vec4 vsFarPlane;
uniform vec4 lightParams;

uniform float lightInvSqrRange;
uniform float shadowSoftness;
uniform mat3 worldToLightProj;
uniform mat3 dynamicWorldToLightProj;

uniform vec3 eyePosWorld;
uniform mat4 cameraToWorld;

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
   Surface surface = createSurface( normDepth, colorBuffer, matInfoBuffer,
                                    uvScene, eyePosWorld, wsEyeRay, cameraToWorld);
   
   //early out if emissive
   if (getFlag(surface.matFlag, 0))
   {
      OUT_col = vec4(0.0);
	  return;
   }

   vec3 L = lightPosition - surface.P;
   float dist = length(L);
   vec3 lighting = vec3(0.0);
   if(dist < lightRange)
   {
      float distToLight = dist / lightRange;
      SurfaceToLight surfaceToLight = createSurfaceToLight(surface, L);

   #ifdef NO_SHADOW
      float shadowed = 1.0;
   #else

      #ifdef SHADOW_CUBE
              
         // TODO: We need to fix shadow cube to handle soft shadows!
         float occ = texture( shadowMap, ttMul( worldToLightProj, -surfaceToLight.L ) ).r;
         float shadowed = saturate( exp( lightParams.y * ( occ - distToLight ) ) );
         
      #else
      vec2 shadowCoord = decodeShadowCoord( tMul( worldToLightProj, -surfaceToLight.L ) ).xy;
      vec2 dynShadowCoord = decodeShadowCoord( tMul( dynamicWorldToLightProj, -surfaceToLight.L ) ).xy;
      float static_shadowed = softShadow_filter(shadowMap, ssPos.xy/ssPos.w, shadowCoord, shadowSoftness, distToLight, surfaceToLight.NdotL, lightParams.y);
      float dynamic_shadowed = softShadow_filter(dynamicShadowMap, ssPos.xy/ssPos.w, dynShadowCoord, shadowSoftness, distToLight, surfaceToLight.NdotL, lightParams.y);
         float shadowed = min(static_shadowed, dynamic_shadowed);
      #endif

   #endif // !NO_SHADOW
   
      vec3 lightCol = lightColor.rgb;
   #ifdef USE_COOKIE_TEX

      // Lookup the cookie sample.
      vec4 cookie = texture(cookieMap, ttMul(worldToLightProj, -surfaceToLight.L));
      // Multiply the light with the cookie tex.
      lightCol *= cookie.rgb;
      // Use a maximum channel luminance to attenuate 
      // the lighting else we get specular in the dark
      // regions of the cookie texture.
      lightCol *= max(cookie.r, max(cookie.g, cookie.b));
   #endif

      //get punctual light contribution   
      lighting = getPunctualLight(surface, surfaceToLight, lightCol, lightBrightness, lightInvSqrRange, shadowed);
   }

   OUT_col = vec4(lighting, 0);
}
