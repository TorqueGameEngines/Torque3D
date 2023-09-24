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

class FileShaderBlueprint
{
public:
   String entryPoint;

   String mShaderLines;

   String entryFunctionBody;

   FileShaderBlueprint()
      : entryPoint("main"),
      entryFunctionBody(String::EmptyString)
   {
   }

   FileShaderBlueprint(String entryName)
      : entryPoint(entryName),
      entryFunctionBody(String::EmptyString)
   {
   }

};

class ShaderBlueprint : public SimObject
{
   typedef SimObject Parent;

protected:
   ///
   static Vector<ShaderBlueprint*> smAllShaderData;
   typedef HashTable<String, GFXShaderRef> ShaderCache;
   ShaderCache mShaders;

   StringTableEntry mBluePrintFile;

   String mShaderFileName;

   bool mExportFiles;

   void _onFileChanged(const Torque::Path& path) { _reload(); }

   GFXShader* mCompiledShader;
   Vector<GFXShaderMacro> mShaderMacros;

   bool mCorrectSSP;
   bool mRTParams[16];

   bool _checkDefinition(GFXShader* shader);
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

   GFXShader* _createShader(const Vector<GFXShaderMacro>& macros);

   // Conversion functions
   void convertShaders();
   void convertToHLSL(bool exportFile);
   void convertToGLSL(bool exportFile);

   // ConsoleObject
   static void initPersistFields();

   GFXShader* getShader(const Vector<GFXShaderMacro>& macros = Vector<GFXShaderMacro>());

   bool _reload();

   DECLARE_CONOBJECT(ShaderBlueprint);
};


#endif // !_SHADERBLUEPRINT_H_
