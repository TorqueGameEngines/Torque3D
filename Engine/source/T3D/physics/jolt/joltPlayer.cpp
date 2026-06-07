#include "platform/platform.h"
#include "T3D/physics/jolt/joltPlayer.h"
#include "collision/collision.h"
#include "scene/sceneObject.h"
#include "T3D/player.h"

#ifdef Offset
#pragma push_macro("Offset")
#undef Offset
#endif

#include <Jolt/Physics/Collision/Shape/CapsuleShape.h>
#include <Jolt/Physics/Collision/CollideShape.h>
#include <Jolt/Physics/Collision/Shape/RotatedTranslatedShape.h>
#include <Jolt/Physics/Collision/BroadPhase/BroadPhaseLayer.h>

#ifdef Offset
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
      mWorld->getPhysicsSystem()->GetBodyInterface().SetUserData(
         mCharacter->GetBodyID(), 0);

      if (mCollisionEnabled)
         disableCollision();

      mCharacter = NULL;
   }
   mIsEnabled = false;
}

void JoltPlayer::setTransform(const MatrixF& xfm)
{
   if (!mCharacter)
      return;

   const Point3F pos = xfm.getPosition();
   const QuatF   rot(xfm);

   // Character::SetPosition / SetRotation go through BodyInterface internally.
   mCharacter->SetPosition(joltCast(pos), JPH::EActivation::Activate);
   mCharacter->SetRotation(joltCast(rot), JPH::EActivation::Activate);
}

MatrixF& JoltPlayer::getTransform(MatrixF* outMatrix)
{
   *outMatrix = joltCast(mCharacter->GetWorldTransform());
   return *outMatrix;
}

Box3F JoltPlayer::getWorldBounds()
{
   const JPH::AABox box = mCharacter->GetShape()->GetWorldSpaceBounds(
      mCharacter->GetWorldTransform(), JPH::Vec3::sOne());
   return Box3F(Point3F(joltCast(box.mMin)), Point3F(joltCast(box.mMax)));
}

void JoltPlayer::setSimulationEnabled(bool enabled)
{
   if (!mCharacter || !mWorld)
      return;
   mIsEnabled = enabled;
}

void JoltPlayer::init(const char* type, const Point3F& size, F32 runSurfaceCos,
   F32 stepHeight, SceneObject* obj, PhysicsWorld* world)
{
   if (!obj || !world)
      return;

   mObject = obj;
   mWorld = dynamic_cast<JoltWorld*>(world);
   if (!mWorld)
      return;

   mStepHeight = stepHeight;
   mMaxSlopeCos = runSurfaceCos;

   const F32 radius = mMax(size.x, size.y) * 0.5f;
   F32 height = mMax(0.01f, size.z);

   mOriginOffset = (0.5f * height);

   // Capsule centred at mOriginOffset along Z so the bottom of the capsule
   // sits at world Z = 0 (feet).  rotFix converts Y-axis capsule → Z-up.
   const JPH::Quat rotFix = JPH::Quat::sRotation(
      JPH::Vec3::sAxisX(), JPH::DegreesToRadians(90.0f));

   JPH::Ref<JPH::Shape> shape =
      JPH::RotatedTranslatedShapeSettings(
         JPH::Vec3(0.0f, 0.0f, mOriginOffset), rotFix,
         new JPH::CapsuleShape((0.5f * height) - radius, radius))
      .Create().Get();

   JPH::Ref<JPH::CharacterSettings> settings = new JPH::CharacterSettings();

   settings->mUp = JPH::Vec3::sAxisZ();          // Z-up world
   settings->mMaxSlopeAngle = mAcos(runSurfaceCos);
   settings->mShape = shape;
   settings->mMass = obj->getMass();
   settings->mFriction = 0.5f;
   settings->mLayer = Layers::CHARACTER;

   // Accept contacts that touch the hemisphere at the bottom of the capsule
   settings->mSupportingVolume = JPH::Plane(JPH::Vec3::sAxisZ(), -radius);

   // Torque's Player already applies gravity via the displacement passed to
   // move().  Suppress Jolt's built-in gravity here so it is not applied twice.
   settings->mGravityFactor = 0.0f;

   Con::printf("JoltPlayer::init - maxSlopeAngle: %f degrees",
      mRadToDeg(mAcos(runSurfaceCos)));

   // --- Create Character ---
   MatrixF objXfm = obj->getTransform();
   QuatF   angPos(objXfm);
   Point3F pos;
   objXfm.getColumn(3, &pos);

   mCharacter = new JPH::Character(
      settings,
      joltCast(pos),
      joltCast(angPos),
      reinterpret_cast<U64>(&mUserData),
      mWorld->getPhysicsSystem()
   );

   // Ensure Z is treated as up (may also be set via CharacterBaseSettings but
   // calling SetUp explicitly guarantees it regardless of library version).
   mCharacter->SetUp(JPH::Vec3::sAxisZ());

   getUserData().setObject(obj);

   mCharacter->AddToPhysicsSystem(JPH::EActivation::Activate);
   setSimulationEnabled(true);
}

void JoltPlayer::preUpdate(F32 dt)
{
   if (!mCharacter || !mIsEnabled)
      return;

   static const float cCollisionTolerance = 0.05f;
   mCharacter->PostSimulation(cCollisionTolerance);
}

Point3F JoltPlayer::move(const VectorF& displacement, CollisionList& outCol)
{
   if (!mCharacter || !mWorld)
      return Point3F::Zero;

   if (!mIsEnabled)
      return joltCast(mCharacter->GetPosition());

   // If preUpdate() was not called by the engine, call PostSimulation here.
   // (In architectures where preUpdate IS called this is a no-op because
   //  PostSimulation is idempotent between physics steps.)
   static const float cCollisionTolerance = 0.05f;
   mCharacter->PostSimulation(cCollisionTolerance);

   const F32       dt = TickSec;
   JPH::Vec3       velocity = joltCast(displacement) / dt;
   const JPH::Vec3 up = mCharacter->GetUp();

   const JPH::Character::EGroundState groundState = mCharacter->GetGroundState();
   const bool isOnGround =
      groundState == JPH::Character::EGroundState::OnGround;

   if (isOnGround && !mCharacter->IsSlopeTooSteep(mCharacter->GetGroundNormal()))
   {
      const JPH::Vec3 horizontalVel(velocity.GetX(), velocity.GetY(), 0.0f);
      mAllowSliding = horizontalVel.Length() > 0.01f;

      // Clamp small upward residuals on flat ground to prevent floating
      if (velocity.GetZ() < 0.05f)
         velocity.SetZ(0.0f);

      // Carry platform / conveyor velocity
      const JPH::Vec3 groundVel = mCharacter->GetGroundVelocity();
      if (groundVel.LengthSq() > 0.01f)
      {
         velocity.SetX(velocity.GetX() + groundVel.GetX());
         velocity.SetY(velocity.GetY() + groundVel.GetY());
         // Only add upward elevator velocity, not static-surface residuals
         if (groundVel.GetZ() > 0.05f)
            velocity.SetZ(velocity.GetZ() + groundVel.GetZ());
      }
   }
   else
   {
      mAllowSliding = true;
   }

   // Hand velocity to Jolt — the physics step (tickPhysics) will move the body.
   // Unlike CharacterVirtual there is no ExtendedUpdate here; collision response
   // and stair-stepping are resolved by Jolt's constraint solver.
   mCharacter->SetLinearVelocity(velocity);
   const bool activelyJumping = (velocity.GetZ() > 0.01f);

   // -----------------------------------------------------------------
   // Fill collision list — ground contact only
   // (Non-ground contacts come through the physics ContactListener;
   //  sensor / trigger overlaps are found in findContact via broadphase)
   // -----------------------------------------------------------------
   if (isOnGround && !activelyJumping && outCol.getCount() < CollisionList::MaxCollisions)
   {
      const JPH::BodyID groundBodyID = mCharacter->GetGroundBodyID();
      JPH::BodyLockRead lock(
         mWorld->getPhysicsSystem()->GetBodyLockInterface(), groundBodyID);

      if (lock.Succeeded())
      {
         const JPH::Body& body = lock.GetBody();
         PhysicsUserData* ud = reinterpret_cast<PhysicsUserData*>(body.GetUserData());

         Collision& col = outCol.increment();
         col.point = joltCast(mCharacter->GetGroundPosition());
         col.normal = joltCast(mCharacter->GetGroundNormal());
         col.object = ud ? ud->getObject() : NULL;
         col.material = NULL;
         col.distance = 0.0f;
         col.faceDot = mDot(col.normal, VectorF(0.f, 0.f, 1.f));
      }
   }

   // Return the position from the last physics step.  tickPhysics() will move
   // the body further based on the velocity we just set; that result feeds into
   // the next tick via GetPosition() here.
   return joltCast(mCharacter->GetPosition());
}

void JoltPlayer::findContact(SceneObject** contactObject, VectorF* contactNormal,
   Vector<SceneObject*>* outOverlapObjects) const
{
   if (!mCharacter || !mIsEnabled)
      return;

   const auto& system = mWorld->getPhysicsSystem();

   // --- Primary ground contact -----------------------------------------
   // PostSimulation() already ran in preUpdate() and produced reliable ground
   // data.  Pull it directly rather than re-deriving the normal from
   // CheckCollision's mPenetrationAxis.
   if (mCharacter->GetGroundState() == JPH::Character::EGroundState::OnGround
      && !mCharacter->GetGroundBodyID().IsInvalid())
   {
      JPH::BodyLockRead lock(system->GetBodyLockInterface(),
         mCharacter->GetGroundBodyID());
      if (lock.Succeeded())
      {
         auto* ud = reinterpret_cast<PhysicsUserData*>(lock.GetBody().GetUserData());
         if (ud)
         {
            *contactObject = ud->getObject();
            *contactNormal = joltCast(mCharacter->GetGroundNormal());
         }
      }
   }

   // --- Overlap harvest for triggers / items ---------------------------
   // CheckCollision tests the character's actual capsule (not an expanded
   // AABB) and returns every body within the skin distance.  We only need
   // body references here — no normal math — so the collector is trivial.
   // Sensor bodies (triggers) and physical bodies (items) are both included
   // so that Player::findContact() can call potentialEnterObject() on them.
   struct OverlapCollector : public JPH::CollideShapeCollector
   {
      OverlapCollector(const JPH::PhysicsSystem* inSystem,
         Vector<SceneObject*>& inOverlaps)
         : mSystem(inSystem), mOverlaps(inOverlaps) {
      }

      void AddHit(const JPH::CollideShapeResult& inResult) override
      {
         JPH::BodyLockRead lock(mSystem->GetBodyLockInterface(), inResult.mBodyID2);
         if (!lock.Succeeded())
            return;

         auto* ud = reinterpret_cast<PhysicsUserData*>(
            lock.GetBody().GetUserData());
         if (!ud)
            return;

         if (auto* obj = ud->getObject(); obj && !mOverlaps.contains(obj))
            mOverlaps.push_back(obj);
      }

      const JPH::PhysicsSystem* mSystem;
      Vector<SceneObject*>& mOverlaps;
   };

   const JPH::RVec3 pos = mCharacter->GetPosition();

   OverlapCollector collector(system, *outOverlapObjects);
   mCharacter->CheckCollision(
      pos,
      mCharacter->GetRotation(),
      JPH::Vec3::sZero(),         // no movement hint needed — pure overlap harvest
      0.1f,                        // 10 cm skin
      mCharacter->GetShape(),
      pos,                         // base offset for float precision near origin
      collector
   );
}

bool JoltPlayer::testSpacials(const Point3F& nPos, const Point3F& nSize) const
{
   return true;
}

void JoltPlayer::setSpacials(const Point3F& nPos, const Point3F& nSize)
{
   if (!mCharacter || !mWorld)
      return;

   const F32 radius = mMax(nSize.x, nSize.y) * 0.5f;
   const F32 height = mMax(0.01f, nSize.z);

   mOriginOffset = 0.5f * height;

   const JPH::Quat rotFix = JPH::Quat::sRotation(
      JPH::Vec3::sAxisX(), JPH::DegreesToRadians(90.0f));

   JPH::Ref<JPH::Shape> shape =
      JPH::RotatedTranslatedShapeSettings(
         JPH::Vec3(0.0f, 0.0f, mOriginOffset), rotFix,
         new JPH::CapsuleShape((0.5f * height) - radius, radius))
      .Create().Get();

   // Character::SetShape is simpler than CharacterVirtual::SetShape —
   // no filter objects or TempAllocator required.
   const float maxPenetration = 0.05f;
   mCharacter->SetShape(shape, maxPenetration);
}

void JoltPlayer::enableCollision()
{
   if (!mCharacter || !mWorld || mCollisionEnabled)
      return;

   mCollisionEnabled = true;
   // Character IS a body — adding it back to the physics system re-enables it
   mCharacter->AddToPhysicsSystem(JPH::EActivation::Activate);
}

void JoltPlayer::disableCollision()
{
   if (!mCharacter || !mWorld || !mCollisionEnabled)
      return;

   mCollisionEnabled = false;
   mCharacter->RemoveFromPhysicsSystem();
}
