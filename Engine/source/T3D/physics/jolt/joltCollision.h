#ifndef _JOLTCOLLISION_H_
#define _JOLTCOLLISION_H_

#ifndef _T3D_PHYSICS_PHYSICSCOLLISION_H_
#include "T3D/physics/physicsCollision.h"
#endif

#ifndef _T3D_JOLT_PLUGIN_H_
#include "T3D/physics/jolt/joltPlugin.h"
#endif

#ifndef _MMATRIX_H_
#include "math/mMatrix.h"
#endif

#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif

struct ChildShapeEntry
{
   JPH::Ref<JPH::Shape> shape;
   JPH::Mat44 localXfm;
   JPH::Vec3 localPos;
   JPH::Quat localRot;
};

class JoltCollision : public PhysicsCollision
{
private:
   JPH::Ref<JPH::Shape> mCompundShape;
   Vector<ChildShapeEntry> mChildren;

public:
   JoltCollision();
   virtual ~JoltCollision();

   // Add basic primitives
   void addPlane(const PlaneF& plane) override;

   void addBox(const Point3F& halfWidth, const MatrixF& localXfm) override;
   void addSphere(F32 radius, const MatrixF& localXfm) override;
   void addCapsule(F32 radius, F32 height, const MatrixF& localXfm) override;
   bool addConvex(const Point3F* points, U32 count, const MatrixF& localXfm) override;
   bool addTriangleMesh(const Point3F* vert, U32 vertCount,
      const U32* index, U32 triCount,
      const MatrixF& localXfm) override;
   bool addHeightfield(const U16* heights, const bool* holes, U32 blockSize, F32 metersPerSample, const MatrixF& localXfm) override;

   void rebuildCompound();

   JPH::Ref<JPH::Shape> getJoltShape() const { return mCompundShape; }
};

/// A strong pointer to a reference counted JoltCollision.
typedef StrongRefPtr<JoltCollision> JoltCollisionRef;


/// A weak pointer to a reference counted JoltCollision.
typedef WeakRefPtr<JoltCollision> JoltCollisionWeakRef;

#endif // !_JOLTCOLLISION_H_
