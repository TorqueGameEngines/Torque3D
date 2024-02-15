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
};

uniform float2 sizeUni;
uniform float2 rectCenter;
uniform float radius;

float RoundedRectSDF(float2 p, float2 size, float radius)
{
    float2 halfSize = size / 2.0;

    // Calculate distance to each side of the rectangle
    float2 dist = abs(p) - halfSize + radius;

    // Compute the distance to the rounded corners
    float cornerDist = length(max(abs(p) - (halfSize - float2(radius, radius)), 0.0));

    // Return the minimum distance (negative inside, positive outside)
    return min(max(dist.x, dist.y), 0.0) + cornerDist - radius;
}
 
float4 main(Conn IN) : TORQUE_TARGET0
{  
    float2 p = IN.HPOS.xy;
    float2 halfSize = sizeUni / 2; 

    float2 offset = rectCenter - halfSize;
    p -= rectCenter;
    
    // Calculate signed distance field for rounded rectangle 
    float sdf = RoundedRectSDF(p, sizeUni, radius);

    // Apply smoothing to create rounded effect 
    float alpha = smoothstep(1.0, 0.0, sdf); 

    return float4(IN.color.rgb, IN.color.a * alpha);
}