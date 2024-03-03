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

#include "core/frameAllocator.h"
#include "core/stream/fileStream.h"
#include "core/stream/memStream.h"
#include "console/consoleTypes.h"
#include "gui/core/guiCanvas.h"
#include "console/engineAPI.h"
#include "console/script.h"

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

   mActive = true;
   mMouseDownMode = GuiShaderEditor::Selecting;

   mTrash = NULL;
   mSelectedSet = NULL;
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

void GuiShaderEditor::initPersistFields()
{
   docsURL;
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
   mSelectedSet = new SimSet();

   if (!mTrash->registerObject())
      return false;
   if (!mSelectedSet->registerObject())
      return false;

   return true;
}

void GuiShaderEditor::onRemove()
{
   mTrash->deleteObject();
   mSelectedSet->deleteObject();

   mTrash = NULL;
   mSelectedSet = NULL;
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

   GFXDrawUtil* drawer = GFX->getDrawUtil();

   for (ShaderNode* node : mCurrNodes)
   {
      // this is useful for sub node graphs.
      if (node->isVisible())
      {
         Point2I childPos = offset + node->getPosition();
         RectI childClip(childPos, node->getExtent() + Point2I(1, 1));

         if (childClip.intersect(clipRect))
         {
            GFX->setClipRect(childClip);
            GFX->setStateBlock(mDefaultGuiSB);
            node->onRender(offset, childClip);
         }

         if (selectionContains(node))
         {
            GFX->setClipRect(clipRect);
            childClip.inset(1, 1);
            drawer->drawRect(childClip, ColorI(255, 255, 0, 128));
         }
      }
   }

   // Restore the clip rect to what it was at the start
   // of this method.
   GFX->setClipRect(savedClipRect);
}

void GuiShaderEditor::onRender(Point2I offset, const RectI& updateRect)
{
   offset += mViewOffset * mZoomScale;

   GFXDrawUtil* drawer = GFX->getDrawUtil();

   // render our nodes.
   renderNodes(offset, updateRect);

   // Draw selection rectangle last so it is rendered on top.
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
}

bool GuiShaderEditor::onKeyDown(const GuiEvent& event)
{
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
   mLastMousePos = globalToLocalCoord(event.mousePoint) + mViewOffset * mZoomScale;

   ShaderNode* node = findHitNode(mLastMousePos);

   if (event.modifier & SI_SHIFT)
   {
      startDragRectangle(mLastMousePos);
      mDragAddSelection = true;
   }
   else if (selectionContains(node))
   {
      if (event.modifier & SI_MULTISELECT)
      {
         removeSelection(node);
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
      if (node == NULL)
      {
         startDragRectangle(mLastMousePos);
         mDragAddSelection = false;
      }
      else if (event.modifier & SI_PRIMARY_ALT && node != NULL)
      {
         // Alt is down.  Start a drag clone.
         clearSelection();
         addSelection(node);
         startDragClone(mLastMousePos);
      }
      else if (event.modifier & SI_MULTISELECT)
      {
         addSelection(node);
      }
      else
      {
         // Clicked on node.  Start move.
         clearSelection();
         addSelection(node);
         startDragMove(mLastMousePos);
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

   ShaderNode* node = findHitNode(mLastMousePos);

   //unlock the mouse
   mouseUnlock();

   // Reset Drag Axis Alignment Information
   mDragBeginPoint.set(-1, -1);
   mDragBeginPoints.clear();

   // get mouse pos with our view offset and scale.
   mLastMousePos = globalToLocalCoord(event.mousePoint) + mViewOffset * mZoomScale;

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
         Vector< ShaderNode* > hits;
         findNodesInRect(rect, hits);

         for (ShaderNode* node : hits)
         {
            addSelection(node);
         }
      }
   }

   if (mMouseDownMode == MovingSelection && mDragMoveUndo)
   {

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
   Point2I mousePoint = globalToLocalCoord(event.mousePoint) + mViewOffset * mZoomScale;

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
   mLastMousePos = globalToLocalCoord(event.mousePoint) + mViewOffset * mZoomScale;

   setMouseMode(DragPanning);

}

void GuiShaderEditor::onMiddleMouseUp(const GuiEvent& event)
{
   if (!mActive)
   {
      Parent::onMiddleMouseUp(event);
      return;
   }

   //unlock the mouse
   mouseUnlock();

   // Reset Drag Axis Alignment Information
   mDragBeginPoint.set(-1, -1);
   mDragBeginPoints.clear();

   // get mouse pos with our view offset and scale.
   mLastMousePos = globalToLocalCoord(event.mousePoint) + mViewOffset * mZoomScale;

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
   Point2I mousePoint = globalToLocalCoord(event.mousePoint) + mViewOffset * mZoomScale;

   if (mMouseDownMode == DragPanning)
   {
      Point2I delta = mousePoint - mLastMousePos;
      RectI selBounds = getSelectionBounds();

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

   mZoomScale *= 1.1;

   return true;
}

bool GuiShaderEditor::onMouseWheelDown(const GuiEvent& event)
{
   if (!mActive || !mAwake || !mVisible)
      return Parent::onMouseWheelDown(event);

   mZoomScale *= 0.9;

   return true;
}

RectI GuiShaderEditor::getSelectionBounds()
{

   Vector<ShaderNode*>::const_iterator i = mSelectedNodes.begin();

   Point2I minPos = (*i)->localToGlobalCoord(Point2I(0, 0)) + mViewOffset * mZoomScale;
   Point2I maxPos = minPos;

   for (; i != mSelectedNodes.end(); i++)
   {
      Point2I iPos = (**i).localToGlobalCoord(Point2I(0, 0)) + mViewOffset * mZoomScale;

      minPos.x = getMin(iPos.x, minPos.x);
      minPos.y = getMin(iPos.y, minPos.y);

      Point2I iExt = (**i).getExtent();

      iPos.x += iExt.x;
      iPos.y += iExt.y;

      maxPos.x = getMax(iPos.x, maxPos.x);
      maxPos.y = getMax(iPos.y, maxPos.y);
   }

   minPos = globalToLocalCoord(minPos) + mViewOffset * mZoomScale;
   maxPos = globalToLocalCoord(maxPos) + mViewOffset * mZoomScale;

   return RectI(minPos.x, minPos.y, (maxPos.x - minPos.x), (maxPos.y - minPos.y));
}

void GuiShaderEditor::deleteSelection()
{
   for (ShaderNode* node : mSelectedNodes)
   {
      mTrash->addObject(node);
   }

   clearSelection();
}

void GuiShaderEditor::moveSelection(const Point2I& delta, bool callback)
{
   for (ShaderNode* node : mSelectedNodes)
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
   Vector<ShaderNode*> newSelection;

   for (ShaderNode* node : mSelectedNodes)
   {
      ShaderNode* clone = dynamic_cast<ShaderNode*>(node->deepClone());
      if (clone)
         newSelection.push_back(clone);
   }

   clearSelection();

   for (ShaderNode* cloneNode : newSelection)
   {
      addSelection(cloneNode);
   }
}

void GuiShaderEditor::addSelectionAtPoint(const Point2I& pos)
{
   // turn hit off on already selected nodes.
   canHitSelectedNodes(false);

   ShaderNode* node = findHitNode(pos);

   // reset hit status.
   canHitSelectedNodes();

   if (node)
      addSelection(node);
}

void GuiShaderEditor::addSelection(ShaderNode* inNode)
{
   if (inNode != NULL && !selectionContains(inNode))
   {
      mSelectedNodes.push_back(inNode);
   }
}

bool GuiShaderEditor::selectionContains(ShaderNode* inNode)
{
   for (ShaderNode* node : mSelectedNodes)
   {
      if (node == inNode)
         return true;
   }

   return false;
}

void GuiShaderEditor::removeSelection(ShaderNode* inNode)
{
   if (selectionContains(inNode))
   {
      Vector< ShaderNode* >::iterator i = T3D::find(mSelectedNodes.begin(), mSelectedNodes.end(), inNode);
      if (i != mSelectedNodes.end())
         mSelectedNodes.erase(i);
   }
}

void GuiShaderEditor::canHitSelectedNodes(bool state)
{
   for (ShaderNode* node : mSelectedNodes)
      node->setCanHit(state);
}

//-----------------------------------------------------------------------------
// Input handling
//-----------------------------------------------------------------------------

ShaderNode* GuiShaderEditor::findHitNode(const Point2I& pt)
{
   for (ShaderNode* node : mCurrNodes)
   {
      if (node->pointInControl(pt))
      {
         return node;
      }
   }

   return nullptr;
}

void GuiShaderEditor::findNodesInRect(const RectI& rect, Vector<ShaderNode*>& outResult)
{
   canHitSelectedNodes(false);
   for (ShaderNode* node : mCurrNodes)
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

   for (ShaderNode* node : mSelectedNodes)
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

