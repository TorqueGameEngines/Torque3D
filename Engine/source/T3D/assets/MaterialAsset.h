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

#endif // _ASSET_BASE_H_

