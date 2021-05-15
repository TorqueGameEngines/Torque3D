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


///
GFX_DeclareTextureProfile( PostFxTargetProfile );




///
class PostEffect : public SimGroup
{
   typedef SimGroup Parent;

   friend class PostEffectVis;

public:

   enum
   {
      NumTextures = 8,
   };

protected:

   //DECLARE_IMAGEASSET_ARRAY(PostEffect, Texture, PostFxTextureProfile, NumTextures);
public: \
   static const U32 smTextureCount = NumTextures; \
   GFXTexHandle mTexture[NumTextures] = { NULL };\
   FileName mTextureName[NumTextures] = { String::EmptyString }; \
   StringTableEntry mTextureAssetId[NumTextures] = { StringTable->EmptyString() };\
   AssetPtr<ImageAsset>  mTextureAsset[NumTextures] = { NULL };\
   GFXTextureProfile * mTextureProfile = &PostFxTextureProfile;\
public: \
   const StringTableEntry getTextureFile(const U32& index) const { return StringTable->insert(mTextureName[index].c_str()); }\
   void setTextureFile(const FileName &_in, const U32& index) { mTextureName[index] = _in;}\
   const AssetPtr<ImageAsset> & getTextureAsset(const U32& index) const { return mTextureAsset[index]; }\
   void setTextureAsset(const AssetPtr<ImageAsset> &_in, const U32& index) { mTextureAsset[index] = _in;}\
   \
   bool _setTexture(StringTableEntry _in, const U32& index)\
   {\
      if(index >= smTextureCount || index < 0)\
         return false;\
      if (_in == StringTable->EmptyString())\
      {\
         mTextureName[index] = String::EmptyString;\
         mTextureAssetId[index] = StringTable->EmptyString();\
         mTextureAsset[index] = NULL;\
         mTexture[index].free();\
         mTexture[index] = NULL;\
         return true;\
      }\
      else if(_in[0] == '$' || _in[0] == '#')\
      {\
         mTextureName[index] = _in;\
         mTextureAssetId[index] = StringTable->EmptyString();\
         mTextureAsset[index] = NULL;\
         mTexture[index].free();\
         mTexture[index] = NULL;\
         return true;\
      }\
      \
      if (AssetDatabase.isDeclaredAsset(_in))\
      {\
         mTextureAssetId[index] = _in;\
         \
         U32 assetState = ImageAsset::getAssetById(mTextureAssetId[index], &mTextureAsset[index]);\
         \
         if (ImageAsset::Ok == assetState)\
         {\
            mTextureName[index] = StringTable->EmptyString();\
         }\
         else\
         {\
            mTextureName[index] = _in;\
            mTextureAsset[index] = NULL;\
         }\
      }\
      else\
      {\
         if (ImageAsset::getAssetByFilename(_in, &mTextureAsset[index]))\
         {\
            mTextureAssetId[index] = mTextureAsset[index].getAssetId();\
            \
            if (ImageAsset::Ok == mTextureAsset[index]->getStatus())\
               mTextureName[index] = StringTable->EmptyString();\
         }\
         else\
         {\
            mTextureName[index] = _in;\
            mTextureAssetId[index] = StringTable->EmptyString();\
            mTextureAsset[index] = NULL;\
         }\
      }\
      if (getTexture(index) != StringTable->EmptyString() && !mTextureName[index].equal("texhandle", String::NoCase))\
      {\
         mTexture[index].set(getTexture(index), mTextureProfile, avar("%s() - mTextureObject (line %d)", __FUNCTION__, __LINE__));\
         return true;\
      }\
      return false;\
   }\
   \
   const StringTableEntry getTexture(const U32& index) const\
   {\
      if (mTextureAsset[index] && (mTextureAsset[index]->getImageFileName() != StringTable->EmptyString()))\
         return  Platform::makeRelativePathName(mTextureAsset[index]->getImagePath(), Platform::getMainDotCsDir());\
      else if (mTextureName[index].isNotEmpty())\
         return StringTable->insert(Platform::makeRelativePathName(mTextureName[index].c_str(), Platform::getMainDotCsDir()));\
      else\
         return StringTable->EmptyString();\
   }\
   GFXTexHandle getTextureResource(const U32& index) \
   {\
      if(index >= smTextureCount || index < 0)\
         return nullptr;\
      return mTexture[index];\
   }

   DECLARE_IMAGEASSET_ARRAY_SETGET(PostEffect, Texture);

   bool mTexSRGB[NumTextures];

   enum
   {
      NormalTextureType = 0,
      CubemapType,
      CubemapArrayType,
   } mTextureType[NumTextures];

   GFXCubemapHandle mCubemapTextures[NumTextures];
   GFXCubemapArrayHandle mCubemapArrayTextures[NumTextures];

   NamedTexTarget mNamedTarget;
   NamedTexTarget mNamedTargetDepthStencil; 

   GFXTextureObject *mActiveTextures[NumTextures];

   NamedTexTarget *mActiveNamedTarget[NumTextures];

   RectI mActiveTextureViewport[NumTextures];

   GFXStateBlockData *mStateBlockData;

   GFXStateBlockRef mStateBlock;

   String mShaderName;

   GFXShaderRef mShader;

   Vector<GFXShaderMacro> mShaderMacros;
   
   GFXShaderConstBufferRef mShaderConsts;

   GFXShaderConstHandle *mRTSizeSC;
   GFXShaderConstHandle *mOneOverRTSizeSC;

   GFXShaderConstHandle *mTexSizeSC[NumTextures];
   GFXShaderConstHandle *mRenderTargetParamsSC[NumTextures];

   GFXShaderConstHandle *mViewportOffsetSC;

   GFXShaderConstHandle *mTargetViewportSC;

   GFXShaderConstHandle *mFogDataSC;
   GFXShaderConstHandle *mFogColorSC;
   GFXShaderConstHandle *mEyePosSC;
   GFXShaderConstHandle *mMatWorldToScreenSC;
   GFXShaderConstHandle *mMatScreenToWorldSC;
   GFXShaderConstHandle *mMatPrevScreenToWorldSC;
   GFXShaderConstHandle *mNearFarSC;
   GFXShaderConstHandle *mInvNearFarSC;   
   GFXShaderConstHandle *mWorldToScreenScaleSC;
   GFXShaderConstHandle *mProjectionOffsetSC;
   GFXShaderConstHandle *mWaterColorSC;
   GFXShaderConstHandle *mWaterFogDataSC;     
   GFXShaderConstHandle *mAmbientColorSC;
   GFXShaderConstHandle *mWaterFogPlaneSC;
   GFXShaderConstHandle *mWaterDepthGradMaxSC;
   GFXShaderConstHandle *mScreenSunPosSC;
   GFXShaderConstHandle *mLightDirectionSC;
   GFXShaderConstHandle *mCameraForwardSC;
   GFXShaderConstHandle *mAccumTimeSC;
   GFXShaderConstHandle *mDeltaTimeSC;
   GFXShaderConstHandle *mInvCameraMatSC;
   GFXShaderConstHandle *mMatCameraToWorldSC;
   GFXShaderConstHandle *mInvCameraTransSC;
   GFXShaderConstHandle *mMatCameraToScreenSC;
   GFXShaderConstHandle *mMatScreenToCameraSC;

   bool mAllowReflectPass;

   /// If true update the shader.
   bool mUpdateShader;   

   GFXTextureTargetRef mTarget;

   String mTargetName;
   GFXTexHandle mTargetTex;

   String mTargetDepthStencilName;
   GFXTexHandle mTargetDepthStencil;

   /// If mTargetSize is zero then this scale is
   /// used to make a relative texture size to the
   /// active render target.
   Point2F mTargetScale;

   /// If non-zero this is used as the absolute
   /// texture target size.
   /// @see mTargetScale
   Point2I mTargetSize;

   GFXFormat mTargetFormat;

   /// The color to prefill the named target when
   /// first created by the effect.
   LinearColorF mTargetClearColor;

   PFXRenderTime mRenderTime;
   PFXTargetClear mTargetClear;
   PFXTargetViewport mTargetViewport;

   String mRenderBin;

   F32 mRenderPriority;

   /// This is true if the effect has been succesfully
   /// initialized and all requirements are met for use.
   bool mIsValid;

   /// True if the effect has been enabled by the manager.
   bool mEnabled;
   
   /// Skip processing of this PostEffect and its children even if its parent is enabled. 
   /// Parent and sibling PostEffects in the chain are still processed.
   /// This is intended for debugging purposes.
   bool mSkip;

   bool mOneFrameOnly;
   bool mOnThisFrame;  

   U32 mShaderReloadKey;

   class EffectConst
   {
   public:

      EffectConst( const String &name, const String &val )
         : mName( name ), 
           mHandle( NULL ),
           mDirty( true )
      {
         set( val );
      }

      EffectConst(const String &name, const F32 &val)
         : mName(name),
         mHandle(NULL),
         mDirty(true)
      {
         set(val);
      }

      EffectConst(const String& name, const int& val)
         : mName(name),
         mHandle(NULL),
         mDirty(true)
      {
         set(val);
      }

      EffectConst(const String &name, const Point4F &val)
         : mName(name),
         mHandle(NULL),
         mDirty(true)
      {
         set(val);
      }

      EffectConst(const String &name, const MatrixF &val)
         : mName(name),
         mHandle(NULL),
         mDirty(true)
      {
         set(val);
      }

      EffectConst(const String &name, const Vector<Point4F> &val)
         : mName(name),
         mHandle(NULL),
         mDirty(true)
      {
         set(val);
      }

      EffectConst(const String &name, const Vector<MatrixF> &val)
         : mName(name),
         mHandle(NULL),
         mDirty(true)
      {
         set(val);
      }

      void set( const String &newVal );
      void set(const F32 &newVal);
      void set(const int& newVal);
      void set(const Point4F &newVal);
      void set(const MatrixF &newVal);
      void set(const Vector<Point4F> &newVal);
      void set(const Vector<MatrixF> &newVal);

      void setToBuffer( GFXShaderConstBufferRef buff );

      String mName;

      GFXShaderConstHandle *mHandle;

      String mStringVal;

      S32     mIntVal;
      F32     mFloatVal;
      Point4F mPointVal;
      MatrixF mMatrixVal;

      Vector<Point4F> mPointArrayVal;
      Vector<MatrixF> mMatrixArrayVal;

      enum
      {
         StringType,
         IntType,
         FloatType,
         PointType,
         MatrixType,
         PointArrayType,
         MatrixArrayType
      } mValueType;

      bool mDirty;
   };

   typedef HashTable<StringCase,EffectConst*> EffectConstTable;

   EffectConstTable mEffectConsts;

   ///
   virtual void _updateScreenGeometry( const Frustum &frustum,
                                       GFXVertexBufferHandle<PFXVertex> *outVB );

   ///
   virtual void _setupStateBlock( const SceneRenderState *state );

   /// 
   virtual void _setupConstants( const SceneRenderState *state );

   ///
   virtual void _setupTransforms();

   ///
   virtual void _setupTarget( const SceneRenderState *state, bool *outClearTarget );

   ///
   virtual void _setupTexture( U32 slot, GFXTexHandle &inputTex, const RectI *inTexViewport );
   virtual void _setupCubemapTexture(U32 stage, GFXCubemapHandle &inputTex);
   virtual void _setupCubemapArrayTexture(U32 slot, GFXCubemapArrayHandle &inputTex);


   /// Protected set method for toggling the enabled state.
   static bool _setIsEnabled( void *object, const char *index, const char *data );

   /// Called from the light manager activate signal.
   /// @see LightManager::addActivateCallback
   void _onLMActivate( const char*, bool activate )
   {
      if ( activate ) 
         mUpdateShader = true; 
   }

   /// We handle texture events to release named rendered targets.
   /// @see GFXTextureManager::addEventDelegate
   void _onTextureEvent( GFXTexCallbackCode code )
   {
      if ( code == GFXZombify && (mNamedTarget.isRegistered() || mNamedTargetDepthStencil.isRegistered()) )
         _cleanTargets();
   }

   ///
   void _updateConditioners();

   ///
   void _cleanTargets( bool recurse = false );

   /// 
   void _checkRequirements();

   ///
   GFXTextureObject* _getTargetTexture( U32 index );

public:

   /// Constructor.
   PostEffect();

   /// Destructor.
   virtual ~PostEffect();

   DECLARE_CONOBJECT(PostEffect);

   // SimObject
   virtual bool onAdd();
   virtual void onRemove();
   static void initPersistFields();

   /// @name Callbacks
   /// @{

   DECLARE_CALLBACK( void, onAdd, () );
   DECLARE_CALLBACK( void, preProcess, () );
   DECLARE_CALLBACK( void, setShaderConsts, () );
   DECLARE_CALLBACK( bool, onEnabled, () );
   DECLARE_CALLBACK( void, onDisabled, () );

   /// @}

   virtual void process(   const SceneRenderState *state, 
                           GFXTexHandle &inOutTex,
                           const RectI *inTexViewport = NULL );

   /// 
   void reload();

   /// 
   void enable();

   /// 
   void disable();

   /// Dump the shader disassembly to a temporary text file.
   /// Returns true and sets outFilename to the file if successful.
   bool dumpShaderDisassembly( String &outFilename ) const;

   /// Returns the SimSet which contains all PostEffects.
   SimSet* getSet() const;

   ///
   bool isEnabled() const { return mEnabled; }

   /// Is set to skip rendering.
   bool isSkipped() const { return mSkip; }

   /// Set the effect to skip rendering.
   void setSkip( bool skip ) { mSkip = skip; }

   PFXRenderTime getRenderTime() const { return mRenderTime; }

   const String& getRenderBin() const { return mRenderBin; }

   F32 getPriority() const { return mRenderPriority; }

   void setTexture( U32 index, const String &filePath );
   void setTexture(U32 index, const GFXTexHandle& texHandle);
   void setCubemapTexture(U32 index, const GFXCubemapHandle &cubemapHandle);
   void setCubemapArrayTexture(U32 index, const GFXCubemapArrayHandle &cubemapArrayHandle);

   void setShaderMacro( const String &name, const String &value = String::EmptyString );
   bool removeShaderMacro( const String &name );
   void clearShaderMacros();

   ///
   void setShaderConst( const String &name, const String &val );   
   void setShaderConst(const String &name, const F32 &val);
   void setShaderConst(const String& name, const int& val);
   void setShaderConst(const String &name, const Point4F &val);
   void setShaderConst(const String &name, const MatrixF &val);
   void setShaderConst(const String &name, const Vector<Point4F> &val);
   void setShaderConst(const String &name, const Vector<MatrixF> &val);

   void setOnThisFrame( bool enabled ) { mOnThisFrame = enabled; }
   bool isOnThisFrame() { return mOnThisFrame; }
   void setOneFrameOnly( bool enabled ) { mOneFrameOnly = enabled; }
   bool isOneFrameOnly() { return mOneFrameOnly; }   

   F32 getAspectRatio() const;

   GFXShaderRef getShader() { return mShader; }
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
