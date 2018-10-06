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

uniform vec4 vsFarPlane;

uniform float4x4 invViewMat;

uniform vec3 eyePosWorld;

vec3 iblSpecular(vec3 v, vec3 n, float roughness)
{
	vec3 R = reflect(v, n); 
	const float MAX_REFLECTION_LOD = 4.0;
	vec3 prefilteredColor = TORQUE_TEXCUBELOD(cubeMap, vec4(R, roughness * MAX_REFLECTION_LOD)).rgb;
	vec2 envBRDF  = TORQUE_TEX2D(BRDFTexture, vec2(max(dot(n, v), 0.0), roughness)).rg;
	return prefilteredColor * (envBRDF.x + envBRDF.y);
   //return prefilteredColor;
}

out vec4 OUT_col;
out vec4 OUT_col1;

void main()
{
    // Compute scene UV
    vec3 ssPos = IN.ssPos.xyz / IN.ssPos.w; 

    //vec4 hardCodedRTParams0 = vec4(0,0.0277777780,1,0.972222209);
    vec2 uvScene = getUVFromSSPos( ssPos, rtParams0 );

    // Matinfo flags
    vec4 matInfo = TORQUE_TEX2D( matInfoBuffer, uvScene ); 

    // Sample/unpack the normal/z data
    vec4 deferredSample = TORQUE_DEFERRED_UNCONDITION( deferredBuffer, uvScene );
    vec3 normal = deferredSample.rgb;
    float depth = deferredSample.a;
    if (depth>0.9999)
        return Output; 

    // Need world-space normal.
    vec3 wsNormal = mul(vec4(normal, 1), invViewMat).rgb;

    vec3 eyeRay = getDistanceVectorToPlane( -vsFarPlane.w, IN.vsEyeDir.xyz, vsFarPlane );

    vec3 wsEyeRay = mul(vec4(eyeRay, 1), invViewMat).rgb;

    // Use eye ray to get ws pos
    vec3 worldPos = vec3(eyePosWorld + wsEyeRay * depth);

    vec3 reflectionVec = reflect(IN.wsEyeDir, vec4(wsNormal,1)).xyz;

    float roughness = 1 - matInfo.b;

    vec3 v = normalize(eyePosWorld - worldPos);

    vec3 irradiance = TORQUE_TEXCUBE(irradianceCubemap, wsNormal).rgb;

    vec3 specular = iblSpecular(wsEyeRay, wsNormal, roughness);


    OUT_col = vec4(irradiance.rgb, 1);
    OUT_col1 = vec4(specular.rgb, 1);
}
