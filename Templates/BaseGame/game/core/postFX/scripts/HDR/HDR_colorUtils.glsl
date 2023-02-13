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

vec3 TO_Exposure (vec3 x, float exposureValue, vec3 colorFilter)
{
   x = exp2(vec3(exposureValue))/2 * colorFilter;
   return x;     
} 

vec3 TO_Saturation (vec3 x, float saturation)
{   
    float L = hdrLuminance(x); 
	x = mix(vec3(L), x, saturation);	
    return x; 
}   
     
float TO_LogContrast (float x, float contrast)
{       
    float a =  0.15 + (log2(x + 0.0001f ) - 0.15)* contrast ;
    return clamp(exp2(a)-0.0001f,0.0 , 2.5);  
} 

float KarisAverage(float3 col)
{
	float luma = rgbToHSL(col).z;
	return 1.0 / (1.0f + luma);
}