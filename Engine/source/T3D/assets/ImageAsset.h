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

#include "gfx/bitmap/gBitmap.h"
#include "gfx/gfxTextureHandle.h"

#include "sim/netConnection.h"

#include <string>
#include "assetMacroHelpers.h"
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

   static StringTableEntry smNoImageAssetFallback;

protected:
   StringTableEntry mImageFileName;
   StringTableEntry mImagePath;

   bool mIsValidImage;
   bool mUseMips;
   bool mIsHDRImage;

   ImageTypes mImageType;

   HashMap<GFXTextureProfile*, GFXTexHandle> mResourceMap;

   typedef Signal<void()> ImageAssetChanged;
   ImageAssetChanged mChangeSignal;

   typedef Signal<void(S32 index)> ImageAssetArrayChanged;
   ImageAssetArrayChanged mChangeArraySignal;

public:
   ImageAsset();
   virtual ~ImageAsset();

   /// Set up some global script interface stuff.
   static void consoleInit();

   /// Engine.
   static void initPersistFields();
   virtual void copyTo(SimObject* object);

   /// Declare Console Object.
   DECLARE_CONOBJECT(ImageAsset);

   void _onResourceChanged(const Torque::Path& path);

   ImageAssetChanged& getChangedSignal() { return mChangeSignal; }
   ImageAssetArrayChanged& getChangedArraySignal() { return mChangeArraySignal; }

   void                    setImageFileName(StringTableEntry pScriptFile);
   inline StringTableEntry getImageFileName(void) const { return mImageFileName; };

   inline StringTableEntry getImagePath(void) const { return mImagePath; };

   bool isValid() { return mIsValidImage; }

   const GBitmap& getImage();
   GFXTexHandle getTexture(GFXTextureProfile* requestedProfile);

   StringTableEntry getImageInfo();

   static StringTableEntry getImageTypeNameFromType(ImageTypes type);
   static ImageTypes getImageTypeFromName(StringTableEntry name);

   void setImageType(ImageTypes type) { mImageType = type; }
   ImageTypes getImageType() { return mImageType; }

   static U32 getAssetByFilename(StringTableEntry fileName, AssetPtr<ImageAsset>* imageAsset);
   static StringTableEntry getAssetIdByFilename(StringTableEntry fileName);
   static U32 getAssetById(StringTableEntry assetId, AssetPtr<ImageAsset>* imageAsset);
   static U32 getAssetById(String assetId, AssetPtr<ImageAsset>* imageAsset) { return getAssetById(assetId.c_str(), imageAsset); };

protected:
   virtual void            initializeAsset(void);
   virtual void            onAssetRefresh(void);

   static bool setImageFileName(void* obj, StringTableEntry index, StringTableEntry data) { static_cast<ImageAsset*>(obj)->setImageFileName(data); return false; }
   static StringTableEntry getImageFileName(void* obj, StringTableEntry data) { return static_cast<ImageAsset*>(obj)->getImageFileName(); }

   void loadImage();
};

DefineConsoleType(TypeImageAssetPtr, ImageAsset)
DefineConsoleType(TypeImageAssetId, String)

typedef ImageAsset::ImageTypes ImageAssetType;
DefineEnumType(ImageAssetType);

#pragma region Singular Asset Macros

//Singular assets
/// <Summary>
/// Declares an image asset
/// This establishes the assetId, asset and legacy filepath fields, along with supplemental getter and setter functions
/// </Summary>
#define DECLARE_IMAGEASSET(className, name, changeFunc, profile) public: \
   GFXTexHandle m##name = NULL;\
   StringTableEntry m##name##Name; \
   StringTableEntry m##name##AssetId;\
   AssetPtr<ImageAsset>  m##name##Asset;\
   GFXTextureProfile* m##name##Profile = &profile;\
public: \
   const StringTableEntry get##name##File() const { return m##name##Name; }\
   void set##name##File(const FileName &_in) { m##name##Name = StringTable->insert(_in.c_str());}\
   const AssetPtr<ImageAsset> & get##name##Asset() const { return m##name##Asset; }\
   void set##name##Asset(const AssetPtr<ImageAsset> &_in) { m##name##Asset = _in;}\
   \
   bool _set##name(StringTableEntry _in)\
   {\
      if(m##name##AssetId != _in || m##name##Name != _in)\
      {\
         if (m##name##Asset.notNull())\
         {\
            m##name##Asset->getChangedSignal().remove(this, &className::changeFunc);\
         }\
         if (_in == NULL || _in == StringTable->EmptyString())\
         {\
            m##name##Name = StringTable->EmptyString();\
            m##name##AssetId = StringTable->EmptyString();\
            m##name##Asset = NULL;\
            m##name.free();\
            m##name = NULL;\
            return true;\
         }\
         else if(_in[0] == '$' || _in[0] == '#')\
         {\
            m##name##Name = _in;\
            m##name##AssetId = StringTable->EmptyString();\
            m##name##Asset = NULL;\
            m##name.free();\
            m##name = NULL;\
            return true;\
         }\
         \
         if (AssetDatabase.isDeclaredAsset(_in))\
         {\
            m##name##AssetId = _in;\
            \
            U32 assetState = ImageAsset::getAssetById(m##name##AssetId, &m##name##Asset);\
            \
            if (ImageAsset::Ok == assetState)\
            {\
               m##name##Name = StringTable->EmptyString();\
            }\
         }\
         else\
         {\
            StringTableEntry assetId = ImageAsset::getAssetIdByFilename(_in);\
            if (assetId != StringTable->EmptyString())\
            {\
               m##name##AssetId = assetId;\
               if (ImageAsset::getAssetById(m##name##AssetId, &m##name##Asset) == ImageAsset::Ok)\
               {\
                  m##name##Name = StringTable->EmptyString();\
               }\
            }\
            else\
            {\
               m##name##Name = _in;\
               m##name##AssetId = StringTable->EmptyString();\
               m##name##Asset = NULL;\
            }\
         }\
      }\
      if (get##name() != StringTable->EmptyString() && m##name##Name != StringTable->insert("texhandle"))\
      {\
         if (m##name##Asset.notNull())\
         {\
            m##name##Asset->getChangedSignal().notify(this, &className::changeFunc);\
         }\
         \
         m##name.set(get##name(), m##name##Profile, avar("%s() - mTextureObject (line %d)", __FUNCTION__, __LINE__));\
      }\
      else\
      {\
         m##name.free();\
         m##name = NULL;\
      }\
      \
      if(get##name() == StringTable->EmptyString())\
         return true;\
      \
      if (m##name##Asset.notNull() && m##name##Asset->getStatus() != ImageAsset::Ok)\
      {\
         Con::errorf("%s(%s)::_set%s() - image asset failure\"%s\" due to [%s]", macroText(className), getName(), macroText(name), _in, ImageAsset::getAssetErrstrn(m##name##Asset->getStatus()).c_str());\
         return false; \
      }\
      else if (!m##name)\
      {\
         Con::errorf("%s(%s)::_set%s() - Couldn't load image \"%s\"", macroText(className), getName(), macroText(name), _in);\
         return false;\
      }\
      return true;\
   }\
   \
   const StringTableEntry get##name() const\
   {\
      if (m##name##Asset && (m##name##Asset->getImageFileName() != StringTable->EmptyString()))\
         return  Platform::makeRelativePathName(m##name##Asset->getImagePath(), Platform::getMainDotCsDir());\
      else if (m##name##AssetId != StringTable->EmptyString())\
         return m##name##AssetId;\
      else if (m##name##Name != StringTable->EmptyString())\
         return StringTable->insert(Platform::makeRelativePathName(m##name##Name, Platform::getMainDotCsDir()));\
      else\
         return StringTable->EmptyString();\
   }\
   GFXTexHandle get##name##Resource() \
   {\
      return m##name;\
   }\
   bool name##Valid() {return (get##name() != StringTable->EmptyString() && m##name##Asset->getStatus() == AssetBase::Ok); }

#ifdef TORQUE_SHOW_LEGACY_FILE_FIELDS

#define INITPERSISTFIELD_IMAGEASSET(name, consoleClass, docs) \
   addProtectedField(#name, TypeImageFilename, Offset(m##name##Name, consoleClass), _set##name##Data, &defaultProtectedGetFn, assetDoc(name, docs)); \
   addProtectedField(assetText(name, Asset), TypeImageAssetId, Offset(m##name##AssetId, consoleClass), _set##name##Data, &defaultProtectedGetFn, assetDoc(name, asset docs.));

#else

#define INITPERSISTFIELD_IMAGEASSET(name, consoleClass, docs) \
   addProtectedField(#name, TypeImageFilename, Offset(m##name##Name, consoleClass), _set##name##Data, &defaultProtectedGetFn, assetDoc(name, docs), AbstractClassRep::FIELD_HideInInspectors); \
   addProtectedField(assetText(name, Asset), TypeImageAssetId, Offset(m##name##AssetId, consoleClass), _set##name##Data, &defaultProtectedGetFn, assetDoc(name, asset docs.));

#endif // SHOW_LEGACY_FILE_FIELDS

#define LOAD_IMAGEASSET(name)\
if (m##name##AssetId != StringTable->EmptyString())\
{\
   S32 assetState = ImageAsset::getAssetById(m##name##AssetId, &m##name##Asset);\
   if (assetState == ImageAsset::Ok )\
   {\
      m##name##Name = StringTable->EmptyString();\
   }\
   else Con::warnf("Warning: %s::LOAD_IMAGEASSET(%s)-%s", mClassName, m##name##AssetId, ImageAsset::getAssetErrstrn(assetState).c_str());\
}


#pragma endregion

#pragma region Arrayed Asset Macros

//Arrayed Assets
#define DECLARE_IMAGEASSET_ARRAY(className, name, max) public: \
   static const U32 sm##name##Count = max;\
   GFXTexHandle m##name[max];\
   StringTableEntry m##name##Name[max]; \
   StringTableEntry m##name##AssetId[max];\
   AssetPtr<ImageAsset>  m##name##Asset[max];\
   GFXTextureProfile * m##name##Profile[max];\
public: \
   const StringTableEntry get##name##File(const U32& index) const { return m##name##Name[index]; }\
   void set##name##File(const FileName &_in, const U32& index) { m##name##Name[index] = StringTable->insert(_in.c_str());}\
   const AssetPtr<ImageAsset> & get##name##Asset(const U32& index) const { return m##name##Asset[index]; }\
   void set##name##Asset(const AssetPtr<ImageAsset> &_in, const U32& index) { m##name##Asset[index] = _in;}\
   \
   bool _set##name(StringTableEntry _in, const U32& index)\
   {\
      if(m##name##AssetId[index] != _in || m##name##Name[index] != _in)\
      {\
         if(index >= sm##name##Count || index < 0)\
            return false;\
         if (_in == NULL || _in == StringTable->EmptyString())\
         {\
            m##name##Name[index] = StringTable->EmptyString();\
            m##name##AssetId[index] = StringTable->EmptyString();\
            m##name##Asset[index] = NULL;\
            m##name[index].free();\
            m##name[index] = NULL;\
            return true;\
         }\
         else if(_in[0] == '$' || _in[0] == '#')\
         {\
            m##name##Name[index] = _in;\
            m##name##AssetId[index] = StringTable->EmptyString();\
            m##name##Asset[index] = NULL;\
            m##name[index].free();\
            m##name[index] = NULL;\
            return true;\
         }\
         \
         if (AssetDatabase.isDeclaredAsset(_in))\
         {\
            m##name##AssetId[index] = _in;\
            \
            U32 assetState = ImageAsset::getAssetById(m##name##AssetId[index], &m##name##Asset[index]);\
            \
            if (ImageAsset::Ok == assetState)\
            {\
               m##name##Name[index] = StringTable->EmptyString();\
            }\
         }\
         else\
         {\
            StringTableEntry assetId = ImageAsset::getAssetIdByFilename(_in);\
            if (assetId != StringTable->EmptyString())\
            {\
               m##name##AssetId[index] = assetId;\
               if (ImageAsset::getAssetById(m##name##AssetId[index], &m##name##Asset[index]) == ImageAsset::Ok)\
               {\
                  m##name##Name[index] = StringTable->EmptyString();\
               }\
            }\
            else\
            {\
               m##name##Name[index] = _in;\
               m##name##AssetId[index] = StringTable->EmptyString();\
               m##name##Asset[index] = NULL;\
            }\
         }\
      }\
      if (get##name(index) != StringTable->EmptyString() && m##name##Name[index] != StringTable->insert("texhandle"))\
      {\
         m##name[index].set(get##name(index), m##name##Profile[index], avar("%s() - mTextureObject (line %d)", __FUNCTION__, __LINE__));\
      }\
      else\
      {\
         m##name[index].free();\
         m##name[index] = NULL;\
      }\
      \
      if(get##name(index) == StringTable->EmptyString())\
         return true;\
      \
      if (m##name##Asset[index].notNull() && m##name##Asset[index]->getStatus() != ImageAsset::Ok)\
      {\
         Con::errorf("%s(%s)::_set%s(%i) - image asset failure\"%s\" due to [%s]", macroText(className), getName(), macroText(name), index, _in, ImageAsset::getAssetErrstrn(m##name##Asset[index]->getStatus()).c_str());\
         return false; \
      }\
      else if (!m##name[index])\
      {\
         Con::errorf("%s(%s)::_set%s(%i) - Couldn't load image \"%s\"", macroText(className), getName(), macroText(name), index, _in);\
         return false; \
      }\
      return true;\
   }\
   \
   const StringTableEntry get##name(const U32& index) const\
   {\
      if (m##name##Asset[index] && (m##name##Asset[index]->getImageFileName() != StringTable->EmptyString()))\
         return  Platform::makeRelativePathName(m##name##Asset[index]->getImagePath(), Platform::getMainDotCsDir());\
      else if (m##name##AssetId[index] != StringTable->EmptyString())\
         return m##name##AssetId[index];\
      else if (m##name##Name[index] != StringTable->EmptyString())\
      {\
         if (String(m##name##Name[index]).startsWith("#") || String(m##name##Name[index]).startsWith("$"))\
            return StringTable->insert(m##name##Name[index]);\
         else\
            return StringTable->insert(Platform::makeRelativePathName(m##name##Name[index], Platform::getMainDotCsDir()));\
      }\
      else\
         return StringTable->EmptyString();\
   }\
   GFXTexHandle get##name##Resource(const U32& index) \
   {\
      if(index >= sm##name##Count || index < 0)\
         return nullptr;\
      return m##name[index];\
   }\
   bool name##Valid(const U32& id) {return (get##name(id) != StringTable->EmptyString() && m##name##Asset[id]->getStatus() == AssetBase::Ok); }

#define DECLARE_IMAGEASSET_ARRAY_SETGET(className, name)\
   static bool _set##name##Data(void* obj, const char* index, const char* data)\
   {\
      if (!index) return false;\
      U32 idx = dAtoi(index);\
      if (idx >= sm##name##Count)\
         return false;\
      bool ret = false;\
      className* object = static_cast<className*>(obj);\
      ret = object->_set##name(StringTable->insert(data),idx);\
      return ret;\
   }

#define DECLARE_IMAGEASSET_ARRAY_NET_SETGET(className, name, bitmask)\
   static bool _set##name##Data(void* obj, const char* index, const char* data)\
   {\
      if (!index) return false;\
      U32 idx = dAtoi(index);\
      if (idx >= sm##name##Count)\
         return false;\
      bool ret = false;\
      className* object = static_cast<className*>(obj);\
      ret = object->_set##name(StringTable->insert(data),idx);\
      if(ret)\
         object->setMaskBits(bitmask);\
      return ret;\
   }

#define INIT_IMAGEASSET_ARRAY(name, profile, index) \
{\
   m##name##Name[index] = StringTable->EmptyString(); \
   m##name##AssetId[index] = StringTable->EmptyString(); \
   m##name##Asset[index] = NULL;\
   m##name[index] = NULL;\
   m##name##Profile[index] = &profile;\
}

#define DEF_IMAGEASSET_ARRAY_BINDS(className,name)\
DefineEngineMethod(className, get##name, const char*, (S32 index), , "get name")\
{\
   return object->get##name(index); \
}\
DefineEngineMethod(className, get##name##Asset, const char*, (S32 index), , assetText(name, asset reference))\
{\
   if(index >= className::sm##name##Count || index < 0)\
      return "";\
   return object->m##name##AssetId[index]; \
}\
DefineEngineMethod(className, set##name, bool, (const char* map, S32 index), , assetText(name,assignment. first tries asset then flat file.))\
{\
    return object->_set##name(StringTable->insert(map), index);\
}

#ifdef TORQUE_SHOW_LEGACY_FILE_FIELDS

#define INITPERSISTFIELD_IMAGEASSET_ARRAY(name, arraySize, consoleClass, docs) \
   addProtectedField(#name, TypeImageFilename, Offset(m##name##Name, consoleClass), _set##name##Data, &defaultProtectedGetFn, arraySize, assetDoc(name, docs)); \
   addProtectedField(assetText(name, Asset), TypeImageAssetId, Offset(m##name##AssetId, consoleClass), _set##name##Data, &defaultProtectedGetFn, arraySize, assetDoc(name, asset docs.));

#else

#define INITPERSISTFIELD_IMAGEASSET_ARRAY(name, arraySize, consoleClass, docs) \
   addProtectedField(#name, TypeImageFilename, Offset(m##name##Name, consoleClass), _set##name##Data, &defaultProtectedGetFn, arraySize, assetDoc(name, docs), AbstractClassRep::FIELD_HideInInspectors); \
   addProtectedField(assetText(name, Asset), TypeImageAssetId, Offset(m##name##AssetId, consoleClass), _set##name##Data, &defaultProtectedGetFn, arraySize, assetDoc(name, asset docs.));

#endif

#define LOAD_IMAGEASSET_ARRAY(name, index)\
if (m##name##AssetId[index] != StringTable->EmptyString())\
{\
   S32 assetState = ImageAsset::getAssetById(m##name##AssetId[index], &m##name##Asset[index]);\
   if (assetState == ImageAsset::Ok )\
   {\
      m##name##Name[index] = StringTable->EmptyString();\
   }\
   else Con::warnf("Warning: %s::LOAD_IMAGEASSET(%s)-%s", mClassName, m##name##AssetId[index], ImageAsset::getAssetErrstrn(assetState).c_str());\
}

#pragma endregion


