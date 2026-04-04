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
   JPH::Vec3 mDesiredVelocity;
   F32 mMaxSlopeCos;
   F32 mStepHeight;
   F32 mOriginOffset;
   /// Is the body participating in the physics simulation.
   bool mIsEnabled;
   bool mAllowSliding;
   bool mCollisionEnabled;

   using ContactSet = JPH::Array<JPH::CharacterVirtual::ContactKey>;
   ContactSet				mActiveContacts;
public:
   JoltPlayer();
   virtual ~JoltPlayer();

   // PhysicsObject
   PhysicsWorld* getWorld() override { return mWorld; }
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

   void preUpdate(F32 dt);

   Point3F move(const VectorF& displacement, CollisionList& outCol) override;

   bool _recoverFromPenetration(JPH::RVec3& inOutPos);
   bool _sweep(JPH::RVec3& inOutPos, const JPH::Vec3& disp, CollisionList* outCol);
   void _stepForward(JPH::RVec3& inOutPos, const JPH::Vec3& displacement, CollisionList* outCol);

   void findContact(SceneObject** contactObject, VectorF* contactNormal, Vector<SceneObject*>* outOverlapObjects) const override;
   bool testSpacials(const Point3F& nPos, const Point3F& nSize) const override;
   void setSpacials(const Point3F& nPos, const Point3F& nSize) override;
   void enableCollision() override;
   void disableCollision() override;

   JPH::Ref<JPH::CharacterVirtual> getCharacter() { return mCharacter; }

protected:
   // Common function to be called when contacts are added/persisted
   void					OnContactCommon(const JPH::CharacterVirtual* inCharacter, const JPH::BodyID& inBodyID2, const JPH::SubShapeID& inSubShapeID2, JPH::RVec3Arg inContactPosition, JPH::Vec3Arg inContactNormal, JPH::CharacterContactSettings& ioSettings);
   void					OnCharacterContactCommon(const JPH::CharacterVirtual* inCharacter, const JPH::CharacterVirtual* inOtherCharacter, const JPH::SubShapeID& inSubShapeID2, JPH::RVec3Arg inContactPosition, JPH::Vec3Arg inContactNormal, JPH::CharacterContactSettings& ioSettings);


public: // contact listener
   /// Callback to adjust the velocity of a body as seen by the character. Can be adjusted to e.g. implement a conveyor belt or an inertial dampener system of a sci-fi space ship.
   virtual void			OnAdjustBodyVelocity(const JPH::CharacterVirtual* inCharacter, const JPH::Body& inBody2, JPH::Vec3& ioLinearVelocity, JPH::Vec3& ioAngularVelocity) override;

   // Called whenever the character collides with a body.
   virtual void			OnContactAdded(const JPH::CharacterVirtual* inCharacter, const JPH::BodyID& inBodyID2, const JPH::SubShapeID& inSubShapeID2, JPH::RVec3Arg inContactPosition, JPH::Vec3Arg inContactNormal, JPH::CharacterContactSettings& ioSettings) override;

   // Called whenever the character persists colliding with a body.
   virtual void			OnContactPersisted(const JPH::CharacterVirtual* inCharacter, const JPH::BodyID& inBodyID2, const JPH::SubShapeID& inSubShapeID2, JPH::RVec3Arg inContactPosition, JPH::Vec3Arg inContactNormal, JPH::CharacterContactSettings& ioSettings) override;

   // Called whenever the character loses contact with a body.
   virtual void			OnContactRemoved(const JPH::CharacterVirtual* inCharacter, const JPH::BodyID& inBodyID2, const JPH::SubShapeID& inSubShapeID2) override;

   // Called whenever the character collides with a virtual character.
   virtual void			OnCharacterContactAdded(const JPH::CharacterVirtual* inCharacter, const JPH::CharacterVirtual* inOtherCharacter, const JPH::SubShapeID& inSubShapeID2, JPH::RVec3Arg inContactPosition, JPH::Vec3Arg inContactNormal, JPH::CharacterContactSettings& ioSettings) override;

   // Called whenever the character persists colliding with a virtual character.
   virtual void			OnCharacterContactPersisted(const JPH::CharacterVirtual* inCharacter, const JPH::CharacterVirtual* inOtherCharacter, const JPH::SubShapeID& inSubShapeID2, JPH::RVec3Arg inContactPosition, JPH::Vec3Arg inContactNormal, JPH::CharacterContactSettings& ioSettings) override;

   // Called whenever the character loses contact with a virtual character.
   virtual void			OnCharacterContactRemoved(const JPH::CharacterVirtual* inCharacter, const JPH::CharacterID& inOtherCharacterID, const JPH::SubShapeID& inSubShapeID2) override;

   // Called whenever the character movement is solved and a constraint is hit. Allows the listener to override the resulting character velocity (e.g. by preventing sliding along certain surfaces).
   virtual void			OnContactSolve(const JPH::CharacterVirtual* inCharacter, const JPH::BodyID& inBodyID2, const JPH::SubShapeID& inSubShapeID2, JPH::RVec3Arg inContactPosition, JPH::Vec3Arg inContactNormal, JPH::Vec3Arg inContactVelocity, const JPH::PhysicsMaterial* inContactMaterial, JPH::Vec3Arg inCharacterVelocity, JPH::Vec3& ioNewCharacterVelocity) override;


};


#endif
