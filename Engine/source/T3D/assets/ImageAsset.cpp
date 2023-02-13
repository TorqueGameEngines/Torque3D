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

#ifndef IMAGE_ASSET_H
#include "ImageAsset.h"
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

#include "gfx/gfxStringEnumTranslate.h"

#include "ImageAssetInspectors.h"

// Debug Profiling.
#include "platform/profiler.h"

#include "T3D/assets/assetImporter.h"
#include "gfx/gfxDrawUtil.h"

//-----------------------------------------------------------------------------

StringTableEntry ImageAsset::smNoImageAssetFallback = NULL;

//-----------------------------------------------------------------------------

IMPLEMENT_CONOBJECT(ImageAsset);

ConsoleType(ImageAssetPtr, TypeImageAssetPtr, const char*, "")

//-----------------------------------------------------------------------------

ConsoleGetType(TypeImageAssetPtr)
{
   // Fetch asset Id.
   return *((const char**)(dptr));
}

//-----------------------------------------------------------------------------

ConsoleSetType(TypeImageAssetPtr)
{
   // Was a single argument specified?
   if (argc == 1)
   {
      // Yes, so fetch field value.
      *((const char**)dptr) = StringTable->insert(argv[0]);

      return;
   }

   // Warn.
   Con::warnf("(TypeImageAssetPtr) - Cannot set multiple args to a single asset.");
}

ConsoleType(assetIdString, TypeImageAssetId, const char*, "")

ConsoleGetType(TypeImageAssetId)
{
   // Fetch asset Id.
   return *((const char**)(dptr));
}

ConsoleSetType(TypeImageAssetId)
{
   // Was a single argument specified?
   if (argc == 1)
   {
      *((const char**)dptr) = StringTable->insert(argv[0]);

      return;
   }

   // Warn.
   Con::warnf("(TypeAssetId) - Cannot set multiple args to a single asset.");
}
//-----------------------------------------------------------------------------

ImplementEnumType(ImageAssetType,
   "Type of mesh data available in a shape.\n"
   "@ingroup gameObjects")
{ ImageAsset::Albedo, "Albedo", "" },
{ ImageAsset::Normal,      "Normal",      "" },
{ ImageAsset::ORMConfig,   "ORMConfig",   "" },
{ ImageAsset::GUI,         "GUI",         "" },
{ ImageAsset::Roughness,   "Roughness",   "" },
{ ImageAsset::AO,          "AO",          "" },
{ ImageAsset::Metalness,   "Metalness",   "" },
{ ImageAsset::Glow,        "Glow",        "" },
{ ImageAsset::Particle,    "Particle",    "" },
{ ImageAsset::Decal,       "Decal",       "" },
{ ImageAsset::Cubemap,     "Cubemap",       "" },

EndImplementEnumType;


//-----------------------------------------------------------------------------
ImageAsset::ImageAsset() : AssetBase(), mUseMips(true), mIsHDRImage(false), mIsValidImage(false), mImageType(Albedo)
{
   mImageFileName = StringTable->EmptyString();
   mImagePath = StringTable->EmptyString();
   mLoadedState = AssetErrCode::NotLoaded;
}

//-----------------------------------------------------------------------------

ImageAsset::~ImageAsset()
{
}


void ImageAsset::consoleInit()
{
   Parent::consoleInit();
   Con::addVariable("$Core::NoImageAssetFallback", TypeString, &smNoImageAssetFallback,
      "The assetId of the texture to display when the requested image asset is missing.\n"
      "@ingroup GFX\n");

   smNoImageAssetFallback = StringTable->insert(Con::getVariable("$Core::NoImageAssetFallback"));
}

//-----------------------------------------------------------------------------

void ImageAsset::initPersistFields()
{
   docsURL;
   // Call parent.
   Parent::initPersistFields();

   addProtectedField("imageFile", TypeAssetLooseFilePath, Offset(mImageFileName, ImageAsset),
      &setImageFileName, &getImageFileName, "Path to the image file.");

   addField("useMips", TypeBool, Offset(mUseMips, ImageAsset), "Should the image use mips? (Currently unused).");
   addField("isHDRImage", TypeBool, Offset(mIsHDRImage, ImageAsset), "Is the image in an HDR format? (Currently unused)");

   addField("imageType", TypeImageAssetType, Offset(mImageType, ImageAsset), "What the main use-case for the image is for.");
}

//------------------------------------------------------------------------------
//Utility function to 'fill out' bindings and resources with a matching asset if one exists
U32 ImageAsset::getAssetByFilename(StringTableEntry fileName, AssetPtr<ImageAsset>* imageAsset)
{
   AssetQuery query;
   S32 foundAssetcount = AssetDatabase.findAssetLooseFile(&query, fileName);
   if (foundAssetcount == 0)
   {
      //Didn't work, so have us fall back to a placeholder asset
      imageAsset->setAssetId(ImageAsset::smNoImageAssetFallback);

      if (imageAsset->isNull())
      {
         //Well that's bad, loading the fallback failed.
         Con::warnf("ImageAsset::getAssetByFilename - Finding of asset associated with file %s failed with no fallback asset", fileName);
         return AssetErrCode::Failed;
      }

      //handle noshape not being loaded itself
      if ((*imageAsset)->mLoadedState == BadFileReference)
      {
         Con::warnf("ImageAsset::getAssetByFilename - Finding of associated with file %s failed, and fallback asset reported error of Bad File Reference.", fileName);
         return AssetErrCode::BadFileReference;
      }

      Con::warnf("ImageAsset::getAssetByFilename - Finding of associated with file %s failed, utilizing fallback asset", fileName);

      (*imageAsset)->mLoadedState = AssetErrCode::UsingFallback;
      return AssetErrCode::UsingFallback;
   }
   else
   {
      //acquire and bind the asset, and return it out
      imageAsset->setAssetId(query.mAssetList[0]);
      return (*imageAsset)->mLoadedState;
   }
}

StringTableEntry ImageAsset::getAssetIdByFilename(StringTableEntry fileName)
{
   if (fileName == StringTable->EmptyString())
      return StringTable->EmptyString();

   StringTableEntry imageAssetId = ImageAsset::smNoImageAssetFallback;

   AssetQuery query;
   S32 foundAssetcount = AssetDatabase.findAssetLooseFile(&query, fileName);
   if (foundAssetcount != 0)
   {
      //acquire and bind the asset, and return it out
      imageAssetId = query.mAssetList[0];
   }
   else
   {
      AssetPtr<ImageAsset> imageAsset = imageAssetId; //ensures the fallback is loaded
   }

   return imageAssetId;
}

U32 ImageAsset::getAssetById(StringTableEntry assetId, AssetPtr<ImageAsset>* imageAsset)
{
   (*imageAsset) = assetId;

   if (imageAsset->notNull())
   {
      return (*imageAsset)->mLoadedState;
   }
   else
   {
      if (imageAsset->isNull())
      {
         //Well that's bad, loading the fallback failed.
         Con::warnf("ImageAsset::getAssetById - Finding of asset with id %s failed with no fallback asset", assetId);
         return AssetErrCode::Failed;
      }

      //handle noshape not being loaded itself
      if ((*imageAsset)->mLoadedState == BadFileReference)
      {
         Con::warnf("ImageAsset::getAssetById - Finding of asset with id %s failed, and fallback asset reported error of Bad File Reference.", assetId);
         return AssetErrCode::BadFileReference;
      }

      Con::warnf("ImageAsset::getAssetById - Finding of asset with id %s failed, utilizing fallback asset", assetId);

      (*imageAsset)->mLoadedState = AssetErrCode::UsingFallback;
      return AssetErrCode::UsingFallback;
   }
}

//------------------------------------------------------------------------------
void ImageAsset::copyTo(SimObject* object)
{
   // Call to parent.
   Parent::copyTo(object);
}

void ImageAsset::loadImage()
{
   if (mImagePath)
   {
      if (!Torque::FS::IsFile(mImagePath))
      {
         Con::errorf("ImageAsset::initializeAsset: Attempted to load file %s but it was not valid!", mImageFileName);
         mLoadedState = BadFileReference;
         return;
      }

      mLoadedState = Ok;
      mIsValidImage = true;
      mChangeSignal.trigger();
      return;
   }
   mLoadedState = BadFileReference;

   mIsValidImage = false;
}

void ImageAsset::initializeAsset()
{
   ResourceManager::get().getChangedSignal().notify(this, &ImageAsset::_onResourceChanged);

   mImagePath = getOwned() ? expandAssetFilePath(mImageFileName) : mImagePath;
   loadImage();
}

void ImageAsset::onAssetRefresh()
{
   mImagePath = getOwned() ? expandAssetFilePath(mImageFileName) : mImagePath;
   loadImage();
}

void ImageAsset::_onResourceChanged(const Torque::Path& path)
{
   if (path != Torque::Path(mImagePath))
      return;

   refreshAsset();

   //loadImage();
}

void ImageAsset::setImageFileName(const char* pScriptFile)
{
   // Sanity!
   AssertFatal(pScriptFile != NULL, "Cannot use a NULL image file.");

   // Update.
   mImageFileName = StringTable->insert(pScriptFile, true);

   // Refresh the asset.
   refreshAsset();
}

const GBitmap& ImageAsset::getImage()
{
   return GBitmap(); //TODO fix this
}

GFXTexHandle ImageAsset::getTexture(GFXTextureProfile* requestedProfile)
{
   if (mResourceMap.contains(requestedProfile))
   {
      mLoadedState = Ok;
      return mResourceMap.find(requestedProfile)->value;
   }
   else
   {
      //If we don't have an existing map case to the requested format, we'll just create it and insert it in
      GFXTexHandle newTex = TEXMGR->createTexture(mImagePath, requestedProfile);
      if (newTex)
      {
         mResourceMap.insert(requestedProfile, newTex);
         mLoadedState = Ok;
         return newTex;
      }
      else
         mLoadedState = BadFileReference;
   }

   //if (mTexture.isValid())
   //   return mTexture;

   return nullptr;
}

const char* ImageAsset::getImageInfo()
{
   if (mIsValidImage)
   {
      static const U32 bufSize = 2048;
      char* returnBuffer = Con::getReturnBuffer(bufSize);

      GFXTexHandle newTex = TEXMGR->createTexture(mImagePath, &GFXStaticTextureSRGBProfile);
      if (newTex)
      {
         dSprintf(returnBuffer, bufSize, "%s %d %d %d", GFXStringTextureFormat[newTex->getFormat()], newTex->getHeight(), newTex->getWidth(), newTex->getDepth());
         newTex = nullptr;
      }
      else
      {
         dSprintf(returnBuffer, bufSize, "ImageAsset::getImageInfo() - Failed to get image info for %s", getAssetId());
      }

      return returnBuffer;
   }

   return "";
}

const char* ImageAsset::getImageTypeNameFromType(ImageAsset::ImageTypes type)
{
   // must match ImageTypes order
   static const char* _names[] = {
      "Albedo",
      "Normal",
      "ORMConfig",
      "GUI",
      "Roughness",
      "AO",
      "Metalness",
      "Glow",
      "Particle",
      "Decal",
      "Cubemap"
   };

   if (type < 0 || type >= ImageTypeCount)
   {
      Con::errorf("ImageAsset::getAdapterNameFromType - Invalid ImageType, defaulting to Albedo");
      return _names[Albedo];
   }

   return _names[type];
}

ImageAsset::ImageTypes ImageAsset::getImageTypeFromName(const char* name)
{
   if (dStrIsEmpty(name))
   {
      return (ImageTypes)Albedo;
   }

   S32 ret = -1;
   for (S32 i = 0; i < ImageTypeCount; i++)
   {
      if (!dStricmp(getImageTypeNameFromType((ImageTypes)i), name))
         ret = i;
   }

   if (ret == -1)
   {
      Con::errorf("ImageAsset::getImageTypeFromName - Invalid ImageType name, defaulting to Albedo");
      ret = Albedo;
   }

   return (ImageTypes)ret;
}

DefineEngineMethod(ImageAsset, getImagePath, const char*, (), ,
   "Gets the image filepath of this asset.\n"
   "@return File path of the image file.")
{
   return object->getImagePath();
}

DefineEngineMethod(ImageAsset, getImageInfo, const char*, (), ,
   "Gets the info and properties of the image.\n"
   "@return The info/properties of the image.")
{
   return object->getImageInfo();
}

#ifdef TORQUE_TOOLS
DefineEngineStaticMethod(ImageAsset, getAssetIdByFilename, const char*, (const char* filePath), (""),
   "Queries the Asset Database to see if any asset exists that is associated with the provided file path.\n"
   "@return The AssetId of the associated asset, if any.")
{
   return ImageAsset::getAssetIdByFilename(StringTable->insert(filePath));
}

//-----------------------------------------------------------------------------
// GuiInspectorTypeAssetId
//-----------------------------------------------------------------------------

IMPLEMENT_CONOBJECT(GuiInspectorTypeImageAssetPtr);

ConsoleDocClass(GuiInspectorTypeImageAssetPtr,
   "@brief Inspector field type for Shapes\n\n"
   "Editor use only.\n\n"
   "@internal"
);

void GuiInspectorTypeImageAssetPtr::consoleInit()
{
   Parent::consoleInit();

   ConsoleBaseType::getType(TypeImageAssetPtr)->setInspectorFieldType("GuiInspectorTypeImageAssetPtr");
}

GuiControl* GuiInspectorTypeImageAssetPtr::constructEditControl()
{
   // Create base filename edit controls
   GuiControl* retCtrl = Parent::constructEditControl();
   if (retCtrl == NULL)
      return retCtrl;

   retCtrl->getRenderTooltipDelegate().bind(this, &GuiInspectorTypeImageAssetPtr::renderTooltip);

   // Change filespec
   char szBuffer[512];

   const char* previewImage;

   if (mInspector->getInspectObject() != nullptr)
   {
      dSprintf(szBuffer, sizeof(szBuffer), "AssetBrowser.showDialog(\"ImageAsset\", \"AssetBrowser.changeAsset\", %s, %s);",
         mInspector->getIdString(), mCaption);
      mBrowseButton->setField("Command", szBuffer);

      setDataField(StringTable->insert("targetObject"), NULL, mInspector->getInspectObject()->getIdString());

      previewImage = mInspector->getInspectObject()->getDataField(mCaption, NULL);
   }
   else
   {
      //if we don't have a target object, we'll be manipulating the desination value directly
      dSprintf(szBuffer, sizeof(szBuffer), "AssetBrowser.showDialog(\"ImageAsset\", \"AssetBrowser.changeAsset\", %s, \"%s\");",
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
   /*mEditButton = new GuiBitmapButtonCtrl();

   dSprintf(szBuffer, sizeof(szBuffer), "AssetBrowser.editAsset(%d.getText());", retCtrl->getId());
   mEditButton->setField("Command", szBuffer);

   mEditButton->setText("Edit");
   mEditButton->setSizing(horizResizeLeft, vertResizeAspectTop);

   mEditButton->setDataField(StringTable->insert("Profile"), NULL, "ToolsGuiButtonProfile");
   mEditButton->setDataField(StringTable->insert("tooltipprofile"), NULL, "GuiToolTipProfile");
   mEditButton->setDataField(StringTable->insert("hovertime"), NULL, "1000");
   mEditButton->setDataField(StringTable->insert("tooltip"), NULL, "Open this asset in the Image Editor");

   mEditButton->registerObject();
   addObject(mEditButton);*/

   //
   mUseHeightOverride = true;
   mHeightOverride = 72;

   return retCtrl;
}

bool GuiInspectorTypeImageAssetPtr::updateRects()
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

   //mEditButton->resize(Point2I(fieldExtent.x - 105, previewRect.point.y + previewRect.extent.y - rowSize), Point2I(100, rowSize));

   mBrowseButton->setHidden(true);

   return true;
}

bool GuiInspectorTypeImageAssetPtr::renderTooltip(const Point2I& hoverPos, const Point2I& cursorPos, const char* tipText)
{
   if (!mAwake)
      return false;

   GuiCanvas* root = getRoot();
   if (!root)
      return false;

   AssetPtr<ImageAsset> imgAsset;
   U32 assetState = ImageAsset::getAssetById(getData(), &imgAsset);
   if (imgAsset == NULL || assetState == ImageAsset::Failed)
      return false;

   StringTableEntry filename = imgAsset->getImagePath();
   if (!filename || !filename[0])
      return false;

   StringTableEntry previewFilename = filename;
   if (Con::isFunction("getAssetPreviewImage"))
   {
      ConsoleValue consoleRet = Con::executef("getAssetPreviewImage", filename);
      previewFilename = StringTable->insert(consoleRet.getString());

      if (AssetDatabase.isDeclaredAsset(previewFilename))
      {
         ImageAsset* previewAsset = AssetDatabase.acquireAsset<ImageAsset>(previewFilename);
         previewFilename = previewAsset->getImagePath();
      }
   }

   GFXTexHandle texture(previewFilename, &GFXStaticTextureSRGBProfile, avar("%s() - tooltip texture (line %d)", __FUNCTION__, __LINE__));
   if (texture.isNull())
      return false;

   // Render image at a reasonable screen size while
   // keeping its aspect ratio...
   Point2I screensize = getRoot()->getWindowSize();
   Point2I offset = hoverPos;
   Point2I tipBounds;

   U32 texWidth = texture.getWidth();
   U32 texHeight = texture.getHeight();
   F32 aspect = (F32)texHeight / (F32)texWidth;

   const F32 newWidth = 150.0f;
   F32 newHeight = aspect * newWidth;

   // Offset below cursor image
   offset.y += 20; // TODO: Attempt to fix?: root->getCursorExtent().y;
   tipBounds.x = newWidth;
   tipBounds.y = newHeight;

   // Make sure all of the tooltip will be rendered width the app window,
   // 5 is given as a buffer against the edge
   if (screensize.x < offset.x + tipBounds.x + 5)
      offset.x = screensize.x - tipBounds.x - 5;
   if (screensize.y < offset.y + tipBounds.y + 5)
      offset.y = hoverPos.y - tipBounds.y - 5;

   RectI oldClip = GFX->getClipRect();
   RectI rect(offset, tipBounds);
   GFX->setClipRect(rect);

   GFXDrawUtil* drawer = GFX->getDrawUtil();
   drawer->clearBitmapModulation();
   GFX->getDrawUtil()->drawBitmapStretch(texture, rect);

   GFX->setClipRect(oldClip);

   return true;
}

void GuiInspectorTypeImageAssetPtr::updateValue()
{
   Parent::updateValue();

   updatePreviewImage();
}

void GuiInspectorTypeImageAssetPtr::updatePreviewImage()
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

   String imgPreviewAssetId = String(previewImage) + "_PreviewImage";
   imgPreviewAssetId.replace(":", "_");
   imgPreviewAssetId = "ToolsModule:" + imgPreviewAssetId;
   if (AssetDatabase.isDeclaredAsset(imgPreviewAssetId.c_str()))
   {
      mPreviewImage->setBitmap(StringTable->insert(imgPreviewAssetId.c_str()));
   }
   else
   {
      if (AssetDatabase.isDeclaredAsset(previewImage))
      {
         ImageAsset* imgAsset = AssetDatabase.acquireAsset<ImageAsset>(previewImage);
         if (imgAsset && imgAsset->isAssetValid())
         {
            mPreviewImage->_setBitmap(imgAsset->getAssetId());
         }
      }
   }

   if (mPreviewImage->getBitmapAsset().isNull())
      mPreviewImage->_setBitmap(StringTable->insert("ToolsModule:genericAssetIcon_image"));
}

void GuiInspectorTypeImageAssetPtr::setPreviewImage(StringTableEntry assetId)
{
   //if what we're working with isn't even a valid asset, don't present like we found a good one
   if (!AssetDatabase.isDeclaredAsset(assetId))
   {
      mPreviewImage->_setBitmap(StringTable->EmptyString());
      return;
   }

   String imgPreviewAssetId = String(assetId) + "_PreviewImage";
   imgPreviewAssetId.replace(":", "_");
   imgPreviewAssetId = "ToolsModule:" + imgPreviewAssetId;
   if (AssetDatabase.isDeclaredAsset(imgPreviewAssetId.c_str()))
   {
      mPreviewImage->setBitmap(StringTable->insert(imgPreviewAssetId.c_str()));
   }
   else
   {
      if (AssetDatabase.isDeclaredAsset(assetId))
      {
         ImageAsset* imgAsset = AssetDatabase.acquireAsset<ImageAsset>(assetId);
         if (imgAsset && imgAsset->isAssetValid())
         {
            mPreviewImage->_setBitmap(imgAsset->getAssetId());
         }
      }
   }

   if (mPreviewImage->getBitmapAsset().isNull())
      mPreviewImage->_setBitmap(StringTable->insert("ToolsModule:genericAssetIcon_image"));
}

IMPLEMENT_CONOBJECT(GuiInspectorTypeImageAssetId);

ConsoleDocClass(GuiInspectorTypeImageAssetId,
   "@brief Inspector field type for Shapes\n\n"
   "Editor use only.\n\n"
   "@internal"
);

void GuiInspectorTypeImageAssetId::consoleInit()
{
   Parent::consoleInit();

   ConsoleBaseType::getType(TypeImageAssetId)->setInspectorFieldType("GuiInspectorTypeImageAssetId");
}

#endif
