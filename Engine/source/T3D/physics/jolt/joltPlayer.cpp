#include "platform/platform.h"
#include "T3D/physics/jolt/joltPlayer.h"
#include "collision/collision.h"
#include "scene/sceneObject.h"
#include "T3D/player.h"

// we use capsule for player?
#ifdef Offset
#pragma push_macro("Offset")
#undef Offset
#endif

#include <Jolt/Physics/Collision/ShapeCast.h>
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
   mOriginOffset(0.0f),
   mAllowSliding(false),
   mCollisionEnabled(true),
   mIsEnabled(false)
{
   mDesiredVelocity = JPH::Vec3::sZero();
}

JoltPlayer::~JoltPlayer()
{
   if (mCharacter)
   {
      // Remove the inner body from the physics world before the character is released.
      // Setting mCharacter=nullptr first would make disableCollision() a no-op.
      if (mCollisionEnabled)
         disableCollision();

      mCharacter->SetUserData(0);
      mCharacter = nullptr;
   }

   mIsEnabled = false;
}

void JoltPlayer::setTransform(const MatrixF& xfm)
{
   if (!mCharacter)
      return;

   JPH::Mat44 mat = joltCast(xfm);

   mCharacter->SetPosition(mat.GetTranslation());
   mCharacter->SetRotation(mat.GetQuaternion());
}

MatrixF& JoltPlayer::getTransform(MatrixF* outMatrix)
{
   const JPH::Mat44 trans = mCharacter->GetWorldTransform();
   *outMatrix = joltCast(trans);
   return *outMatrix;
}

Box3F JoltPlayer::getWorldBounds()
{
   JPH::AABox box = mCharacter->GetShape()->GetWorldSpaceBounds(mCharacter->GetCenterOfMassTransform(), JPH::Vec3::sOne());
   return Box3F(
      Point3F(joltCast(box.mMin)),
      Point3F(joltCast(box.mMax)));
}

void JoltPlayer::setSimulationEnabled(bool enabled)
{
   if (!mCharacter || !mWorld)
      return;

   mIsEnabled = enabled;
}

void JoltPlayer::init(const char* type, const Point3F& size, F32 runSurfaceCos, F32 stepHeight, SceneObject* obj, PhysicsWorld* world)
{
   if (!obj || !world)
      return;

   mObject = obj;

   mWorld = dynamic_cast<JoltWorld*>(world);
   if (!mWorld)
      return;

   mStepHeight = stepHeight;
   mMaxSlopeCos = runSurfaceCos;

   F32 radius = mMax(size.x, size.y) * 0.5f;
   F32 height = size.z;// +0.5f;
   height = mMax(0.01f, height);

   mOriginOffset = (0.5f * height);// +radius;
   JPH::Quat rotFix = JPH::Quat::sRotation(JPH::Vec3::sAxisX(), JPH::DegreesToRadians(90.0f)); // zup 
   JPH::Ref<JPH::Shape> shape = JPH::RotatedTranslatedShapeSettings(JPH::Vec3(0, 0, mOriginOffset), rotFix, new JPH::CapsuleShape(0.5f * height, radius)).Create().Get();
   JPH::Ref<JPH::Shape> inner_shape = JPH::RotatedTranslatedShapeSettings(JPH::Vec3(0, 0, mOriginOffset), rotFix, new JPH::CapsuleShape(0.5f * 0.9f * height, 0.9f * radius)).Create().Get();

   JPH::Ref<JPH::CharacterVirtualSettings> settings = new JPH::CharacterVirtualSettings();
   Con::printf("JoltPlayer::init - maxSlopeAngle: %f degrees", mRadToDeg(mAcos(runSurfaceCos)));
   settings->mMaxSlopeAngle = mAcos(runSurfaceCos);
   settings->mMaxStrength = 100.0f;
   settings->mShape = shape;
   settings->mMass = obj->getMass();
   settings->mBackFaceMode = JPH::EBackFaceMode::IgnoreBackFaces;
   settings->mCharacterPadding = 0.05f;
   settings->mPenetrationRecoverySpeed = 1.0f;
   settings->mMaxNumHits = 64;
   settings->mPredictiveContactDistance = 0.05f;
   settings->mSupportingVolume = JPH::Plane(JPH::Vec3::sAxisZ(), -(radius));
   settings->mEnhancedInternalEdgeRemoval = true;
   settings->mInnerBodyShape = inner_shape;
   settings->mInnerBodyLayer = Layers::CHARACTER;

   MatrixF objXfm = obj->getTransform();
   QuatF angPos(objXfm);
   Point3F pos;
   objXfm.getColumn(3, &pos);

   mCharacter = new JPH::CharacterVirtual(
      settings,
      joltCast(pos),
      joltCast(angPos),
      0,
      mWorld->getPhysicsSystem()
   );

   getUserData().setObject(obj);
   //getUserData().setBody(this);

   mCharacter->SetUserData(reinterpret_cast<U64>(&mUserData));
   mCharacter->SetUp(JPH::Vec3::sAxisZ());
   mCharacter->SetListener(this);

   setSimulationEnabled(true);
}

void JoltPlayer::preUpdate(F32 dt)
{
   // Intentionally empty. Ground velocity is refreshed inside move() on every
   // call. If the calling code ever starts calling preUpdate() before move(),
   // the refresh in move() will simply be a no-op on the same-frame data.
}

Point3F JoltPlayer::move(const VectorF& displacement, CollisionList& outCol)
{
   if (!mCharacter || !mWorld)
      return Point3F::Zero;

   if (!mIsEnabled)
      return joltCast(mCharacter->GetPosition());

   const F32 dt = TickSec;
   JPH::Vec3 velocity = joltCast(displacement) / dt;

   const auto& system = mWorld->getPhysicsSystem();
   const JPH::Vec3 up = mCharacter->GetUp();

   mCharacter->UpdateGroundVelocity();

   const JPH::CharacterVirtual::EGroundState groundState = mCharacter->GetGroundState();
   const bool isOnGround = groundState == JPH::CharacterVirtual::EGroundState::OnGround;

   if (isOnGround && !mCharacter->IsSlopeTooSteep(mCharacter->GetGroundNormal()))
   {
      JPH::Vec3 horizontalVel(velocity.GetX(), velocity.GetY(), 0.0f);
      mAllowSliding = horizontalVel.Length() > 0.01f;

      if (velocity.GetZ() < 0.05f)
         velocity.SetZ(0.00f);

      JPH::Vec3 groundVel = mCharacter->GetGroundVelocity();
      // Threshold raised to filter static-surface floating-point residuals.
      if (groundVel.LengthSq() > 0.01f)
      {
         // Always carry horizontal platform motion (conveyor belts, sliding floors).
         velocity.SetX(velocity.GetX() + groundVel.GetX());
         velocity.SetY(velocity.GetY() + groundVel.GetY());
         // Only carry Z from platforms that are meaningfully moving upward (elevators).
         // Static surfaces can produce tiny Z residuals that fight gravity resolution.
         if (groundVel.GetZ() > 0.05f)
            velocity.SetZ(velocity.GetZ() + groundVel.GetZ());
      }
   }
   else
   {
      mAllowSliding = true;
   }

   mCharacter->SetLinearVelocity(velocity);

   //----------------------------------------
   // Substep
   //----------------------------------------
   const U32 iterations = 3;
   const F32 subDt = dt / iterations;

   // Build settings once outside the loop — they don't change per-substep.
   JPH::CharacterVirtual::ExtendedUpdateSettings extSettings;
   extSettings.mWalkStairsStepUp = JPH::Vec3(0, 0, mStepHeight);
   extSettings.mStickToFloorStepDown = JPH::Vec3(0, 0, -mStepHeight);
   extSettings.mWalkStairsCosAngleForwardContact = mMaxSlopeCos;

   for (U32 i = 0; i < iterations; ++i)
   {
      mCharacter->ExtendedUpdate(
         subDt,
         system->GetGravity(),
         extSettings,
         system->GetDefaultBroadPhaseLayerFilter(Layers::CHARACTER),
         system->GetDefaultLayerFilter(Layers::CHARACTER),
         {},
         {},
         *mWorld->getTempAllocator()
      );
   }

   //----------------------------------------
   // Fill collision list from active contacts
   //----------------------------------------
   const JPH::CharacterVirtual::ContactList& contacts = mCharacter->GetActiveContacts();

   for (const JPH::CharacterVirtual::Contact& c : contacts)
   {
      if (!c.mHadCollision)
         continue;

      if (outCol.getCount() >= CollisionList::MaxCollisions)
         break;

      JPH::BodyLockRead lock(system->GetBodyLockInterface(), c.mBodyB);
      if (!lock.Succeeded())
         continue;

      const JPH::Body& body = lock.GetBody();
      PhysicsUserData* ud = reinterpret_cast<PhysicsUserData*>(body.GetUserData());

      Collision& col = outCol.increment();
      col.point = joltCast(c.mPosition);
      col.normal = joltCast(c.mContactNormal);
      col.object = ud ? ud->getObject() : nullptr;
      col.material = nullptr;       // material lookup not available yet
      col.distance = c.mDistance;
      col.face = 0;
      col.faceDot = mDot(col.normal, VectorF(0.f, 0.f, 1.f));
   }

   // If on ground, ensure the ground body is represented even if it
   // wasn't caught in the contact list (CharacterVirtual separates these)
   if (mCharacter->GetGroundState() == JPH::CharacterVirtual::EGroundState::OnGround
      && outCol.getCount() < CollisionList::MaxCollisions)
   {
      JPH::BodyLockRead lock(system->GetBodyLockInterface(), mCharacter->GetGroundBodyID());
      if (lock.Succeeded())
      {
         const JPH::Body& body = lock.GetBody();
         PhysicsUserData* ud = reinterpret_cast<PhysicsUserData*>(body.GetUserData());

         // Avoid duplicating if already added via active contacts
         SceneObject* groundObj = ud ? ud->getObject() : nullptr;
         bool alreadyPresent = false;
         for (S32 i = 0; i < outCol.getCount(); ++i)
         {
            if (outCol[i].object == groundObj)
            {
               alreadyPresent = true;
               break;
            }
         }

         if (!alreadyPresent)
         {
            Collision& col = outCol.increment();
            col.point = joltCast(mCharacter->GetGroundPosition());
            col.normal = joltCast(mCharacter->GetGroundNormal());
            col.object = groundObj;
            col.material = nullptr;
            col.distance = 0.f;
            col.faceDot = mDot(col.normal, VectorF(0.f, 0.f, 1.f));
         }
      }
   }

   //----------------------------------------
   // Final position
   //----------------------------------------
   Point3F finalPos = joltCast(mCharacter->GetPosition());
   return finalPos;
}

void JoltPlayer::findContact(SceneObject** contactObject, VectorF* contactNormal, Vector<SceneObject*>* outOverlapObjects) const
{
   if (!mCharacter || !mIsEnabled)
      return;

   const bool isOnGround = mCharacter->GetGroundState() == JPH::CharacterVirtual::EGroundState::OnGround;
   F32 bestDot = -1.0f;
   const JPH::Vec3 up = mCharacter->GetUp();

   for (const JPH::CharacterVirtual::Contact& c : mCharacter->GetActiveContacts())
   {
      if (c.mBodyB.IsInvalid())
         continue;

      if (c.mIsSensorB)
      {
         JPH::BodyLockRead lock(mWorld->getPhysicsSystem()->GetBodyLockInterface(), c.mBodyB);
         if (!lock.Succeeded())
            continue;

         const JPH::Body& body = lock.GetBody();
         PhysicsUserData* ud = (PhysicsUserData*)body.GetUserData();
         if (!ud)
            continue;

         SceneObject* obj = ud->getObject();
         if (obj && !outOverlapObjects->contains(obj))
            outOverlapObjects->push_back(obj);
         continue; // do not use for physical contact normal
      }


      if (c.mHadCollision)
      {
         JPH::BodyLockRead lock(mWorld->getPhysicsSystem()->GetBodyLockInterface(), c.mBodyB);
         if (!lock.Succeeded())
            continue;

         const JPH::Body& body = lock.GetBody();
         PhysicsUserData* ud = (PhysicsUserData*)body.GetUserData();
         if (!ud)
            continue;

         VectorF normal = joltCast(c.mContactNormal);
         F32 dot = mDot(normal, VectorF(0, 0, 1));
         if (dot > bestDot)
         {
            bestDot = dot;
            *contactObject = ud->getObject();
            *contactNormal = normal;
         }
         SceneObject* obj = ud->getObject();
         if (obj && !outOverlapObjects->contains(obj))
            outOverlapObjects->push_back(obj);
      }
   }

   if (isOnGround)
   {
      JPH::BodyLockRead lock(mWorld->getPhysicsSystem()->GetBodyLockInterface(), mCharacter->GetGroundBodyID());
      if (!lock.Succeeded())
         return;

      const JPH::Body& body = lock.GetBody();
      PhysicsUserData* ud = (PhysicsUserData*)body.GetUserData();
      if (!ud)
         return;

      *contactObject = ud->getObject();
      *contactNormal = joltCast(mCharacter->GetGroundNormal());
   }
}


bool JoltPlayer::testSpacials(const Point3F& nPos, const Point3F& nSize) const
{
   return true;

   //if (!mCharacter || !mWorld)
   //   return false;

   //const auto& system = mWorld->getPhysicsSystem();

   //JPH::BodyFilter body_filter;
   //JPH::ShapeFilter shape_filter;

   //F32 radius = getMax(nSize.x, nSize.y) * 0.5f;
   //F32 height = nSize.z - (radius * 2.0f);

   //F32 halfHeight = 0.5f * height;
   //JPH::Vec3 shapeTranslation(0, 0, halfHeight + radius);

   //JPH::Quat rotFix = JPH::Quat::sRotation(JPH::Vec3::sAxisX(), JPH::DegreesToRadians(90.0f)); // zup 
   //JPH::Ref<JPH::Shape> shape = JPH::RotatedTranslatedShapeSettings(shapeTranslation, rotFix, new JPH::CapsuleShape(halfHeight, radius)).Create().Get();

   //const float maxPenetration = 0.05f; // tweak tolerance

   //return mCharacter->SetShape(
   //   shape,
   //   maxPenetration,
   //   system->GetDefaultBroadPhaseLayerFilter(Layers::MOVING),
   //   system->GetDefaultLayerFilter(Layers::MOVING),
   //   body_filter,
   //   shape_filter,
   //   *mWorld->getTempAllocator());

}

void JoltPlayer::setSpacials(const Point3F& nPos, const Point3F& nSize)
{
   if (!mCharacter || !mWorld)
      return;

   const auto& system = mWorld->getPhysicsSystem();

   JPH::BodyFilter body_filter;
   JPH::ShapeFilter shape_filter;

   F32 radius = mMax(nSize.x, nSize.y) * 0.5f;
   F32 height = nSize.z;// +0.5f;
   height = mMax(0.01f, height);

   mOriginOffset = (0.5f * height);// +radius;
   JPH::Quat rotFix = JPH::Quat::sRotation(JPH::Vec3::sAxisX(), JPH::DegreesToRadians(90.0f)); // zup 
   JPH::Ref<JPH::Shape> shape = JPH::RotatedTranslatedShapeSettings(JPH::Vec3(0, 0, mOriginOffset), rotFix, new JPH::CapsuleShape(0.5f * height, radius)).Create().Get();
   JPH::Ref<JPH::Shape> inner_shape = JPH::RotatedTranslatedShapeSettings(JPH::Vec3(0, 0, mOriginOffset), rotFix, new JPH::CapsuleShape(0.5f * 0.9f * height, 0.9f * radius)).Create().Get();

   const float maxPenetration = 0.05f; // tweak tolerance

   if (mCharacter->SetShape(
      shape,
      maxPenetration,
      system->GetDefaultBroadPhaseLayerFilter(Layers::CHARACTER),
      system->GetDefaultLayerFilter(Layers::CHARACTER),
      body_filter,
      shape_filter,
      *mWorld->getTempAllocator())
      )
   {
      mCharacter->SetInnerBodyShape(inner_shape);
   }
}

void JoltPlayer::enableCollision()
{
   if (!mCharacter || !mWorld || mCollisionEnabled)
      return;

   mCollisionEnabled = true;

   JPH::BodyID innerBodyID = mCharacter->GetInnerBodyID();
   if (innerBodyID.IsInvalid())
      return;

   mWorld->getPhysicsSystem()->GetBodyInterface().AddBody(
      innerBodyID,
      JPH::EActivation::Activate
   );
}

void JoltPlayer::disableCollision()
{
   if (!mCharacter || !mWorld || !mCollisionEnabled)
      return;

   mCollisionEnabled = false;

   JPH::BodyID innerBodyID = mCharacter->GetInnerBodyID();
   if (innerBodyID.IsInvalid())
      return;

   mWorld->getPhysicsSystem()->GetBodyInterface().RemoveBody(innerBodyID);
}

void JoltPlayer::OnContactCommon(const JPH::CharacterVirtual* inCharacter, const JPH::BodyID& inBodyID2, const JPH::SubShapeID& inSubShapeID2, JPH::RVec3Arg inContactPosition, JPH::Vec3Arg inContactNormal, JPH::CharacterContactSettings& ioSettings)
{
   if (inCharacter == mCharacter)
   {
      if (ioSettings.mCanPushCharacter && mWorld->getPhysicsSystem()->GetBodyInterface().GetMotionType(inBodyID2) != JPH::EMotionType::Static)
      {
         mAllowSliding = true;
      }
   }
}

void JoltPlayer::OnCharacterContactCommon(const JPH::CharacterVirtual* inCharacter, const JPH::CharacterVirtual* inOtherCharacter, const JPH::SubShapeID& inSubShapeID2, JPH::RVec3Arg inContactPosition, JPH::Vec3Arg inContactNormal, JPH::CharacterContactSettings& ioSettings)
{
   if (inCharacter == mCharacter && ioSettings.mCanPushCharacter)
      mAllowSliding = true;
}

//------------------------------------------------------------------
// Character Contact Listener Callbacks
//------------------------------------------------------------------

void JoltPlayer::OnAdjustBodyVelocity(const JPH::CharacterVirtual* inCharacter, const JPH::Body& inBody2, JPH::Vec3& ioLinearVelocity, JPH::Vec3& ioAngularVelocity)
{
}

bool JoltPlayer::OnContactValidate(const JPH::CharacterVirtual* inCharacter, const JPH::BodyID& inBodyID2, const JPH::SubShapeID& inSubShapeID2)
{
   if (inCharacter != mCharacter)
      return true;

   JPH::BodyLockRead lock(mWorld->getPhysicsSystem()->GetBodyLockInterface(), inBodyID2);
   if (lock.Succeeded() && lock.GetBody().IsSensor())
      return false;

   return true;
}

void JoltPlayer::OnContactAdded(const JPH::CharacterVirtual* inCharacter, const JPH::BodyID& inBodyID2, const JPH::SubShapeID& inSubShapeID2, JPH::RVec3Arg inContactPosition, JPH::Vec3Arg inContactNormal, JPH::CharacterContactSettings& ioSettings)
{
   if (inCharacter != mCharacter)
      return;

   // Sensors are already rejected by OnContactValidate so this callback will
   // never fire for them. No sensor check needed here.
   JPH::CharacterVirtual::ContactKey c(inBodyID2, inSubShapeID2);
   if (std::find(mActiveContacts.begin(), mActiveContacts.end(), c) != mActiveContacts.end())
   {
      Con::warnf("JoltPlayer::OnContactAdded - contact already present, skipping duplicate");
      return;
   }
   mActiveContacts.push_back(c);

   OnContactCommon(inCharacter, inBodyID2, inSubShapeID2, inContactPosition, inContactNormal, ioSettings);
}

void JoltPlayer::OnContactPersisted(const JPH::CharacterVirtual* inCharacter, const JPH::BodyID& inBodyID2, const JPH::SubShapeID& inSubShapeID2, JPH::RVec3Arg inContactPosition, JPH::Vec3Arg inContactNormal, JPH::CharacterContactSettings& ioSettings)
{
   if (inCharacter != mCharacter)
      return;

   // Sensors are already rejected by OnContactValidate — this callback will
   // not fire for them.
   JPH::CharacterVirtual::ContactKey c(inBodyID2, inSubShapeID2);
   if (std::find(mActiveContacts.begin(), mActiveContacts.end(), c) == mActiveContacts.end())
   {
      Con::warnf("JoltPlayer::OnContactPersisted - contact not in set, inserting as new");
      mActiveContacts.push_back(c);
   }

   OnContactCommon(inCharacter, inBodyID2, inSubShapeID2, inContactPosition, inContactNormal, ioSettings);
}

void JoltPlayer::OnContactRemoved(const JPH::CharacterVirtual* inCharacter, const JPH::BodyID& inBodyID2, const JPH::SubShapeID& inSubShapeID2)
{
   if (inCharacter == mCharacter)
   {
      JPH::CharacterVirtual::ContactKey c(inBodyID2, inSubShapeID2);
      ContactSet::iterator it = std::find(mActiveContacts.begin(), mActiveContacts.end(), c);
      if (it == mActiveContacts.end())
      {
         // Can occur when the contact was never added due to an earlier ordering anomaly.
         Con::warnf("JoltPlayer::OnContactRemoved - contact not found, ignoring");
         return;
      }
      mActiveContacts.erase(it);
   }
}

void JoltPlayer::OnCharacterContactAdded(const JPH::CharacterVirtual* inCharacter, const JPH::CharacterVirtual* inOtherCharacter, const JPH::SubShapeID& inSubShapeID2, JPH::RVec3Arg inContactPosition, JPH::Vec3Arg inContactNormal, JPH::CharacterContactSettings& ioSettings)
{
}

void JoltPlayer::OnCharacterContactPersisted(const JPH::CharacterVirtual* inCharacter, const JPH::CharacterVirtual* inOtherCharacter, const JPH::SubShapeID& inSubShapeID2, JPH::RVec3Arg inContactPosition, JPH::Vec3Arg inContactNormal, JPH::CharacterContactSettings& ioSettings)
{
}

void JoltPlayer::OnCharacterContactRemoved(const JPH::CharacterVirtual* inCharacter, const JPH::CharacterID& inOtherCharacterID, const JPH::SubShapeID& inSubShapeID2)
{
}

void JoltPlayer::OnContactSolve(const JPH::CharacterVirtual* inCharacter, const JPH::BodyID& inBodyID2, const JPH::SubShapeID& inSubShapeID2, JPH::RVec3Arg inContactPosition, JPH::Vec3Arg inContactNormal, JPH::Vec3Arg inContactVelocity, const JPH::PhysicsMaterial* inContactMaterial, JPH::Vec3Arg inCharacterVelocity, JPH::Vec3& ioNewCharacterVelocity)
{
   if (inCharacter != mCharacter)
      return;

   // When not sliding and contact surface isn't moving and slope is walkable,
   // zero out velocity to prevent micro-jitter from solver residuals
   if (!mAllowSliding && inContactVelocity.IsNearZero() && !inCharacter->IsSlopeTooSteep(inContactNormal))
      ioNewCharacterVelocity = JPH::Vec3::sZero();
}
