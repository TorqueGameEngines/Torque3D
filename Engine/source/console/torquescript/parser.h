#ifndef _TORQUESCRIPT_PARSER_H_
#define _TORQUESCRIPT_PARSER_H_
#include <cstdio>

#include "platform/types.h"

const char* CMDGetCurrentFile();
S32 CMDGetCurrentLine();
S32 CMDparse();
void CMDrestart(FILE* in);
void CMDSetScanBuffer(const char *sb, const char *fn);

extern void expandEscape(char *dest, const char *src);
extern bool collapseEscape(char *buf);

class TorqueScriptParser
{
public:
   TorqueScriptParser() = default;

   const char* mExtension;

   //-----------------------------------------------------------------------------
   /// \brief Function for GetCurrentFile from the lexer
   //-----------------------------------------------------------------------------
   const char* getCurrentFile() { return CMDGetCurrentFile(); }

   //-----------------------------------------------------------------------------
   /// \brief Function for GetCurrentLine from the lexer
   //-----------------------------------------------------------------------------
   S32 getCurrentLine() { return CMDGetCurrentLine(); }

   //-----------------------------------------------------------------------------
   /// \brief Function for Parse from the lexer
   //-----------------------------------------------------------------------------
   S32 parse() { return CMDparse(); }

   //-----------------------------------------------------------------------------
   /// \brief Function for Restart from the lexer
   //-----------------------------------------------------------------------------
   void restart(FILE *pInputFile) { CMDrestart(pInputFile); }

   //-----------------------------------------------------------------------------
   /// \brief Function for SetScanBuffer from the lexer
   //-----------------------------------------------------------------------------
   void setScanBuffer(const char* sb, const char* fn) { CMDSetScanBuffer(sb, fn); }
};

#endif
