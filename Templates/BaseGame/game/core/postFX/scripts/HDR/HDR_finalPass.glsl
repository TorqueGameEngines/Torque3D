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

#include "core/rendering/shaders/gl/torque.glsl"
#include "core/rendering/shaders/gl/hlslCompat.glsl"
#include "core/rendering/shaders/postFX/gl/postFx.glsl"
#include "shadergen:/autogenConditioners.h"
#include "HDR_Tonemap.glsl"   
#include "HDR_colorUtils.glsl"
#line 29
uniform sampler2D sceneTex;
uniform sampler2D luminanceTex;
uniform sampler2D bloomTex;

uniform vec2 texSize0;
uniform vec2 texSize2;

uniform float g_fEnableToneMapping;
uniform float g_fMiddleGray;
uniform float g_fWhiteCutoff;

uniform float g_fEnableAutoExposure;
uniform float g_fTonemapMode;

//uniform float g_fBloomScale;

uniform float g_fOneOverGamma;
uniform float Brightness;
uniform float Contrast;

//Explicit HDR Params
uniform float exposureValue;
uniform float whitePoint;
uniform float logContrast;
uniform float brightnessValue;
uniform float saturationValue;
uniform vec3 colorFilter;

out vec4 OUT_col;


vec3 Tonemap(vec3 x)
{     
    //ACES      
    if(g_fTonemapMode == 1.0f)    
   {
	  x = ACESFitted(x, whitePoint);  //ACES is crushing our blacks, need to pre-expose!    	  
   }             
   //Filmic Helji	       
   if(g_fTonemapMode == 2.0f) 
   {             
      x = TO_Hejl(x, whitePoint);
   }   
   //Hable Uncharted 2          
   if (g_fTonemapMode == 3.0)      
   {                                              
      x = TO_HableU2(x, whitePoint);         
   }      
                           
   //Reinhard       
   if (g_fTonemapMode == 4.0)
   {   
	  float L = hdrLuminance(x);   
      vec3 nL = TO_Reinhard(vec3(L), whitePoint);
      x *= (nL / L);                  	    	                           
   }  
        
   //Linear Tonemap  
   else if (g_fTonemapMode == 5.0)
   {  
      x = toLinear(x);    	   
   }
        
   return x;
}  

void main()
{
   vec4 _sample = hdrDecode( texture( sceneTex, IN_uv0 ) );
   float adaptedLum = texture( luminanceTex, vec2( 0.5f, 0.5f ) ).r;
   vec4 bloom = texture( bloomTex, IN_uv2 );

   // Add the bloom effect.     
   _sample.rgb +=bloom.rgb;  
           
   //Apply Exposure     
   _sample.rgb *= TO_Exposure(_sample.rgb, exposureValue, colorFilter);
   
   	//Apply Saturation
   _sample.rgb = TO_Saturation(_sample.rgb, saturationValue);

   // Apply contrast
   _sample.rgb = ((_sample.rgb - 0.5f) * Contrast) + 0.5f;

   // Apply brightness
   //_sample.rgb += Brightness;
   
    //Apply Color Contrast   
   _sample.r = TO_LogContrast(_sample.r, logContrast);
   _sample.g = TO_LogContrast(_sample.g, logContrast);  
   _sample.b = TO_LogContrast(_sample.b, logContrast);

   //tonemapping - TODO fix up eye adaptation
   if ( g_fEnableToneMapping > 0.0f )  
   {    
      float adapation = 1.0;  
	   
      if( g_fEnableAutoExposure > 0.0f )  
	   {  	     		 
         adaptedLum = saturate(adaptedLum); 
         float linearExposure = (g_fMiddleGray / adaptedLum);
         adapation = log2(max(linearExposure, 0.0001f));     
		          
         _sample.rgb = Tonemap(exposureValue * _sample.rgb *exp2(adapation)); 
	   }   
         
        else {
		
		  _sample.rgb = Tonemap(_sample.rgb);
	    }		
      	           
   }      

   OUT_col = _sample;
}
