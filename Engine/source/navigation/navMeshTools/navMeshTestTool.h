#ifndef _NAVMESHTESTTOOL_H_
#define _NAVMESHTESTTOOL_H_


#ifndef _NAVMESH_TOOL_H_
#include "navigation/navMeshTool.h"
#endif

#ifndef _NAVPATH_H_
#include "navigation/navPath.h"
#endif

class NavMeshTestTool : public NavMeshTool
{
   typedef NavMeshTool Parent;
protected:
   String mSpawnClass;
   String mSpawnDatablock;
   SimObjectPtr<SceneObject> mPlayer;
   SimObjectPtr<SceneObject> mCurPlayer;
   SimObjectPtr<SceneObject> mFollowObject;
   SimObjectPtr<SceneObject> mCurFollowObject;
   Point3F mPathStart;
   Point3F mPathEnd;
   NavPath* mTestPath;
   LinkData mLinkTypes;
   dtQueryFilter mFilter;
   bool mSelectFollow;

public:
   DECLARE_CONOBJECT(NavMeshTestTool);

   void spawnPlayer(const Point3F& position);

   void drawAgent(duDebugDrawTorque& dd, const F32* pos, F32 r, F32 h, F32 c, const U32 col);

   NavMeshTestTool();

   virtual ~NavMeshTestTool() {}

   void onActivated(const Gui3DMouseEvent& evt) override;
   void onDeactivated() override;

   void on3DMouseDown(const Gui3DMouseEvent& evt) override;
   void on3DMouseMove(const Gui3DMouseEvent& evt) override;
   void onRender3D() override;

   bool updateGuiInfo() override;

   S32 getPlayerId();
   S32 getFollowObjectId();

   void setSpawnClass(String className) { mSpawnClass = className; }
   void setSpawnDatablock(String dbName) { mSpawnDatablock = dbName; }
   void followSelectMode() { mSelectFollow = true; }

};


#endif // !_NAVMESHTESTTOOL_H_
