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

   static U32 getAssetErrCode(AssetPtr<ShapeAsset> shapeAsset) { if (shapeAsset) return shapeAsset->mLoadedState; else return 0; }

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

#ifdef TORQUE_TOOLS
   const char* generateCachedPreviewImage(S32 resolution);
#endif

protected:
   virtual void            onAssetRefresh(void);

   static bool setShapeFile(void* obj, StringTableEntry index, StringTableEntry data) { static_cast<ShapeAsset*>(obj)->setShapeFile(data); return false; }
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

   GuiBitmapButtonCtrl* mShapeEdButton;

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

#define DECLARE_SHAPEASSET(className,name) public: \
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
      if (_in == StringTable->EmptyString())\
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
         else\
         {\
            m##name##Name = _in;\
            m##name##Asset = NULL;\
         }\
      }\
      else\
      {\
         StringTableEntry assetId = ShapeAsset::getAssetIdByFilename(_in);\
         if (assetId != StringTable->EmptyString())\
         {\
            m##name##AssetId = _in;\
            if (ShapeAsset::getAssetById(m##name##AssetId, &m##name##Asset))\
            {\
               if (m##name##Asset.getAssetId() != StringTable->insert("Core_Rendering:noShape"))\
               {\
                  m##name##Name = StringTable->EmptyString();\
               }\
               else\
               {\
                  m##name##AssetId = StringTable->EmptyString();\
               }\
            }\
         }\
         else\
         {\
            m##name##Name = _in;\
            m##name##AssetId = StringTable->EmptyString();\
            m##name##Asset = NULL;\
         }\
      }\
      if (get##name() != StringTable->EmptyString() && m##name##Asset.notNull())\
      {\
         m##name = m##name##Asset->getShapeResource();\
         \
         if (bool(m##name) == NULL)\
         {\
            Con::errorf("classname::_set##name() - %s: Couldn't load shape %s", assetText(className,""), get##name());\
            return false;\
         }\
         return true;\
      }\
      return false;\
   }\
   \
   const StringTableEntry get##name() const\
   {\
      if (m##name##Asset && (m##name##Asset->getShapePath() != StringTable->EmptyString()))\
         return m##name##Asset->getShapePath();\
      else if (m##name##Name != StringTable->EmptyString())\
         return StringTable->insert(m##name##Name);\
      else\
         return StringTable->EmptyString();\
   }\
   Resource<TSShape> get##name##Resource() \
   {\
      return m##name;\
   }

#define DECLARE_SHAPEASSET_SETGET(className, name)\
   static bool _set##name##Data(void* obj, const char* index, const char* data)\
   {\
      bool ret = false;\
      className* object = static_cast<className*>(obj);\
      ret = object->_set##name(StringTable->insert(data));\
      return ret;\
   }

#define DECLARE_SHAPEASSET_NET_SETGET(className, name, bitmask)\
   static bool _set##name##Data(void* obj, const char* index, const char* data)\
   {\
      bool ret = false;\
      className* object = static_cast<className*>(obj);\
      ret = object->_set##name(StringTable->insert(data));\
      if(ret)\
         object->setMaskBits(bitmask);\
      return ret;\
   }

#define DEF_SHAPEASSET_BINDS(className,name)\
DefineEngineMethod(className, get##name, String, (), , "get name")\
{\
   return object->get##name(); \
}\
DefineEngineMethod(className, get##name##Asset, String, (), , assetText(name, asset reference))\
{\
   return object->m##name##AssetId; \
}\
DefineEngineMethod(className, set##name, bool, (const char*  shape), , assetText(name,assignment. first tries asset then flat file.))\
{\
   return object->_set##name(StringTable->insert(shape));\
}

#define INIT_SHAPEASSET(name) \
   m##name##Name = StringTable->EmptyString(); \
   m##name##AssetId = StringTable->EmptyString(); \
   m##name##Asset = NULL; \
   m##name = NULL;\

#define INITPERSISTFIELD_SHAPEASSET(name, consoleClass, docs) \
   addProtectedField(assetText(name, File), TypeShapeFilename, Offset(m##name##Name, consoleClass), _set##name##Data, & defaultProtectedGetFn, assetText(name, docs)); \
   addProtectedField(assetText(name, Asset), TypeShapeAssetId, Offset(m##name##AssetId, consoleClass), _set##name##Data, & defaultProtectedGetFn, assetText(name, asset reference.));

#define CLONE_SHAPEASSET(name) \
   m##name##Name = other.m##name##Name;\
   m##name##AssetId = other.m##name##AssetId;\
   m##name##Asset = other.m##name##Asset;\

#define PACKDATA_SHAPEASSET(name)\
   if (stream->writeFlag(m##name##Asset.notNull()))\
   {\
      stream->writeString(m##name##Asset.getAssetId());\
   }\
   else\
      stream->writeString(m##name##Name);

#define UNPACKDATA_SHAPEASSET(name)\
   if (stream->readFlag())\
   {\
      m##name##AssetId = stream->readSTString();\
   }\
   else\
      m##name##Name = stream->readSTString();

#define PACK_SHAPEASSET(netconn, name)\
   if (stream->writeFlag(m##name##Asset.notNull()))\
   {\
      NetStringHandle assetIdStr = m##name##Asset.getAssetId();\
      netconn->packNetStringHandleU(stream, assetIdStr);\
   }\
   else\
      stream->writeString(m##name##Name);

#define UNPACK_SHAPEASSET(netconn, name)\
   if (stream->readFlag())\
   {\
      m##name##AssetId = StringTable->insert(netconn->unpackNetStringHandleU(stream).getString());\
      _set##name(m##name##AssetId);\
   }\
   else\
      m##name##Name = stream->readSTString();

#endif
