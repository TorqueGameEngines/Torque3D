
#include "platform/platform.h"
#include "T3D/physics/jolt/joltPlugin.h"
 
#include "T3D/physics/jolt/joltWorld.h"
#include "T3D/physics/jolt/joltCollision.h"
#include "T3D/physics/jolt/joltBody.h"
#include "T3D/gameBase/gameProcess.h"
#include "core/util/tNamedFactory.h"
#include "gfx/sim/debugDraw.h"

AFTER_MODULE_INIT(Sim)
{
   NamedFactory<PhysicsPlugin>::add("JoltPhysics", &JoltPlugin::create);
}

JoltPlugin::JoltPlugin()
{
   JPH::RegisterDefaultAllocator();

   JPH::Factory::sInstance = new JPH::Factory();
   JPH::RegisterTypes();

#ifdef JPH_DEBUG_RENDERER
   JPH::DebugRenderer::sInstance = new JoltDebugRenderer();
#endif // TORQUE_TOOLS
}

JoltPlugin::~JoltPlugin()
{
   delete JPH::Factory::sInstance;
#ifdef JPH_DEBUG_RENDERER
   delete JPH::DebugRenderer::sInstance;
   JPH::DebugRenderer::sInstance = nullptr;
#endif
}

void JoltPlugin::reset()
{
   // First delete all the cleanup objects.
   if (getPhysicsCleanup())
      getPhysicsCleanup()->deleteAllObjects();

   getPhysicsResetSignal().trigger(PhysicsResetEvent_Restore);

   // Now let each world reset itself.
   Map<StringNoCase, PhysicsWorld*>::Iterator iter = mPhysicsWorldLookup.begin();
   for (; iter != mPhysicsWorldLookup.end(); iter++)
      iter->value->reset();
}

PhysicsPlugin* JoltPlugin::create()
{
   return new JoltPlugin();
}


void JoltPlugin::destroyPlugin()
{
   // Cleanup any worlds that are still kicking.
   Map<StringNoCase, PhysicsWorld*>::Iterator iter = mPhysicsWorldLookup.begin();
   for (; iter != mPhysicsWorldLookup.end(); iter++)
   {
      iter->value->destroyWorld();
      delete iter->value;
   }
   mPhysicsWorldLookup.clear();

   delete this;
}

PhysicsCollision* JoltPlugin::createCollision()
{
   return new JoltCollision();
}

PhysicsBody* JoltPlugin::createBody()
{
   return new JoltBody();
}

PhysicsPlayer* JoltPlugin::createPlayer()
{
   return nullptr;
}

bool JoltPlugin::isSimulationEnabled() const
{
   bool ret = false;
   JoltWorld* world = static_cast<JoltWorld*>(getWorld(smClientWorldName));
   if (world)
   {
      ret = world->getEnabled();
      return ret;
   }

   world = static_cast<JoltWorld*>(getWorld(smServerWorldName));
   if (world)
   {
      ret = world->getEnabled();
      return ret;
   }

   return ret;
}

void JoltPlugin::enableSimulation(const String& worldName, bool enable)
{
   JoltWorld* world = static_cast<JoltWorld*>(getWorld(worldName));
   if (world)
      world->setEnabled(enable);
}


void JoltPlugin::setTimeScale(const F32 timeScale)
{
   // Grab both the client and
   // server worlds and set their time
   // scales to the passed value.
   JoltWorld* world = static_cast<JoltWorld*>(getWorld(smClientWorldName));
   if (world)
      world->setEditorTimeScale(timeScale);

   world = static_cast<JoltWorld*>(getWorld(smServerWorldName));
   if (world)
      world->setEditorTimeScale(timeScale);
}


const F32 JoltPlugin::getTimeScale() const
{
   // Grab both the client and
   // server worlds and call 
   // setEnabled( true ) on them.
   JoltWorld* world = static_cast<JoltWorld*>(getWorld(smClientWorldName));
   if (!world)
   {
      world = static_cast<JoltWorld*>(getWorld(smServerWorldName));
      if (!world)
         return 0.0f;
   }

   return world->getEditorTimeScale();
}

bool JoltPlugin::createWorld(const String& worldName)
{
   Map<StringNoCase, PhysicsWorld*>::Iterator iter = mPhysicsWorldLookup.find(worldName);
   PhysicsWorld* world = NULL;

   iter != mPhysicsWorldLookup.end() ? world = (*iter).value : world = NULL;

   if (world)
   {
      Con::errorf("BtPlugin::createWorld - %s world already exists!", worldName.c_str());
      return false;
   }

   world = new JoltWorld();

   if (worldName.equal(smClientWorldName, String::NoCase))
      world->initWorld(false, ClientProcessList::get());
   else
      world->initWorld(true, ServerProcessList::get());

   mPhysicsWorldLookup.insert(worldName, world);

   return world != NULL;
}

void JoltPlugin::destroyWorld(const String& worldName)
{
   Map<StringNoCase, PhysicsWorld*>::Iterator iter = mPhysicsWorldLookup.find(worldName);
   if (iter == mPhysicsWorldLookup.end())
      return;

   PhysicsWorld* world = (*iter).value;
   world->destroyWorld();


   mPhysicsWorldLookup.erase(iter);
}

PhysicsWorld* JoltPlugin::getWorld(const String& worldName) const
{
   if (mPhysicsWorldLookup.isEmpty())
      return NULL;

   Map<StringNoCase, PhysicsWorld*>::ConstIterator iter = mPhysicsWorldLookup.find(worldName);

   return iter != mPhysicsWorldLookup.end() ? (*iter).value : NULL;
}

PhysicsWorld* JoltPlugin::getWorld() const
{
   if (mPhysicsWorldLookup.size() == 0)
      return NULL;

   Map<StringNoCase, PhysicsWorld*>::ConstIterator iter = mPhysicsWorldLookup.begin();
   return iter->value;
}

U32 JoltPlugin::getWorldCount() const
{
   return mPhysicsWorldLookup.size();
}

#ifdef JPH_DEBUG_RENDERER
JoltDebugRenderer::JoltDebugRenderer()
{
   JPH::DebugRenderer::Initialize();
}

void JoltDebugRenderer::DrawLine(JPH::RVec3Arg inFrom, JPH::RVec3Arg inTo, JPH::ColorArg inColor)
{
   DebugDrawer::get()->drawLine(joltCast(inFrom), joltCast(inTo), fromJolt(inColor));
}

void JoltDebugRenderer::DrawTriangle(JPH::RVec3Arg inV1, JPH::RVec3Arg inV2, JPH::RVec3Arg inV3, JPH::ColorArg inColor, ECastShadow inCastShadow)
{
   DebugDrawer::get()->drawTri(joltCast(inV1), joltCast(inV2), joltCast(inV3), fromJolt(inColor));
}

JPH::DebugRenderer::Batch JoltDebugRenderer::CreateTriangleBatch(const Triangle* inTriangles, int inTriangleCount)
{
   BatchImpl* batch = new BatchImpl;
   if (inTriangles == nullptr || inTriangleCount == 0)
      return batch;

   batch->mTriangles.assign(inTriangles, inTriangles + inTriangleCount);
   return batch;
}

JPH::DebugRenderer::Batch JoltDebugRenderer::CreateTriangleBatch(const Vertex* inVertices, int inVertexCount, const JPH::uint32* inIndices, int inIndexCount)
{
   BatchImpl* batch = new BatchImpl;
   if (inVertices == nullptr || inVertexCount == 0 || inIndices == nullptr || inIndexCount == 0)
      return batch;

   // Convert indexed triangle list to triangle list
   batch->mTriangles.resize(inIndexCount / 3);
   for (size_t t = 0; t < batch->mTriangles.size(); ++t)
   {
      JPH::DebugRenderer::Triangle& triangle = batch->mTriangles[t];
      triangle.mV[0] = inVertices[inIndices[t * 3 + 0]];
      triangle.mV[1] = inVertices[inIndices[t * 3 + 1]];
      triangle.mV[2] = inVertices[inIndices[t * 3 + 2]];
   }

   return batch;
}

void JoltDebugRenderer::DrawGeometry(JPH::RMat44Arg inModelMatrix, const JPH::AABox& inWorldSpaceBounds, float inLODScaleSq, JPH::ColorArg inModelColor, const GeometryRef& inGeometry, ECullMode inCullMode, ECastShadow inCastShadow, EDrawMode inDrawMode)
{
   // Figure out which LOD to use
   const JPH::DebugRenderer::LOD* lod = inGeometry->mLODs.data();

   // Draw the batch
   const BatchImpl* batch = static_cast<const BatchImpl*>(lod->mTriangleBatch.GetPtr());
   for (const JPH::DebugRenderer::Triangle& triangle : batch->mTriangles)
   {
      JPH::Vec3 v0 = inModelMatrix * JPH::Vec3(triangle.mV[0].mPosition);
      JPH::Vec3 v1 = inModelMatrix * JPH::Vec3(triangle.mV[1].mPosition);
      JPH::Vec3 v2 = inModelMatrix * JPH::Vec3(triangle.mV[2].mPosition);
      JPH::Color color = inModelColor * triangle.mV[0].mColor;

      DrawTriangle(v0, v1, v2, color, inCastShadow);

   }
}
#endif
