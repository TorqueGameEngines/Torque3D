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

#ifndef _GUISHADEREDITOR_H_
#define _GUISHADEREDITOR_H_

#ifndef _GUICONTROL_H_
#include "gui/core/guiControl.h"
#endif
#ifndef _UNDO_H_
#include "util/undo.h"
#endif
#ifndef _GFX_GFXDRAWER_H_
#include "gfx/gfxDrawUtil.h"
#endif

#ifndef _SHADERNODE_H_
#include "gui/shaderEditor/nodes/shaderNode.h"
#endif // !_SHADERNODE_H_

class GuiShaderEditor : public GuiControl
{
public:

   typedef GuiControl Parent;

   enum mouseModes { Selecting, MovingSelection, DragPanning, DragConnection, DragSelecting, DragClone };

protected:

   // list
   typedef Vector<GuiShaderNode*> ShaderNodeVector;
   // all nodes in this graph.
   ShaderNodeVector mCurrNodes;

   // Undo
   SimGroup* mTrash;

   // view controls
   Point2I mViewOffset;
   F32 mZoomScale;
   // mouse interaction
   mouseModes mMouseDownMode;
   Point2I mLastMousePos;
   Point2I mLastDragPos;
   Point2I mSelectionAnchor;
   Point2I mDragBeginPoint;
   Vector<Point2I> mDragBeginPoints;
   bool mDragAddSelection;
   bool mDragMoveUndo;
   bool mFullBoxSelection;
   S32 mNodeSize;
   ShaderNodeVector mSelectedNodes;

   void renderNodes(Point2I offset, const RectI& updateRect);

   // functions for handling mouse events.
   GuiShaderNode* findHitNode(const Point2I& pt);
   void findNodesInRect(const RectI& rect, Vector<GuiShaderNode*>& outResult);

   void getDragRect(RectI& box);
   void startDragMove(const Point2I& startPoint);
   void startDragRectangle(const Point2I& startPoint);
   void startDragClone(const Point2I& startPoint);
   void setMouseMode(mouseModes mode);

public:
   GuiShaderEditor();

   DECLARE_CONOBJECT(GuiShaderEditor);
   DECLARE_CATEGORY("Shader Editor");
   DECLARE_DESCRIPTION("Implements a shader node based editor.");

   bool onWake();
   void onSleep();
   static void initPersistFields();
   virtual bool onAdd() override;
   virtual void onRemove() override;

   virtual void onPreRender() override;
   virtual void onRender(Point2I offset, const RectI& updateRect) override;

   // interaction
   virtual bool onKeyDown(const GuiEvent& event) override;
   virtual void onMouseDown(const GuiEvent& event) override;
   virtual void onMouseUp(const GuiEvent& event) override;
   virtual void onMouseDragged(const GuiEvent& event) override;
   virtual void onMiddleMouseDown(const GuiEvent& event) override;
   virtual void onMiddleMouseUp(const GuiEvent& event) override;
   virtual void onMiddleMouseDragged(const GuiEvent& event) override;
   virtual bool onMouseWheelUp(const GuiEvent& event) override;
   virtual bool onMouseWheelDown(const GuiEvent& event) override;

   RectI getSelectionBounds();
   void deleteSelection();
   void moveSelection(const Point2I& delta, bool callback = true);
   void clearSelection();
   void cloneSelection();
   void addSelectionAtPoint(const Point2I& pos);
   void addSelection(GuiShaderNode* inNode);
   bool selectionContains(GuiShaderNode* inNode);
   void removeSelection(GuiShaderNode* inNode);
   void canHitSelectedNodes(bool state = true);
};

#endif _GUISHADEREDITOR_H_
