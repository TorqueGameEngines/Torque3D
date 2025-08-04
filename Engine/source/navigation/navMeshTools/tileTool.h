#ifndef _TILETOOL_H_
#define _TILETOOL_H_


#ifndef _NAVMESH_TOOL_H_
#include "navigation/navMeshTool.h"
#endif

class TileTool : public NavMeshTool
{
   typedef NavMeshTool Parent;
   S32 mCurTile;
   S32 mSelTile;
public:
   DECLARE_CONOBJECT(TileTool);

   TileTool() { mCurTile = -1; mSelTile = -1; }
   virtual ~TileTool() {}

   void onActivated(const Gui3DMouseEvent& evt) override;
   void onDeactivated() override;

   void on3DMouseDown(const Gui3DMouseEvent& evt) override;
   void on3DMouseMove(const Gui3DMouseEvent& evt) override;
   void onRender3D() override;
   void buildTile();

   bool updateGuiInfo() override;
};

#endif
