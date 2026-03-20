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

#include <Jolt/Physics/Character/CharacterVirtual.h>

#ifdef Offset
// Restore the original macro after includes
#pragma pop_macro("Offset")
#endif

class JoltPlayer : public PhysicsPlayer, public JPH::CharacterContactListener
{
protected:
   JoltWorld* mWorld;
   SceneObject* mObject;
   JPH::Ref<JPH::CharacterVirtual> mCharacter;
   JPH::Vec3 mDesirdVelocity;
   F32 mMaxSlopeCos;
   F32 mStepHeight;
   /// Is the body participating in the physics simulation.
   bool mIsEnabled;

   using ContactSet = JPH::Array<JPH::CharacterVirtual::ContactKey>;
   ContactSet				mActiveContacts;
public:
   JoltPlayer();
   virtual ~JoltPlayer();

   // PhysicsObject
   PhysicsWorld* getWorld() override;
   void setTransform(const MatrixF& xfm) override;
   MatrixF& getTransform(MatrixF* outMatrix) override;
   Box3F getWorldBounds() override;
   void setSimulationEnabled(bool enabled) override;
   bool isSimulationEnabled() override { return mIsEnabled; }

   // Physics Player.
   void init(const char* type,
            const Point3F& size,
            F32 runSurfaceCos,
            F32 stepHeight,
            SceneObject* obj,
            PhysicsWorld* world) override;

   void preUpdate(U32 elapsedMs);

   Point3F move(const VectorF& displacement, CollisionList& outCol) override;
   void findContact(SceneObject** contactObject, VectorF* contactNormal, Vector<SceneObject*>* outOverlapObjects) const override;
   bool testSpacials(const Point3F& nPos, const Point3F& nSize) const override;
   void setSpacials(const Point3F& nPos, const Point3F& nSize) override;
   void enableCollision() override;
   void disableCollision() override;

private:

   class CharacterContactListener : public JPH::CharacterContactListener
   {
   public:
      CharacterContactListener(JoltPlayer* characterController)
         : mJoltPlayer(characterController) {
      }

      void OnContactAdded(const JPH::CharacterVirtual* inCharacter, const JPH::BodyID& inBodyID2, const JPH::SubShapeID& inSubShapeID2, JPH::Vec3Arg inContactPosition, JPH::Vec3Arg inContactNormal, JPH::CharacterContactSettings& ioSettings);

   private:
      JoltPlayer* mJoltPlayer;
   };
};


#endif
