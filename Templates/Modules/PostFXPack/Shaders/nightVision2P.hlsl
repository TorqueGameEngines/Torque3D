#include "shaders/common/postFx/postFx.hlsl"
#include "shadergen:/autogenConditioners.h"

uniform float accumTime;
TORQUE_UNIFORM_SAMPLER2D(backBuffer, 0);
uniform float luminanceThreshold; // 0.2
uniform float colorAmplification; // 4.0

float4 main(PFXVertToPix IN) : TORQUE_TARGET0
{
   float speed = 100;
   float Yres = 1024;
   float brightness = 0.2;
   
   float4 finalColor = float4(1.0, 1.0, 1.0, 1.0);
   
   float2 uv;
   uv.x = 0.4 * sin(accumTime * 50.0);
   uv.y = 0.4 * cos(accumTime * 50.0);
   //float m = TORQUE_TEX2D(maskTex, gl_TexCoord[0].st).r;
   //vec3 n = texture2D(noiseTex, (gl_TexCoord[0].st*3.5) + uv).rgb;
   float3 c = TORQUE_TEX2D(backBuffer, IN.uv0).rgb;

   float lum = dot(float3(0.30, 0.59, 0.11), c);
   if (lum < luminanceThreshold)
      c *= colorAmplification; 

   float3 visionColor = float3(0.1, 0.95, 0.2);
   finalColor.rgb = c * visionColor;
   
   // add noise
   float noise = IN.uv0.x * IN.uv0.y * accumTime * speed;
   noise = fmod(noise, 10) * fmod(noise, 100);   
   noise = fmod(noise, 0.01);
   
   float3 color = finalColor.rgb;
   color = color + color * saturate(noise.xxx * 200);
   
   // add banding
	float sin,cos;
	sincos(IN.uv0.y * Yres, sin, cos);
   color += color * float3(sin, cos, sin) * brightness;
   
   finalColor.rgb = color;
   
   return finalColor;

}