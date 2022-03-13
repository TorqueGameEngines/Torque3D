#include "hlslShaderData.h"
#include "platform/platform.h"
#include "materials/crossShaderData.h"
#include "core/volume.h"
#include "console/consoleTypes.h"
#include "core/strings/stringUnit.h"
#include "console/engineAPI.h"
#include "core/stream/fileStream.h"
#include "core/fileObject.h"

void HLSLCrossShader::checkMainLine(String& line, bool isVert)
{
   if (!isVert)
   {
      for (U32 i = 0; i < mHLSLUniPixList->mUniformPixList.size(); i++)
      {
         HLSLInfo info = mHLSLUniPixList->mUniformPixList[i];
         char* pch = dStrstr(line, info.name);
         if (pch != NULL)
         {
            if (!String::compare(info.type, "Texture2D"))
            {
               String remove(pch);
               remove.erase(0, dStrlen(info.name));
               char out[256];
               dSprintf(out, sizeof(out), "%sTex.Sample", info.name);
               remove.insert(0, out);
               // copy and add null termination.
               dStrncpy(pch, remove.c_str(), (remove.length()))[remove.length()] = '\0';
               break;
            }
         }
      }
   }
}

void HLSLCrossShader::generateShader(char* shaderName)
{
   char vertShaderFile[256];
   dSprintf(vertShaderFile, sizeof(vertShaderFile), "%s_V.hlsl", shaderName);
   char pixShaderFile[256];
   dSprintf(pixShaderFile, sizeof(pixShaderFile), "%s_P.hlsl", shaderName);

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
// HLSLCrossShaderInputList
//-----------------------------------------------------------

void HLSLCrossShader::HLSLCrossShaderInputList::addInput(char* type, char* name, char* target)
{
   HLSLInfo in;
   in.type = type;
   in.name = name;
   in.target = target;

   mInputList.push_back(in);
}

void HLSLCrossShader::HLSLCrossShaderInputList::print(Stream& stream)
{
   const char* head = "//-------------------------------\r\n";
   const char* head1 = "// GLSL INPUTS\r\n";
   const char* head2 = "//-------------------------------\r\n\r\n";

   stream.write(dStrlen(head), head);
   stream.write(dStrlen(head1), head1);
   stream.write(dStrlen(head2), head2);

   const char* structName = "struct VertData\r\n";
   const char* open = "{\r\n";
   const char* closer = "}\r\n";

   stream.write(dStrlen(structName), structName);
   stream.write(dStrlen(open), open);

   for (U32 i = 0; i < mInputList.size(); i++)
   {
      char output[256];
      HLSLInfo info = mInputList[i];
      dSprintf(output, sizeof(output), "\t%s %s \t\t: %s;\r\n", info.type, info.name, info.target);
      stream.write(dStrlen((char*)output), output);
   }

   stream.write(dStrlen(closer), closer);
   // clean new line afterwards.
   const char* newLine = "\r\n";
   stream.write(dStrlen((char*)newLine), newLine);

}

//-----------------------------------------------------------
// HLSLCrossShaderConnList
//-----------------------------------------------------------

void HLSLCrossShader::HLSLCrossShaderConnectList::addConnect(char* type, char* name, char* target)
{
   HLSLInfo in;
   in.type = type;
   in.name = name;
   in.target = target;

   mConnectList.push_back(in);
}

void HLSLCrossShader::HLSLCrossShaderConnectList::print(Stream& stream)
{
   // in hlsl this is the same in both vert and pixel.
   const char* head = "//-------------------------------\r\n";
   const char* head1 = "// HLSL CONNECTS\r\n";
   const char* head2 = "//-------------------------------\r\n\r\n";

   stream.write(dStrlen(head), head);
   stream.write(dStrlen(head1), head1);
   stream.write(dStrlen(head2), head2);

   const char* structName = "struct ConnectData\r\n";
   const char* open = "{\r\n";
   const char* closer = "}\r\n";

   stream.write(dStrlen(structName), structName);
   stream.write(dStrlen(open), open);

   for (U32 i = 0; i < mConnectList.size(); i++)
   {
      char output[256];
      HLSLInfo info = mConnectList[i];
      dSprintf(output, sizeof(output), "\t%s %s \t\t: %s;\r\n", info.type, info.name, info.target);
      stream.write(dStrlen((char*)output), output);
   }

   stream.write(dStrlen(closer), closer);
   // clean new line afterwards.
   const char* newLine = "\r\n";
   stream.write(dStrlen((char*)newLine), newLine);

}

//-----------------------------------------------------------
// HLSLCrossShaderUniformVertList
//-----------------------------------------------------------

void HLSLCrossShader::HLSLCrossShaderUniformVertList::addVertUniform(char* type, char* name)
{
   HLSLInfo in;
   in.type = type;
   in.name = name;
   //check uniform for register number.
   checkUniform(in);

   mUniformVertList.push_back(in);
}

void HLSLCrossShader::HLSLCrossShaderUniformVertList::checkUniform(HLSLInfo& in)
{
   char buff[3];
   if (!String::compare(in.type, "float"))
   {
      dSprintf(buff, sizeof(buff), "C%d", cReg);
      in.regNum = buff;
      cReg++;
      return;
   }

   if (!String::compare(in.type, "float2"))
   {
      dSprintf(buff, sizeof(buff), "C%d", cReg);
      in.regNum = buff;
      cReg++;
      return;
   }

   if (!String::compare(in.type, "float3"))
   {
      dSprintf(buff, sizeof(buff), "C%d", cReg);
      in.regNum = buff;
      cReg++;
      return;
   }

   if (!String::compare(in.type, "float4"))
   {
      dSprintf(buff, sizeof(buff), "C%d", cReg);
      in.regNum = buff;
      cReg++;
      return;
   }

   if (!String::compare(in.type, "float2x2"))
   {
      dSprintf(buff, sizeof(buff), "C%d", cReg);
      in.regNum = buff;
      cReg += 2;
      return;
   }

   if (!String::compare(in.type, "float3x3"))
   {
      dSprintf(buff, sizeof(buff), "C%d", cReg);
      in.regNum = buff;
      cReg += 3;
      return;
   }

   if (!String::compare(in.type, "float4x3"))
   {
      dSprintf(buff, sizeof(buff), "C%d", cReg);
      in.regNum = buff;
      cReg += 3;
      return;
   }

   if (!String::compare(in.type, "float4x4"))
   {
      dSprintf(buff, sizeof(buff), "C%d", cReg);
      in.regNum = buff;
      cReg += 4;
      return;
   }

   if (!String::compare(in.type, "SamplerState"))
   {
      dSprintf(buff, sizeof(buff), "S%d", sReg);
      in.regNum = buff;
      sReg++;
      return;
   }

   if (!String::compare(in.type, "Texture2D"))
   {
      char* sampName = in.name;
      addVertUniform("SamplerState", sampName);
      dSprintf(buff, sizeof(buff), "T%d", tReg);
      in.regNum = buff;
      tReg++;
      return;
   }

}

void HLSLCrossShader::HLSLCrossShaderUniformVertList::print(Stream& stream)
{
   // uniforms printed in main block, no header please.

   for (U32 i = 0; i < mUniformVertList.size(); i++)
   {
      char output[512];
      HLSLInfo info = mUniformVertList[i];
      if (!String::compare(info.type, "Texture2D"))
      {
         info.name = dStrncat(info.name, "Tex", dStrlen(info.name));
      }

      if(i == mUniformVertList.size()-1)
      {
         dSprintf(
            output,
            sizeof(output),
            "\t\t\tuniform %s\t\t%s\t\t: register(%s)\r\n",
            info.type,
            info.name,
            info.regNum.c_str());
      }
      else
      {
         dSprintf(
            output,
            sizeof(output),
            "\t\t\tuniform %s\t\t%s\t\t: register(%s),\r\n",
            info.type,
            info.name,
            info.regNum.c_str());
      }
      stream.write(dStrlen((char*)output), output);
   }
   const char* closeIn = ")\r\n{\r\n";
   stream.write(dStrlen((char*)closeIn), closeIn);
}

//-----------------------------------------------------------
// HLSLCrossShaderUniformPixList
//-----------------------------------------------------------

void HLSLCrossShader::HLSLCrossShaderUniformPixList::addPixUniform(char* type, char* name)
{
   HLSLInfo in;
   in.type = type;
   in.name = name;
   in.target = "";
   //check uniform for register number.
   checkUniform(in);

   mUniformPixList.push_back(in);
}

void HLSLCrossShader::HLSLCrossShaderUniformPixList::checkUniform(HLSLInfo& in)
{
   char buff[4];
   if (!String::compare(in.type, "float"))
   {
      dSprintf(buff, sizeof(buff), "C%d", cReg);
      in.regNum = buff;
      cReg++;
      return;
   }

   if (!String::compare(in.type, "float2"))
   {
      dSprintf(buff, sizeof(buff), "C%d", cReg);
      in.regNum = buff;
      cReg++;
      return;
   }

   if (!String::compare(in.type, "float3"))
   {
      dSprintf(buff, sizeof(buff), "C%d", cReg);
      in.regNum = buff;
      cReg++;
      return;
   }

   if (!String::compare(in.type, "float4"))
   {
      dSprintf(buff, sizeof(buff), "C%d", cReg);
      in.regNum = buff;
      cReg++;
      return;
   }

   if (!String::compare(in.type, "float2x2"))
   {
      dSprintf(buff, sizeof(buff), "C%d", cReg);
      in.regNum = buff;
      cReg += 2;
      return;
   }

   if (!String::compare(in.type, "float3x3"))
   {
      dSprintf(buff, sizeof(buff), "C%d", cReg);
      in.regNum = buff;
      cReg += 3;
      return;
   }

   if (!String::compare(in.type, "float4x3"))
   {
      dSprintf(buff, sizeof(buff), "C%d", cReg);
      in.regNum = buff;
      cReg += 3;
      return;
   }

   if (!String::compare(in.type, "float4x4"))
   {
      dSprintf(buff, sizeof(buff), "C%d", cReg);
      in.regNum = buff;
      cReg += 4;
      return;
   }

   if (!String::compare(in.type, "SamplerState"))
   {
      dSprintf(buff, sizeof(buff), "S%d", sReg);
      in.regNum = buff;
      sReg++;
      return;
   }

   if (!String::compare(in.type, "Texture2D"))
   {
      // if texture we need sampler.
      addPixUniform("SamplerState",in.name);
      // now finish off the texture.
      dSprintf(buff, sizeof(buff), "T%d", tReg);
      in.regNum = buff;
      tReg++;
      
      return;
   }
}

void HLSLCrossShader::HLSLCrossShaderUniformPixList::print(Stream& stream)
{
   // uniforms printed in main block, no header please.
   for (U32 i = 0; i < mUniformPixList.size(); i++)
   {
      HLSLInfo info = mUniformPixList[i];
      if (!String::compare(info.type, "Texture2D"))
      {
         info.name = dStrncat(info.name, "Tex", dStrlen(info.name));
      }

      char output[512];
      if (i == mUniformPixList.size() - 1)
      {
         dSprintf(
            output,
            sizeof(output),
            "\t\t\tuniform %s\t\t%s\t\t: register(%s)\r\n",
            info.type,
            info.name,
            info.regNum.c_str());
      }
      else
      {
         dSprintf(
            output,
            sizeof(output),
            "\t\t\tuniform %s \t\t%s\t\t: register(%s),\r\n",
            info.type,
            info.name,
            info.regNum.c_str());
      }

      stream.write(dStrlen((char*)output), output);
   }
   const char* closeIn = ")\r\n{\r\n";
   stream.write(dStrlen((char*)closeIn), closeIn);
}

//-----------------------------------------------------------
// HLSLCrossShaderPixOutputs
//-----------------------------------------------------------

void HLSLCrossShader::HLSLCrossShaderPixOutputs::addPixOutput(char* type, char* name, char* target)
{
   HLSLInfo in;
   in.type = type;
   in.name = name;
   in.target = target;

   mPixOutputList.push_back(in);
}

void HLSLCrossShader::HLSLCrossShaderPixOutputs::print(Stream& stream)
{
   // in hlsl this is the same in both vert and pixel.
   const char* head = "//-------------------------------\r\n";
   const char* head1 = "// HLSL PIXEL OUTPUTS\r\n";
   const char* head2 = "//-------------------------------\r\n\r\n";

   stream.write(dStrlen(head), head);
   stream.write(dStrlen(head1), head1);
   stream.write(dStrlen(head2), head2);

   const char* structName = "struct PixelOut\r\n";
   const char* open = "{\r\n";
   const char* closer = "}\r\n";

   stream.write(dStrlen(structName), structName);
   stream.write(dStrlen(open), open);

   for (U32 i = 0; i < mPixOutputList.size(); i++)
   {
      char output[256];
      HLSLInfo info = mPixOutputList[i];
      dSprintf(output, sizeof(output), "\t%s %s \t\t: %s;\r\n", info.type, info.name, info.target);
      stream.write(dStrlen((char*)output), output);
   }

   stream.write(dStrlen(closer), closer);
   // clean new line afterwards.
   const char* newLine = "\r\n";
   stream.write(dStrlen((char*)newLine), newLine);

}

//-----------------------------------------------------------
// HLSLCrossShaderVertMain
//-----------------------------------------------------------

void HLSLCrossShader::HLSLCrossShaderVertMain::addLine(String line)
{
   // already sorted by glslShader just push it back.
   mLines.push_back(line);
}

void HLSLCrossShader::HLSLCrossShaderVertMain::printHeader(Stream& stream)
{
   const char* head = "//-------------------------------\r\n";
   const char* head1 = "// HLSL VERTEX MAIN\r\n";
   const char* head2 = "//-------------------------------\r\n\r\n";
   const char* mainEntry = "ConnectData main( VertData IN,\r\n";

   stream.write(dStrlen(head), head);
   stream.write(dStrlen(head1), head1);
   stream.write(dStrlen(head2), head2);
   stream.write(dStrlen(mainEntry), mainEntry);

}

void HLSLCrossShader::HLSLCrossShaderVertMain::print(Stream& stream)
{
   const char* closer = "}\r\n";
   const char* outBind = "ConnectData OUT;\r\n";
   stream.write(dStrlen((char*)outBind), outBind);

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
// HLSLCrossShaderPixMain
//-----------------------------------------------------------

void HLSLCrossShader::HLSLCrossShaderPixMain::addLine(String line)
{
   // already sorted by glslShader just push it back.
   mLines.push_back(line);
}

void HLSLCrossShader::HLSLCrossShaderPixMain::printHeader(Stream& stream)
{
   const char* head = "//-------------------------------\r\n";
   const char* head1 = "// HLSL PIXEL MAIN\r\n";
   const char* head2 = "//-------------------------------\r\n\r\n";
   const char* mainEntry = "PixelOut main( ConnectData IN,\r\n";

   stream.write(dStrlen(head), head);
   stream.write(dStrlen(head1), head1);
   stream.write(dStrlen(head2), head2);
   stream.write(dStrlen(mainEntry), mainEntry);

}

void HLSLCrossShader::HLSLCrossShaderPixMain::print(Stream& stream)
{
   const char* closer = "}\r\n";
   const char* outBind = "\tPixelOut OUT;\r\n";
   stream.write(dStrlen((char*)outBind), outBind);

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
// HLSLCrossShader functions.
//-----------------------------------------------------------

HLSLCrossShader::HLSLCrossShader()
{
   // shader blueprint holders.
   mHLSLInList = new HLSLCrossShaderInputList(this);
   mHLSLConnList = new HLSLCrossShaderConnectList(this);
   mHLSLUniVertList = new HLSLCrossShaderUniformVertList(this);
   mHLSLUniPixList = new HLSLCrossShaderUniformPixList(this);
   mHLSLPixOut = new HLSLCrossShaderPixOutputs(this);
   mHLSLVertMain = new HLSLCrossShaderVertMain(this);
   mHLSLPixMain = new HLSLCrossShaderPixMain(this);

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

void HLSLCrossShader::processInput(const char* inputBuff)
{
   char* type = Con::getReturnBuffer(StringUnit::getUnit(inputBuff, 0, " \t\n"));
   char* name = Con::getReturnBuffer(StringUnit::getUnit(inputBuff, 1, " \t\n"));
   char* target = Con::getReturnBuffer(StringUnit::getUnit(inputBuff, 2, " \t\n"));

   mHLSLInList->addInput(type, name, target);

}

void HLSLCrossShader::processConnect(const char* connBuff)
{
   char* type = Con::getReturnBuffer(StringUnit::getUnit(connBuff, 0, " \t\n"));
   char* name = Con::getReturnBuffer(StringUnit::getUnit(connBuff, 1, " \t\n"));
   char* target = Con::getReturnBuffer(StringUnit::getUnit(connBuff, 2, " \t\n"));

   mHLSLConnList->addConnect(type, name, target);
}

void HLSLCrossShader::processVertUniforms(const char* vertUni)
{
   char* type = Con::getReturnBuffer(StringUnit::getUnit(vertUni, 0, " \t\n"));
   char* name = Con::getReturnBuffer(StringUnit::getUnit(vertUni, 1, " \t\n"));

   mHLSLUniVertList->addVertUniform(type, name);
}

void HLSLCrossShader::processPixUniforms(const char* pixUni)
{
   char* type = Con::getReturnBuffer(StringUnit::getUnit(pixUni, 0, " \t\n"));
   char* name = Con::getReturnBuffer(StringUnit::getUnit(pixUni, 1, " \t\n"));

   mHLSLUniPixList->addPixUniform(type, name);
}

void HLSLCrossShader::processPixOutputs(const char* pixOut)
{
   char* type = Con::getReturnBuffer(StringUnit::getUnit(pixOut, 0, " \t\n"));
   char* name = Con::getReturnBuffer(StringUnit::getUnit(pixOut, 1, " \t\n"));
   char* target = Con::getReturnBuffer(StringUnit::getUnit(pixOut, 2, " \t\n"));

   mHLSLPixOut->addPixOutput(type, name, target);
}

void HLSLCrossShader::processVertMainLine(const char* vLine)
{
   String newLine = vLine;

   mHLSLVertMain->addLine(newLine);
}

void HLSLCrossShader::processPixelMainLine(const char* pLine)
{
   String newLine = pLine;

   checkMainLine(newLine, false);

   mHLSLPixMain->addLine(newLine);
}

void HLSLCrossShader::_printVertexShader(Stream& stream)
{
   const char* head = "//------------------------------------------\r\n";
   const char* head1 = "// HLSL VERTEX SHADER FROM CROSS API (0.3b)\r\n";
   const char* head2 = "//-----------------------------------------\r\n\r\n";

   stream.write(dStrlen(head), head);
   stream.write(dStrlen(head1), head1);
   stream.write(dStrlen(head2), head2);

   mHLSLInList->print(stream);
   mHLSLConnList->print(stream);
   
   mHLSLVertMain->printHeader(stream);
   mHLSLUniVertList->print(stream);

   mHLSLVertMain->print(stream);
}

void HLSLCrossShader::_printPixelShader(Stream& stream)
{
   const char* head = "//------------------------------------------\r\n";
   const char* head1 = "// HLSL PIXEL SHADER FROM CROSS API (0.3b)\r\n";
   const char* head2 = "//-----------------------------------------\r\n\r\n";

   stream.write(dStrlen(head), head);
   stream.write(dStrlen(head1), head1);
   stream.write(dStrlen(head2), head2);

   mHLSLConnList->print(stream);
   mHLSLPixOut->print(stream);
   
   mHLSLPixMain->printHeader(stream);
   mHLSLUniPixList->print(stream);
   mHLSLPixMain->print(stream);

}
