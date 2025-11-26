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


ImplementFeatureType(SNF_DefaultTexCoord,    U32(-1), -1, false);
ImplementFeatureType(SNF_TextureFeature,     U32(-1), -1, false);
ImplementFeatureType(SNF_NormalMapFeature,   U32(-1), -1, false);

ImplementEnumType(ShaderNodeFeature_enum, "Shader node features. Each of thes relates to a specific node for generating a shader.\n\n")
   { ShaderNodeFeature_enum::eSNF_DefaultTexCoord, "SNF_DefaultTexCoord", "Setup the default texcoord." },
   { ShaderNodeFeature_enum::eSNF_TextureFeature,  "SNF_TextureFeature", "Sample a Texture - Params: (string,string,GFXSamplerStateData,bool)." },
   { ShaderNodeFeature_enum::eSNF_NormalMapFeature,"SNF_NormalMapFeature", "Convert a texture to a normalmap - Params: (string,float,bool,bool)." },
EndImplementEnumType;

namespace
{
   void register_node_features(GFXAdapterType type)
   {
      FEATUREMGR->registerFeature(SNF_DefaultTexCoord,   new DefaultTexcoordFeature);
      FEATUREMGR->registerFeature(SNF_TextureFeature,    new TextureFeature,     TextureFeature::createFunction);
      FEATUREMGR->registerFeature(SNF_NormalMapFeature,  new NormalMapFeature,   NormalMapFeature::createFunction);

      REGISTER_FEATURE_PARAMS(SNF_TextureFeature, TextureFeatureParams);
      REGISTER_FEATURE_PARAMS(SNF_NormalMapFeature, NormalMapFeatureParams);
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
   String sampVarName = samplerName;
   String resultVarName = samplerName + "_col";

   
   Var* samplerVar = dynamic_cast<Var*>(LangElement::find(sampVarName));
   Var* textureVar;
  
   if (!isGL) // HLSL requires both Texture + SamplerState
   {
      if (!samplerVar)
      {
         samplerVar = new Var;
         samplerVar->setType(isComparison ? "SamplerComparisonState" : "SamplerState");
         samplerVar->setName(sampVarName);
         samplerVar->uniform = true;
         samplerVar->sampler = true;
         samplerVar->constNum = Var::getTexUnitNum();
      }

      textureVar = dynamic_cast<Var*>(LangElement::find(texVarName));
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
      if (!samplerVar)
      {
         samplerVar = new Var;
         samplerVar->setType(LangElement::samplerTypeToString(samplerType));
         samplerVar->setName(sampVarName);
         samplerVar->uniform = true;
         samplerVar->sampler = true;
         samplerVar->constNum = Var::getTexUnitNum();
      }
   }

   // The sampled color variable (e.g. "samplerName_col") should always be new but just in case
   Var* sampledColor = (Var*)LangElement::find(resultVarName);
   if (!sampledColor)
   {
      sampledColor->setType(GFXSCT_Float4);
      sampledColor->setName(resultVarName); // The result var will be named like the sampler
      meta->addStatement(new GenOp("   @", new DecOp(sampledColor)));
   }
   else
   {
      meta->addStatement(new GenOp("   @",sampledColor));
   }
   
   if (isGL)
   {
      // ---------------- GLSL Sampling ----------------
      if (isComparison)
      {
         if (useGather)
            meta->addStatement(new GenOp(
               " = textureGather(@, @, @);\r\n",
                samplerVar, texCoord, compareValue));
         else
            meta->addStatement(new GenOp(
               " = texture(@, @, @);\r\n",
               samplerVar, texCoord, compareValue));
      }
      else
      {
         if (useGather)
            meta->addStatement(new GenOp(
               " = textureGather(@, @);\r\n",
               samplerVar, texCoord));
         else
            meta->addStatement(new GenOp(
               " = texture(@, @);\r\n",
               samplerVar, texCoord));
      }
   }
   else
   {
      // ---------------- HLSL Sampling ----------------
      if (isComparison)
      {
         if (useGather)
            meta->addStatement(new GenOp(
               " = @.SampleCmpGather(@, @, @);\r\n",
               textureVar, samplerVar, texCoord, compareValue));
         else
            meta->addStatement(new GenOp(
               " = @.SampleCmp(@, @, @);\r\n",
               textureVar, samplerVar, texCoord, compareValue));
      }
      else
      {
         if (useGather)
            meta->addStatement(new GenOp(
               " = @.Gather(@, @);\r\n",
               textureVar, samplerVar, texCoord));
         else
            meta->addStatement(new GenOp(
               " = @.Sample(@, @);\r\n",
               textureVar, samplerVar, texCoord));
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
   Var* inTex = getInTexCoord(params->uvName, GFXSCT_Float2, componentList);
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

//--------------------------------------------------------
// NORMAL MAPPING FEATURE
//--------------------------------------------------------

void NormalMapFeature::processPix(Vector<ShaderComponent*>& componentList, const MaterialFeatureData& fd)
{
   String colorVarName = params->inputName;
   Var* sampledColor = (Var*)LangElement::find(colorVarName);

   if (!sampledColor)
   {
      Con::warnf("NormalMapFeature: sampler %s not sampled yet!", params->inputName.c_str());
      return; // TextureFeature must run first
   }


   MultiLine* meta = new MultiLine;

   // TEMP float3 for base decoded normal
   Var* tempNorm = new Var;
   tempNorm->setName(params->inputName + "_normTemp");
   tempNorm->setType(GFXSCT_Float4);
   LangElement* tempNormDecl = new DecOp(tempNorm);

   // sampledColor is the result of the textureFeature.
   meta->addStatement(expandNormalMap(sampledColor, tempNormDecl, tempNorm, fd));

   meta->addStatement(
      new GenOp("   @.xy *= float2(@, @);\r\n", tempNorm, params->flipX ? -1.0f : 1.0f, params->flipY ? -1.0f : 1.0f));

   meta->addStatement(new GenOp("   @.xyz = normalize( float3( @.xy * @, @.z ) );\r\n",
      tempNorm, tempNorm, params->strength, tempNorm));

   // write back into our known variable.
   meta->addStatement(new GenOp("   @ = @;\r\n", sampledColor, tempNorm));

   output = meta;

}
