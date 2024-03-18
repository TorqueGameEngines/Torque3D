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
#ifndef SCRIPT_ASSET_H
#define SCRIPT_ASSET_H
#pragma once

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

#ifndef _ASSET_PTR_H_
#include "assets/assetPtr.h"
#endif

//-----------------------------------------------------------------------------
class ScriptAsset : public AssetBase
{
   typedef AssetBase Parent;

   StringTableEntry        mScriptFile;
   StringTableEntry        mScriptPath;
   bool                    mIsServerSide;

   Vector<AssetPtr<ScriptAsset>> mScriptAssetDependencies;

public:
   ScriptAsset();
   virtual ~ScriptAsset();

   /// Engine.
   static void initPersistFields();
   void copyTo(SimObject* object) override;

   /// Declare Console Object.
   DECLARE_CONOBJECT(ScriptAsset);

   void                    setScriptFile(const char* pScriptFile);
   inline StringTableEntry getScriptFile(void) const { return mScriptFile; };

   inline StringTableEntry getScriptPath(void) const { return mScriptPath; };

   bool execScript();

   DECLARE_CALLBACK(void, onInitializeAsset, ());
   DECLARE_CALLBACK(void, onRefreshAsset, ());
   DECLARE_CALLBACK(void, onUnloadAsset, ());

protected:
   void            initializeAsset(void) override;
   void            onAssetRefresh(void) override;
   void            unloadAsset(void) override;

   static bool setScriptFile(void *obj, const char *index, const char *data) { static_cast<ScriptAsset*>(obj)->setScriptFile(data); return false; }
   static const char* getScriptFile(void* obj, const char* data) { return static_cast<ScriptAsset*>(obj)->getScriptFile(); }
};

DefineConsoleType(TypeScriptAssetPtr, ScriptAsset)

#endif // _ASSET_BASE_H_

