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

StringTableEntry MaterialAsset::smNoMaterialAssetFallback = NULL;

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
   
   smNoMaterialAssetFallback = StringTable->insert(Con::getVariable("$Core::NoMaterialAssetFallback"));
}

void MaterialAsset::initPersistFields()
{
   docsURL;
   // Call parent.
   Parent::initPersistFields();

   //addField("shaderGraph", TypeRealString, Offset(mShaderGraphFile, MaterialAsset), "");
   //addProtectedField("scriptFile", TypeAssetLooseFilePath, Offset(mScriptFile, MaterialAsset),
   //   &setScriptFile, &getScriptFile, "Path to the file containing the material definition.");
   addField("scriptFile", TypeAssetLooseFilePath, Offset(mScriptFile, MaterialAsset), "");

   addField("materialDefinitionName", TypeString, Offset(mMatDefinitionName, MaterialAsset), "Name of the material definition this asset is for.");
}

void MaterialAsset::initializeAsset()
{
   // Call parent.
   Parent::initializeAsset();

   mScriptPath = getOwned() ? expandAssetFilePath(mScriptFile) : mScriptPath;

   if (mMatDefinitionName == StringTable->EmptyString())
   {
      mLoadedState = Failed;
      return;
   }

   if (size() != 0 && mScriptPath == StringTable->EmptyString())
   {
      mLoadedState = EmbeddedDefinition;
   }
   else if (Torque::FS::IsScriptFile(mScriptPath))
   {
      if (!Sim::findObject(mMatDefinitionName))
      {
          if (Con::executeFile(mScriptPath, false, false))
          {
              mLoadedState = ScriptLoaded;
          }
          else
          {
              mLoadedState = Failed;
          }
      }
      else
      {
         mLoadedState = DefinitionAlreadyExists;
      }
   }

   loadMaterial();
}

void MaterialAsset::onAssetRefresh()
{
   mScriptPath = getOwned() ? expandAssetFilePath(mScriptFile) : mScriptPath;

   if (mMatDefinitionName == StringTable->EmptyString())
   {
      mLoadedState = Failed;
      return;
   }

   if (Torque::FS::IsScriptFile(mScriptPath))
   {
      //Since we're refreshing, we can assume that the file we're executing WILL have an existing definition.
      //But that definition, whatever it is, is the 'correct' one, so we enable the Replace Existing behavior
      //when the engine encounters a named object conflict.
      String redefineBehaviorPrev = Con::getVariable("$Con::redefineBehavior");
      Con::setVariable("$Con::redefineBehavior", "replaceExisting");

      if (Con::executeFile(mScriptPath, false, false))
         mLoadedState = ScriptLoaded;
      else
         mLoadedState = Failed;

      //And now that we've executed, switch back to the prior behavior
      Con::setVariable("$Con::redefineBehavior", redefineBehaviorPrev.c_str());
   }

   loadMaterial();
}

void MaterialAsset::setScriptFile(const char* pScriptFile)
{
   // Sanity!
   AssertFatal(pScriptFile != NULL, "Cannot use a NULL script file.");

   pScriptFile = StringTable->insert(pScriptFile, true);

   // Update.
   mScriptFile = getOwned() ? expandAssetFilePath(pScriptFile) : pScriptFile;

   // Refresh the asset.
   refreshAsset();
}

//------------------------------------------------------------------------------

void MaterialAsset::loadMaterial()
{
   if (mMaterialDefinition)
   {
      mMaterialDefinition->safeDeleteObject();
   }

   if (mLoadedState == EmbeddedDefinition)
   {
      if (size() != 0)
      {
         for (U32 i = 0; i < size(); i++)
         {
            mMaterialDefinition = dynamic_cast<Material*>(getObject(i));
            if (mMaterialDefinition)
            {
               mLoadedState = Ok;
               mMaterialDefinition->setInternalName(getAssetId());
               mMaterialDefinition->reload();
               return;
            }
         }
      }
   }
   else if ((mLoadedState == ScriptLoaded || mLoadedState == DefinitionAlreadyExists) && mMatDefinitionName != StringTable->EmptyString())
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
      mMaterialDefinition->setInternalName(getAssetId());
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
U32 MaterialAsset::getAssetByMaterialName(StringTableEntry matName, AssetPtr<MaterialAsset>* matAsset)
{
   AssetQuery query;
   U32 foundAssetcount = AssetDatabase.findAssetType(&query, "MaterialAsset");
   if (foundAssetcount == 0)
   {
      //Didn't work, so have us fall back to a placeholder asset
      matAsset->setAssetId(MaterialAsset::smNoMaterialAssetFallback);

      if (matAsset->isNull())
      {
         //Well that's bad, loading the fallback failed.
         Con::warnf("MaterialAsset::getAssetByMaterialName - Finding of asset associated with material name %s failed with no fallback asset", matName);
         return AssetErrCode::Failed;
      }

      //handle noshape not being loaded itself
      if ((*matAsset)->mLoadedState == BadFileReference)
      {
         Con::warnf("MaterialAsset::getAssetByMaterialName - Finding of associated with aterial name %s failed, and fallback asset reported error of Bad File Reference.", matName);
         return AssetErrCode::BadFileReference;
      }

      Con::warnf("MaterialAsset::getAssetByMaterialName - Finding of associated with aterial name %s failed, utilizing fallback asset", matName);

      (*matAsset)->mLoadedState = AssetErrCode::UsingFallback;
      return AssetErrCode::UsingFallback;
   }
   else
   {
      for (U32 i = 0; i < foundAssetcount; i++)
      {
         MaterialAsset* tMatAsset = AssetDatabase.acquireAsset<MaterialAsset>(query.mAssetList[i]);
         if (tMatAsset && tMatAsset->getMaterialDefinitionName() == matName)
         {
            matAsset->setAssetId(query.mAssetList[i]);
            AssetDatabase.releaseAsset(query.mAssetList[i]);
            return (*matAsset)->mLoadedState;
         }
         AssetDatabase.releaseAsset(query.mAssetList[i]); //cleanup if that's not the one we needed
      }
   }

   //Somehow we failed to bind an asset, so just use the fallback and mark the failure
   matAsset->setAssetId(MaterialAsset::smNoMaterialAssetFallback);
   (*matAsset)->mLoadedState = AssetErrCode::UsingFallback;
   return AssetErrCode::UsingFallback;

}

StringTableEntry MaterialAsset::getAssetIdByMaterialName(StringTableEntry matName)
{
   if (matName == StringTable->EmptyString())
      return StringTable->EmptyString();

   StringTableEntry materialAssetId = MaterialAsset::smNoMaterialAssetFallback;

   AssetQuery query;
   U32 foundCount = AssetDatabase.findAssetType(&query, "MaterialAsset");
   if (foundCount != 0)
   {
      for (U32 i = 0; i < foundCount; i++)
      {
         MaterialAsset* matAsset = AssetDatabase.acquireAsset<MaterialAsset>(query.mAssetList[i]);
         if (matAsset && matAsset->getMaterialDefinitionName() == matName)
         {
            materialAssetId = matAsset->getAssetId();
            AssetDatabase.releaseAsset(query.mAssetList[i]);
            break;
         }
         AssetDatabase.releaseAsset(query.mAssetList[i]);
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

      if (materialAsset->isNull())
      {
         //Well that's bad, loading the fallback failed.
         Con::warnf("MaterialAsset::getAssetById - Finding of asset with id %s failed with no fallback asset", assetId);
         return AssetErrCode::Failed;
      }

      //handle noshape not being loaded itself
      if ((*materialAsset)->mLoadedState == BadFileReference)
      {
         Con::warnf("MaterialAsset::getAssetById - Finding of asset with id %s failed, and fallback asset reported error of Bad File Reference.", assetId);
         return AssetErrCode::BadFileReference;
      }

      Con::warnf("MaterialAsset::getAssetById - Finding of asset with id %s failed, utilizing fallback asset", assetId);

      (*materialAsset)->mLoadedState = AssetErrCode::UsingFallback;
      return AssetErrCode::UsingFallback;
   }
}

SimObjectPtr<Material> MaterialAsset::findMaterialDefinitionByAssetId(StringTableEntry assetId)
{
   SimSet* matSet = MATMGR->getMaterialSet();
   if (matSet)
   {
      SimObjectPtr<Material> matDef = dynamic_cast<Material*>(matSet->findObjectByInternalName(assetId));
      return matDef;
   }
   return nullptr;
}

#ifdef TORQUE_TOOLS
DefineEngineStaticMethod(MaterialAsset, getAssetIdByMaterialName, const char*, (const char* materialName), (""),
   "Queries the Asset Database to see if any asset exists that is associated with the provided material name.\n"
   "@return The AssetId of the associated asset, if any.")
{
   return MaterialAsset::getAssetIdByMaterialName(StringTable->insert(materialName));
}

//MaterialAsset::findMaterialDefinitionByAssetId("Prototyping:Detail")
DefineEngineStaticMethod(MaterialAsset, findMaterialDefinitionByAssetId, S32, (const char* assetId), (""),
   "Queries the MaterialSet to see if any MaterialDefinition exists that is associated to the provided assetId.\n"
   "@return The MaterialDefinition Id associated to the assetId, if any")
{
   SimObjectPtr<Material> matDef = MaterialAsset::findMaterialDefinitionByAssetId(StringTable->insert(assetId));
   if (matDef.isNull())
      return SimObjectId(0);
   else
      return matDef->getId();
}


DefineEngineMethod(MaterialAsset, getScriptPath, const char*, (), ,
   "Gets the script file path for the asset.")
{
   return object->getScriptPath();
}
#endif

#ifdef TORQUE_TOOLS
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

   const char* previewImage;

   if (mInspector->getInspectObject() != nullptr)
   {
      dSprintf(szBuffer, sizeof(szBuffer), "AssetBrowser.showDialog(\"MaterialAsset\", \"AssetBrowser.changeAsset\", %s, %s);",
         mInspector->getIdString(), mCaption);
      mBrowseButton->setField("Command", szBuffer);

      setDataField(StringTable->insert("targetObject"), NULL, mInspector->getInspectObject()->getIdString());

      previewImage = mInspector->getInspectObject()->getDataField(mCaption, NULL);
   }
   else
   {
      //if we don't have a target object, we'll be manipulating the desination value directly
      dSprintf(szBuffer, sizeof(szBuffer), "AssetBrowser.showDialog(\"MaterialAsset\", \"AssetBrowser.changeAsset\", %s, \"%s\");",
         mInspector->getIdString(), mVariableName);
      mBrowseButton->setField("Command", szBuffer);

      previewImage = Con::getVariable(mVariableName);
   }

   mLabel = new GuiTextCtrl();
   mLabel->registerObject();
   mLabel->setControlProfile(mProfile);
   mLabel->setText(mCaption);
   addObject(mLabel);

   //
   GuiTextEditCtrl* editTextCtrl = static_cast<GuiTextEditCtrl*>(retCtrl);
   GuiControlProfile* toolEditProfile;
   if (Sim::findObject("ToolsGuiTextEditProfile", toolEditProfile))
      editTextCtrl->setControlProfile(toolEditProfile);

   GuiControlProfile* toolDefaultProfile = nullptr;
   Sim::findObject("ToolsGuiDefaultProfile", toolDefaultProfile);

   //
   mPreviewImage = new GuiBitmapCtrl();
   mPreviewImage->registerObject();

   if(toolDefaultProfile)
      mPreviewImage->setControlProfile(toolDefaultProfile);

   updatePreviewImage();

   addObject(mPreviewImage);

   //
   mPreviewBorderButton = new GuiBitmapButtonCtrl();
   mPreviewBorderButton->registerObject();

   if(toolDefaultProfile)
      mPreviewBorderButton->setControlProfile(toolDefaultProfile);

   mPreviewBorderButton->_setBitmap(StringTable->insert("ToolsModule:cubemapBtnBorder_n_image"));

   mPreviewBorderButton->setField("Command", szBuffer); //clicking the preview does the same thing as the edit button, for simplicity
   addObject(mPreviewBorderButton);

   //
   // Create "Open in Editor" button
   mEditButton = new GuiBitmapButtonCtrl();

   dSprintf(szBuffer, sizeof(szBuffer), "AssetBrowser.editAsset(%d.getText());", retCtrl->getId());
   mEditButton->setField("Command", szBuffer);

   mEditButton->setText("Edit");
   mEditButton->setSizing(horizResizeLeft, vertResizeAspectTop);

   mEditButton->setDataField(StringTable->insert("Profile"), NULL, "ToolsGuiButtonProfile");
   mEditButton->setDataField(StringTable->insert("tooltipprofile"), NULL, "GuiToolTipProfile");
   mEditButton->setDataField(StringTable->insert("hovertime"), NULL, "1000");
   mEditButton->setDataField(StringTable->insert("tooltip"), NULL, "Open this asset in the Material Editor");

   mEditButton->registerObject();
   addObject(mEditButton);

   //
   mUseHeightOverride = true;
   mHeightOverride = 72;

   return retCtrl;
}

bool GuiInspectorTypeMaterialAssetPtr::updateRects()
{
   S32 rowSize = 18;
   S32 dividerPos, dividerMargin;
   mInspector->getDivider(dividerPos, dividerMargin);
   Point2I fieldExtent = getExtent();
   Point2I fieldPos = getPosition();

   mEditCtrlRect.set(0, 0, fieldExtent.x, fieldExtent.y);
   mLabel->resize(Point2I(mProfile->mTextOffset.x, 0), Point2I(fieldExtent.x, rowSize));

   RectI previewRect = RectI(Point2I(mProfile->mTextOffset.x, rowSize), Point2I(50, 50));
   mPreviewBorderButton->resize(previewRect.point, previewRect.extent);
   mPreviewImage->resize(previewRect.point, previewRect.extent);

   S32 editPos = previewRect.point.x + previewRect.extent.x + 10;
   mEdit->resize(Point2I(editPos, rowSize * 1.5), Point2I(fieldExtent.x - editPos - 5, rowSize));

   mEditButton->resize(Point2I(fieldExtent.x - 105, previewRect.point.y + previewRect.extent.y - rowSize), Point2I(100, rowSize));

   mBrowseButton->setHidden(true);

   return true;
}

void GuiInspectorTypeMaterialAssetPtr::updateValue()
{
   Parent::updateValue();

   updatePreviewImage();
}

void GuiInspectorTypeMaterialAssetPtr::updatePreviewImage()
{
   const char* previewImage;
   if (mInspector->getInspectObject() != nullptr)
      previewImage = mInspector->getInspectObject()->getDataField(mCaption, NULL);
   else
      previewImage = Con::getVariable(mVariableName);

   //if what we're working with isn't even a valid asset, don't present like we found a good one
   if (!AssetDatabase.isDeclaredAsset(previewImage))
   {
      mPreviewImage->_setBitmap(StringTable->EmptyString());
      return;
   }

   String matPreviewAssetId = String(previewImage) + "_PreviewImage";
   matPreviewAssetId.replace(":", "_");
   matPreviewAssetId = "ToolsModule:" + matPreviewAssetId;
   if (AssetDatabase.isDeclaredAsset(matPreviewAssetId.c_str()))
   {
      mPreviewImage->setBitmap(StringTable->insert(matPreviewAssetId.c_str()));
   }
   else
   {
      if (AssetDatabase.isDeclaredAsset(previewImage))
      {
         MaterialAsset* matAsset = AssetDatabase.acquireAsset<MaterialAsset>(previewImage);
         if (matAsset && matAsset->getMaterialDefinition())
         {
            mPreviewImage->_setBitmap(matAsset->getMaterialDefinition()->mDiffuseMapAssetId[0]);
         }
      }
   }

   if (mPreviewImage->getBitmapAsset().isNull())
      mPreviewImage->_setBitmap(StringTable->insert("ToolsModule:genericAssetIcon_image"));
}

void GuiInspectorTypeMaterialAssetPtr::setPreviewImage(StringTableEntry assetId)
{
   //if what we're working with isn't even a valid asset, don't present like we found a good one
   if (!AssetDatabase.isDeclaredAsset(assetId))
   {
      mPreviewImage->_setBitmap(StringTable->EmptyString());
      return;
   }

   String matPreviewAssetId = String(assetId) + "_PreviewImage";
   matPreviewAssetId.replace(":", "_");
   matPreviewAssetId = "ToolsModule:" + matPreviewAssetId;
   if (AssetDatabase.isDeclaredAsset(matPreviewAssetId.c_str()))
   {
      mPreviewImage->setBitmap(StringTable->insert(matPreviewAssetId.c_str()));
   }
   else
   {
      if (AssetDatabase.isDeclaredAsset(assetId))
      {
         MaterialAsset* matAsset = AssetDatabase.acquireAsset<MaterialAsset>(assetId);
         if (matAsset && matAsset->getMaterialDefinition())
         {
            mPreviewImage->_setBitmap(matAsset->getMaterialDefinition()->mDiffuseMapAssetId[0]);
         }
      }
   }

   if (mPreviewImage->getBitmapAsset().isNull())
      mPreviewImage->_setBitmap(StringTable->insert("ToolsModule:genericAssetIcon_image"));
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
#endif
