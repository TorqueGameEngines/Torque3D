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
#ifndef _MATERIALDEFINITION_H_
#define _MATERIALDEFINITION_H_

#ifndef _BASEMATERIALDEFINITION_H_
#include "materials/baseMaterialDefinition.h"
#endif
#ifndef _TDICTIONARY_H_
#include "core/util/tDictionary.h"
#endif
#ifndef _GFXTEXTUREHANDLE_H_
#include "gfx/gfxTextureHandle.h"
#endif
#ifndef _GFXSTRUCTS_H_
#include "gfx/gfxStructs.h"
#endif
#ifndef _GFXCUBEMAP_H_
#include "gfx/gfxCubemap.h"
#endif
#ifndef _DYNAMIC_CONSOLETYPES_H_
#include "console/dynamicTypes.h"
#endif

#ifndef IMAGE_ASSET_H
#include "T3D/assets/ImageAsset.h"
#endif
#ifndef _ASSET_PTR_H_
#include "assets/assetPtr.h"
#endif
#ifndef SOUND_ASSET_H
#include "T3D/assets/SoundAsset.h"
#endif

class CubemapData;
class SFXTrack;
struct SceneData;
class FeatureSet;
class FeatureType;
class MaterialSoundProfile;
class MaterialPhysicsProfile;

/// The basic material definition.
class Material : public BaseMaterialDefinition
{
   typedef BaseMaterialDefinition Parent;
public:
   static GFXCubemap* GetNormalizeCube();

   //-----------------------------------------------------------------------
   // Enums
   //-----------------------------------------------------------------------
   enum Constants
   {
      MAX_TEX_PER_PASS = 16,         ///< Number of textures per pass
      MAX_STAGES = 4,
      NUM_EFFECT_COLOR_STAGES = 2,  ///< Number of effect color definitions for transitioning effects.
   };

   enum TexType
   {
      NoTexture = 0,
      Standard = 1,
      Detail,
      Bump,
      DetailBump,
      Env,
      Cube,
      SGCube,  // scene graph cube - probably dynamic
      Lightmap,
      ToneMapTex,
      Mask,
      BackBuff,
      ReflectBuff,
      Misc,
      DynamicLight,
      DynamicLightMask,
      PhotometricMask,
      NormalizeCube,
      TexTarget,
      AccuMap,
   };

   enum BlendOp
   {
      None = 0,
      Mul,
      PreMul,
      Add,
      AddAlpha,      // add modulated with alpha channel
      Sub,
      LerpAlpha,     // linear interpolation modulated with alpha channel
      ToneMap,
      NumBlendTypes
   };

   enum AnimType
   {
      Scroll = BIT(0),
      Rotate = BIT(1),
      Wave = BIT(2),
      Scale = BIT(3),
      Sequence = BIT(4),
   };

   enum WaveType
   {
      Sin = 0,
      Triangle,
      Square,
   };

   enum SourceChannelType
   {
      RedChannel = 0,
      GreenChannel,
      BlueChannel,
      AlphaChannel
   };

   class StageData
   {
   protected:

      ///
      typedef HashTable<const FeatureType*, GFXTexHandle> TextureTable;

      /// The sparse table of textures by feature index.
      /// @see getTex
      /// @see setTex
      TextureTable mTextures;

      /// The cubemap for this stage.
      GFXTexHandle mCubemap;

   public:

      StageData()
         : mCubemap(NULL)
      {
      }

      /// Returns the texture object or NULL if there is no
      /// texture entry for that feature type in the table.
      inline GFXTextureObject* getTex(const FeatureType& type) const
      {
         TextureTable::ConstIterator iter = mTextures.find(&type);
         if (iter == mTextures.end())
            return NULL;

         return iter->value.getPointer();
      }

      /// Assigns a texture object by feature type.
      inline void setTex(const FeatureType& type, GFXTextureObject* tex)
      {
         if (!tex)
         {
            TextureTable::Iterator iter = mTextures.find(&type);
            if (iter != mTextures.end())
               mTextures.erase(iter);

            return;
         }

         TextureTable::Iterator iter = mTextures.findOrInsert(&type);
         iter->value = tex;
      }

      /// Returns true if we have a valid texture assigned to
      /// any feature in the texture table.
      inline bool hasValidTex() const
      {
         TextureTable::ConstIterator iter = mTextures.begin();
         for (; iter != mTextures.end(); ++iter)
         {
            if (iter->value.isValid())
               return true;
         }

         return false;
      }

      /// Returns the active texture features.
      void getFeatureSet(FeatureSet* outFeatures) const;

      /// Returns the stage cubemap.
      GFXTexHandle getCubemap() const { return mCubemap; }

      /// Set the stage cubemap.
      void setCubemap(GFXTexHandle cubemap) { mCubemap = cubemap; }

   };

public:

   //-----------------------------------------------------------------------
   // Data
   //-----------------------------------------------------------------------
   AssetRef<ImageAsset> mDiffuseMapAssetRef[MAX_STAGES];
   inline StringTableEntry getDiffuseMapAssetId(const U32& index) const { return mDiffuseMapAssetRef[index].assetId; }
   void setDiffuseMap(StringTableEntry assetId, const U32& index) { mDiffuseMapAssetRef[index] = assetId; }
   GFXTexHandle getDiffuseMap(const U32& index) { return mDiffuseMapAssetRef[index].notNull() ? mDiffuseMapAssetRef[index].assetPtr->getTexture(&GFXStaticTextureSRGBProfile) : GFXTexHandle(); }
   AssetPtr<ImageAsset> getDiffuseMapAsset(const U32& index) { return mDiffuseMapAssetRef[index].assetPtr; }

   AssetRef<ImageAsset> mNormalMapAssetRef[MAX_STAGES];
   inline StringTableEntry getNormalMapAssetId(const U32& index) const { return mNormalMapAssetRef[index].assetId; }
   void setNormalMap(StringTableEntry assetId, const U32& index) { mNormalMapAssetRef[index] = assetId; }
   GFXTexHandle getNormalMap(const U32& index) { return mNormalMapAssetRef[index].notNull() ? mNormalMapAssetRef[index].assetPtr->getTexture(&GFXNormalMapProfile) : GFXTexHandle(); }

   AssetRef<ImageAsset> mDetailNormalMapAssetRef[MAX_STAGES];
   inline StringTableEntry getDetailNormalMapAssetId(const U32& index) const { return mDetailNormalMapAssetRef[index].assetId; }
   void setDetailNormalMap(StringTableEntry assetId, const U32& index) { mDetailNormalMapAssetRef[index] = assetId; }
   GFXTexHandle getDetailNormalMap(const U32& index) { return mDetailNormalMapAssetRef[index].notNull() ? mDetailNormalMapAssetRef[index].assetPtr->getTexture(&GFXNormalMapProfile) : GFXTexHandle(); }

   AssetRef<ImageAsset> mOverlayMapAssetRef[MAX_STAGES];
   inline StringTableEntry getOverlayMapAssetId(const U32& index) const { return mOverlayMapAssetRef[index].assetId; }
   void setOverlayMap(StringTableEntry assetId, const U32& index) { mOverlayMapAssetRef[index] = assetId; }
   GFXTexHandle getOverlayMap(const U32& index) { return mOverlayMapAssetRef[index].notNull() ? mOverlayMapAssetRef[index].assetPtr->getTexture(&GFXStaticTextureProfile) : GFXTexHandle(); }

   AssetRef<ImageAsset> mLightMapAssetRef[MAX_STAGES];
   inline StringTableEntry getLightMapAssetId(const U32& index) const { return mLightMapAssetRef[index].assetId; }
   void setLightMap(StringTableEntry assetId, const U32& index) { mLightMapAssetRef[index] = assetId; }
   GFXTexHandle getLightMap(const U32& index) { return mLightMapAssetRef[index].notNull() ? mLightMapAssetRef[index].assetPtr->getTexture(&GFXStaticTextureProfile) : GFXTexHandle(); }

   AssetRef<ImageAsset> mToneMapAssetRef[MAX_STAGES];
   inline StringTableEntry getToneMapAssetId(const U32& index) const { return mToneMapAssetRef[index].assetId; }
   void setToneMap(StringTableEntry assetId, const U32& index) { mToneMapAssetRef[index] = assetId; }
   GFXTexHandle getToneMap(const U32& index) { return mToneMapAssetRef[index].notNull() ? mToneMapAssetRef[index].assetPtr->getTexture(&GFXStaticTextureProfile) : GFXTexHandle(); }

   AssetRef<ImageAsset> mDetailMapAssetRef[MAX_STAGES];
   inline StringTableEntry getDetailMapAssetId(const U32& index) const { return mDetailMapAssetRef[index].assetId; }
   void setDetailMap(StringTableEntry assetId, const U32& index) { mDetailMapAssetRef[index] = assetId; }
   GFXTexHandle getDetailMap(const U32& index) { return mDetailMapAssetRef[index].notNull() ? mDetailMapAssetRef[index].assetPtr->getTexture(&GFXStaticTextureProfile) : GFXTexHandle(); }

   AssetRef<ImageAsset> mORMConfigMapAssetRef[MAX_STAGES];
   inline StringTableEntry getORMConfigMapAssetId(const U32& index) const { return mORMConfigMapAssetRef[index].assetId; }
   void setORMConfigMap(StringTableEntry assetId, const U32& index) { mORMConfigMapAssetRef[index] = assetId; }
   GFXTexHandle getORMConfigMap(const U32& index) { return getORMConfigMap(&GFXStaticTextureProfile, index); }
   GFXTexHandle getORMConfigMap(GFXTextureProfile* requestedProfile, const U32& index) { return mORMConfigMapAssetRef[index].notNull() ? mORMConfigMapAssetRef[index].assetPtr->getTexture(requestedProfile) : GFXTexHandle(); }

   AssetRef<ImageAsset> mAOMapAssetRef[MAX_STAGES];
   inline StringTableEntry getAOMapAssetId(const U32& index) const { return mAOMapAssetRef[index].assetId; }
   void setAOMap(StringTableEntry assetId, const U32& index) { mAOMapAssetRef[index] = assetId; }
   GFXTexHandle getAOMap(const U32& index) { return mAOMapAssetRef[index].notNull() ? mAOMapAssetRef[index].assetPtr->getTexture(&GFXStaticTextureProfile) : GFXTexHandle(); }
   StringTableEntry getAOMapFile(const U32& index) { return mAOMapAssetRef[index].notNull() ? mAOMapAssetRef[index].assetPtr->getImageFile() : StringTable->EmptyString(); }

   AssetRef<ImageAsset> mRoughMapAssetRef[MAX_STAGES];
   inline StringTableEntry getRoughMapAssetId(const U32& index) const { return mRoughMapAssetRef[index].assetId; }
   void setRoughMap(StringTableEntry assetId, const U32& index) { mRoughMapAssetRef[index] = assetId; }
   GFXTexHandle getRoughMap(const U32& index) { return mRoughMapAssetRef[index].notNull() ? mRoughMapAssetRef[index].assetPtr->getTexture(&GFXStaticTextureProfile) : GFXTexHandle(); }
   StringTableEntry getRoughMapFile(const U32& index) { return mRoughMapAssetRef[index].notNull() ? mRoughMapAssetRef[index].assetPtr->getImageFile() : StringTable->EmptyString(); }

   AssetRef<ImageAsset> mMetalMapAssetRef[MAX_STAGES];
   inline StringTableEntry getMetalMapAssetId(const U32& index) const { return mMetalMapAssetRef[index].assetId; }
   void setMetalMap(StringTableEntry assetId, const U32& index) { mMetalMapAssetRef[index] = assetId; }
   GFXTexHandle getMetalMap(const U32& index) { return mMetalMapAssetRef[index].notNull() ? mMetalMapAssetRef[index].assetPtr->getTexture(&GFXStaticTextureProfile) : GFXTexHandle(); }
   StringTableEntry getMetalMapFile(const U32& index) { return mMetalMapAssetRef[index].notNull() ? mMetalMapAssetRef[index].assetPtr->getImageFile() : StringTable->EmptyString(); }

   AssetRef<ImageAsset> mGlowMapAssetRef[MAX_STAGES];
   inline StringTableEntry getGlowMapAssetId(const U32& index) const { return mGlowMapAssetRef[index].assetId; }
   void setGlowMap(StringTableEntry assetId, const U32& index) { mGlowMapAssetRef[index] = assetId; }
   GFXTexHandle getGlowMap(const U32& index) { return mGlowMapAssetRef[index].notNull() ? mGlowMapAssetRef[index].assetPtr->getTexture(&GFXStaticTextureProfile) : GFXTexHandle(); }

   bool     mDiffuseMapSRGB[MAX_STAGES];   // SRGB diffuse
   bool     mIsSRGb[MAX_STAGES];           // SRGB ORM
   U32      mAOChan[MAX_STAGES];
   bool     mInvertRoughness[MAX_STAGES];
   U32      mRoughnessChan[MAX_STAGES];
   U32      mMetalChan[MAX_STAGES];
   F32      mGlowMul[MAX_STAGES];

   /// The strength scalar for the detail normal map.
   F32      mDetailNormalMapStrength[MAX_STAGES];
   bool     mAccuEnabled[MAX_STAGES];
   F32      mAccuScale[MAX_STAGES];
   F32      mAccuDirection[MAX_STAGES];
   F32      mAccuStrength[MAX_STAGES];
   F32      mAccuCoverage[MAX_STAGES];
   F32      mAccuSpecular[MAX_STAGES];

   /// This color is the diffuse color of the material
   /// or if it has a texture it is multiplied against 
   /// the diffuse texture color.
   LinearColorF mDiffuse[MAX_STAGES];

   F32 mRoughness[MAX_STAGES];
   F32 mMetalness[MAX_STAGES];

   bool mVertLit[MAX_STAGES];

   /// If true for a stage, vertex colors are multiplied
   /// against diffuse colors.
   bool mVertColor[MAX_STAGES];

   F32 mParallaxScale[MAX_STAGES];

   F32 mMinnaertConstant[MAX_STAGES];
   bool mSubSurface[MAX_STAGES];
   LinearColorF mSubSurfaceColor[MAX_STAGES];
   F32 mSubSurfaceRolloff[MAX_STAGES];

   /// The repetition scale of the detail texture
   /// over the base texture.
   Point2F mDetailScale[MAX_STAGES];
   Point2F mTileScale[MAX_STAGES];

   U32 mAnimFlags[MAX_STAGES];
   Point2F mScrollDir[MAX_STAGES];
   F32 mScrollSpeed[MAX_STAGES];
   Point2F mScrollOffset[MAX_STAGES];

   F32 mRotSpeed[MAX_STAGES];
   Point2F mRotPivotOffset[MAX_STAGES];
   F32 mRotPos[MAX_STAGES];

   F32 mWavePos[MAX_STAGES];
   F32 mWaveFreq[MAX_STAGES];
   F32 mWaveAmp[MAX_STAGES];
   U32 mWaveType[MAX_STAGES];

   F32 mSeqFramePerSec[MAX_STAGES];
   F32 mSeqSegSize[MAX_STAGES];

   bool mGlow[MAX_STAGES];          // entire stage glows
   bool mReceiveShadows[MAX_STAGES];
   bool mIgnoreLighting[MAX_STAGES];

   Point2I mCellIndex[MAX_STAGES];
   Point2I mCellLayout[MAX_STAGES];
   U32 mCellSize[MAX_STAGES];
   bool mNormalMapAtlas[MAX_STAGES];

   /// Special array of UVs for imposter rendering.
   /// @see TSLastDetail
   Vector<RectF> mImposterUVs;

   /// Specual imposter rendering paramters.
   /// @see TSLastDetail
   Point4F mImposterLimits;

   /// If the stage should use anisotropic filtering.
   bool mUseAnisotropic[MAX_STAGES];


   bool mDoubleSided;

   String mCubemapName;
   CubemapData* mCubemapData;
   bool mDynamicCubemap;

   // Deferred Shading
   F32 mMatInfoFlags[MAX_STAGES];
   bool mTranslucent;
   BlendOp mTranslucentBlendOp;
   bool mTranslucentZWrite;

   /// A generic setting which tells the system to skip 
   /// generation of shadows from this material.
   bool mCastShadows;

   bool mAlphaTest;
   U32 mAlphaRef;

   bool mPlanarReflection;

   bool mAutoGenerated;

   static bool sAllowTextureTargetAssignment;

   ///@{
   /// Behavioral properties.

   bool mShowFootprints;            ///< If true, show footprints when walking on surface with this material.  Defaults to false.
   bool mShowDust;                  ///< If true, show dust emitters (footpuffs, hover trails, etc) when on surface with this material.  Defaults to false.

   /// Color to use for particle effects and such when located on this material.
   LinearColorF mEffectColor[NUM_EFFECT_COLOR_STAGES];

   /// Footstep sound to play when walking on surface with this material.
   /// Numeric ID of footstep sound defined on player datablock (0 == soft,
   /// 1 == hard, 2 == metal, 3 == snow).
   /// Defaults to -1 which deactivates default sound.
   /// @see mFootstepSoundCustom
   S32 mFootstepSoundId;
   S32 mImpactSoundId;
   S32 mImpactFXIndex;

   /// Sound effect to play when walking on surface with this material.
   /// If defined, overrides mFootstepSoundId.
   /// @see mFootstepSoundId
   DECLARE_SOUNDASSET(Material, CustomFootstepSound);
   DECLARE_ASSET_SETGET(Material, CustomFootstepSound);
   DECLARE_SOUNDASSET(Material, CustomImpactSound);
   DECLARE_ASSET_SETGET(Material, CustomImpactSound);

   F32 mFriction;                   ///< Friction coefficient when moving along surface.

   F32 mDirectSoundOcclusion;       ///< Amount of volume occlusion on direct sounds.
   F32 mReverbSoundOcclusion;       ///< Amount of volume occlusion on reverb sounds.

   ///@}

   String mMapTo; // map Material to this texture name
  
   ///
   /// Material interface
   ///
   Material();

   /// Allocates and returns a BaseMatInstance for this material.  Caller is responsible
   /// for freeing the instance
   BaseMatInstance* createMatInstance() override;
   bool isTranslucent() const override { return mTranslucent && mTranslucentBlendOp != Material::None; }
   bool isAlphatest() const override { return mAlphaTest; }
   bool isDoubleSided() const override { return mDoubleSided; }
   virtual bool isAutoGenerated() const { return mAutoGenerated; }
   virtual void setAutoGenerated(bool isAutoGenerated) { mAutoGenerated = isAutoGenerated; }
   bool isLightmapped() const override;
   bool castsShadows() const override { return mCastShadows; }
   const String& getPath() const { return mPath; }

   void flush();

   /// Re-initializes all the material instances 
   /// that use this material.
   void reload();

   /// Called to update time based parameters for a material.  Ensures 
   /// that it only happens once per tick.
   void updateTimeBasedParams();

   // SimObject
   bool onAdd() override;
   void onRemove() override;
   void inspectPostApply() override;
   bool writeField(StringTableEntry fieldname, const char* value) override;

   //
   // ConsoleObject interface
   //
   static void initPersistFields();

   // Accumulation
   static bool _setAccuEnabled(void* object, const char* index, const char* data);

   DECLARE_CONOBJECT(Material);
protected:

   // Per material animation parameters
   U32 mLastUpdateTime;

   String mPath;

   static EnumTable mAnimFlagTable;
   static EnumTable mBlendOpTable;
   static EnumTable mWaveTypeTable;

   /// Map this material to the texture specified
   /// in the "mapTo" data variable.
   virtual void _mapMaterial();

private:
   static GFXCubemapHandle smNormalizeCube;
};

typedef Material::AnimType MaterialAnimType;
typedef Material::BlendOp MaterialBlendOp;
typedef Material::WaveType MaterialWaveType;
typedef Material::SourceChannelType MaterialSourceChannelType;

DefineBitfieldType(MaterialAnimType);
DefineEnumType(MaterialBlendOp);
DefineEnumType(MaterialWaveType);
DefineEnumType(MaterialSourceChannelType);

#endif // _MATERIALDEFINITION_H_
