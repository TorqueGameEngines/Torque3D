//-----------------------------------------------------------------------------
// Copyright (c) 2013 GarageGames, LLC
// Copyright (c) 2015 Faust Logic, Inc.
// Copyright (c) 2021 TGEMIT Authors & Contributors
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

#include "platform/platform.h"
#include "console/console.h"

#include "console/ast.h"
#include "core/tAlgorithm.h"

#include "core/strings/findMatch.h"
#include "core/strings/stringUnit.h"
#include "console/consoleInternal.h"
#include "core/stream/fileStream.h"
#include "console/compiler.h"

#include "console/simBase.h"
#include "console/telnetDebugger.h"
#include "sim/netStringTable.h"
#include "console/ICallMethod.h"
#include "console/stringStack.h"
#include "util/messaging/message.h"
#include "core/frameAllocator.h"

#include "console/returnBuffer.h"
#include "console/consoleValueStack.h"

#ifndef TORQUE_TGB_ONLY
#include "materials/materialDefinition.h"
#include "materials/materialManager.h"
#endif

using namespace Compiler;

enum EvalConstants
{
   MaxStackSize = 1024,
   FieldBufferSizeString = 2048,
   FieldBufferSizeNumeric = 128,
   MethodOnComponent = -2
};

/// Frame data for a foreach/foreach$ loop.
struct IterStackRecord
{
   /// If true, this is a foreach$ loop; if not, it's a foreach loop.
   bool mIsStringIter;

   /// The iterator variable.
   Dictionary::Entry* mVariable;

   /// Information for an object iterator loop.
   struct ObjectPos
   {
      /// The set being iterated over.
      SimSet* mSet;

      /// Current index in the set.
      U32 mIndex;
   };

   /// Information for a string iterator loop.
   struct StringPos
   {
      /// The raw string data on the string stack.
      const char* mString;

      /// Current parsing position.
      U32 mIndex;
   };
   union
   {
      ObjectPos mObj;
      StringPos mStr;
   } mData;
};

ConsoleValueStack<4096> gCallStack;

StringStack STR;

U32 _FLT = 0;     ///< Stack pointer for floatStack.
U32 _UINT = 0;    ///< Stack pointer for intStack.
U32 _ITER = 0;    ///< Stack pointer for iterStack.

IterStackRecord iterStack[MaxStackSize];

F64 floatStack[MaxStackSize];
S64 intStack[MaxStackSize];

char curFieldArray[256];
char prevFieldArray[256];

namespace Con
{
   // Current script file name and root, these are registered as
   // console variables.
   extern StringTableEntry gCurrentFile;
   extern StringTableEntry gCurrentRoot;
}

namespace Con
{
   const char *getNamespaceList(Namespace *ns)
   {
      U32 size = 1;
      Namespace * walk;
      for (walk = ns; walk; walk = walk->mParent)
         size += dStrlen(walk->mName) + 4;
      char *ret = Con::getReturnBuffer(size);
      ret[0] = 0;
      for (walk = ns; walk; walk = walk->mParent)
      {
         dStrcat(ret, walk->mName, size);
         if (walk->mParent)
            dStrcat(ret, " -> ", size);
      }
      return ret;
   }
}

// Gets a component of an object's field value or a variable and returns it
// in val.
static void getFieldComponent(SimObject* object, StringTableEntry field, const char* array, StringTableEntry subField, char val[])
{
   const char* prevVal = NULL;

   // Grab value from object.
   if (object && field)
      prevVal = object->getDataField(field, array);

   // Otherwise, grab from the string stack. The value coming in will always
   // be a string because that is how multicomponent variables are handled.
   else
      prevVal = STR.getStringValue();

   // Make sure we got a value.
   if (prevVal && *prevVal)
   {
      static const StringTableEntry xyzw[] =
      {
         StringTable->insert("x"),
         StringTable->insert("y"),
         StringTable->insert("z"),
         StringTable->insert("w")
      };

      static const StringTableEntry rgba[] =
      {
         StringTable->insert("r"),
         StringTable->insert("g"),
         StringTable->insert("b"),
         StringTable->insert("a")
      };

      // Translate xyzw and rgba into the indexed component 
      // of the variable or field.
      if (subField == xyzw[0] || subField == rgba[0])
         dStrcpy(val, StringUnit::getUnit(prevVal, 0, " \t\n"), 128);

      else if (subField == xyzw[1] || subField == rgba[1])
         dStrcpy(val, StringUnit::getUnit(prevVal, 1, " \t\n"), 128);

      else if (subField == xyzw[2] || subField == rgba[2])
         dStrcpy(val, StringUnit::getUnit(prevVal, 2, " \t\n"), 128);

      else if (subField == xyzw[3] || subField == rgba[3])
         dStrcpy(val, StringUnit::getUnit(prevVal, 3, " \t\n"), 128);

      else
         val[0] = 0;
   }
   else
      val[0] = 0;
}

// Sets a component of an object's field value based on the sub field. 'x' will
// set the first field, 'y' the second, and 'z' the third.
static void setFieldComponent(SimObject* object, StringTableEntry field, const char* array, StringTableEntry subField)
{
   // Copy the current string value
   char strValue[1024];
   dStrncpy(strValue, STR.getStringValue(), 1024);

   char val[1024] = "";
   const char* prevVal = NULL;

   // Set the value on an object field.
   if (object && field)
      prevVal = object->getDataField(field, array);

   // Set the value on a variable.
   else if (gEvalState.currentVariable)
      prevVal = gEvalState.getStringVariable();

   // Ensure that the variable has a value
   if (!prevVal)
      return;

   static const StringTableEntry xyzw[] =
   {
      StringTable->insert("x"),
      StringTable->insert("y"),
      StringTable->insert("z"),
      StringTable->insert("w")
   };

   static const StringTableEntry rgba[] =
   {
      StringTable->insert("r"),
      StringTable->insert("g"),
      StringTable->insert("b"),
      StringTable->insert("a")
   };

   // Insert the value into the specified 
   // component of the string.
   if (subField == xyzw[0] || subField == rgba[0])
      dStrcpy(val, StringUnit::setUnit(prevVal, 0, strValue, " \t\n"), 128);

   else if (subField == xyzw[1] || subField == rgba[1])
      dStrcpy(val, StringUnit::setUnit(prevVal, 1, strValue, " \t\n"), 128);

   else if (subField == xyzw[2] || subField == rgba[2])
      dStrcpy(val, StringUnit::setUnit(prevVal, 2, strValue, " \t\n"), 128);

   else if (subField == xyzw[3] || subField == rgba[3])
      dStrcpy(val, StringUnit::setUnit(prevVal, 3, strValue, " \t\n"), 128);

   if (val[0] != 0)
   {
      // Update the field or variable.
      if (object && field)
         object->setDataField(field, 0, val);
      else if (gEvalState.currentVariable)
         gEvalState.setStringVariable(val);
   }
}

//------------------------------------------------------------

F64 consoleStringToNumber(const char *str, StringTableEntry file, U32 line)
{
   F64 val = dAtof(str);
   if (val != 0)
      return val;
   else if (!dStricmp(str, "true"))
      return 1;
   else if (!dStricmp(str, "false"))
      return 0;
   else if (file)
   {
      Con::warnf(ConsoleLogEntry::General, "%s (%d): string always evaluates to 0.", file, line);
      return 0;
   }
   return 0;
}

//------------------------------------------------------------

namespace Con
{
   ReturnBuffer retBuffer;

   char *getReturnBuffer(U32 bufferSize)
   {
      return retBuffer.getBuffer(bufferSize);
   }

   char *getReturnBuffer(const char *stringToCopy)
   {
      U32 len = dStrlen(stringToCopy) + 1;
      char *ret = retBuffer.getBuffer(len);
      dMemcpy(ret, stringToCopy, len);
      return ret;
   }

   char* getReturnBuffer(const String& str)
   {
      const U32 size = str.size();
      char* ret = retBuffer.getBuffer(size);
      dMemcpy(ret, str.c_str(), size);
      return ret;
   }

   char* getReturnBuffer(const StringBuilder& str)
   {
      char* buffer = Con::getReturnBuffer(str.length() + 1);
      str.copy(buffer);
      buffer[str.length()] = '\0';

      return buffer;
   }

   char *getArgBuffer(U32 bufferSize)
   {
      return STR.getArgBuffer(bufferSize);
   }

   char *getFloatArg(F64 arg)
   {
      char *ret = STR.getArgBuffer(32);
      dSprintf(ret, 32, "%g", arg);
      return ret;
   }

   char *getIntArg(S32 arg)
   {
      char *ret = STR.getArgBuffer(32);
      dSprintf(ret, 32, "%d", arg);
      return ret;
   }

   char* getBoolArg(bool arg)
   {
      char *ret = STR.getArgBuffer(32);
      dSprintf(ret, 32, "%d", arg);
      return ret;
   }

   char *getStringArg(const char *arg)
   {
      U32 len = dStrlen(arg) + 1;
      char *ret = STR.getArgBuffer(len);
      dMemcpy(ret, arg, len);
      return ret;
   }

   char* getStringArg(const String& arg)
   {
      const U32 size = arg.size();
      char* ret = STR.getArgBuffer(size);
      dMemcpy(ret, arg.c_str(), size);
      return ret;
   }
}

//------------------------------------------------------------

void ExprEvalState::setCurVarName(StringTableEntry name)
{
   if (name[0] == '$')
      currentVariable = globalVars.lookup(name);
   else if (getStackDepth() > 0)
      currentVariable = getCurrentFrame().lookup(name);
   if (!currentVariable && gWarnUndefinedScriptVariables)
      Con::warnf(ConsoleLogEntry::Script, "Variable referenced before assignment: %s", name);
}

void ExprEvalState::setCurVarNameCreate(StringTableEntry name)
{
   if (name[0] == '$')
      currentVariable = globalVars.add(name);
   else if (getStackDepth() > 0)
      currentVariable = getCurrentFrame().add(name);
   else
   {
      currentVariable = NULL;
      Con::warnf(ConsoleLogEntry::Script, "Accessing local variable in global scope... failed: %s", name);
   }
}

//------------------------------------------------------------

S32 ExprEvalState::getIntVariable()
{
   return currentVariable ? currentVariable->getIntValue() : 0;
}

F64 ExprEvalState::getFloatVariable()
{
   return currentVariable ? currentVariable->getFloatValue() : 0;
}

const char *ExprEvalState::getStringVariable()
{
   return currentVariable ? currentVariable->getStringValue() : "";
}

//------------------------------------------------------------

void ExprEvalState::setIntVariable(S32 val)
{
   AssertFatal(currentVariable != NULL, "Invalid evaluator state - trying to set null variable!");
   currentVariable->setIntValue(val);
}

void ExprEvalState::setFloatVariable(F64 val)
{
   AssertFatal(currentVariable != NULL, "Invalid evaluator state - trying to set null variable!");
   currentVariable->setFloatValue(val);
}

void ExprEvalState::setStringVariable(const char *val)
{
   AssertFatal(currentVariable != NULL, "Invalid evaluator state - trying to set null variable!");
   currentVariable->setStringValue(val);
}

//-----------------------------------------------------------------------------

U32 gExecCount = 0;
void CodeBlock::exec(U32 ip, const char* functionName, Namespace* thisNamespace, U32 argc, ConsoleValue* argv, bool noCalls, StringTableEntry packageName, ConsoleValue& returnValue, S32 setFrame)
{
#ifdef TORQUE_DEBUG
   U32 stackStart = STR.mStartStackSize;
   gExecCount++;
#endif

   const dsize_t TRACE_BUFFER_SIZE = 1024;
   static char traceBuffer[TRACE_BUFFER_SIZE];
   U32 i;

   U32 iterDepth = 0;

   incRefCount();
   F64* curFloatTable;
   char* curStringTable;
   S32 curStringTableLen = 0; //clint to ensure we dont overwrite it
   STR.clearFunctionOffset();
   StringTableEntry thisFunctionName = NULL;
   bool popFrame = false;
   if (argv)
   {
      // assume this points into a function decl:
      U32 fnArgc = code[ip + 2 + 6];
      U32 regCount = code[ip + 2 + 7];
      thisFunctionName = CodeToSTE(code, ip);
      S32 wantedArgc = getMin(argc - 1, fnArgc); // argv[0] is func name
      if (gEvalState.traceOn)
      {
         traceBuffer[0] = 0;
         dStrcat(traceBuffer, "Entering ", TRACE_BUFFER_SIZE);
         if (packageName)
         {
            dStrcat(traceBuffer, "[", TRACE_BUFFER_SIZE);
            dStrcat(traceBuffer, packageName, TRACE_BUFFER_SIZE);
            dStrcat(traceBuffer, "]", TRACE_BUFFER_SIZE);
         }
         if (thisNamespace && thisNamespace->mName)
         {
            dSprintf(traceBuffer + dStrlen(traceBuffer), sizeof(traceBuffer) - dStrlen(traceBuffer),
               "%s::%s(", thisNamespace->mName, thisFunctionName);
         }
         else
         {
            dSprintf(traceBuffer + dStrlen(traceBuffer), sizeof(traceBuffer) - dStrlen(traceBuffer),
               "%s(", thisFunctionName);
         }
         for (i = 0; i < wantedArgc; i++)
         {
            dStrcat(traceBuffer, argv[i + 1].getString(), TRACE_BUFFER_SIZE);
            if (i != wantedArgc - 1)
               dStrcat(traceBuffer, ", ", TRACE_BUFFER_SIZE);
         }
         dStrcat(traceBuffer, ")", TRACE_BUFFER_SIZE);
         Con::printf("%s", traceBuffer);
      }
      gEvalState.pushFrame(thisFunctionName, thisNamespace, regCount);
      popFrame = true;
      for (i = 0; i < wantedArgc; i++)
      {
         S32 reg = code[ip + (2 + 6 + 1 + 1) + i];
         ConsoleValue& value = argv[i + 1];
         switch (value.getType())
         {
         case ConsoleValueType::cvString:
            gEvalState.setLocalStringVariable(reg, value.getString(), dStrlen(value.getString()));
            break;
         case ConsoleValueType::cvInteger:
            gEvalState.setLocalIntVariable(reg, value.getInt());
            break;
         case ConsoleValueType::cvFloat:
            gEvalState.setLocalFloatVariable(reg, value.getFloat());
            break;
         case ConsoleValueType::cvSTEntry:
            gEvalState.setLocalStringTableEntryVariable(reg, value.getString());
            break;
         default:
            AssertFatal(false, avar("Invalid local variable type. Type was: %i", value.getType()));
         }
      }
      ip = ip + fnArgc + (2 + 6 + 1 + 1);
      curFloatTable = functionFloats;
      curStringTable = functionStrings;
      curStringTableLen = functionStringsMaxLen;
   }
   else
   {
      curFloatTable = globalFloats;
      curStringTable = globalStrings;
      curStringTableLen = globalStringsMaxLen;

      // Do we want this code to execute using a new stack frame?
      if (setFrame < 0)
      {
         gEvalState.pushFrame(NULL, NULL, 0);
         gCallStack.pushFrame(0);
         popFrame = true;
      }
      else if (!gEvalState.stack.empty())
      {
         // We want to copy a reference to an existing stack frame
         // on to the top of the stack.  Any change that occurs to
         // the locals during this new frame will also occur in the
         // original frame.
         S32 stackIndex = gEvalState.stack.size() - setFrame - 1;
         gEvalState.pushFrameRef(stackIndex);
         popFrame = true;
      }
   }

   // Grab the state of the telenet debugger here once
   // so that the push and pop frames are always balanced.
   const bool telDebuggerOn = TelDebugger && TelDebugger->isConnected();
   if (telDebuggerOn && setFrame < 0)
      TelDebugger->pushStackFrame();

   StringTableEntry var, objParent;
   U32 failJump;
   StringTableEntry fnName;
   StringTableEntry fnNamespace, fnPackage;

   static const U32 objectCreationStackSize = 32;
   U32 objectCreationStackIndex = 0;
   struct {
      SimObject* newObject;
      U32 failJump;
   } objectCreationStack[objectCreationStackSize];

   SimObject* currentNewObject = 0;
   StringTableEntry prevField = NULL;
   StringTableEntry curField = NULL;
   SimObject* prevObject = NULL;
   SimObject* curObject = NULL;
   SimObject* saveObject = NULL;
   Namespace::Entry* nsEntry;
   Namespace* ns;
   const char* curFNDocBlock = NULL;
   const char* curNSDocBlock = NULL;
   const S32 nsDocLength = 128;
   char nsDocBlockClass[nsDocLength];

   S32 callArgc;
   ConsoleValue* callArgv;

   static char curFieldArray[256];
   static char prevFieldArray[256];

   CodeBlock* saveCodeBlock = smCurrentCodeBlock;
   smCurrentCodeBlock = this;
   if (this->name)
   {
      Con::gCurrentFile = this->name;
      Con::gCurrentRoot = this->modPath;
   }
   const char* val;
   S32 reg;

   // The frame temp is used by the variable accessor ops (OP_SAVEFIELD_* and
   // OP_LOADFIELD_*) to store temporary values for the fields.
   static S32 VAL_BUFFER_SIZE = 1024;
   FrameTemp<char> valBuffer(VAL_BUFFER_SIZE);

   for (;;)
   {
      U32 instruction = code[ip++];
   breakContinue:
      switch (instruction)
      {
      case OP_FUNC_DECL:
         if (!noCalls)
         {
            fnName = CodeToSTE(code, ip);
            fnNamespace = CodeToSTE(code, ip + 2);
            fnPackage = CodeToSTE(code, ip + 4);
            bool hasBody = (code[ip + 6] & 0x01) != 0;
            U32 lineNumber = code[ip + 6] >> 1;

            Namespace::unlinkPackages();
            if (fnNamespace == NULL && fnPackage == NULL)
               ns = Namespace::global();
            else
               ns = Namespace::find(fnNamespace, fnPackage);
            ns->addFunction(fnName, this, hasBody ? ip : 0);// if no body, set the IP to 0
            if (curNSDocBlock)
            {
               if (fnNamespace == StringTable->lookup(nsDocBlockClass))
               {
                  char* usageStr = dStrdup(curNSDocBlock);
                  usageStr[dStrlen(usageStr)] = '\0';
                  ns->mUsage = usageStr;
                  ns->mCleanUpUsage = true;
                  curNSDocBlock = NULL;
               }
            }
            Namespace::relinkPackages();

            // If we had a docblock, it's definitely not valid anymore, so clear it out.
            curFNDocBlock = NULL;

            //Con::printf("Adding function %s::%s (%d)", fnNamespace, fnName, ip);
         }
         ip = code[ip + 7];
         break;

      case OP_CREATE_OBJECT:
      {
         // Read some useful info.
         objParent = CodeToSTE(code, ip);
         bool isDataBlock = code[ip + 2];
         bool isInternal = code[ip + 3];
         bool isSingleton = code[ip + 4];
         U32  lineNumber = code[ip + 5];
         failJump = code[ip + 6];

         // If we don't allow calls, we certainly don't allow creating objects!
         // Moved this to after failJump is set. Engine was crashing when
         // noCalls = true and an object was being created at the beginning of
         // a file. ADL.
         if (noCalls)
         {
            ip = failJump;
            break;
         }

         // Push the old info to the stack
         //Assert( objectCreationStackIndex < objectCreationStackSize );
         objectCreationStack[objectCreationStackIndex].newObject = currentNewObject;
         objectCreationStack[objectCreationStackIndex++].failJump = failJump;

         // Get the constructor information off the stack.
         gCallStack.argvc(NULL, callArgc, &callArgv);
         AssertFatal(callArgc - 3 >= 0, avar("Call Arg needs at least 3, only has %d", callArgc));
         const char* objectName = callArgv[2].getString();

         // Con::printf("Creating object...");

         // objectName = argv[1]...
         currentNewObject = NULL;

         // Are we creating a datablock? If so, deal with case where we override
         // an old one.
         if (isDataBlock)
         {
            // Con::printf("  - is a datablock");

            // Find the old one if any.
            SimObject* db = Sim::getDataBlockGroup()->findObject(objectName);

            // Make sure we're not changing types on ourselves...
            if (db && dStricmp(db->getClassName(), callArgv[1].getString()))
            {
               Con::errorf(ConsoleLogEntry::General, "Cannot re-declare data block %s with a different class.", objectName);
               ip = failJump;
               gCallStack.popFrame();
               break;
            }

            // If there was one, set the currentNewObject and move on.
            if (db)
               currentNewObject = db;
         }
         else if (!isInternal)
         {
            AbstractClassRep* rep = AbstractClassRep::findClassRep(objectName);
            if (rep != NULL)
            {
               Con::errorf(ConsoleLogEntry::General, "%s: Cannot name object [%s] the same name as a script class.",
                  getFileLine(ip), objectName);
               ip = failJump;
               gCallStack.popFrame();
               break;
            }

            SimObject* obj = Sim::findObject((const char*)objectName);
            if (obj)
            {
               if (isSingleton)
               {
                  // Make sure we're not trying to change types
                  if (dStricmp(obj->getClassName(), callArgv[1].getString()) != 0)
                  {
                     Con::errorf(ConsoleLogEntry::General, "%s: Cannot re-declare object [%s] with a different class [%s] - was [%s].",
                        getFileLine(ip), objectName, callArgv[1].getString(), obj->getClassName());
                     ip = failJump;
                     gCallStack.popFrame();
                     break;
                  }

                  // We're creating a singleton, so use the found object instead of creating a new object.
                  currentNewObject = obj;
                  Con::warnf("%s: Singleton Object was already created with name %s. Using existing object.",
                     getFileLine(ip), objectName);
               }
            }
         }

         gCallStack.popFrame();

         if (!currentNewObject)
         {
            // Well, looks like we have to create a new object.
            ConsoleObject* object = ConsoleObject::create(callArgv[1].getString());

            // Deal with failure!
            if (!object)
            {
               Con::errorf(ConsoleLogEntry::General, "%s: Unable to instantiate non-conobject class %s.", getFileLine(ip - 1), callArgv[1].getString());
               ip = failJump;
               break;
            }

            // Do special datablock init if appropros
            if (isDataBlock)
            {
               SimDataBlock* dataBlock = dynamic_cast<SimDataBlock*>(object);
               if (dataBlock)
               {
                  dataBlock->assignId();
               }
               else
               {
                  // They tried to make a non-datablock with a datablock keyword!
                  Con::errorf(ConsoleLogEntry::General, "%s: Unable to instantiate non-datablock class %s.", getFileLine(ip - 1), callArgv[1].getString());

                  // Clean up...
                  delete object;
                  ip = failJump;
                  break;
               }
            }

            // Finally, set currentNewObject to point to the new one.
            currentNewObject = dynamic_cast<SimObject*>(object);

            // Deal with the case of a non-SimObject.
            if (!currentNewObject)
            {
               Con::errorf(ConsoleLogEntry::General, "%s: Unable to instantiate non-SimObject class %s.", getFileLine(ip - 1), callArgv[1].getString());
               delete object;
               ip = failJump;
               break;
            }

            // Set the declaration line
            currentNewObject->setDeclarationLine(lineNumber);

            // Set the file that this object was created in
            currentNewObject->setFilename(this->name);

            // Does it have a parent object? (ie, the copy constructor : syntax, not inheriance)
            if (*objParent)
            {
               // Find it!
               SimObject* parent;
               if (Sim::findObject(objParent, parent))
               {
                  // Con::printf(" - Parent object found: %s", parent->getClassName());

                  currentNewObject->setCopySource(parent);
                  currentNewObject->assignFieldsFrom(parent);

                  // copy any substitution statements
                  SimDataBlock* parent_db = dynamic_cast<SimDataBlock*>(parent);
                  if (parent_db)
                  {
                     SimDataBlock* currentNewObject_db = dynamic_cast<SimDataBlock*>(currentNewObject);
                     if (currentNewObject_db)
                        currentNewObject_db->copySubstitutionsFrom(parent_db);
                  }
               }
               else
               {
                  Con::errorf(ConsoleLogEntry::General, "%s: Unable to find parent object %s for %s.", getFileLine(ip - 1), objParent, callArgv[1].getString());
                  delete object;
                  currentNewObject = NULL;
                  ip = failJump;
                  break;
               }
            }

            // If a name was passed, assign it.
            if (objectName[0])
            {
               if (!isInternal)
                  currentNewObject->assignName(objectName);
               else
                  currentNewObject->setInternalName(objectName);

               // Set the original name
               currentNewObject->setOriginalName( objectName );
            }

            // Do the constructor parameters.
            if (!currentNewObject->processArguments(callArgc - 3, callArgv + 3))
            {
               delete currentNewObject;
               currentNewObject = NULL;
               ip = failJump;
               break;
            }

            // If it's not a datablock, allow people to modify bits of it.
            if (!isDataBlock)
            {
               currentNewObject->setModStaticFields(true);
               currentNewObject->setModDynamicFields(true);
            }
         }
         else
         {
            currentNewObject->reloadReset(); // AFX (reload-reset)

            // Does it have a parent object? (ie, the copy constructor : syntax, not inheriance)
            if (*objParent)
            {
               // Find it!
               SimObject* parent;
               if (Sim::findObject(objParent, parent))
               {
                  // Con::printf(" - Parent object found: %s", parent->getClassName());

                  // temporarily block name change
                  SimObject::preventNameChanging = true;
                  currentNewObject->setCopySource(parent);
                  currentNewObject->assignFieldsFrom(parent);
                  // restore name changing
                  SimObject::preventNameChanging = false;

                  // copy any substitution statements
                  SimDataBlock* parent_db = dynamic_cast<SimDataBlock*>(parent);
                  if (parent_db)
                  {
                     SimDataBlock* currentNewObject_db = dynamic_cast<SimDataBlock*>(currentNewObject);
                     if (currentNewObject_db)
                        currentNewObject_db->copySubstitutionsFrom(parent_db);
                  }
               }
               else
               {
                  Con::errorf(ConsoleLogEntry::General, "%d: Unable to find parent object %s for %s.", lineNumber, objParent, callArgv[1].getString());
               }
            }
         }

         // Advance the IP past the create info...
         ip += 7;
         break;
      }

      case OP_ADD_OBJECT:
      {
         // See OP_SETCURVAR for why we do this.
         curFNDocBlock = NULL;
         curNSDocBlock = NULL;

         // Do we place this object at the root?
         bool placeAtRoot = code[ip++];

         // Con::printf("Adding object %s", currentNewObject->getName());

         // Make sure it wasn't already added, then add it.
         if (currentNewObject == NULL)
         {
            break;
         }

         bool isMessage = dynamic_cast<Message*>(currentNewObject) != NULL;

         if (currentNewObject->isProperlyAdded() == false)
         {
            bool ret = false;
            if (isMessage)
            {
               SimObjectId id = Message::getNextMessageID();
               if (id != 0xffffffff)
                  ret = currentNewObject->registerObject(id);
               else
                  Con::errorf("%s: No more object IDs available for messages", getFileLine(ip));
            }
            else
               ret = currentNewObject->registerObject();

            if (!ret)
            {
               // This error is usually caused by failing to call Parent::initPersistFields in the class' initPersistFields().
               Con::warnf(ConsoleLogEntry::General, "%s: Register object failed for object %s of class %s.", getFileLine(ip - 2), currentNewObject->getName(), currentNewObject->getClassName());
               delete currentNewObject;
               ip = failJump;
               break;
            }
         }

         // Are we dealing with a datablock?
         SimDataBlock* dataBlock = dynamic_cast<SimDataBlock*>(currentNewObject);
         String errorStr;

         // If so, preload it.
         if (dataBlock && !dataBlock->preload(true, errorStr))
         {
            Con::errorf(ConsoleLogEntry::General, "%s: preload failed for %s: %s.", getFileLine(ip - 2),
               currentNewObject->getName(), errorStr.c_str());
            dataBlock->deleteObject();
            ip = failJump;
            break;
         }

         // What group will we be added to, if any?
         U32 groupAddId = (U32)intStack[_UINT];
         SimGroup* grp = NULL;
         SimSet* set = NULL;

         if (!placeAtRoot || !currentNewObject->getGroup())
         {
            if (!isMessage)
            {
               if (!placeAtRoot)
               {
                  // Otherwise just add to the requested group or set.
                  if (!Sim::findObject(groupAddId, grp))
                     Sim::findObject(groupAddId, set);
               }

               if (placeAtRoot)
               {
                  // Deal with the instantGroup if we're being put at the root or we're adding to a component.
                  if (Con::gInstantGroup.isEmpty() || !Sim::findObject(Con::gInstantGroup, grp))
                     grp = Sim::getRootGroup();
               }
            }

            // If we didn't get a group, then make sure we have a pointer to
            // the rootgroup.
            if (!grp)
               grp = Sim::getRootGroup();

            // add to the parent group
            grp->addObject(currentNewObject);

            // If for some reason the add failed, add the object to the
            // root group so it won't leak.
            if (currentNewObject->getGroup() == NULL)
               Sim::getRootGroup()->addObject(currentNewObject);

            // add to any set we might be in
            if (set)
               set->addObject(currentNewObject);
         }

         // store the new object's ID on the stack (overwriting the group/set
         // id, if one was given, otherwise getting pushed)
         S32 id = currentNewObject->getId();
         if (placeAtRoot)
            intStack[_UINT] = id;
         else
            intStack[++_UINT] = id;

         break;
      }

      case OP_END_OBJECT:
      {
         // If we're not to be placed at the root, make sure we clean up
         // our group reference.
         bool placeAtRoot = code[ip++];
         if (!placeAtRoot)
            _UINT--;
         break;
      }

      case OP_FINISH_OBJECT:
      {
         if (currentNewObject)
            currentNewObject->onPostAdd();

         //Assert( objectCreationStackIndex >= 0 );
         // Restore the object info from the stack [7/9/2007 Black]
         currentNewObject = objectCreationStack[--objectCreationStackIndex].newObject;
         failJump = objectCreationStack[objectCreationStackIndex].failJump;
         break;
      }

      case OP_JMPIFFNOT:
         if (floatStack[_FLT--])
         {
            ip++;
            break;
         }
         ip = code[ip];
         break;
      case OP_JMPIFNOT:
         if (intStack[_UINT--])
         {
            ip++;
            break;
         }
         ip = code[ip];
         break;
      case OP_JMPIFF:
         if (!floatStack[_FLT--])
         {
            ip++;
            break;
         }
         ip = code[ip];
         break;
      case OP_JMPIF:
         if (!intStack[_UINT--])
         {
            ip++;
            break;
         }
         ip = code[ip];
         break;
      case OP_JMPIFNOT_NP:
         if (intStack[_UINT])
         {
            _UINT--;
            ip++;
            break;
         }
         ip = code[ip];
         break;
      case OP_JMPIF_NP:
         if (!intStack[_UINT])
         {
            _UINT--;
            ip++;
            break;
         }
         ip = code[ip];
         break;
      case OP_JMP:
         ip = code[ip];
         break;

         // This fixes a bug when not explicitly returning a value.
      case OP_RETURN_VOID:
         STR.setStringValue("");
         // We're falling thru here on purpose.

      case OP_RETURN:

         if (iterDepth > 0)
         {
            // Clear iterator state.
            while (iterDepth > 0)
            {
               iterStack[--_ITER].mIsStringIter = false;
               --iterDepth;
            }

            const char* retVal = STR.getStringValue();
            STR.rewind();

            returnValue.setString(retVal, STR.mLen);
            //STR.setStringValue(returnValue); // Not nice but works.
         }

         goto execFinished;

      case OP_RETURN_FLT:

         if (iterDepth > 0)
         {
            // Clear iterator state.
            while (iterDepth > 0)
            {
               iterStack[--_ITER].mIsStringIter = false;
               --iterDepth;
            }

         }

         returnValue.setFloat(floatStack[_FLT]);
         _FLT--;

         goto execFinished;

      case OP_RETURN_UINT:

         if (iterDepth > 0)
         {
            // Clear iterator state.
            while (iterDepth > 0)
            {
               iterStack[--_ITER].mIsStringIter = false;
               --iterDepth;
            }
         }

         returnValue.setInt(intStack[_UINT]);
         _UINT--;

         goto execFinished;

      case OP_CMPEQ:
         intStack[_UINT + 1] = bool(floatStack[_FLT] == floatStack[_FLT - 1]);
         _UINT++;
         _FLT -= 2;
         break;

      case OP_CMPGR:
         intStack[_UINT + 1] = bool(floatStack[_FLT] > floatStack[_FLT - 1]);
         _UINT++;
         _FLT -= 2;
         break;

      case OP_CMPGE:
         intStack[_UINT + 1] = bool(floatStack[_FLT] >= floatStack[_FLT - 1]);
         _UINT++;
         _FLT -= 2;
         break;

      case OP_CMPLT:
         intStack[_UINT + 1] = bool(floatStack[_FLT] < floatStack[_FLT - 1]);
         _UINT++;
         _FLT -= 2;
         break;

      case OP_CMPLE:
         intStack[_UINT + 1] = bool(floatStack[_FLT] <= floatStack[_FLT - 1]);
         _UINT++;
         _FLT -= 2;
         break;

      case OP_CMPNE:
         intStack[_UINT + 1] = bool(floatStack[_FLT] != floatStack[_FLT - 1]);
         _UINT++;
         _FLT -= 2;
         break;

      case OP_XOR:
         intStack[_UINT - 1] = intStack[_UINT] ^ intStack[_UINT - 1];
         _UINT--;
         break;

      case OP_MOD:
         if (intStack[_UINT - 1] != 0)
            intStack[_UINT - 1] = intStack[_UINT] % intStack[_UINT - 1];
         else
            intStack[_UINT - 1] = 0;
         _UINT--;
         break;

      case OP_BITAND:
         intStack[_UINT - 1] = intStack[_UINT] & intStack[_UINT - 1];
         _UINT--;
         break;

      case OP_BITOR:
         intStack[_UINT - 1] = intStack[_UINT] | intStack[_UINT - 1];
         _UINT--;
         break;

      case OP_NOT:
         intStack[_UINT] = !intStack[_UINT];
         break;

      case OP_NOTF:
         intStack[_UINT + 1] = !floatStack[_FLT];
         _FLT--;
         _UINT++;
         break;

      case OP_ONESCOMPLEMENT:
         intStack[_UINT] = ~intStack[_UINT];
         break;

      case OP_SHR:
         intStack[_UINT - 1] = intStack[_UINT] >> intStack[_UINT - 1];
         _UINT--;
         break;

      case OP_SHL:
         intStack[_UINT - 1] = intStack[_UINT] << intStack[_UINT - 1];
         _UINT--;
         break;

      case OP_AND:
         intStack[_UINT - 1] = intStack[_UINT] && intStack[_UINT - 1];
         _UINT--;
         break;

      case OP_OR:
         intStack[_UINT - 1] = intStack[_UINT] || intStack[_UINT - 1];
         _UINT--;
         break;

      case OP_ADD:
         floatStack[_FLT - 1] = floatStack[_FLT] + floatStack[_FLT - 1];
         _FLT--;
         break;

      case OP_SUB:
         floatStack[_FLT - 1] = floatStack[_FLT] - floatStack[_FLT - 1];
         _FLT--;
         break;

      case OP_MUL:
         floatStack[_FLT - 1] = floatStack[_FLT] * floatStack[_FLT - 1];
         _FLT--;
         break;
      case OP_DIV:
         floatStack[_FLT - 1] = floatStack[_FLT] / floatStack[_FLT - 1];
         _FLT--;
         break;
      case OP_NEG:
         floatStack[_FLT] = -floatStack[_FLT];
         break;

      case OP_INC:
         reg = code[ip++];
         gEvalState.setLocalFloatVariable(reg, gEvalState.getLocalFloatVariable(reg) + 1.0);
         break;

      case OP_SETCURVAR:
         var = CodeToSTE(code, ip);
         ip += 2;

         // If a variable is set, then these must be NULL. It is necessary
         // to set this here so that the vector parser can appropriately
         // identify whether it's dealing with a vector.
         prevField = NULL;
         prevObject = NULL;
         curObject = NULL;

         gEvalState.setCurVarName(var);

         // In order to let docblocks work properly with variables, we have
         // clear the current docblock when we do an assign. This way it
         // won't inappropriately carry forward to following function decls.
         curFNDocBlock = NULL;
         curNSDocBlock = NULL;
         break;

      case OP_SETCURVAR_CREATE:
         var = CodeToSTE(code, ip);
         ip += 2;

         // See OP_SETCURVAR
         prevField = NULL;
         prevObject = NULL;
         curObject = NULL;

         gEvalState.setCurVarNameCreate(var);

         // See OP_SETCURVAR for why we do this.
         curFNDocBlock = NULL;
         curNSDocBlock = NULL;
         break;

      case OP_SETCURVAR_ARRAY:
         var = STR.getSTValue();

         // See OP_SETCURVAR
         prevField = NULL;
         prevObject = NULL;
         curObject = NULL;

         gEvalState.setCurVarName(var);

         // See OP_SETCURVAR for why we do this.
         curFNDocBlock = NULL;
         curNSDocBlock = NULL;
         break;

      case OP_SETCURVAR_ARRAY_CREATE:
         var = STR.getSTValue();

         // See OP_SETCURVAR
         prevField = NULL;
         prevObject = NULL;
         curObject = NULL;

         gEvalState.setCurVarNameCreate(var);

         // See OP_SETCURVAR for why we do this.
         curFNDocBlock = NULL;
         curNSDocBlock = NULL;
         break;

      case OP_LOADVAR_UINT:
         intStack[_UINT + 1] = gEvalState.getIntVariable();
         _UINT++;
         break;

      case OP_LOADVAR_FLT:
         floatStack[_FLT + 1] = gEvalState.getFloatVariable();
         _FLT++;
         break;

      case OP_LOADVAR_STR:
         val = gEvalState.getStringVariable();
         STR.setStringValue(val);
         break;

      case OP_SAVEVAR_UINT:
         gEvalState.setIntVariable((S32)intStack[_UINT]);
         break;

      case OP_SAVEVAR_FLT:
         gEvalState.setFloatVariable(floatStack[_FLT]);
         break;

      case OP_SAVEVAR_STR:
         gEvalState.setStringVariable(STR.getStringValue());
         break;

      case OP_LOAD_LOCAL_VAR_UINT:
         reg = code[ip++];
         intStack[_UINT + 1] = gEvalState.getLocalIntVariable(reg);
         _UINT++;
         break;

      case OP_LOAD_LOCAL_VAR_FLT:
         reg = code[ip++];
         floatStack[_FLT + 1] = gEvalState.getLocalFloatVariable(reg);
         _FLT++;
         break;

      case OP_LOAD_LOCAL_VAR_STR:
         reg = code[ip++];
         val = gEvalState.getLocalStringVariable(reg);
         STR.setStringValue(val);
         break;

      case OP_SAVE_LOCAL_VAR_UINT:
         reg = code[ip++];
         gEvalState.setLocalIntVariable(reg, (S32)intStack[_UINT]);
         break;

      case OP_SAVE_LOCAL_VAR_FLT:
         reg = code[ip++];
         gEvalState.setLocalFloatVariable(reg, floatStack[_FLT]);
         break;

      case OP_SAVE_LOCAL_VAR_STR:
         reg = code[ip++];
         gEvalState.setLocalStringVariable(reg, STR.getStringValue(), (S32)STR.mLen);
         break;

      case OP_SETCUROBJECT:
         // Save the previous object for parsing vector fields.
         prevObject = curObject;
         val = STR.getStringValue();

         // Sim::findObject will sometimes find valid objects from
         // multi-component strings. This makes sure that doesn't
         // happen.
         for (const char* check = val; *check; check++)
         {
            if (*check == ' ')
            {
               val = "";
               break;
            }
         }
         curObject = Sim::findObject(val);
         break;

      case OP_SETCUROBJECT_INTERNAL:
         ++ip; // To skip the recurse flag if the object wasnt found
         if (curObject)
         {
            SimGroup* group = dynamic_cast<SimGroup*>(curObject);
            if (group)
            {
               StringTableEntry intName = StringTable->insert(STR.getStringValue());
               bool recurse = code[ip - 1];
               SimObject* obj = group->findObjectByInternalName(intName, recurse);
               intStack[_UINT + 1] = obj ? obj->getId() : 0;
               _UINT++;
            }
            else
            {
               Con::errorf(ConsoleLogEntry::Script, "%s: Attempt to use -> on non-group %s of class %s.", getFileLine(ip - 2), curObject->getName(), curObject->getClassName());
               intStack[_UINT] = 0;
            }
         }
         break;

      case OP_SETCUROBJECT_NEW:
         curObject = currentNewObject;
         break;

      case OP_SETCURFIELD:
         // Save the previous field for parsing vector fields.
         prevField = curField;
         dStrcpy(prevFieldArray, curFieldArray, 256);
         curField = CodeToSTE(code, ip);
         curFieldArray[0] = 0;
         ip += 2;
         break;

      case OP_SETCURFIELD_ARRAY:
         dStrcpy(curFieldArray, STR.getStringValue(), 256);
         break;

      case OP_SETCURFIELD_TYPE:
         if(curObject)
            curObject->setDataFieldType(code[ip], curField, curFieldArray);
         ip++;
         break;

      case OP_LOADFIELD_UINT:
         if (curObject)
            intStack[_UINT + 1] = U32(dAtoi(curObject->getDataField(curField, curFieldArray)));
         else
         {
            // The field is not being retrieved from an object. Maybe it's
            // a special accessor?
            char buff[FieldBufferSizeNumeric];
            memset(buff, 0, sizeof(buff));
            getFieldComponent(prevObject, prevField, prevFieldArray, curField, buff);
            intStack[_UINT + 1] = dAtoi(buff);
         }
         _UINT++;
         break;

      case OP_LOADFIELD_FLT:
         if (curObject)
            floatStack[_FLT + 1] = dAtof(curObject->getDataField(curField, curFieldArray));
         else
         {
            // The field is not being retrieved from an object. Maybe it's
            // a special accessor?
            char buff[FieldBufferSizeNumeric];
            memset(buff, 0, sizeof(buff));
            getFieldComponent(prevObject, prevField, prevFieldArray, curField, buff);
            floatStack[_FLT + 1] = dAtof(buff);
         }
         _FLT++;
         break;

      case OP_LOADFIELD_STR:
         if (curObject)
         {
            val = curObject->getDataField(curField, curFieldArray);
            STR.setStringValue(val);
         }
         else
         {
            // The field is not being retrieved from an object. Maybe it's
            // a special accessor?
            char buff[FieldBufferSizeString];
            memset(buff, 0, sizeof(buff));
            getFieldComponent(prevObject, prevField, prevFieldArray, curField, buff);
            STR.setStringValue(buff);
         }

         break;

      case OP_SAVEFIELD_UINT:
         STR.setIntValue((U32)intStack[_UINT]);
         if (curObject)
            curObject->setDataField(curField, curFieldArray, STR.getStringValue());
         else
         {
            // The field is not being set on an object. Maybe it's
            // a special accessor?
            setFieldComponent( prevObject, prevField, prevFieldArray, curField );
            prevObject = NULL;
         }
         break;

      case OP_SAVEFIELD_FLT:
         STR.setFloatValue(floatStack[_FLT]);
         if (curObject)
            curObject->setDataField(curField, curFieldArray, STR.getStringValue());
         else
         {
            // The field is not being set on an object. Maybe it's
            // a special accessor?
            setFieldComponent( prevObject, prevField, prevFieldArray, curField );
            prevObject = NULL;
         }
         break;

      case OP_SAVEFIELD_STR:
         if (curObject)
            curObject->setDataField(curField, curFieldArray, STR.getStringValue());
         else
         {
            // The field is not being set on an object. Maybe it's
            // a special accessor?
            setFieldComponent( prevObject, prevField, prevFieldArray, curField );
            prevObject = NULL;
         }
         break;

      case OP_STR_TO_UINT:
         intStack[_UINT + 1] = STR.getIntValue();
         _UINT++;
         break;

      case OP_STR_TO_FLT:
         floatStack[_FLT + 1] = STR.getFloatValue();
         _FLT++;
         break;

      case OP_STR_TO_NONE:
         // This exists simply to deal with certain typecast situations.
         break;

      case OP_FLT_TO_UINT:
         intStack[_UINT + 1] = (S64)floatStack[_FLT];
         _FLT--;
         _UINT++;
         break;

      case OP_FLT_TO_STR:
         STR.setFloatValue(floatStack[_FLT]);
         _FLT--;
         break;

      case OP_FLT_TO_NONE:
         _FLT--;
         break;

      case OP_UINT_TO_FLT:
         floatStack[_FLT + 1] = (F64)intStack[_UINT];
         _UINT--;
         _FLT++;
         break;

      case OP_UINT_TO_STR:
         STR.setIntValue((U32)intStack[_UINT]);
         _UINT--;
         break;

      case OP_UINT_TO_NONE:
         _UINT--;
         break;

      case OP_LOADIMMED_UINT:
         intStack[_UINT + 1] = code[ip++];
         _UINT++;
         break;

      case OP_LOADIMMED_FLT:
         floatStack[_FLT + 1] = curFloatTable[code[ip]];
         ip++;
         _FLT++;
         break;
      case OP_TAG_TO_STR:
         code[ip - 1] = OP_LOADIMMED_STR;
         // it's possible the string has already been converted
         if (U8(curStringTable[code[ip]]) != StringTagPrefixByte)
         {
            U32 id = GameAddTaggedString(curStringTable + code[ip]);
            dSprintf(curStringTable + code[ip] + 1, 7, "%d", id);
            *(curStringTable + code[ip]) = StringTagPrefixByte;
         }
      case OP_LOADIMMED_STR:
         STR.setStringValue(curStringTable + code[ip++]);
         break;

      case OP_DOCBLOCK_STR:
      {
         // If the first word of the doc is '\class' or '@class', then this
         // is a namespace doc block, otherwise it is a function doc block.
         const char* docblock = curStringTable + code[ip++];

         const char* sansClass = dStrstr(docblock, "@class");
         if (!sansClass)
            sansClass = dStrstr(docblock, "\\class");

         if (sansClass)
         {
            // Don't save the class declaration. Scan past the 'class'
            // keyword and up to the first whitespace.
            sansClass += 7;
            S32 index = 0;
            while ((*sansClass != ' ') && (*sansClass != '\n') && *sansClass && (index < (nsDocLength - 1)))
            {
               nsDocBlockClass[index++] = *sansClass;
               sansClass++;
            }
            nsDocBlockClass[index] = '\0';

            curNSDocBlock = sansClass + 1;
         }
         else
            curFNDocBlock = docblock;
      }

      break;

      case OP_LOADIMMED_IDENT:
         STR.setStringValue(CodeToSTE(code, ip));
         ip += 2;
         break;

      case OP_CALLFUNC:
      {
         // This routingId is set when we query the object as to whether
         // it handles this method.  It is set to an enum from the table
         // above indicating whether it handles it on a component it owns
         // or just on the object.
         S32 routingId = 0;

         fnName = CodeToSTE(code, ip);
         fnNamespace = CodeToSTE(code, ip + 2);
         U32 callType = code[ip + 4];

         //if this is called from inside a function, append the ip and codeptr
         if (!gEvalState.stack.empty())
         {
            gEvalState.stack.last()->code = this;
            gEvalState.stack.last()->ip = ip - 1;
         }

         ip += 5;
         gCallStack.argvc(fnName, callArgc, &callArgv);

         if (callType == FuncCallExprNode::FunctionCall)
         {
            // Note: This works even if the function was in a package. Reason being is when
            // activatePackage() is called, it swaps the namespaceEntry into the global namespace
            // (and reverts it when deactivatePackage is called). Method or Static related ones work
            // as expected, as the namespace is resolved on the fly.
            nsEntry = Namespace::global()->lookup(fnName);
            if (!nsEntry)
            {
               Con::warnf(ConsoleLogEntry::General,
                  "%s: Unable to find function %s",
                  getFileLine(ip - 4), fnName);
               //STR.popFrame();
               gCallStack.popFrame();
               break;
            }
         }
         else if (callType == FuncCallExprNode::StaticCall)
         {
            // Try to look it up.
            ns = Namespace::find(fnNamespace);
            nsEntry = ns->lookup(fnName);
            if (!nsEntry)
            {
               Con::warnf(ConsoleLogEntry::General,
                  "%s: Unable to find function %s%s%s",
                  getFileLine(ip - 4), fnNamespace ? fnNamespace : "",
                  fnNamespace ? "::" : "", fnName);
               //STR.popFrame();
               gCallStack.popFrame();
               break;
            }
         }
         else if (callType == FuncCallExprNode::MethodCall)
         {
            saveObject = gEvalState.thisObject;

            // Optimization: If we're an integer, we can lookup the value by SimObjectId
            const ConsoleValue& simObjectLookupValue = callArgv[1];
            if (simObjectLookupValue.getType() == ConsoleValueType::cvInteger)
               gEvalState.thisObject = Sim::findObject(static_cast<SimObjectId>(simObjectLookupValue.getInt()));
            else
               gEvalState.thisObject = Sim::findObject(simObjectLookupValue.getString());

            if (gEvalState.thisObject == NULL)
            {
               Con::warnf(
                  ConsoleLogEntry::General,
                  "%s: Unable to find object: '%s' attempting to call function '%s'",
                  getFileLine(ip - 6),
                  simObjectLookupValue.getString(),
                  fnName
               );
               //STR.popFrame();
               gCallStack.popFrame();
               STR.setStringValue("");
               break;
            }

            ns = gEvalState.thisObject->getNamespace();
            if (ns)
               nsEntry = ns->lookup(fnName);
            else
               nsEntry = NULL;
         }
         else // it's a ParentCall
         {
            if (thisNamespace)
            {
               ns = thisNamespace->mParent;
               if (ns)
                  nsEntry = ns->lookup(fnName);
               else
                  nsEntry = NULL;
            }
            else
            {
               ns = NULL;
               nsEntry = NULL;
            }
         }

         if (!nsEntry || noCalls)
         {
            if (!noCalls)
            {
               Con::warnf(ConsoleLogEntry::General, "%s: Unknown command %s.", getFileLine(ip - 4), fnName);
               if (callType == FuncCallExprNode::MethodCall)
               {
                  Con::warnf(ConsoleLogEntry::General, "  Object %s(%d) %s",
                     gEvalState.thisObject->getName() ? gEvalState.thisObject->getName() : "",
                     gEvalState.thisObject->getId(), Con::getNamespaceList(ns));
               }
            }
            gCallStack.popFrame();
            STR.setStringValue("");
            STR.setStringValue("");
            break;
         }
         if (nsEntry->mType == Namespace::Entry::ConsoleFunctionType)
         {
            if (nsEntry->mFunctionOffset)
            {
               ConsoleValue ret;
               nsEntry->mCode->exec(nsEntry->mFunctionOffset, fnName, nsEntry->mNamespace, callArgc, callArgv, false, nsEntry->mPackage, ret);
               STR.setStringValue(ret.getString());
            }
            else // no body
               STR.setStringValue("");

            gCallStack.popFrame();
         }
         else
         {
            if ((nsEntry->mMinArgs && S32(callArgc) < nsEntry->mMinArgs) || (nsEntry->mMaxArgs && S32(callArgc) > nsEntry->mMaxArgs))
            {
               const char* nsName = ns ? ns->mName : "";
               Con::warnf(ConsoleLogEntry::Script, "%s: %s::%s - wrong number of arguments.", getFileLine(ip - 4), nsName, fnName);
               Con::warnf(ConsoleLogEntry::Script, "%s: usage: %s", getFileLine(ip - 4), nsEntry->mUsage);
               gCallStack.popFrame();
               STR.setStringValue("");
            }
            else
            {
               switch (nsEntry->mType)
               {
               case Namespace::Entry::StringCallbackType:
               {
                  const char* ret = nsEntry->cb.mStringCallbackFunc(gEvalState.thisObject, callArgc, callArgv);
                  gCallStack.popFrame();
                  if (ret != STR.getStringValue())
                     STR.setStringValue(ret);
                  else
                     STR.setLen(dStrlen(ret));
                  break;
               }
               case Namespace::Entry::IntCallbackType:
               {
                  S32 result = nsEntry->cb.mIntCallbackFunc(gEvalState.thisObject, callArgc, callArgv);
                  gCallStack.popFrame();
                  if (code[ip] == OP_STR_TO_UINT)
                  {
                     ip++;
                     intStack[++_UINT] = result;
                     break;
                  }
                  else if (code[ip] == OP_STR_TO_FLT)
                  {
                     ip++;
                     floatStack[++_FLT] = result;
                     break;
                  }
                  else if (code[ip] == OP_STR_TO_NONE)
                     ip++;
                  else
                     STR.setIntValue(result);
                  break;
               }
               case Namespace::Entry::FloatCallbackType:
               {
                  F64 result = nsEntry->cb.mFloatCallbackFunc(gEvalState.thisObject, callArgc, callArgv);
                  gCallStack.popFrame();
                  if (code[ip] == OP_STR_TO_UINT)
                  {
                     ip++;
                     intStack[++_UINT] = (S64)result;
                     break;
                  }
                  else if (code[ip] == OP_STR_TO_FLT)
                  {
                     ip++;
                     floatStack[++_FLT] = result;
                     break;
                  }
                  else if (code[ip] == OP_STR_TO_NONE)
                     ip++;
                  else
                     STR.setFloatValue(result);
                  break;
               }
               case Namespace::Entry::VoidCallbackType:
               {
                  nsEntry->cb.mVoidCallbackFunc(gEvalState.thisObject, callArgc, callArgv);
                  if (code[ip] != OP_STR_TO_NONE)
                     Con::warnf(ConsoleLogEntry::General, "%s: Call to %s in %s uses result of void function call.", getFileLine(ip - 4), fnName, functionName);
                  gCallStack.popFrame();
                  STR.setStringValue("");
                  break;
               }
               case Namespace::Entry::BoolCallbackType:
               {
                  bool result = nsEntry->cb.mBoolCallbackFunc(gEvalState.thisObject, callArgc, callArgv);
                  gCallStack.popFrame();
                  if (code[ip] == OP_STR_TO_UINT)
                  {
                     ip++;
                     intStack[++_UINT] = result;
                     break;
                  }
                  else if (code[ip] == OP_STR_TO_FLT)
                  {
                     ip++;
                     floatStack[++_FLT] = result;
                     break;
                  }
                  else if (code[ip] == OP_STR_TO_NONE)
                     ip++;
                  else
                     STR.setIntValue(result);
                  break;
               }
               }
            }
         }

         if (callType == FuncCallExprNode::MethodCall)
            gEvalState.thisObject = saveObject;
         break;
      }
      case OP_ADVANCE_STR:
         STR.advance();
         break;
      case OP_ADVANCE_STR_APPENDCHAR:
         STR.advanceChar(code[ip++]);
         break;

      case OP_ADVANCE_STR_COMMA:
         STR.advanceChar('_');
         break;

      case OP_ADVANCE_STR_NUL:
         STR.advanceChar(0);
         break;

      case OP_REWIND_STR:
         STR.rewind();
         break;

      case OP_TERMINATE_REWIND_STR:
         STR.rewindTerminate();
         break;

      case OP_COMPARE_STR:
         intStack[++_UINT] = STR.compare();
         break;

      case OP_PUSH:
         gCallStack.pushString(STR.getStringValue(), STR.mLen);
         break;

      case OP_PUSH_UINT:
         gCallStack.pushInt((U32)intStack[_UINT--]);
         break;

      case OP_PUSH_FLT:
         gCallStack.pushFloat(floatStack[_FLT--]);
         break;

      case OP_PUSH_FRAME:
         gCallStack.pushFrame(code[ip++]);
         break;

      case OP_ASSERT:
      {
         if (!intStack[_UINT--])
         {
            const char* message = curStringTable + code[ip];

            U32 breakLine, inst;
            findBreakLine(ip - 1, breakLine, inst);

            if (PlatformAssert::processAssert(PlatformAssert::Fatal,
               name ? name : "eval",
               breakLine,
               message))
            {
               if (TelDebugger && TelDebugger->isConnected() && breakLine > 0)
               {
                  TelDebugger->breakProcess();
               }
               else
                  Platform::debugBreak();
            }
         }

         ip++;
         break;
      }

      case OP_BREAK:
      {
         //append the ip and codeptr before managing the breakpoint!
         AssertFatal(!gEvalState.stack.empty(), "Empty eval stack on break!");
         gEvalState.stack.last()->code = this;
         gEvalState.stack.last()->ip = ip - 1;

         U32 breakLine;
         findBreakLine(ip - 1, breakLine, instruction);
         if (!breakLine)
            goto breakContinue;
         TelDebugger->executionStopped(this, breakLine);

         goto breakContinue;
      }

      case OP_ITER_BEGIN_STR:
      {
         iterStack[_ITER].mIsStringIter = true;
         /* fallthrough */
      }

      case OP_ITER_BEGIN:
      {
         StringTableEntry varName = CodeToSTE(code, ip);
         U32 failIp = code[ip + 2];

         IterStackRecord& iter = iterStack[_ITER];

         iter.mVariable = gEvalState.getCurrentFrame().add(varName);

         if (iter.mIsStringIter)
         {
            iter.mData.mStr.mString = STR.getStringValue();
            iter.mData.mStr.mIndex = 0;
         }
         else
         {
            // Look up the object.

            SimSet* set;
            if (!Sim::findObject(STR.getStringValue(), set))
            {
               Con::errorf(ConsoleLogEntry::General, "No SimSet object '%s'", STR.getStringValue());
               Con::errorf(ConsoleLogEntry::General, "Did you mean to use 'foreach$' instead of 'foreach'?");
               ip = failIp;
               continue;
            }

            // Set up.

            iter.mData.mObj.mSet = set;
            iter.mData.mObj.mIndex = 0;
         }

         _ITER++;
         iterDepth++;

         STR.push();

         ip += 3;
         break;
      }

      case OP_ITER:
      {
         U32 breakIp = code[ip];
         IterStackRecord& iter = iterStack[_ITER - 1];

         if (iter.mIsStringIter)
         {
            const char* str = iter.mData.mStr.mString;

            U32 startIndex = iter.mData.mStr.mIndex;
            U32 endIndex = startIndex;

            // Break if at end.

            if (!str[startIndex])
            {
               ip = breakIp;
               continue;
            }

            // Find right end of current component.

            if (!dIsspace(str[endIndex]))
               do ++endIndex;
            while (str[endIndex] && !dIsspace(str[endIndex]));

            // Extract component.

            if (endIndex != startIndex)
            {
               char savedChar = str[endIndex];
               const_cast<char*>(str)[endIndex] = '\0'; // We are on the string stack so this is okay.
               iter.mVariable->setStringValue(&str[startIndex]);
               const_cast<char*>(str)[endIndex] = savedChar;
            }
            else
               iter.mVariable->setStringValue("");

            // Skip separator.
            if (str[endIndex] != '\0')
               ++endIndex;

            iter.mData.mStr.mIndex = endIndex;
         }
         else
         {
            U32 index = iter.mData.mObj.mIndex;
            SimSet* set = iter.mData.mObj.mSet;

            if (index >= set->size())
            {
               ip = breakIp;
               continue;
            }

            iter.mVariable->setIntValue(set->at(index)->getId());
            iter.mData.mObj.mIndex = index + 1;
         }

         ++ip;
         break;
      }

      case OP_ITER_END:
      {
         --_ITER;
         --iterDepth;

         STR.rewind();

         iterStack[_ITER].mIsStringIter = false;
         break;
      }

      case OP_INVALID:

      default:
         // error!
         goto execFinished;
      }
   }
execFinished:
#ifdef TORQUE_DEBUG
   AssertFatal(returnValue.getType() == ConsoleValueType::cvNone, "returnValue was never set during script exec");
#endif

   if (telDebuggerOn && setFrame < 0)
      TelDebugger->popStackFrame();

   if (popFrame)
   {
      gEvalState.popFrame();
   }

   if (argv)
   {
      if (gEvalState.traceOn)
      {
         traceBuffer[0] = 0;
         dStrcat(traceBuffer, "Leaving ", TRACE_BUFFER_SIZE);

         if (packageName)
         {
            dStrcat(traceBuffer, "[", TRACE_BUFFER_SIZE);
            dStrcat(traceBuffer, packageName, TRACE_BUFFER_SIZE);
            dStrcat(traceBuffer, "]", TRACE_BUFFER_SIZE);
         }
         if (thisNamespace && thisNamespace->mName)
         {
            dSprintf(traceBuffer + dStrlen(traceBuffer), sizeof(traceBuffer) - dStrlen(traceBuffer),
               "%s::%s() - return %s", thisNamespace->mName, thisFunctionName, returnValue.getString());
         }
         else
         {
            dSprintf(traceBuffer + dStrlen(traceBuffer), sizeof(traceBuffer) - dStrlen(traceBuffer),
               "%s() - return %s", thisFunctionName, returnValue.getString());
         }
         Con::printf("%s", traceBuffer);
      }
   }
   else
   {
      delete[] const_cast<char*>(globalStrings);
      delete[] globalFloats;
      globalStrings = NULL;
      globalFloats = NULL;
   }
   smCurrentCodeBlock = saveCodeBlock;
   if (saveCodeBlock && saveCodeBlock->name)
   {
      Con::gCurrentFile = saveCodeBlock->name;
      Con::gCurrentRoot = saveCodeBlock->modPath;
   }

   decRefCount();

#ifdef TORQUE_DEBUG
   AssertFatal(!(STR.mStartStackSize > stackStart), "String stack not popped enough in script exec");
   AssertFatal(!(STR.mStartStackSize < stackStart), "String stack popped too much in script exec");
#endif
}

//------------------------------------------------------------
