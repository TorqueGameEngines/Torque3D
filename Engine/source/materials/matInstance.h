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
#ifndef _MATINSTANCE_H_
#define _MATINSTANCE_H_

#ifndef _MATERIALDEFINITION_H_
#include "materials/materialDefinition.h"
#endif
#ifndef _BASEMATINSTANCE_H_
#include "materials/baseMatInstance.h"
#endif
#ifndef _SCENEDATA_H_
#include "materials/sceneData.h"
#endif
#ifndef _GFXSTATEBLOCK_H_
#include "gfx/gfxStateBlock.h"
#endif
#ifndef _FEATURESET_H_
#include "shaderGen/featureSet.h"
#endif

class GFXShader;
class GFXCubemap;
class ShaderFeature;
class MatInstanceParameterHandle;
class MatInstParameters;
class ProcessedMaterial;
class GuiTreeViewCtrl;

///
class MatInstance : public BaseMatInstance
{   
public:
   virtual ~MatInstance();

   // BaseMatInstance
   bool init(   const FeatureSet &features, 
                        const GFXVertexFormat *vertexFormat ) override;
   bool reInit() override;
   void addStateBlockDesc(const GFXStateBlockDesc& desc) override;
   void updateStateBlocks() override;
   void addShaderMacro( const String &name, const String &value ) override;
   MaterialParameters* allocMaterialParameters() override;
   void setMaterialParameters(MaterialParameters* param) override; 
   MaterialParameters* getMaterialParameters() override;
   MaterialParameterHandle* getMaterialParameterHandle(const String& name) override;
   bool setupPass(SceneRenderState *, const SceneData &sgData ) override;
   void setTransforms(const MatrixSet &matrixSet, SceneRenderState *state) override;
   void setNodeTransforms(const MatrixF *address, const U32 numTransforms) override;
   void setCustomShaderData(Vector<CustomShaderBindingData> &shaderData) override;
   void setSceneInfo(SceneRenderState *, const SceneData& sgData) override;
   void setTextureStages(SceneRenderState * state, const SceneData &sgData ) override;
   void setBuffers(GFXVertexBufferHandleBase* vertBuffer, GFXPrimitiveBufferHandle* primBuffer) override;
   bool isInstanced() const override;
   bool stepInstance() override;
   bool isForwardLit() const override { return mIsForwardLit; }
   virtual bool isHardwareSkinned() const { return mIsHardwareSkinned; }
   void setUserObject( SimObject *userObject ) override { mUserObject = userObject; }
   SimObject* getUserObject() const override { return mUserObject; }
   Material *getMaterial() override { return mMaterial; }
   bool hasGlow() override;
   bool hasAccumulation() override;
   U32 getCurPass() override { return getMax( mCurPass, 0 ); }
   U32 getCurStageNum() override;
   RenderPassData *getPass(U32 pass) override;   
   const MatStateHint& getStateHint() const override;
   const GFXVertexFormat* getVertexFormat() const override { return mVertexFormat; }
   const FeatureSet& getFeatures() const override;
   const FeatureSet& getRequestedFeatures() const override { return mFeatureList; }
   void dumpShaderInfo() const override;
   void getShaderInfo(GuiTreeViewCtrl* tree, U32 item) const override;
   

   ProcessedMaterial *getProcessedMaterial() const { return mProcessedMaterial; }

   const GFXStateBlockDesc &getUserStateBlock() const override { return mUserDefinedState; }

   bool isCustomMaterial() const override { return mCreatedFromCustomMaterial; }
protected:

   friend class Material;

   /// Create a material instance by reference to a Material.
   MatInstance( Material &mat );

   virtual bool processMaterial();
   virtual ProcessedMaterial* getShaderMaterial();

   Material* mMaterial;
   ProcessedMaterial* mProcessedMaterial;

   /// The features requested at material creation time.
   FeatureSet mFeatureList;

   /// The vertex format on which this material will render.
   const GFXVertexFormat *mVertexFormat;

   /// If the processed material requires forward lighting or not.
   bool mIsForwardLit;

   /// If the processed material requires bone transforms
   bool mIsHardwareSkinned;

   S32               mCurPass;
   U32               mMaxStages;

   GFXStateBlockDesc mUserDefinedState;

   Vector<GFXShaderMacro> mUserMacros;

   SimObject *mUserObject;
   
   Vector<MatInstanceParameterHandle*> mCurrentHandles;
   Vector<MatInstParameters*> mCurrentParameters;
   MatInstParameters* mActiveParameters;
   MatInstParameters* mDefaultParameters;
   
   bool mCreatedFromCustomMaterial;
private:
   void construct();  
};

//
// MatInstParameters 
//
class MatInstParameters : public MaterialParameters
{
public:
   MatInstParameters();
   MatInstParameters(MaterialParameters* matParams);
   virtual ~MatInstParameters();
   
   void loadParameters(ProcessedMaterial* pmat);

   /// Returns our list of shader constants, the material can get this and just set the constants it knows about
   const Vector<GFXShaderConstDesc>& getShaderConstDesc() const override;

   /// @name Set shader constant values
   /// @{
   /// Actually set shader constant values
   /// @param name Name of the constant, this should be a name contained in the array returned in getShaderConstDesc,
   /// if an invalid name is used, it is ignored.
   void set(MaterialParameterHandle* handle, const F32 f) override;
   void set(MaterialParameterHandle* handle, const Point2F& fv) override;
   void set(MaterialParameterHandle* handle, const Point3F& fv) override;
   void set(MaterialParameterHandle* handle, const Point4F& fv) override;
   void set(MaterialParameterHandle* handle, const LinearColorF& fv) override;
   void set(MaterialParameterHandle* handle, const S32 f) override;
   void set(MaterialParameterHandle* handle, const Point2I& fv) override;
   void set(MaterialParameterHandle* handle, const Point3I& fv) override;
   void set(MaterialParameterHandle* handle, const Point4I& fv) override;
   void set(MaterialParameterHandle* handle, const AlignedArray<F32>& fv) override;
   void set(MaterialParameterHandle* handle, const AlignedArray<Point2F>& fv) override;
   void set(MaterialParameterHandle* handle, const AlignedArray<Point3F>& fv) override;
   void set(MaterialParameterHandle* handle, const AlignedArray<Point4F>& fv) override;
   void set(MaterialParameterHandle* handle, const AlignedArray<S32>& fv) override;
   void set(MaterialParameterHandle* handle, const AlignedArray<Point2I>& fv) override;
   void set(MaterialParameterHandle* handle, const AlignedArray<Point3I>& fv) override;
   void set(MaterialParameterHandle* handle, const AlignedArray<Point4I>& fv) override;
   void set(MaterialParameterHandle* handle, const MatrixF& mat, const GFXShaderConstType matrixType = GFXSCT_Float4x4) override;
   void set(MaterialParameterHandle* handle, const MatrixF* mat, const U32 arraySize, const GFXShaderConstType matrixType = GFXSCT_Float4x4) override;
   U32 getAlignmentValue(const GFXShaderConstType constType) override;
private:
   MaterialParameters* mParameters;
   bool mOwnParameters;
};


#endif // _MATINSTANCE_H_
