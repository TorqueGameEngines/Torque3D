#include "platform/platform.h"
#include "T3D/physics/jolt/joltBody.h"

#include "math/mBox.h"
#include "console/console.h"
#include "scene/sceneObject.h"

JoltBody::JoltBody()
   :mBody(NULL),
   mWorld(NULL),
   mMass(0.0f),
   mCenterOfMass(NULL),
   mInvCenterOfMass(NULL),
   mIsDynamic(false),
   mIsEnabled(false)

{
}

JoltBody::~JoltBody()
{
   SAFE_DELETE(mCenterOfMass);
   SAFE_DELETE(mInvCenterOfMass);

   mColShape = nullptr;

   if (!isValid())
      return;

   // User data must be cleared BEFORE the body is removed or destroyed.
   // DestroyBody returns the body to Jolt's internal pool; touching it
   // afterwards is use-after-free undefined behaviour.
   mBody->SetUserData(0);

   setSimulationEnabled(false); // removes body from the simulation

   JPH::BodyInterface& bi = mWorld->getPhysicsSystem()->GetBodyInterface();
   bi.DestroyBody(mBody->GetID());
   mBody = nullptr;
}

PhysicsWorld* JoltBody::getWorld()
{
   return mWorld;
}

PhysicsCollision* JoltBody::getColShape()
{
   return mColShape;
}

bool JoltBody::init(PhysicsCollision* shape, F32 mass, U32 bodyFlags, SceneObject* obj, PhysicsWorld* world)
{
   if (!shape || !world)
      return false;

   mWorld = dynamic_cast<JoltWorld*>(world);
   if (!mWorld)
      return false;

   mColShape = dynamic_cast<JoltCollision*>(shape);
   if (!mColShape)
      return false;

   mIsDynamic = false;

   const JPH::Shape* joltShape = mColShape->getJoltShape();

   // Determine motion type
   JPH::EMotionType motionType = JPH::EMotionType::Static;
   JPH::ObjectLayer layer = Layers::NON_MOVING;

   if (mass > 0.0f)
   {
      motionType = JPH::EMotionType::Dynamic;
      layer = Layers::MOVING;
   }
   else if (bodyFlags & BF_KINEMATIC)
   {
      motionType = JPH::EMotionType::Kinematic;
      layer = Layers::MOVING;
   }

   mMass = mass;

   MatrixF objXfm = obj->getTransform();

   QuatF angPos(objXfm);
   Point3F pos;
   objXfm.getColumn(3, &pos);

   JPH::BodyCreationSettings settings(
      joltShape,
      joltCast(pos),              // initial position
      joltCast(angPos),          // rotation
      motionType,
      layer
   );

   // Mass override if dynamic
   if (motionType == JPH::EMotionType::Dynamic)
   {
      settings.mOverrideMassProperties = JPH::EOverrideMassProperties::CalculateInertia;
      settings.mMassPropertiesOverride.mMass = mass;
      settings.mMaxLinearVelocity = 1000.0f; // stops an assert, this is torques upper limit, jolts is 500.0f by default.
      mIsDynamic = true;
   }

   JPH::BodyInterface& bi = mWorld->getPhysicsSystem()->GetBodyInterface();
   JPH::Body* body = bi.CreateBody(settings);
   bi.AddBody(body->GetID(), JPH::EActivation::Activate);

   if (bodyFlags & BF_TRIGGER)
   {
      body->SetIsSensor(true);
   }

   mBody = body;

   getUserData().setObject(obj);
   getUserData().setBody(this);
   mBody->SetUserData(reinterpret_cast<U64>(&mUserData));

   const JPH::Mat44 trans = mBody->GetCenterOfMassTransform();
   MatrixF comMat;
   QuatF qang = joltCast(trans.GetQuaternion());
   qang.setMatrix(&comMat);
   comMat.setPosition(joltCast(trans.GetTranslation()));

   mCenterOfMass = new MatrixF(comMat);
   mInvCenterOfMass = new MatrixF(*mCenterOfMass);
   mInvCenterOfMass->inverse();

   return true;
}

void JoltBody::setTransform(const MatrixF& xfm)
{
   if (!isValid())
      return;

   Point3F pos = xfm.getPosition();
   QuatF q(xfm);
   JPH::BodyInterface& bi = mWorld->getPhysicsSystem()->GetBodyInterface();

   bi.SetPositionAndRotation(
      mBody->GetID(),
      joltCast(pos),
      joltCast(q),
      mIsEnabled ? JPH::EActivation::Activate : JPH::EActivation::DontActivate
   );

   if (isDynamic())
   {
      // ResetMotion (clears accumulated forces/torques) is a Body method only,
      // so acquire a write lock. Velocity is cleared through the thread-safe interface.
      {
         JPH::BodyLockWrite lock(mWorld->getPhysicsSystem()->GetBodyLockInterface(), mBody->GetID());
         if (lock.Succeeded())
            lock.GetBody().ResetMotion();
      }
      bi.SetLinearVelocity(mBody->GetID(), JPH::Vec3::sZero());
      bi.SetAngularVelocity(mBody->GetID(), JPH::Vec3::sZero());
   }
}

void JoltBody::applyCorrection(const MatrixF& xfm)
{
   setTransform(xfm);
}

MatrixF& JoltBody::getTransform(MatrixF* outMatrix)
{
   const JPH::Mat44 trans = mBody->GetWorldTransform();
   *outMatrix = joltCast(trans);

   return *outMatrix;
}

void JoltBody::applyImpulse(const Point3F& origin, const Point3F& force)
{
   if (!isValid())
      return;
   JPH::BodyInterface& bi = mWorld->getPhysicsSystem()->GetBodyInterface();
   bi.AddImpulse(mBody->GetID(), joltCast(force), joltCast(origin));
}

void JoltBody::applyTorque(const Point3F& torque)
{
   if (!isValid())
      return;
   JPH::BodyInterface& bi = mWorld->getPhysicsSystem()->GetBodyInterface();
   bi.AddTorque(mBody->GetID(), joltCast(torque));
}

void JoltBody::applyForce(const Point3F& force)
{
   if (!isValid())
      return;
   JPH::BodyInterface& bi = mWorld->getPhysicsSystem()->GetBodyInterface();
   bi.AddForce(mBody->GetID(), joltCast(force));
}

void JoltBody::moveKinematicTo(const MatrixF& xfm)
{
   Point3F pos = xfm.getPosition();
   QuatF angPos(xfm);
   mWorld->getPhysicsSystem()->GetBodyInterface().MoveKinematic(
      mBody->GetID(),
      joltCast(pos),
      joltCast(angPos),
      TickSec
   );
}

bool JoltBody::isValid()
{
   return mBody != nullptr && mWorld != NULL;
}

Box3F JoltBody::getWorldBounds()
{
   JPH::AABox box = mBody->GetWorldSpaceBounds();

   return Box3F(
      Point3F(joltCast(box.mMin)),
      Point3F(joltCast(box.mMax))
   );
}

void JoltBody::setSimulationEnabled(bool enabled)
{
   if (!isValid())
      return;

   JPH::BodyInterface& bi = mWorld->getPhysicsSystem()->GetBodyInterface();

   if (enabled)
   {
      if (bi.IsAdded(mBody->GetID()))
      {
         bi.ActivateBody(mBody->GetID());
      }
      else
      {
         bi.AddBody(mBody->GetID(), JPH::EActivation::Activate);
      }
   }
   else
   {
      bi.DeactivateBody(mBody->GetID());
      bi.RemoveBody(mBody->GetID());
   }

   mIsEnabled = enabled;
}

void JoltBody::setSleepThreshold(F32 linear, F32 angular)
{
   if (!mBody->IsDynamic())
      return;

   JPH::MotionProperties* mp = mBody->GetMotionProperties();

   /* mp->SetLinearSleepThreshold(linear);
    mp->SetAngularSleepThreshold(angular);*/
}

void JoltBody::setDamping(F32 linear, F32 angular)
{
   if (!mBody->IsDynamic())
      return;

   JPH::MotionProperties* mp = mBody->GetMotionProperties();

   mp->SetLinearDamping(linear);
   mp->SetAngularDamping(angular);
}

void JoltBody::setSleeping(bool sleeping)
{
   if (!isValid())
      return;

   if (!mIsEnabled)
      return;

   JPH::BodyInterface& bi = mWorld->getPhysicsSystem()->GetBodyInterface();

   if (sleeping)
      bi.DeactivateBody(mBody->GetID());
   else
      bi.ActivateBody(mBody->GetID());
}

void JoltBody::setMaterial(F32 restitution, F32 friction, F32 staticFriction)
{
   mBody->SetRestitution(restitution);
   mBody->SetFriction(friction);
}

void JoltBody::getState(PhysicsState* outState)
{
   if (!outState)
      return;

   const JPH::RMat44 worldXfm = mBody->GetWorldTransform();

   outState->position = joltCast(worldXfm.GetTranslation());
   outState->orientation = joltCast(mBody->GetRotation());
   outState->linVelocity = getLinVelocity();
   outState->angVelocity = getAngVelocity();

   if (mBody->IsDynamic())
   {
      const JPH::MotionProperties* mp = mBody->GetMotionProperties();

      // Linear momentum = m * v
      F32 mass = mp->GetInverseMass() > 0.0f ? 1.0f / mp->GetInverseMass() : 0.0f;
      outState->momentum = outState->linVelocity * mass;
      outState->angularMomentum = outState->angVelocity;
   }
   else
   {
      outState->momentum.set(0, 0, 0);
      outState->angularMomentum.set(0, 0, 0);
   }

   // Sleeping?
   outState->sleeping = !mBody->IsActive();
}

Point3F JoltBody::getCMassPosition() const
{
   JPH::RVec3 p = mBody->GetCenterOfMassPosition();
   return Point3F(joltCast(p));
}

Point3F JoltBody::getLinVelocity() const
{
   return joltCast(mBody->GetLinearVelocity());
}

Point3F JoltBody::getAngVelocity() const
{
   return joltCast(mBody->GetAngularVelocity());
}

void JoltBody::setLinVelocity(const Point3F& vel)
{
   if (!isValid())
      return;

   JPH::BodyInterface& bi = mWorld->getPhysicsSystem()->GetBodyInterface();

   if (!bi.IsAdded(mBody->GetID()))
      return;

   bi.SetLinearVelocity(mBody->GetID(), joltCast(vel));
}

void JoltBody::setAngVelocity(const Point3F& vel)
{
   if (!isValid())
      return;

   JPH::BodyInterface& bi = mWorld->getPhysicsSystem()->GetBodyInterface();

   if (!bi.IsAdded(mBody->GetID()))
      return;

   bi.SetAngularVelocity(mBody->GetID(), joltCast(vel));
}

void JoltBody::findContact(SceneObject** contactObject,
   VectorF* contactNormal,
   Vector<SceneObject*>* outOverlapObjects) const
{
   if (contactObject)
      *contactObject = nullptr;

   if (contactNormal)
      *contactNormal = VectorF::Zero;
}
