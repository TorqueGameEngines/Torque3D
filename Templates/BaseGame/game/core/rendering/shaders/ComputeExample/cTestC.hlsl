
RWTexture2D<float4> BufferOut;

[numthreads(32, 32, 1)]
void main(uint3 id : SV_DispatchThreadID)
{
    uint2 dims;
    BufferOut.GetDimensions(dims.x, dims.y);

    float2 uv = float2(id.xy) / float2(dims);

    float checker = fmod(floor(id.x / 32.0) + floor(id.y / 32.0), 2.0);
    float3 color = lerp(float3(uv, 1.0), float3(0.0, 0.0, 0.0), checker);

    BufferOut[id.xy] = float4(color, 1.0);
}