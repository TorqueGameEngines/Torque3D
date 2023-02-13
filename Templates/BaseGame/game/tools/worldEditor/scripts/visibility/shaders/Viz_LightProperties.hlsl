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

#include "../../../../core/rendering/shaders/postFX/postFx.hlsl"
#include "../../../../core/rendering/shaders/shaderModel.hlsl"
#include "../../../../core/rendering/shaders/shaderModelAutoGen.hlsl"
#include "../../../../core/rendering/shaders/lighting.hlsl"

TORQUE_UNIFORM_SAMPLER2D(deferredBuffer, 0);
TORQUE_UNIFORM_SAMPLER2D(colorBuffer, 1);
TORQUE_UNIFORM_SAMPLER2D(matInfoBuffer, 2);
TORQUE_UNIFORM_SAMPLER2D(ssaoMaskTex, 3);
TORQUE_UNIFORM_SAMPLER2D(backbufferTex, 4);
TORQUE_UNIFORM_SAMPLER2D(glowBuffer, 5);

uniform float mode;
uniform float3 eyePosWorld;
uniform float4x4 cameraToWorld;

float4 main( PFXVertToPix IN ) : TORQUE_TARGET0
{     
    //unpack normal and linear depth 
    float4 normDepth = TORQUE_DEFERRED_UNCONDITION(deferredBuffer, IN.uv0.xy);

    //create surface
    Surface surface = createSurface(normDepth, TORQUE_SAMPLER2D_MAKEARG(colorBuffer),TORQUE_SAMPLER2D_MAKEARG(matInfoBuffer),
        IN.uv0.xy, eyePosWorld, IN.wsEyeRay, cameraToWorld);

    [branch]
    if(mode == 0)
        return float4(surface.baseColor.rgb,1);
    else if(mode == 1)
        return float4(surface.N.rgb,1);
    else if(mode == 2)
        return float4(surface.ao.rrr,1);
    else if(mode == 3)
        return float4(surface.roughness.rrr,1);
    else if(mode == 4)
        return float4(surface.metalness.rrr,1);
    else if(mode == 5)
        return float4(surface.depth.rrr,1);
    else if(mode == 6) //Diffuse Color
        return float4(surface.albedo.rgb,1);
    else if(mode == 7) //Specular Color
    {
        float3 specularColor = surface.baseColor.rgb * surface.ao;
        return float4(specularColor.rgb,1);
    }
    else if(mode == 8) //Mat Flags
        return float4(surface.matFlag.rrr,1);
    else if(mode == 9)
        return float4(surface.P.xyz,1);
    else if(mode == 10)
        return float4(surface.R.xyz,1);
    else if(mode == 11)
        return float4(surface.F.rgb,1);
    else if(mode == 12)
        float4(TORQUE_TEX2D( ssaoMaskTex, IN.uv0 ).rgb, 1.0);
    else if(mode == 13)
        float4(TORQUE_TEX2D( backbufferTex, IN.uv0 ).rgb, 1.0);
    else if(mode == 14)
        float4(TORQUE_TEX2D( glowBuffer, IN.uv0 ).rgb, 1.0);

    return float4(0,0,0,1);   
}
