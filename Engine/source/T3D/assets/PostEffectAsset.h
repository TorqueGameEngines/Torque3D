#pragma once
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
#ifndef POSTEFFECT_ASSET_H
#define POSTEFFECT_ASSET_H

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

#include "postFx/postEffect.h"

//-----------------------------------------------------------------------------
class PostEffectAsset : public AssetBase
{
   typedef AssetBase Parent;

   StringTableEntry        mScriptFile;
   StringTableEntry        mHLSLShaderFile;
   StringTableEntry        mGLSLShaderFile;

   StringTableEntry        mScriptPath;
   StringTableEntry        mHLSLShaderPath;
   StringTableEntry        mGLSLShaderPath;
   
public:
   PostEffectAsset();
   virtual ~PostEffectAsset();

   /// Engine.
   static void initPersistFields();
   void copyTo(SimObject* object) override;

   void                    setScriptFile(const char* pScriptFile);
   inline StringTableEntry getScriptFile(void) const { return mScriptFile; };

   void                    setHLSLShaderFile(const char* pShaderFile);
   inline StringTableEntry getHLSLShaderFile(void) const { return mHLSLShaderFile; };
   void                    setGLSLShaderFile(const char* pShaderFile);
   inline StringTableEntry getGLSLShaderFile(void) const { return mGLSLShaderFile; };

   inline StringTableEntry getScriptPath(void) const { return mScriptPath; };
   inline StringTableEntry getHLSLShaderPath(void) const { return mHLSLShaderPath; };
   inline StringTableEntry getGLSLShaderPath(void) const { return mGLSLShaderPath; };

   /// Declare Console Object.
   DECLARE_CONOBJECT(PostEffectAsset);

protected:
   void initializeAsset() override;
   void onAssetRefresh(void) override;

   static bool setScriptFile(void *obj, const char *index, const char *data) { static_cast<PostEffectAsset*>(obj)->setScriptFile(data); return false; }
   static const char* getScriptFile(void* obj, const char* data) { return static_cast<PostEffectAsset*>(obj)->getScriptFile(); }

   static bool setHLSLShaderFile(void* obj, const char* index, const char* data) { static_cast<PostEffectAsset*>(obj)->setHLSLShaderFile(data); return false; }
   static const char* getHLSLShaderFile(void* obj, const char* data) { return static_cast<PostEffectAsset*>(obj)->getHLSLShaderFile(); }
   static bool setGLSLShaderFile(void* obj, const char* index, const char* data) { static_cast<PostEffectAsset*>(obj)->setGLSLShaderFile(data); return false; }
   static const char* getGLSLShaderFile(void* obj, const char* data) { return static_cast<PostEffectAsset*>(obj)->getGLSLShaderFile(); }
};

DefineConsoleType(TypePostEffectAssetPtr, PostEffectAsset)

#endif // _ASSET_BASE_H_

