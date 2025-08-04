//-----------------------------------------------------------------------------
// Copyright (c) 2014 Daniel Buckmaster
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------
#include "torqueConfig.h"
#ifdef TORQUE_TOOLS
#include "platform/platform.h"
#include "guiNavEditorCtrl.h"
#include "duDebugDrawTorque.h"
#include "console/engineAPI.h"

#include "console/consoleTypes.h"
#include "math/util/frustum.h"
#include "math/mathUtils.h"
#include "gfx/primBuilder.h"
#include "gfx/gfxDrawUtil.h"
#include "scene/sceneRenderState.h"
#include "scene/sceneManager.h"
#include "gui/core/guiCanvas.h"
#include "gui/buttons/guiButtonCtrl.h"
#include "gui/worldEditor/undoActions.h"
#include "T3D/gameBase/gameConnection.h"
#include "T3D/AI/AIController.h"
#include "navigation/navMeshTool.h"

IMPLEMENT_CONOBJECT(GuiNavEditorCtrl);

ConsoleDocClass(GuiNavEditorCtrl,
                "@brief GUI tool that makes up the Navigation Editor\n\n"
                "Editor use only.\n\n"
                "@internal"
                );

GuiNavEditorCtrl::GuiNavEditorCtrl()
{
   mIsDirty = false;
   mStartDragMousePoint = InvalidMousePoint;
   mMesh = NULL;
}

GuiNavEditorCtrl::~GuiNavEditorCtrl()
{
}

void GuiNavEditorUndoAction::undo()
{
}

bool GuiNavEditorCtrl::onAdd()
{
   if(!Parent::onAdd())
      return false;

   GFXStateBlockDesc desc;
   desc.fillMode = GFXFillSolid;
   desc.setBlend(false);
   desc.setZReadWrite(false, false);
   desc.setCullMode(GFXCullNone);

   mZDisableSB = GFX->createStateBlock(desc);

   desc.setZReadWrite(true, true);
   mZEnableSB = GFX->createStateBlock(desc);

   SceneManager::getPreRenderSignal().notify(this, &GuiNavEditorCtrl::_prepRenderImage);

   return true;
}

void GuiNavEditorCtrl::initPersistFields()
{
   docsURL;
   addField("isDirty", TypeBool, Offset(mIsDirty, GuiNavEditorCtrl));

   Parent::initPersistFields();
}

void GuiNavEditorCtrl::onSleep()
{
   Parent::onSleep();
}

void GuiNavEditorCtrl::selectMesh(NavMesh *mesh)
{
   mesh->setSelected(true);
   mMesh = mesh;

   if (mTool)
      mTool->setActiveNavMesh(mMesh);
}

DefineEngineMethod(GuiNavEditorCtrl, selectMesh, void, (S32 id),,
   "@brief Select a NavMesh object.")
{
   NavMesh *obj;
   if(Sim::findObject(id, obj))
      object->selectMesh(obj);
}

S32 GuiNavEditorCtrl::getMeshId()
{
   return mMesh.isNull() ? 0 : mMesh->getId();
}

DefineEngineMethod(GuiNavEditorCtrl, getMesh, S32, (),,
   "@brief Select a NavMesh object.")
{
   return object->getMeshId();
}

void GuiNavEditorCtrl::get3DCursor(GuiCursor *&cursor,
                                   bool &visible,
                                   const Gui3DMouseEvent &event_)
{
   //cursor = mAddNodeCursor;
   //visible = false;

   cursor = NULL;
   visible = false;

   GuiCanvas *root = getRoot();
   if(!root)
      return;

   S32 currCursor = PlatformCursorController::curArrow;

   if(root->mCursorChanged == currCursor)
      return;

   PlatformWindow *window = root->getPlatformWindow();
   PlatformCursorController *controller = window->getCursorController();

   // We've already changed the cursor,
   // so set it back before we change it again.
   if(root->mCursorChanged != -1)
      controller->popCursor();

   // Now change the cursor shape
   controller->pushCursor(currCursor);
   root->mCursorChanged = currCursor;
}

bool GuiNavEditorCtrl::get3DCentre(Point3F &pos)
{
   Point3F screen, start, end;

   screen.set(getExtent().x / 2, getExtent().y / 2, 0);
   unproject(screen, &start);

   screen.z = 1.0f;
   unproject(screen, &end);

   RayInfo ri;
   if(gServerContainer.castRay(start, end, StaticObjectType, &ri))
   {
      pos = ri.point;
      return true;
   }
   return false;
}

void GuiNavEditorCtrl::on3DMouseDown(const Gui3DMouseEvent & event)
{
   mGizmo->on3DMouseDown(event);

   if (mTool)
      mTool->on3DMouseDown(event);

   mouseLock();

   return;
}

void GuiNavEditorCtrl::on3DMouseUp(const Gui3DMouseEvent & event)
{
   // Keep the Gizmo up to date.
   mGizmo->on3DMouseUp(event);

   if (mTool)
      mTool->on3DMouseUp(event);

   mouseUnlock();
}

void GuiNavEditorCtrl::on3DMouseMove(const Gui3DMouseEvent & event)
{
   if (mTool)
      mTool->on3DMouseMove(event);

   return;
}

void GuiNavEditorCtrl::on3DMouseDragged(const Gui3DMouseEvent & event)
{
   mGizmo->on3DMouseDragged(event);
   if(mGizmo->isDirty())
   {
      Point3F scale = mGizmo->getScale();
      const MatrixF &mat = mGizmo->getTransform();
      VectorF normal;
      mat.getColumn(2, &normal);

      //mSelRiver->setNode(pos, scale.x, scale.z, normal, mSelNode);
      mIsDirty = true;
   }
}

void GuiNavEditorCtrl::on3DMouseEnter(const Gui3DMouseEvent & event)
{
}

void GuiNavEditorCtrl::on3DMouseLeave(const Gui3DMouseEvent & event)
{
}

void GuiNavEditorCtrl::updateGuiInfo()
{
   if (mTool)
   {
      if (mTool->updateGuiInfo())
         return;
   }
}

void GuiNavEditorCtrl::onRender(Point2I offset, const RectI &updateRect)
{
   PROFILE_SCOPE(GuiNavEditorCtrl_OnRender);

   Parent::onRender(offset, updateRect);
   return;
}

void GuiNavEditorCtrl::renderScene(const RectI & updateRect)
{
   GFX->setStateBlock(mZDisableSB);

   // get the projected size...
   GameConnection* connection = GameConnection::getConnectionToServer();
   if(!connection)
      return;

   // Grab the camera's transform
   MatrixF mat;
   connection->getControlCameraTransform(0, &mat);

   // Get the camera position
   Point3F camPos;
   mat.getColumn(3,&camPos);

   if (mTool)
      mTool->onRender3D();

   duDebugDrawTorque d;
   if (!mMesh.isNull())
   {
      mMesh->renderLinks(d);
      d.immediateRender();
   }

   // Now draw all the 2d stuff!
   GFX->setClipRect(updateRect);
}

bool GuiNavEditorCtrl::getStaticPos(const Gui3DMouseEvent & event, Point3F &tpos)
{
   // Find clicked point on the terrain

   Point3F startPnt = event.pos;
   Point3F endPnt = event.pos + event.vec * 1000.0f;

   RayInfo ri;
   bool hit;

   hit = gServerContainer.castRay(startPnt, endPnt, StaticShapeObjectType, &ri);
   tpos = ri.point;

   return hit;
}

void GuiNavEditorCtrl::submitUndo(const UTF8 *name)
{
   // Grab the mission editor undo manager.
   UndoManager *undoMan = NULL;
   if(!Sim::findObject("EUndoManager", undoMan))
   {
      Con::errorf("GuiNavEditorCtrl::submitUndo() - EUndoManager not found!");
      return;
   }

   // Setup the action.
   GuiNavEditorUndoAction *action = new GuiNavEditorUndoAction(name);

   action->mNavEditor = this;

   undoMan->addAction(action);
}

void GuiNavEditorCtrl::_prepRenderImage(SceneManager* sceneGraph, const SceneRenderState* state)
{
   /*if(isAwake() && River::smEditorOpen && mSelRiver)
   {
      ObjectRenderInst *ri = state->getRenderPass()->allocInst<ObjectRenderInst>();
      ri->type = RenderPassManager::RIT_Editor;
      ri->renderDelegate.bind(this, &GuiNavEditorCtrl::_renderSelectedRiver);
      ri->defaultKey = 100;
      state->getRenderPass()->addInst(ri);
   }*/
}

void GuiNavEditorCtrl::setActiveTool(NavMeshTool* tool)
{
   if (mTool)
   {
      mTool->onDeactivated();
   }

   mTool = tool;

   if (mTool)
   {
      mTool->setActiveEditor(this);
      mTool->setActiveNavMesh(mMesh);
      mTool->onActivated(mLastEvent);
   }
}

void GuiNavEditorCtrl::setDrawMode(S32 id)
{
   if (mMesh.isNull())
      return;

   mMesh->setDrawMode((NavMesh::DrawMode)id);
}

DefineEngineMethod(GuiNavEditorCtrl, setDrawMode, void, (S32 id), ,
   "@brief Deselect whatever is currently selected in the editor.")
{
   object->setDrawMode(id);
}

DefineEngineMethod(GuiNavEditorCtrl, setActiveTool, void, (const char* toolName), , "( NavMeshTool tool )")
{
   NavMeshTool* tool = dynamic_cast<NavMeshTool*>(Sim::findObject(toolName));
   object->setActiveTool(tool);
}

#endif
