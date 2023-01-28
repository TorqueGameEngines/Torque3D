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
      
#include "core/rendering/shaders/torque.hlsl"
#include "core/rendering/shaders/postFX/postFx.hlsl"
#include "core/rendering/shaders/shaderModelAutoGen.hlsl"
#include "./HDR_Tonemap.hlsl"   
#include "./HDR_colorUtils.hlsl"
                 
TORQUE_UNIFORM_SAMPLER2D(sceneTex, 0);
TORQUE_UNIFORM_SAMPLER2D(luminanceTex, 1);
TORQUE_UNIFORM_SAMPLER2D(bloomTex, 2);

uniform float2 texSize0;
uniform float2 texSize2;
 
uniform float g_fEnableToneMapping;
uniform float g_fMiddleGray;

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
uniform float3 colorFilter;
            	 
			
float3 Tonemap(float3 x)
{     
    //ACES           
    if(g_fTonemapMode == 1.0f)    
   {              
      x = ACESFitted(x, whitePoint); //ACES is crushing our blacks, need to pre-expose!  
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
      float3 nL = TO_Reinhard(L, whitePoint);
      x *= (nL / L);                  	    	                           
   }  
        
   //Linear Tonemap  
   else if (g_fTonemapMode == 5.0)
   {  
      x = toLinear(x);   	   
   }
        
   return x;
}  
   
float4 main( PFXVertToPix IN ) : TORQUE_TARGET0
{
   float4 sample = hdrDecode( TORQUE_TEX2D( sceneTex, IN.uv0 ) );
   float adaptedLum = TORQUE_TEX2D( luminanceTex, float2( 0.5f, 0.5f ) ).r;
   float4 bloom = TORQUE_TEX2D( bloomTex, IN.uv2 ); 
        	    
   // Add the bloom effect.     
   sample.rgb += bloom.rgb;        
   		 	
	//Apply Exposure     
   sample.rgb *= TO_Exposure(sample.rgb, exposureValue, colorFilter); 
                                        
   	//Apply Saturation
   sample.rgb = TO_Saturation(sample.rgb, saturationValue);	      	    
                                                         
   // Apply Screen contrast 
   sample.rgb = ((sample.rgb - 0.5f) * Contrast) + 0.5f;
      
   // Apply Screen brightness
   //sample.rgb += Brightness;
                                                  
   	 //Apply Color Contrast   
   sample.r = TO_LogContrast(sample.r, logContrast);
   sample.g = TO_LogContrast(sample.g, logContrast);  
   sample.b = TO_LogContrast(sample.b, logContrast);
                                                                                                     
   //tonemapping - TODO fix up eye adaptation
   if ( g_fEnableToneMapping > 0.0f )  
   {    
      float adapation = 1.0;  
	   
      if( g_fEnableAutoExposure > 0.0f )  
	   {  	     		 
         adaptedLum = saturate(adaptedLum); 
         float linearExposure = (g_fMiddleGray * rcp(adaptedLum));
         adapation = log2(max(linearExposure, 0.0001f));     
		          
         sample.rgb = Tonemap(exposureValue * sample.rgb *exp2(adapation)); 
	   }   
         
        else {
		
		  sample.rgb = Tonemap(sample.rgb);
	    }		
      	           
   }      
      
   return sample;
}  
      