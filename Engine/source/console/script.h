#ifndef _SCRIPT_H_
#define _SCRIPT_H_

#include "runtime.h"
#include "core/stream/stream.h"
#include "module.h"

namespace Con
{
   inline EvalResult gLastEvalResult;
   inline EvalResult setLastEvalResult(EvalResult pLastEvalResult)
   {
      gLastEvalResult.valid = pLastEvalResult.valid;
      gLastEvalResult.error = pLastEvalResult.error;
      gLastEvalResult.value.setString(pLastEvalResult.value.getString());
      return std::move(pLastEvalResult);
   }
   inline EvalResult getLastEvalResult() { return setLastEvalResult(std::move(gLastEvalResult)); };

   bool runStream(Stream* byteCode, const char* fileName);

   bool isCurrentScriptToolScript();


   Module* getCurrentModule();

   inline Vector<Runtime*> gRuntimes(32);
   inline Runtime* getRuntime(S32 pRuntimeId = 0) { return gRuntimes[pRuntimeId]; }
   inline void registerRuntime(S32 pRuntimeId, Runtime* pRuntime)
   {
      if (gRuntimes.size() == 0)
      {
         gRuntimes.setSize(pRuntimeId + 1);
         gRuntimes.fill(NULL);
      }
      AssertFatal(gRuntimes[pRuntimeId] == NULL, "A runtime with that ID already exists");
      gRuntimes[pRuntimeId] = pRuntime;
   }


   /// Evaluate an arbitrary chunk of code.
   ///
   /// @param  script   Buffer containing code to execute.
   /// @param  echo     Should we echo the string to the console?
   /// @param  fileName Indicate what file this code is coming from; used in error reporting and such.
   /// NOTE: This function restores the console stack on return.
   inline EvalResult evaluate(const char* script, bool echo = false, const char *fileName = NULL) { return setLastEvalResult(getRuntime()->evaluate(script, echo, fileName)); };

   inline EvalResult evaluate(const char* script, S32 frame, bool echo = false, const char *fileName = NULL) { return setLastEvalResult(getRuntime()->evaluate(script, frame, echo, fileName)); };

   /// Evaluate an arbitrary line of script.
   ///
   /// This wraps dVsprintf(), so you can substitute parameters into the code being executed.
   /// NOTE: This function restores the console stack on return.
   inline EvalResult evaluatef(const char* string, ...)
   {
      va_list args;
      va_start(args, string);
      EvalResult result = setLastEvalResult(getRuntime()->evaluatef(string, args));
      va_end(args);
      return result;
   };

   /// Executes a script file and compiles it for use in script.
   ///
   /// @param  string   File name that is the script to be executed and compiled.
   /// @param fileName Path to the file to execute
   /// @param noCalls Deprecated
   /// @param journalScript Deprecated
   ///
   /// @return True if the script was successfully executed, false if not.
   inline bool executeFile(const char* fileName, bool noCalls, bool journalScript) { return getRuntime()->executeFile(fileName, noCalls, journalScript); };
}

#endif
