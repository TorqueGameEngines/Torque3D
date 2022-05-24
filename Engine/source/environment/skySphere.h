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

#ifndef _SKYSPHERE_H_
#define _SKYSPHERE_H_

#ifndef _SCENEOBJECT_H_
#include "scene/sceneObject.h"
#endif

#ifndef _GFXDEVICE_H_
#include "gfx/gfxDevice.h"
#endif

#ifndef _CUBEMAPDATA_H_
#include "gfx/sim/cubemapData.h"
#endif

#ifndef _MATERIALLIST_H_
#include "materials/materialList.h"
#endif

#ifndef _GFXVERTEXBUFFER_H_
#include "gfx/gfxVertexBuffer.h"
#endif

#ifndef _GFXPRIMITIVEBUFFER_H_
#include "gfx/gfxPrimitiveBuffer.h"
#endif

#include "T3D/assets/MaterialAsset.h"

struct SkyMatParams
{
   void init(BaseMatInstance* matInst) {};
};

class MatrixSet;

class SkySphere : public SceneObject
{
   typedef SceneObject Parent;

public:

   SkySphere();
   virtual ~SkySphere();

   DECLARE_CONOBJECT(SkySphere);

   // SimObject
   void onStaticModified(const char* slotName, const char* newValue);

   // ConsoleObject
   virtual bool onAdd();
   virtual void onRemove();
   static void initPersistFields();
   virtual void inspectPostApply();

   // NetObject
   virtual U32 packUpdate(NetConnection* conn, U32 mask, BitStream* stream);
   virtual void unpackUpdate(NetConnection* conn, BitStream* stream);

   // SceneObject
   void prepRenderImage(SceneRenderState* state);

   /// Our render delegate.
   void _renderObject(ObjectRenderInst* ri, SceneRenderState* state, BaseMatInstance* mi);

   void clearVectors();

   void addVertex(Point3F vert);

   void addNormal(Point3F nor);

   void addTexcoord(F32 s, F32 t);

   void addColor(ColorI col);

   void BuildFinalVert();

   void BuildFinalFogVert();

   /// Prepares rendering structures and geometry.
   void _initRender();

   struct SphereVertex
   {
      Point3F pos;
      Point3F nor;
      F32 s, t;
   };

   Vector<SphereVertex> tmpVertices;
   Vector<F32> vertsVec;
   Vector<F32> texCoordVec;
   Vector<F32> normsVec;

   struct FinalVertexData
   {
      Point3F pos;
      Point3F nor;
      F32 s;
      F32 t;
   };

   Vector<FinalVertexData> finalVertData;

   struct FogVertex
   {
      // might need normals for smoothing.
      Point3F pos;
      ColorI col;
   };

   Vector<FogVertex> finalFogVertex;
   Vector<FogVertex> tempFogVertex;
   Vector<ColorI> colVec;
   Vector<F32> fogVerts;

protected:

   // Material
   DECLARE_MATERIALASSET(SkySphere, Material);
   DECLARE_ASSET_NET_SETGET(SkySphere, Material, -1);

   BaseMatInstance* mMatInstance;
   SkyMatParams mMatParamHandle;

   GFXVertexBufferHandle<GFXVertexPNT> mVB;

   GFXVertexBufferHandle<GFXVertexPC> mFogBandVB;
   Material* mFogBandMat;
   BaseMatInstance* mFogBandMatInst;

   LinearColorF mLastFogColor;

   bool mIsVBDirty;
   U32 mPrimCount;

   MatrixSet* mMatrixSet;

   F32 mFogBandHeight;
   U32 mFogPrimCount;

   void _updateMaterial();
   void _initMaterial();

   BaseMatInstance* _getMaterialInstance();

};

#endif
