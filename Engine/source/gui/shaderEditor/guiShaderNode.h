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

#ifndef _SHADERNODE_H_
#define _SHADERNODE_H_

#ifndef _GUICONTROL_H_
#include "gui/core/guiControl.h"
#endif

#ifndef _SIMBASE_H_
#include "console/simBase.h"
#endif

#ifndef _GFX_GFXDRAWER_H_
#include "gfx/gfxDrawUtil.h"
#endif


enum class NodeTypes
{
   Default,
   Uniform,
   Input,
   Output,
   TextureSampler,
   MathOperation,
   Procedural,
   Generator
};

enum class DataDimensions
{
   Dynamic, // can be any dimension, usually defined by what was connected to it.
   Scalar,
   Vector2,
   Vector3,
   Vector4,
   Mat4x4,
};

// parent class for sockets detection in shaderEditor.
struct NodeSocket
{
   String name;
   DataDimensions dimensions;
   ColorI col = ColorI::WHITE;
   NodeSocket()
      :name(String::EmptyString), dimensions(DataDimensions::Dynamic)
   {}
   NodeSocket(String inName, DataDimensions inDim)
      :name(inName), dimensions(inDim)
   {
      switch (inDim)
      {
      case DataDimensions::Dynamic:
         col = ColorI(200, 200, 200, 128);
         break;
      case DataDimensions::Scalar:
         col = ColorI(210, 105, 30, 128);
         break;
      case DataDimensions::Vector2:
         col = ColorI(152, 251,152, 128);
         break;
      case DataDimensions::Vector3:
         col = ColorI(127, 255, 212, 128);
         break;
      case DataDimensions::Vector4:
         col = ColorI(100, 149, 237, 128);
         break;
      case DataDimensions::Mat4x4:
         col = ColorI(153, 50, 204, 128);
         break;
      default:
         break;
      }
   }

public:
   virtual ~NodeSocket() {}
};

struct NodeInput : NodeSocket
{
   Point2I pos = Point2I::Zero;

   NodeInput()
      :NodeSocket()
   {}
   NodeInput(String inName , DataDimensions inDim)
      :NodeSocket(inName , inDim)
   {}
};

struct NodeOutput : NodeSocket
{
   Point2I pos = Point2I::Zero;

   NodeOutput()
      :NodeSocket()
   {}
   NodeOutput(String inName, DataDimensions inDim)
      :NodeSocket(inName, inDim)
   {}
};

class GuiShaderNode : public GuiControl
{
private:
   typedef GuiControl Parent;

protected:
   String mTitle;
   NodeTypes mNodeType;
   S32 mPrevNodeSize;
public:
   Vector<NodeInput*> mInputNodes;
   Vector<NodeOutput*> mOutputNodes;

   GuiShaderNode();

   bool onWake();
   void onSleep();
   static void initPersistFields();
   virtual bool onAdd() override;
   virtual void onRemove() override;

   void renderNode(Point2I offset, const RectI& updateRect, const S32 nodeSize);
   // Serialization functions
   void write(Stream& stream, U32 tabStop = 0, U32 flags = 0);
   void read(Stream& stream);

   // is the parent that all other nodes are derived from.
   DECLARE_CONOBJECT(GuiShaderNode);
   DECLARE_CATEGORY("Shader Core");
   DECLARE_DESCRIPTION("Base class for all shader nodes.");

   bool mSelected;
};
#endif // !_SHADERNODE_H_
