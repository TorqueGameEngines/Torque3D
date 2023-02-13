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

#ifdef TORQUE_TOOLS
#include "ts/tsLastDetail.h"
#endif
#include "util/imposterCapture.h"

#include "ts/tsShapeInstance.h"
#include "gfx/bitmap/imageUtils.h"

StringTableEntry ShapeAsset::smNoShapeAssetFallback = NULL;

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

ConsoleType(assetIdString, TypeShapeAssetId, const char*, ASSET_ID_FIELD_PREFIX)

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
      *((const char**)dptr) = StringTable->insert(argv[0]);

      return;
   }

   // Warn.
   Con::warnf("(TypeAssetId) - Cannot set multiple args to a single asset.");
}

//-----------------------------------------------------------------------------

const String ShapeAsset::mShapeErrCodeStrings[] =
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

   mDiffuseImposterFileName = StringTable->EmptyString();
   mDiffuseImposterPath = StringTable->EmptyString();
   mNormalImposterFileName = StringTable->EmptyString();
   mNormalImposterPath = StringTable->EmptyString();


   mLoadedState = AssetErrCode::NotLoaded;
}

//-----------------------------------------------------------------------------

ShapeAsset::~ShapeAsset()
{
}

//-----------------------------------------------------------------------------

void ShapeAsset::consoleInit()
{
   Parent::consoleInit();

   Con::addVariable("$Core::NoShapeAssetFallback", TypeString, &smNoShapeAssetFallback,
      "The assetId of the shape to display when the requested shape asset is missing.\n"
      "@ingroup GFX\n");
   
   smNoShapeAssetFallback = StringTable->insert(Con::getVariable("$Core::NoShapeAssetFallback"));
}

//-----------------------------------------------------------------------------

void ShapeAsset::initPersistFields()
{
   docsURL;
   // Call parent.
   Parent::initPersistFields();

   addProtectedField("fileName", TypeAssetLooseFilePath, Offset(mFileName, ShapeAsset),
      &setShapeFile, &getShapeFile, "Path to the shape file we want to render");
   addProtectedField("constuctorFileName", TypeAssetLooseFilePath, Offset(mConstructorFileName, ShapeAsset),
      &setShapeConstructorFile, &getShapeConstructorFile, "Path to the shape file we want to render");

   addProtectedField("diffuseImposterFileName", TypeAssetLooseFilePath, Offset(mDiffuseImposterFileName, ShapeAsset),
      &setDiffuseImposterFile, &getDiffuseImposterFile, "Path to the diffuse imposter file we want to render");
   addProtectedField("normalImposterFileName", TypeAssetLooseFilePath, Offset(mNormalImposterFileName, ShapeAsset),
      &setNormalImposterFile, &getNormalImposterFile, "Path to the normal imposter file we want to render");

}

void ShapeAsset::setDataField(StringTableEntry slotName, StringTableEntry array, StringTableEntry value)
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
   mFilePath = getOwned() ? expandAssetFilePath(mFileName) : mFilePath;

   mConstructorFilePath = getOwned() ? expandAssetFilePath(mConstructorFileName) : mConstructorFilePath;
   if (!Torque::FS::IsFile(mConstructorFilePath))
      Con::errorf("ShapeAsset::initializeAsset (%s) could not find %s!", getAssetName(), mConstructorFilePath);
   mDiffuseImposterPath = getOwned() ? expandAssetFilePath(mDiffuseImposterFileName) : mDiffuseImposterFileName;
   if (mDiffuseImposterPath == StringTable->EmptyString())
   {
      String diffusePath = String(mFilePath) + "_imposter.dds";
      mDiffuseImposterPath = StringTable->insert(diffusePath.c_str());
   }

   mNormalImposterPath = getOwned() ? expandAssetFilePath(mNormalImposterFileName) : mNormalImposterFileName;
   if (mNormalImposterPath == StringTable->EmptyString())
   {
      String normalPath = String(mFilePath) + "_imposter_normals.dds";
      mNormalImposterPath = StringTable->insert(normalPath.c_str());
   }

   loadShape();
}

void ShapeAsset::setShapeFile(const char* pShapeFile)
{
   // Sanity!
   AssertFatal(pShapeFile != NULL, "Cannot use a NULL shape file.");

   // Fetch image file.
   pShapeFile = StringTable->insert(pShapeFile, true);

   // Ignore no change,
   if (pShapeFile == mFileName)
      return;

   mFileName = getOwned() ? expandAssetFilePath(pShapeFile) : pShapeFile;

   // Refresh the asset.
   refreshAsset();
}

void ShapeAsset::setShapeConstructorFile(const char* pShapeConstructorFile)
{
   // Sanity!
   AssertFatal(pShapeConstructorFile != NULL, "Cannot use a NULL shape constructor file.");

   // Fetch image file.
   pShapeConstructorFile = StringTable->insert(pShapeConstructorFile, true);

   // Ignore no change,
   if (pShapeConstructorFile == mConstructorFileName)
      return;

   mConstructorFileName = getOwned() ? expandAssetFilePath(pShapeConstructorFile) : pShapeConstructorFile;

   // Refresh the asset.
   refreshAsset();
}

void ShapeAsset::setDiffuseImposterFile(const char* pImageFile)
{
   // Sanity!
   AssertFatal(pImageFile != NULL, "Cannot use a NULL image file.");

   // Fetch image file.
   pImageFile = StringTable->insert(pImageFile, true);

   // Ignore no change,
   if (pImageFile == mDiffuseImposterFileName)
      return;

   mDiffuseImposterFileName = getOwned() ? expandAssetFilePath(pImageFile) : pImageFile;

   // Refresh the asset.
   refreshAsset();
}

void ShapeAsset::setNormalImposterFile(const char* pImageFile)
{
   // Sanity!
   AssertFatal(pImageFile != NULL, "Cannot use a NULL image file.");

   // Fetch image file.
   pImageFile = StringTable->insert(pImageFile, true);

   // Ignore no change,
   if (pImageFile == mNormalImposterFileName)
      return;

   mNormalImposterFileName = getOwned() ? expandAssetFilePath(pImageFile) : pImageFile;

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
      Con::errorf("ShapeAsset::loadShape : failed to load shape file %s (%s)!", getAssetName(), mFilePath);
      mLoadedState = BadFileReference;
      return false; //if it failed to load, bail out
   }
   // Construct billboards if not done already
   if (GFXDevice::devicePresent())
      mShape->setupBillboardDetails(mFilePath, mDiffuseImposterPath, mNormalImposterPath);

   //If they exist, grab our imposters here and bind them to our shapeAsset

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
U32 ShapeAsset::getAssetByFilename(StringTableEntry fileName, AssetPtr<ShapeAsset>* shapeAsset)
{
   AssetQuery query;
   S32 foundAssetcount = AssetDatabase.findAssetLooseFile(&query, fileName);
   if (foundAssetcount == 0)
   {
      //Didn't work, so have us fall back to a placeholder asset
      shapeAsset->setAssetId(ShapeAsset::smNoShapeAssetFallback);

      if (shapeAsset->isNull())
      {
         //Well that's bad, loading the fallback failed.
         Con::warnf("ShapeAsset::getAssetByFilename - Finding of asset associated with file %s failed with no fallback asset", fileName);
         return AssetErrCode::Failed;
      }

      //handle noshape not being loaded itself
      if ((*shapeAsset)->mLoadedState == BadFileReference)
      {
         Con::warnf("ShapeAsset::getAssetByFilename - Finding of associated with file %s failed, and fallback asset reported error of Bad File Reference.", fileName);
         return AssetErrCode::BadFileReference;
      }

      Con::warnf("ShapeAsset::getAssetByFilename - Finding of associated with file %s failed, utilizing fallback asset", fileName);

      (*shapeAsset)->mLoadedState = AssetErrCode::UsingFallback;
      return AssetErrCode::UsingFallback;
   }
   else
   {
      //acquire and bind the asset, and return it out
      shapeAsset->setAssetId(query.mAssetList[0]);
      return (*shapeAsset)->mLoadedState;
   }
}

StringTableEntry ShapeAsset::getAssetIdByFilename(StringTableEntry fileName)
{
   if (fileName == StringTable->EmptyString())
      return StringTable->EmptyString();

   StringTableEntry shapeAssetId = ShapeAsset::smNoShapeAssetFallback;

   AssetQuery query;
   S32 foundAssetcount = AssetDatabase.findAssetLooseFile(&query, fileName);
   if (foundAssetcount != 0)
   {
      //acquire and bind the asset, and return it out
      shapeAssetId = query.mAssetList[0];
   }
   else
   {
      AssetPtr<ShapeAsset> shapeAsset = shapeAssetId; //ensures the fallback is loaded
   }

   return shapeAssetId;
}

U32 ShapeAsset::getAssetById(StringTableEntry assetId, AssetPtr<ShapeAsset>* shapeAsset)
{
   (*shapeAsset) = assetId;

   if (shapeAsset->notNull())
   {
      return (*shapeAsset)->mLoadedState;
   }
   else
   {
      //Didn't work, so have us fall back to a placeholder asset
      shapeAsset->setAssetId(ShapeAsset::smNoShapeAssetFallback);

      if (shapeAsset->isNull())
      {
         //Well that's bad, loading the fallback failed.
         Con::warnf("ShapeAsset::getAssetById - Finding of asset with id %s failed with no fallback asset", assetId);
         return AssetErrCode::Failed;
      }

      //handle noshape not being loaded itself
      if ((*shapeAsset)->mLoadedState == BadFileReference)
      {
         Con::warnf("ShapeAsset::getAssetById - Finding of asset with id %s failed, and fallback asset reported error of Bad File Reference.", assetId);
         return AssetErrCode::BadFileReference;
      }

      Con::warnf("ShapeAsset::getAssetById - Finding of asset with id %s failed, utilizing fallback asset", assetId);

      (*shapeAsset)->mLoadedState = AssetErrCode::UsingFallback;
      return AssetErrCode::UsingFallback;
   }
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

#ifdef TORQUE_TOOLS
const char* ShapeAsset::generateCachedPreviewImage(S32 resolution, String overrideMaterial)
{
   if (!mShape)
      return "";

   // We're gonna render... make sure we can.
   bool sceneBegun = GFX->canCurrentlyRender();
   if (!sceneBegun)
      GFX->beginScene();

   // We need to create our own instance to render with.
   TSShapeInstance* shape = new TSShapeInstance(mShape, true);

   if (overrideMaterial.isNotEmpty())
   {
      Material *tMat = dynamic_cast<Material*>(Sim::findObject(overrideMaterial));
      if (tMat)
         shape->reSkin(tMat->mMapTo, mShape->materialList->getMaterialName(0));
   }
   // Animate the shape once.
   shape->animate(0);

   // So we don't have to change it everywhere.
   const GFXFormat format = GFXFormatR8G8B8A8;

   GBitmap* imposter = NULL;
   GBitmap* imposterNrml = NULL;

   ImposterCapture* imposterCap = new ImposterCapture();

   static const MatrixF topXfm(EulerF(-M_PI_F / 2.0f, 0, 0));
   static const MatrixF bottomXfm(EulerF(M_PI_F / 2.0f, 0, 0));

   MatrixF angMat;

   S32 mip = 0;

   PROFILE_START(ShapeAsset_generateCachedPreviewImage);

   //dMemset(destBmp.getWritableBits(mip), 0, destBmp.getWidth(mip) * destBmp.getHeight(mip) * GFXFormat_getByteSize(format));

   F32 rotX = -(mDegToRad(60.0) - 0.5f * M_PI_F);
   F32 rotZ = -(mDegToRad(45.0) - 0.5f * M_PI_F);

   // We capture the images in a particular order which must
   // match the order expected by the imposter renderer.

   imposterCap->begin(shape, 0, resolution, mShape->mRadius, mShape->center);

   angMat.mul(MatrixF(EulerF(rotX, 0, 0)),
      MatrixF(EulerF(0, 0, rotZ)));

   imposterCap->capture(angMat, &imposter, &imposterNrml);

   imposterCap->end();

   PROFILE_END(); // ShapeAsset_generateCachedPreviewImage

   delete imposterCap;
   delete shape;

   String dumpPath = String(mFilePath) + "_Preview.dds";

   char* returnBuffer = Con::getReturnBuffer(128);
   dSprintf(returnBuffer, 128, "%s", dumpPath.c_str());

   /*FileStream stream;
   if (stream.open(dumpPath, Torque::FS::File::Write))
      destBmp.writeBitmap("png", stream);
   stream.close();*/
   
   DDSFile* ddsDest = DDSFile::createDDSFileFromGBitmap(imposter);
   ImageUtil::ddsCompress(ddsDest, GFXFormatBC2);

   // Finally save the imposters to disk.
   FileStream fs;
   if (fs.open(returnBuffer, Torque::FS::File::Write))
   {
      ddsDest->write(fs);
      fs.close();
   }

   delete ddsDest;
   delete imposter;
   delete imposterNrml;

   // If we did a begin then end it now.
   if (!sceneBegun)
      GFX->endScene();

   return returnBuffer;
}
#endif

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

DefineEngineMethod(ShapeAsset, getShapePath, const char*, (), ,
   "Gets the shape's file path\n"
   "@return The filename of the shape file")
{
   return object->getShapeFilePath();
}

DefineEngineMethod(ShapeAsset, getShapeConstructorFilePath, const char*, (), ,
   "Gets the shape's constructor file.\n"
   "@return The filename of the shape constructor file")
{
   return object->getShapeConstructorFilePath();
}

DefineEngineMethod(ShapeAsset, getStatusString, String, (), , "get status string")\
{
   return ShapeAsset::getAssetErrstrn(object->getStatus());
}


#ifdef TORQUE_TOOLS
DefineEngineMethod(ShapeAsset, generateCachedPreviewImage, const char*, (S32 resolution, const char* overrideMaterialName), (256, ""),
   "Generates a baked preview image of the given shapeAsset. Only really used for generating Asset Browser icons.\n"
   "@param resolution Optional field for what resolution to bake the preview image at. Must be pow2\n"
   "@param overrideMaterialName Optional field for overriding the material used when rendering the shape for the bake.")
{
   return object->generateCachedPreviewImage(resolution, overrideMaterialName);
}

DefineEngineStaticMethod(ShapeAsset, getAssetIdByFilename, const char*, (const char* filePath), (""),
   "Queries the Asset Database to see if any asset exists that is associated with the provided file path.\n"
   "@return The AssetId of the associated asset, if any.")
{
   return ShapeAsset::getAssetIdByFilename(StringTable->insert(filePath));
}
#endif

#ifdef TORQUE_TOOLS
//-----------------------------------------------------------------------------
// GuiInspectorTypeAssetId
//-----------------------------------------------------------------------------

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
   GuiControl* retCtrl = Parent::constructEditControl();
   if (retCtrl == NULL)
      return retCtrl;

   // Change filespec
   char szBuffer[512];

   const char* previewImage;

   if (mInspector->getInspectObject() != nullptr)
   {
      dSprintf(szBuffer, sizeof(szBuffer), "AssetBrowser.showDialog(\"ShapeAsset\", \"AssetBrowser.changeAsset\", %s, %s);",
         mInspector->getIdString(), mCaption);
      mBrowseButton->setField("Command", szBuffer);

      setDataField(StringTable->insert("targetObject"), NULL, mInspector->getInspectObject()->getIdString());

      previewImage = mInspector->getInspectObject()->getDataField(mCaption, NULL);
   }
   else
   {
      //if we don't have a target object, we'll be manipulating the desination value directly
      dSprintf(szBuffer, sizeof(szBuffer), "AssetBrowser.showDialog(\"ShapeAsset\", \"AssetBrowser.changeAsset\", %s, \"%s\");",
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

   if (toolDefaultProfile)
      mPreviewImage->setControlProfile(toolDefaultProfile);

   updatePreviewImage();

   addObject(mPreviewImage);

   //
   mPreviewBorderButton = new GuiBitmapButtonCtrl();
   mPreviewBorderButton->registerObject();

   if (toolDefaultProfile)
      mPreviewBorderButton->setControlProfile(toolDefaultProfile);

   mPreviewBorderButton->_setBitmap(StringTable->insert("ToolsModule:cubemapBtnBorder_n_image"));

   mPreviewBorderButton->setField("Command", szBuffer); //clicking the preview does the same thing as the edit button, for simplicity
   addObject(mPreviewBorderButton);

   //
   // Create "Open in Editor" button
   mEditButton = new GuiBitmapButtonCtrl();

   dSprintf(szBuffer, sizeof(szBuffer), "ShapeEditorPlugin.openShapeAssetId(%d.getText());", retCtrl->getId());
   mEditButton->setField("Command", szBuffer);

   mEditButton->setText("Edit");
   mEditButton->setSizing(horizResizeLeft, vertResizeAspectTop);

   mEditButton->setDataField(StringTable->insert("Profile"), NULL, "ToolsGuiButtonProfile");
   mEditButton->setDataField(StringTable->insert("tooltipprofile"), NULL, "GuiToolTipProfile");
   mEditButton->setDataField(StringTable->insert("hovertime"), NULL, "1000");
   mEditButton->setDataField(StringTable->insert("tooltip"), NULL, "Open this asset in the Shape Editor");

   mEditButton->registerObject();
   addObject(mEditButton);

   //
   mUseHeightOverride = true;
   mHeightOverride = 72;

   return retCtrl;
}

bool GuiInspectorTypeShapeAssetPtr::updateRects()
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

void GuiInspectorTypeShapeAssetPtr::updateValue()
{
   Parent::updateValue();

   updatePreviewImage();
}

void GuiInspectorTypeShapeAssetPtr::updatePreviewImage()
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

   String shpPreviewAssetId = String(previewImage) + "_PreviewImage";
   shpPreviewAssetId.replace(":", "_");
   shpPreviewAssetId = "ToolsModule:" + shpPreviewAssetId;
   if (AssetDatabase.isDeclaredAsset(shpPreviewAssetId.c_str()))
   {
      mPreviewImage->setBitmap(StringTable->insert(shpPreviewAssetId.c_str()));
   }

   if (mPreviewImage->getBitmapAsset().isNull())
      mPreviewImage->_setBitmap(StringTable->insert("ToolsModule:genericAssetIcon_image"));
}

void GuiInspectorTypeShapeAssetPtr::setPreviewImage(StringTableEntry assetId)
{
   //if what we're working with isn't even a valid asset, don't present like we found a good one
   if (!AssetDatabase.isDeclaredAsset(assetId))
   {
      mPreviewImage->_setBitmap(StringTable->EmptyString());
      return;
   }

   String shpPreviewAssetId = String(assetId) + "_PreviewImage";
   shpPreviewAssetId.replace(":", "_");
   shpPreviewAssetId = "ToolsModule:" + shpPreviewAssetId;
   if (AssetDatabase.isDeclaredAsset(shpPreviewAssetId.c_str()))
   {
      mPreviewImage->setBitmap(StringTable->insert(shpPreviewAssetId.c_str()));
   }

   if (mPreviewImage->getBitmapAsset().isNull())
      mPreviewImage->_setBitmap(StringTable->insert("ToolsModule:genericAssetIcon_image"));
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
