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


// Stephen Hill's ACES Fit
// Source: https://github.com/TheRealMJP/BakingLab/blob/master/BakingLab/ACES.hlsl

// sRGB => XYZ => D65_2_D60 => AP1 => RRT_SAT
static const float3x3 ACESInputMat =
{
     {0.59719, 0.35458, 0.04823},
     {0.07600, 0.90834, 0.01566},
     {0.02840, 0.13383, 0.83777}
}; 

// ODT_SAT => XYZ => D60_2_D65 => sRGB
static const float3x3 ACESOutputMat =
{
     { 1.60475, -0.53108, -0.07367},
     {-0.10208,  1.10813, -0.00605},
     {-0.00327, -0.07276,  1.07602}
};

float3 RRTAndODTFit(float3 x, float w)
{
     float3 a = (x * (x + 0.0245786f) - 0.000090537f) / (x * (0.983729f * x + 0.4329510f) + 0.238081f);
     float3 b = (w * (w + 0.0245786f) - 0.000090537f) / (w * (0.983729f * w + 0.4329510f) + 0.238081f);
     return a/b;
}

float3 ACESFitted(float3 x, float w)
{
     x = mul(ACESInputMat, x);

     // Apply RRT and ODT
     x = RRTAndODTFit(x, w);

     x = mul(ACESOutputMat, x);
     
     // Clamp to [0, 1]
    return saturate(x);
     
}


// Luminance Reinhard Operator as explained in: 
// Source: https://imdoingitwrong.wordpress.com/2010/08/19/why-reinhard-desaturates-my-blacks-3/  
float3 TO_Reinhard(float3 x, float w) 
{
     float3 n = x * (1.0f + (x / (w * w)));
     return saturate(n / (1.0f + x)); 
} 
           
// John Hable Uncharted 2 Operator
// We're actually using his filmic curve from: https://www.slideshare.net/naughty_dog/lighting-shading-by-john-hable
float3 TO_HableU2(float3 x, float w)
{
      
     //x *= 1.5f;	  //Hardcoded Exposure
	 float3 curr =  ((x* (0.22f * x + 0.10f * 0.30f) + 0.20f * 0.01f)/
	                 (x* (0.22f * x + 0.30f) + 0.20f * 0.30f))-0.01f/0.30f;
	 
	 float3 white = ((w* (0.22f * w + 0.10f * 0.30f) + 0.20f * 0.01f)/
	                 (w* (0.22f * w + 0.30f) + 0.20f * 0.30f))-0.01f/0.30f;
	  
     return saturate(curr / white);        
}
  
// Jim Hejl 2015 Filmic Curve 
// Source: https://twitter.com/jimhejl/status/633777619998130176/
float3 TO_Hejl (float3 x, float w)
{
     float4 vh = float4 (x, w);
	 float4 va = (1.425 * vh) + 0.05f;
	 float4 vf = ((vh * va + 0.004f) / ((vh * (va + 0.55f) + 0.0491f))) - 0.0821f;
	
	return saturate(vf.rgb / vf.www);
}


float3 TO_Linear (float3 x)
{
     return saturate((x * (1.8 * x + 1.4)) / (x * (1.8 * x + 0.5) + 1.5));
}


/* Narkowicz ACES Tonemap Curve
   Source: https://knarkowicz.wordpress.com/2016/01/06/aces-filmic-tone-mapping-curve/
float3 ACES_Narkowicz( float3 x )
{
     const float a = 2.51f;
     const float b = 0.03f;
     const float c = 2.43f;
     const float d = 0.59f;
     const float e = 0.14f;
    return saturate((x*(a*x+b))/(x*(c*x+d)+e));
}

 Filmic ALU Curve Jim Hejl and Richard Burgess-Dawson 
 Source: http://filmicworlds.com/blog/filmic-tonemapping-operators/
float3 TO_Filmic(float3 x)
{   
     x = max(0,x-0.004f);
     return (x*(6.2f*x+.5f))/(x*(6.2f*x+1.7f)+0.06f);
}   

*/  