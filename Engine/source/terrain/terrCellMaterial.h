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

#ifndef _TERRCELLMATERIAL_H_
#define _TERRCELLMATERIAL_H_

#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif
#ifndef _MATTEXTURETARGET_H_
#include "materials/matTextureTarget.h"
#endif
#ifndef _GFXTEXTUREHANDLE_H_
#include "gfx/gfxTextureHandle.h"
#endif
#ifndef _GFXSHADER_H_
#include "gfx/gfxShader.h"
#endif
#ifndef _GFXSTATEBLOCK_H_
#include "gfx/gfxStateBlock.h"
#endif


class GFXTextureArray;
class SceneRenderState;
struct SceneData;
class TerrainMaterial;
class TerrainBlock;
class BaseMatInstance;


/// This is a complex material which holds one or more
/// optimized shaders for rendering a single cell.
class TerrainCellMaterial
{
protected:

   class MaterialInfo
   {
   public:

      MaterialInfo()
         :mat(NULL), layerId(0), mBlendDepthConst(NULL), mBlendContrastConst(NULL), mBlendHardnessConst(NULL)
      {
      }

      ~MaterialInfo() 
      {
      }

      TerrainMaterial *mat;
      U32 layerId;
      GFXShaderConstHandle *mBlendDepthConst;
      GFXShaderConstHandle *mBlendContrastConst;
      GFXShaderConstHandle* mBlendHardnessConst;
   };

   ///
   GFXShader *mShader;

   GFXShaderConstBufferRef mConsts;

   GFXStateBlockRef mStateBlock;
   GFXStateBlockRef mWireframeStateBlock;
   GFXStateBlockRef mReflectionStateBlock;

   GFXShaderConstHandle *mModelViewProjConst;
   GFXShaderConstHandle *mWorldViewOnlyConst;
   GFXShaderConstHandle *mViewToObjConst;

   GFXShaderConstHandle *mEyePosWorldConst;
   GFXShaderConstHandle *mEyePosConst;

   GFXShaderConstHandle *mObjTransConst;
   GFXShaderConstHandle *mWorldToObjConst;
   GFXShaderConstHandle *mVEyeConst;

   GFXShaderConstHandle *mLayerSizeConst;
   GFXShaderConstHandle *mLightParamsConst;
   GFXShaderConstHandle *mLightInfoBufferConst;

   GFXShaderConstHandle *mBaseTexMapConst;
   GFXShaderConstHandle *mLayerTexConst;

   GFXShaderConstHandle *mLightMapTexConst;

   GFXShaderConstHandle *mSquareSizeConst;
   GFXShaderConstHandle *mOneOverTerrainSizeConst;

   GFXShaderConstHandle* mDetailInfoVArrayConst;
   GFXShaderConstHandle* mDetailInfoPArrayConst;
   GFXShaderConstHandle* mMacroInfoVArrayConst;
   GFXShaderConstHandle* mMacroInfoPArrayConst;

   GFXShaderConstHandle *mFogDataConst;
   GFXShaderConstHandle *mFogColorConst;

   GFXShaderConstHandle *mDetailTexArrayConst;
   GFXShaderConstHandle *mMacroTexArrayConst;
   GFXShaderConstHandle *mNormalTexArrayConst;
   GFXShaderConstHandle *mOrmTexArrayConst;

   GFXShaderConstHandle* mBlendDepthConst;
   GFXShaderConstHandle* mBlendHeightFloorConst;

   TerrainBlock *mTerrain;

   U32 mCurrPass;

   U64 mMaterials;
   Vector<MaterialInfo*> mMaterialInfos;

   static const Vector<String> mSamplerNames;

   GFXTexHandle mBaseMapTexture;

   GFXTexHandle mLayerMapTexture;

   NamedTexTargetRef mLightInfoTarget;

   /// The deferred material for this material.
   TerrainCellMaterial *mDeferredMat;

   /// The reflection material for this material.
   TerrainCellMaterial *mReflectMat;

   /// A vector of all terrain cell materials loaded in the system.
   static Vector<TerrainCellMaterial*> smAllMaterials;

   bool _initShader( bool deferredMat,
                     bool reflectMat,
                     bool baseOnly );

   void _updateMaterialConsts();

public:
   
   TerrainCellMaterial();
   ~TerrainCellMaterial();

   void init(  TerrainBlock *block, 
               U64 activeMaterials,
               bool deferredMat = false,
               bool reflectMat = false,
               bool baseOnly = false );

   /// Returns a deferred material from this material.
   TerrainCellMaterial* getDeferredMat();

   /// Returns the reflection material from this material.
   TerrainCellMaterial* getReflectMat();

   void setTransformAndEye(   const MatrixF &modelXfm, 
                              const MatrixF &viewXfm,
                              const MatrixF &projectXfm,
                              F32 farPlane );

   ///
   bool setupPass(   const SceneRenderState *state,
                     const SceneData &sceneData );

   ///
   static BaseMatInstance* getShadowMat();

   /// 
   static void _updateDefaultAnisotropy();
};

#endif // _TERRCELLMATERIAL_H_

