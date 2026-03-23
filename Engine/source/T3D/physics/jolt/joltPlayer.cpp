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
   mDesiredVelocity = JPH::Vec3::sZero();
}

JoltPlayer::~JoltPlayer()
{
   if (mCharacter && mIsEnabled)
   {
      if (mWorld && mWorld->isEnabled())
         mWorld->removePlayer(this);
   }
   mCharacter->SetUserData(NULL);
   mCharacter = NULL;
   setSimulationEnabled(false);
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

   F32 height = size.z;
   F32 radius = mMax(size.x, size.y) * 0.5f;
   JPH::Quat rotFix = JPH::Quat::sRotation(JPH::Vec3::sAxisX(), JPH::DegreesToRadians(90.0f)); // zup 
   JPH::Ref<JPH::Shape> shape = JPH::RotatedTranslatedShapeSettings(JPH::Vec3(0, 0, 0.5f * height + radius), rotFix, new JPH::CapsuleShape(0.5f * height, radius)).Create().Get();
   JPH::Ref<JPH::Shape> inner_shape = JPH::RotatedTranslatedShapeSettings(JPH::Vec3(0, 0, 0.5f * height + radius), rotFix, new JPH::CapsuleShape(0.5f * height, 0.9f * radius)).Create().Get();

   JPH::Ref<JPH::CharacterVirtualSettings> settings = new JPH::CharacterVirtualSettings();
   settings->mMaxSlopeAngle = runSurfaceCos;
   settings->mMaxStrength = 100.0f;
   settings->mShape = shape;
   settings->mMass = obj->getMass();
   settings->mBackFaceMode = JPH::EBackFaceMode::CollideWithBackFaces;
   settings->mCharacterPadding = 0.02f;
   settings->mPenetrationRecoverySpeed = 1.0f;
   settings->mPredictiveContactDistance = 0.1f;
   settings->mSupportingVolume = JPH::Plane(JPH::Vec3::sAxisZ(), -radius);
   settings->mEnhancedInternalEdgeRemoval = false;
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
   getUserData().setBody(this);
   mCharacter->SetUserData(reinterpret_cast<U64>(&mUserData));

   mCharacter->SetUp(JPH::Vec3::sAxisZ());

   mWorld->addPlayer(this);
   setSimulationEnabled(true);
}

void JoltPlayer::preUpdate(F32 dt)
{
   if (!mCharacter || !mIsEnabled)
      return;

   const auto& system = mWorld->getPhysicsSystem();

   JPH::Vec3 up = mCharacter->GetUp();

   // --- Decompose current velocity ---
   JPH::Vec3 desired_vel = mDesiredVelocity;
   mDesiredVelocity = JPH::Vec3::sZero();

   JPH::Vec3 verticalVel = mCharacter->GetLinearVelocity().Dot(up) * up;

   JPH::Vec3 groundVel = mCharacter->GetGroundVelocity();

   const bool isOnGround = mCharacter->GetGroundState() == JPH::CharacterVirtual::EGroundState::OnGround;
   const bool notJumping = (verticalVel - groundVel).Dot(up) < 0.1f;

   JPH::Vec3 newVel;
   if (isOnGround && notJumping)
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
   JPH::Vec3 gravity = -up * system->GetGravity().Length();

   newVel += gravity * dt;
   newVel += desired_vel;

   // --- Apply to character ---
   mCharacter->SetLinearVelocity(newVel);

   JPH::CharacterVirtual::ExtendedUpdateSettings settings;

   settings.mStickToFloorStepDown = -up * settings.mStickToFloorStepDown.Length();
   settings.mWalkStairsStepUp = up * settings.mWalkStairsStepUp.Length();

   mCharacter->ExtendedUpdate(
      dt,
      gravity,
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

   mDesiredVelocity = joltCast(displacement) / TickSec;

   return joltCast(mCharacter->GetPosition());
}

void JoltPlayer::findContact(SceneObject** contactObject, VectorF* contactNormal, Vector<SceneObject*>* outOverlapObjects) const
{
   if (!mCharacter || !mIsEnabled)
      return;

   const bool isOnGround = mCharacter->GetGroundState() == JPH::CharacterVirtual::EGroundState::OnGround;
   if (isOnGround)
   {
      JPH::BodyLockRead lock(
         mWorld->getPhysicsSystem()->GetBodyLockInterface(),
         mCharacter->GetGroundBodyID()
      );

      if (!lock.Succeeded())
         return;

      const JPH::Body& body = lock.GetBody();

      if (body.GetObjectLayer() == Layers::CHARACTER || !body.GetUserData())
      {
         return;
      }

      *contactNormal = joltCast(mCharacter->GetGroundNormal());
      if (mCharacter->GetGroundUserData())
      {
         PhysicsUserData* userData = PhysicsUserData::cast((void*)body.GetUserData());
         *contactObject = userData->getObject();
      }
   }
}

bool JoltPlayer::testSpacials(const Point3F& nPos, const Point3F& nSize) const
{
   if (!mCharacter || !mWorld)
      return false;

   const auto& system = mWorld->getPhysicsSystem();

   JPH::BodyFilter body_filter;
   JPH::ShapeFilter shape_filter;

   F32 height = nSize.z;
   F32 radius = mMax(nSize.x, nSize.y) * 0.5f;
   JPH::Quat rotFix = JPH::Quat::sRotation(JPH::Vec3::sAxisX(), JPH::DegreesToRadians(90.0f)); // zup 
   JPH::Ref<JPH::Shape> shape = JPH::RotatedTranslatedShapeSettings(JPH::Vec3(0, 0, 0.5f * height + radius), rotFix, new JPH::CapsuleShape(0.5f * height, radius)).Create().Get();

   const float maxPenetration = 0.05f; // tweak tolerance

   return mCharacter->SetShape(
      shape,
      maxPenetration,
      system->GetDefaultBroadPhaseLayerFilter(Layers::MOVING),
      system->GetDefaultLayerFilter(Layers::MOVING),
      body_filter,
      shape_filter,
      *mWorld->getTempAllocator());

}

void JoltPlayer::setSpacials(const Point3F& nPos, const Point3F& nSize)
{
   if (!mCharacter || !mWorld)
      return;

   const auto& system = mWorld->getPhysicsSystem();

   JPH::BodyFilter body_filter;
   JPH::ShapeFilter shape_filter;

   F32 height = nSize.z;
   F32 radius = mMax(nSize.x, nSize.y) * 0.5f;
   JPH::Quat rotFix = JPH::Quat::sRotation(JPH::Vec3::sAxisX(), JPH::DegreesToRadians(90.0f)); // zup 
   JPH::Ref<JPH::Shape> shape = JPH::RotatedTranslatedShapeSettings(JPH::Vec3(0, 0, 0.5f * height + radius), rotFix, new JPH::CapsuleShape(0.5f * height, radius)).Create().Get();
   JPH::Ref<JPH::Shape> inner_shape = JPH::RotatedTranslatedShapeSettings(JPH::Vec3(0, 0, 0.5f * height + radius), rotFix, new JPH::CapsuleShape(0.5f * height, 0.9f * radius)).Create().Get();

   const float maxPenetration = 0.05f; // tweak tolerance

   if (mCharacter->SetShape(
      shape,
      maxPenetration,
      system->GetDefaultBroadPhaseLayerFilter(Layers::MOVING),
      system->GetDefaultLayerFilter(Layers::MOVING),
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
}

void JoltPlayer::disableCollision()
{
}
