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

#ifndef _GUIFORMCTRL_H_
#define _GUIFORMCTRL_H_

#ifndef _GUICONTROL_H_
#include "gui/core/guiControl.h"
#endif

#ifndef _GUI_PANEL_H_
#include "gui/containers/guiPanel.h"
#endif

#ifndef _GUIMENUBAR_H_
#include "gui/editor/guiMenuBar.h"
#endif

#ifndef _GUICANVAS_H_
#include "gui/core/guiCanvas.h"
#endif

#include "console/console.h"
#include "console/consoleTypes.h"

class GuiMenuBar;


/// @addtogroup gui_container_group Containers
///
/// @ingroup gui_group Gui System
/// @{
class GuiFormCtrl : public GuiPanel
{
private:
   typedef GuiPanel Parent;

   Resource<GFont>  mFont;
   String           mCaption;
   bool             mCanMove;
   bool             mUseSmallCaption;
   String           mSmallCaption;
   StringTableEntry mContentLibrary;
   StringTableEntry mContent;

   Point2I          mThumbSize;

   bool             mHasMenu;
   GuiMenuBar*      mMenuBar;

   bool mMouseMovingWin;

   Point2I mMouseDownPosition;
   RectI mOrigBounds;
   RectI mStandardBounds;

   RectI mCloseButton;
   RectI mMinimizeButton;
   RectI mMaximizeButton;

   bool mMouseOver;
   bool mDepressed;
   
   static bool _setHasMenu( void *object, const char *index, const char *data );

protected:
   /// @name Callbacks
   /// @{
   DECLARE_CALLBACK( void, onResize, () );
   /// @}

public:
   GuiFormCtrl();
   virtual ~GuiFormCtrl();

   void setCaption( const char* caption ) { mCaption = caption; }
   void setHasMenu( bool value );

   bool resize(const Point2I &newPosition, const Point2I &newExtent) override;
   void onRender(Point2I offset, const RectI &updateRect) override;

   bool onWake() override;
   void onSleep() override;

   void addObject( SimObject *object ) override;
   void removeObject( SimObject* object ) override;
   bool acceptsAsChild( SimObject* object ) const override;

   void onMouseDown(const GuiEvent &event) override;
   void onMouseUp(const GuiEvent &event) override;
   void onMouseMove(const GuiEvent &event) override;
   void onMouseLeave(const GuiEvent &event) override;
   void onMouseEnter(const GuiEvent &event) override;

   U32  getMenuBarID();

   static void initPersistFields();
   DECLARE_CONOBJECT(GuiFormCtrl);
};
/// @}

#endif