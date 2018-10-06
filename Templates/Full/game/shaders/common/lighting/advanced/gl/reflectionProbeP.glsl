#include "../../../gl/hlslCompat.glsl"
#include "shadergen:/autogenConditioners.h"

#include "farFrustumQuad.glsl"
#include "lightingUtils.glsl"
#include "../../../gl/lighting.glsl"
#include "../../../gl/torque.glsl"
#line 8

in vec4 pos;
in vec4 wsEyeDir;
in vec4 ssPos;
in vec4 vsEyeDir;

uniform sampler2D deferredBuffer;
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

uniform mat4x4 invViewMat;

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

vec3 iblBoxDiffuse(vec3 normal,
					vec3 wsPos, 
                    samplerCube irradianceCube, 
                    vec3 boxPos,
                    vec3 boxMin,
                    vec3 boxMax)
{
    // Irradiance (Diffuse)
    vec3 cubeN = normalize(normal);
    vec3 irradiance = texture(irradianceCube, cubeN).xyz;

    return irradiance;
}

vec3 iblBoxSpecular(vec3 normal,
					vec3 wsPos, 
					float roughness,
                    vec3 surfToEye, 
                    sampler2D brdfTexture, 
                    samplerCube radianceCube,
                    vec3 boxPos,
                    vec3 boxMin,
                    vec3 boxMax)
{
    float ndotv = clamp(dot(normal, surfToEye), 0.0, 1.0);

    // BRDF
    vec2 brdf = texture(brdfTexture, vec2(roughness, ndotv)).xy;

    // Radiance (Specular)
	float maxmip = pow(cubeMips+1,2);
    float lod = roughness*maxmip;
    vec3 r = reflect(surfToEye, normal);
    vec3 cubeR = normalize(r);
    cubeR = boxProject(wsPos, cubeR, boxPos, boxMin, boxMax);
	
    vec3 radiance = textureLod(radianceCube, cubeR, lod).xyz * (brdf.x + brdf.y);
    
    return radiance;
}

float defineSphereSpaceInfluence(vec3 centroidPosVS, float rad, vec2 atten, vec3 surfPosVS, vec3 norm)
{
    // Build light vec, get length, clip pixel if needed
    vec3 lightVec = centroidPosVS - surfPosVS;
    float lenLightV = length( lightVec );
    if (( rad - lenLightV )<0)
		return -1;

    // Get the attenuated falloff.
    float attn = attenuate( vec4(1,1,1,1), atten, lenLightV );
    if ((attn - 1e-6)<0)
		return -1;

    // Normalize lightVec
    lightVec = lightVec /= lenLightV;

    // If we can do dynamic branching then avoid wasting
    // fillrate on pixels that are backfacing to the light.
    float nDotL = abs(dot( lightVec, norm ));

    return saturate( nDotL * attn );
}

float defineBoxSpaceInfluence(vec3 surfPosWS, vec3 probePos, float rad, vec2 atten) //atten currently unused
{
    vec3 boxMin = probePos-(vec3(0.5,0.5,0.5)*rad);
	vec3 boxMax = probePos+(vec3(0.5,0.5,0.5)*rad);
	//Try to clip anything that falls outside our box as well
	//TODO: Make it support rotated boxes as well
	if(surfPosWS.x > boxMax.x || surfPosWS.y > boxMax.y || surfPosWS.z > boxMax.z ||
		surfPosWS.x < boxMin.x || surfPosWS.y < boxMin.y || surfPosWS.z < boxMin.z)
		return -1;
		
	float blendVal = 1;
	//vec3 atten = min(boxMax-surfPosWS,surfPosWS-boxMin);
	//blendVal = min(min(atten.x,atten.y),atten.z);
	return blendVal;
}

float defineDepthInfluence(vec3 probePosWS, vec3 surfPosWS, samplerCube radianceCube)
{
	//TODO properly: filter out pixels projected uppon by probes behind walls by looking up the depth stored in the probes cubemap alpha
	//and comparing legths
	vec3 probeToSurf = probePosWS-surfPosWS;
			
	float depthRef = texture(cubeMap, -probeToSurf,0).a*radius;
	float dist = length( probeToSurf );

	return depthRef-dist;
}

out vec4 OUT_col;
out vec4 OUT_col1;

void main()
{   

    // Compute scene UV
    vec3 ssPos = ssPos.xyz / ssPos.w; 

    vec2 uvScene = getUVFromSSPos( ssPos, rtParams0 );

    // Matinfo flags
    vec4 matInfo = texture( matInfoBuffer, uvScene ); 

    // Sample/unpack the normal/z data
    vec4 deferredSample = deferredUncondition( deferredBuffer, uvScene );
    vec3 normal = deferredSample.rgb;
    float depth = deferredSample.a;
    if (depth>0.9999)
    {
      OUT_col = vec4(0.0);
      OUT_col1 = vec4(0.0);
      return;
    }

    // Need world-space normal.
    vec3 wsNormal = tMul(vec4(normal, 1), invViewMat).rgb;

    vec3 eyeRay = getDistanceVectorToPlane( -vsFarPlane.w, vsEyeDir.xyz, vsFarPlane );
    vec3 viewSpacePos = eyeRay * depth;

    vec3 wsEyeRay = tMul(vec4(eyeRay, 1), invViewMat).rgb;

    // Use eye ray to get ws pos
    vec3 worldPos = vec3(eyePosWorld + wsEyeRay * depth);
		  
    float blendVal = 1.0;
	
	//clip bounds and (TODO properly: set falloff)
	if(useSphereMode>0)
    {
        blendVal = defineSphereSpaceInfluence(probeLSPos, radius, attenuation, viewSpacePos, normal);
    }
    else
    {
	   blendVal = defineBoxSpaceInfluence(worldPos, probeWSPos, radius*2, attenuation);
    }
	if (blendVal<0)
	{
      OUT_col = vec4(0.0);
      OUT_col1 = vec4(0.0);
      return;
	}
      
	//flip me on to have probes filter by depth
	//clip(defineDepthInfluence(probeWSPos, worldPos, cubeMap));
		
	
	//render into the bound space defined above
	vec3 surfToEye = normalize(worldPos.xyz-eyePosWorld.xyz);
	OUT_col = vec4(iblBoxDiffuse(wsNormal, worldPos, irradianceCubemap, probeWSPos, bbMin, bbMax), blendVal);
	OUT_col1 = vec4(iblBoxSpecular(wsNormal, worldPos, 1.0 - matInfo.b, surfToEye, BRDFTexture, cubeMap, probeWSPos, bbMin, bbMax), blendVal);
}
