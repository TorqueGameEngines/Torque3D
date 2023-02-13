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
#include "terrain/glsl/terrFeatureGLSL.h"

#include "terrain/terrFeatureTypes.h"
#include "materials/materialFeatureTypes.h"
#include "materials/materialFeatureData.h"
#include "materials/processedMaterial.h"
#include "gfx/gfxDevice.h"
#include "shaderGen/langElement.h"
#include "shaderGen/shaderOp.h"
#include "shaderGen/featureMgr.h"
#include "shaderGen/shaderGen.h"
#include "core/module.h"

namespace 
{
   void register_glsl_shader_features_for_terrain(GFXAdapterType type)
   {
      if(type != OpenGL)
         return;

      FEATUREMGR->registerFeature( MFT_TerrainBaseMap, new TerrainBaseMapFeatGLSL );
      FEATUREMGR->registerFeature( MFT_TerrainParallaxMap, new NamedFeatureGLSL( "Terrain Parallax Texture" ) );   
      FEATUREMGR->registerFeature( MFT_TerrainDetailMap, new TerrainDetailMapFeatGLSL );
      FEATUREMGR->registerFeature( MFT_TerrainNormalMap, new TerrainNormalMapFeatGLSL );
      FEATUREMGR->registerFeature( MFT_TerrainMacroMap, new NamedFeatureGLSL("TerrainMacroMap Deprecated")); // new TerrainMacroMapFeatGLSL);
      FEATUREMGR->registerFeature( MFT_TerrainLightMap, new TerrainLightMapFeatGLSL );
      FEATUREMGR->registerFeature( MFT_TerrainSideProject, new NamedFeatureGLSL( "Terrain Side Projection" ) );
      FEATUREMGR->registerFeature(MFT_TerrainHeightBlend, new TerrainHeightMapBlendGLSL);
      FEATUREMGR->registerFeature( MFT_TerrainORMMap, new TerrainORMMapFeatGLSL );
      FEATUREMGR->registerFeature( MFT_DeferredTerrainBlankInfoMap, new TerrainBlankInfoMapFeatGLSL );
   }

};

MODULE_BEGIN( TerrainFeatGLSL )

   MODULE_INIT_AFTER( ShaderGen )

   MODULE_INIT
   {      
      SHADERGEN->getFeatureInitSignal().notify(&register_glsl_shader_features_for_terrain);
   }

MODULE_END;


TerrainFeatGLSL::TerrainFeatGLSL()
   : mTorqueDep(ShaderGen::smCommonShaderPath + String("/gl/torque.glsl" ))
   {      
   addDependency( &mTorqueDep );
   }

Var* TerrainFeatGLSL::_getUniformVar( const char *name, const char *type, ConstantSortPosition csp )
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

Var* TerrainFeatGLSL::_getInDetailCoord( Vector<ShaderComponent*> &componentList )
{
   String name( String::ToString( "detCoord%d", getProcessIndex() ) );
   Var *inDet = (Var*)LangElement::find( name );
   
   if ( !inDet )
   {
      ShaderConnector *connectComp = dynamic_cast<ShaderConnector *>( componentList[C_CONNECTOR] );
      
      inDet = connectComp->getElement( RT_TEXCOORD );
      inDet->setName( name );
      inDet->setStructName( "IN" );
      inDet->setType( "vec4" );
   }
   
   return inDet;
}

Var* TerrainFeatGLSL::_getInMacroCoord( Vector<ShaderComponent*> &componentList )
{
   String name( String::ToString( "macroCoord%d", getProcessIndex() ) );
   Var *inDet = (Var*)LangElement::find( name );

   if ( !inDet )
   {
      ShaderConnector *connectComp = dynamic_cast<ShaderConnector *>( componentList[C_CONNECTOR] );

      inDet = connectComp->getElement( RT_TEXCOORD );
      inDet->setName( name );
      inDet->setStructName( "IN" );
      inDet->setType( "vec4" );
   }

   return inDet;
}

Var* TerrainFeatGLSL::_getDetailMapSampler()
{
   String name("detailMapSampler");
   Var* detailMapSampler = (Var*)LangElement::find(name);

   if (!detailMapSampler)
   {
      detailMapSampler = new Var;
      detailMapSampler->setName(name);
      detailMapSampler->setType("sampler2DArray");
      detailMapSampler->uniform = true;
      detailMapSampler->sampler = true;
      detailMapSampler->constNum = Var::getTexUnitNum();
   }

   return detailMapSampler;
}

Var* TerrainFeatGLSL::_getNormalMapSampler()
{
   String name("normalMapSampler");
   Var* normalMapSampler = (Var*)LangElement::find(name);

   if (!normalMapSampler)
   {
      normalMapSampler = new Var;
      normalMapSampler->setName(name);
      normalMapSampler->setType("sampler2DArray");
      normalMapSampler->uniform = true;
      normalMapSampler->sampler = true;
      normalMapSampler->constNum = Var::getTexUnitNum();
   }

   return normalMapSampler;
}

Var* TerrainFeatGLSL::_getOrmMapSampler()
{
   String name("ormMapSampler");
   Var* ormMapSampler = (Var*)LangElement::find(name);

   if (!ormMapSampler)
   {
      ormMapSampler = new Var;
      ormMapSampler->setName(name);
      ormMapSampler->setType("sampler2DArray");
      ormMapSampler->uniform = true;
      ormMapSampler->sampler = true;
      ormMapSampler->constNum = Var::getTexUnitNum();
   }

   return ormMapSampler;
}

Var* TerrainFeatGLSL::_getDetailIdStrengthParallax()
{
   String name(String::ToString("detailIdStrengthParallax", getProcessIndex()));

   Var* detailInfo = (Var*)LangElement::find(name);
   if (!detailInfo)
   {
      detailInfo = new Var;
      detailInfo->setType("vec4");
      detailInfo->setName(name);
      detailInfo->uniform = true;
      detailInfo->constSortPos = cspPotentialPrimitive;
      detailInfo->arraySize = getProcessIndex();
   }

   detailInfo->arraySize = mMax(detailInfo->arraySize, getProcessIndex() + 1);

   return detailInfo;
}

Var* TerrainFeatGLSL::_getMacroIdStrengthParallax()
{
   String name(String::ToString("macroIdStrengthParallax%d", getProcessIndex()));

   Var* detailInfo = (Var*)LangElement::find(name);
   if (!detailInfo)
   {
      detailInfo = new Var;
      detailInfo->setType("vec3");
      detailInfo->setName(name);
      detailInfo->uniform = true;
      detailInfo->constSortPos = cspPotentialPrimitive;
   }

   return detailInfo;
}


void TerrainBaseMapFeatGLSL::processVert( Vector<ShaderComponent*> &componentList, 
                                          const MaterialFeatureData &fd )
{
   MultiLine *meta = new MultiLine;
   output = meta;

   // Generate the incoming texture var.
   Var* inPos = (Var*)LangElement::find("inPosition");
   if (!inPos)
      inPos = (Var*)LangElement::find("position");

   Var* inTex = new Var("texCoord", "vec3");

   Var* oneOverTerrainSize = _getUniformVar("oneOverTerrainSize", "float", cspPass);

   meta->addStatement(new GenOp("   @ = @.xyz * vec3( @, @, @ );\r\n",
      new DecOp(inTex), inPos, oneOverTerrainSize, oneOverTerrainSize, oneOverTerrainSize));

   ShaderConnector *connectComp = dynamic_cast<ShaderConnector *>( componentList[C_CONNECTOR] );

   // Pass the texture coord to the pixel shader.
   Var *outTex = connectComp->getElement( RT_TEXCOORD );
   outTex->setName( "outTexCoord" );
   outTex->setStructName( "OUT" );
   outTex->setType( "vec4" );
   meta->addStatement( new GenOp( "   @.xy = @.xy;\r\n", outTex, inTex ) );

   // If this shader has a side projected layer then we 
   // pass the dot product between the +Y and the normal
   // thru outTexCoord.z and w for use in blending the textures.
   if ( fd.features.hasFeature( MFT_TerrainSideProject ) )
   {
      Var* inNormal = (Var*)LangElement::find("normal");
      meta->addStatement( 
         new GenOp("   @.z = dot( normalize( vec3( @.x, @.y, 0 ) ), vec3( 0, 1, 0 ) );\r\n",
            outTex, inNormal, inNormal));
      meta->addStatement(
         new GenOp("   @.w = 1.0 - dot( normalize( @.xyz ), vec3( 0, 0, 1 ) );\r\n",
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
   Var *inTanget = new Var( "T", "vec3" );
   Var *squareSize = _getUniformVar( "squareSize", "float", cspPass );
   meta->addStatement( new GenOp( "   @ = normalize( vec3( @, 0, @ ) );\r\n", 
      new DecOp( inTanget ), squareSize, inTangentZ ) );

   getOutViewToTangent(componentList, meta, fd);
}

void TerrainBaseMapFeatGLSL::processPix(  Vector<ShaderComponent*> &componentList, 
                                          const MaterialFeatureData &fd )
{
   // grab connector texcoord register
   Var *texCoord = getInTexCoord( "texCoord", "vec4", componentList );

   // create texture var
   Var *diffuseMap = new Var;
   diffuseMap->setType( "sampler2D" );
   diffuseMap->setName( "baseTexMap" );
   diffuseMap->uniform = true;
   diffuseMap->sampler = true;
   diffuseMap->constNum = Var::getTexUnitNum();     // used as texture unit num here

   MultiLine *meta = new MultiLine;

   Var *baseColor = new Var;
   baseColor->setType( "vec4" );
   baseColor->setName( "baseColor" );
   meta->addStatement( new GenOp( "   @ = tex2D( @, @.xy );\r\n", new DecOp( baseColor ), diffuseMap, texCoord ) );

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
      ormConfig = new Var("ORMConfig", "vec4");
      meta->addStatement(new GenOp("   @;\r\n", new DecOp(ormConfig)));
   }

   meta->addStatement(new GenOp("   @ = float4(1.0f/255.0f, 1.0, 1.0, 0.0);\r\n", ormConfig));

   output = meta;

   Var* viewToTangent = getInViewToTangent(componentList);
}

ShaderFeature::Resources TerrainBaseMapFeatGLSL::getResources( const MaterialFeatureData &fd )
{
   Resources res;

   // Sample base texture
   res.numTexReg = 1;
   res.numTex = 1;

   return res;
}

U32 TerrainBaseMapFeatGLSL::getOutputTargets( const MaterialFeatureData &fd ) const
{
   return fd.features[MFT_isDeferred] ? ShaderFeature::RenderTarget2 | ShaderFeature::RenderTarget1 : ShaderFeature::DefaultTarget;
}

TerrainDetailMapFeatGLSL::TerrainDetailMapFeatGLSL()
   :  mTorqueDep(ShaderGen::smCommonShaderPath + String("/gl/torque.glsl" )),
      mTerrainDep(ShaderGen::smCommonShaderPath + String("/terrain/terrain.glsl" ))
      
{
   addDependency( &mTorqueDep );
   addDependency( &mTerrainDep );
}

void TerrainDetailMapFeatGLSL::processVert(  Vector<ShaderComponent*> &componentList, 
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
   Var *eyePos = _getUniformVar( "eyePos", "vec3", cspPotentialPrimitive );

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
      outNegViewTS->setType( "vec3" );
      meta->addStatement( new GenOp( "   @ = tMul( @, vec3( @ - @.xyz ) );\r\n", 
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
   detCoord->setType( "vec4" );

   // Get the detail scale and fade info.
   Var* detScaleAndFade = (Var*)LangElement::find("detailScaleAndFade");
   if (detScaleAndFade == NULL)
   {
      detScaleAndFade = new Var;
      detScaleAndFade->setType("vec4");
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
   // See TerrainBaseMapFeatGLSL::processVert().
   //
   meta->addStatement( new GenOp( "   @.xyz = @ * @.xyx;\r\n", detCoord, inTexCoord, new IndexOp(detScaleAndFade, detailIndex) ) );

   // And sneak the detail fade thru the w detailCoord.
   meta->addStatement(new GenOp("   @.w = ( @.z - @ ) * @.w;\r\n",
      detCoord, new IndexOp(detScaleAndFade, detailIndex), dist, new IndexOp(detScaleAndFade, detailIndex)));

   output = meta;
}

void TerrainDetailMapFeatGLSL::processPix(   Vector<ShaderComponent*> &componentList, 
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
         inNegViewTS->setType( "vec3" );
      }
   
      negViewTS = new Var( "negViewTS", "vec3" );
      meta->addStatement( new GenOp( "   @ = normalize( @ );\r\n", new DecOp( negViewTS ), inNegViewTS ) );
   }

   // Get the layer samples.
   Var *layerSample = (Var*)LangElement::find( "layerSample" );
   if ( !layerSample )
   {
      layerSample = new Var;
      layerSample->setType( "vec4" );
      layerSample->setName( "layerSample" );

      // Get the layer texture var
      Var *layerTex = new Var;
      layerTex->setType( "sampler2D" );
      layerTex->setName( "layerTex" );
      layerTex->uniform = true;
      layerTex->sampler = true;
      layerTex->constNum = Var::getTexUnitNum();

      // Read the layer texture to get the samples.
      meta->addStatement( new GenOp( "   @ = round( tex2D( @, @.xy ) * 255.0f );\r\n", 
                                       new DecOp( layerSample ), layerTex, inTexCoord ) );
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
      // Get the normal map textures.
      Var* normalMapArray = _getNormalMapSampler();

      // Call the library function to do the rest.
      if (fd.features.hasFeature(MFT_IsBC3nm, detailIndex))
      {
         meta->addStatement(new GenOp("   @.xy += parallaxOffsetDxtnm( @, vec3(@.xy, @.x), @, @.z * @ );\r\n",
            detCoord, normalMapArray, detCoord, new IndexOp(detailInfo, detailIndex), negViewTS, new IndexOp(detailInfo, detailIndex), detailBlend));
      }
      else
      {
         meta->addStatement(new GenOp("   @.xy += parallaxOffset( @, vec3(@.xy, @.x), @, @.z * @ );\r\n",
            detCoord, normalMapArray, detCoord, new IndexOp(detailInfo, detailIndex), negViewTS, new IndexOp(detailInfo, detailIndex), detailBlend));
      }
   }

   Var *detailColor = (Var*)LangElement::find(String::ToString("detailColor%d", detailIndex));
   if ( !detailColor )
   {
      detailColor = new Var;
      detailColor->setType( "vec4" );
      detailColor->setName( String::ToString("detailColor%d", detailIndex) );
      meta->addStatement( new GenOp( "   @;\r\n", new DecOp( detailColor ) ) );
   }

   // Get the detail texture.
   Var *detailMapArray = _getDetailMapSampler();

   // If we had a parallax feature... then factor in the parallax
  // amount so that it fades out with the layer blending.
   if (fd.features.hasFeature(MFT_TerrainSideProject, detailIndex))
   {
      meta->addStatement(new GenOp("   @ = ( lerp( tex2D( @, vec3(@.xy, @.x) ), lerp( tex2D( @, vec3(@.yz, @.x) ), tex2D( @, vec3(@.xz, @.x) ), @.z ), @.w) * 2.0 ) - 1.0;\r\n",
         detailColor,
         detailMapArray, detCoord, new IndexOp(detailInfo, detailIndex),
         detailMapArray, detCoord, new IndexOp(detailInfo, detailIndex),
         detailMapArray, detCoord, new IndexOp(detailInfo, detailIndex),
         inTexCoord, inTexCoord));
   }
   else
   {
	   meta->addStatement(new GenOp("   @ = ( tex2D( @, vec3(@.xy, @.x) ) * 2.0 ) - 1.0;\r\n",
		   detailColor, detailMapArray, detCoord, new IndexOp(detailInfo, detailIndex)));
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

         meta->addStatement(new GenOp("   @ = lerp( @, tGetMatrix3Row(@, 2), @ ) );\r\n", gbNormal, gbNormal, viewToTangent, detailBlend));
      }

      ShaderFeature::OutputTarget target = (fd.features[MFT_isDeferred]) ? RenderTarget1 : DefaultTarget;

      Var* outColor = (Var*)LangElement::find(getOutputTargetVarName(target));

      meta->addStatement(new GenOp("      @ += @ * @;\r\n", outColor, detailColor, detailBlend));
   }

   output = meta;
}

ShaderFeature::Resources TerrainDetailMapFeatGLSL::getResources( const MaterialFeatureData &fd )
{
   Resources res;

   if ( getProcessIndex() == 0 )
   {
      // If this is the first detail pass then we 
      // samples from the layer tex.
      res.numTex = 1;
      res.numTexReg = 1;

      // Add Detail TextureArray
      res.numTex += 1;
      res.numTexReg += 1;
   }

   return res;
}

U32 TerrainDetailMapFeatGLSL::getOutputTargets( const MaterialFeatureData &fd ) const
{
   return fd.features[MFT_isDeferred] ? ShaderFeature::RenderTarget1 : ShaderFeature::DefaultTarget;
}


TerrainMacroMapFeatGLSL::TerrainMacroMapFeatGLSL()
   :  mTorqueDep(ShaderGen::smCommonShaderPath + String("/gl/torque.glsl" )),
      mTerrainDep(ShaderGen::smCommonShaderPath + String("/terrain/terrain.glsl" ))
      
{
   addDependency( &mTorqueDep );
   addDependency( &mTerrainDep );
}


void TerrainMacroMapFeatGLSL::processVert(  Vector<ShaderComponent*> &componentList, 
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
   Var *eyePos = _getUniformVar( "eyePos", "vec3", cspPotentialPrimitive );

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
   outTex->setType( "vec4" );

   // Get the detail scale and fade info.
   Var *macroScaleAndFade = new Var;
   macroScaleAndFade->setType( "vec4" );
   macroScaleAndFade->setName( String::ToString( "macroScaleAndFade%d", detailIndex ) );
   macroScaleAndFade->uniform = true;
   macroScaleAndFade->constSortPos = cspPotentialPrimitive;

   // Setup the detail coord.
   meta->addStatement( new GenOp( "   @.xyz = @ * @.xyx;\r\n", outTex, inTex, macroScaleAndFade ) );

   // And sneak the detail fade thru the w detailCoord.
   meta->addStatement( new GenOp( "   @.w =  ( @.z - @ ) * @.w;\r\n",  outTex, macroScaleAndFade, dist, macroScaleAndFade ) );   

   output = meta;
}


void TerrainMacroMapFeatGLSL::processPix(   Vector<ShaderComponent*> &componentList, 
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
         inNegViewTS->setType( "vec3" );
      }

      negViewTS = new Var( "negViewTS", "vec3" );
      meta->addStatement( new GenOp( "   @ = normalize( @ );\r\n", new DecOp( negViewTS ), inNegViewTS ) );
   }

   // Get the layer samples.
   Var *layerSample = (Var*)LangElement::find( "layerSample" );
   if ( !layerSample )
   {
      layerSample = new Var;
      layerSample->setType( "vec4" );
      layerSample->setName( "layerSample" );

      // Get the layer texture var
      Var *layerTex = new Var;
      layerTex->setType( "sampler2D" );
      layerTex->setName( "macrolayerTex" );
      layerTex->uniform = true;
      layerTex->sampler = true;
      layerTex->constNum = Var::getTexUnitNum();

      // Read the layer texture to get the samples.
      meta->addStatement( new GenOp( "   @ = round( tex2D( @, @.xy ) * 255.0f );\r\n", 
                                       new DecOp( layerSample ), layerTex, inTex ) );
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
   Var *detCoord = _getInMacroCoord( componentList );

   // Get the detail id.
   Var *detailInfo = _getMacroIdStrengthParallax();

   // Create the detail blend var.
   Var *detailBlend = new Var;
   detailBlend->setType( "float" );
   detailBlend->setName( String::ToString( "macroBlend%d", detailIndex ) );

   // Calculate the blend for this detail texture.
   meta->addStatement( new GenOp( "   @ = calcBlend( @.x, @.xy, @, @ );\r\n", 
                                    new DecOp( detailBlend ), detailInfo, inTex, layerSize, layerSample ) );

   // Check to see if we have a gbuffer normal.
   Var* gbNormal = (Var*)LangElement::find("gbNormal");

   // If we have a gbuffer normal and we don't have a
   // normal map feature then we need to lerp in a 
   // default normal else the normals below this layer
   // will show thru.
   if (gbNormal &&
      !fd.features.hasFeature(MFT_TerrainNormalMap, detailIndex))
   {
      Var *viewToTangent = getInViewToTangent( componentList );
      
      meta->addStatement( new GenOp( "   @ = lerp( @, @[2], min( @, @.w ) );\r\n", 
         gbNormal, gbNormal, viewToTangent, detailBlend, detCoord ) );
   }

   Var *detailColor = (Var*)LangElement::find( "macroColor" ); 
   if ( !detailColor )
   {
      detailColor = new Var;
      detailColor->setType( "vec4" );
      detailColor->setName( "macroColor" );
      meta->addStatement( new GenOp( "   @;\r\n", new DecOp( detailColor ) ) );
   }

   // Get the detail texture.
   Var *detailMapArray = new Var;
   detailMapArray->setType( "sampler2D" );
   detailMapArray->setName( String::ToString( "macroMap%d", detailIndex ) );
   detailMapArray->uniform = true;
   detailMapArray->sampler = true;
   detailMapArray->constNum = Var::getTexUnitNum();     // used as texture unit num here

   meta->addStatement( new GenOp( "   if ( @ > 0.0f )\r\n", detailBlend ) );

   meta->addStatement( new GenOp( "   {\r\n" ) );

   // Note that we're doing the standard greyscale detail 
   // map technique here which can darken and lighten the 
   // diffuse texture.
   //
   // We take two color samples and lerp between them for
   // side projection layers... else a single sample.
   //
   if (fd.features.hasFeature(MFT_TerrainSideProject, detailIndex))
   {
      meta->addStatement(new GenOp("   @ = ( lerp( tex2D( @, vec3(@.xy, @.x) ), lerp( tex2D( @, vec3(@.yz, @.x) ), tex2D( @, vec3(@.xz, @.x) ), @.z ), @.w) * 2.0 ) - 1.0;\r\n",
         detailColor,
         detailMapArray, detCoord, new IndexOp(detailInfo, detailIndex),
         detailMapArray, detCoord, new IndexOp(detailInfo, detailIndex),
         detailMapArray, detCoord, new IndexOp(detailInfo, detailIndex),
         inTex, inTex));
   }
   else
   {
      meta->addStatement( new GenOp( "      @ = ( tex2D( @, @.xy ) * 2.0 ) - 1.0;\r\n", 
                                       detailColor, detailMapArray, detCoord) );
   }

   meta->addStatement( new GenOp( "      @ *= @.y * @.w;\r\n", detailColor, detailInfo, detCoord) );

   ShaderFeature::OutputTarget target = (fd.features[MFT_isDeferred]) ? RenderTarget1 : DefaultTarget;

   Var *outColor = (Var*)LangElement::find( getOutputTargetVarName(target) );

   meta->addStatement(new GenOp("      @ += @ * @;\r\n",
                                    outColor, detailColor, detailBlend));

   meta->addStatement( new GenOp( "   }\r\n" ) );

   output = meta;
}

ShaderFeature::Resources TerrainMacroMapFeatGLSL::getResources( const MaterialFeatureData &fd )
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

U32 TerrainMacroMapFeatGLSL::getOutputTargets( const MaterialFeatureData &fd ) const
{
   return fd.features[MFT_isDeferred] ? ShaderFeature::RenderTarget1 : ShaderFeature::DefaultTarget;
}

void TerrainNormalMapFeatGLSL::processVert(  Vector<ShaderComponent*> &componentList, 
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

void TerrainNormalMapFeatGLSL::processPix(   Vector<ShaderComponent*> &componentList, 
                                             const MaterialFeatureData &fd )
{
   // We only need to process normals during the deferred.
   if (!fd.features.hasFeature(MFT_DeferredConditioner))
      return;

   MultiLine *meta = new MultiLine;

   const S32 normalIndex = getProcessIndex();

   Var *detailBlend = (Var*)LangElement::find( String::ToString( "detailBlend%d", normalIndex ) );
   AssertFatal( detailBlend, "The detail blend is missing!" );

   // Get the normal map texture.
   Var *normalMapArray = _getNormalMapSampler();

   /// Get the texture coord.
   Var* inDet = _getInDetailCoord(componentList);
   Var* inTex = getVertTexCoord("texCoord");
   Var* detailInfo = _getDetailIdStrengthParallax();

   // Sample the normal map.
   //
   // We take two normal samples and lerp between them for
   // side projection layers... else a single sample.
   LangElement* texOp;
   if (fd.features.hasFeature(MFT_TerrainSideProject, normalIndex))
   {
      texOp = new GenOp("lerp( tex2D( @, float3(@.xy, @.x) ), lerp( tex2D( @, float3(@.yz, @.x) ), tex2D( @, float3(@.xz, @.x) ), @.z ), @.w )",
         normalMapArray, inDet, new IndexOp(detailInfo, normalIndex),
         normalMapArray, inDet, new IndexOp(detailInfo, normalIndex),
         normalMapArray, inDet, new IndexOp(detailInfo, normalIndex),
         inTex, inTex);
   }
   else
      texOp = new GenOp( String::ToString("tex2D(@, vec3(@.xy, @.x))", normalIndex), normalMapArray, inDet, new IndexOp(detailInfo, normalIndex));

   // create bump normal
   Var* bumpNorm = new Var;
   bumpNorm->setName(String::ToString("bumpNormal%d", normalIndex));
   bumpNorm->setType("vec4");

   LangElement* bumpNormDecl = new DecOp(bumpNorm);
   meta->addStatement(expandNormalMap(texOp, bumpNormDecl, bumpNorm, fd));

   if (!fd.features.hasFeature(MFT_TerrainNormalMap))
   {
      Var* viewToTangent = getInViewToTangent(componentList);

      // This var is read from GBufferConditionerGLSL and 
      // used in the deferred output.
      Var* gbNormal = (Var*)LangElement::find("gbNormal");
      if (!gbNormal)
      {
         gbNormal = new Var;
         gbNormal->setName("gbNormal");
         gbNormal->setType("vec3");
         meta->addStatement(new GenOp("   @ = tGetMatrix3Row(@, 2);\r\n", new DecOp(gbNormal), viewToTangent));
      }

      // If we're using SM 3.0 then take advantage of 
      // dynamic branching to skip layers per-pixel.
      if (GFX->getPixelShaderVersion() >= 3.0f)
         meta->addStatement(new GenOp("   if ( @ > 0.0f )\r\n", detailBlend));

      meta->addStatement(new GenOp("   {\r\n"));

      // Normalize is done later... 
      // Note: The reverse mul order is intentional. Affine matrix.
      meta->addStatement(new GenOp("      @ = lerp( @, tMul( @.xyz, @ ), min( @, @.w ) );\r\n",
         gbNormal, gbNormal, bumpNorm, viewToTangent, detailBlend, inDet));

      // End the conditional block.
      meta->addStatement(new GenOp("   }\r\n"));
   }

   output = meta;
}

ShaderFeature::Resources TerrainNormalMapFeatGLSL::getResources( const MaterialFeatureData &fd )
{
   Resources res;

   if (!fd.features.hasFeature(MFT_DeferredConditioner))
   {
      return  res;
   }

   S32 featureIndex = 0, firstNormalMapIndex = 0;
   for (int idx = 0; idx < fd.features.getCount(); ++idx) {
      const FeatureType& type = fd.features.getAt(idx, &featureIndex);
      if (type == MFT_TerrainNormalMap) {
         firstNormalMapIndex = getMin(firstNormalMapIndex, featureIndex);
      }
   }

   // We only need to process normals during the deferred.
   if (getProcessIndex() == firstNormalMapIndex)
   {
      // Normal Texture Array
      res.numTexReg += 1;
      res.numTex += 1;
   }

   return res;
}

void TerrainLightMapFeatGLSL::processPix( Vector<ShaderComponent*> &componentList, 
                                          const MaterialFeatureData &fd )
{
   // grab connector texcoord register
   Var *inTex = (Var*)LangElement::find( "texCoord" );
   if ( !inTex )
      return;

   // Get the lightmap texture.
   Var *lightMap = new Var;
   lightMap->setType( "sampler2D" );
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
      lightMask = new Var( "lightMask", "vec4" );
      meta->addStatement( new GenOp( "   @ = vec4(1);\r\n", new DecOp( lightMask ) ) );
   }

   meta->addStatement( new GenOp( "   @[0] = tex2D( @, @.xy ).r;\r\n", lightMask, lightMap, inTex ) );
   output = meta;
}

ShaderFeature::Resources TerrainLightMapFeatGLSL::getResources( const MaterialFeatureData &fd )
{
   Resources res; 
   res.numTex = 1;
   return res;
}

void TerrainORMMapFeatGLSL::processVert(Vector<ShaderComponent*> &componentList,
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

U32 TerrainORMMapFeatGLSL::getOutputTargets(const MaterialFeatureData &fd) const
{
	return fd.features[MFT_isDeferred] ? ShaderFeature::RenderTarget2 : ShaderFeature::RenderTarget1;
}

void TerrainORMMapFeatGLSL::processPix(Vector<ShaderComponent*> &componentList,
	const MaterialFeatureData &fd)
{
	/// Get the texture coord.
	Var *inDet = _getInDetailCoord(componentList);
	Var *inTex = getVertTexCoord("texCoord");
   Var* detailInfo = _getDetailIdStrengthParallax();

	const S32 compositeIndex = getProcessIndex();
	Var *ormConfigMap = _getOrmMapSampler();
	// Sample the normal map.
	//
	// We take two normal samples and lerp between them for
	// side projection layers... else a single sample.
	LangElement *texOp;
	
	if (fd.features.hasFeature(MFT_TerrainSideProject, compositeIndex))
	{
      texOp = new GenOp("lerp( tex2D( @, vec3(@.xy, @.x) ), lerp( tex2D( @, vec3(@.yz, @.x) ), tex2D( @, vec3(@.xz, @.x) ), @.z ), @.w )",
            ormConfigMap, inDet, new IndexOp(detailInfo, compositeIndex),
            ormConfigMap, inDet, new IndexOp(detailInfo, compositeIndex),
            ormConfigMap, inDet, new IndexOp(detailInfo, compositeIndex),
            inTex, inTex);
	}
	else
		texOp = new GenOp("tex2D(@, vec3(@.xy, @.x))", ormConfigMap, inDet, new IndexOp(detailInfo, compositeIndex));

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
         ormConfig = new Var("ORMConfig", "vec4");
         meta->addStatement(new GenOp("   @;\r\n", new DecOp(ormConfig)));
      }
   }
   if (compositeIndex == 0)
   {
      meta->addStatement(new GenOp("   @ = vec4(1.0f/255.0f, 1.0, 1.0, 0.0);\r\n", ormConfig));
   }

	Var *detailBlend = (Var*)LangElement::find(String::ToString("detailBlend%d", compositeIndex));
	AssertFatal(detailBlend, "The detail blend is missing!");

	String matinfoName(String::ToString("matinfoCol%d", compositeIndex));
	Var *matinfoCol = new Var(matinfoName, "vec3");

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

ShaderFeature::Resources TerrainORMMapFeatGLSL::getResources(const MaterialFeatureData &fd)
{
   Resources res;
   res.numTex = 1;
   return res;
}

// reminder, the matinfo buffer is flags, smooth, ao, metal
void TerrainBlankInfoMapFeatGLSL::processPix(Vector<ShaderComponent*> &componentList,
   const MaterialFeatureData &fd)
{
   S32 compositeIndex = getProcessIndex();

   MultiLine* meta = new MultiLine;   Var* ormConfig;
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
         ormConfig = new Var("ORMConfig", "vec4");
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
      meta->addStatement(new GenOp("   @.gba += vec3(@, @, 0.0);\r\n", ormConfig, detailBlend, detailBlend));
   }

   output = meta;
}

void TerrainHeightMapBlendGLSL::processVert(
    Vector<ShaderComponent *> &componentList, const MaterialFeatureData &fd) {
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

void TerrainHeightMapBlendGLSL::processPix(Vector<ShaderComponent*>& componentList,
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

   Var* heightRange = new Var("heightRange", "vec2");
   meta->addStatement(new GenOp("   @ = vec2(2.0f,0);//x=min, y=max\r\n", new DecOp(heightRange)));
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
         meta->addStatement(new GenOp("   @ = vec2(min(@.x,@),max(@.y,@));\r\n", heightRange, heightRange, detailH, heightRange, detailH));
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
         meta->addStatement(new GenOp("(vec3(1.0, 1.0, 0.0) * @)", detailH));
      }
   }

   meta->addStatement(new GenOp(");\r\n"));

    // Compute normals
   Var* viewToTangent = getInViewToTangent(componentList);
   Var* bumpSum = new Var("bumpNorm", "vec3");

   meta->addStatement(new GenOp("   @ = vec3(0, 0, 1)", new DecOp(bumpSum)));
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
      gbNormal = new Var("gbNormal","vec3");
      meta->addStatement(new GenOp("   @ = ", new DecOp(gbNormal)));
   }
   else
      meta->addStatement(new GenOp("   @ = ", gbNormal));
   meta->addStatement(new GenOp("tMul(normalize(@),@);\r\n", bumpSum, viewToTangent));
   output = meta;
}
