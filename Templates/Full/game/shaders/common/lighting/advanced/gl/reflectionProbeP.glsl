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
#include "../../../gl/torque.glsl"
#include "../../../gl/lighting.glsl"
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
uniform float cubeMips;

uniform vec4 rtParams0;

uniform vec3 probeWSPos;
uniform vec3 probeLSPos;
uniform vec4 vsFarPlane;

uniform float radius;
uniform vec2 attenuation;

uniform mat4 worldToObj;
uniform mat4 cameraToWorld;

uniform vec3 eyePosWorld;
uniform vec3 bbMin;
uniform vec3 bbMax;

uniform float useSphereMode;

// Box Projected IBL Lighting
// Based on: http://www.gamedev.net/topic/568829-box-projected-cubemap-environment-mapping/
// and https://seblagarde.wordpress.com/2012/09/29/image-based-lighting-approaches-and-parallax-corrected-cubemap/
vec3 boxProject(vec3 wsPosition, vec3 reflectDir, vec3 boxWSPos, vec3 boxMin, vec3 boxMax)
{ 
    vec3 nrdir = reflectDir;
	vec3 offset = wsPosition;
    vec3 plane1vec = (boxMax - offset) / nrdir;
    vec3 plane2vec = (boxMin - offset) / nrdir;
	
	vec3 furthestPlane = max(plane1vec, plane2vec);
	float dist = min(min(furthestPlane.x, furthestPlane.y), furthestPlane.z);
    vec3 posonbox = offset + nrdir * dist;

    return posonbox - boxWSPos;
}

vec3 iblBoxSpecular(vec3 normal, vec3 wsPos, float roughness, vec3 surfToEye,
                    sampler2D brdfTexture, 
                    samplerCube radianceCube,
                    vec3 boxPos,
                    vec3 boxMin,
                    vec3 boxMax)
{
    float ndotv = clamp(dot(normal, surfToEye), 0.0, 1.0);

    // BRDF
    vec2 brdf = textureLod(brdfTexture, vec2(roughness, ndotv),0).xy;

    // Radiance (Specular)
	float maxmip = pow(cubeMips+1,2);
    float lod = roughness*maxmip;
    vec3 r = reflect(surfToEye, normal);
    vec3 cubeR = normalize(r);
    cubeR = boxProject(wsPos, cubeR, boxPos, boxMin, boxMax);
	
    vec3 radiance = textureLod(radianceCube, cubeR, lod).xyz * (brdf.x + brdf.y);
    
    return radiance;
}

float defineBoxSpaceInfluence(vec3 surfPosWS, vec3 probePos, float radius, float atten)
{
    vec3 surfPosLS = tMul( worldToObj, vec4(surfPosWS,1.0)).xyz;

    vec3 boxMinLS = probePos-(vec3(1,1,1)*radius);
    vec3 boxMaxLS = probePos+(vec3(1,1,1)*radius);

    float boxOuterRange = length(boxMaxLS - boxMinLS);
    float boxInnerRange = boxOuterRange / atten;

    vec3 localDir = vec3(abs(surfPosLS.x), abs(surfPosLS.y), abs(surfPosLS.z));
    localDir = (localDir - boxInnerRange) / (boxOuterRange - boxInnerRange);

    return max(localDir.x, max(localDir.y, localDir.z)) * -1;
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
    float blendVal = 1.0;
	if(useSphereMode>0)
    {
		vec3 L = probeWSPos - surface.P;
		blendVal = 1.0-length(L)/radius;
		clip(blendVal);		
    }
    else
    {
        float tempAttenVal = 3.5;
		blendVal = defineBoxSpaceInfluence(surface.P, probeWSPos, radius, tempAttenVal);
		clip(blendVal);
		float compression = 0.05;
		blendVal=(1.0-compression)+blendVal*compression;
	}
	//render into the bound space defined above
	vec3 surfToEye = normalize(surface.P - eyePosWorld);
	vec3 irradiance = textureLod(irradianceCubemap, surface.N,0).xyz;
	vec3 specular = iblBoxSpecular(surface.N, surface.P, surface.roughness, surfToEye, BRDFTexture, cubeMap, probeWSPos, bbMin, bbMax);
   vec3 F = FresnelSchlickRoughness(surface.NdotV, surface.f0, surface.roughness);
   specular *= F;
   //energy conservation
	vec3 kD = vec3(1.0) - F;
	kD *= 1.0 - surface.metalness;
   //final diffuse color
   vec3 diffuse = kD * irradiance * surface.baseColor.rgb;
   
   OUT_col = vec4(diffuse + specular * surface.ao, blendVal);
}
