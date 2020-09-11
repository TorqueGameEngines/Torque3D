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

#ifndef REFLECTIONPROBE_H
#define REFLECTIONPROBE_H

#ifndef _SCENEOBJECT_H_
#include "scene/sceneObject.h"
#endif
#ifndef _GFXVERTEXBUFFER_H_
#include "gfx/gfxVertexBuffer.h"
#endif
#ifndef _GFXPRIMITIVEBUFFER_H_
#include "gfx/gfxPrimitiveBuffer.h"
#endif
#ifndef _TSSHAPEINSTANCE_H_
#include "ts/tsShapeInstance.h"
#endif
#include "lighting/lightInfo.h"

#ifndef _RENDERPASSMANAGER_H_
#include "renderInstance/renderPassManager.h"
#endif

#ifndef RENDER_PROBE_MGR_H
#include "renderInstance/renderProbeMgr.h"
#endif

class BaseMatInstance;

//-----------------------------------------------------------------------------
// This class implements a basic SceneObject that can exist in the world at a
// 3D position and render itself. There are several valid ways to render an
// object in Torque. This class implements the preferred rendering method which
// is to submit a MeshRenderInst along with a Material, vertex buffer,
// primitive buffer, and transform and allow the RenderMeshMgr handle the
// actual setup and rendering for you.
//-----------------------------------------------------------------------------

class ReflectionProbe : public SceneObject
{
   typedef SceneObject Parent;
   friend class RenderProbeMgr;

public:

   enum ReflectionModeType
   {
      NoReflection = 0,
      StaticCubemap = 1,
      BakedCubemap = 2,
      DynamicCubemap = 5,
   };

protected:

   // Networking masks
   // We need to implement a mask specifically to handle
   // updating our transform from the server object to its
   // client-side "ghost". We also need to implement a
   // maks for handling editor updates to our properties
   // (like material).
   enum MaskBits
   {
      TransformMask = Parent::NextFreeMask << 0,
      StaticDataMask = Parent::NextFreeMask << 1,
      EnabledMask = Parent::NextFreeMask << 2,
      NextFreeMask = Parent::NextFreeMask << 3
   };

   bool mBake;
   bool mEnabled;
   bool mDirty;
   bool mCubemapDirty;

   Resource<TSShape> mEditorShape;
   TSShapeInstance* mEditorShapeInst;

   //--------------------------------------------------------------------------
   // Rendering variables
   //--------------------------------------------------------------------------
   ProbeRenderInst::ProbeShapeType mProbeShapeType;

   ProbeRenderInst* mProbeInfo;

   //Reflection Contribution stuff
   ReflectionModeType mReflectionModeType;

   F32 mRadius;
   Point3F mProbeRefOffset;
   Point3F mProbeRefScale;
   bool mEditPosOffset;

   String mCubemapName;
   CubemapData *mStaticCubemap;
   GFXCubemapHandle  mDynamicCubemap;

   String cubeDescName;
   U32 cubeDescId;
   CubeReflector mCubeReflector;
   ReflectorDesc *reflectorDesc;

   //Utilized in dynamic reflections
   //CubeReflector mCubeReflector;

   ///Prevents us from saving out the cubemaps(for now) but allows us the full HDR range on the in-memory cubemap captures
   bool mUseHDRCaptures;

   //irridiance resources
   CubemapData *mIrridianceMap;

   //prefilter resources
   CubemapData *mPrefilterMap;
   U32 mPrefilterMipLevels;
   U32 mPrefilterSize;

   String mProbeUniqueID;

   // Define our vertex format here so we don't have to
   // change it in multiple spots later
   typedef GFXVertexPNTTB VertexType;

   // The GFX vertex and primitive buffers
   GFXVertexBufferHandle< VertexType > mVertexBuffer;
   GFXPrimitiveBufferHandle            mPrimitiveBuffer;

   U32 mSphereVertCount;
   U32 mSpherePrimitiveCount;

   //Debug rendering
   static bool smRenderPreviewProbes;

   U32 mDynamicLastBakeMS;
   U32 mRefreshRateMS;

   F32 mMaxDrawDistance;

   bool mResourcesCreated;
   U32 mCaptureMask;

public:
   ReflectionProbe();
   virtual ~ReflectionProbe();

   // Declare this object as a ConsoleObject so that we can
   // instantiate it into the world and network it
   DECLARE_CONOBJECT(ReflectionProbe);

   //--------------------------------------------------------------------------
   // Object Editing
   // Since there is always a server and a client object in Torque and we
   // actually edit the server object we need to implement some basic
   // networking functions
   //--------------------------------------------------------------------------
   // Set up any fields that we want to be editable (like position)
   static void initPersistFields();

   // Allows the object to update its editable settings
   // from the server object to the client
   virtual void inspectPostApply();

   static bool _setEnabled(void *object, const char *index, const char *data);
   static bool _doBake(void *object, const char *index, const char *data);
   static bool _toggleEditPosOffset(void *object, const char *index, const char *data);
   static bool _setRadius(void *object, const char *index, const char *data);
   static bool _setReflectionMode(void *object, const char *index, const char *data);

   // Handle when we are added to the scene and removed from the scene
   bool onAdd();
   void onRemove();

   virtual void handleDeleteAction();

   // Override this so that we can dirty the network flag when it is called
   virtual void setTransform(const MatrixF &mat);
   virtual const MatrixF& getTransform() const;
   virtual void setScale(const VectorF &scale);
   virtual const VectorF& getScale() const;

   virtual bool writeField(StringTableEntry fieldname, const char *value);

   // This function handles sending the relevant data from the server
   // object to the client object
   U32 packUpdate(NetConnection *conn, U32 mask, BitStream *stream);
   // This function handles receiving relevant data from the server
   // object and applying it to the client object
   void unpackUpdate(NetConnection *conn, BitStream *stream);

   //--------------------------------------------------------------------------
   // Object Rendering
   // Torque utilizes a "batch" rendering system. This means that it builds a
   // list of objects that need to render (via RenderInst's) and then renders
   // them all in one batch. This allows it to optimized on things like
   // minimizing texture, state, and shader switching by grouping objects that
   // use the same Materials.
   //--------------------------------------------------------------------------

   // Create the geometry for rendering
   void createGeometry();

   virtual void updateProbeParams();

   bool createClientResources();

   void processDynamicCubemap();
   void processBakedCubemap();
   void processStaticCubemap();

   // This is the function that allows this object to submit itself for rendering
   void prepRenderImage(SceneRenderState *state);

   void _onRenderViz(ObjectRenderInst *ri,
      SceneRenderState *state,
      BaseMatInstance *overrideMat);

   void setPreviewMatParameters(SceneRenderState* renderState, BaseMatInstance* mat);

   //Baking
   String getPrefilterMapPath();
   String getIrradianceMapPath();
   void bake();
};

typedef ProbeRenderInst::ProbeShapeType ReflectProbeType;
DefineEnumType(ReflectProbeType);

typedef ReflectionProbe::ReflectionModeType ReflectionModeEnum;
DefineEnumType(ReflectionModeEnum);

#endif // _ReflectionProbe_H_
