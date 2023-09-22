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
#ifndef _SHADERBLUEPRINT_H_
#define _SHADERBLUEPRINT_H_

#ifndef _SIMOBJECT_H_
#include "console/simObject.h"
#endif
#ifndef _GFXSHADER_H_
#include "gfx/gfxShader.h"
#endif
#ifndef _TDICTIONARY_H_
#include "core/util/tDictionary.h"
#endif
#ifndef _GFXENUMS_H_
#include "gfx/gfxEnums.h"
#endif
#ifndef _FILEOBJECT_H_
#include "core/fileObject.h"
#endif

class GFXShader;
class ShaderData;
struct GFXShaderMacro;

enum class GFXSamplerType
{
   SAMP_Uknown,
   SAMP_Sampler1D,
   SAMP_Sampler2D,
   SAMP_Sampler3D,
   SAMP_SamplerCube,
   SAMP_Sampler2DArray,
   SAMP_SamplerCubeArray,
   SAMP_Sampler1DShadow,
   SAMP_Sampler2DShadow,

};

class ShaderDataType
{
public:
   String varName;
   GFXShaderConstType dataConstType;
   GFXSamplerType samplerType;
   bool isArray;
   U32 arraySize;

   ShaderDataType()
      : varName(String::EmptyString),
      dataConstType(GFXShaderConstType::GFXSCT_Unknown),
      isArray(false),
      arraySize(0),
      samplerType(GFXSamplerType::SAMP_Uknown)
   {}

   ShaderDataType(GFXShaderConstType constType, String name, bool arrayType = false, U32 size = 0)
      : dataConstType(constType),
      varName(name),
      isArray(arrayType),
      arraySize(size),
      samplerType(GFXSamplerType::SAMP_Uknown)
   {}

   void setSamplerType(GFXSamplerType inSamplerType) { samplerType = inSamplerType; }
};

class ShaderStructDataType : public ShaderDataType
{
public:
   GFXShaderSemantic dataSemantic;
   S32 dataResourceNumber;

   ShaderStructDataType()
      : ShaderDataType(),
      dataSemantic(GFXShaderSemantic::GFXSS_Unknown),
      dataResourceNumber(-1)
   {}

   ShaderStructDataType(GFXShaderConstType constType,
      String name,
      GFXShaderSemantic semanticType,
      S32 resourceNumber = -1,
      bool arrayType = false,
      U32 size = 0)
      : ShaderDataType(constType, name, arrayType, size),
      dataSemantic(semanticType),
      dataResourceNumber(resourceNumber)
   {}
};

class ShaderFunctionArg : public ShaderDataType
{
protected:
   bool in;
   bool out;
   bool inout;
public:

   ShaderFunctionArg()
      : ShaderDataType(),
      in(false),
      out(false),
      inout(false)
   {}

   ShaderFunctionArg(GFXShaderConstType constType,
      String name,
      bool isIn,
      bool isOut,
      bool isInout,
      bool arrayType = false,
      U32 size = 0)
      : ShaderDataType(constType, name, arrayType, size),
      in(isIn),
      out(isOut),
      inout(isInout)
   {}
};

class ShaderStruct
{
protected:
   String structName;
public:
   Vector<ShaderStructDataType*> structDataTypes;
   GFXShaderStructType structType;
   ShaderStruct()
      : structType(GFXShaderStructType::GFXSST_Unknown),
      structName(String::EmptyString)
   {
      VECTOR_SET_ASSOCIATION(structDataTypes);
   }

   ShaderStruct(GFXShaderStructType inStructType, String inName)
      : structType(inStructType),
      structName(inName)
   {
      VECTOR_SET_ASSOCIATION(structDataTypes);
   }

   // print struct
   void printStructHLSL(String& inString);

};

class ShaderFunction
{
protected:
   GFXShaderConstType returnType;
   String name;
   bool isInline;
public:
   Vector<ShaderFunctionArg*> arguments;
   String functionBody;

   ShaderFunction()
      : returnType(GFXShaderConstType::GFXSCT_Unknown),
      name(String::EmptyString),
      functionBody(String::EmptyString),
      isInline(false)
   {
      VECTOR_SET_ASSOCIATION(arguments);
   }

   ShaderFunction(GFXShaderConstType inConstType, String inName, bool inIsInline)
      : returnType(inConstType),
      name(inName),
      functionBody(String::EmptyString),
      isInline(inIsInline)
   {
      VECTOR_SET_ASSOCIATION(arguments);
   }

   void printFunctionHLSL(String& inString);
   void printFunctionGLSL(String& inString);
};

class FileShaderBlueprint
{
public:
   String entryPoint;
   Vector<ShaderDataType*> mShaderUniforms;
   Vector<ShaderFunction*> mShaderFunctions;

   String entryFunctionBody;

   FileShaderBlueprint()
      : entryPoint("main"),
      entryFunctionBody(String::EmptyString)
   {
      VECTOR_SET_ASSOCIATION(mShaderUniforms);
      VECTOR_SET_ASSOCIATION(mShaderFunctions);
   }

   FileShaderBlueprint(String entryName)
      : entryPoint(entryName),
      entryFunctionBody(String::EmptyString)
   {
      VECTOR_SET_ASSOCIATION(mShaderUniforms);
      VECTOR_SET_ASSOCIATION(mShaderFunctions);
   }

};

class ShaderBlueprint : public SimObject
{
   typedef SimObject Parent;

protected:

   StringTableEntry mBluePrintFile;

   String mShaderFileName;

   static Vector<ShaderBlueprint*> smAllShaderBlueprints;
   bool mExportFiles;

   void _onFileChanged(const Torque::Path& path) { _reload(); }

public:

   Vector<ShaderStruct*> mShaderStructs;

   FileShaderBlueprint* mVertexShader;
   FileShaderBlueprint* mPixelShader;

   ShaderBlueprint();
   virtual ~ShaderBlueprint();

   // SimObject
   virtual bool onAdd();
   virtual void onRemove();

   bool initParser(const char* filePath);

   bool readFileShaderData(FileShaderBlueprint* inShader, FileObject& file, U32& lineNum);

   bool shaderFunctionArguments(String lineIn, ShaderFunction* function);

   void convertShaders();

   void convertToHLSL(bool exportFile);
   void convertToGLSL(bool exportFile);

   // ConsoleObject
   static void initPersistFields();

   bool _reload();

   DECLARE_CONOBJECT(ShaderBlueprint);
};


#endif // !_SHADERBLUEPRINT_H_
