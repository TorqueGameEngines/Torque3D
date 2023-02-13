#ifndef _CONSOLFUNCTIONS_H_
#define _CONSOLFUNCTIONS_H_

#ifndef _STRINGFUNCTIONS_H_
#include "core/strings/stringFunctions.h"
#endif

bool isInt(const char* str);

bool isFloat(const char* str);

bool isValidIP(const char* ip);

bool isValidPort(U16 port);

void gotoWebPage(const char* address);

bool getDocsURL(void* obj, const char* array, const char* data);
const char* getDocsLink(const char* filename, U32 lineNumber);

#define docsURL addGroup("Ungrouped");\
                addProtectedField("docsURL", TypeBool, Offset(mDocsClick, ConsoleObject), &getDocsURL, &defaultProtectedGetFn, getDocsLink(__FILE__,__LINE__), AbstractClassRep::FieldFlags::FIELD_ComponentInspectors);\
                endGroup("Ungrouped")
#endif
