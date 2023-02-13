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
#include "../../../gl/hlslCompat.glsl"
#include "shadergen:/autogenConditioners.h"
#include "farFrustumQuad.glsl"
#include "../../../gl/lighting.glsl"
#include "../../../gl/torque.glsl"
#line 27

in vec4 pos;
in vec4 wsEyeDir;
in vec4 ssPos;
in vec4 vsEyeDir;

uniform sampler2D deferredBuffer;
uniform sampler2D colorBuffer;
uniform sampler2D matInfoBuffer;
uniform samplerCube cubeMap;
uniform samplerCube irradianceCubemap;
uniform sampler2D BRDFTexture;

uniform vec4 rtParams0;

uniform vec4 vsFarPlane;
uniform mat4 cameraToWorld;
uniform vec3 eyePosWorld;

vec3 iblSpecular(in Surface surface, vec3 F)
{
	const float MAX_REFLECTION_LOD = 4.0;
	vec3 prefilteredColor = textureLod(cubeMap, surface.R, surface.roughness * MAX_REFLECTION_LOD).rgb;
	vec2 envBRDF  = texture(BRDFTexture, vec2(surface.NdotV, surface.roughness)).rg;
	return prefilteredColor * (F * envBRDF.x + envBRDF.y);
}

out vec4 OUT_col;
void main()
{
    // Compute scene UV
    vec2 uvScene = getUVFromSSPos( ssPos.xyz/ssPos.w, rtParams0 );

   //eye ray WS/LS
   vec3 vsEyeRay = getDistanceVectorToPlane( -vsFarPlane.w, vsEyeDir.xyz, vsFarPlane );
   vec3 wsEyeRay = tMul(cameraToWorld, vec4(vsEyeRay, 0)).xyz;
   
   //unpack normal and linear depth 
   vec4 normDepth = deferredUncondition(deferredBuffer, uvScene);
   
   //create surface
   Surface surface = createSurface( normDepth, colorBuffer, matInfoBuffer,
                                    uvScene, eyePosWorld, wsEyeRay, cameraToWorld);

   vec3 F = FresnelSchlickRoughness(surface.NdotV, surface.f0, surface.roughness);
   vec3 irradiance = textureLod(irradianceCubemap, surface.N,0).rgb;
   vec3 specular = iblSpecular(surface, F);
   //energy conservation
	vec3 kD = vec3(1.0) - F;
	kD *= 1.0 - surface.metalness;
   //final diffuse color
   vec3 diffuse = kD * irradiance * surface.baseColor.rgb;

   OUT_col = vec4(diffuse + specular * surface.ao, 0);
}
