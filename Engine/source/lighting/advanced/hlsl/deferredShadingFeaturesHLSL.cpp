//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#include "platform/platform.h"
#include "lighting/advanced/hlsl/deferredShadingFeaturesHLSL.h"

#include "lighting/advanced/advancedLightBinManager.h"
#include "shaderGen/langElement.h"
#include "shaderGen/shaderOp.h"
#include "shaderGen/conditionerFeature.h"
#include "renderInstance/renderDeferredMgr.h"
#include "materials/processedMaterial.h"
#include "materials/materialFeatureTypes.h"


//****************************************************************************
// Deferred Shading Features
//****************************************************************************
U32 DeferredOrmMapHLSL::getOutputTargets(const MaterialFeatureData& fd) const
{
   return fd.features[MFT_isDeferred] ? ShaderFeature::RenderTarget2 : ShaderFeature::DefaultTarget;
}

void DeferredOrmMapHLSL::processPix( Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd )
{
   // Get the texture coord.
   Var *texCoord = getInTexCoord( "texCoord", "float2", componentList );

   MultiLine* meta = new MultiLine;
   Var* ormConfig;
   if (fd.features[MFT_isDeferred])
   {
      ormConfig = (Var*)LangElement::find(getOutputTargetVarName(ShaderFeature::RenderTarget2));
      if (!ormConfig)
      {
         // create material var
         ormConfig = new Var;
         ormConfig->setType("fragout");
         ormConfig->setName(getOutputTargetVarName(ShaderFeature::RenderTarget2));
         ormConfig->setStructName("OUT");
      }
   }
   else
   {
      ormConfig = (Var*)LangElement::find("ORMConfig");
      if (!ormConfig)
      {
         ormConfig = new Var("ORMConfig", "float4");
         meta->addStatement(new GenOp("   @;\r\n", new DecOp(ormConfig)));
      }
   }

   // create texture var
   Var * ormMap = new Var;
   ormMap->setType( "SamplerState" );
   ormMap->setName( "ORMConfigMap" );
   ormMap->uniform = true;
   ormMap->sampler = true;
   ormMap->constNum = Var::getTexUnitNum();

   Var* ormMapTex = new Var;
   ormMapTex->setName("ORMConfigMapTex");
   ormMapTex->setType("Texture2D");
   ormMapTex->uniform = true;
   ormMapTex->texture = true;
   ormMapTex->constNum = ormMap->constNum;
   LangElement *texOp = new GenOp("@.Sample(@, @)", ormMapTex, ormMap, texCoord);
   
   Var *metalness = (Var*)LangElement::find("metalness");
   if (!metalness) metalness = new Var("metalness", "float");
   Var *roughness = (Var*)LangElement::find("roughness");
   if (!roughness) roughness = new Var("roughness", "float");
   Var* ao = (Var*)LangElement::find("ao");
   if (!ao) ao = new Var("ao", "float");


   meta->addStatement(new GenOp("   @.gba = @.rgb;\r\n", ormConfig, texOp));

   meta->addStatement(new GenOp("   @ = @.g;\r\n", new DecOp(ao), ormConfig));
   meta->addStatement(new GenOp("   @ = @.b;\r\n", new DecOp(roughness), ormConfig));
   if (fd.features[MFT_InvertRoughness])
   {
      meta->addStatement(new GenOp("   @.b = 1.0-@.b;\r\n", ormConfig, ormConfig));
      meta->addStatement(new GenOp("   @ = 1.0-@;\r\n", roughness, roughness));
   }
   meta->addStatement(new GenOp("   @ = @.a;\r\n", new DecOp(metalness), ormConfig));

   output = meta;
}

ShaderFeature::Resources DeferredOrmMapHLSL::getResources( const MaterialFeatureData &fd )
{
   Resources res; 
   res.numTex = 1;
   res.numTexReg = 1;

   return res;
}

void DeferredOrmMapHLSL::setTexData(   Material::StageData &stageDat,
                                       const MaterialFeatureData &fd,
                                       RenderPassData &passData,
                                       U32 &texIndex )
{
   GFXTextureObject *tex = stageDat.getTex(MFT_OrmMap);
   if ( tex )
   {
      passData.mTexType[ texIndex ] = Material::Standard;
      passData.mSamplerNames[ texIndex ] = "ORMConfigMap";
      passData.mTexSlot[ texIndex++ ].texObject = tex;
   }
}

void DeferredOrmMapHLSL::processVert( Vector<ShaderComponent*> &componentList,
                                       const MaterialFeatureData &fd )
{
   MultiLine *meta = new MultiLine;
   getOutTexCoord(   "texCoord", 
                     "float2", 
                     fd.features[MFT_TexAnim], 
                     meta, 
                     componentList );
   output = meta;
}

U32 MatInfoFlagsHLSL::getOutputTargets(const MaterialFeatureData& fd) const
{
   return fd.features[MFT_isDeferred] ? ShaderFeature::RenderTarget2 : ShaderFeature::DefaultTarget;
}

// Material Info Flags -> Red ( Flags ) of Material Info Buffer.
void MatInfoFlagsHLSL::processPix( Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd )
{
   // search for material var
   Var* ormConfig;
   if (fd.features[MFT_isDeferred])
   {
      ormConfig = (Var*)LangElement::find(getOutputTargetVarName(ShaderFeature::RenderTarget2));
      if (!ormConfig)
      {
         // create material var
         ormConfig = new Var;
         ormConfig->setType("fragout");
         ormConfig->setName(getOutputTargetVarName(ShaderFeature::RenderTarget2));
         ormConfig->setStructName("OUT");
      }
   }
   else
   {
      ormConfig = (Var*)LangElement::find("ORMConfig");
      if (!ormConfig) ormConfig = new Var("ORMConfig", "float4");
   }

   Var *matInfoFlags = new Var;
   matInfoFlags->setType( "float" );
   matInfoFlags->setName( "matInfoFlags" );
   matInfoFlags->uniform = true;
   matInfoFlags->constSortPos = cspPotentialPrimitive;

   output = new GenOp( "   @.r = @;\r\n", ormConfig, matInfoFlags );
}

U32 ORMConfigVarsHLSL::getOutputTargets(const MaterialFeatureData& fd) const
{
   return fd.features[MFT_isDeferred] ? ShaderFeature::RenderTarget2 : ShaderFeature::DefaultTarget;
}

void ORMConfigVarsHLSL::processPix( Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd )
{
   MultiLine* meta = new MultiLine;
   Var* ormConfig;
   if (fd.features[MFT_isDeferred])
   {
      ormConfig = (Var*)LangElement::find(getOutputTargetVarName(ShaderFeature::RenderTarget2));
      if (!ormConfig)
      {
         // create material var
         ormConfig = new Var;
         ormConfig->setType("fragout");
         ormConfig->setName(getOutputTargetVarName(ShaderFeature::RenderTarget2));
         ormConfig->setStructName("OUT");
      }
   }
   else
   {
      ormConfig = (Var*)LangElement::find("ORMConfig");
      if (!ormConfig) ormConfig = new Var("ORMConfig", "float4");
      meta->addStatement(new GenOp("   @;\r\n", new DecOp(ormConfig)));
   }
   Var *metalness = new Var("metalness", "float");
   metalness->uniform = true;
   metalness->constSortPos = cspPotentialPrimitive;

   Var *roughness = new Var("roughness", "float");
   roughness->uniform = true;
   roughness->constSortPos = cspPotentialPrimitive;

   //matinfo.g slot reserved for AO later
   meta->addStatement(new GenOp("   @.g = 1.0;\r\n", ormConfig));
   meta->addStatement(new GenOp("   @.b = @;\r\n", ormConfig, roughness));
   if (fd.features[MFT_InvertRoughness])
      meta->addStatement(new GenOp("   @ = 1.0-@;\r\n", roughness, roughness));
   meta->addStatement(new GenOp("   @.a = @;\r\n", ormConfig, metalness));
   output = meta;
}

U32 GlowMapHLSL::getOutputTargets(const MaterialFeatureData& fd) const
{
   return fd.features[MFT_isDeferred] ? ShaderFeature::RenderTarget3 : ShaderFeature::DefaultTarget;
}

//deferred emissive
void GlowMapHLSL::processPix(Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd)
{
   Var* texCoord = getInTexCoord("texCoord", "float2", componentList);

   // create texture var
   Var* glowMap = new Var;
   glowMap->setType("SamplerState");
   glowMap->setName("glowMap");
   glowMap->uniform = true;
   glowMap->sampler = true;
   glowMap->constNum = Var::getTexUnitNum();

   Var* glowMapTex = new Var;
   glowMapTex->setName("glowMapTex");
   glowMapTex->setType("Texture2D");
   glowMapTex->uniform = true;
   glowMapTex->texture = true;
   glowMapTex->constNum = glowMap->constNum;
   LangElement* texOp = new GenOp("@.Sample(@, @)", glowMapTex, glowMap, texCoord);

   Var* glowMul = new Var("glowMul", "float");
   glowMul->uniform = true;
   glowMul->constSortPos = cspPotentialPrimitive;

   Var *targ = (Var*)LangElement::find(getOutputTargetVarName(ShaderFeature::DefaultTarget));
   if (fd.features[MFT_isDeferred])
   {
      targ = (Var*)LangElement::find(getOutputTargetVarName(ShaderFeature::RenderTarget3));
      if (!targ)
      {
         // create scene color target var
         targ = new Var;
         targ->setType("fragout");
         targ->setName(getOutputTargetVarName(ShaderFeature::RenderTarget3));
         targ->setStructName("OUT");
         output = new GenOp("@ = float4(pow(max(@.rgb*@,0.0),3.54406804435),0);", targ, texOp, glowMul);
      }
      else
      {
         output = new GenOp("@ += float4(pow(max(@.rgb*@,0.0),3.54406804435),0);", targ, texOp, glowMul);
      }
   }
   else
   {
      output = new GenOp("@ += float4(pow(max(@.rgb*@,0.0),3.54406804435),@.a);", targ, texOp, glowMul, targ);
   }

}

ShaderFeature::Resources GlowMapHLSL::getResources(const MaterialFeatureData& fd)
{
   Resources res;
   res.numTex = 1;
   res.numTexReg = 1;

   return res;
}

void GlowMapHLSL::setTexData(Material::StageData& stageDat,
   const MaterialFeatureData& fd,
   RenderPassData& passData,
   U32& texIndex)
{
   GFXTextureObject* tex = stageDat.getTex(MFT_GlowMap);
   if (tex)
   {
      passData.mTexType[texIndex] = Material::Standard;
      passData.mSamplerNames[texIndex] = "glowMap";
      passData.mTexSlot[texIndex++].texObject = tex;
   }
}
