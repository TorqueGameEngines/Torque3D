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

TORQUE_UNIFORM_SAMPLER2D(deferredBuffer, 0);
TORQUE_UNIFORM_SAMPLER2D(shadowMap, 1);
TORQUE_UNIFORM_SAMPLER2D(dynamicShadowMap,2);

#ifdef USE_COOKIE_TEX

/// The texture for cookie rendering.
TORQUE_UNIFORM_SAMPLER2D(cookieMap, 3);

#endif

TORQUE_UNIFORM_SAMPLER2D(lightBuffer, 5);
TORQUE_UNIFORM_SAMPLER2D(colorBuffer, 6);
TORQUE_UNIFORM_SAMPLER2D(matInfoBuffer, 7);

uniform float4 rtParams0;

uniform float  lightBrightness;
uniform float3 lightPosition;

uniform float4 lightColor;

uniform float  lightRange;
uniform float3 lightDirection;

uniform float4 lightSpotParams;
uniform float4 lightMapParams;
uniform float4 vsFarPlane;
uniform float4x4 viewToLightProj;
uniform float4 lightParams;
uniform float4x4 dynamicViewToLightProj;

uniform float2 lightAttenuation;
uniform float shadowSoftness;

struct PS_OUTPUT
{
   float4 diffuse: TORQUE_TARGET0;
   float4 spec: TORQUE_TARGET1;
};

PS_OUTPUT main(   ConvexConnectP IN ) : TORQUE_TARGET0
{   
   PS_OUTPUT Output = (PS_OUTPUT)0;
   // Compute scene UV
   float3 ssPos = IN.ssPos.xyz / IN.ssPos.w;
   float2 uvScene = getUVFromSSPos( ssPos, rtParams0 );
   
   // Matinfo flags
   float4 matInfo = TORQUE_TEX2D( matInfoBuffer, uvScene );
   //early out if emissive
   bool emissive = getFlag(matInfo.r, 0);
   if (emissive)
   {
      return Output;
   }

   float4 colorSample = TORQUE_TEX2D( colorBuffer, uvScene );
   float3 subsurface = float3(0.0,0.0,0.0); 
   if (getFlag( matInfo.r, 1 ))
   {
      subsurface = colorSample.rgb;
      if (colorSample.r>colorSample.g)
         subsurface = float3(0.772549, 0.337255, 0.262745);
	  else
         subsurface = float3(0.337255, 0.772549, 0.262745);
	}
	
   // Sample/unpack the normal/z data
   float4 deferredSample = TORQUE_DEFERRED_UNCONDITION( deferredBuffer, uvScene );
   float3 normal = deferredSample.rgb;
   float depth = deferredSample.a;
   
   // Eye ray - Eye -> Pixel
   float3 eyeRay = getDistanceVectorToPlane( -vsFarPlane.w, IN.vsEyeDir.xyz, vsFarPlane );
   float3 viewSpacePos = eyeRay * depth;
      
   // Build light vec, get length, clip pixel if needed
   float3 lightToPxlVec = viewSpacePos - lightPosition;
   float lenLightV = length( lightToPxlVec );
   lightToPxlVec /= lenLightV;

   //lightDirection = float3( -lightDirection.xy, lightDirection.z ); //float3( 0, 0, -1 );
   float cosAlpha = dot( lightDirection, lightToPxlVec );   
   clip( cosAlpha - lightSpotParams.x );
   clip( lightRange - lenLightV );

   float atten = attenuate( lightColor, lightAttenuation, lenLightV );
   atten *= ( cosAlpha - lightSpotParams.x ) / lightSpotParams.y;
   clip( atten - 1e-6 );
   atten = saturate( atten );
   
   float nDotL = dot( normal, -lightToPxlVec );

   // Get the shadow texture coordinate
   float4 pxlPosLightProj = mul( viewToLightProj, float4( viewSpacePos, 1 ) );
   float2 shadowCoord = ( ( pxlPosLightProj.xy / pxlPosLightProj.w ) * 0.5 ) + float2( 0.5, 0.5 );
   shadowCoord.y = 1.0f - shadowCoord.y;

   // Get the dynamic shadow texture coordinate
   float4 dynpxlPosLightProj = mul( dynamicViewToLightProj, float4( viewSpacePos, 1 ) );
   float2 dynshadowCoord = ( ( dynpxlPosLightProj.xy / dynpxlPosLightProj.w ) * 0.5 ) + float2( 0.5, 0.5 );
   dynshadowCoord.y = 1.0f - dynshadowCoord.y;
   
   #ifdef NO_SHADOW
   
      float shadowed = 1.0;
      	
   #else

      // Get a linear depth from the light source.
      float distToLight = pxlPosLightProj.z / lightRange;

      float static_shadowed = softShadow_filter( TORQUE_SAMPLER2D_MAKEARG(shadowMap),
                                          ssPos.xy,
                                          shadowCoord,
                                          shadowSoftness,
                                          distToLight,
                                          nDotL,
                                          lightParams.y );
                                          
      float dynamic_shadowed = softShadow_filter( TORQUE_SAMPLER2D_MAKEARG(dynamicShadowMap),
                                          ssPos.xy,
                                          dynshadowCoord,
                                          shadowSoftness,
                                          distToLight,
                                          nDotL,
                                          lightParams.y );
      float shadowed = min(static_shadowed, dynamic_shadowed);
   #endif // !NO_SHADOW
   
   float3 lightcol = lightColor.rgb;
   #ifdef USE_COOKIE_TEX

      // Lookup the cookie sample.
      float4 cookie = TORQUE_TEX2D( cookieMap, shadowCoord );

      // Multiply the light with the cookie tex.
      lightcol *= cookie.rgb;

      // Use a maximum channel luminance to attenuate 
      // the lighting else we get specular in the dark
      // regions of the cookie texture.
      atten *= max( cookie.r, max( cookie.g, cookie.b ) );

   #endif

   // NOTE: Do not clip on fully shadowed pixels as it would
   // cause the hardware occlusion query to disable the shadow.

   float3 l = normalize(-lightDirection);
   float3 v = eyeRay;// normalize(eyePosWorld - worldPos.xyz);

   float3 h = normalize(v + l);
   float dotNLa = clamp(dot(normal, l), 0.0, 1.0);
   float dotNVa = clamp(dot(normal, v), 0.0, 1.0);
   float dotNHa = clamp(dot(normal, h), 0.0, 1.0);
   float dotHVa = clamp(dot(normal, v), 0.0, 1.0);
   float dotLHa = clamp(dot(l, h), 0.0, 1.0);

   float roughness = matInfo.g;
   float metalness = matInfo.b;

   //diffuse
   float disDiff = Fr_DisneyDiffuse(dotNVa, dotNLa, dotLHa, roughness);
   float3 diffuse = float3(disDiff, disDiff, disDiff) / M_PI_F;
   //specular
   float3 specular = directSpecular(normal, v, l, roughness, 1.0) * lightColor.rgb;

   
   if (nDotL<0) shadowed = 0;
   float Sat_NL_Att = saturate( nDotL * shadowed ) * lightBrightness;
   //output
   Output.diffuse = float4(diffuse * lightBrightness, Sat_NL_Att*shadowed);
   Output.spec = float4(specular * lightBrightness, Sat_NL_Att*shadowed);

   return Output;
}
