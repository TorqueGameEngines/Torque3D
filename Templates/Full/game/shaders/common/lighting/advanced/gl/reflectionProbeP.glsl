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

uniform vec4 rtParams0;

uniform vec3 probeWSPos;
uniform vec3 probeLSPos;
uniform vec4 vsFarPlane;

uniform float  lightRange;
uniform vec2 lightAttenuation;

uniform mat4 invViewMat;

uniform vec3 eyePosWorld;
uniform vec3 bbMin;
uniform vec3 bbMax;

uniform float Intensity;

//SHTerms
uniform vec4 SHTerms0;
uniform vec4 SHTerms1;
uniform vec4 SHTerms2;
uniform vec4 SHTerms3;
uniform vec4 SHTerms4;
uniform vec4 SHTerms5;
uniform vec4 SHTerms6;
uniform vec4 SHTerms7;
uniform vec4 SHTerms8;

uniform float SHConsts0;
uniform float SHConsts1;
uniform float SHConsts2;
uniform float SHConsts3;
uniform float SHConsts4;

uniform float useSphereMode;

vec4 decodeSH(vec3 normal)
{
   float x = normal.x;
   float y = normal.y;
   float z = normal.z;

   vec3 l00 = SHTerms0.rgb;

   vec3 l10 = SHTerms1.rgb;
   vec3 l11 = SHTerms2.rgb;
   vec3 l12 = SHTerms3.rgb;

   vec3 l20 = SHTerms4.rgb;
   vec3 l21 = SHTerms5.rgb;
   vec3 l22 = SHTerms6.rgb;
   vec3 l23 = SHTerms7.rgb;
   vec3 l24 = SHTerms8.rgb;

   vec3 result = (
         l00 * SHConsts0 +

         l12 * SHConsts1 * x +
         l10 * SHConsts1 * y +
         l11 * SHConsts1 * z +

         l20 * SHConsts2 * x*y +
         l21 * SHConsts2 * y*z +
         l22 * SHConsts3 * (3.0*z*z - 1.0) +
         l23 * SHConsts2 * x*z +
         l24 * SHConsts4 * (x*x - y*y)
      );

    return vec4(result,1);
}

out vec4 OUT_col;
void main()
{ 
    // Compute scene UV
    vec3 ssPos = ssPos.xyz / ssPos.w; 

    //vec4 hardCodedRTParams0 = vec4(0,0.0277777780,1,0.972222209);
    vec2 uvScene = getUVFromSSPos( ssPos, rtParams0 );

    // Matinfo flags
    vec4 matInfo = texture( matInfoBuffer, uvScene ); 

    // Sample/unpack the normal/z data
    vec4 deferredSample = deferredUncondition( deferredBuffer, uvScene );
    vec3 normal = deferredSample.rgb;
    float depth = deferredSample.a;
    if (depth>0.9999)
        OUT_col = vec4(0,0,0,0); 

    // Need world-space normal.
    vec3 wsNormal = tMul(vec4(normal, 1), invViewMat).rgb;

    vec4 color = vec4(1, 1, 1, 1);
    vec4 ref = vec4(0,0,0,0);
    float alpha = 0;

    vec3 eyeRay = getDistanceVectorToPlane( -vsFarPlane.w, vsEyeDir.xyz, vsFarPlane );
    vec3 viewSpacePos = eyeRay * depth;

    vec3 wsEyeRay = tMul(vec4(eyeRay, 1), invViewMat).rgb;

    // Use eye ray to get ws pos
    vec3 worldPos = vec3(eyePosWorld + wsEyeRay * depth);
    float smoothness = min((1.0 - matInfo.b)*11.0 + 1.0, 8.0);//bump up to 8 for finalization

    if(useSphereMode>0.0)
    {
        // Eye ray - Eye -> Pixel
        
            
        // Build light vec, get length, clip pixel if needed
        vec3 lightVec = probeLSPos - viewSpacePos;
        float lenLightV = length( lightVec );
        clip( lightRange - lenLightV );

        // Get the attenuated falloff.
        float atten = attenuate( vec4(1,1,1,1), lightAttenuation, lenLightV );
        clip( atten - 1e-6 );

        // Normalize lightVec
        lightVec /= lenLightV;

        // If we can do dynamic branching then avoid wasting
        // fillrate on pixels that are backfacing to the light.
        float nDotL = abs(dot( lightVec, normal ));

        float Sat_NL_Att = saturate( nDotL * atten );

        vec3 reflectionVec = reflect(wsEyeDir, vec4(wsNormal,nDotL)).xyz;

        vec3 nrdir = normalize(reflectionVec);
        vec3 rbmax = (bbMax - worldPos.xyz) / nrdir;
        vec3 rbmin = (bbMin - worldPos.xyz) / nrdir;

       vec3 rbminmax = rbmin;
	   if (nrdir.x > 0.0)
          rbminmax.x = rbmax.x;
	   if (nrdir.y > 0.0)
          rbminmax.y = rbmax.y;
	   if (nrdir.z > 0.0)
          rbminmax.z = rbmax.z;
		  
        float fa = min(min(rbminmax.x,rbminmax.y),rbminmax.z);
		  if (dot( lightVec, normal )<0.0f)
           clip(fa);

        vec3 posOnBox = worldPos.xyz + nrdir * fa;
        reflectionVec = posOnBox - probeWSPos;

        //reflectionVec = tMul(probeWSPos,reflectionVec);

        ref = vec4(reflectionVec, smoothness);

        alpha = Sat_NL_Att;
    }
    else
    {
       // Build light vec, get length, clip pixel if needed
       vec3 lightVec = probeLSPos - viewSpacePos;
       float lenLightV = length(lightVec);
       //clip(lightRange - lenLightV);

       // Normalize lightVec
       lightVec /= lenLightV;

       // If we can do dynamic branching then avoid wasting
       // fillrate on pixels that are backfacing to the light.
       float nDotL = abs(dot(lightVec, normal));

       vec3 reflectionVec = reflect(wsEyeDir, vec4(wsNormal, nDotL)).xyz;

       vec3 nrdir = normalize(reflectionVec);
       vec3 rbmax = (bbMax - worldPos.xyz) / nrdir;
       vec3 rbmin = (bbMin - worldPos.xyz) / nrdir;

       vec3 rbminmax = rbmin;
	   if (nrdir.x > 0.0)
          rbminmax.x = rbmax.x;
	   if (nrdir.y > 0.0)
          rbminmax.y = rbmax.y;
	   if (nrdir.z > 0.0)
          rbminmax.z = rbmax.z;
		  
       float fa = min(min(rbminmax.x, rbminmax.y), rbminmax.z);
       if (dot(lightVec, normal)<0.0f)
          clip(fa);

       //Try to clip anything that falls outside our box as well
       //TODO: Make it support rotated boxes as well
       if(worldPos.x > bbMax.x || worldPos.y > bbMax.y || worldPos.z > bbMax.z ||
          worldPos.x < bbMin.x || worldPos.y < bbMin.y || worldPos.z < bbMin.z)
          clip(-1);

       vec3 posOnBox = worldPos.xyz + nrdir * fa;
       reflectionVec = posOnBox - probeWSPos;

       ref = vec4(reflectionVec, smoothness);

        alpha = 1;
    }

    color = textureLod(cubeMap, vec3(ref.xyz), float(ref.w));

    vec4 specularColor = (color);
    vec4 indirectColor = (decodeSH(wsNormal));

    color.rgb = lerp(indirectColor.rgb * 1.5, specularColor.rgb * 1.5, matInfo.b);

    OUT_col = vec4(color.rgb, alpha);
}
