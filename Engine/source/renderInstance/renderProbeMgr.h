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
#pragma once
#ifndef RENDER_PROBE_MGR_H
#define RENDER_PROBE_MGR_H

#ifndef _RENDERBINMANAGER_H_
#include "renderInstance/renderBinManager.h"
#endif
#ifndef _MATINSTANCE_H_
#include "materials/matInstance.h"
#endif
#ifndef _MATTEXTURETARGET_H_
#include "materials/matTextureTarget.h"
#endif
#ifndef _GFXPRIMITIVEBUFFER_H_
#include "gfx/gfxPrimitiveBuffer.h"
#endif
#ifndef _GFXVERTEXBUFFER_H_
#include "gfx/gfxVertexBuffer.h"
#endif

//#include "core/util/systemInterfaceList.h"

#ifndef _MATERIALS_PROCESSEDSHADERMATERIAL_H_
#include "materials/processedShaderMaterial.h"
#endif
#ifndef _POSTEFFECTCOMMON_H_
#include "postFx/postEffectCommon.h"
#endif

#ifndef _REFLECTOR_H_
#include "scene/reflector.h"
#endif

#ifndef REFLECTIONPROBE_H
#include "T3D/lighting/reflectionProbe.h"
#endif

class PostEffect;
class ReflectionProbe;

/// <summary>
/// A simple container for a ReflectionProbe's ProbeInfo and index for it's associated
/// cubemaps in the cubemap array pair
/// </summary>
struct ProbeRenderInst
{
   ReflectionProbe::ProbeInfo* mProbeInfo;

   U32 mCubemapIndex;

public:

   ProbeRenderInst();
   ~ProbeRenderInst();

   // Copies data passed in from light
   void set(const ProbeRenderInst *probeInfo);
};

/// <summary>
/// A container for all the shader consts needed for rendering probes in forward mode
/// </summary>
struct ProbeShaderConstants
{
   bool mInit;

   GFXShaderRef mShader;
   
   //Reflection Probes
   GFXShaderConstHandle *mProbePositionArraySC;
   GFXShaderConstHandle *mProbeRefPosArraySC;
   GFXShaderConstHandle *mRefScaleArraySC;
   GFXShaderConstHandle *mWorldToObjArraySC;
   GFXShaderConstHandle *mProbeConfigDataArraySC;
   GFXShaderConstHandle *mProbeSpecularCubemapArraySC;
   GFXShaderConstHandle *mProbeIrradianceCubemapArraySC;
   GFXShaderConstHandle *mProbeCountSC;

   GFXShaderConstHandle *mBRDFTextureMap;
   GFXShaderConstHandle* mWetnessTextureMap;   
   GFXShaderConstHandle *mSkylightCubemapIdxSC;
   GFXShaderConstHandle* mSkylightDampSC;

   GFXShaderConstHandle* mMaxProbeDrawDistanceSC;

   ProbeShaderConstants();
   ~ProbeShaderConstants();

   void init(GFXShader* buffer);

   bool isValid();

   void _onShaderReload();
};

typedef Map<GFXShader*, ProbeShaderConstants*> ProbeConstantMap;

/// <summary>
/// A container for processed and packed probe data. This is made when we get the frame's
/// best probes, and is passed to the shader for actual rendering.
/// </summary>
struct ProbeDataSet
{
   Vector<Point4F> probePositionArray;
   Vector<Point4F> refScaleArray;
   Vector<Point4F> probeRefPositionArray;
   Vector<Point4F> probeConfigArray;

   Vector<MatrixF> probeWorldToObjArray;
   S32 skyLightIdx;
   bool skyLightDamp;
   U32 effectiveProbeCount;
   U32 maxProbeCount;

   ProbeDataSet()
   {
      probePositionArray.setSize(0);
      refScaleArray.setSize(0);
      probeRefPositionArray.setSize(0);
      probeConfigArray.setSize(0);

      probeWorldToObjArray.setSize(0);
      skyLightIdx = -1;
      effectiveProbeCount = 0;
      maxProbeCount = 0;
      skyLightDamp = true;
   }

   ProbeDataSet(U32 _maxProbeCount)
   {
      maxProbeCount = _maxProbeCount;

      probePositionArray.setSize(maxProbeCount);
      refScaleArray.setSize(maxProbeCount);
      probeRefPositionArray.setSize(maxProbeCount);
      probeConfigArray.setSize(maxProbeCount);

      probeWorldToObjArray.setSize(maxProbeCount);

      effectiveProbeCount = 0;
   }
};

//**************************************************************************
// RenderObjectMgr
//**************************************************************************
class RenderProbeMgr : public RenderBinManager
{
   typedef RenderBinManager Parent;

public:
   //maximum number of allowed probes
   static const U32 PROBE_MAX_COUNT = 250;
   //maximum number of rendered probes per frame adjust as needed
   static const U32 PROBE_MAX_FRAME = 8;
   //number of slots to allocate at once in the cubemap array
   static const U32 PROBE_ARRAY_SLOT_BUFFER_SIZE = 10;

   //These dictate the default resolution size for the probe arrays
   static const GFXFormat PROBE_FORMAT = GFXFormatR16G16B16A16F;// GFXFormatR8G8B8A8;// when hdr fixed GFXFormatR16G16B16A16F; look into bc6h compression
   static const U32 INVALID_CUBE_SLOT = U32_MAX;

   static F32 smMaxProbeDrawDistance;
   static S32 smMaxProbesPerFrame;
   static S32 smProbeBakeResolution;
   SceneRenderState *mState;
private:
   /// <summary>
   /// List of registered probes. These are not necessarily rendered in a given frame
   /// but the Probe Manager is aware of them and they have cubemap array slots allocated
   /// </summary>
   Vector<ProbeRenderInst>    mRegisteredProbes;

   /// <summary>
   /// List of active probes. These are ones that are not only registered, but submitted by the probe itself as
   /// ready to be rendered. Likely to be rendered in the current frame, settings-dependent.
   /// </summary>
   Vector<ProbeRenderInst>    mActiveProbes;

   /// <summary>
   /// The PostEffect used to actually rendered the probes into the frame when in deferred mode
   /// </summary>
   SimObjectPtr<PostEffect>   mProbeArrayEffect;

   /// <summary>
   /// Do we have a active skylight probe
   /// </summary>
   bool            mHasSkylight;

   /// <summary>
   /// If we have a skylight, what's the array pair index for it?
   /// </summary>
   S32             mSkylightCubemapIdx;
   bool            mSkylightDamp;
   /// <summary>
   /// The 'effective' probe count. This tracks the number of probes that are actually going to be rendered
   /// </summary>
   U32                        mEffectiveProbeCount;
   //
   //Array rendering

   /// <summary>
   /// The number of mips the cubemap array has. Mips are used in the PBR calcs for handling roughness
   /// </summary>
   S32                        mMipCount;

   /// <summary>
   /// The number of cubemaps registered in our array pair
   /// </summary>
   U32 mCubeMapCount;

   /// <summary>
   /// The number of allocated slots for the array pair. Rather than adding slots one at a time to the arrays
   /// We allocate in chunks so we don't have to resize/rebuild the arrays as often
   /// </summary>
   U32 mCubeSlotCount;

   /// <summary>
   /// List indicating if a given allocated slot is actually in use.
   /// Due to the editor these may be mixed around as probes are added and deleted
   /// </summary>
   /// <returns></returns>
   bool mCubeMapSlots[PROBE_MAX_COUNT];

   /// <summary>
   /// The prefilter cubemap array
   /// </summary>
   GFXCubemapArrayHandle mPrefilterArray;

   /// <summary>
   /// The irradiance cubemap array
   /// </summary>
   GFXCubemapArrayHandle mIrradianceArray;

   //Utilized in forward rendering

   /// <summary>
   /// This is used to look up already-made ProbeShaderConsts for a given shader
   /// This allows us to avoid having to rebuild the consts each frame if it's a shader
   /// we've already handled before.
   /// </summary>
   ProbeConstantMap mConstantLookup;

   /// <summary>
   /// The last shader we rendered(in forward mode). With this, we can shortcut the constant
   /// lookup if the shader being processed and the last one are the same.
   /// </summary>
   GFXShaderRef mLastShader;

   /// <summary>
   /// THe previous shader constants. When used in conjunction with the mLastShader, we can skip
   /// having to do a lookup to find an existing ProbeShaderConstants, saving overhead on batched
   /// rendering
   /// </summary>
   ProbeShaderConstants* mLastConstants;

   /// <summary>
   /// The BRDF texture used in PBR math calculations
   /// </summary>
   GFXTexHandle mBRDFTexture;
   GFXTexHandle mWetnessTexture;
   
   /// <summary>
   /// Processed best probe selection list of the current frame when rendering in deferred mode.
   /// </summary>
   ProbeDataSet mProbeData;

   /// <summary>
   /// Allows us the full HDR range on the in-memory cubemap captures
   /// </summary>
   bool mUseHDRCaptures;

   /// <summary>
   /// holds the normal render state for light fade so we can capture them before and restore them after baking
   /// </summary>
   S32 mRenderMaximumNumOfLights;
   bool mRenderUseLightFade;
protected:
   /// The current active light manager.
   static RenderProbeMgr* smProbeManager;

   //=============================================================================
   // Internal Management/Utility Functions
   //=============================================================================

   /// <summary>
   /// Simple utility function that finds the next free cubemap slot for the cubemap array
   /// </summary>
   /// <returns>U32 index of next available slot</returns>
   U32 _findNextEmptyCubeSlot()
   {
      for (U32 i = 0; i < PROBE_MAX_COUNT; i++)
      {
         if (!mCubeMapSlots[i])
            return i;
      }
      return INVALID_CUBE_SLOT;
   }

   /// <summary>
   /// Utility function to quickly find a ProbeRenderInst in association to a
   /// ReflectionProbe's ProbeInfo
   /// </summary>
   /// <param name="probeInfo"></param>
   /// <returns>Associated ProbeRederInst to param's probeInfo. Null if no matches found</returns>
   ProbeRenderInst* findProbeInst(ReflectionProbe::ProbeInfo* probeInfo)
   {
      for (U32 i = 0; i < mRegisteredProbes.size(); i++)
      {
         auto asd = mRegisteredProbes[i];
         if (mRegisteredProbes[i].mProbeInfo == probeInfo)
         {
            return &mRegisteredProbes[i];
         }
      }

      return nullptr;
   }

public:
   RenderProbeMgr();
   RenderProbeMgr(RenderInstType riType, F32 renderOrder, F32 processAddOrder);
   virtual ~RenderProbeMgr();
   virtual bool onAdd();
   virtual void onRemove();

   // ConsoleObject
   static void initPersistFields();
   static void consoleInit();

   virtual void addElement(RenderInst* inst) {};
   DECLARE_CONOBJECT(RenderProbeMgr);

   /// <summary>
   /// Static flag used to indicate if probes should be rendered at all. Used for debugging
   /// </summary>
   static bool smRenderReflectionProbes;

   //=============================================================================
   // Utility functions for processing and setting up the probes for rendering
   //=============================================================================

   /// <summary>
   /// Sorts probes based on their score values. These scores are calculated by the probes themselves based on size, distance from camera, etc
   /// </summary>
   static S32 QSORT_CALLBACK _probeScoreCmp(const ProbeRenderInst* a, const  ProbeRenderInst* b);

   /// <summary>
   /// Builds a dataset of the best probes to be rendered this frame.
   /// </summary>
   /// <param name="objPosition"></param>
   /// <param name="probeDataSet"></param>

   void getBestProbes(const Point3F& objPosition, ProbeDataSet* probeDataSet);

   /// <summary>
   /// This function adds a ReflectionProbe to the registered list and also allocates
   /// a slot in the cubemap array pair for its use
   /// </summary>
   /// <param name="probeInfo">The probe info to be registered to the bin</param>
   void registerProbe(ReflectionProbe::ProbeInfo* probeInfo);

   /// <summary>
   /// This function removes the ReflectionProbe from the registered list, and marks it's cubemap
   /// array slots as unused, allowing them to be freed.
   /// </summary>
   /// <param name="probeInfo">The probe info to be un-registered to the bin</param>
   void unregisterProbe(ReflectionProbe::ProbeInfo* probeInfo);

   /// <summary>
   /// This function is for registering a ReflectionProbe's probe info
   /// as being rendered in the current frame. This is distinct from
   /// registered probes in that registered probes are any 'real' probe
   /// in the scene, but they may not necessarily render
   /// Active(submmitted) probes are intended to actual be rendered this frame
   /// </summary>
   /// <param name="probe">The ProbeInfo being submitted to be rendered</param>
   void submitProbe(ReflectionProbe::ProbeInfo* probe);

   /// <summary>
   /// Gets the PostEffect used by the bin for rendering the probe array in deferred
   /// </summary>
   /// <returns>the PostEffect object</returns>
   PostEffect* getProbeArrayEffect();
   U32 getProbeTexSize();
   /// <summary>
   /// Finds the associated cubemap array slot for the incoming ProbeInfo and updates the array's texture(s) from it
   /// </summary>
   /// <param name="probeInfo"></param>
   void updateProbeTexture(ReflectionProbe::ProbeInfo* probeInfo);

   /// <summary>
   /// Forces an update for all registered probes' cubemaps
   /// </summary>
   void reloadTextures();

   /// <summary>
   /// Takes a reflection probe and runs the cubemap bake process on it, outputting the resulting files to disk
   /// </summary>
   void bakeProbe(ReflectionProbe* probe);
   void preBake();
   void postBake();
   /// <summary>
   /// Runs the cubemap bake on all probes in the current scene
   /// </summary>
   void bakeProbes();

   /// <summary>
   /// Returns the active Probe Manager.
   /// </summary>
   static inline RenderProbeMgr* getProbeManager();

   //=============================================================================
   // Forward Rendering functions
   //=============================================================================

   /// <summary>
   /// This function returns or builds a ProbeShaderConsts containing needed data for
   /// rendering probes in forward mode
   /// </summary>
   /// <param name="buffer">The GFXShaderConstBuffer used to build or fetch the Probe Consts</param>
   ProbeShaderConstants* getProbeShaderConstants(GFXShaderConstBuffer* buffer);

   /// <summary>
   /// Sets up the probe data required for doing a render in forward mode.
   /// </summary>
   virtual void setProbeInfo(ProcessedMaterial* pmat,
      const Material* mat,
      const SceneData& sgData,
      const SceneRenderState* state,
	   U32 pass,
      GFXShaderConstBuffer* shaderConsts);

   /// <summary>
   /// Invoked as part of the setup in preperation to render an object in forward mode. Used to ensure the probes are
   /// sorted ahead of render.
   /// </summary>
   /// <param name="state"></param>
   void setupSGData(SceneData& data, const SceneRenderState* state, LightInfo* light);
   
   /// <summary>
   /// Sets up and binds all the shader const data required for rendering probes/IBL for a forward-rendered material.
   /// </summary>
   /// <returns></returns>
   void _update4ProbeConsts(const SceneData& sgData,
      MatrixSet& matSet,
      ProbeShaderConstants* probeShaderConsts,
      GFXShaderConstBuffer* shaderConsts);

   //=============================================================================
   // Deferred Rendering Functions
   //=============================================================================

   /// <summary>
   /// Ensures the probes are properly sorted before we render them in deferred mode
   /// </summary>
   void _setupPerFrameParameters(const SceneRenderState *state);

   /// <summary>
   /// Renders the sorted probes list via a PostEffect to draw them into the buffer data in deferred mode.
   /// </summary>
   virtual void render(SceneRenderState * state);

   virtual void clear() { mActiveProbes.clear(); Parent::clear(); }
};

RenderProbeMgr* RenderProbeMgr::getProbeManager()
{
   if (smProbeManager == nullptr)
   {
      RenderProbeMgr* probeManager = new RenderProbeMgr();

      smProbeManager = probeManager;
   }

   return smProbeManager;
}

#define PROBEMGR RenderProbeMgr::getProbeManager()

#endif // RENDER_PROBE_MGR_H
