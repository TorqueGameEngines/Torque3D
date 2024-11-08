%option yylineno nounput
%{

// flex --nounput -o CMDscan.cpp -P CMD CMDscan.l

#define YYLMAX 4096
#define YY_NO_UNISTD_H

#include <stdio.h>
#include "platform/platform.h"
#include "core/stringTable.h"
#include "console/console.h"
#include "console/torquescript/compiler.h"
#include "console/dynamicTypes.h"
#include "core/strings/stringFunctions.h"

template< typename T >
struct Token
{
   T value;
   S32 lineNumber;
};

// Can't have ctors in structs used in unions, so we have this.
template< typename T >
inline Token< T > MakeToken( T value, U32 lineNumber )
{
   Token< T > result;
   result.value = value;
   result.lineNumber = lineNumber;
   return result;
}

#include "console/torquescript/CMDgram.h"

// HACK: C++17 and beyond can't use register keyword
#define register

using namespace Compiler;

#define YY_NEVER_INTERACTIVE 1

// Some basic parsing primitives...
static int Sc_ScanDocBlock();
static int Sc_ScanString(int ret);
static int Sc_ScanNum();
static int Sc_ScanVar();
static int Sc_ScanHex();
static int Sc_ScanIdent();

// Deal with debuggability of FLEX.
#ifdef TORQUE_DEBUG
#define FLEX_DEBUG 1
#else
#define FLEX_DEBUG 0
#endif

Vector<String> lines;

// Install our own input code...
#undef CMDgetc
int CMDgetc();

// Hack to make windows lex happy.
#ifndef isatty
inline int isatty(int) { return 0; }
#endif
static int yycolumn = 1;
// Wrap our getc, so that lex doesn't try to do its own buffering/file IO.
#define YY_INPUT(buf,result,max_size) \
   { \
      int c = '*', n; \
      for ( n = 0; n < max_size && \
            (c = CMDgetc()) != EOF && c != '\n'; ++n ) \
         buf[n] = (char) c; \
      if ( c == '\n' ) \
         buf[n++] = (char) c; yycolumn = 1;\
      result = n; \
   }

#define YY_USER_ACTION do { \
    CMDlloc.first_line = CMDlloc.last_line = yylineno; \
    CMDlloc.first_column = yycolumn; CMDlloc.last_column = yycolumn + yyleng - 1; \
    yycolumn += yyleng; \
    } while(0);

// File state
void CMDSetScanBuffer(const char *sb, const char *fn);

// Error reporting
void CMDerror(const char * s, ...);

// Reset the parser.
void CMDrestart(FILE *in);

%}

DIGIT    [0-9]
INTEGER  {DIGIT}+
FLOAT    ({INTEGER}?\.{INTEGER})|({INTEGER}(\.{INTEGER})?[eE][+-]?{INTEGER})
LETTER   [A-Za-z_]
FILECHAR [A-Za-z_\.]
VARMID   [:A-Za-z0-9_]
IDTAIL   [A-Za-z0-9_]
VARTAIL  {VARMID}*{IDTAIL}
VAR      [$%]{LETTER}{VARTAIL}*
ID       {LETTER}{IDTAIL}*
ILID     [$%]{DIGIT}+{LETTER}{VARTAIL}*
FILENAME {FILECHAR}+
SPACE    [ \t\v\f]
HEXDIGIT [a-fA-F0-9]

%%
         ;
{SPACE}+ { }
("///"([^/\n\r][^\n\r]*)?[\n\r]+)+ { return(Sc_ScanDocBlock()); }
"//"[^\n\r]*   ;
[\r]        ;
\n.*        { 
   yycolumn = 1;
   lines.push_back(String::ToString("%s", yytext+1));
   if (lines.size() > Con::getIntVariable("$scriptErrorLineCount", 10))
      lines.erase(lines.begin());

   yyless(1);
}
\"(\\.|[^\\"\n\r])*\"      { return(Sc_ScanString(STRATOM)); }
\'(\\.|[^\\'\n\r])*\'      { return(Sc_ScanString(TAGATOM)); }
"=="        { CMDlval.i = MakeToken< int >( opEQ, yylineno ); return opEQ; }
"!="        { CMDlval.i = MakeToken< int >( opNE, yylineno ); return opNE; }
">="        { CMDlval.i = MakeToken< int >( opGE, yylineno ); return opGE; }
"<="        { CMDlval.i = MakeToken< int >( opLE, yylineno ); return opLE; }
"&&"        { CMDlval.i = MakeToken< int >( opAND, yylineno ); return opAND; }
"||"        { CMDlval.i = MakeToken< int >( opOR, yylineno ); return opOR; }
"::"        { CMDlval.i = MakeToken< int >( opCOLONCOLON, yylineno ); return opCOLONCOLON; }
"--"        { CMDlval.i = MakeToken< int >( opMINUSMINUS, yylineno ); return opMINUSMINUS; }
"++"        { CMDlval.i = MakeToken< int >( opPLUSPLUS, yylineno ); return opPLUSPLUS; }
"$="        { CMDlval.i = MakeToken< int >( opSTREQ, yylineno ); return opSTREQ; }
"!$="       { CMDlval.i = MakeToken< int >( opSTRNE, yylineno ); return opSTRNE; }
"<<"        { CMDlval.i = MakeToken< int >( opSHL, yylineno ); return opSHL; }
">>"        { CMDlval.i = MakeToken< int >( opSHR, yylineno ); return opSHR; }
"+="        { CMDlval.i = MakeToken< int >( opPLASN, yylineno ); return opPLASN; }
"-="        { CMDlval.i = MakeToken< int >( opMIASN, yylineno ); return opMIASN; }
"*="        { CMDlval.i = MakeToken< int >( opMLASN, yylineno ); return opMLASN; }
"/="        { CMDlval.i = MakeToken< int >( opDVASN, yylineno ); return opDVASN; }
"%="        { CMDlval.i = MakeToken< int >( opMODASN, yylineno ); return opMODASN; }
"&="        { CMDlval.i = MakeToken< int >( opANDASN, yylineno ); return opANDASN; }
"^="        { CMDlval.i = MakeToken< int >( opXORASN, yylineno ); return opXORASN; }
"|="        { CMDlval.i = MakeToken< int >( opORASN, yylineno ); return opORASN; }
"<<="       { CMDlval.i = MakeToken< int >( opSLASN, yylineno ); return opSLASN; }
">>="       { CMDlval.i = MakeToken< int >( opSRASN, yylineno ); return opSRASN; }
"->"        { CMDlval.i = MakeToken< int >( opINTNAME, yylineno ); return opINTNAME; }
"-->"       { CMDlval.i = MakeToken< int >( opINTNAMER, yylineno ); return opINTNAMER; }
"NL"        { CMDlval.i = MakeToken< int >( '\n', yylineno ); return '@'; }
"TAB"       { CMDlval.i = MakeToken< int >( '\t', yylineno ); return '@'; }
"SPC"       { CMDlval.i = MakeToken< int >( ' ', yylineno ); return '@'; }
"@"         { CMDlval.i = MakeToken< int >( 0, yylineno ); return '@'; }
"/*" { /* this comment stops syntax highlighting from getting messed up when editing the lexer in TextPad */
         int c = 0, l;
         for ( ; ; )
         {
            l = c;
            c = yyinput();

            // Is this an open comment?
            if ( c == EOF )
            {
               CMDerror( "unexpected end of file found in comment" );
               break;
            }

            // Did we find the end of the comment?
            else if ( l == '*' && c == '/' )
               break;
         }
      }
"?" |
"[" |
"]" |
"(" |
")" |
"+" |
"-" |
"*" |
"/" |
"<" |
">" |
"|" |
"." |
"!" |
":" |
";" |
"{" |
"}" |
"," |
"&" |
"%" |
"^" |
"~" |
"="         { CMDlval.i = MakeToken< int >( CMDtext[ 0 ], yylineno ); return CMDtext[ 0 ]; }
"in"        { CMDlval.i = MakeToken< int >( rwIN, yylineno ); return(rwIN); }
"or"        { CMDlval.i = MakeToken< int >( rwCASEOR, yylineno ); return(rwCASEOR); }
"break"     { CMDlval.i = MakeToken< int >( rwBREAK, yylineno ); return(rwBREAK); }
"return"    { CMDlval.i = MakeToken< int >( rwRETURN, yylineno ); return(rwRETURN); }
"else"      { CMDlval.i = MakeToken< int >( rwELSE, yylineno ); return(rwELSE); }
"assert"    { CMDlval.i = MakeToken< int >( rwASSERT, yylineno ); return(rwASSERT); }
"while"     { CMDlval.i = MakeToken< int >( rwWHILE, yylineno ); return(rwWHILE); }
"do"        { CMDlval.i = MakeToken< int >( rwDO, yylineno ); return(rwDO); }
"if"        { CMDlval.i = MakeToken< int >( rwIF, yylineno ); return(rwIF); }
"foreach$"  { CMDlval.i = MakeToken< int >( rwFOREACHSTR, yylineno ); return(rwFOREACHSTR); }
"foreach"   { CMDlval.i = MakeToken< int >( rwFOREACH, yylineno ); return(rwFOREACH); }
"for"       { CMDlval.i = MakeToken< int >( rwFOR, yylineno ); return(rwFOR); }
"continue"  { CMDlval.i = MakeToken< int >( rwCONTINUE, yylineno ); return(rwCONTINUE); }
"function"  { CMDlval.i = MakeToken< int >( rwDEFINE, yylineno ); return(rwDEFINE); }
"new"       { CMDlval.i = MakeToken< int >( rwDECLARE, yylineno ); return(rwDECLARE); }
"singleton" { CMDlval.i = MakeToken< int >( rwDECLARESINGLETON, yylineno ); return(rwDECLARESINGLETON); }
"datablock" { CMDlval.i = MakeToken< int >( rwDATABLOCK, yylineno ); return(rwDATABLOCK); }
"case"      { CMDlval.i = MakeToken< int >( rwCASE, yylineno ); return(rwCASE); }
"switch$"   { CMDlval.i = MakeToken< int >( rwSWITCHSTR, yylineno ); return(rwSWITCHSTR); }
"switch"    { CMDlval.i = MakeToken< int >( rwSWITCH, yylineno ); return(rwSWITCH); }
"default"   { CMDlval.i = MakeToken< int >( rwDEFAULT, yylineno ); return(rwDEFAULT); }
"package"   { CMDlval.i = MakeToken< int >( rwPACKAGE, yylineno ); return(rwPACKAGE); }
"namespace" { CMDlval.i = MakeToken< int >( rwNAMESPACE, yylineno ); return(rwNAMESPACE); }
"true"      { CMDlval.i = MakeToken< int >( 1, yylineno ); return INTCONST; }
"false"     { CMDlval.i = MakeToken< int >( 0, yylineno ); return INTCONST; }
{VAR}       { return(Sc_ScanVar()); }

{ID}        { return Sc_ScanIdent(); }
0[xX]{HEXDIGIT}+ return(Sc_ScanHex());
{INTEGER}   { CMDtext[CMDleng] = 0; CMDlval.i = MakeToken< int >( dAtoi(CMDtext), yylineno ); return INTCONST; }
{FLOAT}     return Sc_ScanNum();
{ILID}      return(ILLEGAL_TOKEN);
.           return(ILLEGAL_TOKEN);
%%

static const char *scanBuffer;
static const char *fileName;
static int scanIndex;
extern YYLTYPE CMDlloc;

const char * CMDGetCurrentFile()
{
   return fileName;
}

int CMDGetCurrentLine()
{
   return yylineno;
}

extern bool gConsoleSyntaxError;

void CMDerror(const char *format, ...)
{
   Compiler::gSyntaxError = true;

   const int BUFMAX = 1024;
   char tempBuf[BUFMAX];
   va_list args;
   va_start( args, format );
#ifdef TORQUE_OS_WIN
   _vsnprintf( tempBuf, BUFMAX, format, args );
#else
   vsnprintf( tempBuf, BUFMAX, format, args );
#endif
   va_end(args);

   if(fileName)
   {
      Con::errorf(ConsoleLogEntry::Script, "%s Line: %d - %s", fileName, yylineno, tempBuf);
      // Update the script-visible error buffer.
      const char *prevStr = Con::getVariable("$ScriptError");
      if (prevStr[0])
         dSprintf(tempBuf, sizeof(tempBuf), "%s\n%s Line: %d - Syntax error.", prevStr, fileName, yylineno);
      else
         dSprintf(tempBuf, sizeof(tempBuf), "%s Line: %d - Syntax error.", fileName, yylineno);
      Con::setVariable("$ScriptError", tempBuf);

      // We also need to mark that we came up with a new error.
      static S32 sScriptErrorHash=1000;
      Con::setIntVariable("$ScriptErrorHash", sScriptErrorHash++);

   }
   else
   {
      Con::errorf(ConsoleLogEntry::Script, tempBuf);
   }
}

void CMDSetScanBuffer(const char *sb, const char *fn)
{
   scanBuffer = sb;
   fileName = fn;
   scanIndex = 0;
   yylineno = 1;
   lines.clear();
}

int CMDgetc()
{
   int ret = scanBuffer[scanIndex];
   if(ret)
      scanIndex++;
   else
      ret = -1;
   return ret;
}

int CMDwrap()
{
   return 1;
}

static int Sc_ScanVar()
{
   // Truncate the temp buffer...
   CMDtext[CMDleng] = 0;

   // Make it a stringtable string!
   CMDlval.s = MakeToken< StringTableEntry >( StringTable->insert(CMDtext), yylineno );
   return(VAR);
}

static int charConv(int in)
{
   switch(in)
   {
      case 'r':
         return '\r';
      case 'n':
         return '\n';
      case 't':
         return '\t';
      default:
         return in;
   }
}

static int getHexDigit(char c)
{
   if(c >= '0' && c <= '9')
      return c - '0';
   if(c >= 'A' && c <= 'F')
      return c - 'A' + 10;
   if(c >= 'a' && c <= 'f')
      return c - 'a' + 10;
   return -1;
}

static int Sc_ScanDocBlock()
{
   S32 len = dStrlen(CMDtext);
   char* text = (char *) consoleAlloc(len + 1);
   S32 line = yylineno;

   for( S32 i = 0, j = 0; j <= len; j++ )
   {
      if( ( j <= (len - 2) ) && ( CMDtext[j] == '/' ) && ( CMDtext[j + 1] == '/' ) && ( CMDtext[j + 2] == '/' ) )
      {
         j += 2;
         continue;
      }

      if( CMDtext[j] == '\r' )
         continue;

      text[i++] = CMDtext[j];
   }

   CMDlval.str = MakeToken< char* >( text, line );
   return(DOCBLOCK);
}

static int Sc_ScanString(int ret)
{
   CMDtext[CMDleng - 1] = 0;
   if(!collapseEscape(CMDtext+1))
      return -1;

   dsize_t bufferLen = dStrlen( CMDtext );
   char* buffer = ( char* ) consoleAlloc( bufferLen );
   dStrcpy( buffer, CMDtext + 1, bufferLen );

   CMDlval.str = MakeToken< char* >( buffer, yylineno );
   return ret;
}

static int Sc_ScanIdent()
{
   ConsoleBaseType *type;

   CMDtext[CMDleng] = 0;

   if((type = ConsoleBaseType::getTypeByName(CMDtext)) != NULL)
   {
      /* It's a type */
      CMDlval.i = MakeToken< int >( type->getTypeID(), yylineno );
      return TYPEIDENT;
   }

   /* It's an identifier */
   CMDlval.s = MakeToken< StringTableEntry >( StringTable->insert(CMDtext), yylineno );
   return IDENT;
}

void expandEscape(char *dest, const char *src)
{
   U8 c;
   while((c = (U8) *src++) != 0)
   {
      if(c == '\"')
      {
         *dest++ = '\\';
         *dest++ = '\"';
      }
      else if(c == '\\')
      {
         *dest++ = '\\';
         *dest++ = '\\';
      }
      else if(c == '\r')
      {
         *dest++ = '\\';
         *dest++ = 'r';
      }
      else if(c == '\n')
      {
         *dest++ = '\\';
         *dest++ = 'n';
      }
      else if(c == '\t')
      {
         *dest++ = '\\';
         *dest++ = 't';
      }
      else if(c == '\'')
      {
         *dest++ = '\\';
         *dest++ = '\'';
      }
      else if((c >= 1 && c <= 7) ||
              (c >= 11 && c <= 12) ||
              (c >= 14 && c <= 15))
      {
        /*  Remap around: \b = 0x8, \t = 0x9, \n = 0xa, \r = 0xd */
        static U8 expandRemap[15] = { 0x0,
                                        0x0,
                                        0x1,
                                        0x2,
                                        0x3,
                                        0x4,
                                        0x5,
                                        0x6,
                                        0x0,
                                        0x0,
                                        0x0,
                                        0x7,
                                        0x8,
                                        0x0,
                                        0x9 };

         *dest++ = '\\';
         *dest++ = 'c';
         if(c == 15)
            *dest++ = 'r';
         else if(c == 16)
            *dest++ = 'p';
         else if(c == 17)
            *dest++ = 'o';
         else
            *dest++ = expandRemap[c] + '0';
      }
      else if(c < 32)
      {
         *dest++ = '\\';
         *dest++ = 'x';
         S32 dig1 = c >> 4;
         S32 dig2 = c & 0xf;
         if(dig1 < 10)
            dig1 += '0';
         else
            dig1 += 'A' - 10;
         if(dig2 < 10)
            dig2 += '0';
         else
            dig2 += 'A' - 10;
         *dest++ = dig1;
         *dest++ = dig2;
      }
      else
         *dest++ = c;
   }
   *dest = '\0';
}

bool collapseEscape(char *buf)
{
   S32 len = dStrlen(buf) + 1;
   for(S32 i = 0; i < len;)
   {
      if(buf[i] == '\\')
      {
         if(buf[i+1] == 'x')
         {
            S32 dig1 = getHexDigit(buf[i+2]);
            if(dig1 == -1)
               return false;

            S32 dig2 = getHexDigit(buf[i+3]);
            if(dig2 == -1)
               return false;
            buf[i] = dig1 * 16 + dig2;
            dMemmove(buf + i + 1, buf + i + 4, len - i - 3);
            len -= 3;
            i++;
         }
         else if(buf[i+1] == 'c')
         {
            /*  Remap around: \b = 0x8, \t = 0x9, \n = 0xa, \r = 0xd */
            static U8 collapseRemap[10] = { 0x1,
                                              0x2,
                                              0x3,
                                              0x4,
                                              0x5,
                                              0x6,
                                              0x7,
                                              0xb,
                                              0xc,
                                              0xe };

            if(buf[i+2] == 'r')
                buf[i] = 15;
            else if(buf[i+2] == 'p')
               buf[i] = 16;
            else if(buf[i+2] == 'o')
               buf[i] = 17;
            else
            {
                int dig1 = buf[i+2] - '0';
                if(dig1 < 0 || dig1 > 9)
                   return false;
                buf[i] = collapseRemap[dig1];
            }
            // Make sure we don't put 0x1 at the beginning of the string.
            if ((buf[i] == 0x1) && (i == 0))
            {
               buf[i] = 0x2;
               buf[i+1] = 0x1;
               dMemmove(buf + i + 2, buf + i + 3, len - i - 1);
               len -= 1;
            }
            else
            {
               dMemmove(buf + i + 1, buf + i + 3, len - i - 2);
               len -= 2;
            }
            i++;
         }
         else
         {
            buf[i] = charConv(buf[i+1]);
            dMemmove(buf + i + 1, buf + i + 2, len - i - 1);
            len--;
            i++;
         }
      }
      else
         i++;
   }
   return true;
}

static int Sc_ScanNum()
{
   CMDtext[CMDleng] = 0;
   CMDlval.f = MakeToken< double >( dAtof(CMDtext), yylineno );
   return(FLTCONST);
}

static int Sc_ScanHex()
{
   S32 val = 0;
   dSscanf(CMDtext, "%x", &val);
   CMDlval.i = MakeToken< int >( val, yylineno );
   return INTCONST;
}

void CMD_reset()
{
   CMDrestart(NULL);
}
