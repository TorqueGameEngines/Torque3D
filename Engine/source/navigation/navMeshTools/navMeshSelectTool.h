#ifndef _NAVMESHSELECTTOOL_H_
#define _NAVMESHSELECTTOOL_H_


#ifndef _NAVMESH_TOOL_H_
#include "navigation/navMeshTool.h"
#endif

class NavMeshSelectTool : public NavMeshTool
{
   typedef NavMeshTool Parent;
protected:
   SimObjectPtr<NavMesh> mCurMesh;
   SimObjectPtr<NavMesh> mSelMesh;
public:
   DECLARE_CONOBJECT(NavMeshSelectTool);

   NavMeshSelectTool();
   virtual ~NavMeshSelectTool() {}

   void setActiveNavMesh(NavMesh* nav_mesh) { mNavMesh = nav_mesh; mSelMesh = nav_mesh; }
   void onActivated(const Gui3DMouseEvent& evt) override;
   void onDeactivated() override;

   void on3DMouseDown(const Gui3DMouseEvent& evt) override;
   void on3DMouseMove(const Gui3DMouseEvent& evt) override;
   void onRender3D() override;

   bool updateGuiInfo() override;
};

#endif
