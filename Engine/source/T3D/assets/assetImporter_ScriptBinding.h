#pragma once

#include "console/engineAPI.h"
#include "assetImporter.h"

//Console Functions

DefineEngineMethod(AssetImportConfig, loadImportConfig, void, (Settings* configSettings, String configName), (nullAsType<Settings*>(), ""),
   "Creates a new script asset using the targetFilePath.\n"
   "@return The bool result of calling exec")
{
   return object->loadImportConfig(configSettings, configName);
}

DefineEngineMethod(AssetImporter, setTargetPath, void, (String path), (""),
   "Creates a new script asset using the targetFilePath.\n"
   "@return The bool result of calling exec")
{
   return object->setTargetPath(path);
}

DefineEngineMethod(AssetImporter, resetImportSession, void, (bool forceResetSession), (false),
   "Creates a new script asset using the targetFilePath.\n"
   "@return The bool result of calling exec")
{
   return object->resetImportSession(forceResetSession);
}

DefineEngineMethod(AssetImporter, dumpActivityLog, void, (), ,
   "Creates a new script asset using the targetFilePath.\n"
   "@return The bool result of calling exec")
{
   return object->dumpActivityLog();
}

DefineEngineMethod(AssetImporter, getActivityLogLineCount, S32, (),,
   "Creates a new script asset using the targetFilePath.\n"
   "@return The bool result of calling exec")
{
   return object->getActivityLogLineCount();
}

DefineEngineMethod(AssetImporter, getActivityLogLine, String, (S32 i), (0),
   "Creates a new script asset using the targetFilePath.\n"
   "@return The bool result of calling exec")
{
   return object->getActivityLogLine(i);
}

DefineEngineMethod(AssetImporter, autoImportFile, String, (String path, String typeHint), ("", ""),
   "Creates a new script asset using the targetFilePath.\n"
   "@return The bool result of calling exec")
{
   return object->autoImportFile(path, typeHint);
}

DefineEngineMethod(AssetImporter, addImportingFile, AssetImportObject*, (String path), (""),
   "Creates a new script asset using the targetFilePath.\n"
   "@return The bool result of calling exec")
{
   return object->addImportingFile(path);
}

DefineEngineMethod(AssetImporter, addImportingAssetItem, void, (AssetImportObject* assetItem, AssetImportObject* parentItem), (nullAsType< AssetImportObject*>(), nullAsType< AssetImportObject*>()),
   "Creates a new script asset using the targetFilePath.\n"
   "@return The bool result of calling exec")
{
   return object->addImportingAssetItem(assetItem, parentItem);
}

DefineEngineMethod(AssetImporter, processImportingAssets, void, (), ,
   "Creates a new script asset using the targetFilePath.\n"
   "@return The bool result of calling exec")
{
   return object->processImportAssets();
}

DefineEngineMethod(AssetImporter, validateImportingAssets, bool, (), ,
   "Creates a new script asset using the targetFilePath.\n"
   "@return The bool result of calling exec")
{
   return object->validateAssets();
}

DefineEngineMethod(AssetImporter, resolveAssetItemIssues, void, (AssetImportObject* assetItem), (nullAsType< AssetImportObject*>()),
   "Creates a new script asset using the targetFilePath.\n"
   "@return The bool result of calling exec")
{
   object->resolveAssetItemIssues(assetItem);
}

DefineEngineMethod(AssetImporter, importAssets, void, (),,
   "Creates a new script asset using the targetFilePath.\n"
   "@return The bool result of calling exec")
{
   return object->importAssets();
}

DefineEngineMethod(AssetImporter, getAssetItemCount, S32, (),,
   "Creates a new script asset using the targetFilePath.\n"
   "@return The bool result of calling exec")
{
   return object->getAssetItemCount();
}

DefineEngineMethod(AssetImporter, getAssetItem, AssetImportObject*, (S32 index), (0),
   "Creates a new script asset using the targetFilePath.\n"
   "@return The bool result of calling exec")
{
   return object->getAssetItem(index);
}

DefineEngineMethod(AssetImporter, getAssetItemChildCount, S32, (AssetImportObject* assetItem), (nullAsType< AssetImportObject*>()),
   "Creates a new script asset using the targetFilePath.\n"
   "@return The bool result of calling exec")
{
   if (assetItem == nullptr)
      return 0;

   return object->getAssetItemChildCount(assetItem);
}

DefineEngineMethod(AssetImporter, getAssetItemChild, AssetImportObject*, (AssetImportObject* assetItem, S32 index), (nullAsType< AssetImportObject*>(), 0),
   "Creates a new script asset using the targetFilePath.\n"
   "@return The bool result of calling exec")
{
   if (assetItem == nullptr)
      return nullptr;

   return object->getAssetItemChild(assetItem, index);
}

DefineEngineMethod(AssetImporter, deleteImportingAsset, void, (AssetImportObject* assetItem), (nullAsType< AssetImportObject*>()),
   "Creates a new script asset using the targetFilePath.\n"
   "@return The bool result of calling exec")
{
   return object->deleteImportingAsset(assetItem);
}

DefineEngineMethod(AssetImporter, setImportConfig, void, (AssetImportConfig* importConfig), (nullAsType< AssetImportConfig*>()),
   "Creates a new script asset using the targetFilePath.\n"
   "@return The bool result of calling exec")
{
   return object->setImportConfig(importConfig);
}


/*DefineEngineFunction(enumColladaForImport, bool, (const char* shapePath, const char* ctrl, bool loadCachedDts), ("", "", true),
   "(string shapePath, GuiTreeViewCtrl ctrl) Collect scene information from "
   "a COLLADA file and store it in a GuiTreeView control. This function is "
   "used by the COLLADA import gui to show a preview of the scene contents "
   "prior to import, and is probably not much use for anything else.\n"
   "@param shapePath COLLADA filename\n"
   "@param ctrl GuiTreeView control to add elements to\n"
   "@param loadCachedDts dictates if it should try and load the cached dts file if it exists"
   "@return true if successful, false otherwise\n"
   "@ingroup Editors\n"
   "@internal")
{
   return enumColladaForImport(shapePath, ctrl, loadCachedDts);
}*/
