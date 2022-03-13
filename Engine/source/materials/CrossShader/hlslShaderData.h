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
      Vector <HLSLInfo> mUniformVertList;
   public:
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

   // matrix inputs model
   bool mUseModelMat;
   bool mUseModelViewMat;
   bool mUseModelViewProjMat;
   // matrix inputs view
   bool mUseViewMat;
   bool mUseViewProjMat;
   // matrix inputs proj
   bool mUseProjMat;
   // time
   bool mUseTime;

   void _printVertexShader(Stream& stream);
   void _printPixelShader(Stream& stream);

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
   // should be hlsl already are these needed?
   //char* checkType(char* type);
   //void checkName(char* name);

   // finally process shader:
   void generateShader(char* shaderName);

};


#endif
