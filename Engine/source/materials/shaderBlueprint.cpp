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

Vector<ShaderBlueprint*> ShaderBlueprint::smAllShaderData;

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

void functionLine(String& inLine, U32& depth, bool& singleLineStatement)
{
   bool lineEnding = true;

   // we probably wont need to convert anything.
   if (inLine == String::EmptyString)
   {
      // may not be needed but when in a text editor its nice if the empty lines start at the same depth.
      for (U32 i = 0; i < depth; i++)
      {
         // insert a tab for each depth.
         inLine.insert(0, "\t");
      }
      inLine += "\n";
      return;
   }
   else if (inLine.startsWith("//") || inLine.startsWith("///"))
   {
      for (U32 i = 0; i < depth; i++)
      {
         // insert a tab for each depth.
         inLine.insert(0, "\t");
      }

      inLine += "\n";
      return;
   }

   if (singleLineStatement)
   {
      if (inLine.equal("{"))
      {
         singleLineStatement = false;
         return;
      }

      inLine.insert(0, "\t");

      for (U32 i = 0; i < depth; i++)
      {
         // insert a tab for each depth.
         inLine.insert(0, "\t");
         depth--;
      }

      singleLineStatement = false;
   }

   if (inLine.find("else") != String::NPos ||
      inLine.find("endif") != String::NPos)
   {
      bool isStatement = false;

      for (U32 i = 0; i < depth; i++)
      {
         // insert a tab for each depth.
         inLine.insert(0, "\t");
      }

      S32 pos = inLine.find("else") + 4;

      if (inLine.size() == pos || inLine.size() == pos +1)
      {
         lineEnding = false;
         isStatement = true;
         singleLineStatement = true;
      }
      else if (dIsspace(inLine[pos]) || inLine[pos] == '(')
      {
         lineEnding = false;
         isStatement = true;
         singleLineStatement = true;
      }

      pos = inLine.find("endif") + 5;
      if (inLine.size() == pos || inLine.size() == pos + 1)
      {
         lineEnding = false;
      }
      else if (dIsspace(inLine[pos]) || inLine[pos] == '(')
         lineEnding = false;

      if (lineEnding)
         inLine += ";\n";
      else
         inLine += "\n";

      return;
   }

   if (inLine.equal("{"))
   {
      singleLineStatement = false;
      depth++;
      return;
   }

   if (depth > 0)
   {
      if (inLine.equal("}"))
      {
         depth--;
      }

      for (U32 i = 0; i < depth; i++)
      {
         // insert a tab for each depth.
         inLine.insert(0, "\t");
      }
   }

   if (inLine.find("if") != String::NPos ||
      inLine.find("for") != String::NPos ||
      inLine.find("while") != String::NPos ||
      inLine.find("do") != String::NPos)
   {
      bool isStatement = false;
      S32 pos = 0;

      if (inLine.find("if") != String::NPos)
      {
         pos = inLine.find("if") + 2;
         if (dIsspace(inLine[pos]) || inLine[pos] == '(')
            isStatement = true;
      }

      if (inLine.find("for") != String::NPos)
      {
         pos = inLine.find("for") + 3;
         if (dIsspace(inLine[pos]) || inLine[pos] == '(')
            isStatement = true;
      }

      if (inLine.find("while") != String::NPos)
      {
         pos = inLine.find("while") + 5;
         if (dIsspace(inLine[pos]) || inLine[pos] == '(')
            isStatement = true;
      }

      if (inLine.find("do") != String::NPos)
      {
         pos = inLine.find("do") + 2;
         if (dIsspace(inLine[pos]) || inLine[pos] == '(')
         {
            //things get called albedo.........
            if (inLine[pos + 1] == '=')
               isStatement = false;
            else
               isStatement = true;
         }
      }

      // if we are already in a statement, add another tab for this.
      if (depth > 0)
      {
         inLine.insert(0, "\t");
      }
      else if (inLine.startsWith("\t") && isStatement)
      {
         depth++;
      }

      if (isStatement)
      {
         lineEnding = false;

         if (inLine.find("{") != String::NPos)
         {
            depth++;
            singleLineStatement = false;
         }
         else
            singleLineStatement = true;
      }
   }

   if (inLine.find(";") != String::NPos)
      lineEnding = false; // line end already exists.

   if (lineEnding)
      inLine += ";\n";
   else
      inLine += "\n";

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

   if (inString.equal("TANGENT"))
      return GFXShaderSemantic::GFXSS_TANGENT;

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
      case GFXShaderSemantic::GFXSS_TANGENT:
         return "TANGENT";
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

   if (stringType.equal("void"))
      return GFXShaderConstType::GFXSCT_Void;

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
      inString += "Texture2D texture" + inName + ", SamplerState " + inName;
      break;
   case GFXSamplerType::SAMP_Sampler2D:
      inString += "Texture2D texture" + inName + ", SamplerState " + inName;
      break;
   case GFXSamplerType::SAMP_Sampler3D:
      inString += "Texture3D texture" + inName + ", SamplerState " + inName;
      break;
   case GFXSamplerType::SAMP_SamplerCube:
      inString += "TextureCube texture" + inName + ", SamplerState " + inName;
      break;
   case GFXSamplerType::SAMP_SamplerCubeArray:
      inString += "TextureCubeArray texture" + inName + ", SamplerState " + inName;
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

      case GFXShaderConstType::GFXSCT_Void:
         return "void";
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
   case GFXShaderConstType::GFXSCT_Void:
      return "void";

   default:
      // samplers are handled differently.
      return String::EmptyString;
   }
}

void ConvertHLSLLineKeywords(String& inLine, U32 samplerNum = 0)
{
   // data types replacement.
   inLine.replace("mat4", "float4x4");
   inLine.replace("mat4x3", "float4x3");
   inLine.replace("mat3x4", "float3x4");
   inLine.replace("mat3", "float3x3");
   inLine.replace("mat2", "float2x2");
   inLine.replace("vec2", "float2");
   inLine.replace("vec3", "float3");
   inLine.replace("vec4", "float4");
   inLine.replace("bvec2", "bool2");
   inLine.replace("bvec3", "bool3");
   inLine.replace("bvec4", "bool4");
   inLine.replace("ivec2", "int2");
   inLine.replace("ivec3", "int3");
   inLine.replace("ivec4", "int4");

   // built in function replacement.
   inLine.replace("mix", "lerp");
   inLine.replace("fract", "frac");

   if (inLine.find("sampler", 0, String::Case) != String::NPos)
   {
      GFXSamplerType type;
      String name;
      Vector<String> declaration;
      // function arg
      
      String newString;
      if (inLine.startsWith("uniform"))
      {
         inLine.split(" ", declaration);
         if (declaration.size() < 3)
         {
            Con::errorf("ShaderBlueprint - Error in sampler type definition.");
            return;
         }

         type = ToSamplerType(declaration[1]);
         name = declaration[2].substr(0, declaration[2].find(";"));

         UniformSamplerTypeToStringHLSL(type, name, newString, samplerNum);
         inLine = newString;
      }
   }

   if (inLine.find("Sample(") != String::NPos)
   {
      // read until we get to the first , for our texture variable being sampled.
      S32 start = inLine.find("Sample(") + 7;
      S32 end = inLine.find(",");
      String tex = inLine.substr(start, end - start);

      tex = TrimTabAndWhiteSpace(tex);

      inLine.replace("Sample(", "texture" + tex + ".Sample(");

   }
}

void ConvertGLSLLineKeywords(String& inLine, bool vert)
{
   inLine.replace("float4x4", "mat4");
   inLine.replace("float4x3", "mat4x3");
   inLine.replace("float3x4", "mat3x4");
   inLine.replace("float2x2", "mat2");
   inLine.replace("float3x3", "mat3");
   inLine.replace("float4", "vec4");
   inLine.replace("float3", "vec3");
   inLine.replace("float2", "vec2");
   inLine.replace("lerp", "mix");
   inLine.replace("frac", "fract");
   inLine.replace("bool2", "bvec2");
   inLine.replace("bool3", "bvec3");
   inLine.replace("bool4", "bvec4");
   inLine.replace("int2", "ivec2");
   inLine.replace("int3", "ivec3");
   inLine.replace("int4", "ivec4");
   inLine.replace("static ", "");

   if (inLine.find("Sample(") != String::NPos)
   {
      inLine.replace("Sample(", "texture(");
   }

   if (inLine.find("IN.") != String::NPos)
   {
      S32 start = inLine.find("IN.") + 3;
      S32 end = inLine.find(",", start);

      if (end == -1)
         end = inLine.find(")", start);

      if (end > inLine.find(".", start))
         end = inLine.find(".", start);

      if (end > inLine.find(" ", start))
         end = inLine.find(" ", start);

      if (end == -1)
         end = inLine.length();

      String var = inLine.substr(start, end - start);

      if (vert)
         inLine.replace("IN." + var, var + "In");
      else
         inLine.replace("IN." + var, var + "Conn");
   }

   if (inLine.find("OUT.") != String::NPos)
   {
      S32 start = inLine.find("OUT.") + 4;
      S32 end = inLine.find(" ", start);

      if (end == -1)
         end = inLine.find(")", start);

      if (end > inLine.find(".", start))
         end = inLine.find(".", start);

      if (end > inLine.find(" ", start))
         end = inLine.find(" ", start);

      if (end == -1)
         end = inLine.length();

      String var = inLine.substr(start, end - start);

      if (vert)
         inLine.replace("OUT." + var, var + "Conn");
      else
         inLine.replace("OUT." + var, var);
   }

   // built in function replacement.
   if (inLine.find("mul") != String::NPos)
   {
      S32 start = inLine.find("mul");
      S32 openBracket = 0;
      S32 firstBracket = 0;
      S32 mulLoc = 0;
      S32 lastBracket = 0;

      String mulFunc = inLine.substr(start, inLine.length() - start);

      for (U32 i = 0; i < mulFunc.size(); i++)
      {
         if (mulFunc[i] == '(')
         {
            if(openBracket == 0)
               firstBracket = i + 1;

            openBracket++;
         }
         // this is not mul
         if (i == 5 && openBracket == 0)
            return;

         if (mulFunc[i] == ')')
            openBracket--;

         if (mulFunc[i] == ',' && openBracket == 1)
         {
            mulLoc = i;
         }

         if (mulFunc[i] == ')' && openBracket == 0)
            lastBracket = i;

      }

      String newMul = TrimTabAndWhiteSpace(mulFunc.substr(firstBracket, mulLoc - firstBracket)) + " * ";
      newMul += TrimTabAndWhiteSpace(mulFunc.substr(mulLoc + 1, lastBracket - (mulLoc + 1)));

      inLine.replace(mulFunc, newMul);
   }

   if (inLine.find("clip") != String::NPos)
   {
      S32 start = inLine.find("clip");
      S32 openBracket = 0;
      S32 firstBracket = 0;
      S32 lastBracket = 0;

      String clipFunc = inLine.substr(start, inLine.length() - start);

      for (U32 i = 0; i < clipFunc.size(); i++)
      {
         if (clipFunc[i] == '(')
         {
            if (openBracket == 0)
               firstBracket = i + 1;
            openBracket++;
         }

         // this is not clip
         if (i == 6 && openBracket == 0)
            return;

         if (clipFunc[i] == ')')
            openBracket--;

         if (clipFunc[i] == ')' && openBracket == 0)
            lastBracket = i;
      }

      String clipArg = inLine.substr(firstBracket, lastBracket - firstBracket );
      clipArg = TrimTabAndWhiteSpace(clipArg);

      inLine = "if( " + clipArg + " )\n\t\tdiscard;";
   }

   // needs to be while since more than 1 saturate function can exist on a line.
   while (inLine.find("saturate") != String::NPos)
   {
      S32 start = inLine.find("saturate");
      S32 openBracket = 0;
      S32 lastBracket = 0;

      String saturateFunc = inLine.substr(start, inLine.length() - start);

      for (U32 i = 0; i < saturateFunc.size(); i++)
      {
         if (saturateFunc[i] == '(')
            openBracket++;

         // this is not saturate
         if (i == 9 && openBracket == 0)
            return;

         if (saturateFunc[i] == ')')
            openBracket--;


         if (saturateFunc[i] == ')' && openBracket == 0)
            lastBracket = i;
      }

      String clampFunc = saturateFunc;
      clampFunc.replace(lastBracket, 1, ", 0.0, 1.0)");
      clampFunc.replace(0, 9, "clamp(");

      inLine.replace(saturateFunc, clampFunc);
   }
   
}

bool ShaderBlueprint::_checkDefinition(GFXShader* shader)
{
   bool error = false;
   Vector<String> samplers;
   samplers.reserve(mShaderSamplers.size());
   bool rtParams[16];
   for (int i = 0; i < 16; ++i)
      rtParams[i] = false;

   const Vector<GFXShaderConstDesc>& shaderConstDesc = shader->getShaderConstDesc();

   for (int i = 0; i < shaderConstDesc.size(); ++i)
   {
      const GFXShaderConstDesc& desc = shaderConstDesc[i];
      if (desc.constType == GFXSCT_Sampler)
      {
         samplers.push_back(desc.name);
      }
   }

   for (int i = 0; i < samplers.size(); ++i)
   {
      int pos;
      bool find = hasSamplerDef(samplers[i], pos);

      if (find && pos >= 0 && mRTParams[pos])
      {
         if (!shader->findShaderConstHandle(String::ToString("$rtParams%d", pos)))
         {
            String errStr = String::ToString("ShaderBlueprint(%s) sampler[%d] used but rtParams%d not used in shader compilation. Possible error", mShaderFileName.c_str(), pos, pos);
            Con::errorf(errStr);
            error = true;
         }
      }

      if (!find)
      {
         String errStr = String::ToString("ShaderBlueprint(%s) sampler %s not defined", mShaderFileName.c_str(), samplers[i].c_str());
         Con::errorf(errStr);
         GFXAssertFatal(0, errStr);
         error = true;
      }
   }

   return !error;
}

bool ShaderBlueprint::hasSamplerDef(const String& _samplerName, int& pos) const
{
   String samplerName = _samplerName.startsWith("$") ? _samplerName : "$" + _samplerName;
   for (int i = 0; i < mShaderSamplers.size(); ++i)
   {
      if (mShaderSamplers[i].equal(samplerName, String::NoCase))
      {
         pos = i;
         return true;
      }
   }

   pos = -1;
   return false;
}

ShaderBlueprint::ShaderBlueprint()
{
   mExportFiles = false;
   mShaderFileName = String::EmptyString;
   //------------------------------------
   VECTOR_SET_ASSOCIATION(mShaderDataStructs);
   VECTOR_SET_ASSOCIATION(mShaderSamplers);
   VECTOR_SET_ASSOCIATION(mShaderMacros);

   mVertexShader = new FileShaderBlueprint();
   mPixelShader = new FileShaderBlueprint();

   mVertexShaderConverted = String::EmptyString;
   mPixelShaderConverted = String::EmptyString;

   mCorrectSSP = false;

   mCompiledShader = NULL;

   for (int i = 0; i < 16; ++i)
      mRTParams[i] = false;
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

GFXShader* ShaderBlueprint::getShader(const Vector<GFXShaderMacro>& macros)
{
   // Combine the dynamic macros with our script defined macros.
   Vector<GFXShaderMacro> finalMacros;
   finalMacros.merge(mShaderMacros);
   finalMacros.merge(macros);

   // Convert the final macro list to a string.
   String cacheKey;
   GFXShaderMacro::stringize(macros, &cacheKey);

   // Lookup the shader for this instance.
   ShaderCache::Iterator iter = mShaders.find(cacheKey);
   if (iter != mShaders.end())
      return iter->value;

   GFXShader* shader = _createShader(finalMacros);
   if (!shader)
      return NULL;

   _checkDefinition(shader);

   mCompiledShader = shader;

   // Store the shader in the cache and return it.
   mShaders.insertUnique(cacheKey, shader);
   return shader;
}

bool ShaderBlueprint::_reload()
{
   mShaderDataStructs.clear();

   SAFE_DELETE(mVertexShader);
   SAFE_DELETE(mPixelShader);

   mVertexShader = new FileShaderBlueprint();
   mPixelShader = new FileShaderBlueprint();

   mVertexShaderConverted.clear();
   mPixelShaderConverted.clear();

   if (!initParser(mBluePrintFile))
      return false;

   if (mExportFiles)
   {
      convertShaders();
   }

   if (mCompiledShader != NULL)
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

      mCompiledShader->reloadStringShader(mVertexShaderConverted, mPixelShaderConverted);
   }

   return true;
}

bool ShaderBlueprint::onAdd()
{
   if (!Parent::onAdd())
      return false;

   mShaderMacros.clear();

   if (!initParser(mBluePrintFile))
      return false;

   if(mExportFiles)
      convertShaders();

   Torque::FS::AddChangeNotification(mBluePrintFile, this, &ShaderBlueprint::_onFileChanged);

   smAllShaderData.push_back(this);

   return true;
}

void ShaderBlueprint::onRemove()
{
   Torque::FS::RemoveChangeNotification(mBluePrintFile, this, &ShaderBlueprint::_onFileChanged);

   smAllShaderData.remove(this);

   Parent::onRemove();
}

bool ShaderBlueprint::initParser(const char* filePath)
{
   Torque::Path path = filePath;

   if (!path.getExtension().equal("tlsl", String::NoCase))
   {
      Con::printf("ShaderBlueprint - Error: Shader blueprint files must have tlsl extension.");
      return false;
   }

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
         if (line.find("//") != String::NPos || line.find("///") != String::NPos)
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
            bool readStructIn = true;

            while (readStructIn)
            {
               readStructIn = readShaderDataStruct(f, line, lineNum);
            }

            continue;
         }

         // use starts with because people could put { at the end of vertexShader.
         if (!vertexShaderFound) {
            if (line.find("VertexShader") != String::NPos)
            {
               entries++;
               vertexShaderFound = true;

               // for our while loop.
               bool readVertex = false;

               while (!readVertex)
               {
                  if (line.find("{") != String::NPos)
                  {
                     readVertex = true;
                     break;
                  }

                  // read the file line by line.
                  line = String((char*)f.readLine());
                  lineNum++;
               }

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
            if (line.find("PixelShader") != String::NPos)
            {
               pixelShaderFound = true;

               // for our while loop.
               bool readPixel = false;

               while (!readPixel)
               {
                  if (line.find("{") != String::NPos)
                  {
                     readPixel = true;
                     break;
                  }

                  // read the file line by line.
                  line = String((char*)f.readLine());
                  lineNum++;
               }

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

bool ShaderBlueprint::initIncludeFileParser(FileShaderBlueprint* inShader, const char* includePath)
{
   Torque::Path path = includePath;

   if (!path.getExtension().equal("tlsl", String::NoCase))
   {
      Con::printf("ShaderBlueprint - Error: include files must have tlsl extension.");
      return false;
   }

   UTF8 scriptFilenameBuffer[1024];
   Con::expandScriptFilename((char*)scriptFilenameBuffer, sizeof(scriptFilenameBuffer), includePath);

   if (!Torque::FS::IsFile(scriptFilenameBuffer))
   {
      Con::errorf("ShaderBlueprint - include file %s not found", scriptFilenameBuffer);
      return false;
   }

   FileObject f;
   if (!f.readMemory(scriptFilenameBuffer))
   {
      Con::errorf("ShaderBlueprint - couldn't read include file %s", scriptFilenameBuffer);
      return false;
   }

   U32 lineNum = 0;
   bool readInclude = true;
   while (readInclude)
   {
      readInclude = readFileShaderData(inShader, f, lineNum);
   }

   // we have reached here, all must be good.
   return true;
}

bool ShaderBlueprint::readShaderDataStruct(FileObject& file, String curLine, U32& lineNum)
{
   String structName;
   // make sure lineWords has more than 1 entry.
   Vector<String> lineWords;
   curLine.split(" ", lineWords);

   if (lineWords.size() > 1)
   {
      for (U32 i = 1; i < lineWords.size(); i++)
      {
         //this should be our struct name.
         if (lineWords[i].find('{') != String::NPos)
         {
            structName = lineWords[i].substr(0, lineWords[i].find('{'));
         }
         else if (!lineWords[i].equal("{"))
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

   ShaderDataStruct* sctStruct = new ShaderDataStruct(type, structName);

   // initializers
   bool findParameters = true;
   bool foundConstType = false;
   bool foundName = false;
   bool foundSemantic = false;

   // find struct parameters.
   while (findParameters)
   {
      // read the next line.
      String line = TrimTabAndWhiteSpace(String((char*)file.readLine()));
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

   mShaderDataStructs.push_back(sctStruct);

   return findParameters;
}

bool ShaderBlueprint::readFileShaderData(FileShaderBlueprint* inShader, FileObject& file, U32& lineNum)
{

   bool readShaderData = true;
   while (readShaderData)
   {
      String line = String((char*)file.readLine());
      lineNum++;

      // remove leading and trailing spaces.
      line = TrimTabAndWhiteSpace(line);
      // split it up into words.
      Vector<String> lineWords;

      // skip empty lines
      if (line == String::EmptyString || line.equal(" "))
      {
         inShader->mShaderLines += "\n";
         continue;
      }

      if (line.equal("{"))
      {
         inShader->mShaderLines += line + "\n";
         continue;
      }

      if (line.equal("};"))
      {
         readShaderData = false;
         break;
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
                  S32 startPos = lineWords[2].find('"') + 1;
                  S32 endPos = lineWords[2].find('"', startPos);
                  inShader->entryPoint = lineWords[2].substr(startPos, endPos - startPos);
               }

               continue;
            }
            else if (lineWords.size() > 1)
            {
               // do we require screenspace correction.
               if (lineWords[1].equal("SCREENSPACEPOS", String::NoCase))
               {
                  mCorrectSSP = true;
               }

               // do we require hdrencode function?
               if (lineWords[1].equal("HDRENCODE", String::NoCase))
               {
                  inShader->mShaderLines += "/// The maximum value for 10bit per component integer HDR encoding.\n";
                  inShader->mShaderLines += "static const float HDR_RGB10_MAX = 4.0;\n";
                  inShader->mShaderLines += "/// Encodes an HDR color for storage into a target.\n";
                  inShader->mShaderLines += "float3 hdrEncode(float3 inColor)\n";
                  inShader->mShaderLines += "{\n";
                  inShader->mShaderLines += "#if defined( TORQUE_HDR_RGB10 )\n";
                  inShader->mShaderLines += "\treturn inColor / HDR_RGB10_MAX;\n";
                  inShader->mShaderLines += "#else\n";
                  inShader->mShaderLines += "\treturn inColor;\n";
                  inShader->mShaderLines += "#endif\n";
                  inShader->mShaderLines += "}\n\n";
                  inShader->mShaderLines += "/// Encodes an HDR color for storage into a target.\n";
                  inShader->mShaderLines += "float4 hdrEncode(float4 inColor)\n";
                  inShader->mShaderLines += "{\n";
                  inShader->mShaderLines += "return float4(hdrEncode(inColor.rgb), inColor.a);\n";
                  inShader->mShaderLines += "}\n\n";
               }

               continue;
            }
            else
            {
               Con::printf("ShaderBlueprint - Error #pragma incomplete on line %d", lineNum);
               return false;
            }


         }

         if (lineWords[0].equal("#define"))
         {
            if (lineWords.size() > 1)
            {
               GFXShaderMacro macro;
               macro.name = lineWords[1];
               macro.value = lineWords[2];
               mShaderMacros.push_back(macro);
            }
            else
            {
               Con::printf("ShaderBlueprint - Error #define doesn't have a value on line %d", lineNum);
               return false;
            }
         }

         if (lineWords[0].equal("#include"))
         {
            if (lineWords.size() > 1)
            {
               S32 startPos = lineWords[1].find('"') + 1;;
               S32 endPos = lineWords[1].find('"', startPos) - 1;
               String includeFile = lineWords[1].substr(startPos, endPos);
               Torque::Path filePath = mBluePrintFile;

               String fullPath = filePath.getRootAndPath();
               fullPath += includeFile.startsWith("/") ? "" + includeFile : "/" + includeFile;

               if (!initIncludeFileParser(inShader, fullPath))
               {
                  Con::printf("ShaderBlueprint - Failed to parse include on line %d", lineNum);
                  return false;
               }

               continue;
            }
            else
            {
               Con::printf("ShaderBlueprint - Error missing include file %d", lineNum);
               return false;
            }
         }

         if (lineWords[0].equal("struct"))
         {
            bool readStructIn = true;
            inShader->mShaderLines += line + "\n";

            while (readStructIn)
            {
               line = String((char*)file.readLine());
               lineNum++;
               line = TrimTabAndWhiteSpace(line);

               if (line.find("}") != String::NPos)
               {
                  inShader->mShaderLines += line + "\n";
                  readStructIn = false;
                  break;
               }

               if (line.find("(") != String::NPos)
               {
                  GFXShaderConstType type = GFXShaderConstType::GFXSCT_Unknown;
                  bool isInline = false;

                  U32 functionNum = 0;
                  for (U32 j = 0; j < lineWords.size(); j++)
                  {
                     if (lineWords[j].find("inline") != String::NPos)
                     {
                        isInline = true;
                     }

                     if (ToConstType(lineWords[j]) != GFXShaderConstType::GFXSCT_Unknown)
                     {
                        // we have the location of our function name. break
                        type = ToConstType(lineWords[j]);
                        functionNum = j + 1;
                        break;
                     }
                  }

                  String functionString;
                  if (lineWords[functionNum].find("(") != String::NPos)
                     functionString = lineWords[functionNum].substr(0, lineWords[functionNum].find("("));
                  else
                     functionString = lineWords[functionNum];

                  // place our catcher for function placement
                  inShader->mShaderLines += "##" + functionString + "\n";

                  ShaderFunction curFunc(type, functionString, isInline);
                  bool readArgs = true;
                  while (readArgs)
                  {
                     Vector<String> args;
                     line.split(",", args);

                     for (U32 i = 0; i < args.size(); i++)
                     {
                        // initializers.
                        bool in = false;
                        bool out = false;
                        bool inout = false;
                        bool isSampler = false;
                        GFXShaderConstType argType = GFXShaderConstType::GFXSCT_Unknown;
                        GFXSamplerType samplerType = GFXSamplerType::SAMP_Uknown;
                        String argName = String::EmptyString;

                        args[i] = TrimTabAndWhiteSpace(args[i]);

                        Vector<String> argWords;
                        args[i].split(" ", argWords);

                        for (U32 j = 0; j < argWords.size(); j++)
                        {
                           if (argWords[j].equal("in"))
                           {
                              in = true;
                              continue;
                           }

                           if (argWords[j].equal("out"))
                           {
                              out = true;
                              continue;
                           }

                           if (argWords[j].equal("inout"))
                           {
                              inout = true;
                              continue;
                           }

                           if (argWords[j].find(")") != String::NPos)
                              readArgs = false;

                           if (ToConstType(argWords[j]) != GFXShaderConstType::GFXSCT_Unknown)
                           {
                              argType = ToConstType(argWords[j]);

                              samplerType = ToSamplerType(argWords[j]);

                              if (argWords.size() > j)
                              {
                                 argName = argWords[j + 1];
                              }
                              else
                              {
                                 Con::printf("ShaderBlueprint - Error: Missing argument name on line %d", lineNum);
                              }
                           }
                        }

                        // safeties.
                        if (argName.find(",") != String::NPos)
                           argName = argName.substr(0, argName.find(","));

                        if (argName.find(")") != String::NPos)
                        {
                           argName = argName.substr(0, argName.find(")"));
                           readArgs = false;
                        }

                        argName = TrimTabAndWhiteSpace(argName);

                        curFunc.arguments.push_back(ShaderFunctionArg(argType,
                           samplerType,
                           argName,
                           in,
                           out,
                           inout));
                     }

                     line = String((char*)file.readLine());
                     lineNum++;

                     // remove leading and trailing spaces.
                     line = TrimTabAndWhiteSpace(line);
                  }

                  bool readBody = true;
                  while (readBody)
                  {
                     line = String((char*)file.readLine());
                     lineNum++;

                     if (line.find("{") != String::NPos)
                        continue;

                     if (line.find("}") != String::NPos)
                        break;

                     line = TrimTabAndWhiteSpace(line);

                     curFunc.functionBody += line + "\n";
                  }

                  inShader->shaderFunctions.push_back(curFunc);

                  continue;
               }

               inShader->mShaderLines += "\t" + line + "\n";
            }

            continue;
         }

         if (lineWords[0].equal("uniform"))
         {
            if (lineWords.size() > 0)
            {
               if (ToSamplerType(lineWords[1]) != GFXSamplerType::SAMP_Uknown)
               {
                  String sampler = lineWords[2].substr(0, lineWords[2].find(";"));

                  // just in case
                  sampler = TrimTabAndWhiteSpace(sampler);
                  mShaderSamplers.push_back(sampler);

               }
            }
         }

         // this could be a function or just a variable initialization.
         if (ToConstType(lineWords[0]) != GFXShaderConstType::GFXSCT_Unknown ||
            lineWords[0].equal("inline") ||
            lineWords[0].equal("static") ||
            lineWords[0].equal("const"))
         {
            // for hlsl we need to keep track of functions so we can parse sampler arguments.
            // this is an initialization.
            if (line.find("=") != String::NPos)
            {
               // this is an initialization, just add it and continue.
               inShader->mShaderLines += line + "\n";
               continue;
            }
            else
            {
               // we check for '=' before this so this must be a function.
               if (line.find("(") != String::NPos)
               {
                  GFXShaderConstType type = GFXShaderConstType::GFXSCT_Unknown;
                  bool isInline = false;

                  U32 functionNum = 0;
                  for (U32 j = 0; j < lineWords.size(); j++)
                  {
                     if (lineWords[j].find("inline") != String::NPos)
                     {
                        isInline = true;
                     }
                     
                     if (ToConstType(lineWords[j]) != GFXShaderConstType::GFXSCT_Unknown)
                     {
                        // we have the location of our function name. break
                        type = ToConstType(lineWords[j]);
                        functionNum = j + 1;
                        break;
                     }
                  }

                  String functionString;
                  if (lineWords[functionNum].find("(") != String::NPos)
                     functionString = lineWords[functionNum].substr(0, lineWords[functionNum].find("("));
                  else
                     functionString = lineWords[functionNum];

                  // place our catcher for function placement
                  inShader->mShaderLines += "##" + functionString + "\n";

                  ShaderFunction curFunc(type, functionString, isInline);
                  bool readArgs = true;
                  while (readArgs)
                  {
                     Vector<String> args;
                     line.split(",", args);

                     for (U32 i = 0; i < args.size(); i++)
                     {
                        // initializers.
                        bool in = false;
                        bool out = false;
                        bool inout = false;
                        bool isSampler = false;
                        GFXShaderConstType argType = GFXShaderConstType::GFXSCT_Unknown;
                        GFXSamplerType samplerType = GFXSamplerType::SAMP_Uknown;
                        String argName = String::EmptyString;

                        args[i] = TrimTabAndWhiteSpace(args[i]);

                        Vector<String> argWords;
                        args[i].split(" ", argWords);

                        for (U32 j = 0; j < argWords.size(); j++)
                        {
                           if (argWords[j].equal("in"))
                           {
                              in = true;
                              continue;
                           }

                           if (argWords[j].equal("out"))
                           {
                              out = true;
                              continue;
                           }

                           if (argWords[j].equal("inout"))
                           {
                              inout = true;
                              continue;
                           }

                           if (argWords[j].find(")") != String::NPos)
                              readArgs = false;

                           if (ToConstType(argWords[j]) != GFXShaderConstType::GFXSCT_Unknown)
                           {
                              argType = ToConstType(argWords[j]);

                              samplerType = ToSamplerType(argWords[j]);

                              if (argWords.size() > j)
                              {
                                 argName = argWords[j + 1];
                              }
                              else
                              {
                                 Con::printf("ShaderBlueprint - Error: Missing argument name on line %d", lineNum);
                              }
                           }
                        }

                        // safeties.
                        if (argName.find(",") != String::NPos)
                           argName = argName.substr(0, argName.find(","));

                        if (argName.find(")") != String::NPos)
                        {
                           argName = argName.substr(0, argName.find(")"));
                           readArgs = false;
                        }

                        argName = TrimTabAndWhiteSpace(argName);

                        curFunc.arguments.push_back(ShaderFunctionArg(argType,
                           samplerType,
                           argName,
                           in,
                           out,
                           inout));
                     }

                     line = String((char*)file.readLine());
                     lineNum++;

                     // remove leading and trailing spaces.
                     line = TrimTabAndWhiteSpace(line);
                  }

                  bool readBody = true;
                  while (readBody)
                  {
                     line = String((char*)file.readLine());
                     lineNum++;

                     if (line.find("{") != String::NPos)
                        continue;

                     if (line.find("}") != String::NPos)
                        break;

                     line = TrimTabAndWhiteSpace(line);

                     curFunc.functionBody += line + "\n";
                  }

                  inShader->shaderFunctions.push_back(curFunc);

                  continue;
               }
            }
         }

         inShader->mShaderLines += line + "\n";
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
               break;
            }

            if (line.find(";") == line.length() - 1)
               line = line.substr(0, line.find(";"));

            // just add our entry function line.
            inShader->entryFunctionBody += line + "\n";
         }
      }
   }

   return readShaderData;
}

GFXShader* ShaderBlueprint::_createShader(const Vector<GFXShaderMacro>& macros)
{
   Vector<String> samplers;
   samplers.setSize(mShaderSamplers.size());
   for (U32 i = 0; i < mShaderSamplers.size(); i++)
   {
      // we should be able to do this while finding the samplers?
      samplers[i] = mShaderSamplers[i][0] == '$' ? mShaderSamplers[i] : "$" + mShaderSamplers[i];
   }

   // Enable shader error logging.
   GFXShader::setLogging(true, true);

   GFXShader* shader = GFX->createShader();
   bool success = false;
   F32 pixver = GFX->getPixelShaderVersion();

   // eventually will want to split up vertex and pixel shader compile steps
   // and add the extra shader types eg. compute, geometry, tess.
   switch (GFX->getAdapterType())
   {
      case Direct3D11:
      {
         if(mVertexShaderConverted == String::EmptyString && mPixelShaderConverted == String::EmptyString)
            convertToHLSL(false);

         success = shader->initFromString(mVertexShaderConverted,
                                          mPixelShaderConverted,
                                          pixver,
                                          macros,
                                          samplers);

         break;
      }

      case OpenGL:
      {
         if (mVertexShaderConverted == String::EmptyString && mPixelShaderConverted == String::EmptyString)
            convertToGLSL(false);

         success = shader->initFromString(mVertexShaderConverted,
                                          mPixelShaderConverted,
                                          pixver,
                                          macros,
                                          samplers);
         break;
      }

      default:
         success = false;
         break;
   }

   // If we failed to load the shader then
   // cleanup and return NULL.
   if (!success)
   {
      SAFE_DELETE(shader);
   }

   return shader;
}

void ShaderBlueprint::convertShaders()
{
      convertToHLSL(true);
      mPixelShaderConverted.clear();
      mVertexShaderConverted.clear();

      convertToGLSL(true);
      mPixelShaderConverted.clear();
      mVertexShaderConverted.clear();
}

void ShaderBlueprint::convertToHLSL(bool exportFile)
{
   if (mVertexShader != NULL)
   {
      // print our VertexData struct (there has to be a better way)
      for (U32 i = 0; i < mShaderDataStructs.size(); i++)
      {
         if (mShaderDataStructs[i]->structType == GFXShaderStructType::GFXSST_VertexData)
         {
            mShaderDataStructs[i]->printStructHLSL(mVertexShaderConverted);
         }
      }

      // print our ConnectionData struct (there has to be a better way)
      for (U32 i = 0; i < mShaderDataStructs.size(); i++)
      {
         if (mShaderDataStructs[i]->structType == GFXShaderStructType::GFXSST_Connection)
         {
            mShaderDataStructs[i]->printStructHLSL(mVertexShaderConverted);
         }
      }

      processShaderLines(mVertexShader, mVertexShaderConverted, mVertexShader->mShaderLines);

      mVertexShaderConverted += "ConnectData " + mVertexShader->entryPoint + "( VertData IN )\n";
      mVertexShaderConverted += "{\n";
      Vector<String> entryFunctionLines;
      mVertexShader->entryFunctionBody.split("\n", entryFunctionLines);

      U32 depth = 0;
      bool inStatement = false;
      for (U32 i = 0; i < entryFunctionLines.size(); i++)
      {
         if (entryFunctionLines[i].find("[unroll]") != String::NPos)
         {
            if (depth > 0)
            {
               for (U32 j = 0; j < depth; j++)
                  mVertexShaderConverted += "\t";
            }
            mVertexShaderConverted += "\t[unroll]\n";
            continue;
         }

         ConvertHLSLLineKeywords(entryFunctionLines[i]);
         functionLine(entryFunctionLines[i], depth, inStatement);
         mVertexShaderConverted += "\t" + entryFunctionLines[i];
      }

      mVertexShaderConverted += "};";

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

         s->writeText(mVertexShaderConverted.c_str());
         delete s;
      }
   }

   if (mPixelShader != NULL)
   {
      // print our ConnectionData struct (there has to be a better way)
      for (U32 i = 0; i < mShaderDataStructs.size(); i++)
      {
         if (mShaderDataStructs[i]->structType == GFXShaderStructType::GFXSST_Connection)
         {
            mShaderDataStructs[i]->printStructHLSL(mPixelShaderConverted);
         }
      }

      // print our ConnectionData struct (there has to be a better way)
      for (U32 i = 0; i < mShaderDataStructs.size(); i++)
      {
         if (mShaderDataStructs[i]->structType == GFXShaderStructType::GFXSST_PixelOut)
         {
            mShaderDataStructs[i]->printStructHLSL(mPixelShaderConverted);
         }
      }

      processShaderLines(mPixelShader, mPixelShaderConverted, mPixelShader->mShaderLines);

      mPixelShaderConverted += "FragOut " + mPixelShader->entryPoint + "( ConnectData IN )\n";
      mPixelShaderConverted += "{\n";
      Vector<String> entryFunctionLines;
      mPixelShader->entryFunctionBody.split("\n", entryFunctionLines);

      U32 depth = 0;
      bool inStatement = false;
      for (U32 i = 0; i < entryFunctionLines.size(); i++)
      {
         if (entryFunctionLines[i].find("[unroll]") != String::NPos)
         {
            if (depth > 0)
            {
               for (U32 j = 0; j < depth; j++)
                  mPixelShaderConverted += "\t";
            }
            mPixelShaderConverted += "\t[unroll]\n";
            continue;
         }

         ConvertHLSLLineKeywords(entryFunctionLines[i]);
         functionLine(entryFunctionLines[i], depth, inStatement);
         mPixelShaderConverted += "\t" + entryFunctionLines[i];
      }

      mPixelShaderConverted += "};";

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

         s->writeText(mPixelShaderConverted.c_str());
         delete s;
      }
   }
}

void ShaderBlueprint::convertToGLSL(bool exportFile)
{
   String svPos;

   if (mVertexShader != NULL)
   {
      mVertexShaderConverted += "#version 330\n\n";

      // add required extensions. these automatically got added in the shaderFRomStream in glsl
      mVertexShaderConverted += "#extension GL_ARB_texture_cube_map_array : enable\n";
      mVertexShaderConverted += "#extension GL_ARB_gpu_shader5 : enable\n\n";

      // print our VertexData struct (there has to be a better way)
      for (U32 i = 0; i < mShaderDataStructs.size(); i++)
      {
         if (mShaderDataStructs[i]->structType == GFXShaderStructType::GFXSST_VertexData)
         {
            for (U32 j = 0; j < mShaderDataStructs[i]->structDataTypes.size(); j++)
            {
               S32 semanticBind = mShaderDataStructs[i]->structDataTypes[j]->dataSemantic;
               // most of the time resource number will be 0 but for texcoords it can go up to 9
               if(mShaderDataStructs[i]->structDataTypes[j]->dataResourceNumber > -1)
                  semanticBind += mShaderDataStructs[i]->structDataTypes[j]->dataResourceNumber;

               mVertexShaderConverted += "layout(location = " + String::ToString(semanticBind) + ") ";
               mVertexShaderConverted += "in " + ConstTypeToStringGLSL(mShaderDataStructs[i]->structDataTypes[j]->dataConstType) + " ";
               mVertexShaderConverted += mShaderDataStructs[i]->structDataTypes[j]->varName + "In;\n";
            }
         }
      }

      mVertexShaderConverted += "\n";

      // print our ConnectionData struct (there has to be a better way)
      for (U32 i = 0; i < mShaderDataStructs.size(); i++)
      {
         if (mShaderDataStructs[i]->structType == GFXShaderStructType::GFXSST_Connection)
         {
            for (U32 j = 0; j < mShaderDataStructs[i]->structDataTypes.size(); j++)
            {
               if (mShaderDataStructs[i]->structDataTypes[j]->dataSemantic == GFXShaderSemantic::GFXSS_SVPOSITION)
               {
                  svPos = mShaderDataStructs[i]->structDataTypes[j]->varName;
                  continue;
               }

               mVertexShaderConverted += "out " + ConstTypeToStringGLSL(mShaderDataStructs[i]->structDataTypes[j]->dataConstType) + " ";
               mVertexShaderConverted += mShaderDataStructs[i]->structDataTypes[j]->varName + "Conn;\n";
            }
         }
      }

      processShaderLines(mVertexShader, mVertexShaderConverted, mVertexShader->mShaderLines, true, true);

      mVertexShaderConverted += "void main()\n";
      mVertexShaderConverted += "{\n";
      Vector<String> entryFunctionLines;
      mVertexShader->entryFunctionBody.split("\n", entryFunctionLines);

      U32 depth = 0;
      bool inStatement = false;
      for (U32 i = 0; i < entryFunctionLines.size(); i++)
      {
         if (entryFunctionLines[i].find("ConnectData OUT") != String::NPos)
         {
            continue;
         }

         if (entryFunctionLines[i].find("return") != String::NPos)
         {
            continue;
         }

         if (entryFunctionLines[i].find("[unroll]") != String::NPos)
         {
            continue;
         }

         if (entryFunctionLines[i].find("OUT." + svPos) != String::NPos)
         {
            entryFunctionLines[i].replace("OUT." + svPos, "gl_Position");
         }

         ConvertGLSLLineKeywords(entryFunctionLines[i], true);
         functionLine(entryFunctionLines[i], depth, inStatement);
         mVertexShaderConverted += "\t" + entryFunctionLines[i];
      }

      if (mCorrectSSP)
      {
         mVertexShaderConverted += "\tgl_Position.y *= -1;\n";
      }

      mVertexShaderConverted += "};";

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

         s->writeText(mVertexShaderConverted.c_str());
         delete s;
      }
   }

   if (mPixelShader != NULL)
   {
      mPixelShaderConverted += "#version 330\n\n";

      // add required extensions. these automatically got added in the shaderFRomStream in glsl
      mPixelShaderConverted += "#extension GL_ARB_texture_cube_map_array : enable\n";
      mPixelShaderConverted += "#extension GL_ARB_gpu_shader5 : enable\n\n";

      // print our ConnectionData struct (there has to be a better way)
      for (U32 i = 0; i < mShaderDataStructs.size(); i++)
      {
         if (mShaderDataStructs[i]->structType == GFXShaderStructType::GFXSST_Connection)
         {
            for (U32 j = 0; j < mShaderDataStructs[i]->structDataTypes.size(); j++)
            {
               if (mShaderDataStructs[i]->structDataTypes[j]->dataSemantic == GFXShaderSemantic::GFXSS_SVPOSITION)
               {
                  svPos = mShaderDataStructs[i]->structDataTypes[j]->varName;
                  continue;
               }

               mPixelShaderConverted += "in " + ConstTypeToStringGLSL(mShaderDataStructs[i]->structDataTypes[j]->dataConstType) + " ";
               mPixelShaderConverted += mShaderDataStructs[i]->structDataTypes[j]->varName + "Conn;\n";
            }
         }
      }

      mPixelShaderConverted += "\n";

      // print our ConnectionData struct (there has to be a better way)
      for (U32 i = 0; i < mShaderDataStructs.size(); i++)
      {
         if (mShaderDataStructs[i]->structType == GFXShaderStructType::GFXSST_PixelOut)
         {
            for (U32 j = 0; j < mShaderDataStructs[i]->structDataTypes.size(); j++)
            {

               // SV_Target can have up to 7 targets, this should happen automatically.
               S32 semanticBind = 0;
               // most of the time resource number will be 0 but for texcoords it can go up to 9
               if (mShaderDataStructs[i]->structDataTypes[j]->dataResourceNumber > -1)
                  semanticBind += mShaderDataStructs[i]->structDataTypes[j]->dataResourceNumber;

               mPixelShaderConverted += "layout(location = " + String::ToString(semanticBind) + ") ";
               mPixelShaderConverted += "out " + ConstTypeToStringGLSL(mShaderDataStructs[i]->structDataTypes[j]->dataConstType) + " ";
               mPixelShaderConverted += mShaderDataStructs[i]->structDataTypes[j]->varName + ";\n";
            }
         }
      }

      processShaderLines(mPixelShader, mPixelShaderConverted, mPixelShader->mShaderLines, true, false);

      mPixelShaderConverted += "void main()\n";
      mPixelShaderConverted += "{\n";
      Vector<String> entryFunctionLines;
      mPixelShader->entryFunctionBody.split("\n", entryFunctionLines);

      U32 depth = 0;
      bool inStatement = false;
      for (U32 i = 0; i < entryFunctionLines.size(); i++)
      {
         bool formatLine = true;

         if (entryFunctionLines[i].find("clip") != String::NPos)
         {
            formatLine = false;
         }

         if (entryFunctionLines[i].find("FragOut OUT") != String::NPos)
         {
            continue;
         }

         if (entryFunctionLines[i].find("return") != String::NPos)
         {
            continue;
         }

         if (entryFunctionLines[i].find("[unroll]") != String::NPos)
         {
            continue;
         }

         ConvertGLSLLineKeywords(entryFunctionLines[i], false);

         if(formatLine)
            functionLine(entryFunctionLines[i], depth, inStatement);

         mPixelShaderConverted += "\t" + entryFunctionLines[i];
      }

      mPixelShaderConverted += "};";

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

         s->writeText(mPixelShaderConverted.c_str());
         delete s;
      }
   }
}

void ShaderDataStruct::printStructHLSL(String& inString)
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

void ShaderFunction::printFunctionHLSL(String& inString, U32 startDepth)
{
   for (U32 i = 0; i < startDepth; i++)
      inString += "\t";

   if (isInline)
      inString += "inline ";

   Vector<String> samplerArgs;

   inString += ConstTypeToStringHLSL(returnType) + " ";
   inString += name + "(";
   for (U32 i = 0; i < arguments.size(); i++)
   {

      if (i > 0)
      {
         inString += ",\n";
      }

      if (arguments[i].in)
         inString += "in";
      else if (arguments[i].out)
         inString += "out";
      else if (arguments[i].inout)
         inString += "inout";

      if (arguments[i].samplerType != GFXSamplerType::SAMP_Uknown)
      {
         ArgSamplerToStringHLSL(arguments[i].samplerType, arguments[i].varName, inString);
         samplerArgs.push_back(arguments[i].varName);
      }
      else
      {
         if (i > 0)
            inString += "\t\t";

         inString += ConstTypeToStringHLSL(arguments[i].dataConstType) + " " + arguments[i].varName;
      }

   }

   inString += ")\n";

   for (U32 i = 0; i < startDepth; i++)
      inString += "\t";

   inString += "{\n";

   Vector<String> funcLines;
   functionBody.split("\n", funcLines);

   U32 depth = 0;
   bool inStatement = false;
   for (U32 j = 0; j < funcLines.size(); j++)
   {
      // we probably wont need to convert anything.
      if (funcLines[j] == String::EmptyString)
         inString += "\n";
      else
      {
         ConvertHLSLLineKeywords(funcLines[j]);
         functionLine(funcLines[j], depth, inStatement);

         for (U32 k = 0; k < samplerArgs.size(); k++)
         {
         
            if (funcLines[j].find("SamplerState", String::Case) != String::NPos)
               continue;
            else
            {
               if (funcLines[j].find(samplerArgs[k], String::Cas) != String::NPos)
               {
                  // in hlsl we need to send the texture var along with the sampler var.
                  funcLines[j].replace(samplerArgs[k], "texture" + samplerArgs[k] + ", " + samplerArgs[k]);
               }
            }
         }

         for (U32 i = 0; i < startDepth; i++)
            inString += "\t";

         inString += "\t" + funcLines[j];
      }
   }

   inString += "}\n\n";
}

void ShaderFunction::printFunctionGLSL(String& inString, bool vert, U32 startDepth)
{
   for (U32 i = 0; i < startDepth; i++)
      inString += "\t";

   if (isInline)
      inString += "inline ";

   inString += ConstTypeToStringGLSL(returnType) + " ";
   inString += name + "(";
   for (U32 i = 0; i < arguments.size(); i++)
   {

      if (i > 0)
      {
         inString += ",\n";
      }

      if (arguments[i].in)
         inString += "in";
      else if (arguments[i].out)
         inString += "out";
      else if (arguments[i].inout)
         inString += "inout";

      if (arguments[i].samplerType != GFXSamplerType::SAMP_Uknown)
      {
         SamplerTypeToStringGLSL(arguments[i].samplerType, arguments[i].varName, inString);
      }
      else
      {
         if (i > 0)
            inString += "\t\t";

         inString += ConstTypeToStringGLSL(arguments[i].dataConstType) + " " + arguments[i].varName;
      }

   }

   inString += ")\n";

   for (U32 i = 0; i < startDepth; i++)
      inString += "\t";

   inString += "{\n";

   Vector<String> funcLines;
   functionBody.split("\n", funcLines);

   U32 depth = 0;
   bool inStatement = false;
   for (U32 j = 0; j < funcLines.size(); j++)
   {
      // we probably wont need to convert anything.
      if (funcLines[j] == String::EmptyString)
         inString += "\n";
      else
      {
         ConvertGLSLLineKeywords(funcLines[j], vert);
         functionLine(funcLines[j], depth, inStatement);

         for (U32 i = 0; i < startDepth; i++)
            inString += "\t";

         inString += "\t" + funcLines[j];
      }
   }

   inString += "}\n\n";
}

void ShaderBlueprint::processShaderLines(FileShaderBlueprint* inShader, String& convertedShaderString, String inShaderLines, bool isGLSL, bool isVert)
{
   Vector<String> shaderLines;
   inShaderLines.split("\n", shaderLines);

   U32 entries = 0;
   U32 samplers = -1;
   bool funcFound = false;
   for (U32 i = 0; i < shaderLines.size(); i++)
   {
      U32 funcId = 0;

      for (U32 k = 0; k < inShader->shaderFunctions.size(); k++)
      {
         String funcName = inShader->shaderFunctions[k].name;

         if (shaderLines[i].find("##" + funcName, 0, String::Case) != String::NPos)
         {
            funcId = k;
            funcFound = true;
         }
      }

      if (shaderLines[i].find("}") != String::NPos)
         entries--;

      if (shaderLines[i].find("sampler") != String::NPos && shaderLines[i].startsWith("uniform"))
         samplers++;

      if(!isGLSL)
         ConvertHLSLLineKeywords(shaderLines[i], samplers);
      else
         ConvertGLSLLineKeywords(shaderLines[i], isVert);

      for (U32 j = 0; j < entries; j++)
         convertedShaderString += "\t";

      if (!funcFound)
         convertedShaderString += shaderLines[i] + "\n";
      else
      {
         if (!isGLSL)
            inShader->shaderFunctions[funcId].printFunctionHLSL(convertedShaderString, entries);
         else
            inShader->shaderFunctions[funcId].printFunctionGLSL(convertedShaderString, entries);

         funcFound = false;
      }

      if (shaderLines[i].find("{") != String::NPos)
         entries++;

   }
}
