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
    float4 hpos     : SV_Position;
    float2 uv      : TEXCOORD;
};

TORQUE_UNIFORM_SAMPLERCUBE(environmentMap, 0);

uniform float roughness;
uniform int face;
uniform int mipSize;
uniform int resolution;
float RadicalInverse_VdC(uint bits)
{
	bits = (bits << 16u) | (bits >> 16u);
	bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
	bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
	bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
	bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
	return float(bits) * 2.3283064365386963e-10; // / 0x100000000
}

float2 Hammersley(uint i, uint N)
{
	return float2(float(i) / float(N), RadicalInverse_VdC(i));
}

float DistributionGGX(float3 N, float3 H, float roughness)
{
	float a = roughness * roughness;
	float a2 = a * a;
	float NdotH = max(dot(N, H), 0.0);
	float NdotH2 = NdotH * NdotH;

	float nom = a2;
	float denom = (NdotH2 * (a2 - 1.0) + 1.0);
	denom = M_PI_F * denom * denom;

	return nom / denom;
}

float3 ImportanceSampleGGX(float2 Xi, float3 N)
{
	float a = roughness * roughness;

	float phi = 2.0 * M_PI_F * Xi.x;
	float cosTheta = sqrt((1.0 - Xi.y) / (1.0 + (a*a - 1.0) * Xi.y));
	float sinTheta = sqrt(1.0 - cosTheta * cosTheta);

	// from spherical coordinates to cartesian coordinates
	float3 H;
	H.x = cos(phi) * sinTheta;
	H.y = sin(phi) * sinTheta;
	H.z = cosTheta;

	// from tangent-space vector to world-space sample vector
	float3 up = abs(N.z) < 0.999 ? float3(0.0, 0.0, 1.0) : float3(1.0, 0.0, 0.0);
	float3 tangent = normalize(cross(up, N));
	float3 bitangent = cross(N, tangent);

	float3 sampleVec = tangent * H.x + bitangent * H.y + N * H.z;
	return normalize(sampleVec);
}

float4 prefilterEnvMap(float3 R)
{
    int sampleCount = resolution*2;
	float3 N = R;
	float3 V = R;
	float totalWeight = 0.0;
	float4 prefilteredColor = float4(0.0, 0.0, 0.0, 0.0);

	for (int i = 0; i < sampleCount; ++i)
	{
			float2 Xi = Hammersley(i, sampleCount);
			float3 H = ImportanceSampleGGX(Xi, N);
			float3 L = normalize(2.0 * dot(V, H) * H - V);

			float NdotL = max(dot(N, L), 0.0);
			if (NdotL > 0.0)
			{
				// sample from the environment's mip level based on roughness/pdf
				float D = DistributionGGX(N, H, roughness);
				float NdotH = max(dot(N, H), 0.0);
				float HdotV = max(dot(H, V), 0.0);
				float pdf = D * NdotH / (4.0 * HdotV) + 0.0001;

				float saTexel = 4.0 * M_PI_F / (6.0 * sampleCount * sampleCount);
				float saSample = 1.0 / (float(sampleCount) * pdf + 0.0001);

				float mipLevel = roughness == 0.0 ? 0.0 : 0.5 * log2(saSample / saTexel);

				prefilteredColor += TORQUE_TEXCUBELOD(environmentMap, float4(L, mipLevel)) * NdotL;				

				totalWeight += NdotL;
			}
	}

	return (prefilteredColor / totalWeight);
}

float4 main(ConnectData IN) : TORQUE_TARGET0
{
	float3 N = getCubeDir(face, IN.uv);
	return prefilterEnvMap(N);
}