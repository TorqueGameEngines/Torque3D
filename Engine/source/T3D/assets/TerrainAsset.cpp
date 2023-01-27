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

#ifndef TERRAINASSET_H
#include "TerrainAsset.h"
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

#include "T3D/assets/TerrainMaterialAsset.h"

#include "assetImporter.h"

//-----------------------------------------------------------------------------

IMPLEMENT_CONOBJECT(TerrainAsset);

ConsoleType(TerrainAssetPtr, TypeTerrainAssetPtr, TerrainAsset, ASSET_ID_FIELD_PREFIX)

//-----------------------------------------------------------------------------

ConsoleGetType(TypeTerrainAssetPtr)
{
   // Fetch asset Id.
   return (*((AssetPtr<TerrainAsset>*)dptr)).getAssetId();
}

//-----------------------------------------------------------------------------

ConsoleSetType(TypeTerrainAssetPtr)
{
   // Was a single argument specified?
   if (argc == 1)
   {
      // Yes, so fetch field value.
      const char* pFieldValue = argv[0];

      // Fetch asset pointer.
      AssetPtr<TerrainAsset>* pAssetPtr = dynamic_cast<AssetPtr<TerrainAsset>*>((AssetPtrBase*)(dptr));

      // Is the asset pointer the correct type?
      if (pAssetPtr == NULL)
      {
         // No, so fail.
         //Con::warnf("(TypeMaterialAssetPtr) - Failed to set asset Id '%d'.", pFieldValue);
         return;
      }

      // Set asset.
      pAssetPtr->setAssetId(pFieldValue);

      return;
   }

   // Warn.
   Con::warnf("(TypeTerrainAssetPtr) - Cannot set multiple args to a single asset.");
}


//-----------------------------------------------------------------------------
ConsoleType(assetIdString, TypeTerrainAssetId, const char*, ASSET_ID_FIELD_PREFIX)

ConsoleGetType(TypeTerrainAssetId)
{
   // Fetch asset Id.
   return *((const char**)(dptr));
}

ConsoleSetType(TypeTerrainAssetId)
{
   // Was a single argument specified?
   if (argc == 1)
   {
      // Yes, so fetch field value.
      const char* pFieldValue = argv[0];

      *((const char**)dptr) = StringTable->insert(argv[0]);

      return;
   }

   // Warn.
   Con::warnf("(TypeAssetId) - Cannot set multiple args to a single asset.");
}

//-----------------------------------------------------------------------------

TerrainAsset::TerrainAsset()
{
   mTerrainFileName = StringTable->EmptyString();
   mTerrainFilePath = StringTable->EmptyString();
}

//-----------------------------------------------------------------------------

TerrainAsset::~TerrainAsset()
{
}

//-----------------------------------------------------------------------------

void TerrainAsset::initPersistFields()
{
   docsURL;
   // Call parent.
   Parent::initPersistFields();

   //addField("shaderGraph", TypeRealString, Offset(mShaderGraphFile, TerrainAsset), "");
   addProtectedField("terrainFile", TypeAssetLooseFilePath, Offset(mTerrainFileName, TerrainAsset),
      &setTerrainFileName, &getTerrainFileName, "Path to the file containing the terrain data.");
}

void TerrainAsset::setDataField(StringTableEntry slotName, const char* array, const char* value)
{
   Parent::setDataField(slotName, array, value);

   //Now, if it's a material slot of some fashion, set it up
   StringTableEntry matSlotName = StringTable->insert("terrainMaterialAsset");
   if (String(slotName).startsWith(matSlotName))
   {
      StringTableEntry matId = StringTable->insert(value);

      mTerrMaterialAssetIds.push_back(matId);
   }
}

void TerrainAsset::initializeAsset()
{
   // Call parent.
   Parent::initializeAsset();

   mTerrainFilePath = getOwned() ? expandAssetFilePath(mTerrainFileName) : mTerrainFilePath;

   loadTerrain();
}

void TerrainAsset::onAssetRefresh()
{
   mTerrainFilePath = getOwned() ? expandAssetFilePath(mTerrainFileName) : mTerrainFilePath;

   loadTerrain();
}

void TerrainAsset::setTerrainFileName(const char* pScriptFile)
{
   // Sanity!
   AssertFatal(pScriptFile != NULL, "Cannot use a NULL terrain file.");

   pScriptFile = StringTable->insert(pScriptFile, true);

   // Ignore no change,
   if (pScriptFile == mTerrainFileName)
      return;

   // Update.
   mTerrainFileName = getOwned() ? expandAssetFilePath(pScriptFile) : pScriptFile;

   // Refresh the asset.
   refreshAsset();
}

bool TerrainAsset::loadTerrain()
{
   if (!Torque::FS::IsFile(mTerrainFilePath))
      return false;

   mTerrMaterialAssets.clear();
   mTerrMaterialAssetIds.clear();

   StringTableEntry terrainMatAssetType = StringTable->insert("TerrainMaterialAsset");

   //First, load any material, animation, etc assets we may be referencing in our asset
   // Find any asset dependencies.
   AssetManager::typeAssetDependsOnHash::Iterator assetDependenciesItr = mpOwningAssetManager->getDependedOnAssets()->find(mpAssetDefinition->mAssetId);

   // Does the asset have any dependencies?
   if (assetDependenciesItr != mpOwningAssetManager->getDependedOnAssets()->end())
   {
      // Iterate all dependencies.
      while (assetDependenciesItr != mpOwningAssetManager->getDependedOnAssets()->end() && assetDependenciesItr->key == mpAssetDefinition->mAssetId)
      {
         StringTableEntry assetType = mpOwningAssetManager->getAssetType(assetDependenciesItr->value);

         if (assetType == terrainMatAssetType)
         {
            StringTableEntry assetId = StringTable->insert(assetDependenciesItr->value);
            mTerrMaterialAssetIds.push_front(assetId);

            //Force the asset to become initialized if it hasn't been already
            AssetPtr<TerrainMaterialAsset> matAsset = assetId;
            mTerrMaterialAssets.push_front(matAsset);
         }

         // Next dependency.
         assetDependenciesItr++;
      }
   }

   mTerrainFile = ResourceManager::get().load(mTerrainFilePath);

   if (mTerrainFile)
      return true;

   return false;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//Utility function to 'fill out' bindings and resources with a matching asset if one exists
bool TerrainAsset::getAssetByFilename(StringTableEntry fileName, AssetPtr<TerrainAsset>* shapeAsset)
{
   AssetQuery query;
   S32 foundAssetcount = AssetDatabase.findAssetLooseFile(&query, fileName);
   if (foundAssetcount == 0)
   {
      //Didn't find any assets
      //If possible, see if we can run an in-place import and the get the asset from that
#ifdef TORQUE_DEBUG
      Con::warnf("TerrainAsset::getAssetByFilename - Attempted to in-place import a terrainFile(%s) that had no associated asset", fileName);
#endif

      Torque::Path terrFilePath = fileName;

      TerrainAsset* newTerrainAsset = new TerrainAsset();

      String assetName = terrFilePath.getFileName();
      assetName.replace(" ", "_");

      newTerrainAsset->setAssetName(assetName.c_str());
      String terrainPathBind = terrFilePath.getFileName() + terrFilePath.getExtension();

      newTerrainAsset->mTerrainFileName = StringTable->insert(terrainPathBind.c_str());

      newTerrainAsset->saveAsset();

      Taml taml;

      // Yes, so set it.
      taml.setFormatMode(Taml::getFormatModeEnum("xml"));

      // Turn-off auto-formatting.
      taml.setAutoFormat(false);

      String tamlPath = terrFilePath.getFullPath() + "/" + assetName + ".asset.taml";

      // Read object.
      bool success = taml.write(newTerrainAsset, tamlPath.c_str());

      if (!success)
      {
         Con::printf("TerrainAsset::getAssetByFilename() - failed to auto-import terrainfile(%s) as an TerrainAsset", fileName);
         return false;
      }

      ModuleDefinition* targetModuleDef = AssetImporter::getModuleFromPath(fileName);

      if (!targetModuleDef)
      {
         Con::printf("TerrainAsset::getAssetByFilename() - failed to auto-import terrainfile(%s) as an TerrainAsset, unable to find a valid Module for the filePath", fileName);
         return false;
      }

      success = AssetDatabase.addDeclaredAsset(targetModuleDef, tamlPath.c_str());

      if (!success)
      {
         Con::printf("TerrainAsset::getAssetByFilename() - failed to auto-import terrainfile(%s) as an TerrainAsset, unable to find a register asset with path", tamlPath.c_str());
         return false;
      }

      String assetId = targetModuleDef->getModuleId();
      assetId += ":";
      assetId += assetName.c_str();

      StringTableEntry resultingAssetId = StringTable->insert(assetId.c_str());

      if (resultingAssetId != StringTable->EmptyString())
      {
         shapeAsset->setAssetId(resultingAssetId);

         if (!shapeAsset->isNull())
            return true;
      }

      //That didn't work, so fail out
      return false;
   }
   else
   {
      //acquire and bind the asset, and return it out
      shapeAsset->setAssetId(query.mAssetList[0]);
      return true;
   }
}

StringTableEntry TerrainAsset::getAssetIdByFilename(StringTableEntry fileName)
{
   if (fileName == StringTable->EmptyString())
      return StringTable->EmptyString();

   StringTableEntry shapeAssetId = StringTable->EmptyString();

   AssetQuery query;
   S32 foundAssetcount = AssetDatabase.findAssetLooseFile(&query, fileName);
   if (foundAssetcount == 0)
   {
      //Didn't find any assets
      //If possible, see if we can run an in-place import and the get the asset from that
#if TORQUE_DEBUG
      Con::warnf("TerrainAsset::getAssetByFilename - Attempted to in-place import a terrainFile(%s) that had no associated asset", fileName);
#endif

      Torque::Path terrFilePath = fileName;

      TerrainAsset* newTerrainAsset = new TerrainAsset();

      String assetName = terrFilePath.getFileName();
      assetName.replace(" ", "_");

      newTerrainAsset->setAssetName(assetName.c_str());
      String terrainPathBind = terrFilePath.getFileName() + "." + terrFilePath.getExtension();

      newTerrainAsset->mTerrainFileName = StringTable->insert(terrainPathBind.c_str());

      newTerrainAsset->saveAsset();

      Taml taml;

      // Yes, so set it.
      taml.setFormatMode(Taml::getFormatModeEnum("xml"));

      // Turn-off auto-formatting.
      taml.setAutoFormat(false);

      String tamlPath = terrFilePath.getPath() + "/" + assetName + ".asset.taml";

      // Read object.
      bool success = taml.write(newTerrainAsset, tamlPath.c_str());

      if (!success)
      {
         Con::printf("TerrainAsset::getAssetIdByFilename() - failed to auto-import terrainfile(%s) as an TerrainAsset", fileName);
         return StringTable->EmptyString();
      }

      ModuleDefinition* targetModuleDef = AssetImporter::getModuleFromPath(fileName);

      if (!targetModuleDef)
      {
         Con::printf("TerrainAsset::getAssetIdByFilename() - failed to auto-import terrainfile(%s) as an TerrainAsset, unable to find a valid Module for the filePath", fileName);
         return StringTable->EmptyString();
      }

      success = AssetDatabase.addDeclaredAsset(targetModuleDef, tamlPath.c_str());

      if (!success)
      {
         Con::printf("TerrainAsset::getAssetIdByFilename() - failed to auto-import terrainfile(%s) as an TerrainAsset, unable to find a register asset with path", tamlPath.c_str());
         return StringTable->EmptyString();
      }

      String assetId = targetModuleDef->getModuleId();
      assetId += ":";
      assetId += assetName.c_str();

      StringTableEntry resultingAssetId = StringTable->insert(assetId.c_str());

      if (resultingAssetId != StringTable->EmptyString())
      {
         shapeAssetId = resultingAssetId;
         return shapeAssetId;
      }
   }
   else
   {
      //acquire and bind the asset, and return it out
      shapeAssetId = query.mAssetList[0];
   }

   return shapeAssetId;
}

bool TerrainAsset::getAssetById(StringTableEntry assetId, AssetPtr<TerrainAsset>* shapeAsset)
{
   (*shapeAsset) = assetId;

   if (!shapeAsset->isNull())
      return true;

   return false;
}

//------------------------------------------------------------------------------
void TerrainAsset::copyTo(SimObject* object)
{
   // Call to parent.
   Parent::copyTo(object);
}

DefineEngineMethod(TerrainAsset, getTerrainFilePath, const char*, (), ,
   "Gets the terrain filepath of this asset.\n"
   "@return File path of the terrain file.")
{
   return object->getTerrainFilePath();
}

#ifdef TORQUE_TOOLS
//-----------------------------------------------------------------------------
// GuiInspectorTypeAssetId
//-----------------------------------------------------------------------------

IMPLEMENT_CONOBJECT(GuiInspectorTypeTerrainAssetPtr);

ConsoleDocClass(GuiInspectorTypeTerrainAssetPtr,
   "@brief Inspector field type for Material Asset Objects\n\n"
   "Editor use only.\n\n"
   "@internal"
);

void GuiInspectorTypeTerrainAssetPtr::consoleInit()
{
   Parent::consoleInit();

   ConsoleBaseType::getType(TypeTerrainAssetPtr)->setInspectorFieldType("GuiInspectorTypeTerrainAssetPtr");
}

GuiControl* GuiInspectorTypeTerrainAssetPtr::constructEditControl()
{
   // Create base filename edit controls
   GuiControl* retCtrl = Parent::constructEditControl();
   if (retCtrl == NULL)
      return retCtrl;

   // Change filespec
   char szBuffer[512];
   dSprintf(szBuffer, sizeof(szBuffer), "AssetBrowser.showDialog(\"TerrainAsset\", \"AssetBrowser.changeAsset\", %s, %s);",
      mInspector->getIdString(), mCaption);
   mBrowseButton->setField("Command", szBuffer);

   setDataField(StringTable->insert("targetObject"), NULL, mInspector->getInspectObject()->getIdString());

   // Create "Open in ShapeEditor" button
   mShapeEdButton = new GuiBitmapButtonCtrl();

   mShapeEdButton->setField("Command", "EditorGui.setEditor(TerrainEditorPlugin);");

   char bitmapName[512] = "ToolsModule:TerrainBlock_image";
   mShapeEdButton->setBitmap(StringTable->insert(bitmapName));

   mShapeEdButton->setDataField(StringTable->insert("Profile"), NULL, "GuiButtonProfile");
   mShapeEdButton->setDataField(StringTable->insert("tooltipprofile"), NULL, "GuiToolTipProfile");
   mShapeEdButton->setDataField(StringTable->insert("hovertime"), NULL, "1000");
   mShapeEdButton->setDataField(StringTable->insert("tooltip"), NULL, "Open this file in the Shape Editor");

   mShapeEdButton->registerObject();
   addObject(mShapeEdButton);

   return retCtrl;
}

bool GuiInspectorTypeTerrainAssetPtr::updateRects()
{
   S32 dividerPos, dividerMargin;
   mInspector->getDivider(dividerPos, dividerMargin);
   Point2I fieldExtent = getExtent();
   Point2I fieldPos = getPosition();

   mCaptionRect.set(0, 0, fieldExtent.x - dividerPos - dividerMargin, fieldExtent.y);
   mEditCtrlRect.set(fieldExtent.x - dividerPos + dividerMargin, 1, dividerPos - dividerMargin - 34, fieldExtent.y);

   bool resized = mEdit->resize(mEditCtrlRect.point, mEditCtrlRect.extent);
   if (mBrowseButton != NULL)
   {
      mBrowseRect.set(fieldExtent.x - 32, 2, 14, fieldExtent.y - 4);
      resized |= mBrowseButton->resize(mBrowseRect.point, mBrowseRect.extent);
   }

   if (mShapeEdButton != NULL)
   {
      RectI shapeEdRect(fieldExtent.x - 16, 2, 14, fieldExtent.y - 4);
      resized |= mShapeEdButton->resize(shapeEdRect.point, shapeEdRect.extent);
   }

   return resized;
}

IMPLEMENT_CONOBJECT(GuiInspectorTypeTerrainAssetId);

ConsoleDocClass(GuiInspectorTypeTerrainAssetId,
   "@brief Inspector field type for Shapes\n\n"
   "Editor use only.\n\n"
   "@internal"
);

void GuiInspectorTypeTerrainAssetId::consoleInit()
{
   Parent::consoleInit();

   ConsoleBaseType::getType(TypeTerrainAssetId)->setInspectorFieldType("GuiInspectorTypeTerrainAssetId");
}
#endif
