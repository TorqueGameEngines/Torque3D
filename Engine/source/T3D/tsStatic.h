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

//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~//
// Arcane-FX for MIT Licensed Open Source version of Torque 3D from GarageGames
// Copyright (C) 2015 Faust Logic, Inc.
//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~//

#ifndef _TSSTATIC_H_
#define _TSSTATIC_H_

#ifndef _SCENEOBJECT_H_
#include "scene/sceneObject.h"
#endif
#ifndef _CONVEX_H_
#include "collision/convex.h"
#endif
#ifndef __RESOURCE_H__
#include "core/resource.h"
#endif
#ifndef _NETSTRINGTABLE_H_
#include "sim/netStringTable.h"
#endif
#ifndef _TSSHAPE_H_
#include "ts/tsShape.h"
#endif

#ifndef _REFLECTOR_H_
#include "scene/reflector.h"
#endif

#ifndef _COLLADA_UTILS_H_
#include "ts/collada/colladaUtils.h"
#endif

#ifndef _ASSET_PTR_H_
#include "assets/assetPtr.h"
#endif 
#ifndef SHAPEASSET_H
#include "T3D/assets/ShapeAsset.h"
#endif 

class TSShapeInstance;
class TSThread;
class TSStatic;
class PhysicsBody;
struct ObjectRenderInst;


class TSStaticPolysoupConvex : public Convex
{
   typedef Convex Parent;
   friend class TSMesh;

public:
   TSStaticPolysoupConvex();
   ~TSStaticPolysoupConvex() {};

public:
   Box3F                box;
   Point3F              verts[4];
   PlaneF               normal;
   S32                  idx;
   TSMesh* mesh;

   static SceneObject* smCurObject;

public:

   // Returns the bounding box in world coordinates
   Box3F getBoundingBox() const;
   Box3F getBoundingBox(const MatrixF& mat, const Point3F& scale) const;

   void getFeatures(const MatrixF& mat, const VectorF& n, ConvexFeature* cf);

   // This returns a list of convex faces to collide against
   void getPolyList(AbstractPolyList* list);

   // This returns the furthest point from the input vector
   Point3F support(const VectorF& v) const;
};


/// A simple mesh shape with optional ambient animation.
class TSStatic : public SceneObject
{
   typedef SceneObject Parent;

   static U32 smUniqueIdentifier;

   enum MaskBits
   {
      TransformMask = Parent::NextFreeMask << 0,
      AdvancedStaticOptionsMask = Parent::NextFreeMask << 1,
      UpdateCollisionMask = Parent::NextFreeMask << 2,
      SkinMask = Parent::NextFreeMask << 3,
      MaterialMask = Parent::NextFreeMask << 4,
      NextFreeMask = Parent::NextFreeMask << 5
   };

public:
   void setAlphaFade(bool enable, F32 start, F32 end, bool inverse)
   {
      mUseAlphaFade = enable;
      mAlphaFadeStart = start;
      mAlphaFadeEnd = end;
      mInvertAlphaFade = inverse;
   }

   /// The different types of mesh data types
   enum MeshType
   {
      None = 0,            ///< No mesh
      Bounds = 1,          ///< Bounding box of the shape
      CollisionMesh = 2,   ///< Specifically designated collision meshes
      VisibleMesh = 3      ///< Rendered mesh polygons
   };

protected:
   bool mUseAlphaFade;
   F32  mAlphaFadeStart;
   F32  mAlphaFadeEnd;
   F32  mAlphaFade;
   bool mInvertAlphaFade;

   struct matMap
   {
      MaterialAsset* matAsset;
      String assetId;
      U32 slot;
   };

   Vector<matMap>  mChangingMaterials;
   Vector<matMap>  mMaterials;

   bool onAdd();
   void onRemove();

   // Collision
   void prepCollision();
   bool castRay(const Point3F& start, const Point3F& end, RayInfo* info);
   bool castRayRendered(const Point3F& start, const Point3F& end, RayInfo* info);
   bool buildPolyList(PolyListContext context, AbstractPolyList* polyList, const Box3F& box, const SphereF& sphere);
   bool buildExportPolyList(ColladaUtils::ExportData* exportData, const Box3F& box, const SphereF&);
   void buildConvex(const Box3F& box, Convex* convex);

   bool _createShape();

   void _updatePhysics();

   void _renderNormals(ObjectRenderInst* ri, SceneRenderState* state, BaseMatInstance* overrideMat);

   void _onResourceChanged(const Torque::Path& path);
   void onShapeChanged();

   // ProcessObject
   virtual void processTick(const Move* move);
   virtual void interpolateTick(F32 delta);
   virtual void advanceTime(F32 dt);

   virtual void onDynamicModified(const char* slotName, const char* newValue);

   /// Start or stop processing ticks depending on our state.
   void _updateShouldTick();

   String cubeDescName;
   U32 cubeDescId;
   ReflectorDesc* reflectorDesc;
   CubeReflector mCubeReflector;

protected:

   Convex* mConvexList;

   DECLARE_SHAPEASSET(TSStatic, Shape, onShapeChanged);
   DECLARE_ASSET_NET_SETGET(TSStatic, Shape, AdvancedStaticOptionsMask);

   U32               mShapeHash;
   Vector<S32> mCollisionDetails;
   Vector<S32> mLOSDetails;
   TSShapeInstance* mShapeInstance;

   NetStringHandle   mSkinNameHandle;
   String            mAppliedSkinName;

   bool              mPlayAmbient;
   TSThread*         mAmbientThread;
   F32               mAnimOffset;
   F32               mAnimSpeed;
   /// The type of mesh data to return for collision queries.
   MeshType mCollisionType;

   /// The type of mesh data to return for decal polylist queries.
   MeshType mDecalType;

   bool mAllowPlayerStep;

   /// If true each submesh within the TSShape is culled 
   /// against the object space frustum.
   bool mMeshCulling;

   /// If true the shape is sorted by the origin of the
   /// model instead of the nearest point of the bounds.
   bool mUseOriginSort;

   PhysicsBody* mPhysicsRep;

   LinearColorF mOverrideColor;

   // Debug stuff
   F32 mRenderNormalScalar;
   S32 mForceDetail;

public:

   TSStatic();
   ~TSStatic();

   DECLARE_CONOBJECT(TSStatic);
   static void initPersistFields();
   static void consoleInit();
   static bool _setFieldSkin(void* object, const char* index, const char* data);
   static const char* _getFieldSkin(void* object, const char* data);

   // Skinning
   void setSkinName(const char* name);
   void reSkin();

   // NetObject
   U32 packUpdate(NetConnection* conn, U32 mask, BitStream* stream);
   void unpackUpdate(NetConnection* conn, BitStream* stream);

   // SceneObject
   void setTransform(const MatrixF& mat);
   void onScaleChanged();
   void prepRenderImage(SceneRenderState* state);
   void inspectPostApply();
   virtual void onMount(SceneObject* obj, S32 node);
   virtual void onUnmount(SceneObject* obj, S32 node);

   /// The type of mesh data use for collision queries.
   MeshType getCollisionType() const { return mCollisionType; }

   bool allowPlayerStep() const { return mAllowPlayerStep; }

   TSShapeInstance* getShapeInstance() const { return mShapeInstance; }

   U32 getNumDetails();

   const Vector<S32>& getCollisionDetails() const { return mCollisionDetails; }

   const Vector<S32>& getLOSDetails() const { return mLOSDetails; }
   bool hasAnim() { return mAmbientThread != NULL; }

   virtual void onInspect(GuiInspector*);

   void updateMaterials();

   bool isAnimated() { return mPlayAmbient; }
   void getNodeTransform(const char *nodeName, const MatrixF &xfm, MatrixF *outMat);

   virtual void getUtilizedAssets(Vector<StringTableEntry>* usedAssetsList);

private:
   virtual void   onStaticModified(const char* slotName, const char* newValue = NULL);
protected:
   Vector<S32>    mDecalDetails;
   Vector<S32>* mDecalDetailsPtr;

   ///Indicates if all statics should utilize the distance-based object fadeout logic
   static bool    smUseStaticObjectFade;

   ///Distance at which static object fading begins if smUseStaticObjectFade is on
   static F32 smStaticObjectFadeStart;

   ///Distance at which static object fading should have fully faded if smUseStaticObjectFade is on
   static F32 smStaticObjectFadeEnd;

   ///Size of object where if the bounds is at or bigger than this, it will be ignored in the smUseStaticObjectFade logic. Useful for very large, distance-important objects
   static F32 smStaticObjectUnfadeableSize;
public:
   bool           mIgnoreZodiacs;
   bool           mHasGradients;
   bool           mInvertGradientRange;
   Point2F        mGradientRangeUser;
   Point2F        mGradientRange;
private:
   void           set_special_typing();
   virtual void setSelectionFlags(U8 flags);
};

typedef TSStatic::MeshType TSMeshType;
DefineEnumType(TSMeshType);

#endif // _H_TSSTATIC

