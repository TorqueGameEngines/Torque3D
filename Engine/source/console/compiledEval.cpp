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
   ConcatBufferInitialSize = 8192,
   MethodOnComponent = -2
};

/// Frame data for a foreach/foreach$ loop.
struct IterStackRecord
{
   /// If true, this is a foreach$ loop; if not, it's a foreach loop.
   bool mIsStringIter;

   /// True if the variable referenced is a global
   bool mIsGlobalVariable;

   union
   {

      /// The iterator variable if we are a global variable
      Dictionary::Entry* mVariable;

      /// The register variable if we are a local variable
      S32 mRegister;
   } mVar;

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

IterStackRecord iterStack[MaxStackSize];
U32 _ITER = 0;    ///< Stack pointer for iterStack.

ConsoleValue stack[MaxStackSize];
S32 _STK = 0;

char curFieldArray[256];
char prevFieldArray[256];

const char* tsconcat(const char* strA, const char* strB, S32& outputLen)
{
   S32 lenA = dStrlen(strA);
   S32 lenB = dStrlen(strB);

   S32 len = lenA + lenB + 1;

   char* concatBuffer = (char*)dMalloc(len);

   concatBuffer[len - 1] = '\0';
   memcpy(concatBuffer, strA, lenA);
   memcpy(concatBuffer + lenA, strB, lenB);

   outputLen = lenA + lenB;
   return concatBuffer;
}

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
      prevVal = stack[_STK].getString();

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
   dStrncpy(strValue, stack[_STK].getString(), 1024);

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

enum class FloatOperation
{
   Add,
   Sub,
   Mul,
   Div,

   LT,
   LE,
   GR,
   GE,
   EQ,
   NE
};

template<FloatOperation Op>
TORQUE_FORCEINLINE void doFloatMathOperation()
{
   ConsoleValue& a = stack[_STK];
   ConsoleValue& b = stack[_STK - 1];

   S32 fastIf = (a.getType() == ConsoleValueType::cvFloat) & (b.getType() == ConsoleValueType::cvFloat);
   if (fastIf)
   {
      // Arithmetic
      if constexpr (Op == FloatOperation::Add)
         stack[_STK - 1].setFastFloat(a.getFastFloat() + b.getFastFloat());
      if constexpr (Op == FloatOperation::Sub)
         stack[_STK - 1].setFastFloat(a.getFastFloat() - b.getFastFloat());
      if constexpr (Op == FloatOperation::Mul)
         stack[_STK - 1].setFastFloat(a.getFastFloat() * b.getFastFloat());
      if constexpr (Op == FloatOperation::Div)
         stack[_STK - 1].setFastFloat(a.getFastFloat() / b.getFastFloat());

      // Logical
      if constexpr (Op == FloatOperation::LT)
         stack[_STK - 1].setFastInt(a.getFastFloat() < b.getFastFloat());
      if constexpr (Op == FloatOperation::LE)
         stack[_STK - 1].setFastInt(a.getFastFloat() <= b.getFastFloat());
      if constexpr (Op == FloatOperation::GR)
         stack[_STK - 1].setFastInt(a.getFastFloat() > b.getFastFloat());
      if constexpr (Op == FloatOperation::GE)
         stack[_STK - 1].setFastInt(a.getFastFloat() >= b.getFastFloat());
      if constexpr (Op == FloatOperation::EQ)
         stack[_STK - 1].setFastInt(a.getFastFloat() == b.getFastFloat());
      if constexpr (Op == FloatOperation::NE)
         stack[_STK - 1].setFastInt(a.getFastFloat() != b.getFastFloat());

      _STK--;
   }
   else
   {
      doSlowMathOp<Op>();
   }
}

template<FloatOperation Op>
TORQUE_NOINLINE void doSlowMathOp()
{
   ConsoleValue& a = stack[_STK];
   ConsoleValue& b = stack[_STK - 1];

   // Arithmetic
   if constexpr (Op == FloatOperation::Add)
      stack[_STK - 1].setFloat(a.getFloat() + b.getFloat());
   else if constexpr (Op == FloatOperation::Sub)
      stack[_STK - 1].setFloat(a.getFloat() - b.getFloat());
   else if constexpr (Op == FloatOperation::Mul)
      stack[_STK - 1].setFloat(a.getFloat() * b.getFloat());
   else if constexpr (Op == FloatOperation::Div)
      stack[_STK - 1].setFloat(a.getFloat() / b.getFloat());

   // Logical
   if constexpr (Op == FloatOperation::LT)
      stack[_STK - 1].setInt(a.getFloat() < b.getFloat());
   if constexpr (Op == FloatOperation::LE)
      stack[_STK - 1].setInt(a.getFloat() <= b.getFloat());
   if constexpr (Op == FloatOperation::GR)
      stack[_STK - 1].setInt(a.getFloat() > b.getFloat());
   if constexpr (Op == FloatOperation::GE)
      stack[_STK - 1].setInt(a.getFloat() >= b.getFloat());
   if constexpr (Op == FloatOperation::EQ)
      stack[_STK - 1].setInt(a.getFloat() == b.getFloat());
   if constexpr (Op == FloatOperation::NE)
      stack[_STK - 1].setInt(a.getFloat() != b.getFloat());

   _STK--;
}

//-----------------------------------------------------------------------------

enum class IntegerOperation
{
   BitAnd,
   BitOr,
   Xor,
   LShift,
   RShift,

   LogicalAnd,
   LogicalOr
};

template<IntegerOperation Op>
TORQUE_FORCEINLINE void doIntOperation()
{
   ConsoleValue& a = stack[_STK];
   ConsoleValue& b = stack[_STK - 1];

   if (a.isNumberType() && b.isNumberType())
   {
      // Bitwise Op
      if constexpr (Op == IntegerOperation::BitAnd)
         stack[_STK - 1].setFastInt(a.getFastInt() & b.getFastInt());
      if constexpr (Op == IntegerOperation::BitOr)
         stack[_STK - 1].setFastInt(a.getFastInt() | b.getFastInt());
      if constexpr (Op == IntegerOperation::Xor)
         stack[_STK - 1].setFastInt(a.getFastInt() ^ b.getFastInt());
      if constexpr (Op == IntegerOperation::LShift)
         stack[_STK - 1].setFastInt(a.getFastInt() << b.getFastInt());
      if constexpr (Op == IntegerOperation::RShift)
         stack[_STK - 1].setFastInt(a.getFastInt() >> b.getFastInt());

      // Logical Op
      if constexpr (Op == IntegerOperation::LogicalAnd)
         stack[_STK - 1].setFastInt(a.getFastInt() && b.getFastInt());
      if constexpr (Op == IntegerOperation::LogicalOr)
         stack[_STK - 1].setFastInt(a.getFastInt() || b.getFastInt());

      _STK--;
   }
   else
   {
      doSlowIntegerOp<Op>();
   }
}

template<IntegerOperation Op>
TORQUE_NOINLINE void doSlowIntegerOp()
{
   ConsoleValue& a = stack[_STK];
   ConsoleValue& b = stack[_STK - 1];

   // Bitwise Op
   if constexpr (Op == IntegerOperation::BitAnd)
      stack[_STK - 1].setInt(a.getInt() & b.getInt());
   if constexpr (Op == IntegerOperation::BitOr)
      stack[_STK - 1].setInt(a.getInt() | b.getInt());
   if constexpr (Op == IntegerOperation::Xor)
      stack[_STK - 1].setInt(a.getInt() ^ b.getInt());
   if constexpr (Op == IntegerOperation::LShift)
      stack[_STK - 1].setInt(a.getInt() << b.getInt());
   if constexpr (Op == IntegerOperation::RShift)
      stack[_STK - 1].setInt(a.getInt() >> b.getInt());

   // Logical Op
   if constexpr (Op == IntegerOperation::LogicalAnd)
      stack[_STK - 1].setInt(a.getInt() && b.getInt());
   if constexpr (Op == IntegerOperation::LogicalOr)
      stack[_STK - 1].setInt(a.getInt() || b.getInt());

   _STK--;
}

//-----------------------------------------------------------------------------

U32 gExecCount = 0;
ConsoleValue CodeBlock::exec(U32 ip, const char* functionName, Namespace* thisNamespace, U32 argc, ConsoleValue* argv, bool noCalls, StringTableEntry packageName, S32 setFrame)
{
#ifdef TORQUE_DEBUG
   U32 stackStart = _STK;
   gExecCount++;
#endif

   const dsize_t TRACE_BUFFER_SIZE = 1024;
   static char traceBuffer[TRACE_BUFFER_SIZE];
   U32 i;

   U32 iterDepth = 0;
   ConsoleValue returnValue;

   incRefCount();
   F64* curFloatTable;
   char* curStringTable;
   S32 curStringTableLen = 0; //clint to ensure we dont overwrite it

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
         gEvalState.moveConsoleValue(reg, std::move(value));
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

      // If requested stack frame isn't available, request a new one
      // (this prevents assert failures when creating local
      //  variables without a stack frame)
      if (gEvalState.getStackDepth() <= setFrame)
         setFrame = -1;

      // Do we want this code to execute using a new stack frame?
      if (setFrame < 0)
      {
         gEvalState.pushFrame(NULL, NULL, 0);
         gCallStack.pushFrame(0);
         popFrame = true;
      }
      else
      {
         // We want to copy a reference to an existing stack frame
         // on to the top of the stack.  Any change that occurs to
         // the locals during this new frame will also occur in the
         // original frame.
         S32 stackIndex = gEvalState.getTopOfStack() - setFrame - 1;
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
                  currentNewObject = NULL;
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
         U32 groupAddId = (U32)stack[_STK].getInt();
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
            stack[_STK].setInt(id);
         else
            stack[++_STK].setInt(id);

         break;
      }

      case OP_END_OBJECT:
      {
         // If we're not to be placed at the root, make sure we clean up
         // our group reference.
         bool placeAtRoot = code[ip++];
         if (!placeAtRoot)
            _STK--;
         break;
      }

      case OP_FINISH_OBJECT:
      {
         if (currentNewObject)
            currentNewObject->onPostAdd();

         AssertFatal( objectCreationStackIndex >= 0, "Object Stack is empty." );
         // Restore the object info from the stack [7/9/2007 Black]
         currentNewObject = objectCreationStack[--objectCreationStackIndex].newObject;
         failJump = objectCreationStack[objectCreationStackIndex].failJump;
         break;
      }

      case OP_JMPIFFNOT:
         if (stack[_STK--].getFloat())
         {
            ip++;
            break;
         }
         ip = code[ip];
         break;
      case OP_JMPIFNOT:
         if (stack[_STK--].getInt())
         {
            ip++;
            break;
         }
         ip = code[ip];
         break;
      case OP_JMPIFF:
         if (!stack[_STK--].getFloat())
         {
            ip++;
            break;
         }
         ip = code[ip];
         break;
      case OP_JMPIF:
         if (!stack[_STK--].getFloat())
         {
            ip++;
            break;
         }
         ip = code[ip];
         break;
      case OP_JMPIFNOT_NP:
         if (stack[_STK].getInt())
         {
            _STK--;
            ip++;
            break;
         }
         ip = code[ip];
         break;
      case OP_JMPIF_NP:
         if (!stack[_STK].getInt())
         {
            _STK--;
            ip++;
            break;
         }
         ip = code[ip];
         break;
      case OP_JMP:
         ip = code[ip];
         break;

      case OP_RETURN_VOID:
      {
         if (iterDepth > 0)
         {
            // Clear iterator state.
            while (iterDepth > 0)
            {
               iterStack[--_ITER].mIsStringIter = false;
               --iterDepth;
            }

            _STK--; // this is a pop from foreach()
         }

         returnValue.setEmptyString();

         goto execFinished;
      }

      case OP_RETURN:
      {
         if (iterDepth > 0)
         {
            // Clear iterator state.
            while (iterDepth > 0)
            {
               iterStack[--_ITER].mIsStringIter = false;
               --iterDepth;
            }

            
            const char* retVal = stack[_STK].getString();
            _STK--;
            _STK--;
            stack[_STK + 1].setString(retVal);
            _STK++; // Not nice but works.
         }

         returnValue = std::move(stack[_STK]);
         _STK--;

         goto execFinished;
      }
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

         returnValue.setFloat(stack[_STK].getFloat());
         _STK--;

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

         returnValue.setInt(stack[_STK].getInt());
         _STK--;

         goto execFinished;

      case OP_CMPEQ:
         doFloatMathOperation<FloatOperation::EQ>();
         break;

      case OP_CMPGR:
         doFloatMathOperation<FloatOperation::GR>();
         break;

      case OP_CMPGE:
         doFloatMathOperation<FloatOperation::GE>();
         break;

      case OP_CMPLT:
         doFloatMathOperation<FloatOperation::LT>();
         break;

      case OP_CMPLE:
         doFloatMathOperation<FloatOperation::LE>();
         break;

      case OP_CMPNE:
         doFloatMathOperation<FloatOperation::NE>();
         break;

      case OP_XOR:
         doIntOperation<IntegerOperation::Xor>();
         break;

      case OP_BITAND:
         doIntOperation<IntegerOperation::BitAnd>();
         break;

      case OP_BITOR:
         doIntOperation<IntegerOperation::BitOr>();
         break;

      case OP_NOT:
         stack[_STK].setInt(!stack[_STK].getInt());
         break;

      case OP_NOTF:
         stack[_STK].setInt(!stack[_STK].getFloat());
         break;

      case OP_ONESCOMPLEMENT:
         stack[_STK].setInt(~stack[_STK].getInt());
         break;

      case OP_SHR:
         doIntOperation<IntegerOperation::RShift>();
         break;

      case OP_SHL:
         doIntOperation<IntegerOperation::LShift>();
         break;

      case OP_AND:
         doIntOperation<IntegerOperation::LogicalAnd>();
         break;

      case OP_OR:
         doIntOperation<IntegerOperation::LogicalOr>();
         break;

      case OP_ADD:
         doFloatMathOperation<FloatOperation::Add>();
         break;

      case OP_SUB:
         doFloatMathOperation<FloatOperation::Sub>();
         break;

      case OP_MUL:
         doFloatMathOperation<FloatOperation::Mul>();
         break;

      case OP_DIV:
         doFloatMathOperation<FloatOperation::Div>();
         break;

      case OP_MOD:
      {
         S64 divisor = stack[_STK - 1].getInt();
         if (divisor != 0)
            stack[_STK - 1].setInt(stack[_STK].getInt() % divisor);
         else
            stack[_STK - 1].setInt(0);
         _STK--;
         break;
      }

      case OP_NEG:
         stack[_STK].setFloat(-stack[_STK].getFloat());
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
         var = StringTable->insert(stack[_STK].getString());

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
         var = StringTable->insert(stack[_STK].getString());

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
         stack[_STK + 1].setInt(gEvalState.getIntVariable());
         _STK++;
         break;

      case OP_LOADVAR_FLT:
         stack[_STK + 1].setFloat(gEvalState.getFloatVariable());
         _STK++;
         break;

      case OP_LOADVAR_STR:
         stack[_STK + 1].setString(gEvalState.getStringVariable());
         _STK++;
         break;

      case OP_SAVEVAR_UINT:
         gEvalState.setIntVariable(stack[_STK].getInt());
         break;

      case OP_SAVEVAR_FLT:
         gEvalState.setFloatVariable(stack[_STK].getFloat());
         break;

      case OP_SAVEVAR_STR:
         gEvalState.setStringVariable(stack[_STK].getString());
         break;

      case OP_LOAD_LOCAL_VAR_UINT:
         reg = code[ip++];
         stack[_STK + 1].setInt(gEvalState.getLocalIntVariable(reg));
         _STK++;
         break;

      case OP_LOAD_LOCAL_VAR_FLT:
         reg = code[ip++];
         stack[_STK + 1].setFloat(gEvalState.getLocalFloatVariable(reg));
         _STK++;
         break;

      case OP_LOAD_LOCAL_VAR_STR:
         reg = code[ip++];
         val = gEvalState.getLocalStringVariable(reg);
         stack[_STK + 1].setString(val);
         _STK++;
         break;

      case OP_SAVE_LOCAL_VAR_UINT:
         reg = code[ip++];
         gEvalState.setLocalIntVariable(reg, stack[_STK].getInt());
         break;

      case OP_SAVE_LOCAL_VAR_FLT:
         reg = code[ip++];
         gEvalState.setLocalFloatVariable(reg, stack[_STK].getFloat());
         break;

      case OP_SAVE_LOCAL_VAR_STR:
         reg = code[ip++];
         val = stack[_STK].getString();
         gEvalState.setLocalStringVariable(reg, val, (S32)dStrlen(val));
         break;

      case OP_SETCUROBJECT:
         // Save the previous object for parsing vector fields.
         prevObject = curObject;
         val = stack[_STK].getString();
         _STK--;

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
               StringTableEntry intName = StringTable->insert(stack[_STK].getString());
               bool recurse = code[ip - 1];
               SimObject* obj = group->findObjectByInternalName(intName, recurse);
               stack[_STK].setInt(obj ? obj->getId() : 0);
            }
            else
            {
               Con::errorf(ConsoleLogEntry::Script, "%s: Attempt to use -> on non-group %s of class %s.", getFileLine(ip - 2), curObject->getName(), curObject->getClassName());
               stack[_STK].setInt(0);
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
         dStrcpy(curFieldArray, stack[_STK].getString(), 256);
         break;

      case OP_SETCURFIELD_TYPE:
         if(curObject)
            curObject->setDataFieldType(code[ip], curField, curFieldArray);
         ip++;
         break;

      case OP_LOADFIELD_UINT:
         if (curObject)
            stack[_STK + 1].setInt(dAtol(curObject->getDataField(curField, curFieldArray)));
         else
         {
            // The field is not being retrieved from an object. Maybe it's
            // a special accessor?
            char buff[FieldBufferSizeNumeric];
            memset(buff, 0, sizeof(buff));
            getFieldComponent(prevObject, prevField, prevFieldArray, curField, buff);
            stack[_STK + 1].setInt(dAtol(buff));
         }
         _STK++;
         break;

      case OP_LOADFIELD_FLT:
         if (curObject)
            stack[_STK + 1].setFloat(dAtod(curObject->getDataField(curField, curFieldArray)));
         else
         {
            // The field is not being retrieved from an object. Maybe it's
            // a special accessor?
            char buff[FieldBufferSizeNumeric];
            memset(buff, 0, sizeof(buff));
            getFieldComponent(prevObject, prevField, prevFieldArray, curField, buff);
            stack[_STK + 1].setFloat(dAtod(buff));
         }
         _STK++;
         break;

      case OP_LOADFIELD_STR:
         if (curObject)
         {
            val = curObject->getDataField(curField, curFieldArray);
            stack[_STK + 1].setString(val);
         }
         else
         {
            // The field is not being retrieved from an object. Maybe it's
            // a special accessor?
            char buff[FieldBufferSizeString];
            memset(buff, 0, sizeof(buff));
            getFieldComponent(prevObject, prevField, prevFieldArray, curField, buff);
            stack[_STK + 1].setString(buff);
         }
         _STK++;
         break;

      case OP_SAVEFIELD_UINT:
         if (curObject)
            curObject->setDataField(curField, curFieldArray, stack[_STK].getString());
         else
         {
            // The field is not being set on an object. Maybe it's
            // a special accessor?
            setFieldComponent( prevObject, prevField, prevFieldArray, curField );
            prevObject = NULL;
         }
         break;

      case OP_SAVEFIELD_FLT:
         if (curObject)
            curObject->setDataField(curField, curFieldArray, stack[_STK].getString());
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
            curObject->setDataField(curField, curFieldArray, stack[_STK].getString());
         else
         {
            // The field is not being set on an object. Maybe it's
            // a special accessor?
            setFieldComponent( prevObject, prevField, prevFieldArray, curField );
            prevObject = NULL;
         }
         break;

      case OP_POP_STK:
         _STK--;
         break;

      case OP_LOADIMMED_UINT:
         stack[_STK + 1].setInt(code[ip++]);
         _STK++;
         break;

      case OP_LOADIMMED_FLT:
         stack[_STK + 1].setFloat(curFloatTable[code[ip++]]);
         _STK++;
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
         TORQUE_CASE_FALLTHROUGH;

      case OP_LOADIMMED_STR:
         stack[_STK + 1].setString(curStringTable + code[ip++]);
         _STK ++;
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
         stack[_STK + 1].setString(CodeToSTE(code, ip));
         _STK++;
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

               gCallStack.popFrame();
               stack[_STK + 1].setEmptyString();
               _STK++;
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

               gCallStack.popFrame();
               stack[_STK + 1].setEmptyString();
               _STK++;
               break;
            }
         }
         else if (callType == FuncCallExprNode::MethodCall)
         {
            saveObject = gEvalState.thisObject;

            // Optimization: If we're an integer, we can lookup the value by SimObjectId
            const ConsoleValue& simObjectLookupValue = callArgv[1];
            if (simObjectLookupValue.getType() == ConsoleValueType::cvInteger)
               gEvalState.thisObject = Sim::findObject(static_cast<SimObjectId>(simObjectLookupValue.getFastInt()));
            else
            {
               SimObject *foundObject = Sim::findObject(simObjectLookupValue.getString());

               // Optimization: If we're not an integer, let's make it so that the fast path exists
               // on the first argument of the method call (speeds up future usage of %this, for example)
               if (foundObject != NULL)
                  callArgv[1].setInt(static_cast<S64>(foundObject->getId()));

               gEvalState.thisObject = foundObject;
            }

            if (gEvalState.thisObject == NULL)
            {
               Con::warnf(
                  ConsoleLogEntry::General,
                  "%s: Unable to find object: '%s' attempting to call function '%s'",
                  getFileLine(ip - 6),
                  simObjectLookupValue.getString(),
                  fnName
               );

               gCallStack.popFrame();
               stack[_STK + 1].setEmptyString();
               _STK++;
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
            stack[_STK + 1].setEmptyString();
            _STK++;
            break;
         }
         if (nsEntry->mType == Namespace::Entry::ConsoleFunctionType)
         {
            if (nsEntry->mFunctionOffset)
            {
               ConsoleValue returnFromFn = nsEntry->mCode->exec(nsEntry->mFunctionOffset, fnName, nsEntry->mNamespace, callArgc, callArgv, false, nsEntry->mPackage);
               stack[_STK + 1] = std::move(returnFromFn);
            }
            else // no body
               stack[_STK + 1].setEmptyString();
            _STK++;

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
               stack[_STK + 1].setEmptyString();
               _STK++;
            }
            else
            {
               switch (nsEntry->mType)
               {
               case Namespace::Entry::StringCallbackType:
               {
                  const char* result = nsEntry->cb.mStringCallbackFunc(gEvalState.thisObject, callArgc, callArgv);
                  gCallStack.popFrame();
                  stack[_STK + 1].setString(result);
                  _STK++;
                  break;
               }
               case Namespace::Entry::IntCallbackType:
               {
                  S64 result = nsEntry->cb.mIntCallbackFunc(gEvalState.thisObject, callArgc, callArgv);
                  gCallStack.popFrame();

                  if (code[ip] == OP_POP_STK)
                  {
                     ip++;
                     break;
                  }

                  stack[_STK + 1].setInt(result);
                  _STK++;
                  break;
               }
               case Namespace::Entry::FloatCallbackType:
               {
                  F64 result = nsEntry->cb.mFloatCallbackFunc(gEvalState.thisObject, callArgc, callArgv);
                  gCallStack.popFrame();

                  if (code[ip] == OP_POP_STK)
                  {
                     ip++;
                     break;
                  }

                  stack[_STK + 1].setInt(result);
                  _STK++;
                  break;
               }
               case Namespace::Entry::VoidCallbackType:
               {
                  nsEntry->cb.mVoidCallbackFunc(gEvalState.thisObject, callArgc, callArgv);
                  gCallStack.popFrame();

                  if (code[ip] == OP_POP_STK)
                  {
                     ip++;
                     break;
                  }

                  Con::warnf(ConsoleLogEntry::General, "%s: Call to %s in %s uses result of void function call.", getFileLine(ip - 4), fnName, functionName);
                  stack[_STK + 1].setEmptyString();
                  _STK++;

                  break;
               }
               case Namespace::Entry::BoolCallbackType:
               {
                  bool result = nsEntry->cb.mBoolCallbackFunc(gEvalState.thisObject, callArgc, callArgv);
                  gCallStack.popFrame();

                  if (code[ip] == OP_POP_STK)
                  {
                     ip++;
                     break;
                  }

                  stack[_STK + 1].setBool(result);
                  _STK++;

                  break;
               }
               }
            }
         }

         if (callType == FuncCallExprNode::MethodCall)
            gEvalState.thisObject = saveObject;
         break;
      }

      case OP_ADVANCE_STR_APPENDCHAR:
      {
         char buff[2];
         buff[0] = (char)code[ip++];
         buff[1] = '\0';

         S32 len;
         const char* concat = tsconcat(stack[_STK].getString(), buff, len);

         stack[_STK].setStringRef(concat, len);
         break;
      }

      case OP_REWIND_STR:
         TORQUE_CASE_FALLTHROUGH;
      case OP_TERMINATE_REWIND_STR:
      {
         S32 len;
         const char* concat = tsconcat(stack[_STK - 1].getString(), stack[_STK].getString(), len);

         stack[_STK - 1].setStringRef(concat, len);
         _STK--;
         break;
      }

      case OP_COMPARE_STR:
         stack[_STK - 1].setBool(!dStricmp(stack[_STK].getString(), stack[_STK - 1].getString()));
         _STK--;
         break;

      case OP_PUSH:
         gCallStack.push(std::move(stack[_STK--]));
         break;

      case OP_PUSH_FRAME:
         gCallStack.pushFrame(code[ip++]);
         break;

      case OP_ASSERT:
      {
         if (!stack[_STK--].getBool())
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
         TORQUE_CASE_FALLTHROUGH;
      }

      case OP_ITER_BEGIN:
      {
         bool isGlobal = code[ip];

         U32 failIp = code[ip + isGlobal ? 3 : 2];

         IterStackRecord& iter = iterStack[_ITER];
         iter.mIsGlobalVariable = isGlobal;

         if (isGlobal)
         {
            StringTableEntry varName = CodeToSTE(code, ip + 1);
            iter.mVar.mVariable = gEvalState.globalVars.add(varName);
         }
         else
         {
            iter.mVar.mRegister = code[ip + 1];
         }

         if (iter.mIsStringIter)
         {
            iter.mData.mStr.mString = stack[_STK].getString();
            iter.mData.mStr.mIndex = 0;
         }
         else
         {
            // Look up the object.

            SimSet* set;
            if (!Sim::findObject(stack[_STK].getString(), set))
            {
               Con::errorf(ConsoleLogEntry::General, "No SimSet object '%s'", stack[_STK].getString());
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

         ip += isGlobal ? 4 : 3;
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

               if (iter.mIsGlobalVariable)
                  iter.mVar.mVariable->setStringValue(&str[startIndex]);
               else
                  gEvalState.setLocalStringVariable(iter.mVar.mRegister, &str[startIndex], endIndex - startIndex);

               const_cast<char*>(str)[endIndex] = savedChar;
            }
            else
            {
               if (iter.mIsGlobalVariable)
                  iter.mVar.mVariable->setStringValue("");
               else
                  gEvalState.setLocalStringVariable(iter.mVar.mRegister, "", 0);
            }

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

            SimObjectId id = set->at(index)->getId();

            if (iter.mIsGlobalVariable)
               iter.mVar.mVariable->setIntValue(id);
            else
               gEvalState.setLocalIntVariable(iter.mVar.mRegister, id);

            iter.mData.mObj.mIndex = index + 1;
         }

         ++ip;
         break;
      }

      case OP_ITER_END:
      {
         --_ITER;
         --iterDepth;

         _STK--;

         iterStack[_ITER].mIsStringIter = false;
         break;
      }

      case OP_INVALID:
         TORQUE_CASE_FALLTHROUGH;
      default:
         // error!
         AssertISV(false, "Invalid OPCode Processed!");
         goto execFinished;
      }
   }
execFinished:

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
   AssertFatal(!(_STK > stackStart), "String stack not popped enough in script exec");
   AssertFatal(!(_STK < stackStart), "String stack popped too much in script exec");
#endif

   return std::move(returnValue);
}

//------------------------------------------------------------
