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
#ifndef _ASSET_BASE_H_
#define _ASSET_BASE_H_

#ifndef _ASSET_DEFINITION_H_
#include "assetDefinition.h"
#endif

#ifndef _STRINGUNIT_H_
#include "string/stringUnit.h"
#endif

#ifndef _ASSET_FIELD_TYPES_H_
#include "assets/assetFieldTypes.h"
#endif

//-----------------------------------------------------------------------------

class AssetManager;

//-----------------------------------------------------------------------------

extern StringTableEntry assetNameField;
extern StringTableEntry assetDescriptionField;
extern StringTableEntry assetCategoryField;
extern StringTableEntry assetInternalField;
extern StringTableEntry assetPrivateField;
extern StringTableEntry assetAutoUnloadField;
extern StringTableEntry assetTypeField;

//#define ASSET_BASE_ASSETNAME_FIELD         "AssetName"
//#define ASSET_BASE_ASSETDESCRIPTION_FIELD  "AssetDescription"
//#define ASSET_BASE_ASSETCATEGORY_FIELD     "AssetCategory"
//#define ASSET_BASE_ASSETINTERNAL_FIELD     "AssetInternal"
//#define ASSET_BASE_ASSETPRIVATE_FIELD      "AssetPrivate"
//#define ASSET_BASE_AUTOUNLOAD_FIELD        "AssetAutoUnload"

//-----------------------------------------------------------------------------
class AssetBase : public SimGroup
{
   friend class AssetManager;

   typedef SimGroup Parent;

protected:
   AssetManager*           mpOwningAssetManager;
   bool                    mAssetInitialized;
   AssetDefinition*        mpAssetDefinition;
   U32                     mAcquireReferenceCount;
   U32                     mLoadedState;

public:
   enum AssetErrCode
   {
      Failed,
      Ok,
      NotLoaded,
      BadFileReference,
      InvalidFormat,
      DependencyNotFound,
      FileTooLarge,
      UsingFallback,
      Extended
   };

   static const String mErrCodeStrings[AssetErrCode::Extended + 1];
   static String getAssetErrstrn(U32 errCode)
   {
      if (errCode > AssetErrCode::Extended) return "undefined error";
      return mErrCodeStrings[errCode];
   };
   U32 getStatus() { return mLoadedState; };
   AssetBase();
   virtual ~AssetBase();

   /// Engine.
   static void initPersistFields();
   virtual void copyTo(SimObject* object);

   /// Asset configuration.
   inline void             setAssetName(const char* pAssetName)              { if (mpOwningAssetManager == NULL) mpAssetDefinition->mAssetName = StringTable->insert(pAssetName); }
   inline StringTableEntry getAssetName(void) const                          { return mpAssetDefinition ? mpAssetDefinition->mAssetName : StringTable->EmptyString(); }
   void                    setAssetDescription(const char* pAssetDescription);
   inline StringTableEntry getAssetDescription(void) const                   { return mpAssetDefinition ? mpAssetDefinition->mAssetDescription : StringTable->EmptyString(); }
   void                    setAssetCategory(const char* pAssetCategory);
   inline StringTableEntry getAssetCategory(void) const                      { return mpAssetDefinition ? mpAssetDefinition->mAssetCategory : StringTable->EmptyString(); }
   void                    setAssetAutoUnload(const bool autoUnload);
   inline bool             getAssetAutoUnload(void) const                    { return mpAssetDefinition->mAssetAutoUnload; }
   void                    setAssetInternal(const bool assetInternal);
   inline bool             getAssetInternal(void) const                      { return mpAssetDefinition->mAssetInternal; }
   inline bool             getAssetPrivate(void) const                       { return mpAssetDefinition->mAssetPrivate; }
   inline StringTableEntry getAssetType(void) const                          { return mpAssetDefinition ? mpAssetDefinition->mAssetType: StringTable->EmptyString(); }

   inline S32              getAcquiredReferenceCount(void) const             { return mAcquireReferenceCount; }
   inline bool             getOwned(void) const                              { return mpOwningAssetManager != NULL; }

   // Asset Id is only available once registered with the asset manager.
   inline StringTableEntry getAssetId(void) const { return mpAssetDefinition ? mpAssetDefinition->mAssetId : StringTable->EmptyString(); }

   /// Expanding/Collapsing asset paths is only available once registered with the asset manager.
   StringTableEntry        expandAssetFilePath(const char* pAssetFilePath) const;
   StringTableEntry        collapseAssetFilePath(const char* pAssetFilePath) const;

   virtual bool            isAssetValid(void) const                          { return true; }

   void                    refreshAsset(void);

   S32 getAssetDependencyFieldCount(const char* pFieldName);
   StringTableEntry getAssetDependencyField(const char* pFieldName, S32 index = 0);
   void clearAssetDependencyFields(const char* pFieldName);
   void addAssetDependencyField(const char* pFieldName, const char* pAssetId);

   bool saveAsset();

   /// Declare Console Object.
   DECLARE_CONOBJECT(AssetBase);

protected:
   virtual void            initializeAsset(void) {}
   virtual void            onAssetRefresh(void) {}
   virtual void            unloadAsset(void) {}

protected:
   static bool             setAssetName(void *obj, const char *array, const char *data)           { static_cast<AssetBase*>(obj)->setAssetName(data); return false; }
   static const char*      getAssetName(void* obj, const char* data)           { return static_cast<AssetBase*>(obj)->getAssetName(); }
   static bool             writeAssetName(void* obj, StringTableEntry pFieldName) { return static_cast<AssetBase*>(obj)->getAssetName() != StringTable->EmptyString(); }

   static bool             setAssetDescription(void *obj, const char *array, const char *data)    { static_cast<AssetBase*>(obj)->setAssetDescription(data); return false; }
   static const char*      getAssetDescription(void* obj, const char* data)    { return static_cast<AssetBase*>(obj)->getAssetDescription(); }
   static bool             writeAssetDescription(void* obj, StringTableEntry pFieldName) { return static_cast<AssetBase*>(obj)->getAssetDescription() != StringTable->EmptyString(); }

   static bool             setAssetCategory(void *obj, const char *array, const char *data)       { static_cast<AssetBase*>(obj)->setAssetCategory(data); return false; }
   static const char*      getAssetCategory(void* obj, const char* data)       { return static_cast<AssetBase*>(obj)->getAssetCategory(); }
   static bool             writeAssetCategory(void* obj, StringTableEntry pFieldName) { return static_cast<AssetBase*>(obj)->getAssetCategory() != StringTable->EmptyString(); }

   static bool             setAssetAutoUnload(void *obj, const char *array, const char *data)     { static_cast<AssetBase*>(obj)->setAssetAutoUnload(dAtob(data)); return false; }
   static const char*      getAssetAutoUnload(void* obj, const char* data)     { return Con::getBoolArg(static_cast<AssetBase*>(obj)->getAssetAutoUnload()); }
   static bool             writeAssetAutoUnload(void* obj, StringTableEntry pFieldName) { return static_cast<AssetBase*>(obj)->getAssetAutoUnload() == false; }

   static bool             setAssetInternal(void *obj, const char *array, const char *data)       { static_cast<AssetBase*>(obj)->setAssetInternal(dAtob(data)); return false; }
   static const char*      getAssetInternal(void* obj, const char* data)       { return Con::getBoolArg(static_cast<AssetBase*>(obj)->getAssetInternal()); }
   static bool             writeAssetInternal(void* obj, StringTableEntry pFieldName) { return static_cast<AssetBase*>(obj)->getAssetInternal() == true; }

   static const char*      getAssetPrivate(void* obj, const char* data)        { return Con::getBoolArg(static_cast<AssetBase*>(obj)->getAssetPrivate()); }

private:
   void                    acquireAssetReference(void);
   bool                    releaseAssetReference(void);

   /// Set asset manager ownership.
   void                    setOwned(AssetManager* pAssetManager, AssetDefinition* pAssetDefinition);
};

//helper macro for stitching string and non string values togeather sans quotes
#define assetText(x,suff) #x#suff
#define macroText(x) #x
#define assetDoc(x,suff) "@brief "#x" "#suff
#endif // _ASSET_BASE_H_

