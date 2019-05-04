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

#ifndef _ASSIMP_APPMESH_H_
#define _ASSIMP_APPMESH_H_

#ifndef _APPMESH_H_
#include "ts/loader/appMesh.h"
#endif
#ifndef _TSSHAPELOADER_H_
#include "ts/loader/tsShapeLoader.h"
#endif
#ifndef _ASSIMP_APPNODE_H_
#include "ts/assimp/assimpAppNode.h"
#endif

class AssimpAppMesh : public AppMesh
{
   typedef AppMesh Parent;

protected:
   class AssimpAppNode* appNode;                     ///< Pointer to the node that owns this mesh
   const struct aiMesh* mMeshData;
   bool mIsSkinMesh;

   static bool fixedSizeEnabled;                     ///< Set to true to fix the detail size to a particular value for all geometry
   static S32 fixedSize;                             ///< The fixed detail size value for all geometry

public:

   AssimpAppMesh(const struct aiMesh* mesh, AssimpAppNode* node);
   ~AssimpAppMesh()
   {
      //delete geomExt;
   }

   void lookupSkinData();

   static void fixDetailSize(bool fixed, S32 size=2)
   {
      fixedSizeEnabled = fixed;
      fixedSize = size;
   }

   /// Get the name of this mesh
   ///
   /// @return A string containing the name of this mesh
   const char *getName(bool allowFixed=true);

   //-----------------------------------------------------------------------

   /// Get a floating point property value
   ///
   /// @param propName     Name of the property to get
   /// @param defaultVal   Reference to variable to hold return value
   ///
   /// @return True if a value was set, false if not
   bool getFloat(const char *propName, F32 &defaultVal)
   {
      return appNode->getFloat(propName,defaultVal);
   }

   /// Get an integer property value
   ///
   /// @param propName     Name of the property to get
   /// @param defaultVal   Reference to variable to hold return value
   ///
   /// @return True if a value was set, false if not
   bool getInt(const char *propName, S32 &defaultVal)
   {
      return appNode->getInt(propName,defaultVal);
   }

   /// Get a boolean property value
   ///
   /// @param propName     Name of the property to get
   /// @param defaultVal   Reference to variable to hold return value
   ///
   /// @return True if a value was set, false if not
   bool getBool(const char *propName, bool &defaultVal)
   {
      return appNode->getBool(propName,defaultVal);
   }

   /// Return true if this mesh is a skin
   bool isSkin()
   {
      return mIsSkinMesh;
   }

   /// Generate the vertex, normal and triangle data for the mesh.
   ///
   /// @param time           Time at which to generate the mesh data
   /// @param objectOffset   Transform to apply to the generated data (bounds transform)
   void lockMesh(F32 time, const MatrixF& objOffset);

   /// Get the transform of this mesh at a certain time
   ///
   /// @param time   Time at which to get the transform
   ///
   /// @return The mesh transform at the specified time
   MatrixF getMeshTransform(F32 time);
   F32 getVisValue(F32 t);
};

#endif // _COLLADA_APPMESH_H_
