#ifndef _TORQUESCRIPT_RUNTIME_H_
#define _TORQUESCRIPT_RUNTIME_H_
#include "ast.h"
#include "console/runtime.h"

namespace TorqueScript
{
   class TorqueScriptRuntime : public Con::Runtime
   {
   public:
      TorqueScriptRuntime();
      ~TorqueScriptRuntime() override;

      void expandEscapedCharacters(char* dest, const char* src) override { expandEscape(dest, src); }
      bool collapseEscapedCharacters(char* buf) override { return collapseEscape(buf); }
      Con::EvalResult evaluate(const char* string, bool echo = false, const char* fileName = NULL) override;
      Con::EvalResult evaluate(const char* script, S32 frame, bool echo = false, const char *fileName = NULL) override;
      Con::EvalResult evaluatef(const char* string, ...) override;
      bool executeFile(const char* fileName, bool noCalls, bool journalScript) override;
      bool compile(const char* fileName, bool overrideNoDso);
   };

   inline TorqueScriptRuntime* gRuntime = new TorqueScriptRuntime();
   inline TorqueScriptRuntime* getRuntime() { return gRuntime; }
}

#endif
