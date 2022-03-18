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

#ifndef _GUINODECTRL_H_
#define _GUINODECTRL_H_

#ifndef _GUICONTAINER_H_
#include "gui/containers/guiContainer.h"
#endif

class GuiNodeCtrl : public GuiControl
{
public:
   typedef GuiControl Parent;

   struct Input
   {
      String label;
      // all input sockets default to red.
      ColorI color;
      Point2I pos;
      bool hasConnection = false;
      bool allowMultiple;
   };

   struct Output
   {
      String label;
      // outputs default to green.
      ColorI color;
      Point2I pos;
      bool hasConnection = false;
      bool allowMultiple;
   };

protected:
   String mText;
   S32 mTitleHeight;
   S32 mChildPadding;
   S32 mConnectionPadding;
   S32 mConnectionIndent;
   ColorI mTitleBarColor;
   ColorI mTitleBarFadeColor;
   bool mCanCollapse;
   bool mCollapsed;
   GFXStateBlockRef mStateBlock;
   //DECLARE_CALLBACK(void, onCollapse, ());
   //DECLARE_CALLBACK(void, onRestore, ());
public:

   // needs to be public for nodeGraphAccess.
   bool mHasConnections;
   Vector<Input> mInputs;
   Vector<Output> mOutputs;

   DECLARE_CONOBJECT(GuiNodeCtrl);
   DECLARE_CATEGORY("Gui Containers");

   // 
   GuiNodeCtrl();
   void drawBlendHeader(RectI& bounds, ColorI leftCol, ColorI rightCol);
   virtual bool onWake();
   virtual void onSleep();
   static void initPersistFields();
   void updateNodeSize();
   void updateConnections(Point2I& curPos);

   virtual void onRender(Point2I offset, const RectI& updateRect);

   // interaction only when its in a graphc.
   bool inTitleBar(const GuiEvent& event);
   void onMouseDownGraph(const GuiEvent& event);

   // handle node sockets.
   void addInput(String text, ColorI col = ColorI(255,0,0), bool allowMultiple = false);
   void addOutput(String text, ColorI col = ColorI(0, 255, 0), bool allowMultiple = false);

   // accessors.
   bool hasConnections() { return mHasConnections; }
   void childResized(GuiControl* child);
   bool resize(const Point2I& newPosition, const Point2I& newExtent);

};

#endif // !_GUINODECTRL_H_
