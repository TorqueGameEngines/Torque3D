#pragma once
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

#ifndef _ASSET_BASE_H_
#include "assets/assetBase.h"
#endif
#ifndef _ASSET_DEFINITION_H_
#include "assets/assetDefinition.h"
#endif
#ifndef _STRINGUNIT_H_
#include "string/stringUnit.h"
#endif
#ifndef _ASSET_FIELD_TYPES_H_
#include "assets/assetFieldTypes.h"
#endif
#ifndef _ASSET_PTR_H_
#include "assets/assetPtr.h"
#endif 
#ifndef _GBITMAP_H_
#include "gfx/bitmap/gBitmap.h"
#endif
#ifndef _GFXTEXTUREHANDLE_H_
#include "gfx/gfxTextureHandle.h"
#endif
#ifndef _NETCONNECTION_H_
#include "sim/netConnection.h"
#endif
#ifndef _GFXDEVICE_H_
#include "gfx/gfxDevice.h"
#endif
#ifndef _MATTEXTURETARGET_H_
#include "materials/matTextureTarget.h"
#endif

#include "assetMacroHelpers.h"

//-----------------------------------------------------------------------------
class ImageAsset : public AssetBase
{
   typedef AssetBase Parent;
   typedef AssetPtr<ImageAsset> ConcreteAssetPtr;

public:
   typedef HashMap<GFXTextureProfile*, GFXTexHandle> ImageTextureMap;
   /// The different types of image use cases
   enum ImageTypes
   {
      Albedo = 0,
      Normal = 1,
      ORMConfig = 2,
      GUI = 3,
      Roughness = 4,
      AO = 5,
      Metalness = 6,
      Glow = 7,
      Particle = 8,
      Decal = 9,
      Cubemap = 10,
      ImageTypeCount = 11
   };

   class Frame
   {
   public:
      Frame(const S32 pixelOffsetX, const S32 pixelOffsetY,
         const U32 pixelWidth, const U32 pixelHeight,
         const F32 texelWidthScale, const F32 texelHeightScale,
         StringTableEntry inRegionName = StringTable->EmptyString())
         : regionName(inRegionName)
      {
         pixelOffset.set(pixelOffsetY, pixelOffsetY);
         pixelSize.set(pixelWidth, pixelHeight);

         texelLower.set(pixelOffsetX * texelWidthScale, pixelOffsetY * texelHeightScale);
         texelSize.set(pixelWidth * texelWidthScale, pixelHeight * texelHeightScale);
         texelUpper.set(texelLower.x + texelSize.x, texelLower.y + texelSize.y);
      }

      void setFlip(bool flipX, bool flipY)
      {
         if (flipX) mSwap(texelLower.x, texelUpper.x);
         if (flipY) mSwap(texelLower.y, texelUpper.y);
      }

      Point2I pixelOffset;
      Point2I pixelSize;

      Point2F texelLower;
      Point2F texelUpper;
      Point2F texelSize;

      StringTableEntry regionName;
   };

   static StringTableEntry smNoImageAssetFallback;
   static AssetPtr<ImageAsset> smNoImageAssetFallbackAssetPtr;

   static StringTableEntry smNamedTargetAssetFallback;
   static AssetPtr<ImageAsset> smNamedTargetAssetFallbackAssetPtr;

   enum ImageAssetErrCode
   {
      TooManyMips = AssetErrCode::Extended,
      Extended
   };

   static const String mErrCodeStrings[U32(ImageAssetErrCode::Extended) - U32(Parent::Extended) + 1];
   static U32 getAssetErrCode(ConcreteAssetPtr checkAsset) { if (checkAsset.notNull()) return checkAsset->mLoadedState; else return 0; }

   static String getAssetErrstrn(U32 errCode)
   {
      if (errCode < Parent::Extended) return Parent::getAssetErrstrn(errCode);
      if (errCode > ImageAssetErrCode::Extended) return "undefined error";
      return mErrCodeStrings[errCode - Parent::Extended];
   };
private:

   StringTableEntry  mImageFile;
   bool              mUseMips;
   bool              mIsHDRImage;
   ImageTypes        mImageType;
   ImageTextureMap   mResourceMap;
   bool              mIsNamedTarget;
   S32               mImageWidth;
   S32               mImageHeight;
   S32               mImageDepth;
   S32               mImageChannels;
public:
   ImageAsset();
   virtual ~ImageAsset();

   /// Set up some global script interface stuff.
   static void consoleInit();

   /// Engine.
   static void initPersistFields();

   /// Sim
   bool onAdd() override;
   void onRemove() override;
   void copyTo(SimObject* object) override;

   /// Declare Console Object.
   DECLARE_CONOBJECT(ImageAsset);

   void _onResourceChanged(const Torque::Path& path);

   // asset Base load
   U32 load() override;
#ifdef TORQUE_TOOLS
   U32 getAssetMemoryUsage() const override;
#endif
   bool canBePurged() const override { return !mIsNamedTarget; }

   void                    setImageFile(StringTableEntry pImageFile);
   inline StringTableEntry getImageFile(void) const { return mImageFile; };
   inline StringTableEntry getRelativeImageFile(void) const { return collapseAssetFilePath(mImageFile); };

   void                    setGenMips(const bool pGenMips);
   inline bool             getGenMips(void) const { return mUseMips; };

   void                    setTextureHDR(const bool pIsHDR);
   inline bool             getTextureHDR(void) const { return mIsHDRImage; };

   GFXTexHandle            getTexture(GFXTextureProfile* requestedProfile);

   static StringTableEntry getImageTypeNameFromType(ImageTypes type);
   static ImageTypes       getImageTypeFromName(StringTableEntry name);

   void                    setImageType(ImageTypes type) { mImageType = type; }
   ImageTypes              getImageType() { return mImageType; }

   inline U32              getTextureBitmapWidth(void) const { return mImageWidth; }
   inline U32              getTextureBitmapHeight(void) const { return mImageHeight; }
   inline U32              getTextureBitmapDepth(void) const { return mImageDepth; }

   bool                    isNamedTarget(void) const { return mIsNamedTarget; }
   NamedTexTargetRef       getNamedTarget(void) const { return NamedTexTarget::find(mImageFile + 1); }

   static U32 getAssetByFilename(StringTableEntry fileName, AssetPtr<ImageAsset>* imageAsset);
   static StringTableEntry getAssetIdByFilename(StringTableEntry fileName);

   static StringTableEntry getAssetIdFromFilePath(StringTableEntry filePath);

   /// Returns true if the given value follows the named target naming convention:
   /// ($backBuffer, #color)
   static bool isNamedTarget(StringTableEntry name) { return name != NULL && name != StringTable->EmptyString() && (name[0] == '$' || name[0] == '#'); }

   /// Resolves a named render target ($backBuffer, #color) to an asset
   /// pointer, binding/creating a private ImageAsset if needed.
   static AssetPtr<ImageAsset> getNamedTargetAssetPtr(StringTableEntry filePath);

   static U32 getAssetById(StringTableEntry assetId, AssetPtr<ImageAsset>* imageAsset);
   static U32 getAssetById(String assetId, AssetPtr<ImageAsset>* imageAsset) { return getAssetById(assetId.c_str(), imageAsset); };

   void populateImage(void);
   const char* getImageInfo();

protected:
   // Asset Base callback
   void initializeAsset(void) override;
   void onAssetRefresh(void) override;

   /// Taml callbacks.
   void onTamlPreWrite(void) override;
   void onTamlPostWrite(void) override;
   void onTamlCustomWrite(TamlCustomNodes& customNodes) override;
   void onTamlCustomRead(const TamlCustomNodes& customNodes) override;

protected:
   // Texture file 
   static bool setImageFile(void* obj, StringTableEntry index, StringTableEntry data) { static_cast<ImageAsset*>(obj)->setImageFile(data); return false; }
   static const char* getImageFile(void* obj, StringTableEntry data) { return static_cast<ImageAsset*>(obj)->getImageFile(); }
   static bool writeImageFile(void* obj, StringTableEntry pFieldName) { return static_cast<ImageAsset*>(obj)->getImageFile() != StringTable->EmptyString(); }

   // Gen mips?
   static bool setGenMips(void* obj, StringTableEntry index, StringTableEntry data) { static_cast<ImageAsset*>(obj)->setGenMips(dAtob(data)); return false; }
   static bool writeGenMips(void* obj, StringTableEntry pFieldName) { return static_cast<ImageAsset*>(obj)->getGenMips() == true; }

   // Texture Is Hdr?
   static bool setTextureHDR(void* obj, StringTableEntry index, StringTableEntry data) { static_cast<ImageAsset*>(obj)->setTextureHDR(dAtob(data)); return false; }
   static bool writeTextureHDR(void* obj, StringTableEntry pFieldName) { return static_cast<ImageAsset*>(obj)->getTextureHDR() == true; }
};

DECLARE_STRUCT(AssetPtr<ImageAsset>)
DefineConsoleType(TypeImageAssetPtr, AssetPtr<ImageAsset> )

DECLARE_STRUCT(AssetRef<ImageAsset>)
DefineConsoleType(TypeImageAssetRef, AssetRef<ImageAsset>)

typedef ImageAsset::ImageTypes ImageAssetType;
DefineEnumType(ImageAssetType);
