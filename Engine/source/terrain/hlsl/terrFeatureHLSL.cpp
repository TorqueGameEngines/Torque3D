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
#include "terrain/hlsl/terrFeatureHLSL.h"

#include "terrain/terrFeatureTypes.h"
#include "materials/materialFeatureTypes.h"
#include "materials/materialFeatureData.h"
#include "materials/processedMaterial.h"
#include "gfx/gfxDevice.h"
#include "shaderGen/langElement.h"
#include "shaderGen/shaderOp.h"
#include "shaderGen/featureType.h"
#include "shaderGen/featureMgr.h"
#include "shaderGen/shaderGen.h"
#include "core/module.h"

namespace 
{
   void register_hlsl_shader_features_for_terrain(GFXAdapterType type)
   {
      if (type != Direct3D11)
         return;

      FEATUREMGR->registerFeature( MFT_TerrainBaseMap, new TerrainBaseMapFeatHLSL );
      FEATUREMGR->registerFeature( MFT_TerrainParallaxMap, new NamedFeatureHLSL( "Terrain Parallax Texture" ) );   
      FEATUREMGR->registerFeature( MFT_TerrainDetailMap, new TerrainDetailMapFeatHLSL );
      FEATUREMGR->registerFeature( MFT_TerrainNormalMap, new TerrainNormalMapFeatHLSL );
      FEATUREMGR->registerFeature( MFT_TerrainMacroMap, new NamedFeatureHLSL("TerrainMacroMap Deprecated")); // new TerrainMacroMapFeatHLSL);
      FEATUREMGR->registerFeature( MFT_TerrainLightMap, new TerrainLightMapFeatHLSL );
      FEATUREMGR->registerFeature( MFT_TerrainSideProject, new NamedFeatureHLSL( "Terrain Side Projection" ) );
      FEATUREMGR->registerFeature( MFT_TerrainHeightBlend, new TerrainHeightMapBlendHLSL );
      FEATUREMGR->registerFeature( MFT_TerrainORMMap, new TerrainORMMapFeatHLSL );
      FEATUREMGR->registerFeature( MFT_DeferredTerrainBlankInfoMap, new TerrainBlankInfoMapFeatHLSL );
   }
};

MODULE_BEGIN( TerrainFeatHLSL )

   MODULE_INIT_AFTER( ShaderGen )

   MODULE_INIT
   {      
      SHADERGEN->getFeatureInitSignal().notify(&register_hlsl_shader_features_for_terrain);
   }

MODULE_END;


TerrainFeatHLSL::TerrainFeatHLSL()
   : mTorqueDep(ShaderGen::smCommonShaderPath + String("/torque.hlsl" ))
{      
   addDependency( &mTorqueDep );
}

Var* TerrainFeatHLSL::_getUniformVar( const char *name, const char *type, ConstantSortPosition csp )
{
   Var *theVar = (Var*)LangElement::find( name );
   if ( !theVar )
   {
      theVar = new Var;
      theVar->setType( type );
      theVar->setName( name );
      theVar->uniform = true;
      theVar->constSortPos = csp;
   }

   return theVar;
}

Var* TerrainFeatHLSL::_getInDetailCoord( Vector<ShaderComponent*> &componentList )
{
   String name( String::ToString( "detCoord%d", getProcessIndex() ) );
   Var *inDet = (Var*)LangElement::find( name );

   if ( !inDet )
   {
      ShaderConnector *connectComp = dynamic_cast<ShaderConnector *>( componentList[C_CONNECTOR] );

      inDet = connectComp->getElement( RT_TEXCOORD );
      inDet->setName( name );
      inDet->setStructName( "IN" );
      inDet->setType( "float4" );
   }

   return inDet;
}

Var* TerrainFeatHLSL::_getInMacroCoord( Vector<ShaderComponent*> &componentList )
{
   String name( String::ToString( "macroCoord%d", getProcessIndex() ) );
   Var *inDet = (Var*)LangElement::find( name );

   if ( !inDet )
   {
      ShaderConnector *connectComp = dynamic_cast<ShaderConnector *>( componentList[C_CONNECTOR] );

      inDet = connectComp->getElement( RT_TEXCOORD );
      inDet->setName( name );
      inDet->setStructName( "IN" );
      inDet->setType( "float4" );
   }

   return inDet;
}

Var* TerrainFeatHLSL::_getDetailMapSampler()
{
   String name("detailMapSampler");
   Var* detailMapSampler = (Var*)LangElement::find(name);

   if(!detailMapSampler)
   {
      detailMapSampler = new Var;
      detailMapSampler->setName(name);
      detailMapSampler->setType("SamplerState");
      detailMapSampler->uniform = true;
      detailMapSampler->sampler = true;
      detailMapSampler->constNum = Var::getTexUnitNum();
   }

   return detailMapSampler;
}

Var* TerrainFeatHLSL::_getDetailMapArray()
{
   String name("detailMapArray");
   Var* detailMapArray = (Var*)LangElement::find(name);

   if(!detailMapArray)
   {
      detailMapArray = new Var;
      detailMapArray->setName(name);
      detailMapArray->setType("Texture2DArray");
      detailMapArray->uniform = true;
      detailMapArray->texture = true;
      detailMapArray->constNum = _getDetailMapSampler()->constNum;
   }

   return detailMapArray;
}

Var* TerrainFeatHLSL::_getNormalMapSampler()
{
   String name("normalMapSampler");
   Var* normalMapSampler = (Var*)LangElement::find(name);

   if (!normalMapSampler)
   {
      normalMapSampler = new Var;
      normalMapSampler->setName(name);
      normalMapSampler->setType("SamplerState");
      normalMapSampler->uniform = true;
      normalMapSampler->sampler = true;
      normalMapSampler->constNum = Var::getTexUnitNum();
   }

   return normalMapSampler;
}

Var* TerrainFeatHLSL::_getNormalMapArray()
{
   String name("normalMapArray");
   Var* normalMapArray = (Var*)LangElement::find(name);

   if (!normalMapArray)
   {
      normalMapArray = new Var;
      normalMapArray->setName(name);
      normalMapArray->setType("Texture2DArray");
      normalMapArray->uniform = true;
      normalMapArray->texture = true;
      normalMapArray->constNum = _getNormalMapSampler()->constNum;
   }

   return normalMapArray;
}

Var* TerrainFeatHLSL::_getOrmMapSampler()
{
   String name("ormMapSampler");
   Var* ormMapSampler = (Var*)LangElement::find(name);

   if (!ormMapSampler)
   {
      ormMapSampler = new Var;
      ormMapSampler->setName(name);
      ormMapSampler->setType("SamplerState");
      ormMapSampler->uniform = true;
      ormMapSampler->sampler = true;
      ormMapSampler->constNum = Var::getTexUnitNum();
   }

   return ormMapSampler;
}

Var* TerrainFeatHLSL::_getOrmMapArray()
{
   String name("ormMapArray");
   Var* ormMapArray = (Var*)LangElement::find(name);

   if (!ormMapArray)
   {
      ormMapArray = new Var;
      ormMapArray->setName(name);
      ormMapArray->setType("Texture2DArray");
      ormMapArray->uniform = true;
      ormMapArray->texture = true;
      ormMapArray->constNum = _getOrmMapSampler()->constNum;
   }

   return ormMapArray;
}

Var* TerrainFeatHLSL::_getDetailIdStrengthParallax()
{
   String name( String::ToString( "detailIdStrengthParallax", getProcessIndex() ) );

   Var *detailInfo = (Var*)LangElement::find( name );
   if ( !detailInfo )
   {
      detailInfo = new Var;
      detailInfo->setType( "float4" );
      detailInfo->setName( name );
      detailInfo->uniform = true;
      detailInfo->constSortPos = cspPotentialPrimitive;
      detailInfo->arraySize = getProcessIndex();
   }

   detailInfo->arraySize = mMax(detailInfo->arraySize, getProcessIndex() + 1);

   return detailInfo;
}

Var* TerrainFeatHLSL::_getMacroIdStrengthParallax()
{
   String name( String::ToString( "macroIdStrengthParallax%d", getProcessIndex() ) );

   Var *detailInfo = (Var*)LangElement::find( name );
   if ( !detailInfo )
   {
      detailInfo = new Var;
      detailInfo->setType( "float3" );
      detailInfo->setName( name );
      detailInfo->uniform = true;
      detailInfo->constSortPos = cspPotentialPrimitive;
   }

   return detailInfo;
}


void TerrainBaseMapFeatHLSL::processVert(Vector<ShaderComponent*>& componentList,
   const MaterialFeatureData& fd)
{
   MultiLine* meta = new MultiLine;
   output = meta;

   // Generate the incoming texture var.

   Var* inPos = (Var*)LangElement::find("inPosition");
   if (!inPos)
      inPos = (Var*)LangElement::find("position");

   Var* inTex = new Var("texCoord", "float3");

   Var* oneOverTerrainSize = _getUniformVar("oneOverTerrainSize", "float", cspPass);

   meta->addStatement(new GenOp("   @ = @.xyz * @;\r\n",
      new DecOp(inTex), inPos, oneOverTerrainSize));

   ShaderConnector* connectComp = dynamic_cast<ShaderConnector*>(componentList[C_CONNECTOR]);

   // Pass the texture coord to the pixel shader.
   Var* outTex = connectComp->getElement(RT_TEXCOORD);
   outTex->setName("outTexCoord");
   outTex->setStructName("OUT");
   outTex->setType("float4");
   meta->addStatement(new GenOp("   @.xy = @.xy;\r\n", outTex, inTex));

   // If this shader has a side projected layer then we 
   // pass the dot product between the +Y and the normal
   // thru outTexCoord.z for use in blending the textures.
   if (fd.features.hasFeature(MFT_TerrainSideProject))
   {
      Var* inNormal = (Var*)LangElement::find("normal");
      meta->addStatement( 
         new GenOp("   @.z = dot( normalize( float3( @.x, @.y, 0 ) ), float3( 0, 1, 0 ) );\r\n",
            outTex, inNormal, inNormal));
      meta->addStatement(
         new GenOp("   @.w = 1.0 - dot( normalize( @.xyz ), float3( 0, 0, 1 ) );\r\n",
            outTex, inNormal));
   }
   else
   {
      meta->addStatement(new GenOp("   @.z = 0;\r\n", outTex));
      meta->addStatement(new GenOp("   @.w = 0;\r\n", outTex));
   }

   // HACK: This is sort of lazy... we generate the tanget
   // vector here so that we're sure it exists in the parallax
   // and normal features which will expect "T" to exist.
   //
   // If this shader doesn't use it the shader compiler will
   // optimize away this code.
   //
   Var *inTangentZ = getVertTexCoord( "tcTangentZ" );
   Var *inTanget = new Var( "T", "float3" );
   Var *squareSize = _getUniformVar( "squareSize", "float", cspPass );
   meta->addStatement( new GenOp( "   @ = normalize( float3( @, 0, @ ) );\r\n", 
      new DecOp( inTanget ), squareSize, inTangentZ ) );
}

void TerrainBaseMapFeatHLSL::processPix(Vector<ShaderComponent*>& componentList,
   const MaterialFeatureData& fd)
{
   // grab connector texcoord register
   Var *texCoord = getInTexCoord( "texCoord", "float4", componentList );

   // create texture var
   Var* diffuseMap = new Var;
   diffuseMap->setType("SamplerState");
   diffuseMap->setName("baseTexMap");
   diffuseMap->uniform = true;
   diffuseMap->sampler = true;
   diffuseMap->constNum = Var::getTexUnitNum();     // used as texture unit num here

   MultiLine* meta = new MultiLine;

   Var* baseColor = new Var;
   baseColor->setType("float4");
   baseColor->setName("baseColor");

   Var* diffuseTex = new Var;
   diffuseTex->setType("Texture2D");
   diffuseTex->setName("baseTexture");
   diffuseTex->uniform = true;
   diffuseTex->texture = true;
   diffuseTex->constNum = diffuseMap->constNum;
   meta->addStatement(new GenOp("   @ = @.Sample( @, @.xy );\r\n", new DecOp(baseColor), diffuseTex, diffuseMap, texCoord));

   ShaderFeature::OutputTarget target = (fd.features[MFT_isDeferred]) ? RenderTarget1 : DefaultTarget;
   meta->addStatement(new GenOp("   @;\r\n", assignColor(baseColor, Material::Mul, NULL, target)));

   Var* ormConfig;
   if ((fd.features[MFT_isDeferred]))
   {
      // Set base ORM info
      ormConfig = (Var*)LangElement::find(getOutputTargetVarName(RenderTarget2));

      if (!ormConfig)
      {
         // create color var
         ormConfig = new Var;
         ormConfig->setType("fragout");
         ormConfig->setName(getOutputTargetVarName(RenderTarget2));
         ormConfig->setStructName("OUT");
      }
   }
   else
   {
      ormConfig = new Var("ORMConfig", "float4");
      meta->addStatement(new GenOp("   @;\r\n", new DecOp(ormConfig)));
   }

   meta->addStatement(new GenOp("   @ = float4(1.0f/255.0f, 1.0, 1.0, 0.0);\r\n", ormConfig));

   output = meta;
}

ShaderFeature::Resources TerrainBaseMapFeatHLSL::getResources( const MaterialFeatureData &fd )
{
   Resources res; 
   res.numTexReg = 1;
      res.numTex = 1;

   return res;
}

U32 TerrainBaseMapFeatHLSL::getOutputTargets( const MaterialFeatureData &fd ) const
{
   return fd.features[MFT_isDeferred] ? ShaderFeature::RenderTarget2 | ShaderFeature::RenderTarget1 : ShaderFeature::DefaultTarget;
}

TerrainDetailMapFeatHLSL::TerrainDetailMapFeatHLSL()
   :  mTorqueDep(ShaderGen::smCommonShaderPath + String("/torque.hlsl" )),
      mTerrainDep(ShaderGen::smCommonShaderPath + String("/terrain/terrain.hlsl" ))
      
{
   addDependency( &mTorqueDep );
   addDependency( &mTerrainDep );
}

void TerrainDetailMapFeatHLSL::processVert(  Vector<ShaderComponent*> &componentList, 
                                             const MaterialFeatureData &fd )
{
   const S32 detailIndex = getProcessIndex();

   // Grab incoming texture coords... the base map feature
   // made sure this was created.
   Var * inTexCoord = (Var*)LangElement::find( "texCoord" );
   AssertFatal(inTexCoord, "The texture coord is missing!" );

   // Grab the input position.
   Var *inPos = (Var*)LangElement::find( "inPosition" );
   if ( !inPos )
      inPos = (Var*)LangElement::find( "position" );

   // Get the object space eye position.
   Var *eyePos = _getUniformVar( "eyePos", "float3", cspPotentialPrimitive );

   MultiLine *meta = new MultiLine;

   // If we have parallax mapping then make sure we've sent
   // the negative view vector to the pixel shader.
   if (  fd.features.hasFeature( MFT_TerrainParallaxMap ) &&
         !LangElement::find( "outNegViewTS" ) )
   {
      // Get the object to tangent transform which
      // will consume 3 output registers.
      Var *objToTangentSpace = getOutObjToTangentSpace( componentList, meta, fd );

      // Now use a single output register to send the negative
      // view vector in tangent space to the pixel shader.
      ShaderConnector *connectComp = dynamic_cast<ShaderConnector *>( componentList[C_CONNECTOR] );
      Var *outNegViewTS = connectComp->getElement( RT_TEXCOORD );
      outNegViewTS->setName( "outNegViewTS" );
      outNegViewTS->setStructName( "OUT" );
      outNegViewTS->setType( "float3" );
      meta->addStatement( new GenOp( "   @ = mul( @, float3( @ - @.xyz ) );\r\n", 
         outNegViewTS, objToTangentSpace, eyePos, inPos ) );
   }

   // Get the distance from the eye to this vertex.
   Var *dist = (Var*)LangElement::find( "dist" );
   if ( !dist )
   {
      dist = new Var;
      dist->setType( "float" );
      dist->setName( "dist" );  

      meta->addStatement( new GenOp( "   @ = distance( @.xyz, @ );\r\n", 
                                       new DecOp( dist ), inPos, eyePos ) );
   }

   // grab connector texcoord register
   ShaderConnector *connectComp = dynamic_cast<ShaderConnector *>( componentList[C_CONNECTOR] );
   Var * detCoord = connectComp->getElement( RT_TEXCOORD );
   detCoord->setName( String::ToString( "detCoord%d", detailIndex ) );
   detCoord->setStructName( "OUT" );
   detCoord->setType( "float4" );

   // Get the detail scale and fade info.
   Var* detScaleAndFade = (Var*)LangElement::find("detailScaleAndFade");
   if (detScaleAndFade == NULL)
   {
      detScaleAndFade = new Var;
      detScaleAndFade->setType("float4");
      detScaleAndFade->setName("detailScaleAndFade");
      detScaleAndFade->uniform = true;
      detScaleAndFade->constSortPos = cspPotentialPrimitive;
   }

   detScaleAndFade->arraySize = mMax(detScaleAndFade->arraySize, detailIndex + 1);

   // Setup the detail coord.
   //
   // NOTE: You see here we scale the texture coord by 'xyx'
   // to generate the detail coord.  This y is here because
   // its scale is flipped to correct for the non negative y
   // in texCoord.
   //
   // See TerrainBaseMapFeatHLSL::processVert().
   //
   meta->addStatement( new GenOp( "   @.xyz = @ * @.xyx;\r\n", detCoord, inTexCoord, new IndexOp(detScaleAndFade, detailIndex) ) );

   // And sneak the detail fade thru the w detailCoord.
   meta->addStatement(new GenOp("   @.w = ( @.z - @ ) * @.w;\r\n",
      detCoord, new IndexOp(detScaleAndFade, detailIndex), dist, new IndexOp(detScaleAndFade, detailIndex)));

   output = meta;
}

void TerrainDetailMapFeatHLSL::processPix(   Vector<ShaderComponent*> &componentList, 
                                             const MaterialFeatureData &fd )
{
   const S32 detailIndex = getProcessIndex();
   Var *inTexCoord = getVertTexCoord( "texCoord" );
   
   MultiLine *meta = new MultiLine;

   // We need the negative tangent space view vector
   // as in parallax mapping we step towards the camera.
   Var *negViewTS = (Var*)LangElement::find( "negViewTS" );
   if (  !negViewTS &&
         fd.features.hasFeature( MFT_TerrainParallaxMap ) )
   {
      Var *inNegViewTS = (Var*)LangElement::find( "outNegViewTS" );
      if ( !inNegViewTS )
      {
         ShaderConnector *connectComp = dynamic_cast<ShaderConnector *>( componentList[C_CONNECTOR] );
         inNegViewTS = connectComp->getElement( RT_TEXCOORD );
         inNegViewTS->setName( "outNegViewTS" );
         inNegViewTS->setStructName( "IN" );
         inNegViewTS->setType( "float3" );
      }

      negViewTS = new Var( "negViewTS", "float3" );
      meta->addStatement( new GenOp( "   @ = normalize( @ );\r\n", new DecOp( negViewTS ), inNegViewTS ) );
   }

   // Get the layer samples.
   Var *layerSample = (Var*)LangElement::find( "layerSample" );
   if ( !layerSample )
   {
      layerSample = new Var;
      layerSample->setType( "float4" );
      layerSample->setName( "layerSample" );

      // Get the layer texture var
      Var *layerTex = new Var;
      layerTex->setType( "SamplerState" );
      layerTex->setName( "layerTex" );
      layerTex->uniform = true;
      layerTex->sampler = true;
      layerTex->constNum = Var::getTexUnitNum();

      Var* layerTexObj = new Var;
      layerTexObj->setName("layerTexObj");
      layerTexObj->setType("Texture2D");
      layerTexObj->uniform = true;
      layerTexObj->texture = true;
      layerTexObj->constNum = layerTex->constNum;
      // Read the layer texture to get the samples.
      meta->addStatement(new GenOp("   @ = round( @.Sample( @, @.xy ) * 255.0f );\r\n",
         new DecOp(layerSample), layerTexObj, layerTex, inTexCoord));
   }

   Var *layerSize = (Var*)LangElement::find( "layerSize" );
   if ( !layerSize )
   {
      layerSize = new Var;
      layerSize->setType( "float" );
      layerSize->setName( "layerSize" );
      layerSize->uniform = true;
      layerSize->constSortPos = cspPass;
   }

   // Grab the incoming detail coord.
   Var * detCoord = _getInDetailCoord( componentList );

   // Get the detail id.
   Var *detailInfo = _getDetailIdStrengthParallax();

   // Create the detail blend var.
   Var *detailBlend = new Var;
   detailBlend->setType( "float" );
   detailBlend->setName( String::ToString( "detailBlend%d", detailIndex ) );

   // Calculate the blend for this detail texture.
   meta->addStatement( new GenOp( "   @ = calcBlend( @.x, @.xy, @, @ );\r\n", 
                                    new DecOp( detailBlend ), new IndexOp(detailInfo, detailIndex), inTexCoord, layerSize, layerSample ) );

   // If we had a parallax feature... then factor in the parallax
   // amount so that it fades out with the layer blending.
   if (fd.features.hasFeature(MFT_TerrainParallaxMap, detailIndex))
   {
      Var* normalMapArray = _getNormalMapArray();
      Var* normalMapSampler = _getNormalMapSampler();

      // Call the library function to do the rest.
      if (fd.features.hasFeature(MFT_IsBC3nm, detailIndex))
      {
         meta->addStatement(new GenOp("   @.xy += parallaxOffsetDxtnmTexArray( @, @, float3(@.xy, @.x), @, @.z * @ );\r\n",
            detCoord, normalMapArray, normalMapSampler, detCoord, new IndexOp(detailInfo, detailIndex), negViewTS, new IndexOp(detailInfo, detailIndex), detailBlend));
      }
      else
      {
         meta->addStatement(new GenOp("   @.xy += parallaxOffsetTexArray( @, @, float3(@.xy, @.x), @, @.z * @ );\r\n",
            detCoord, normalMapArray, normalMapSampler, detCoord, new IndexOp(detailInfo, detailIndex), negViewTS, new IndexOp(detailInfo, detailIndex), detailBlend));
      }
     
   }

   Var *detailColor = (Var*)LangElement::find(String::ToString("detailColor%d", detailIndex));
   if ( !detailColor )
   {
      detailColor = new Var;
      detailColor->setType( "float4" );
      detailColor->setName( String::ToString("detailColor%d", detailIndex) );
      meta->addStatement( new GenOp( "   @;\r\n", new DecOp( detailColor ) ) );
   }

   //Sampled detail texture that is not expanded
   Var* detailMapArray = _getDetailMapArray();
   Var* detailMapSampler = _getDetailMapSampler();

   if (fd.features.hasFeature(MFT_TerrainSideProject, detailIndex))
   {
      meta->addStatement(new GenOp("   @ = ( lerp( @.Sample( @, float3(@.xy, @.x) ), lerp( @.Sample( @, float3(@.yz, @.x) ), @.Sample( @, float3(@.xz, @.x) ), @.z ), @.w) * 2.0 ) - 1.0;\r\n",
         detailColor,
         detailMapArray, detailMapSampler, detCoord, new IndexOp(detailInfo, detailIndex),
         detailMapArray, detailMapSampler, detCoord, new IndexOp(detailInfo, detailIndex),
         detailMapArray, detailMapSampler, detCoord, new IndexOp(detailInfo, detailIndex),
         inTexCoord, inTexCoord));
   }
   else
   {
      meta->addStatement(new GenOp("   @ = ( @.Sample( @, float3(@.xy, @.x) ) * 2.0 ) - 1.0;\r\n",
         detailColor, detailMapArray, detailMapSampler, detCoord, new IndexOp(detailInfo, detailIndex)));
   }

   meta->addStatement(new GenOp("   @ *= @.y * @;\r\n", detailColor, new IndexOp(detailInfo, detailIndex), detailBlend));

   if (!fd.features.hasFeature(MFT_TerrainNormalMap))
   {
      // Check to see if we have a gbuffer normal.
      Var* gbNormal = (Var*)LangElement::find("gbNormal");

      // If we have a gbuffer normal and we don't have a
      // normal map feature then we need to lerp in a
      // default normal else the normals below this layer
      // will show thru.
      if (gbNormal &&
         !fd.features.hasFeature(MFT_TerrainNormalMap, detailIndex))
      {
         Var* viewToTangent = getInViewToTangent(componentList);

         meta->addStatement(new GenOp("   @ = lerp( @, @[2], @ );\r\n", gbNormal, gbNormal, viewToTangent, detailBlend));
      }

      ShaderFeature::OutputTarget target = (fd.features[MFT_isDeferred]) ? RenderTarget1 : DefaultTarget;

      Var* outColor = (Var*)LangElement::find(getOutputTargetVarName(target));

      meta->addStatement(new GenOp("      @ += @ * @;\r\n", outColor, detailColor, detailBlend));
   }

   output = meta;
}

ShaderFeature::Resources TerrainDetailMapFeatHLSL::getResources( const MaterialFeatureData &fd )
{
   Resources res;

   if ( getProcessIndex() == 0 )
   {
      // If this is the first detail pass then we 
      // samples from the layer tex.
      res.numTex += 1;
      res.numTexReg += 1;

      // Add Detail TextureArray
      res.numTex += 1;
      res.numTexReg += 1;
   }

   return res;
}

U32 TerrainDetailMapFeatHLSL::getOutputTargets( const MaterialFeatureData &fd ) const
{
   return fd.features[MFT_isDeferred] ? ShaderFeature::RenderTarget1 : ShaderFeature::DefaultTarget;
}


TerrainMacroMapFeatHLSL::TerrainMacroMapFeatHLSL()
   :  mTorqueDep(ShaderGen::smCommonShaderPath + String("/torque.hlsl" )),
      mTerrainDep(ShaderGen::smCommonShaderPath + String("/terrain/terrain.hlsl" ))
      
{
   addDependency( &mTorqueDep );
   addDependency( &mTerrainDep );
}


void TerrainMacroMapFeatHLSL::processVert(  Vector<ShaderComponent*> &componentList, 
                                             const MaterialFeatureData &fd )
{
   const S32 detailIndex = getProcessIndex();

   // Grab incoming texture coords... the base map feature
   // made sure this was created.
   Var *inTex = (Var*)LangElement::find( "texCoord" );
   AssertFatal( inTex, "The texture coord is missing!" );

   // Grab the input position.
   Var *inPos = (Var*)LangElement::find( "inPosition" );
   if ( !inPos )
      inPos = (Var*)LangElement::find( "position" );

   // Get the object space eye position.
   Var *eyePos = _getUniformVar( "eyePos", "float3", cspPotentialPrimitive );

   MultiLine *meta = new MultiLine;

   // Get the distance from the eye to this vertex.
   Var *dist = (Var*)LangElement::find( "macroDist" );
   if ( !dist )
   {
      dist = new Var;
      dist->setType( "float" );
      dist->setName( "macroDist" );  

      meta->addStatement( new GenOp( "   @ = distance( @.xyz, @ );\r\n", 
                                       new DecOp( dist ), inPos, eyePos ) );
   }

   // grab connector texcoord register
   ShaderConnector *connectComp = dynamic_cast<ShaderConnector *>( componentList[C_CONNECTOR] );
   Var *outTex = connectComp->getElement( RT_TEXCOORD );
   outTex->setName( String::ToString( "macroCoord%d", detailIndex ) );
   outTex->setStructName( "OUT" );
   outTex->setType( "float4" );

   // Get the detail scale and fade info.
   Var* macroScaleAndFade = (Var*)LangElement::find("macroScaleAndFade");
   if (macroScaleAndFade == NULL)
   {
      macroScaleAndFade = new Var;
      macroScaleAndFade->setType("float4");
      macroScaleAndFade->setName("macroScaleAndFade");
      macroScaleAndFade->uniform = true;
      macroScaleAndFade->constSortPos = cspPotentialPrimitive;
   }

   macroScaleAndFade->arraySize = mMax(macroScaleAndFade->arraySize, detailIndex + 1);

   // Setup the detail coord.
   meta->addStatement( new GenOp( "   @.xyz = @ * @.xyx;\r\n", outTex, inTex, new IndexOp(macroScaleAndFade, detailIndex)) );

   // And sneak the detail fade thru the w detailCoord.
   meta->addStatement( new GenOp( "   @.w = ( @.z - @ ) * @.w;\r\n", 
                                    outTex, new IndexOp(macroScaleAndFade, detailIndex), dist, new IndexOp(macroScaleAndFade, detailIndex)) );

   output = meta;
}


void TerrainMacroMapFeatHLSL::processPix(   Vector<ShaderComponent*> &componentList, 
                                             const MaterialFeatureData &fd )
{
   const S32 detailIndex = getProcessIndex();
   Var *inTex = getVertTexCoord( "texCoord" );
   
   MultiLine *meta = new MultiLine;

   // We need the negative tangent space view vector
   // as in parallax mapping we step towards the camera.
   Var *negViewTS = (Var*)LangElement::find( "negViewTS" );
   if (  !negViewTS &&
         fd.features.hasFeature( MFT_TerrainParallaxMap ) )
   {
      Var *inNegViewTS = (Var*)LangElement::find( "outNegViewTS" );
      if ( !inNegViewTS )
      {
         ShaderConnector *connectComp = dynamic_cast<ShaderConnector *>( componentList[C_CONNECTOR] );
         inNegViewTS = connectComp->getElement( RT_TEXCOORD );
         inNegViewTS->setName( "outNegViewTS" );
         inNegViewTS->setStructName( "IN" );
         inNegViewTS->setType( "float3" );
      }

      negViewTS = new Var( "negViewTS", "float3" );
      meta->addStatement( new GenOp( "   @ = normalize( @ );\r\n", new DecOp( negViewTS ), inNegViewTS ) );
   }

   // Get the layer samples.
   Var *layerSample = (Var*)LangElement::find( "layerSample" );
   if ( !layerSample )
   {
      layerSample = new Var;
      layerSample->setType( "float4" );
      layerSample->setName( "layerSample" );

      // Get the layer texture var
      Var *layerTex = new Var;
      layerTex->setType( "SamplerState" );
      layerTex->setName( "macrolayerTex" );
      layerTex->uniform = true;
      layerTex->sampler = true;
      layerTex->constNum = Var::getTexUnitNum();

      // Read the layer texture to get the samples.
      Var *layerTexObj = new Var;
      layerTexObj->setType("Texture2D");
      layerTexObj->setName("macroLayerTexObj");
      layerTexObj->uniform = true;
      layerTexObj->texture = true;
      layerTexObj->constNum = layerTex->constNum;
      meta->addStatement(new GenOp("   @ = round( @.Sample( @, @.xy ) * 255.0f );\r\n",
         new DecOp(layerSample), layerTexObj, layerTex, inTex));
   }

   Var *layerSize = (Var*)LangElement::find( "layerSize" );
   if ( !layerSize )
   {
      layerSize = new Var;
      layerSize->setType( "float" );
      layerSize->setName( "layerSize" );
      layerSize->uniform = true;
      layerSize->constSortPos = cspPass;
   }

   // Grab the incoming detail coord.
   Var *inDet = _getInMacroCoord( componentList );

   // Get the detail id.
   Var *detailInfo = _getMacroIdStrengthParallax();

   // Create the detail blend var.
   Var *detailBlend = new Var;
   detailBlend->setType( "float" );
   detailBlend->setName( String::ToString( "macroBlend%d", detailIndex ) );

   // Calculate the blend for this detail texture.
   meta->addStatement( new GenOp( "   @ = calcBlend( @.x, @.xy, @, @ );\r\n", 
                                    new DecOp( detailBlend ), new IndexOp(detailInfo, detailIndex), inTex, layerSize, layerSample ) );
   
   // Check to see if we have a gbuffer normal.
   Var *gbNormal = (Var*)LangElement::find( "gbNormal" );
   
   // If we have a gbuffer normal and we don't have a
   // normal map feature then we need to lerp in a 
   // default normal else the normals below this layer
   // will show thru.
   if (  gbNormal && 
      !fd.features.hasFeature( MFT_TerrainNormalMap, detailIndex ) )
   {
      Var *viewToTangent = getInViewToTangent( componentList );
      
      meta->addStatement( new GenOp( "   @ = lerp( @, @[2], min( @, @.w ) );\r\n", 
         gbNormal, gbNormal, viewToTangent, detailBlend, inDet ) );
   }
   
   Var *detailColor = (Var*)LangElement::find("macroColor");
   if (!detailColor)
   {
      detailColor = new Var;
      detailColor->setType( "float4" );
      detailColor->setName( "macroColor" );
      meta->addStatement( new GenOp( "   @;\r\n", new DecOp( detailColor ) ) );
   }

   // If we're using SM 3.0 then take advantage of 
   // dynamic branching to skip layers per-pixel.
   if ( GFX->getPixelShaderVersion() >= 3.0f )
      meta->addStatement( new GenOp( "   if ( @ > 0.0f )\r\n", detailBlend ) );

   meta->addStatement( new GenOp( "   {\r\n" ) );

   Var* detailMapArray = _getDetailMapArray();
   Var* detailMapSampler = _getDetailMapSampler();

   // Note that we're doing the standard greyscale detail 
   // map technique here which can darken and lighten the 
   // diffuse texture.
   //
   // We take two color samples and lerp between them for
   // side projection layers... else a single sample.
   //
   if (fd.features.hasFeature(MFT_TerrainSideProject, detailIndex))
   {
      meta->addStatement(new GenOp("   @ = ( lerp( @.Sample( @, float3(@.xy, @.x) ), lerp( @.Sample( @, float3(@.yz, @.x) ), @.Sample( @, float3(@.xz, @.x) ), @.z ), @.w ) * 2.0 ) - 1.0;\r\n",
         detailColor,
         detailMapArray, detailMapSampler, inDet, new IndexOp(detailInfo, detailIndex),
         detailMapArray, detailMapSampler, inDet, new IndexOp(detailInfo, detailIndex),
         detailMapArray, detailMapSampler, inDet, new IndexOp(detailInfo, detailIndex),
         inTex, inTex));
   }
   else
   {
      meta->addStatement(new GenOp("   @ = ( @.Sample( @, float3(@.xy, @.x) ) * 2.0 ) - 1.0;\r\n",
         detailColor, detailMapArray, detailMapSampler, inDet, new IndexOp(detailInfo, detailIndex)));
   }

   meta->addStatement( new GenOp( "   @ *= @.y * @.w;\r\n",
                                    detailColor, new IndexOp(detailInfo, detailIndex), inDet ) );

   ShaderFeature::OutputTarget target = (fd.features[MFT_isDeferred]) ? RenderTarget1 : DefaultTarget;

   Var *outColor = (Var*)LangElement::find( getOutputTargetVarName(target) );

   meta->addStatement(new GenOp("      @ += @ * @;\r\n",
                                    outColor, detailColor, detailBlend));

   meta->addStatement( new GenOp( "   }\r\n" ) );

   output = meta;
}

ShaderFeature::Resources TerrainMacroMapFeatHLSL::getResources( const MaterialFeatureData &fd )
{
   Resources res;

   if ( getProcessIndex() == 0 )
   {
      // If this is the first detail pass then we 
      // samples from the layer tex.
      res.numTex += 1;
   }

      res.numTex += 1;

   // Finally we always send the detail texture 
   // coord to the pixel shader.
   res.numTexReg += 1;

   return res;
}

U32 TerrainMacroMapFeatHLSL::getOutputTargets( const MaterialFeatureData &fd ) const
{
   return fd.features[MFT_isDeferred] ? ShaderFeature::RenderTarget1 : ShaderFeature::DefaultTarget;
}

void TerrainNormalMapFeatHLSL::processVert(  Vector<ShaderComponent*> &componentList, 
                                             const MaterialFeatureData &fd )
{
   // We only need to process normals during the deferred.
   if ( !fd.features.hasFeature( MFT_DeferredConditioner ) )
      return;

   MultiLine *meta = new MultiLine;

   if ( !fd.features.hasFeature(MFT_TerrainHeightBlend) )
   {
      // Make sure the world to tangent transform
      // is created and available for the pixel shader.
      getOutViewToTangent(componentList, meta, fd);
   }

   output = meta;
}

void TerrainNormalMapFeatHLSL::processPix(   Vector<ShaderComponent*> &componentList, 
                                             const MaterialFeatureData &fd )
{
   // We only need to process normals during the deferred.
   if (!fd.features.hasFeature(MFT_DeferredConditioner))
      return;

   MultiLine *meta = new MultiLine;

   const S32 normalIndex = getProcessIndex();

   Var *detailBlend = (Var*)LangElement::find( String::ToString( "detailBlend%d", normalIndex ) );
   AssertFatal( detailBlend, "The detail blend is missing!" );

   /// Get the texture coord.
   Var* inDet = _getInDetailCoord(componentList);
   Var* inTex = getVertTexCoord("texCoord");
   Var* detailInfo = _getDetailIdStrengthParallax();

   // Sample the normal map.
   //
   // We take two normal samples and lerp between them for
   // side projection layers... else a single sample.
   LangElement* texOp;

   Var* normalMapSampler = _getNormalMapSampler();
   Var* normalMapArray = _getNormalMapArray();

   if (fd.features.hasFeature(MFT_TerrainSideProject, normalIndex))
   {
      texOp = new GenOp("lerp( @.Sample( @, float3(@.xy, @.x) ), lerp( @.Sample( @, float3(@.yz, @.x) ), @.Sample( @, float3(@.xz, @.x) ), @.z ), @.w )",
         normalMapArray, normalMapSampler, inDet, new IndexOp(detailInfo, normalIndex),
         normalMapArray, normalMapSampler, inDet, new IndexOp(detailInfo, normalIndex),
         normalMapArray, normalMapSampler, inDet, new IndexOp(detailInfo, normalIndex),
         inTex, inTex);
   }
   else
      texOp = new GenOp("@.Sample(@, float3(@.xy, @.x))", normalMapArray, normalMapSampler, inDet, new IndexOp(detailInfo, normalIndex));

   // create bump normal
   Var* bumpNorm = new Var;
   bumpNorm->setName(String::ToString("bumpNormal%d", normalIndex));
   bumpNorm->setType("float4");

   LangElement* bumpNormDecl = new DecOp(bumpNorm);
   meta->addStatement(expandNormalMap(texOp, bumpNormDecl, bumpNorm, fd));

   if (!fd.features.hasFeature(MFT_TerrainNormalMap))
   {
      Var* viewToTangent = getInViewToTangent(componentList);

      // This var is read from GBufferConditionerHLSL and 
      // used in the deferred output.
      Var* gbNormal = (Var*)LangElement::find("gbNormal");
      if (!gbNormal)
      {
         gbNormal = new Var;
         gbNormal->setName("gbNormal");
         gbNormal->setType("float3");
         meta->addStatement(new GenOp("   @ = @[2];\r\n", new DecOp(gbNormal), viewToTangent));
      }

      // If we're using SM 3.0 then take advantage of 
      // dynamic branching to skip layers per-pixel.
      if (GFX->getPixelShaderVersion() >= 3.0f)
         meta->addStatement(new GenOp("   if ( @ > 0.0f )\r\n", detailBlend));

      meta->addStatement(new GenOp("   {\r\n"));

      // Normalize is done later... 
      // Note: The reverse mul order is intentional. Affine matrix.
      meta->addStatement(new GenOp("      @ = lerp( @, mul( @.xyz, @ ), min( @, @.w ) );\r\n",
         gbNormal, gbNormal, bumpNorm, viewToTangent, detailBlend, inDet));

      // End the conditional block.
      meta->addStatement(new GenOp("   }\r\n"));
   }
   
   output = meta;
}

ShaderFeature::Resources TerrainNormalMapFeatHLSL::getResources( const MaterialFeatureData &fd )
{
   Resources res;

   if (!fd.features.hasFeature(MFT_DeferredConditioner))
   {
      return  res;
   }

   S32 featureIndex = 0, firstNormalMapIndex = 0;
   for (int idx = 0; idx < fd.features.getCount(); ++idx) {
      const FeatureType &type = fd.features.getAt(idx, &featureIndex);
     if (type == MFT_TerrainNormalMap) {
        firstNormalMapIndex = getMin(firstNormalMapIndex, featureIndex);
     }
   }

   // We only need to process normals during the deferred.
   if (getProcessIndex() == firstNormalMapIndex)
   {
      res.numTexReg += 1;
      res.numTex += 1;
   }

   return res;
}

void TerrainLightMapFeatHLSL::processPix( Vector<ShaderComponent*> &componentList, 
                                          const MaterialFeatureData &fd )
{
   // grab connector texcoord register
   Var *inTex = (Var*)LangElement::find( "texCoord" );
   if ( !inTex )
      return;

   // Get the lightmap texture.
   Var *lightMap = new Var;
   lightMap->setType( "SamplerState" );
   lightMap->setName( "lightMapTex" );
   lightMap->uniform = true;
   lightMap->sampler = true;
   lightMap->constNum = Var::getTexUnitNum();

   MultiLine *meta = new MultiLine;

   // Find or create the lightMask value which is read by
   // RTLighting to mask out the lights.
   //
   // The first light is always the sunlight so we apply
   // the shadow mask to only the first channel.
   //
   Var *lightMask = (Var*)LangElement::find( "lightMask" );
   if ( !lightMask )
   {
      lightMask = new Var( "lightMask", "float4" );
      meta->addStatement( new GenOp( "   @ = 1;\r\n", new DecOp( lightMask ) ) );
   }

   Var* lightMapTex = new Var;
   lightMapTex->setName("lightMapTexObj");
   lightMapTex->setType("Texture2D");
   lightMapTex->uniform = true;
   lightMapTex->texture = true;
   lightMapTex->constNum = lightMap->constNum;
   meta->addStatement(new GenOp("   @[0] = @.Sample( @, @.xy ).r;\r\n", lightMask, lightMapTex, lightMap, inTex));

   output = meta;
}

ShaderFeature::Resources TerrainLightMapFeatHLSL::getResources( const MaterialFeatureData &fd )
{
   Resources res; 
   res.numTex = 1;
   return res;
}

void TerrainORMMapFeatHLSL::processVert(Vector<ShaderComponent*> &componentList,
   const MaterialFeatureData &fd)
{
   // We only need to process normals during the deferred.
   if (!fd.features.hasFeature(MFT_DeferredConditioner))
      return;

   MultiLine* meta = new MultiLine;

   if (!fd.features.hasFeature(MFT_TerrainHeightBlend))
   {
      // Make sure the world to tangent transform
      // is created and available for the pixel shader.
      getOutViewToTangent(componentList, meta, fd);
   }


   output = meta;
}

U32 TerrainORMMapFeatHLSL::getOutputTargets(const MaterialFeatureData &fd) const
{
   return fd.features[MFT_isDeferred] ? ShaderFeature::RenderTarget2 : ShaderFeature::DefaultTarget;
}

void TerrainORMMapFeatHLSL::processPix(Vector<ShaderComponent*> &componentList,
   const MaterialFeatureData &fd)
{
   /// Get the texture coord.
   Var *inDet = _getInDetailCoord(componentList);
   Var *inTex = getVertTexCoord("texCoord");
   Var* detailInfo = _getDetailIdStrengthParallax();

   const S32 compositeIndex = getProcessIndex();
   // Sample the normal map.
   //
   // We take two normal samples and lerp between them for
   // side projection layers... else a single sample.
   LangElement *texOp;

   Var* ormMapArray = _getOrmMapArray();
   Var* ormMapSampler = _getOrmMapSampler();
   if (fd.features.hasFeature(MFT_TerrainSideProject, compositeIndex))
   {
      texOp = new GenOp("lerp( @.Sample( @, float3(@.xy, @.x) ), lerp( @.Sample( @, float3(@.yz, @.x) ), @.Sample( @, float3(@.xz, @.x) ), @.z ), @.w )",
         ormMapArray, ormMapSampler, inDet, new IndexOp(detailInfo, compositeIndex),
         ormMapArray, ormMapSampler, inDet, new IndexOp(detailInfo, compositeIndex),
         ormMapArray, ormMapSampler, inDet, new IndexOp(detailInfo, compositeIndex),
         inTex, inTex);
   }
   else
      texOp = new GenOp("@.Sample(@, float3(@.xy, @.x))", ormMapArray, ormMapSampler, inDet, new IndexOp(detailInfo, compositeIndex));

   MultiLine* meta = new MultiLine;
   // search for material var
   Var* ormConfig;
   if ((fd.features[MFT_isDeferred]))
   {
      // Set base ORM info
      ormConfig = (Var*)LangElement::find(getOutputTargetVarName(RenderTarget2));

      if (!ormConfig)
      {
         // create color var
         ormConfig = new Var;
         ormConfig->setType("fragout");
         ormConfig->setName(getOutputTargetVarName(RenderTarget2));
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
   if (compositeIndex == 0)
   {
      meta->addStatement(new GenOp("   @ = float4(1.0f/255.0f, 0.0, 0.0, 0.0);\r\n", ormConfig));
   }

   Var *detailBlend = (Var*)LangElement::find(String::ToString("detailBlend%d", compositeIndex));
   AssertFatal(detailBlend, "The detail blend is missing!");

   String matinfoName(String::ToString("matinfoCol%d", compositeIndex));
   Var *matinfoCol = new Var(matinfoName, "float3");

   meta->addStatement(new GenOp("   @ = @.rgb;\r\n", new DecOp(matinfoCol), texOp));

   if (fd.features.hasFeature(MFT_InvertRoughness, compositeIndex))
   {
      meta->addStatement(new GenOp("   @.b = 1.0 - @.b;\r\n", matinfoCol, matinfoCol));
   }

   meta->addStatement(new GenOp("   @ = lerp(float3(1.0, 1.0, 0.0), @, @.y * @.w);\r\n", matinfoCol, matinfoCol, new IndexOp(detailInfo, compositeIndex), inDet));

   if (!fd.features.hasFeature(MFT_TerrainHeightBlend))
   {
      meta->addStatement(new GenOp("   @.gba += @ * @;\r\n", ormConfig, matinfoCol, detailBlend));
   }

   output = meta;
}

ShaderFeature::Resources TerrainORMMapFeatHLSL::getResources(const MaterialFeatureData &fd)
{
   Resources res;
   res.numTex = 1;
   return res;
}

void TerrainBlankInfoMapFeatHLSL::processPix(Vector<ShaderComponent*> &componentList,
   const MaterialFeatureData &fd)
{
   S32 compositeIndex = getProcessIndex();

   MultiLine * meta = new MultiLine;   Var* ormConfig;
   if ((fd.features[MFT_isDeferred]))
   {
      // Set base ORM info
      ormConfig = (Var*)LangElement::find(getOutputTargetVarName(RenderTarget2));

      if (!ormConfig)
      {
         // create color var
         ormConfig = new Var;
         ormConfig->setType("fragout");
         ormConfig->setName(getOutputTargetVarName(RenderTarget2));
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

   if (compositeIndex == 0)
   {
      meta->addStatement(new GenOp("   @ = float4(1.0f/255.0f, 1.0, 1.0, 0.0);\r\n", ormConfig));
   }

   Var* detailBlend = (Var*)LangElement::find(String::ToString("detailBlend%d", compositeIndex));
   AssertFatal(detailBlend, "The detail blend is missing!");

   String matinfoName(String::ToString("matinfoCol%d", compositeIndex));

   if (!fd.features.hasFeature(MFT_TerrainHeightBlend))
   {
      meta->addStatement(new GenOp("   @.gba += float3(@, @, 0.0);\r\n", ormConfig, detailBlend, detailBlend));
   }

   output = meta;
}

void TerrainHeightMapBlendHLSL::processVert(Vector<ShaderComponent*>& componentList,
   const MaterialFeatureData& fd)
{
   // We only need to process normals during the deferred.
   if (!fd.features.hasFeature(MFT_DeferredConditioner))
      return;

   MultiLine* meta = new MultiLine;

   // Handle an edge-case when there are no detail-maps available
   if (fd.features.getNextFeatureIndex(MFT_TerrainDetailMap, -1) >= 0)
   {
      // Make sure the world to tangent transform
      // is created and available for the pixel shader.
      getOutViewToTangent(componentList, meta, fd);
   }

   output = meta;
}

void TerrainHeightMapBlendHLSL::processPix(Vector<ShaderComponent*>& componentList,
   const MaterialFeatureData& fd)
{
   ShaderFeature::OutputTarget target = (fd.features[MFT_isDeferred]) ? RenderTarget1 : DefaultTarget;

   Var* outColor = (Var*)LangElement::find(getOutputTargetVarName(target));

   if (!outColor)
      return;

   MultiLine* meta = new MultiLine;

   // Count number of detail layers
   int detailCount = 0;
   while (true)
   {
      if (LangElement::find(String::ToString("detailBlend%d", detailCount)) == NULL)
      {
         break;
      }

      ++detailCount;
   }

   if (detailCount == 0)
   {
      return;
   }

   Var* depth = (Var*)LangElement::find("baseBlendDepth");
   if (depth == NULL)
   {
      depth = new Var;
      depth->setType("float");
      depth->setName("baseBlendDepth");
      depth->uniform = true;
      depth->constSortPos = cspPrimitive;
   }

   Var* heightRange = new Var("heightRange", "float2");
   meta->addStatement(new GenOp("   @ = float2(2.0f,0);//x=min, y=max\r\n", new DecOp(heightRange)));
   // Compute blend factors
   for (S32 idx = 0; idx < detailCount; ++idx)
   {
      Var* bumpNormal = (Var*)LangElement::find(String::ToString("bumpNormal%d", idx));
      Var* blendDepth = (Var*)LangElement::find(String::ToString("blendDepth%d", idx));
      if (!blendDepth)
      {
         blendDepth = new Var;
         blendDepth->setType("float");
         blendDepth->setName(String::ToString("blendDepth%d", idx));
         blendDepth->uniform = true;
         blendDepth->constSortPos = cspPrimitive;
      }

      Var* blendContrast = (Var*)LangElement::find(String::ToString("blendContrast%d", idx));
      if (!blendContrast)
      {
         blendContrast = new Var;
         blendContrast->setType("float");
         blendContrast->setName(String::ToString("blendContrast%d", idx));
         blendContrast->uniform = true;
         blendContrast->constSortPos = cspPrimitive;
      }
      Var* detailH = (Var*)LangElement::find(String::ToString("detailH%d", idx));
      Var* detailBlend = (Var*)LangElement::find(String::ToString("detailBlend%d", idx));
      if (!detailH)
      {
         detailH = new Var;
         detailH->setType("float");
         detailH->setName(String::ToString("detailH%d", idx));

         meta->addStatement(new GenOp("   @ = @+@;\r\n", new DecOp(detailH), blendDepth, depth));
         if (bumpNormal != NULL)
         {
            meta->addStatement(new GenOp("   @ += @.a * @;\r\n", detailH, bumpNormal, blendContrast));
         }
         meta->addStatement(new GenOp("   @ *= @;\r\n", detailH, detailBlend));
         meta->addStatement(new GenOp("   @ = float2(min(@.x,@),max(@.y,@));\r\n", heightRange, heightRange, detailH, heightRange, detailH));
      }
   }

   meta->addStatement(new GenOp("\r\n"));
   if (detailCount > 1)
   {
      for (S32 idx = 0; idx < detailCount; ++idx)
      {
         Var* detailBlend = (Var*)LangElement::find(String::ToString("detailBlend%d", idx));
         Var* detailH = (Var*)LangElement::find(String::ToString("detailH%d", idx));
         meta->addStatement(new GenOp("   @ = (@-@.x)/(@.y-@.x);\r\n", detailH, detailH, heightRange, heightRange, heightRange));
      }
      meta->addStatement(new GenOp("\r\n"));
   }
   else
   {
      for (S32 idx = 0; idx < detailCount; ++idx)
      {
         Var* detailH = (Var*)LangElement::find(String::ToString("detailH%d", idx));
         meta->addStatement(new GenOp("   @ = 1.0;\r\n", detailH));
      }
   }

   meta->addStatement(new GenOp("   @.rgb += (", outColor));

   for (S32 idx = 0; idx < detailCount; ++idx)
   {
      Var* detailColor = (Var*)LangElement::find(String::ToString("detailColor%d", idx));
      Var* detailH = (Var*)LangElement::find(String::ToString("detailH%d", idx));
      Var* detCoord = (Var*)LangElement::find(String::ToString("detCoord%d", idx));

      if (idx > 0)
      {
         meta->addStatement(new GenOp(" + "));
      }

      meta->addStatement(new GenOp("((@.rgb * @)*max(@.w,0))", detailColor, detailH, detCoord));
   }

   meta->addStatement(new GenOp(");\r\n"));

   // Compute ORM
   Var* ormOutput;
   if (fd.features[MFT_isDeferred])
   {
      ormOutput = (Var*)LangElement::find(getOutputTargetVarName(RenderTarget2));
   }
   else
   {
      ormOutput = (Var*)LangElement::find("ORMConfig");
   }
   meta->addStatement(new GenOp("   @.gba = (", ormOutput));

   for (S32 idx = 0; idx < detailCount; ++idx)
   {
      Var* matinfoCol = (Var*)LangElement::find(String::ToString("matinfoCol%d", idx));
      Var* detailH = (Var*)LangElement::find(String::ToString("detailH%d", idx));

      if (idx > 0)
      {
         meta->addStatement(new GenOp(" + "));
      }
      if (matinfoCol)
      {
         meta->addStatement(new GenOp("(@ * @)", matinfoCol, detailH));
      }
      else
      {
         meta->addStatement(new GenOp("(float3(1.0, 1.0, 0.0) * @)", detailH));
      }
   }

   meta->addStatement(new GenOp(");\r\n"));

    // Compute normals
   Var* viewToTangent = getInViewToTangent(componentList);
   Var* bumpSum = new Var("bumpNorm", "float3");

   meta->addStatement(new GenOp("   @ = float3(0, 0, 1)", new DecOp(bumpSum)));
   for (S32 idx = 0; idx < detailCount; ++idx)
   {
      Var* detailH = (Var*)LangElement::find(String::ToString("detailH%d", idx));
      Var* bumpNormal = (Var*)LangElement::find(String::ToString("bumpNormal%d", idx));
      Var* detCoord = (Var*)LangElement::find(String::ToString("detCoord%d", idx));
      if (bumpNormal != NULL)
      {
         meta->addStatement(new GenOp("+(@.xyz * @*max(@.w,0))", bumpNormal, detailH, detCoord));
      }
         
   }
   meta->addStatement(new GenOp(";\r\n"));

   Var* gbNormal = (Var*)LangElement::find("gbNormal");
   if (!gbNormal)
   {
      gbNormal = new Var("gbNormal","float3");
      meta->addStatement(new GenOp("   @ = ", new DecOp(gbNormal)));
   }
   else
      meta->addStatement(new GenOp("   @ = ", gbNormal));
   meta->addStatement(new GenOp("mul(normalize(@),@);\r\n", bumpSum, viewToTangent));
   output = meta;
}
