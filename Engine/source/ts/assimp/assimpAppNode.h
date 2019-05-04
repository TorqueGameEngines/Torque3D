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

#ifndef _ASSIMP_APPNODE_H_
#define _ASSIMP_APPNODE_H_

#ifndef _TDICTIONARY_H_
#include "core/tDictionary.h"
#endif
#ifndef _APPNODE_H_
#include "ts/loader/appNode.h"
#endif
#ifndef _COLLADA_EXTENSIONS_H_
#include "ts/collada/colladaExtensions.h"
#endif

#ifndef AI_TYPES_H_INC
#include <assimp/types.h>
#endif
#include <assimp/scene.h>

class AssimpAppNode : public AppNode
{
   typedef AppNode Parent;
   friend class AssimpAppMesh;

   MatrixF getTransform(F32 time);
   void getAnimatedTransform(MatrixF& mat, F32 t, aiAnimation* animSeq);
   void buildMeshList();
   void buildChildList();

protected:

   const struct aiScene*   mScene;
   const struct aiNode*    mNode;                  ///< Pointer to the assimp scene node
   AssimpAppNode*          appParent;              ///< Parent node
   MatrixF                 mNodeTransform;         ///< Scene node transform converted to TorqueSpace (filled for ALL nodes)

   bool                    mInvertMeshes;          ///< True if this node's coordinate space is inverted (left handed)
   F32                     mLastTransformTime;     ///< Time of the last transform lookup (getTransform)
   MatrixF                 mLastTransform;         ///< Last transform lookup (getTransform) (Only Non-Dummy Nodes)
   bool                    mDefaultTransformValid; ///< Flag indicating whether the defaultNodeTransform is valid
   MatrixF                 mDefaultNodeTransform;  ///< Transform at DefaultTime (Only Non-Dummy Nodes)

public:

   AssimpAppNode(const struct aiScene* scene, const struct aiNode* node, AssimpAppNode* parent = 0);
   virtual ~AssimpAppNode()
   {
      //
   }

   static aiAnimation* sActiveSequence;
   static F32 sTimeMultiplier;

   //-----------------------------------------------------------------------
   const char *getName() { return mName; }
   const char *getParentName() { return mParentName; }

   bool isEqual(AppNode* node)
   {
      const AssimpAppNode* appNode = dynamic_cast<const AssimpAppNode*>(node);
      return (appNode && (appNode->mNode == mNode));
   }

   // Property look-ups: only float properties are stored, the rest are
   // converted from floats as needed
   bool getFloat(const char* propName, F32& defaultVal)
   {
      //Map<StringTableEntry,F32>::Iterator itr = mProps.find(propName);
      //if (itr != mProps.end())
       //  defaultVal = itr->value;
      return false;
   }
   bool getInt(const char* propName, S32& defaultVal)
   {
      F32 value = defaultVal;
      bool ret = getFloat(propName, value);
      defaultVal = (S32)value;
      return ret;
   }
   bool getBool(const char* propName, bool& defaultVal)
   {
      F32 value = defaultVal;
      bool ret = getFloat(propName, value);
      defaultVal = (value != 0);
      return ret;
   }

   MatrixF getNodeTransform(F32 time);
   bool animatesTransform(const AppSequence* appSeq);
   bool isParentRoot() { return (appParent == NULL); }

   static void assimpToTorqueMat(const aiMatrix4x4& inAssimpMat, MatrixF& outMat);
   static void convertMat(MatrixF& outMat);
   static aiNode* findChildNodeByName(const char* nodeName, aiNode* rootNode);
};

#endif // _ASSIMP_APPNODE_H_
