#include "../../../gl/hlslCompat.glsl"
#include "../../../postFX/gl/postFx.glsl"
#include "../../../gl/torque.glsl"
#include "shadergen:/autogenConditioners.h"
#include "../../../gl/lighting.glsl"
#include "../../../gl/brdf.glsl"

#line 7

uniform sampler2D deferredBuffer;
uniform sampler2D colorBuffer;
uniform sampler2D matInfoBuffer;
uniform sampler2D BRDFTexture;

uniform vec3 ambientColor;
uniform vec4 rtParams0;
uniform vec4 vsFarPlane;
uniform mat4 cameraToWorld;

//cubemap arrays require all the same size. so shared mips# value
uniform float cubeMips;

uniform int numProbes;

uniform samplerCubeArray specularCubemapAR;
uniform samplerCubeArray irradianceCubemapAR;
uniform sampler2D WetnessTexture;
#ifdef USE_SSAO_MASK
uniform sampler2D ssaoMask;
uniform vec4 rtParams7;
#endif
//The interior amount (0-1) is how much of an Interior probe a pixel is in. It drives the skylight suppression, the
//ambient blend and the sun darkening, which goes in the light buffer's alpha (the sun is scaled by 1 - alpha)
#ifndef INTERIOR_SUN_ALPHA
#define INTERIOR_SUN_ALPHA 0
#endif
#if INTERIOR_SUN_ALPHA == 1
uniform float interiorSunResidual;
uniform vec4 interiorSunFade; //x = eye distance where the sun darkening starts, y = 1 / the length it fades in over
uniform vec4 zNearFar;
#endif
uniform float accumTime;
uniform float dampness;

uniform vec4    probePosArray[MAX_PROBES];
uniform vec4    refPosArray[MAX_PROBES];
uniform mat4    worldToObjArray[MAX_PROBES];
uniform vec4    refScaleArray[MAX_PROBES];
uniform vec4    probeConfigData[MAX_PROBES];   //r,g,b/mode,radius,atten

uniform int numLowLodProbes;

uniform int skylightCubemapIdx;
uniform int SkylightDamp;

uniform sampler2D probeAtlas;

//x = its row in probeAtlas, y = distance fade (0-1)
uniform vec4    probeLowLodList[MAX_LOWLOD_PROBES];
uniform vec4    probeAtlasRow[MAX_PROBES];

out vec4 OUT_col;

void main()
{
   //unpack normal and linear depth 
   vec4 normDepth = deferredUncondition(deferredBuffer, IN_uv0.xy);

   //create surface
   Surface surface = createSurface(normDepth, colorBuffer, matInfoBuffer, IN_uv0.xy, eyePosWorld, IN_wsEyeRay, cameraToWorld);
   if (getFlag(surface.matFlag, 2))
   { 
      OUT_col = vec4(0,0,0,0);
      return;
   } 
   #ifdef USE_SSAO_MASK
      float ssao =  1.0 - texture( ssaoMask, viewportCoordToRenderTarget( IN_uv0.xy, rtParams7 ) ).r;
      surface.ao = min(surface.ao, ssao);  
   #endif


   //How much of an interior this pixel is in (0-1), worked out from the Interior probes below
   float interiorAmt = 0.0;

   float alpha = 1;
   float wetAmmout = 0;

#if SKYLIGHT_ONLY == 0
   int i = 0;
   int totalProbes = numProbes + numLowLodProbes;
   float blendFactor[TOTAL_PROBES];
   float blendSum = 0;
   float blendFacSum = 0;
   float invBlendSum = 0;
   float probehits = 0;
   //Set up our struct data
   float contribution[TOTAL_PROBES];

   float blendCap = 0;
   if (alpha > 0)
   {
      //Process prooooobes
      for (i = 0; i < totalProbes; i++)
      {
         contribution[i] = 0;

         float atten = 0.0;
         float influence = 0.0;
         int probeFlags = 0;

         if (i >= numProbes)
         {
            //Early out on the bounds if we can so we can skip texture samples we don't need to do
            vec4 lowEntry = probeLowLodList[i - numProbes];
            int lowRow = int(lowEntry.x);
            atten = lowEntry.y;

            if (probeInfoContains(probeAtlas, lowRow, surface.P))
            {
               ProbeInfo lowProbe = loadProbeInfoVolume(probeAtlas, lowRow);
               influence = defineProbeInfoInfluence(surface.P, lowProbe);

               if (influence * atten > 0.0)
               {
                  loadProbeInfoColor(probeAtlas, lowRow, lowProbe);
                  probeFlags = lowProbe.flags;
               }
            }
         }
         else
         {
            if (probePosArray[i].w < 0.0)
               atten = 1.0-(length(eyePosWorld-probePosArray[i].xyz)/maxProbeDrawDistance); //no atlas row to hand over to, so do a plain falloff
            else
               atten = probePosArray[i].w;
            if (probeConfigData[i].r == 0) //box
            {
               influence = defineBoxSpaceInfluence(surface.P, worldToObjArray[i], probeConfigData[i].b);
            }
            else if (probeConfigData[i].r == 1) //sphere
            {
               influence = defineSphereSpaceInfluence(surface.P, probePosArray[i].xyz, probeConfigData[i].g, probeConfigData[i].b);
            }

            //refScaleArray.w has the packed bits. bit 0 = wetness, bit 1 = Interior probe
            probeFlags = int(refScaleArray[i].w + 0.5);
         }
         contribution[i] = influence*atten;
         if ((probeFlags & 2) != 0)
            interiorAmt = max(interiorAmt, influence);

         if (contribution[i]>0.0)
            probehits++;
         else
            contribution[i] = 0;

         if ((probeFlags & 1) != 0)
            wetAmmout += contribution[i];
         else
            wetAmmout -= contribution[i];

         blendSum += contribution[i];
         blendCap = max(contribution[i],blendCap);
      }
      if (wetAmmout<0) wetAmmout =0;
      
       if (probehits > 0.0)
	   {
         invBlendSum = (probehits - blendSum)/probehits; //grab the remainder
         //Give a bit of room so we can't div/0
         invBlendSum = max(invBlendSum, 0.001);
         for (i = 0; i < totalProbes; i++)
         {
               blendFactor[i] = contribution[i]/blendSum; //what % total is this instance
               blendFactor[i] *= blendFactor[i]/invBlendSum;  //what should we add to sum to 1
               blendFacSum += blendFactor[i]; //running tally of results
         }

         float probeShare = lerp(blendCap, 1.0, interiorAmt);
         for (i = 0; i < totalProbes; i++)
         {
            //normalize, but in the range of the highest value applied
            //to preserve blend vs skylight
            contribution[i] = blendFactor[i]/blendFacSum*probeShare;
         }
      }
      #if DEBUGVIZ_ATTENUATION == 1
      float contribAlpha = 0;
      for (i = 0; i < totalProbes; i++)
      {
         contribAlpha += contribution[i];
      }

      OUT_col = vec4(contribAlpha,contribAlpha,contribAlpha, 1);
      return;
#endif

#if DEBUGVIZ_LOD == 1
      //Red = high LOD, green = high LOD blended into it's ambient, blue = low LOD/ambient color
      vec3 lodVizColor = vec3(0, 0, 0);
      for (i = 0; i < totalProbes; i++)
      {
         vec3 lodColor = vec3(1, 0, 0);
         if (i < numProbes)
            lodColor = lerp(vec3(0, 1, 0), vec3(1, 0, 0), (probePosArray[i].w < 0.0) ? 1.0 : refPosArray[i].w);
         else
            lodColor = vec3(0, 0, 1); //the atlas tier is always the flat ambient color

         lodVizColor += contribution[i] * lodColor;
      }
      OUT_col = vec4(lodVizColor, 1);
      return;
#endif

#if DEBUGVIZ_CONTRIB == 1
      vec3 finalContribColor = vec3(0, 0, 0);
      for (i = 0; i < totalProbes; i++)
      {
         finalContribColor += contribution[i] * (0.5 + 0.5 * sin(vec3(0.0, 2.0944, 4.1888) + float(i + 1) * 2.39996));
      }
      OUT_col = vec4(finalContribColor, 1);
      return;
#endif
   }
   for (i = 0; i < totalProbes; i++)
   {
      float contrib = contribution[i];
      if (contrib > 0.0f)
      {
         alpha -= contrib;
      }
   }

#endif

   vec3 irradiance = vec3(0, 0, 0);
   vec3 specular = vec3(0, 0, 0);

   if (SkylightDamp>0)
      wetAmmout += alpha;
   dampen(surface, WetnessTexture, accumTime, wetAmmout*dampness);
   
   // Radiance (Specular)
#if DEBUGVIZ_SPECCUBEMAP == 0
   float lod = roughnessToMipLevel(surface.roughness, cubeMips);
#elif DEBUGVIZ_SPECCUBEMAP == 1
   float lod = 0;
#endif

#if SKYLIGHT_ONLY == 0
   for (i = 0; i < totalProbes; i++)
   {
      float contrib = contribution[i];
      if (contrib > 0.0f)
      {
         if (i < numProbes)
         {
            //High LOD: full cubemaps
            int cubemapIdx = int(probeConfigData[i].a);
            vec3 dir = boxProject(surface.P-refPosArray[i].xyz, surface.R, worldToObjArray[i], refScaleArray[i].xyz, probePosArray[i].xyz);

            vec3 probeIrradiance = textureLod(irradianceCubemapAR, vec4(dir, cubemapIdx), 0).xyz;
            vec3 probeSpecular = textureLod(specularCubemapAR, vec4(dir, cubemapIdx), lod).xyz;

            //Ease to this probe's low LOD ambient color at-distance
            if (probePosArray[i].w >= 0.0 && refPosArray[i].w < 1.0)
            {
               float cubemapShare = refPosArray[i].w;
               int atlasRow = int(probeAtlasRow[i].x);
               if (atlasRow >= 0)
               {
                  ProbeInfo highProbe;
                  highProbe.flags = 0;
                  loadProbeInfoColor(probeAtlas, atlasRow, highProbe);
                  probeIrradiance = lerp(toGamma(highProbe.ambientCol), probeIrradiance, cubemapShare);
                  probeSpecular = lerp(highProbe.ambientCol, probeSpecular, cubemapShare);
               }
            }

            irradiance += probeIrradiance * contrib;
            specular += probeSpecular * contrib;
         }
         else
         {
            //Low LOD. Take the baked ambient color for both irrad and specular
            ProbeInfo lowProbe;
            lowProbe.flags = 0;
            loadProbeInfoColor(probeAtlas, int(probeLowLodList[i - numProbes].x), lowProbe);

            irradiance += toGamma(lowProbe.ambientCol) * contrib;
            specular += lowProbe.ambientCol * contrib;
         }
      }
   }
#endif
      
   if (skylightCubemapIdx != -1 && alpha >= 0.001)
   {
      irradiance = lerp(irradiance,textureLod(irradianceCubemapAR, vec4(surface.R, skylightCubemapIdx), 0).xyz,alpha);
      specular = lerp(specular,textureLod(specularCubemapAR, vec4(surface.R, skylightCubemapIdx), lod).xyz,alpha);
   }
   
#if DEBUGVIZ_SPECCUBEMAP == 1 && DEBUGVIZ_DIFFCUBEMAP == 0
   OUT_col = vec4(specular, 1);
   return;
#elif DEBUGVIZ_DIFFCUBEMAP == 1
   OUT_col = vec4(irradiance, 1);
   return;
#endif

   vec2 envBRDF = textureLod(BRDFTexture, vec2(surface.NdotV, surface.roughness),0).rg;
   vec3 diffuse = irradiance * lerp(surface.baseColor.rgb, vec3(0.04f,0.04f,0.04f), surface.metalness);
   vec3 specularCol = (specular * surface.f0 * envBRDF.x + envBRDF.y)*surface.metalness;
   
   float horizonOcclusion = 1.3;
   float horizon = saturate( 1 + horizonOcclusion * dot(surface.R, surface.N));
   horizon *= horizon;
   
   // Final color output after environment lighting
   vec3 finalColor = diffuse + specularCol * horizon;
   finalColor *= surface.ao;
   
   if(isCapturing == 1)
      OUT_col = vec4(lerp((finalColor), surface.baseColor.rgb,surface.metalness),0);
   else
   {
      vec3 ambientScale = mix(ambientColor, vec3(1.0, 1.0, 1.0), interiorAmt);

      //How much of the sun to reduce, written to alpha. 
      float sunDarken = 0.0;
#if INTERIOR_SUN_ALPHA == 1 && SKYLIGHT_ONLY == 0
      if (getFlag(surface.matFlag, 0) && surface.depth < 0.9999)
      {
         float zDist = zNearFar.x + zNearFar.y * surface.depth;
         float gate = saturate((zDist - interiorSunFade.x) * interiorSunFade.y);
         sunDarken = saturate(interiorAmt) * gate * (1.0 - interiorSunResidual);
      }
#endif
      OUT_col = vec4(finalColor*ambientScale, sunDarken);
   }
}
