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

out vec4 OUT_col;

uniform vec2 sizeUni;
uniform float radius;
uniform vec2 rectCenter;
uniform float borderSize;
uniform vec4 borderCol;

float circle(vec2 p, vec2 center, float r)
{
    return length(p - center);
}
 
void main()
{   
    float dist = circle(gl_FragCoord.xy, rectCenter, radius);
    
    vec4 fromColor = borderCol;
    vec4 toColor = vec4(0.0, 0.0, 0.0, 0.0);

    if(dist < radius)
    {
        dist = abs(dist) - radius;
        
        if(dist < (radius - (borderSize)))
        {
            toColor = color;
            dist = abs(dist) - (borderSize);
        }

        float blend = smoothstep(0.0, 1.0, dist);
        OUT_col = mix(fromColor, toColor, blend);
    }
    
    dist = abs(dist) - radius; 
    float blend = smoothstep(0.0, 1.0, dist);
    OUT_col = mix(fromColor, toColor, blend);
}