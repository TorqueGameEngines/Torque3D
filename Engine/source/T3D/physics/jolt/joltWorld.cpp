
#include "platform/platform.h"
#include "T3D/physics/jolt/joltWorld.h"
 
#include "platform/profiler.h"
#include "sim/netConnection.h"
#include "console/console.h"
#include "console/consoleTypes.h"
#include "scene/sceneRenderState.h"
#include "T3D/gameBase/gameProcess.h"

#include "T3D/physics/physicsUserData.h"

#include <Jolt/Physics/Collision/RayCast.h>
#include <Jolt/Physics/Collision/CastResult.h>
#include <Jolt/Physics/Body/BodyLock.h>
#include <Jolt/Physics/Body/Body.h>
#include <Jolt/Physics/Collision/NarrowPhaseQuery.h>

JoltWorld::JoltWorld()
   :mIsEnabled(false),
   mProcessList(NULL),
   mEditorTimeScale(1.0f)
{
   mTempAllocator = nullptr;
   mJobSystem = nullptr;
}


JoltWorld::~JoltWorld()
{
   destroyWorld();
}

bool JoltWorld::initWorld(bool isServer, ProcessList* processList)
{
   const U32 cMaxBodies = 65536;
   const U32 cNumBodyMutexes = 1024;
   const U32 cMaxBodyPairs = 65536;
   const U32 cMaxContactConstraints = 10240;

   mTempAllocator = new JPH::TempAllocatorImpl(10 * 1024 * 1024);

   // thread pool of 2 threads?
   mJobSystem = new JPH::JobSystemThreadPool(
      JPH::cMaxPhysicsJobs,
      JPH::cMaxPhysicsBarriers,
      -1
   );

   mPhysicsSystem.Init(
      cMaxBodies,
      cNumBodyMutexes,
      cMaxBodyPairs,
      cMaxContactConstraints,
      mBroadPhaseLayerInterface,
      mObjectVsBroadPhaseLayerFilter,
      mObjectLayerPairFilter
   );

   mIsEnabled = true;

   mPhysicsSystem.SetGravity(joltCast(mGravity));


   mProcessList = processList;
   mProcessList->preTickSignal().notify(this, &JoltWorld::getPhysicsResults);
   mProcessList->postTickSignal().notify(this, &JoltWorld::tickPhysics, 1000.0f);

   return true;
}

void JoltWorld::destroyWorld()
{
   // Release the tick processing signals.
   if (mProcessList)
   {
      mProcessList->preTickSignal().remove(this, &JoltWorld::getPhysicsResults);
      mProcessList->postTickSignal().remove(this, &JoltWorld::tickPhysics);
      mProcessList = NULL;
   }
}

bool JoltWorld::castRay(const Point3F& startPnt, const Point3F& endPnt, RayInfo* ri, const Point3F& impulse)
{
   JPH::Vec3 startV(startPnt.x, startPnt.y, startPnt.z);
   JPH::Vec3 dir = JPH::Vec3(endPnt.x - startPnt.x, endPnt.y - startPnt.y, endPnt.z - startPnt.z);

   F32 rayLength = dir.Length();

   if (rayLength <= 0.0001f)
      return false;

   JPH::RRayCast ray(startV, dir);

   JPH::RayCastResult result;

   if (!mPhysicsSystem.GetNarrowPhaseQuery().CastRay(ray, result))
      return false;

   JPH::BodyLockRead lock(
      mPhysicsSystem.GetBodyLockInterface(),
      result.mBodyID
   );

   if (!lock.Succeeded())
      return false;

   dir /= rayLength;

   const JPH::Body& body = lock.GetBody();

   JPH::RVec3 hitPos = ray.GetPointOnRay(result.mFraction);

   JPH::Vec3 normal = body.GetWorldSpaceSurfaceNormal( result.mSubShapeID2, hitPos );

   if (ri)
   {
      ri->point.set(joltCast(hitPos));
      ri->normal.set(joltCast(normal));

      ri->distance = result.mFraction * rayLength;

      // SceneObject mapping
      PhysicsUserData* userData = reinterpret_cast<PhysicsUserData*>(body.GetUserData());
      ri->object = userData->getObject();

      ri->material = NULL;
      ri->face = 0;
      ri->faceDot = 0;
   }

   return true;
}

PhysicsBody* JoltWorld::castRay(const Point3F& start, const Point3F& end, U32 bodyTypes)
{
   return nullptr;
}

void JoltWorld::explosion(const Point3F& pos, F32 radius, F32 forceMagnitude)
{
}

void JoltWorld::onDebugDraw(const SceneRenderState* state)
{
#ifdef TORQUE_TOOLS
   if (!mIsEnabled)
      return;

   if (!JPH::DebugRenderer::sInstance)
      return;

   JPH::BodyManager::DrawSettings settings;

   settings.mDrawShape = true;
   settings.mDrawWorldTransform = false;
   settings.mDrawBoundingBox = true;
   settings.mDrawVelocity = false;
   settings.mDrawCenterOfMassTransform = true;

   mPhysicsSystem.DrawBodies(settings, JPH::DebugRenderer::sInstance);
#endif
}

void JoltWorld::tickPhysics(U32 elapsedMs)
{
   if (!mIsEnabled)
      return;

   if (mResetPending.exchange(false))
      performReset();

   const F32 elapsedSec = (F32)elapsedMs * 0.001f;

   mPhysicsSystem.Update(
      elapsedSec * mEditorTimeScale,
      smPhysicsMaxSubSteps, // collision steps
      mTempAllocator,
      mJobSystem
   );
}

void JoltWorld::getPhysicsResults()
{
}

void JoltWorld::performReset()
{
   JPH::BodyInterface& bodyInterface = mPhysicsSystem.GetBodyInterface();

   JPH::BodyIDVector bodies;
   mPhysicsSystem.GetBodies(bodies);

   for (JPH::BodyID id : bodies)
   {
      if (!bodyInterface.IsAdded(id))
         continue;

      bodyInterface.ActivateBody(id);

      bodyInterface.SetLinearAndAngularVelocity(
         id,
         JPH::Vec3::sZero(),
         JPH::Vec3::sZero()
      );
   }

   mPhysicsSystem.OptimizeBroadPhase();
}

void JoltWorld::reset()
{
   if (!mIsEnabled)
      return;

   // we operate with a threading environment o not reset right away.
   mResetPending.store(true, std::memory_order_release);

}

void JoltWorld::setEnabled(bool enabled)
{
   mIsEnabled = enabled;

   if (!mIsEnabled)
      getPhysicsResults();
}


