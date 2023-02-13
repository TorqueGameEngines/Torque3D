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

   /// <summary>
   /// Used to dictate what sort of cubemap the probes use when using IBL
   /// </summary>
   enum ReflectionModeType
   {
      NoReflection = 0,
      StaticCubemap = 1,
      BakedCubemap = 2,
      DynamicCubemap = 5,
   };

   /// <summary>
   /// This contains all the important data the Probe uses for rendering.
   /// </summary>
   struct ProbeInfo
   {
      bool mIsEnabled;

      MatrixF mTransform;

      ReflectionProbe* mObject;

      F32 mRadius;

      bool mDirty;

      Box3F mBounds;
      Point3F mExtents;
      Point3F mPosition;
      Point3F mProbeRefOffset;
      Point3F mProbeRefScale;
      F32 mAtten;

      F32 mScore;

      GFXCubemapHandle mPrefilterCubemap;
      GFXCubemapHandle mIrradianceCubemap;

      /// The priority of this light used for
      /// light and shadow scoring.
      F32 mPriority;

      enum ProbeShapeType
      {
         Box = 0,            
         Sphere = 1,               
         Skylight = 2
      };

      ProbeShapeType mProbeShapeType;
      bool mCanDamp;
   public:

      ProbeInfo() : mScore(0) {}
      ~ProbeInfo() {}

      // Copies data passed in from light
      void set(const ProbeInfo* probeInfo);

      // Accessors
      const MatrixF& getTransform() const { return mTransform; }
      void setTransform(const MatrixF& xfm) { mTransform = xfm; }

      Point3F getPosition() const { return mPosition; }
      void setPosition(const Point3F& pos) { mPosition = pos; }

      void setPriority(F32 priority) { mPriority = priority; }
      F32 getPriority() const { return mPriority; }

      void clear();
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

   /// <summary>
   /// Only used for interfacing with the editor's inspector bake button
   /// </summary>
   bool mBakeReflections;

   /// <summary>
   /// Whether this probe is enabled or not
   /// </summary>
   bool mEnabled;
   
   bool mDirty;

   /// <summary>
   /// Whether this probe's cubemap is dirty or not
   /// </summary>
   bool mCubemapDirty;

#ifdef TORQUE_TOOLS
   /// <summary>
   /// Used only when the editor is loaded, this is the shape data used for the probe viewing(aka, a sphere)
   /// </summary>
   Resource<TSShape> mEditorShape;
   /// <summary>
   /// This is the shape instance of the editor shape data
   /// </summary>
   TSShapeInstance* mEditorShapeInst;
#endif // TORQUE_TOOLS

   //--------------------------------------------------------------------------
   // Rendering variables
   //--------------------------------------------------------------------------
   /// <summary>
   /// The shape of the probe
   /// </summary>
   ProbeInfo::ProbeShapeType mProbeShapeType;

   /// <summary>
   /// This is effectively a packed cache of the probe data actually utilized for rendering.
   /// The RenderProbeManager uses this via the probe calling registerProbe on creation, and unregisterProbe on destruction
   /// When the manager goes to render it has the compacted data to read over more efficiently for setting up what probes should
   /// Actually render in that frame
   /// </summary>
   ProbeInfo mProbeInfo;

   /// <summary>
   /// Used to dictate what sort of cubemap the probes use when using IBL
   /// </summary>
   ReflectionModeType mReflectionModeType;

   /// <summary>
   /// The radius of the probe's influence. Only really relevent in Sphere probes
   /// </summary>
   F32 mRadius;
   /// <summary>
   /// The reference positional offset for the probe. This is used for adjusting the perceived center and area of influence.
   /// Helpful in adjusting parallax issues
   /// </summary>
   Point3F mProbeRefOffset;
   /// <summary>
   /// The reference scale for the probe. This is used for adjusting the perceived center and area of influence.
   /// Helpful in adjusting parallax issues
   /// </summary>
   Point3F mProbeRefScale;

   /// <summary>
   /// Only used for interfacing with the editor's inspector edit offset button
   /// </summary>
   bool mEditPosOffset;

   /// <summary>
   /// This is used when a static cubemap is used. The name of the cubemap is looked up and loaded for the IBL calculations
   /// </summary>
   StringTableEntry mCubemapName;
   CubemapData *mStaticCubemap;
   GFXCubemapHandle  mDynamicCubemap;

   //String cubeDescName;
   //U32 cubeDescId;
   //ReflectorDesc *reflectorDesc;

   //Utilized in dynamic reflections
   //CubeReflector mCubeReflector;

   bool mUseHDRCaptures;

   //irridiance resources
   CubemapData *mIrridianceMap;

   //prefilter resources
   CubemapData *mPrefilterMap;
   U32 mPrefilterMipLevels;
   U32 mPrefilterSize;

   /// <summary>
   /// This is calculated based on the object's persistantID. Effectively a unique hash ID to set it apart from other probes
   /// Used to ensure the cubemaps named when baking are unique
   /// </summary>
   String mProbeUniqueID;

   //Debug rendering
   static bool smRenderPreviewProbes;

   U32 mDynamicLastBakeMS;
   U32 mRefreshRateMS;


   bool mResourcesCreated;
   U32 mCaptureMask;
   bool mCanDamp;
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

   /// <summary>
   /// This is called when the object is deleted. It allows us to do special-case cleanup actions
   /// In probes' case, it's used to delete baked cubemap files
   /// </summary>
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
   void createEditorResources();

   /// <summary>
   /// Updates the probe rendering data
   /// </summary>
   virtual void updateProbeParams();
   
   bool createClientResources();

   /// <summary>
   /// Updates the probe's cubemaps in the array when using dynamic reflections
   /// </summary>
   void processDynamicCubemap();
   /// <summary>
   /// Updates the probe's cubemaps in the array when using baked cubemaps
   /// </summary>
   void processBakedCubemap();
   /// <summary>
   /// Updates the probe's cubemaps in the array when using a static cubemaps
   /// </summary>
   void processStaticCubemap();

   // This is the function that allows this object to submit itself for rendering
   void prepRenderImage(SceneRenderState *state);

   void _onRenderViz(ObjectRenderInst *ri,
      SceneRenderState *state,
      BaseMatInstance *overrideMat);

   void setPreviewMatParameters(SceneRenderState* renderState, BaseMatInstance* mat);

   /// <summary>
   /// This gets the filepath to the prefilter cubemap associated to this probe.
   /// In the event the probe is set to use a static cubemap, it is the prefiltered version of the cubemap's file
   /// </summary>
   /// <returns>The filepath to the prefilter cubemap</returns>
   String getPrefilterMapPath();
   /// <summary>
   /// This gets the filepath to the irradiance cubemap associated to this probe.
   /// In the event the probe is set to use a static cubemap, it is the irradiance version of the cubemap's file
   /// </summary>
   /// <returns>The filepath to the irradiance cubemap</returns>
   String getIrradianceMapPath();

   /// <summary>
   /// Invokes a cubemap bake action for this probe
   /// </summary>
   void bake();
};

typedef ReflectionProbe::ProbeInfo::ProbeShapeType ReflectProbeType;
DefineEnumType(ReflectProbeType);

typedef ReflectionProbe::ReflectionModeType ReflectionModeEnum;
DefineEnumType(ReflectionModeEnum);

#endif // _ReflectionProbe_H_
