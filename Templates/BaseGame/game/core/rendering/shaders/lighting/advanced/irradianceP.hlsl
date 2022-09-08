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

#include "../../torque.hlsl"

struct ConnectData
{
    float4 hpos    : TORQUE_POSITION;
    float2 uv      : TEXCOORD;
};

uniform int face;

TORQUE_UNIFORM_SAMPLERCUBE(environmentMap, 0);

float4 main(ConnectData IN) : TORQUE_TARGET0
{
    float3 N = getCubeDir(face,IN.uv);
    float3 irradiance = 0;
    
    // tangent space calculation from origin point
    float3 up    = float3(0.0, 0.0, 1.0);
    float3 right = cross(up, N);
    up           = cross(N, right);
       
    float sampleDelta = 0.025;
    int nrSamples = 0;
    for(float phi = 0.0; phi < M_2PI_F; phi += sampleDelta)
    {
        for(float theta = 0.0; theta < M_HALFPI_F; theta += sampleDelta)
        {
            // spherical to cartesian (in tangent space)
            float3 tangentSample = float3(sin(theta) * cos(phi),  sin(theta) * sin(phi), cos(theta));
            // tangent space to world
            float3 sampleVec = tangentSample.x * right + tangentSample.y * up + tangentSample.z * N; 

            irradiance += TORQUE_TEXCUBE(environmentMap, sampleVec).rgb * cos(theta) * sin(theta);
            nrSamples++;
        }
    }
    irradiance = M_PI_F * irradiance * (1.0 / float(nrSamples));
    
    return float4(toGamma(irradiance), 1.0);
}