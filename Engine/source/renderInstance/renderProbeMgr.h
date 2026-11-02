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
#ifndef _ENGINEAPI_H_
#include "console/engineAPI.h"
#endif

class PostEffect;
class ReflectionProbe;
class SubScene;

/// <summary>
/// A simple container for a ReflectionProbe's ProbeInfo and index for it's associated
/// cubemaps in the cubemap array pair
/// </summary>
struct ProbeRenderInst
{
   ReflectionProbe::ProbeInfo* mProbeInfo;

   U32 mCubemapIndex;

   /// <summary>
   /// Score based on camera proximity.
   /// </summary>
   F32 mPriorityScore;

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

/// <summary>
/// One probe's atlas record, which is also its row in the atlas texture.
/// It's packed so that we can do early out tests in the shader like bounds checking with the fewest
/// reads possible to keep cost low per probe we do as low-LOD rendering
/// If the layout's changed, update sProbeAtlasVersion.
/// </summary>
#pragma pack(push, 4)
struct ProbeAtlasRecord
{
   enum Flags
   {
      CanDamp = BIT(0),
      Interior = BIT(1) //If flagged, we'll blend out the sun's light for the probe's influence area
   };

   //Texels 0-1: the bounds of the probe's influence
   Point3F boundsMin = Point3F::Zero;
   F32 reserved0 = 0;
   Point3F boundsMax = Point3F::Zero;
   F32 reserved1 = 0;

   //Texels 2-4: ProbeInfo::mTransform
   F32 worldToObj[3][4] = {};

   //Texel 5
   Point3F position = Point3F::Zero;
   F32 shapeType = 0;

   //Texel 6
   F32 radius = 0;
   F32 atten = 0;
   U32 persistentProbeId = 0;
   U32 reserved2 = 0;

   //Texel 7
   F32 ambient[3] = {};         //linear ambient average color
   U32 flags = 0;

   //Texels 8-9, only read on the CPU
   Point3F refOffset = Point3F::Zero;
   F32 reserved3 = 0;
   Point3F refScale = Point3F::Zero;
   F32 reserved4 = 0;

   Box3F getBounds() const { return Box3F(boundsMin, boundsMax); }
};
#pragma pack(pop)

/// <summary>
/// Header stored in row 0 of every probe atlas file. It is copied over the start of that row
/// </summary>
#pragma pack(push, 4)
struct ProbeAtlasHeader
{
   U32 fileId = 0;      //sProbeAtlasFileId
   U32 version = 0;     //sProbeAtlasVersion
   U32 bakeStamp = 0;   //Platform::getTime() when atlas was updated
   U32 count = 0;       //number of probes
};
#pragma pack(pop)

//Atlas file: a GFXFormatR32G32B32A32F texture of ProbeAtlasRecord rows, after a header row
static const U32 sProbeAtlasFileId = 0x41425250; //'PRBA'
static const U32 sProbeAtlasVersion = 1;
static const U32 sProbeAtlasRowBytes = sizeof(ProbeAtlasRecord);
static const U32 sProbeAtlasRowTexels = sProbeAtlasRowBytes / 16;

//**************************************************************************
// RenderObjectMgr
//**************************************************************************
class RenderProbeMgr : public RenderBinManager
{
   typedef RenderBinManager Parent;

public:
   enum PublicConstants {
      //Default max number of rendered high-LOD probes per frame
      DefaultMaxProbePerFrame = 8,
      //Default max size of the high-LOD slot pool
      DefaultMaxHighLodSlots = 32,

      //These dictate the default resolution size for the probe arrays
      ProbeFormat = GFXFormatR16G16B16A16F,// GFXFormatR8G8B8A8 for non-HDR; look into bc6h compression
      InvalidCubeSlot = U32_MAX
   };

   static F32 smMaxProbeDrawDistance;

   //The requested number of high LOD probes per frame. 
   static S32 smMaxHighProbesPerFrame;
   static S32 smProbeBakeResolution;

   //Size of the high-LOD slot pool. Read once in onAdd(), as the arrays are allocated at this size and never grow
   static S32 smMaxHighLodSlots;

   //Milliseconds between progress reports while a bake runs
   static S32 smBakeProgressIntervalMS;

   //How much of the sun is left inside an interior probe once its shadows have faded out (0 = none, 1 = full sun)
   static F32 smInteriorSunResidual;

   //Diffuse light floor a probe capture gives every light even in full shadow
   static F32 smCaptureLightFloor;

private:
   /// <summary>
   /// List of registered probes. These are not necessarily rendered in a given frame
   /// but the Probe Manager is aware of them. They are given a cubemap slot depending on scoring
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
   /// List indicating if a given high-LOD slot is currently occupied by sufficiently scoring probe.
   /// </summary>
   Vector<bool> mCubeMapSlots;

   /// <summary>
   /// The prefilter cubemap array
   /// </summary>
   GFXTexHandle mPrefilterArray;

   /// <summary>
   /// The irradiance cubemap array
   /// </summary>
   GFXTexHandle mIrradianceArray;

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
   /// State of an bake. WaitingForGhosts runs from the SubScene load until the client ghosts
   /// of the probes exist, Ready is that having happened and the loop being queued, and Running is the loop baking the probes
   /// </summary>
   enum BakeState
   {
      BakeIdle,
      BakeWaitingForGhosts,
      BakeReady,
      BakeRunning
   };

   BakeState mBakeState;
   U32 mBakeWaitStartMS;

   /// <summary>
   /// The server probes being baked.
   /// </summary>
   Vector<SimObjectPtr<ReflectionProbe> > mBakeProbes;

   U32 pendingGhostCount();
   void beginBakeRun();
   void finishBake(bool success);
   void onSceneGhostingDone(NetConnection* conn);

   /// <summary>
   /// Timestamp when we last updated probe priorities, to avoid reruns in a frame
   /// </summary>
   U32  mLastPriorityUpdateMS;

   /// <summary>
   /// The root scene's probe atlas roster
   /// </summary>
   Vector<ProbeAtlasRecord> mRootAtlasRoster;

   /// <summary>
   /// Level assetId the client was told about at level start, used to look up the atlas
   /// </summary>
   StringTableEntry mLevelAssetId = NULL;

   /// <summary>
   /// Each loaded SubScene's roster, keyed to that SubScene instance
   /// </summary>
   Map<SubScene*, Vector<ProbeAtlasRecord> > mSubSceneAtlasRosters;

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
   U32 findNextEmptyCubeSlot()
   {
      for (U32 i = 0; i < mCubeMapSlots.size(); i++)
      {
         if (!mCubeMapSlots[i])
            return i;
      }
      return InvalidCubeSlot;
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
         if (mRegisteredProbes[i].mProbeInfo == probeInfo)
         {
            return &mRegisteredProbes[i];
         }
      }

      return NULL;
   }

public:
   RenderProbeMgr();
   RenderProbeMgr(RenderInstType riType, F32 renderOrder, F32 processAddOrder);
   virtual ~RenderProbeMgr();
   bool onAdd() override;
   void onRemove() override;

   // ConsoleObject
   static void initPersistFields();
   static void consoleInit();

   void addElement(RenderInst* inst) override {};
   DECLARE_CONOBJECT(RenderProbeMgr);

   /// <summary>
   /// Static flag used to indicate if probes should be rendered at all. Used for debugging
   /// </summary>
   static bool smRenderReflectionProbes;

   static bool smBakeReflectionProbes;
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
   /// Registers a probe to the manager.
   /// </summary>
   /// <param name="probeInfo">The probe info to be registered</param>
   void registerProbe(ReflectionProbe::ProbeInfo* probeInfo);

   /// <summary>
   /// Removes the ReflectionProbe from the registered list, releasing its high-LOD slot first if it held one.
   /// </summary>
   /// <param name="probeInfo">The probe info to be un-registered</param>
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
   /// Acquires a high-LOD slot for the probeInfo if it doesn't already have one.
   /// Replaces the lowest-scoring existing slot if no slots are free.
   /// Returns true if the probeInfo has a slot.
   /// </summary>
   bool acquireSlot(ReflectionProbe::ProbeInfo* probeInfo);

   /// <summary>
   /// Frees probeInfo's high-LOD slot, if it holds one.
   /// </summary>
   void releaseSlot(ReflectionProbe::ProbeInfo* probeInfo);

   /// <summary>
   /// Picks the best-scoring probes for high-LOD slots. 
   /// </summary>
   void updateHighLodSlots();

   /// <summary>
   /// Updates the scores for all candidate probes.
   /// Returns false if it had already run this frame, or this isn't the primary view pass
   /// </summary>
   bool updateProbeScores(const SceneRenderState* state);

   /// <summary>
   /// Returns true for the primary client camera view, which is used to dictate high-LOD scoring/slot assigments.
   /// </summary>
   static bool isPrimaryView(const SceneRenderState* state);

   /// <summary>
   /// The number of high LOD probes per frame in effect: smMaxProbesPerFrame held to what the shader supports
   /// </summary>
   static U32 getMaxHighLodProbes();

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
   /// Bakes every probe in the scene. For SubScemes, tt force loads them, then waits for the client ghosts
   /// of their probes. Once ghosting is completed, the actual bake runs.
   ///Returns false if a bake is already running or there is no scene somehow
   /// </summary>
   bool startBakeProbes();

   /// <summary>
   /// Stops a bake started, and releases any SubScenes it loaded. Probes already baked stay baked
   /// </summary>
   void cancelBake();

   bool isBaking() const { return mBakeState != BakeIdle; }

   /// <summary>
   /// Runs the bake loop of a bake, once its ghosts have ghosted. Called after the ghosting is done.
   /// </summary>
   void runBake();

   DECLARE_CALLBACK(void, onProbeBakeProgress, (U32 done, U32 total));
   DECLARE_CALLBACK(void, onProbeBakeComplete, (bool success));

   /// <summary>
   /// Writes out every baked probe's data to an atlas file, respective its owner. Root level asset has its own, and then any given subscene has its own as well.
   /// </summary>
   void serializeProbeAtlas();

   /// <summary>
   /// Loads the root scene's probe atlas into the roster.
   /// </summary>
   bool loadLevelAtlas(const char* levelAssetId = "");
   void clearLevelAtlas() { mRootAtlasRoster.clear(); mLevelAssetId = NULL; }

   /// <summary>
   /// The root level atlas file path
   /// </summary>
   String rootAtlasPath() const;

   /// <summary>
   /// Loads/unloads a SubScene's probe atlas into the roster
   /// </summary>
   bool loadSubSceneAtlas(SubScene* subScene);
   void unloadSubSceneAtlas(SubScene* subScene);

   /// <summary>
   /// Total roster entries across the root scene and every loaded SubScene
   /// </summary>
   U32 getAtlasRosterCount();

   static void fillProbeAtlasRecord(ProbeAtlasRecord& record, ReflectionProbe* clientProbe);
   static bool readProbeAtlasFile(const String& path, Vector<ProbeAtlasRecord>& outRoster, ProbeAtlasHeader* outHeader = NULL);
   static void writeProbeAtlasFile(const String& path, const Vector<ProbeAtlasRecord>& records);
   static void collectAtlasProbes(Vector<ReflectionProbe*>& outRootProbes, Map<SubScene*, Vector<ReflectionProbe*> >& outPartitions);
   static const ProbeAtlasRecord* findAtlasRecord(const Vector<ProbeAtlasRecord>& records, U32 persistentProbeId);
   static U32 buildAtlasPartitionRecords(const String& path, const Vector<ReflectionProbe*>& serverProbes, Vector<ProbeAtlasRecord>& outRecords);

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
   void render(SceneRenderState * state) override;

   void clear() override { mActiveProbes.clear(); Parent::clear(); }
};

RenderProbeMgr* RenderProbeMgr::getProbeManager()
{
   if (smProbeManager == NULL)
   {
      RenderProbeMgr* probeManager = new RenderProbeMgr();

      smProbeManager = probeManager;
   }

   return smProbeManager;
}

#define PROBEMGR RenderProbeMgr::getProbeManager()

#endif // RENDER_PROBE_MGR_H
