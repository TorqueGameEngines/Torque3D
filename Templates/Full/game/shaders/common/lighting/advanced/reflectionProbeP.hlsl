#include "../../shaderModelAutoGen.hlsl"

#include "farFrustumQuad.hlsl"
#include "lightingUtils.hlsl"
#include "../../lighting.hlsl"
#include "../../torque.hlsl"

struct ConvexConnectP
{
   float4 pos : TORQUE_POSITION;
   float4 wsEyeDir : TEXCOORD0;
   float4 ssPos : TEXCOORD1;
   float4 vsEyeDir : TEXCOORD2;
};

TORQUE_UNIFORM_SAMPLER2D(deferredBuffer, 0);
TORQUE_UNIFORM_SAMPLER2D(matInfoBuffer, 1);
TORQUE_UNIFORM_SAMPLERCUBE(cubeMap, 2);
TORQUE_UNIFORM_SAMPLERCUBE(irradianceCubemap, 3);
TORQUE_UNIFORM_SAMPLER2D(BRDFTexture, 4);
uniform float cubeMips;

uniform float4 rtParams0;

uniform float3 probeWSPos;
uniform float3 probeLSPos;
uniform float4 vsFarPlane;

uniform float  radius;
uniform float2 attenuation;

uniform float4x4 invViewMat;
uniform float4x4 worldToObj;

uniform float3 eyePosWorld;
uniform float3 bbMin;
uniform float3 bbMax;

uniform float useSphereMode;

// Box Projected IBL Lighting
// Based on: http://www.gamedev.net/topic/568829-box-projected-cubemap-environment-mapping/
// and https://seblagarde.wordpress.com/2012/09/29/image-based-lighting-approaches-and-parallax-corrected-cubemap/
float3 boxProject(float3 wsPosition, float3 reflectDir, float3 boxWSPos, float3 boxMin, float3 boxMax)
{ 
    float3 nrdir = reflectDir;
	float3 offset = wsPosition;
    float3 plane1vec = (boxMax - offset) / nrdir;
    float3 plane2vec = (boxMin - offset) / nrdir;
	
	float3 furthestPlane = max(plane1vec, plane2vec);
	float dist = min(min(furthestPlane.x, furthestPlane.y), furthestPlane.z);
    float3 posonbox = offset + nrdir * dist;

    return posonbox - boxWSPos;
}

float3 iblBoxDiffuse(float3 normal,
					float3 wsPos, 
                    TORQUE_SAMPLERCUBE(irradianceCube), 
                    float3 boxPos,
                    float3 boxMin,
                    float3 boxMax)
{
    // Irradiance (Diffuse)
    float3 cubeN = normalize(normal);
    float3 irradiance = TORQUE_TEXCUBE(irradianceCube, cubeN).xyz;

    return irradiance;
}

float3 iblBoxSpecular(float3 normal,
					float3 wsPos, 
					float roughness,
                    float3 surfToEye, 
                    TORQUE_SAMPLER2D(brdfTexture), 
                    TORQUE_SAMPLERCUBE(radianceCube),
                    float3 boxPos,
                    float3 boxMin,
                    float3 boxMax)
{
    float ndotv = clamp(dot(normal, surfToEye), 0.0, 1.0);

    // BRDF
    float2 brdf = TORQUE_TEX2D(brdfTexture, float2(roughness, ndotv)).xy;

    // Radiance (Specular)
	float maxmip = pow(cubeMips+1,2);
    float lod = roughness*maxmip;
    float3 r = reflect(surfToEye, normal);
    float3 cubeR = normalize(r);
    cubeR = boxProject(wsPos, cubeR, boxPos, boxMin, boxMax);
	
    float3 radiance = TORQUE_TEXCUBELOD(radianceCube, float4(cubeR, lod)).xyz * (brdf.x + brdf.y);
    
    return radiance;
}

struct PS_OUTPUT
{
    float4 diffuse: TORQUE_TARGET0;
    float4 spec: TORQUE_TARGET1;
};

float defineSphereSpaceInfluence(float3 centroidPosVS, float rad, float2 atten, float3 surfPosVS, float3 norm)
{
    // Build light vec, get length, clip pixel if needed
    float3 lightVec = centroidPosVS - surfPosVS;
    float lenLightV = length( lightVec );
    if (( rad - lenLightV )<0)
		return -1;

    // Get the attenuated falloff.
    float attn = attenuate( float4(1,1,1,1), atten, lenLightV );
    if ((attn - 1e-6)<0)
		return -1;

    // Normalize lightVec
    lightVec = lightVec /= lenLightV;

    // If we can do dynamic branching then avoid wasting
    // fillrate on pixels that are backfacing to the light.
    float nDotL = abs(dot( lightVec, norm ));

    return saturate( nDotL * attn );
}

float defineBoxSpaceInfluence(float3 surfPosWS, float3 probePos, float radius, float atten)
{
    float3 surfPosLS = mul( worldToObj, float4(surfPosWS,1.0)).xyz;

    float3 boxMinLS = probePos-(float3(1,1,1)*radius);
    float3 boxMaxLS = probePos+(float3(1,1,1)*radius);

    float boxOuterRange = length(boxMaxLS - boxMinLS);
    float boxInnerRange = boxOuterRange / atten;

    float3 localDir = float3(abs(surfPosLS.x), abs(surfPosLS.y), abs(surfPosLS.z));
    localDir = (localDir - boxInnerRange) / (boxOuterRange - boxInnerRange);

    float influenceVal =  max(localDir.x, max(localDir.y, localDir.z)) * -1;

    return influenceVal;
}

float defineDepthInfluence(float3 probePosWS, float3 surfPosWS, TORQUE_SAMPLERCUBE(radianceCube))
{
	//TODO properly: filter out pixels projected uppon by probes behind walls by looking up the depth stored in the probes cubemap alpha
	//and comparing legths
	float3 probeToSurf = probePosWS-surfPosWS;
			
	float depthRef = TORQUE_TEXCUBELOD(cubeMap, float4(-probeToSurf,0)).a*radius;
	float dist = length( probeToSurf );

	return depthRef-dist;
}

PS_OUTPUT main( ConvexConnectP IN )
{ 
    PS_OUTPUT Output = (PS_OUTPUT)0;

    // Compute scene UV
    float3 ssPos = IN.ssPos.xyz / IN.ssPos.w; 

    float2 uvScene = getUVFromSSPos( ssPos, rtParams0 );

    // Matinfo flags
    float4 matInfo = TORQUE_TEX2D( matInfoBuffer, uvScene ); 

    // Sample/unpack the normal/z data
    float4 deferredSample = TORQUE_DEFERRED_UNCONDITION( deferredBuffer, uvScene );
    float3 normal = deferredSample.rgb;
    float depth = deferredSample.a;
    if (depth>0.9999)
          clip(-1);

    // Need world-space normal.
    float3 wsNormal = mul(float4(normal, 1), invViewMat).rgb;

    float3 eyeRay = getDistanceVectorToPlane( -vsFarPlane.w, IN.vsEyeDir.xyz, vsFarPlane );
    float3 viewSpacePos = eyeRay * depth;

    float3 wsEyeRay = mul(float4(eyeRay, 1), invViewMat).rgb;

    // Use eye ray to get ws pos
    float3 worldPos = float3(eyePosWorld + wsEyeRay * depth);
		  
    float blendVal = 1.0;
	
	//clip bounds and (TODO properly: set falloff)
	if(useSphereMode)
    {
        blendVal = defineSphereSpaceInfluence(probeLSPos, radius, attenuation, viewSpacePos, normal);
    }
    else
    {
       float tempAttenVal = 3.5;
	   blendVal = defineBoxSpaceInfluence(worldPos, probeWSPos, radius, tempAttenVal);
    }
	clip(blendVal);
	
	//flip me on to have probes filter by depth
	//clip(defineDepthInfluence(probeWSPos, worldPos, TORQUE_SAMPLERCUBE_MAKEARG(cubeMap)));
		
	
	//render into the bound space defined above
	float3 surfToEye = normalize(worldPos.xyz-eyePosWorld.xyz);
	Output.diffuse = float4(iblBoxDiffuse(wsNormal, worldPos, TORQUE_SAMPLERCUBE_MAKEARG(irradianceCubemap), probeWSPos, bbMin, bbMax), blendVal);
	Output.spec = float4(iblBoxSpecular(wsNormal, worldPos, 1.0 - matInfo.b, surfToEye, TORQUE_SAMPLER2D_MAKEARG(BRDFTexture), TORQUE_SAMPLERCUBE_MAKEARG(cubeMap), probeWSPos, bbMin, bbMax), blendVal);
	Output.diffuse.rgb *= matInfo.g;
	Output.spec.rgb *= matInfo.g;
	return Output;
}
