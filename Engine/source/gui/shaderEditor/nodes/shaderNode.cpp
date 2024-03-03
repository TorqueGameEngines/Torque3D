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
#include "gui/shaderEditor/nodes/shaderNode.h"

#include "gui/core/guiCanvas.h"

IMPLEMENT_CONOBJECT(ShaderNode);

ConsoleDocClass(ShaderNode,
   "@brief Base class for all nodes to derive from.\n\n"
   "Editor use only.\n\n"
   "@internal"
);


ShaderNode::ShaderNode()
{
   mTitle = "Default Node";
   mSelected = false;
   // fixed extent for all nodes, only height should be changed
   setExtent(150, 100);

   GuiControlProfile* profile = NULL;
   if (Sim::findObject("ToolsGuiDefaultProfile", profile))
      setControlProfile(profile);
}

bool ShaderNode::onWake()
{
   if (!Parent::onWake())
      return false;

   return true;
}

void ShaderNode::onSleep()
{
   Parent::onSleep();
}

void ShaderNode::initPersistFields()
{
   docsURL;
   Parent::initPersistFields();
}

bool ShaderNode::onAdd()
{
   if (!Parent::onAdd())
      return false;

   return true;
}

void ShaderNode::onRemove()
{
   Parent::onRemove();
}

void ShaderNode::onRender(Point2I offset, const RectI& updateRect)
{
   if (!mProfile)
      return Parent::onRender(offset, updateRect);

   GFXDrawUtil* drawer = GFX->getDrawUtil();

   // Get our rect.
   RectI winRect;
   winRect.point = offset;
   winRect.extent = getExtent();

   // draw background.
   drawer->drawRectFill(winRect, mProfile->mFillColor);

   // draw header text.
   U32 strWidth = mProfile->mFont->getStrWidth(mTitle.c_str());
   Point2I headerPos = Point2I((getExtent().x / 2) - (strWidth / 2), (30 / 2) - (mProfile->mFont->getFontSize() / 2));
   drawer->setBitmapModulation(mProfile->mFontColor);
   drawer->drawText(mProfile->mFont, headerPos + offset, mTitle);
   drawer->clearBitmapModulation();

   ColorI border(128, 128, 128, 128);

   if (mSelected)
      border = ColorI(128, 0, 128, 128);

   winRect.inset(1, 1);
   drawer->drawRect(winRect, border);

}

void ShaderNode::write(Stream& stream, U32 tabStop, U32 flags)
{
}

void ShaderNode::read(Stream& stream)
{
}
