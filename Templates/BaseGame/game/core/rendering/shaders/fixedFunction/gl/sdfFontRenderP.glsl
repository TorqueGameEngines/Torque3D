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

in vec4 color;
in vec2 texCoord;

uniform sampler2D diffuseMap;
uniform vec2 texDim;

out vec4 OUT_col;

// Customizable parameters   
float sdfThreshold = 0.5;      // Center threshold for the edge of the glyph
                               // Min: 0.4 , Max: 0.6  
float slopeMultiplier = 0.5;   // Multiplies the slope of the transition
                               // Min: 0.5 (softer edges), Max: 4.0 (sharper edges)
float inBias = -0.01;          // Shifts the threshold inward 
                               // Min: -0.05 (slightly thinner), Max: 0.0 (default, no inward shift)
float outBias = 0.04;          // Shifts the threshold outward 
                               // Min: 0.0 (default, no outward shift), Max: 0.05 (slightly thicker)
float smoothness = 0.05;       // Controls the falloff region
                               // Min: 0.005 (very sharp edges), Max: 0.05 (soft, anti-aliased edges)
int supersample = 4;           // Supersampling factor
                               // Min: 1 (no supersampling), Max: 8 (high-quality, computationally expensive)
float alphaThreshold = 0.01;   // Sets the alpha threshold 

void main() 
{
    float distance = texture(diffuseMap, texCoord).a;

    float adjustedThreshold = sdfThreshold + inBias - outBias;

    float edge = (distance - adjustedThreshold) * slopeMultiplier;

    // Apply smoothing for anti-aliasing
    float alpha = smoothstep(-smoothness, smoothness, edge);

    // Supersampling for high-quality edges
    if (supersample > 1)
    {
        vec2 texelSize = 1.0 / texDim;
        vec2 offsets[4];
        offsets[0] = vec2(-0.5, -0.5) * texelSize;
        offsets[1] = vec2( 0.5, -0.5) * texelSize;
        offsets[2] = vec2(-0.5,  0.5) * texelSize;
        offsets[3] = vec2( 0.5,  0.5) * texelSize;

        float totalAlpha = 0.0; 
        for (int i = 0; i < supersample; ++i)
        {
            vec2 offsetCoord = texCoord + offsets[i % 4]; 
            float sampleDist = texture(diffuseMap, offsetCoord).a;
            float sampleEdge = (sampleDist - adjustedThreshold) * slopeMultiplier;
            totalAlpha += smoothstep(-smoothness, smoothness, sampleEdge);
        }
        alpha = totalAlpha / float(supersample);
    }

    // Discard fragments with alpha below the threshold
    if (alpha < alphaThreshold)
        discard;

    // Debug: Uncomment to visualize alpha field
    //OUT_col = vec4(alpha, alpha, alpha, 1.0);

    OUT_col = vec4(color.rgb, alpha);
}