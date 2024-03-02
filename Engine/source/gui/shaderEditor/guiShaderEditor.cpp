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
{
}

bool GuiShaderEditor::onWake()
{
   return false;
}

void GuiShaderEditor::onSleep()
{
}

void GuiShaderEditor::initPersistFields()
{
}

bool GuiShaderEditor::onAdd()
{
   return false;
}

void GuiShaderEditor::onRemove()
{
}

void GuiShaderEditor::onPreRender()
{
}

void GuiShaderEditor::onRender(Point2I offset, const RectI& updateRect)
{
}

bool GuiShaderEditor::onKeyDown(const GuiEvent& event)
{
   return false;
}

void GuiShaderEditor::onMouseDown(const GuiEvent& event)
{
}

void GuiShaderEditor::onMouseUp(const GuiEvent& event)
{
}

void GuiShaderEditor::onMouseMove(const GuiEvent& event)
{
}

void GuiShaderEditor::onMiddleMouseDown(const GuiEvent& event)
{
}

bool GuiShaderEditor::onMouseWheelUp(const GuiEvent& event)
{
   return false;
}

bool GuiShaderEditor::onMouseWheelDown(const GuiEvent& event)
{
   return false;
}
