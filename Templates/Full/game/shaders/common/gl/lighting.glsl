//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
// Portions Copyright Zefiros
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

#include "./torque.glsl"

#ifndef TORQUE_SHADERGEN

// These are the uniforms used by most lighting shaders.

uniform vec4 inLightPos[3];
uniform vec4 inLightInvRadiusSq;
uniform vec4 inLightColor[4];

#ifndef TORQUE_BL_NOSPOTLIGHT
   uniform vec4 inLightSpotDir[3];
   uniform vec4 inLightSpotAngle;
   uniform vec4 inLightSpotFalloff;
#endif

uniform vec4 ambient;
#define ambientCameraFactor 0.3
uniform float smoothness;
uniform float metalness;
uniform vec4 albedo;

#endif // !TORQUE_SHADERGEN


vec3 F_schlick( in vec3 f0, in vec3 f90, in float u )
{
	//
    //  F( v, h ) =  F0 + ( 1.0 - F0 ) *  pow( 1.0f - HdotV,  5.0f )
    //
    //
    //  where 
    //
    //  F0 = BaseColor * nDotL
    //
    //  Dielectric materials always have a range of 0.02 < F0 < 0.05 , use a stock value of 0.04 ( roughly plastics )
    //

	return f0 + ( f90 - f0 ) * pow( 1.0f - u ,  5.0f );
}

float Fr_DisneyDiffuse ( float NdotV , float NdotL , float LdotH , float linearRoughness )
{
	float energyBias = mix (0 , 0.5 , linearRoughness );
	float energyFactor = mix (1.0 , 1.0 / 1.51 , linearRoughness );
	float fd90 = energyBias + 2.0 * LdotH * LdotH * linearRoughness ;
	vec3 f0 = vec3 ( 1.0f , 1.0f , 1.0f );
	float lightScatter = F_schlick( f0 , vec3(fd90), NdotL ).r;
	float viewScatter = F_schlick(f0 , vec3(fd90), NdotV ).r;

	return lightScatter * viewScatter * energyFactor ;
}

float SmithGGX( float NdotL, float NdotV, float alpha )
{
    //
    // G( L, V, h ) = G( L ) G( V )
    //
    //                    nDotL
    // G( L ) = _________________________
    //             nDotL ( 1 - k ) + k
    //
    //         
    //                     NdotV
    // G( V ) = _________________________
    //             NdotV ( 1 - k ) + k
    //
    //
    //               pow( ( Roughness + 1 ), 2)
    //  , Where  k = __________________________     ( unreal 4 )
    //                          8
    //
	
	float alphaSqr = alpha * alpha;

	//float GGX_V = NdotL * sqrt ( ( - NdotV * alphaSqr + NdotV ) * NdotV + alphaSqr );
	//float GGX_L = NdotV * sqrt ( ( - NdotL * alphaSqr + NdotL ) * NdotL + alphaSqr );
	
	float GGX_V = NdotL + sqrt ( ( - NdotV * alphaSqr + NdotV ) * NdotV + alphaSqr );
	float GGX_L = NdotV + sqrt ( ( - NdotL * alphaSqr + NdotL ) * NdotL + alphaSqr );
	
	return 1.0/( GGX_V + GGX_L ); 
	//return 0.5f / ( GGX_V + GGX_L ); 
}

float D_GGX( float NdotH , float alpha )
{
    //
    // or GGX ( disney / unreal 4 )
    //
    //  alpha = pow( roughness, 2 );
    //
    //                                    pow( alpha, 2 )
    //  D( h ) = ________________________________________________________________      
    //           PI pow( pow( NdotH , 2 ) ( pow( alpha, 2 ) - 1 ) + 1 ), 2 )
    //

	float alphaSqr = alpha*alpha;
	float f = ( NdotH * alphaSqr - NdotH ) * NdotH + 1;
	return alphaSqr / ( M_PI_F * (f * f) );
}

vec4 EvalBDRF( vec3 baseColor, vec3 lightColor, vec3 toLight, vec3 position, vec3 normal,  float roughness, float metallic )
{
	//
    //  Microfacet Specular Cook-Torrance
    //
    //                D( h ) F( v, h ) G( l, v, h )
    //    f( l, v ) = ____________________________
    //                 4 ( dot( n, l ) dot( n, v )
    //                 
    //

	vec3 L = normalize( toLight );
	vec3 V = normalize( -position );
	vec3 H = normalize( L + V );
	vec3 N = normal;
	
	float NdotV = abs( dot( N, V ) ) + 1e-5f;
	float NdotH = saturate( dot( N, H ) );
	float NdotL = saturate( dot( N, L ) );
	float LdotH = saturate( dot( L, H ) );
	
	float VdotH = saturate( dot( V, H ) );

	if ( NdotL == 0 ) 
		return vec4( 0.0f, 0.0f, 0.0f, 0.0f ); 
	
	float alpha = roughness;
	float visLinAlpha = alpha * alpha;
	
	vec3 f0 = baseColor;
	float  metal = metallic;
	
	vec3 F_conductor= F_schlick( f0, vec3( 1.0, 1.0, 1.0 ), VdotH );
	vec3 F_dielec   = F_schlick( vec3( 0.04, 0.04, 0.04 ), vec3( 1.0, 1.0, 1.0 ), VdotH );
	float  Vis        = SmithGGX( NdotL, NdotV, visLinAlpha );
	float  D          = D_GGX( NdotH, visLinAlpha );
	
	vec3 Fr_dielec    = D * F_dielec * Vis; 
	vec3 Fr_conductor = D * F_conductor * Vis; 
	
	vec3 Fd = vec3(Fr_DisneyDiffuse( NdotV , NdotL , LdotH , visLinAlpha ) / M_PI_F);
    vec3 specular = ( 1.0f - metal ) * Fr_dielec + metal * Fr_conductor;
	vec3 diffuse  = ( 1.0f - metal ) * Fd * f0;
   
    vec3 ret = ( diffuse + specular + lightColor) * vec3(NdotL);
	
	float FR = saturate(length(specular));
	return vec4(ret,FR);
}

void compute4Lights( vec3 wsView, 
                     vec3 wsPosition, 
                     vec3 wsNormal,
                     vec4 shadowMask,

                     #ifdef TORQUE_SHADERGEN
                     
                        vec4 inLightPos[3],
                        vec4 inLightInvRadiusSq,
                        vec4 inLightColor[4],
                        vec4 inLightSpotDir[3],
                        vec4 inLightSpotAngle,
                        vec4 inLightSpotFalloff,
                        float smoothness,
                        float metalness,
                        vec4 albedo,

                     #endif // TORQUE_SHADERGEN
                     
                     out vec4 outDiffuse,
                     out vec4 outSpecular )
{
   // NOTE: The light positions and spotlight directions
   // are stored in SoA order, so inLightPos[0] is the
   // x coord for all 4 lights... inLightPos[1] is y... etc.
   //
   // This is the key to fully utilizing the vector units and
   // saving a huge amount of instructions.
   //
   // For example this change saved more than 10 instructions 
   // over a simple for loop for each light.
   
   int i;

   vec4 lightVectors[3];
   for ( i = 0; i < 3; i++ )
      lightVectors[i] = wsPosition[i] - inLightPos[i];


   // Accumulate the dot product between the light 
   // vector and the normal.
   //
   // The normal is negated because it faces away from
   // the surface and the light faces towards the
   // surface... this keeps us from needing to flip
   // the light vector direction which complicates
   // the spot light calculations.
   //
   // We normalize the result a little later.
   //
   vec4 nDotL = vec4(0);
   for ( i = 0; i < 3; i++ )
      nDotL += lightVectors[i] * -wsNormal[i];
 
   vec4 squareDists = vec4(0);
   for ( i = 0; i < 3; i++ )
      squareDists += lightVectors[i] * lightVectors[i];
   half4 correction = half4(inversesqrt( squareDists ));
   nDotL = saturate( nDotL * correction );

   // First calculate a simple point light linear 
   // attenuation factor.
   //
   // If this is a directional light the inverse
   // radius should be greater than the distance
   // causing the attenuation to have no affect.
   //
   vec4 atten = saturate( 1.0 - ( squareDists * inLightInvRadiusSq ) );

   #ifndef TORQUE_BL_NOSPOTLIGHT

      // The spotlight attenuation factor.  This is really
      // fast for what it does... 6 instructions for 4 spots.

      vec4 spotAtten = vec4(0);
      for ( i = 0; i < 3; i++ )
         spotAtten += lightVectors[i] * inLightSpotDir[i];

      vec4 cosAngle = ( spotAtten * correction ) - inLightSpotAngle;
      atten *= saturate( cosAngle * inLightSpotFalloff );

   #endif

   // Get the final light intensity.
   vec4 intensity = nDotL * atten;
   
   // Combine the light colors for output.
   vec4 lightColor = vec4(0);
   for ( i = 0; i < 4; i++ )
      lightColor += intensity[i] * inLightColor[i];
      
   vec3 toLight = vec3(0);
   for ( i = 0; i < 3; i++ )
      toLight += lightVectors[i].rgb;
      
   outDiffuse = vec4(albedo.rgb*(1.0-metalness),albedo.a);
   outSpecular = EvalBDRF( vec3( 1.0, 1.0, 1.0 ), lightColor.rgb, toLight, wsPosition, wsNormal, smoothness, metalness );
}