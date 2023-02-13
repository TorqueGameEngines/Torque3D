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
#ifndef SHAPE_ASSET_H
#define SHAPE_ASSET_H

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

#ifndef _TSSHAPE_H_
#include "ts/tsShape.h"
#endif
#ifndef __RESOURCE_H__
#include "core/resource.h"
#endif
#ifndef _ASSET_PTR_H_
#include "assets/assetPtr.h"
#endif 
#ifndef MATERIALASSET_H
#include "MaterialAsset.h"
#endif
#ifndef SHAPE_ANIMATION_ASSET_H
#include "ShapeAnimationAsset.h"
#endif

#ifdef TORQUE_TOOLS
#include "gui/editor/guiInspectorTypes.h"
#endif
#ifndef _BITSTREAM_H_
#include "core/stream/bitStream.h"
#endif
#include "assetMacroHelpers.h"
//-----------------------------------------------------------------------------
class ShapeAsset : public AssetBase
{
   typedef AssetBase Parent;

protected:
   StringTableEntry   mFileName;
   StringTableEntry   mConstructorFileName;
   StringTableEntry   mFilePath;
   StringTableEntry   mConstructorFilePath;
   Resource<TSShape>	 mShape;

   StringTableEntry   mDiffuseImposterFileName;
   StringTableEntry   mDiffuseImposterPath;

   StringTableEntry   mNormalImposterFileName;
   StringTableEntry   mNormalImposterPath;

   //Material assets we're dependent on and use
   Vector<StringTableEntry> mMaterialAssetIds;
   Vector<AssetPtr<MaterialAsset>> mMaterialAssets;

   //Animation assets we're dependent on and use
   Vector<StringTableEntry> mAnimationAssetIds;
   Vector<AssetPtr<ShapeAnimationAsset>> mAnimationAssets;

   typedef Signal<void()> ShapeAssetChanged;
   ShapeAssetChanged mChangeSignal;

   typedef Signal<void(S32 index)> ShapeAssetArrayChanged;
   ShapeAssetArrayChanged mChangeArraySignal;

public:
   enum ShapeAssetErrCode
   {
      TooManyVerts = AssetErrCode::Extended,
      TooManyBones,
      MissingAnimatons,
      Extended
   };

   static StringTableEntry smNoShapeAssetFallback;

   static const String mShapeErrCodeStrings[ShapeAssetErrCode::Extended - Parent::Extended + 1];

   static U32 getAssetErrCode(AssetPtr<ShapeAsset> shapeAsset) { if (shapeAsset) return shapeAsset->mLoadedState; else return 0; }

   static String getAssetErrstrn(U32 errCode)
   {
      if (errCode < Parent::Extended) return Parent::getAssetErrstrn(errCode);
      if (errCode > ShapeAssetErrCode::Extended) return "undefined error";
      return mShapeErrCodeStrings[errCode - Parent::Extended];
   };

   ShapeAsset();
   virtual ~ShapeAsset();

   /// Set up some global script interface stuff.
   static void consoleInit();

   /// Engine.
   static void initPersistFields();
   virtual void copyTo(SimObject* object);

   virtual void setDataField(StringTableEntry slotName, StringTableEntry array, StringTableEntry value);

   virtual void initializeAsset();

   /// Declare Console Object.
   DECLARE_CONOBJECT(ShapeAsset);

   bool loadShape();

   TSShape* getShape() { return mShape; }

   Resource<TSShape> getShapeResource() { return mShape; }

   void SplitSequencePathAndName(String& srcPath, String& srcName);
   StringTableEntry getShapeFileName() { return mFileName; }
   StringTableEntry getShapePath() { return mFilePath; }

   U32 getShapeFilenameHash() { return _StringTable::hashString(mFilePath); }

   Vector<AssetPtr<MaterialAsset>> getMaterialAssets() { return mMaterialAssets; }

   inline AssetPtr<MaterialAsset> getMaterialAsset(U32 matId)
   {
      if (matId >= mMaterialAssets.size())
         return nullptr;
      else
         return mMaterialAssets[matId];
   }

   void clearMaterialAssets() { mMaterialAssets.clear(); }

   void addMaterialAssets(AssetPtr<MaterialAsset> matPtr) { mMaterialAssets.push_back(matPtr); }

   S32 getMaterialCount() { return mMaterialAssets.size(); }
   S32 getAnimationCount() { return mAnimationAssets.size(); }
   ShapeAnimationAsset* getAnimation(S32 index);

   void _onResourceChanged(const Torque::Path& path);

   ShapeAssetChanged& getChangedSignal() { return mChangeSignal; }
   ShapeAssetArrayChanged& getChangedArraySignal() { return mChangeArraySignal; }

   void                    setShapeFile(const char* pScriptFile);
   inline StringTableEntry getShapeFile(void) const { return mFileName; };

   void                    setShapeConstructorFile(const char* pScriptFile);
   inline StringTableEntry getShapeConstructorFile(void) const { return mConstructorFileName; };

   inline StringTableEntry getShapeFilePath(void) const { return mFilePath; };
   inline StringTableEntry getShapeConstructorFilePath(void) const { return mConstructorFilePath; };

   //Imposter images
   void                    setDiffuseImposterFile(const char* pImageFile);
   inline StringTableEntry getDiffuseImposterFile(void) const { return mDiffuseImposterFileName; };
   inline StringTableEntry getDiffuseImposterFilePath(void) const { return mDiffuseImposterPath; };

   void                    setNormalImposterFile(const char* pImageFile);
   inline StringTableEntry getNormalImposterFile(void) const { return mNormalImposterFileName; };
   inline StringTableEntry getNormalImposterFilePath(void) const { return mNormalImposterPath; };

   static U32 getAssetByFilename(StringTableEntry fileName, AssetPtr<ShapeAsset>* shapeAsset);

   static StringTableEntry getAssetIdByFilename(StringTableEntry fileName);
   static U32 getAssetById(StringTableEntry assetId, AssetPtr<ShapeAsset>* shapeAsset);

#ifdef TORQUE_TOOLS
   const char* generateCachedPreviewImage(S32 resolution, String overrideMaterial = "");
#endif

protected:
   virtual void            onAssetRefresh(void);

   static bool setShapeFile(void* obj, StringTableEntry index, StringTableEntry data) { static_cast<ShapeAsset*>(obj)->setShapeFile(data); return false; }
   static const char* getShapeFile(void* obj, const char* data) { return static_cast<ShapeAsset*>(obj)->getShapeFile(); }

   static bool setShapeConstructorFile(void* obj, const char* index, const char* data) { static_cast<ShapeAsset*>(obj)->setShapeConstructorFile(data); return false; }
   static const char* getShapeConstructorFile(void* obj, const char* data) { return static_cast<ShapeAsset*>(obj)->getShapeConstructorFile(); }

   static bool setDiffuseImposterFile(void* obj, StringTableEntry index, StringTableEntry data) { static_cast<ShapeAsset*>(obj)->setDiffuseImposterFile(data); return false; }
   static const char* getDiffuseImposterFile(void* obj, const char* data) { return static_cast<ShapeAsset*>(obj)->getDiffuseImposterFile(); }
   static bool setNormalImposterFile(void* obj, StringTableEntry index, StringTableEntry data) { static_cast<ShapeAsset*>(obj)->setNormalImposterFile(data); return false; }
   static const char* getNormalImposterFile(void* obj, const char* data) { return static_cast<ShapeAsset*>(obj)->getNormalImposterFile(); }
};

DefineConsoleType(TypeShapeAssetPtr, S32)
DefineConsoleType(TypeShapeAssetId, String)

#ifdef TORQUE_TOOLS
//-----------------------------------------------------------------------------
// TypeAssetId GuiInspectorField Class
//-----------------------------------------------------------------------------
class GuiInspectorTypeShapeAssetPtr : public GuiInspectorTypeFileName
{
   typedef GuiInspectorTypeFileName Parent;
public:

   GuiTextCtrl* mLabel;
   GuiBitmapButtonCtrl* mPreviewBorderButton;
   GuiBitmapCtrl* mPreviewImage;
   GuiButtonCtrl* mEditButton;

   DECLARE_CONOBJECT(GuiInspectorTypeShapeAssetPtr);
   static void consoleInit();

   virtual GuiControl* constructEditControl();
   virtual bool updateRects();

   virtual void updateValue();

   void updatePreviewImage();
   void setPreviewImage(StringTableEntry assetId);
};

class GuiInspectorTypeShapeAssetId : public GuiInspectorTypeShapeAssetPtr
{
   typedef GuiInspectorTypeShapeAssetPtr Parent;
public:

   DECLARE_CONOBJECT(GuiInspectorTypeShapeAssetId);
   static void consoleInit();
};
#endif

#pragma region Singular Asset Macros

#define DECLARE_SHAPEASSET(className,name,changeFunc) public: \
   Resource<TSShape>m##name;\
   StringTableEntry m##name##Name; \
   StringTableEntry m##name##AssetId;\
   AssetPtr<ShapeAsset>  m##name##Asset;\
public: \
   const StringTableEntry get##name##File() const { return StringTable->insert(m##name##Name); }\
   void set##name##Name(const FileName &_in) { m##name##Name = _in;}\
   const AssetPtr<ShapeAsset> & get##name##Asset() const { return m##name##Asset; }\
   void set##name##Asset(const AssetPtr<ShapeAsset> &_in) { m##name##Asset = _in;}\
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
            m##name = NULL;\
            return true;\
         }\
         \
         if (AssetDatabase.isDeclaredAsset(_in))\
         {\
            m##name##AssetId = _in;\
            \
            U32 assetState = ShapeAsset::getAssetById(m##name##AssetId, &m##name##Asset);\
            \
            if (ShapeAsset::Ok == assetState)\
            {\
               m##name##Name = StringTable->EmptyString();\
            }\
         }\
         else\
         {\
            StringTableEntry assetId = ShapeAsset::getAssetIdByFilename(_in);\
            if (assetId != StringTable->EmptyString())\
            {\
               m##name##AssetId = assetId;\
               if (ShapeAsset::getAssetById(m##name##AssetId, &m##name##Asset) == ShapeAsset::Ok)\
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
      if (get##name() != StringTable->EmptyString() && m##name##Asset.notNull())\
      {\
         m##name = m##name##Asset->getShapeResource();\
         \
         m##name##Asset->getChangedSignal().notify(this, &className::changeFunc);\
      }\
      else\
      {\
         m##name = NULL;\
      }\
      \
      if(get##name() == StringTable->EmptyString())\
         return true;\
      \
      if (m##name##Asset.notNull() && m##name##Asset->getStatus() != ShapeAsset::Ok)\
      {\
         Con::errorf("%s(%s)::_set%s() - shape asset failure \"%s\" due to [%s]", macroText(className), getName(), macroText(name), _in, ShapeAsset::getAssetErrstrn(m##name##Asset->getStatus()).c_str());\
         return false; \
      }\
      else if (!m##name)\
      {\
         Con::errorf("%s(%s)::_set%s() - Couldn't load shape \"%s\"", macroText(className), getName(), macroText(name), _in);\
         return false;\
      }\
      return true;\
   }\
   \
   const StringTableEntry get##name() const\
   {\
      if (m##name##Asset && (m##name##Asset->getShapePath() != StringTable->EmptyString()))\
         return m##name##Asset->getShapePath();\
      else if (m##name##AssetId != StringTable->EmptyString())\
         return m##name##AssetId;\
      else if (m##name##Name != StringTable->EmptyString())\
         return m##name##Name;\
      else\
         return StringTable->EmptyString();\
   }\
   Resource<TSShape> get##name##Resource() \
   {\
      return m##name;\
   }\
   bool is##name##Valid() {return (get##name() != StringTable->EmptyString() && m##name##Asset->getStatus() == AssetBase::Ok); }

#ifdef TORQUE_SHOW_LEGACY_FILE_FIELDS

#define INITPERSISTFIELD_SHAPEASSET(name, consoleClass, docs) \
   addProtectedField(assetText(name, File), TypeShapeFilename, Offset(m##name##Name, consoleClass), _set##name##Data, & defaultProtectedGetFn, assetText(name, docs)); \
   addProtectedField(assetText(name, Asset), TypeShapeAssetId, Offset(m##name##AssetId, consoleClass), _set##name##Data, & defaultProtectedGetFn, assetText(name, asset reference.));

#else

#define INITPERSISTFIELD_SHAPEASSET(name, consoleClass, docs) \
   addProtectedField(assetText(name, File), TypeShapeFilename, Offset(m##name##Name, consoleClass), _set##name##Data, & defaultProtectedGetFn, assetText(name, docs), AbstractClassRep::FIELD_HideInInspectors); \
   addProtectedField(assetText(name, Asset), TypeShapeAssetId, Offset(m##name##AssetId, consoleClass), _set##name##Data, & defaultProtectedGetFn, assetText(name, asset reference.));

#endif // SHOW_LEGACY_FILE_FIELDS

#pragma endregion

#pragma region Arrayed Asset Macros

#define DECLARE_SHAPEASSET_ARRAY(className,name,max) public: \
   static const U32 sm##name##Count = max;\
   Resource<TSShape>m##name[max];\
   StringTableEntry m##name##Name[max]; \
   StringTableEntry m##name##AssetId[max];\
   AssetPtr<ShapeAsset>  m##name##Asset[max];\
public: \
   const StringTableEntry get##name##File(const U32& index) const { return m##name##Name[index]; }\
   void set##name##Name(const FileName &_in, const U32& index) { m##name##Name[index] = _in;}\
   const AssetPtr<ShapeAsset> & get##name##Asset(const U32& index) const { return m##name##Asset[index]; }\
   void set##name##Asset(const AssetPtr<ShapeAsset> &_in, const U32& index) { m##name##Asset[index] = _in;}\
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
            m##name[index] = NULL;\
            return true;\
         }\
         \
         if (AssetDatabase.isDeclaredAsset(_in))\
         {\
            m##name##AssetId[index] = _in;\
            \
            U32 assetState = ShapeAsset::getAssetById(m##name##AssetId[index], &m##name##Asset[index]);\
            \
            if (ShapeAsset::Ok == assetState)\
            {\
               m##name##Name[index] = StringTable->EmptyString();\
            }\
         }\
         else\
         {\
            StringTableEntry assetId = ShapeAsset::getAssetIdByFilename(_in);\
            if (assetId != StringTable->EmptyString())\
            {\
               m##name##AssetId[index] = assetId;\
               if (ShapeAsset::getAssetById(m##name##AssetId[index], &m##name##Asset[index]) == ShapeAsset::Ok)\
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
      if (get##name(index) != StringTable->EmptyString() && m##name##Asset[index].notNull())\
      {\
         m##name[index] = m##name##Asset[index]->getShapeResource();\
      }\
      else\
      {\
         m##name[index] = NULL;\
      }\
      \
      if(get##name(index) == StringTable->EmptyString())\
         return true;\
      \
      if (m##name##Asset[index].notNull() && m##name##Asset[index]->getStatus() != ShapeAsset::Ok)\
      {\
         Con::errorf("%s(%s)::_set%s(%i) - shape asset failure \"%s\" due to [%s]", macroText(className), getName(), macroText(name), index, _in, ShapeAsset::getAssetErrstrn(m##name##Asset[index]->getStatus()).c_str());\
         return false; \
      }\
      else if (!m##name[index])\
      {\
         Con::errorf("%s(%s)::_set%s(%i) - Couldn't load shape \"%s\"", macroText(className), getName(), macroText(name), index, _in);\
         return false; \
      }\
      return true;\
   }\
   \
   const StringTableEntry get##name(const U32& index) const\
   {\
      if (m##name##Asset[index] && (m##name##Asset[index]->getShapePath() != StringTable->EmptyString()))\
         return m##name##Asset[index]->getShapePath();\
      else if (m##name##AssetId[index] != StringTable->EmptyString())\
         return m##name##AssetId[index];\
      else if (m##name##Name[index] != StringTable->EmptyString())\
         return StringTable->insert(m##name##Name[index]);\
      else\
         return StringTable->EmptyString();\
   }\
   Resource<TSShape> get##name##Resource(const U32& index) \
   {\
      if(index >= sm##name##Count || index < 0)\
         return ResourceManager::get().load( "" );\
      return m##name[index];\
   }\
   bool is##name##Valid(const U32& id) {return (get##name(id) != StringTable->EmptyString() && m##name##Asset[id]->getStatus() == AssetBase::Ok); }

#ifdef TORQUE_SHOW_LEGACY_FILE_FIELDS

#define INITPERSISTFIELD_SHAPEASSET_ARRAY(name, arraySize, consoleClass, docs) \
   addProtectedField(assetText(name, File), TypeShapeFilename, Offset(m##name##Name, consoleClass), _set##name##Data, & defaultProtectedGetFn, arraySize, assetText(name, docs)); \
   addProtectedField(assetText(name, Asset), TypeShapeAssetId, Offset(m##name##AssetId, consoleClass), _set##name##Data, & defaultProtectedGetFn, arraySize, assetText(name, asset reference.));

#else

#define INITPERSISTFIELD_SHAPEASSET_ARRAY(name, arraySize, consoleClass, docs) \
   addProtectedField(assetText(name, File), TypeShapeFilename, Offset(m##name##Name, consoleClass), _set##name##Data, & defaultProtectedGetFn, arraySize, assetText(name, docs), AbstractClassRep::FIELD_HideInInspectors); \
   addProtectedField(assetText(name, Asset), TypeShapeAssetId, Offset(m##name##AssetId, consoleClass), _set##name##Data, & defaultProtectedGetFn, arraySize,assetText(name, asset reference.));

#endif // SHOW_LEGACY_FILE_FIELDS

#pragma endregion

#endif
