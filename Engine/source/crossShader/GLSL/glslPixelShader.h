#ifndef _GLSLPIXELSHADER_H_
#define _GLSLPIXELSHADER_H_

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

class GLSLPixelShader
{
protected:
   Vector<String> mLines;
   GLSLCrossShader* shader;
public:
   GLSLPixelShader(GLSLCrossShader* shader) : shader(shader) {}
   ~GLSLPixelShader() {}
   
   void addConnect(String type, String name, String target);
   void addOutput(String type, String name, String target);
   void addMainLine(String line);

};

#endif
