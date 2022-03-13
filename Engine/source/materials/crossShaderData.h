#ifndef _CROSSSHADERTDATA_H_
#define _CROSSSHADERTDATA_H_

#ifndef _SIMOBJECT_H_
#include "console/simObject.h"
#endif
#ifndef _TDICTIONARY_H_
#include "core/util/tDictionary.h"
#endif
#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif

#ifndef _GLSLSHADERTDATA_H_
#include "CrossShader/glslShaderData.h"
#endif

#ifndef _HLSLSHADERTDATA_H_
#include "CrossShader/hlslShaderData.h"
#endif

#include "core/util/path.h"
#include "core/fileObject.h"

class CrossShaderData : public SimObject
{
   typedef SimObject Parent;

protected:

   GLSLCrossShader* mGLSLShader;
   HLSLCrossShader* mHLSLShader;

   StringTableEntry mCrossShaderFile;

   void readBlueprint(const Torque::Path& filePath);

   char* StripChars(const char* buffer);

public:

   CrossShaderData();

   // SimObject
   virtual bool onAdd();
   virtual void onRemove();

   // ConsoleObject
   static void initPersistFields();
   DECLARE_CONOBJECT(CrossShaderData);

};

#endif
