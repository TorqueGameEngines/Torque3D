/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_CMD_CMDGRAM_H_INCLUDED
# define YY_CMD_CMDGRAM_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int CMDdebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    rwDEFINE = 258,                /* rwDEFINE  */
    rwENDDEF = 259,                /* rwENDDEF  */
    rwDECLARE = 260,               /* rwDECLARE  */
    rwDECLARESINGLETON = 261,      /* rwDECLARESINGLETON  */
    rwBREAK = 262,                 /* rwBREAK  */
    rwELSE = 263,                  /* rwELSE  */
    rwCONTINUE = 264,              /* rwCONTINUE  */
    rwGLOBAL = 265,                /* rwGLOBAL  */
    rwIF = 266,                    /* rwIF  */
    rwNIL = 267,                   /* rwNIL  */
    rwRETURN = 268,                /* rwRETURN  */
    rwWHILE = 269,                 /* rwWHILE  */
    rwDO = 270,                    /* rwDO  */
    rwENDIF = 271,                 /* rwENDIF  */
    rwENDWHILE = 272,              /* rwENDWHILE  */
    rwENDFOR = 273,                /* rwENDFOR  */
    rwDEFAULT = 274,               /* rwDEFAULT  */
    rwFOR = 275,                   /* rwFOR  */
    rwFOREACH = 276,               /* rwFOREACH  */
    rwFOREACHSTR = 277,            /* rwFOREACHSTR  */
    rwIN = 278,                    /* rwIN  */
    rwDATABLOCK = 279,             /* rwDATABLOCK  */
    rwSWITCH = 280,                /* rwSWITCH  */
    rwCASE = 281,                  /* rwCASE  */
    rwSWITCHSTR = 282,             /* rwSWITCHSTR  */
    rwCASEOR = 283,                /* rwCASEOR  */
    rwPACKAGE = 284,               /* rwPACKAGE  */
    rwASSERT = 285,                /* rwASSERT  */
    ILLEGAL_TOKEN = 286,           /* ILLEGAL_TOKEN  */
    CHRCONST = 287,                /* CHRCONST  */
    INTCONST = 288,                /* INTCONST  */
    TTAG = 289,                    /* TTAG  */
    VAR = 290,                     /* VAR  */
    IDENT = 291,                   /* IDENT  */
    TYPEIDENT = 292,               /* TYPEIDENT  */
    DOCBLOCK = 293,                /* DOCBLOCK  */
    STRATOM = 294,                 /* STRATOM  */
    TAGATOM = 295,                 /* TAGATOM  */
    FLTCONST = 296,                /* FLTCONST  */
    opINTNAME = 297,               /* opINTNAME  */
    opINTNAMER = 298,              /* opINTNAMER  */
    opMINUSMINUS = 299,            /* opMINUSMINUS  */
    opPLUSPLUS = 300,              /* opPLUSPLUS  */
    opSHL = 301,                   /* opSHL  */
    opSHR = 302,                   /* opSHR  */
    opPLASN = 303,                 /* opPLASN  */
    opMIASN = 304,                 /* opMIASN  */
    opMLASN = 305,                 /* opMLASN  */
    opDVASN = 306,                 /* opDVASN  */
    opMODASN = 307,                /* opMODASN  */
    opANDASN = 308,                /* opANDASN  */
    opXORASN = 309,                /* opXORASN  */
    opORASN = 310,                 /* opORASN  */
    opSLASN = 311,                 /* opSLASN  */
    opSRASN = 312,                 /* opSRASN  */
    opCAT = 313,                   /* opCAT  */
    opEQ = 314,                    /* opEQ  */
    opNE = 315,                    /* opNE  */
    opGE = 316,                    /* opGE  */
    opLE = 317,                    /* opLE  */
    opAND = 318,                   /* opAND  */
    opOR = 319,                    /* opOR  */
    opSTREQ = 320,                 /* opSTREQ  */
    opSTRNE = 321,                 /* opSTRNE  */
    opCOLONCOLON = 322,            /* opCOLONCOLON  */
    UNARY = 323                    /* UNARY  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 107 "CMDgram.y"

   Token< char >           c;
   Token< int >            i;
   Token< const char* >    s;
   Token< char* >          str;
   Token< double >         f;
   StmtNode*               stmt;
   ExprNode*               expr;
   SlotAssignNode*         slist;
   VarNode*                var;
   SlotDecl                slot;
   InternalSlotDecl        intslot;
   ObjectBlockDecl         odcl;
   ObjectDeclNode*         od;
   AssignDecl              asn;
   IfStmtNode*             ifnode;

#line 150 "CMDgram.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE CMDlval;
extern YYLTYPE CMDlloc;

int CMDparse (void);


#endif /* !YY_CMD_CMDGRAM_H_INCLUDED  */
