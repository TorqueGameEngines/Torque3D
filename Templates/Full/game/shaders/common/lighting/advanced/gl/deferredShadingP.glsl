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

#include "../../../gl/hlslCompat.glsl"
#include "shadergen:/autogenConditioners.h"
#include "../../../postFx/gl/postFX.glsl"
#include "../../../gl/torque.glsl"

uniform sampler2D colorBufferTex;
uniform sampler2D diffuseLightingBuffer;
uniform sampler2D matInfoTex;
uniform sampler2D specularLightingBuffer;
uniform sampler2D deferredTex;

out vec4 OUT_col;

void main()
{
   float depth = deferredUncondition( deferredTex, uv0 ).w;
   if (depth>0.9999)
   {
      OUT_col = vec4(0.0);
      return;
   }
   
   vec3 colorBuffer = texture( colorBufferTex, uv0 ).rgb; //albedo
   vec4 matInfo = texture( matInfoTex, uv0 ); //flags|smoothness|ao|metallic
   bool emissive = getFlag(matInfo.r, 0);
   if (emissive)
   {
      OUT_col = float4(colorBuffer, 1.0);
	  return;
   }
   
   vec4 diffuseLighting = texture( diffuseLightingBuffer, uv0 ); //shadowmap*specular
   
   vec3 specularLighting = texture( specularLightingBuffer, uv0 ).rgb; //environment mapping*lightmaps
   float metalness = matInfo.a;
      
   float frez = diffuseLighting.a;
   
   vec3 diffuseColor = colorBuffer - (colorBuffer * metalness);
   vec3 reflectColor = specularLighting*colorBuffer;
   colorBuffer = diffuseColor+lerp(reflectColor,specularLighting,frez);
   colorBuffer *= max(diffuseLighting.rgb,vec3(0,0,0)); 
   
   OUT_col =  hdrEncode(vec4(colorBuffer,1.0));
}
