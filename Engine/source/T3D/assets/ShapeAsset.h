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

   //Material assets we're dependent on and use
   Vector<StringTableEntry> mMaterialAssetIds;
   Vector<AssetPtr<MaterialAsset>> mMaterialAssets;

   //Animation assets we're dependent on and use
   Vector<StringTableEntry> mAnimationAssetIds;
   Vector<AssetPtr<ShapeAnimationAsset>> mAnimationAssets;

   typedef Signal<void()> ShapeAssetChanged;

   ShapeAssetChanged mChangeSignal;

public:
   enum ShapeAssetErrCode
   {
      TooManyVerts = AssetErrCode::Extended,
      TooManyBones,
      MissingAnimatons,
      Extended
   };

   static const String mErrCodeStrings[ShapeAssetErrCode::Extended - Parent::Extended + 1];
   static String getAssetErrstrn(U32 errCode)
   {
      if (errCode < Parent::Extended) return Parent::getAssetErrstrn(errCode);
      if (errCode > ShapeAssetErrCode::Extended) return "undefined error";
      return mErrCodeStrings[errCode];
   };

   ShapeAsset();
   virtual ~ShapeAsset();

   /// Engine.
   static void initPersistFields();
   virtual void copyTo(SimObject* object);

   virtual void setDataField(StringTableEntry slotName, const char *array, const char *value);

   virtual void initializeAsset();

   /// Declare Console Object.
   DECLARE_CONOBJECT(ShapeAsset);

   bool loadShape();
   U32 mLoadedState;

   TSShape* getShape() { return mShape; }

   Resource<TSShape> getShapeResource() { return mShape; }

   void SplitSequencePathAndName(String& srcPath, String& srcName);
   StringTableEntry getShapeFilename() { return mFilePath; }
   
   U32 getShapeFilenameHash() { return _StringTable::hashString(mFilePath); }

   Vector<AssetPtr<MaterialAsset>> getMaterialAssets() { return mMaterialAssets; }

   inline AssetPtr<MaterialAsset> getMaterialAsset(U32 matId) 
   { 
      if(matId >= mMaterialAssets.size()) 
          return nullptr; 
      else 
         return mMaterialAssets[matId]; 
   }

   void clearMaterialAssets() { mMaterialAssets.clear(); }

   void addMaterialAssets(AssetPtr<MaterialAsset> matPtr) { mMaterialAssets.push_back(matPtr); }

   S32 getMaterialCount() { return mMaterialAssets.size(); }
   S32 getAnimationCount() { return mAnimationAssets.size(); }
   ShapeAnimationAsset* getAnimation(S32 index);

   void _onResourceChanged(const Torque::Path &path);

   ShapeAssetChanged& getChangedSignal() { return mChangeSignal; }

   void                    setShapeFile(const char* pScriptFile);
   inline StringTableEntry getShapeFile(void) const { return mFileName; };

   void                    setShapeConstructorFile(const char* pScriptFile);
   inline StringTableEntry getShapeConstructorFile(void) const { return mConstructorFileName; };

   inline StringTableEntry getShapeFilePath(void) const { return mFilePath; };
   inline StringTableEntry getShapeConstructorFilePath(void) const { return mConstructorFilePath; };

   static bool getAssetByFilename(StringTableEntry fileName, AssetPtr<ShapeAsset>* shapeAsset);

   static StringTableEntry getAssetIdByFilename(StringTableEntry fileName);
   static U32 getAssetById(StringTableEntry assetId, AssetPtr<ShapeAsset>* shapeAsset);

   static StringTableEntry getNoShapeAssetId() { return StringTable->insert("Core_Rendering:noshape"); }

protected:
   virtual void            onAssetRefresh(void);

   static bool setShapeFile(void *obj, const char *index, const char *data) { static_cast<ShapeAsset*>(obj)->setShapeFile(data); return false; }
   static const char* getShapeFile(void* obj, const char* data) { return static_cast<ShapeAsset*>(obj)->getShapeFile(); }

   static bool setShapeConstructorFile(void* obj, const char* index, const char* data) { static_cast<ShapeAsset*>(obj)->setShapeConstructorFile(data); return false; }
   static const char* getShapeConstructorFile(void* obj, const char* data) { return static_cast<ShapeAsset*>(obj)->getShapeConstructorFile(); }

};

#ifdef TORQUE_TOOLS
DefineConsoleType(TypeShapeAssetPtr, S32)
DefineConsoleType(TypeShapeAssetId, String)

//-----------------------------------------------------------------------------
// TypeAssetId GuiInspectorField Class
//-----------------------------------------------------------------------------
class GuiInspectorTypeShapeAssetPtr : public GuiInspectorTypeFileName
{
   typedef GuiInspectorTypeFileName Parent;
public:

   GuiBitmapButtonCtrl  *mShapeEdButton;

   DECLARE_CONOBJECT(GuiInspectorTypeShapeAssetPtr);
   static void consoleInit();

   virtual GuiControl* constructEditControl();
   virtual bool updateRects();
};

class GuiInspectorTypeShapeAssetId : public GuiInspectorTypeShapeAssetPtr
{
   typedef GuiInspectorTypeShapeAssetPtr Parent;
public:

   DECLARE_CONOBJECT(GuiInspectorTypeShapeAssetId);
   static void consoleInit();
};
#endif

#define assetText(x,suff) std::string(std::string(#x) + std::string(#suff)).c_str()

#define initShapeAsset(name) m##name##Filename = StringTable->EmptyString(); m##name##AssetId = StringTable->EmptyString(); m##name##Asset = NULL;
#define bindShapeAsset(name) if (m##name##AssetId != StringTable->EmptyString()) m##name##Asset = m##name##AssetId;

#define scriptBindShapeAsset(name, consoleClass, docs) addProtectedField(assetText(name, File), TypeShapeFilename, Offset(m##name##Filename, consoleClass), consoleClass::_set##name##Filename,  & defaultProtectedGetFn, assetText(name, docs)); \
                                      addProtectedField(assetText(name, Asset), TypeShapeAssetId, Offset(m##name##AssetId, consoleClass), consoleClass::_set##name##Asset, & defaultProtectedGetFn, assetText(name, asset reference.));

#define DECLARE_SHAPEASSET(className,name)      protected: \
                                      StringTableEntry m##name##Filename;\
                                      StringTableEntry m##name##AssetId;\
                                      AssetPtr<ShapeAsset>  m##name##Asset;\
                                      public: \
                                      const StringTableEntry& get##name() const { return m##name##Filename; }\
                                      void set##name(FileName _in) { m##name##Filename = _in; }\
                                      const AssetPtr<ShapeAsset> & get##name##Asset() const { return m##name##Asset; }\
                                      void set##name##Asset(AssetPtr<ShapeAsset>_in) { m##name##Asset = _in; }\
static bool _set##name##Filename(void* obj, const char* index, const char* data)\
{\
   className* shape = static_cast<className*>(obj);\
   \
   StringTableEntry assetId = ShapeAsset::getAssetIdByFilename(StringTable->insert(data));\
   if (assetId != StringTable->EmptyString())\
   {\
      if (shape->_set##name##Asset(obj, index, assetId))\
      {\
         if (assetId == StringTable->insert("Core_Rendering:noShape"))\
         {\
            shape->m##name##Filename = data;\
            shape->m##name##AssetId = StringTable->EmptyString();\
            \
            return true;\
         }\
         else\
         {\
            shape->m##name##AssetId = assetId;\
            shape->m##name##Filename = StringTable->EmptyString();\
            \
            return false;\
         }\
      }\
   }\
   else\
   {\
      shape->m##name##Asset = StringTable->EmptyString();\
   }\
   \
   return true;\
}\
\
static bool _set##name##Asset(void* obj, const char* index, const char* data)\
{\
   className* shape = static_cast<className*>(obj);\
   shape->m##name##AssetId = StringTable->insert(data);\
   if (ShapeAsset::getAssetById(shape->m##name##AssetId, &shape->m##name##Asset))\
   {\
      if (shape->m##name##Asset.getAssetId() != StringTable->insert("Core_Rendering:noShape"))\
         shape->m##name##Filename = StringTable->EmptyString();\
      \
      shape->setMaskBits(-1);\
      return true;\
   }\
   return false;\
}

#endif

