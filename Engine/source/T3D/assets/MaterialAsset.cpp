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
#pragma once

#ifndef MATERIALASSET_H
#include "MaterialAsset.h"
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

#include "T3D/assets/assetImporter.h"

StringTableEntry MaterialAsset::smNoMaterialAssetFallback(StringTable->insert(Con::getVariable("$Core::NoMaterialAssetFallback")));

//-----------------------------------------------------------------------------

IMPLEMENT_CONOBJECT(MaterialAsset);

ConsoleType(MaterialAssetPtr, TypeMaterialAssetPtr, MaterialAsset, ASSET_ID_FIELD_PREFIX)

//-----------------------------------------------------------------------------

ConsoleGetType(TypeMaterialAssetPtr)
{
   // Fetch asset Id.
   return (*((AssetPtr<MaterialAsset>*)dptr)).getAssetId();
}

//-----------------------------------------------------------------------------

ConsoleSetType(TypeMaterialAssetPtr)
{
   // Was a single argument specified?
   if (argc == 1)
   {
      // Yes, so fetch field value.
      const char* pFieldValue = argv[0];

      // Fetch asset pointer.
      AssetPtr<MaterialAsset>* pAssetPtr = dynamic_cast<AssetPtr<MaterialAsset>*>((AssetPtrBase*)(dptr));

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
   Con::warnf("(TypeMaterialAssetPtr) - Cannot set multiple args to a single asset.");
}


ConsoleType(assetIdString, TypeMaterialAssetId, const char*, ASSET_ID_FIELD_PREFIX)

ConsoleGetType(TypeMaterialAssetId)
{
   // Fetch asset Id.
   return *((const char**)(dptr));
}

ConsoleSetType(TypeMaterialAssetId)
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
   Con::warnf("(TypeMaterialAssetId) - Cannot set multiple args to a single asset.");
}
//-----------------------------------------------------------------------------

MaterialAsset::MaterialAsset()
{
   mShaderGraphFile = "";
   mScriptFile = StringTable->EmptyString();
   mScriptPath = StringTable->EmptyString();
   mMatDefinitionName = StringTable->EmptyString();
   mMaterialDefinition = nullptr;
}

//-----------------------------------------------------------------------------

MaterialAsset::~MaterialAsset()
{
   //SAFE_DELETE(mMaterialDefinition);
}

//-----------------------------------------------------------------------------

void MaterialAsset::consoleInit()
{
   Parent::consoleInit();
   Con::addVariable("$Core::NoMaterialAssetFallback", TypeString, &smNoMaterialAssetFallback,
      "The assetId of the material to display when the requested material asset is missing.\n"
      "@ingroup GFX\n");
}

void MaterialAsset::initPersistFields()
{
   // Call parent.
   Parent::initPersistFields();

   //addField("shaderGraph", TypeRealString, Offset(mShaderGraphFile, MaterialAsset), "");
   addProtectedField("scriptFile", TypeAssetLooseFilePath, Offset(mScriptFile, MaterialAsset),
      &setScriptFile, &getScriptFile, "Path to the file containing the material definition.");

   addField("materialDefinitionName", TypeString, Offset(mMatDefinitionName, MaterialAsset), "Name of the material definition this asset is for.");
}

void MaterialAsset::initializeAsset()
{
   // Call parent.
   Parent::initializeAsset();

   mScriptPath = getOwned() ? expandAssetFilePath(mScriptFile) : mScriptPath;

   if (Platform::isFile(mScriptPath))
      Con::executeFile(mScriptPath, false, false);

   loadMaterial();
}

void MaterialAsset::onAssetRefresh()
{
   mScriptPath = getOwned() ? expandAssetFilePath(mScriptFile) : mScriptPath;

   if (Platform::isFile(mScriptPath))
      Con::executeFile(mScriptPath, false, false);

   loadMaterial();
}

void MaterialAsset::setScriptFile(const char* pScriptFile)
{
   // Sanity!
   AssertFatal(pScriptFile != NULL, "Cannot use a NULL script file.");

   // Fetch image file.
   pScriptFile = StringTable->insert(pScriptFile);

   // Update.
   mScriptFile = getOwned() ? expandAssetFilePath(pScriptFile) : pScriptFile;

   // Refresh the asset.
   refreshAsset();
}

//------------------------------------------------------------------------------

void MaterialAsset::loadMaterial()
{
   if (mMaterialDefinition)
      SAFE_DELETE(mMaterialDefinition);

   if (mMatDefinitionName != StringTable->EmptyString())
   {
      Material* matDef;
      if (!Sim::findObject(mMatDefinitionName, matDef))
      {
         Con::errorf("MaterialAsset: Unable to find the Material %s", mMatDefinitionName);
         mLoadedState = BadFileReference;
         return;
      }

      mMaterialDefinition = matDef;

      mLoadedState = Ok;

      mMaterialDefinition->reload();
      return;
   }

   mLoadedState = Failed;
}

//------------------------------------------------------------------------------

void MaterialAsset::copyTo(SimObject* object)
{
   // Call to parent.
   Parent::copyTo(object);
}

//------------------------------------------------------------------------------
bool MaterialAsset::getAssetByMaterialName(StringTableEntry matName, AssetPtr<MaterialAsset>* matAsset)
{
   AssetQuery* query = new AssetQuery();
   U32 foundCount = AssetDatabase.findAssetType(query, "MaterialAsset");
   if (foundCount != 0)
   {
      for (U32 i = 0; i < foundCount; i++)
      {
         MaterialAsset* tMatAsset = AssetDatabase.acquireAsset<MaterialAsset>(query->mAssetList[i]);
         if (tMatAsset && tMatAsset->getMaterialDefinitionName() == matName)
         {
            AssetDatabase.releaseAsset(query->mAssetList[i]);
            matAsset->setAssetId(query->mAssetList[i]);
            return true;
         }
         AssetDatabase.releaseAsset(query->mAssetList[i]); //cleanup if that's not the one we needed
      }
   }

   //Didn't work, so have us fall back to a placeholder asset
   matAsset->setAssetId(MaterialAsset::smNoMaterialAssetFallback);

   if (!matAsset->isNull())
   {
      Con::warnf("MaterialAsset::getAssetByMaterialName - Finding of material(%s) associated to asset failed, utilizing fallback asset", matName);
      return false;
   }

   //That didn't work, so fail out
   Con::warnf("MaterialAsset::getAssetByMaterialName -  Finding of material(%s) associated to asset failed with no fallback asset", matName);
   return false;
}

StringTableEntry MaterialAsset::getAssetIdByMaterialName(StringTableEntry matName)
{
   StringTableEntry materialAssetId = StringTable->EmptyString();

   AssetQuery* query = new AssetQuery();
   U32 foundCount = AssetDatabase.findAssetType(query, "MaterialAsset");
   if (foundCount == 0)
   {
      //Didn't work, so have us fall back to a placeholder asset
      materialAssetId = MaterialAsset::smNoMaterialAssetFallback;
   }
   else
   {
      for (U32 i = 0; i < foundCount; i++)
      {
         MaterialAsset* matAsset = AssetDatabase.acquireAsset<MaterialAsset>(query->mAssetList[i]);
         if (matAsset && matAsset->getMaterialDefinitionName() == matName)
         {
            materialAssetId = matAsset->getAssetId();
            AssetDatabase.releaseAsset(query->mAssetList[i]);
            break;
         }
         AssetDatabase.releaseAsset(query->mAssetList[i]);
      }
   }

   return materialAssetId;
}

U32 MaterialAsset::getAssetById(StringTableEntry assetId, AssetPtr<MaterialAsset>* materialAsset)
{
   (*materialAsset) = assetId;

   if (materialAsset->notNull())
   {
      return (*materialAsset)->mLoadedState;
   }
   else
   {
      //Didn't work, so have us fall back to a placeholder asset
      materialAsset->setAssetId(MaterialAsset::smNoMaterialAssetFallback);

      if ((*materialAsset)->mLoadedState == BadFileReference)
         return AssetErrCode::BadFileReference;

      (*materialAsset)->mLoadedState = AssetErrCode::UsingFallback;
      return AssetErrCode::UsingFallback;
   }

   return AssetErrCode::Failed;
}

#ifdef TORQUE_TOOLS
DefineEngineStaticMethod(MaterialAsset, getAssetIdByMaterialName, const char*, (const char* materialName), (""),
   "Queries the Asset Database to see if any asset exists that is associated with the provided material name.\n"
   "@return The AssetId of the associated asset, if any.")
{
   return MaterialAsset::getAssetIdByMaterialName(StringTable->insert(materialName));
}
#endif

//-----------------------------------------------------------------------------
// GuiInspectorTypeAssetId
//-----------------------------------------------------------------------------

IMPLEMENT_CONOBJECT(GuiInspectorTypeMaterialAssetPtr);

ConsoleDocClass(GuiInspectorTypeMaterialAssetPtr,
   "@brief Inspector field type for Shapes\n\n"
   "Editor use only.\n\n"
   "@internal"
);

void GuiInspectorTypeMaterialAssetPtr::consoleInit()
{
   Parent::consoleInit();

   ConsoleBaseType::getType(TypeMaterialAssetPtr)->setInspectorFieldType("GuiInspectorTypeMaterialAssetPtr");
}

GuiControl* GuiInspectorTypeMaterialAssetPtr::constructEditControl()
{
   // Create base filename edit controls
   GuiControl* retCtrl = Parent::constructEditControl();
   if (retCtrl == NULL)
      return retCtrl;

   // Change filespec
   char szBuffer[512];
   dSprintf(szBuffer, sizeof(szBuffer), "AssetBrowser.showDialog(\"MaterialAsset\", \"AssetBrowser.changeAsset\", %s, \"\");",
      getIdString());
   mBrowseButton->setField("Command", szBuffer);

   setDataField(StringTable->insert("targetObject"), NULL, mInspector->getInspectObject()->getIdString());

   // Create "Open in Editor" button
   mEditButton = new GuiBitmapButtonCtrl();

   dSprintf(szBuffer, sizeof(szBuffer), "AssetBrowser.editAsset(%d.getText());", retCtrl->getId());
   mEditButton->setField("Command", szBuffer);

   char bitmapName[512] = "tools/worldEditor/images/toolbar/material-editor";
   mEditButton->setBitmap(bitmapName);

   mEditButton->setDataField(StringTable->insert("Profile"), NULL, "GuiButtonProfile");
   mEditButton->setDataField(StringTable->insert("tooltipprofile"), NULL, "GuiToolTipProfile");
   mEditButton->setDataField(StringTable->insert("hovertime"), NULL, "1000");
   mEditButton->setDataField(StringTable->insert("tooltip"), NULL, "Open this file in the Material Editor");

   mEditButton->registerObject();
   addObject(mEditButton);

   return retCtrl;
}

bool GuiInspectorTypeMaterialAssetPtr::updateRects()
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

   if (mEditButton != NULL)
   {
      RectI shapeEdRect(fieldExtent.x - 16, 2, 14, fieldExtent.y - 4);
      resized |= mEditButton->resize(shapeEdRect.point, shapeEdRect.extent);
   }

   return resized;
}

IMPLEMENT_CONOBJECT(GuiInspectorTypeMaterialAssetId);

ConsoleDocClass(GuiInspectorTypeMaterialAssetId,
   "@brief Inspector field type for Material Assets\n\n"
   "Editor use only.\n\n"
   "@internal"
);

void GuiInspectorTypeMaterialAssetId::consoleInit()
{
   Parent::consoleInit();

   ConsoleBaseType::getType(TypeMaterialAssetId)->setInspectorFieldType("GuiInspectorTypeMaterialAssetId");
}
