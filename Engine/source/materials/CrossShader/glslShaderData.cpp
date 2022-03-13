#include "glslShaderData.h"
#include "platform/platform.h"
#include "materials/crossShaderData.h"
#include "core/volume.h"
#include "console/consoleTypes.h"
#include "core/strings/stringUnit.h"
#include "console/engineAPI.h"
#include "core/stream/fileStream.h"
#include "core/fileObject.h"

char* GLSLCrossShader::checkType(char* type)
{
   if (!String::compare(type, "float"))
      return type;

   if (!String::compare(type, "float2"))
      return "vec2";

   if (!String::compare(type, "float3"))
      return "vec3";

   if (!String::compare(type, "float4"))
      return "vec4";

   if (!String::compare(type, "float2x2"))
      return "mat2";

   if (!String::compare(type, "float3x3"))
      return "mat3";

   if (!String::compare(type, "float4x3"))
      return "mat4x3";

   if (!String::compare(type, "float4x4"))
      return "mat4";

   if (!String::compare(type, "Texture2D"))
      return "sampler2D";

   return "UKNOWN TYPE";
}

void GLSLCrossShader::checkMainLine(String& line, bool isVert)
{
   // only in vert shader.
   if (isVert)
   {
      if (mUseGLPosition)
      {
         line.replace("OUT.vPosition", "gl_Position");
      }
   }

   line.replace("IN.", "IN_");
   line.replace("OUT.", "OUT_");
   line.replace("float2", "vec2");
   line.replace("float3", "vec3");
   line.replace("float4", "vec4");
   line.replace("float2x2", "mat2");
   line.replace("float3x3", "mat3");
   line.replace("float4x4", "mat4");
   line.replace("float4x3", "mat4x3");
   line.replace("lerp", "mix");

   U32 pos = line.find("mul");
   if (pos)
   {
      mUseMulDef = true;
   }

   if (!isVert)
   {
      for (U32 i = 0; i < mGLSLUniPixList->mUniformPixList.size(); i++)
      {
         GLSLInfo info = mGLSLUniPixList->mUniformPixList[i];
         char* pch = dStrstr(line, info.name);
         if (pch != NULL)
         {
            if (!String::compare(info.type, "sampler2D"))
            {
               String remove(pch);
               remove.erase(0, dStrlen(info.name));
               remove.insert(0, "texture");
               // copy and add null termination.
               dStrncpy(pch, remove.c_str(), (remove.length()))[remove.length()] = '\0';
               break;
            }
         }
      }
   }

}

void GLSLCrossShader::checkName(char* name)
{
   // check names for known vars and set our shader.
   // these are used for the source side output.
   if (!String::compare(name, "model"))
      mUseModelMat = true;

   if (!String::compare(name, "modelView"))
      mUseModelViewMat = true;

   if (!String::compare(name, "modelViewProj"))
      mUseModelViewProjMat = true;

   // this one should probably always be true.
   if (!String::compare(name, "vPosition") || !String::compare(name, "vPos"))
      mUseGLPosition = true;

}

void GLSLCrossShader::generateShader(char* shaderName)
{
   char vertShaderFile[256];
   dSprintf(vertShaderFile, sizeof(vertShaderFile), "%s_V.glsl", shaderName);
   char pixShaderFile[256];
   dSprintf(pixShaderFile, sizeof(pixShaderFile), "%s_P.glsl", shaderName);

   // create the shader file.
   FileStream* s = new FileStream();
   if (!s->open(vertShaderFile, Torque::FS::File::Write))
   {
      AssertFatal(false, "Failed to open Vertex shader stream");
      return;
   }

   _printVertexShader(*s);
   delete s;

   s = new FileStream();
   if (!s->open(pixShaderFile, Torque::FS::File::Write))
   {
      AssertFatal(false, "Failed to open Pixel shader stream");
      return;
   }
   _printPixelShader(*s);
   delete s;

}

//-----------------------------------------------------------
// GLSLCrossShaderInputList
//-----------------------------------------------------------

void GLSLCrossShader::GLSLCrossShaderInputList::addInput(char* type, char* name)
{
   GLSLInfo in;
   char* glType = shader->checkType(type);

   in.type = glType;
   in.name = name;

   mInputList.push_back(in);
}

void GLSLCrossShader::GLSLCrossShaderInputList::print(Stream& stream)
{
   const char* head = "//-------------------------------\r\n";
   const char* head1 = "// GLSL INPUTS\r\n";
   const char* head2 = "//-------------------------------\r\n\r\n";

   stream.write(dStrlen(head), head);
   stream.write(dStrlen(head1), head1);
   stream.write(dStrlen(head2), head2);

   for (U32 i = 0; i < mInputList.size(); i++)
   {
      char output[256];
      GLSLInfo info = mInputList[i];
      dSprintf(output, sizeof(output), "in %s %s;\r\n", info.type, info.name);

      stream.write(dStrlen((char*)output), output);
   }

   // do it again for defines only glsl
   for (U32 i = 0; i < mInputList.size(); i++)
   {
      char output[256];
      GLSLInfo info = mInputList[i];
      dSprintf(output, sizeof(output), "#define IN_%s %s\r\n", info.name, info.name);
      stream.write(dStrlen((char*)output), output);
   }

   // clean new line afterwards.
   const char* newLine = "\r\n";
   stream.write(dStrlen((char*)newLine), newLine);

}

//-----------------------------------------------------------
// GLSLCrossShaderConnList
//-----------------------------------------------------------

void GLSLCrossShader::GLSLCrossShaderConnectList::addConnect(char* type, char* name)
{
   // gl_Position is used in glsl instead no need to write this out.
   if (!String::compare(name, "vPos") || !String::compare(name, "vPosition"))
   {
      // send it to shader to check and set gl_Position to true.
      shader->checkName(name);
      return;
   }

   GLSLInfo in;
   char* glType = shader->checkType(type);

   in.type = glType;
   in.name = name;

   mConnectList.push_back(in);
}

void GLSLCrossShader::GLSLCrossShaderConnectList::print(Stream& stream, bool isVShader)
{
   const char* head = "//-------------------------------\r\n";
   const char* head1 = "// GLSL CONNECTS\r\n";
   const char* head2 = "//-------------------------------\r\n\r\n";

   stream.write(dStrlen(head), head);
   stream.write(dStrlen(head1), head1);
   stream.write(dStrlen(head2), head2);

   if (isVShader)
   {
      for (U32 i = 0; i < mConnectList.size(); i++)
      {
         char output[256];
         GLSLInfo info = mConnectList[i];
         dSprintf(output, sizeof(output), "out %s %s;\r\n", info.type, info.name);

         stream.write(dStrlen((char*)output), output);
      }

      // do it again for defines only glsl
      for (U32 i = 0; i < mConnectList.size(); i++ )
      {
         char output[256];
         GLSLInfo info = mConnectList[i];
         dSprintf(output, sizeof(output), "#define OUT_%s %s\r\n", info.name, info.name);
         stream.write(dStrlen((char*)output), output);
      }
   }
   else
   {
      for (U32 i = 0; i < mConnectList.size(); i++)
      {
         char output[256];
         GLSLInfo info = mConnectList[i];
         dSprintf(output, sizeof(output), "in %s %s;\r\n", info.type, info.name);

         stream.write(dStrlen((char*)output), output);
      }

      // do it again for defines only glsl
      for (U32 i = 0; i < mConnectList.size(); i++)
      {
         char output[256];
         GLSLInfo info = mConnectList[i];
         dSprintf(output, sizeof(output), "#define IN_%s %s\r\n", info.name, info.name);
         stream.write(dStrlen((char*)output), output);
      }
   }

   // clean new line afterwards.
   const char* newLine = "\r\n";
   stream.write(dStrlen((char*)newLine), newLine);
}

//-----------------------------------------------------------
// GLSLCrossShaderUniformVertList
//-----------------------------------------------------------

void GLSLCrossShader::GLSLCrossShaderUniformVertList::addVertUniform(char* type, char* name)
{
   GLSLInfo in;
   char* glType = shader->checkType(type);
   shader->checkName(name);

   in.type = glType;
   in.name = name;
   Con::printf("uniform %s %s", in.type, in.name);

   mUniformVertList.push_back(in);
}

void GLSLCrossShader::GLSLCrossShaderUniformVertList::print(Stream& stream)
{
   const char* head = "//-------------------------------\r\n";
   const char* head1 = "// GLSL VERTEX UNIFORMS\r\n";
   const char* head2 = "//-------------------------------\r\n\r\n";

   stream.write(dStrlen(head), head);
   stream.write(dStrlen(head1), head1);
   stream.write(dStrlen(head2), head2);

   for (U32 i = 0; i < mUniformVertList.size(); i++)
   {
      char output[256];
      GLSLInfo info = mUniformVertList[i];
      dSprintf(output, sizeof(output), "uniform %s %s;\r\n", info.type, info.name);

      stream.write(dStrlen((char*)output), output);
   }
   // clean new line afterwards.
   const char* newLine = "\r\n";
   stream.write(dStrlen((char*)newLine), newLine);
}

//-----------------------------------------------------------
// GLSLCrossShaderUniformPixList
//-----------------------------------------------------------

void GLSLCrossShader::GLSLCrossShaderUniformPixList::addPixUniform(char* type, char* name)
{
   GLSLInfo in;
   char* glType = shader->checkType(type);
   shader->checkName(name);

   in.type = glType;
   in.name = name;

   mUniformPixList.push_back(in);
}

void GLSLCrossShader::GLSLCrossShaderUniformPixList::print(Stream& stream)
{
   const char* head = "//-------------------------------\r\n";
   const char* head1 = "// GLSL PIXEL UNIFORMS\r\n";
   const char* head2 = "//-------------------------------\r\n\r\n";

   stream.write(dStrlen(head), head);
   stream.write(dStrlen(head1), head1);
   stream.write(dStrlen(head2), head2);

   for (U32 i = 0; i < mUniformPixList.size(); i++)
   {
      char output[256];
      GLSLInfo info = mUniformPixList[i];
      dSprintf(output, sizeof(output), "uniform %s %s;\r\n", info.type, info.name);

      stream.write(dStrlen((char*)output), output);
   }
   // clean new line afterwards.
   const char* newLine = "\r\n";
   stream.write(dStrlen((char*)newLine), newLine);
}

//-----------------------------------------------------------
// GLSLCrossShaderPixOutputs
//-----------------------------------------------------------

void GLSLCrossShader::GLSLCrossShaderPixOutputs::addPixOutput(char* type, char* name)
{
   GLSLInfo in;
   char* glType = shader->checkType(type);

   in.type = glType;
   in.name = name;

   mPixOutputList.push_back(in);
}

void GLSLCrossShader::GLSLCrossShaderPixOutputs::print(Stream& stream)
{
   const char* head = "//-------------------------------\r\n";
   const char* head1 = "// GLSL PIXEL OUTPUTS\r\n";
   const char* head2 = "//-------------------------------\r\n\r\n";

   stream.write(dStrlen(head), head);
   stream.write(dStrlen(head1), head1);
   stream.write(dStrlen(head2), head2);

   for (U32 i = 0; i < mPixOutputList.size(); i++)
   {
      char output[256];
      GLSLInfo info = mPixOutputList[i];
      dSprintf(output, sizeof(output), "out %s OUT_%s;\r\n", info.type, info.name);

      stream.write(dStrlen((char*)output), output);
   }
   // clean new line afterwards.
   const char* newLine = "\r\n";
   stream.write(dStrlen((char*)newLine), newLine);
}


//-----------------------------------------------------------
// GLSLCrossShaderVertMain
//-----------------------------------------------------------

void GLSLCrossShader::GLSLCrossShaderVertMain::addLine(String line)
{
   // already sorted by glslShader just push it back.
   mLines.push_back(line);
}

void GLSLCrossShader::GLSLCrossShaderVertMain::print(Stream& stream, bool useGlPos)
{
   const char* head = "//-------------------------------\r\n";
   const char* head1 = "// GLSL VERTEX MAIN\r\n";
   const char* head2 = "//-------------------------------\r\n\r\n";
   const char* mainEntry = "void main() {\r\n";
   const char* glFix = "\tgl_Position.y *= -1;\r\n";
   const char* closer = "}\r\n";

   stream.write(dStrlen(head), head);
   stream.write(dStrlen(head1), head1);
   stream.write(dStrlen(head2), head2);
   stream.write(dStrlen(mainEntry), mainEntry);

   for (U32 i = 0; i < mLines.size(); i++)
   {
      char output[512];
      String info = mLines[i];
      dSprintf(output, sizeof(output), "\t%s;\r\n", info.c_str());

      stream.write(dStrlen((char*)output), output);
   }
   if(useGlPos)
      stream.write(dStrlen((char*)glFix), glFix);

   stream.write(dStrlen((char*)closer), closer);

}

//-----------------------------------------------------------
// GLSLCrossShaderPixMain
//-----------------------------------------------------------

void GLSLCrossShader::GLSLCrossShaderPixMain::addLine(String line)
{
   // already sorted by glslShader just push it back.
   mLines.push_back(line);
}

void GLSLCrossShader::GLSLCrossShaderPixMain::print(Stream& stream)
{
   const char* head = "//-------------------------------\r\n";
   const char* head1 = "// GLSL PIXEL MAIN\r\n";
   const char* head2 = "//-------------------------------\r\n\r\n";
   const char* mainEntry = "void main() {\r\n";
   const char* closer = "}\r\n";

   stream.write(dStrlen(head), head);
   stream.write(dStrlen(head1), head1);
   stream.write(dStrlen(head2), head2);
   stream.write(dStrlen(mainEntry), mainEntry);

   for (U32 i = 0; i < mLines.size(); i++)
   {
      char output[512];
      String info = mLines[i];
      dSprintf(output, sizeof(output), "\t%s;\r\n", info.c_str());

      stream.write(dStrlen((char*)output), output);
   }

   stream.write(dStrlen((char*)closer), closer);
}

//-----------------------------------------------------------
// GLSLCrossShader functions.
//-----------------------------------------------------------

GLSLCrossShader::GLSLCrossShader()
{
   // shader blueprint holders.
   mGLSLInList = new GLSLCrossShaderInputList(this);
   mGLSLConnList = new GLSLCrossShaderConnectList(this);
   mGLSLUniVertList = new GLSLCrossShaderUniformVertList(this);
   mGLSLUniPixList = new GLSLCrossShaderUniformPixList(this);
   mGLSLPixOut = new GLSLCrossShaderPixOutputs(this);
   mGLSLVertMain = new GLSLCrossShaderVertMain(this);
   mGLSLPixMain = new GLSLCrossShaderPixMain(this);

   mUseMulDef = false;
   mUseGLPosition = false;
   // matrix inputs model
   mUseModelMat = false;
   mUseModelViewMat = false;
   mUseModelViewProjMat = false;
   // matrix inputs view
   mUseViewMat = false;
   mUseViewProjMat = false;
   // matrix inputs proj
   mUseProjMat = false;
   // time
   mUseTime = false;

}

//------------------------------------------------------------
// PROCESSORS FOR SHADER BLUEPRINT FILE
//------------------------------------------------------------

void GLSLCrossShader::processInput(const char* inputBuff)
{
   char* type = Con::getReturnBuffer(StringUnit::getUnit(inputBuff, 0, " \t\n"));
   char* name = Con::getReturnBuffer(StringUnit::getUnit(inputBuff, 1, " \t\n"));

   mGLSLInList->addInput(type, name);

}

void GLSLCrossShader::processConnect(const char* connBuff)
{
   char* type = Con::getReturnBuffer(StringUnit::getUnit(connBuff, 0, " \t\n"));
   char* name = Con::getReturnBuffer(StringUnit::getUnit(connBuff, 1, " \t\n"));

   mGLSLConnList->addConnect(type, name);
}

void GLSLCrossShader::processVertUniforms(const char* vertUni)
{
   char* type = Con::getReturnBuffer(StringUnit::getUnit(vertUni, 0, " \t\n"));
   char* name = Con::getReturnBuffer(StringUnit::getUnit(vertUni, 1, " \t\n"));

   mGLSLUniVertList->addVertUniform(type, name);
}

void GLSLCrossShader::processPixUniforms(const char* pixUni)
{
   char* type = Con::getReturnBuffer(StringUnit::getUnit(pixUni, 0, " \t\n"));
   char* name = Con::getReturnBuffer(StringUnit::getUnit(pixUni, 1, " \t\n"));

   mGLSLUniPixList->addPixUniform(type, name);
}

void GLSLCrossShader::processPixOutputs(const char* pixOut)
{
   char* type = Con::getReturnBuffer(StringUnit::getUnit(pixOut, 0, " \t\n"));
   char* name = Con::getReturnBuffer(StringUnit::getUnit(pixOut, 1, " \t\n"));

   mGLSLPixOut->addPixOutput(type, name);
}

void GLSLCrossShader::processVertMainLine(const char* vLine)
{
   String newLine = vLine;
   
   checkMainLine(newLine, true);

   mGLSLVertMain->addLine(newLine);
}

void GLSLCrossShader::processPixelMainLine(const char* pLine)
{
   String newLine = pLine;

   checkMainLine(newLine, false);

   mGLSLPixMain->addLine(newLine);
}

void GLSLCrossShader::_printVertexShader(Stream& stream)
{
   const char* head = "//------------------------------------------\r\n";
   const char* head1 = "// GLSL VERTEX SHADER FROM CROSS API (0.3b)\r\n";
   const char* head2 = "//-----------------------------------------\r\n\r\n";

   stream.write(dStrlen(head), head);
   stream.write(dStrlen(head1), head1);
   stream.write(dStrlen(head2), head2);
   if (mUseMulDef)
   {
      const char* mulDef = "#define mul(a, b) (a*b)\r\n";
      stream.write(dStrlen(mulDef), mulDef);
   }

   mGLSLInList->print(stream);
   mGLSLConnList->print(stream, true);
   mGLSLUniVertList->print(stream);
   mGLSLVertMain->print(stream, mUseGLPosition);

}

void GLSLCrossShader::_printPixelShader(Stream& stream)
{
   const char* head = "//------------------------------------------\r\n";
   const char* head1 = "// GLSL PIXEL SHADER FROM CROSS API (0.3b)\r\n";
   const char* head2 = "//-----------------------------------------\r\n\r\n";

   stream.write(dStrlen(head), head);
   stream.write(dStrlen(head1), head1);
   stream.write(dStrlen(head2), head2);
   if (mUseMulDef)
   {
      const char* mulDef = "#define mul(a, b) (a*b)\r\n";
      stream.write(dStrlen(mulDef), mulDef);
   }

   mGLSLConnList->print(stream, false);
   mGLSLUniPixList->print(stream);
   mGLSLPixOut->print(stream);
   mGLSLPixMain->print(stream);

}

