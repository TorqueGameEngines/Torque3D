#pragma once

#include "console/engineAPI.h"
#include "assetImporter.h"

//Console Functions

DefineEngineMethod(AssetImportConfig, loadImportConfig, void, (Settings* configSettings, String configName), (nullAsType<Settings*>(), ""),
   "Loads the provided import config to the importer.\n"
   "@param configSettings A Settings object containing the import configs.\n"
   "@param configName The specific name of the config to be used.")
{
   return object->loadImportConfig(configSettings, configName);
}

DefineEngineMethod(AssetImporter, setTargetPath, void, (String path), (""),
   "Sets the target path the importing assets will be put into.\n"
   "@param A string of the target path.")
{
   return object->setTargetPath(path);
}

DefineEngineMethod(AssetImporter, resetImportSession, void, (bool forceResetSession), (false),
   "Resets the importer's import session. All existing import items, logs, etc will be cleared.")
{
   return object->resetImportSession(forceResetSession);
}

DefineEngineMethod(AssetImporter, dumpActivityLog, void, (), ,
   "Dumps the import activity log. If the importer is set to, it will save to file, otherwise dump to console.")
{
   return object->dumpActivityLog();
}

DefineEngineMethod(AssetImporter, getActivityLogLineCount, S32, (),,
   "Gets the number of lines in the import activity log.\n"
   "@return The number of lines in the import activity log.")
{
   return object->getActivityLogLineCount();
}

DefineEngineMethod(AssetImporter, getActivityLogLine, String, (S32 index), (0),
   "Gets a specific line in the import activity log.\n"
   "@param index The index of the line to be returned.\n"
   "@return The string of the requested line of the activity log")
{
   return object->getActivityLogLine(index);
}

DefineEngineMethod(AssetImporter, autoImportFile, String, (String path, String typeHint), ("", ""),
   "Run the full import process on a specific file.\n"
   "@return If import is successful, the assetId of the new asset. If it failed, an empty string.")
{
   return object->autoImportFile(path, typeHint);
}

DefineEngineMethod(AssetImporter, addImportingFile, AssetImportObject*, (String path), (""),
   "Adds a filepath to the current importing session.\n"
   "@param path The path to the file to be imported.\n"
   "@return The AssetImportObject from the import session.")
{
   return object->addImportingFile(path);
}

DefineEngineMethod(AssetImporter, addImportingAssetItem, void, (AssetImportObject* assetItem, AssetImportObject* parentItem), (nullAsType< AssetImportObject*>(), nullAsType< AssetImportObject*>()),
   "Adds an existing AssetImportObject to the current improting session.\n"
   "@param assetItem The AssetImportObject to be added to the import session.\n"
   "@param parentItem An AssetImportObject that to act as the parent of the item being added.")
{
   return object->addImportingAssetItem(assetItem, parentItem);
}

DefineEngineMethod(AssetImporter, processImportingAssets, void, (), ,
   "Processes the importing assets.")
{
   return object->processImportAssets();
}

DefineEngineMethod(AssetImporter, hasImportIssues, bool, (), ,
   "Validates the status of the importing items.\n"
   "@return False if there are no issues, true if there are importing issues")
{
   return object->validateAssets();
}

DefineEngineMethod(AssetImporter, resolveAssetItemIssues, void, (AssetImportObject* assetItem), (nullAsType< AssetImportObject*>()),
   "Runs the issue resolver to attempt to correct any simple issues, such as utilizing the config's settings to resolve collisions.")
{
   object->resolveAssetItemIssues(assetItem);
}

DefineEngineMethod(AssetImporter, importAssets, void, (),,
   "Runs the actual import action on the items.")
{
   object->importAssets();

   object->acquireAssets();
}

DefineEngineMethod(AssetImporter, getAssetItemCount, S32, (),,
   "Gets the number of importing asset items.\n"
   "@return The number of importing asset items")
{
   return object->getAssetItemCount();
}

DefineEngineMethod(AssetImporter, getAssetItem, AssetImportObject*, (S32 index), (0),
   "Gets a specific import asset item.\n"
   "@param index The index of the AssetImportObject to be returned.\n"
   "@return AssetImportObject")
{
   return object->getAssetItem(index);
}

DefineEngineMethod(AssetImporter, getAssetItemChildCount, S32, (AssetImportObject* assetItem), (nullAsType< AssetImportObject*>()),
   "Gets number of child items for a given importing asset item.\n"
   "@param assetItem The AssetImportObject to get the number of children of.\n"
   "@return The number of child items")
{
   if (assetItem == nullptr)
      return 0;

   return object->getAssetItemChildCount(assetItem);
}

DefineEngineMethod(AssetImporter, getAssetItemChild, AssetImportObject*, (AssetImportObject* assetItem, S32 index), (nullAsType< AssetImportObject*>(), 0),
   "Gets a specific child item of a given importing asset item.\n"
   "@param assetItem The AssetImportObject to get the child from.\n"
   "@param index The index of the child to get.\n"
   "@return The child AssetImportObect")
{
   if (assetItem == nullptr)
      return nullptr;

   return object->getAssetItemChild(assetItem, index);
}

DefineEngineMethod(AssetImporter, deleteImportingAsset, void, (AssetImportObject* assetItem), (nullAsType< AssetImportObject*>()),
   "Deletes an importing AssetImportObject from the import session.\n"
   "@param assetItem The AssetImportObject to delete.")
{
   return object->deleteImportingAsset(assetItem);
}

DefineEngineMethod(AssetImporter, setImportConfig, void, (AssetImportConfig* importConfig), (nullAsType< AssetImportConfig*>()),
   "Sets the import config to be used via a AssetImportConfig object.\n"
   "@param importConfig The AssetImportConfig object to use.")
{
   return object->setImportConfig(importConfig);
}
