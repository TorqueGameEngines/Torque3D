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
#include "lighting/advanced/glsl/deferredShadingFeaturesGLSL.h"

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
U32 PBRConfigMapGLSL::getOutputTargets(const MaterialFeatureData& fd) const
{
   return fd.features[MFT_isDeferred] ? ShaderFeature::RenderTarget2 : ShaderFeature::DefaultTarget;
}

void PBRConfigMapGLSL::processPix( Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd )
{
   // Get the texture coord.
   Var *texCoord = getInTexCoord( "texCoord", "vec2", componentList );
   
   MultiLine* meta = new MultiLine;
   Var* pbrConfig;
   if (fd.features[MFT_isDeferred])
   {
      pbrConfig = (Var*)LangElement::find(getOutputTargetVarName(ShaderFeature::RenderTarget2));
      if (!pbrConfig)
      {
         // create material var
         pbrConfig = new Var;
         pbrConfig->setType("vec4");
         pbrConfig->setName(getOutputTargetVarName(ShaderFeature::RenderTarget2));
         pbrConfig->setStructName("OUT");
      }
   }
   else
   {
      pbrConfig = (Var*)LangElement::find("PBRConfig");
      if (!pbrConfig)
      {
         pbrConfig = new Var("PBRConfig", "vec4");
         meta->addStatement(new GenOp("   @;\r\n", new DecOp(pbrConfig)));
      }
   }

   // create texture var
   Var *pbrConfigMap = new Var;
   pbrConfigMap->setType( "sampler2D" );
   pbrConfigMap->setName( "pbrConfigMap" );
   pbrConfigMap->uniform = true;
   pbrConfigMap->sampler = true;
   pbrConfigMap->constNum = Var::getTexUnitNum();
   LangElement *texOp = new GenOp( "tex2D(@, @)", pbrConfigMap, texCoord );

   Var *metalness = (Var*)LangElement::find("metalness");
   if (!metalness) metalness = new Var("metalness", "float");
   Var *smoothness = (Var*)LangElement::find("smoothness");
   if (!smoothness) smoothness = new Var("smoothness", "float");
   Var* ao = (Var*)LangElement::find("ao");
   if (!ao) ao = new Var("ao", "float");


   meta->addStatement(new GenOp("   @.bga = @.rgb;\r\n", pbrConfig, texOp));

   meta->addStatement(new GenOp("   @ = @.b;\r\n", new DecOp(smoothness), pbrConfig));
   if (fd.features[MFT_InvertSmoothness])
   {
      meta->addStatement(new GenOp("   @.b = 1.0-@.b;\r\n", pbrConfig, pbrConfig));
      meta->addStatement(new GenOp("   @ = 1.0-@;\r\n", smoothness, smoothness));
   }
   meta->addStatement(new GenOp("   @ = @.g;\r\n", new DecOp(ao), pbrConfig));
   meta->addStatement(new GenOp("   @ = @.a;\r\n", new DecOp(metalness), pbrConfig));

   output = meta;
}

ShaderFeature::Resources PBRConfigMapGLSL::getResources( const MaterialFeatureData &fd )
{
   Resources res; 
   res.numTex = 1;
   res.numTexReg = 1;

   return res;
}

void PBRConfigMapGLSL::setTexData(   Material::StageData &stageDat,
                                       const MaterialFeatureData &fd,
                                       RenderPassData &passData,
                                       U32 &texIndex )
{
   GFXTextureObject *tex = stageDat.getTex(MFT_PBRConfigMap);
   if ( tex )
   {
      passData.mTexType[ texIndex ] = Material::Standard;
      passData.mSamplerNames[ texIndex ] = "pbrConfigMap";
      passData.mTexSlot[ texIndex++ ].texObject = tex;
   }
}

void PBRConfigMapGLSL::processVert( Vector<ShaderComponent*> &componentList,
                                       const MaterialFeatureData &fd )
{
   MultiLine *meta = new MultiLine;
   getOutTexCoord(   "texCoord", 
                     "vec2", 
                     fd.features[MFT_TexAnim], 
                     meta, 
                     componentList );
   output = meta;
}

U32 MatInfoFlagsGLSL::getOutputTargets(const MaterialFeatureData& fd) const
{
   return fd.features[MFT_isDeferred] ? ShaderFeature::RenderTarget2 : ShaderFeature::DefaultTarget;
}

// Material Info Flags -> Red ( Flags ) of Material Info Buffer.
void MatInfoFlagsGLSL::processPix( Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd )
{
	MultiLine *meta = new MultiLine;

   Var* pbrConfig;
   if (fd.features[MFT_isDeferred])
   {
      pbrConfig = (Var*)LangElement::find(getOutputTargetVarName(ShaderFeature::RenderTarget2));
      if (!pbrConfig)
      {
         // create material var
         pbrConfig = new Var;
         pbrConfig->setType("vec4");
         pbrConfig->setName(getOutputTargetVarName(ShaderFeature::RenderTarget2));
         pbrConfig->setStructName("OUT");
      }
   }
   else
   {
      pbrConfig = (Var*)LangElement::find("PBRConfig");
      if (!pbrConfig)
      {
         pbrConfig = new Var("PBRConfig", "vec4");
         meta->addStatement(new GenOp("   @;\r\n", new DecOp(pbrConfig)));
      }
   }

   Var *matInfoFlags = new Var;
   matInfoFlags->setType( "float" );
   matInfoFlags->setName( "matInfoFlags" );
   matInfoFlags->uniform = true;
   matInfoFlags->constSortPos = cspPotentialPrimitive;

   meta->addStatement(output = new GenOp("   @.r = @;\r\n", pbrConfig, matInfoFlags));
   output = meta;
}

U32 PBRConfigVarsGLSL::getOutputTargets(const MaterialFeatureData& fd) const
{
   return fd.features[MFT_isDeferred] ? ShaderFeature::RenderTarget2 : ShaderFeature::DefaultTarget;
}

// Spec Strength -> Blue Channel of Material Info Buffer.
// Spec Power -> Alpha Channel ( of Material Info Buffer.
void PBRConfigVarsGLSL::processPix( Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd )
{
   MultiLine* meta = new MultiLine;

   Var* pbrConfig;
   if (fd.features[MFT_isDeferred])
   {
      pbrConfig = (Var*)LangElement::find(getOutputTargetVarName(ShaderFeature::RenderTarget2));
      if (!pbrConfig)
      {
         // create material var
         pbrConfig = new Var;
         pbrConfig->setType("vec4");
         pbrConfig->setName(getOutputTargetVarName(ShaderFeature::RenderTarget2));
         pbrConfig->setStructName("OUT");
      }
   }
   else
   {
      pbrConfig = (Var*)LangElement::find("PBRConfig");
      if (!pbrConfig)
      {
         pbrConfig = new Var("PBRConfig", "vec4");
         meta->addStatement(new GenOp("   @;\r\n", new DecOp(pbrConfig)));
      }
   }
   Var* metalness = new Var("metalness", "float");
   metalness->uniform = true;
   metalness->constSortPos = cspPotentialPrimitive;

   Var* smoothness = new Var("smoothness", "float");
   smoothness->uniform = true;
   smoothness->constSortPos = cspPotentialPrimitive;

   //matinfo.g slot reserved for AO later
   meta->addStatement(new GenOp("   @.g = 1.0;\r\n", pbrConfig));
   meta->addStatement(new GenOp("   @.b = @;\r\n", pbrConfig, smoothness));
   if (fd.features[MFT_InvertSmoothness])
      meta->addStatement(new GenOp("   @ = 1.0-@;\r\n", smoothness, smoothness));
   meta->addStatement(new GenOp("   @.a = @;\r\n", pbrConfig, metalness));
   output = meta;
}

U32 GlowMapGLSL::getOutputTargets(const MaterialFeatureData& fd) const
{
   return fd.features[MFT_isDeferred] ? ShaderFeature::RenderTarget3 : ShaderFeature::DefaultTarget;
}

//deferred emissive
void GlowMapGLSL::processPix(Vector<ShaderComponent*>& componentList, const MaterialFeatureData& fd)
{
   Var* texCoord = getInTexCoord("texCoord", "vec2", componentList);

   Var* glowMap = new Var;
   glowMap->setType("sampler2D");
   glowMap->setName("glowMap");
   glowMap->uniform = true;
   glowMap->sampler = true;
   glowMap->constNum = Var::getTexUnitNum();
   LangElement* texOp = new GenOp("tex2D(@, @)", glowMap, texCoord);
   
   Var* glowMul = new Var("glowMul", "float");
   glowMul->uniform = true;
   glowMul->constSortPos = cspPotentialPrimitive;

   Var* targ = (Var*)LangElement::find(getOutputTargetVarName(ShaderFeature::DefaultTarget));
   if (fd.features[MFT_isDeferred])
   {
      targ = (Var*)LangElement::find(getOutputTargetVarName(ShaderFeature::RenderTarget3));
      if (!targ)
      {
         // create scene color target var
         targ = new Var;
         targ->setType("vec4");
         targ->setName(getOutputTargetVarName(ShaderFeature::RenderTarget3));
         targ->setStructName("OUT");
         output = new GenOp("@ = vec4(@.rgb*@,0);", targ, texOp, glowMul);
      }
      else
      {
         output = new GenOp("@ += vec4(@.rgb*@,0);", targ, texOp, glowMul);
      }
   }
   else
   {
      output = new GenOp("@ += vec4(@.rgb*@,@.a);", targ, texOp, glowMul, targ);
   }

}

ShaderFeature::Resources GlowMapGLSL::getResources(const MaterialFeatureData& fd)
{
   Resources res;
   res.numTex = 1;
   res.numTexReg = 1;

   return res;
}

void GlowMapGLSL::setTexData(Material::StageData& stageDat,
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
