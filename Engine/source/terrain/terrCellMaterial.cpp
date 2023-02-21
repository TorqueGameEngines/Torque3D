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
#include "terrain/terrCellMaterial.h"


#include "core/util/safeRelease.h"
#include "terrain/terrData.h"
#include "terrain/terrCell.h"
#include "materials/materialFeatureTypes.h"
#include "materials/materialManager.h"
#include "terrain/terrFeatureTypes.h"
#include "terrain/terrMaterial.h"
#include "renderInstance/renderDeferredMgr.h"
#include "shaderGen/shaderGen.h"
#include "shaderGen/featureMgr.h"
#include "scene/sceneRenderState.h"
#include "materials/sceneData.h"
#include "gfx/util/screenspace.h"
#include "lighting/advanced/advancedLightBinManager.h"

S32 sgMaxTerrainMaterialsPerPass = 32;

AFTER_MODULE_INIT( MaterialManager )
{
   Con::NotifyDelegate callabck( &TerrainCellMaterial::_updateDefaultAnisotropy );
   Con::addVariableNotify( "$pref::Video::defaultAnisotropy", callabck );
}

Vector<TerrainCellMaterial*> TerrainCellMaterial::smAllMaterials;

Vector<String> _initSamplerNames()
{
   Vector<String> samplerNames;
   samplerNames.push_back("$baseTexMap");
   samplerNames.push_back("$layerTex");
   samplerNames.push_back("$lightMapTex");
   samplerNames.push_back("$lightInfoBuffer");
   samplerNames.push_back("$normalMapSampler");
   samplerNames.push_back("$detailMapSampler");
   samplerNames.push_back("$macroMapSampler");
   samplerNames.push_back("$ormMapSampler"); 

   return samplerNames;
}


const Vector<String> TerrainCellMaterial::mSamplerNames = _initSamplerNames();

TerrainCellMaterial::TerrainCellMaterial()
   :  mTerrain( NULL ),
      mDeferredMat( NULL ),
      mReflectMat( NULL ),
      mShader( NULL ),
      mCurrPass( 0 ),
      mMaterials( 0 )
{
   smAllMaterials.push_back( this );
}

TerrainCellMaterial::~TerrainCellMaterial()
{
   SAFE_DELETE( mDeferredMat );
   SAFE_DELETE( mReflectMat );   
   smAllMaterials.remove( this );

   T3D::for_each(mMaterialInfos.begin(), mMaterialInfos.end(), T3D::delete_pointer());
   mMaterialInfos.clear();
}

void TerrainCellMaterial::_updateDefaultAnisotropy()
{
   // TODO: We need to split the stateblock initialization
   // from the shader constant lookup and pass setup in a 
   // future version of terrain materials.
   //
   // For now use some custom code in a horrible loop to 
   // change the anisotropy directly and fast.
   //

   const U32 maxAnisotropy = MATMGR->getDefaultAnisotropy();

   Vector<TerrainCellMaterial*>::iterator iter = smAllMaterials.begin();
   for ( ; iter != smAllMaterials.end(); iter++ )
   {
      // Start from the existing state block.
      GFXStateBlockDesc desc = (*iter)->mStateBlock->getDesc();

      if ((*iter)->mDetailTexArrayConst->isValid())
      {
         const S32 sampler = (*iter)->mDetailTexArrayConst->getSamplerRegister();

         if (maxAnisotropy > 1)
         {
            desc.samplers[sampler].minFilter = GFXTextureFilterAnisotropic;
            desc.samplers[sampler].maxAnisotropy = maxAnisotropy;
         }
         else
            desc.samplers[sampler].minFilter = GFXTextureFilterLinear;
      }

      if ((*iter)->mMacroTexArrayConst->isValid())
      {
         const S32 sampler = (*iter)->mMacroTexArrayConst->getSamplerRegister();

         if (maxAnisotropy > 1)
         {
            desc.samplers[sampler].minFilter = GFXTextureFilterAnisotropic;
            desc.samplers[sampler].maxAnisotropy = maxAnisotropy;
         }
         else
            desc.samplers[sampler].minFilter = GFXTextureFilterLinear;
      }

      if ((*iter)->mNormalTexArrayConst->isValid())
      {
         const S32 sampler = (*iter)->mNormalTexArrayConst->getSamplerRegister();

         if (maxAnisotropy > 1)
         {
            desc.samplers[sampler].minFilter = GFXTextureFilterAnisotropic;
            desc.samplers[sampler].maxAnisotropy = maxAnisotropy;
         }
         else
            desc.samplers[sampler].minFilter = GFXTextureFilterLinear;
      }

      if ((*iter)->mOrmTexArrayConst->isValid())
      {
         const S32 sampler = (*iter)->mOrmTexArrayConst->getSamplerRegister();

         if (maxAnisotropy > 1)
         {
            desc.samplers[sampler].minFilter = GFXTextureFilterAnisotropic;
            desc.samplers[sampler].maxAnisotropy = maxAnisotropy;
         }
         else
            desc.samplers[sampler].minFilter = GFXTextureFilterLinear;
      }

      // Set the updated stateblock.
      desc.setCullMode(GFXCullCCW);
      (*iter)->mStateBlock = GFX->createStateBlock(desc);

      //reflection
      desc.setCullMode(GFXCullCW);
      (*iter)->mReflectionStateBlock = GFX->createStateBlock(desc);

      // Create the wireframe state blocks.
      GFXStateBlockDesc wireframe(desc);
      wireframe.fillMode = GFXFillWireframe;
      wireframe.setCullMode(GFXCullCCW);
      (*iter)->mWireframeStateBlock = GFX->createStateBlock(wireframe);
   }

}

void TerrainCellMaterial::setTransformAndEye(   const MatrixF &modelXfm, 
                                                const MatrixF &viewXfm,
                                                const MatrixF &projectXfm,
                                                F32 farPlane )
{
   PROFILE_SCOPE( TerrainCellMaterial_SetTransformAndEye );

   MatrixF modelViewProj = projectXfm * viewXfm * modelXfm;
  
   MatrixF invViewXfm( viewXfm );
   invViewXfm.inverse();
   Point3F eyePos = invViewXfm.getPosition();
   
   MatrixF invModelXfm( modelXfm );
   invModelXfm.inverse();

   Point3F objEyePos = eyePos;
   invModelXfm.mulP( objEyePos );
   
   VectorF vEye = invViewXfm.getForwardVector();
   vEye.normalize( 1.0f / farPlane );

   mConsts->setSafe(mModelViewProjConst, modelViewProj);

   if (mViewToObjConst->isValid() || mWorldViewOnlyConst->isValid())
   {
      MatrixF worldViewOnly = viewXfm * modelXfm;

      mConsts->setSafe(mWorldViewOnlyConst, worldViewOnly);

      if (mViewToObjConst->isValid())
      {
         worldViewOnly.affineInverse();
         mConsts->set(mViewToObjConst, worldViewOnly);
      }
   }

   mConsts->setSafe(mEyePosWorldConst, eyePos);
   mConsts->setSafe(mEyePosConst, objEyePos);
   mConsts->setSafe(mObjTransConst, modelXfm);
   mConsts->setSafe(mWorldToObjConst, invModelXfm);
   mConsts->setSafe(mVEyeConst, vEye);
}

TerrainCellMaterial* TerrainCellMaterial::getDeferredMat()
{
   if ( !mDeferredMat )
   {
      mDeferredMat = new TerrainCellMaterial();
      mDeferredMat->init( mTerrain, mMaterials, true, false, mMaterials == 0 );
   }

   return mDeferredMat;
}

TerrainCellMaterial* TerrainCellMaterial::getReflectMat()
{
   if ( !mReflectMat )
   {
      mReflectMat = new TerrainCellMaterial();
      mReflectMat->init( mTerrain, mMaterials, false, true, true );
   }

   return mReflectMat;
}

void TerrainCellMaterial::init(  TerrainBlock *block,
                                 U64 activeMaterials, 
                                 bool deferredMat,
                                 bool reflectMat,
                                 bool baseOnly )
{
   // This isn't allowed for now.
   AssertFatal( !( deferredMat && reflectMat ), "TerrainCellMaterial::init - We shouldn't get deferred and reflection in the same material!" );

   mTerrain = block;
   mMaterials = activeMaterials;

   mMaterialInfos.clear();
   for ( U32 i = 0; i < 64; i++ )
   {
      if ( !( mMaterials & ((U64)1 << i ) ) )
         continue;

      TerrainMaterial *mat = block->getMaterial( i );

      MaterialInfo *info = new MaterialInfo();
      info->layerId = i;
      info->mat = mat;
      mMaterialInfos.push_back(info);
   }

   if (!_initShader(deferredMat,
                     reflectMat,
                     baseOnly))
   {
      Con::errorf("TerrainCellMaterial::init - Failed to init shader!");

      T3D::for_each(mMaterialInfos.begin(), mMaterialInfos.end(), T3D::delete_pointer());
      mMaterialInfos.clear();
      return;
   }

   // If we have attached mats then update them too.
   if ( mDeferredMat )
      mDeferredMat->init( mTerrain, mMaterials, true, false, baseOnly );
   if ( mReflectMat )
      mReflectMat->init( mTerrain, mMaterials, false, true, baseOnly );
}

bool TerrainCellMaterial::_initShader(bool deferredMat,
   bool reflectMat,
   bool baseOnly)
{
   if (GFX->getPixelShaderVersion() < 3.0f)
      baseOnly = true;

   // NOTE: At maximum we only try to combine sgMaxTerrainMaterialsPerPass materials 
   // into a single pass.  This is sub-optimal for the simplest
   // cases, but the most common case results in much fewer
   // shader generation failures and permutations leading to
   // faster load time and less hiccups during gameplay.
   U32 matCount = getMin(sgMaxTerrainMaterialsPerPass, mMaterialInfos.size());

   Vector<GFXTexHandle> normalMaps;

   // See if we're currently running under the
   // basic lighting manager.
   //
   // TODO: This seems ugly... we should trigger
   // features like this differently in the future.
   //
   bool useBLM = String::compare(LIGHTMGR->getId(), "BLM") == 0;

   // Do we need to disable normal mapping?
   const bool disableNormalMaps = MATMGR->getExclusionFeatures().hasFeature(MFT_NormalMap) || useBLM;

   // How about parallax?
   const bool disableParallaxMaps = GFX->getPixelShaderVersion() < 3.0f ||
      MATMGR->getExclusionFeatures().hasFeature(MFT_Parallax);

   // Has advanced lightmap support been enabled for deferred.
   bool advancedLightmapSupport = false;
   if (deferredMat)
   {
      // This sucks... but it works.
      AdvancedLightBinManager* lightBin;
      if (Sim::findObject("AL_LightBinMgr", lightBin))
         advancedLightmapSupport = lightBin->MRTLightmapsDuringDeferred();
   }

   // Loop till we create a valid shader!
   while (true)
   {
      FeatureSet features;
      features.addFeature(MFT_VertTransform);
      features.addFeature(MFT_TerrainBaseMap);

      if (deferredMat)
      {
         features.addFeature(MFT_EyeSpaceDepthOut);
         features.addFeature(MFT_DeferredConditioner);
         features.addFeature(MFT_isDeferred);

         if (advancedLightmapSupport)
            features.addFeature(MFT_RenderTarget3_Zero);
      }
      else
      {
         features.addFeature(MFT_RTLighting);

         // The HDR feature is always added... it will compile out
         // if HDR is not enabled in the engine.
         features.addFeature(MFT_HDROut);
      }

      // Enable lightmaps and fogging if we're in BL.
      if (reflectMat || useBLM)
      {
         features.addFeature(MFT_Fog);
         features.addFeature(MFT_ForwardShading);
      }
      if (useBLM)
         features.addFeature(MFT_TerrainLightMap);

      normalMaps.clear();

      S32 featureIndex = 0;

      // Now add all the material layer features.
      for (U32 i = 0; i < matCount && !baseOnly; i++)
      {
         TerrainMaterial* mat = mMaterialInfos[i]->mat;

         if (mat == NULL)
            continue;

         // We only include materials that 
         // have more than a base texture.
         if (!(mat->DetailMapValid() && mat->getDetailSize() > 0 && mat->getDetailDistance()>0))
            continue;

         if (deferredMat)
            features.addFeature(MFT_isDeferred, featureIndex);
         features.addFeature(MFT_TerrainDetailMap, featureIndex);

         // check for macro detail texture
         if (mat->MacroMapValid() && mat->getMacroSize() > 0 && mat->getMacroDistance() > 0)
         {
            features.addFeature(MFT_TerrainMacroMap, featureIndex);
         }

         if (mat->ORMConfigMapValid())
         {
            features.addFeature(MFT_TerrainORMMap, featureIndex);
         }
         else
         {
            features.addFeature(MFT_DeferredTerrainBlankInfoMap, featureIndex);
         }
         
         if (mat->getInvertRoughness())
            features.addFeature(MFT_InvertRoughness, featureIndex);


         // Skip normal maps if we need to.
         if (!disableNormalMaps && mat->NormalMapValid())
         {
            normalMaps.increment();
            features.addFeature(MFT_TerrainNormalMap, featureIndex);

            normalMaps.last() = mat->getNormalMapResource();

            GFXFormat normalFmt = normalMaps.last().getFormat();
            if (normalFmt == GFXFormatBC3)
               features.addFeature(MFT_IsBC3nm, featureIndex);
            else if (normalFmt == GFXFormatBC5)
               features.addFeature(MFT_IsBC5nm, featureIndex);

            // Do we need and can we do parallax mapping?
            if (!disableParallaxMaps &&
               mat->getParallaxScale() > 0.0f &&
               !mat->useSideProjection())
               features.addFeature(MFT_TerrainParallaxMap, featureIndex);
         }

         // Is this layer got side projection?
         if (mat->useSideProjection())
            features.addFeature(MFT_TerrainSideProject, featureIndex);

         featureIndex++;
      }

      // New blending
      if (matCount > 0 && !Con::getBoolVariable("$Terrain::LerpBlend", false))
      {
         features.addFeature(MFT_TerrainHeightBlend);
      }

      MaterialFeatureData featureData;
      featureData.features = features;
      featureData.materialFeatures = features;

      // Check to see how many vertex shader output 
      // registers we're gonna need.
      U32 numTex = 0;
      U32 numTexReg = 0;
      for (U32 i = 0; i < features.getCount(); i++)
      {
         S32 index;
         const FeatureType& type = features.getAt(i, &index);
         ShaderFeature* sf = FEATUREMGR->getByType(type);
         if (!sf)
            continue;

         sf->setProcessIndex(index);
         ShaderFeature::Resources res = sf->getResources(featureData);

         numTex += res.numTex;
         numTexReg += res.numTexReg;
      }

      // Can we build the shader?
      //
      // NOTE: The 10 is sort of an abitrary SM 3.0 
      // limit.  Its really supposed to be 11, but that
      // always fails to compile so far.
      //
      if (numTex < GFX->getNumSamplers() &&
         numTexReg <= 10)
      {
         // NOTE: We really shouldn't be getting errors building the shaders,
         // but we can generate more instructions than the ps_2_x will allow.
         //
         // There is no way to deal with this case that i know of other than
         // letting the compile fail then recovering by trying to build it
         // with fewer materials.
         //
         // We normally disable the shader error logging so that the user 
         // isn't fooled into thinking there is a real bug.  That is until
         // we get down to a single material.  If a single material case
         // fails it means it cannot generate any passes at all!
         const bool logErrors = true;// matCount == 1;
         GFXShader::setLogging(logErrors, true);

         mShader = SHADERGEN->getShader(featureData, getGFXVertexFormat<TerrVertex>(), NULL, mSamplerNames);
      }

      // If we got a shader then we can continue.
      if (mShader)
         break;

      // If the material count is already 1 then this
      // is a real shader error... give up!
      if (matCount <= 1)
         return false;

      // If we failed we next try half the input materials
      // so that we can more quickly arrive at a valid shader.
      matCount -= matCount / 2;
   }

   // Setup the constant buffer.
   mConsts = mShader->allocConstBuffer();

   // Prepare the basic constants.
   mModelViewProjConst = mShader->getShaderConstHandle("$modelview");
   mWorldViewOnlyConst = mShader->getShaderConstHandle("$worldViewOnly");
   mViewToObjConst = mShader->getShaderConstHandle("$viewToObj");
   mEyePosWorldConst = mShader->getShaderConstHandle("$eyePosWorld");
   mEyePosConst = mShader->getShaderConstHandle("$eyePos");
   mVEyeConst = mShader->getShaderConstHandle("$vEye");
   mLayerSizeConst = mShader->getShaderConstHandle("$layerSize");
   mObjTransConst = mShader->getShaderConstHandle("$objTrans");
   mWorldToObjConst = mShader->getShaderConstHandle("$worldToObj");
   mLightInfoBufferConst = mShader->getShaderConstHandle("$lightInfoBuffer");
   mBaseTexMapConst = mShader->getShaderConstHandle("$baseTexMap");
   mLayerTexConst = mShader->getShaderConstHandle("$layerTex");
   mFogDataConst = mShader->getShaderConstHandle("$fogData");
   mFogColorConst = mShader->getShaderConstHandle("$fogColor");
   mLightMapTexConst = mShader->getShaderConstHandle("$lightMapTex");
   mOneOverTerrainSizeConst = mShader->getShaderConstHandle("$oneOverTerrainSize");
   mSquareSizeConst = mShader->getShaderConstHandle("$squareSize");
   mBlendDepthConst = mShader->getShaderConstHandle("$baseBlendDepth");

   mLightParamsConst = mShader->getShaderConstHandle("$rtParamslightInfoBuffer");

   // Now prepare the basic stateblock.
   GFXStateBlockDesc desc;

   // We write to the zbuffer if this is a deferred
   // material or if the deferred is disabled.
   desc.setZReadWrite(true, !MATMGR->getDeferredEnabled() ||
      deferredMat ||
      reflectMat);

   desc.samplersDefined = true;
   if (mBaseTexMapConst->isValid())
      desc.samplers[mBaseTexMapConst->getSamplerRegister()] = GFXSamplerStateDesc::getWrapLinear();

   if (mLayerTexConst->isValid())
      desc.samplers[mLayerTexConst->getSamplerRegister()] = GFXSamplerStateDesc::getClampPoint();

   if (mLightInfoBufferConst->isValid())
      desc.samplers[mLightInfoBufferConst->getSamplerRegister()] = GFXSamplerStateDesc::getClampPoint();

   if (mLightMapTexConst->isValid())
      desc.samplers[mLightMapTexConst->getSamplerRegister()] = GFXSamplerStateDesc::getWrapLinear();

   const U32 maxAnisotropy = MATMGR->getDefaultAnisotropy();

   mDetailInfoVArrayConst = mShader->getShaderConstHandle("$detailScaleAndFade");
   mDetailInfoPArrayConst = mShader->getShaderConstHandle("$detailIdStrengthParallax");
   mMacroInfoVArrayConst = mShader->getShaderConstHandle("$macroScaleAndFade");
   mMacroInfoPArrayConst = mShader->getShaderConstHandle("$macroIdStrengthParallax");

   mDetailTexArrayConst = mShader->getShaderConstHandle("$detailMapSampler");
   if (mDetailTexArrayConst->isValid())
   {
      const S32 sampler = mDetailTexArrayConst->getSamplerRegister();

      desc.samplers[sampler] = GFXSamplerStateDesc::getWrapLinear();
      desc.samplers[sampler].magFilter = GFXTextureFilterLinear;
      desc.samplers[sampler].mipFilter = GFXTextureFilterLinear;

      if (maxAnisotropy > 1)
      {
         desc.samplers[sampler].minFilter = GFXTextureFilterAnisotropic;
         desc.samplers[sampler].maxAnisotropy = maxAnisotropy;
      }
      else
         desc.samplers[sampler].minFilter = GFXTextureFilterLinear;
   }

   mMacroTexArrayConst = mShader->getShaderConstHandle("$macroMapSampler");
   if (mMacroTexArrayConst->isValid())
   {
      const S32 sampler = mMacroTexArrayConst->getSamplerRegister();

      desc.samplers[sampler] = GFXSamplerStateDesc::getWrapLinear();
      desc.samplers[sampler].magFilter = GFXTextureFilterLinear;
      desc.samplers[sampler].mipFilter = GFXTextureFilterLinear;

      if (maxAnisotropy > 1)
      {
         desc.samplers[sampler].minFilter = GFXTextureFilterAnisotropic;
         desc.samplers[sampler].maxAnisotropy = maxAnisotropy;
      }
      else
         desc.samplers[sampler].minFilter = GFXTextureFilterLinear;
   }

   mNormalTexArrayConst = mShader->getShaderConstHandle("$normalMapSampler");
   if (mNormalTexArrayConst->isValid())
   {
      const S32 sampler = mNormalTexArrayConst->getSamplerRegister();

      desc.samplers[sampler] = GFXSamplerStateDesc::getWrapLinear();
      desc.samplers[sampler].magFilter = GFXTextureFilterLinear;
      desc.samplers[sampler].mipFilter = GFXTextureFilterLinear;

      if (maxAnisotropy > 1)
      {
         desc.samplers[sampler].minFilter = GFXTextureFilterAnisotropic;
         desc.samplers[sampler].maxAnisotropy = maxAnisotropy;
      }
      else
         desc.samplers[sampler].minFilter = GFXTextureFilterLinear;
   }

   mOrmTexArrayConst = mShader->getShaderConstHandle("$ormMapSampler");
   if (mOrmTexArrayConst->isValid())
   {
      const S32 sampler = mOrmTexArrayConst->getSamplerRegister();

      desc.samplers[sampler] = GFXSamplerStateDesc::getWrapLinear();
      desc.samplers[sampler].magFilter = GFXTextureFilterLinear;
      desc.samplers[sampler].mipFilter = GFXTextureFilterLinear;

      if (maxAnisotropy > 1)
      {
         desc.samplers[sampler].minFilter = GFXTextureFilterAnisotropic;
         desc.samplers[sampler].maxAnisotropy = maxAnisotropy;
      }
      else
         desc.samplers[sampler].minFilter = GFXTextureFilterLinear;
   }

   for (U32 i = 0; i < matCount && !baseOnly; i++)
   {
      TerrainMaterial* mat = mMaterialInfos[i]->mat;

      if (mat == NULL)
         continue;

      // We only include materials that 
      // have more than a base texture.
      if (!(mat->DetailMapValid() && mat->getDetailSize() > 0 && mat->getDetailDistance() > 0))
         continue;

      mMaterialInfos[i]->mBlendDepthConst = mShader->getShaderConstHandle(avar("$blendDepth%d", i));
      mMaterialInfos[i]->mBlendContrastConst = mShader->getShaderConstHandle(avar("$blendContrast%d", i));
      mMaterialInfos[i]->mBlendHardnessConst = mShader->getShaderConstHandle(avar("$blendHardness%d", i));
   }

   // If we're doing deferred it requires some 
   // special stencil settings for it to work.
   if ( deferredMat )
      desc.addDesc( RenderDeferredMgr::getOpaqueStenciWriteDesc( false ) );

   desc.setCullMode( GFXCullCCW );
   mStateBlock = GFX->createStateBlock(desc);

   //reflection stateblock
   desc.setCullMode( GFXCullCW );
   mReflectionStateBlock = GFX->createStateBlock(desc);

   // Create the wireframe state blocks.
   GFXStateBlockDesc wireframe( desc );
   wireframe.fillMode = GFXFillWireframe;
   wireframe.setCullMode( GFXCullCCW );
   mWireframeStateBlock = GFX->createStateBlock( wireframe );

   return true;
}

void TerrainCellMaterial::_updateMaterialConsts( )
{
   PROFILE_SCOPE( TerrainCellMaterial_UpdateMaterialConsts );

   int detailMatCount = 0;
   for (MaterialInfo* materialInfo : mMaterialInfos)
   {
      if (materialInfo == NULL)
         continue;

      TerrainMaterial* mat = materialInfo->mat;

      if (mat == NULL)
         continue;

      if (!(mat->DetailMapValid() && mat->getDetailSize() > 0 && mat->getDetailDistance() > 0))
         continue;

      detailMatCount++;
   }

   if (detailMatCount == 0)
   {
      return;
   }

   AlignedArray<Point4F> detailInfoArray(detailMatCount, sizeof(Point4F));
   AlignedArray<Point4F> detailScaleAndFadeArray(detailMatCount, sizeof(Point4F));

   AlignedArray<Point4F> macroInfoArray(detailMatCount, sizeof(Point4F));
   AlignedArray<Point4F> macroScaleAndFadeArray(detailMatCount, sizeof(Point4F));

   int detailIndex = 0;
   for (MaterialInfo* matInfo : mMaterialInfos)
   {
      if (matInfo == NULL)
         continue;

      TerrainMaterial* mat = matInfo->mat;

      if (mat == NULL)
         continue;

      if (!(mat->DetailMapValid() && mat->getDetailSize() > 0 && mat->getDetailDistance() > 0))
         continue;

      F32 detailSize = matInfo->mat->getDetailSize();
      F32 detailScale = 1.0f;
      if ( !mIsZero( detailSize ) )
         detailScale = mTerrain->getWorldBlockSize() / detailSize;

      // Scale the distance by the global scalar.
      const F32 distance = mTerrain->smDetailScale * matInfo->mat->getDetailDistance();

      // NOTE: The negation of the y scale is to make up for 
      // my mistake early in development and passing the wrong
      // y texture coord into the system.
      //
      // This negation fixes detail, normal, and parallax mapping
      // without harming the layer id blending code.
      //
      // Eventually we should rework this to correct this little
      // mistake, but there isn't really a hurry to.
      //
      Point4F detailScaleAndFade(   detailScale,
                                    -detailScale,
                                    distance, 
                                    0 );

      if ( !mIsZero( distance ) )
         detailScaleAndFade.w = 1.0f / distance;

      Point4F detailIdStrengthParallax( matInfo->layerId,
                                        matInfo->mat->getDetailStrength(),
                                        matInfo->mat->getParallaxScale(), 0 );

      detailScaleAndFadeArray[detailIndex] = detailScaleAndFade;
      detailInfoArray[detailIndex] = detailIdStrengthParallax;

      if (matInfo->mBlendDepthConst != NULL)
      {
         mConsts->setSafe(matInfo->mBlendDepthConst, matInfo->mat->getBlendDepth());
      }

      if (matInfo->mBlendContrastConst != NULL)
      {
         mConsts->setSafe(matInfo->mBlendContrastConst, matInfo->mat->getBlendContrast());
      }

      if (matInfo->mBlendHardnessConst != NULL)
      {
         mConsts->setSafe(matInfo->mBlendHardnessConst, matInfo->mat->getBlendHardness());
      }

      // macro texture info

      F32 macroSize = matInfo->mat->getMacroSize();
      F32 macroScale = 1.0f;
      if (!mIsZero(macroSize))
         macroScale = mTerrain->getWorldBlockSize() / macroSize;

      // Scale the distance by the global scalar.
      const F32 macroDistance = mTerrain->smDetailScale * matInfo->mat->getMacroDistance();

      Point4F macroScaleAndFade(macroScale,
         -macroScale,
         macroDistance,
         0);

      if (!mIsZero(macroDistance))
         macroScaleAndFade.w = 1.0f / macroDistance;

      Point4F macroIdStrengthParallax(matInfo->layerId,
         matInfo->mat->getMacroStrength(),
         0, 0);

      macroScaleAndFadeArray[detailIndex] = macroScaleAndFade;
      macroInfoArray[detailIndex] = macroIdStrengthParallax;

      detailIndex++;
   }

   mConsts->setSafe(mDetailInfoVArrayConst, detailScaleAndFadeArray);
   mConsts->setSafe(mDetailInfoPArrayConst, detailInfoArray);

   mConsts->setSafe(mMacroInfoVArrayConst, macroScaleAndFadeArray);
   mConsts->setSafe(mMacroInfoPArrayConst, macroInfoArray);
}

bool TerrainCellMaterial::setupPass(   const SceneRenderState *state, 
                                       const SceneData &sceneData )
{
   PROFILE_SCOPE( TerrainCellMaterial_SetupPass );

   if (mCurrPass > 0)
   {
      mCurrPass = 0;
      return false;
   }

   mCurrPass++;

   _updateMaterialConsts();

   if ( mBaseTexMapConst->isValid() )
      GFX->setTexture( mBaseTexMapConst->getSamplerRegister(), mTerrain->mBaseTex.getPointer() );

   if ( mLayerTexConst->isValid() )
      GFX->setTexture( mLayerTexConst->getSamplerRegister(), mTerrain->mLayerTex.getPointer() );

   if ( mLightMapTexConst->isValid() )
      GFX->setTexture( mLightMapTexConst->getSamplerRegister(), mTerrain->getLightMapTex() );

   if ( sceneData.wireframe )
      GFX->setStateBlock( mWireframeStateBlock );
   else if ( state->isReflectPass( ))
      GFX->setStateBlock( mReflectionStateBlock );
   else
      GFX->setStateBlock( mStateBlock );

   GFX->setShader( mShader );
   GFX->setShaderConstBuffer( mConsts );

   // Let the light manager prepare any light stuff it needs.
   LIGHTMGR->setLightInfo( NULL,
                           NULL,
                           sceneData,
                           state,
                           0,
                           mConsts );

   if (mDetailTexArrayConst->isValid() && mTerrain->getDetailTextureArray().isValid())
      GFX->setTextureArray(mDetailTexArrayConst->getSamplerRegister(), mTerrain->getDetailTextureArray());
   if (mMacroTexArrayConst->isValid() && mTerrain->getMacroTextureArray().isValid())
      GFX->setTextureArray(mMacroTexArrayConst->getSamplerRegister(), mTerrain->getMacroTextureArray());
   if (mNormalTexArrayConst->isValid() && mTerrain->getNormalTextureArray().isValid())
      GFX->setTextureArray(mNormalTexArrayConst->getSamplerRegister(), mTerrain->getNormalTextureArray());
   if (mOrmTexArrayConst->isValid() && mTerrain->getOrmTextureArray().isValid())
      GFX->setTextureArray(mOrmTexArrayConst->getSamplerRegister(), mTerrain->getOrmTextureArray());

   mConsts->setSafe( mLayerSizeConst, (F32)mTerrain->mLayerTex.getWidth() );

   if ( mOneOverTerrainSizeConst->isValid() )
   {
      F32 oneOverTerrainSize = 1.0f / mTerrain->getWorldBlockSize();
      mConsts->set( mOneOverTerrainSizeConst, oneOverTerrainSize );
   }

   mConsts->setSafe( mSquareSizeConst, mTerrain->getSquareSize() );

   if ( mFogDataConst->isValid() )
   {
      Point3F fogData;
      fogData.x = sceneData.fogDensity;
      fogData.y = sceneData.fogDensityOffset;
      fogData.z = sceneData.fogHeightFalloff;     
      mConsts->set( mFogDataConst, fogData );
   }

   if (String::isEmpty(Con::getVariable("$Terrain::BlendDepth")))
   {
      mConsts->setSafe(mBlendDepthConst, 0.2f);
   }
   else
   {
      mConsts->setSafe(mBlendDepthConst, Con::getFloatVariable("$Terrain::BlendDepth"));
   }

   mConsts->setSafe( mFogColorConst, sceneData.fogColor );

   if (  mLightInfoBufferConst->isValid() &&
         mLightParamsConst->isValid() )
   {
      if ( !mLightInfoTarget )
         mLightInfoTarget = NamedTexTarget::find( "diffuseLighting" );

      GFXTextureObject *texObject = mLightInfoTarget->getTexture();
      
      // TODO: Sometimes during reset of the light manager we get a
      // NULL texture here.  This is corrected on the next frame, but
      // we should still investigate why that happens.
      
      if ( texObject )
      {
         GFX->setTexture( mLightInfoBufferConst->getSamplerRegister(), texObject );

         const Point3I &targetSz = texObject->getSize();
         const RectI &targetVp = mLightInfoTarget->getViewport();
         Point4F rtParams;
         ScreenSpace::RenderTargetParameters(targetSz, targetVp, rtParams);
         mConsts->setSafe( mLightParamsConst, rtParams );
      }
   }

   return true;
}

BaseMatInstance* TerrainCellMaterial::getShadowMat()
{
   // Find our material which has some settings
   // defined on it in script.
   Material *mat = MATMGR->getMaterialDefinitionByName( "AL_DefaultShadowMaterial" );

   // Create the material instance adding the feature which
   // handles rendering terrain cut outs.
   FeatureSet features = MATMGR->getDefaultFeatures();
   BaseMatInstance *matInst = mat->createMatInstance();
   if ( !matInst->init( features, getGFXVertexFormat<TerrVertex>() ) )
   {
      delete matInst;
      matInst = NULL;
   }

   return matInst;
}

