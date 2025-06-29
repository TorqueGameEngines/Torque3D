
RWTexture2D<float4> BufferOut;

[numthreads(32, 32, 1)]
void main(uint3 id : SV_DispatchThreadID)
{
    float4 col = float4(1.0, 0.0, 0.0, 1.0);

    col.r = float(id.x) / 256.0f;
    col.g = float(id.y) / 256.0f;
    
    BufferOut[id.xy] = col;
}