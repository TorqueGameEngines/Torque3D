#ifndef _RUNTIME_H_
#define _RUNTIME_H_

#include "console/console.h"

namespace Con
{
   struct EvalResult
   {
      bool valid;
      ConsoleValue value;
      String error;

   public:
      EvalResult() {}

      EvalResult(ConsoleValue&& pValue)
      {
         valid = true;
         value = (ConsoleValue&&)pValue;
      }

      EvalResult(String errorMessage)
      {
         valid = false;
         error = errorMessage;
      }
   };

   struct Error
   {
      const char* message;
   };

   struct SyntaxError : Error {};

   class Stack
   {
      class Frame
      {
      public:
         ConsoleValue* lookup(const char*);
      };

   public:
      S32 getDepth();
      Frame getFrame(S32 idx);
   };

   class Runtime
   {
   private:
      Stack mStack;
   public:
      virtual ~Runtime() = default;
      virtual Stack getStack() { return mStack; }

      /// Convert from a relative script path to an absolute script path.
      ///
      /// This is used in (among other places) the exec() script function, which
      /// takes a parameter indicating a script file and executes it. Script paths
      /// can be one of:
      ///      - <b>Absolute:</b> <i>fps/foo/bar.tscript</i> Paths of this sort are passed
      ///        through.
      ///      - <b>Mod-relative:</b> <i>~/foo/bar.tscript</i> Paths of this sort have their
      ///        replaced with the name of the current mod.
      ///      - <b>File-relative:</b> <i>./baz/blip.tscript</i> Paths of this sort are
      ///        calculated relative to the path of the current scripting file.
      ///
      /// @note This function determines paths relative to the currently executing
      ///       CodeBlock. Calling it outside of script execution will result in
      ///       it directly copying src to filename, since it won't know to what the
      ///       path is relative!
      ///
      /// @param  filename    Pointer to string buffer to fill with absolute path.
      /// @param  size        Size of buffer pointed to by filename.
      /// @param  src         Original, possibly relative script path.
      bool expandScriptFilename(char *filename, U32 size, const char *src);
      bool expandToolScriptFilename(char *filename, U32 size, const char *src);
      bool collapseScriptFilename(char *filename, U32 size, const char *src);

      virtual void expandEscapedCharacters(char* dest, const char* src) = 0;
      virtual bool collapseEscapedCharacters(char* buf) = 0;

      /// Evaluate an arbitrary chunk of code.
      ///
      /// @param  string   Buffer containing code to execute.
      /// @param  echo     Should we echo the string to the console?
      /// @param  fileName Indicate what file this code is coming from; used in error reporting and such.
      /// NOTE: This function restores the console stack on return.
      virtual EvalResult evaluate(const char* string, bool echo = false, const char *fileName = NULL) = 0;

      virtual EvalResult evaluate(const char* string, S32 frame, bool echo = false, const char *fileName = NULL) = 0;

      /// Evaluate an arbitrary line of script.
      ///
      /// This wraps dVsprintf(), so you can substitute parameters into the code being executed.
      /// NOTE: This function restores the console stack on return.
      virtual EvalResult evaluatef(const char* string, ...) = 0;

      /// Executes a script file and compiles it for use in script.
      ///
      /// @param  fileName File name that is the script to be executed and compiled.
      /// @param noCalls Deprecated
      /// @param journalScript Deprecated
      ///
      /// @return True if the script was successfully executed, false if not.
      virtual bool executeFile(const char* fileName, bool noCalls, bool journalScript) = 0;
   };
}

#endif
