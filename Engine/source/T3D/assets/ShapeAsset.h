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
   typedef AssetPtr<ShapeAsset> ConcreteAssetPtr;

public:
   enum ShapeAssetErrCode
   {
      TooManyVerts = AssetErrCode::Extended,
      TooManyBones,
      MissingAnimatons,
      Extended
   };

   static StringTableEntry smNoShapeAssetFallback;

   static const String mErrCodeStrings[U32(ShapeAssetErrCode::Extended) - U32(Parent::Extended) + 1];
   static U32 getAssetErrCode(ConcreteAssetPtr checkAsset) { if (checkAsset) return checkAsset->mLoadedState; else return 0; }

   static String getAssetErrstrn(U32 errCode)
   {
      if (errCode < Parent::Extended) return Parent::getAssetErrstrn(errCode);
      if (errCode > ShapeAssetErrCode::Extended) return "undefined error";
      return mErrCodeStrings[errCode - Parent::Extended];
   };

private:
   StringTableEntry   mShapeFile;
   StringTableEntry   mConstructorFileName;
   StringTableEntry   mDiffuseImposterFileName;
   StringTableEntry   mNormalImposterFileName;

   //Material assets we're dependent on and use
   Vector<StringTableEntry> mMaterialAssetIds;
   Vector<AssetPtr<MaterialAsset>> mMaterialAssets;

   //Animation assets we're dependent on and use
   Vector<StringTableEntry> mAnimationAssetIds;
   Vector<AssetPtr<ShapeAnimationAsset>> mAnimationAssets;

   Resource<TSShape>	 mShape;
public:

   ShapeAsset();
   virtual ~ShapeAsset();

   /// Set up some global script interface stuff.
   static void consoleInit();

   /// Engine.
   static void initPersistFields();
   void copyTo(SimObject* object) override;

   virtual void setDataField(StringTableEntry slotName, StringTableEntry array, StringTableEntry value);

   /// Declare Console Object.
   DECLARE_CONOBJECT(ShapeAsset);

   U32 load() override;

   TSShape* getShape() { load(); return mShape; }

   Resource<TSShape> getShapeResource() { load(); return mShape; }

   void SplitSequencePathAndName(String& srcPath, String& srcName);

   U32 getShapeFilenameHash() { return _StringTable::hashString(mShapeFile); }

   Vector<AssetPtr<MaterialAsset>> getMaterialAssets() { return mMaterialAssets; }

   inline AssetPtr<MaterialAsset> getMaterialAsset(U32 matId)
   {
      if (matId >= mMaterialAssets.size())
         return NULL;
      else
         return mMaterialAssets[matId];
   }

   void clearMaterialAssets() { mMaterialAssets.clear(); }

   void addMaterialAssets(AssetPtr<MaterialAsset> matPtr) { mMaterialAssets.push_back(matPtr); }

   S32 getMaterialCount() { return mMaterialAssets.size(); }
   S32 getAnimationCount() { return mAnimationAssets.size(); }
   ShapeAnimationAsset* getAnimation(S32 index);

   void _onResourceChanged(const Torque::Path& path);

   void                    setShapeFile(const char* pScriptFile);
   inline StringTableEntry getShapeFile(void) const { return mShapeFile; };

   void                    setShapeConstructorFile(const char* pScriptFile);
   inline StringTableEntry getShapeConstructorFile(void) const { return mConstructorFileName; };

   //Imposter images
   void                    setDiffuseImposterFile(const char* pImageFile);
   inline StringTableEntry getDiffuseImposterFile(void) const { return mDiffuseImposterFileName; };

   void                    setNormalImposterFile(const char* pImageFile);
   inline StringTableEntry getNormalImposterFile(void) const { return mNormalImposterFileName; };

   static U32 getAssetByFilename(StringTableEntry fileName, AssetPtr<ShapeAsset>* shapeAsset);

   static StringTableEntry getAssetIdByFilename(StringTableEntry fileName);
   static U32 getAssetById(StringTableEntry assetId, AssetPtr<ShapeAsset>* shapeAsset);

#ifdef TORQUE_TOOLS
   const char* generateCachedPreviewImage(S32 resolution, String overrideMaterial = "");
#endif

protected:
   // Asset Base callback
   void initializeAsset(void) override;
   void onAssetRefresh(void) override;

   /// Taml callbacks.
   void onTamlPreWrite(void) override;
   void onTamlPostWrite(void) override;

protected:
   static bool setShapeFile(void* obj, StringTableEntry index, StringTableEntry data) { static_cast<ShapeAsset*>(obj)->setShapeFile(data); return false; }
   static const char* getShapeFile(void* obj, const char* data) { return static_cast<ShapeAsset*>(obj)->getShapeFile(); }
   static bool writeShapeFile(void* obj, StringTableEntry pFieldName) { return static_cast<ShapeAsset*>(obj)->getShapeFile() != StringTable->EmptyString(); }

   static bool setShapeConstructorFile(void* obj, const char* index, const char* data) { static_cast<ShapeAsset*>(obj)->setShapeConstructorFile(data); return false; }
   static const char* getShapeConstructorFile(void* obj, const char* data) { return static_cast<ShapeAsset*>(obj)->getShapeConstructorFile(); }

   static bool setDiffuseImposterFile(void* obj, StringTableEntry index, StringTableEntry data) { static_cast<ShapeAsset*>(obj)->setDiffuseImposterFile(data); return false; }
   static const char* getDiffuseImposterFile(void* obj, const char* data) { return static_cast<ShapeAsset*>(obj)->getDiffuseImposterFile(); }

   static bool setNormalImposterFile(void* obj, StringTableEntry index, StringTableEntry data) { static_cast<ShapeAsset*>(obj)->setNormalImposterFile(data); return false; }
   static const char* getNormalImposterFile(void* obj, const char* data) { return static_cast<ShapeAsset*>(obj)->getNormalImposterFile(); }
};

DefineConsoleType(TypeShapeAssetId, String)

DECLARE_STRUCT(AssetPtr<ShapeAsset>)
DefineConsoleType(TypeShapeAssetPtr, AssetPtr<ShapeAsset>)

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

   GuiControl* constructEditControl() override;
   bool updateRects() override;

   void updateValue() override;

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

//-----------------------------------------------------------------------------
// REFACTOR
//-----------------------------------------------------------------------------

#pragma region Refactor Asset Macros

#define DECLARE_SHAPEASSET_REFACTOR(className, name)                                                                                                                          \
private:                                                                                                                                                                      \
   AssetPtr<ShapeAsset> m##name##Asset;                                                                                                                                       \
   StringTableEntry     m##name##File = StringTable->EmptyString();                                                                                                           \
public:                                                                                                                                                                       \
   void _set##name(StringTableEntry _in) {                                                                                                                                    \
      if (m##name##Asset.getAssetId() == _in)                                                                                                                                 \
         return;                                                                                                                                                              \
      if(get##name##File() == _in)                                                                                                                                            \
         return;                                                                                                                                                              \
      if(_in == NULL || !String::compare(_in,StringTable->EmptyString()))                                                                                                       \
      {                                                                                                                                                                       \
         m##name##Asset = NULL;                                                                                                                                               \
         m##name##File = "";                                                                                                                                                  \
         return;                                                                                                                                                              \
      }                                                                                                                                                                       \
      if (!AssetDatabase.isDeclaredAsset(_in))                                                                                                                                \
      {                                                                                                                                                                       \
         StringTableEntry shapeAssetId = StringTable->EmptyString();                                                                                                          \
         AssetQuery query;                                                                                                                                                    \
         S32 foundAssetcount = AssetDatabase.findAssetLooseFile(&query, _in);                                                                                                 \
         if (foundAssetcount != 0)                                                                                                                                            \
         {                                                                                                                                                                    \
            shapeAssetId = query.mAssetList[0];                                                                                                                               \
         }                                                                                                                                                                    \
         else if (Torque::FS::IsFile(_in) || (_in[0] == '$' || _in[0] == '#'))                                                                                                \
         {                                                                                                                                                                    \
            shapeAssetId = ShapeAsset::getAssetIdByFilename(_in);                                                                                                             \
            if (shapeAssetId == ShapeAsset::smNoShapeAssetFallback)                                                                                                           \
            {                                                                                                                                                                 \
               ShapeAsset* privateShape = new ShapeAsset();                                                                                                                   \
               privateShape->setShapeFile(_in);                                                                                                                               \
               shapeAssetId = AssetDatabase.addPrivateAsset(privateShape);                                                                                                    \
            }                                                                                                                                                                 \
         }                                                                                                                                                                    \
         else                                                                                                                                                                 \
         {                                                                                                                                                                    \
            Con::warnf("%s::%s: Could not find asset for: %s using fallback", #className, #name, _in);                                                                        \
            shapeAssetId = ShapeAsset::smNoShapeAssetFallback;                                                                                                                \
         }                                                                                                                                                                    \
         m##name##Asset = shapeAssetId;                                                                                                                                       \
         m##name##File = _in;                                                                                                                                                 \
      }                                                                                                                                                                       \
      else                                                                                                                                                                    \
      {                                                                                                                                                                       \
         m##name##Asset = _in;                                                                                                                                                \
         m##name##File = get##name##File();                                                                                                                                   \
      }                                                                                                                                                                       \
   };                                                                                                                                                                         \
                                                                                                                                                                              \
   inline StringTableEntry _get##name##AssetId(void) const { return m##name##Asset.getAssetId(); }                                                                            \
   TSShape* get##name() { if (m##name##Asset.notNull()) return m##name##Asset->getShape(); else return NULL; }                                                                \
   AssetPtr<ShapeAsset> get##name##Asset(void) { return m##name##Asset; }                                                                                                     \
   static bool _set##name##Data(void* obj, const char* index, const char* data) { static_cast<className*>(obj)->_set##name(_getStringTable()->insert(data)); return false; }  \
   StringTableEntry get##name##File() { return m##name##Asset.notNull() ? m##name##Asset->getShapeFile() : ""; }

#define DECLARE_SHAPEASSET_NET_REFACTOR(className, name, mask)                                                                                                                \
private:                                                                                                                                                                      \
   AssetPtr<ShapeAsset> m##name##Asset;                                                                                                                                       \
   StringTableEntry     m##name##File = StringTable->EmptyString();                                                                                                           \
public:                                                                                                                                                                       \
   void _set##name(StringTableEntry _in) {                                                                                                                                    \
      if (m##name##Asset.getAssetId() == _in)                                                                                                                                 \
         return;                                                                                                                                                              \
      if(get##name##File() == _in)                                                                                                                                            \
         return;                                                                                                                                                              \
      if(_in == NULL || !String::compare(_in,StringTable->EmptyString()))                                                                                                       \
      {                                                                                                                                                                       \
         m##name##Asset = NULL;                                                                                                                                               \
         m##name##File = "";                                                                                                                                                  \
         setMaskBits(mask);                                                                                                                                                   \
         return;                                                                                                                                                              \
      }                                                                                                                                                                       \
      if (!AssetDatabase.isDeclaredAsset(_in))                                                                                                                                \
      {                                                                                                                                                                       \
         StringTableEntry shapeAssetId = StringTable->EmptyString();                                                                                                          \
         AssetQuery query;                                                                                                                                                    \
         S32 foundAssetcount = AssetDatabase.findAssetLooseFile(&query, _in);                                                                                                 \
         if (foundAssetcount != 0)                                                                                                                                            \
         {                                                                                                                                                                    \
            shapeAssetId = query.mAssetList[0];                                                                                                                               \
         }                                                                                                                                                                    \
         else if (Torque::FS::IsFile(_in) || (_in[0] == '$' || _in[0] == '#'))                                                                                                \
         {                                                                                                                                                                    \
            shapeAssetId = ShapeAsset::getAssetIdByFilename(_in);                                                                                                             \
            if (shapeAssetId == ShapeAsset::smNoShapeAssetFallback)                                                                                                           \
            {                                                                                                                                                                 \
               ShapeAsset* privateShape = new ShapeAsset();                                                                                                                   \
               privateShape->setShapeFile(_in);                                                                                                                               \
               shapeAssetId = AssetDatabase.addPrivateAsset(privateShape);                                                                                                    \
            }                                                                                                                                                                 \
         }                                                                                                                                                                    \
         else                                                                                                                                                                 \
         {                                                                                                                                                                    \
            Con::warnf("%s::%s: Could not find asset for: %s using fallback", #className, #name, _in);                                                                        \
            shapeAssetId = ShapeAsset::smNoShapeAssetFallback;                                                                                                                \
         }                                                                                                                                                                    \
         m##name##Asset = shapeAssetId;                                                                                                                                       \
         m##name##File = _in;                                                                                                                                                 \
      }                                                                                                                                                                       \
      else                                                                                                                                                                    \
      {                                                                                                                                                                       \
         m##name##Asset = _in;                                                                                                                                                \
         m##name##File = get##name##File();                                                                                                                                   \
      }                                                                                                                                                                       \
      setMaskBits(mask);                                                                                                                                                      \
   };                                                                                                                                                                         \
                                                                                                                                                                              \
   inline StringTableEntry _get##name##AssetId(void) const { return m##name##Asset.getAssetId(); }                                                                            \
   TSShape* get##name() { if (m##name##Asset.notNull()) return m##name##Asset->getShape(); else return NULL; }                                                                \
   AssetPtr<ShapeAsset> get##name##Asset(void) { return m##name##Asset; }                                                                                                     \
   static bool _set##name##Data(void* obj, const char* index, const char* data) { static_cast<className*>(obj)->_set##name(_getStringTable()->insert(data)); return false; }  \
   StringTableEntry get##name##File() { return m##name##Asset.notNull() ? m##name##Asset->getShapeFile() : ""; }  

#define INITPERSISTFIELD_SHAPEASSET_REFACTOR(name, consoleClass, docs)                                                                                                        \
   addProtectedField(assetText(name, Asset), TypeShapeAssetPtr, Offset(m##name##Asset, consoleClass), _set##name##Data, &defaultProtectedGetFn, assetDoc(name, asset docs.)); \
   addProtectedField(assetText(name, File), TypeFilename, Offset(m##name##File, consoleClass), _set##name##Data, &defaultProtectedGetFn, assetDoc(name, file docs.), AbstractClassRep::FIELD_HideInInspectors);


#define DECLARE_SHAPEASSET_ARRAY_REFACTOR(className, name, max)                                                                                                               \
private:                                                                                                                                                                      \
   AssetPtr<ShapeAsset> m##name##Asset[max];                                                                                                                                  \
   StringTableEntry     m##name##File[max] = {StringTable->EmptyString() };                                                                                                   \
public:                                                                                                                                                                       \
   void _set##name(StringTableEntry _in, const U32& index){                                                                                                                   \
      if (m##name##Asset[index].getAssetId() == _in)                                                                                                                          \
         return;                                                                                                                                                              \
      if(get##name##File(index) == _in)                                                                                                                                       \
         return;                                                                                                                                                              \
      if(_in == NULL || !String::compare(_in,StringTable->EmptyString()))                                                                                                       \
      {                                                                                                                                                                       \
         m##name##Asset[index] = NULL;                                                                                                                                        \
         m##name##File[index] = "";                                                                                                                                           \
         return;                                                                                                                                                              \
      }                                                                                                                                                                       \
      if (!AssetDatabase.isDeclaredAsset(_in))                                                                                                                                \
      {                                                                                                                                                                       \
         StringTableEntry shapeAssetId = StringTable->EmptyString();                                                                                                          \
         AssetQuery query;                                                                                                                                                    \
         S32 foundAssetcount = AssetDatabase.findAssetLooseFile(&query, _in);                                                                                                 \
         if (foundAssetcount != 0)                                                                                                                                            \
         {                                                                                                                                                                    \
            shapeAssetId = query.mAssetList[0];                                                                                                                               \
         }                                                                                                                                                                    \
         else if (Torque::FS::IsFile(_in) || (_in[0] == '$' || _in[0] == '#'))                                                                                                \
         {                                                                                                                                                                    \
            shapeAssetId = ShapeAsset::getAssetIdByFilename(_in);                                                                                                             \
            if (shapeAssetId == ShapeAsset::smNoShapeAssetFallback)                                                                                                           \
            {                                                                                                                                                                 \
               ShapeAsset* privateShape = new ShapeAsset();                                                                                                                   \
               privateShape->setShapeFile(_in);                                                                                                                               \
               shapeAssetId = AssetDatabase.addPrivateAsset(privateShape);                                                                                                    \
            }                                                                                                                                                                 \
         }                                                                                                                                                                    \
         else                                                                                                                                                                 \
         {                                                                                                                                                                    \
            Con::warnf("%s::%s: Could not find asset for: %s using fallback", #className, #name, _in);                                                                        \
            shapeAssetId = ShapeAsset::smNoShapeAssetFallback;                                                                                                                \
         }                                                                                                                                                                    \
         m##name##Asset[index] = shapeAssetId;                                                                                                                                \
         m##name##File[index] = _in;                                                                                                                                          \
      }                                                                                                                                                                       \
      else                                                                                                                                                                    \
      {                                                                                                                                                                       \
         m##name##Asset[index] = _in;                                                                                                                                         \
         m##name##File[index] = get##name##File(index);                                                                                                                       \
      }                                                                                                                                                                       \
   };                                                                                                                                                                         \
                                                                                                                                                                              \
   inline StringTableEntry _get##name##AssetId(const U32& index) const { return m##name##Asset[index].getAssetId(); }                                                         \
   TSShape* get##name(const U32& index) { if (m##name##Asset[index].notNull()) return m##name##Asset[index]->getShape(); else return NULL; }                                  \
   AssetPtr<ShapeAsset> get##name##Asset(const U32& index) { return m##name##Asset[index]; }                                                                                  \
   static bool _set##name##Data(void* obj, const char* index, const char* data) { static_cast<className*>(obj)->_set##name(_getStringTable()->insert(data), dAtoi(index)); return false;}\
   StringTableEntry get##name##File(const U32& idx) { return m##name##Asset[idx].notNull() ? m##name##Asset[idx]->getShapeFile() : ""; }

#define DECLARE_SHAPEASSET_ARRAY_NET_REFACTOR(className, name, max, mask)                                                                                                     \
private:                                                                                                                                                                      \
   AssetPtr<ShapeAsset> m##name##Asset[max];                                                                                                                                  \
   StringTableEntry     m##name##File[max] = {StringTable->EmptyString() };                                                                                                   \
public:                                                                                                                                                                       \
   void _set##name(StringTableEntry _in, const U32& index){                                                                                                                   \
      if (m##name##Asset[index].getAssetId() == _in)                                                                                                                          \
         return;                                                                                                                                                              \
      if(get##name##File(index) == _in)                                                                                                                                       \
         return;                                                                                                                                                              \
      if (_in == NULL || !String::compare(_in,StringTable->EmptyString()))                                                                                                                   \
      {                                                                                                                                                                       \
         m##name##Asset[index] = NULL;                                                                                                                                        \
         m##name##File[index] = "";                                                                                                                                           \
         setMaskBits(mask);                                                                                                                                                   \
         return;                                                                                                                                                              \
      }                                                                                                                                                                       \
      if (!AssetDatabase.isDeclaredAsset(_in))                                                                                                                                \
      {                                                                                                                                                                       \
         StringTableEntry shapeAssetId = StringTable->EmptyString();                                                                                                          \
         AssetQuery query;                                                                                                                                                    \
         S32 foundAssetcount = AssetDatabase.findAssetLooseFile(&query, _in);                                                                                                 \
         if (foundAssetcount != 0)                                                                                                                                            \
         {                                                                                                                                                                    \
            shapeAssetId = query.mAssetList[0];                                                                                                                               \
         }                                                                                                                                                                    \
         else if (Torque::FS::IsFile(_in) || (_in[0] == '$' || _in[0] == '#'))                                                                                                \
         {                                                                                                                                                                    \
            shapeAssetId = ShapeAsset::getAssetIdByFilename(_in);                                                                                                             \
            if (shapeAssetId == ShapeAsset::smNoShapeAssetFallback)                                                                                                           \
            {                                                                                                                                                                 \
               ShapeAsset* privateShape = new ShapeAsset();                                                                                                                   \
               privateShape->setShapeFile(_in);                                                                                                                               \
               shapeAssetId = AssetDatabase.addPrivateAsset(privateShape);                                                                                                    \
            }                                                                                                                                                                 \
         }                                                                                                                                                                    \
         else                                                                                                                                                                 \
         {                                                                                                                                                                    \
            Con::warnf("%s::%s: Could not find asset for: %s using fallback", #className, #name, _in);                                                                        \
            shapeAssetId = ShapeAsset::smNoShapeAssetFallback;                                                                                                                \
         }                                                                                                                                                                    \
         m##name##Asset[index] = shapeAssetId;                                                                                                                                \
         m##name##File[index] = _in;                                                                                                                                          \
      }                                                                                                                                                                       \
      else                                                                                                                                                                    \
      {                                                                                                                                                                       \
         m##name##Asset[index] = _in;                                                                                                                                         \
         m##name##File[index] = get##name##File(index);                                                                                                                       \
      }                                                                                                                                                                       \
      setMaskBits(mask);                                                                                                                                                      \
   };                                                                                                                                                                         \
                                                                                                                                                                              \
   inline StringTableEntry _get##name##AssetId(const U32& index) const { return m##name##Asset[index].getAssetId(); }                                                         \
   TSShape* get##name(const U32& index) { if (m##name##Asset[index].notNull()) return m##name##Asset[index]->getShape(); else return NULL; }                                   \
   AssetPtr<ShapeAsset> get##name##Asset(const U32& index) { return m##name##Asset[index]; }                                                                                  \
   static bool _set##name##Data(void* obj, const char* index, const char* data) { static_cast<className*>(obj)->_set##name(_getStringTable()->insert(data), dAtoi(index)); return false;}\
   StringTableEntry get##name##File(const U32& idx) { return m##name##Asset[idx].notNull() ? m##name##Asset[idx]->getShapeFile() : ""; }

#define INITPERSISTFIELD_SHAPEASSET_ARRAY_REFACTOR(name, arraySize, consoleClass, docs)                                                                                       \
   addProtectedField(assetText(name, Asset), TypeShapeAssetPtr, Offset(m##name##Asset, consoleClass), _set##name##Data, &defaultProtectedGetFn, arraySize, assetDoc(name, asset docs.));\
   addProtectedField(assetText(name, File), TypeFilename, Offset(m##name##File, consoleClass), _set##name##Data, &defaultProtectedGetFn, arraySize, assetDoc(name, asset docs.));

#pragma endregion

//-----------------------------------------------------------------------------
// REFACTOR END
//-----------------------------------------------------------------------------

#endif
