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

#include "core/util/SystemInterfaceList.h"

#ifndef _MATERIALS_PROCESSEDSHADERMATERIAL_H_
#include "materials/processedShaderMaterial.h"
#endif
#ifndef _POSTEFFECTCOMMON_H_
#include "postFx/postEffectCommon.h"
#endif

struct ProbeRenderInst : public SystemInterface<ProbeRenderInst>
{
   LinearColorF mAmbient;

   MatrixF mTransform;

   F32 mRadius;
   F32 mIntensity;

   bool mDirty;

   Box3F mBounds;
   Point3F mProbePosOffset;

   GFXCubemapHandle mCubemap;

   GFXCubemapHandle mIrradianceCubemap;

   GFXTexHandle *mBRDFTexture;

   /// The priority of this light used for
   /// light and shadow scoring.
   F32 mPriority;

   /// A temporary which holds the score used
   /// when prioritizing lights for rendering.
   F32 mScore;

   bool mIsSkylight;

   /// Whether to render debugging visualizations
   /// for this light.
   bool mDebugRender;

   GFXPrimitiveBufferHandle primBuffer;
   GFXVertexBufferHandle<GFXVertexPC> vertBuffer;
   U32 numPrims;
   U32 numVerts;
   Vector< U32 > numIndicesForPoly;

   enum ProbeShapeType
   {
      Sphere = 0,            ///< Sphere shaped
      Box = 1,               ///< Box-based shape
   };

   ProbeShapeType mProbeShapeType;

   //Spherical Harmonics data
   LinearColorF mSHTerms[9];
   F32 mSHConstants[5];

public:

   ProbeRenderInst();
   ~ProbeRenderInst();

   // Copies data passed in from light
   void set(const ProbeRenderInst *probeInfo);

   // Accessors
   const MatrixF& getTransform() const { return mTransform; }
   void setTransform(const MatrixF &xfm) { mTransform = xfm; }

   Point3F getPosition() const { return mTransform.getPosition(); }
   void setPosition(const Point3F &pos) { mTransform.setPosition(pos); }

   VectorF getDirection() const { return mTransform.getForwardVector(); }
   void setDirection(const VectorF &val);

   const LinearColorF& getAmbient() const { return mAmbient; }
   void setAmbient(const LinearColorF &val) { mAmbient = val; }

   void setPriority(F32 priority) { mPriority = priority; }
   F32 getPriority() const { return mPriority; }

   void setScore(F32 score) { mScore = score; }
   F32 getScore() const { return mScore; }

   bool isDebugRenderingEnabled() const { return mDebugRender; }
   void enableDebugRendering(bool value) { mDebugRender = value; }

   // Builds the world to light view projection used for
   // shadow texture and cookie lookups.
   void getWorldToLightProj(MatrixF *outMatrix) const;

   void clear();
};

struct ProbeShaderConstants
{
   bool mInit;

   GFXShaderRef mShader;

   GFXShaderConstHandle* mProbeParamsSC;

   //Reflection Probes
   GFXShaderConstHandle *mProbePositionSC;
   GFXShaderConstHandle *mProbeRadiusSC;
   GFXShaderConstHandle *mProbeBoxMinSC;
   GFXShaderConstHandle *mProbeBoxMaxSC;
   GFXShaderConstHandle *mProbeIsSphereSC;
   GFXShaderConstHandle *mProbeLocalPosSC;
   GFXShaderConstHandle *mProbeCubemapSC;
   GFXShaderConstHandle *mProbeCountSC;

   ProbeShaderConstants();
   ~ProbeShaderConstants();

   void init(GFXShader* buffer);

   void _onShaderReload();
};

typedef Map<GFXShader*, ProbeShaderConstants*> ProbeConstantMap;

class ReflectProbeMatInstance : public MatInstance
{
   typedef MatInstance Parent;
protected:
   MaterialParameterHandle * mProbeParamsSC;
   bool mInternalPass;

   GFXStateBlockRef mProjectionState;

   ProcessedShaderMaterial* mShaderMat;

public:
   ReflectProbeMatInstance(Material &mat) : Parent(mat), mProbeParamsSC(NULL), mInternalPass(false), mProjectionState(NULL) {}

   virtual bool init(const FeatureSet &features, const GFXVertexFormat *vertexFormat);
   virtual bool setupPass(SceneRenderState *state, const SceneData &sgData);

   ProcessedShaderMaterial* getProcessedShaderMaterial() { return mShaderMat; }
};

//**************************************************************************
// RenderObjectMgr
//**************************************************************************
class RenderProbeMgr : public RenderBinManager
{
   typedef RenderBinManager Parent;

   struct ReflectProbeMaterialInfo
   {
      ReflectProbeMatInstance *matInstance;

      // { zNear, zFar, 1/zNear, 1/zFar }
      MaterialParameterHandle *zNearFarInvNearFar;

      // Far frustum plane (World Space)
      MaterialParameterHandle *farPlane;

      // Far frustum plane (View Space)
      MaterialParameterHandle *vsFarPlane;

      // -dot( farPlane, eyePos )
      MaterialParameterHandle *negFarPlaneDotEye;

      // Light Parameters
      MaterialParameterHandle *probeLSPos;
      MaterialParameterHandle *probeWSPos;
      MaterialParameterHandle *attenuation;
      MaterialParameterHandle *radius;

      MaterialParameterHandle *useCubemap;
      MaterialParameterHandle *cubemap;
      MaterialParameterHandle *cubeMips;

      MaterialParameterHandle *eyePosWorld;
      MaterialParameterHandle *bbMin;
      MaterialParameterHandle *bbMax;

      MaterialParameterHandle *useSphereMode;

      MaterialParameterHandle *shTerms[9];
      MaterialParameterHandle *shConsts[5];

      MaterialParameterHandle *probeCount;

      ReflectProbeMaterialInfo(const String &matName, const GFXVertexFormat *vertexFormat);

      virtual ~ReflectProbeMaterialInfo();


      void setViewParameters(const F32 zNear,
         const F32 zFar,
         const Point3F &eyePos,
         const PlaneF &farPlane,
         const PlaneF &_vsFarPlane);

      void setProbeParameters(const ProbeRenderInst *probe, const SceneRenderState* renderState, const MatrixF &worldViewOnly);
   };

   enum SpecialProbeTypesEnum
   {
      SkylightProbeType,
      SpecialProbeTypesCount
   };

   Vector<U32> mRegisteredProbes;

   ReflectProbeMaterialInfo* mReflectProbeMaterial;

   /// The scene graph the light manager is associated with.
   SceneManager *mSceneManager;

   ProbeConstantMap mConstantLookup;
   GFXShaderRef mLastShader;
   ProbeShaderConstants* mLastConstants;

protected:

   /// The current active light manager.
   static RenderProbeMgr *smProbeManager;

   GFXVertexBufferHandle<GFXVertexPC> mFarFrustumQuadVerts;

   /// This helper function sets the shader constansts
   /// for the stock 4 light forward lighting code.
   void _update4ProbeConsts(const SceneData &sgData,
      MatrixSet &matSet,
      GFXShaderConstHandle *probePositionSC,
      GFXShaderConstHandle *probeRadiusSC,
      GFXShaderConstHandle *probeBoxMinSC,
      GFXShaderConstHandle *probeBoxMaxSC,
      GFXShaderConstHandle *probeCubemapSC,
      GFXShaderConstHandle *probeIsSphereSC,
      GFXShaderConstHandle *probeLocalPosSC,
      GFXShaderConstBuffer *shaderConsts);

      GFXTextureObject * mBrdfTexture;
public:
   RenderProbeMgr();
   RenderProbeMgr(RenderInstType riType, F32 renderOrder, F32 processAddOrder);

   // RenderBinMgr
   void _setupPerFrameParameters(const SceneRenderState *state);
   virtual void addElement(RenderInst *inst);
   virtual void render(SceneRenderState * state);

   virtual void setProbeInfo(ProcessedMaterial *pmat,
      const Material *mat,
      const SceneData &sgData,
      const SceneRenderState *state,
      U32 pass,
      GFXShaderConstBuffer *shaderConsts);
   ProbeShaderConstants* getProbeShaderConstants(GFXShaderConstBuffer* buffer);

   // ConsoleObject
   static void initPersistFields();
   DECLARE_CONOBJECT(RenderProbeMgr);

   /// Returns the active LM.
   static inline RenderProbeMgr* getProbeManager();

   ReflectProbeMaterialInfo* getReflectProbeMaterial();

   void registerProbe(U32 probeIdx);

   // Returns the scene manager passed at activation.
   SceneManager* getSceneManager() { return mSceneManager; }

   void setSceneManager(SceneManager* sceneManager) { mSceneManager = sceneManager; }

   /// Debug rendering
   static bool smRenderReflectionProbes;
};

RenderProbeMgr* RenderProbeMgr::getProbeManager()
{
   if (smProbeManager == nullptr)
   {
      RenderProbeMgr* probeManager = new RenderProbeMgr();

      if (gClientSceneGraph != nullptr)
      {
         probeManager->setSceneManager(gClientSceneGraph);
         smProbeManager = probeManager;
      }
      else
      {
         delete probeManager;
      }
   }

   return smProbeManager;
}

#define PROBEMGR RenderProbeMgr::getProbeManager()

#endif // RENDER_PROBE_MGR_H