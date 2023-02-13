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

#ifndef MATERIALASSET_H
#define MATERIALASSET_H

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

#ifndef _GFXDEVICE_H_
#include "gfx/gfxDevice.h"
#endif

#ifndef _NETCONNECTION_H_
#include "sim/netConnection.h"
#endif

#ifndef _GUI_INSPECTOR_TYPES_H_
#include "gui/editor/guiInspectorTypes.h"
#endif

#include "materials/matTextureTarget.h"
#include "materials/materialDefinition.h"
#include "materials/customMaterialDefinition.h"
#include "materials/materialManager.h"
#include "assetMacroHelpers.h"
#include <gui/controls/guiBitmapCtrl.h>

//-----------------------------------------------------------------------------
class MaterialAsset : public AssetBase
{
   typedef AssetBase Parent;

   String                  mShaderGraphFile;
   StringTableEntry        mScriptFile;
   StringTableEntry        mScriptPath;
   StringTableEntry        mMatDefinitionName;

   SimObjectPtr<Material>  mMaterialDefinition;

public:
   static StringTableEntry smNoMaterialAssetFallback;

   enum MaterialAssetErrCode
   {
      ScriptLoaded = AssetErrCode::Extended,
      DefinitionAlreadyExists,
      EmbeddedDefinition,
      Extended
   };

public:
   MaterialAsset();
   virtual ~MaterialAsset();

   /// Set up some global script interface stuff.
   static void consoleInit();

   /// Engine.
   static void initPersistFields();
   virtual void copyTo(SimObject* object);

   void loadMaterial();

   StringTableEntry getMaterialDefinitionName() { return mMatDefinitionName; }
   SimObjectPtr<Material> getMaterialDefinition() { return mMaterialDefinition; }

   void                    setScriptFile(const char* pScriptFile);
   inline StringTableEntry getScriptFile(void) const { return mScriptFile; };

   inline StringTableEntry getScriptPath(void) const { return mScriptPath; };

   /// <summary>
   /// Looks for any assets that uses the provided Material Definition name.
   /// If none are found, attempts to auto-import the material definition if the
   /// material definition exists.
   /// </summary>
   /// <param name="matName">Material Definition name to look for</param>
   /// <returns>AssetId of matching asset.</returns>
   static StringTableEntry getAssetIdByMaterialName(StringTableEntry matName);
   static U32 getAssetById(StringTableEntry assetId, AssetPtr<MaterialAsset>* materialAsset);
   static SimObjectPtr<Material> findMaterialDefinitionByAssetId(StringTableEntry assetId);
   static U32 getAssetByMaterialName(StringTableEntry matName, AssetPtr<MaterialAsset>* matAsset);

   /// Declare Console Object.
   DECLARE_CONOBJECT(MaterialAsset);

protected:
   virtual void initializeAsset();
   virtual void onAssetRefresh(void);

   static bool setScriptFile(void *obj, const char *index, const char *data)
   {
      static_cast<MaterialAsset*>(obj)->setScriptFile(data);
      return false;
   }
   static const char* getScriptFile(void* obj, const char* data) { return static_cast<MaterialAsset*>(obj)->getScriptFile(); }
};

DefineConsoleType(TypeMaterialAssetPtr, MaterialAsset)
DefineConsoleType(TypeMaterialAssetId, String)
#ifdef TORQUE_TOOLS
//-----------------------------------------------------------------------------
// TypeAssetId GuiInspectorField Class
//-----------------------------------------------------------------------------
class GuiInspectorTypeMaterialAssetPtr : public GuiInspectorTypeFileName
{
   typedef GuiInspectorTypeFileName Parent;
public:

   GuiTextCtrl* mLabel;
   GuiBitmapButtonCtrl* mPreviewBorderButton;
   GuiBitmapCtrl* mPreviewImage;
   GuiButtonCtrl* mEditButton;

   DECLARE_CONOBJECT(GuiInspectorTypeMaterialAssetPtr);
   static void consoleInit();

   virtual GuiControl* constructEditControl();
   virtual bool updateRects();

   virtual void updateValue();

   void updatePreviewImage();
   void setPreviewImage(StringTableEntry assetId);
};

class GuiInspectorTypeMaterialAssetId : public GuiInspectorTypeMaterialAssetPtr
{
   typedef GuiInspectorTypeMaterialAssetPtr Parent;
public:

   DECLARE_CONOBJECT(GuiInspectorTypeMaterialAssetId);
   static void consoleInit();
};
#endif
#pragma region Singular Asset Macros

//Singular assets
/// <Summary>
/// Declares an material asset
/// This establishes the assetId, asset and legacy filepath fields, along with supplemental getter and setter functions
/// </Summary>
#define DECLARE_MATERIALASSET(className, name) public: \
   StringTableEntry m##name##Name;\
   StringTableEntry m##name##AssetId;\
   AssetPtr<MaterialAsset>  m##name##Asset;\
   SimObjectPtr<Material> m##name;\
public: \
   const StringTableEntry get##name##File() const { return m##name##Name; }\
   void set##name##Name(const FileName &_in) { m##name##Name = StringTable->insert(_in.c_str());}\
   const AssetPtr<MaterialAsset> & get##name##Asset() const { return m##name##Asset; }\
   void set##name##Asset(const AssetPtr<MaterialAsset> &_in) { m##name##Asset = _in;}\
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
            m##name = NULL;\
            return true;\
         }\
         \
         if (AssetDatabase.isDeclaredAsset(_in))\
         {\
            m##name##AssetId = _in;\
            \
            U32 assetState = MaterialAsset::getAssetById(m##name##AssetId, &m##name##Asset);\
            \
            if (MaterialAsset::Ok == assetState)\
            {\
               m##name##Name = StringTable->EmptyString();\
            }\
         }\
         else\
         {\
            StringTableEntry assetId = MaterialAsset::getAssetIdByMaterialName(_in);\
            if (assetId != StringTable->EmptyString())\
            {\
               m##name##AssetId = assetId;\
               if (MaterialAsset::getAssetById(m##name##AssetId, &m##name##Asset) == MaterialAsset::Ok)\
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
         if (m##name && String(m##name##Asset->getMaterialDefinitionName()).equal(m##name->getName(), String::NoCase))\
            return false;\
         \
         Material* tempMat = nullptr;\
         \
         if (!Sim::findObject(m##name##Asset->getMaterialDefinitionName(), tempMat))\
            Con::errorf("%s::_set%s() - Material %s was not found.", macroText(className), macroText(name), m##name##Asset->getMaterialDefinitionName());\
         m##name = tempMat;\
      }\
      else\
      {\
         m##name = NULL;\
      }\
      \
      if(get##name() == StringTable->EmptyString())\
         return true;\
      \
      if (m##name##Asset.notNull() && m##name##Asset->getStatus() != MaterialAsset::Ok)\
      {\
         Con::errorf("%s::_set%s() - material asset failure\"%s\" due to [%s]", macroText(className), macroText(name), _in, MaterialAsset::getAssetErrstrn(m##name##Asset->getStatus()).c_str());\
         return false; \
      }\
      else if (!m##name)\
      {\
         Con::errorf("%s::_set%s() - Couldn't load material \"%s\"", macroText(className), macroText(name), _in);\
         return false;\
      }\
      return true;\
   }\
   \
   const StringTableEntry get##name() const\
   {\
      if (m##name##Asset && (m##name##Asset->getMaterialDefinitionName() != StringTable->EmptyString()))\
         return m##name##Asset->getMaterialDefinitionName();\
      else if (m##name##AssetId != StringTable->EmptyString())\
         return m##name##AssetId;\
      else if (m##name##Name != StringTable->EmptyString())\
         return m##name##Name;\
      else\
         return StringTable->EmptyString();\
   }\
   SimObjectPtr<Material> get##name##Resource() \
   {\
      return m##name;\
   }\
   bool is##name##Valid() {return (get##name() != StringTable->EmptyString() && m##name##Asset->getStatus() == AssetBase::Ok); }

#ifdef TORQUE_SHOW_LEGACY_FILE_FIELDS

#define INITPERSISTFIELD_MATERIALASSET(name, consoleClass, docs) \
   addProtectedField(#name, TypeMaterialName, Offset(m##name##Name, consoleClass), _set##name##Data, &defaultProtectedGetFn,assetDoc(name, docs)); \
   addProtectedField(assetText(name, Asset), TypeMaterialAssetId, Offset(m##name##AssetId, consoleClass), _set##name##Data, &defaultProtectedGetFn, assetDoc(name, asset docs.));

#else

#define INITPERSISTFIELD_MATERIALASSET(name, consoleClass, docs) \
   addProtectedField(#name, TypeMaterialName, Offset(m##name##Name, consoleClass), _set##name##Data, &defaultProtectedGetFn,assetDoc(name, docs), AbstractClassRep::FIELD_HideInInspectors); \
   addProtectedField(assetText(name, Asset), TypeMaterialAssetId, Offset(m##name##AssetId, consoleClass), _set##name##Data, &defaultProtectedGetFn, assetDoc(name, asset docs.));

#endif // SHOW_LEGACY_FILE_FIELDS

#define LOAD_MATERIALASSET(name)\
if (m##name##AssetId != StringTable->EmptyString())\
{\
   S32 assetState = MaterialAsset::getAssetById(m##name##AssetId, &m##name##Asset);\
   if (assetState == MaterialAsset::Ok )\
   {\
      m##name##Name = StringTable->EmptyString();\
   }\
   else Con::warnf("Warning: %s::LOAD_MATERIALASSET(%s)-%s", mClassName, m##name##AssetId, MaterialAsset::getAssetErrstrn(assetState).c_str());\
}
#pragma endregion

#endif // _ASSET_BASE_H_

