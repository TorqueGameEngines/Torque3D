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

#ifndef _GUIMOUSEEVENTCTRL_H_
#define _GUIMOUSEEVENTCTRL_H_

#ifndef _GUICONTROL_H_
#include "gui/core/guiControl.h"
#endif


class GuiMouseEventCtrl : public GuiControl
{
   private:
      typedef  GuiControl     Parent;
      void sendMouseEvent(const char * name, const GuiEvent &);

      // field info
      bool        mLockMouse;

   public:

      GuiMouseEventCtrl();

      DECLARE_CALLBACK( void, onMouseDown, ( S32 modifier, Point2I mousePoint, S32 mouseClickCount ));
      DECLARE_CALLBACK( void, onMouseUp, ( S32 modifier, Point2I mousePoint, S32 mouseClickCount ));
      DECLARE_CALLBACK( void, onMouseMove, ( S32 modifier, Point2I mousePoint, S32 mouseClickCount ));
      DECLARE_CALLBACK( void, onMouseDragged, ( S32 modifier, Point2I mousePoint, S32 mouseClickCount ));
      DECLARE_CALLBACK( void, onMouseEnter, ( S32 modifier, Point2I mousePoint, S32 mouseClickCount ));
      DECLARE_CALLBACK( void, onMouseLeave, ( S32 modifier, Point2I mousePoint, S32 mouseClickCount ));
      DECLARE_CALLBACK( void, onRightMouseDown, ( S32 modifier, Point2I mousePoint, S32 mouseClickCount ));
      DECLARE_CALLBACK( void, onRightMouseUp, ( S32 modifier, Point2I mousePoint, S32 mouseClickCount ));
      DECLARE_CALLBACK( void, onRightMouseDragged, ( S32 modifier, Point2I mousePoint, S32 mouseClickCount ));

      // GuiControl
      void onMouseDown(const GuiEvent & event) override;
      void onMouseUp(const GuiEvent & event) override;
      void onMouseMove(const GuiEvent & event) override;
      void onMouseDragged(const GuiEvent & event) override;
      void onMouseEnter(const GuiEvent & event) override;
      void onMouseLeave(const GuiEvent & event) override;
      void onRightMouseDown(const GuiEvent & event) override;
      void onRightMouseUp(const GuiEvent & event) override;
      void onRightMouseDragged(const GuiEvent & event) override;

      static void initPersistFields();

      DECLARE_CONOBJECT( GuiMouseEventCtrl );
      DECLARE_CATEGORY( "Gui Other Script" );
      DECLARE_DESCRIPTION( "A control that relays all mouse events to script." );
};

#endif
