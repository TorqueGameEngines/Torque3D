
#include "platform/platform.h"
#include "navigation/navMeshTool.h"
#ifdef TORQUE_TOOLS
#include "util/undo.h"
#include "math/mMath.h"
#include "math/mathUtils.h"

IMPLEMENT_CONOBJECT(NavMeshTool);

ConsoleDocClass(NavMeshTool,
   "@brief Base class for NavMesh Editor specific tools\n\n"
   "Editor use only.\n\n"
   "@internal"
);

void NavMeshTool::_submitUndo(UndoAction* action)
{
   AssertFatal(action, "NavMeshTool::_submitUndo() - No undo action!");

   // Grab the mission editor undo manager.
   UndoManager* undoMan = NULL;
   if (!Sim::findObject("EUndoManager", undoMan))
   {
      Con::errorf("NavMeshTool::_submitUndo() - EUndoManager not found!");
      return;
   }

   undoMan->addAction(action);
}

NavMeshTool::NavMeshTool()
   : mNavMesh(NULL)
{
}

NavMeshTool::~NavMeshTool()
{
}
#endif
