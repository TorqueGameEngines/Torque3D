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

   bool                    mIsSubLevel;
   StringTableEntry        mMainLevelAsset;

   StringTableEntry        mGamemodeName;

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

   SimObjectId load();

protected:
   static bool setLevelFile(void *obj, const char *index, const char *data) { static_cast<LevelAsset*>(obj)->setLevelFile(data); return false; }
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
   void                    loadAsset();
};

DefineConsoleType(TypeLevelAssetPtr, LevelAsset)

#endif // _ASSET_BASE_H_

