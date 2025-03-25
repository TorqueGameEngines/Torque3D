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

#include "gfx/gfxDevice.h"

#ifndef _MATTEXTURETARGET_H_
#include "materials/matTextureTarget.h"
#endif

//-----------------------------------------------------------------------------
class ImageAsset : public AssetBase
{
   typedef AssetBase Parent;
   typedef AssetPtr<ImageAsset> ConcreteAssetPtr;

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

   enum ImageAssetErrCode
   {
      TooManyMips = AssetErrCode::Extended,
      Extended
   };

   static const String mErrCodeStrings[U32(ImageAssetErrCode::Extended) - U32(Parent::Extended) + 1];
   static U32 getAssetErrCode(ConcreteAssetPtr checkAsset) { if (checkAsset) return checkAsset->mLoadedState; else return 0; }

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
   GFXTexHandle      mTextureHandle;
   ImageTypes        mImageType;
   HashMap<GFXTextureProfile*, GFXTexHandle> mResourceMap;
   void generateTexture(void);
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

   void                    setImageFile(StringTableEntry pImageFile);
   inline StringTableEntry getImageFile(void) const { return mImageFile; };

   void                    setGenMips(const bool pGenMips);
   inline bool             getGenMips(void) const { return mUseMips; };

   void                    setTextureHDR(const bool pIsHDR);
   inline bool             getTextureHDR(void) const { return mIsHDRImage; };

   inline GFXTexHandle&    getTexture(void) { load(); generateTexture(); return mTextureHandle; }
   GFXTexHandle            getTexture(GFXTextureProfile* requestedProfile);

   static StringTableEntry getImageTypeNameFromType(ImageTypes type);
   static ImageTypes       getImageTypeFromName(StringTableEntry name);

   void                    setImageType(ImageTypes type) { mImageType = type; }
   ImageTypes              getImageType() { return mImageType; }

   inline U32              getTextureWidth(void) const { return mTextureHandle->getWidth(); }
   inline U32              getTextureHeight(void) const { return mTextureHandle->getHeight(); }
   inline U32              getTextureDepth(void) const { return mTextureHandle->getDepth(); }

   inline U32              getTextureBitmapWidth(void) const { return mTextureHandle->getBitmapWidth(); }
   inline U32              getTextureBitmapHeight(void) const { return mTextureHandle->getBitmapHeight(); }
   inline U32              getTextureBitmapDepth(void) const { return mTextureHandle->getBitmapDepth(); }
   bool                    isAssetValid(void) const override { return !mTextureHandle.isNull(); }

   bool                    isNamedTarget(void) const { return String(getImageFile()).startsWith("#"); }
   NamedTexTargetRef       getNamedTarget(void) const { return NamedTexTarget::find(mImageFile + 1); }

   static U32 getAssetByFilename(StringTableEntry fileName, AssetPtr<ImageAsset>* imageAsset);
   static StringTableEntry getAssetIdByFilename(StringTableEntry fileName);
   static U32 getAssetById(StringTableEntry assetId, AssetPtr<ImageAsset>* imageAsset);
   static U32 getAssetById(String assetId, AssetPtr<ImageAsset>* imageAsset) { return getAssetById(assetId.c_str(), imageAsset); };


   const char* getImageInfo();

protected:
   // Asset Base callback
   void initializeAsset(void) override;
   void onAssetRefresh(void) override;
   void _onFileChanged(const Torque::Path& path);

   /// Taml callbacks.
   void onTamlPreWrite(void) override;
   void onTamlPostWrite(void) override;

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

DefineConsoleType(TypeImageAssetPtr, ImageAsset)
DefineConsoleType(TypeImageAssetId, String)

DECLARE_STRUCT(AssetPtr<ImageAsset>)
DefineConsoleType(TypeImageAssetPtrRefactor, AssetPtr<ImageAsset> )

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
            m##name##Name =  _in;\
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
         \
         if (get##name()[0] != '$' && get##name()[0] != '#') {\
            m##name.set(get##name(), m##name##Profile, avar("%s() - mTextureObject (line %d)", __FUNCTION__, __LINE__));\
         }\
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
         if (GFX->getAdapterType() != NullDevice)\
            Con::errorf("%s(%s)::_set%s() - Couldn't load image \"%s\"", macroText(className), getName(), macroText(name), _in);\
         return false;\
      }\
      return true;\
   }\
   \
   const StringTableEntry get##name() const\
   {\
      if (m##name##Asset && (m##name##Asset->getImageFile() != StringTable->EmptyString()))\
         if (m##name##Asset->getImageFile()[0] == '#' || m##name##Asset->getImageFile()[0] == '$')\
            return m##name##Asset->getImageFile();\
         else\
            return  Platform::makeRelativePathName(m##name##Asset->getImageFile(), Platform::getMainDotCsDir());\
      else if (m##name##AssetId != StringTable->EmptyString())\
         return m##name##AssetId;\
      else if (m##name##Name != StringTable->EmptyString())\
         return StringTable->insert(Platform::makeRelativePathName(m##name##Name, Platform::getMainDotCsDir()));\
      else\
         return StringTable->EmptyString();\
   }\
   GFXTexHandle get##name##Resource() \
   {\
      if (m##name##Asset && (m##name##Asset->getImageFile() != StringTable->EmptyString()))\
         return m##name##Asset->getTexture(m##name##Profile);\
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
#define DECLARE_IMAGEASSET_ARRAY(className, name, max, changeFunc) public: \
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
            m##name##Name[index] =  _in;\
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
         if (get##name(index)[0] != '$' && get##name(index)[0] != '#')\
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
         if (GFX->getAdapterType() != NullDevice)\
            Con::errorf("%s(%s)::_set%s(%i) - Couldn't load image \"%s\"", macroText(className), getName(), macroText(name), index, _in);\
         return false; \
      }\
      return true;\
   }\
   \
   const StringTableEntry get##name(const U32& index) const\
   {\
      if (m##name##Asset[index] && (m##name##Asset[index]->getImageFile() != StringTable->EmptyString()))\
         if (m##name##Asset[index]->getImageFile()[0] == '#' || m##name##Asset[index]->getImageFile()[0] == '$')\
            return m##name##Asset[index]->getImageFile();\
         else\
            return  Platform::makeRelativePathName(m##name##Asset[index]->getImageFile(), Platform::getMainDotCsDir());\
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
      if (m##name##Asset[index] && (m##name##Asset[index]->getImageFile() != StringTable->EmptyString()))\
         return m##name##Asset[index]->getTexture(m##name##Profile[index]);\
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

#pragma region Refactor Asset Macros

#define DECLARE_IMAGEASSET_REFACTOR(className, name, profile)                                                                                                                 \
private:                                                                                                                                                                      \
   AssetPtr<ImageAsset> m##name##Asset;                                                                                                                                       \
public:                                                                                                                                                                       \
   void _set##name(StringTableEntry _in){                                                                                                                                     \
      if(m##name##Asset.getAssetId() == _in)                                                                                                                                  \
         return;                                                                                                                                                              \
                                                                                                                                                                              \
      if(!AssetDatabase.isDeclaredAsset(_in))                                                                                                                                 \
      {                                                                                                                                                                       \
         StringTableEntry imageAssetId = StringTable->EmptyString();                                                                                                          \
         AssetQuery query;                                                                                                                                                    \
         S32 foundAssetcount = AssetDatabase.findAssetLooseFile(&query, _in);                                                                                                 \
         if (foundAssetcount != 0)                                                                                                                                            \
         {                                                                                                                                                                    \
            imageAssetId = query.mAssetList[0];                                                                                                                               \
         }                                                                                                                                                                    \
         else if(Torque::FS::IsFile(_in))                                                                                                                                     \
         {                                                                                                                                                                    \
            ImageAsset* privateImage = new ImageAsset();                                                                                                                      \
            privateImage->setImageFile(_in);                                                                                                                                  \
            imageAssetId = AssetDatabase.addPrivateAsset(privateImage);                                                                                                       \
         }                                                                                                                                                                    \
         m##name##Asset = imageAssetId;                                                                                                                                       \
      }                                                                                                                                                                       \
      else                                                                                                                                                                    \
      {                                                                                                                                                                       \
         m##name##Asset = _in;                                                                                                                                                \
      }                                                                                                                                                                       \
   };                                                                                                                                                                         \
                                                                                                                                                                              \
   inline StringTableEntry _get##name(void) const { return m##name##Asset.getAssetId(); }                                                                                     \
   GFXTexHandle get##name() { return m##name##Asset.notNull() ? m##name##Asset->getTexture(&profile) : NULL; }                                                                \
   AssetPtr<ImageAsset> get##name##Asset(void) { return m##name##Asset; }                                                                                                     \
   static bool _set##name##Data(void* obj, const char* index, const char* data) { static_cast<className*>(obj)->_set##name(_getStringTable()->insert(data)); return false;}


#define DECLARE_IMAGEASSET_NET_REFACTOR(className, name, profile, mask)                                                                                                       \
private:                                                                                                                                                                      \
   AssetPtr<ImageAsset> m##name##Asset;                                                                                                                                       \
public:                                                                                                                                                                       \
   void _set##name(StringTableEntry _in){                                                                                                                                     \
      if(m##name##Asset.getAssetId() == _in)                                                                                                                                  \
         return;                                                                                                                                                              \
                                                                                                                                                                              \
      if(!AssetDatabase.isDeclaredAsset(_in))                                                                                                                                 \
      {                                                                                                                                                                       \
         StringTableEntry imageAssetId = StringTable->EmptyString();                                                                                                          \
         AssetQuery query;                                                                                                                                                    \
         S32 foundAssetcount = AssetDatabase.findAssetLooseFile(&query, _in);                                                                                                 \
         if (foundAssetcount != 0)                                                                                                                                            \
         {                                                                                                                                                                    \
            imageAssetId = query.mAssetList[0];                                                                                                                               \
         }                                                                                                                                                                    \
         m##name##Asset = imageAssetId;                                                                                                                                       \
      }                                                                                                                                                                       \
      else                                                                                                                                                                    \
      {                                                                                                                                                                       \
         m##name##Asset = _in;                                                                                                                                                \
      }                                                                                                                                                                       \
      setMaskBits(mask);                                                                                                                                                      \
   };                                                                                                                                                                         \
                                                                                                                                                                              \
   inline StringTableEntry _get##name(void) const { return m##name##Asset.getAssetId(); }                                                                                     \
   GFXTexHandle get##name() { return m##name##Asset.notNull() ? m##name##Asset->getTexture(&profile) : NULL; }                                                                \
   AssetPtr<ImageAsset> get##name##Asset(void) { return m##name##Asset; }                                                                                                     \
   static bool _set##name##Data(void* obj, const char* index, const char* data) { static_cast<className*>(obj)->_set##name(_getStringTable()->insert(data)); return false;}


#define INITPERSISTFIELD_IMAGEASSET_REFACTOR(name, consoleClass, docs)                                                                                                        \
   addProtectedField(assetText(name, Asset), TypeImageAssetPtrRefactor, Offset(m##name##Asset, consoleClass), _set##name##Data, &defaultProtectedGetFn, assetDoc(name, asset docs.));


#define DECLARE_IMAGEASSET_ARRAY_REFACTOR(className, name, profile, max)                                                                                                      \
private:                                                                                                                                                                      \
   AssetPtr<ImageAsset> m##name##Asset[max];                                                                                                                                  \
public:                                                                                                                                                                       \
   void _set##name(StringTableEntry _in, const U32& index){                                                                                                                   \
      if(m##name##Asset[index].getAssetId() == _in)                                                                                                                           \
         return;                                                                                                                                                              \
                                                                                                                                                                              \
      if(!AssetDatabase.isDeclaredAsset(_in))                                                                                                                                 \
      {                                                                                                                                                                       \
         StringTableEntry imageAssetId = StringTable->EmptyString();                                                                                                          \
         AssetQuery query;                                                                                                                                                    \
         S32 foundAssetcount = AssetDatabase.findAssetLooseFile(&query, _in);                                                                                                 \
         if (foundAssetcount != 0)                                                                                                                                            \
         {                                                                                                                                                                    \
            imageAssetId = query.mAssetList[0];                                                                                                                               \
         }                                                                                                                                                                    \
         else if(Torque::FS::IsFile(_in))                                                                                                                                     \
         {                                                                                                                                                                    \
            ImageAsset* privateImage = new ImageAsset();                                                                                                                      \
            privateImage->setImageFile(_in);                                                                                                                                  \
            imageAssetId = AssetDatabase.addPrivateAsset(privateImage);                                                                                                       \
         }                                                                                                                                                                    \
         m##name##Asset[index] = imageAssetId;                                                                                                                                \
      }                                                                                                                                                                       \
      else                                                                                                                                                                    \
      {                                                                                                                                                                       \
         m##name##Asset[index] = _in;                                                                                                                                         \
      }                                                                                                                                                                       \
   };                                                                                                                                                                         \
                                                                                                                                                                              \
   inline StringTableEntry _get##name(const U32& index) const { return m##name##Asset[index].getAssetId(); }                                                                  \
   GFXTexHandle get##name(const U32& index) { return m##name##Asset[index].notNull() ? m##name##Asset[index]->getTexture(&profile) : NULL; }                                  \
   GFXTexHandle get##name(GFXTextureProfile* requestedProfile, const U32& index) { return m##name##Asset[index].notNull() ? m##name##Asset[index]->getTexture(requestedProfile) : NULL; }\
   AssetPtr<ImageAsset> get##name##Asset(const U32& index) { return m##name##Asset[index]; }                                                                                  \
   static bool _set##name##Data(void* obj, const char* index, const char* data) { static_cast<className*>(obj)->_set##name(_getStringTable()->insert(data), dAtoi(index)); return false;}


#define DECLARE_IMAGEASSET_ARRAY_NET_REFACTOR(className, name, profile, max, mask)                                                                                            \
private:                                                                                                                                                                      \
   AssetPtr<ImageAsset> m##name##Asset[max];                                                                                                                                  \
public:                                                                                                                                                                       \
   void _set##name(StringTableEntry _in, const U32& index){                                                                                                                   \
      if(m##name##Asset[index].getAssetId() == _in)                                                                                                                           \
         return;                                                                                                                                                              \
                                                                                                                                                                              \
      if(!AssetDatabase.isDeclaredAsset(_in))                                                                                                                                 \
      {                                                                                                                                                                       \
         StringTableEntry imageAssetId = StringTable->EmptyString();                                                                                                          \
         AssetQuery query;                                                                                                                                                    \
         S32 foundAssetcount = AssetDatabase.findAssetLooseFile(&query, _in);                                                                                                 \
         if (foundAssetcount != 0)                                                                                                                                            \
         {                                                                                                                                                                    \
            imageAssetId = query.mAssetList[0];                                                                                                                               \
         }                                                                                                                                                                    \
         m##name##Asset[index] = imageAssetId;                                                                                                                                \
      }                                                                                                                                                                       \
      else                                                                                                                                                                    \
      {                                                                                                                                                                       \
         m##name##Asset[index] = _in;                                                                                                                                         \
      }                                                                                                                                                                       \
      setMaskBits(mask);                                                                                                                                                      \
   };                                                                                                                                                                         \
                                                                                                                                                                              \
   inline StringTableEntry _get##name(const U32& index) const { return m##name##Asset[index].getAssetId(); }                                                                  \
   GFXTexHandle get##name(const U32& index) { return m##name##Asset[index].notNull() ? m##name##Asset[index]->getTexture(&profile) : NULL; }                                  \
   GFXTexHandle get##name(GFXTextureProfile* requestedProfile, const U32& index) { return m##name##Asset[index].notNull() ? m##name##Asset[index]->getTexture(requestedProfile) : NULL; }\
   AssetPtr<ImageAsset> get##name##Asset(const U32& index) { return m##name##Asset[index]; }                                                                                  \
   static bool _set##name##Data(void* obj, const char* index, const char* data) { static_cast<className*>(obj)->_set##name(_getStringTable()->insert(data), dAtoi(index)); return false;}


#define INITPERSISTFIELD_IMAGEASSET_ARRAY_REFACTOR(name, arraySize, consoleClass, docs)                                                                                       \
   addProtectedField(assetText(name, Asset), TypeImageAssetPtrRefactor, Offset(m##name##Asset, consoleClass), _set##name##Data, &defaultProtectedGetFn, arraySize, assetDoc(name, asset docs.));

#define DEF_IMAGEASSET_ARRAY_BINDS_REFACTOR(className,name, max)\
DefineEngineMethod(className, get##name, const char*, (S32 index), , "get name")\
{\
   return object->get##name##Asset(index).notNull() ? object->get##name##Asset(index)->getImageFile() : ""; \
}\
DefineEngineMethod(className, get##name##Asset, const char*, (S32 index), , assetText(name, asset reference))\
{\
   if(index >= max || index < 0)\
      return "";\
   return object->_get##name(index); \
}\
DefineEngineMethod(className, set##name, void, (const char* map, S32 index), , assetText(name,assignment. first tries asset then flat file.))\
{\
    object->_set##name(StringTable->insert(map), index);\
}

#pragma endregion
