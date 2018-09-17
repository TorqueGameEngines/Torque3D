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

#ifndef PROBEMANAGER_H
#define PROBEMANAGER_H

#ifndef _TORQUE_STRING_H_
#include "core/util/str.h"
#endif
#ifndef _TSIGNAL_H_
#include "core/util/tSignal.h"
#endif
#ifndef _LIGHTINFO_H_
#include "lighting/lightInfo.h"
#endif
#ifndef _LIGHTQUERY_H_
#include "lighting/lightQuery.h"
#endif
#ifndef _MATRIXSET_H_
#include "math/util/matrixSet.h"
#endif
#ifndef _CUBEMAPDATA_H_
#include "gfx/sim/cubemapData.h"
#endif

class SimObject;
class ProbeManager;
class Material;
class ProcessedMaterial;
class SceneManager;
struct SceneData;
class Point3F;
class AvailableSLInterfaces;
class SceneObject;
class GFXShaderConstBuffer;
class GFXShaderConstHandle;
class ShaderConstHandles;
class SceneRenderState;
class RenderDeferredMgr;
class Frustum;

struct ProbeInfo
{
   LinearColorF mAmbient;

   MatrixF mTransform;

   F32 mRadius;
   F32 mIntensity;

   Box3F mBounds;

   GFXCubemapHandle *mCubemap;

   GFXCubemapHandle *mIrradianceCubemap;

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

   //GFXPrimitiveBufferHandle primBuffer;
   //GFXVertexBufferHandle<GFXVertexPC> vertBuffer;
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

   ProbeInfo();
   ~ProbeInfo();

   // Copies data passed in from another probe
   void set(const ProbeInfo *probe);

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

class ProbeInfoList : public Vector<ProbeInfo*>
{
public:
   void registerProbe(ProbeInfo *probe);
   void unregisterProbe(ProbeInfo *probe);
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

   ProbeShaderConstants();
   ~ProbeShaderConstants();

   void init(GFXShader* buffer);

   void _onShaderReload();
};

typedef Map<GFXShader*, ProbeShaderConstants*> ProbeConstantMap;

class ProbeManager
{
public:

   enum SpecialProbeTypesEnum
   {
      SkylightProbeType,
      SpecialProbeTypesCount
   };

   ProbeManager();

   ~ProbeManager();

   ///
   static void initProbeFields();

   /// 
   static ProbeInfo* createProbeInfo(ProbeInfo* light = NULL);

   /// The light manager activation signal.
   static Signal<void(const char*,bool)> smActivateSignal;

   /// Returns the active LM.
   static inline ProbeManager* getProbeManager();

   // Returns the scene manager passed at activation.
   SceneManager* getSceneManager() { return mSceneManager; }

   // Called when the lighting manager should become active
   virtual void activate( SceneManager *sceneManager );

   // Called when we don't want the light manager active (should clean up)
   virtual void deactivate();

   // Returns the active scene lighting interface for this light manager.  
   virtual AvailableSLInterfaces* getSceneLightingInterface();

   // Returns a "default" light info that callers should not free.  Used for instances where we don't actually care about 
   // the light (for example, setting default data for SceneData)
   virtual ProbeInfo* getDefaultLight();

   /// Returns the special light or the default light if useDefault is true.
   /// @see getDefaultLight
   virtual ProbeInfo* getSpecialProbe(SpecialProbeTypesEnum type,
                                       bool useDefault = true );

   /// Set a special light type.
   virtual void setSpecialProbe(SpecialProbeTypesEnum type, ProbeInfo *light );

   void registerSkylight(ProbeInfo *probe, SimObject *obj);

   // registered before scene traversal...
   virtual void registerProbe(ProbeInfo *light, SimObject *obj );
   virtual void unregisterProbe(ProbeInfo *light );

   virtual void registerProbes( const Frustum *frustum, bool staticlighting );
   virtual void unregisterAllProbes();

   /// Returns all unsorted and un-scored lights (both global and local).
   void getAllUnsortedProbes( Vector<ProbeInfo*> *list ) const;

   /// Sets shader constants / textures for light infos
   virtual void setProbeInfo( ProcessedMaterial *pmat, 
                              const Material *mat, 
                              const SceneData &sgData, 
                              const SceneRenderState *state,
                              U32 pass, 
                              GFXShaderConstBuffer *shaderConsts );

   /// Allows us to set textures during the Material::setTextureStage call, return true if we've done work.
   virtual bool setTextureStage( const SceneData &sgData, 
                                 const U32 currTexFlag, 
                                 const U32 textureSlot, 
                                 GFXShaderConstBuffer *shaderConsts, 
                                 ShaderConstHandles *handles );
protected:

   /// The current active light manager.
   static ProbeManager *smProbeManager;

   /// Find the pre-pass render bin on the scene's default render pass.
   RenderDeferredMgr* _findDeferredRenderBin();

public:
   ProbeShaderConstants* getProbeShaderConstants(GFXShaderConstBuffer* buffer);
protected:
   /// This helper function sets the shader constansts
   /// for the stock 4 light forward lighting code.
   void _update4ProbeConsts( const SceneData &sgData,
                                    MatrixSet &matSet,
                                    GFXShaderConstHandle *probePositionSC,
                                    GFXShaderConstHandle *probeRadiusSC,
                                    GFXShaderConstHandle *probeBoxMinSC,
                                    GFXShaderConstHandle *probeBoxMaxSC,
                                    GFXShaderConstHandle *probeCubemapSC,
                                    GFXShaderConstHandle *probeIsSphereSC,
                                    GFXShaderConstHandle *probeLocalPosSC,
                                    GFXShaderConstBuffer *shaderConsts );

   /// A dummy default light used when no lights
   /// happen to be registered with the manager.
   ProbeInfo *mDefaultProbe;
  
   /// The list of global registered lights which is
   /// initialized before the scene is rendered.
   ProbeInfoList mRegisteredProbes;

   ProbeInfo* mSkylight;

   /// The registered special light list.
   ProbeInfo *mSpecialProbes[SpecialProbeTypesCount];

   /// The root culling position used for
   /// special sun light placement.
   /// @see setSpecialLight
   Point3F mCullPos;

   ///
   //virtual void _initLightFields();

   /// The scene graph the light manager is associated with.
   SceneManager *mSceneManager;

   ProbeConstantMap mConstantLookup;

   GFXShaderRef mLastShader;

   ProbeShaderConstants* mLastConstants;
};

ProbeManager* ProbeManager::getProbeManager()
{
	if (smProbeManager == nullptr)
	{
		ProbeManager* probeManager = new ProbeManager();

		if (gClientSceneGraph != nullptr)
		{
			probeManager->activate(gClientSceneGraph);
		}
		else
		{
			delete probeManager;
		}
	}

	return smProbeManager;
}

/// Returns the current active light manager.
#define PROBEMGR ProbeManager::getProbeManager()

#endif // PROBEMANAGER_H
