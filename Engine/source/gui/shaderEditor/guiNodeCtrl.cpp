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
#include "guiNodeCtrl.h"

#include "console/consoleTypes.h"
#include "console/console.h"
#include "console/engineAPI.h"
#include "gfx/gfxDevice.h"
#include "gui/core/guiCanvas.h"
#include "gui/core/guiDefaultControlRender.h"
#include "gfx/gfxDevice.h"
#include "gfx/gfxDrawUtil.h"
#include "gui/containers/guiRolloutCtrl.h"
#include "gfx/primBuilder.h"

IMPLEMENT_CONOBJECT(GuiNodeCtrl);
ConsoleDocClass(GuiNodeCtrl,
   "@ingroup GuiContainers"
);

GuiNodeCtrl::GuiNodeCtrl()
   :  mCanCollapse(true),
      mCollapsed(false),
      mTitleBarColor("Blue"),
      mTitleBarFadeColor("Black")
{

   VECTOR_SET_ASSOCIATION(mInputs);
   VECTOR_SET_ASSOCIATION(mOutputs);

   mIsContainer = true;
   mHasConnections = false;
   mTitleHeight = 24;
   mText = "Default Node";
   mChildPadding = 5;
   mConnectionPadding = 5;
   mConnectionIndent = 20;
   // minimum width and height due to header
   setMinExtent(Point2I(200, mTitleHeight));

   addOutput("X");
   addOutput("Y");
   addOutput("Z");
   addOutput("W");

}

void GuiNodeCtrl::drawBlendHeader(RectI& bounds, ColorI leftCol, ColorI rightCol)
{
   GFX->setStateBlock(mStateBlock);

   S32 l = bounds.point.x, r = bounds.point.x + bounds.extent.x;
   S32 t = bounds.point.y, b = bounds.point.y + bounds.extent.y;

   PrimBuild::begin(GFXTriangleStrip, 4);

   // top left.
   PrimBuild::color(leftCol);
   PrimBuild::vertex2i(l, t);

   // bottom left.
   PrimBuild::color(leftCol);
   PrimBuild::vertex2i(l, b);

   // top right.
   PrimBuild::color(rightCol);
   PrimBuild::vertex2i(r, t);

   // bottom right.
   PrimBuild::color(rightCol);
   PrimBuild::vertex2i(r, b);

   PrimBuild::end();
}

bool GuiNodeCtrl::onWake()
{
   if (!Parent::onWake())
      return false;

   updateNodeSize();

   return true;
}

void GuiNodeCtrl::onSleep()
{
   Parent::onSleep();
}

void GuiNodeCtrl::initPersistFields()
{
   addGroup("Node");

      addField("titleHeight", TypeS32, Offset(mTitleHeight, GuiNodeCtrl),
         "The height of the title bar.");

      addField("connectionIndent", TypeS32, Offset(mConnectionIndent, GuiNodeCtrl),
         "The indent from the edges for the connections.");

      addField("connectionPadding", TypeS32, Offset(mConnectionPadding, GuiNodeCtrl),
         "The padding between connections and child items area.");

      addField("childPadding", TypeS32, Offset(mChildPadding, GuiNodeCtrl),
         "The padding between child items.");

      addField("titleHeight", TypeS32, Offset(mTitleHeight, GuiNodeCtrl),
         "The height of the title bar.");

      addField("headerColor", TypeColorI, Offset(mTitleBarColor, GuiNodeCtrl),
         "The title bar color for this node.");

      addField("headerFadeColor", TypeColorI, Offset(mTitleBarFadeColor, GuiNodeCtrl),
         "The title bar fade color for this node.");

      addField("text", TypeRealString, Offset(mText, GuiNodeCtrl),
         "Text label to display in titlebar.");

      addField("canCollapse", TypeBool, Offset(mCanCollapse, GuiNodeCtrl),
         "Whether the node can be collapsed by clicking the collapse button.");
      
   endGroup("Node");

   Parent::initPersistFields();
}

void GuiNodeCtrl::updateNodeSize()
{
   Point2I extent = getExtent();
   S32 begin, end, step, maxWidth;
   begin = 0;
   end = size();
   step = 1;
   maxWidth = 0;
   Point2I curPos(0, mTitleHeight);

   if (empty())
   {
      // just update our connections.
      updateConnections(curPos);
      Point2I newPos(getPosition());
      Point2I newSize(maxWidth, curPos.y);
      newSize.setMax(getMinExtent());
      resize(newPos, newSize);

      return;
   }

   for (S32 i = begin; i != end; i += step)
   {
      GuiControl* gc = dynamic_cast<GuiControl*>(at(i));
      if (gc && gc->isVisible())
      {
         // Add padding between controls
         if (curPos.y > 0)
            curPos.y += mChildPadding;

         Point2I childPos = curPos;
         childPos.x = gc->getLeft();

         Point2I childSize(gc->getExtent());

         gc->resize(childPos, childSize);

         curPos.y += gc->getHeight();
         maxWidth = getMax(maxWidth, childPos.x + childSize.x);
      }
   }

   updateConnections(curPos);

   Point2I newPos(getPosition());
   Point2I newSize( maxWidth, curPos.y);
   newSize.setMax(getMinExtent());
   resize(newPos, newSize);

}

void GuiNodeCtrl::updateConnections(Point2I& curPos)
{
   if (!mProfile)
      return;

   Point2I inputPos(mConnectionIndent, curPos.y);
   for (U32 i = 0; i < mInputs.size(); i++)
   {
      // apply padding
      if (curPos.y > 0)
         inputPos.y += mConnectionPadding;

      // 20 height for each connection.
      inputPos.y += 20;

      Point2I connPos(mConnectionIndent, 0);
      connPos.y = (inputPos.y - mProfile->mFont->getFontSize());
      mInputs[i].pos = connPos;
   }

   Point2I outPos(0, curPos.y);
   for (U32 j = 0; j < mOutputs.size(); j++)
   {
      // apply padding
      if (curPos.y > 0)
         outPos.y += mConnectionPadding;

      outPos.y += 20;

      Point2I connPos(getExtent().x - mConnectionIndent, 0);
      U32 strWidth = mProfile->mFont->getStrWidth((const UTF8*)mOutputs[j].label.c_str());
      connPos.x = connPos.x - strWidth;
      connPos.y = (outPos.y - mProfile->mFont->getFontSize());
      mOutputs[j].pos = connPos;
   }

   // get the max and add a final pad.
   curPos.y = getMax(inputPos.y + mConnectionPadding, outPos.y + mConnectionPadding);
}

//-----------------------------------------------------------------------------
// Render this mutha
//-----------------------------------------------------------------------------

void GuiNodeCtrl::onRender(Point2I offset, const RectI& updateRect)
{
   if (!mProfile)
      return Parent::onRender(offset, updateRect);

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

   // Get our rect.
   RectI winRect;
   winRect.point = offset;
   winRect.extent = getExtent();

   // draw background.
   drawer->drawRectFill(winRect, mProfile->mFillColor);

   RectI headRect;
   headRect.point = winRect.point;
   headRect.extent = Point2I(winRect.extent.x, mTitleHeight);

   // draw header.
   //drawer->drawRectFill(headRect, mTitleBarColor);

   drawBlendHeader(headRect, mTitleBarColor, mTitleBarFadeColor);

   // draw header text.
   U32 strWidth = mProfile->mFont->getStrWidth(mText.c_str());
   Point2I headerPos = Point2I((getExtent().x / 2) - (strWidth / 2), (mTitleHeight / 2) - (mProfile->mFont->getFontSize() / 2));
   drawer->setBitmapModulation(mProfile->mFontColor);
   drawer->drawText(mProfile->mFont, headerPos + offset, mText);
   drawer->clearBitmapModulation();

   if (!mCollapsed)
   {
      for (U32 i = 0; i < mInputs.size(); i++)
      {
         drawer->setBitmapModulation(mProfile->mFontColor);
         drawer->drawText(mProfile->mFont, mInputs[i].pos + offset, (char*)mInputs[i].label.c_str());
         drawer->clearBitmapModulation();
      }

      for (U32 j = 0; j < mOutputs.size(); j++)
      {
         drawer->setBitmapModulation(mProfile->mFontColor);
         drawer->drawText(mProfile->mFont, mOutputs[j].pos + offset, mOutputs[j].label.c_str());
         drawer->clearBitmapModulation();
      }

      // Render the children
      renderChildControls(offset, updateRect);
   }

}

//-----------------------------------------------------------------------------
// Handle mouse input.
//-----------------------------------------------------------------------------

bool GuiNodeCtrl::inTitleBar(const GuiEvent& event)
{
   Point2I localPoint = globalToLocalCoord(event.mousePoint);
   // If we clicked within the title bar
   if (localPoint.y < mTitleHeight)
   {
      return true;
   }

   return false;
}

void GuiNodeCtrl::onMouseDownGraph(const GuiEvent& event)
{
   Point2I localPoint = globalToLocalCoord(event.mousePoint);

   GuiControl* ctrl = findHitControl(localPoint);
   if (ctrl && ctrl != this)
      ctrl->onMouseDown(event);
}

//-----------------------------------------------------------------------------
// Handle adding sockets./don't need a remove?
//-----------------------------------------------------------------------------

void GuiNodeCtrl::addInput(String text, ColorI col, bool allowMultiple)
{
   Input in;
   in.label = text;
   in.color = col;
   in.allowMultiple = allowMultiple;

   mInputs.push_back(in);

   updateNodeSize();
}

void GuiNodeCtrl::addOutput(String text, ColorI col, bool allowMultiple)
{
   Output out;
   out.label = text;
   out.color = col;
   out.allowMultiple = allowMultiple;

   mOutputs.push_back(out);

   updateNodeSize();
}

void GuiNodeCtrl::childResized(GuiControl* child)
{
   updateNodeSize();
}

bool GuiNodeCtrl::resize(const Point2I& newPosition, const Point2I& newExtent)
{
   if (!Parent::resize(newPosition, newExtent))
      return false;

   updateNodeSize();

   // CodeReview This logic should be updated to correctly return true/false
   //  based on whether it sized it's children. [7/1/2007 justind]
   return true;
}

//-----------------------------------------------------------------------------
// Script side
//-----------------------------------------------------------------------------

DefineEngineMethod(GuiNodeCtrl, addInput, void, (String text, ColorI col, bool allowMultiple), ,
   "Add Input socket to the node\n\n")
{
   object->addInput(text, col, allowMultiple);
}

DefineEngineMethod(GuiNodeCtrl, addOutput, void, (String text, ColorI col, bool allowMultiple), ,
   "Add Output socket to the node\n\n")
{
   object->addOutput(text, col, allowMultiple);
}
