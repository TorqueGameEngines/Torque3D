#pragma once
#pragma once 
#ifndef _NAVMESH_TOOL_H_
#define _NAVMESH_TOOL_H_
#ifdef TORQUE_TOOLS
#include "console/simBase.h"

#include "gui/core/guiTypes.h"

#include "navigation/navMesh.h"

#include "navigation/guiNavEditorCtrl.h"

class UndoAction;

class NavMeshTool : public SimObject
{
   typedef SimObject Parent;
protected:
   SimObjectPtr<NavMesh> mNavMesh;
   SimObjectPtr<GuiNavEditorCtrl> mCurEditor;

   void _submitUndo(UndoAction* action);

public:
   
   NavMeshTool();
   virtual ~NavMeshTool();

   DECLARE_CONOBJECT(NavMeshTool);

   virtual void setActiveNavMesh(NavMesh* nav_mesh) { mNavMesh = nav_mesh; }
   virtual void setActiveEditor(GuiNavEditorCtrl* nav_editor) { mCurEditor = nav_editor; }

   virtual void onActivated(const Gui3DMouseEvent& lastEvent) {}
   virtual void onDeactivated() {}

   virtual void on3DMouseDown(const Gui3DMouseEvent& evt) {}
   virtual void on3DMouseUp(const Gui3DMouseEvent& evt) {}
   virtual void on3DMouseMove(const Gui3DMouseEvent& evt) {}
   virtual void on3DMouseDragged(const Gui3DMouseEvent& evt) {}
   virtual void on3DMouseEnter(const Gui3DMouseEvent& evt) {}
   virtual void on3DMouseLeave(const Gui3DMouseEvent& evt) {}
   virtual bool onMouseWheel(const GuiEvent& evt) { return false; }
   virtual void onRender3D() {}
   virtual void onRender2D() {}
   virtual void updateGizmo() {}
   virtual bool updateGuiInfo() { return false; }
   virtual void onUndoAction() {}

};
#endif
#endif // !_NAVMESH_TOOL_H_
