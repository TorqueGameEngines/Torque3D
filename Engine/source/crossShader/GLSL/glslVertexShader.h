#ifndef _GLSLVERTEXSHADER_H_
#define _GLSLVERTEXSHADER_H_

#ifndef _SIMOBJECT_H_
#include "console/simObject.h"
#endif
#ifndef _TDICTIONARY_H_
#include "core/util/tDictionary.h"
#endif
#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif
#ifndef _GLSLSHADERDATA_H_
#include "glslShaderData.h"
#endif

#include "core/util/path.h"

class GLSLVertexShader
{
protected:
   Vector<String> mLines;
   GLSLCrossShader* shader;
public:
   GLSLVertexShader(GLSLCrossShader* shader) : shader(shader) {}
   ~GLSLVertexShader() {}

   void addInput(String type,String name, String target);
   void addConnect(String type, String name, String target);
   void addMainLine(String line);

};

#endif
