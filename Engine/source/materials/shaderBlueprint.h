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

class ShaderDataType
{
public:
   String varName;
   GFXShaderConstType dataConstType;
   bool isArray;
   U32 arraySize;

   ShaderDataType()
      : varName(String::EmptyString),
      dataConstType(GFXShaderConstType::GFXSCT_Unknown),
      isArray(false),
      arraySize(0)
   {}

   ShaderDataType(GFXShaderConstType constType, String name, bool arrayType = false, U32 size = 0)
      : dataConstType(constType),
      varName(name),
      isArray(arrayType),
      arraySize(size)
   {}
};

class ShaderFunctionArg : public ShaderDataType
{
public:
   bool in;
   bool out;
   bool inout;
   GFXSamplerType samplerType;

   ShaderFunctionArg()
      : ShaderDataType(),
      samplerType(GFXSamplerType::SAMP_Uknown),
      in(false),
      out(false),
      inout(false)
   {}

   ShaderFunctionArg(GFXShaderConstType constType,
      GFXSamplerType inSamplerType,
      String name,
      bool isIn,
      bool isOut,
      bool isInout,
      bool isSampler = false,
      bool arrayType = false,
      U32 size = 0)
      : ShaderDataType(constType, name, arrayType, size),
      samplerType(inSamplerType),
      in(isIn),
      out(isOut),
      inout(isInout)
   {}
};

class ShaderFunction
{
public:
   GFXShaderConstType returnType;
   String name;
   bool isInline;
   Vector<ShaderFunctionArg> arguments;
   String functionBody;
   bool isPrinted;

   ShaderFunction()
      : returnType(GFXShaderConstType::GFXSCT_Unknown),
      name(String::EmptyString),
      functionBody(String::EmptyString),
      isInline(false),
      isPrinted(false)
   {
      VECTOR_SET_ASSOCIATION(arguments);
   }

   ShaderFunction(GFXShaderConstType inConstType, String inName, bool inIsInline)
      : returnType(inConstType),
      name(inName),
      functionBody(String::EmptyString),
      isInline(inIsInline),
      isPrinted(false)
   {
      VECTOR_SET_ASSOCIATION(arguments);
   }

   void setPrinted(bool inPrinted) { isPrinted = inPrinted; }

   void printFunctionHLSL(String& inString, U32 startDepth = 0);
   void printFunctionGLSL(String& inString, bool vert, U32 startDepth = 0);
};


class ShaderStructDataType
{
public:
   GFXShaderSemantic dataSemantic;
   S32 dataResourceNumber;
   String varName;
   GFXShaderConstType dataConstType;

   ShaderStructDataType()
      : dataConstType(GFXShaderConstType::GFXSCT_Unknown),
      varName(String::EmptyString),
      dataSemantic(GFXShaderSemantic::GFXSS_Unknown),
      dataResourceNumber(-1)
   {}

   ShaderStructDataType(GFXShaderConstType constType,
      String name,
      GFXShaderSemantic semanticType,
      S32 resourceNumber = -1)
      : dataConstType(constType),
      varName(name),
      dataSemantic(semanticType),
      dataResourceNumber(resourceNumber)
   {}
};

class ShaderDataStruct
{
protected:
   String structName;
public:
   Vector<ShaderStructDataType*> structDataTypes;
   GFXShaderStructType structType;
   ShaderDataStruct()
      : structType(GFXShaderStructType::GFXSST_Unknown),
      structName(String::EmptyString)
   {
      VECTOR_SET_ASSOCIATION(structDataTypes);
   }

   ShaderDataStruct(GFXShaderStructType inStructType, String inName)
      : structType(inStructType),
      structName(inName)
   {
      VECTOR_SET_ASSOCIATION(structDataTypes);
   }

   // print struct
   void printStructHLSL(String& inString);
};

class ShaderSampler
{
public:
   String shaderName;
   GFXSamplerType type;

   ShaderSampler()
      : shaderName(String::EmptyString),
      type(GFXSamplerType::SAMP_Uknown)
   {}

   ShaderSampler(String name, GFXSamplerType inType)
      : shaderName(name),
      type(inType)
   {}
};

class FileShaderBlueprint
{
public:
   String entryPoint;
   String mShaderLines;
   String entryFunctionBody;

   Vector<ShaderFunction> shaderFunctions;

   FileShaderBlueprint()
      : entryPoint("main"),
      entryFunctionBody(String::EmptyString)
   {
      VECTOR_SET_ASSOCIATION(shaderFunctions);
   }

   FileShaderBlueprint(String entryName)
      : entryPoint(entryName),
      entryFunctionBody(String::EmptyString)
   {
      VECTOR_SET_ASSOCIATION(shaderFunctions);
   }

};

class ShaderBlueprint : public SimObject
{
   typedef SimObject Parent;

protected:
   ///
   struct ShaderStage {
      String mStageName;
      String mGlobal;
      String mPixelShader;
      String mVertexShader;

      ShaderStage()
      {
         mStageName = String::EmptyString;
         mGlobal = String::EmptyString;
         mPixelShader = String::EmptyString;
         mVertexShader = String::EmptyString;
      }

      ShaderStage(String inStageName, String inGlobal, String inPixel, String inVertex)
      {
         mStageName = inStageName;
         mGlobal = inGlobal;
         mPixelShader = inPixel;
         mVertexShader = inVertex;
      }
   };

   Vector<ShaderStage> smShaderStages;

   static Vector<ShaderBlueprint*> smAllShaderData;
   typedef HashTable<String, GFXShaderRef> ShaderCache;
   ShaderCache mShaders;

   StringTableEntry mBluePrintFile;

   String mShaderFileName;

   bool mExportFiles;
   bool mAutoCompile;
   bool mMultiStage;

   void _onFileChanged(const Torque::Path& path) { _reload(); }

   GFXShader* mCompiledShader;
   Vector<GFXShaderMacro> mShaderMacros;

   bool mCorrectSSP;
   bool mRTParams[16];
   bool _checkDefinition(GFXShader* shader);

   S32 mCurStage;

public:

   Vector<ShaderDataStruct*> mShaderDataStructs;
   Vector<String> mShaderSamplers;

   FileShaderBlueprint* mVertexShader;
   FileShaderBlueprint* mPixelShader;

   String mVertexShaderConverted;
   String mPixelShaderConverted;

   bool hasSamplerDef(const String& _samplerName, int& pos) const;
   bool hasRTParamsDef(const int pos) const { return mRTParams[pos]; }

   ShaderBlueprint();
   virtual ~ShaderBlueprint();

   // SimObject
   virtual bool onAdd();
   virtual void onRemove();

   bool initParser(const char* filePath);

   bool initIncludeFileParser(FileShaderBlueprint* inShader, const char* includePath);

   // parse functions
   bool readShaderDataStruct(FileObject& file, String curLine, U32& lineNum);
   bool readFileShaderData(FileShaderBlueprint* inShader, FileObject& file, U32& lineNum);

   GFXShader* _createShader(const Vector<GFXShaderMacro>& macros, S32 shaderStage = -1);

   // Conversion functions
   void exportShaderFiles();
   void convertToHLSL(bool exportFile, S32 stage = -1);
   void convertToGLSL(bool exportFile, S32 stage = -1);

   void processShaderLines(FileShaderBlueprint* inShader, String& convertedShaderString, String inShaderLines, bool isGLSL = false, bool isVert = false);

   // ConsoleObject
   static void initPersistFields();

   GFXShader* getShaderStage(const Vector<GFXShaderMacro>& macros = Vector<GFXShaderMacro>(), String mStageName = String::EmptyString);

   GFXShader* getShader(const Vector<GFXShaderMacro>& macros = Vector<GFXShaderMacro>(), S32 shaderStage = -1);

   bool _reload();

   DECLARE_CONOBJECT(ShaderBlueprint);
};


#endif // !_SHADERBLUEPRINT_H_
