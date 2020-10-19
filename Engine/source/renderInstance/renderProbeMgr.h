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

#include "core/util/systemInterfaceList.h"

#ifndef _MATERIALS_PROCESSEDSHADERMATERIAL_H_
#include "materials/processedShaderMaterial.h"
#endif
#ifndef _POSTEFFECTCOMMON_H_
#include "postFx/postEffectCommon.h"
#endif

#ifndef _REFLECTOR_H_
#include "scene/reflector.h"
#endif

static U32 MAXPROBECOUNT = 50;

class PostEffect;
class ReflectionProbe;

struct ProbeRenderInst
{
   bool mIsEnabled;

   MatrixF mTransform;

   F32 mRadius;

   bool mDirty;

   Box3F mBounds;
   Point3F mExtents;
   Point3F mPosition;
   Point3F mProbeRefOffset;
   Point3F mProbeRefScale;
   F32 mAtten;

   GFXCubemapHandle mPrefilterCubemap;
   GFXCubemapHandle mIrradianceCubemap;

   /// The priority of this light used for
   /// light and shadow scoring.
   F32 mPriority;

   /// A temporary which holds the score used
   /// when prioritizing lights for rendering.
   F32 mScore;

   enum ProbeShapeType
   {
      Box = 0,            ///< Sphere shaped
      Sphere = 1,               ///< Box-based shape
      Skylight = 2
   };

   ProbeShapeType mProbeShapeType;

   U32 mCubemapIndex;

   U32 mProbeIdx;

public:

   ProbeRenderInst();
   ~ProbeRenderInst();

   // Copies data passed in from light
   void set(const ProbeRenderInst *probeInfo);

   // Accessors
   const MatrixF& getTransform() const { return mTransform; }
   void setTransform(const MatrixF &xfm) { mTransform = xfm; }

   Point3F getPosition() const { return mPosition; }
   void setPosition(const Point3F &pos) { mPosition = pos; }

   void setPriority(F32 priority) { mPriority = priority; }
   F32 getPriority() const { return mPriority; }

   void setScore(F32 score) { mScore = score; }
   F32 getScore() const { return mScore; }

   void clear();

   inline bool operator ==(const ProbeRenderInst& b) const
   {
      return mProbeIdx == b.mProbeIdx;
   }
};

struct ProbeShaderConstants
{
   bool mInit;

   GFXShaderRef mShader;
   
   //Reflection Probes
   GFXShaderConstHandle *mProbePositionSC;
   GFXShaderConstHandle *mProbeRefPosSC;
   GFXShaderConstHandle *mRefScaleSC;
   GFXShaderConstHandle *mWorldToObjArraySC;
   GFXShaderConstHandle *mProbeConfigDataSC;
   GFXShaderConstHandle *mProbeSpecularCubemapSC;
   GFXShaderConstHandle *mProbeIrradianceCubemapSC;
   GFXShaderConstHandle *mProbeCountSC;

   GFXShaderConstHandle *mBRDFTextureMap;

   GFXShaderConstHandle *mSkylightCubemapIdxSC;

   ProbeShaderConstants();
   ~ProbeShaderConstants();

   void init(GFXShader* buffer);

   bool isValid();

   void _onShaderReload();
};

typedef Map<GFXShader*, ProbeShaderConstants*> ProbeConstantMap;

struct ProbeDataSet
{
   Vector<Point4F> probePositionArray;
   Vector<Point4F> refScaleArray;
   Vector<Point4F> probeRefPositionArray;
   Vector<Point4F> probeConfigArray;

   Vector<MatrixF> probeWorldToObjArray;

   S32 skyLightIdx;

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
   }

   ProbeDataSet(U32 _maxProbeCount)
   {
      maxProbeCount = _maxProbeCount;

      probePositionArray.setSize(maxProbeCount);
      refScaleArray.setSize(maxProbeCount);
      probeRefPositionArray.setSize(maxProbeCount);
      probeConfigArray.setSize(maxProbeCount);

      probeWorldToObjArray.setSize(maxProbeCount);

      skyLightIdx = -1;
      effectiveProbeCount = 0;
   }
};

struct ProbeTextureArrayData
{
   GFXTexHandle BRDFTexture;
   GFXCubemapArrayHandle prefilterArray;
   GFXCubemapArrayHandle irradianceArray;
};

//**************************************************************************
// RenderObjectMgr
//**************************************************************************
class RenderProbeMgr : public RenderBinManager
{
   typedef RenderBinManager Parent;

   Vector<ProbeRenderInst*> mRegisteredProbes;

   bool mProbesDirty;
   
   Vector<ProbeRenderInst>  mActiveProbes;
public:
   //maximum number of allowed probes
   static const U32 PROBE_MAX_COUNT = 250;
   //maximum number of rendered probes per frame adjust as needed
   static const U32 PROBE_MAX_FRAME = 8;
   //number of slots to allocate at once in the cubemap array
   static const U32 PROBE_ARRAY_SLOT_BUFFER_SIZE = 10;

   static const U32 PROBE_IRRAD_SIZE = 64;
   static const U32 PROBE_PREFILTER_SIZE = 64;
   static const GFXFormat PROBE_FORMAT = GFXFormatR16G16B16A16F;// GFXFormatR8G8B8A8;// when hdr fixed GFXFormatR16G16B16A16F; look into bc6h compression
   static const U32 INVALID_CUBE_SLOT = U32_MAX;

   static F32 smMaxProbeDrawDistance;
   static S32 smMaxProbesPerFrame;

private:
   //Array rendering
   U32 mEffectiveProbeCount;
   S32 mMipCount;

   bool            mHasSkylight;
   S32             mSkylightCubemapIdx;

   //number of cubemaps
   U32 mCubeMapCount;
   //number of cubemap slots allocated
   U32 mCubeSlotCount;
   //array of cubemap slots, due to the editor these may be mixed around as probes are added and deleted
   bool mCubeMapSlots[PROBE_MAX_COUNT];

   GFXCubemapArrayHandle mPrefilterArray;
   GFXCubemapArrayHandle mIrradianceArray;

   //Utilized in forward rendering
   ProbeConstantMap mConstantLookup;
   GFXShaderRef mLastShader;
   ProbeShaderConstants* mLastConstants;

   //
   SimObjectPtr<PostEffect> mProbeArrayEffect;

   //Default skylight, used for shape editors, etc
   ProbeRenderInst* mDefaultSkyLight;

   GFXTexHandle mBRDFTexture;

   ProbeDataSet mProbeData;
   ///Prevents us from saving out the cubemaps(for now) but allows us the full HDR range on the in-memory cubemap captures
   bool mUseHDRCaptures;

   U32 mPrefilterMipLevels;
   U32 mPrefilterSize;
public:
   RenderProbeMgr();
   RenderProbeMgr(RenderInstType riType, F32 renderOrder, F32 processAddOrder);
   virtual ~RenderProbeMgr();
   virtual bool onAdd();
   virtual void onRemove();

   // ConsoleObject
   static void initPersistFields();
   static void consoleInit();

   DECLARE_CONOBJECT(RenderProbeMgr);

protected:
   /// The current active light manager.
   static RenderProbeMgr *smProbeManager;

   /// This helper function sets the shader constansts
   /// for the stock 4 light forward lighting code.
   void _update4ProbeConsts(const SceneData &sgData,
      MatrixSet &matSet,
      ProbeShaderConstants *probeShaderConsts,
      GFXShaderConstBuffer *shaderConsts);

   void _setupStaticParameters();
   void _setupPerFrameParameters(const SceneRenderState *state);
   virtual void addElement(RenderInst* inst) {};
   virtual void render(SceneRenderState * state);

   ProbeShaderConstants* getProbeShaderConstants(GFXShaderConstBuffer* buffer);

   PostEffect* getProbeArrayEffect();


   U32 _findNextEmptyCubeSlot()
   {
      for (U32 i = 0; i < PROBE_MAX_COUNT; i++)
      {
         if (!mCubeMapSlots[i])
            return i;
      }
      return INVALID_CUBE_SLOT;
   }

public:
   // RenderBinMgr
   void updateProbes();

   /// Returns the active LM.
   static inline RenderProbeMgr* getProbeManager();

   void registerProbe(ProbeRenderInst* newProbe);
   void unregisterProbe(U32 probeIdx);
   void submitProbe(const ProbeRenderInst& newProbe);

   static S32 QSORT_CALLBACK _probeScoreCmp(const ProbeRenderInst* a, const  ProbeRenderInst* b);

   virtual void setProbeInfo(ProcessedMaterial *pmat,
	   const Material *mat,
	   const SceneData &sgData,
	   const SceneRenderState *state,
	   U32 pass,
	   GFXShaderConstBuffer *shaderConsts);

   void setupSGData(SceneData& data, const SceneRenderState* state, LightInfo* light);
   
   void updateProbeTexture(ProbeRenderInst* probeInfo);

   void reloadTextures();

   /// Debug rendering
   static bool smRenderReflectionProbes;

   void bakeProbe(ReflectionProbe *probeInfo);
   void bakeProbes();

   void getProbeTextureData(ProbeTextureArrayData* probeTextureSet);
   S32 getSkylightIndex() { return mSkylightCubemapIdx; }
   //accumulates the best fit of probes given the object position
   void getBestProbes(const Point3F& objPosition, ProbeDataSet* probeDataSet);
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
