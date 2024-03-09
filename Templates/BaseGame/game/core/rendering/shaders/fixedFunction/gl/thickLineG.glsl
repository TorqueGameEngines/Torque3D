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

layout (lines) in; 
layout (triangle_strip, max_vertices = 4) out;

in VS_OUT {
    vec4 color;
} gs_in[];


out vec4 fragColor;

uniform float thickness;
uniform vec2 oneOverViewport;

void main()
{
    // Calculate the direction of the line segment
    vec2 direction = normalize(gl_in[1].gl_Position.xy - gl_in[0].gl_Position.xy);

    // Calculate perpendicular direction
    vec2 perpendicular = normalize(vec2(-direction.y, direction.x));

    // Calculate offset for thickness 
    vec2 offset = vec2(thickness * oneOverViewport.x, thickness *  oneOverViewport.y) * perpendicular;
 
    // Calculate vertices for the line with thickness
    vec2 p0 = gl_in[0].gl_Position.xy + offset;
    vec2 p1 = gl_in[0].gl_Position.xy - offset;
    vec2 p2 = gl_in[1].gl_Position.xy + offset;
    vec2 p3 = gl_in[1].gl_Position.xy - offset;

    fragColor = gs_in[0].color;
    gl_Position = vec4(p0, 0.0f, 1.0f);
    EmitVertex();

    gl_Position = vec4(p1, 0.0f, 1.0f);
    EmitVertex();

    gl_Position = vec4(p2, 0.0f, 1.0f);
    EmitVertex();

    gl_Position = vec4(p3, 0.0f, 1.0f);
    EmitVertex();

    EndPrimitive();
}