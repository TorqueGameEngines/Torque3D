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

   bool mIsSkylight;

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

   VectorF getDirection() const { return mTransform.getForwardVector(); }
   void setDirection(const VectorF &val);

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
   GFXShaderConstHandle *mRefBoxMinSC;
   GFXShaderConstHandle *mRefBoxMaxSC;
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
   AlignedArray<Point4F> probePositionArray;
   AlignedArray<Point4F> refBoxMinArray;
   AlignedArray<Point4F> refBoxMaxArray;
   AlignedArray<Point4F> probeRefPositionArray;
   AlignedArray<Point4F> probeConfigArray;

   Vector<MatrixF> probeWorldToObjArray;

   S32 skyLightIdx;

   U32 effectiveProbeCount;

   U32 MAX_PROBE_COUNT;

   ProbeDataSet(U32 maxProbeCount)
   {
      MAX_PROBE_COUNT = maxProbeCount;

      probePositionArray = AlignedArray<Point4F>(maxProbeCount, sizeof(Point4F));
      refBoxMinArray = AlignedArray<Point4F>(maxProbeCount, sizeof(Point4F));
      refBoxMaxArray = AlignedArray<Point4F>(maxProbeCount, sizeof(Point4F));
      probeRefPositionArray = AlignedArray<Point4F>(maxProbeCount, sizeof(Point4F));
      probeConfigArray = AlignedArray<Point4F>(maxProbeCount, sizeof(Point4F));

      probeWorldToObjArray.setSize(maxProbeCount);

      // Need to clear the buffers so that we don't leak
      // lights from previous passes or have NaNs.
      dMemset(probePositionArray.getBuffer(), 0, probePositionArray.getBufferSize());
      dMemset(refBoxMinArray.getBuffer(), 0, refBoxMinArray.getBufferSize());
      dMemset(refBoxMaxArray.getBuffer(), 0, refBoxMaxArray.getBufferSize());
      dMemset(probeRefPositionArray.getBuffer(), 0, probeRefPositionArray.getBufferSize());
      dMemset(probeConfigArray.getBuffer(), 0, probeConfigArray.getBufferSize());
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

   Vector<ProbeRenderInst> mRegisteredProbes;

   bool mProbesDirty;

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

   //Array rendering
   U32 mEffectiveProbeCount;
   S32 mMipCount;
   Vector<Point4F> probePositionsData;
   Vector<Point4F> probeRefPositionsData;
   Vector<MatrixF> probeWorldToObjData;
   Vector<Point4F> refBoxMinData;
   Vector<Point4F> refBoxMaxData;
   Vector<Point4F> probeConfigData;

   bool            mHasSkylight;
   S32             mSkylightCubemapIdx;

   AlignedArray<Point4F> mProbePositions;
   AlignedArray<Point4F> mRefBoxMin;
   AlignedArray<Point4F> mRefBoxMax;
   AlignedArray<float> mProbeUseSphereMode;
   AlignedArray<float> mProbeRadius;
   AlignedArray<float> mProbeAttenuation;

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

public:
   RenderProbeMgr();
   RenderProbeMgr(RenderInstType riType, F32 renderOrder, F32 processAddOrder);
   virtual ~RenderProbeMgr();
   virtual bool onAdd();
   virtual void onRemove();

   // ConsoleObject
   static void initPersistFields();
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
   virtual void addElement(RenderInst *inst);
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

   ProbeRenderInst* registerProbe();
   void unregisterProbe(U32 probeIdx);

   virtual void setProbeInfo(ProcessedMaterial *pmat,
	   const Material *mat,
	   const SceneData &sgData,
	   const SceneRenderState *state,
	   U32 pass,
	   GFXShaderConstBuffer *shaderConsts);

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
