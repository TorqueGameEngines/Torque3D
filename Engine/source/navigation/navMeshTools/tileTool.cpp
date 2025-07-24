#include "tileTool.h"
#include "navigation/guiNavEditorCtrl.h"
#include "console/consoleTypes.h"
#include "gfx/gfxDrawUtil.h"
#include "scene/sceneManager.h"
#include "math/mathUtils.h"

IMPLEMENT_CONOBJECT(TileTool);

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

void TileTool::onActivated(const Gui3DMouseEvent& lastEvent)
{
   Con::executef(this, "onActivated");
}

void TileTool::onDeactivated()
{
   Con::executef(this, "onDeactivated");
}

void TileTool::on3DMouseDown(const Gui3DMouseEvent& evt)
{
   if (mNavMesh.isNull())
      return;

   Point3F start = evt.pos;
   Point3F end = evt.pos + evt.vec * 1000.0f;

   RayInfo ri;
   if (gServerContainer.castRay(start, end, StaticObjectType, &ri))
   {
      mSelTile = mNavMesh->getTile(ri.point);
   }
}

void TileTool::on3DMouseMove(const Gui3DMouseEvent& evt)
{
   if (mNavMesh.isNull())
      return;

   Point3F startPnt = evt.pos;
   Point3F endPnt = evt.pos + evt.vec * 1000.0f;

   RayInfo ri;

   if (gServerContainer.castRay(startPnt, endPnt, StaticObjectType, &ri))
      mCurTile = mNavMesh->getTile(ri.point);
   else
      mCurTile = -1;
}

void TileTool::onRender3D()
{
   if (mNavMesh.isNull())
      return;

   if(mCurTile != -1)
      renderBoxOutline(mNavMesh->getTileBox(mCurTile), ColorI::BLUE);

   if(mSelTile != -1)
      renderBoxOutline(mNavMesh->getTileBox(mSelTile), ColorI::GREEN);
}

void TileTool::buildTile()
{
   if (!mNavMesh.isNull() && mSelTile != -1)
      mNavMesh->buildTile(mSelTile);
}

bool TileTool::updateGuiInfo()
{
   SimObject* statusbar;
   Sim::findObject("EditorGuiStatusBar", statusbar);

   GuiTextCtrl* selectionBar;
   Sim::findObject("EWorldEditorStatusBarSelection", selectionBar);

   String text;

   text = "LMB To select NavMesh Tile";

   if (statusbar)
      Con::executef(statusbar, "setInfo", text.c_str());

   if (mSelTile != -1)
      text = String::ToString("Selected Tile: %d", mSelTile);
   else
      text = "";

   if (selectionBar)
      selectionBar->setText(text);

   return true;
}

DefineEngineMethod(TileTool, buildTile, void, (), ,
   "@brief Build the currently selected tile.")
{
   return object->buildTile();
}
