#include "platform/platform.h"
#include "T3D/physics/jolt/joltPlayer.h"
#include "collision/collision.h"
#include "scene/sceneObject.h"

// we use capsule for player?
#ifdef Offset
#pragma push_macro("Offset")
#undef Offset
#endif

#include <Jolt/Physics/Collision/Shape/CapsuleShape.h>
#include <Jolt/Physics/Collision/Shape/RotatedTranslatedShape.h>
#include <Jolt/Physics/Collision/CollideShape.h>
#include <Jolt/Physics/Collision/CollisionCollectorImpl.h>

#ifdef Offset
    // Restore the original macro after includes
#pragma pop_macro("Offset")
#endif


JoltPlayer::JoltPlayer()
   : mCharacter(NULL),
   mObject(NULL),
   mWorld(NULL),
   mMaxSlopeCos(0.0f),
   mStepHeight(0.0f),
   mIsEnabled(false)
{
   mDesirdVelocity = JPH::Vec3::sZero();
}

JoltPlayer::~JoltPlayer()
{
   if (mWorld && mWorld->getProcessList())
   {
      mWorld->getProcessList()->postTickSignal().remove(this, &JoltPlayer::preUpdate);
   }
}

PhysicsWorld* JoltPlayer::getWorld()
{
   return mWorld;
}

void JoltPlayer::setTransform(const MatrixF& xfm)
{
   if (!mCharacter)
      return;

   Point3F pos = xfm.getPosition();
   QuatF q(xfm);


}

MatrixF& JoltPlayer::getTransform(MatrixF* outMatrix)
{
   const JPH::Mat44 trans = mCharacter->GetWorldTransform();
   QuatF qang = joltCast(trans.GetQuaternion());
   qang.setMatrix(outMatrix);
   outMatrix->setPosition(joltCast(trans.GetTranslation()));
   return *outMatrix;
}

Box3F JoltPlayer::getWorldBounds()
{
   JPH::AABox box = mCharacter->GetShape()->GetWorldSpaceBounds(mCharacter->GetCenterOfMassTransform(), JPH::Vec3::sOne());
   return Box3F(
      Point3F(joltCast(box.mMin)),
      Point3F(joltCast(box.mMax))
   );
}

void JoltPlayer::setSimulationEnabled(bool enabled)
{
   if (!mCharacter)
      return;

   JPH::BodyInterface& bi = mWorld->getPhysicsSystem()->GetBodyInterface();

   if (enabled)
      bi.AddBody(mCharacter->GetInnerBodyID(), JPH::EActivation::Activate);
   else
      bi.RemoveBody(mCharacter->GetInnerBodyID());

   mIsEnabled = enabled;
}

void JoltPlayer::init(const char* type, const Point3F& size, F32 runSurfaceCos, F32 stepHeight, SceneObject* obj, PhysicsWorld* world)
{
   if (!world || !obj)
      return;

   mObject = obj;

   mWorld = dynamic_cast<JoltWorld*>(world);
   if (!mWorld)
      return;

   F32 height = size.z;
   F32 radius = size.x * 0.5f;

   // Convert to Jolt capsule
   F32 halfHeight = (height * 0.5f) - radius;
   JPH::Vec3 offset(0, 0, halfHeight + radius);

  

   JPH::Quat rotFix = JPH::Quat::sRotation(JPH::Vec3::sAxisX(), JPH::DegreesToRadians(90.0f));
   JPH::Ref<JPH::Shape> shape = JPH::RotatedTranslatedShapeSettings( offset, rotFix, new JPH::CapsuleShape(halfHeight, radius) ).Create().Get();

   JPH::CharacterVirtualSettings settings;
   settings.mShape = shape;
   settings.mMass = 120.0f;
   settings.mInnerBodyShape = shape; // the same for now but inner shape would probably be something that actually follows the player geometry (ragdoll/hitboxes)
   settings.mMaxSlopeAngle = mAcos(runSurfaceCos);

   mUserData.setObject(obj);

   MatrixF objXfm = obj->getTransform();
   QuatF angPos(objXfm);
   Point3F pos;
   objXfm.getColumn(3, &pos);

   mCharacter = new JPH::CharacterVirtual(
      &settings,
      joltCast(pos),
      joltCast(angPos),
      reinterpret_cast<U64>(&mUserData), // set scene object to the user data, physicsuserdata does not have an interface for setplayer....
      mWorld->getPhysicsSystem()
      );

   mCharacter->SetUp(JPH::Vec3(0, 0, 1));
   mMaxSlopeCos = runSurfaceCos;
   mStepHeight = stepHeight;

   if (mWorld && mWorld->getProcessList())
   {
      mWorld->getProcessList()->postTickSignal().notify(this, &JoltPlayer::preUpdate, 1000.0f);
   }

}

void JoltPlayer::preUpdate(U32 elapsedMs)
{
   if (!mCharacter)
      return;

   const F32 dt = mWorld->getProcessList()->getLastInterpDelta();

   JPH::Vec3 up = mCharacter->GetUp();

   // --- Decompose current velocity ---
   JPH::Vec3 currentVel = mDesirdVelocity / dt;
   mDesirdVelocity = JPH::Vec3::sZero();

   JPH::Vec3 verticalVel = currentVel.Dot(up) * up;

   JPH::Vec3 groundVel = mCharacter->GetGroundVelocity();

   JPH::Vec3 newVel;

   bool movingTowardGround = (verticalVel - groundVel).Dot(up) < 0.1f;

   if (mCharacter->GetGroundState() == JPH::CharacterVirtual::EGroundState::OnGround
      && movingTowardGround)
   {
      newVel = groundVel;

      //if (mJump)
      //   newVel += up * currentVel;
   }
   else
   {
      newVel = verticalVel;
   }

   // Apply input
   newVel += currentVel;

   // --- Apply to character ---
   mCharacter->SetLinearVelocity(newVel);

   // --- Extended update ---
   JPH::CharacterVirtual::ExtendedUpdateSettings settings;
   settings.mWalkStairsStepUp = up * mStepHeight;
   settings.mStickToFloorStepDown = -up * mStepHeight;

   mCharacter->ExtendedUpdate(
      dt,
      mWorld->getPhysicsSystem()->GetGravity(),
      settings,
      mWorld->getPhysicsSystem()->GetDefaultBroadPhaseLayerFilter(Layers::MOVING),
      mWorld->getPhysicsSystem()->GetDefaultLayerFilter(Layers::MOVING),
      {},
      {},
      *mWorld->getTempAllocator()
   );
}

Point3F JoltPlayer::move(const VectorF& displacement, CollisionList& outCol)
{
   if (!mCharacter)
      return Point3F::Zero;

   JPH::Vec3 desiredVel(displacement.x, displacement.y, displacement.z);
   mDesirdVelocity += desiredVel;

   JPH::RVec3 pos = mCharacter->GetPosition();

   // Clear previous collisions
   outCol.clear();

   // Iterate over all active contacts after movement
   const auto& contacts = mCharacter->GetActiveContacts();
   for (const auto& contact : contacts)
   {
      if (!contact.mHadCollision)
         continue;

      Collision& col = outCol.increment();

      // Retrieve SceneObject from Jolt body user data
      SceneObject* obj = NULL;
      // Retrieve SceneObject from user data
      PhysicsUserData* userData = PhysicsUserData::cast((void*)contact.mUserData);
      obj = userData->getObject();

      if (!obj)
         continue;

      col.object = obj;
      col.point = joltCast(contact.mPosition);

      col.normal = joltCast(contact.mSurfaceNormal);
      col.normal.normalize();

      col.distance = contact.mDistance;

      // Optional: assign face/material if you have material mapping
      col.material = nullptr;
      col.generateTexCoord = false;
   }

   return Point3F(
      pos.GetX(),
      pos.GetY(),
      pos.GetZ()
   );
}

void JoltPlayer::findContact(SceneObject** contactObject, VectorF* contactNormal, Vector<SceneObject*>* outOverlapObjects) const
{
   if (!mCharacter || !mWorld)
      return;

   *contactObject = nullptr;
   if (contactNormal)
      *contactNormal = VectorF(0, 0, 1);

   if (!outOverlapObjects)
      return;

   outOverlapObjects->clear();

   // Get the contact points from the CharacterVirtual
   const auto& contacts = mCharacter->GetActiveContacts();
   for (const auto& contact : contacts)
   {
      // Only consider actual collisions
      if (!contact.mHadCollision)
         continue;

      SceneObject* obj = NULL;

      // Retrieve SceneObject from user data
      PhysicsUserData* userData = PhysicsUserData::cast((void*)contact.mUserData);
      obj = userData->getObject();

      if (!obj)
         continue;

      // Add to overlap list if not already added
      if (std::find(outOverlapObjects->begin(), outOverlapObjects->end(), obj) == outOverlapObjects->end())
         outOverlapObjects->push_back(obj);

      // Pick the first valid contact as main contact
      if (!*contactObject)
      {
         *contactObject = obj;
         if (contactNormal)
         {
            *contactNormal = joltCast(contact.mSurfaceNormal);
            contactNormal->normalize();
         }
      }
   }
}
bool JoltPlayer::testSpacials(const Point3F& nPos, const Point3F& nSize) const
{
   if (!mWorld || !mCharacter)
      return true; // assume free if no world

   F32 height = nSize.z;
   F32 radius = nSize.x * 0.5f;
   F32 halfHeight = (height * 0.5f) - radius;
   if (halfHeight < 0.01f) halfHeight = 0.01f;

   JPH::Vec3 offset(0, 0, halfHeight + radius);
   JPH::Quat rotFix = JPH::Quat::sRotation(JPH::Vec3::sAxisX(), JPH::DegreesToRadians(90.0f));
   JPH::Ref<JPH::Shape> testShape = JPH::RotatedTranslatedShapeSettings(offset, rotFix, new JPH::CapsuleShape(halfHeight, radius)).Create().Get();

   JPH::RMat44 transform = JPH::RMat44::sTranslation(JPH::RVec3(nPos.x, nPos.y, nPos.z));

   // Filters for collision
   JPH::DefaultBroadPhaseLayerFilter broadPhaseFilter(mWorld->getObjectVsBroadPhaseLayerFilter(), Layers::MOVING);
   JPH::DefaultObjectLayerFilter objectLayerFilter(mWorld->getObjectLayerPairFilter(), Layers::MOVING);
   JPH::BodyFilter bodyFilter;
   JPH::ShapeFilter shapeFilter;

   JPH::AnyHitCollisionCollector<JPH::CollideShapeCollector> collector;

   JPH::CollideShapeSettings settings;
   mWorld->getPhysicsSystem()->GetNarrowPhaseQuery().CollideShape(
      testShape,
      JPH::Vec3::sReplicate(1.0f), // scale
      transform,
      {},
      JPH::RVec3::sZero(),
      collector,
      broadPhaseFilter,
      objectLayerFilter,
      bodyFilter,
      shapeFilter
   );

   return !collector.HadHit();
}

void JoltPlayer::setSpacials(const Point3F& nPos, const Point3F& nSize)
{
   if (!mCharacter)
      return;

   F32 height = nSize.z;
   F32 radius = nSize.x * 0.5f;

   JPH::Ref<JPH::Shape> newShape = new JPH::CapsuleShape(0.5f * height, radius);

   const auto& system = mWorld->getPhysicsSystem();

   JPH::BodyFilter body_filter;
   JPH::ShapeFilter shape_filter;

   bool success = mCharacter->SetShape(
      newShape,
      0.05f,
      system->GetDefaultBroadPhaseLayerFilter(Layers::MOVING),
      system->GetDefaultLayerFilter(Layers::MOVING),
      body_filter,
      shape_filter,
      *mWorld->getTempAllocator()
   );

   if (success)
      mCharacter->SetInnerBodyShape(newShape);

}

void JoltPlayer::enableCollision()
{
   if (mCharacter)
      mCharacter->SetMaxStrength(10000.0f);
}

void JoltPlayer::disableCollision()
{
   if (mCharacter)
      mCharacter->SetMaxStrength(0.0f);
}

void JoltPlayer::CharacterContactListener::OnContactAdded(const JPH::CharacterVirtual* inCharacter, const JPH::BodyID& inBodyID2, const JPH::SubShapeID& inSubShapeID2, JPH::Vec3Arg inContactPosition, JPH::Vec3Arg inContactNormal, JPH::CharacterContactSettings& ioSettings)
{
}
