#include "../shaderModel.hlsl"

struct Appdata
{
	float3 position : POSITION;
};

struct GSConn
{
   float4 HPOS : TORQUE_POSITION;
};

uniform float4x4 modelMat;

GSConn main( Appdata In )
{
   GSConn Out;
   Out.HPOS = mul(modelMat, float4(In.position,1.0));
   return Out;
}
