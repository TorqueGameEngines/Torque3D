#include "T3D/physics/jolt/joltCollision.h"
#include "terrain/terrFile.h"

// Save and undefine the macro if it exists
#ifdef Offset
#pragma push_macro("Offset")
#undef Offset
#endif

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
#include <Jolt/Physics/Collision/Shape/RotatedTranslatedShape.h>

#ifdef Offset
    // Restore the original macro after includes
#pragma pop_macro("Offset")
#endif

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
   JPH::PlaneShapeSettings planeSettings(joltPlane);
   auto result = planeSettings.Create();
   if (result.HasError())
   {
      Con::errorf("Jolt Error: %s", result.GetError().c_str());
      return;
   }

   ChildShapeEntry entry;
   entry.shape = result.Get();
   entry.localXfm = JPH::Mat44::sIdentity();  // Plane at origin by default
   entry.localPos = JPH::Vec3::sZero();
   entry.localRot = JPH::Quat::sIdentity();
   mChildren.push_back(entry);

   rebuildCompound();
}

void JoltCollision::addBox(const Point3F& halfWidth, const MatrixF& localXfm)
{
   JPH::BoxShapeSettings boxSettings(JPH::Vec3(halfWidth.x, halfWidth.y, halfWidth.z));

   auto result = boxSettings.Create();
   if (result.HasError())
   {
      Con::errorf("Jolt Error: %s", result.GetError().c_str());
      return;
   }

   auto baseShape = result.Get();

   // Convert engine matrix to Jolt position + rotation
   JPH::Vec3 localPos;
   JPH::Quat localRot;
   toJolt(localXfm, localPos, localRot);

   // Wrap the base shape with RotatedTranslatedShape
   JPH::Ref<JPH::RotatedTranslatedShapeSettings> rtsSettings = new JPH::RotatedTranslatedShapeSettings(localPos, localRot, baseShape);
   auto rtsShape = rtsSettings->Create().Get();

   // Store in child entry
   ChildShapeEntry entry;
   entry.shape = rtsShape;
   entry.localPos = localPos;
   entry.localRot = localRot;
   entry.localXfm = joltCast(localXfm);
   mChildren.push_back(entry);

   rebuildCompound();
}

void JoltCollision::addSphere(F32 radius, const MatrixF& localXfm)
{
   JPH::SphereShapeSettings settings(radius);
   auto result = settings.Create();
   if (result.HasError())
   {
      Con::errorf("Jolt Error: %s", result.GetError().c_str());
      return;
   }

   auto baseShape = result.Get();

   JPH::Vec3 localPos;
   JPH::Quat localRot;
   toJolt(localXfm, localPos, localRot);

   JPH::Ref<JPH::RotatedTranslatedShapeSettings> rtsSettings = new JPH::RotatedTranslatedShapeSettings(localPos, localRot, baseShape);
   auto rtsShape = rtsSettings->Create().Get();

   ChildShapeEntry entry;
   entry.shape = rtsShape;
   entry.localPos = localPos;
   entry.localRot = localRot;
   entry.localXfm = joltCast(localXfm);
   mChildren.push_back(entry);

   rebuildCompound();
}

void JoltCollision::addCapsule(F32 radius, F32 height, const MatrixF& localXfm)
{
   JPH::CapsuleShapeSettings settings(radius, height);
   auto result = settings.Create();
   if (result.HasError())
   {
      Con::errorf("Jolt Error: %s", result.GetError().c_str());
      return;
   }

   auto baseShape = result.Get();

   JPH::Vec3 localPos;
   JPH::Quat localRot;
   toJolt(localXfm, localPos, localRot);

   JPH::Ref<JPH::RotatedTranslatedShapeSettings> rtsSettings = new JPH::RotatedTranslatedShapeSettings(localPos, localRot, baseShape);
   auto rtsShape = rtsSettings->Create().Get();

   ChildShapeEntry entry;
   entry.shape = rtsShape;
   entry.localPos = localPos;
   entry.localRot = localRot;
   entry.localXfm = joltCast(localXfm);
   mChildren.push_back(entry);

   rebuildCompound();
}

bool JoltCollision::addConvex(const Point3F* points, U32 count, const MatrixF& localXfm)
{
   if (count == 0)
      return false;

   // Pre-transform points into shape-local space for the same reason as
   // addTriangleMesh: avoids the RTS wrapper and the double-transform in
   // rebuildCompound when multiple shapes share a JoltCollision.
   const bool isIdentity = localXfm.isIdentity();

   std::vector<JPH::Vec3> verts;
   verts.reserve(count);
   for (U32 i = 0; i < count; ++i)
   {
      Point3F p = points[i];
      if (!isIdentity)
         localXfm.mulP(points[i], &p);
      verts.emplace_back(p.x, p.y, p.z);
   }

   JPH::ConvexHullShapeSettings settings(verts.data(), (int)verts.size());
   auto result = settings.Create();
   if (result.HasError())
   {
      Con::errorf("Jolt addConvex Error: %s", result.GetError().c_str());
      return false;
   }

   ChildShapeEntry entry;
   entry.shape = result.Get();
   entry.localPos = JPH::Vec3::sZero();
   entry.localRot = JPH::Quat::sIdentity();
   entry.localXfm = JPH::Mat44::sIdentity();
   mChildren.push_back(entry);

   rebuildCompound();
   return true;
}

bool JoltCollision::addTriangleMesh(const Point3F* vert, U32 vertCount, const U32* index, U32 triCount, const MatrixF& localXfm)
{
   if (!vert || !index || vertCount == 0 || triCount == 0)
      return false;

   // Bake localXfm directly into the vertex positions so the MeshShape sits in
   // shape-local space with an identity transform. This avoids the need for an
   // RTS wrapper and eliminates the double-transform bug that occurs when the
   // wrapper's position is later re-applied by rebuildCompound's AddShape call.
   const bool isIdentity = localXfm.isIdentity();

   JPH::TriangleList triangles;
   triangles.reserve(triCount);

   for (U32 i = 0; i < triCount; ++i)
   {
      Point3F p0 = vert[index[i * 3 + 0]];
      Point3F p1 = vert[index[i * 3 + 1]];
      Point3F p2 = vert[index[i * 3 + 2]];

      if (!isIdentity)
      {
         localXfm.mulP(vert[index[i * 3 + 0]], &p0);
         localXfm.mulP(vert[index[i * 3 + 1]], &p1);
         localXfm.mulP(vert[index[i * 3 + 2]], &p2);
      }

      triangles.push_back(
         JPH::Triangle(
            JPH::Float3(p0.x, p0.y, p0.z),
            JPH::Float3(p2.x, p2.y, p2.z),  // winding order maintained
            JPH::Float3(p1.x, p1.y, p1.z),
            0, // material index
            i  // user data = original triangle index
         )
      );
   }

   JPH::MeshShapeSettings settings(triangles);
   auto result = settings.Create();
   if (result.HasError())
   {
      Con::errorf("Jolt addTriangleMesh Error: %s", result.GetError().c_str());
      return false;
   }

   // Store at identity — vertices are already in shape-local space.
   ChildShapeEntry entry;
   entry.shape = result.Get();
   entry.localPos = JPH::Vec3::sZero();
   entry.localRot = JPH::Quat::sIdentity();
   entry.localXfm = JPH::Mat44::sIdentity();
   mChildren.push_back(entry);

   rebuildCompound();
   return true;
}

bool JoltCollision::addHeightfield(
   const U16* heightData,
   const bool* holes,
   U32 blockSize,
   F32 metersPerSample,
   const MatrixF& localXfm) // We won’t use localXfm directly
{
   if (!heightData || blockSize == 0)
      return false;

   // Jolt's internal BVH page size: power-of-2 between 2 and 8, independent of
   // inSampleCount. Use 4 for larger terrains to produce a shallower BVH tree.
   const U32 joltBlockSize = (blockSize >= 512) ? 4 : 2;

   // inSampleCount must be a multiple of joltBlockSize. Round up so any blockSize
   // works — padding columns/rows are edge-clamped to stay physically correct.
   const U32 paddedSize = ((blockSize + joltBlockSize - 1) / joltBlockSize) * joltBlockSize;
   const U32 totalSamples = paddedSize * paddedSize;

   // Pass 1: build a flat (un-flipped) padded grid with edge-clamping.
   std::vector<float> unflipped(totalSamples);
   for (U32 y = 0; y < paddedSize; ++y)
   {
      U32 srcY = (y < blockSize) ? y : blockSize - 1;
      for (U32 x = 0; x < paddedSize; ++x)
      {
         U32 srcX = (x < blockSize) ? x : blockSize - 1;
         U32 srcIdx = srcY * blockSize + srcX;

         float h = fixedToFloat(heightData[srcIdx]);
         if (holes && holes[srcIdx])
            h = JPH::HeightFieldShapeConstants::cNoCollisionValue;

         unflipped[y * paddedSize + x] = h;
      }
   }

   // Pass 2: flip Y axis into the final sample array for Jolt's coordinate system.
   std::vector<float> samples(totalSamples);
   for (U32 y = 0; y < paddedSize; ++y)
      for (U32 x = 0; x < paddedSize; ++x)
         samples[(paddedSize - 1 - y) * paddedSize + x] = unflipped[y * paddedSize + x];

   // Offset uses actual terrain extent (blockSize) so the padded fringe never
   // shifts the visible terrain. The vertical adjustment centres quantisation error.
   const float heightScale = 0.03125f;
   const float verticalAdjust = -heightScale * 0.5f;
   const float terrainSize = blockSize * metersPerSample;

   JPH::Vec3 joltOffset(0.0f, verticalAdjust, -terrainSize);
   JPH::Vec3 joltScale(metersPerSample, 1.0f, metersPerSample);

   JPH::HeightFieldShapeSettings settings(samples.data(), joltOffset, joltScale, paddedSize);
   settings.mBlockSize = joltBlockSize;

   auto result = settings.Create();
   if (result.HasError())
   {
      Con::errorf("Jolt addHeightfield Error (blockSize=%u paddedSize=%u): %s",
         blockSize, paddedSize, result.GetError().c_str());
      return false;
   }

   auto baseShape = result.Get();

   JPH::Vec3 localPos;
   JPH::Quat localRot;
   toJolt(localXfm, localPos, localRot);
   JPH::Quat rotFix = JPH::Quat::sRotation(JPH::Vec3::sAxisX(), JPH::DegreesToRadians(90.0f));
   localRot = rotFix * localRot;

   JPH::Ref<JPH::RotatedTranslatedShapeSettings> rtsSettings = new JPH::RotatedTranslatedShapeSettings(localPos, localRot, baseShape);
   auto rtsShape = rtsSettings->Create().Get();

   ChildShapeEntry entry;
   entry.shape = rtsShape;
   entry.localPos = localPos;
   entry.localRot = localRot;
   mChildren.push_back(entry);

   rebuildCompound();

   return true;
}

void JoltCollision::rebuildCompound()
{
   if (mChildren.empty())
      return;

   if (mChildren.size() == 1)
   {
      // Single shape: use it directly. For primitive shapes this is the
      // RotatedTranslatedShape with the local transform baked in. For
      // triangle meshes and convex hulls it is the base shape at identity.
      mCompundShape = mChildren[0].shape;
      return;
   }

   // Multiple shapes: build a static compound. Each child's ChildShapeEntry
   // already has its local transform baked into entry.shape (either as an RTS
   // wrapper for primitives, or pre-transformed vertices for meshes/convex).
   // Using localPos/localRot here would apply the offset a SECOND time.
   JPH::StaticCompoundShapeSettings compoundSettings;
   for (const auto& child : mChildren)
   {
      compoundSettings.AddShape(
         JPH::Vec3::sZero(),
         JPH::Quat::sIdentity(),
         child.shape
      );
   }

   auto result = compoundSettings.Create();
   if (result.HasError())
   {
      Con::errorf("Jolt rebuildCompound Error: %s", result.GetError().c_str());
      return;
   }

   mCompundShape = result.Get();
}
