//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~//
// This is the original Post-Effect Shader used in the resource,
// "Silhoute selection via postFX for Torque3D" posted by Konrad Kiss.
// http://www.garagegames.com/community/resources/view/17821
// (currently not used for default AFX selection-highlighting)
//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~//

#include "../common/shaderModel.hlsl"
#include "../common/shaderModelAutoGen.hlsl"
#include "shaders/common/postFX/postFx.hlsl"  
  
TORQUE_UNIFORM_SAMPLER2D(highlightBuffer,0);
TORQUE_UNIFORM_SAMPLER2D(backBuffer,1);
uniform float2 targetSize;
				 
float4 main( PFXVertToPix IN ) : TORQUE_TARGET0
{  
   float2 offsets[9] = {  
      float2( 0.0,  0.0),  
      float2(-1.0, -1.0),  
      float2( 0.0, -1.0),  
      float2( 1.0, -1.0),  
      float2( 1.0,  0.0),  
      float2( 1.0,  1.0),  
      float2( 0.0,  1.0),  
      float2(-1.0,  1.0),  
      float2(-1.0,  0.0),  
   };

   float2 PixelSize = 1.0 / targetSize;  

	float avgval = 0;

   for(int i = 0; i < 9; i++)  
   {  
      float2 uv = IN.uv0 + offsets[i] * PixelSize;  
      float4 cpix = float4( TORQUE_TEX2D( highlightBuffer, uv ).rrr, 1.0 );
		avgval += clamp(cpix.r*256, 0, 1);
	}
	
	avgval /= 9;

	float vis = round(1.0-(abs(frac(avgval)-0.5)*2));

	float4 bb = TORQUE_TEX2D(backBuffer, IN.uv0);
	float4 outlineColor = float4(vis, 0, 0, vis);
	float4 overlayColor = float4(avgval, 0, 0, avgval);
	//float4 outlineColor = float4(vis*0.5, vis*0.5, vis*0.5, vis*0.5);
	//float4 overlayColor = float4(avgval, avgval, avgval, avgval);

	overlayColor *= 0.4;

	bb = lerp(bb, overlayColor, overlayColor.a);

	outlineColor = lerp(bb, outlineColor, outlineColor.a);

	return outlineColor;
}  