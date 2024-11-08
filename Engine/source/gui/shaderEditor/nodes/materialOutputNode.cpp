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
#include "gui/shaderEditor/nodes/materialOutputNode.h"

//-----------------------------------------------------------------
// BRDF Output Node.
//-----------------------------------------------------------------

IMPLEMENT_CONOBJECT(BRDFOutputNode);

ConsoleDocClass(BRDFOutputNode,
   "@brief Deferred Material output.\n\n"
   "Editor use only.\n\n"
   "@internal"
);

BRDFOutputNode::BRDFOutputNode()
   : GuiShaderNode()
{
   mNodeType = NodeTypes::Output;

   mInputNodes.push_back(new NodeInput("Albedo", DataDimensions::Vector3));
   mInputNodes.push_back(new NodeInput("Normal", DataDimensions::Vector3));
   mInputNodes.push_back(new NodeInput("Ambient Occlusion", DataDimensions::Scalar));
   mInputNodes.push_back(new NodeInput("Metallic", DataDimensions::Scalar));
   mInputNodes.push_back(new NodeInput("Roughness", DataDimensions::Scalar));
   mInputNodes.push_back(new NodeInput("Emissive Color", DataDimensions::Vector3));
   mInputNodes.push_back(new NodeInput("Opacity", DataDimensions::Scalar));

   mTitle = "Standard BRDF";
}
