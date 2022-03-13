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
#include "materials/crossShaderData.h"
#include "core/volume.h"
#include "console/consoleTypes.h"
#include "core/strings/stringUnit.h"
#include "console/engineAPI.h"
#include "core/stream/fileStream.h"
#include "core/fileObject.h"

// opengl glsl
#include "CrossShader/glslShaderData.h"

// directx hlsl
#include "CrossShader/hlslShaderData.h"

IMPLEMENT_CONOBJECT(CrossShaderData);

ConsoleDocClass(CrossShaderData,
   "@brief Special type of data block that stores information about a handwritten shader.\n\n"
   "Shader is written with json style in hlsl and output for both apis.\n\n"

   "To use hand written shaders, a ShaderData datablock must be used. This datablock "
   "refers only to the vertex and pixel shader filenames and a hardware target level. "
   "Shaders are API specific, so DirectX and OpenGL shaders must be explicitly identified.\n\n "

   "@ingroup Shaders\n");

CrossShaderData::CrossShaderData()
{
   mCrossShaderFile = StringTable->EmptyString();
   mGLSLShader = new GLSLCrossShader();
   mHLSLShader = new HLSLCrossShader();

}

void CrossShaderData::initPersistFields()
{
   addField("ShaderBlueprint", TypeStringFilename, Offset(mCrossShaderFile, CrossShaderData),
      "@brief %Path to the file to use to generate shaers.\n\n");

   Parent::initPersistFields();
}

bool CrossShaderData::onAdd()
{
   if (!Parent::onAdd())
      return false;

   readBlueprint(mCrossShaderFile);

   return true;
}

void CrossShaderData::onRemove()
{
   Parent::onRemove();
}

void CrossShaderData::readBlueprint(const Torque::Path& filePath)
{
   FileObject file;
   if(!file.readMemory(filePath.getFullPath()))
   {
      Con::errorf("CrossShaderData - couldn't read file %s", filePath.getFullPath().c_str());
      return;
   }

   Con::printf("//-------------------------------");
   Con::printf("Building Cross api Shader - %s", this->getName());

   // process file.
   const char *buffer;
   while (!file.isEOF())
   {
      buffer = (const char*)file.readLine();
      buffer = StripChars(buffer);
      if (!String::compare(buffer, "input {"))
      {
         Con::printf("processing inputs");
         buffer = (const char*)file.readLine();
         buffer = StripChars(buffer);
         while (String::compare(buffer, "}"))
         {
            mGLSLShader->processInput(buffer);
            mHLSLShader->processInput(buffer);
            buffer = (const char*)file.readLine();
            buffer = StripChars(buffer);
         }
      }
      else
      {
         Con::errorf("CrossShaderDat - no input in file %s", filePath.getFullPath().c_str());
         return;
      }

      buffer = (const char*)file.readLine();
      buffer = StripChars(buffer);
      if (!String::compare(buffer, "connect {"))
      {
         Con::printf("processing connections");
         buffer = (const char*)file.readLine();
         buffer = StripChars(buffer);
         while (String::compare(buffer, "}"))
         {
            mGLSLShader->processConnect(buffer);
            mHLSLShader->processConnect(buffer);
            buffer = (const char*)file.readLine();
            buffer = StripChars(buffer);
         }
      }
      else
      {
         Con::errorf("CrossShaderDat - no connect in file %s", filePath.getFullPath().c_str());
         return;
      }

      buffer = (const char*)file.readLine();
      buffer = StripChars(buffer);
      if (!String::compare(buffer, "vertex {"))
      {
         // if not vertex shader out.
         Con::printf("processing vertex");
         while (String::compare(buffer, "}"))
         {
            buffer = (const char*)file.readLine();
            buffer = StripChars(buffer);
            if (!String::compare(buffer, "uniform {"))
            {
               Con::printf("processing vertex uniforms");
               buffer = (const char*)file.readLine();
               buffer = StripChars(buffer);
               // if not uniform out.
               while (String::compare(buffer, "}"))
               {
                  mGLSLShader->processVertUniforms(buffer);
                  mHLSLShader->processVertUniforms(buffer);
                  buffer = (const char*)file.readLine();
                  buffer = StripChars(buffer);
               }
            }
            buffer = (const char*)file.readLine();
            buffer = StripChars(buffer);
            if (!String::compare(buffer, "main {"))
            {
               Con::printf("processing vertex main");
               // if not main out.
               buffer = (const char*)file.readLine();
               buffer = StripChars(buffer);
               while (String::compare(buffer, "}"))
               {
                  mGLSLShader->processVertMainLine(buffer);
                  mHLSLShader->processVertMainLine(buffer);
                  buffer = (const char*)file.readLine();
                  buffer = StripChars(buffer);
               }
            }

            buffer = (const char*)file.readLine();
            buffer = StripChars(buffer);
         }
      }

      buffer = (const char*)file.readLine();
      buffer = StripChars(buffer);
      if (!String::compare(buffer, "pixel {"))
      {
         // if not vertex shader out.
         Con::printf("processing pixel");
         while (String::compare(buffer, "}"))
         {
            buffer = (const char*)file.readLine();
            buffer = StripChars(buffer);
            if (!String::compare(buffer, "uniform {"))
            {
               Con::printf("processing pixel uniforms");
               buffer = (const char*)file.readLine();
               buffer = StripChars(buffer);
               // if not uniform out.
               while (String::compare(buffer, "}"))
               {
                  mGLSLShader->processPixUniforms(buffer);
                  mHLSLShader->processPixUniforms(buffer);
                  buffer = (const char*)file.readLine();
                  buffer = StripChars(buffer);
               }
            }
            buffer = (const char*)file.readLine();
            buffer = StripChars(buffer);
            if (!String::compare(buffer, "output {"))
            {
               Con::printf("processing pixel outputs");
               buffer = (const char*)file.readLine();
               buffer = StripChars(buffer);
               // if not uniform out.
               while (String::compare(buffer, "}"))
               {
                  mGLSLShader->processPixOutputs(buffer);
                  mHLSLShader->processPixOutputs(buffer);
                  buffer = (const char*)file.readLine();
                  buffer = StripChars(buffer);
               }
            }
            buffer = (const char*)file.readLine();
            buffer = StripChars(buffer);
            if (!String::compare(buffer, "main {"))
            {
               Con::printf("processing pixel main");
               // if not main out.
               buffer = (const char*)file.readLine();
               buffer = StripChars(buffer);
               while (String::compare(buffer, "}"))
               {
                  mGLSLShader->processPixelMainLine(buffer);
                  mHLSLShader->processPixelMainLine(buffer);
                  buffer = (const char*)file.readLine();
                  buffer = StripChars(buffer);
               }
            }
            buffer = (const char*)file.readLine();
            buffer = StripChars(buffer);
         }
      }

   }
   Con::printf("Shader blueprint successful!");
   mGLSLShader->generateShader((char*)this->getName());
   mHLSLShader->generateShader((char*)this->getName());
}

char* CrossShaderData::StripChars(const char* buffer)
{
   S32 len = dStrlen(buffer) + 1;

   char* ret = Con::getReturnBuffer(len);
   dStrcpy(ret, buffer, len);
   U32 pos = dStrcspn(ret, ":;\t");
   while (pos < dStrlen(ret))
   {
      dStrcpy(ret + pos, ret + pos + 1, len - pos);
      pos = dStrcspn(ret, ":;\t");
   }

   return ret;
}

