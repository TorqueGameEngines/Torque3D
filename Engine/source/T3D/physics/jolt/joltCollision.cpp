#include "T3D/physics/jolt/joltCollision.h"

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
   auto rtsSettings = new JPH::RotatedTranslatedShapeSettings(localPos, localRot, baseShape);
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

   auto rtsSettings = new JPH::RotatedTranslatedShapeSettings(localPos, localRot, baseShape);
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

   auto rtsSettings = new JPH::RotatedTranslatedShapeSettings(localPos, localRot, baseShape);
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

   std::vector<JPH::Vec3> verts;
   verts.reserve(count);
   for (U32 i = 0; i < count; ++i)
      verts.emplace_back(points[i].x, points[i].y, points[i].z);

   JPH::ConvexHullShapeSettings settings(verts.data(), verts.size());
   auto result = settings.Create();
   if (result.HasError())
   {
      Con::errorf("Jolt Error: %s", result.GetError().c_str());
      return false;
   }

   auto baseShape = result.Get();

   JPH::Vec3 localPos;
   JPH::Quat localRot;
   toJolt(localXfm, localPos, localRot);

   auto rtsSettings = new JPH::RotatedTranslatedShapeSettings(localPos, localRot, baseShape);
   auto rtsShape = rtsSettings->Create().Get();

   ChildShapeEntry entry;
   entry.shape = rtsShape;
   entry.localPos = localPos;
   entry.localRot = localRot;
   entry.localXfm = joltCast(localXfm);
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
   auto result = settings.Create();
   if (result.HasError())
   {
      Con::errorf("Jolt Error: %s", result.GetError().c_str());
      return false;
   }

   auto baseShape = result.Get();

   JPH::Vec3 localPos;
   JPH::Quat localRot;
   toJolt(localXfm, localPos, localRot);

   auto rtsSettings = new JPH::RotatedTranslatedShapeSettings(localPos, localRot, baseShape);
   auto rtsShape = rtsSettings->Create().Get();

   ChildShapeEntry entry;
   entry.shape = rtsShape;
   entry.localPos = localPos;
   entry.localRot = localRot;
   entry.localXfm = joltCast(localXfm);
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

   const F32 heightScale = 0.03125f;
   const F32 minHeight = 0;
   const F32 maxHeight = 65535 * heightScale;

   const U32 sampleCount = blockSize * blockSize;
   std::vector<float> samples(sampleCount);

   for (U32 x = 0; x < blockSize; ++x)
   {
      for (U32 y = 0; y < blockSize; ++y)
      {
         // Terrain storage (row-major)
         U32 srcIdx = y * blockSize + x;

         // Flip Z direction for Jolt
         U32 dstIdx = (blockSize - 1 - y) * blockSize + x;

         float h = float(heightData[srcIdx]) * heightScale;

         if (holes && holes[srcIdx])
            h = JPH::HeightFieldShapeConstants::cNoCollisionValue;

         samples[dstIdx] = h;
      }
   }

   float terrainSize = blockSize * metersPerSample;
   float verticalAdjust = -heightScale * 0.5f;
   JPH::Vec3 joltOffset(
    0.0,
    verticalAdjust,
    -terrainSize
);

   JPH::Vec3 joltScale(metersPerSample,1.0f, metersPerSample);

   JPH::HeightFieldShapeSettings settings(samples.data(), joltOffset, joltScale, blockSize);

   auto result = settings.Create();
   if (result.HasError())
   {
      Con::errorf("Jolt Error: %s", result.GetError().c_str());
      return false;
   }

   auto baseShape = result.Get();

   JPH::Vec3 localPos;
   JPH::Quat localRot;
   toJolt(localXfm, localPos, localRot);
   JPH::Quat rotFix = JPH::Quat::sRotation(JPH::Vec3::sAxisX(), JPH::DegreesToRadians(90.0f));
   localRot = rotFix * localRot;

   auto rtsSettings = new JPH::RotatedTranslatedShapeSettings(localPos, localRot, baseShape);
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
