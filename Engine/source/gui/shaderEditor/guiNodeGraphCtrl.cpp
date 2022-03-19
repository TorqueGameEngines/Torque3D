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

#include "platform/platform.h"
#include "guiNodeGraphCtrl.h"

#include "core/frameAllocator.h"
#include "core/stream/fileStream.h"
#include "core/stream/memStream.h"
#include "console/console.h"
#include "console/consoleTypes.h"
#include "console/engineAPI.h"
#include "gui/core/guiCanvas.h"
#include "gui/containers/guiScrollCtrl.h"
#include "core/strings/stringUnit.h"
#include "console/engineAPI.h"
#include "gfx/gfxDevice.h"
#include "gfx/primBuilder.h"

IMPLEMENT_CONOBJECT(GuiNodeGraphCtrl);

ConsoleDocClass(GuiNodeGraphCtrl,
   "@brief Node graph.\n\n"
   "@ingroup GuiContainers"
);

IMPLEMENT_CALLBACK(GuiNodeGraphCtrl, onDelete, void, (), (),
   "");

void GuiNodeGraphCtrl::startDragMove(const Point2I& startPoint)
{
   mDragMoveUndo = true;

   // For calculating mouse delta
   mDragBeginPoint = globalToLocalCoord(startPoint);

   // Allocate enough space for our selected controls
   mDragBeginPoints.reserve(mSelectedNodes.size());

   // For snapping to origin
   for (U32 i = 0; i < mSelectedNodes.size(); i++)
      mDragBeginPoints.push_back(mSelectedNodes[i]->mNode->getPosition());

   // Set Mouse Mode
   setMouseMode(MovingSelection);
}

void GuiNodeGraphCtrl::startDragRectangle(const Point2I& startPoint)
{
   mSelectionAnchor = globalToLocalCoord(startPoint);
   setMouseMode(DragSelecting);
}

void GuiNodeGraphCtrl::startDragClone(const Point2I& startPoint)
{
   mDragBeginPoint = globalToLocalCoord(startPoint);

   setMouseMode(DragClone);
}

void GuiNodeGraphCtrl::setMouseMode(mouseModes mode)
{
   if (mMouseDownMode != mode)
   {
      mMouseDownMode = mode;
   }
}

void GuiNodeGraphCtrl::getDragRect(RectI& box)
{
   box.point.x = getMin(mLastMousePos.x, mSelectionAnchor.x);
   box.extent.x = getMax(mLastMousePos.x, mSelectionAnchor.x) - box.point.x + 1;
   box.point.y = getMin(mLastMousePos.y, mSelectionAnchor.y);
   box.extent.y = getMax(mLastMousePos.y, mSelectionAnchor.y) - box.point.y + 1;
}

GuiNodeGraphCtrl::GuiNodeGraphCtrl()
    : mDragBeginPoint(-1,-1),
      mGridSnap(10,10),
      mDragAddSelection(false),
      mDragMoveUndo(false)
{
   VECTOR_SET_ASSOCIATION(mLinks);
   VECTOR_SET_ASSOCIATION(mSelectedNodes);
   VECTOR_SET_ASSOCIATION(mDragBeginPoints);

   mDotSB = NULL;
   mTrash = NULL;
   mSelectedSet = NULL;
   mMouseDownMode = GuiNodeGraphCtrl::Selecting;

}

//-----------------------------------------------------------------------------

void GuiNodeGraphCtrl::initPersistFields()
{
   Parent::initPersistFields();
}

//-----------------------------------------------------------------------------

bool GuiNodeGraphCtrl::onAdd()
{
   if (!Parent::onAdd())
      return false;

   mTrash = new SimGroup();
   mSelectedSet = new SimSet();

   if (!mTrash->registerObject())
      return false;
   if (!mSelectedSet->registerObject())
      return false;

   return true;
}

//-----------------------------------------------------------------------------

void GuiNodeGraphCtrl::onRemove()
{
   Parent::onRemove();

   mDotSB = NULL;

   mTrash->deleteObject();
   mSelectedSet->deleteObject();

   mTrash = NULL;
   mSelectedSet = NULL;
}

void GuiNodeGraphCtrl::renderNode(GuiNodeCtrl* node, Point2I offset, const RectI& updateRect)
{
   // Save the current clip rect 
   // so we can restore it at the end of this method.
   RectI savedClipRect = GFX->getClipRect();

   // offset is the upper-left corner of this control in screen coordinates
   // updateRect is the intersection rectangle in screen coords of the control
   // hierarchy.  This can be set as the clip rectangle in most cases.
   RectI clipRect = updateRect;

   if (node->isVisible())
   {
      Point2I childPosition = offset + node->getPosition();
      RectI childClip(childPosition, node->getExtent() + Point2I(1, 1));

      if (childClip.intersect(clipRect))
      {
         GFX->setClipRect(childClip);
         GFX->setStateBlock(mDefaultGuiSB);
         node->onRender(childPosition, childClip);
      }
   }

   // Restore the clip rect to what it was at the start
   // of this method.
   GFX->setClipRect(savedClipRect);
}

void GuiNodeGraphCtrl::drawThickLine(const Point2I& pt1, const Point2I& pt2, U32 thickness = 2, ColorI col1 = ColorI(255,255,255), ColorI col2 = ColorI(255, 255, 255))
{
   Point2F dir = Point2F(pt2.x - pt1.x, pt2.y - pt1.y);
   Point2F unitDir = dir / mSqrt(dir.x * dir.x + dir.y * dir.y);
   Point2F unitPerp(-unitDir.y, unitDir.x);
   Point2F offset = (thickness / 2.0f) * unitPerp;

   GFX->setStateBlock(mStateBlock);

   Point2F lT = Point2F(pt1.x,pt1.y) + offset;
   Point2F lB = Point2F(pt1.x, pt1.y) - offset;
   Point2F rT = Point2F(pt2.x, pt2.y) + offset;
   Point2F rB = Point2F(pt2.x, pt2.y) - offset;
   

   PrimBuild::begin(GFXTriangleStrip, 4);

   // top left.
   PrimBuild::color(col1);
   PrimBuild::vertex2f(lT.x,lT.y);

   // bottom left.
   PrimBuild::color(col1);
   PrimBuild::vertex2f(lB.x, lB.y);

   // top right.
   PrimBuild::color(col2);
   PrimBuild::vertex2f(rT.x, rT.y);

   // bottom right.
   PrimBuild::color(col2);
   PrimBuild::vertex2f(rB.x, rB.y);

   PrimBuild::end();
}

void GuiNodeGraphCtrl::onRender(Point2I offset, const RectI& updateRect)
{
   Point2I ctOffset;
   Point2I cext;
   bool keyFocused = isFirstResponder();

   if (mStateBlock.isNull())
   {
      GFXStateBlockDesc desc;
      desc.setBlend(true, GFXBlendSrcAlpha, GFXBlendInvSrcAlpha);
      desc.setZReadWrite(false);
      desc.zWriteEnable = false;
      desc.setCullMode(GFXCullNone);
      mStateBlock = GFX->createStateBlock(desc);
   }

   GFXDrawUtil* drawer = GFX->getDrawUtil();

   if (mActive)
   {
      bool multisel = mSelectedNodes.size() > 1;
      for (U32 i = 0; i < mSelectedNodes.size(); i++)
      {
         GuiNodeCtrl* ctrl = mSelectedNodes[i]->mNode;
         cext = ctrl->getExtent();
         ctOffset = ctrl->localToGlobalCoord(Point2I(0, 0));
         RectI box(ctOffset.x, ctOffset.y, cext.x, cext.y);
         ColorI outlineColor = multisel ? ColorI(0, 0, 0, 100) : ColorI(255, 255, 255, 100);
         drawer->drawRect(box, outlineColor);

      }
   }

   //renderChildControls(offset, updateRect);

   // Draw selection rectangle.
   if (mActive && mMouseDownMode == DragSelecting)
   {
      RectI b;
      getDragRect(b);
      b.point += offset;

      // Draw outline.
      drawer->drawRect(b, ColorI(100, 100, 100, 128));

      // Draw fill.
      b.inset(1, 1);
      drawer->drawRectFill(b, ColorI(150, 150, 150, 128));
   }

   // draw our sockets.
   for (U32 i = 0; i < mGraphNodes.size(); i++)
   {
      // render node in this loop so they can be drawn over the top of sockets.
      renderNode(mGraphNodes[i]->mNode, offset, updateRect);

      // render slots here so they can be drawn outside node space if needed.
      for (U32 j = 0; j < mGraphNodes[i]->mInSlots.size(); j++)
      {
         RectI s = mGraphNodes[i]->mInSlots[j]->bounds;
         s.point += offset;
         drawer->drawRect(s, mGraphNodes[i]->mInSlots[j]->col);
         if (mGraphNodes[i]->mInSlots[j]->conn)
            drawer->drawRectFill(s, mGraphNodes[i]->mInSlots[j]->col);
      }

      for (U32 j = 0; j < mGraphNodes[i]->mOutSlots.size(); j++)
      {
         RectI s = mGraphNodes[i]->mOutSlots[j]->bounds;
         s.point += offset;
         drawer->drawRect(s, mGraphNodes[i]->mOutSlots[j]->col);
         if (mGraphNodes[i]->mOutSlots[j]->conn)
            drawer->drawRectFill(s, mGraphNodes[i]->mOutSlots[j]->col);
      }
   }

   // draw connections.
   for (U32 i = 0; i < mLinks.size(); i++)
   {
      Point2I start = getSlotCenter(mLinks[i].startSocket);
      Point2I end = getSlotCenter(mLinks[i].endSocket);
      drawThickLine(start += offset, end += offset, 2, mLinks[i].startSocket->col, mLinks[i].endSocket->col);
   }

   // draw new connections on top of sockets.
   if (mMouseDownMode == DragConnection)
   {
      Point2I start = getSlotCenter(mDragStartSlot);
      drawThickLine(start += offset, mLastMousePos, 2, mDragStartSlot->col);
   }

   // draw snapping dots.
   if (mActive &&
      (mMouseDownMode == MovingSelection) &&
      (mGridSnap.x || mGridSnap.y))
   {
      cext = this->getExtent();
      Point2I coff = this->localToGlobalCoord(Point2I(0, 0));

      // create point-dots
      const Point2I& snap = mGridSnap;
      U32 maxdot = (U32)(mCeil(cext.x / (F32)snap.x) - 1) * (U32)(mCeil(cext.y / (F32)snap.y) - 1);

      if (mDots.isNull() || maxdot != mDots->mNumVerts)
      {
         mDots.set(GFX, maxdot, GFXBufferTypeStatic);

         U32 ndot = 0;
         mDots.lock();
         for (U32 ix = snap.x; ix < cext.x; ix += snap.x)
         {
            for (U32 iy = snap.y; ndot < maxdot && iy < cext.y; iy += snap.y)
            {
               mDots[ndot].color.set(50, 50, 254, 100);
               mDots[ndot].point.x = F32(ix + coff.x);
               mDots[ndot].point.y = F32(iy + coff.y);
               mDots[ndot].point.z = 0.0f;
               ndot++;
            }
         }
         mDots.unlock();
         AssertFatal(ndot <= maxdot, "dot overflow");
         AssertFatal(ndot == maxdot, "dot underflow");
      }

      if (!mDotSB)
      {
         GFXStateBlockDesc dotdesc;
         dotdesc.setBlend(true, GFXBlendSrcAlpha, GFXBlendInvSrcAlpha);
         dotdesc.setCullMode(GFXCullNone);
         mDotSB = GFX->createStateBlock(dotdesc);
      }

      GFX->setStateBlock(mDotSB);

      // draw the points.
      GFX->setVertexBuffer(mDots);
      GFX->drawPrimitive(GFXPointList, 0, mDots->mNumVerts);
   }

}

//-----------------------------------------------------------------------------
// Just in case we need these in future.
//-----------------------------------------------------------------------------

bool GuiNodeGraphCtrl::onWake()
{
   if (!Parent::onWake())
      return false;

   return true;
}

//-----------------------------------------------------------------------------

void GuiNodeGraphCtrl::onSleep()
{
   Parent::onSleep();
}

//-----------------------------------------------------------------------------
// Selection handling
//-----------------------------------------------------------------------------

void GuiNodeGraphCtrl::addSelection(GraphNode* node)
{
   if (!selectionContains(node))
      mSelectedNodes.push_back(node);
}

void GuiNodeGraphCtrl::deleteSelection()
{
   for (U32 i = 0; i < mSelectedNodes.size(); i++)
   {
      for (U32 j = 0; j < mGraphNodes.size(); j++)
         if (mGraphNodes[j] == mSelectedNodes[i])
            mGraphNodes.remove(mGraphNodes[j]);

      mTrash->addObject(mGraphNodes[i]->mNode);
   }

   clearSelection();
}

void GuiNodeGraphCtrl::removeSelection(GraphNode* node)
{
   if (selectionContains(node))
   {
      Vector< GraphNode* >::iterator i = T3D::find(mSelectedNodes.begin(), mSelectedNodes.end(), node);
      if (i != mSelectedNodes.end())
         mSelectedNodes.erase(i);

   }
}

void GuiNodeGraphCtrl::clearSelection(void)
{
   mSelectedNodes.clear();
}

void GuiNodeGraphCtrl::Select(GraphNode* node)
{
   clearSelection();
   addSelection(node);
}

bool GuiNodeGraphCtrl::selectionContains(GraphNode* node)
{
   Vector<GraphNode*>::iterator i;
   for (i = mSelectedNodes.begin(); i != mSelectedNodes.end(); i++)
      if (node == *i) return true;
   return false;
}

void GuiNodeGraphCtrl::moveSelection(const Point2I& delta, bool callback)
{
   Vector<GraphNode*>::iterator i;
   for (i = mSelectedNodes.begin(); i != mSelectedNodes.end(); i++)
   {
      GraphNode* node = *i;
      if (!node->mNode->isLocked())
      {
         node->mNode->setPosition(node->mNode->getPosition() + delta);
         updateSlotPosition(delta, node);
      }
   }
}

void GuiNodeGraphCtrl::cloneSelection()
{
   Vector< GraphNode* > newSelection;

   // Clone the controls in the current selection.

   const U32 numOldControls = mSelectedNodes.size();
   for (U32 i = 0; i < numOldControls; ++i)
   {
      GraphNode* ctrl = mSelectedNodes[i];
      // Clone and add to set.

      GuiNodeCtrl* clone = dynamic_cast<GuiNodeCtrl*>(ctrl->mNode->deepClone());
      if (clone)
      {
         // create a new graph node.
         GraphNode* gNode = new GraphNode();
         // set the clone.
         gNode->mNode = clone;
         // create their slots.
         addNodeSlots(gNode);
         // push back to the main vector.
         mGraphNodes.push_back(gNode);
         // add the graph node.
         newSelection.push_back(gNode);
      }
   }

   // Exchange the selection set.
   clearSelection();
   const U32 numNewControls = newSelection.size();
   for (U32 i = 0; i < numNewControls; ++i)
   {
      addSelection(newSelection[i]);
   }

}

RectI GuiNodeGraphCtrl::getSelectionBounds()
{
   Point2I minPos = this->localToGlobalCoord(Point2I(0, 0));
   Point2I maxPos = minPos;

   for (U32 i = 0; i < mSelectedNodes.size(); i++)
   {
      Point2I iPos = mSelectedNodes[i]->mNode->localToGlobalCoord(Point2I(0, 0));

      minPos.x = getMin(iPos.x, minPos.x);
      minPos.y = getMin(iPos.y, minPos.y);

      Point2I iExt = mSelectedNodes[i]->mNode->getExtent();

      iPos.x += iExt.x;
      iPos.y += iExt.y;

      maxPos.x = getMax(iPos.x, maxPos.x);
      maxPos.y = getMax(iPos.y, maxPos.y);
   }

   minPos = this->globalToLocalCoord(minPos);
   maxPos = this->globalToLocalCoord(maxPos);

   return RectI(minPos.x, minPos.y, (maxPos.x - minPos.x), (maxPos.y - minPos.y));
}

void GuiNodeGraphCtrl::addSelectNodesInRegion(const RectI& rect, U32 flags)
{
   // Do a hit test on the content control.

   Vector< GraphNode* > hits;

   findHitNodes(rect, hits);
   // Add all controls that got hit.

   for (U32 i = 0, num = hits.size(); i < num; ++i)
      addSelection(hits[i]);
}

void GuiNodeGraphCtrl::addSelectNodeAt(const Point2I& pos)
{
   GraphNode* hit = findHitNode(pos);

   if (hit)
      addSelection(hit);
}

//-----------------------------------------------------------------------------
// Snapping
//-----------------------------------------------------------------------------

void GuiNodeGraphCtrl::doSnapping(const GuiEvent& event, const RectI& selectionBounds, Point2I& delta)
{
   RectI selectionBoundsGlobal = selectionBounds;
   selectionBoundsGlobal.point = this->localToGlobalCoord(selectionBoundsGlobal.point);

   doGridSnap(event, selectionBounds, selectionBoundsGlobal, delta);
}

void GuiNodeGraphCtrl::doGridSnap(const GuiEvent& event, const RectI& selectionBounds, const RectI& selectionBoundsGlobal, Point2I& delta)
{
   delta += selectionBounds.point;

   if (mGridSnap.x)
      delta.x -= delta.x % mGridSnap.x;
   if (mGridSnap.y)
      delta.y -= delta.y % mGridSnap.y;

   delta -= selectionBounds.point;
}


//-----------------------------------------------------------------------------
// Input handling
//-----------------------------------------------------------------------------

GuiNodeGraphCtrl::GraphNode* GuiNodeGraphCtrl::findHitNode(const Point2I& pt)
{
   for (U32 i = 0; i < mGraphNodes.size(); i++)
   {
      if (mGraphNodes[i]->mNode->pointInControl(pt))
      {
         return mGraphNodes[i];
      }
   }

   return NULL;
}

GuiNodeGraphCtrl::Slot* GuiNodeGraphCtrl::findHitSlotNode(const Point2I& pt, GraphNode* node)
{
   for (U32 i = 0; i < node->mInSlots.size(); i++)
   {
      Slot* slot = node->mInSlots[i];
      if (slot->bounds.pointInRect(pt))
         return slot;
   }

   for (U32 i = 0; i < node->mOutSlots.size(); i++)
   {
      Slot* slot = node->mOutSlots[i];
      if (slot->bounds.pointInRect(pt))
         return slot;
   }

   return NULL;
}

GuiNodeGraphCtrl::Slot* GuiNodeGraphCtrl::findHitSlot(const Point2I& pt)
{
   for (U32 i = 0; i < mGraphNodes.size(); i++)
   {
      for (U32 j = 0; j < mGraphNodes[i]->mInSlots.size(); j++)
      {
         Slot* slot = mGraphNodes[i]->mInSlots[j];
         if (slot->bounds.pointInRect(pt))
            return slot;
      }

      for (U32 j = 0; j < mGraphNodes[i]->mOutSlots.size(); j++)
      {
         Slot* slot = mGraphNodes[i]->mOutSlots[j];
         if (slot->bounds.pointInRect(pt))
            return slot;
      }

   }

   return NULL;
}

void GuiNodeGraphCtrl::findHitNodes(const RectI& rect, Vector< GraphNode* >& outResult)
{

   for(U32 i = 0; i < mGraphNodes.size(); i++)
   {
      GraphNode* node = mGraphNodes[i];

      if (node->mNode->isVisible())
      {
         RectI rectInParentSpace = rect;
         // not sure if this is needed but do it anyway.
         rectInParentSpace.point += getPosition();

         if (rectInParentSpace.contains(node->mNode->getBounds()))
         {
            outResult.push_back(node);
         }
      }

   }
}

//-----------------------------------------------------------------------------

bool GuiNodeGraphCtrl::onKeyDown(const GuiEvent& event)
{
   if (!mActive)
      return Parent::onKeyDown(event);
   if (!(event.modifier & SI_PRIMARY_CTRL))
   {
      switch (event.keyCode)
      {
      case KEY_BACKSPACE:
      case KEY_DELETE:
         deleteSelection();
         onDelete_callback();
         return true;
      default:
         break;
      }
   }
   return false;
}

void GuiNodeGraphCtrl::onMouseDown(const GuiEvent& event)
{
   if (!mActive)
   {
      Parent::onMouseDown(event);
      return;
   }

   setFirstResponder();
   mouseLock();

   mLastMousePos = globalToLocalCoord(event.mousePoint);

   GraphNode* node = findHitNode(mLastMousePos);

   // could maybe use the node in this search too?
   Slot* sock = new Slot();
   if (node != NULL)
   {
      sock = findHitSlotNode(mLastMousePos, node);
   }
   else
   {
      sock = findHitSlot(mLastMousePos);
   }

   if (sock != NULL)
   {
      mDragStartSlot = sock;
      mMouseDownMode = DragConnection;
   }

   if (sock == NULL)
   {
      delete sock;
   }

   if (event.modifier & SI_SHIFT)
   {
      // Shift is down.  Start rectangle selection in add mode
      // no matter what we have hit.
      startDragRectangle(event.mousePoint);
      mDragAddSelection = true;
   }
   if (node == NULL)
   {
      clearSelection();
      startDragRectangle(event.mousePoint);
      mDragAddSelection = true;
   }
   else if (mSelectedNodes.size() > 1 && selectionContains(node))
   {
      if (event.modifier & SI_MULTISELECT)
      {
         removeSelection(node);

         //set the mode
         setMouseMode(Selecting);
      }
      else if (event.modifier & SI_PRIMARY_ALT)
      {
         // Alt is down.  Start a drag clone.
         startDragClone(event.mousePoint);
      }
      else
      {
         // if this is a multiple selection just move.
         startDragMove(event.mousePoint);
      }
   }
   else
   {
      if (event.modifier & SI_PRIMARY_ALT)
      {
         // Alt is down.  Start a drag clone.
         clearSelection();
         addSelection(node);
         startDragClone(event.mousePoint);
      }
      else if (event.modifier & SI_MULTISELECT)
      {
            addSelection(node);
      }
      else
      {
         // Clicked on child control.  Start move.
         clearSelection();
         addSelection(node);

         // only one node selected, so make sure we are in header.
         if (node->mNode->inTitleBar(event))
            startDragMove(event.mousePoint);
         else
            node->mNode->onMouseDownGraph(event);
      }
   }
}

void GuiNodeGraphCtrl::onMouseUp(const GuiEvent& event)
{
   if (!mActive)
   {
      Parent::onMouseUp(event);
      return;
   }

   mouseUnlock();

   // Reset Drag Axis Alignment Information
   mDragBeginPoint.set(-1, -1);
   mDragBeginPoints.clear();

   mLastMousePos = globalToLocalCoord(event.mousePoint);

   if (mMouseDownMode == DragConnection)
   {
      Slot* slot = findHitSlot(mLastMousePos);

      if (slot != NULL)
      {

         // are we connecting to the same type?
         if (mDragStartSlot->in && slot->in || mDragStartSlot->out && slot->out)
         {
            //reset the mouse mode
            setFirstResponder();
            setMouseMode(Selecting);
            return;
         }

         // are we connecting to the same node......
         if (mDragStartSlot->ownerNode == slot->ownerNode)
         {
            //reset the mouse mode
            setFirstResponder();
            setMouseMode(Selecting);
            return;
         }

         // we have hit an opposite socket.
         Link conn;
         if (mDragStartSlot->in)
         {
            conn.startSocket = mDragStartSlot;
            conn.endSocket = slot;
         }
         else
         {
            conn.startSocket = slot;
            conn.endSocket = mDragStartSlot;
         }
         // if we have reached here both have a connection.
         mDragStartSlot->conn = true;
         slot->conn = true;
         mLinks.push_back(conn);
      }
   }

   if (mMouseDownMode == DragSelecting)
   {
      // If not multiselecting, clear the current selection.

      if (!(event.modifier & SI_MULTISELECT) && !mDragAddSelection)
         clearSelection();

      RectI rect;
      getDragRect(rect);

      // If the region is somewhere less than at least 2x2, count this as a
      // normal, non-rectangular selection. 

      if (rect.extent.x <= 2 && rect.extent.y <= 2)
         addSelectNodeAt(rect.point);
      else
      {
         // Use HIT_AddParentHits by default except if ALT is pressed.
         // Use HIT_ParentPreventsChildHit if ALT+CTRL is pressed.

         U32 hitFlags = 0;
         if (!(event.modifier & SI_PRIMARY_ALT))
            hitFlags |= HIT_AddParentHits;
         if (event.modifier & SI_PRIMARY_ALT && event.modifier & SI_CTRL)
            hitFlags |= HIT_ParentPreventsChildHit;

         addSelectNodesInRegion(rect, hitFlags);
      }
   }

   //reset the mouse mode
   setFirstResponder();
   setMouseMode(Selecting);

}

void GuiNodeGraphCtrl::onMouseDragged(const GuiEvent& event)
{
   if (!mActive)
   {
      Parent::onMouseDragged(event);
      return;
   }

   Point2I mousePoint = globalToLocalCoord(event.mousePoint);

   GraphNode* node = findHitNode(mousePoint);

   if (mMouseDownMode == DragConnection)
   {
      mLastMousePos = mousePoint;
   }

   // If we're doing a drag clone, see if we have crossed the move threshold.  If so,
   // clone the selection and switch to move mode.
   if (mMouseDownMode == DragClone)
   {
      // If we haven't yet crossed the mouse delta to actually start the
      // clone, check if we have now.

      S32 delta = mAbs((mousePoint - mDragBeginPoint).len());
      if (delta >= 4)
      {
         cloneSelection();
         mLastMousePos = mDragBeginPoint;
         mDragMoveUndo = false;

         setMouseMode(MovingSelection);
      }
   }
   if (mMouseDownMode == MovingSelection && mSelectedNodes.size())
   {
      Point2I delta = mousePoint - mLastMousePos;
      RectI selectionBounds = getSelectionBounds();

      // Apply snaps.
      doSnapping(event, selectionBounds, delta);

      //RDTODO: to me seems to be in need of revision
      // Do we want to align this drag to the X and Y axes within a certain threshold?
      if (event.modifier & SI_SHIFT && !(event.modifier & SI_PRIMARY_ALT))
      {
         Point2I dragTotalDelta = event.mousePoint - localToGlobalCoord(mDragBeginPoint);
         if (dragTotalDelta.y < 10 && dragTotalDelta.y > -10)
         {
            for (S32 i = 0; i < mSelectedNodes.size(); i++)
            {
               Point2I selCtrlPos = mSelectedNodes[i]->mNode->getPosition();
               Point2I snapBackPoint(selCtrlPos.x, mDragBeginPoints[i].y);
               // This is kind of nasty but we need to snap back if we're not at origin point with selection - JDD
               if (selCtrlPos.y != mDragBeginPoints[i].y)
                  mSelectedNodes[i]->mNode->setPosition(snapBackPoint);
            }
            delta.y = 0;
         }
         if (dragTotalDelta.x < 10 && dragTotalDelta.x > -10)
         {
            for (S32 i = 0; i < mSelectedNodes.size(); i++)
            {
               Point2I selCtrlPos = mSelectedNodes[i]->mNode->getPosition();
               Point2I snapBackPoint(mDragBeginPoints[i].x, selCtrlPos.y);
               // This is kind of nasty but we need to snap back if we're not at origin point with selection - JDD
               if (selCtrlPos.x != mDragBeginPoints[i].x)
                  mSelectedNodes[i]->mNode->setPosition(snapBackPoint);
            }
            delta.x = 0;
         }
      }

      if (delta.x || delta.y)
         moveSelection(delta, mDragMoveUndo);

      mLastMousePos += delta;
   }
   else
      mLastMousePos = mousePoint;

}

//-----------------------------------------------------------------------------
// Node add handling
//-----------------------------------------------------------------------------

void GuiNodeGraphCtrl::addNewNode(GuiNodeCtrl* node)
{
   this->addObject(node);
   GraphNode* gNode = new GraphNode();
   gNode->mNode = node;
   addNodeSlots(gNode);

   mGraphNodes.push_back(gNode);
}

void GuiNodeGraphCtrl::addNodeSlots(GraphNode* node)
{
   GuiNodeCtrl* guiNode = node->mNode;
   // loop through inputs.
   Point2I ext(16, 16);
   for (U32 i = 0; i < node->mNode->mInputs.size(); i++)
   {
      // put our rect on the left edge.
      Point2I pos = globalToLocalCoord(guiNode->localToGlobalCoord(Point2I(0, guiNode->mInputs[i].pos.y)));
      Slot* inSlot = new Slot();
      inSlot->ownerNode = guiNode;
      // convert coords to global.
      inSlot->bounds = RectI(pos, ext);
      inSlot->col = guiNode->mInputs[i].color;
      inSlot->in = true;
      node->mInSlots.push_back(inSlot);
   }

   // loop through outputs.
   for (U32 j = 0; j < guiNode->mOutputs.size(); j++)
   {
      // put our rect on the right edge.
      Point2I pos = globalToLocalCoord(guiNode->localToGlobalCoord(Point2I(guiNode->getExtent().x - 20, guiNode->mOutputs[j].pos.y)));
      Slot* outSlot = new Slot();
      outSlot->ownerNode = guiNode;
      // convert coords to global.
      outSlot->bounds = RectI(pos, ext);
      outSlot->col = guiNode->mOutputs[j].color;
      outSlot->out = true;
      node->mOutSlots.push_back(outSlot);
   }
}

void GuiNodeGraphCtrl::updateSlotPosition(const Point2I& delta, GraphNode* node)
{
   for (U32 i = 0; i < node->mInSlots.size(); i++)
   {
      node->mInSlots[i]->bounds.point += delta;
   }

   for (U32 i = 0; i < node->mOutSlots.size(); i++)
   {
      node->mOutSlots[i]->bounds.point += delta;
   }
}

Point2I GuiNodeGraphCtrl::getSlotCenter(Slot* slot)
{
   RectI bounds = slot->bounds;

   return Point2I(bounds.point.x + (bounds.extent.x / 2),
                  bounds.point.y + (bounds.extent.y / 2));

}

//-----------------------------------------------------------------------------
// Script side functions.
//-----------------------------------------------------------------------------

DefineEngineMethod(GuiNodeGraphCtrl, addNewNode, void, (GuiNodeCtrl* node), , "(GuiNodeCtrl node)")
{
   if (node)
      object->addNewNode(node);
}

DefineEngineMethod(GuiNodeGraphCtrl, getTrash, SimGroup*, (), ,
   "Gets the Node(s) that are currently in the trash.")
{
   return object->getTrash();
}

DefineEngineMethod(GuiNodeGraphCtrl, deleteSelection, void, (), , "() - Delete the selected controls.")
{
   object->deleteSelection();
}

