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

#ifndef _SIMBASE_H_
#include "console/simBase.h"
#endif

enum class NodeTypes
{
   Uniform,
   Input,
   Output,
   TextureSampler,
   MathOperation,
   Procedural
};

enum class DataDimensions
{
   Scalar,
   Vector2,
   Vector3,
   Vector4,
   Mat4x4,
};

struct NodeInput
{
   String name;
   DataDimensions dimensions;
};

struct NodeOutput
{
   String name;
   DataDimensions dimensions;
};

class ShaderNode : public GuiControl
{
private:
   typedef GuiControl Parent;

public:
   ShaderNode();

   bool onWake();
   void onSleep();
   static void initPersistFields();
   virtual bool onAdd() override;
   virtual void onRemove() override;

   // Serialization functions
   void write(Stream& stream, U32 tabStop = 0, U32 flags = 0);
   void read(Stream& stream);

   // is the parent that all other nodes are derived from.
   DECLARE_CONOBJECT(ShaderNode);
   DECLARE_CATEGORY("Shader Core");
   DECLARE_DESCRIPTION("Base class for all shader nodes.");
};
#endif // !_SHADERNODE_H_
