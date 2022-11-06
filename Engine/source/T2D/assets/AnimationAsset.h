#ifndef _ANIMATION_ASSET_H_
#define _ANIMATION_ASSET_H_

#ifndef _SPRITE_ASSET_H_
#include "T2D/assets/SpriteAsset.h"
#endif

#ifndef _ASSET_BASE_H_
#include "assets/assetBase.h"
#endif

#ifndef _MMATH_H_
#include "math/mMath.h"
#endif

#ifndef _ASSET_DEFINITION_H_
#include "assets/assetDefinition.h"
#endif

#ifndef _STRINGUNIT_H_
#include "string/stringUnit.h"
#endif

#ifndef _ASSET_FIELD_TYPES_H_
#include "assets/assetFieldTypes.h"
#endif

#ifndef _ASSET_PTR_H_
#include "assets/assetPtr.h"
#endif

//---------------------
class SpriteAsset;
//---------------------

class AnimationAsset : public AssetBase
{
   typedef AssetBase Parent;

private:

   AssetPtr<SpriteAsset>   mSpriteAsset;
   StringTableEntry        mSpriteAssetId;
   Vector<S32>             mAnimFrames;
   S32                     mAnimFPS;
   bool                    mAnimLoop;
   bool                    mRandomStart;
   bool                    mBounce;

public:
   //------------------------------
   // TODO: Add multiple animations to 1 asset.
   //       |- Controllable animation references.
   //       if possible, transition blending anims.
   //       Add sound triggers to animations.
   //------------------------------

   AnimationAsset();
   virtual ~AnimationAsset();

   static bool _setSpriteAsset(void *obj, const char* index, const char* data);
   static bool _setAnimationFrames(void *obj, const char* index, const char* data);

   /// Engine.
   static void initPersistFields();
   virtual void copyTo(SimObject* object);

   inline S32  getAnimationFrame(U32 frame) const { return mAnimFrames[frame]; }
   inline S32  getAnimationFPS() const { return mAnimFPS; }
   inline S32  getAnimationLength() const { return mAnimFrames.size(); }
   inline bool getAnimationLoop() const { return mAnimLoop; }
   inline bool getAnimationBounce() const { return mBounce; }
   inline AssetPtr<SpriteAsset> getSpriteAsset() const { return mSpriteAsset; }

   static bool getAssetById(StringTableEntry assetId, AssetPtr<AnimationAsset>* animAsset);

   SpriteAsset::FrameArea getActiveFrameArea(U32 frame);

   /// Declare Console Object.
   DECLARE_CONOBJECT(AnimationAsset);

protected:

   bool setSpriteAsset(const StringTableEntry spriteAssetId);
   bool setAnimationFrames(const char* animFrames);

};

DefineConsoleType(TypeAnimationAssetPtr, S32)
DefineConsoleType(TypeAnimationAssetId, String)

class GuiInspectorTypeAnimationAssetPtr : public GuiInspectorTypeFileName
{
   typedef GuiInspectorTypeFileName Parent;

public:

   GuiBitmapButtonCtrl *mSpriteEdButton;
   DECLARE_CONOBJECT(GuiInspectorTypeAnimationAssetPtr);
   static void consoleInit();

   virtual GuiControl* constructEditControl();
   virtual bool updateRects();

};

class GuiInspectorTypeAnimationAssetId : public GuiInspectorTypeAnimationAssetPtr
{
   typedef GuiInspectorTypeAnimationAssetPtr Parent;
public:
   DECLARE_CONOBJECT(GuiInspectorTypeAnimationAssetId);
   static void consoleInit();
};

#endif // !_ANIMATION_ASSET_H_
