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
#line 24
// sRGB => XYZ => D65_2_D60 => AP1 => RRT_SAT
const mat3 ACESInputMat = mat3
(     
     0.59719, 0.07600, 0.02840,
     0.35458, 0.90834, 0.13383,
     0.04823, 0.01566, 0.83777
); 

// ODT_SAT => XYZ => D60_2_D65 => sRGB
const mat3 ACESOutputMat = mat3
(     
     1.60475, -0.10208, -0.00327,
     -0.53108,  1.10813, -0.07276,
     -0.07367, -0.00605,  1.07602
);

vec3 RRTAndODTFit(vec3 x, float w)
{
     vec3 a = vec3((x * (x + 0.0245786f) - 0.000090537f) / (x * (0.983729f * x + 0.4329510f) + 0.238081f));
     vec3 b = vec3((w * (w + 0.0245786f) - 0.000090537f) / (w * (0.983729f * w + 0.4329510f) + 0.238081f));
     return a/b;
}

vec3 ACESFitted(vec3 x, float w)
{
     x = tMul(ACESInputMat, x);

     // Apply RRT and ODT
     x = RRTAndODTFit(x, w);

     x = tMul(ACESOutputMat, x);
     
     // Clamp to [0, 1]
    return saturate(x);
     
}


// Luminance Reinhard Operator as explained in: 
// Source: https://imdoingitwrong.wordpress.com/2010/08/19/why-reinhard-desaturates-my-blacks-3/  
vec3 TO_Reinhard(vec3 x, float w) 
{
     vec3 n = x * (1.0f + (x / (w * w)));
     return saturate(n / (1.0f + x)); 
} 
           
// John Hable Uncharted 2 Operator
// We're actually using his filmic curve from: https://www.slideshare.net/naughty_dog/lighting-shading-by-john-hable
vec3 TO_HableU2(vec3 x, float w)
{
      
     //x *= 1.5f;	  //Hardcoded Exposure
	 vec3 curr =  vec3(((x* (0.22f * x + 0.10f * 0.30f) + 0.20f * 0.01f)/
	                 (x* (0.22f * x + 0.30f) + 0.20f * 0.30f))-0.01f/0.30f);
	 
	 vec3 white = vec3(((w* (0.22f * w + 0.10f * 0.30f) + 0.20f * 0.01f)/
	                 (w* (0.22f * w + 0.30f) + 0.20f * 0.30f))-0.01f/0.30f);
	  
     return saturate(curr / white);        
}
  
// Jim Hejl 2015 Filmic Curve 
// Source: https://twitter.com/jimhejl/status/633777619998130176/
vec3 TO_Hejl (vec3 x, float w)
{
     vec4 vh = vec4 (x, w);
	 vec4 va = (1.425 * vh) + 0.05f;
	 vec4 vf = ((vh * va + 0.004f) / ((vh * (va + 0.55f) + 0.0491f))) - 0.0821f;
	
	return saturate(vf.rgb / vf.www);
}


vec3 TO_Linear (vec3 x)
{
     return saturate((x * (1.8 * x + 1.4)) / (x * (1.8 * x + 0.5) + 1.5));
}


/* Narkowicz ACES Tonemap Curve
   Source: https://knarkowicz.wordpress.com/2016/01/06/aces-filmic-tone-mapping-curve/
vec3 ACES_Narkowicz( vec3 x )
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
vec3 TO_Filmic(vec3 x)
{   
     x = max(0,x-0.004f);
     return (x*(6.2f*x+.5f))/(x*(6.2f*x+1.7f)+0.06f);
}   

*/  