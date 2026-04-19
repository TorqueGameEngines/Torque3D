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

#ifndef _POST_EFFECT_H_
#define _POST_EFFECT_H_

#ifndef _SIMSET_H_
#include "console/simSet.h"
#endif
#ifndef _MPOINT3_H_
#include "math/mPoint3.h"
#endif
#ifndef _MPOINT2_H_
#include "math/mPoint2.h"
#endif
#ifndef _GFXSHADER_H_
#include "gfx/gfxShader.h"
#endif
#ifndef _GFXSTATEBLOCK_H_
#include "gfx/gfxStateBlock.h"
#endif
#ifndef _GFXTEXTUREHANDLE_H_
#include "gfx/gfxTextureHandle.h"
#endif
#ifndef _GFXCUBEMAP_H_
#include "gfx/gfxCubemap.h"
#endif
#ifndef _GFXTARGET_H_
#include "gfx/gfxTarget.h"
#endif
#ifndef _GFXVERTEXBUFFER_H_
#include "gfx/gfxVertexBuffer.h"
#endif
#ifndef _POSTEFFECTCOMMON_H_
#include "postFx/postEffectCommon.h"
#endif
#ifndef _TDICTIONARY_H_
#include "core/util/tDictionary.h"
#endif
#ifndef _MATTEXTURETARGET_H_
#include "materials/matTextureTarget.h"
#endif

#include "T3D/assets/ImageAsset.h"

class GFXStateBlockData;
class Frustum;
class SceneRenderState;
class ConditionerFeature;

class PostEffect : public SimGroup
{
   typedef SimGroup Parent;

   friend class PostEffectVis;

public:

   enum
   {
      NumTextures = 16,

      /// Maximum simultaneous color render target outputs (MRT)
      NumMRTTargets = 4,
   };

protected:

   //--------------------------------------------------------------------------
   // Input textures
   //--------------------------------------------------------------------------

   DECLARE_IMAGEASSET_ARRAY(PostEffect, Texture, GFXStaticTextureSRGBProfile, NumTextures);
   GFXTextureProfile*    mTextureProfile[NumTextures];
   GFXTexHandle          mTexture[NumTextures];
   bool                  mTexSRGB[NumTextures];

   enum { NormalTextureType = 0, CubemapType, CubemapArrayType } mTextureType[NumTextures];

   GFXCubemapHandle      mCubemapTextures[NumTextures];
   GFXCubemapArrayHandle mCubemapArrayTextures[NumTextures];

   GFXTextureObject*     mActiveTextures[NumTextures];
   NamedTexTarget*       mActiveNamedTarget[NumTextures];
   RectI                 mActiveTextureViewport[NumTextures];

   //--------------------------------------------------------------------------
   // MRT color output targets
   //
   // Replaces the original single: mNamedTarget, mTargetName, mTargetTex,
   //                               mTargetFormat, mTargetClearColor, mTargetClear
   //--------------------------------------------------------------------------

   String         mTargetName[NumMRTTargets];        ///< Per-slot output name.
   GFXFormat      mTargetFormat[NumMRTTargets];      ///< Per-slot texture format.
   LinearColorF   mTargetClearColor[NumMRTTargets];  ///< Per-slot clear colour.
   PFXTargetClear mTargetClear[NumMRTTargets];       ///< Per-slot clear policy.

   GFXTexHandle   mTargetTex[NumMRTTargets];         ///< Runtime texture per slot.
   NamedTexTarget mNamedTarget[NumMRTTargets];       ///< Named target per slot.

   // These remain single values — shared across ALL active MRT slots.
   Point2F           mTargetScale;    ///< Relative size vs current GFX render target.
   Point2I           mTargetSize;     ///< Absolute size override; (0,0) = use mTargetScale.
   PFXTargetViewport mTargetViewport; ///< How the viewport rect is derived.

   /// Single GFXTextureTarget — ALL active MRT slots attach to this one object.
   GFXTextureTargetRef mTarget;

   S32 mMipCap;

   //--------------------------------------------------------------------------
   // Depth stencil
   //--------------------------------------------------------------------------

   String         mTargetDepthStencilName;
   GFXTexHandle   mTargetDepthStencil;
   NamedTexTarget mNamedTargetDepthStencil;

   //--------------------------------------------------------------------------
   // State block / shader
   //--------------------------------------------------------------------------

   GFXStateBlockData* mStateBlockData;
   GFXStateBlockRef        mStateBlock;
   String                  mShaderName;
   GFXShaderRef            mShader;
   Vector<GFXShaderMacro>  mShaderMacros;
   GFXShaderConstBufferRef mShaderConsts;

   //--------------------------------------------------------------------------
   // Auto shader constant handles
   //--------------------------------------------------------------------------

   GFXShaderConstHandle* mRTSizeSC;
   GFXShaderConstHandle* mOneOverRTSizeSC;
   GFXShaderConstHandle* mRTRatioSC;
   GFXShaderConstHandle* mTexSizeSC[NumTextures];
   GFXShaderConstHandle* mRenderTargetParamsSC[NumTextures];
   GFXShaderConstHandle* mMipCountSC[NumTextures];
   GFXShaderConstHandle* mViewportOffsetSC;
   GFXShaderConstHandle* mTargetViewportSC;
   GFXShaderConstHandle* mFogDataSC;
   GFXShaderConstHandle* mFogColorSC;
   GFXShaderConstHandle* mEyePosSC;
   GFXShaderConstHandle* mMatWorldToScreenSC;
   GFXShaderConstHandle* mMatScreenToWorldSC;
   GFXShaderConstHandle* mMatPrevScreenToWorldSC;
   GFXShaderConstHandle* mNearFarSC;
   GFXShaderConstHandle* mInvNearFarSC;
   GFXShaderConstHandle* mWorldToScreenScaleSC;
   GFXShaderConstHandle* mProjectionOffsetSC;
   GFXShaderConstHandle* mWaterColorSC;
   GFXShaderConstHandle* mWaterFogDataSC;
   GFXShaderConstHandle* mAmbientColorSC;
   GFXShaderConstHandle* mWaterFogPlaneSC;
   GFXShaderConstHandle* mWaterDepthGradMaxSC;
   GFXShaderConstHandle* mScreenSunPosSC;
   GFXShaderConstHandle* mLightDirectionSC;
   GFXShaderConstHandle* mCameraForwardSC;
   GFXShaderConstHandle* mAccumTimeSC;
   GFXShaderConstHandle* mDampnessSC;
   GFXShaderConstHandle* mDeltaTimeSC;
   GFXShaderConstHandle* mInvCameraMatSC;
   GFXShaderConstHandle* mMatCameraToWorldSC;
   GFXShaderConstHandle* mInvCameraTransSC;
   GFXShaderConstHandle* mMatCameraToScreenSC;
   GFXShaderConstHandle* mMatScreenToCameraSC;
   GFXShaderConstHandle* mIsCapturingSC;

   //--------------------------------------------------------------------------
   // Render scheduling
   //--------------------------------------------------------------------------

   bool          mAllowReflectPass;
   bool          mUpdateShader;
   PFXRenderTime mRenderTime;
   PFXTargetClear mTargetClear_unused; // kept for binary compat if needed — see arrays above
   String        mRenderBin;
   S16           mRenderPriority;
   bool          mIsValid;
   bool          mEnabled;
   bool          mSkip;
   bool          mPreProcessed;
   bool          mOneFrameOnly;
   bool          mOnThisFrame;
   U32           mShaderReloadKey;

   //--------------------------------------------------------------------------
   // EffectConst
   //--------------------------------------------------------------------------

   class EffectConst
   {
   public:
      EffectConst(const String& name, const String& val)
         : mName(name), mHandle(NULL), mDirty(true) {
         set(val);
      }
      EffectConst(const String& name, const F32& val)
         : mName(name), mHandle(NULL), mDirty(true) {
         set(val);
      }
      EffectConst(const String& name, const int& val)
         : mName(name), mHandle(NULL), mDirty(true) {
         set(val);
      }
      EffectConst(const String& name, const Point4F& val)
         : mName(name), mHandle(NULL), mDirty(true) {
         set(val);
      }
      EffectConst(const String& name, const MatrixF& val)
         : mName(name), mHandle(NULL), mDirty(true) {
         set(val);
      }
      EffectConst(const String& name, const Vector<Point4F>& val)
         : mName(name), mHandle(NULL), mDirty(true) {
         set(val);
      }
      EffectConst(const String& name, const Vector<MatrixF>& val)
         : mName(name), mHandle(NULL), mDirty(true) {
         set(val);
      }

      void set(const String& newVal);
      void set(const F32& newVal);
      void set(const int& newVal);
      void set(const Point4F& newVal);
      void set(const MatrixF& newVal);
      void set(const Vector<Point4F>& newVal);
      void set(const Vector<MatrixF>& newVal);
      void setToBuffer(GFXShaderConstBufferRef buff);

      String   mName;
      GFXShaderConstHandle* mHandle;
      String   mStringVal;
      S32      mIntVal;
      F32      mFloatVal;
      Point4F  mPointVal;
      MatrixF  mMatrixVal;
      Vector<Point4F> mPointArrayVal;
      Vector<MatrixF> mMatrixArrayVal;

      enum {
         StringType, IntType, FloatType, PointType,
         MatrixType, PointArrayType, MatrixArrayType
      } mValueType;

      bool mDirty;
   };

   typedef HashTable<StringCase, EffectConst*> EffectConstTable;
   EffectConstTable mEffectConsts;

   //--------------------------------------------------------------------------
   // Internal methods
   //--------------------------------------------------------------------------

   virtual void _updateScreenGeometry(const Frustum& frustum, GFXVertexBufferHandle<PFXVertex>* outVB);
   virtual void _setupStateBlock(const SceneRenderState* state);
   virtual void _setupConstants(const SceneRenderState* state);
   virtual void _setupTransforms();
   virtual void _setupTarget(const SceneRenderState* state, bool* outClearTarget);
   virtual void _setupTexture(U32 slot, GFXTexHandle& inputTex, const RectI* inTexViewport);
   virtual void _setupCubemapTexture(U32 stage, GFXCubemapHandle& inputTex);
   virtual void _setupCubemapArrayTexture(U32 slot, GFXCubemapArrayHandle& inputTex);

   static bool _setIsEnabled(void* object, const char* index, const char* data);

   void _onLMActivate(const char*, bool activate)
   {
      if (activate) mUpdateShader = true;
   }

   void _onTextureEvent(GFXTexCallbackCode code)
   {
      if (code != GFXZombify) return;
      bool anyNamed = mNamedTargetDepthStencil.isRegistered();
      for (U32 c = 0; c < NumMRTTargets && !anyNamed; c++)
         anyNamed = mNamedTarget[c].isRegistered();
      if (anyNamed) _cleanTargets();
   }

   void _updateConditioners();
   void _cleanTargets(bool recurse = false);
   void _checkRequirements();
   GFXTextureObject* _getTargetTexture(U32 index);

   /// Map "$outTex" / "$outTex0".."$outTex3" to a slot index [0..NumMRTTargets-1].
   /// Returns -1 if the name is not an $outTexN pattern.
   S32 _outTexSlotFromName(const String& name)
   {
      if (name.compare("$outTex", 0, String::NoCase) == 0) return 0; // backwards compat
      if (name.compare("$outTex0", 0, String::NoCase) == 0) return 0;
      if (name.compare("$outTex1", 0, String::NoCase) == 0) return 1;
      if (name.compare("$outTex2", 0, String::NoCase) == 0) return 2;
      if (name.compare("$outTex3", 0, String::NoCase) == 0) return 3;
      return -1;
   }

   S32 _inTexSlotFromName(const String& name)
   {
      if (name.compare("$inTex", 0, String::NoCase) == 0) return 0; // backwards compat
      if (name.compare("$inTex0", 0, String::NoCase) == 0) return 0;
      if (name.compare("$inTex1", 0, String::NoCase) == 0) return 1;
      if (name.compare("$inTex2", 0, String::NoCase) == 0) return 2;
      if (name.compare("$inTex3", 0, String::NoCase) == 0) return 3;
      return -1;
   }

public:

   PostEffect();
   virtual ~PostEffect();

   DECLARE_CONOBJECT(PostEffect);

   bool onAdd() override;
   void onRemove() override;
   static void initPersistFields();

   DECLARE_CALLBACK(void, onAdd, ());
   DECLARE_CALLBACK(void, preProcess, ());
   DECLARE_CALLBACK(void, setShaderConsts, ());
   DECLARE_CALLBACK(bool, onEnabled, ());
   DECLARE_CALLBACK(void, onDisabled, ());

   virtual void process(const SceneRenderState* state,
      GFXTexHandle& inOutTex,
      const RectI* inTexViewport = NULL);

   void reload();
   void enable();
   void disable();

   bool   dumpShaderDisassembly(String& outFilename) const;
   SimSet* getSet() const;

   bool isEnabled() const { return mEnabled; }
   bool isSkipped() const { return mSkip; }
   void setSkip(bool s) { mSkip = s; }

   PFXRenderTime getRenderTime() const { return mRenderTime; }
   const String& getRenderBin()  const { return mRenderBin; }
   F32           getPriority()   const { return mRenderPriority; }

   void setTexture(U32 index, const String& filePath);
   void setTexture(U32 index, const GFXTexHandle& texHandle);
   void setCubemapTexture(U32 index, const GFXCubemapHandle& handle);
   void setCubemapArrayTexture(U32 index, const GFXCubemapArrayHandle& handle);

   void setShaderMacro(const String& name, const String& value = String::EmptyString);
   bool removeShaderMacro(const String& name);
   void clearShaderMacros();

   void setShaderConst(const String& name, const String& val);
   void setShaderConst(const String& name, const F32& val);
   void setShaderConst(const String& name, const int& val);
   void setShaderConst(const String& name, const Point4F& val);
   void setShaderConst(const String& name, const MatrixF& val);
   void setShaderConst(const String& name, const Vector<Point4F>& val);
   void setShaderConst(const String& name, const Vector<MatrixF>& val);

   void setOnThisFrame(bool e) { mOnThisFrame = e; }
   bool isOnThisFrame() { return mOnThisFrame; }
   void setOneFrameOnly(bool e) { mOneFrameOnly = e; }
   bool isOneFrameOnly() { return mOneFrameOnly; }

   F32                     getAspectRatio()     const;
   GFXShaderRef            getShader() { return mShader; }
   Vector<GFXShaderMacro>* getShaderMacros() { return &mShaderMacros; }
   GFXShaderConstBufferRef getShaderConstBuffer() { return mShaderConsts; }

   enum PostEffectRequirements
   {
      RequiresDepth      = BIT(0),
      RequiresNormals    = BIT(1),
      RequiresLightInfo  = BIT(2),
   };
};

#endif // _POST_EFFECT_H_
