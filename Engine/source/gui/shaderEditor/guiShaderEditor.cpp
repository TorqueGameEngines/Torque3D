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
#include "gui/shaderEditor/guiShaderEditor.h"
#include "gui/shaderEditor/nodes/materialOutputNode.h"
#include "gui/shaderEditor/nodes/mathNode.h"

#include "core/frameAllocator.h"
#include "core/stream/fileStream.h"
#include "core/stream/memStream.h"
#include "console/consoleTypes.h"
#include "gui/core/guiCanvas.h"
#include "console/engineAPI.h"
#include "console/script.h"
#include "console/typeValidators.h"
#include "gfx/primBuilder.h"

IMPLEMENT_CONOBJECT(GuiShaderEditor);

ConsoleDocClass(GuiShaderEditor,
   "@brief Implementation of a shader node editor.\n\n"
   "Editor use only.\n\n"
   "@internal"
);

GuiShaderEditor::GuiShaderEditor()
   : mDragBeginPoint(-1, -1),
   mViewOffset(0,0),
   mZoomScale(1.0f),
   mFullBoxSelection(false),
   mDragAddSelection(false),
   mDragMoveUndo(false)
{
   VECTOR_SET_ASSOCIATION(mCurrNodes);
   VECTOR_SET_ASSOCIATION(mSelectedNodes);
   VECTOR_SET_ASSOCIATION(mDragBeginPoints);
   VECTOR_SET_ASSOCIATION(mCurrConnections);

   mActive = true;
   mMouseDownMode = GuiShaderEditor::Selecting;

   mTrash = NULL;
   mTempConnection = NULL;
   mNodeSize = 10;
   // test
   addNode(new BRDFOutputNode());
   addNode(new MathAddNode());
   addNode(new GuiShaderNode());
}

bool GuiShaderEditor::onWake()
{
   if (!Parent::onWake())
      return false;

   return true;
}

void GuiShaderEditor::onSleep()
{
   Parent::onSleep();
}

// anything smaller than 4 is way too small....
IRangeValidator nodeSizeRange(4, 30);

void GuiShaderEditor::initPersistFields()
{
   docsURL;
   addGroup("Node Settings");
      addFieldV("nodeSize", TypeS32, Offset(mNodeSize, GuiShaderEditor),&nodeSizeRange,
         "Size of nodes.");
   endGroup("Node Settings");

   addGroup("Selection");
      addField("fullBoxSelection", TypeBool, Offset(mFullBoxSelection, GuiShaderEditor),
         "If true, rectangle selection will only select controls fully inside the drag rectangle.");
   endGroup("Selection");
   Parent::initPersistFields();
}

bool GuiShaderEditor::onAdd()
{
   if (!Parent::onAdd())
      return false;

   mTrash = new SimGroup();

   if (!mTrash->registerObject())
      return false;


   return true;
}

void GuiShaderEditor::onRemove()
{
   Parent::onRemove();

   mTrash->deleteObject();

   mTrash = NULL;

  /* for (GuiShaderNode* node : mCurrNodes)
   {
      SAFE_DELETE(node);
   }*/

   for (GuiShaderNode* node : mSelectedNodes)
   {
      SAFE_DELETE(node);
   }
}

void GuiShaderEditor::onPreRender()
{
   setUpdate();
}

void GuiShaderEditor::renderNodes(Point2I offset, const RectI& updateRect)
{
   // Save the current clip rect
   // so we can restore it at the end of this method.
   RectI savedClipRect = GFX->getClipRect();

   // offset is the upper-left corner of this control in screen coordinates
   // updateRect is the intersection rectangle in screen coords of the control
   // hierarchy.  This can be set as the clip rectangle in most cases.
   RectI clipRect = updateRect;
   clipRect.inset(2, 2);

   GFXDrawUtil* drawer = GFX->getDrawUtil();

   // render nodes in reverse order.
   for (ShaderNodeVector::iterator i = mCurrNodes.end(); i-- != mCurrNodes.begin(); )
   {
      GuiShaderNode* node = *i;
      // this is useful for sub node graphs.
      if (node->isVisible())
      {
         Point2I childPos = offset + node->getPosition();
         RectI childClip(childPos, node->getExtent() );

         if (selectionContains(node))
         {
            node->mSelected = true;
         }
         else
         {
            node->mSelected = false;
         }

         if (childClip.intersect(clipRect))
         {
            GFX->setClipRect(childClip);
            GFX->setStateBlock(mDefaultGuiSB);
            node->renderNode(childPos, childClip, mNodeSize);
         }

         GFX->setClipRect(clipRect);
         GFX->setStateBlock(mDefaultGuiSB);
         for (NodeInput* input : node->mInputNodes)
         {
            Point2I pos = node->localToGlobalCoord(input->pos) + offset;

            ColorI border = input->col;

            ColorI fill = mProfile->mFillColor;
            if (hasConnection(input))
            {
               fill = input->col;
            }

            RectI socketRect(pos, Point2I(mNodeSize, mNodeSize));
            drawer->drawCircleFill(socketRect, fill, mNodeSize / 2, 1.0f, border);
         }

         for (NodeOutput* output : node->mOutputNodes)
         {
            Point2I pos = node->localToGlobalCoord(output->pos) + offset;

            ColorI border = output->col;

            ColorI fill = mProfile->mFillColor;
            if (hasConnection(output))
            {
               fill = output->col;
            }

            RectI socketRect(pos, Point2I(mNodeSize, mNodeSize));
            drawer->drawCircleFill(socketRect, fill, mNodeSize / 2, 1.0f, border);
         }
      }
   }

   // Restore the clip rect to what it was at the start
   // of this method.
   GFX->setClipRect(savedClipRect);
}

void GuiShaderEditor::renderConnections(Point2I offset, const RectI& updateRect)
{
   // Save the current clip rect
   // so we can restore it at the end of this method.
   RectI savedClipRect = GFX->getClipRect();

   // offset is the upper-left corner of this control in screen coordinates
   // updateRect is the intersection rectangle in screen coords of the control
   // hierarchy.  This can be set as the clip rectangle in most cases.
   RectI clipRect = updateRect;
   clipRect.inset(2, 2);

   GFXDrawUtil* drawer = GFX->getDrawUtil();

   for (NodeConnection* conn : mCurrConnections)
   {
      // for temp connetion, nodeA is always the first node selected.
      Point2I start(Point2I::Zero);
      Point2I end(Point2I::Zero);

      start = conn->nodeA->localToGlobalCoord(conn->inSocket->pos) + offset;
      end = conn->nodeB->localToGlobalCoord(conn->outSocket->pos) + offset;

      start += Point2I(mNodeSize / 2, mNodeSize / 2);
      end += Point2I(mNodeSize / 2, mNodeSize / 2);

      drawer->drawThickLine(start, end,ColorI(255,255,255,255), 2.0f);
   }

   // Restore the clip rect to what it was at the start
   // of this method.
   GFX->setClipRect(savedClipRect);
}

void GuiShaderEditor::onRender(Point2I offset, const RectI& updateRect)
{
   offset += mViewOffset;

   GFXDrawUtil* drawer = GFX->getDrawUtil();

   // render our nodes.
   renderConnections(offset, updateRect);
   renderNodes(offset, updateRect);

   if (mActive)
   {
      if (mMouseDownMode == DragConnection)
      {
         // something went wrong.... fix it fix it fix it.
         if (mTempConnection == NULL)
            return;
         else
         {
            // for temp connetion, nodeA is always the first node selected.
            Point2I start(Point2I::Zero);
            ColorI color(ColorI::WHITE);
            if (mTempConnection->inSocket != NULL)
            {
               start = mTempConnection->nodeA->localToGlobalCoord(mTempConnection->inSocket->pos) + offset;
               color = mTempConnection->inSocket->col;
            }
            else if (mTempConnection->outSocket != NULL)
            {
               start = mTempConnection->nodeA->localToGlobalCoord(mTempConnection->outSocket->pos) + offset;
               color = mTempConnection->outSocket->col;
            }

            RectI sockActive(start, Point2I(mNodeSize, mNodeSize));
            start += Point2I(mNodeSize / 2, mNodeSize / 2);

            drawer->drawThickLine(start, mLastMousePos + offset, color, 2.0f);

            // draw socket overlay over the top of the line.
            drawer->drawCircleFill(sockActive, color, mNodeSize / 2);
         }
      }
      // Draw selection rectangle last so it is rendered on top.
      if (mMouseDownMode == DragSelecting)
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
   }
}

bool GuiShaderEditor::onKeyDown(const GuiEvent& event)
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
         return true;
      default:
         break;
      }
   }

   return false;
}

void GuiShaderEditor::onMouseDown(const GuiEvent& event)
{
   if (!mActive)
   {
      Parent::onMouseDown(event);
      return;
   }

   setFirstResponder();

   // lock mouse
   mouseLock();

   // get mouse pos with our view offset and scale.
   mLastMousePos = globalToLocalCoord(event.mousePoint) - mViewOffset;

   GuiShaderNode* hitNode = findHitNode(mLastMousePos);

   if(findHitSocket(mLastMousePos))
   {
      // handled in hit socket.
      return;
   }
   else
   {
      if (event.modifier & SI_SHIFT)
      {
         startDragRectangle(mLastMousePos);
         mDragAddSelection = true;
      }
      else if (selectionContains(hitNode))
      {
         if (event.modifier & SI_MULTISELECT)
         {
            removeSelection(hitNode);
            setMouseMode(Selecting);
         }
         else if (event.modifier & SI_PRIMARY_ALT)
         {
            startDragClone(mLastMousePos);
         }
         else
         {
            startDragMove(mLastMousePos);
         }
      }
      else
      {
         if (hitNode == NULL)
         {
            startDragRectangle(mLastMousePos);
            mDragAddSelection = false;
         }
         else if (event.modifier & SI_PRIMARY_ALT && hitNode != NULL)
         {
            // Alt is down.  Start a drag clone.
            clearSelection();
            addSelection(hitNode);
            startDragClone(mLastMousePos);
         }
         else if (event.modifier & SI_MULTISELECT)
         {
            addSelection(hitNode);
         }
         else
         {
            // Clicked on node.  Start move.
            clearSelection();
            addSelection(hitNode);
            startDragMove(mLastMousePos);
         }
      }
   }

}

void GuiShaderEditor::onMouseUp(const GuiEvent& event)
{
   if (!mActive)
   {
      Parent::onMouseUp(event);
      return;
   }

   //unlock the mouse
   mouseUnlock();

   // Reset Drag Axis Alignment Information
   mDragBeginPoint.set(-1, -1);
   mDragBeginPoints.clear();

   // get mouse pos with our view offset and scale.
   mLastMousePos = globalToLocalCoord(event.mousePoint) - mViewOffset;

   if (mMouseDownMode == DragConnection)
   {
      U32 ret = finishConnection(mLastMousePos);

      if (ret == 1) // we set the input on mouse up, nodeB is the inputSocket, swap order.
      {
         NodeConnection* conn = new NodeConnection();
         conn->nodeA = mTempConnection->nodeB;
         conn->nodeB = mTempConnection->nodeA;
         conn->inSocket = mTempConnection->inSocket;
         conn->outSocket = mTempConnection->outSocket;

         mCurrConnections.push_back(conn);
      }

      if (ret == 2) // we set the output on mouse up, nodeB is the outputSocket
      {
         NodeConnection* conn = new NodeConnection();
         conn->nodeA = mTempConnection->nodeA;
         conn->nodeB = mTempConnection->nodeB;
         conn->inSocket = mTempConnection->inSocket;
         conn->outSocket = mTempConnection->outSocket;

         mCurrConnections.push_back(conn);
      }

      mTempConnection = NULL;
   }

   if (mMouseDownMode == DragSelecting)
   {
      if (!(event.modifier & SI_MULTISELECT) && !mDragAddSelection)
         clearSelection();

      RectI rect;
      getDragRect(rect);

      if (rect.extent.x <= 2 && rect.extent.y <= 2)
      {
         addSelectionAtPoint(rect.point);
      }
      else
      {
         Vector< GuiShaderNode* > hits;
         findNodesInRect(rect, hits);

         for (GuiShaderNode* node : hits)
         {
            addSelection(node);
         }
      }
   }

   //reset the mouse mode
   setFirstResponder();
   setMouseMode(Selecting);
}

void GuiShaderEditor::onMouseDragged(const GuiEvent& event)
{
   if (!mActive)
   {
      Parent::onMouseDragged(event);
      return;
   }

   // get mouse pos with our view offset and scale.
   Point2I mousePoint = globalToLocalCoord(event.mousePoint) - mViewOffset;

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
      RectI selBounds = getSelectionBounds();

      if (delta.x || delta.y)
         moveSelection(delta, mDragMoveUndo);

      mLastMousePos += delta;
   }
   else
      mLastMousePos = mousePoint;
}

void GuiShaderEditor::onMiddleMouseDown(const GuiEvent& event)
{
   if (!mActive)
   {
      Parent::onMiddleMouseDown(event);
      return;
   }

   setFirstResponder();

   // lock mouse
   mouseLock();

   // get mouse pos with our view offset and scale.
   mLastMousePos = globalToLocalCoord(event.mousePoint);

   setMouseMode(DragPanning);
   getRoot()->showCursor(false);
}

void GuiShaderEditor::onMiddleMouseUp(const GuiEvent& event)
{
   if (!mActive)
   {
      Parent::onMiddleMouseUp(event);
      return;
   }

   getRoot()->showCursor(true);

   //unlock the mouse
   mouseUnlock();

   // Reset Drag Axis Alignment Information
   mDragBeginPoint.set(-1, -1);
   mDragBeginPoints.clear();

   // get mouse pos with our view offset and scale.
   mLastMousePos = globalToLocalCoord(event.mousePoint);

   setFirstResponder();
   setMouseMode(Selecting);
}

void GuiShaderEditor::onMiddleMouseDragged(const GuiEvent& event)
{
   if (!mActive)
   {
      Parent::onMiddleMouseDragged(event);
      return;
   }

   // get mouse pos with our view offset and scale.
   Point2I mousePoint = globalToLocalCoord(event.mousePoint);

   if (mMouseDownMode == DragPanning)
   {
      Point2I delta = mousePoint - mLastMousePos;
      // invert it
      if (delta.x || delta.y)
         mViewOffset += -delta;

      mLastMousePos += delta;
   }
   else
      mLastMousePos = mousePoint;
}

bool GuiShaderEditor::onMouseWheelUp(const GuiEvent& event)
{
   if (!mActive || !mAwake || !mVisible)
      return Parent::onMouseWheelUp(event);

   mZoomScale *= 1.1f;

   return true;
}

bool GuiShaderEditor::onMouseWheelDown(const GuiEvent& event)
{
   if (!mActive || !mAwake || !mVisible)
      return Parent::onMouseWheelDown(event);

   mZoomScale *= 0.9f;

   return true;
}

RectI GuiShaderEditor::getSelectionBounds()
{

   Vector<GuiShaderNode*>::const_iterator i = mSelectedNodes.begin();

   Point2I minPos = (*i)->localToGlobalCoord(Point2I(0, 0));
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

   minPos = globalToLocalCoord(minPos);
   maxPos = globalToLocalCoord(maxPos);

   return RectI(minPos.x, minPos.y, (maxPos.x - minPos.x), (maxPos.y - minPos.y));
}

void GuiShaderEditor::deleteSelection()
{
   for (GuiShaderNode* node : mSelectedNodes)
   {
      mTrash->addObject(node);

      Vector<NodeConnection*> connVec;
      for (NodeInput* input : node->mInputNodes)
      {
         hasConnection(input, connVec);
      }

      for (NodeOutput* output : node->mOutputNodes)
      {
         hasConnection(output, connVec);
      }

      for (NodeConnection* conn : connVec)
      {
         Vector< NodeConnection* >::iterator i = T3D::find(mCurrConnections.begin(), mCurrConnections.end(), conn);
         if (i != mCurrConnections.end())
         {
            mCurrConnections.erase(i);
         }
      }

      Vector< GuiShaderNode* >::iterator i = T3D::find(mCurrNodes.begin(), mCurrNodes.end(), node);
      if (i != mCurrNodes.end())
         mCurrNodes.erase(i);
   }

   clearSelection();
}

void GuiShaderEditor::moveSelection(const Point2I& delta, bool callback)
{
   for (GuiShaderNode* node : mSelectedNodes)
   {
      node->setPosition(node->getPosition() + delta);
   }
}

void GuiShaderEditor::clearSelection()
{
   mSelectedNodes.clear();
}

void GuiShaderEditor::cloneSelection()
{
   Vector<GuiShaderNode*> newSelection;

   for (GuiShaderNode* node : mSelectedNodes)
   {
      GuiShaderNode* clone = dynamic_cast<GuiShaderNode*>(node->deepClone());
      if (clone)
         newSelection.push_back(clone);
   }

   clearSelection();

   for (GuiShaderNode* cloneNode : newSelection)
   {
      mCurrNodes.push_back(cloneNode);
      addSelection(cloneNode);
   }
}

void GuiShaderEditor::addSelectionAtPoint(const Point2I& pos)
{
   // turn hit off on already selected nodes.
   canHitSelectedNodes(false);

   GuiShaderNode* node = findHitNode(pos);

   // reset hit status.
   canHitSelectedNodes();

   if (node)
      addSelection(node);
}

void GuiShaderEditor::addSelection(GuiShaderNode* inNode)
{
   if (inNode != NULL && !selectionContains(inNode))
   {
      mSelectedNodes.push_back(inNode);
   }
}

bool GuiShaderEditor::selectionContains(GuiShaderNode* inNode)
{
   for (GuiShaderNode* node : mSelectedNodes)
   {
      if (node == inNode)
         return true;
   }

   return false;
}

void GuiShaderEditor::removeSelection(GuiShaderNode* inNode)
{
   if (selectionContains(inNode))
   {
      Vector< GuiShaderNode* >::iterator i = T3D::find(mSelectedNodes.begin(), mSelectedNodes.end(), inNode);
      if (i != mSelectedNodes.end())
         mSelectedNodes.erase(i);
   }
}

void GuiShaderEditor::canHitSelectedNodes(bool state)
{
   for (GuiShaderNode* node : mSelectedNodes)
      node->setCanHit(state);
}

//-----------------------------------------------------------------------------
// Input handling
//-----------------------------------------------------------------------------

GuiShaderNode* GuiShaderEditor::findHitNode(const Point2I& pt)
{
   for (GuiShaderNode* node : mCurrNodes)
   {
      if (node->pointInControl(pt))
      {
         // selecting one node, push it to the front of the mcurrnodes stack so its rendered on top.
         Vector< GuiShaderNode* >::iterator i = T3D::find(mCurrNodes.begin(), mCurrNodes.end(), node);
         if (i != mCurrNodes.end())
         {
            mCurrNodes.erase(i);
            mCurrNodes.insert(mCurrNodes.begin(), node);
         }

         return node;
      }
   }

   return nullptr;
}

bool GuiShaderEditor::findHitSocket(const Point2I& pt)
{
   Point2I parentOffset = localToGlobalCoord(getPosition()) + mViewOffset;
   Point2I offsetPoint = pt + localToGlobalCoord(getPosition());

   for (GuiShaderNode* node : mCurrNodes)
   {
      for (NodeInput* inNode : node->mInputNodes)
      {
         Point2I offSet = node->localToGlobalCoord(inNode->pos) + parentOffset;
         RectI box(offSet.x, offSet.y, mNodeSize, mNodeSize);

         S32 xt = offsetPoint.x - box.point.x;
         S32 yt = offsetPoint.y - box.point.y;
         if (xt >= 0 && yt >= 0 && xt < box.extent.x && yt < box.extent.y)
         {
            mTempConnection = new NodeConnection();
            mTempConnection->nodeA = node;
            mTempConnection->inSocket = inNode;
            setMouseMode(DragConnection);
            return true;
         }
      }

      for (NodeOutput* outNode : node->mOutputNodes)
      {
         Point2I offSet = node->localToGlobalCoord(outNode->pos) + parentOffset;
         RectI box(offSet.x, offSet.y, mNodeSize, mNodeSize);

         S32 xt = offsetPoint.x - box.point.x;
         S32 yt = offsetPoint.y - box.point.y;
         if (xt >= 0 && yt >= 0 && xt < box.extent.x && yt < box.extent.y)
         {
            mTempConnection = new NodeConnection();
            mTempConnection->nodeA = node;
            mTempConnection->outSocket = outNode;
            setMouseMode(DragConnection);
            return true;
         }
      }
   }
   return false;
}

U32 GuiShaderEditor::finishConnection(const Point2I& pt)
{
   Point2I parentOffset = localToGlobalCoord(getPosition()) + mViewOffset;
   Point2I offsetPoint = pt + localToGlobalCoord(getPosition());

   for (GuiShaderNode* node : mCurrNodes)
   {
      for (NodeInput* inNode : node->mInputNodes)
      {
         Point2I offSet = node->localToGlobalCoord(inNode->pos) + parentOffset;
         RectI box(offSet.x, offSet.y, mNodeSize, mNodeSize);

         S32 xt = offsetPoint.x - box.point.x;
         S32 yt = offsetPoint.y - box.point.y;
         if (xt >= 0 && yt >= 0 && xt < box.extent.x && yt < box.extent.y)
         {
            if (mTempConnection->nodeA == node || mTempConnection->inSocket != NULL)
               return false;

            NodeConnection* conn;
            if(hasConnection(inNode, conn))
            {
               Vector< NodeConnection* >::iterator i = T3D::find(mCurrConnections.begin(), mCurrConnections.end(), conn);
               if (i != mCurrConnections.end())
               {
                  mCurrConnections.erase(i);
               }
            }

            mTempConnection->nodeB = node;
            mTempConnection->inSocket = inNode;
            return 1;
         }
      }

      for (NodeOutput* outNode : node->mOutputNodes)
      {
         Point2I offSet = node->localToGlobalCoord(outNode->pos) + parentOffset;
         RectI box(offSet.x, offSet.y, mNodeSize, mNodeSize);

         S32 xt = offsetPoint.x - box.point.x;
         S32 yt = offsetPoint.y - box.point.y;
         if (xt >= 0 && yt >= 0 && xt < box.extent.x && yt < box.extent.y)
         {
            if (mTempConnection->nodeA == node || mTempConnection->outSocket != NULL)
               return false;

            NodeConnection* conn;
            if (hasConnection(mTempConnection->inSocket, conn))
            {
               Vector< NodeConnection* >::iterator i = T3D::find(mCurrConnections.begin(), mCurrConnections.end(), conn);
               if (i != mCurrConnections.end())
               {
                  mCurrConnections.erase(i);
               }
            }

            mTempConnection->nodeB = node;
            mTempConnection->outSocket = outNode;
            return 2;
         }
      }
   }
   return 0;
}

bool GuiShaderEditor::hasConnection(NodeSocket* inSocket)
{
   for (NodeConnection* con : mCurrConnections)
   {
      if (con->inSocket == dynamic_cast<NodeInput*>(inSocket) || con->outSocket == dynamic_cast<NodeOutput*>(inSocket))
      {
         return true;
      }
   }

   return false;
}

bool GuiShaderEditor::hasConnection(NodeSocket* inSocket, Vector<NodeConnection*>& conn)
{
   bool ret = false;

   for (NodeConnection* con : mCurrConnections)
   {
      if (con->inSocket == dynamic_cast<NodeInput*>(inSocket) || con->outSocket == dynamic_cast<NodeOutput*>(inSocket))
      {
         conn.push_back(con);
         ret = true;
      }
   }

   return ret;
}

bool GuiShaderEditor::hasConnection(NodeSocket* inSocket, NodeConnection*& conn)
{
   for (NodeConnection* con : mCurrConnections)
   {
      if (con->inSocket == dynamic_cast<NodeInput*>(inSocket) || con->outSocket == dynamic_cast<NodeOutput*>(inSocket))
      {
         if (conn != nullptr)
            conn = con;
         return true;
      }
   }
   return false;
}

void GuiShaderEditor::findNodesInRect(const RectI& rect, Vector<GuiShaderNode*>& outResult)
{
   canHitSelectedNodes(false);
   for (GuiShaderNode* node : mCurrNodes)
   {
      if (node->getBounds().overlaps(rect))
      {
         outResult.push_back(node);
      }
   }

   canHitSelectedNodes();
}

void GuiShaderEditor::getDragRect(RectI& box)
{
   box.point.x = getMin(mLastMousePos.x, mSelectionAnchor.x);
   box.extent.x = getMax(mLastMousePos.x, mSelectionAnchor.x) - box.point.x + 1;
   box.point.y = getMin(mLastMousePos.y, mSelectionAnchor.y);
   box.extent.y = getMax(mLastMousePos.y, mSelectionAnchor.y) - box.point.y + 1;
}

void GuiShaderEditor::startDragMove(const Point2I& startPoint)
{
   mDragMoveUndo = true;

   mDragBeginPoint = startPoint;

   mDragBeginPoints.reserve(mSelectedNodes.size());

   for (GuiShaderNode* node : mSelectedNodes)
   {
      mDragBeginPoints.push_back(node->getPosition());
   }

   setMouseMode(MovingSelection);

}

void GuiShaderEditor::startDragRectangle(const Point2I& startPoint)
{
   mSelectionAnchor = startPoint;
   setMouseMode(DragSelecting);
}

void GuiShaderEditor::startDragClone(const Point2I& startPoint)
{
   mDragBeginPoint = startPoint;
   setMouseMode(DragClone);
}

void GuiShaderEditor::setMouseMode(mouseModes mode)
{
   if (mMouseDownMode != mode)
   {
      mMouseDownMode = mode;
   }
}

void GuiShaderEditor::addNode(GuiShaderNode* newNode)
{
   mCurrNodes.push_back(newNode);
}

