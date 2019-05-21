//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
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

#ifndef _ASSIMP_SHAPELOADER_H_
#define _ASSIMP_SHAPELOADER_H_

#ifndef _TSSHAPELOADER_H_
#include "ts/loader/tsShapeLoader.h"
#endif
#include <assimp/texture.h>

class GuiTreeViewCtrl;
struct aiNode;
struct aiMetadata;
//-----------------------------------------------------------------------------
class AssimpShapeLoader : public TSShapeLoader
{
   friend TSShape* assimpLoadShape(const Torque::Path &path);

protected:
   const struct aiScene* mScene;

   virtual bool ignoreNode(const String& name);
   virtual bool ignoreMesh(const String& name);
   void detectDetails();
   void extractTexture(U32 index, aiTexture* pTex);

private:
   void addNodeToTree(S32 parentItem, aiNode* node, GuiTreeViewCtrl* tree, U32& nodeCount);
   void addMetaDataToTree(const aiMetadata* metaData, GuiTreeViewCtrl* tree);
   bool getMetabool(const char* key, bool& boolVal);
   bool getMetaInt(const char* key, S32& intVal);
   bool getMetaFloat(const char* key, F32& floatVal);
   bool getMetaDouble(const char* key, F64& doubleVal);

public:
   AssimpShapeLoader();
   ~AssimpShapeLoader();

   void releaseImport();
   void enumerateScene();
   void updateMaterialsScript(const Torque::Path &path);
   void processAnimations();

   void computeBounds(Box3F& bounds);

   bool fillGuiTreeView(const char* shapePath, GuiTreeViewCtrl* tree);

   static bool canLoadCachedDTS(const Torque::Path& path);
   static void assimpLogCallback(const char* message, char* user);
};

#endif // _ASSIMP_SHAPELOADER_H_
