#ifndef _HLSLSHADERTDATA_H_
#define _HLSLSHADERTDATA_H_

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

struct HLSLInfo
{
   char* type;
   char* name;
   char* target;
   String regNum;
   U32 arraySize = 0;
};

struct SourceInfo
{
   char* name;
   char* type;
   bool sampler = false;
   bool ModelMat = false;
   bool ModelViewMat = false;
   bool ModelViewProjMat = false;
   bool ViewMat = false;
   bool ViewProjMat = false;
   bool ProjMat = false;
   bool Time = false;
};

class HLSLCrossShader
{
public:
   class HLSLCrossShaderInputList
   {
      HLSLCrossShader* shader;
   protected:
      Vector <HLSLInfo> mInputList;
   public:
      HLSLCrossShaderInputList(HLSLCrossShader* shader) : shader(shader) {}
      ~HLSLCrossShaderInputList() {}

      void addInput(char* type, char* name, char* target);
      void print(Stream& stream);
   };

   class HLSLCrossShaderConnectList
   {
      HLSLCrossShader* shader;
   protected:
      Vector <HLSLInfo> mConnectList;
   public:
      HLSLCrossShaderConnectList(HLSLCrossShader* shader) : shader(shader) {}
      ~HLSLCrossShaderConnectList() {}

      void addConnect(char* type, char* name, char* target);
      void print(Stream& stream);
   };

   class HLSLCrossShaderUniformVertList
   {
      HLSLCrossShader* shader;
   protected:
      U32 cReg = 0;
      U32 sReg = 0;
      U32 tReg = 0;

   public:
      Vector <HLSLInfo> mUniformVertList;
      HLSLCrossShaderUniformVertList(HLSLCrossShader* shader) : shader(shader) {}
      ~HLSLCrossShaderUniformVertList() {}

      void checkUniform(HLSLInfo& info);
      void addVertUniform(char* type, char* name);
      void print(Stream& stream);
      
   };

   class HLSLCrossShaderUniformPixList
   {
      HLSLCrossShader* shader;
   protected:
      U32 cReg = 0;
      U32 sReg = 0;
      U32 tReg = 0;
      
   public:
      Vector <HLSLInfo> mUniformPixList;
      HLSLCrossShaderUniformPixList(HLSLCrossShader* shader) : shader(shader) {}
      ~HLSLCrossShaderUniformPixList() {}

      void checkUniform(HLSLInfo& in);
      void addPixUniform(char* type, char* name);
      void print(Stream& stream);
   };

   class HLSLCrossShaderPixOutputs
   {
      HLSLCrossShader* shader;
   protected:
      Vector <HLSLInfo> mPixOutputList;
   public:
      HLSLCrossShaderPixOutputs(HLSLCrossShader* shader) : shader(shader) {}
      ~HLSLCrossShaderPixOutputs() {}

      void addPixOutput(char* type, char* name, char* target);
      void print(Stream& stream);
   };

   class HLSLCrossShaderVertMain
   {
      HLSLCrossShader* shader;
   protected:
      Vector<String> mLines;
   public:
      HLSLCrossShaderVertMain(HLSLCrossShader* shader) : shader(shader) {}
      ~HLSLCrossShaderVertMain() {}
      void addLine(String line);
      void printHeader(Stream& stream);
      void print(Stream& stream);
   };

   class HLSLCrossShaderPixMain
   {
      HLSLCrossShader* shader;
   protected:
      Vector<String> mLines;
   public:
      HLSLCrossShaderPixMain(HLSLCrossShader* shader) : shader(shader) {}
      ~HLSLCrossShaderPixMain() {}
      void addLine(String line);
      void printHeader(Stream& stream);
      void print(Stream& stream);
   };

protected:
   // required
   HLSLCrossShaderInputList* mHLSLInList;
   HLSLCrossShaderConnectList* mHLSLConnList;
   HLSLCrossShaderUniformVertList* mHLSLUniVertList;
   HLSLCrossShaderUniformPixList* mHLSLUniPixList;
   HLSLCrossShaderPixOutputs* mHLSLPixOut;
   HLSLCrossShaderVertMain* mHLSLVertMain;
   HLSLCrossShaderPixMain* mHLSLPixMain;
   //
   bool samplersDefined;
   U32 samplers;
   bool isMat;
   U32 matID;

   //shader printers
   char* shaderObjName;
   void _printVertexShader(Stream& stream);
   void _printPixelShader(Stream& stream);

   // source file printers
   void _buildSourceInfo();
   void _printSourceFile(Stream& stream);
   void _printOnAdd(Stream& stream);
   void _printStateBlock(Stream& stream);
   void _printRenderObject(Stream& stream);
   void _printIncludesSource(Stream& stream);

   // header file printers
   void _printHeaderFile(Stream& stream);
   
   Vector <SourceInfo> mSourceList;
public:
   HLSLCrossShader();
   ~HLSLCrossShader();

   void processInput(const char* inputBuff);
   void processConnect(const char* connBuff);
   void processVertUniforms(const char* vertUni);
   void processPixUniforms(const char* pixUni);
   void processPixOutputs(const char* pixOut);
   void processVertMainLine(const char* vLine);
   void processPixelMainLine(const char* pLine);

   void checkMainLine(String& line, bool isVert);
   // process shader:
   void generateShader(char* shaderName);

   // print out source side helper.
   void generateSource(char* shaderName);

   // print out script side helper.
   void genereateScript(char* shaderName);


};


#endif
