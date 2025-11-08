#include "platform/platform.h"
#include "shaderGen/shaderGen.h"

#include "shaderGen/NODE/shaderGenNodes.h"
#include "shaderGen/langElement.h"
#include "shaderGen/shaderOp.h"
#include "shaderGen/shaderGenVars.h"
#include "gfx/gfxDevice.h"
#include "materials/matInstance.h"
#include "materials/processedMaterial.h"
#include "materials/materialFeatureTypes.h"
#include "core/util/autoPtr.h"

#include "core/module.h"
#include "materials/materialFeatureTypes.h"


ImplementFeatureType(SNF_DefaultTexCoord, U32(-1), -1, false);
ImplementFeatureType(SNF_TextureFeature, U32(-1), -1, false);

ImplementEnumType(ShaderNodeFeature_enum, "Shader node features. Each of thes relates to a specific node for generating a shader.\n\n")
   { ShaderNodeFeature_enum::eSNF_DefaultTexCoord, "SNF_DefaultTexCoord", "Setup the default texcoord." },
   { ShaderNodeFeature_enum::eSNF_TextureFeature, "SNF_TextureFeature", "Sample a Texture - Params: (string,string,GFXSamplerStateData,bool)." },
EndImplementEnumType;

namespace
{
   void register_node_features(GFXAdapterType type)
   {
      FEATUREMGR->registerFeature(SNF_DefaultTexCoord,   new DefaultTexcoordFeature);
      FEATUREMGR->registerFeature(SNF_TextureFeature,    new TextureFeature, TextureFeature::createFunction);
   }

};

MODULE_BEGIN(ShaderGenNodes)

MODULE_INIT_AFTER(ShaderGen)
MODULE_INIT_AFTER(ShaderGenFeatureMgr)

MODULE_INIT
{
   SHADERGEN->getFeatureInitSignal().notify(&register_node_features);
}

MODULE_END;

void ShaderFeatureNode::setupTextureSample(  const String& samplerName,
                                             GFXShaderConstType samplerType,
                                             Vector<ShaderComponent*>& componentList,
                                             MultiLine* meta,
                                             LangElement* texCoord,
                                             LangElement* compareValue,
                                             bool useGather)
{
   const bool isGL = (GFX->getAdapterType() == OpenGL);
   const bool isComparison = (compareValue != NULL);

   // ---- Create or find texture/sampler vars ----
   String texVarName = samplerName + "_tex";
   String sampVarName = samplerName + "_sampler";

   Var* textureVar = dynamic_cast<Var*>(LangElement::find(texVarName));
   Var* samplerVar = dynamic_cast<Var*>(LangElement::find(sampVarName));

   if (!isGL)
   {
      // HLSL requires both Texture + SamplerState
      if (!samplerVar)
      {
         samplerVar = new Var;
         samplerVar->setType(isComparison ? "SamplerComparisonState" : "SamplerState");
         samplerVar->setName(sampVarName);
         samplerVar->uniform = true;
         samplerVar->sampler = true;
         samplerVar->constNum = Var::getTexUnitNum();
      }

      if (!textureVar)
      {
         textureVar = new Var;
         textureVar->setType(LangElement::samplerTypeToString(samplerType)); // Texture2D, TextureCube, etc.
         textureVar->setName(texVarName);
         textureVar->uniform = true;
         textureVar->texture = true;
         textureVar->constNum = samplerVar->constNum;
      }
   }
   else
   {
      // GLSL uses a single sampler uniform
      if (!textureVar)
      {
         textureVar = new Var;
         textureVar->setType(LangElement::samplerTypeToString(samplerType));
         textureVar->setName(texVarName);
         textureVar->uniform = true;
         textureVar->sampler = true;
         textureVar->constNum = Var::getTexUnitNum();
      }
   }

   // ---- Emit sampling code ----
   String sampleFunc;
   if (isComparison)
   {
      if (useGather)
         sampleFunc = isGL ? "textureGather" : "SampleCmpGather";
      else
         sampleFunc = isGL ? "texture" : "SampleCmp";
   }
   else
   {
      sampleFunc = isGL ? "texture" : "Sample";
   }

   // The sampled color variable (e.g. "diffuseColor")
   Var* sampledColor = new Var;
   sampledColor->setType("float4");
   sampledColor->setName(samplerName); // The result var will be named like the sampler

   if (isGL)
   {
      if (isComparison)
      {
         meta->addStatement(new GenOp("   @ = %s(@, @, @);\r\n",
            sampledColor, sampleFunc.c_str(), textureVar, texCoord, compareValue));
      }
      else
      {
         meta->addStatement(new GenOp("   @ = %s(@, @);\r\n",
            sampledColor, sampleFunc.c_str(), textureVar, texCoord));
      }
   }
   else
   {
      if (isComparison)
      {
         if (useGather)
            meta->addStatement(new GenOp("   @ = @.%s(@, @, @);\r\n",
               sampledColor, textureVar, sampleFunc.c_str(), samplerVar, texCoord, compareValue));
         else
            meta->addStatement(new GenOp("   @ = @.%s(@, @, @);\r\n",
               sampledColor, textureVar, sampleFunc.c_str(), samplerVar, texCoord, compareValue));
      }
      else
      {
         meta->addStatement(new GenOp("   @ = @.%s(@, @);\r\n",
            sampledColor, textureVar, sampleFunc.c_str(), samplerVar, texCoord));
      }
   }
}

Var* ShaderFeatureNode::getOutTexCoord(const char* name, GFXShaderConstType type, bool useTexAnim, MultiLine* meta, Vector<ShaderComponent*>& componentList)
{
   String outTexName = String::ToString("out_%s", name);
   Var* texCoord = (Var*)LangElement::find(outTexName);
   if (!texCoord)
   {
      Var* inTex = getVertTexCoord(name);
      AssertFatal(inTex, "ShaderFeatureNode::getOutTexCoord - Unknown vertex input coord!");

      ShaderConnector* connectComp = dynamic_cast<ShaderConnector*>(componentList[C_CONNECTOR]);

      texCoord = connectComp->getElement(RT_TEXCOORD);
      texCoord->setName(outTexName);
      texCoord->setStructName("OUT");
      texCoord->setType(type);

      // Statement allows for casting of different types which
      // eliminates vector truncation problems.
      String statement = String::ToString("   @ = (%s)@;\r\n", type);
      meta->addStatement(new GenOp(statement, texCoord, inTex));

   }

   return texCoord;
}

LangElement* ShaderFeatureNode::setupTexSpaceMat(Vector<ShaderComponent*>& componentList, Var** texSpaceMat)
{
   return nullptr;
}

LangElement* ShaderFeatureNode::assignColor(LangElement* elem, Material::BlendOp blend, LangElement* lerpElem, ShaderFeature::OutputTarget outputTarget)
{
   // search for color var
   Var* color = (Var*)LangElement::find(getOutputTargetVarName(outputTarget));

   if (!color)
   {
      // create color var
      color = new Var;
      color->setType("fragout");
      color->setName(getOutputTargetVarName(outputTarget));
      color->setStructName("OUT");

      return new GenOp("@ = @", color, elem);
   }

   switch (blend)
   {
   case Material::Add:
      return new GenOp("@ += @", color, elem);
      break;

   case Material::Sub:
      return new GenOp("@ -= @", color, elem);
      break;

   case Material::Mul:
      return new GenOp("@ *= @", color, elem);
      break;

   case Material::PreMul:
      return new GenOp("@.rgb = @.rgb + (@.rgb*(1.0-@.a))", color, elem, color, elem);
      break;

   case Material::AddAlpha:
      return new GenOp("@ += @ * @.a", color, elem, elem);
      break;

   case Material::LerpAlpha:
      if (!lerpElem)
         lerpElem = elem;
      return new GenOp("@.rgb = lerp( @.rgb, (@).rgb, (@).a )", color, color, elem, lerpElem);
      break;

   case Material::ToneMap:
      return new GenOp("@ = 1.0 - exp(-1.0 * @ * @)", color, color, elem);
      break;

   case Material::None:
      return new GenOp("@ = @", color, elem);
      break;

   default:
      AssertFatal(false, "Unrecognized color blendOp");
      // Fallthru   
   }

   return NULL;
}

//--------------------------------------------------------
// Setup the default texcoord
//--------------------------------------------------------

void DefaultTexcoordFeature::processVert(Vector<ShaderComponent*>& componentList, const MaterialFeatureData& fd)
{
   MultiLine* meta = new MultiLine;
   getOutTexCoord("texCoord",
      GFXSCT_Float2,
      fd.features[MFT_TexAnim],
      meta,
      componentList);
   output = meta;
}

void DefaultTexcoordFeature::processPix(Vector<ShaderComponent*>& componentList, const MaterialFeatureData& fd)
{
   // grab connector texcoord register
   Var* inTex = getInTexCoord("texCoord", GFXSCT_Float2, componentList);
   if (!inTex)
      return;
}

//--------------------------------------------------------
// TEXTURE SAMPLER FEATURE
//--------------------------------------------------------

void TextureFeature::processPix(Vector<ShaderComponent*>& componentList, const MaterialFeatureData& fd)
{
   // find the uv var.
   Var* inTex = (Var*)LangElement::find(params->uvName);
   if (!inTex)
      return;

   MultiLine* meta = new MultiLine;

   // Sample texture
   setupTextureSample(
      params->samplerName,   // name of the output variable.
      params->samplerType,   // or GFXSCT_SamplerCube, etc.
      componentList,
      meta,
      inTex,
      NULL,                  // compareValue (for SampleCmp)
      params->useGather      // enable gather if desired
   );

   output = meta;
}

ShaderFeature::Resources TextureFeature::getResources(const MaterialFeatureData& fd)
{
   Resources res;
   res.numTex = 1;
   res.numTexReg = 1;

   return res;
}
