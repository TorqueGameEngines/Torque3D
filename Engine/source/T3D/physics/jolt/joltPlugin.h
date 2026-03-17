#ifndef _T3D_JOLT_PLUGIN_H_
#define _T3D_JOLT_PLUGIN_H_

#ifndef _T3D_PHYSICS_PHYSICSPLUGIN_H_
#include "T3D/physics/physicsPlugin.h"
#endif

#ifdef TORQUE_TOOLS
#ifndef JPH_DEBUG_RENDERER
#define JPH_DEBUG_RENDERER
#endif
#endif

#include <Jolt/Jolt.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/StreamWrapper.h>
#include <Jolt/Physics/Collision/RayCast.h>
#include <Jolt/Physics/Collision/CastResult.h>
#ifdef TORQUE_TOOLS
#include <Jolt/Renderer/DebugRenderer.h>
#endif
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/StateRecorderImpl.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/CylinderShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Collision/Shape/MeshShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Constraints/SixDOFConstraint.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>

inline Point3F joltCast(const JPH::Vec3& vec)
{
   return Point3F(vec.GetX(), vec.GetY(), vec.GetZ());
}

inline JPH::Vec3 joltCast(const Point3F& point)
{
   return JPH::Vec3(point.x, point.y, point.z);
}

inline QuatF joltCast(const JPH::Quat& quat)
{
   /// The Torque quat has the opposite winding order.
   return QuatF(-quat.GetX(), -quat.GetY(), -quat.GetZ(), quat.GetW());
}

inline JPH::Quat joltCast(const QuatF& quat)
{
   /// The Torque quat has the opposite winding order.
   return JPH::Quat(-quat.x, -quat.y, -quat.z, quat.w);
}

inline JPH::RMat44 joltCast(const MatrixF& m)
{
   return JPH::RMat44(
      JPH::Vec4(m[0], m[1], m[2], 0.0f),
      JPH::Vec4(m[4], m[5], m[6], 0.0f),
      JPH::Vec4(m[8], m[9], m[10], 0.0f),
      JPH::Vec4(m[3], m[7], m[1], 1.0f)
   );
}

inline MatrixF joltCast(const JPH::Mat44& xfm)
{
   MatrixF out;

   // Set the rotation.
   out[0] = xfm(0, 0); out[1] = xfm(0, 1); out[2] = xfm(0, 2);
   out[4] = xfm(1, 0); out[5] = xfm(1, 1); out[6] = xfm(1, 2);
   out[8] = xfm(2, 0); out[9] = xfm(2, 1); out[10] = xfm(2, 2);

   // The position.
   out[3] = xfm.GetTranslation().GetX();
   out[7] = xfm.GetTranslation().GetY();
   out[11] = xfm.GetTranslation().GetZ();

   // Clear out the rest.
   out[12] = out[13] = out[14] = 0.0f;
   out[15] = 1.0f;

   return out;
}

inline void toJolt(const MatrixF& mat, JPH::RVec3& pos, JPH::Quat& rot)
{
   Point3F p;
   p = mat.getPosition();

   pos = joltCast(p);

   QuatF q(mat);

   rot = joltCast(q);
}

inline JPH::AABox toJolt(const Box3F& box)
{
   return JPH::AABox(
      joltCast(box.minExtents),
      joltCast(box.maxExtents)
   );
}

inline Box3F fromJolt(const JPH::AABox& box)
{
   return Box3F(
      joltCast(box.mMin),
      joltCast(box.mMax)
   );
}

#ifndef _COLOR_H_
#include "core/color.h"
#endif

inline JPH::Color toJolt(const ColorI& c)
{
   return JPH::Color(c.red, c.green, c.blue, c.alpha);
}



inline ColorI fromJolt(const JPH::Color& c)
{
   return ColorI(c.r, c.g, c.b, c.a);
}

#ifdef TORQUE_TOOLS
class JoltDebugRenderer final : public JPH::DebugRenderer
{
public:
   JPH_OVERRIDE_NEW_DELETE
   explicit  JoltDebugRenderer();
   virtual void DrawLine(JPH::RVec3Arg inFrom, JPH::RVec3Arg inTo, JPH::ColorArg inColor) override;
   virtual void DrawTriangle(JPH::RVec3Arg inV1, JPH::RVec3Arg inV2, JPH::RVec3Arg inV3, JPH::ColorArg inColor, ECastShadow inCastShadow) override;
   virtual JPH::DebugRenderer::Batch CreateTriangleBatch(const Triangle* inTriangles, int inTriangleCount) override;
   virtual JPH::DebugRenderer::Batch CreateTriangleBatch(const Vertex* inVertices, int inVertexCount, const JPH::uint32* inIndices, int inIndexCount) override;
   virtual void DrawGeometry(JPH::RMat44Arg inModelMatrix, const JPH::AABox& inWorldSpaceBounds, float inLODScaleSq, JPH::ColorArg inModelColor, const GeometryRef& inGeometry, ECullMode inCullMode, ECastShadow inCastShadow, EDrawMode inDrawMode) override;
   virtual void DrawText3D(JPH::RVec3Arg inPosition, const JPH::string_view& inString, JPH::ColorArg inColor, float inHeight) override {};

   /// Implementation specific batch object
   class BatchImpl : public JPH::RefTargetVirtual
   {
   public:
      JPH_OVERRIDE_NEW_DELETE

         virtual void AddRef() override
      {
         ++mRefCount;
      }
      virtual void Release() override
      {
         if (--mRefCount == 0)
            delete this;
      }

      JPH::Array<JPH::DebugRenderer::Triangle> mTriangles;

   private:
      JPH::atomic<U32> mRefCount = 0;
   };
};
#endif

class JoltPlugin : public PhysicsPlugin
{
public:
   JoltPlugin();
   ~JoltPlugin();

   /// Create function for factory.
   static PhysicsPlugin* create();

   // PhysicsPlugin
   virtual void destroyPlugin();
   virtual void reset();
   virtual PhysicsCollision* createCollision();
   virtual PhysicsBody* createBody();
   virtual PhysicsPlayer* createPlayer();
   virtual bool isSimulationEnabled() const;
   virtual void enableSimulation(const String& worldName, bool enable);
   virtual void setTimeScale(const F32 timeScale);
   virtual const F32 getTimeScale() const;
   virtual bool createWorld(const String& worldName);
   virtual void destroyWorld(const String& worldName);
   virtual PhysicsWorld* getWorld(const String& worldName) const;
   virtual PhysicsWorld* getWorld() const;
   virtual U32 getWorldCount() const;
};

#endif // !_T3D_JOLT_PLUGIN_H_
