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

#include "materials/shaderBlueprint.h"
#include "core/volume.h"
#include "core/stream/fileStream.h"
#include "console/consoleTypes.h"
#include "gfx/gfxDevice.h"
#include "core/strings/stringUnit.h"
#include "lighting/lightManager.h"
#include "console/engineAPI.h"

using namespace Torque;

Vector<ShaderBlueprint*> ShaderBlueprint::smAllShaderBlueprints;

IMPLEMENT_CONOBJECT(ShaderBlueprint);

ConsoleDocClass(ShaderBlueprint,
   "@brief Special type of data block that stores information for a shader blueprint.\n\n"

   "@tsexample\n"
   "singleton ShaderBlueprint( DiffuseShader )\n"
   "{\n"
   "	BlueprintFile = $Core::CommonShaderPath @ \"/diffuse.blueprint\";\n"
   "};\n"
   "@endtsexample\n\n"

   "@ingroup Shaders\n");

String TrimTabAndWhiteSpace(String stringIn)
{
   const char* ptr = stringIn;
   while (*ptr == ' ' || *ptr == '\n' || *ptr == '\t')
      ptr++;
   S32 firstWhitespace = 0;
   S32 pos = 0;
   while (ptr[pos])
   {
      if (ptr[pos] != ' ' && ptr[pos] != '\n' && ptr[pos] != '\t')
         firstWhitespace = pos + 1;
      pos++;
   }
   char* ret = Con::getReturnBuffer(firstWhitespace + 1);
   dStrncpy(ret, ptr, firstWhitespace);
   ret[firstWhitespace] = 0;

   return ret;
}


GFXShaderSemantic ToSemantic(String inString)
{
   if (inString.equal("POSITION"))
      return GFXShaderSemantic::GFXSS_POSITION;

   if (inString.equal("BINORMAL"))
      return GFXShaderSemantic::GFXSS_BINORMAL;

   if (inString.equal("NORMAL"))
      return GFXShaderSemantic::GFXSS_NORMAL;

   if (inString.equal("COLOR"))
      return GFXShaderSemantic::GFXSS_COLOR;

   if (inString.equal("SV_POSITION", String::NoCase))
      return GFXShaderSemantic::GFXSS_SVPOSITION;

   if (inString.equal("SV_TARGET", String::NoCase))
      return GFXShaderSemantic::GFXSS_SVTARGET;

   if (inString.equal("SV_DEPTH", String::NoCase))
      return GFXShaderSemantic::GFXSS_SVDEPTH;

   if (inString.startsWith("TEXCOORD"))
      return GFXShaderSemantic::GFXSS_TEXCOORD;

   return GFXShaderSemantic::GFXSS_Unknown;
}

String SemanticToString(GFXShaderSemantic inSemantic)
{
   switch (inSemantic)
   {
      case GFXShaderSemantic::GFXSS_POSITION:
         return "POSITION";
      case GFXShaderSemantic::GFXSS_BINORMAL:
         return "BINORMAL";
      case GFXShaderSemantic::GFXSS_NORMAL:
         return "NORMAL";
      case GFXShaderSemantic::GFXSS_COLOR:
         return "COLOR";
      case GFXShaderSemantic::GFXSS_SVPOSITION:
         return "SV_Position";
      case GFXShaderSemantic::GFXSS_SVTARGET:
         return "SV_Target";
      case GFXShaderSemantic::GFXSS_SVDEPTH:
         return "SV_Depth";
      case GFXShaderSemantic::GFXSS_TEXCOORD:
         return "TEXCOORD";
      default:
         return String::EmptyString;
   }
}

GFXShaderConstType ToConstType(String stringType)
{
   // HLSL types
   // we start with float lets see which one.
   if (stringType.startsWith("float")) {

      if (stringType.endsWith("4x4"))
         return GFXShaderConstType::GFXSCT_Float4x4;

      if (stringType.endsWith("3x4"))
         return GFXShaderConstType::GFXSCT_Float3x4;

      if (stringType.endsWith("4x3"))
         return GFXShaderConstType::GFXSCT_Float4x3;

      if (stringType.endsWith("3x3"))
         return GFXShaderConstType::GFXSCT_Float3x3;

      if (stringType.endsWith("2x2"))
         return GFXShaderConstType::GFXSCT_Float2x2;

      if (stringType.endsWith("2"))
         return GFXShaderConstType::GFXSCT_Float2;

      if (stringType.endsWith("3"))
         return GFXShaderConstType::GFXSCT_Float3;

      if (stringType.endsWith("4"))
         return GFXShaderConstType::GFXSCT_Float4;

      if(stringType.equal("float", String::NoCase))
         return GFXShaderConstType::GFXSCT_Float;
   }

   // lets check for int
   if (stringType.startsWith("int")) {

      if (stringType.endsWith("4"))
         return GFXShaderConstType::GFXSCT_Int4;

      if (stringType.endsWith("3"))
         return GFXShaderConstType::GFXSCT_Int3;

      if (stringType.endsWith("2"))
         return GFXShaderConstType::GFXSCT_Int2;

      if (stringType.equal("int", String::NoCase))
         return GFXShaderConstType::GFXSCT_Int;
   }

   // HLSL TYPES END
   
   //GLSL Types
   // Check for mat type
   if (stringType.startsWith("mat")) {

      if (stringType.endsWith("4x4") || stringType.endsWith("4"))
         return GFXShaderConstType::GFXSCT_Float4x4;

      if (stringType.endsWith("3x4"))
         return GFXShaderConstType::GFXSCT_Float3x4;

      if (stringType.endsWith("4x3"))
         return GFXShaderConstType::GFXSCT_Float4x3;

      if (stringType.endsWith("3x3") || stringType.endsWith("3"))
         return GFXShaderConstType::GFXSCT_Float3x3;

      if (stringType.endsWith("2x2") || stringType.endsWith("2"))
         return GFXShaderConstType::GFXSCT_Float2x2;
   }

   // check for vec type
   if (stringType.startsWith("vec")) {
      if (stringType.endsWith("2"))
         return GFXShaderConstType::GFXSCT_Float2;

      if (stringType.endsWith("3"))
         return GFXShaderConstType::GFXSCT_Float3;

      if (stringType.endsWith("4"))
         return GFXShaderConstType::GFXSCT_Float4;
   }

   // in torque each texture is linked to a sampler because of opengl
   // use sampler types from glsl for simplicity.
   if (stringType.startsWith("sampler"))
   {
      if (stringType.endsWith("1D") ||
         stringType.endsWith("2D") ||
         stringType.endsWith("3D") ||
         stringType.endsWith("1DShadow") ||
         stringType.endsWith("2DShadow"))
         return GFXShaderConstType::GFXSCT_Sampler;

      if (stringType.endsWith("2DArray"))
         return GFXShaderConstType::GFXSCT_SamplerTextureArray;

      if (stringType.endsWith("Cube"))
         return GFXShaderConstType::GFXSCT_SamplerCube;

      if (stringType.endsWith("CubeArray"))
         return GFXShaderConstType::GFXSCT_SamplerCubeArray;
   }

   // we have reached here, we do not know this type...
   return GFXShaderConstType::GFXSCT_Unknown;
}

GFXSamplerType ToSamplerType(String stringType)
{
   if (stringType.startsWith("sampler"))
   {
      if (stringType.endsWith("1D"))
         return GFXSamplerType::SAMP_Sampler1D;

     if(stringType.endsWith("2D"))
        return GFXSamplerType::SAMP_Sampler2D;

     if (stringType.endsWith("3D"))
        return GFXSamplerType::SAMP_Sampler3D;

     if (stringType.endsWith("1DShadow"))
        return GFXSamplerType::SAMP_Sampler1DShadow;

      if(stringType.endsWith("2DShadow"))
         return GFXSamplerType::SAMP_Sampler2DShadow;

      if (stringType.endsWith("2DArray"))
         return GFXSamplerType::SAMP_Sampler2DArray;

      if (stringType.endsWith("Cube"))
         return GFXSamplerType::SAMP_SamplerCube;

      if (stringType.endsWith("CubeArray"))
         return GFXSamplerType::SAMP_SamplerCubeArray;
   }

   return GFXSamplerType::SAMP_Uknown;
}

void UniformSamplerTypeToStringHLSL(GFXSamplerType inSamplerType, String inName, String& inString, U32 tReg)
{
   // hlsl in torque goes to texture2d for 1d?
   // have to add comparison states.
   switch (inSamplerType)
   {
   case GFXSamplerType::SAMP_Sampler1D:
      inString += "uniform Texture2D texture" + inName + " : register(T" + String::ToString(tReg) + ");\n";
      inString += "uniform SamplerState " + inName + " : register(S" + String::ToString(tReg) + ");\n";
      break;
   case GFXSamplerType::SAMP_Sampler2D:
      inString += "uniform Texture2D texture" + inName + " : register(T" + String::ToString(tReg) + ");\n";
      inString += "uniform SamplerState " + inName + " : register(S" + String::ToString(tReg) + ");\n";
      break;
   case GFXSamplerType::SAMP_Sampler2DArray:
      inString += "uniform Texture2DArray texture" + inName + " : register(T" + String::ToString(tReg) + ");\n";
      inString += "uniform SamplerState " + inName + " : register(S" + String::ToString(tReg) + ");\n";
      break;
   case GFXSamplerType::SAMP_Sampler3D:
      inString += "uniform Texture3D texture" + inName + " : register(T" + String::ToString(tReg) + ");\n";
      inString += "uniform SamplerState " + inName + " : register(S" + String::ToString(tReg) + ");\n";
      break;
   case GFXSamplerType::SAMP_SamplerCube:
      inString += "uniform TextureCube texture" + inName + " : register(T" + String::ToString(tReg) + ");\n";
      inString += "uniform SamplerState " + inName + " : register(S" + String::ToString(tReg) + ");\n";
      break;
   case GFXSamplerType::SAMP_SamplerCubeArray:
      inString += "uniform TextureCubeArray texture" + inName + " : register(T" + String::ToString(tReg) + ");\n";
      inString += "uniform SamplerState " + inName + " : register(S" + String::ToString(tReg) + ");\n";
      break;
   default:
      // other types not supported for now ?
      break;
   }
}

void SamplerTypeToStringGLSL(GFXSamplerType inSamplerType, String inName, String& inString)
{
   // hlsl in torque goes to texture2d for 1d?
   // have to add comparison states.
   switch (inSamplerType)
   {
   case GFXSamplerType::SAMP_Sampler1D:
      inString += "sampler2D " + inName;
      break;
   case GFXSamplerType::SAMP_Sampler2D:
      inString += "sampler2D " + inName;
      break;
   case GFXSamplerType::SAMP_Sampler2DArray:
      inString += "sampler2DArray " + inName;
      break;
   case GFXSamplerType::SAMP_Sampler3D:
      inString += "sampler3D " + inName;
      break;
   case GFXSamplerType::SAMP_SamplerCube:
      inString += "samplerCube " + inName;
      break;
   case GFXSamplerType::SAMP_SamplerCubeArray:
      inString += "samplerCubeArray " + inName;
      break;
   default:
      // other types not supported for now ?
      break;
   }
}

void ArgSamplerToStringHLSL(GFXSamplerType inSamplerType, String inName, String& inString)
{
   // hlsl in torque goes to texture2d for 1d?
   // have to add comparison states.
   switch (inSamplerType)
   {
   case GFXSamplerType::SAMP_Sampler1D:
      inString += "Texture2D texture" + inName + ",\nSamplerState " + inName;
      break;
   case GFXSamplerType::SAMP_Sampler2D:
      inString += "Texture2D texture" + inName + ",\nSamplerState " + inName;
      break;
   case GFXSamplerType::SAMP_Sampler3D:
      inString += "Texture3D texture" + inName + ",\nSamplerState " + inName;
      break;
   case GFXSamplerType::SAMP_SamplerCube:
      inString += "TextureCube texture" + inName + ",\nSamplerState " + inName;
      break;
   case GFXSamplerType::SAMP_SamplerCubeArray:
      inString += "TextureCubeArray texture" + inName + ",\nSamplerState " + inName;
      break;
   default:
      // other types not supported for now ?
      break;
   }
}

GFXShaderStructType StructTypeFromString(String structName)
{
   if (structName.equal("VertData"))
      return GFXShaderStructType::GFXSST_VertexData;

   if (structName.equal("ConnectData"))
      return GFXShaderStructType::GFXSST_Connection;

   if (structName.equal("FragOut"))
      return GFXShaderStructType::GFXSST_PixelOut;

   return GFXShaderStructType::GFXSST_Unknown;
}

String ConstTypeToStringHLSL(GFXShaderConstType inConstType)
{
   switch (inConstType)
   {
      case GFXShaderConstType::GFXSCT_Float:
         return "float";

      case GFXShaderConstType::GFXSCT_Float2:
         return "float2";

      case GFXShaderConstType::GFXSCT_Float3:
         return "float3";

      case GFXShaderConstType::GFXSCT_Float4:
         return "float4";

      case GFXShaderConstType::GFXSCT_Float2x2:
         return "float2x2";

      case GFXShaderConstType::GFXSCT_Float3x3:
         return "float3x3";

      case GFXShaderConstType::GFXSCT_Float3x4:
         return "float3x4";

      case GFXShaderConstType::GFXSCT_Float4x3:
         return "float4x3";

      case GFXShaderConstType::GFXSCT_Float4x4:
         return "float4x4";

      case GFXShaderConstType::GFXSCT_Int:
         return "int";

      case GFXShaderConstType::GFXSCT_Int2:
         return "int2";

      case GFXShaderConstType::GFXSCT_Int3:
         return "int3";

      case GFXShaderConstType::GFXSCT_Int4:
         return "int4";

      default:
         // samplers are handled differently.
         return String::EmptyString;
   }
}

String ConstTypeToStringGLSL(GFXShaderConstType inConstType)
{
   switch (inConstType)
   {
   case GFXShaderConstType::GFXSCT_Float:
      return "float";

   case GFXShaderConstType::GFXSCT_Float2:
      return "vec2";

   case GFXShaderConstType::GFXSCT_Float3:
      return "vec3";

   case GFXShaderConstType::GFXSCT_Float4:
      return "vec4";

   case GFXShaderConstType::GFXSCT_Float2x2:
      return "mat2";

   case GFXShaderConstType::GFXSCT_Float3x3:
      return "mat3";

   case GFXShaderConstType::GFXSCT_Float3x4:
      return "mat3x4";

   case GFXShaderConstType::GFXSCT_Float4x3:
      return "mat4x3";

   case GFXShaderConstType::GFXSCT_Float4x4:
      return "mat4";

   case GFXShaderConstType::GFXSCT_Int:
      return "int";

   case GFXShaderConstType::GFXSCT_Int2:
      return "int2";

   case GFXShaderConstType::GFXSCT_Int3:
      return "int3";

   case GFXShaderConstType::GFXSCT_Int4:
      return "int4";

   default:
      // samplers are handled differently.
      return String::EmptyString;
   }
}

void ConvertHLSLLineKeywords(String& inLine)
{
   if (inLine.find("Sample") != String::NPos)
   {
      // read until we get to the first , for our texture variable being sampled.
      S32 start = inLine.find("(") + 1;
      S32 end = inLine.find(",");
      String tex = inLine.substr(start, end - start);

      inLine.replace("Sample", "texture" + tex + ".Sample");
   }

   inLine.replace("mat4", "float4x4");
   inLine.replace("mat4x3", "float4x3");
   inLine.replace("mat3x4", "float3x4");
   inLine.replace("mat3", "float3x3");
   inLine.replace("mat2", "float2x2");
   inLine.replace("vec2", "float2");
   inLine.replace("vec3", "float3");
   inLine.replace("vec4", "float4");
}

void ConvertGLSLLineKeywords(String& inLine, bool vert)
{
   if (inLine.find("Sample") != String::NPos)
   {
      inLine.replace("Sample", "texture");
   }

   if (inLine.find("IN.") != String::NPos)
   {
      S32 start = inLine.find("IN.") + 3;
      S32 end = inLine.find(",", start);

      if(end == -1)
         end = inLine.find(")", start);

      if (end == -1)
         end = inLine.length();

      String var = inLine.substr(start, end - start);

      if(vert)
         inLine.replace("IN." + var, var + "In");
      else
         inLine.replace("IN." + var, var + "Conn");
   }

   if (inLine.find("OUT.") != String::NPos)
   {
      S32 start = inLine.find("OUT.") + 4;
      S32 end = inLine.find(" ", start);
      String var = inLine.substr(start, end - start);

      if (vert)
         inLine.replace("OUT." + var, var + "Conn");
      else
         inLine.replace("OUT." + var, var);
   }

   inLine.replace("float4x4", "mat4");
   inLine.replace("float4x3", "mat4x3");
   inLine.replace("float3x4", "mat3x4");
   inLine.replace("float2x2", "mat2");
   inLine.replace("float3x3", "mat3");
   inLine.replace("float4", "vec4");
   inLine.replace("float3", "vec3");
   inLine.replace("float2", "vec2");

   if (inLine.find("mul") != String::NPos)
   {
      S32 start = inLine.find("mul");
      S32 openBracket = 0;
      S32 mulLoc = 0;
      S32 lastBracket = 0;

      String mulFunc = inLine.substr(start, inLine.length() - start);

      for (U32 i = 0; i < mulFunc.size(); i++)
      {
         if (mulFunc[i] == '(')
            openBracket++;

         if (mulFunc[i] == ')')
            openBracket--;

         if (mulFunc[i] == ',' && openBracket == 1)
         {
            mulLoc = i;
         }

         if (mulFunc[i] == ')' && openBracket == 0)
            lastBracket = i;

      }

      String newMul = mulFunc;
      newMul.erase(lastBracket, 1);
      newMul.replace(mulLoc, 1, " * ");
      newMul.replace("mul(","");

      inLine.replace(mulFunc, newMul);

   }
}

ShaderBlueprint::ShaderBlueprint()
{
   mExportFiles = false;
   mShaderFileName = String::EmptyString;
   //------------------------------------
   VECTOR_SET_ASSOCIATION(mShaderStructs);

   mVertexShader = new FileShaderBlueprint();
   mPixelShader = new FileShaderBlueprint();
}

ShaderBlueprint::~ShaderBlueprint()
{
}

void ShaderBlueprint::initPersistFields()
{
   docsURL;

   addField("BlueprintFile", TypeStringFilename, Offset(mBluePrintFile, ShaderBlueprint),
      "@brief %Path to the blueprint file.\n\n");

   addField("exportFiles", TypeBool, Offset(mExportFiles, ShaderBlueprint),
      "@Export glsl and hlsl files from this blueprint.\n\n");

   Parent::initPersistFields();

}

bool ShaderBlueprint::_reload()
{
   if (!initParser(mBluePrintFile))
      return false;



   return true;
}

bool ShaderBlueprint::onAdd()
{
   if (!Parent::onAdd())
      return false;

   if (!initParser(mBluePrintFile))
      return false;

   convertShaders();

   Torque::FS::AddChangeNotification(mBluePrintFile, this, &ShaderBlueprint::_onFileChanged);

   smAllShaderBlueprints.push_back(this);

   return true;
}

void ShaderBlueprint::onRemove()
{
   Torque::FS::RemoveChangeNotification(mBluePrintFile, this, &ShaderBlueprint::_onFileChanged);

   smAllShaderBlueprints.remove(this);

   Parent::onRemove();
}

bool ShaderBlueprint::initParser(const char* filePath)
{
   UTF8 scriptFilenameBuffer[1024];
   Con::expandScriptFilename((char*)scriptFilenameBuffer, sizeof(scriptFilenameBuffer), filePath);

   if (!Torque::FS::IsFile(scriptFilenameBuffer))
   {
      Con::errorf("ShaderBlueprint - file %s not found", scriptFilenameBuffer);
      return false;
   }

   FileObject f;
   if (!f.readMemory(scriptFilenameBuffer))
   {
      Con::errorf("ShaderBlueprint - couldn't read file %s", scriptFilenameBuffer);
      return false;
   }

   U32 lineNum = 0;
   U32 entries = 0;
   bool blueprintFound = false;
   bool vertexShaderFound = false;
   bool pixelShaderFound = false;

   while (!f.isEOF())
   {
      // this is mostly for error reporting.
      lineNum++;

      // read the file line by line.
      String line = String((char*)f.readLine());

      // skip empty lines
      if (line == String::EmptyString || line.equal(" "))
         continue;

      // comment line so skip it.
      if (!blueprintFound)
         if (line.find('//') != String::NPos || line.find('///') != String::NPos)
            continue;

      // remove leading and trailing spaces.
      line = TrimTabAndWhiteSpace(line);

      // split into words
      Vector<String> lineWords;
      line.split(" ", lineWords);

      if (lineWords.size() == 1)
      {
         if (blueprintFound)
         {
            if (lineWords[0].equal("{"))
            {
               entries++;
               continue;
            }

            if (lineWords[0].equal("};"))
            {
               entries--;
               if (entries == 0)
                  break;
            }
         }
         else {

            Con::printf("ShaderBlueprint - Error: Unexpected \"{\" at line %d", lineNum);
            return false;
         }
      }

      // we havent found blueprint header yet.. dont do anything until we do.
      if (!blueprintFound)
      {
         if (lineWords[0].equal("blueprint", String::NoCase))
         {
            blueprintFound = true;
         }

         S32 startPos = lineWords[1].find('"');
         S32 endPos = lineWords[1].find('"', startPos + 1) - 1;

         mShaderFileName = lineWords[1].substr(startPos + 1, endPos - startPos);

         // see if our open brace is at the end of this word
         if (lineWords[1].find('{') != String::NPos)
         {
            entries++;
         }

         //or in the next word
         if (lineWords.size() > 2)
         {
            if (lineWords[2].equal("{"))
            {
               entries++;
            }
         }
      }
      else // we have already found blueprint.
      {
         if (lineWords[0].equal("struct"))
         {
            String structName;
            // make sure lineWords has more than 1 entry.
            if (lineWords.size() > 1)
            {
               for (U32 i = 1; i < lineWords.size(); i++)
               {
                  //this should be our struct name.
                  if (lineWords[i].find('{') != String::NPos)
                  {
                     structName = lineWords[i].substr(0, lineWords[i].find('{'));
                  }
                  else if(!lineWords[i].equal("{"))
                  {
                     structName = lineWords[i];
                  }

                  if (lineWords[i].equal("{"))
                  {
                     continue;
                  }
               }
            }
            else {
               Con::printf("ShaderBlueprint - Error no struct name on line %d", lineNum);
               return false;
            }
            GFXShaderStructType type = StructTypeFromString(structName);
            if (type == GFXShaderStructType::GFXSST_Unknown)
            {
               Con::printf("ShaderBlueprint - Unknown struct %s on line %d. Possible names are VertData, ConnectData, Fragout", structName.c_str(), lineNum);
               return false;
            }

            ShaderStruct* sctStruct = new ShaderStruct(type, structName);
                  
            // initializers
            bool findParameters = true;
            bool foundConstType = false;
            bool foundName = false;
            bool foundSemantic = false;

            // find struct parameters.
            while (findParameters)
            {
               // read the next line.
               line = TrimTabAndWhiteSpace(String((char*)f.readLine()));
               lineNum++;

               //clear our linewords vector
               lineWords.clear();

               // file it with the new line
               line.split(" ", lineWords);
               GFXShaderConstType sctType;
               String name;
               GFXShaderSemantic sctSemantic;
               S32 resourceNumber = -1;
               for (U32 i = 0; i < lineWords.size(); i++)
               {
                  if (lineWords[i].equal("};"))
                  {
                     findParameters = false;
                     break;
                  }

                  if (!foundConstType)
                  {
                     sctType = ToConstType(lineWords[i]);
                     if (sctType == GFXShaderConstType::GFXSCT_Unknown)
                     {
                        foundConstType = false;
                     }
                     else
                     {
                        foundConstType = true;
                        continue;
                     }
                  }

                  if (!foundName)
                  {
                     if (ToConstType(lineWords[i]) == GFXShaderConstType::GFXSCT_Unknown)
                     {
                        // we are not a const type make it our name
                        name = lineWords[i];
                        foundName = true;
                        continue;
                     }
                  }

                  if (!foundSemantic)
                  {
                     String sctSemanticString;
                     if (lineWords[i].find(';') != String::NPos)
                        sctSemanticString = lineWords[i].substr(0, lineWords[i].find(';'));
                     else
                        sctSemanticString = lineWords[i];

                     sctSemantic = ToSemantic(sctSemanticString);
                     if (sctSemantic == GFXShaderSemantic::GFXSS_Unknown)
                     {
                        foundSemantic = false;
                     }
                     else
                     {
                        // check for trailing number. resourceNumber will be -1 if none exist.
                        String::GetTrailingNumber(sctSemanticString, resourceNumber);
                        foundSemantic = true;
                     }
                  }
               }

               if (foundConstType && foundName && foundSemantic)
               {
                  ShaderStructDataType* structDataType = new ShaderStructDataType(sctType,
                     name,
                     sctSemantic,
                     resourceNumber);

                  sctStruct->structDataTypes.push_back(structDataType);

                  foundConstType = false;
                  foundName = false;
                  foundSemantic = false;
               }

            }

            mShaderStructs.push_back(sctStruct);
            continue;
         }

         // use starts with because people could put { at the end of vertexShader.
         if (!vertexShaderFound) {
            if (lineWords[0].equal("VertexShader"))
            {
               entries++;
               vertexShaderFound = true;

               // for our while loop.
               bool readVertex = true;
               while (readVertex)
               {
                  readVertex = readFileShaderData(mVertexShader, f, lineNum);
               }

               continue;
            }
         }

         if (!pixelShaderFound)
         {
            entries++;
            if (lineWords[0].equal("PixelShader") || lineWords[0].equal("PixelShader{"))
            {
               pixelShaderFound = true;

               // for our while loop.
               bool readPixel = true;
               while (readPixel)
               {
                  readPixel = readFileShaderData(mPixelShader, f, lineNum);
               }

               continue;
            }
         }
      }
   }

   if (!pixelShaderFound)
   {
      Con::printf("ShaderBlueprint - Error: Could not find pixel shader.");
      return false;
   }

   if (!vertexShaderFound)
   {
      Con::printf("ShaderBlueprint - Error: Could not find pixel shader.");
      return false;
   }

   // we have reached here, all must be good.
   return true;
}

bool ShaderBlueprint::readFileShaderData(FileShaderBlueprint* inShader, FileObject& file, U32& lineNum)
{
   String line = String((char*)file.readLine());
   lineNum++;

   // remove leading and trailing spaces.
   line = TrimTabAndWhiteSpace(line);
   // split it up into words.
   Vector<String> lineWords;

   // skip empty lines
   if (line == String::EmptyString || line.equal(" "))
      return true;

   if (line.equal("{"))
      return true;

   if (line.equal("};"))
   {
      return false;
   }

   line.split(" ", lineWords);

   bool inEntryFunction = false;

   // needs to probably be updated to take an argument for what the entry function struct data is.
   if (lineWords[0].equal("ConnectData", String::NoCase) || lineWords[0].equal("FragOut", String::NoCase))
   {
      inEntryFunction = true;
   }

   if (!inEntryFunction)
   {
      if (lineWords[0].equal("#pragma"))
      {
         if (lineWords.size() > 2) {
            if (lineWords[1].equal("entry"))
            {
               S32 startPos = lineWords[2].find('"');
               S32 endPos = lineWords[2].find('"', startPos + 1) - 1;
               inShader->entryPoint = lineWords[2].substr(startPos + 1, endPos - startPos);
            }
            return true;
         }
         else
         {
            Con::printf("ShaderBlueprint - Error #pragma incomplete on line %d", lineNum);
            return false;
         }
      }

      // is this a uniform line.
      if (lineWords[0].equal("uniform"))
      {
         if (lineWords.size() > 2)
         {
            // next word should be a type.
            GFXShaderConstType constType = ToConstType(lineWords[1]);
            GFXSamplerType samplerType = GFXSamplerType::SAMP_Uknown;
            bool isArray = false;
            U32 arraySize = 0;

            if (constType == GFXShaderConstType::GFXSCT_Unknown)
            {
               Con::printf("ShaderBlueprint - Error unknown uniform type on line %d", lineNum);
               return false;
            }

            // are we a sampler?
            if (constType == GFXShaderConstType::GFXSCT_Sampler ||
               constType == GFXShaderConstType::GFXSCT_SamplerCube ||
               constType == GFXShaderConstType::GFXSCT_SamplerCubeArray ||
               constType == GFXShaderConstType::GFXSCT_SamplerTextureArray)
            {
               samplerType = ToSamplerType(lineWords[1]);
            }

            String uniformName;
            if (lineWords[2].find(';') != String::NPos)
               uniformName = lineWords[2].substr(0, lineWords[2].find(';'));
            else
               uniformName = lineWords[2];

            if (uniformName.find('[') != String::NPos)
            {
               isArray = true;
               U32 startPos = uniformName.find('[');
               U32 endPos = uniformName.find(']');
               // find the number inbetween the brackets. Arrays can only be initialized by INTs for now.
               arraySize = dAtoi(String::GetFirstNumber(uniformName, startPos, endPos));
            }

            ShaderDataType* uniformType = new ShaderDataType(constType, uniformName, isArray, arraySize);
            if (samplerType != GFXSamplerType::SAMP_Uknown)
               uniformType->setSamplerType(samplerType);

            inShader->mShaderUniforms.push_back(uniformType);
            return true;
         }
      }

      // this must be a function.
      if (ToConstType(lineWords[0]) != GFXShaderConstType::GFXSCT_Unknown || lineWords[0].equal("inline"))
      {
         // set this to false until we find "{" and all the args.
         bool readFunction = false;
         GFXShaderConstType returnType;
         String funcName;
         bool isInline = false;
         bool returnTypeFound = false;
         bool funcNameFound = false;

         // split function into words.
         lineWords.clear();
         line.split("(", lineWords);

         ShaderFunction* shaderFunction = NULL;

         for (U32 i = 0; i < lineWords.size(); i++)
         {
            // first word should be a function declaration string.
            if (i == 0)
            {
               // split by space now.
               Vector<String> functionDeclaration;
               lineWords[i].split(" ", functionDeclaration);

               for (U32 j = 0; j < functionDeclaration.size(); j++)
               {
                  if (!isInline)
                  {
                     if (functionDeclaration[j].equal("inline"))
                     {
                        isInline = true;
                        continue;
                     }
                  }

                  if (!returnTypeFound)
                  {
                     returnType = ToConstType(functionDeclaration[j]);
                     if (returnType == GFXShaderConstType::GFXSCT_Unknown)
                     {
                        Con::printf("ShaderBlueprint - Unknown return type for function on line %d", lineNum);
                        return false;
                     }
                     else
                     {
                        returnTypeFound = true;
                        continue;
                     }
                  }

                  if (returnTypeFound)
                  {
                     if (!funcNameFound)
                     {
                        if (functionDeclaration[j].find("("))
                        {
                           funcName = functionDeclaration[j].substr(0, functionDeclaration[j].find('('));
                        }
                        else
                        {
                           funcName = functionDeclaration[j];
                        }

                        funcNameFound = true;
                        break;
                     }
                  }
               }

               if (funcNameFound == true && returnTypeFound == true)
               {
                  shaderFunction = new ShaderFunction(returnType, funcName, isInline);
                  continue;
               }
               else
               {
                  Con::printf("ShaderBlueprint - Error: function declared incorrectly on line %d", lineNum);
                  return false;
               }
            }
            else
            {
               readFunction = shaderFunctionArguments(lineWords[i], shaderFunction);
            }
         }

         // if this is false we have more arguments to process.
         if (!readFunction)
         {
            while (!readFunction)
            {
               line = String((char*)file.readLine());
               lineNum++;
               // remove leading and trailing spaces.
               line = TrimTabAndWhiteSpace(line);
               readFunction = shaderFunctionArguments(line, shaderFunction);
            }
         }

         // now we can read our function..
         if (readFunction)
         {
            while (readFunction)
            {
               // just straight up read the lines, as this will be changed per api.
               line = String((char*)file.readLine());
               lineNum++;

               line = TrimTabAndWhiteSpace(line);
               // dont need to worry about opening brace.
               if (line.equal("{"))
                  continue;

               // close out when we find closing brace.
               if (line.find('}') != String::NPos)
               {
                  readFunction = false;
                  break;
               }

               if (shaderFunction != NULL)
                  shaderFunction->functionBody += line + "\n";
            }
         }

         if (shaderFunction != NULL)
            inShader->mShaderFunctions.push_back(shaderFunction);
      }
   }

   if (inEntryFunction)
   {
      while (inEntryFunction)
      {
         // just straight up read the lines, as this will be changed per api.
         line = String((char*)file.readLine());
         lineNum++;
         // remove leading and trailing spaces.
         line = TrimTabAndWhiteSpace(line);

         // dont need to worry about opening brace.
         if (line.equal("{"))
            continue;

         // close out when we find closing brace.
         if (line.equal("};"))
         {
            return false;
         }

         if (line.find(";") != String::NPos)
            line = line.substr(0, line.find(";"));

         // just add our entry function line.
         inShader->entryFunctionBody += line + "\n";
      }
   }

   return true;
}

bool ShaderBlueprint::shaderFunctionArguments(String lineIn, ShaderFunction* function)
{
   // split args by space.
   Vector<String> arguments;
   lineIn.split(" ", arguments);
   bool readFunction = false;
   // arguments dont have spaces, bad programmer!.
   if (lineIn.size() == 1)
   {
      arguments.clear();
      lineIn.split(",", arguments);
   }

   bool in = false;
   bool out = false;
   bool inout = false;

   bool foundType = false;
   bool foundName = false;

   for (U32 j = 0; j < arguments.size(); j++)
   {
      if (arguments[j].find(')') != String::NPos)
      {
         if (!arguments[j].equal(")"))
         {
            arguments[j] = arguments[j].substr(0, arguments[j].find(')'));
         }

         readFunction = true;
      }

      if (arguments[j].find(",") != String::NPos)
      {
         arguments[j] = arguments[j].substr(0, arguments[j].find(','));
      }

      String argumentName;
      GFXShaderConstType type;
      GFXSamplerType samplerType = GFXSamplerType::SAMP_Uknown;

      if (!foundType)
      {
         if (arguments[j].equal("in"))
         {
            in = true;
            continue;
         }

         if (arguments[j].equal("out"))
         {
            out = true;
            continue;
         }

         if (arguments[j].equal("inout"))
         {
            inout = true;
            continue;
         }

         type = ToConstType(arguments[j]);
         samplerType = GFXSamplerType::SAMP_Uknown;

         // are we a sampler?
         if (type == GFXShaderConstType::GFXSCT_Sampler ||
            type == GFXShaderConstType::GFXSCT_SamplerCube ||
            type == GFXShaderConstType::GFXSCT_SamplerCubeArray ||
            type == GFXShaderConstType::GFXSCT_SamplerTextureArray)
         {
            samplerType = ToSamplerType(arguments[j]);
         }

         if (type == GFXSCT_Unknown)
         {
            continue;
         }
         else
         {
            foundType = true;
         }
      }

      if (j > 0)
      {
            argumentName = arguments[j];
            foundName = true;
      }

      if (foundName && foundType)
      {
         function->arguments.push_back(new ShaderFunctionArg(
            type,
            argumentName,
            in,
            out,
            inout
         ));

         in = false;
         out = false;
         inout = false;

         foundType = false;
         foundName = false;
      }
   }

   return readFunction;
}

void ShaderBlueprint::convertShaders()
{
   if (mExportFiles)
   {
      convertToHLSL(true);
      convertToGLSL(true);
   }
   else
   {
      switch (GFX->getAdapterType())
      {
         case Direct3D11:
         {
            convertToHLSL(false);
            break;
         }

         case OpenGL:
         {
            convertToGLSL(false);
            break;
         }

         default:
            break;
      }

   }
}

void ShaderBlueprint::convertToHLSL(bool exportFile)
{
   if (mVertexShader != NULL)
   {
      String vertexShader;

      // print our VertexData struct (there has to be a better way)
      for (U32 i = 0; i < mShaderStructs.size(); i++)
      {
         if (mShaderStructs[i]->structType == GFXShaderStructType::GFXSST_VertexData)
         {
            mShaderStructs[i]->printStructHLSL(vertexShader);
         }
      }

      // print our ConnectionData struct (there has to be a better way)
      for (U32 i = 0; i < mShaderStructs.size(); i++)
      {
         if (mShaderStructs[i]->structType == GFXShaderStructType::GFXSST_Connection)
         {
            mShaderStructs[i]->printStructHLSL(vertexShader);
         }
      }

      for (U32 i = 0; i < mVertexShader->mShaderUniforms.size(); i++)
      {
         // torque doesnt allow samplers in vertex shader for now...
         U32 samplers = 0;
         if (mVertexShader->mShaderUniforms[i]->dataConstType == GFXShaderConstType::GFXSCT_Sampler ||
            mVertexShader->mShaderUniforms[i]->dataConstType == GFXShaderConstType::GFXSCT_SamplerCube ||
            mVertexShader->mShaderUniforms[i]->dataConstType == GFXShaderConstType::GFXSCT_SamplerCubeArray ||
            mVertexShader->mShaderUniforms[i]->dataConstType == GFXShaderConstType::GFXSCT_SamplerTextureArray)
         {
            UniformSamplerTypeToStringHLSL(mVertexShader->mShaderUniforms[i]->samplerType, mVertexShader->mShaderUniforms[i]->varName, vertexShader, samplers);
            samplers++;
         }
         else
         {
            vertexShader += "uniform " + ConstTypeToStringHLSL(mVertexShader->mShaderUniforms[i]->dataConstType) + " " + mVertexShader->mShaderUniforms[i]->varName;
            if (mVertexShader->mShaderUniforms[i]->isArray)
            {
               vertexShader += "[" + String::ToString(mVertexShader->mShaderUniforms[i]->arraySize) + "];\n";
            }
            else
            {
               vertexShader += ";\n";
            }
         }

      }

      vertexShader += "\n";

      if (mVertexShader->mShaderFunctions.size() > 0)
      {
         for (U32 j = 0; j < mVertexShader->mShaderFunctions.size(); j++)
         {
            mVertexShader->mShaderFunctions[j]->printFunctionHLSL(vertexShader);
         }
      }

      vertexShader += "ConnectData " + mVertexShader->entryPoint + "( VertData IN )\n";
      vertexShader += "{\n";
      Vector<String> entryFunctionLines;
      mVertexShader->entryFunctionBody.split("\n", entryFunctionLines);

      for (U32 i = 0; i < entryFunctionLines.size(); i++)
      {
         // we probably wont need to convert anything.
         if (entryFunctionLines[i] == String::EmptyString)
            vertexShader += "\n";
         else
         {
            ConvertHLSLLineKeywords(entryFunctionLines[i]);

            vertexShader += "\t" + entryFunctionLines[i] + ";\n";
         }
      }

      vertexShader += "};";

      if (exportFile)
      {
         Torque::Path filePath = mBluePrintFile;

         String fullPath = filePath.getRootAndPath();
         fullPath += "/Export/HLSL/" + mShaderFileName + "_V.hlsl";

         FileStream* s = new FileStream();
         if (!s->open(fullPath, Torque::FS::File::Write))
         {
            AssertFatal(false, "ShaderBlueprint - Export Vertex: Failed to open Shader Stream");
            return;
         }

         s->writeText(vertexShader.c_str());
         delete s;
      }
   }

   if (mPixelShader != NULL)
   {
      String pixelShader;
      // print our ConnectionData struct (there has to be a better way)
      for (U32 i = 0; i < mShaderStructs.size(); i++)
      {
         if (mShaderStructs[i]->structType == GFXShaderStructType::GFXSST_Connection)
         {
            mShaderStructs[i]->printStructHLSL(pixelShader);
         }
      }

      // print our ConnectionData struct (there has to be a better way)
      for (U32 i = 0; i < mShaderStructs.size(); i++)
      {
         if (mShaderStructs[i]->structType == GFXShaderStructType::GFXSST_PixelOut)
         {
            mShaderStructs[i]->printStructHLSL(pixelShader);
         }
      }

      for (U32 i = 0; i < mPixelShader->mShaderUniforms.size(); i++)
      {
         U32 samplers = 0;
         if (mPixelShader->mShaderUniforms[i]->dataConstType == GFXShaderConstType::GFXSCT_Sampler ||
            mPixelShader->mShaderUniforms[i]->dataConstType == GFXShaderConstType::GFXSCT_SamplerCube ||
            mPixelShader->mShaderUniforms[i]->dataConstType == GFXShaderConstType::GFXSCT_SamplerCubeArray ||
            mPixelShader->mShaderUniforms[i]->dataConstType == GFXShaderConstType::GFXSCT_SamplerTextureArray)
         {
            UniformSamplerTypeToStringHLSL(mPixelShader->mShaderUniforms[i]->samplerType, mPixelShader->mShaderUniforms[i]->varName, pixelShader, samplers);
            samplers++;
         }
         else
         {
            pixelShader += "uniform " + ConstTypeToStringHLSL(mPixelShader->mShaderUniforms[i]->dataConstType) + " " + mPixelShader->mShaderUniforms[i]->varName;
            if (mPixelShader->mShaderUniforms[i]->isArray)
            {
               pixelShader += "[" + String::ToString(mPixelShader->mShaderUniforms[i]->arraySize) + "];\n";
            }
            else
            {
               pixelShader += ";\n";
            }
         }

      }

      pixelShader += "\n";

      if (mPixelShader->mShaderFunctions.size() > 0)
      {
         for (U32 j = 0; j < mPixelShader->mShaderFunctions.size(); j++)
         {
            mPixelShader->mShaderFunctions[j]->printFunctionHLSL(pixelShader);
         }
      }

      pixelShader += "FragOut " + mPixelShader->entryPoint + "( ConnectData IN )\n";
      pixelShader += "{\n";
      Vector<String> entryFunctionLines;
      mPixelShader->entryFunctionBody.split("\n", entryFunctionLines);

      for (U32 i = 0; i < entryFunctionLines.size(); i++)
      {
         // we probably wont need to convert anything.
         if (entryFunctionLines[i] == String::EmptyString)
            pixelShader += "\n";
         else
         {
            ConvertHLSLLineKeywords(entryFunctionLines[i]);
            pixelShader += "\t" + entryFunctionLines[i] + ";\n";
         }
      }

      pixelShader += "};";

      if (exportFile)
      {
         Torque::Path filePath = mBluePrintFile;

         String fullPath = filePath.getRootAndPath();
         fullPath += "/Export/HLSL/" + mShaderFileName + "_P.hlsl";

         FileStream* s = new FileStream();
         if (!s->open(fullPath, Torque::FS::File::Write))
         {
            AssertFatal(false, "ShaderBlueprint - Export Vertex: Failed to open Shader Stream");
            return;
         }

         s->writeText(pixelShader.c_str());
         delete s;
      }
   }
}

void ShaderBlueprint::convertToGLSL(bool exportFile)
{
   String svPos;

   if (mVertexShader != NULL)
   {
      String vertexShader;

      // print our VertexData struct (there has to be a better way)
      for (U32 i = 0; i < mShaderStructs.size(); i++)
      {
         if (mShaderStructs[i]->structType == GFXShaderStructType::GFXSST_VertexData)
         {
            for (U32 j = 0; j < mShaderStructs[i]->structDataTypes.size(); j++)
            {
               vertexShader += "in " + ConstTypeToStringGLSL(mShaderStructs[i]->structDataTypes[j]->dataConstType) + " ";
               vertexShader += mShaderStructs[i]->structDataTypes[j]->varName + "In;\n";
            }
         }
      }

      vertexShader += "\n";

      // print our ConnectionData struct (there has to be a better way)
      for (U32 i = 0; i < mShaderStructs.size(); i++)
      {
         if (mShaderStructs[i]->structType == GFXShaderStructType::GFXSST_Connection)
         {
            for (U32 j = 0; j < mShaderStructs[i]->structDataTypes.size(); j++)
            {
               if (mShaderStructs[i]->structDataTypes[j]->dataSemantic == GFXShaderSemantic::GFXSS_SVPOSITION)
               {
                  svPos = mShaderStructs[i]->structDataTypes[j]->varName;
                  continue;
               }

               vertexShader += "out " + ConstTypeToStringGLSL(mShaderStructs[i]->structDataTypes[j]->dataConstType) + " ";
               vertexShader += mShaderStructs[i]->structDataTypes[j]->varName + "Conn;\n";
            }
         }
      }

      vertexShader += "\n";

      for (U32 i = 0; i < mVertexShader->mShaderUniforms.size(); i++)
      {
         // torque doesnt allow samplers in vertex shader for now...
         if (mVertexShader->mShaderUniforms[i]->dataConstType == GFXShaderConstType::GFXSCT_Sampler ||
            mVertexShader->mShaderUniforms[i]->dataConstType == GFXShaderConstType::GFXSCT_SamplerCube ||
            mVertexShader->mShaderUniforms[i]->dataConstType == GFXShaderConstType::GFXSCT_SamplerCubeArray ||
            mVertexShader->mShaderUniforms[i]->dataConstType == GFXShaderConstType::GFXSCT_SamplerTextureArray)
         {
            vertexShader += "uniform ";
            SamplerTypeToStringGLSL(mVertexShader->mShaderUniforms[i]->samplerType, mVertexShader->mShaderUniforms[i]->varName, vertexShader);
            vertexShader += ";\n";
         }
         else
         {
            vertexShader += "uniform " + ConstTypeToStringGLSL(mVertexShader->mShaderUniforms[i]->dataConstType) + " " + mVertexShader->mShaderUniforms[i]->varName;
            if (mVertexShader->mShaderUniforms[i]->isArray)
            {
               vertexShader += "[" + String::ToString(mVertexShader->mShaderUniforms[i]->arraySize) + "];\n";
            }
            else
            {
               vertexShader += ";\n";
            }
         }

      }

      vertexShader += "\n";

      if (mVertexShader->mShaderFunctions.size() > 0)
      {
         for (U32 j = 0; j < mVertexShader->mShaderFunctions.size(); j++)
         {
            mVertexShader->mShaderFunctions[j]->printFunctionGLSL(vertexShader, true);
         }
      }

      vertexShader += "void main()\n";
      vertexShader += "{\n";
      Vector<String> entryFunctionLines;
      mVertexShader->entryFunctionBody.split("\n", entryFunctionLines);

      for (U32 i = 0; i < entryFunctionLines.size(); i++)
      {
         // we probably wont need to convert anything.
         if (entryFunctionLines[i] == String::EmptyString)
            vertexShader += "\n";
         else
         {
            if (entryFunctionLines[i].find("ConnectData OUT") != String::NPos)
            {
               continue;
            }

            if (entryFunctionLines[i].find("return") != String::NPos)
            {
               continue;
            }

            if (entryFunctionLines[i].find("OUT." + svPos) != String::NPos)
            {
               entryFunctionLines[i].replace("OUT." + svPos, "gl_Position");
            }

            ConvertGLSLLineKeywords(entryFunctionLines[i], true);

            vertexShader += "\t" + entryFunctionLines[i] + ";\n";
         }
      }

      vertexShader += "};";

      if (exportFile)
      {
         Torque::Path filePath = mBluePrintFile;

         String fullPath = filePath.getRootAndPath();
         fullPath += "/Export/GLSL/" + mShaderFileName + "_V.glsl";

         FileStream* s = new FileStream();
         if (!s->open(fullPath, Torque::FS::File::Write))
         {
            AssertFatal(false, "ShaderBlueprint - Export Vertex: Failed to open Shader Stream");
            return;
         }

         s->writeText(vertexShader.c_str());
         delete s;
      }
   }

   if (mPixelShader != NULL)
   {
      String pixelShader;
      // print our ConnectionData struct (there has to be a better way)
      for (U32 i = 0; i < mShaderStructs.size(); i++)
      {
         if (mShaderStructs[i]->structType == GFXShaderStructType::GFXSST_Connection)
         {
            for (U32 j = 0; j < mShaderStructs[i]->structDataTypes.size(); j++)
            {
               if (mShaderStructs[i]->structDataTypes[j]->dataSemantic == GFXShaderSemantic::GFXSS_SVPOSITION)
               {
                  svPos = mShaderStructs[i]->structDataTypes[j]->varName;
                  continue;
               }

               pixelShader += "in " + ConstTypeToStringGLSL(mShaderStructs[i]->structDataTypes[j]->dataConstType) + " ";
               pixelShader += mShaderStructs[i]->structDataTypes[j]->varName + "Conn;\n";
            }
         }
      }

      pixelShader += "\n";

      // print our ConnectionData struct (there has to be a better way)
      for (U32 i = 0; i < mShaderStructs.size(); i++)
      {
         if (mShaderStructs[i]->structType == GFXShaderStructType::GFXSST_PixelOut)
         {
            for (U32 j = 0; j < mShaderStructs[i]->structDataTypes.size(); j++)
            {
               if (mShaderStructs[i]->structDataTypes[j]->dataSemantic == GFXShaderSemantic::GFXSS_SVPOSITION)
               {
                  svPos = mShaderStructs[i]->structDataTypes[j]->varName;
                  continue;
               }

               pixelShader += "out " + ConstTypeToStringGLSL(mShaderStructs[i]->structDataTypes[j]->dataConstType) + " ";
               pixelShader += mShaderStructs[i]->structDataTypes[j]->varName + ";\n";
            }
         }
      }

      pixelShader += "\n";

      for (U32 i = 0; i < mPixelShader->mShaderUniforms.size(); i++)
      {
         if (mPixelShader->mShaderUniforms[i]->dataConstType == GFXShaderConstType::GFXSCT_Sampler ||
            mPixelShader->mShaderUniforms[i]->dataConstType == GFXShaderConstType::GFXSCT_SamplerCube ||
            mPixelShader->mShaderUniforms[i]->dataConstType == GFXShaderConstType::GFXSCT_SamplerCubeArray ||
            mPixelShader->mShaderUniforms[i]->dataConstType == GFXShaderConstType::GFXSCT_SamplerTextureArray)
         {
            pixelShader += "uniform ";
            SamplerTypeToStringGLSL(mPixelShader->mShaderUniforms[i]->samplerType, mPixelShader->mShaderUniforms[i]->varName, pixelShader);
            pixelShader += ";\n";
         }
         else
         {
            pixelShader += "uniform " + ConstTypeToStringGLSL(mPixelShader->mShaderUniforms[i]->dataConstType) + " " + mPixelShader->mShaderUniforms[i]->varName;
            if (mPixelShader->mShaderUniforms[i]->isArray)
            {
               pixelShader += "[" + String::ToString(mPixelShader->mShaderUniforms[i]->arraySize) + "];\n";
            }
            else
            {
               pixelShader += ";\n";
            }
         }

      }

      pixelShader += "\n";

      if (mPixelShader->mShaderFunctions.size() > 0)
      {
         for (U32 j = 0; j < mPixelShader->mShaderFunctions.size(); j++)
         {
            mPixelShader->mShaderFunctions[j]->printFunctionGLSL(pixelShader, false);
         }
      }

      pixelShader += "void main()\n";
      pixelShader += "{\n";
      Vector<String> entryFunctionLines;
      mPixelShader->entryFunctionBody.split("\n", entryFunctionLines);

      for (U32 i = 0; i < entryFunctionLines.size(); i++)
      {
         // we probably wont need to convert anything.
         if (entryFunctionLines[i] == String::EmptyString)
            pixelShader += "\n";
         else
         {
            if (entryFunctionLines[i].find("FragOut OUT") != String::NPos)
            {
               continue;
            }

            if (entryFunctionLines[i].find("return") != String::NPos)
            {
               continue;
            }

            ConvertGLSLLineKeywords(entryFunctionLines[i], false);
            pixelShader += "\t" + entryFunctionLines[i] + ";\n";
         }
      }

      pixelShader += "};";

      if (exportFile)
      {
         Torque::Path filePath = mBluePrintFile;

         String fullPath = filePath.getRootAndPath();
         fullPath += "/Export/GLSL/" + mShaderFileName + "_F.glsl";

         FileStream* s = new FileStream();
         if (!s->open(fullPath, Torque::FS::File::Write))
         {
            AssertFatal(false, "ShaderBlueprint - Export Vertex: Failed to open Shader Stream");
            return;
         }

         s->writeText(pixelShader.c_str());
         delete s;
      }
   }
}

void ShaderStruct::printStructHLSL(String& inString)
{
   inString += "struct " + structName + "\n";
   inString += "{\n";

   for (U32 i = 0; i < structDataTypes.size(); i++)
   {
      inString += "\t" + ConstTypeToStringHLSL(structDataTypes[i]->dataConstType) + " ";
      inString += structDataTypes[i]->varName + " ";
      inString += ": " + SemanticToString(structDataTypes[i]->dataSemantic);
      if (structDataTypes[i]->dataResourceNumber > -1)
      {
         inString += String::ToString(structDataTypes[i]->dataResourceNumber);
      }
      inString += ";\n";
   }

   inString += "};\n\n";
}

void ShaderFunction::printFunctionHLSL(String& inString)
{
   if (isInline)
      inString += "inline ";

   inString += ConstTypeToStringHLSL(returnType) + " ";
   inString += name + "(";
   for (U32 i = 0; i < arguments.size(); i++)
   {

      if (i > 0)
      {
         inString += ",\n";
      }

      if (arguments[i]->in)
         inString += "in";
      else if (arguments[i]->out)
         inString += "out";
      else if (arguments[i]->inout)
         inString += "inout";

      if (arguments[i]->dataConstType == GFXShaderConstType::GFXSCT_Sampler ||
         arguments[i]->dataConstType == GFXShaderConstType::GFXSCT_SamplerCube ||
         arguments[i]->dataConstType == GFXShaderConstType::GFXSCT_SamplerCubeArray ||
         arguments[i]->dataConstType == GFXShaderConstType::GFXSCT_SamplerTextureArray)
      {
         ArgSamplerToStringHLSL(arguments[i]->samplerType, arguments[i]->varName, inString);
      }
      else
      {
         inString += ConstTypeToStringHLSL(arguments[i]->dataConstType) + " " + arguments[i]->varName;
      }

   }

   inString += ")\n{";

   Vector<String> funcLines;

   functionBody.split("\n", funcLines);

   for (U32 j = 0; j < funcLines.size(); j++)
   {
      ConvertHLSLLineKeywords(funcLines[j]);
      inString += "\t" + funcLines[j] + ";\n";
   }

   inString += "}\n";
}

void ShaderFunction::printFunctionGLSL(String& inString, bool vert)
{
   if (isInline)
      inString += "inline ";

   inString += ConstTypeToStringHLSL(returnType) + " ";
   inString += name + "(";
   for (U32 i = 0; i < arguments.size(); i++)
   {

      if (i > 0)
      {
         inString += ",\n";
      }

      if (arguments[i]->in)
         inString += "in";
      else if (arguments[i]->out)
         inString += "out";
      else if (arguments[i]->inout)
         inString += "inout";

      if (arguments[i]->dataConstType == GFXShaderConstType::GFXSCT_Sampler ||
         arguments[i]->dataConstType == GFXShaderConstType::GFXSCT_SamplerCube ||
         arguments[i]->dataConstType == GFXShaderConstType::GFXSCT_SamplerCubeArray ||
         arguments[i]->dataConstType == GFXShaderConstType::GFXSCT_SamplerTextureArray)
      {
         SamplerTypeToStringGLSL(arguments[i]->samplerType, arguments[i]->varName, inString);
      }
      else
      {
         inString += ConstTypeToStringGLSL(arguments[i]->dataConstType) + " " + arguments[i]->varName;
      }

   }

   inString += ")\n{";

   Vector<String> funcLines;

   functionBody.split("\n", funcLines);

   for (U32 j = 0; j < funcLines.size(); j++)
   {
      ConvertGLSLLineKeywords(funcLines[j], vert);
      inString += "\t" + funcLines[j] + ";\n";
   }

   inString += "}\n";
}
