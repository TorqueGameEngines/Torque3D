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

#include "../../../../core/rendering/shaders/postFX/gl/postFx.glsl"
#include "../../../../core/rendering/shaders/gl/hlslCompat.glsl"
#include "../../../../core/rendering/shaders/gl/lighting.glsl"
#include "shadergen:/autogenConditioners.h"

#line 27

uniform sampler2D deferredBuffer;
uniform sampler2D colorBuffer;
uniform sampler2D matInfoBuffer;
uniform sampler2D ssaoMaskTex;
uniform sampler2D backbufferTex;
uniform sampler2D glowBuffer;

uniform float mode;
uniform vec3 eyePosWorld;
uniform mat4 cameraToWorld;

out vec4 OUT_col;

void main()
{     
    //unpack normal and linear depth 
    vec4 normDepth = deferredUncondition(deferredBuffer, IN_uv0);

    //create surface
    Surface surface = createSurface(normDepth, colorBuffer, matInfoBuffer, IN_uv0.xy, eyePosWorld, IN_wsEyeRay, cameraToWorld);

    OUT_col = vec4(0,0,0,1);   

    if(mode == 0)
        OUT_col.rgb = surface.baseColor.rgb;
    else if(mode == 1)
        OUT_col = vec4(surface.N.rgb,1);
    else if(mode == 2)
        OUT_col = vec4(surface.ao, surface.ao, surface.ao, 1);
    else if(mode == 3)
        OUT_col = vec4(surface.roughness, surface.roughness, surface.roughness, 1);
    else if(mode == 4)
        OUT_col = vec4(surface.metalness, surface.metalness, surface.metalness,1);
    else if(mode == 5)
        OUT_col = vec4(surface.depth, surface.depth, surface.depth,1);
    else if(mode == 6) //Diffuse Color
        OUT_col = vec4(surface.albedo.rgb,1);
    else if(mode == 7) //Specular Color
        OUT_col = vec4(surface.baseColor.rgb * surface.ao,1);
    else if(mode == 8) //Mat Flags
        OUT_col = vec4(surface.matFlag, surface.matFlag, surface.matFlag,1);
    else if(mode == 9)
        OUT_col = vec4(surface.P.xyz,1);
    else if(mode == 10)
        OUT_col = vec4(surface.R.xyz,1);
    else if(mode == 11)
        OUT_col = vec4(surface.F.rgb,1);
    else if(mode == 12)
        OUT_col = vec4(texture( ssaoMaskTex, IN_uv0 ).rgb, 1.0);
    else if(mode == 13)
        OUT_col = vec4(texture( backbufferTex, IN_uv0 ).rgb, 1.0);
    else if(mode == 14)
        OUT_col = vec4(texture( glowBuffer, IN_uv0 ).rgb, 1.0);
}
