#ifndef _OFFMESHCONNTOOL_H_
#define _OFFMESHCONNTOOL_H_


#ifndef _NAVMESH_TOOL_H_
#include "navigation/navMeshTool.h"
#endif

class OffMeshConnectionTool : public NavMeshTool
{
   typedef NavMeshTool Parent;
   bool mStartPosSet;
   bool mBiDir;
   S32 mLink;
   S32 mCurLink;
   Point3F mLinkStart;
   LinkData mLinkCache;
   F32 mLinkRadius;
public:

   DECLARE_CONOBJECT(OffMeshConnectionTool);

   OffMeshConnectionTool() {
      mStartPosSet = false;
      mBiDir = false;
      mLink = -1;
      mCurLink = -1;
      mLinkStart = Point3F::Max;
      mLinkCache = LinkData(0);
      mLinkRadius = 1.0;
   }
   virtual ~OffMeshConnectionTool() {}

   void setActiveNavMesh(NavMesh* nav_mesh) override {
      mNavMesh = nav_mesh;

      if (!mNavMesh.isNull())
         mLinkRadius = mNavMesh->mWalkableRadius;
   }

   void onActivated(const Gui3DMouseEvent& evt) override;
   void onDeactivated() override;

   void on3DMouseDown(const Gui3DMouseEvent& evt) override;
   void on3DMouseMove(const Gui3DMouseEvent& evt) override;
   void onRender3D() override;

   bool updateGuiInfo() override;

   void setLinkProperties(const LinkData& d, bool biDir, F32 rad);
};

#endif
