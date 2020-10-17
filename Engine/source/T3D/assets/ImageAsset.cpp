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

// Debug Profiling.
#include "platform/profiler.h"

#include "T3D/assets/assetImporter.h"

//-----------------------------------------------------------------------------

IMPLEMENT_CONOBJECT(ImageAsset);

ConsoleType(ImageAssetPtr, TypeImageAssetPtr, String, ASSET_ID_FIELD_PREFIX)

//-----------------------------------------------------------------------------

ConsoleGetType(TypeImageAssetPtr)
{
   // Fetch asset Id.
   return *((StringTableEntry*)dptr);
}

//-----------------------------------------------------------------------------

ConsoleSetType(TypeImageAssetPtr)
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
   Con::warnf("(TypeImageAssetPtr) - Cannot set multiple args to a single asset.");
}

ConsoleType(assetIdString, TypeImageAssetId, String, ASSET_ID_FIELD_PREFIX)

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

ImplementEnumType(ImageAssetType,
   "Type of mesh data available in a shape.\n"
   "@ingroup gameObjects")
   { ImageAsset::Albedo,      "Albedo",      "" },
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
ImageAsset::ImageAsset() : AssetBase(), mImage(nullptr), mUseMips(true), mIsHDRImage(false), mIsValidImage(false), mImageType(Albedo)
{
   mImageFileName = StringTable->EmptyString();
   mImagePath = StringTable->EmptyString();
}

//-----------------------------------------------------------------------------

ImageAsset::~ImageAsset()
{
}

//-----------------------------------------------------------------------------

void ImageAsset::initPersistFields()
{
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
bool ImageAsset::getAssetByFilename(StringTableEntry fileName, AssetPtr<ImageAsset>* imageAsset)
{
   AssetQuery query;
   S32 foundAssetcount = AssetDatabase.findAssetLooseFile(&query, fileName);
   if (foundAssetcount == 0)
   {
      //Didn't find any assets
      //If possible, see if we can run an in-place import and the get the asset from that
#if TORQUE_DEBUG
      Con::warnf("ImageAsset::getAssetByFilename - Attempted to in-place import a image file(%s) that had no associated asset", fileName);
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
         imageAsset->setAssetId(resultingAssetId);

         if (!imageAsset->isNull())
            return true;
      }

      //Didn't work, so have us fall back to a placeholder asset
      imageAsset->setAssetId(StringTable->insert("Core_Rendering:noImage"));

      if (!imageAsset->isNull())
         return true;

      //That didn't work, so fail out
      return false;
   }
   else
   {
      //acquire and bind the asset, and return it out
      imageAsset->setAssetId(query.mAssetList[0]);
      return true;
   }
}

StringTableEntry ImageAsset::getAssetIdByFilename(StringTableEntry fileName)
{
   StringTableEntry imageAssetId = StringTable->EmptyString();

   AssetQuery query;
   S32 foundAssetcount = AssetDatabase.findAssetLooseFile(&query, fileName);
   if (foundAssetcount == 0)
   {
      //Didn't find any assets
      //If possible, see if we can run an in-place import and the get the asset from that
#if TORQUE_DEBUG
      Con::warnf("ImageAsset::getAssetByFilename - Attempted to in-place import a image file(%s) that had no associated asset", fileName);
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
         imageAssetId = resultingAssetId;
         return imageAssetId;
      }

      //Didn't work, so have us fall back to a placeholder asset
      imageAssetId = StringTable->insert("Core_Rendering:noImage");
   }
   else
   {
      //acquire and bind the asset, and return it out
      imageAssetId = query.mAssetList[0];
   }

   return imageAssetId;
}

bool ImageAsset::getAssetById(StringTableEntry assetId, AssetPtr<ImageAsset>* imageAsset)
{
   (*imageAsset) = assetId;

   if (!imageAsset->isNull())
      return true;

   //Didn't work, so have us fall back to a placeholder asset
   StringTableEntry noImageId = StringTable->insert("Core_Rendering:noMaterial");
   imageAsset->setAssetId(noImageId);

   if (!imageAsset->isNull())
      return true;

   return false;
}
//------------------------------------------------------------------------------
void ImageAsset::copyTo(SimObject* object)
{
   // Call to parent.
   Parent::copyTo(object);
}

void ImageAsset::loadImage()
{
   SAFE_DELETE(mImage);

   if (mImagePath)
   {
      if (!Platform::isFile(mImagePath))
      {
         Con::errorf("ImageAsset::initializeAsset: Attempted to load file %s but it was not valid!", mImageFileName);
         return;
      }

      mImage.set(mImagePath, &GFXStaticTextureSRGBProfile, avar("%s() - mImage (line %d)", __FUNCTION__, __LINE__));

      if (mImage)
      {
         mIsValidImage = true;
         return;
      }
   }

   mIsValidImage = false;
}

void ImageAsset::initializeAsset()
{
   mImagePath = expandAssetFilePath(mImageFileName);

   loadImage();
}

void ImageAsset::onAssetRefresh()
{
   mImagePath = expandAssetFilePath(mImageFileName);

   loadImage();
}

void ImageAsset::setImageFileName(const char* pScriptFile)
{
   // Sanity!
   AssertFatal(pScriptFile != NULL, "Cannot use a NULL image file.");

   // Update.
   mImageFileName = StringTable->insert(pScriptFile);
}

GFXTexHandle ImageAsset::getImage(GFXTextureProfile requestedProfile)
{
   /*if (mResourceMap.contains(requestedProfile))
   {
      return mResourceMap.find(requestedProfile)->value;
   }
   else
   {
      //If we don't have an existing map case to the requested format, we'll just create it and insert it in
      GFXTexHandle newImage;
      newImage.set(mImageFileName, &requestedProfile, avar("%s() - mImage (line %d)", __FUNCTION__, __LINE__));
      mResourceMap.insert(requestedProfile, newImage);

      return newImage;
   }*/

   if (mImage.isValid())
      return mImage;

   return nullptr;
}

const char* ImageAsset::getImageInfo()
{
   if (mIsValidImage)
   {
      static const U32 bufSize = 2048;
      char* returnBuffer = Con::getReturnBuffer(bufSize);
      dSprintf(returnBuffer, bufSize, "%s %d %d %d", GFXStringTextureFormat[mImage.getFormat()], mImage.getHeight(), mImage.getWidth(), mImage.getDepth());

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
   "Creates an instance of the given GameObject given the asset definition.\n"
   "@return The GameObject entity created from the asset.")
{
   return object->getImagePath();
}

DefineEngineMethod(ImageAsset, getImageInfo, const char*, (), ,
   "Creates an instance of the given GameObject given the asset definition.\n"
   "@return The GameObject entity created from the asset.")
{
   return object->getImageInfo();
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

   // Change filespec
   char szBuffer[512];
   dSprintf(szBuffer, sizeof(szBuffer), "AssetBrowser.showDialog(\"ImageAsset\", \"AssetBrowser.changeAsset\", %s, %s);",
      mInspector->getInspectObject()->getIdString(), mCaption);
   mBrowseButton->setField("Command", szBuffer);

   const char* id = mInspector->getInspectObject()->getIdString();

   setDataField(StringTable->insert("targetObject"), NULL, mInspector->getInspectObject()->getIdString());

   // Create "Open in ShapeEditor" button
   mImageEdButton = new GuiBitmapButtonCtrl();

   dSprintf(szBuffer, sizeof(szBuffer), "ShapeEditorPlugin.openShapeAssetId(%d.getText());", retCtrl->getId());
   mImageEdButton->setField("Command", szBuffer);

   char bitmapName[512] = "tools/worldEditor/images/toolbar/shape-editor";
   mImageEdButton->setBitmap(bitmapName);

   mImageEdButton->setDataField(StringTable->insert("Profile"), NULL, "GuiButtonProfile");
   mImageEdButton->setDataField(StringTable->insert("tooltipprofile"), NULL, "GuiToolTipProfile");
   mImageEdButton->setDataField(StringTable->insert("hovertime"), NULL, "1000");
   mImageEdButton->setDataField(StringTable->insert("tooltip"), NULL, "Open this file in the Shape Editor");

   mImageEdButton->registerObject();
   addObject(mImageEdButton);

   return retCtrl;
}

bool GuiInspectorTypeImageAssetPtr::updateRects()
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

   if (mImageEdButton != NULL)
   {
      RectI shapeEdRect(fieldExtent.x - 16, 2, 14, fieldExtent.y - 4);
      resized |= mImageEdButton->resize(shapeEdRect.point, shapeEdRect.extent);
   }

   return resized;
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
