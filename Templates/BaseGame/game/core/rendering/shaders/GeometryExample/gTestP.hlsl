#include "../shaderModel.hlsl"

struct PSConn
{
    float4 HPOS : TORQUE_POSITION;
};

uniform float4 col;

float4 main(PSConn IN) : TORQUE_TARGET0
{
   return float4(col.rgb,1.0);
}