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

#ifndef _TSRENDERDATA_H_
#define _TSRENDERDATA_H_

#ifndef _MMATRIX_H_
#include "math/mMatrix.h"
#endif

#ifndef _GFXDEVICE_H_
#include "gfx/gfxDevice.h"
#endif

class SceneRenderState;
class GFXCubemap;
class Frustum;
class LightQuery;
class TSShape;

struct CustomShaderBindingData
{
public:
	enum UniformType
	{
		Float = 0,
		Float2,
		Float3,
		Float4,
		Texture2D,
		Texture3D,
		Cubemap,
		Matrix2x2,
		Matrix2x3,
		Matrix2x4,
		Matrix3x2,
		Matrix3x3,
		Matrix3x4,
		Matrix4x2,
		Matrix4x3,
		Matrix4x4
	};
private:
	StringTableEntry targetedUniformName;

	//ShaderConstHandles shaderConstHandle;

	UniformType type;

	F32 mFloat;
	Point2F mFloat2;
	Point3F mFloat3;
	Point4F mFloat4;

	//Image stuff
	GFXTexHandle texture;
	GFXSamplerStateDesc samplerState;

public:
	void setFloat(StringTableEntry shaderConstName, F32 f)
	{
		targetedUniformName = shaderConstName;
		mFloat = f;
		type = Float;
	}
	F32 getFloat() { return mFloat; }

	void setFloat2(StringTableEntry shaderConstName, Point2F f)
	{
		targetedUniformName = shaderConstName;
		mFloat2 = f;
		type = Float2;
	}
	Point2F getFloat2() { return mFloat2; }
	
	void setFloat3(StringTableEntry shaderConstName, Point3F f)
	{
		targetedUniformName = shaderConstName;
		mFloat3 = f;
		type = Float3;
	}
	Point3F getFloat3() { return mFloat3; }
	
	void setFloat4(StringTableEntry shaderConstName, Point4F f)
	{
		targetedUniformName = shaderConstName;
		mFloat4 = f;
		type = Float4;
	}
	Point4F getFloat4() { return mFloat4; }
	
	StringTableEntry getHandleName() {
		return targetedUniformName;
	}

	UniformType getType() {
		return type;
	}
};

/// A simple class for passing render state through the pre-render pipeline.
///
/// @section TSRenderState_intro Introduction
///
/// TSRenderState holds on to certain pieces of data that may be
/// set at the preparation stage of rendering (prepRengerImage etc.)
/// which are needed further along in the process of submitting
/// a render instance for later rendering by the RenderManager.
///
/// It was created to clean up and refactor the DTS rendering
/// from having a large number of static data that would be used
/// in varying places.  These statics were confusing and would often
/// cause problems when not properly cleaned up by various objects after
/// submitting their RenderInstances.
///
/// @section TSRenderState_functionality What Does TSRenderState Do?
///
/// TSRenderState is a simple class that performs the function of passing along
/// (from the prep function(s) to the actual submission) the data 
/// needed for the desired state of rendering.
///
/// @section TSRenderState_example Usage Example
///
/// TSRenderState is very easy to use.  Merely create a TSRenderState object (in prepRenderImage usually)
/// and set any of the desired data members (SceneRenderState, camera transform etc.), and pass the address of
/// your TSRenderState to your render function.
///
class TSRenderState
{
protected:
   
   const SceneRenderState *mState;

   GFXCubemap *mCubemap;

   /// Used to override the normal
   /// fade value of an object.
   /// This is multiplied by the current
   /// fade value of the instance
   /// to gain the resulting visibility fade (see TSMesh::render()).
   F32 mFadeOverride;

   /// These are used in some places
   /// TSShapeInstance::render, however,
   /// it appears they are never set to anything
   /// other than false.  We provide methods
   /// for setting them regardless.
   bool mNoRenderTranslucent;
   bool mNoRenderNonTranslucent;

   /// A generic hint value passed from the game
   /// code down to the material for use by shader 
   /// features.
   void *mMaterialHint;

   /// An optional object space frustum used to cull
   /// subobjects within the shape.
   const Frustum *mCuller;

   /// Use the origin point of the mesh for distance
   /// sorting for transparency instead of the nearest
   /// bounding box point.
   bool mUseOriginSort;

   /// The lighting query object used if any materials
   /// are forward lit and need lights.
   LightQuery *mLightQuery;

   // The accumulation texture provided by an accumulation
   // volume. This is passed down per-object.
   GFXTextureObject* mAccuTex;

   /// List of matrices to use for hardware skinning
   MatrixF *mNodeTransforms;

   /// Count of matrices in the mNodeTransforms list
   U32 mNodeTransformCount;

   //Custom Shader data
   Vector<CustomShaderBindingData> mCustomShaderData;

public:
   TSRenderState();
   TSRenderState( const TSRenderState &state );

   /// @name Get/Set methods.
   /// @{

   ///@see mState
   const SceneRenderState* getSceneState() const { return mState; }
   void setSceneState( const SceneRenderState *state ) { mState = state; }

   ///@see mCubemap
   GFXCubemap* getCubemap() const { return mCubemap; }
   void setCubemap( GFXCubemap *cubemap ) { mCubemap = cubemap; }

   ///@see mFadeOverride
   F32 getFadeOverride() const { return mFadeOverride; }
   void setFadeOverride( F32 fade ) { mFadeOverride = fade; }

   ///@see mNoRenderTranslucent
   bool isNoRenderTranslucent() const { return mNoRenderTranslucent; }
   void setNoRenderTranslucent( bool noRenderTrans ) { mNoRenderTranslucent = noRenderTrans; }

   ///@see mNoRenderNonTranslucent
   bool isNoRenderNonTranslucent() const { return mNoRenderNonTranslucent; }
   void setNoRenderNonTranslucent( bool noRenderNonTrans ) { mNoRenderNonTranslucent = noRenderNonTrans; }

   ///@see mMaterialHint
   void* getMaterialHint() const { return mMaterialHint; }
   void setMaterialHint( void *materialHint ) { mMaterialHint = materialHint; }

   ///@see mCuller
   const Frustum* getCuller() const { return mCuller; }
   void setCuller( const  Frustum *culler ) { mCuller = culler; }

   ///@see mUseOriginSort
   void setOriginSort( bool enable ) { mUseOriginSort = enable; }
   bool useOriginSort() const { return mUseOriginSort; }

   ///@see mLightQuery
   void setLightQuery( LightQuery *query ) { mLightQuery = query; }
   LightQuery* getLightQuery() const { return mLightQuery; }

   ///@see mAccuTex
   void setAccuTex( GFXTextureObject* query ) { mAccuTex = query; }
   GFXTextureObject* getAccuTex() const { return mAccuTex; }

   void addCustomShaderBinding(CustomShaderBindingData data)
   {
	   mCustomShaderData.push_back(data);
   }
   Vector<CustomShaderBindingData> getCustomShaderBinding() const 
   { 
	   return mCustomShaderData; 
   }

   ///@ see mNodeTransforms, mNodeTransformCount
   void setNodeTransforms(MatrixF *list, U32 count) { mNodeTransforms = list; mNodeTransformCount = count; }
   void getNodeTransforms(MatrixF **list, U32 *count) const { *list = mNodeTransforms; *count = mNodeTransformCount; }

   /// @}
};

#endif // _TSRENDERDATA_H_
