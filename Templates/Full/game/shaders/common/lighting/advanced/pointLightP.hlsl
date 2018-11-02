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
#include "lightingUtils.hlsl"
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


#ifdef USE_COOKIE_TEX

/// The texture for cookie rendering.
TORQUE_UNIFORM_SAMPLERCUBE(cookieMap, 3);

#endif


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
      //shadowCoord.xy *= 0.997;

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
TORQUE_UNIFORM_SAMPLER2D(dynamicShadowMap, 2);
#endif

TORQUE_UNIFORM_SAMPLER2D(lightBuffer, 5);
TORQUE_UNIFORM_SAMPLER2D(colorBuffer, 6);
TORQUE_UNIFORM_SAMPLER2D(matInfoBuffer, 7);

uniform float4 rtParams0;
uniform float4 lightColor;

uniform float  lightBrightness;
uniform float3 lightPosition;

uniform float4 lightMapParams;
uniform float4 vsFarPlane;
uniform float4 lightParams;

uniform float  lightRange;
uniform float shadowSoftness;
uniform float2 lightAttenuation;

uniform float3x3 viewToLightProj;
uniform float3x3 dynamicViewToLightProj;

uniform float3 eyePosWorld;
uniform float4x4 cameraToWorld;

LightTargetOutput main(   ConvexConnectP IN )
{   
   LightTargetOutput Output = (LightTargetOutput)0;

   // Compute scene UV
   float3 ssPos = IN.ssPos.xyz / IN.ssPos.w;
   float2 uvScene = getUVFromSSPos(ssPos, rtParams0);

   //sky and editor background check
   float4 normDepth = UnpackDepthNormal(TORQUE_SAMPLER2D_MAKEARG(deferredBuffer), uvScene);
   if (normDepth.w>0.9999)
      return Output;
      
   // Eye ray - Eye -> Pixel
   float3 eyeRay = getDistanceVectorToPlane( -vsFarPlane.w, IN.vsEyeDir.xyz, vsFarPlane );
   float3 viewSpacePos = eyeRay * normDepth.w;
   
   //create surface
   Surface surface = CreateSurface( normDepth, TORQUE_SAMPLER2D_MAKEARG(colorBuffer),TORQUE_SAMPLER2D_MAKEARG(matInfoBuffer),
                                    uvScene, eyePosWorld, eyeRay, cameraToWorld);   
   //early out if emissive
   if (getFlag(surface.matFlag, 0))
      return Output;      
   
   // Build light vec, get length, clip pixel if needed
   float3 lightVec = lightPosition - viewSpacePos;
   float lenLightV = length(lightVec);
   clip(lightRange - lenLightV);   

   // Get the attenuated falloff.
   float atten = attenuate(lightColor, lightAttenuation, lenLightV);
   clip(atten - 1e-6);

   // Normalize lightVec
   lightVec /= lenLightV;
   
   
   // If we can do dynamic branching then avoid wasting
   // fillrate on pixels that are backfacing to the light.
   float nDotL = dot( lightVec, normDepth.xyz );
   //DB_CLIP( nDotL < 0 );
   //create surface to light
   SurfaceToLight surfaceToLight = CreateSurfaceToLight(surface, dot( lightVec, normDepth.xyz ));

#ifdef NO_SHADOW

   float shadowed = 1.0;

#else

   // Get a linear depth from the light source.
   float distToLight = lenLightV / lightRange;

#ifdef SHADOW_CUBE

   // TODO: We need to fix shadow cube to handle soft shadows!
   float occ = TORQUE_TEXCUBE(shadowMap, mul(viewToLightProj, -lightVec)).r;
   float shadowed = saturate(exp(lightParams.y * (occ - distToLight)));

#else

   // Static
   float2 shadowCoord = decodeShadowCoord(mul(viewToLightProj, -lightVec)).xy;
   float static_shadowed = softShadow_filter(TORQUE_SAMPLER2D_MAKEARG(shadowMap),
      ssPos.xy,
      shadowCoord,
      shadowSoftness,
      distToLight,
      nDotL,
      lightParams.y);

   // Dynamic
   float2 dynamicShadowCoord = decodeShadowCoord(mul(dynamicViewToLightProj, -lightVec)).xy;
   float dynamic_shadowed = softShadow_filter(TORQUE_SAMPLER2D_MAKEARG(dynamicShadowMap),
      ssPos.xy,
      dynamicShadowCoord,
      shadowSoftness,
      distToLight,
      nDotL,
      lightParams.y);

   float shadowed = min(static_shadowed, dynamic_shadowed);

#endif

#endif // !NO_SHADOW

   float3 lightcol = lightColor.rgb;
#ifdef USE_COOKIE_TEX

   // Lookup the cookie sample.
   float4 cookie = TORQUE_TEXCUBE(cookieMap, mul(viewToLightProj, -lightVec));

   // Multiply the light with the cookie tex.
   lightcol *= cookie.rgb;

   // Use a maximum channel luminance to attenuate 
   // the lighting else we get specular in the dark
   // regions of the cookie texture.
   atten *= max(cookie.r, max(cookie.g, cookie.b));

#endif

   //get directional light contribution   
   LightResult result = GetDirectionalLight(surface, surfaceToLight, lightColor.rgb, lightBrightness, shadowed);
      
   //output
   Output.diffuse = float4(result.diffuse*atten, 0);
   Output.spec = float4(result.spec*atten, 0);
   
   return Output;
}
