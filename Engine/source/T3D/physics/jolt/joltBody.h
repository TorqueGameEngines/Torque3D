#ifndef _JOLTBODY_H_
#define _JOLTBODY_H_

#ifndef _T3D_PHYSICS_PHYSICSBODY_H_
#include "T3D/physics/physicsBody.h"
#endif
#ifndef _REFBASE_H_
#include "core/util/refBase.h"
#endif
#ifndef _MMATRIX_H_
#include "math/mMatrix.h"
#endif

#ifndef _T3D_JOLT_PLUGIN_H_
#include "T3D/physics/jolt/joltPlugin.h"
#endif

#ifndef _JOLTWORLD_H_
#include "T3D/physics/jolt/joltWorld.h"
#endif

#ifndef _JOLTCOLLISION_H_
#include "T3D/physics/jolt/joltCollision.h"
#endif


class JoltBody : public PhysicsBody
{
protected:
   JPH::Body* mBody;

   JoltWorld* mWorld;
   JoltCollisionRef mColShape;

   ///
   F32 mMass;

   ///
   bool mIsDynamic;

   /// Is the body participating in the physics simulation.
   bool mIsEnabled;

   /// The center of mass offset used if the graphical
   /// transform is not at the mass center.
   MatrixF* mCenterOfMass;

   /// The inverse center of mass offset.
   MatrixF* mInvCenterOfMass;

public:
   JoltBody();
   virtual ~JoltBody();

   // PhysicsObject
   virtual PhysicsWorld* getWorld();
   virtual void setTransform(const MatrixF& xfm);
   virtual MatrixF& getTransform(MatrixF* outMatrix);
   virtual Box3F getWorldBounds();
   virtual void setSimulationEnabled(bool enabled);
   virtual bool isSimulationEnabled() { return mIsEnabled; }

   // PhysicsBody
   virtual bool init(PhysicsCollision* shape,
      F32 mass,
      U32 bodyFlags,
      SceneObject* obj,
      PhysicsWorld* world);
   virtual bool isDynamic() const { return mIsDynamic; }
   virtual PhysicsCollision* getColShape();
   virtual void setSleepThreshold(F32 linear, F32 angular);
   virtual void setDamping(F32 linear, F32 angular);
   virtual void getState(PhysicsState* outState);
   virtual F32 getMass() const { return mMass; }
   virtual Point3F getCMassPosition() const;
   virtual void setLinVelocity(const Point3F& vel);
   virtual void setAngVelocity(const Point3F& vel);
   virtual Point3F getLinVelocity() const;
   virtual Point3F getAngVelocity() const;
   virtual void setSleeping(bool sleeping);
   virtual void setMaterial(F32 restitution,
      F32 friction,
      F32 staticFriction);
   virtual void applyCorrection(const MatrixF& xfm);
   virtual void applyImpulse(const Point3F& origin, const Point3F& force);
   virtual void applyTorque(const Point3F& torque);
   virtual void applyForce(const Point3F& force);
   virtual void findContact(SceneObject** contactObject, VectorF* contactNormal, Vector<SceneObject*>* outOverlapObjects) const;
   virtual void moveKinematicTo(const MatrixF& xfm);

   virtual bool isValid() { return mBody != nullptr; }
};

#endif // !_JOLTBODY_H_
