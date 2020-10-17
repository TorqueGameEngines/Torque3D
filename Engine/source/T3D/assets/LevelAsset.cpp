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
#include "LevelAsset.h"
#endif

#ifndef _ASSET_MANAGER_H_
#include "assets/assetManager.h"
#endif

#ifndef _CONSOLETYPES_H_
#include "console/consoleTypes.h"
#endif

#ifndef _TAML_
#include "persistence/taml/taml.h"
#endif

#ifndef _ASSET_PTR_H_
#include "assets/assetPtr.h"
#endif

// Debug Profiling.
#include "platform/profiler.h"

//-----------------------------------------------------------------------------

IMPLEMENT_CONOBJECT(LevelAsset);

ConsoleType(LevelAssetPtr, TypeLevelAssetPtr, String, ASSET_ID_FIELD_PREFIX)

//-----------------------------------------------------------------------------

ConsoleGetType(TypeLevelAssetPtr)
{
   // Fetch asset Id.
   return *((StringTableEntry*)dptr);
}

//-----------------------------------------------------------------------------

ConsoleSetType(TypeLevelAssetPtr)
{
   // Was a single argument specified?
   if (argc == 1)
   {
      // Yes, so fetch field value.
      const char* pFieldValue = argv[0];

      // Fetch asset Id.
      StringTableEntry* assetId = (StringTableEntry*)(dptr);

      // Update asset value.
      *assetId = StringTable->insert(pFieldValue);

      return;
   }

   // Warn.
   Con::warnf("(TypeLevelAssetPtr) - Cannot set multiple args to a single asset.");
}

//-----------------------------------------------------------------------------

LevelAsset::LevelAsset() : AssetBase(), mIsSubLevel(false)
{
   mLevelName = StringTable->EmptyString();
   mLevelFile = StringTable->EmptyString();
   mPreviewImage = StringTable->EmptyString();
   mPostFXPresetFile = StringTable->EmptyString();
   mDecalsFile = StringTable->EmptyString();
   mForestFile = StringTable->EmptyString();
   mNavmeshFile = StringTable->EmptyString();

   mLevelPath = StringTable->EmptyString();
   mPreviewImagePath = StringTable->EmptyString();
   mPostFXPresetPath = StringTable->EmptyString();
   mDecalsPath = StringTable->EmptyString();
   mForestPath = StringTable->EmptyString();
   mNavmeshPath = StringTable->EmptyString();

   mGamemodeName = StringTable->EmptyString();
   mMainLevelAsset = StringTable->EmptyString();

   mEditorFile = StringTable->EmptyString();
   mBakedSceneFile = StringTable->EmptyString();
}

//-----------------------------------------------------------------------------

LevelAsset::~LevelAsset()
{
}

//-----------------------------------------------------------------------------

void LevelAsset::initPersistFields()
{
   // Call parent.
   Parent::initPersistFields();

   addProtectedField("LevelFile", TypeAssetLooseFilePath, Offset(mLevelFile, LevelAsset),
      &setLevelFile, &getLevelFile, "Path to the actual level file.");
   addField("LevelName", TypeString, Offset(mLevelName, LevelAsset), "Human-friendly name for the level.");
   addProtectedField("PreviewImage", TypeAssetLooseFilePath, Offset(mPreviewImage, LevelAsset),
      &setPreviewImageFile, &getPreviewImageFile, "Path to the image used for selection preview.");

   addProtectedField("PostFXPresetFile", TypeAssetLooseFilePath, Offset(mPostFXPresetFile, LevelAsset),
      &setPostFXPresetFile, &getPostFXPresetFile, "Path to the level's postFXPreset.");
   addProtectedField("DecalsFile", TypeAssetLooseFilePath, Offset(mDecalsFile, LevelAsset),
      &setDecalsFile, &getDecalsFile, "Path to the decals cache file.");
   addProtectedField("ForestFile", TypeAssetLooseFilePath, Offset(mForestFile, LevelAsset),
      &setForestFile, &getForestFile, "Path to the Forest cache file.");
   addProtectedField("NavmeshFile", TypeAssetLooseFilePath, Offset(mNavmeshFile, LevelAsset),
      &setNavmeshFile, &getNavmeshFile, "Path to the navmesh file.");

   addProtectedField("EditorFile", TypeAssetLooseFilePath, Offset(mEditorFile, LevelAsset),
      &setEditorFile, &getEditorFile, "Path to the level file with objects that were removed as part of the baking process. Loaded when the editor is loaded for ease of editing.");
   addProtectedField("BakedSceneFile", TypeAssetLooseFilePath, Offset(mBakedSceneFile, LevelAsset),
      &setBakedSceneFile, &getBakedSceneFile, "Path to the level file with the objects generated as part of the baking process");

   addField("isSubScene", TypeBool, Offset(mIsSubLevel, LevelAsset), "Is this a sublevel to another Scene");
   addField("gameModeName", TypeString, Offset(mGamemodeName, LevelAsset), "Name of the Game Mode to be used with this level");
}

//------------------------------------------------------------------------------

void LevelAsset::copyTo(SimObject* object)
{
   // Call to parent.
   Parent::copyTo(object);
}

//
void LevelAsset::initializeAsset()
{
   // Call parent.
   Parent::initializeAsset();

   // Ensure the image-file is expanded.
   mPreviewImagePath = expandAssetFilePath(mPreviewImage);
   mLevelPath = expandAssetFilePath(mLevelFile);
   mPostFXPresetPath = expandAssetFilePath(mPostFXPresetFile);
   mDecalsPath = expandAssetFilePath(mDecalsFile);
   mForestPath = expandAssetFilePath(mForestFile);
   mNavmeshPath = expandAssetFilePath(mNavmeshFile);
}

void LevelAsset::onAssetRefresh(void)
{
   // Ensure the image-file is expanded.
   mPreviewImagePath = expandAssetFilePath(mPreviewImage);
   mLevelPath = expandAssetFilePath(mLevelFile);
   mPostFXPresetPath = expandAssetFilePath(mPostFXPresetFile);
   mDecalsPath = expandAssetFilePath(mDecalsFile);
   mForestPath = expandAssetFilePath(mForestFile);
   mNavmeshPath = expandAssetFilePath(mNavmeshFile);
}

//
void LevelAsset::setLevelFile(const char* pLevelFile)
{
   // Sanity!
   AssertFatal(pLevelFile != NULL, "Cannot use a NULL level file.");

   // Fetch image file.
   pLevelFile = StringTable->insert(pLevelFile);

   // Ignore no change,
   if (pLevelFile == mLevelFile)
      return;

   // Update.
   mLevelFile = pLevelFile;

   // Refresh the asset.
   refreshAsset();
}

void LevelAsset::setImageFile(const char* pImageFile)
{
   // Sanity!
   AssertFatal(pImageFile != NULL, "Cannot use a NULL image file.");

   // Fetch image file.
   pImageFile = StringTable->insert(pImageFile);

   // Ignore no change,
   if (pImageFile == mPreviewImage)
      return;

   // Update.
   mPreviewImage = pImageFile;

   // Refresh the asset.
   refreshAsset();
}

void LevelAsset::setEditorFile(const char* pEditorFile)
{
   // Sanity!
   AssertFatal(pEditorFile != NULL, "Cannot use a NULL level file.");

   // Fetch image file.
   pEditorFile = StringTable->insert(pEditorFile);

   // Ignore no change,
   if (pEditorFile == mEditorFile)
      return;

   // Update.
   mEditorFile = pEditorFile;

   // Refresh the asset.
   refreshAsset();
}

void LevelAsset::setBakedSceneFile(const char* pBakedSceneFile)
{
   // Sanity!
   AssertFatal(pBakedSceneFile != NULL, "Cannot use a NULL level file.");

   // Fetch image file.
   pBakedSceneFile = StringTable->insert(pBakedSceneFile);

   // Ignore no change,
   if (pBakedSceneFile == mBakedSceneFile)
      return;

   // Update.
   mBakedSceneFile = pBakedSceneFile;

   // Refresh the asset.
   refreshAsset();
}

void LevelAsset::setPostFXPresetFile(const char* pPostFXPresetFile)
{
   // Sanity!
   AssertFatal(pPostFXPresetFile != NULL, "Cannot use a NULL postFX preset file.");

   // Fetch file.
   pPostFXPresetFile = StringTable->insert(pPostFXPresetFile);

   // Ignore no change,
   if (pPostFXPresetFile == mPostFXPresetFile)
      return;

   // Update.
   mPostFXPresetFile = pPostFXPresetFile;

   // Refresh the asset.
   refreshAsset();
}

void LevelAsset::setDecalsFile(const char* pDecalsFile)
{
   // Sanity!
   AssertFatal(pDecalsFile != NULL, "Cannot use a NULL decals file.");

   // Fetch file.
   pDecalsFile = StringTable->insert(pDecalsFile);

   // Ignore no change,
   if (pDecalsFile == mDecalsFile)
      return;

   // Update.
   mDecalsFile = pDecalsFile;

   // Refresh the asset.
   refreshAsset();
}

void LevelAsset::setForestFile(const char* pForestFile)
{
   // Sanity!
   AssertFatal(pForestFile != NULL, "Cannot use a NULL decals file.");

   // Fetch file.
   pForestFile = StringTable->insert(pForestFile);

   // Ignore no change,
   if (pForestFile == mForestFile)
      return;

   // Update.
   mForestFile = pForestFile;

   // Refresh the asset.
   refreshAsset();
}

void LevelAsset::setNavmeshFile(const char* pNavmeshFile)
{
   // Sanity!
   AssertFatal(pNavmeshFile != NULL, "Cannot use a NULL Navmesh file.");

   // Fetch file.
   pNavmeshFile = StringTable->insert(pNavmeshFile);

   // Ignore no change,
   if (pNavmeshFile == mNavmeshFile)
      return;

   // Update.
   mNavmeshFile = pNavmeshFile;

   // Refresh the asset.
   refreshAsset();
}

void LevelAsset::loadDependencies()
{
   //First, load any material, animation, etc assets we may be referencing in our asset
   // Find any asset dependencies.
   AssetManager::typeAssetDependsOnHash::Iterator assetDependenciesItr = mpOwningAssetManager->getDependedOnAssets()->find(mpAssetDefinition->mAssetId);

   // Does the asset have any dependencies?
   if (assetDependenciesItr != mpOwningAssetManager->getDependedOnAssets()->end())
   {
      // Iterate all dependencies.
      while (assetDependenciesItr != mpOwningAssetManager->getDependedOnAssets()->end() && assetDependenciesItr->key == mpAssetDefinition->mAssetId)
      {
         //Force it to be loaded by acquiring it
         StringTableEntry assetId = assetDependenciesItr->value;
         mAssetDependencies.push_back(AssetDatabase.acquireAsset<AssetBase>(assetId));

         // Next dependency.
         assetDependenciesItr++;
      }
   }
}

void LevelAsset::unloadDependencies()
{
   for (U32 i = 0; i < mAssetDependencies.size(); i++)
   {
      AssetBase* assetDef = mAssetDependencies[i];
      AssetDatabase.releaseAsset(assetDef->getAssetId());
   }
}

DefineEngineMethod(LevelAsset, getLevelPath, const char*, (),,
   "Gets the full path of the asset's defined level file.\n"
   "@return The string result of the level path")
{
   return object->getLevelPath();
}

DefineEngineMethod(LevelAsset, getPreviewImagePath, const char*, (), ,
   "Gets the full path of the asset's defined preview image file.\n"
   "@return The string result of the level preview image path")
{
   return object->getImagePath();
}

DefineEngineMethod(LevelAsset, getPostFXPresetPath, const char*, (), ,
   "Gets the full path of the asset's defined postFX preset file.\n"
   "@return The string result of the postFX preset path")
{
   return object->getPostFXPresetPath();
}

DefineEngineMethod(LevelAsset, getDecalsPath, const char*, (), ,
   "Gets the full path of the asset's defined decal file.\n"
   "@return The string result of the decal path")
{
   return object->getDecalsPath();
}

DefineEngineMethod(LevelAsset, loadDependencies, void, (), ,
   "Initiates the loading of asset dependencies for this level.")
{
   return object->loadDependencies();
}

DefineEngineMethod(LevelAsset, unloadDependencies, void, (), ,
   "Initiates the unloading of previously loaded asset dependencies for this level.")
{
   return object->unloadDependencies();
}
