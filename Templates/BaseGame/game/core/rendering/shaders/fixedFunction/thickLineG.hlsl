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

struct PSConn
{
   float4 HPOS             : TORQUE_POSITION;
   float4 color            : COLOR;
};

uniform float thickness;
uniform float2 oneOverViewport;

[maxvertexcount(4)]
void main(line Conn lineSegment[2], inout TriangleStream<PSConn> outstream)
{
    // Calculate the direction of the line segment
    float2 direction = normalize(lineSegment[1].HPOS.xy - lineSegment[0].HPOS.xy);

    // Calculate perpendicular direction
    float2 perpendicular = normalize(float2(-direction.y, direction.x));

    // Calculate offset for thickness 
    float2 offset = float2(thickness * oneOverViewport.x, thickness *  oneOverViewport.y) * perpendicular;
 
    // Calculate vertices for the line with thickness
    float2 p0 = lineSegment[0].HPOS.xy + offset;
    float2 p1 = lineSegment[0].HPOS.xy - offset;
    float2 p2 = lineSegment[1].HPOS.xy + offset;
    float2 p3 = lineSegment[1].HPOS.xy - offset;

    PSConn output;

    output.HPOS = float4(p0, 0.0f, 1.0f);
    output.color = lineSegment[0].color;
    outstream.Append(output);

    output.HPOS = float4(p1, 0.0f, 1.0f);
    output.color = lineSegment[0].color;
    outstream.Append(output);

    output.HPOS = float4(p2, 0.0f, 1.0f);
    output.color = lineSegment[1].color;
    outstream.Append(output);

    output.HPOS = float4(p3, 0.0f, 1.0f);
    output.color = lineSegment[1].color;
    outstream.Append(output);

    outstream.RestartStrip();
}