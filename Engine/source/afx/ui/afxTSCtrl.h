
//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~//
// Arcane-FX for MIT Licensed Open Source version of Torque 3D from GarageGames
// Copyright (C) 2015 Faust Logic, Inc.
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
//
//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~//

#ifndef _AFX_TS_CTRL_H_
#define _AFX_TS_CTRL_H_

#include "app/game.h"
#include "gui/3d/guiTSControl.h"
#include "core/iTickable.h"

class GameBase;
class afxSpellBook;

//----------------------------------------------------------------------------
class afxTSCtrl : public GuiTSCtrl, public virtual ITickable
{
private:
  struct Targeting
  { 
    U8   mode;
    U8   check;
  };

  typedef GuiTSCtrl   Parent;

  Point3F             mMouse3DVec;
  Point3F             mMouse3DPos;

  U32                 mouse_dn_timestamp;
  afxSpellBook*       spellbook;
  Vector<Targeting>   targeting_mode;

public:
  /*C*/               afxTSCtrl();

  bool        processCameraQuery(CameraQuery *query) override;
  void        renderWorld(const RectI &updateRect) override;
  void        onRender(Point2I offset, const RectI &updateRect) override;

  void        getCursor(GuiCursor *&cursor, bool &showCursor, const GuiEvent &lastGuiEvent) override;

  void        onMouseDown(const GuiEvent&) override;
  void        onMouseMove(const GuiEvent&) override;
  void        onMouseDragged(const GuiEvent&) override;
  void        onMouseEnter(const GuiEvent&) override;
  void        onMouseLeave(const GuiEvent&) override;

  bool        onMouseWheelUp(const GuiEvent&) override;
  bool        onMouseWheelDown(const GuiEvent&) override;

  void        onRightMouseDown(const GuiEvent&) override;

  Point3F             getMouse3DVec() {return mMouse3DVec;};   
  Point3F             getMouse3DPos() {return mMouse3DPos;};

  void                setSpellBook(afxSpellBook* book);
  void                clearTargetingMode();
  void                pushTargetingMode(U8 mode, U8 check);
  void                popTargetingMode();
  U8                  getTargetingMode();
  U8                  getTargetingCheckMethod();
  void                performTargeting(const Point2I& mousePoint, U8 mode);

  void        interpolateTick( F32 delta ) override {};
  void        processTick() override {};
  void        advanceTime( F32 timeDelta ) override; 

  DECLARE_CONOBJECT(afxTSCtrl);
  DECLARE_CATEGORY("AFX");
};

//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~//

#endif // _AFX_TS_CTRL_H_
