#ifndef _JOLTPLAYER_H_
#define _JOLTPLAYER_H_

#ifndef _T3D_PHYSICS_PHYSICSPLAYER_H_
#include "T3D/physics/physicsPlayer.h"
#endif
#ifndef _T3D_JOLT_PLUGIN_H_
#include "T3D/physics/jolt/joltPlugin.h"
#endif
#ifndef _JOLTWORLD_H_
#include "T3D/physics/jolt/joltWorld.h"
#endif

#ifdef Offset
#pragma push_macro("Offset")
#undef Offset
#endif

#include <Jolt/Physics/Character/Character.h>

#ifdef Offset
#pragma pop_macro("Offset")
#endif

class JoltPlayer : public PhysicsPlayer
{
protected:
   JoltWorld* mWorld;
   SceneObject* mObject;
   JPH::Ref<JPH::Character> mCharacter;
   JPH::Vec3                mDesiredVelocity;
   F32                      mMaxSlopeCos;
   F32                      mStepHeight;
   F32                      mOriginOffset;
   bool                     mIsEnabled;
   bool                     mAllowSliding;
   bool                     mCollisionEnabled;

public:
   JoltPlayer();
   virtual ~JoltPlayer();

   // PhysicsObject
   PhysicsWorld* getWorld() override { return mWorld; }
   void          setTransform(const MatrixF& xfm) override;
   MatrixF& getTransform(MatrixF* outMatrix) override;
   Box3F         getWorldBounds() override;
   void          setSimulationEnabled(bool enabled) override;
   bool          isSimulationEnabled() override { return mIsEnabled; }

   // PhysicsPlayer
   void init(const char* type, const Point3F& size, F32 runSurfaceCos,
      F32 stepHeight, SceneObject* obj, PhysicsWorld* world) override;

   void preUpdate(F32 dt);

   Point3F move(const VectorF& displacement, CollisionList& outCol) override;

   void findContact(SceneObject** contactObject, VectorF* contactNormal,
      Vector<SceneObject*>* outOverlapObjects) const override;
   bool testSpacials(const Point3F& nPos, const Point3F& nSize) const override;
   void setSpacials(const Point3F& nPos, const Point3F& nSize) override;
   void enableCollision()  override;
   void disableCollision() override;

   JPH::Ref<JPH::Character> getCharacter() { return mCharacter; }
};

#endif // _JOLTPLAYER_H_
