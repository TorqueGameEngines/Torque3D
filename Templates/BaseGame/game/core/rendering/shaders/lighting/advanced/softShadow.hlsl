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

#define NUM_TAPS 16

/// The texture used to do per-pixel pseudorandom
/// rotations of the filter taps.
TORQUE_UNIFORM_SAMPLER2D(gTapRotationTex, 2);

float2 VogelDisk(int sampleIndex, int sampleCount, float gradient)
{
	float gA = 2.4f;
	float r = sqrt(sampleIndex + 0.5f) / sqrt(sampleCount);
	float theta = sampleIndex * gA + gradient;
	
	float sine, cosine;
	sincos(theta, sine, cosine);
	
	return float2(r * cosine, r * sine);
}

float GradientNoise(float2 screenPos)
{
	float3 mag = float3(0.06711056f, 0.00583715f, 52.9829189f);
	return frac(mag.z * frac(dot(screenPos, mag.xy)));
}

float AvgOccluderDepthPenumbra(float zShadow, float avgDepth)
{
	float penumbra = (zShadow - avgDepth) / avgDepth;
	penumbra *= penumbra;
	return saturate(80.0f * penumbra);
}

float AvgOccluderDepthPenumbra(float lightSize, float zShadow, float avgDepth)
{
	float penumbra = lightSize * (zShadow - avgDepth) / avgDepth;
	return penumbra;
}

float Penumbra(TORQUE_SAMPLER2D(shadowMap2), float gradient, float2 shadowUV, float zShadow, float filterRadius, float esmFactor, int sampleCount)
{
	float avgOccluderDepth = 0.0f;
	float occluderCount = 0.0f;
	float penumbraFilterMaxSize = 8.0 / 1024.0;
	for(int i = 0; i < sampleCount; i++)
	{
		float2 sampleUV = VogelDisk(i, sampleCount, gradient) * penumbraFilterMaxSize;
		sampleUV = shadowUV + sampleUV;
		float occDepth = TORQUE_TEX2DLOD( shadowMap2, float4(sampleUV,0,0) ).r;
		if(occDepth < zShadow)
		{
			avgOccluderDepth += occDepth;
			occluderCount += 1.0f;
		}
	}
	
	if(occluderCount > 0.0f)
	{
		avgOccluderDepth /= occluderCount;
		return AvgOccluderDepthPenumbra(1000.0f, zShadow, avgOccluderDepth);
	}
	else
	{
		return 0.0f;
	}
}

float softShadow_sampleTaps(  TORQUE_SAMPLER2DCMP(shadowMap1),
							  float2 screenPos,
						      float2 vpos,
                              float2 shadowPos,
                              float filterRadius,
                              float distToLight,
                              float esmFactor,
							  float gradient,
							  float penumbra,
                              int startTap,
                              int endTap )
{
   float shadow = 0;

   float2 tap = 0;
   
   for ( int t = 0; t < NUM_TAPS; t++ )
   {
	  tap = VogelDisk(t, NUM_TAPS, gradient);
	  tap = shadowPos + tap * penumbra * filterRadius;
      float occluder = TORQUE_TEX2DCMP( shadowMap1, tap, distToLight).r;
	  float esm = saturate( exp( esmFactor * ( occluder - distToLight ) ) );
      shadow += esm;
   }

   return shadow;
}


float softShadow_filter(   
TORQUE_SAMPLER2D(shadowMap),
TORQUE_SAMPLER2DCMP(shadowMapCMP),
						   float2 screenPos,
                           float2 vpos,
                           float2 shadowPos,
                           float filterRadius,
                           float distToLight,
                           float dotNL,
                           float esmFactor )
{
   #ifndef SOFTSHADOW

      // If softshadow is undefined then we skip any complex 
      // filtering... just do a single sample ESM.

      float occluder = TORQUE_TEX2DLOD( shadowMap, float4(shadowPos,0,0) ).r;
      float shadow = occluder;

   #else
   
	float gradient = 6.28318530718 * GradientNoise(screenPos);
    float penumbra = Penumbra(TORQUE_SAMPLER2D_MAKEARG(shadowMap), gradient, shadowPos, distToLight, filterRadius, esmFactor, NUM_TAPS);
	if(penumbra < 1.0)
		penumbra = 1.0;
		
	float shadow = softShadow_sampleTaps( TORQUE_SAMPLER2D_MAKEARG(shadowMapCMP),
									 screenPos,
									 vpos,
									 shadowPos,
									 filterRadius,
									 distToLight,
									 esmFactor,
									 gradient,
									 penumbra,
									 0,
									 NUM_TAPS );
									 
	// This averages the taps above with the results
	// of the prediction samples.
	// if you change the number of taps, this value should be set to that.
	shadow = 1.0 - shadow / float(NUM_TAPS);                              

   #endif // SOFTSHADOW

   return shadow;
}