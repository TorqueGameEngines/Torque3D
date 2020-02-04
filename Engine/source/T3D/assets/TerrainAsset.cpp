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

TerrainAsset::TerrainAsset()
{
   mTerrainFilePath = StringTable->EmptyString();
}

//-----------------------------------------------------------------------------

TerrainAsset::~TerrainAsset()
{
}

//-----------------------------------------------------------------------------

void TerrainAsset::initPersistFields()
{
   // Call parent.
   Parent::initPersistFields();

   //addField("shaderGraph", TypeRealString, Offset(mShaderGraphFile, TerrainAsset), "");
   addProtectedField("terrainFile", TypeAssetLooseFilePath, Offset(mTerrainFilePath, TerrainAsset),
      &setTerrainFilePath, &getTerrainFilePath, "Path to the file containing the terrain data.");
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

   mTerrainFilePath = expandAssetFilePath(mTerrainFilePath);

   loadTerrain();
}

void TerrainAsset::onAssetRefresh()
{
   mTerrainFilePath = expandAssetFilePath(mTerrainFilePath);

   loadTerrain();
}

void TerrainAsset::setTerrainFilePath(const char* pScriptFile)
{
   // Sanity!
   AssertFatal(pScriptFile != NULL, "Cannot use a NULL script file.");

   // Fetch image file.
   pScriptFile = StringTable->insert(pScriptFile);

   // Update.
   mTerrainFilePath = pScriptFile;

   // Refresh the asset.
   refreshAsset();
}

bool TerrainAsset::loadTerrain()
{
   if (!Platform::isFile(mTerrainFilePath))
      return false;

   mTerrMaterialAssets.clear();
   mTerrMaterialAssetIds.clear();

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

         if (assetType == StringTable->insert("TerrainMaterialAsset"))
         {
            mTerrMaterialAssetIds.push_front(assetDependenciesItr->value);

            //Force the asset to become initialized if it hasn't been already
            AssetPtr<TerrainMaterialAsset> matAsset = assetDependenciesItr->value;

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

void TerrainAsset::copyTo(SimObject* object)
{
   // Call to parent.
   Parent::copyTo(object);
}

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
   mUseHeightOverride = true;
   mHeightOverride = 100;

   mMatEdContainer = new GuiControl();
   mMatEdContainer->registerObject();

   addObject(mMatEdContainer);

   // Create "Open in ShapeEditor" button
   mMatPreviewButton = new GuiBitmapButtonCtrl();

   const char* matAssetId = getData();

   TerrainAsset* matAsset = AssetDatabase.acquireAsset< TerrainAsset>(matAssetId);

   //TerrainMaterial* materialDef = nullptr;

   char bitmapName[512] = "tools/worldEditor/images/toolbar/shape-editor";

   /*if (!Sim::findObject(matAsset->getMaterialDefinitionName(), materialDef))
   {
      Con::errorf("GuiInspectorTypeTerrainAssetPtr::constructEditControl() - unable to find material in asset");
   }
   else
   {
      mMatPreviewButton->setBitmap(materialDef->mDiffuseMapFilename[0]);
   }*/

   mMatPreviewButton->setPosition(0, 0);
   mMatPreviewButton->setExtent(100,100);

   // Change filespec
   char szBuffer[512];
   dSprintf(szBuffer, sizeof(szBuffer), "AssetBrowser.showDialog(\"TerrainAsset\", \"AssetBrowser.changeAsset\", %d, %s);",
      mInspector->getComponentGroupTargetId(), mCaption);
   mMatPreviewButton->setField("Command", szBuffer);

   mMatPreviewButton->setDataField(StringTable->insert("Profile"), NULL, "GuiButtonProfile");
   mMatPreviewButton->setDataField(StringTable->insert("tooltipprofile"), NULL, "GuiToolTipProfile");
   mMatPreviewButton->setDataField(StringTable->insert("hovertime"), NULL, "1000");

   StringBuilder strbld;
   /*strbld.append(matAsset->getMaterialDefinitionName());
   strbld.append("\n");
   strbld.append("Open this file in the Material Editor");*/

   mMatPreviewButton->setDataField(StringTable->insert("tooltip"), NULL, strbld.data());

   _registerEditControl(mMatPreviewButton);
   //mMatPreviewButton->registerObject();
   mMatEdContainer->addObject(mMatPreviewButton);

   mMatAssetIdTxt = new GuiTextEditCtrl();
   mMatAssetIdTxt->registerObject();
   mMatAssetIdTxt->setActive(false);

   mMatAssetIdTxt->setText(matAssetId);

   mMatAssetIdTxt->setBounds(100, 0, 150, 18);
   mMatEdContainer->addObject(mMatAssetIdTxt);

   return mMatEdContainer;
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

   if (mMatEdContainer != nullptr)
   {
      mMatPreviewButton->resize(mEditCtrlRect.point, mEditCtrlRect.extent);
   }

   if (mMatPreviewButton != nullptr)
   {
      mMatPreviewButton->resize(Point2I::Zero, Point2I(100, 100));
   }

   if (mMatAssetIdTxt != nullptr)
   {
      mMatAssetIdTxt->resize(Point2I(100, 0), Point2I(mEditCtrlRect.extent.x - 100, 18));
   }

   return resized;
}
