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

   mGamemodeName = StringTable->EmptyString();
   mMainLevelAsset = StringTable->EmptyString();
}

//-----------------------------------------------------------------------------

LevelAsset::~LevelAsset()
{
   // If the asset manager does not own the asset then we own the
   // asset definition so delete it.
   if (!getOwned())
      delete mpAssetDefinition;
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
      &setLevelFile, &getLevelFile, "Path to the level's postFXPreset.");
   addProtectedField("DecalsFile", TypeAssetLooseFilePath, Offset(mDecalsFile, LevelAsset),
      &setLevelFile, &getLevelFile, "Path to the decals cache file.");
   addProtectedField("ForestFile", TypeAssetLooseFilePath, Offset(mForestFile, LevelAsset),
      &setLevelFile, &getLevelFile, "Path to the Forest cache file.");
   addProtectedField("NavmeshFile", TypeAssetLooseFilePath, Offset(mNavmeshFile, LevelAsset),
      &setLevelFile, &getLevelFile, "Path to the navmesh file.");

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
   mPreviewImage = expandAssetFilePath(mPreviewImage);
   mLevelFile = expandAssetFilePath(mLevelFile);
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
   mLevelFile = getOwned() ? expandAssetFilePath(pLevelFile) : StringTable->insert(pLevelFile);

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
   mPreviewImage = getOwned() ? expandAssetFilePath(pImageFile) : StringTable->insert(pImageFile);

   // Refresh the asset.
   refreshAsset();
}
