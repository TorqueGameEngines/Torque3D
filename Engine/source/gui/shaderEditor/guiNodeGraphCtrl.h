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

#ifndef _GUINODEGRAPHCTRL_H_
#define _GUINODEGRAPHCTRL_H_

#ifndef _GUICONTROL_H_
#include "gui/core/guiControl.h"
#endif
#ifndef _UNDO_H_
#include "util/undo.h"
#endif
#ifndef _GFX_GFXDRAWER_H_
#include "gfx/gfxDrawUtil.h"
#endif
#ifndef _GUINODECTRL_H_
#include "guiNodeCtrl.h"
#endif // !_GUINODECTRL_H_

class GuiNodeGraphCtrl : public GuiControl
{
public:

   typedef GuiControl Parent;

   // no resizing of nodes yet.
   enum mouseModes
   {
      Selecting,
      MovingSelection,
      DragSelecting,
      DragClone,
      DragConnection
   };

   struct Slot
   {
      GuiNodeCtrl* ownerNode;
      RectI bounds;
      ColorI col;
      bool in = false;
      bool out = false;
      bool conn = false;
      S32 connId = -1;
   };

   struct Link
   {
      Slot* startSocket;
      Slot* endSocket;
   };

   typedef Vector< Slot* > SlotVec;

   struct GraphNode
   {
      GuiNodeCtrl* mNode;
      SlotVec mInSlots;
      SlotVec mOutSlots;
   };

protected:
   typedef Vector< GraphNode* > GraphNodeVector;
   typedef Vector< Link > LinkVec;
   typedef Vector< GuiNodeCtrl* > GuiNodeVector;
   typedef SimObjectPtr< GuiNodeCtrl > GuiNodePtr;
   
   Slot*                mDragStartSlot;
   LinkVec              mLinks;
   bool                 mFullBoxSelection;
   GraphNodeVector      mGraphNodes;
   GraphNodeVector      mSelectedNodes;
   Point2I              mLastMousePos;
   Point2I              mLastDragPos;
   Point2I              mSelectionAnchor;
   Point2I              mGridSnap;
   Point2I              mDragBeginPoint;
   Vector<Point2I>      mDragBeginPoints;
   bool                 mDragAddSelection;
   bool                 mDragMoveUndo;
   mouseModes           mMouseDownMode;

   // snapping is always on.

   // Undo
   SimGroup* mTrash;
   SimSet* mSelectedSet;

   // grid drawing
   GFXVertexBufferHandle<GFXVertexPCT> mDots;
   GFXStateBlockRef mDotSB;
   void                 startDragMove(const Point2I& startPoint);
   void                 startDragRectangle(const Point2I& startPoint);
   void                 startDragClone(const Point2I& startPoint);
   void                 setMouseMode(mouseModes mode);

   DECLARE_CALLBACK(void, onDelete, ());

public:
   DECLARE_CONOBJECT(GuiNodeGraphCtrl);
   DECLARE_CATEGORY("Gui Containers");
   GuiNodeGraphCtrl();

   bool              onWake();
   void              onSleep();
   static void       initPersistFields();
   virtual bool      onAdd();
   virtual void      onRemove();

   // rendering
   void              getDragRect(RectI& box);
   //void              onPreRender();
   void              onRender(Point2I offset, const RectI& updateRect);

   // Undo Access.
   void              undo();
   void              redo();
   SimGroup*         getTrash() { return mTrash; }

   // selection functions
   void              addSelection(GraphNode* node);
   void              removeSelection(S32 id);
   void              removeSelection(GraphNode* node);
   void              clearSelection(void);
   void              Select(GraphNode* node);
   bool              selectionContains(GraphNode* node);
   void              moveSelection(const Point2I& delta, bool callback);
   void              cloneSelection();
   RectI             getSelectionBounds();
   void              addSelectNodesInRegion(const RectI& rect, U32 flags);
   void              addSelectNodeAt(const Point2I& pos);

   // snapping.
   void              doSnapping(const GuiEvent& event, const RectI& selectionBounds, Point2I& delta);
   void              doGridSnap(const GuiEvent& event, const RectI& selectionBounds, const RectI& selectionBoundsGlobal, Point2I& delta);

   // handle input.
   bool              onKeyDown(const GuiEvent& event);
   GraphNode*        findHitNode(const Point2I& pt);
   Slot*             findHitSlotNode(const Point2I& pt, GraphNode* node);
   Slot*             findHitSlot(const Point2I& pt);
   void              findHitNodes(const RectI& rect, Vector<GraphNode*>& outResult);
   void              onMouseDown(const GuiEvent& event);
   void              onMouseUp(const GuiEvent& event);
   void              onMouseDragged(const GuiEvent& event);
   //void              onRightMouseDown(const GuiEvent& event);
   mouseModes        getMouseMode() const { return mMouseDownMode; }

   // handle adding nodes.
   void              addNewNode(GuiNodeCtrl* node);
   void              addNodeSlots(GraphNode* node);
   void              updateSlotPosition(const Point2I& delta, GraphNode* node);
   Point2I           getSlotCenter(Slot* sock);
   void              deleteSelection();

};

#endif // !_GUINODEGRAPHCTRL_H_
