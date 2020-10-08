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
#ifndef IMAGE_ASSET_H
#define IMAGE_ASSET_H

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

#include "gfx/bitmap/gBitmap.h"
#include "gfx/gfxTextureHandle.h"

//-----------------------------------------------------------------------------
class ImageAsset : public AssetBase
{
   typedef AssetBase Parent;

public:
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

protected:
   StringTableEntry mImageFileName;
   StringTableEntry mImagePath;

   GFXTexHandle mImage;

   bool mIsValidImage;
   bool mUseMips;
   bool mIsHDRImage;

   ImageTypes mImageType;

   Map<GFXTextureProfile, GFXTexHandle> mResourceMap;

public:
   ImageAsset();
   virtual ~ImageAsset();

   /// Engine.
   static void initPersistFields();
   virtual void copyTo(SimObject* object);

   /// Declare Console Object.
   DECLARE_CONOBJECT(ImageAsset);

   void                    setImageFileName(const char* pScriptFile);
   inline StringTableEntry getImageFileName(void) const { return mImageFileName; };

   inline StringTableEntry getImagePath(void) const { return mImagePath; };

   bool isValid() { return mIsValidImage; }

   GFXTexHandle getImage(GFXTextureProfile requestedProfile);

   const char* getImageInfo();

   static const char* getImageTypeNameFromType(ImageTypes type);
   static ImageTypes getImageTypeFromName(const char* name);

   void setImageType(ImageTypes type) { mImageType = type; }

   bool getAssetByFilename(StringTableEntry fileName, AssetPtr<ImageAsset>* imageAsset);
   StringTableEntry getAssetIdByFilename(StringTableEntry fileName);

protected:
   virtual void            initializeAsset(void);
   virtual void            onAssetRefresh(void);

   static bool setImageFileName(void *obj, const char *index, const char *data) { static_cast<ImageAsset*>(obj)->setImageFileName(data); return false; }
   static const char* getImageFileName(void* obj, const char* data) { return static_cast<ImageAsset*>(obj)->getImageFileName(); }

   void loadImage();
};

DefineConsoleType(TypeImageAssetPtr, ImageAsset)

typedef ImageAsset::ImageTypes ImageAssetType;
DefineEnumType(ImageAssetType);

#define assetText(x,suff) std::string(std::string(#x) + std::string(#suff)).c_str()

#define initMapSlot(name) m##name##Filename = String::EmptyString; m##name##AssetId = StringTable->EmptyString(); m##name##Asset = NULL;
#define bindMapSlot(name) if (m##name##AssetId != String::EmptyString) m##name##Asset = m##name##AssetId;

#define scriptBindMapSlot(name, consoleClass, docs) addField(#name, TypeImageFilename, Offset(m##name##Filename, consoleClass), assetText(name, docs)); \
                                      addField(assetText(name,Asset), TypeImageAssetPtr, Offset(m##name##AssetId, consoleClass), assetText(name,asset reference.));

#define initMapArraySlot(name,id) m##name##Filename[id] = String::EmptyString; m##name##AssetId[id] = StringTable->EmptyString(); m##name##Asset[id] = NULL;
#define bindMapArraySlot(name,id) if (m##name##AssetId[id] != String::EmptyString) m##name##Asset[id] = m##name##AssetId[id];
#define scriptBindMapArraySlot(name, arraySize, consoleClass, docs) addField(#name, TypeImageFilename, Offset(m##name##Filename, consoleClass), arraySize, assetText(name, docs)); \
                                      addField(assetText(name,Asset), TypeImageAssetPtr, Offset(m##name##AssetId, consoleClass), arraySize, assetText(name,asset reference.));

#define DECLARE_TEXTUREMAP(name)      protected: \
                                      FileName m##name##Filename;\
                                      StringTableEntry m##name##AssetId;\
                                      AssetPtr<ImageAsset>  m##name##Asset;\
                                      public: \
                                      const String& get##name() const { return m##name##Filename; }\
                                      void set##name(FileName _in) { m##name##Filename = _in; }\
                                      const AssetPtr<ImageAsset> & get##name##Asset() const { return m##name##Asset; }\
                                      void set##name##Asset(AssetPtr<ImageAsset>_in) { m##name##Asset = _in; }

#define GET_TEXTUREMAP(name)          get##name()
#define SET_TEXTUREMAP(name,_in)      set##name(_in)
#define GET_TEXTUREASSET(name)        get##name##Asset()
#define SET_TEXTUREASSET(name,_in)    set##name##Asset(_in)

#define DECLARE_TEXTUREARRAY(name,max) FileName m##name##Filename[max];\
                                      StringTableEntry m##name##AssetId[max];\
                                      AssetPtr<ImageAsset>  m##name##Asset[max];

#endif

