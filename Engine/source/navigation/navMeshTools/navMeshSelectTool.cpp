#include "navMeshSelectTool.h"
#include "console/consoleTypes.h"
#include "gfx/gfxDrawUtil.h"

IMPLEMENT_CONOBJECT(NavMeshSelectTool);

static void renderBoxOutline(const Box3F& box, const ColorI& col)
{
   if (box != Box3F::Invalid)
   {
      GFXStateBlockDesc desc;
      desc.setCullMode(GFXCullNone);
      desc.setFillModeSolid();
      desc.setZReadWrite(true, false);
      desc.setBlend(true);
      GFX->getDrawUtil()->drawCube(desc, box, ColorI(col, 20));
      desc.setFillModeWireframe();
      desc.setBlend(false);
      GFX->getDrawUtil()->drawCube(desc, box, ColorI(col, 255));
   }
}

NavMeshSelectTool::NavMeshSelectTool()
{
   mCurMesh = NULL;
}

void NavMeshSelectTool::onActivated(const Gui3DMouseEvent& evt)
{
   Con::executef(this, "onActivated");
}

void NavMeshSelectTool::onDeactivated()
{
   Con::executef(this, "onDeactivated");
}

void NavMeshSelectTool::on3DMouseDown(const Gui3DMouseEvent& evt)
{
   if (mCurEditor.isNull())
      return;

   Point3F startPnt = evt.pos;
   Point3F endPnt = evt.pos + evt.vec * 1000.0f;

   RayInfo ri;
   if (gServerContainer.castRay(startPnt, endPnt, MarkerObjectType, &ri))
   {
      if (!ri.object)
         return;

      NavMesh* selNavMesh = dynamic_cast<NavMesh*>(ri.object);
      if (selNavMesh)
      {
         mCurEditor->selectMesh(selNavMesh);
         return;
      }
   }

}

void NavMeshSelectTool::on3DMouseMove(const Gui3DMouseEvent& evt)
{
   if (mCurEditor.isNull())
      return;

   Point3F startPnt = evt.pos;
   Point3F endPnt = evt.pos + evt.vec * 1000.0f;

   RayInfo ri;
   if (gServerContainer.castRay(startPnt, endPnt, MarkerObjectType, &ri))
   {
      NavMesh* selNavMesh = dynamic_cast<NavMesh*>(ri.object);
      if (selNavMesh)
      {
         mCurMesh = selNavMesh;
      }
      else
      {
         mCurMesh = NULL;
      }
   }
   else
   {
      mCurMesh = NULL;
   }
}

void NavMeshSelectTool::onRender3D()
{
   if (!mCurMesh.isNull())
      renderBoxOutline(mCurMesh->getWorldBox(), ColorI::LIGHT);
}

bool NavMeshSelectTool::updateGuiInfo()
{
   SimObject* statusbar;
   Sim::findObject("EditorGuiStatusBar", statusbar);

   GuiTextCtrl* selectionBar;
   Sim::findObject("EWorldEditorStatusBarSelection", selectionBar);

   String text;

   if (statusbar)
      Con::executef(statusbar, "setInfo", text.c_str());

   if (selectionBar)
      selectionBar->setText(text);

   return true;
}
