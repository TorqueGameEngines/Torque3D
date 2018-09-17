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

uniform float4 rtParams0;

uniform float3 probeWSPos;
uniform float3 probeLSPos;
uniform float4 vsFarPlane;

uniform float  radius;
uniform float2 attenuation;

uniform float4x4 invViewMat;

uniform float3 eyePosWorld;
uniform float3 bbMin;
uniform float3 bbMax;

uniform float useSphereMode;

float3 iblSpecular(float3 v, float3 n, float roughness)
{
   float3 R = reflect(v, n);
   const float MAX_REFLECTION_LOD = 6.0;
   float3 prefilteredColor = TORQUE_TEXCUBELOD(cubeMap, float4(R, roughness * MAX_REFLECTION_LOD)).rgb;
   float2 envBRDF = TORQUE_TEX2D(BRDFTexture, float2(max(dot(n, v), 0.0), roughness)).rg;
   //return prefilteredColor * (envBRDF.x + envBRDF.y);
   return prefilteredColor;
}

// Box Projected IBL Lighting
// Based on: http://www.gamedev.net/topic/568829-box-projected-cubemap-environment-mapping/

float3 boxProject(float3 wsPosition, float3 reflectDir, float3 boxWSPos, float3 boxMin, float3 boxMax)
{ 
    float3 nrdir = normalize(reflectDir);
    float3 rbmax = (boxMax - wsPosition) / nrdir;
    float3 rbmin = (boxMin - wsPosition) / nrdir;

    float3 rbminmax;
    rbminmax.x = (nrdir.x > 0.0) ? rbmax.x : rbmin.x;
    rbminmax.y = (nrdir.y > 0.0) ? rbmax.y : rbmin.y;
    rbminmax.z = (nrdir.z > 0.0) ? rbmax.z : rbmin.z; 

    float fa = min(min(rbminmax.x, rbminmax.y), rbminmax.z);
    float3 posonbox = wsPosition + nrdir * fa;

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
                    float3 viewDir, 
                    TORQUE_SAMPLER2D(brdfTexture), 
                    TORQUE_SAMPLERCUBE(radianceCube),
                    float3 boxPos,
                    float3 boxMin,
                    float3 boxMax)
{
    float3 v = viewDir;
    float3 n = normalize(normal);
    float ndotv = clamp(dot(n, v), 0.0, 1.0);

    // BRDF
    float2 brdf = TORQUE_TEX2D(brdfTexture, float2(roughness, ndotv)).xy;

    // Radiance (Specular)
    float lod = roughness * 6.0;
    float3 r = 2.0 * ndotv * n - v; // reflect(v, n);
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

PS_OUTPUT main( ConvexConnectP IN )
{ 
    PS_OUTPUT Output = (PS_OUTPUT)0;

    // Compute scene UV
    float3 ssPos = IN.ssPos.xyz / IN.ssPos.w; 

    //float4 hardCodedRTParams0 = float4(0,0.0277777780,1,0.972222209);
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

    float4 color = float4(1, 1, 1, 1);
    float4 ref = float4(0,0,0,0);
    float alpha = 1;

    float3 eyeRay = getDistanceVectorToPlane( -vsFarPlane.w, IN.vsEyeDir.xyz, vsFarPlane );
    float3 viewSpacePos = eyeRay * depth;

    float3 wsEyeRay = mul(float4(eyeRay, 1), invViewMat).rgb;

    // Use eye ray to get ws pos
    float3 worldPos = float3(eyePosWorld + wsEyeRay * depth);
    float smoothness = min((1.0 - matInfo.b)*11.0 + 1.0, 8.0);//bump up to 8 for finalization

    if(useSphereMode)
    {
        // Build light vec, get length, clip pixel if needed
        float3 lightVec = probeLSPos - viewSpacePos;
        float lenLightV = length( lightVec );
        clip( radius - lenLightV );

        // Get the attenuated falloff.
        float atten = attenuate( float4(1,1,1,1), attenuation, lenLightV );
        clip( atten - 1e-6 );

        // Normalize lightVec
        lightVec = normalize(lightVec);

        // If we can do dynamic branching then avoid wasting
        // fillrate on pixels that are backfacing to the light.
        float nDotL = abs(dot( lightVec, normal ));

        float Sat_NL_Att = saturate( nDotL * atten );

        float3 reflectionVec = reflect(IN.wsEyeDir, float4(wsNormal,nDotL)).xyz;

        float3 nrdir = normalize(reflectionVec);
        float3 rbmax = (bbMax - worldPos.xyz) / nrdir;
        float3 rbmin = (bbMin - worldPos.xyz) / nrdir;

        float3 rbminmax = (nrdir > 0.0) ? rbmax : rbmin;
        float fa = min(min(rbminmax.x,rbminmax.y),rbminmax.z);
		  if (dot( lightVec, normal )<0.0f)
           clip(fa);

        float3 posOnBox = worldPos.xyz + nrdir * fa;
        reflectionVec = posOnBox - probeWSPos;

        reflectionVec = mul(probeWSPos,reflectionVec);

        ref = float4(reflectionVec, smoothness);

        alpha = Sat_NL_Att;
		float roughness = 1 - matInfo.b;

		float3 irradiance = TORQUE_TEXCUBELOD(irradianceCubemap, ref).rgb;

		float3 specular = TORQUE_TEXCUBELOD(cubeMap, ref).rgb;// iblSpecular(wsEyeRay, wsNormal, roughness);

		Output.diffuse = float4(irradiance.rgb, alpha);
		Output.spec = float4(specular.rgb, alpha);

		return Output;
    }
    else
    {
       //Try to clip anything that falls outside our box as well
       //TODO: Make it support rotated boxes as well
       if(worldPos.x > bbMax.x || worldPos.y > bbMax.y || worldPos.z > bbMax.z ||
          worldPos.x < bbMin.x || worldPos.y < bbMin.y || worldPos.z < bbMin.z)
          clip(-1);
		  
       float blendVal = 1.0;
	   float3 pixDir = normalize(eyePosWorld.xyz - worldPos.xyz);
       Output.diffuse = float4(iblBoxDiffuse(wsNormal, worldPos, TORQUE_SAMPLERCUBE_MAKEARG(irradianceCubemap), probeWSPos, bbMin, bbMax), blendVal);
	   Output.spec = float4(iblBoxSpecular(wsNormal, worldPos, 1.0 - matInfo.b, pixDir, TORQUE_SAMPLER2D_MAKEARG(BRDFTexture), TORQUE_SAMPLERCUBE_MAKEARG(cubeMap), probeWSPos, bbMin, bbMax), blendVal);
       return Output;	   
    }
}
