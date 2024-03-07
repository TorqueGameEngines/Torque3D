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
#include "gui/shaderEditor/guiShaderNode.h"

#include "gui/core/guiCanvas.h"

IMPLEMENT_CONOBJECT(GuiShaderNode);

ConsoleDocClass(GuiShaderNode,
   "@brief Base class for all nodes to derive from.\n\n"
   "Editor use only.\n\n"
   "@internal"
);


GuiShaderNode::GuiShaderNode()
{
   VECTOR_SET_ASSOCIATION(mInputNodes);
   VECTOR_SET_ASSOCIATION(mOutputNodes);

   mTitle = "Default Node";
   mSelected = false;
   mNodeType = NodeTypes::Default;


   GuiControlProfile* profile = NULL;
   if (Sim::findObject("GuiShaderEditorProfile", profile))
      setControlProfile(profile);

   // fixed extent for all nodes, only height should be changed
   setExtent(180, 35);

   mPrevNodeSize = -1;
}

bool GuiShaderNode::onWake()
{
   if (!Parent::onWake())
      return false;

   return true;
}

void GuiShaderNode::onSleep()
{
   Parent::onSleep();
}

void GuiShaderNode::initPersistFields()
{
   docsURL;
   Parent::initPersistFields();
}

bool GuiShaderNode::onAdd()
{
   if (!Parent::onAdd())
      return false;

   return true;
}

void GuiShaderNode::onRemove()
{
   Parent::onRemove();
}

void GuiShaderNode::renderNode(Point2I offset, const RectI& updateRect, const S32 nodeSize)
{
   if (!mProfile)
      return Parent::onRender(offset, updateRect);

   GFXDrawUtil* drawer = GFX->getDrawUtil();

   // draw background.
   // Get our rect.
   RectI winRect;
   winRect.point = offset;
   winRect.extent = getExtent();

   ColorI border = mProfile->mBorderColor;

   if (mSelected)
      border = mProfile->mBorderColorSEL;

   drawer->drawRoundedRect(15.0f, winRect, mProfile->mFillColor, 5.0f, border);

   // draw header
   ColorI header(50, 50, 50, 128);

   switch (mNodeType)
   {
   case NodeTypes::Default:
      header = ColorI(128, 50, 128, 128);
      break;
   case NodeTypes::Uniform:
      header = ColorI(50, 100, 128, 128);
      break;
   case NodeTypes::Input:
      header = ColorI(128, 100, 50, 128);
      break;
   case NodeTypes::Output:
      header = ColorI(50, 100, 50, 128);
      break;
   case NodeTypes::TextureSampler:
      header = ColorI(50, 50, 128, 128);
      break;
   case NodeTypes::MathOperation:
      header = ColorI(128, 0, 128, 128);
      break;
   case NodeTypes::Procedural:
      header = ColorI(128, 100, 0, 128);
      break;
   case NodeTypes::Generator:
      header = ColorI(0, 100, 128, 128);
      break;
   default:
      header = ColorI(128, 0, 0, 128);
      break;
   }

   RectI headRect;
   U32 headerSize = 30;
   headRect.point = offset;
   headRect.extent = Point2I(getExtent().x, headerSize);
   drawer->drawRoundedRect(15.0f, headRect, header);

   // draw header text.
   U32 strWidth = mProfile->mFont->getStrWidth(mTitle.c_str());
   Point2I headerPos = Point2I((getExtent().x / 2) - (strWidth / 2), (headerSize / 2) - (mProfile->mFont->getFontSize() / 2));
   drawer->setBitmapModulation(mProfile->mFontColor);
   drawer->drawText(mProfile->mFont, headerPos + offset, mTitle);
   drawer->clearBitmapModulation();

   if (mInputNodes.size() > 0 || mOutputNodes.size() > 0)
   {
      U32 textPadX = nodeSize, textPadY = mProfile->mFont->getFontSize() + (nodeSize / 2);
      Point2I slotPos(textPadX, headerSize + (nodeSize / 2));
      drawer->setBitmapModulation(mProfile->mFontColor);
      for (NodeInput* input : mInputNodes)
      {
         drawer->drawText(mProfile->mFont, slotPos + offset, input->name);

         if (input->pos == Point2I::Zero || mPrevNodeSize != nodeSize)
            input->pos = Point2I(-(nodeSize / 2) + 1, slotPos.y + ((mProfile->mFont->getFontSize() / 2) - (nodeSize / 2)));

         slotPos.y += textPadY;
      }

      U32 inputY = slotPos.y;

      slotPos = Point2I(getExtent().x, headerSize + (nodeSize / 2));
      for (NodeOutput* output : mOutputNodes)
      {
         strWidth = mProfile->mFont->getStrWidth(output->name.c_str());
         slotPos.x = getExtent().x - strWidth - textPadX;

         drawer->drawText(mProfile->mFont, slotPos + offset, output->name);

         if (output->pos == Point2I::Zero || mPrevNodeSize != nodeSize)
            output->pos = Point2I(getExtent().x - (nodeSize / 2) - 1 , slotPos.y + ((mProfile->mFont->getFontSize() / 2) - (nodeSize / 2)));

         slotPos.y += textPadY;
      }
      drawer->clearBitmapModulation();

      U32 outputY = slotPos.y;

      if (getExtent().y < slotPos.y || mPrevNodeSize != nodeSize)
         setExtent(Point2I(getExtent().x, mMax(inputY, outputY)));

      mPrevNodeSize = nodeSize;
   }
}

void GuiShaderNode::write(Stream& stream, U32 tabStop, U32 flags)
{
}

void GuiShaderNode::read(Stream& stream)
{
}
