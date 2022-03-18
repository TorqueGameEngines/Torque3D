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
#include "console/consoleTypes.h"
#include "gui/core/guiCanvas.h"
#include "gui/containers/guiScrollCtrl.h"
#include "core/strings/stringUnit.h"
#include "console/engineAPI.h"

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
   Vector<GuiNodeCtrl*>::iterator i;
   for (i = mSelectedNodes.begin(); i != mSelectedNodes.end(); i++)
      mDragBeginPoints.push_back((*i)->getPosition());

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
   VECTOR_SET_ASSOCIATION(mSockets);
   VECTOR_SET_ASSOCIATION(mConnections);

   VECTOR_SET_ASSOCIATION(mAllNodes);
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

void GuiNodeGraphCtrl::onRender(Point2I offset, const RectI& updateRect)
{
   Point2I ctOffset;
   Point2I cext;
   bool keyFocused = isFirstResponder();

   GFXDrawUtil* drawer = GFX->getDrawUtil();

   renderChildControls(offset, updateRect);

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

   // draw connections.
   for (U32 i = 0; i < mConnections.size(); i++)
   {
      Point2I start = getSocketCenter(mConnections[i].startSocket);
      Point2I end = getSocketCenter(mConnections[i].endSocket);
      drawer->drawLine(start, end, ColorI(255, 0, 0));
   }

   // draw our sockets.
   for (U32 i = 0; i < mSockets.size(); i++)
   {
      RectI s = mSockets[i].bounds;
      s.point += offset;
      drawer->drawRect(s, mSockets[i].col);
      if (mSockets[i].conn)
         drawer->drawRectFill(s, mSockets[i].col);
   }

   // draw new connections on top of sockets.
   if (mMouseDownMode == DragConnection)
   {
      Point2I start = getSocketCenter(mDragStartSocket);
      drawer->drawLine(start, mLastMousePos, ColorI(255, 0, 0));
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

void GuiNodeGraphCtrl::addSelection(GuiNodeCtrl* node)
{
   if (!selectionContains(node))
      mSelectedNodes.push_back(node);
}

void GuiNodeGraphCtrl::deleteSelection()
{
   Vector< GuiNodeCtrl* >::iterator i;
   for (i = mSelectedNodes.begin(); i != mSelectedNodes.end(); i++)
   {
      Vector< GuiNodeCtrl* >::iterator j;
      for (j = mAllNodes.begin(); j != mAllNodes.end(); j++)
         if (*j == *i)
            mAllNodes.remove(*j);

      mTrash->addObject(*i);
   }

   clearSelection();
}

void GuiNodeGraphCtrl::removeSelection(S32 id)
{
   GuiNodeCtrl* ctrl;
   if (Sim::findObject(id, ctrl))
      removeSelection(ctrl);
}

void GuiNodeGraphCtrl::removeSelection(GuiNodeCtrl* node)
{
   if (selectionContains(node))
   {
      Vector< GuiNodeCtrl* >::iterator i = T3D::find(mSelectedNodes.begin(), mSelectedNodes.end(), node);
      if (i != mSelectedNodes.end())
         mSelectedNodes.erase(i);

   }
}

void GuiNodeGraphCtrl::clearSelection(void)
{
   mSelectedNodes.clear();
}

void GuiNodeGraphCtrl::Select(GuiNodeCtrl* node)
{
   clearSelection();
   addSelection(node);
}

bool GuiNodeGraphCtrl::selectionContains(GuiNodeCtrl* node)
{
   Vector<GuiNodeCtrl*>::iterator i;
   for (i = mSelectedNodes.begin(); i != mSelectedNodes.end(); i++)
      if (node == *i) return true;
   return false;
}

void GuiNodeGraphCtrl::moveSelection(const Point2I& delta, bool callback)
{
   Vector<GuiNodeCtrl*>::iterator i;
   for (i = mSelectedNodes.begin(); i != mSelectedNodes.end(); i++)
   {
      GuiNodeCtrl* node = *i;
      if (!node->isLocked())
         node->setPosition(node->getPosition() + delta);
   }
}

void GuiNodeGraphCtrl::cloneSelection()
{
   Vector< GuiNodeCtrl* > newSelection;

   // Clone the controls in the current selection.

   const U32 numOldControls = mSelectedNodes.size();
   for (U32 i = 0; i < numOldControls; ++i)
   {
      GuiNodeCtrl* ctrl = mSelectedNodes[i];
      // Clone and add to set.

      GuiNodeCtrl* clone = dynamic_cast<GuiNodeCtrl*>(ctrl->deepClone());
      if (clone)
         newSelection.push_back(clone);
   }

   // Exchange the selection set.

   clearSelection();
   const U32 numNewControls = newSelection.size();
   for (U32 i = 0; i < numNewControls; ++i)
      addSelection(newSelection[i]);

}

RectI GuiNodeGraphCtrl::getSelectionBounds()
{
   Vector<GuiNodeCtrl*>::const_iterator i = mSelectedNodes.begin();

   Point2I minPos = this->localToGlobalCoord(Point2I(0, 0));
   Point2I maxPos = minPos;

   for (; i != mSelectedNodes.end(); i++)
   {
      Point2I iPos = (**i).localToGlobalCoord(Point2I(0, 0));

      minPos.x = getMin(iPos.x, minPos.x);
      minPos.y = getMin(iPos.y, minPos.y);

      Point2I iExt = (**i).getExtent();

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

   Vector< GuiNodeCtrl* > hits;

   findHitNodes(rect, hits);
   // Add all controls that got hit.

   for (U32 i = 0, num = hits.size(); i < num; ++i)
      addSelection(hits[i]);
}

void GuiNodeGraphCtrl::addSelectNodeAt(const Point2I& pos)
{
   GuiNodeCtrl* hit = findHitNode(pos);

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

GuiNodeCtrl* GuiNodeGraphCtrl::findHitNode(const Point2I& pt)
{
   if (mAllNodes.size() == 0)
      return NULL;
   U32 i = mAllNodes.size() - 1;
   while (i != 0)
   {
      GuiNodeCtrl* node = mAllNodes[i];

      if (node->isVisible() && node->pointInControl(pt))
      {
         return node;
      }

      i--;
   }

   return NULL;
}

void GuiNodeGraphCtrl::findHitNodes(const RectI& rect, Vector< GuiNodeCtrl* >& outResult)
{
   if (mAllNodes.size() == 0)
      return;

   U32 i = mAllNodes.size() - 1;
   while (i != 0)
   {
      GuiNodeCtrl* node = mAllNodes[i];

      if (node->isVisible())
      {
         RectI rectInParentSpace = rect;
         // not sure if this is needed but do it anyway.
         rectInParentSpace.point += getPosition();

         if (rectInParentSpace.contains(node->getBounds()))
         {
            outResult.push_back(node);
         }
      }

      i--;
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

   GuiNodeCtrl* node = findHitNode(mLastMousePos);

   if (U32 sock = getStartConnectionSocket(mLastMousePos) > -1)
   {
      mDragStartSocket = mSockets[sock];
      mMouseDownMode = DragConnection;
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
      return;
   }
   else if (selectionContains(node))
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
         if (node->inTitleBar(event))
            startDragMove(event.mousePoint);
         else
            node->onMouseDownGraph(event);
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
      if (U32 sock = getStartConnectionSocket(mLastMousePos) > -1)
      {

         // are we connecting to the same type?
         if (mDragStartSocket.in && mSockets[sock].in || mDragStartSocket.out && mSockets[sock].out)
            return;

         // are we connecting to the same node......
         if (mDragStartSocket.ownerNode == mSockets[sock].ownerNode)
            return;

         // we have hit an opposite socket.
         Connection conn;
         if (mDragStartSocket.in)
         {
            conn.startSocket = mDragStartSocket;
            conn.endSocket = mSockets[sock];
         }
         else
         {
            conn.startSocket = mSockets[sock];
            conn.endSocket = mDragStartSocket;
         }
         // if we have reached here both have a connection.
         mDragStartSocket.conn = true;
         mSockets[sock].conn = true;
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

   GuiNodeCtrl* node = findHitNode(mousePoint);

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
               Point2I selCtrlPos = mSelectedNodes[i]->getPosition();
               Point2I snapBackPoint(selCtrlPos.x, mDragBeginPoints[i].y);
               // This is kind of nasty but we need to snap back if we're not at origin point with selection - JDD
               if (selCtrlPos.y != mDragBeginPoints[i].y)
                  mSelectedNodes[i]->setPosition(snapBackPoint);
            }
            delta.y = 0;
         }
         if (dragTotalDelta.x < 10 && dragTotalDelta.x > -10)
         {
            for (S32 i = 0; i < mSelectedNodes.size(); i++)
            {
               Point2I selCtrlPos = mSelectedNodes[i]->getPosition();
               Point2I snapBackPoint(mDragBeginPoints[i].x, selCtrlPos.y);
               // This is kind of nasty but we need to snap back if we're not at origin point with selection - JDD
               if (selCtrlPos.x != mDragBeginPoints[i].x)
                  mSelectedNodes[i]->setPosition(snapBackPoint);
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
   mAllNodes.push_back(node);
   addNodeSockets(node);
}

void GuiNodeGraphCtrl::addNodeSockets(GuiNodeCtrl* node)
{
   // loop through inputs.
   Point2I ext(15, 15);
   for (U32 i = 0; i < node->mInputs.size(); i++)
   {
      // put our rect on the left edge.
      Point2I pos = globalToLocalCoord(node->localToGlobalCoord(Point2I(node->getPosition().x, node->mInputs[i].pos.y)));
      Socket inSock;
      inSock.ownerNode = node;
      // convert coords to global.
      inSock.bounds = RectI(pos, ext);
      inSock.col = node->mInputs[i].color;
      inSock.in = true;
      mSockets.push_back(inSock);
   }

   // loop through outputs.
   for (U32 j = 0; j < node->mOutputs.size(); j++)
   {
      // put our rect on the right edge.
      Point2I pos = globalToLocalCoord(node->localToGlobalCoord(Point2I(node->getExtent().x - 20, node->mOutputs[j].pos.y)));
      Socket outSock;
      outSock.ownerNode = node;
      // convert coords to global.
      outSock.bounds = RectI(pos, ext);
      outSock.col = node->mOutputs[j].color;
      outSock.out = true;
      mSockets.push_back(outSock);
   }
}

U32 GuiNodeGraphCtrl::getStartConnectionSocket(const Point2I& pt)
{
   if (mSockets.size() == 0)
      return -1;

   U32 i = mSockets.size() - 1;
   while (i != 0)
   {
      Socket sock = mSockets[i];
      if(sock.bounds.pointInRect(pt))
         return i;

      i--;
   }

   return -1;
}

Point2I GuiNodeGraphCtrl::getSocketCenter(Socket sock)
{
   RectI bounds = sock.bounds;

   return Point2I(bounds.point.x + bounds.extent.x / 2,
                  bounds.point.y + bounds.extent.y / 2);

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

