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
#include "gui/shaderEditor/guiShaderNode.h"
#endif // !_SHADERNODE_H_

struct NodeConnection
{
   // keep track of the nodes hit.
   GuiShaderNode* nodeA = NULL;
   GuiShaderNode* nodeB = NULL;

   // keep track of the sockets.
   NodeInput* inSocket = NULL;
   NodeOutput* outSocket = NULL;
};

class GuiShaderEditor : public GuiControl
{
public:

   typedef GuiControl Parent;

   enum mouseModes { Selecting, MovingSelection, DragPanning, DragConnection, DragSelecting, DragClone };

protected:

   // list
   typedef Vector<GuiShaderNode*> ShaderNodeVector;
   typedef Vector<NodeConnection*> ShderNodeConnections;
   // all nodes in this graph.
   ShaderNodeVector mCurrNodes;
   ShderNodeConnections mCurrConnections;
   NodeConnection* mTempConnection;
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
   void renderConnections(Point2I offset, const RectI& updateRect);

   // functions for handling mouse events.
   GuiShaderNode* findHitNode(const Point2I& pt);
   bool findHitSocket(const Point2I& pt);
   U32 finishConnection(const Point2I& pt);
   bool hasConnection(NodeSocket* inSocket);
   bool hasConnection(NodeSocket* inSocket, Vector<NodeConnection*>& conn);
   bool hasConnection(NodeSocket* inSocket, NodeConnection*& conn);

   void findNodesInRect(const RectI& rect, Vector<GuiShaderNode*>& outResult);

   void getDragRect(RectI& box);
   void startDragMove(const Point2I& startPoint);
   void startDragRectangle(const Point2I& startPoint);
   void startDragClone(const Point2I& startPoint);
   void setMouseMode(mouseModes mode);
   void addNode(GuiShaderNode* newNode);

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
   void drawThickLine(const Point2I& pt1, const Point2I& pt2, U32 thickness = 2, ColorI col1 = ColorI(255, 255, 255), ColorI col2 = ColorI(255, 255, 255));
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
