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

#ifndef _SHAPE_ASSET_H_
#include "ShapeAsset.h"
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

#include "core/resourceManager.h"

// Debug Profiling.
#include "platform/profiler.h"
#include "T3D/assets/assetImporter.h"

//-----------------------------------------------------------------------------

IMPLEMENT_CONOBJECT(ShapeAsset);

ConsoleType(assetIdString, TypeShapeAssetPtr, String, ASSET_ID_FIELD_PREFIX)

ConsoleGetType(TypeShapeAssetPtr)
{
   // Fetch asset Id.
   //return *((StringTableEntry*)dptr);
   return (*((AssetPtr<ShapeAsset>*)dptr)).getAssetId();
}

ConsoleSetType(TypeShapeAssetPtr)
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
   Con::warnf("(TypeAssetId) - Cannot set multiple args to a single asset.");
}

//-----------------------------------------------------------------------------

ConsoleType(assetIdString, TypeShapeAssetId, String, ASSET_ID_FIELD_PREFIX)

ConsoleGetType(TypeShapeAssetId)
{
   // Fetch asset Id.
   return *((const char**)(dptr));
}

ConsoleSetType(TypeShapeAssetId)
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
   Con::warnf("(TypeAssetId) - Cannot set multiple args to a single asset.");
}

//-----------------------------------------------------------------------------

const String ShapeAsset::mErrCodeStrings[] =
{
   "TooManyVerts",
   "TooManyBones",
   "MissingAnimatons",
   "UnKnown"
};
//-----------------------------------------------------------------------------

ShapeAsset::ShapeAsset()
{
   mFileName = StringTable->EmptyString();
   mConstructorFileName = StringTable->EmptyString();
   mFilePath = StringTable->EmptyString();
   mConstructorFilePath = StringTable->EmptyString();
   mLoadedState = AssetErrCode::NotLoaded;
}

//-----------------------------------------------------------------------------

ShapeAsset::~ShapeAsset()
{
}

//-----------------------------------------------------------------------------

void ShapeAsset::initPersistFields()
{
   // Call parent.
   Parent::initPersistFields();

   addProtectedField("fileName", TypeAssetLooseFilePath, Offset(mFileName, ShapeAsset),
      &setShapeFile, &getShapeFile, "Path to the shape file we want to render");
   addProtectedField("constuctorFileName", TypeAssetLooseFilePath, Offset(mConstructorFileName, ShapeAsset),
      &setShapeConstructorFile, &getShapeConstructorFile, "Path to the shape file we want to render");
}

void ShapeAsset::setDataField(StringTableEntry slotName, const char *array, const char *value)
{
   Parent::setDataField(slotName, array, value);

   //Now, if it's a material slot of some fashion, set it up
   StringTableEntry matSlotName = StringTable->insert("materialAsset");
   if (String(slotName).startsWith(matSlotName))
   {
      StringTableEntry matId = StringTable->insert(value);

      mMaterialAssetIds.push_back(matId);
   }
}

void ShapeAsset::initializeAsset()
{
   // Call parent.
   Parent::initializeAsset();

   if (mFileName == StringTable->EmptyString())
      return;

   ResourceManager::get().getChangedSignal().notify(this, &ShapeAsset::_onResourceChanged);

   //Ensure our path is expando'd if it isn't already
   if (!Platform::isFullPath(mFilePath))
      mFilePath = getOwned() ? expandAssetFilePath(mFileName) : mFilePath;

   mConstructorFilePath = expandAssetFilePath(mConstructorFilePath);

   loadShape();
}

void ShapeAsset::setShapeFile(const char* pShapeFile)
{
   // Sanity!
   AssertFatal(pShapeFile != NULL, "Cannot use a NULL shape file.");

   // Fetch image file.
   pShapeFile = StringTable->insert(pShapeFile);

   // Ignore no change,
   if (pShapeFile == mFileName)
      return;

   mFileName = pShapeFile;

   // Refresh the asset.
   refreshAsset();
}

void ShapeAsset::setShapeConstructorFile(const char* pShapeConstructorFile)
{
   // Sanity!
   AssertFatal(pShapeConstructorFile != NULL, "Cannot use a NULL shape constructor file.");

   // Fetch image file.
   pShapeConstructorFile = StringTable->insert(pShapeConstructorFile);

   // Ignore no change,
   if (pShapeConstructorFile == mConstructorFileName)
      return;

   mConstructorFileName = pShapeConstructorFile;

   // Refresh the asset.
   refreshAsset();
}

void ShapeAsset::_onResourceChanged(const Torque::Path &path)
{
   if (path != Torque::Path(mFilePath) )
      return;

   refreshAsset();

   loadShape();
}

bool ShapeAsset::loadShape()
{
   mMaterialAssets.clear();
   mMaterialAssetIds.clear();

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

         if (assetType == StringTable->insert("MaterialAsset"))
         {
            mMaterialAssetIds.push_front(assetDependenciesItr->value);

            //Force the asset to become initialized if it hasn't been already
            AssetPtr<MaterialAsset> matAsset = assetDependenciesItr->value;

            mMaterialAssets.push_front(matAsset);
         }
         else if (assetType == StringTable->insert("ShapeAnimationAsset"))
         {
            mAnimationAssetIds.push_back(assetDependenciesItr->value);

            //Force the asset to become initialized if it hasn't been already
            AssetPtr<ShapeAnimationAsset> animAsset = assetDependenciesItr->value;

            mAnimationAssets.push_back(animAsset);
         }

         // Next dependency.
         assetDependenciesItr++;
      }
   }

   mShape = ResourceManager::get().load(mFilePath);

   if (!mShape)
   {
      Con::errorf("ShapeAsset::loadShape : failed to load shape file!");
      mLoadedState = BadFileReference;
      return false; //if it failed to load, bail out
   }

   bool hasBlends = false;

   //Now that we've successfully loaded our shape and have any materials and animations loaded
   //we need to set up the animations we're using on our shape
   for (S32 i = mAnimationAssets.size()-1; i >= 0; --i)
   {
      String srcName = mAnimationAssets[i]->getAnimationName();
      String srcPath(mAnimationAssets[i]->getAnimationFilename());
      //SplitSequencePathAndName(srcPath, srcName);

      if (!mShape->addSequence(srcPath, srcName, srcName,
         mAnimationAssets[i]->getStartFrame(), mAnimationAssets[i]->getEndFrame(), mAnimationAssets[i]->getPadRotation(), mAnimationAssets[i]->getPadTransforms()))
      {
         mLoadedState = MissingAnimatons;
         return false;
      }
      if (mAnimationAssets[i]->isBlend())
         hasBlends = true;
   }

   //if any of our animations are blends, set those up now
   if (hasBlends)
   {
      for (U32 i=0; i < mAnimationAssets.size(); ++i)
      {
         if (mAnimationAssets[i]->isBlend() && mAnimationAssets[i]->getBlendAnimationName() != StringTable->EmptyString())
         {
            //gotta do a bit of logic here.
            //First, we need to make sure the anim asset we depend on for our blend is loaded
            AssetPtr<ShapeAnimationAsset> blendAnimAsset = mAnimationAssets[i]->getBlendAnimationName();

            if (blendAnimAsset.isNull())
            {
               Con::errorf("ShapeAsset::initializeAsset - Unable to acquire reference animation asset %s for asset %s to blend!", mAnimationAssets[i]->getBlendAnimationName(), mAnimationAssets[i]->getAssetName());
               {
                  mLoadedState = MissingAnimatons;
                  return false;
               }
            }

            String refAnimName = blendAnimAsset->getAnimationName();
            if (!mShape->setSequenceBlend(mAnimationAssets[i]->getAnimationName(), true, blendAnimAsset->getAnimationName(), mAnimationAssets[i]->getBlendFrame()))
            {
               Con::errorf("ShapeAnimationAsset::initializeAsset - Unable to set animation clip %s for asset %s to blend!", mAnimationAssets[i]->getAnimationName(), mAnimationAssets[i]->getAssetName());
               {
                  mLoadedState = MissingAnimatons;
                  return false;
               }
            }
         }
      }
   }

   mChangeSignal.trigger();

   mLoadedState = Ok;
   return true;
}

//------------------------------------------------------------------------------
//Utility function to 'fill out' bindings and resources with a matching asset if one exists
bool ShapeAsset::getAssetByFilename(StringTableEntry fileName, AssetPtr<ShapeAsset>* shapeAsset)
{
   AssetQuery query;
   S32 foundAssetcount = AssetDatabase.findAssetLooseFile(&query, fileName);
   if (foundAssetcount == 0)
   {
      //Didn't find any assets
      //If possible, see if we can run an in-place import and the get the asset from that
#if TORQUE_DEBUG
      Con::warnf("ShapeAsset::getAssetByFilename - Attempted to in-place import a shapefile(%s) that had no associated asset", fileName);
#endif

      AssetImporter* autoAssetImporter;
      if (!Sim::findObject("autoAssetImporter", autoAssetImporter))
      {
         autoAssetImporter = new AssetImporter();
         autoAssetImporter->registerObject("autoAssetImporter");
      }

      StringTableEntry resultingAssetId = autoAssetImporter->autoImportFile(fileName);

      if (resultingAssetId != StringTable->EmptyString())
      {
         shapeAsset->setAssetId(resultingAssetId);

         if (!shapeAsset->isNull())
            return true;
      }

      //Didn't work, so have us fall back to a placeholder asset
      shapeAsset->setAssetId(StringTable->insert("Core_Rendering:noshape"));

      if (!shapeAsset->isNull())
         return true;

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

StringTableEntry ShapeAsset::getAssetIdByFilename(StringTableEntry fileName)
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
      Con::warnf("ShapeAsset::getAssetByFilename - Attempted to in-place import a shapefile(%s) that had no associated asset", fileName);
#endif

      AssetImporter* autoAssetImporter;
      if (!Sim::findObject("autoAssetImporter", autoAssetImporter))
      {
         autoAssetImporter = new AssetImporter();
         autoAssetImporter->registerObject("autoAssetImporter");
      }

      StringTableEntry resultingAssetId = autoAssetImporter->autoImportFile(fileName);

      if (resultingAssetId != StringTable->EmptyString())
      {
         shapeAssetId = resultingAssetId;
         return shapeAssetId;
      }

      //Didn't work, so have us fall back to a placeholder asset
      shapeAssetId = StringTable->insert("Core_Rendering:noshape");
   }
   else
   {
      //acquire and bind the asset, and return it out
      shapeAssetId = query.mAssetList[0];
   }

   return shapeAssetId;
}

U32 ShapeAsset::getAssetById(StringTableEntry assetId, AssetPtr<ShapeAsset>* shapeAsset)
{
   (*shapeAsset) = assetId;

   if ((*shapeAsset))
      return (*shapeAsset)->mLoadedState;

   //Didn't work, so have us fall back to a placeholder asset
   StringTableEntry noShapeId = StringTable->insert("Core_Rendering:noshape");
   shapeAsset->setAssetId(noShapeId);

   if (shapeAsset->notNull())
   {
      (*shapeAsset)->mLoadedState = AssetErrCode::UsingFallback;
      return AssetErrCode::UsingFallback;
   }

   return AssetErrCode::Failed;
}
//------------------------------------------------------------------------------

void ShapeAsset::copyTo(SimObject* object)
{
   // Call to parent.
   Parent::copyTo(object);
}

void ShapeAsset::onAssetRefresh(void)
{
   if (mFileName == StringTable->EmptyString())
      return;

   // Update.
   if(!Platform::isFullPath(mFileName))
      mFilePath = getOwned() ? expandAssetFilePath(mFileName) : mFilePath;

   loadShape();
}

void ShapeAsset::SplitSequencePathAndName(String& srcPath, String& srcName)
{
   srcName = "";

   // Determine if there is a sequence name at the end of the source string, and
   // if so, split the filename from the sequence name
   S32 split = srcPath.find(' ', 0, String::Right);
   S32 split2 = srcPath.find('\t', 0, String::Right);
   if ((split == String::NPos) || (split2 > split))
      split = split2;
   if (split != String::NPos)
   {
      split2 = split + 1;
      while ((srcPath[split2] != '\0') && dIsspace(srcPath[split2]))
         split2++;

      // now 'split' is at the end of the path, and 'split2' is at the start of the sequence name
      srcName = srcPath.substr(split2);
      srcPath = srcPath.erase(split, srcPath.length() - split);
   }
}

ShapeAnimationAsset* ShapeAsset::getAnimation(S32 index)
{
   if (index < mAnimationAssets.size())
   {
      return mAnimationAssets[index];
   }

   return nullptr;
}

DefineEngineMethod(ShapeAsset, getMaterialCount, S32, (), ,
   "Gets the number of materials for this shape asset.\n"
   "@return Material count.\n")
{
   return object->getMaterialCount();
}

DefineEngineMethod(ShapeAsset, getAnimationCount, S32, (), ,
   "Gets the number of animations for this shape asset.\n"
   "@return Animation count.\n")
{
   return object->getAnimationCount();
}

DefineEngineMethod(ShapeAsset, getAnimation, ShapeAnimationAsset*, (S32 index), (0),
   "Gets a particular shape animation asset for this shape.\n"
   "@param animation asset index.\n"
   "@return Shape Animation Asset.\n")
{
   return object->getAnimation(index);
}
//-----------------------------------------------------------------------------
// GuiInspectorTypeAssetId
//-----------------------------------------------------------------------------

#ifdef TORQUE_TOOLS
IMPLEMENT_CONOBJECT(GuiInspectorTypeShapeAssetPtr);

ConsoleDocClass(GuiInspectorTypeShapeAssetPtr,
   "@brief Inspector field type for Shapes\n\n"
   "Editor use only.\n\n"
   "@internal"
   );

void GuiInspectorTypeShapeAssetPtr::consoleInit()
{
   Parent::consoleInit();

   ConsoleBaseType::getType(TypeShapeAssetPtr)->setInspectorFieldType("GuiInspectorTypeShapeAssetPtr");
}

GuiControl* GuiInspectorTypeShapeAssetPtr::constructEditControl()
{
   // Create base filename edit controls
   GuiControl *retCtrl = Parent::constructEditControl();
   if (retCtrl == NULL)
      return retCtrl;

   // Change filespec
   char szBuffer[512];
   dSprintf(szBuffer, sizeof(szBuffer), "AssetBrowser.showDialog(\"ShapeAsset\", \"AssetBrowser.changeAsset\", %s, %s);", 
      mInspector->getInspectObject()->getIdString(), mCaption);
   mBrowseButton->setField("Command", szBuffer);

   const char* id = mInspector->getInspectObject()->getIdString();

   setDataField(StringTable->insert("targetObject"), NULL, mInspector->getInspectObject()->getIdString());

   // Create "Open in ShapeEditor" button
   mShapeEdButton = new GuiBitmapButtonCtrl();

   dSprintf(szBuffer, sizeof(szBuffer), "ShapeEditorPlugin.openShapeAssetId(%d.getText());", retCtrl->getId());
   mShapeEdButton->setField("Command", szBuffer);

   char bitmapName[512] = "tools/worldEditor/images/toolbar/shape-editor";
   mShapeEdButton->setBitmap(bitmapName);

   mShapeEdButton->setDataField(StringTable->insert("Profile"), NULL, "GuiButtonProfile");
   mShapeEdButton->setDataField(StringTable->insert("tooltipprofile"), NULL, "GuiToolTipProfile");
   mShapeEdButton->setDataField(StringTable->insert("hovertime"), NULL, "1000");
   mShapeEdButton->setDataField(StringTable->insert("tooltip"), NULL, "Open this file in the Shape Editor");

   mShapeEdButton->registerObject();
   addObject(mShapeEdButton);

   return retCtrl;
}

bool GuiInspectorTypeShapeAssetPtr::updateRects()
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

IMPLEMENT_CONOBJECT(GuiInspectorTypeShapeAssetId);

ConsoleDocClass(GuiInspectorTypeShapeAssetId,
   "@brief Inspector field type for Shapes\n\n"
   "Editor use only.\n\n"
   "@internal"
);

void GuiInspectorTypeShapeAssetId::consoleInit()
{
   Parent::consoleInit();

   ConsoleBaseType::getType(TypeShapeAssetId)->setInspectorFieldType("GuiInspectorTypeShapeAssetId");
}

#endif

DefineEngineMethod(ShapeAsset, getShapeFile, const char*, (), ,
   "Creates a new script asset using the targetFilePath.\n"
   "@return The bool result of calling exec")
{
   return object->getShapeFilePath();
}
