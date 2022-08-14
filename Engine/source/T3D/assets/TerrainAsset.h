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
#ifndef TERRAINASSET_H
#define TERRAINASSET_H

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

#ifndef _GUI_INSPECTOR_TYPES_H_
#include "gui/editor/guiInspectorTypes.h"
#endif

//#include "terrain/terrData.h"
#include "assets/assetPtr.h"
#include "terrain/terrFile.h"

class TerrainMaterialAsset;

//-----------------------------------------------------------------------------
class TerrainAsset : public AssetBase
{
   typedef AssetBase Parent;

   StringTableEntry        mTerrainFileName;
   StringTableEntry        mTerrainFilePath;
   Resource<TerrainFile>   mTerrainFile;

   //Material assets we're dependent on and use
   Vector<StringTableEntry> mTerrMaterialAssetIds;
   Vector<AssetPtr<TerrainMaterialAsset>> mTerrMaterialAssets;

public:
   TerrainAsset();
   virtual ~TerrainAsset();

   /// Engine.
   static void initPersistFields();
   virtual void copyTo(SimObject* object);

   virtual void setDataField(StringTableEntry slotName, const char* array, const char* value);

   void                    setTerrainFileName(const char* pTerrainFile);
   inline StringTableEntry getTerrainFileName(void) const { return mTerrainFileName; };
   inline StringTableEntry getTerrainFilePath(void) const { return mTerrainFilePath; };

   inline Resource<TerrainFile> getTerrainResource(void) const { return mTerrainFile; };

   bool loadTerrain();

   static bool getAssetByFilename(StringTableEntry fileName, AssetPtr<TerrainAsset>* shapeAsset);
   static StringTableEntry getAssetIdByFilename(StringTableEntry fileName);
   static bool getAssetById(StringTableEntry assetId, AssetPtr<TerrainAsset>* shapeAsset);

   /// Declare Console Object.
   DECLARE_CONOBJECT(TerrainAsset);

protected:
   virtual void initializeAsset();
   virtual void onAssetRefresh(void);

   static bool setTerrainFileName(void *obj, const char *index, const char *data) { static_cast<TerrainAsset*>(obj)->setTerrainFileName(data); return false; }
   static const char* getTerrainFileName(void* obj, const char* data) { return static_cast<TerrainAsset*>(obj)->getTerrainFileName(); }
};

DefineConsoleType(TypeTerrainAssetPtr, TerrainAsset)
DefineConsoleType(TypeTerrainAssetId, String)
#ifdef TORQUE_TOOLS
//-----------------------------------------------------------------------------
// TypeAssetId GuiInspectorField Class
//-----------------------------------------------------------------------------
class GuiInspectorTypeTerrainAssetPtr : public GuiInspectorTypeFileName
{
   typedef GuiInspectorTypeFileName Parent;
public:

   GuiBitmapButtonCtrl* mShapeEdButton;

   DECLARE_CONOBJECT(GuiInspectorTypeTerrainAssetPtr);
   static void consoleInit();

   virtual GuiControl* constructEditControl();
   virtual bool updateRects();
};

class GuiInspectorTypeTerrainAssetId : public GuiInspectorTypeTerrainAssetPtr
{
   typedef GuiInspectorTypeTerrainAssetPtr Parent;
public:

   DECLARE_CONOBJECT(GuiInspectorTypeTerrainAssetId);
   static void consoleInit();
};
#endif
#endif // _ASSET_BASE_H_

