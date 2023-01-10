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

#ifndef _TORQUE_HLSL_
#define _TORQUE_HLSL_

#include "./shaderModel.hlsl"

static float M_HALFPI_F   = 1.57079632679489661923f;
static float M_PI_F       = 3.14159265358979323846f;
static float M_2PI_F      = 6.28318530717958647692f;
static float M_1OVER_PI_F  = 0.31830988618f;

/// Calculate fog based on a start and end positions in worldSpace.
float computeSceneFog(  float3 startPos,
                        float3 endPos,
                        float fogDensity,
                        float fogDensityOffset,
                        float fogHeightFalloff )
{      
   float f = length( startPos - endPos ) - fogDensityOffset;
   float h = 1.0 - ( endPos.z * fogHeightFalloff );  
   return exp( -fogDensity * f * h );  
}


/// Calculate fog based on a start and end position and a height.
/// Positions do not need to be in worldSpace but height does.
float computeSceneFog( float3 startPos,
                       float3 endPos,
                       float height,
                       float fogDensity,
                       float fogDensityOffset,
                       float fogHeightFalloff )
{
   float f = length( startPos - endPos ) - fogDensityOffset;
   float h = 1.0 - ( height * fogHeightFalloff );
   return exp( -fogDensity * f * h );
}


/// Calculate fog based on a distance, height is not used.
float computeSceneFog( float dist, float fogDensity, float fogDensityOffset )
{
   float f = dist - fogDensityOffset;
   return exp( -fogDensity * f );
}


/// Convert a float4 uv in viewport space to render target space.
float2 viewportCoordToRenderTarget( float4 inCoord, float4 rtParams )
{   
   float2 outCoord = inCoord.xy / inCoord.w;
   outCoord = ( outCoord * rtParams.zw ) + rtParams.xy;  
   return outCoord;
}


/// Convert a float2 uv in viewport space to render target space.
float2 viewportCoordToRenderTarget( float2 inCoord, float4 rtParams )
{   
   float2 outCoord = ( inCoord * rtParams.zw ) + rtParams.xy;
   return outCoord;
}


/// Convert a float4 quaternion into a 3x3 matrix.
float3x3 quatToMat( float4 quat )
{
   float xs = quat.x * 2.0f;
   float ys = quat.y * 2.0f;
   float zs = quat.z * 2.0f;

   float wx = quat.w * xs;
   float wy = quat.w * ys;
   float wz = quat.w * zs;
   
   float xx = quat.x * xs;
   float xy = quat.x * ys;
   float xz = quat.x * zs;
   
   float yy = quat.y * ys;
   float yz = quat.y * zs;
   float zz = quat.z * zs;
   
   float3x3 mat;
   
   mat[0][0] = 1.0f - (yy + zz);
   mat[0][1] = xy - wz;
   mat[0][2] = xz + wy;

   mat[1][0] = xy + wz;
   mat[1][1] = 1.0f - (xx + zz);
   mat[1][2] = yz - wx;

   mat[2][0] = xz - wy;
   mat[2][1] = yz + wx;
   mat[2][2] = 1.0f - (xx + yy);   

   return mat;
}


/// The number of additional substeps we take when refining
/// the results of the offset parallax mapping function below.
///
/// You should turn down the number of steps if your needing
/// more performance out of your parallax surfaces.  Increasing
/// the number doesn't yeild much better results and is rarely
/// worth the additional cost.
///
#define PARALLAX_REFINE_STEPS 3

/// Performs fast parallax offset mapping using 
/// multiple refinement steps.
///
/// @param texMap The texture map whos alpha channel we sample the parallax depth.
/// @param texCoord The incoming texture coordinate for sampling the parallax depth.
/// @param negViewTS The negative view vector in tangent space.
/// @param depthScale The parallax factor used to scale the depth result.
///
float2 parallaxOffset(TORQUE_SAMPLER2D(texMap), float2 texCoord, float3 negViewTS, float depthScale)
{
   float depth = TORQUE_TEX2D(texMap, texCoord).a/(PARALLAX_REFINE_STEPS*2);
   float2 offset = negViewTS.xy * (depth * depthScale)/(PARALLAX_REFINE_STEPS);

   for (int i = 0; i < PARALLAX_REFINE_STEPS; i++)
   {
      depth = (depth + TORQUE_TEX2D(texMap, texCoord + offset).a)/(PARALLAX_REFINE_STEPS*2);
      offset = negViewTS.xy * (depth * depthScale)/(PARALLAX_REFINE_STEPS);
   }

   return offset;
}

/// Same as parallaxOffset but for dxtnm where depth is stored in the red channel instead of the alpha
float2 parallaxOffsetDxtnm(TORQUE_SAMPLER2D(texMap), float2 texCoord, float3 negViewTS, float depthScale)
{
   float depth = TORQUE_TEX2D(texMap, texCoord).r/(PARALLAX_REFINE_STEPS*2);
   float2 offset = negViewTS.xy * (depth * depthScale)/(PARALLAX_REFINE_STEPS*2);

   for (int i = 0; i < PARALLAX_REFINE_STEPS; i++)
   {
      depth = (depth + TORQUE_TEX2D(texMap, texCoord + offset).r)/(PARALLAX_REFINE_STEPS*2);
      offset = negViewTS.xy * (depth * depthScale)/(PARALLAX_REFINE_STEPS*2);
   }

   return offset;
}

/// Copy of the above to functions, but for arrays
float2 parallaxOffsetTexArray(TORQUE_SAMPLER2DARRAY(texMap), float3 texCoord, float3 negViewTS, float depthScale)
{
   float depth = TORQUE_TEX2D(texMap, texCoord).a/(PARALLAX_REFINE_STEPS*2);
   float2 offset = negViewTS.xy * (depth * depthScale)/(PARALLAX_REFINE_STEPS);

   for (int i = 0; i < PARALLAX_REFINE_STEPS; i++)
   {
      depth = (depth + TORQUE_TEX2D(texMap, texCoord + float3(offset, 0.0)).a)/(PARALLAX_REFINE_STEPS*2);
      offset = negViewTS.xy * (depth * depthScale)/(PARALLAX_REFINE_STEPS);
   }

   return offset;
}

float2 parallaxOffsetDxtnmTexArray(TORQUE_SAMPLER2DARRAY(texMap), float3 texCoord, float3 negViewTS, float depthScale)
{
   float depth = TORQUE_TEX2D(texMap, texCoord).r/(PARALLAX_REFINE_STEPS*2);
   float2 offset = negViewTS.xy * (depth * depthScale)/(PARALLAX_REFINE_STEPS*2);

   for (int i = 0; i < PARALLAX_REFINE_STEPS; i++)
   {
      depth = (depth + TORQUE_TEX2D(texMap, texCoord + float3(offset, 0.0)).r)/(PARALLAX_REFINE_STEPS*2);
      offset = negViewTS.xy * (depth * depthScale)/(PARALLAX_REFINE_STEPS*2);
   }

   return offset;
}

/// The maximum value for 10bit per component integer HDR encoding.
static const float HDR_RGB10_MAX = 4.0;

/// Encodes an HDR color for storage into a target.
float3 hdrEncode( float3 sample )
{
   #if defined( TORQUE_HDR_RGB10 )
      return sample / HDR_RGB10_MAX;

   #else

      // No encoding.
      return sample;

   #endif
}

/// Encodes an HDR color for storage into a target.
float4 hdrEncode( float4 sample )
{
   return float4( hdrEncode( sample.rgb ), sample.a );
}

/// Decodes an HDR color from a target.
float3 hdrDecode( float3 sample )
{
   #if defined( TORQUE_HDR_RGB10 )
      return sample * HDR_RGB10_MAX;

   #else

      // No encoding.
      return sample;

   #endif
}

/// Decodes an HDR color from a target.
float4 hdrDecode( float4 sample )
{
   return float4( hdrDecode( sample.rgb ), sample.a );
}

/// Returns the luminance for an HDR pixel.
float hdrLuminance( float3 sample )
{
   // There are quite a few different ways to
   // calculate luminance from an rgb value.
   //
   // If you want to use a different technique
   // then plug it in here.
   //

   ////////////////////////////////////////////////////////////////////////////
   //
   // Max component luminance.
   //
   //float lum = max( sample.r, max( sample.g, sample.b ) );

   ////////////////////////////////////////////////////////////////////////////
   // The perceptual relative luminance.
   //
   // See http://en.wikipedia.org/wiki/Luminance_(relative)
   //
   const float3 RELATIVE_LUMINANCE = float3( 0.2126, 0.7152, 0.0722 );
   float lum = dot( sample, RELATIVE_LUMINANCE );
  
   ////////////////////////////////////////////////////////////////////////////
   //
   // The average component luminance.
   //
   //const float3 AVERAGE_LUMINANCE = float3( 0.3333, 0.3333, 0.3333 );
   //float lum = dot( sample, AVERAGE_LUMINANCE );

   return lum;
}

/// Called from the visibility feature to do screen
/// door transparency for fading of objects.
void fizzle(float2 vpos, float visibility)
{
   // NOTE: The magic values below are what give us 
   // the nice even pattern during the fizzle.
   //
   // These values can be changed to get different 
   // patterns... some better than others.
   //
   // Horizontal Blinds - { vpos.x, 0.916, vpos.y, 0 }
   // Vertical Lines - { vpos.x, 12.9898, vpos.y, 78.233 }
   //
   // I'm sure there are many more patterns here to 
   // discover for different effects.
   
   float2x2 m = { vpos.x, 0.916, vpos.y, 0.350 };
   clip( visibility - frac( determinant( m ) ) );
}

// Deferred Shading: Material Info Flag Check
bool getFlag(float flags, int num)
{
   int process = round(flags * 255);
   int squareNum = pow(2, num);
   return (fmod(process, pow(2, squareNum)) >= squareNum); 
}

// RGB -> HSL
float3 rgbToHSL(float3 col)
{
	float cmax, cmin, h, s, l;
	cmax = max(col.r, max(col.g, col.b));
	cmin = min(col.r, min(col.g, col.b));
	l = min(1.0, (cmax + cmin) / 2.0);

    if (cmax == cmin) {
    h = s = 0.0; /* achromatic */
    }
    else 
	{
        float cdelta = cmax - cmin;
        s = l > 0.5 ? cdelta / (2.0 - cmax - cmin) : cdelta / (cmax + cmin);
        if (cmax == col.r) {
          h = (col.g - col.b) / cdelta + (col.g < col.b ? 6.0 : 0.0);
        }
        else if (cmax == col.g) {
          h = (col.b - col.r) / cdelta + 2.0;
        }
        else {
          h = (col.r - col.b) / cdelta + 4.0;
        }
    }
    h /= 6.0;

	
	return float3(h,s,l);
}

// HSL -> RGB
float3 hslToRGB(float3 hsl)
{
	float nr, ng, nb, chroma, h, s, l;
	h = hsl.r;
	s = hsl.g;
	l = hsl.b;
	
	nr = abs(h * 6.0 - 3.0) - 1.0;
	ng = 2.0 - abs(h * 6.0 - 2.0);
	nb = 2.0 - abs(h * 6.0 - 4.0);
	
	nr = clamp(nr, 0.0, 1.0);
	nb = clamp(nb, 0.0, 1.0);
	ng = clamp(ng, 0.0, 1.0);

	chroma = (1.0 - abs(2.0 * l - 1.0)) * s;
	
	return float3((nr - 0.5) * chroma + l, (ng - 0.5) * chroma + l, (nb - 0.5) * chroma + l);
  
}

// Sample in linear space. Decodes gamma.
float toLinear(float col)
{
	if(col < 0.04045)
	{
		return (col < 0.0) ? 0.0 : col * (1.0 / 12.92);
	}
	
	return pow(abs(col + 0.055) * (1.0 / 1.055), 2.4);
}
float4 toLinear(float4 tex)
{
   return float4(toLinear(tex.r),toLinear(tex.g),toLinear(tex.b), tex.a);
}

float3 toLinear(float3 tex)
{
   return float3(toLinear(tex.r),toLinear(tex.g),toLinear(tex.b));
}

// Encodes gamma.
float toGamma(float col)
{
	if(col < 0.0031308)
	{
		return (col < 0.0) ? 0.0 : col * 12.92;
	}
	
	return 1.055 * pow(abs(col), 1.0 / 2.4) - 0.055;
}

float4 toGamma(float4 tex)
{
   return float4(toGamma(tex.r), toGamma(tex.g), toGamma(tex.b), tex.a);
}

float3 toGamma(float3 tex)
{
   return float3(toGamma(tex.r), toGamma(tex.g), toGamma(tex.b));
}

//
float3 PBRFresnel(float3 albedo, float3 indirect, float metalness, float fresnel)
{
   float3 diffuseColor = albedo - (albedo * metalness);
   float3 reflectColor = lerp(indirect*albedo, indirect, fresnel);

   return diffuseColor + reflectColor;
}

float3 simpleFresnel(float3 diffuseColor, float3 reflectColor, float metalness, float angle, float bias, float power)
{
   float fresnelTerm = bias + (1.0 - bias) * pow(abs(1.0 - max(angle, 0)), power);

   fresnelTerm *= metalness;

   return lerp(diffuseColor, reflectColor, fresnelTerm);
}

//hlsl version of the glsl funcion mod - note hlsl fmod is different
#define mod(x,y) (x-y*floor(x/y))

//get direction for a cube face
float3 getCubeDir(int face, float2 uv)
{
	float2 debiased = uv * 2.0f - 1.0f;

	float3 dir = 0;

	switch (face)
	{
		case 0: dir = float3(1, -debiased.y, -debiased.x); 
			break;

		case 1: dir = float3(-1, -debiased.y, debiased.x); 
			break;

		case 2: dir = float3(debiased.x, 1, debiased.y); 
			break;

		case 3: dir = float3(debiased.x, -1, -debiased.y); 
			break;

		case 4: dir = float3(debiased.x, -debiased.y, 1); 
			break;

		case 5: dir = float3(-debiased.x, -debiased.y, -1); 
			break;
	};

	return normalize(dir);
}

#define sqr(a)		((a)*(a))
#endif // _TORQUE_HLSL_
