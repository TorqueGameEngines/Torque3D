#include "coverTool.h"

IMPLEMENT_CONOBJECT(CoverTool);

CoverTool::CoverTool()
{
}

void CoverTool::onActivated(const Gui3DMouseEvent& evt)
{
   Con::executef(this, "onActivated");
}

void CoverTool::onDeactivated()
{
   Con::executef(this, "onDeactivated");
}

void CoverTool::on3DMouseDown(const Gui3DMouseEvent& evt)
{
   if (mNavMesh.isNull())
      return;
}

void CoverTool::on3DMouseMove(const Gui3DMouseEvent& evt)
{
   if (mNavMesh.isNull())
      return;
}

void CoverTool::onRender3D()
{
   if (mNavMesh.isNull())
      return;
}

bool CoverTool::updateGuiInfo()
{
   return false;
}
