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
   bool isDynamic() const override { return mIsDynamic; }
   PhysicsCollision* getColShape() override;
   void setSleepThreshold(F32 linear, F32 angular) override;
   void setDamping(F32 linear, F32 angular) override;
   void getState(PhysicsState* outState) override;
   F32 getMass() const override { return mMass; }
   Point3F getCMassPosition() const override;
   void setLinVelocity(const Point3F& vel) override;
   void setAngVelocity(const Point3F& vel) override;
   Point3F getLinVelocity() const override;
   Point3F getAngVelocity() const override;
   void setSleeping(bool sleeping) override;
   void setMaterial(F32 restitution,
      F32 friction,
      F32 staticFriction) override;
   void applyCorrection(const MatrixF& xfm) override;
   void applyImpulse(const Point3F& origin, const Point3F& force) override;
   void applyTorque(const Point3F& torque) override;
   void applyForce(const Point3F& force) override;
   void findContact(SceneObject** contactObject, VectorF* contactNormal, Vector<SceneObject*>* outOverlapObjects) const override;
   void moveKinematicTo(const MatrixF& xfm) override;

   bool isValid() override;
};

#endif // !_JOLTBODY_H_
