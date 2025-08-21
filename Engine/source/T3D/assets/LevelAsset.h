#pragma once
//-----------------------------------------------------------------------------
// Copyright (c) 2013 GarageGames, LLC
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
#ifndef LEVEL_ASSET_H
#define LEVEL_ASSET_H

#ifndef _ASSET_BASE_H_
#include "assets/assetBase.h"
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
#include "T3D/assets/ImageAsset.h"

#ifndef _GUI_INSPECTOR_TYPES_H_
#include "gui/editor/guiInspectorTypes.h"
#endif
#include <gui/controls/guiBitmapCtrl.h>

//-----------------------------------------------------------------------------
class LevelAsset : public AssetBase
{
   typedef AssetBase Parent;

   StringTableEntry        mLevelName;
   StringTableEntry        mLevelFile;
   StringTableEntry        mPostFXPresetFile;
   StringTableEntry        mDecalsFile;
   StringTableEntry        mForestFile;
   StringTableEntry        mNavmeshFile;

   StringTableEntry        mLevelPath;
   StringTableEntry        mPostFXPresetPath;
   StringTableEntry        mDecalsPath;
   StringTableEntry        mForestPath;
   StringTableEntry        mNavmeshPath;

   StringTableEntry        mEditorFile;
   StringTableEntry        mBakedSceneFile;

   StringTableEntry        mGameModesNames;

   Vector<AssetBase*>      mAssetDependencies;

   StringTableEntry mPreviewImageAssetId;
   AssetPtr<ImageAsset> mPreviewImageAsset;

public:
   LevelAsset();
   virtual ~LevelAsset();

   /// Engine.
   static void initPersistFields();
   void copyTo(SimObject* object) override;

   /// Declare Console Object.
   DECLARE_CONOBJECT(LevelAsset);

   void loadDependencies();
   void unloadDependencies();

   void                    setLevelFile(const char* pImageFile);
   inline StringTableEntry getLevelFile(void) const { return mLevelFile; };
   void                    setPostFXPresetFile(const char* pPostFXPresetFile);
   inline StringTableEntry getPostFXPresetFile(void) const { return mPostFXPresetFile; };
   void                    setDecalsFile(const char* pDecalsFile);
   inline StringTableEntry getDecalsFile(void) const { return mDecalsFile; };
   void                    setForestFile(const char* pForestFile);
   inline StringTableEntry getForestFile(void) const { return mForestFile; };
   void                    setNavmeshFile(const char* pNavmeshFile);
   inline StringTableEntry getNavmeshFile(void) const { return mNavmeshFile; };

   StringTableEntry        getPreviewImageAsset(void) const;

   inline StringTableEntry getLevelPath(void) const { return mLevelPath; };
   inline StringTableEntry getPostFXPresetPath(void) const { return mPostFXPresetPath; };
   inline StringTableEntry getDecalsPath(void) const { return mDecalsPath; };
   inline StringTableEntry getForestPath(void) const { return mForestPath; };
   inline StringTableEntry getNavmeshPath(void) const { return mNavmeshPath; };

   StringTableEntry        getPreviewImagePath(void) const;

   void                    setEditorFile(const char* pEditorFile);
   inline StringTableEntry getEditorFile(void) const { return mEditorFile; };
   void                    setBakedSceneFile(const char* pBakedSceneFile);
   inline StringTableEntry getBakedSceneFile(void) const { return mBakedSceneFile; };

   U32 load() override { return Ok; };

protected:
   static bool setLevelFile(void* obj, const char* index, const char* data) { static_cast<LevelAsset*>(obj)->setLevelFile(data); return false; }
   static const char* getLevelFile(void* obj, const char* data) { return static_cast<LevelAsset*>(obj)->getLevelFile(); }

   static bool setEditorFile(void* obj, const char* index, const char* data) { static_cast<LevelAsset*>(obj)->setEditorFile(data); return false; }
   static const char* getEditorFile(void* obj, const char* data) { return static_cast<LevelAsset*>(obj)->getEditorFile(); }
   static bool setBakedSceneFile(void* obj, const char* index, const char* data) { static_cast<LevelAsset*>(obj)->setBakedSceneFile(data); return false; }
   static const char* getBakedSceneFile(void* obj, const char* data) { return static_cast<LevelAsset*>(obj)->getBakedSceneFile(); }

   static bool setPostFXPresetFile(void* obj, const char* index, const char* data) { static_cast<LevelAsset*>(obj)->setPostFXPresetFile(data); return false; }
   static const char* getPostFXPresetFile(void* obj, const char* data) { return static_cast<LevelAsset*>(obj)->getPostFXPresetFile(); }
   static bool setDecalsFile(void* obj, const char* index, const char* data) { static_cast<LevelAsset*>(obj)->setDecalsFile(data); return false; }
   static const char* getDecalsFile(void* obj, const char* data) { return static_cast<LevelAsset*>(obj)->getDecalsFile(); }

   static bool setForestFile(void* obj, const char* index, const char* data) { static_cast<LevelAsset*>(obj)->setForestFile(data); return false; }
   static const char* getForestFile(void* obj, const char* data) { return static_cast<LevelAsset*>(obj)->getForestFile(); }
   static bool setNavmeshFile(void* obj, const char* index, const char* data) { static_cast<LevelAsset*>(obj)->setNavmeshFile(data); return false; }
   static const char* getNavmeshFile(void* obj, const char* data) { return static_cast<LevelAsset*>(obj)->getNavmeshFile(); }


   void            initializeAsset(void) override;
   void            onAssetRefresh(void) override;
   void            loadAsset();

   typedef Signal<void()> LevelAssetChanged;
   LevelAssetChanged mChangeSignal;

public:
   LevelAssetChanged& getChangedSignal() { return mChangeSignal; }
};

#ifdef TORQUE_TOOLS
class GuiInspectorTypeLevelAssetPtr : public GuiInspectorTypeFileName
{
   typedef GuiInspectorTypeFileName Parent;
public:

   GuiBitmapButtonCtrl* mEditButton;

   DECLARE_CONOBJECT(GuiInspectorTypeLevelAssetPtr);
   static void consoleInit();

   GuiControl* constructEditControl() override;
   bool updateRects() override;
};

class GuiInspectorTypeLevelAssetId : public GuiInspectorTypeLevelAssetPtr
{
   typedef GuiInspectorTypeLevelAssetPtr Parent;
public:

   DECLARE_CONOBJECT(GuiInspectorTypeLevelAssetId);
   static void consoleInit();
};
#endif


DefineConsoleType(TypeLevelAssetPtr, LevelAsset)
DefineConsoleType(TypeLevelAssetId, String)

#pragma region Singular Asset Macros

//Singular assets
/// <Summary>
/// Declares an level asset
/// This establishes the assetId, asset and legacy filepath fields, along with supplemental getter and setter functions
/// </Summary>
#define DECLARE_LEVELASSET(className, name, changeFunc) public: \
   StringTableEntry m##name##AssetId;\
   AssetPtr<LevelAsset>  m##name##Asset;\
public: \
   const AssetPtr<LevelAsset> & get##name##Asset() const { return m##name##Asset; }\
   void set##name##Asset(const AssetPtr<LevelAsset> &_in) { m##name##Asset = _in;}\
   \
   bool _set##name(StringTableEntry _in)\
   {\
      if(m##name##AssetId != _in)\
      {\
         if (m##name##Asset.notNull())\
         {\
            m##name##Asset->getChangedSignal().remove(this, &className::changeFunc);\
         }\
         if (_in == NULL || !String::compare(_in,StringTable->EmptyString()))\
         {\
            m##name##AssetId = StringTable->EmptyString();\
            m##name##Asset = NULL;\
            return true;\
         }\
         if (AssetDatabase.isDeclaredAsset(_in))\
         {\
            m##name##AssetId = _in;\
            m##name##Asset = _in;\
            return true;\
         }\
      }\
      \
      if(get##name() == StringTable->EmptyString())\
         return true;\
      \
      return false;\
   }\
   \
   const StringTableEntry get##name() const\
   {\
      return m##name##AssetId;\
   }\
   bool name##Valid() {return (get##name() != StringTable->EmptyString() && m##name##Asset->getStatus() == AssetBase::Ok); }

#define INITPERSISTFIELD_LEVELASSET(name, consoleClass, docs) \
   addProtectedField(assetText(name, Asset), TypeLevelAssetId, Offset(m##name##AssetId, consoleClass), _set##name##Data, &defaultProtectedGetFn, assetDoc(name, asset docs.));

#pragma endregion

#endif // _ASSET_BASE_H_

