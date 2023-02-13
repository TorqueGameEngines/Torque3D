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

#ifndef CUBEMAP_ASSET_H
#include "CubemapAsset.h"
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

IMPLEMENT_CONOBJECT(CubemapAsset);

ConsoleType(CubemapAssetPtr, TypeCubemapAssetPtr, CubemapAsset, ASSET_ID_FIELD_PREFIX)

//-----------------------------------------------------------------------------

ConsoleGetType(TypeCubemapAssetPtr)
{
   // Fetch asset Id.
   return (*((AssetPtr<CubemapAsset>*)dptr)).getAssetId();
}

//-----------------------------------------------------------------------------

ConsoleSetType(TypeCubemapAssetPtr)
{
   // Was a single argument specified?
   if (argc == 1)
   {
      // Yes, so fetch field value.
      const char* pFieldValue = argv[0];

      // Fetch asset pointer.
      AssetPtr<CubemapAsset>* pAssetPtr = dynamic_cast<AssetPtr<CubemapAsset>*>((AssetPtrBase*)(dptr));

      // Is the asset pointer the correct type?
      if (pAssetPtr == NULL)
      {
         // No, so fail.
         //Con::warnf("(TypeCubemapAssetPtr) - Failed to set asset Id '%d'.", pFieldValue);
         return;
      }

      // Set asset.
      pAssetPtr->setAssetId(pFieldValue);

      return;
   }

   // Warn.
   Con::warnf("(TypeCubemapAssetPtr) - Cannot set multiple args to a single asset.");
}

//-----------------------------------------------------------------------------

CubemapAsset::CubemapAsset()
{
   mComponentName = StringTable->EmptyString();
   mComponentClass = StringTable->EmptyString();
   mFriendlyName = StringTable->EmptyString();
   mComponentType = StringTable->EmptyString();
   mDescription = StringTable->EmptyString();

   mScriptFile = StringTable->EmptyString();
}

//-----------------------------------------------------------------------------

CubemapAsset::~CubemapAsset()
{
}

//-----------------------------------------------------------------------------

void CubemapAsset::initPersistFields()
{
   docsURL;
   // Call parent.
   Parent::initPersistFields();

   addField("componentName", TypeString, Offset(mComponentName, CubemapAsset), "Unique Name of the component. Defines the namespace of the scripts for the component.");
   addField("componentClass", TypeString, Offset(mComponentClass, CubemapAsset), "Class of object this component uses.");
   addField("friendlyName", TypeString, Offset(mFriendlyName, CubemapAsset), "The human-readble name for the component.");
   addField("componentType", TypeString, Offset(mComponentType, CubemapAsset), "The category of the component for organizing in the editor.");
   addField("description", TypeString, Offset(mDescription, CubemapAsset), "Simple description of the component.");

   addProtectedField("scriptFile", TypeAssetLooseFilePath, Offset(mScriptFile, CubemapAsset),
      &setScriptFile, &getScriptFile, "A script file with additional scripted functionality for this component.");
}

//------------------------------------------------------------------------------

void CubemapAsset::copyTo(SimObject* object)
{
   // Call to parent.
   Parent::copyTo(object);
}

void CubemapAsset::initializeAsset()
{
   // Call parent.
   Parent::initializeAsset();

   mScriptPath = getOwned() ? expandAssetFilePath(mScriptFile) : mScriptPath;

   if (Torque::FS::IsScriptFile(mScriptPath))
      Con::executeFile(mScriptPath, false, false);
}

void CubemapAsset::onAssetRefresh()
{
   mScriptPath = getOwned() ? expandAssetFilePath(mScriptFile) : mScriptPath;

   if (Torque::FS::IsScriptFile(mScriptPath))
      Con::executeFile(mScriptPath, false, false);
}

void CubemapAsset::setScriptFile(const char* pScriptFile)
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
#ifdef TORQUE_TOOLS
//-----------------------------------------------------------------------------
// GuiInspectorTypeAssetId
//-----------------------------------------------------------------------------

IMPLEMENT_CONOBJECT(GuiInspectorTypeCubemapAssetPtr);

ConsoleDocClass(GuiInspectorTypeCubemapAssetPtr,
   "@brief Inspector field type for Shapes\n\n"
   "Editor use only.\n\n"
   "@internal"
);

void GuiInspectorTypeCubemapAssetPtr::consoleInit()
{
   Parent::consoleInit();

   ConsoleBaseType::getType(TypeCubemapAssetPtr)->setInspectorFieldType("GuiInspectorTypeCubemapAssetPtr");
}

GuiControl* GuiInspectorTypeCubemapAssetPtr::constructEditControl()
{
   // Create base filename edit controls
   GuiControl* retCtrl = Parent::constructEditControl();
   if (retCtrl == NULL)
      return retCtrl;

   // Change filespec
   char szBuffer[512];
   dSprintf(szBuffer, sizeof(szBuffer), "AssetBrowser.showDialog(\"CubemapAsset\", \"AssetBrowser.changeAsset\", %d, %s);",
      mInspector->getIdString(), mCaption);
   mBrowseButton->setField("Command", szBuffer);

   setDataField(StringTable->insert("object"), NULL, String::ToString(mInspector->getInspectObject()).c_str());

   // Create "Open in ShapeEditor" button
   mShapeEdButton = new GuiBitmapButtonCtrl();

   dSprintf(szBuffer, sizeof(szBuffer), "CubemapEditor.openCubemapAsset(%d.getText());", retCtrl->getId());
   mShapeEdButton->setField("Command", szBuffer);

   char bitmapName[512] = "ToolsModule:shape_editor_n_image";
   mShapeEdButton->setBitmap(StringTable->insert(bitmapName));

   mShapeEdButton->setDataField(StringTable->insert("Profile"), NULL, "GuiButtonProfile");
   mShapeEdButton->setDataField(StringTable->insert("tooltipprofile"), NULL, "GuiToolTipProfile");
   mShapeEdButton->setDataField(StringTable->insert("hovertime"), NULL, "1000");
   mShapeEdButton->setDataField(StringTable->insert("tooltip"), NULL, "Open this file in the Shape Editor");

   mShapeEdButton->registerObject();
   addObject(mShapeEdButton);

   return retCtrl;
}

bool GuiInspectorTypeCubemapAssetPtr::updateRects()
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
#endif
