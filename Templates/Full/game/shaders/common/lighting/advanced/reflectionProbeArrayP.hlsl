#include "../../shaderModelAutoGen.hlsl"

#include "farFrustumQuad.hlsl"
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
TORQUE_UNIFORM_SAMPLER2D(colorBuffer, 1);
TORQUE_UNIFORM_SAMPLER2D(matInfoBuffer, 2);
TORQUE_UNIFORM_SAMPLERCUBE(cubeMap, 3);
TORQUE_UNIFORM_SAMPLERCUBE(irradianceCubemap, 4);
TORQUE_UNIFORM_SAMPLER2D(BRDFTexture, 5);
uniform float cubeMips;

uniform float4 rtParams0;

uniform float3 probeWSPos;
uniform float3 probeLSPos;
uniform float4 vsFarPlane;

uniform float  radius;
uniform float2 attenuation;

uniform float4x4 worldToObj;
uniform float4x4 cameraToWorld;

uniform float3 eyePosWorld;
uniform float3 bbMin;
uniform float3 bbMax;

uniform float useSphereMode;

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

float3 iblBoxSpecular(float3 normal, float3 wsPos, float roughness, float3 surfToEye,
                     TORQUE_SAMPLER2D(brdfTexture), 
                    //TORQUE_SAMPLERCUBE(radianceCube),
                    float3 boxPos,
                    float3 boxMin,
                    float3 boxMax)
{
   float ndotv = clamp(dot(normal, surfToEye), 0.0, 1.0);

    // BRDF
   float2 brdf = TORQUE_TEX2DLOD(brdfTexture, float4(roughness, ndotv,0.0,0.0)).xy;

    // Radiance (Specular)
	float maxmip = pow(cubeMips+1,2);
   float lod = roughness*maxmip;
   float3 r = reflect(surfToEye, normal);
   float3 cubeR = normalize(r);
   cubeR = boxProject(wsPos, cubeR, boxPos, boxMin, boxMax);
	
   float3 radiance = float3(1,1,1);//TORQUE_TEXCUBELOD(radianceCube, float4(cubeR, lod)).xyz * (brdf.x + brdf.y);
    
   return radiance;
}

float4 main(ConvexConnectP IN) : SV_TARGET
{
    // Compute scene UV
   float3 ssPos = IN.ssPos.xyz / IN.ssPos.w; 
   float2 uvScene = getUVFromSSPos( ssPos, rtParams0 );

   //eye ray WS/LS
   float3 vsEyeRay = getDistanceVectorToPlane( -vsFarPlane.w, IN.vsEyeDir.xyz, vsFarPlane );
   float3 wsEyeRay = mul(cameraToWorld, float4(vsEyeRay, 0)).xyz;
   
   //unpack normal and linear depth 
   float4 normDepth = TORQUE_DEFERRED_UNCONDITION(deferredBuffer, uvScene);
   
   //create surface
   Surface surface = createSurface( normDepth, TORQUE_SAMPLER2D_MAKEARG(colorBuffer),TORQUE_SAMPLER2D_MAKEARG(matInfoBuffer),
                                    uvScene, eyePosWorld, wsEyeRay, cameraToWorld);		  
	float blendVal = 1.0;

    [unroll]
    for(float i=0; i < 10; i++)
    {
        float3 probeWSPos = float3(i * 1.1, 0, 2);
        float3 L = probeWSPos - surface.P;
		blendVal = 1.0-length(L)/radius;
		clip(blendVal);		
    }

    //render into the bound space defined above
	float3 surfToEye = normalize(surface.P - eyePosWorld);
	float3 irradiance = float3(1,0,0);//TORQUE_TEXCUBELOD(irradianceCubemap, float4(surface.N,0)).xyz;
	float3 specular = iblBoxSpecular(surface.N, surface.P, surface.roughness, surfToEye, TORQUE_SAMPLER2D_MAKEARG(BRDFTexture)/*, TORQUE_SAMPLERCUBE_MAKEARG(cubeMap)*/, probeWSPos, bbMin, bbMax);
   float3 F = FresnelSchlickRoughness(surface.NdotV, surface.f0, surface.roughness);
   specular *= F;
   //energy conservation
	float3 kD = 1.0.xxx - F;
	kD *= 1.0 - surface.metalness;
   //final diffuse color
   float3 diffuse = kD * irradiance * surface.baseColor.rgb;

   return float4(diffuse + specular * surface.ao, blendVal);

    /*float3 N = getCubeDir(face,IN.uv);
    float3 irradiance = 0;
    
    // tangent space calculation from origin point
    float3 up    = float3(0.0, 0.0, 1.0);
    float3 right = cross(up, N);
    up           = cross(N, right);
       
    float sampleDelta = 0.025;
    int nrSamples = 0;
    for(float phi = 0.0; phi < M_2PI_F; phi += sampleDelta)
    {
        for(float theta = 0.0; theta < M_HALFPI_F; theta += sampleDelta)
        {
            // spherical to cartesian (in tangent space)
            float3 tangentSample = float3(sin(theta) * cos(phi),  sin(theta) * sin(phi), cos(theta));
            // tangent space to world
            float3 sampleVec = tangentSample.x * right + tangentSample.y * up + tangentSample.z * N; 

            irradiance += TORQUE_TEXCUBE(environmentMap, sampleVec).rgb * cos(theta) * sin(theta);
            nrSamples++;
        }
    }
    irradiance = M_PI_F * irradiance * (1.0 / float(nrSamples));
    
    return float4(irradiance, 1.0);*/

    //return float4(1,0,0,1);

    //float4 texCoord = float4( 1,0,0, 1 );    

    //return texCoord;
}