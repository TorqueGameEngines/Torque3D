#include "platform/platform.h"
#include "T3D/physics/jolt/joltBody.h"

#include "math/mBox.h"
#include "console/console.h"



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
   if (mBody && mWorld)
   {
      mWorld->getPhysicsSystem()->GetBodyInterface().RemoveBody(mBody->GetID());
   }

   SAFE_DELETE(mCenterOfMass);
   SAFE_DELETE(mInvCenterOfMass);

   mColShape = NULL;
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

   const JPH::Shape* joltShape = mColShape->getJoltShape();

   // Determine motion type
   JPH::EMotionType motionType = JPH::EMotionType::Static;
   JPH::ObjectLayer layer = Layers::NON_MOVING;

   if (bodyFlags & BF_KINEMATIC)
   {
      motionType = JPH::EMotionType::Kinematic;
      layer = Layers::MOVING;
   }
   else if (mass > 0.0f)
   {
      motionType = JPH::EMotionType::Dynamic;
      layer = Layers::MOVING;
   }

   // Compute center of the shape
   JPH::AABox bounds = joltShape->GetLocalBounds();
   JPH::Vec3 center = (bounds.mMin + bounds.mMax) * 0.5f;

   JPH::BodyCreationSettings settings(
      joltShape,
      JPH::Vec3(0, 0, 0),              // initial position
      JPH::Quat::sIdentity(),          // rotation
      motionType,
      layer
   );

   // Mass override if dynamic
   if (motionType == JPH::EMotionType::Dynamic)
      settings.mMassPropertiesOverride.mMass = mass;


   JPH::BodyInterface& bi = mWorld->getPhysicsSystem()->GetBodyInterface();
   JPH::Body* body = bi.CreateBody(settings);

   bi.AddBody(body->GetID(), JPH::EActivation::Activate);
   mBody = body;

   mUserData.setObject(obj);
   mUserData.setBody(this);
   mBody->SetUserData(reinterpret_cast<U64>(&mUserData));

   return true;
}

void JoltBody::setTransform(const MatrixF& xfm)
{
   if (!mBody)
      return;

   Point3F pos = xfm.getPosition();

   QuatF q(xfm);

   JPH::BodyInterface& bi = mWorld->getPhysicsSystem()->GetBodyInterface();

   bi.SetPositionAndRotation(
      mBody->GetID(),
      JPH::RVec3(pos.x, pos.y, pos.z),
      JPH::Quat(q.x, q.y, q.z, q.w),
      JPH::EActivation::Activate
   );
}

void JoltBody::applyCorrection(const MatrixF& xfm)
{
   setTransform(xfm);
}

MatrixF& JoltBody::getTransform(MatrixF* outMatrix)
{
   const JPH::RVec3 pos = mBody->GetPosition();
   const JPH::Quat rot = mBody->GetRotation();

   QuatF q(rot.GetX(), rot.GetY(), rot.GetZ(), rot.GetW());

   MatrixF mat(true);
   q.setMatrix(&mat);

   mat.setPosition(Point3F(pos.GetX(), pos.GetY(), pos.GetZ()));

   *outMatrix = mat;
   return *outMatrix;
}

void JoltBody::applyImpulse(const Point3F& origin, const Point3F& force)
{
   mBody->AddImpulse(toJolt(force), toJolt(origin));
}

void JoltBody::applyTorque(const Point3F& torque)
{
   mBody->AddTorque(toJolt(torque));
}

void JoltBody::applyForce(const Point3F& force)
{
   mBody->AddForce(toJolt(force));
}

void JoltBody::moveKinematicTo(const MatrixF& xfm)
{
   Point3F pos = xfm.getPosition();

   QuatF q(xfm);

   mWorld->getPhysicsSystem()->GetBodyInterface().MoveKinematic(
      mBody->GetID(),
      JPH::RVec3(pos.x, pos.y, pos.z),
      JPH::Quat(q.x, q.y, q.z, q.w),
      1.0f / 60.0f
   );
}

Box3F JoltBody::getWorldBounds()
{
   JPH::AABox box = mBody->GetWorldSpaceBounds();

   return Box3F(
      Point3F(box.mMin.GetX(), box.mMin.GetY(), box.mMin.GetZ()),
      Point3F(box.mMax.GetX(), box.mMax.GetY(), box.mMax.GetZ())
   );
}

void JoltBody::setSimulationEnabled(bool enabled)
{
   if (!mBody)
      return;

   JPH::BodyInterface& bi = mWorld->getPhysicsSystem()->GetBodyInterface();

   if (enabled)
      bi.AddBody(mBody->GetID(), JPH::EActivation::Activate);
   else
      bi.RemoveBody(mBody->GetID());

   mIsEnabled = enabled;
}

void JoltBody::setSleepThreshold(F32 linear, F32 angular)
{
   if (!mBody->IsDynamic())
      return;

   JPH::MotionProperties* mp = mBody->GetMotionProperties();

   /*mp->SetLinearSleepThreshold(linear);
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

   outState->linVelocity = getLinVelocity();
   outState->angVelocity = getAngVelocity();

}

Point3F JoltBody::getCMassPosition() const
{
   JPH::RVec3 p = mBody->GetCenterOfMassPosition();
   return Point3F(p.GetX(), p.GetY(), p.GetZ());
}

Point3F JoltBody::getLinVelocity() const
{
   return fromJolt(mBody->GetLinearVelocity());
}

Point3F JoltBody::getAngVelocity() const
{
   return fromJolt(mBody->GetAngularVelocity());
}

void JoltBody::setLinVelocity(const Point3F& vel)
{
   mBody->SetLinearVelocity(toJolt(vel));
}

void JoltBody::setAngVelocity(const Point3F& vel)
{
   mBody->SetAngularVelocity(toJolt(vel));
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
