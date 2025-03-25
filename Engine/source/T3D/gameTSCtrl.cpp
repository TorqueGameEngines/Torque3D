//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
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

#include "T3D/gameTSCtrl.h"
#include "console/consoleTypes.h"
#include "T3D/gameBase/gameBase.h"
#include "T3D/gameBase/gameConnection.h"
#include "T3D/shapeBase.h"
#include "T3D/gameFunctions.h"
#include "console/engineAPI.h"

//---------------------------------------------------------------------------
// Debug stuff:
Point3F lineTestStart = Point3F(0, 0, 0);
Point3F lineTestEnd =   Point3F(0, 1000, 0);
Point3F lineTestIntersect =  Point3F(0, 0, 0);
bool gSnapLine = false;

//----------------------------------------------------------------------------
// Class: GameTSCtrl
//----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT(GameTSCtrl);

// See Torque manual (.CHM) for more information
ConsoleDocClass( GameTSCtrl,
	"@brief The main 3D viewport for a Torque 3D game.\n\n"
	"@ingroup Gui3D\n");

IMPLEMENT_CALLBACK(GameTSCtrl, onMouseDown, void, (const Point2I& screenPosition, const Point3F& worldPosition, const Point3F& clickVector), (screenPosition, worldPosition, clickVector),
   "@brief Callback that occurs whenever the left mouse button is pressed while in this control.\n\n"
   "@param screenPosition Position of screen when mouse was pressed during this callback.\n\n"
   "@param worldPosition Position of world when mouse was pressed during this callback.\n\n"
   "@param clickVector Vector for the click when mouse was pressed during this callback.\n\n"
   "@tsexample\n"
   "// Mouse was pressed down in this control, causing the callback\n"
   "GameTSCtrl::onMouseDown(%this,%screenPosition,%worldPosition,%clickVector)\n"
   "{\n"
   "	// Code to call when a mouse event occurs.\n"
   "}\n"
   "@endtsexample\n\n"
);

IMPLEMENT_CALLBACK(GameTSCtrl, onRightMouseDown, void, (const Point2I& screenPosition, const Point3F& worldPosition, const Point3F& clickVector), (screenPosition, worldPosition, clickVector),
   "@brief Callback that occurs whenever the right mouse button is pressed while in this control.\n\n"
   "@param screenPosition Position of screen when mouse was pressed during this callback.\n\n"
   "@param worldPosition Position of world when mouse was pressed during this callback.\n\n"
   "@param clickVector Vector for the click when mouse was pressed during this callback.\n\n"
   "@tsexample\n"
   "// Mouse was pressed down in this control, causing the callback\n"
   "GameTSCtrl::onRightMouseDown(%this,%screenPosition,%worldPosition,%clickVector)\n"
   "{\n"
   "	// Code to call when a mouse event occurs.\n"
   "}\n"
   "@endtsexample\n\n"
);

IMPLEMENT_CALLBACK(GameTSCtrl, onMiddleMouseDown, void, (const Point2I& screenPosition, const Point3F& worldPosition, const Point3F& clickVector), (screenPosition, worldPosition, clickVector),
   "@brief Callback that occurs whenever the middle mouse button is pressed while in this control.\n\n"
   "@param screenPosition Position of screen when mouse was pressed during this callback.\n\n"
   "@param worldPosition Position of world when mouse was pressed during this callback.\n\n"
   "@param clickVector Vector for the click when mouse was pressed during this callback.\n\n"
   "@tsexample\n"
   "// Mouse was pressed down in this control, causing the callback\n"
   "GameTSCtrl::onMiddleMouseDown(%this,%screenPosition,%worldPosition,%clickVector)\n"
   "{\n"
   "	// Code to call when a mouse event occurs.\n"
   "}\n"
   "@endtsexample\n\n"
);

IMPLEMENT_CALLBACK(GameTSCtrl, onMouseUp, void, (const Point2I& screenPosition, const Point3F& worldPosition, const Point3F& clickVector), (screenPosition, worldPosition, clickVector),
   "@brief Callback that occurs whenever the left mouse button is released while in this control.\n\n"
   "@param screenPosition Position of screen when mouse was released during this callback.\n\n"
   "@param worldPosition Position of world when mouse was released during this callback.\n\n"
   "@param clickVector Vector for the click when mouse was released during this callback.\n\n"
   "@tsexample\n"
   "// Mouse was released down in this control, causing the callback\n"
   "GameTSCtrl::onMouseUp(%this,%screenPosition,%worldPosition,%clickVector)\n"
   "{\n"
   "	// Code to call when a mouse event occurs.\n"
   "}\n"
   "@endtsexample\n\n"
);

IMPLEMENT_CALLBACK(GameTSCtrl, onRightMouseUp, void, (const Point2I& screenPosition, const Point3F& worldPosition, const Point3F& clickVector), (screenPosition, worldPosition, clickVector),
   "@brief Callback that occurs whenever the right mouse button is released while in this control.\n\n"
   "@param screenPosition Position of screen when mouse was released during this callback.\n\n"
   "@param worldPosition Position of world when mouse was released during this callback.\n\n"
   "@param clickVector Vector for the click when mouse was released during this callback.\n\n"
   "@tsexample\n"
   "// Mouse was released down in this control, causing the callback\n"
   "GameTSCtrl::onRightMouseUp(%this,%screenPosition,%worldPosition,%clickVector)\n"
   "{\n"
   "	// Code to call when a mouse event occurs.\n"
   "}\n"
   "@endtsexample\n\n"
);

IMPLEMENT_CALLBACK(GameTSCtrl, onMiddleMouseUp, void, (const Point2I& screenPosition, const Point3F& worldPosition, const Point3F& clickVector), (screenPosition, worldPosition, clickVector),
   "@brief Callback that occurs whenever the middle mouse button is released while in this control.\n\n"
   "@param screenPosition Position of screen when mouse was released during this callback.\n\n"
   "@param worldPosition Position of world when mouse was released during this callback.\n\n"
   "@param clickVector Vector for the click when mouse was released during this callback.\n\n"
   "@tsexample\n"
   "// Mouse was released down in this control, causing the callback\n"
   "GameTSCtrl::onMiddleMouseUp(%this,%screenPosition,%worldPosition,%clickVector)\n"
   "{\n"
   "	// Code to call when a mouse event occurs.\n"
   "}\n"
   "@endtsexample\n\n"
);

IMPLEMENT_CALLBACK(GameTSCtrl, onMouseDragged, void, (const Point2I& screenPosition, const Point3F& worldPosition, const Point3F& clickVector), (screenPosition, worldPosition, clickVector),
   "@brief Callback that occurs whenever the left mouse button is dragged while in this control.\n\n"
   "@param screenPosition Position of screen when mouse was dragged during this callback.\n\n"
   "@param worldPosition Position of world when mouse was dragged during this callback.\n\n"
   "@param clickVector Vector for the click when mouse was dragged during this callback.\n\n"
   "@tsexample\n"
   "// Mouse was dragged down in this control, causing the callback\n"
   "GameTSCtrl::onMouseDragged(%this,%screenPosition,%worldPosition,%clickVector)\n"
   "{\n"
   "	// Code to call when a mouse event occurs.\n"
   "}\n"
   "@endtsexample\n\n"
);

IMPLEMENT_CALLBACK(GameTSCtrl, onRightMouseDragged, void, (const Point2I& screenPosition, const Point3F& worldPosition, const Point3F& clickVector), (screenPosition, worldPosition, clickVector),
   "@brief Callback that occurs whenever the right mouse button is dragged while in this control.\n\n"
   "@param screenPosition Position of screen when mouse was dragged during this callback.\n\n"
   "@param worldPosition Position of world when mouse was dragged during this callback.\n\n"
   "@param clickVector Vector for the click when mouse was dragged during this callback.\n\n"
   "@tsexample\n"
   "// Mouse was dragged down in this control, causing the callback\n"
   "GameTSCtrl::onRightMouseDragged(%this,%screenPosition,%worldPosition,%clickVector)\n"
   "{\n"
   "	// Code to call when a mouse event occurs.\n"
   "}\n"
   "@endtsexample\n\n"
);

IMPLEMENT_CALLBACK(GameTSCtrl, onMiddleMouseDragged, void, (const Point2I& screenPosition, const Point3F& worldPosition, const Point3F& clickVector), (screenPosition, worldPosition, clickVector),
   "@brief Callback that occurs whenever the middle mouse button is dragged while in this control.\n\n"
   "@param screenPosition Position of screen when mouse was dragged during this callback.\n\n"
   "@param worldPosition Position of world when mouse was dragged during this callback.\n\n"
   "@param clickVector Vector for the click when mouse was dragged during this callback.\n\n"
   "@tsexample\n"
   "// Mouse was dragged down in this control, causing the callback\n"
   "GameTSCtrl::onMiddleMouseDragged(%this,%screenPosition,%worldPosition,%clickVector)\n"
   "{\n"
   "	// Code to call when a mouse event occurs.\n"
   "}\n"
   "@endtsexample\n\n"
);

IMPLEMENT_CALLBACK(GameTSCtrl, onMouseWheelUp, void, (const Point2I& screenPosition, const Point3F& worldPosition, const Point3F& clickVector), (screenPosition, worldPosition, clickVector),
   "@brief Callback that occurs whenever the mouse wheel up is pressed while in this control.\n\n"
   "@param screenPosition Position of screen when mouse wheel up was pressed during this callback.\n\n"
   "@param worldPosition Position of world when mouse wheel up was pressed during this callback.\n\n"
   "@param clickVector Vector for the click when mouse wheel up was pressed during this callback.\n\n"
   "@tsexample\n"
   "// Mouse wheel up was pressed in this control, causing the callback\n"
   "GameTSCtrl::onMouseWheelUp(%this,%screenPosition,%worldPosition,%clickVector)\n"
   "{\n"
   "	// Code to call when a mouse event occurs.\n"
   "}\n"
   "@endtsexample\n\n"
);

IMPLEMENT_CALLBACK(GameTSCtrl, onMouseWheelDown, void, (const Point2I& screenPosition, const Point3F& worldPosition, const Point3F& clickVector), (screenPosition, worldPosition, clickVector),
   "@brief Callback that occurs whenever the mouse wheel down is pressed while in this control.\n\n"
   "@param screenPosition Position of screen when mouse wheel down was pressed during this callback.\n\n"
   "@param worldPosition Position of world when mouse wheel down was pressed during this callback.\n\n"
   "@param clickVector Vector for the click when mouse wheel down was pressed during this callback.\n\n"
   "@tsexample\n"
   "// Mouse wheel down was pressed in this control, causing the callback\n"
   "GameTSCtrl::onMouseWheelDown(%this,%screenPosition,%worldPosition,%clickVector)\n"
   "{\n"
   "	// Code to call when a mouse event occurs.\n"
   "}\n"
   "@endtsexample\n\n"
);

IMPLEMENT_CALLBACK(GameTSCtrl, onMouseMove, void, (const Point2I& screenPosition, const Point3F& worldPosition, const Point3F& clickVector), (screenPosition, worldPosition, clickVector),
   "@brief Callback that occurs whenever the mouse is moved (without dragging) while in this control.\n\n"
   "@param screenPosition Position of screen when mouse was moved during this callback.\n\n"
   "@param worldPosition Position of world when mouse was moved during this callback.\n\n"
   "@param clickVector Vector for the click when mouse was moved during this callback.\n\n"
   "@tsexample\n"
   "// Mouse was moved down in this control, causing the callback\n"
   "GameTSCtrl::onMouseMove(%this,%screenPosition,%worldPosition,%clickVector)\n"
   "{\n"
   "	// Code to call when a mouse event occurs.\n"
   "}\n"
   "@endtsexample\n\n"
);

GameTSCtrl::GameTSCtrl()
{
   mFrameTime = PlatformTimer::create();
}

//---------------------------------------------------------------------------
bool GameTSCtrl::onAdd()
{
   if ( !Parent::onAdd() )
      return false;

   return true;
}

//---------------------------------------------------------------------------
bool GameTSCtrl::processCameraQuery(CameraQuery *camq)
{
   GameUpdateCameraFov();
   return GameProcessCameraQuery(camq);
}

//---------------------------------------------------------------------------
void GameTSCtrl::renderWorld(const RectI &updateRect)
{
   GameRenderWorld();
}

//------------------------------------------------------------------------------
void GameTSCtrl::sendMouseEvent(const char *name, const GuiEvent &event)
{
   // write screen position
   Point2I screenPosition = event.mousePoint;

   // write world position
   Point3F worldPosition;
   mLastCameraQuery.cameraMatrix.getColumn(3, &worldPosition);

   // write click vector
   Point3F fp(event.mousePoint.x, event.mousePoint.y, 1.0);
   Point3F clickVector;
   unproject(fp, &clickVector);
   clickVector -= worldPosition;
   clickVector.normalizeSafe();

   if (dStricmp(name, "onMouseDown") == 0)
      onMouseDown_callback(screenPosition, worldPosition, clickVector);
   else if (dStricmp(name, "onRightMouseDown") == 0)
      onRightMouseDown_callback(screenPosition, worldPosition, clickVector);
   else if (dStricmp(name, "onMiddleMouseDown") == 0)
      onMiddleMouseDown_callback(screenPosition, worldPosition, clickVector);
   else if (dStricmp(name, "onMouseUp") == 0)
      onMouseUp_callback(screenPosition, worldPosition, clickVector);
   else if (dStricmp(name, "onRightMouseUp") == 0)
      onRightMouseUp_callback(screenPosition, worldPosition, clickVector);
   else if (dStricmp(name, "onMiddleMouseUp") == 0)
      onMiddleMouseUp_callback(screenPosition, worldPosition, clickVector);
   else if (dStricmp(name, "onMouseDragged") == 0)
      onMouseDragged_callback(screenPosition, worldPosition, clickVector);
   else if (dStricmp(name, "onRightMouseDragged") == 0)
      onRightMouseDragged_callback(screenPosition, worldPosition, clickVector);
   else if (dStricmp(name, "onMiddleMouseDragged") == 0)
      onMiddleMouseDragged_callback(screenPosition, worldPosition, clickVector);
   else if (dStricmp(name, "onMouseWheelUp") == 0)
      onMouseWheelUp_callback(screenPosition, worldPosition, clickVector);
   else if (dStricmp(name, "onMouseWheelDown") == 0)
      onMouseWheelDown_callback(screenPosition, worldPosition, clickVector);
   else if (dStricmp(name, "onMouseMove") == 0)
      onMouseMove_callback(screenPosition, worldPosition, clickVector);
}

void GameTSCtrl::onMouseDown(const GuiEvent &evt)
{
   Parent::onMouseDown(evt);

   sendMouseEvent("onMouseDown", evt);
}

void GameTSCtrl::onRightMouseDown(const GuiEvent &evt)
{
   Parent::onRightMouseDown(evt);

   sendMouseEvent("onRightMouseDown", evt);
}

void GameTSCtrl::onMiddleMouseDown(const GuiEvent &evt)
{
   Parent::onMiddleMouseDown(evt);

   sendMouseEvent("onMiddleMouseDown", evt);
}

void GameTSCtrl::onMouseUp(const GuiEvent &evt)
{
   Parent::onMouseUp(evt);

   sendMouseEvent("onMouseUp", evt);
}

void GameTSCtrl::onRightMouseUp(const GuiEvent &evt)
{
   Parent::onRightMouseUp(evt);

   sendMouseEvent("onRightMouseUp", evt);
}

void GameTSCtrl::onMiddleMouseUp(const GuiEvent &evt)
{
   Parent::onMiddleMouseUp(evt);

   sendMouseEvent("onMiddleMouseUp", evt);
}

void GameTSCtrl::onMouseDragged(const GuiEvent &evt)
{
   Parent::onMouseDragged(evt);

   if (mFrameTime && mFrameTime->getElapsedMs() > 16)
   {
      sendMouseEvent("onMouseDragged", evt);
      mFrameTime->reset();
   }
}

void GameTSCtrl::onRightMouseDragged(const GuiEvent &evt)
{
   Parent::onRightMouseDragged(evt);

   if (mFrameTime && mFrameTime->getElapsedMs() > 16)
   {
      sendMouseEvent("onRightMouseDragged", evt);
      mFrameTime->reset();
   }
}

void GameTSCtrl::onMiddleMouseDragged(const GuiEvent &evt)
{
   Parent::onMiddleMouseDragged(evt);

   if (mFrameTime && mFrameTime->getElapsedMs() > 16)
   {
      sendMouseEvent("onMiddleMouseDragged", evt);
      mFrameTime->reset();
   }
}

bool GameTSCtrl::onMouseWheelUp(const GuiEvent &evt)
{
   sendMouseEvent("onMouseWheelUp", evt);

   return Parent::onMouseWheelUp(evt);
}

bool GameTSCtrl::onMouseWheelDown(const GuiEvent &evt)
{
   sendMouseEvent("onMouseWheelDown", evt);

   return Parent::onMouseWheelDown(evt);
}

void GameTSCtrl::onMouseMove(const GuiEvent &evt)
{
   if(gSnapLine)
      return;

   MatrixF mat;
   Point3F vel;
   if ( GameGetCameraTransform(&mat, &vel) )
   {
      Point3F pos;
      mat.getColumn(3,&pos);
      Point3F screenPoint((F32)evt.mousePoint.x, (F32)evt.mousePoint.y, -1.0f);
      Point3F worldPoint;
      if (unproject(screenPoint, &worldPoint)) {
         Point3F vec = worldPoint - pos;
         lineTestStart = pos;
         vec.normalizeSafe();
         lineTestEnd = pos + vec * 1000;
      }
   }

   if (mFrameTime->getElapsedMs() > 16)
   {
      sendMouseEvent("onMouseMove", evt);
      mFrameTime->reset();
   }
}

void GameTSCtrl::onRender(Point2I offset, const RectI &updateRect)
{
   // check if should bother with a render
   GameConnection * con = GameConnection::getConnectionToServer();
   bool skipRender = !con || (con->getWhiteOut() >= 1.f) || (con->getDamageFlash() >= 1.f) || (con->getBlackOut() >= 1.f);

   if(!skipRender || true)
      Parent::onRender(offset, updateRect);
}

//--------------------------------------------------------------------------

DefineEngineFunction(snapToggle, void, (),,
					 "@brief Prevents mouse movement from being processed\n\n"

					 "In the source, whenever a mouse move event occurs "
					 "GameTSCtrl::onMouseMove() is called. Whenever snapToggle() "
					 "is called, it will flag a variable that can prevent this "
					 "from happening: gSnapLine. This variable is not exposed to "
					 "script, so you need to call this function to trigger it.\n\n"

					 "@tsexample\n"
					 "// Snapping is off by default, so we will toggle\n"
					 "// it on first:\n"
					 "PlayGui.snapToggle();\n\n"
					 "// Mouse movement should be disabled\n"
					 "// Let's turn it back on\n"
					 "PlayGui.snapToggle();\n"
					 "@endtsexample\n\n"

					 "@ingroup GuiGame")
{
	gSnapLine = !gSnapLine;
}
//
//ConsoleFunction( snapToggle, void, 1, 1, "()" )
//{
//   gSnapLine = !gSnapLine;
//}
