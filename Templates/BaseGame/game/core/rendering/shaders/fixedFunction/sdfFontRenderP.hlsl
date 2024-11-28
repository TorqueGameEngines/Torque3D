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

#include "../shaderModel.hlsl"

struct Conn
{
   float4 HPOS             : TORQUE_POSITION;
   float4 color            : COLOR;
   float2 texCoord         : TEXCOORD0;
};

TORQUE_UNIFORM_SAMPLER2D(diffuseMap, 0);
uniform float2 texDim; 

// Customizable parameters
static const float sdfThreshold = 0.6;      // Center threshold for the edge of the glyph
static const float slopeMultiplier = 1.0;   // Multiplies the slope of the transition
static const float inBias = -0.05;            // Shifts the threshold inward
static const float outBias = 0.05;           // Shifts the threshold outward
static const float smoothness = 0.05;       // Controls the falloff region
static const float alphaThreshold = 0.1f;   // Sets the alpha threshold
static const int supersample = 4;           // Supersampling factor
  
float4 main( Conn IN ) : TORQUE_TARGET0 
{
    float distance = TORQUE_TEX2D(diffuseMap, IN.texCoord).a;

    float adjustedThreshold = sdfThreshold + inBias - outBias;

    float edge = (distance - adjustedThreshold) * slopeMultiplier;
 
    // Smooth edges using the distance field
    float alpha = smoothstep(-smoothness, smoothness, edge);

    if(supersample > 1)
    {
        float2 texelSize = float2(1.0f / texDim.x, 1.0f / texDim.y);
        float2 offsets[4] = {
            float2(-0.5, -0.5) * texelSize, 
            float2(0.5, -0.5) * texelSize,
            float2(-0.5, 0.5) * texelSize, 
            float2(0.5, 0.5) * texelSize
        };

        float totalAlpha = 0.0; 
        for(uint i = 0; i < (uint)supersample; ++i)
        {
            float2 offsetCoord = IN.texCoord + offsets[i % 4]; 
            float sampleDist = TORQUE_TEX2D(diffuseMap, offsetCoord).a;
            float sampleEdge = (sampleDist - adjustedThreshold) * slopeMultiplier;
            totalAlpha += smoothstep(-smoothness, smoothness, sampleEdge);
        }
        alpha = totalAlpha / float(supersample);
    }

    // Ensure alpha does not go below a minimum threshold for transparency
    // alpha = max(alpha, alphaThreshold);

    // Debug: Uncomment to visualize alpha field
    //return float4(alpha, alpha, alpha, 1.0);

    return float4(IN.color.rgb, alpha);
}