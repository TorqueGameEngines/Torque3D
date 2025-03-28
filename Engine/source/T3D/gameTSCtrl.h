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

#ifndef _GAMETSCTRL_H_
#define _GAMETSCTRL_H_

#ifndef _GAME_H_
#include "app/game.h"
#endif
#ifndef _GUITSCONTROL_H_
#include "gui/3d/guiTSControl.h"
#endif

class ProjectileData;
class GameBase;

//----------------------------------------------------------------------------
class GameTSCtrl : public GuiTSCtrl
{
private:
   typedef GuiTSCtrl Parent;

   void sendMouseEvent(const char *name, const GuiEvent &evt);

protected:
   PlatformTimer *mFrameTime;

public:
   GameTSCtrl();

   /// @name Callbacks
   /// @{

   DECLARE_CALLBACK(void, onMouseDown, (const Point2I& screenPosition, const Point3F& worldPosition, const Point3F& clickVector));
   DECLARE_CALLBACK(void, onRightMouseDown, (const Point2I& screenPosition, const Point3F& worldPosition, const Point3F& clickVector));
   DECLARE_CALLBACK(void, onMiddleMouseDown, (const Point2I& screenPosition, const Point3F& worldPosition, const Point3F& clickVector));
   DECLARE_CALLBACK(void, onMouseUp, (const Point2I& screenPosition, const Point3F& worldPosition, const Point3F& clickVector));
   DECLARE_CALLBACK(void, onRightMouseUp, (const Point2I& screenPosition, const Point3F& worldPosition, const Point3F& clickVector));
   DECLARE_CALLBACK(void, onMiddleMouseUp, (const Point2I& screenPosition, const Point3F& worldPosition, const Point3F& clickVector));
   DECLARE_CALLBACK(void, onMouseDragged, (const Point2I& screenPosition, const Point3F& worldPosition, const Point3F& clickVector));
   DECLARE_CALLBACK(void, onRightMouseDragged, (const Point2I& screenPosition, const Point3F& worldPosition, const Point3F& clickVector));
   DECLARE_CALLBACK(void, onMiddleMouseDragged, (const Point2I& screenPosition, const Point3F& worldPosition, const Point3F& clickVector));
   DECLARE_CALLBACK(void, onMouseWheelUp, (const Point2I& screenPosition, const Point3F& worldPosition, const Point3F& clickVector));
   DECLARE_CALLBACK(void, onMouseWheelDown, (const Point2I& screenPosition, const Point3F& worldPosition, const Point3F& clickVector));
   DECLARE_CALLBACK(void, onMouseMove, (const Point2I& screenPosition, const Point3F& worldPosition, const Point3F& clickVector));
   /// }

   DECLARE_CONOBJECT(GameTSCtrl);
   DECLARE_DESCRIPTION( "A control that renders a 3D view from the current control object." );

   bool processCameraQuery(CameraQuery *query) override;
   void renderWorld(const RectI &updateRect) override;

   // GuiControl
   void onMouseDown(const GuiEvent &evt) override;
   void onRightMouseDown(const GuiEvent &evt) override;
   void onMiddleMouseDown(const GuiEvent &evt) override;

   void onMouseUp(const GuiEvent &evt) override;
   void onRightMouseUp(const GuiEvent &evt) override;
   void onMiddleMouseUp(const GuiEvent &evt) override;

   void onMouseDragged(const GuiEvent &evt);
   void onRightMouseDragged(const GuiEvent &evt);
   void onMiddleMouseDragged(const GuiEvent &evt);

   bool onMouseWheelUp(const GuiEvent &evt);
   bool onMouseWheelDown(const GuiEvent &evt);

   void onMouseMove(const GuiEvent &evt) override;
   void onRender(Point2I offset, const RectI &updateRect) override;

   bool onAdd() override;
};

#endif
