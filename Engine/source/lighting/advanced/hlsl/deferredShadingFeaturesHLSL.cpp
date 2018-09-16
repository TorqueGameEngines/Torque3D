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

// Specular Map -> Blue of Material Buffer ( greyscaled )
// Gloss Map (Alpha Channel of Specular Map) -> Alpha ( Spec Power ) of Material Info Buffer.
void DeferredSpecMapHLSL::processPix( Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd )
{
   // Get the texture coord.
   Var *texCoord = getInTexCoord( "texCoord", "float2", componentList );

   // search for color var
   Var *material = (Var*) LangElement::find( getOutputTargetVarName(ShaderFeature::RenderTarget2) );
   MultiLine * meta = new MultiLine;
   if ( !material )
   {
      // create color var
      material = new Var;
      material->setType( "fragout" );
      material->setName( getOutputTargetVarName(ShaderFeature::RenderTarget2) );
      material->setStructName( "OUT" );
   }

   // create texture var
   Var *specularMap = new Var;
   specularMap->setType( "SamplerState" );
   specularMap->setName( "specularMap" );
   specularMap->uniform = true;
   specularMap->sampler = true;
   specularMap->constNum = Var::getTexUnitNum();

   Var* specularMapTex = new Var;
   specularMapTex->setName("specularMapTex");
   specularMapTex->setType("Texture2D");
   specularMapTex->uniform = true;
   specularMapTex->texture = true;
   specularMapTex->constNum = specularMap->constNum;
   LangElement *texOp = new GenOp("   @.Sample(@, @)", specularMapTex, specularMap, texCoord);
   
   Var *specularColor = (Var*)LangElement::find("specularColor");
   if (!specularColor) specularColor = new Var("specularColor", "float4");
   Var *metalness = (Var*)LangElement::find("metalness");
   if (!metalness) metalness = new Var("metalness", "float");
   Var *smoothness = (Var*)LangElement::find("smoothness");
   if (!smoothness) smoothness = new Var("smoothness", "float");

   meta->addStatement(new GenOp("   @ = @.r;\r\n", new DecOp(smoothness), texOp));
   meta->addStatement(new GenOp("   @ = @.b;\r\n", new DecOp(metalness), texOp));

   if (fd.features[MFT_InvertSmoothness])
      meta->addStatement(new GenOp("   @ = 1.0-@;\r\n", smoothness, smoothness));

   meta->addStatement(new GenOp("   @ = @.ggga;\r\n", new DecOp(specularColor), texOp));
   meta->addStatement(new GenOp("   @.bga = float3(@,@.g,@);\r\n", material, smoothness, specularColor, metalness));
   output = meta;
}

ShaderFeature::Resources DeferredSpecMapHLSL::getResources( const MaterialFeatureData &fd )
{
   Resources res; 
   res.numTex = 1;
   res.numTexReg = 1;

   return res;
}

void DeferredSpecMapHLSL::setTexData(   Material::StageData &stageDat,
                                       const MaterialFeatureData &fd,
                                       RenderPassData &passData,
                                       U32 &texIndex )
{
   GFXTextureObject *tex = stageDat.getTex( MFT_SpecularMap );
   if ( tex )
   {
      passData.mTexType[ texIndex ] = Material::Standard;
      passData.mSamplerNames[ texIndex ] = "specularMap";
      passData.mTexSlot[ texIndex++ ].texObject = tex;
   }
}

void DeferredSpecMapHLSL::processVert( Vector<ShaderComponent*> &componentList, 
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

// Material Info Flags -> Red ( Flags ) of Material Info Buffer.
void DeferredMatInfoFlagsHLSL::processPix( Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd )
{
   // search for material var
   Var *material = (Var*) LangElement::find( getOutputTargetVarName(ShaderFeature::RenderTarget2) );
   if ( !material )
   {
      // create material var
      material = new Var;
      material->setType( "fragout" );
      material->setName( getOutputTargetVarName(ShaderFeature::RenderTarget2) );
      material->setStructName( "OUT" );
   }

   Var *matInfoFlags = new Var;
   matInfoFlags->setType( "float" );
   matInfoFlags->setName( "matInfoFlags" );
   matInfoFlags->uniform = true;
   matInfoFlags->constSortPos = cspPotentialPrimitive;

   output = new GenOp( "   @.r = @;\r\n", material, matInfoFlags );
}

// Spec Strength -> Blue Channel of Material Info Buffer.
// Spec Power -> Alpha Channel ( of Material Info Buffer.
void DeferredSpecVarsHLSL::processPix( Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd )
{
   // search for material var
   Var *material = (Var*) LangElement::find( getOutputTargetVarName(ShaderFeature::RenderTarget2) );
   if ( !material )
   {
      // create material var
      material = new Var;
      material->setType( "fragout" );
      material->setName( getOutputTargetVarName(ShaderFeature::RenderTarget2) );
      material->setStructName( "OUT" );
   }

   Var *metalness = new Var("metalness", "float");
   metalness->uniform = true;
   metalness->constSortPos = cspPotentialPrimitive;

   Var *smoothness = new Var("smoothness", "float");
   smoothness->uniform = true;
   smoothness->constSortPos = cspPotentialPrimitive;

   MultiLine * meta = new MultiLine;
   //matinfo.g slot reserved for AO later
   meta->addStatement(new GenOp("   @.g = 1.0;\r\n", material));
   meta->addStatement(new GenOp("   @.b = @;\r\n", material, smoothness));
   if (fd.features[MFT_InvertSmoothness])
      meta->addStatement(new GenOp("   @ = 1.0-@;\r\n", smoothness, smoothness));
   meta->addStatement(new GenOp("   @.a = @;\r\n", material, metalness));
   output = meta;
}
