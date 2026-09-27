#pragma once

#ifndef _JOLTWORLD_H_
#define _JOLTWORLD_H_

#ifndef _T3D_PHYSICS_PHYSICSWORLD_H_
#include "T3D/physics/physicsWorld.h"
#endif

#ifndef _T3D_JOLT_PLUGIN_H_
#include "T3D/physics/jolt/joltPlugin.h"
#endif


class ProcessList;
class PhysicsBody;
class JoltPlayer;

namespace Layers
{
   static constexpr JPH::ObjectLayer NON_MOVING = 0;
   static constexpr JPH::ObjectLayer MOVING = 1;
   static constexpr JPH::ObjectLayer CHARACTER = 2;
   static constexpr JPH::ObjectLayer DEBRIS = 3;
   static constexpr JPH::ObjectLayer NUM_LAYERS = 4;
}

namespace BroadPhaseLayers
{
   static constexpr JPH::BroadPhaseLayer NON_MOVING(0);
   static constexpr JPH::BroadPhaseLayer MOVING(1);

   static constexpr U32 NUM_LAYERS = 2;
}

class BPLayerInterfaceImpl final : public JPH::BroadPhaseLayerInterface
{
public:

   BPLayerInterfaceImpl()
   {
      mObjectToBroadPhase[Layers::NON_MOVING] = BroadPhaseLayers::NON_MOVING;
      mObjectToBroadPhase[Layers::MOVING] = BroadPhaseLayers::MOVING;
      mObjectToBroadPhase[Layers::CHARACTER] = BroadPhaseLayers::MOVING;
      mObjectToBroadPhase[Layers::DEBRIS] = BroadPhaseLayers::MOVING;
   }

   virtual U32 GetNumBroadPhaseLayers() const override
   {
      return BroadPhaseLayers::NUM_LAYERS;
   }

   virtual JPH::BroadPhaseLayer GetBroadPhaseLayer(JPH::ObjectLayer layer) const override
   {
      return mObjectToBroadPhase[layer];
   }

#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)

   virtual const char* GetBroadPhaseLayerName(JPH::BroadPhaseLayer layer) const override
   {
      switch ((JPH::BroadPhaseLayer::Type)layer)
      {
      case 0: return "NON_MOVING";
      case 1: return "MOVING";
      default: return "UNKNOWN";
      }
   }

#endif

private:

   JPH::BroadPhaseLayer mObjectToBroadPhase[Layers::NUM_LAYERS];
};

class ObjectLayerPairFilterImpl : public JPH::ObjectLayerPairFilter
{
public:

   virtual bool ShouldCollide(
      JPH::ObjectLayer layer1,
      JPH::ObjectLayer layer2) const override
   {
      switch (layer1)
      {
      case Layers::NON_MOVING:
         return layer2 == Layers::MOVING
            || layer2 == Layers::CHARACTER
            || layer2 == Layers::DEBRIS;

      case Layers::MOVING:
         return true;

      case Layers::CHARACTER:
         return layer2 == Layers::NON_MOVING
            || layer2 == Layers::MOVING
            || layer2 == Layers::CHARACTER;

      case Layers::DEBRIS:
         return layer2 == Layers::NON_MOVING; // Only Statics

      default:
         return false;
      }
   }
};

class ObjectVsBroadPhaseLayerFilterImpl : public JPH::ObjectVsBroadPhaseLayerFilter
{
public:

   virtual bool ShouldCollide(
      JPH::ObjectLayer layer1,
      JPH::BroadPhaseLayer layer2) const override
   {
      switch (layer1)
      {
      case Layers::NON_MOVING:
         return layer2 == BroadPhaseLayers::MOVING;

      case Layers::MOVING:
      case Layers::CHARACTER:
         return true;

      case Layers::DEBRIS:
         return layer2 == BroadPhaseLayers::NON_MOVING;

      default:
         return false;
      }
   }
};

class JoltWorld : public PhysicsWorld
{
protected:
   bool	mIsEnabled;

   U32 mTickCount;
   bool mIsSimulating;

   std::atomic<bool> mResetPending{ false };
   std::atomic<bool> mDestroyPending{ false };

   F32 mEditorTimeScale;
   JPH::PhysicsSystem mPhysicsSystem;
   JPH::TempAllocatorImpl* mTempAllocator;
   JPH::JobSystemThreadPool* mJobSystem;
   BPLayerInterfaceImpl mBroadPhaseLayerInterface;
   ObjectVsBroadPhaseLayerFilterImpl mObjectVsBroadPhaseLayerFilter;
   ObjectLayerPairFilterImpl mObjectLayerPairFilter;
   ProcessList* mProcessList;
public:
   JoltWorld();
   virtual ~JoltWorld();

   // PhysicWorld
   virtual bool initWorld(bool isServer, ProcessList* processList);
   void destroyWorldInternal();
   virtual void destroyWorld();
   virtual bool castRay(const Point3F& startPnt, const Point3F& endPnt, RayInfo* ri, const Point3F& impulse);
   virtual PhysicsBody* castRay(const Point3F& start, const Point3F& end, U32 bodyTypes);
   virtual void explosion(const Point3F& pos, F32 radius, F32 forceMagnitude);
   virtual void onDebugDraw(const SceneRenderState* state);
   virtual void reset();
   virtual bool isEnabled() const { return mIsEnabled; }

   void tickPhysics(U32 elapsedMs);
   void getPhysicsResults();
   bool isWritable() const { return !mIsSimulating; }

   void performReset();

   void setEnabled(bool enabled);
   bool getEnabled() const { return mIsEnabled; }

   void setEditorTimeScale(F32 timeScale) { mEditorTimeScale = timeScale; }
   const F32 getEditorTimeScale() const { return mEditorTimeScale; }
   JPH::PhysicsSystem* getPhysicsSystem() { return &mPhysicsSystem; }

   const JPH::BroadPhaseLayerInterface& getBroadPhaseLayerInterface() const { return mBroadPhaseLayerInterface; };
   const JPH::ObjectLayerPairFilter& getObjectLayerPairFilter() const { return mObjectLayerPairFilter; }
   const JPH::ObjectVsBroadPhaseLayerFilter& getObjectVsBroadPhaseLayerFilter() const { return mObjectVsBroadPhaseLayerFilter; }
   JPH::TempAllocatorImpl* getTempAllocator() { return mTempAllocator; }
   ProcessList* getProcessList() { return mProcessList; }

};

#endif // !_JOLTWORLD_H_
