#include "offMeshConnTool.h"
#include "navigation/guiNavEditorCtrl.h"
#include "console/consoleTypes.h"
#include "gfx/gfxDrawUtil.h"
#include "scene/sceneManager.h"
#include "math/mathUtils.h"

IMPLEMENT_CONOBJECT(OffMeshConnectionTool);

void OffMeshConnectionTool::onActivated(const Gui3DMouseEvent& evt)
{
   Con::executef(this, "onActivated");
}

void OffMeshConnectionTool::onDeactivated()
{
   Con::executef(this, "onDeactivated");
}

void OffMeshConnectionTool::on3DMouseDown(const Gui3DMouseEvent& evt)
{
   if (mNavMesh.isNull())
      return;

   Point3F startPnt = evt.pos;
   Point3F endPnt = evt.pos + evt.vec * 1000.0f;

   RayInfo ri;
   bool shift = evt.modifier & SI_LSHIFT;
   bool ctrl = evt.modifier & SI_LCTRL;

   if (gServerContainer.castRay(startPnt, endPnt, StaticObjectType, &ri))
   {
      U32 link = mNavMesh->getLink(ri.point);
      if (link != -1)
      {
         if (mLink != -1)
            mNavMesh->selectLink(mLink, false);
         mNavMesh->selectLink(link, true, false);
         mLink = link;

         if (ctrl)
         {
            mNavMesh->selectLink(mLink, false);
            mNavMesh->deleteLink(mLink);
            mLink = -1;
            Con::executef(this, "onLinkDeselected");
            return;
         }
         else
         {
            LinkData d = mNavMesh->getLinkFlags(mLink);
            bool biDir = mNavMesh->getLinkDir(mLink);
            F32 linkRad = mNavMesh->getLinkRadius(mLink);
            Con::executef(this, "onLinkSelected", Con::getIntArg(d.getFlags()), Con::getBoolArg(biDir), Con::getFloatArg(linkRad));
         }
      }
      else
      {
         if (mLink != -1)
         {
            mNavMesh->selectLink(mLink, false);
            mLink = -1;
            Con::executef(this, "onLinkDeselected");
         }

         if (mLinkStart != Point3F::Max)
         {
            mLink = mNavMesh->addLink(mLinkStart, ri.point, mBiDir, mLinkRadius);
            mNavMesh->selectLink(mLink, true, false);

            if (shift)
               mLinkStart = ri.point;
            else
               mLinkStart = Point3F::Max;

            Con::executef(this, "onLinkSelected", Con::getIntArg(mLinkCache.getFlags()), Con::getBoolArg(mBiDir), Con::getFloatArg(mLinkRadius));
         }
         else
         {
            mLinkStart = ri.point;
         }
      }
   }
   else
   {
      if (mLink != -1)
      {
         mNavMesh->selectLink(mLink, false);
         mLink = -1;
         Con::executef(this, "onLinkDeselected");
      }
   }

}

void OffMeshConnectionTool::on3DMouseMove(const Gui3DMouseEvent& evt)
{
   if (mNavMesh.isNull())
      return;

   Point3F startPnt = evt.pos;
   Point3F endPnt = evt.pos + evt.vec * 1000.0f;

   RayInfo ri;
   if (gServerContainer.castRay(startPnt, endPnt, StaticObjectType, &ri))
   {
      U32 link = mNavMesh->getLink(ri.point);
      if (link != -1)
      {
         if (link != mLink)
         {
            if (mCurLink != -1)
               mNavMesh->selectLink(mCurLink, false);
            mNavMesh->selectLink(link, true, true);
         }
         mCurLink = link;
      }
      else
      {
         if (mCurLink != mLink)
            mNavMesh->selectLink(mCurLink, false);
         mCurLink = -1;
      }
   }
   else
   {
      mNavMesh->selectLink(mCurLink, false);
      mCurLink = -1;
   }
}

void OffMeshConnectionTool::onRender3D()
{
   if (mNavMesh.isNull())
      return;

   duDebugDrawTorque dd;

   if (mLinkStart != Point3F::Max)
   {
      Point3F rcFrom = DTStoRC(mLinkStart);
      dd.begin(DU_DRAW_LINES);
      dd.depthMask(false);
      duAppendCircle(&dd, rcFrom.x, rcFrom.y, rcFrom.z, mLinkRadius, duRGBA(0, 255, 0, 255));
      dd.end();
   }

   //mNavMesh->renderLinks(dd);

   dd.immediateRender();
}

bool OffMeshConnectionTool::updateGuiInfo()
{
   SimObject* statusbar;
   Sim::findObject("EditorGuiStatusBar", statusbar);

   GuiTextCtrl* selectionBar;
   Sim::findObject("EWorldEditorStatusBarSelection", selectionBar);

   String text;
   text = "LMB To Select Link. CTRL+LMB To Delete Link";

   if (mLinkStart != Point3F::Max)
      text = "LinkStarted: LMB To place End Point. Hold Left Shift to start a new Link from the end point.";

   if (statusbar)
      Con::executef(statusbar, "setInfo", text.c_str());

   if (mLink != -1)
      text = String::ToString("Selected Link: %d", mLink);
   else
      text = "";

   if (selectionBar)
      selectionBar->setText(text);

   return true;
}

void OffMeshConnectionTool::setLinkProperties(const LinkData& d, bool biDir, F32 rad)
{
   if (!mNavMesh.isNull() && mLink != -1)
   {
      mNavMesh->setLinkFlags(mLink, d);
      mNavMesh->setLinkDir(mLink, biDir);
      mNavMesh->setLinkRadius(mLink, rad);
   }

   mLinkCache = d;
   mBiDir = biDir;
   mLinkRadius = rad;
}

DefineEngineMethod(OffMeshConnectionTool, setLinkProperties, void, (U32 flags, bool biDir, F32 rad), ,
   "@Brief Set properties of the selected link.")
{
   object->setLinkProperties(LinkData(flags), biDir, rad);
}
