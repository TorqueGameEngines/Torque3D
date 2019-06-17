#include "shaders/common/postFx/postFx.hlsl"
#include "../../torque.hlsl"

TORQUE_UNIFORM_SAMPLER2D(backBuffer, 0);
uniform float threshold;

float4 main(PFXVertToPix IN) : TORQUE_TARGET0
{
   float4 base = TORQUE_TEX2D(backBuffer, IN.uv0);
   
   const int NUM = 9;
   
   const float2 c[NUM] =
	{
		float2(-0.0078125, 0.0078125), 
		float2( 0.00 ,     0.0078125),
		float2( 0.0078125, 0.0078125),
		float2(-0.0078125, 0.00 ),
		float2( 0.0,       0.0),
		float2( 0.0078125, 0.007 ),
		float2(-0.0078125,-0.0078125),
		float2( 0.00 ,    -0.0078125),
		float2( 0.0078125,-0.0078125),
	};
	
	int i;
	float3 col[NUM];
	
	for (i=0; i < NUM; i++)
	{
		col[i] = TORQUE_TEX2D(backBuffer, IN.uv0 + 0.2*c[i]);
	}
	
	float3 rgb2lum = float3(0.30, 0.59, 0.11);
	float lum[NUM];
	for (i = 0; i < NUM; i++)
	{
		lum[i] = dot(col[i].xyz, rgb2lum);
	}
	
	float x = lum[2]+  lum[8]+2*lum[5]-lum[0]-2*lum[3]-lum[6];
	float y = lum[6]+2*lum[7]+  lum[8]-lum[0]-2*lum[1]-lum[2];
	float edge =(x*x + y*y < threshold)? 1.0:0.0;
	
	base.rgb *= edge;
   
   return base;
}