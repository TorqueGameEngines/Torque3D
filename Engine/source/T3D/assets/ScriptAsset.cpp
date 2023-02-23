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
#ifndef SCRIPT_ASSET_H
#include "ScriptAsset.h"
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

IMPLEMENT_CONOBJECT(ScriptAsset);

ConsoleType(ScriptAssetPtr, TypeScriptAssetPtr, ScriptAsset, ASSET_ID_FIELD_PREFIX)

//-----------------------------------------------------------------------------

ConsoleGetType(TypeScriptAssetPtr)
{
   // Fetch asset Id.
   return (*((AssetPtr<ScriptAsset>*)dptr)).getAssetId();
}

//-----------------------------------------------------------------------------

ConsoleSetType(TypeScriptAssetPtr)
{
   // Was a single argument specified?
   if (argc == 1)
   {
      // Yes, so fetch field value.
      const char* pFieldValue = argv[0];

      // Fetch asset pointer.
      AssetPtr<ScriptAsset>* pAssetPtr = dynamic_cast<AssetPtr<ScriptAsset>*>((AssetPtrBase*)(dptr));

      // Is the asset pointer the correct type?
      if (pAssetPtr == NULL)
      {
         // No, so fail.
         //Con::warnf("(TypeScriptAssetPtr) - Failed to set asset Id '%d'.", pFieldValue);
         return;
      }

      // Set asset.
      pAssetPtr->setAssetId(pFieldValue);

      return;
   }

   // Warn.
   Con::warnf("(TypeScriptAssetPtr) - Cannot set multiple args to a single asset.");
}

//-----------------------------------------------------------------------------

IMPLEMENT_CALLBACK(ScriptAsset, onInitializeAsset, void, (), (),
   "@brief When the ScriptAsset is initialized(loaded) by the AssetManager.\n\n");

IMPLEMENT_CALLBACK(ScriptAsset, onRefreshAsset, void, (), (),
   "@brief When the ScriptAsset is refreshed by the AssetManager.\n\n");

IMPLEMENT_CALLBACK(ScriptAsset, onUnloadAsset, void, (), (),
   "@brief When the ScriptAsset is unloaded by the AssetManager.\n\n");

ScriptAsset::ScriptAsset() : AssetBase(), mIsServerSide(true)
{
   mScriptFile = StringTable->EmptyString();
   mScriptPath = StringTable->EmptyString();
}

//-----------------------------------------------------------------------------

ScriptAsset::~ScriptAsset()
{
}

//-----------------------------------------------------------------------------

void ScriptAsset::initPersistFields()
{
   docsURL;
   // Call parent.
   Parent::initPersistFields();

   addProtectedField("scriptFile", TypeAssetLooseFilePath, Offset(mScriptFile, ScriptAsset),
      &setScriptFile, &getScriptFile, "Path to the script file.");
}

//------------------------------------------------------------------------------

void ScriptAsset::copyTo(SimObject* object)
{
   // Call to parent.
   Parent::copyTo(object);
}

void ScriptAsset::initializeAsset()
{
   if (mpAssetDefinition->mAssetType != StringTable->insert("ScriptAsset"))
   {
      //if we've got a custom type, treat it as our namespace, too
      setClassNamespace(mpAssetDefinition->mAssetType);
   }

   mScriptPath = getOwned() ? expandAssetFilePath(mScriptFile) : mScriptPath;

   if (Torque::FS::IsScriptFile(mScriptPath))
   {
      //We're initialized properly, so we'll go ahead and kick along any dependencies we may have as well
      AssetManager::typeAssetDependsOnHash::Iterator assetDependenciesItr = mpOwningAssetManager->getDependedOnAssets()->find(mpAssetDefinition->mAssetId);

      // Does the asset have any dependencies?
      if (assetDependenciesItr != mpOwningAssetManager->getDependedOnAssets()->end())
      {
         // Iterate all dependencies.
         while (assetDependenciesItr != mpOwningAssetManager->getDependedOnAssets()->end() && assetDependenciesItr->key == mpAssetDefinition->mAssetId)
         {
            AssetPtr<ScriptAsset> scriptAsset = assetDependenciesItr->value;

            mScriptAssetDependencies.push_front(scriptAsset);

            // Next dependency.
            assetDependenciesItr++;
         }
      }

      Con::executeFile(mScriptPath, false, false);
   }

   onInitializeAsset_callback();
}

void ScriptAsset::onAssetRefresh()
{
   mScriptPath = getOwned() ? expandAssetFilePath(mScriptFile) : mScriptPath;

   if (Torque::FS::IsScriptFile(mScriptPath))
   {
      //Refresh any dependencies we may have
      for (U32 i = 0; i < mScriptAssetDependencies.size(); i++)
      {
         mScriptAssetDependencies[i]->onAssetRefresh();
      }

      Con::executeFile(mScriptPath, false, false);
   }

   onRefreshAsset_callback();
}

void ScriptAsset::unloadAsset()
{
   onUnloadAsset_callback();
}

void ScriptAsset::setScriptFile(const char* pScriptFile)
{
   // Sanity!
   AssertFatal(pScriptFile != NULL, "Cannot use a NULL script file.");

   // Fetch image file.
   pScriptFile = StringTable->insert(pScriptFile, true);

   // Ignore no change,
   if (pScriptFile == mScriptFile)
      return;

   // Update.
   mScriptFile = getOwned() ? expandAssetFilePath(pScriptFile) : pScriptFile;

   // Refresh the asset.
   refreshAsset();
}

bool ScriptAsset::execScript()
{
   AssetBase* handle = mpOwningAssetManager->acquireAsset<AssetBase>(getAssetId());

   if (handle)
      return true;

   if (Torque::FS::IsScriptFile(mScriptPath))
   {
      return Con::executeFile(mScriptPath, false, false);
   }
   Con::errorf("ScriptAsset:execScript() - Script asset must have a valid file to exec");
   return false;
}

DefineEngineMethod(ScriptAsset, execScript, bool, (), ,
   "Executes the script file.\n"
   "@return The bool result of calling exec")
{
   return object->execScript();
}

