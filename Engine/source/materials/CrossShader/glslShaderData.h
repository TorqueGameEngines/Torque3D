#ifndef _GLSLSHADERTDATA_H_
#define _GLSLSHADERTDATA_H_

#ifndef _SIMOBJECT_H_
#include "console/simObject.h"
#endif
#ifndef _TDICTIONARY_H_
#include "core/util/tDictionary.h"
#endif
#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif

#include "core/util/path.h"

struct GLSLInfo
{
   char* type;
   char* name;
   U32 arraySize = 0;
};

class GLSLCrossShader
{
public:
   class GLSLCrossShaderInputList
   {
      GLSLCrossShader* shader;
   protected:
      Vector <GLSLInfo> mInputList;
   public:
      GLSLCrossShaderInputList(GLSLCrossShader* shader) : shader(shader) {}
      ~GLSLCrossShaderInputList() {}

      void addInput(char* type, char* name);
      void print(Stream& stream);
   };

   class GLSLCrossShaderConnectList
   {
      GLSLCrossShader* shader;
   protected:
      Vector <GLSLInfo> mConnectList;
   public:
      GLSLCrossShaderConnectList(GLSLCrossShader* shader) : shader(shader) {}
      ~GLSLCrossShaderConnectList() {}

      void addConnect(char* type, char* name);
      void print(Stream& stream, bool isVShader);
   };

   class GLSLCrossShaderUniformVertList
   {
      GLSLCrossShader* shader;
   protected:
      Vector <GLSLInfo> mUniformVertList;
   public:
      GLSLCrossShaderUniformVertList(GLSLCrossShader* shader) : shader(shader) {}
      ~GLSLCrossShaderUniformVertList() {}

      void addVertUniform(char* type, char* name);
      void print(Stream& stream);
   };

   class GLSLCrossShaderUniformPixList
   {
      GLSLCrossShader* shader;
   public:
      Vector <GLSLInfo> mUniformPixList;
      GLSLCrossShaderUniformPixList(GLSLCrossShader* shader) : shader(shader) {}
      ~GLSLCrossShaderUniformPixList() {}

      void addPixUniform(char* type, char* name);
      void print(Stream& stream);
   };

   class GLSLCrossShaderPixOutputs
   {
      GLSLCrossShader* shader;
   protected:
      Vector <GLSLInfo> mPixOutputList;
   public:
      GLSLCrossShaderPixOutputs(GLSLCrossShader* shader) : shader(shader) {}
      ~GLSLCrossShaderPixOutputs() {}

      void addPixOutput(char* type, char* name);
      void print(Stream& stream);
   };

   class GLSLCrossShaderVertMain
   {
      GLSLCrossShader* shader;
   protected:
      Vector<String> mLines;
   public:
      GLSLCrossShaderVertMain(GLSLCrossShader* shader) : shader(shader) {}
      ~GLSLCrossShaderVertMain() {}
      void addLine(String line);
      void print(Stream& stream, bool useGLPos);
   };

   class GLSLCrossShaderPixMain
   {
      GLSLCrossShader* shader;
   protected:
      Vector<String> mLines;
   public:
      GLSLCrossShaderPixMain(GLSLCrossShader* shader) : shader(shader) {}
      ~GLSLCrossShaderPixMain() {}
      void addLine(String line);
      void print(Stream& stream);
   };

protected:
   // required
   GLSLCrossShaderInputList*         mGLSLInList;
   GLSLCrossShaderConnectList*       mGLSLConnList;
   GLSLCrossShaderUniformVertList*   mGLSLUniVertList;
   GLSLCrossShaderUniformPixList*    mGLSLUniPixList;
   GLSLCrossShaderPixOutputs*        mGLSLPixOut;
   GLSLCrossShaderVertMain*          mGLSLVertMain;
   GLSLCrossShaderPixMain*           mGLSLPixMain;


   bool mUseMulDef;
   // vertex inputs
   bool mUseGLPosition;

   void _printVertexShader(Stream& stream);
   void _printPixelShader(Stream& stream);

public:
   GLSLCrossShader();
   ~GLSLCrossShader();

   void processInput(const char* inputBuff);
   void processConnect(const char* connBuff);
   void processVertUniforms(const char* vertUni);
   void processPixUniforms(const char* pixUni);
   void processPixOutputs(const char* pixOut);
   void processVertMainLine(const char* vLine);
   void processPixelMainLine(const char* pLine);

   // change to glsl standard functions.
   void checkMainLine(String& line, bool isVert);
   char* checkType(char* type);
   void checkName(char* name);

   // finally process shader:
   void generateShader(char* shaderName);

};


#endif
