#include "shaderGen/HLSL/debugVizFeatureHLSL.h"
#include "shaderGen/shaderGen.h"
#include "shaderGen/langElement.h"
#include "shaderGen/shaderOp.h"
#include "shaderGen/shaderGenVars.h"
#include "gfx/gfxDevice.h"
#include "materials/matInstance.h"
#include "materials/processedMaterial.h"
#include "materials/materialFeatureTypes.h"
#include "core/util/autoPtr.h"

//****************************************************************************
// HDR Output
//****************************************************************************

DebugVizHLSL::DebugVizHLSL()
   : mTorqueDep(ShaderGen::smCommonShaderPath + String("/torque.hlsl"))
{
   addDependency(&mTorqueDep);
}

void DebugVizHLSL::processPix(Vector<ShaderComponent*>& componentList,
   const MaterialFeatureData& fd)
{
   MultiLine* meta = new MultiLine;
   Var* surface = (Var*)LangElement::find("surface");
   Var* color = (Var*)LangElement::find(getOutputTargetVarName(ShaderFeature::DefaultTarget));

   if (!surface)
      return;

   //0 == display both forward and deferred viz, 1 = display forward only viz, 2 = display deferred only viz
   S32 vizDisplayMode = Con::getIntVariable("$Viz_DisplayMode", 0);
   S32 surfaceVizMode = Con::getIntVariable("$Viz_SurfacePropertiesModeVar", -1);

   if (surfaceVizMode != -1 && vizDisplayMode == 0 || vizDisplayMode == 1)
   {
      if (color)
      {
         Var* specularColor = (Var*)LangElement::find("specularColor");

         switch (surfaceVizMode)
         {
         case 0:
            meta->addStatement(new GenOp("   @.rgb = @.baseColor.rgb;\r\n", color, surface));
            break;
         case 1:
            meta->addStatement(new GenOp("   @.rgb = @.N.rgb;\r\n", color, surface));
            break;
         case 2:
            meta->addStatement(new GenOp("   @.rgb = @.ao.rrr;\r\n", color, surface));
            break;
         case 3:
            meta->addStatement(new GenOp("   @.rgb = @.roughness.rrr;\r\n", color, surface));
            break;
         case 4:
            meta->addStatement(new GenOp("   @.rgb = @.metalness.rrr;\r\n", color, surface));
            break;
         case 5:
            meta->addStatement(new GenOp("   @.rgb = @.depth.rrr;\r\n", color, surface));
            break;
         case 6:
            meta->addStatement(new GenOp("   @.rgb = @.albedo.rgb;\r\n", color, surface));
            break;
         case 7:
            if (!specularColor)
            {
               specularColor = new Var("specularColor", "float3");
               specularColor->uniform = false;
            }

            meta->addStatement(new GenOp("   @ = @.baseColor.rgb * @.ao;\r\n", specularColor, surface, surface));
            meta->addStatement(new GenOp("   @.rgb = @.rgb;\r\n", color, specularColor));
            break;
         case 8:
            meta->addStatement(new GenOp("   @.rgb = @.matFlag.rrr;\r\n", color, surface));
            break;
         case 9:
            meta->addStatement(new GenOp("   @.rgb = @.P.xyz;\r\n", color, surface));
            break;
         case 10:
            meta->addStatement(new GenOp("   @.rgb = @.R.xyz;\r\n", color, surface));
            break;
         case 11:
            meta->addStatement(new GenOp("   @.rgb = @.F.rgb;\r\n", color, surface));
            break;
         case 12: //TODO
            /*Var * ssaoMaskTex = (Var*)LangElement::find("ssaoMaskTex");
            if (!ssaoMaskTex)
            {
               break;
            }

            meta->addStatement(new GenOp("   @.rgb = @.N;\r\n", color, surface));*/
            meta->addStatement(new GenOp("   @.rgb = float3(0,0,0);\r\n", color));
            break;
         case 13: //TODO
            meta->addStatement(new GenOp("   @.rgb = float3(0,0,0);\r\n", color));
            break;
         case 14: //TODO
            meta->addStatement(new GenOp("   @.rgb = float3(0,0,0);\r\n", color));
            break;
         };
      }

      output = meta;
      return;
   }

   //if not that, try the probe viz
   Var* ibl = (Var*)LangElement::find("ibl");
   if (ibl && color)
   {
      const char* showAtten = Con::getVariable("$Probes::showAttenuation", "0");
      const char* showContrib = Con::getVariable("$Probes::showProbeContrib", "0");
      const char* showSpec = Con::getVariable("$Probes::showSpecularCubemaps", "0");
      const char* showDiff = Con::getVariable("$Probes::showDiffuseCubemaps", "0");

      if (showAtten == "0" && showContrib == "0" && showSpec == "0" && showDiff == "0")
         return;

      if (fd.features[MFT_LightMap] || fd.features[MFT_ToneMap] || fd.features[MFT_VertLit])
         return;

      ShaderConnector* connectComp = dynamic_cast<ShaderConnector*>(componentList[C_CONNECTOR]);

      MultiLine* meta = new MultiLine;

      // Now the wsPosition and wsView.
      Var* worldToTangent = getInWorldToTangent(componentList);
      Var* wsNormal = getInWorldNormal(componentList);
      Var* wsPosition = getInWsPosition(componentList);
      Var* wsView = getWsView(wsPosition, meta);

      //Reflection Probe WIP
      U32 MAX_FORWARD_PROBES = 4;

      Var* numProbes = (Var*)LangElement::find("inNumProbes");
      Var* cubeMips = (Var*)LangElement::find("cubeMips");
      Var* skylightCubemapIdx = (Var*)LangElement::find("inSkylightCubemapIdx");
      Var* inProbePosArray = (Var*)LangElement::find("inProbePosArray");
      Var* inRefPosArray = (Var*)LangElement::find("inRefPosArray");
      Var* refScaleArray = (Var*)LangElement::find("inRefScale");

      Var* probeConfigData = (Var*)LangElement::find("inProbeConfigData");
      Var* worldToObjArray = (Var*)LangElement::find("inWorldToObjArray");

      Var* BRDFTexture = (Var*)LangElement::find("BRDFTexture");
      Var* BRDFTextureTex = (Var*)LangElement::find("texture_BRDFTexture");

      Var* specularCubemapAR = (Var*)LangElement::find("inSpecularCubemapAR");
      Var* specularCubemapARTex = (Var*)LangElement::find("texture_inSpecularCubemapAR");

      Var* irradianceCubemapAR = (Var*)LangElement::find("inIrradianceCubemapAR");
      Var* irradianceCubemapARTex = (Var*)LangElement::find("texture_inIrradianceCubemapAR");

      Var* matinfo = (Var*)LangElement::find("ORMConfig");
      Var* metalness = (Var*)LangElement::find("metalness");
      Var* roughness = (Var*)LangElement::find("roughness");

      Var* wsEyePos = (Var*)LangElement::find("eyePosWorld");

      Var* ibl = (Var*)LangElement::find("ibl");

      //Reflection vec
      Var* showAttenVar = new Var("showAttenVar", "int");
      char buf[64];
      dSprintf(buf, sizeof(buf), "   @ = %s;\r\n", showAtten);
      meta->addStatement(new GenOp(buf, new DecOp(showAttenVar)));

      Var* showContribVar = new Var("showContribVar", "int");
      dSprintf(buf, sizeof(buf), "   @ = %s;\r\n", showContrib);
      meta->addStatement(new GenOp(buf, new DecOp(showContribVar)));

      Var* showSpecVar = new Var("showSpecVar", "int");
      dSprintf(buf, sizeof(buf), "   @ = %s;\r\n", showSpec);
      meta->addStatement(new GenOp(buf, new DecOp(showSpecVar)));

      Var* showDiffVar = new Var("showDiffVar", "int");
      dSprintf(buf, sizeof(buf), "   @ = %s;\r\n", showDiff);
      meta->addStatement(new GenOp(buf, new DecOp(showDiffVar)));

      String computeForwardProbes = String("   @ = debugVizForwardProbes(@,@,@,@,@,@,@,@,\r\n\t\t");
      computeForwardProbes += String("@,TORQUE_SAMPLER2D_MAKEARG(@),\r\n\t\t");
      computeForwardProbes += String("TORQUE_SAMPLERCUBEARRAY_MAKEARG(@),TORQUE_SAMPLERCUBEARRAY_MAKEARG(@), @, @, @, @).rgb; \r\n");

      meta->addStatement(new GenOp(computeForwardProbes.c_str(), ibl, surface, cubeMips, numProbes, worldToObjArray, probeConfigData, inProbePosArray, refScaleArray, inRefPosArray,
         skylightCubemapIdx, BRDFTexture,
         irradianceCubemapAR, specularCubemapAR,
         showAttenVar, showContribVar, showSpecVar, showDiffVar));

      meta->addStatement(new GenOp("   @.rgb = @.rgb;\r\n", color, ibl));

      output = meta;
      return;
   }
}
