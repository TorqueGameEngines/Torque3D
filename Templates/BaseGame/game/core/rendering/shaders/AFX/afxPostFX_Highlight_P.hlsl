//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~//
// This Post-Effect Shader is adapted from the resource,
// "Silhoute selection via postFX for Torque3D" posted by Konrad Kiss.
// http://www.garagegames.com/community/resources/view/17821
//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~//

#include "../common/shaderModel.hlsl"
#include "../common/shaderModelAutoGen.hlsl"
#include "shaders/common/postFX/postFx.hlsl"  
  
TORQUE_UNIFORM_SAMPLER2D(highlightBuffer,0);
TORQUE_UNIFORM_SAMPLER2D(backBuffer,1);
uniform float2 targetSize;

float4 main( PFXVertToPix IN ) : TORQUE_TARGET0
{  
	float4 bufferColor = TORQUE_TEX2D(backBuffer, IN.uv0);
	float4 highlightColor = TORQUE_TEX2D(highlightBuffer, IN.uv0);

   if (highlightColor.a > 0.0)
      bufferColor.rgb = clamp(highlightColor.a*(bufferColor.rgb*1.4 + 0.05), 0, 1);

   //if (highlightColor.r + highlightColor.g + highlightColor.b > 0.0)
   //   bufferColor.rgb = clamp(bufferColor.rgb*1.4 + 0.05, 0, 1);

	return bufferColor;
}  