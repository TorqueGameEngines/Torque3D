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
   static AssetPtr<ShapeAsset> smNoShapeAssetFallbackAssetPtr;

   static const String mErrCodeStrings[U32(ShapeAssetErrCode::Extended) - U32(Parent::Extended) + 1];
   static U32 getAssetErrCode(const ConcreteAssetPtr& checkAsset) { if (checkAsset) return checkAsset->mLoadedState; else return 0; }

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

   Resource<TSShape>	 mShape;

   // MaterialAsset dependencies held for the lifetime of the loaded shape, so
   // the materials the TSShape's materialList resolves against can't be purged
   // out from under it. Released in unloadAsset().
   Vector<AssetPtr<MaterialAsset>> mMaterialAssets;
public:

   ShapeAsset();
   virtual ~ShapeAsset();

   /// Set up some global script interface stuff.
   static void consoleInit();

   /// Engine.
   static void initPersistFields();
   void copyTo(SimObject* object) override;

   /// Declare Console Object.
   DECLARE_CONOBJECT(ShapeAsset);

   U32 load() override;
   void unloadAsset() override;
#ifdef TORQUE_TOOLS
   U32 getAssetMemoryUsage() const override;
#endif
   void onAssetReleased() override;
   bool preloadMaterialList();

   TSShape* getShape();
   Resource<TSShape> getShapeResource();

   U32 getShapeFilenameHash() { return _StringTable::hashString(mShapeFile); }

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

   StringTableEntry getMaterial(const S32& index);
   U32 getMaterialCount();

   StringTableEntry getAnimation(const S32& index);
   U32 getAnimationCount();

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
   void onTamlCustomWrite(TamlCustomNodes& customNodes) override;

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

DECLARE_STRUCT(AssetRef<ShapeAsset>)
DefineConsoleType(TypeShapeAssetRef, AssetRef<ShapeAsset>)

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

//-----------------------------------------------------------------------------
class GuiInspectorTypeShapeAssetRef : public GuiInspectorTypeFileName
{
   typedef GuiInspectorTypeFileName Parent;
public:

   GuiTextCtrl* mLabel;
   GuiBitmapButtonCtrl* mPreviewBorderButton;
   GuiBitmapCtrl* mPreviewImage;
   GuiButtonCtrl* mEditButton;

   DECLARE_CONOBJECT(GuiInspectorTypeShapeAssetRef);
   static void consoleInit();

   GuiControl* constructEditControl() override;
   bool updateRects() override;

   void updateValue() override;

   void updatePreviewImage();
   void setPreviewImage(StringTableEntry assetId);
};

#endif

#endif
