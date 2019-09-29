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
   mTerrainFile = StringTable->EmptyString();
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
   addProtectedField("terrainFile", TypeAssetLooseFilePath, Offset(mTerrainFile, TerrainAsset),
      &setTerrainFile, &getTerrainFile, "Path to the file containing the terrain data.");
}

void TerrainAsset::initializeAsset()
{
   // Call parent.
   Parent::initializeAsset();

   if (!Platform::isFullPath(mTerrainFile))
      mTerrainFile = getOwned() ? expandAssetFilePath(mTerrainFile) : mTerrainFile;

   //if (Platform::isFile(mTerrainFile))
   //   Con::executeFile(mScriptFile, false, false);
}

void TerrainAsset::onAssetRefresh()
{
   mTerrainFile = expandAssetFilePath(mTerrainFile);

   //if (Platform::isFile(mScriptFile))
   //   Con::executeFile(mScriptFile, false, false);
}

void TerrainAsset::setTerrainFile(const char* pScriptFile)
{
   // Sanity!
   AssertFatal(pScriptFile != NULL, "Cannot use a NULL script file.");

   // Fetch image file.
   pScriptFile = StringTable->insert(pScriptFile);

   // Update.
   mTerrainFile = getOwned() ? expandAssetFilePath(pScriptFile) : pScriptFile;

   // Refresh the asset.
   refreshAsset();
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

   TerrainMaterial* materialDef = nullptr;

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

void GuiInspectorTypeTerrainAssetPtr::setMaterialAsset(String assetId)
{
   mTargetObject->setDataField(mCaption, "", assetId);

   //force a refresh
   SimObject* obj = mInspector->getInspectObject();
   mInspector->inspectObject(obj);
}

DefineEngineMethod(GuiInspectorTypeTerrainAssetPtr, setMaterialAsset, void, (String assetId), (""),
   "Gets a particular shape animation asset for this shape.\n"
   "@param animation asset index.\n"
   "@return Shape Animation Asset.\n")
{
   if (assetId == String::EmptyString)
      return;

   return object->setMaterialAsset(assetId);
}
