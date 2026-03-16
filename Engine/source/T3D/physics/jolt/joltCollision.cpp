#include "T3D/physics/jolt/joltCollision.h"

#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Collision/Shape/CapsuleShape.h>
#include <Jolt/Physics/Collision/Shape/ConvexHullShape.h>
#include <Jolt/Physics/Collision/Shape/TriangleShape.h>
#include <Jolt/Physics/Collision/Shape/HeightFieldShape.h>
#include <Jolt/Physics/Collision/Shape/PlaneShape.h>
#include <Jolt/Physics/Collision/Shape/CompoundShape.h>
#include <Jolt/Physics/Collision/Shape/MeshShape.h>
#include <Jolt/Physics/Collision/Shape/StaticCompoundShape.h>

JoltCollision::JoltCollision()
{
   VECTOR_SET_ASSOCIATION(mChildren);
}

JoltCollision::~JoltCollision()
{
}

void JoltCollision::addPlane(const PlaneF& plane)
{
   JPH::Plane joltPlane({ plane.x, plane.y, plane.z }, plane.d);
   JPH::PlaneShapeSettings settings(joltPlane);

   ChildShapeEntry entry;
   entry.shape = settings.Create().Get();
   entry.localXfm = JPH::Mat44::sIdentity();  // Plane at origin by default
   entry.localPos = JPH::Vec3::sZero();
   entry.localRot = JPH::Quat::sIdentity();
   mChildren.push_back(entry);

   rebuildCompound();
}

void JoltCollision::addBox(const Point3F& halfWidth, const MatrixF& localXfm)
{
   JPH::BoxShapeSettings settings(JPH::Vec3(halfWidth.x, halfWidth.y, halfWidth.z));
   ChildShapeEntry entry;
   entry.shape = settings.Create().Get();
   entry.localXfm = toJolt(localXfm);
   mChildren.push_back(entry);

   rebuildCompound();
}

void JoltCollision::addSphere(F32 radius, const MatrixF& localXfm)
{
   JPH::SphereShapeSettings settings(radius);
   ChildShapeEntry entry;
   entry.shape = settings.Create().Get();
   entry.localXfm = toJolt(localXfm);
   mChildren.push_back(entry);

   rebuildCompound();
}

void JoltCollision::addCapsule(F32 radius, F32 height, const MatrixF& localXfm)
{
   JPH::CapsuleShapeSettings settings(radius, height);
   ChildShapeEntry entry;
   entry.shape = settings.Create().Get();
   entry.localXfm = toJolt(localXfm);
   mChildren.push_back(entry);

   rebuildCompound();
}

bool JoltCollision::addConvex(const Point3F* points, U32 count, const MatrixF& localXfm)
{
   if (count == 0) return false;

   std::vector<JPH::Vec3> verts;
   verts.reserve(count);
   for (U32 i = 0; i < count; ++i)
      verts.emplace_back(points[i].x, points[i].y, points[i].z);

   JPH::ConvexHullShapeSettings settings(verts.data(), verts.size());
   ChildShapeEntry entry;
   entry.shape = settings.Create().Get();
   JPH::Vec3 localPos;
   JPH::Quat localRot;
   toJolt(localXfm, localPos, localRot);

   entry.localPos = localPos;
   entry.localRot = localRot;
   entry.localXfm = toJolt(localXfm);
   mChildren.push_back(entry);

   rebuildCompound();
   return true;
}

bool JoltCollision::addTriangleMesh(const Point3F* vert, U32 vertCount, const U32* index, U32 triCount, const MatrixF& localXfm)
{
   if (!vert || !index || vertCount == 0 || triCount == 0)
      return false;

   // Build the TriangleList
   JPH::TriangleList triangles;
   triangles.reserve(triCount);

   for (U32 i = 0; i < triCount; ++i)
   {
      const Point3F& v0 = vert[index[i * 3 + 0]];
      const Point3F& v1 = vert[index[i * 3 + 1]];
      const Point3F& v2 = vert[index[i * 3 + 2]];

      triangles.push_back(
         JPH::Triangle(
            JPH::Float3(v0.x, v0.y, v0.z),
            JPH::Float3(v1.x, v1.y, v1.z),
            JPH::Float3(v2.x, v2.y, v2.z),
            0, // material index
            i  // user data = original triangle index
         )
      );
   }

   // Create the MeshShape
   JPH::MeshShapeSettings settings(triangles);

   ChildShapeEntry entry;
   entry.shape = settings.Create().Get();
   entry.localXfm = toJolt(localXfm);
   mChildren.push_back(entry);

   rebuildCompound();

   return true;
}

bool JoltCollision::addHeightfield(const U16* heightData, const bool* holes, U32 size, F32 scale, const MatrixF& localXfm)
{
   if (!heightData) return false;

   std::vector<float> samples(size * size);

   // Convert U16 height data to float and apply scale
   for (U32 y = 0; y < size; ++y)
   {
      for (U32 x = 0; x < size; ++x)
      {
         U32 idx = y * size + x;
         float h = static_cast<float>(heightData[idx]) * scale;

         // Mark holes with a sentinel value (Jolt uses FLT_MAX for cNoCollisionValue)
         if (holes && holes[idx])
            h = JPH::HeightFieldShapeConstants::cNoCollisionValue;

         samples[idx] = h;
      }
   }

   JPH::HeightFieldShapeSettings settings(
      samples.data(),                               // pointer to float samples
      JPH::Vec3(0, 0, 0),                           // offset (can adjust for origin)
      JPH::Vec3(1, 1, 1),                           // scale (can adjust per axis)
      size                                          // sample count
      // Optional: material indices and material list can be added if needed
   );

   ChildShapeEntry entry;
   entry.shape = settings.Create().Get();
   JPH::RVec3 pos;
   JPH::Quat rot;
   toJolt(localXfm, pos, rot);

   entry.localXfm = JPH::RMat44::sRotationTranslation(rot, pos);
   mChildren.push_back(entry);

   rebuildCompound();
   return true;
}

void JoltCollision::rebuildCompound()
{
   if (mChildren.empty())
      return;

   JPH::CompoundShapeSettings* compoundSettings = nullptr;

   if (mChildren.size() > 1)
   {
      compoundSettings = new JPH::StaticCompoundShapeSettings();
   }

   for (auto& colShape : mChildren)
   {
      if (compoundSettings)
      {
         compoundSettings->AddShape(
            colShape.localPos,
            colShape.localRot,
            colShape.shape
         );
      }
      else
      {
         mCompundShape = colShape.shape;
      }
   }

   if (compoundSettings)
   {
      mCompundShape = compoundSettings->Create().Get();
      delete compoundSettings;
   }

}
