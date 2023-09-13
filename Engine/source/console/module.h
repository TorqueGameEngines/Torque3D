#ifndef _SCRIPT_MODULE_H_
#define _SCRIPT_MODULE_H_
#include "runtime.h"
#include "console/console.h"
#include "platform/types.h"

namespace Con
{
   class Module
   {
   private:
      S32 mRefCount = 0;
   public:
      Module() = default;
      virtual ~Module() = default;

      void incRefCount() { mRefCount++; }
      void decRefCount() { mRefCount--; if (!mRefCount) delete this; }
      virtual const char* getFunctionArgs(StringTableEntry functionName, U32 functionOffset) = 0;
      virtual const char* getPath() = 0;
      virtual const char* getName() = 0;

      virtual EvalResult exec(U32 offset, const char* fnName, Namespace* ns, U32 argc,
                              ConsoleValue* argv, bool noCalls, StringTableEntry packageName,
                              S32 setFrame = -1) = 0;
      virtual void findBreakLine(U32 ip, U32& line, U32& instruction) = 0;
      virtual const char *getFileLine(U32 ip) = 0;

      /// Returns the first breakable line or 0 if none was found.
      /// @param lineNumber The one based line number.
      virtual U32 findFirstBreakLine(U32 lineNumber) = 0;

      /// Set a OP_BREAK instruction on a line. If a break
      /// is not possible on that line it returns false.
      /// @param lineNumber The one based line number.
      virtual bool setBreakpoint(U32 lineNumber) = 0;

      virtual void setAllBreaks() = 0;
      virtual void clearAllBreaks() = 0;
      virtual void clearBreakpoint(U32 lineNumber) = 0;
      virtual Vector<U32> getBreakableLines() = 0;
   };
}

#endif
