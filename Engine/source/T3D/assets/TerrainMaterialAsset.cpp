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

#ifndef TERRAINMATERIALASSET_H
#include "TerrainMaterialAsset.h"
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

StringTableEntry TerrainMaterialAsset::smNoTerrainMaterialAssetFallback = NULL;

//-----------------------------------------------------------------------------

IMPLEMENT_CONOBJECT(TerrainMaterialAsset);

ConsoleType(TerrainMaterialAssetPtr, TypeTerrainMaterialAssetPtr, TerrainMaterialAsset, ASSET_ID_FIELD_PREFIX)

//-----------------------------------------------------------------------------

ConsoleGetType(TypeTerrainMaterialAssetPtr)
{
   // Fetch asset Id.
   return (*((AssetPtr<TerrainMaterialAsset>*)dptr)).getAssetId();
}

//-----------------------------------------------------------------------------

ConsoleSetType(TypeTerrainMaterialAssetPtr)
{
   // Was a single argument specified?
   if (argc == 1)
   {
      // Yes, so fetch field value.
      const char* pFieldValue = argv[0];

      // Fetch asset pointer.
      AssetPtr<TerrainMaterialAsset>* pAssetPtr = dynamic_cast<AssetPtr<TerrainMaterialAsset>*>((AssetPtrBase*)(dptr));

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
   Con::warnf("(TypeTerrainMaterialAssetPtr) - Cannot set multiple args to a single asset.");
}


ConsoleType(assetIdString, TypeTerrainMaterialAssetId, const char*, ASSET_ID_FIELD_PREFIX)

ConsoleGetType(TypeTerrainMaterialAssetId)
{
   // Fetch asset Id.
   return *((const char**)(dptr));
}

ConsoleSetType(TypeTerrainMaterialAssetId)
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
   Con::warnf("(TypeTerrainMaterialAssetId) - Cannot set multiple args to a single asset.");
}
//-----------------------------------------------------------------------------

TerrainMaterialAsset::TerrainMaterialAsset()
{
   mScriptFile = StringTable->EmptyString();
   mScriptPath = StringTable->EmptyString();
   mMatDefinitionName = StringTable->EmptyString();
   mMaterialDefinition = nullptr;
   mFXMaterialDefinition = nullptr;
}

//-----------------------------------------------------------------------------

TerrainMaterialAsset::~TerrainMaterialAsset()
{
   if (mMaterialDefinition)
      mMaterialDefinition->safeDeleteObject();
   if (mFXMaterialDefinition)
      mFXMaterialDefinition->safeDeleteObject();
}

//-----------------------------------------------------------------------------

void TerrainMaterialAsset::consoleInit()
{
   Parent::consoleInit();
   Con::addVariable("$Core::NoTerrainMaterialAssetFallback", TypeString, &smNoTerrainMaterialAssetFallback,
      "The assetId of the material to display when the requested material asset is missing.\n"
      "@ingroup GFX\n");
   
   smNoTerrainMaterialAssetFallback = StringTable->insert(Con::getVariable("$Core::NoTerrainMaterialAssetFallback"));
}

void TerrainMaterialAsset::initPersistFields()
{
   docsURL;
   // Call parent.
   Parent::initPersistFields();

   //addField("shaderGraph", TypeRealString, Offset(mShaderGraphFile, TerrainMaterialAsset), "");
   //addProtectedField("scriptFile", TypeAssetLooseFilePath, Offset(mScriptFile, TerrainMaterialAsset),
   //   &setScriptFile, &getScriptFile, "Path to the file containing the material definition.");
   addField("scriptFile", TypeAssetLooseFilePath, Offset(mScriptFile, TerrainMaterialAsset), "");

   addField("materialDefinitionName", TypeString, Offset(mMatDefinitionName, TerrainMaterialAsset), "Name of the material definition this asset is for.");
}

void TerrainMaterialAsset::initializeAsset()
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

void TerrainMaterialAsset::onAssetRefresh()
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

void TerrainMaterialAsset::setScriptFile(const char* pScriptFile)
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

void TerrainMaterialAsset::loadMaterial()
{
   if (mMaterialDefinition)
      mMaterialDefinition->safeDeleteObject();
   if (mFXMaterialDefinition)
      mFXMaterialDefinition->safeDeleteObject();

   if (mLoadedState == EmbeddedDefinition)
   {
      if (size() != 0)
      {
         for (U32 i = 0; i < size(); i++)
         {
            TerrainMaterial* terrMat =  dynamic_cast<TerrainMaterial*>(getObject(i));
            if (terrMat)
            {
               mMaterialDefinition = terrMat;
               mLoadedState = Ok;
               mMaterialDefinition->setInternalName(getAssetId());
               continue;
            }

            //Otherwise, check if it's our FX material
            Material* fxMat = dynamic_cast<Material*>(getObject(i));
            if (fxMat)
            {
               mFXMaterialDefinition = fxMat;
               //mMaterialDefinition->setInternalName(getAssetId());
               mFXMaterialDefinition->reload();
               continue;
            }

         }
      }

      if(mLoadedState == Ok)
         return;
   }
   else if ((mLoadedState == ScriptLoaded || mLoadedState == DefinitionAlreadyExists) && mMatDefinitionName != StringTable->EmptyString())
   {
      TerrainMaterial* matDef;
      if (!Sim::findObject(mMatDefinitionName, matDef))
      {
         Con::errorf("TerrainMaterialAsset: Unable to find the Material %s", mMatDefinitionName);
         mLoadedState = BadFileReference;
         return;
      }

      mMaterialDefinition = matDef;

      mLoadedState = Ok;
      mMaterialDefinition->setInternalName(getAssetId());
      return;
   }

   mLoadedState = Failed;
}

//------------------------------------------------------------------------------

void TerrainMaterialAsset::copyTo(SimObject* object)
{
   // Call to parent.
   Parent::copyTo(object);
}

//------------------------------------------------------------------------------
U32 TerrainMaterialAsset::getAssetByMaterialName(StringTableEntry matName, AssetPtr<TerrainMaterialAsset>* matAsset)
{
   AssetQuery query;
   U32 foundAssetcount = AssetDatabase.findAssetType(&query, "TerrainMaterialAsset");
   if (foundAssetcount == 0)
   {
      //Didn't work, so have us fall back to a placeholder asset
      matAsset->setAssetId(TerrainMaterialAsset::smNoTerrainMaterialAssetFallback);

      if (matAsset->isNull())
      {
         //Well that's bad, loading the fallback failed.
         Con::warnf("TerrainMaterialAsset::getAssetByMaterialName - Finding of asset associated with material name %s failed with no fallback asset", matName);
         return AssetErrCode::Failed;
      }

      //handle noshape not being loaded itself
      if ((*matAsset)->mLoadedState == BadFileReference)
      {
         Con::warnf("TerrainMaterialAsset::getAssetByMaterialName - Finding of associated with aterial name %s failed, and fallback asset reported error of Bad File Reference.", matName);
         return AssetErrCode::BadFileReference;
      }

      Con::warnf("TerrainMaterialAsset::getAssetByMaterialName - Finding of associated with aterial name %s failed, utilizing fallback asset", matName);

      (*matAsset)->mLoadedState = AssetErrCode::UsingFallback;
      return AssetErrCode::UsingFallback;
   }
   else
   {
      for (U32 i = 0; i < foundAssetcount; i++)
      {
         TerrainMaterialAsset* tMatAsset = AssetDatabase.acquireAsset<TerrainMaterialAsset>(query.mAssetList[i]);
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
   matAsset->setAssetId(TerrainMaterialAsset::smNoTerrainMaterialAssetFallback);
   (*matAsset)->mLoadedState = AssetErrCode::UsingFallback;
   return AssetErrCode::UsingFallback;

}

StringTableEntry TerrainMaterialAsset::getAssetIdByMaterialName(StringTableEntry matName)
{
   if (matName == StringTable->EmptyString())
      return StringTable->EmptyString();

   StringTableEntry materialAssetId = TerrainMaterialAsset::smNoTerrainMaterialAssetFallback;

   AssetQuery query;
   U32 foundCount = AssetDatabase.findAssetType(&query, "TerrainMaterialAsset");
   if (foundCount != 0)
   {
      for (U32 i = 0; i < foundCount; i++)
      {
         TerrainMaterialAsset* matAsset = AssetDatabase.acquireAsset<TerrainMaterialAsset>(query.mAssetList[i]);
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

U32 TerrainMaterialAsset::getAssetById(StringTableEntry assetId, AssetPtr<TerrainMaterialAsset>* materialAsset)
{
   (*materialAsset) = assetId;
   if (materialAsset->notNull())
   {
      return (*materialAsset)->mLoadedState;
   }
   else
   {
      //Didn't work, so have us fall back to a placeholder asset
      materialAsset->setAssetId(TerrainMaterialAsset::smNoTerrainMaterialAssetFallback);
      if (materialAsset->isNull())
      {
         //Well that's bad, loading the fallback failed.
         Con::warnf("TerrainMaterialAsset::getAssetById - Finding of asset with id %s failed with no fallback asset", assetId);
         return AssetErrCode::Failed;
      }
      //handle noshape not being loaded itself
      if ((*materialAsset)->mLoadedState == BadFileReference)
      {
         Con::warnf("TerrainMaterialAsset::getAssetById - Finding of asset with id %s failed, and fallback asset reported error of Bad File Reference.", assetId);
         return AssetErrCode::BadFileReference;
      }
      Con::warnf("TerrainMaterialAsset::getAssetById - Finding of asset with id %s failed, utilizing fallback asset", assetId);
      (*materialAsset)->mLoadedState = AssetErrCode::UsingFallback;
      return AssetErrCode::UsingFallback;
   }
}
SimObjectPtr<TerrainMaterial> TerrainMaterialAsset::findMaterialDefinitionByAssetId(StringTableEntry assetId)
{
   SimSet* terrainMatSet;
   if (!Sim::findObject("TerrainMaterialSet", terrainMatSet))
   {
      return nullptr;
   }

   SimObjectPtr<TerrainMaterial> matDef = dynamic_cast<TerrainMaterial*>(terrainMatSet->findObjectByInternalName(assetId));
   return matDef;
}

#ifdef TORQUE_TOOLS
DefineEngineStaticMethod(TerrainMaterialAsset, getAssetIdByMaterialName, const char*, (const char* materialName), (""),
   "Queries the Asset Database to see if any asset exists that is associated with the provided material name.\n"
   "@return The AssetId of the associated asset, if any.")
{
   return TerrainMaterialAsset::getAssetIdByMaterialName(StringTable->insert(materialName));
}

//MaterialAsset::findMaterialDefinitionByAssetId("Prototyping:Detail")
DefineEngineStaticMethod(TerrainMaterialAsset, findMaterialDefinitionByAssetId, S32, (const char* assetId), (""),
   "Queries the MaterialSet to see if any MaterialDefinition exists that is associated to the provided assetId.\n"
   "@return The MaterialDefinition Id associated to the assetId, if any")
{
   SimObjectPtr<TerrainMaterial> matDef = TerrainMaterialAsset::findMaterialDefinitionByAssetId(StringTable->insert(assetId));
   if (matDef.isNull())
      return SimObjectId(0);
   else
      return matDef->getId();
}


DefineEngineMethod(TerrainMaterialAsset, getScriptPath, const char*, (), ,
   "Queries the Asset Database to see if any asset exists that is associated with the provided material name.\n"
   "@return The AssetId of the associated asset, if any.")
{
   return object->getScriptPath();
}

DefineEngineMethod(TerrainMaterialAsset, getMaterialDefinition, S32, (), ,
   "Queries the Asset Database to see if any asset exists that is associated with the provided material name.\n"
   "@return The AssetId of the associated asset, if any.")
{
   SimObjectPtr<TerrainMaterial> mat = object->getMaterialDefinition();
   if (mat.isValid())
      return mat->getId();
   else
      return 0;
}

DefineEngineMethod(TerrainMaterialAsset, getFXMaterialDefinition, S32, (), ,
   "Queries the Asset Database to see if any asset exists that is associated with the provided material name.\n"
   "@return The AssetId of the associated asset, if any.")
{
   SimObjectPtr<Material> mat = object->getFXMaterialDefinition();
   if (mat.isValid())
      return mat->getId();
   else
      return 0;
}
//-----------------------------------------------------------------------------
// GuiInspectorTypeAssetId
//-----------------------------------------------------------------------------

IMPLEMENT_CONOBJECT(GuiInspectorTypeTerrainMaterialAssetPtr);

ConsoleDocClass(GuiInspectorTypeTerrainMaterialAssetPtr,
   "@brief Inspector field type for Material Asset Objects\n\n"
   "Editor use only.\n\n"
   "@internal"
);

void GuiInspectorTypeTerrainMaterialAssetPtr::consoleInit()
{
   Parent::consoleInit();

   ConsoleBaseType::getType(TypeTerrainMaterialAssetPtr)->setInspectorFieldType("GuiInspectorTypeTerrainMaterialAssetPtr");
}

GuiControl* GuiInspectorTypeTerrainMaterialAssetPtr::constructEditControl()
{
   // Create base filename edit controls
   GuiControl* retCtrl = Parent::constructEditControl();
   if (retCtrl == NULL)
      return retCtrl;

   // Change filespec
   char szBuffer[512];
   dSprintf(szBuffer, sizeof(szBuffer), "AssetBrowser.showDialog(\"TerrainMaterialAsset\", \"AssetBrowser.changeAsset\", %s, %s);",
      mInspector->getIdString(), mCaption);
   mBrowseButton->setField("Command", szBuffer);

   setDataField(StringTable->insert("targetObject"), NULL, mInspector->getInspectObject()->getIdString());

   // Create "Open in Editor" button
   mEditButton = new GuiBitmapButtonCtrl();

   dSprintf(szBuffer, sizeof(szBuffer), "AssetBrowser.editAsset(%d.getText());", retCtrl->getId());
   mEditButton->setField("Command", szBuffer);

   char bitmapName[512] = "ToolsModule:material_editor_n_image";
   mEditButton->setBitmap(StringTable->insert(bitmapName));

   mEditButton->setDataField(StringTable->insert("Profile"), NULL, "GuiButtonProfile");
   mEditButton->setDataField(StringTable->insert("tooltipprofile"), NULL, "GuiToolTipProfile");
   mEditButton->setDataField(StringTable->insert("hovertime"), NULL, "1000");
   mEditButton->setDataField(StringTable->insert("tooltip"), NULL, "Open this asset in the Terrain Material Editor");

   mEditButton->registerObject();
   addObject(mEditButton);

   return retCtrl;
}

bool GuiInspectorTypeTerrainMaterialAssetPtr::updateRects()
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

IMPLEMENT_CONOBJECT(GuiInspectorTypeTerrainMaterialAssetId);

ConsoleDocClass(GuiInspectorTypeTerrainMaterialAssetId,
   "@brief Inspector field type for Terrain Material Assets\n\n"
   "Editor use only.\n\n"
   "@internal"
);

void GuiInspectorTypeTerrainMaterialAssetId::consoleInit()
{
   Parent::consoleInit();

   ConsoleBaseType::getType(TypeTerrainMaterialAssetId)->setInspectorFieldType("GuiInspectorTypeTerrainMaterialAssetId");
}
#endif
