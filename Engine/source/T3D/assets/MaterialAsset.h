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

#include "gui/editor/guiInspectorTypes.h"

#include "materials/matTextureTarget.h"
#include "materials/materialDefinition.h"
#include "materials/customMaterialDefinition.h"

//-----------------------------------------------------------------------------
class MaterialAsset : public AssetBase
{
   typedef AssetBase Parent;

   String                  mShaderGraphFile;
   StringTableEntry        mScriptFile;
   StringTableEntry        mScriptPath;
   StringTableEntry        mMatDefinitionName;

public:
   MaterialAsset();
   virtual ~MaterialAsset();

   /// Engine.
   static void initPersistFields();
   virtual void copyTo(SimObject* object);

   void compileShader();

   StringTableEntry getMaterialDefinitionName() { return mMatDefinitionName; }

   void                    setScriptFile(const char* pScriptFile);
   inline StringTableEntry getScriptFile(void) const { return mScriptFile; };

   inline StringTableEntry getScriptPath(void) const { return mScriptPath; };

   static StringTableEntry getAssetIdByMaterialName(StringTableEntry fileName);
   static bool getAssetById(StringTableEntry assetId, AssetPtr<MaterialAsset>* materialAsset);

   /// Declare Console Object.
   DECLARE_CONOBJECT(MaterialAsset);

protected:
   virtual void initializeAsset();
   virtual void onAssetRefresh(void);

   static bool setScriptFile(void *obj, const char *index, const char *data) { static_cast<MaterialAsset*>(obj)->setScriptFile(data); return false; }
   static const char* getScriptFile(void* obj, const char* data) { return static_cast<MaterialAsset*>(obj)->getScriptFile(); }
};

DefineConsoleType(TypeMaterialAssetPtr, MaterialAsset)
DefineConsoleType(TypeMaterialAssetId, String)

//-----------------------------------------------------------------------------
// TypeAssetId GuiInspectorField Class
//-----------------------------------------------------------------------------
class GuiInspectorTypeMaterialAssetPtr : public GuiInspectorTypeFileName
{
   typedef GuiInspectorTypeFileName Parent;
public:

   GuiBitmapButtonCtrl* mEditButton;

   DECLARE_CONOBJECT(GuiInspectorTypeMaterialAssetPtr);
   static void consoleInit();

   virtual GuiControl* constructEditControl();
   virtual bool updateRects();
};

class GuiInspectorTypeMaterialAssetId : public GuiInspectorTypeMaterialAssetPtr
{
   typedef GuiInspectorTypeMaterialAssetPtr Parent;
public:

   DECLARE_CONOBJECT(GuiInspectorTypeMaterialAssetId);
   static void consoleInit();
};

#define assetText(x,suff) std::string(std::string(#x) + std::string(#suff)).c_str()

#define initMaterialAsset(name) m##name##Name = ""; m##name##AssetId = StringTable->EmptyString(); m##name##Asset = NULL;
#define bindMaterialAsset(name) if (m##name##AssetId != StringTable->EmptyString()) m##name##Asset = m##name##AssetId;

#define scriptBindMaterialAsset(name, consoleClass, docs)\
   addProtectedField(assetText(name, File), TypeMaterialName, Offset(m##name##Name, consoleClass), consoleClass::_set##name##Name,  & defaultProtectedGetFn, assetText(name, docs), AbstractClassRep::FIELD_HideInInspectors); \
   addProtectedField(assetText(name, Asset), TypeMaterialAssetId, Offset(m##name##AssetId, consoleClass), consoleClass::_set##name##Asset, & defaultProtectedGetFn, assetText(name, asset reference.));

#define DECLARE_MATERIALASSET(className,name)      protected: \
                                      String m##name##Name;\
                                      StringTableEntry m##name##AssetId;\
                                      AssetPtr<MaterialAsset>  m##name##Asset;\
                                      public: \
                                      const String& get##name() const { return m##name##Name; }\
                                      void set##name(FileName _in) { m##name##Name = _in; }\
                                      const AssetPtr<MaterialAsset> & get##name##Asset() const { return m##name##Asset; }\
                                      void set##name##Asset(AssetPtr<MaterialAsset>_in) { m##name##Asset = _in; }\
static bool _set##name##Name(void* obj, const char* index, const char* data)\
{\
   className* shape = static_cast<className*>(obj);\
   \
   StringTableEntry assetId = MaterialAsset::getAssetIdByMaterialName(StringTable->insert(data));\
   if (assetId != StringTable->EmptyString())\
   {\
      if (shape->_set##name##Asset(obj, index, assetId))\
      {\
         if (assetId == StringTable->insert("Core_Rendering:noMaterial"))\
         {\
            shape->m##name##Name = data;\
            shape->m##name##AssetId = StringTable->EmptyString();\
            \
            return true;\
         }\
         else\
         {\
            shape->m##name##AssetId = assetId;\
            shape->m##name##Name = StringTable->EmptyString();\
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
   if (MaterialAsset::getAssetById(shape->m##name##AssetId, &shape->m##name##Asset))\
   {\
      if (shape->m##name##Asset.getAssetId() != StringTable->insert("Core_Rendering:noMaterial"))\
         shape->m##name##Name = StringTable->EmptyString();\
      \
      return true;\
   }\
   return false;\
}\
\
static bool set##name##Asset(const char* assetId)\
{\
   m##name##AssetId = StringTable->insert(assetId);\
   if (m##name##AssetId != StringTable->EmptyString())\
      m##name##Asset = m##name##AssetId;\
}

/// <summary>
/// DECLARE_MATERIALASSET is a utility macro for MaterialAssets. It takes in the name of the class using it, the name of the field for the material, and a networking bitmask
/// The first 2 are for setting up/filling out the fields and class member defines
/// The bitmask is for when the material is changed, it can automatically kick a network update on the owner object to pass the changed asset to clients
/// </summary>
#define DECLARE_NET_MATERIALASSET(className,name,bitmask)      protected: \
                                      String m##name##Name;\
                                      StringTableEntry m##name##AssetId;\
                                      AssetPtr<MaterialAsset>  m##name##Asset;\
                                      public: \
                                      const String& get##name() const { return m##name##Name; }\
                                      void set##name(FileName _in) { m##name##Name = _in; }\
                                      const AssetPtr<MaterialAsset> & get##name##Asset() const { return m##name##Asset; }\
                                      void set##name##Asset(AssetPtr<MaterialAsset>_in) { m##name##Asset = _in; }\
static bool _set##name##Name(void* obj, const char* index, const char* data)\
{\
   className* shape = static_cast<className*>(obj);\
   \
   StringTableEntry assetId = MaterialAsset::getAssetIdByMaterialName(StringTable->insert(data));\
   if (assetId != StringTable->EmptyString())\
   {\
      if (shape->_set##name##Asset(obj, index, assetId))\
      {\
         if (assetId == StringTable->insert("Core_Rendering:noMaterial"))\
         {\
            shape->m##name##Name = data;\
            shape->m##name##AssetId = StringTable->EmptyString();\
            \
            return true;\
         }\
         else\
         {\
            shape->m##name##AssetId = assetId;\
            shape->m##name##Name = StringTable->EmptyString();\
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
   if (MaterialAsset::getAssetById(shape->m##name##AssetId, &shape->m##name##Asset))\
   {\
      if (shape->m##name##Asset.getAssetId() != StringTable->insert("Core_Rendering:noMaterial"))\
         shape->m##name##Name = StringTable->EmptyString();\
      \
      shape->setMaskBits(bitmask);\
      shape->inspectPostApply();\
      return true;\
   }\
   shape->inspectPostApply();\
   return false;\
}\
\
bool set##name##AssetId(const char* _assetId)\
{\
   m##name##AssetId = StringTable->insert(_assetId);\
   if (m##name##AssetId != StringTable->EmptyString())\
   {\
      m##name##Asset = m##name##AssetId;\
      \
      setMaskBits(bitmask);\
      inspectPostApply();\
      return true;\
   }\
   \
   return false;\
}


#define packMaterialAsset(netconn, name)\
   if (stream->writeFlag(m##name##Asset.notNull()))\
   {\
      NetStringHandle assetIdStr = m##name##Asset.getAssetId();\
      netconn->packNetStringHandleU(stream, assetIdStr);\
   }\
   else\
      stream->writeString(m##name##Name);

#define unpackMaterialAsset(netconn, name)\
   if (stream->readFlag())\
   {\
      m##name##AssetId = StringTable->insert(netconn->unpackNetStringHandleU(stream).getString());\
      MaterialAsset::getAssetById(m##name##AssetId, &m##name##Asset);\
   }\
   else\
      m##name##Name = stream->readSTString();\

#endif // _ASSET_BASE_H_

