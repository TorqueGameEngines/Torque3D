#include "hlslShaderData.h"
#include "platform/platform.h"
#include "materials/crossShaderData.h"
#include "core/volume.h"
#include "console/consoleTypes.h"
#include "core/strings/stringUnit.h"
#include "console/engineAPI.h"
#include "core/stream/fileStream.h"
#include "core/fileObject.h"

const char* newLine = "\r\n";
const char* classClose = "}\r\n\r\n";

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

void HLSLCrossShader::generateSource(char* shaderName)
{
   shaderObjName = shaderName;
   char sourceFile[256];
   dSprintf(sourceFile, sizeof(sourceFile), "%s.cpp", shaderName);
   char headerFile[256];
   dSprintf(headerFile, sizeof(headerFile), "%s.h", shaderName);

   // build constant.
   _buildSourceInfo();

   // create the source file.
   FileStream* s = new FileStream();
   if (!s->open(sourceFile, Torque::FS::File::Write))
   {
      AssertFatal(false, "Failed to open Vertex shader stream");
      return;
   }

   _printSourceFile(*s);
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
   const char* closer = "};\r\n";

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
   const char* closer = "};\r\n";

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
      if(i == mUniformVertList.size()-1)
      {
         if (!String::compare(info.type, "Texture2D"))
         {
            U32 size = dStrlen(info.name);
            char tex[128];
            dStrncpy(tex, info.name, size)[size] = '\0';
            dStrncat(tex, "Tex", dStrlen(tex));
            dSprintf(
               output,
               sizeof(output),
               "\t\t\tuniform %s\t\t%s\t\t: register(%s)\r\n",
               info.type,
               tex,
               info.regNum.c_str());
         }
         else
         {
            dSprintf(
               output,
               sizeof(output),
               "\t\t\tuniform %s\t\t%s\t\t: register(%s)\r\n",
               info.type,
               info.name,
               info.regNum.c_str());
         }
      }
      else
      {
         if (!String::compare(info.type, "Texture2D"))
         {
            U32 size = dStrlen(info.name);
            char tex[128];
            dStrncpy(tex, info.name, size)[size] = '\0';
            dStrncat(tex, "Tex", dStrlen(tex));
            dSprintf(
               output,
               sizeof(output),
               "\t\t\tuniform %s\t\t%s\t\t: register(%s),\r\n",
               info.type,
               tex,
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
      char output[512];
      if (i == mUniformPixList.size() - 1)
      {
         if (!String::compare(info.type, "Texture2D"))
         {
            U32 size = dStrlen(info.name);
            char tex[128];
            dStrncpy(tex, info.name, size)[size] = '\0';
            dStrncat(tex, "Tex", dStrlen(tex));
            dSprintf(
               output,
               sizeof(output),
               "\t\t\tuniform %s\t\t%s\t\t: register(%s)\r\n",
               info.type,
               tex,
               info.regNum.c_str());
         }
         else
         {
            dSprintf(
               output,
               sizeof(output),
               "\t\t\tuniform %s\t\t%s\t\t: register(%s)\r\n",
               info.type,
               info.name,
               info.regNum.c_str());
         }
      }
      else
      {
         if (!String::compare(info.type, "Texture2D"))
         {
            U32 size = dStrlen(info.name);
            char tex[128];
            dStrncpy(tex, info.name, size)[size] = '\0';
            dStrncat(tex, "Tex", dStrlen(tex));
            dSprintf(
               output,
               sizeof(output),
               "\t\t\tuniform %s\t\t%s\t\t: register(%s),\r\n",
               info.type,
               tex,
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
   const char* closer = "};\r\n";

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

   const char* retOut = "\treturn OUT;\r\n";
   stream.write(dStrlen((char*)retOut), retOut);
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

   const char* retOut = "\treturn OUT;\r\n";
   stream.write(dStrlen((char*)retOut), retOut);
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
   samplersDefined = false;
   samplers = 0;
   isMat = false;
   matID = 0;
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
   String newMainLine = vLine;

   mHLSLVertMain->addLine(newMainLine);
}

void HLSLCrossShader::processPixelMainLine(const char* pLine)
{
   String newMainLine = pLine;

   checkMainLine(newMainLine, false);

   mHLSLPixMain->addLine(newMainLine);
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

void HLSLCrossShader::_printSourceFile(Stream& stream)
{
   const char* head = "//------------------------------------------\r\n";
   const char* head1 = "// SHADER SOURCE FROM CROSS API (0.3b)\r\n";
   const char* head2 = "// this will not build, copy to your class.\r\n";
   const char* head3 = "//-----------------------------------------\r\n\r\n";

   stream.write(dStrlen(head), head);
   stream.write(dStrlen(head1), head1);
   stream.write(dStrlen(head2), head2);
   stream.write(dStrlen(head3), head3);

   _printIncludesSource(stream);

   const char* classOpen = "Class::Class()\r\n{\r\n";
   //default inits.
   stream.write(dStrlen(classOpen), classOpen);
   for (U32 i = 0; i < mSourceList.size(); i++)
   {
      SourceInfo info = mSourceList[i];
      // do this now and keep it for renderObject block
      if (info.ModelMat || info.ModelViewMat || info.ModelViewProjMat ||
         info.ViewMat || info.ViewProjMat || info.ProjMat)
      {
         isMat = true;
         matID = i;
      }
      U32 size = dStrlen(info.name);
      char tex[128];
      dStrncpy(tex, info.name, size)[size] = '\0';
      tex[0] = dToupper(tex[0]);
      char output[512];
      dSprintf(output, sizeof(output), "\tm%sSC = NULL;\r\n",tex);

      stream.write(dStrlen((char*)output), output);
   }

   stream.write(dStrlen(classClose), classClose);

   _printOnAdd(stream);

   _printRenderObject(stream);

}

void HLSLCrossShader::_printOnAdd(Stream& stream)
{
   const char* classOpen = "void Class::onAdd()\r\n{\r\n";
   stream.write(dStrlen(classOpen), classOpen);

   const char* isCl = "\tif ( isClientObject() ) \r\n\t{\r\n";
   stream.write(dStrlen(isCl), isCl);

   const char* shaderData = "\t\tShaderData *shaderData;\r\n";
   stream.write(dStrlen(shaderData), shaderData);

   char findShad[512];
   dSprintf(findShad, sizeof(findShad), "\t\tmShader = Sim::findObject( \"%s\", shaderData ) ? shaderData->getShader() : NULL;\r\n", shaderObjName);
   stream.write(dStrlen((char*)findShad), findShad);
   const char* ifNot = "\t\tif ( !mShader )\r\n";
   const char* ifNot2 = "\t\t{\r\n";
   char errOut[512];
   dSprintf(errOut, sizeof(errOut), "\t\t\tCon::errorf( \"Class::onAdd - could not find %s\" );\r\n", shaderObjName);
   const char* ifNot3 = "\t\t\treturn false;\r\n";
   const char* ifNot4 = "\t\t}\r\n\r\n";

   stream.write(dStrlen(ifNot), ifNot);
   stream.write(dStrlen(ifNot2), ifNot2);
   stream.write(dStrlen(errOut), errOut);
   stream.write(dStrlen(ifNot3), ifNot3);
   stream.write(dStrlen(ifNot4), ifNot4);

   const char* shaderComment = "\t\t// Create ShaderConstBuffer and Handles\r\n";
   const char* shaderCosntInit = "\t\tmShaderConsts = mShader->allocConstBuffer();\r\n";
   stream.write(dStrlen(shaderComment), shaderComment);
   stream.write(dStrlen(shaderCosntInit), shaderCosntInit);

   for (U32 i = 0; i < mSourceList.size(); i++)
   {
      
      SourceInfo info = mSourceList[i];
      if (info.sampler)
      {
         samplersDefined = true;
         samplers++;
      }

      U32 size = dStrlen(info.name);
      char tex[128];
      dStrncpy(tex, info.name, size)[size] = '\0';
      tex[0] = dToupper(tex[0]);
      char output[512];
      dSprintf(output, sizeof(output), "\t\tm%sSC = mShader->getShaderConstHandle( \"$%s\" );\r\n", tex, info.name);
      stream.write(dStrlen((char*)output), output);
   }
   
   stream.write(dStrlen(newLine), newLine);

   _printStateBlock(stream);

   const char* clossIf = "\t}\r\n";
   stream.write(dStrlen(clossIf), clossIf);
   stream.write(dStrlen(classClose), classClose);

}

void HLSLCrossShader::_printStateBlock(Stream& stream)
{
   // Create StateBlocks
   const char* line = "\t\tGFXStateBlockDesc desc;\r\n";
   const char* line2 = "\t\tdesc.setCullMode(GFXCullNone);\r\n";
   const char* line3 = "\t\tdesc.setBlend(true);\r\n";
   const char* line4 = "\t\tdesc.setZReadWrite(true, false);\r\n";
   stream.write(dStrlen(line), line);
   stream.write(dStrlen(line2), line2);
   stream.write(dStrlen(line3), line3);
   stream.write(dStrlen(line4), line4);
   if (samplersDefined)
   {
      const char* samp = "\t\tdesc.samplersDefined = true;\r\n";
      stream.write(dStrlen(samp), samp);
      for (U32 i = 0; i < samplers-1; i++)
      {
         char output[512];
         dSprintf(output, sizeof(output), "\t\tdesc.samplers[%d].addressModeU = GFXAddressWrap;\r\n", i);
         stream.write(dStrlen((char*)output), output);
         dSprintf(output, sizeof(output), "\t\tdesc.samplers[%d].addressModeV = GFXAddressWrap;\r\n", i);
         stream.write(dStrlen((char*)output), output);
         dSprintf(output, sizeof(output), "\t\tdesc.samplers[%d].addressModeW = GFXAddressWrap;\r\n", i);
         stream.write(dStrlen((char*)output), output);
         dSprintf(output, sizeof(output), "\t\tdesc.samplers[%d].magFilter = GFXTextureFilterLinear;\r\n", i);
         stream.write(dStrlen((char*)output), output);
         dSprintf(output, sizeof(output), "\t\tdesc.samplers[%d].minFilter = GFXTextureFilterLinear;\r\n", i);
         stream.write(dStrlen((char*)output), output);
         dSprintf(output, sizeof(output), "\t\tdesc.samplers[%d].mipFilter = GFXTextureFilterLinear;\r\n\r\n", i);
         stream.write(dStrlen((char*)output), output);
      }
   }
   else
   {
      const char* samp = "\t\tdesc.samplersDefined = false;\r\n\r\n";
      stream.write(dStrlen(samp), samp);
   }

   const char* fin = "\t\tmStateblock = GFX->createStateBlock(desc);\r\n";
   stream.write(dStrlen(fin), fin);

}

void HLSLCrossShader::_printRenderObject(Stream& stream)
{
   const char* classOpen = "void Class::renderObject( ObjectRenderInst *ri, SceneRenderState *state, BaseMatInstance *mi )\r\n{\r\n";
   stream.write(dStrlen(classOpen), classOpen);

   const char* renderLine = "\tGFX->setShader( mShader );\r\n";
   const char* renderLine1 = "\tGFX->setShaderConstBuffer(mShaderConsts);\r\n";
   const char* renderLine2 = "\tGFX->setStateBlock(mStateblock);\r\n\r\n";
   stream.write(dStrlen(renderLine), renderLine);
   stream.write(dStrlen(renderLine1), renderLine1);
   stream.write(dStrlen(renderLine2), renderLine2);

   for (U32 i = 0; i < mSourceList.size(); i++)
   {
      SourceInfo info = mSourceList[i];
      char output[512];
      U32 size = dStrlen(info.name);
      char tex[128];
      dStrncpy(tex, info.name, size)[size] = '\0';
      tex[0] = dToupper(tex[0]);

      if (info.sampler)
      {
         dSprintf(output, sizeof(output), "\tGFX->setTexture( m%sSC->getSamplerRegister(), texture );\r\n", tex);
         stream.write(dStrlen((char*)output), output);
         continue;
      }
      if (!String::compare(info.type, "time"))
      {
         dSprintf(output, sizeof(output), "\tmShaderConsts->setSafe( m%sSC, (F32)Sim::getCurrentTime() / 1000.0f  );\r\n", tex);
         stream.write(dStrlen((char*)output), output);
         continue;
      }
      dSprintf(output, sizeof(output), "\tmShaderConsts->setSafe( m%sSC, %s );\r\n", tex, info.type);
      stream.write(dStrlen((char*)output), output);
   }
   
   stream.write(dStrlen(classClose), classClose);
}

void HLSLCrossShader::_printIncludesSource(Stream& stream)
{
   // generally required headers.
   const char* inc1 = "#include \"gfx/gfxTransformSaver.h\"\r\n";
   const char* inc2 = "#include \"gfx/gfxTextureManager.h\"\r\n";
   const char* inc3 = "#include \"scene/sceneRenderState.h\"\r\n";
   const char* inc4 = "#include \"renderInstance/renderPassManager.h\"\r\n";
   const char* inc5 = "#include \"materials/shaderData.h\"\r\n";
   const char* inc6 = "#include \"math/mathIO.h\"\r\n\r\n";
   stream.write(dStrlen(inc1), inc1);
   stream.write(dStrlen(inc2), inc2);
   stream.write(dStrlen(inc3), inc3);
   stream.write(dStrlen(inc4), inc4);
   stream.write(dStrlen(inc5), inc5);
   stream.write(dStrlen(inc6), inc6);
}

void HLSLCrossShader::_printHeaderFile(Stream& stream)
{
}

void HLSLCrossShader::_buildSourceInfo()
{
   // do vert first
   for (U32 i = 0; i < mHLSLUniVertList->mUniformVertList.size(); i++)
   {
      HLSLInfo info = mHLSLUniVertList->mUniformVertList[i];
      SourceInfo in;

      if (!String::compare(info.type, "SamplerState"))
      {
         in.name = info.name;
         in.type = "texture";
         // upper case first letter.
         in.sampler = true;
         mSourceList.push_back(in);
         samplers++;
         continue;
      }

      // skip texture2d handled by samplerstates
      if (!String::compare(info.type, "Texture2D"))
      {
         continue;
      }

      if (!String::compare(info.name, "model"))
      {
         in.name = info.name;
         in.type = "modelMatrix";
         // upper case first letter.
         in.ModelMat = true;
         mSourceList.push_back(in);
         continue;
      }

      if (!String::compare(info.name, "modelView"))
      {
         in.name = info.name;
         in.type = "modelViewMatrix";
         // upper case first letter.
         in.ModelViewMat = true;
         mSourceList.push_back(in);
         continue;
      }

      if (!String::compare(info.name, "modelViewProj"))
      {
         in.name = info.name;
         in.type = "modelViewProjMatrix";
         // upper case first letter.
         in.ModelViewProjMat = true;
         mSourceList.push_back(in);
         continue;
      }

      if (!String::compare(info.name, "view"))
      {
         in.name = info.name;
         in.type = "viewMatrix";
         // upper case first letter.
         in.ViewMat = true;
         mSourceList.push_back(in);
         continue;
      }

      if (!String::compare(info.name, "viewProj"))
      {
         in.name = info.name;
         in.type = "viewProjMatrix";
         // upper case first letter.
         in.ViewProjMat = true;
         mSourceList.push_back(in);
         continue;
      }

      if (!String::compare(info.name, "proj"))
      {
         in.name = info.name;
         in.type = "projMatrix";
         // upper case first letter.
         in.ProjMat = true;
         mSourceList.push_back(in);
         continue;
      }

      if (!String::compare(info.name, "accumTime"))
      {
         in.name = info.name;
         in.type = "time";
         // upper case first letter.
         in.Time = true;
         mSourceList.push_back(in);
         continue;
      }

      // else just default.
      in.name = info.name;
      in.type = info.type;
      // upper case first letter.
      in.ProjMat = true;
      mSourceList.push_back(in);

   }

   // now do pixel
   for (U32 i = 0; i < mHLSLUniPixList->mUniformPixList.size(); i++)
   {
      HLSLInfo info = mHLSLUniPixList->mUniformPixList[i];
      SourceInfo in;

      if (!String::compare(info.type, "SamplerState"))
      {
         in.name = info.name;
         in.type = "texture";
         // upper case first letter.
         in.sampler = true;
         mSourceList.push_back(in);
         samplers++;
         continue;
      }

      // skip texture2d handled by samplerstates
      if (!String::compare(info.type, "Texture2D"))
      {
         continue;
      }

      if (!String::compare(info.name, "model"))
      {
         in.name = info.name;
         in.type = "modelMatrix";
         // upper case first letter.
         in.ModelMat = true;
         mSourceList.push_back(in);
         continue;
      }

      if (!String::compare(info.name, "modelView"))
      {
         in.name = info.name;
         in.type = "modelViewMatrix";
         // upper case first letter.
         in.ModelViewMat = true;
         mSourceList.push_back(in);
         continue;
      }

      if (!String::compare(info.name, "modelViewProj"))
      {
         in.name = info.name;
         in.type = "modelViewProjMatrix";
         // upper case first letter.
         in.ModelViewProjMat = true;
         mSourceList.push_back(in);
         continue;
      }

      if (!String::compare(info.name, "view"))
      {
         in.name = info.name;
         in.type = "viewMatrix";
         // upper case first letter.
         in.ViewMat = true;
         mSourceList.push_back(in);
         continue;
      }

      if (!String::compare(info.name, "viewProj"))
      {
         in.name = info.name;
         in.type = "viewProjMatrix";
         // upper case first letter.
         in.ViewProjMat = true;
         mSourceList.push_back(in);
         continue;
      }

      if (!String::compare(info.name, "proj"))
      {
         in.name = info.name;
         in.type = "projMatrix";
         // upper case first letter.
         in.ProjMat = true;
         mSourceList.push_back(in);
         continue;
      }

      if (!String::compare(info.name, "accumTime"))
      {
         in.name = info.name;
         in.type = "time";
         // upper case first letter.
         in.Time = true;
         mSourceList.push_back(in);
         continue;
      }

      // else just default.
      in.name = info.name;
      in.type = info.type;
      // upper case first letter.
      in.ProjMat = true;
      mSourceList.push_back(in);

   }
}
