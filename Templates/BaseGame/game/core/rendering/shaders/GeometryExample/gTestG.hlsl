#include "../shaderModel.hlsl"

struct GSConn
{
   float4 HPOS : TORQUE_POSITION;
};

struct PSConn
{
    float4 HPOS : TORQUE_POSITION;
};

uniform float4x4 projMat;
uniform float4x4 viewMat;

uniform float explosionAmt;

[maxvertexcount(3)]
void main(triangle GSConn input[3], inout TriangleStream<PSConn> outstream)
{
    float3 edgeA = input[0].HPOS.xyz - input[1].HPOS.xyz;
    float3 edgeB = input[2].HPOS.xyz - input[1].HPOS.xyz;
    float3 norm = normalize(cross(edgeA, edgeB)); 

    float3 dir = norm * explosionAmt;

    PSConn output;
    for(uint i =0; i < 3; i++)
    {
        output.HPOS = input[i].HPOS + float4(dir, 0.0);
        output.HPOS = mul(viewMat, output.HPOS);
        output.HPOS = mul(projMat, output.HPOS);
        outstream.Append(output);
    }
    
    outstream.RestartStrip();
}