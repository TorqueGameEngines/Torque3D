#include "shaderGen/GLSL/debugVizFeatureGLSL.h"
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

DebugVizGLSL::DebugVizGLSL()
   : mTorqueDep(ShaderGen::smCommonShaderPath + String("/gl/torque.glsl"))
{
   addDependency(&mTorqueDep);
}

void DebugVizGLSL::processPix(Vector<ShaderComponent*>& componentList,
   const MaterialFeatureData& fd)
{
   MultiLine* meta = new MultiLine;
   Var* surface = (Var*)LangElement::find("surface");

   //0 == display both forward and deferred viz, 1 = display forward only viz, 2 = display deferred only viz
   S32 vizDisplayMode = Con::getIntVariable("$Viz_DisplayMode", 0);

   if (surface && (vizDisplayMode == 0 || vizDisplayMode == 1))
   {
      Var* color = (Var*)LangElement::find("col");
      if (color)
      {
         Var* specularColor = (Var*)LangElement::find("specularColor");

         S32 surfaceVizMode = Con::getIntVariable("$Viz_SurfacePropertiesModeVar", -1);

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
            meta->addStatement(new GenOp("   @.rgb = vec3(0,0,0);\r\n", color));
            break;
         case 13: //TODO
            meta->addStatement(new GenOp("   @.rgb = vec3(0,0,0);\r\n", color));
            break;
         case 14: //TODO
            meta->addStatement(new GenOp("   @.rgb = vec3(0,0,0);\r\n", color));
            break;
         };
      }
   }

   output = meta;
}
