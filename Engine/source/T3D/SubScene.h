#pragma once
#ifndef SUB_SCENE_H
#define SUB_SCENE_H

#ifndef SCENE_GROUP_H
#include "SceneGroup.h"
#endif
#ifndef LEVEL_ASSET_H
#include "assets/LevelAsset.h"
#endif

class GameMode;

class SubScene : public SceneGroup
{
   typedef SceneGroup Parent;

public:
   enum MaskBits
   {
      NextFreeMask = Parent::NextFreeMask << 0
   };

   void onLevelChanged() {}

protected:
   static bool smTransformChildren;

private:
   DECLARE_LEVELASSET(SubScene, Level, onLevelChanged);

   StringTableEntry mGameModesNames;
   Vector<GameMode*> mGameModesList;

   F32 mScopeDistance;

   /// <summary>
   /// How long we wait once every control object has left the SubScene's load boundary for us to unload the levelAsset.
   /// </summary>
   S32 mStartUnloadTimerMS;

   bool mLoaded;
   bool mSaving;
   bool mFreezeLoading;

   String mLoadIf;
   String mOnLoadCommand;
   String mOnUnloadCommand;

   S32 mTickPeriodMS;
   U32 mCurrTick;

   bool mGlobalLayer;

public:
   SubScene();
   virtual ~SubScene();

   DECLARE_CONOBJECT(SubScene);
   DECLARE_CATEGORY("Object \t Collection");

   static void initPersistFields();
   static void consoleInit();
   StringTableEntry getTypeHint() const override { return (getLevelAsset()) ? getLevelAsset()->getAssetName() : StringTable->EmptyString(); }

   // SimObject
   bool onAdd() override;
   void onRemove() override;

   U32 packUpdate(NetConnection* conn, U32 mask, BitStream* stream) override;
   void unpackUpdate(NetConnection* conn, BitStream* stream) override;

   void addObject(SimObject* object);
   void removeObject(SimObject* object);
   //void onEditorEnable() override;
   //void onEditorDisable() override;
   void inspectPostApply() override;

   void setTransform(const MatrixF& mat) override;
   void setRenderTransform(const MatrixF& mat) override;

   bool testBox(const Box3F& testBox);
   bool evaluateCondition();
   void _onSelected() override;
   void _onUnselected() override;

   static S32 mUnloadTimeoutMs;

protected:
   void write(Stream& stream, U32 tabStop, U32 flags = 0) override;

   //
   void _onFileChanged(const Torque::Path& path);
   void _removeContents(SimGroupIterator);
   void _closeFile(bool removeFileNotify);
   void _loadFile(bool addFileNotify);

   //
public:
   void processTick(const Move* move) override;

   //
   void onInspect(GuiInspector* inspector) override;

   void load();
   void unload();

   void prepRenderImage(SceneRenderState* state) override;
   void renderObject(ObjectRenderInst* ri,
      SceneRenderState* state,
      BaseMatInstance* overrideMat);

   bool isLoaded() { return mLoaded; }
   void setUnloadTimeMS(S32 unloadTimeMS) {
      mStartUnloadTimerMS = unloadTimeMS;
   }
   inline S32 getUnloadTimsMS() {
      return mStartUnloadTimerMS;
   }

   bool save();

   DECLARE_CALLBACK(void, onLoaded, ());
   DECLARE_CALLBACK(void, onUnloaded, ());
   DECLARE_ASSET_SETGET(SubScene, Level);
};
#endif
