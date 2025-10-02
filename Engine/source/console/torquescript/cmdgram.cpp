/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         CMDparse
#define yylex           CMDlex
#define yyerror         CMDerror
#define yydebug         CMDdebug
#define yynerrs         CMDnerrs
#define yylval          CMDlval
#define yychar          CMDchar
#define yylloc          CMDlloc

/* First part of user prologue.  */
#line 4 "CMDgram.y"


// bison --defines=cmdgram.h --verbose -o cmdgram.cpp -p CMD CMDgram.y

// Make sure we don't get gram.h twice.
#define _CMDGRAM_H_

#include <stdlib.h>
#include <stdio.h>
#include "console/console.h"
#include "console/torquescript/compiler.h"
#include "console/consoleInternal.h"
#include "core/strings/stringFunctions.h"

#ifndef YYDEBUG
#define YYDEBUG 0
#endif

#define YYSSIZE 350

int outtext(char *fmt, ...);
extern int serrors;
extern Vector<String> lines;

#define nil 0
#undef YY_ARGS
#define YY_ARGS(x)   x

int CMDlex();
void CMDerror(const char *, ...);


#ifdef alloca
#undef alloca
#endif
#define alloca dMalloc

template< typename T >
struct Token
{
   T value;
   U32 lineNumber;
};

#line 49 "CMDgram.y"

        /* Reserved Word Definitions */
#line 60 "CMDgram.y"

        /* Constants and Identifier Definitions */
#line 74 "CMDgram.y"

        /* Operator Definitions */

#line 134 "CMDgram.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "CMDgram.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_rwDEFINE = 3,                   /* rwDEFINE  */
  YYSYMBOL_rwENDDEF = 4,                   /* rwENDDEF  */
  YYSYMBOL_rwDECLARE = 5,                  /* rwDECLARE  */
  YYSYMBOL_rwDECLARESINGLETON = 6,         /* rwDECLARESINGLETON  */
  YYSYMBOL_rwBREAK = 7,                    /* rwBREAK  */
  YYSYMBOL_rwELSE = 8,                     /* rwELSE  */
  YYSYMBOL_rwCONTINUE = 9,                 /* rwCONTINUE  */
  YYSYMBOL_rwGLOBAL = 10,                  /* rwGLOBAL  */
  YYSYMBOL_rwIF = 11,                      /* rwIF  */
  YYSYMBOL_rwNIL = 12,                     /* rwNIL  */
  YYSYMBOL_rwRETURN = 13,                  /* rwRETURN  */
  YYSYMBOL_rwWHILE = 14,                   /* rwWHILE  */
  YYSYMBOL_rwDO = 15,                      /* rwDO  */
  YYSYMBOL_rwENDIF = 16,                   /* rwENDIF  */
  YYSYMBOL_rwENDWHILE = 17,                /* rwENDWHILE  */
  YYSYMBOL_rwENDFOR = 18,                  /* rwENDFOR  */
  YYSYMBOL_rwDEFAULT = 19,                 /* rwDEFAULT  */
  YYSYMBOL_rwFOR = 20,                     /* rwFOR  */
  YYSYMBOL_rwFOREACH = 21,                 /* rwFOREACH  */
  YYSYMBOL_rwFOREACHSTR = 22,              /* rwFOREACHSTR  */
  YYSYMBOL_rwIN = 23,                      /* rwIN  */
  YYSYMBOL_rwDATABLOCK = 24,               /* rwDATABLOCK  */
  YYSYMBOL_rwSWITCH = 25,                  /* rwSWITCH  */
  YYSYMBOL_rwCASE = 26,                    /* rwCASE  */
  YYSYMBOL_rwSWITCHSTR = 27,               /* rwSWITCHSTR  */
  YYSYMBOL_rwCASEOR = 28,                  /* rwCASEOR  */
  YYSYMBOL_rwPACKAGE = 29,                 /* rwPACKAGE  */
  YYSYMBOL_rwNAMESPACE = 30,               /* rwNAMESPACE  */
  YYSYMBOL_rwCLASS = 31,                   /* rwCLASS  */
  YYSYMBOL_rwASSERT = 32,                  /* rwASSERT  */
  YYSYMBOL_ILLEGAL_TOKEN = 33,             /* ILLEGAL_TOKEN  */
  YYSYMBOL_CHRCONST = 34,                  /* CHRCONST  */
  YYSYMBOL_INTCONST = 35,                  /* INTCONST  */
  YYSYMBOL_TTAG = 36,                      /* TTAG  */
  YYSYMBOL_VAR = 37,                       /* VAR  */
  YYSYMBOL_IDENT = 38,                     /* IDENT  */
  YYSYMBOL_TYPEIDENT = 39,                 /* TYPEIDENT  */
  YYSYMBOL_DOCBLOCK = 40,                  /* DOCBLOCK  */
  YYSYMBOL_STRATOM = 41,                   /* STRATOM  */
  YYSYMBOL_TAGATOM = 42,                   /* TAGATOM  */
  YYSYMBOL_FLTCONST = 43,                  /* FLTCONST  */
  YYSYMBOL_44_ = 44,                       /* '+'  */
  YYSYMBOL_45_ = 45,                       /* '-'  */
  YYSYMBOL_46_ = 46,                       /* '*'  */
  YYSYMBOL_47_ = 47,                       /* '/'  */
  YYSYMBOL_48_ = 48,                       /* '<'  */
  YYSYMBOL_49_ = 49,                       /* '>'  */
  YYSYMBOL_50_ = 50,                       /* '='  */
  YYSYMBOL_51_ = 51,                       /* '.'  */
  YYSYMBOL_52_ = 52,                       /* '|'  */
  YYSYMBOL_53_ = 53,                       /* '&'  */
  YYSYMBOL_54_ = 54,                       /* '%'  */
  YYSYMBOL_55_ = 55,                       /* '('  */
  YYSYMBOL_56_ = 56,                       /* ')'  */
  YYSYMBOL_57_ = 57,                       /* ','  */
  YYSYMBOL_58_ = 58,                       /* ':'  */
  YYSYMBOL_59_ = 59,                       /* ';'  */
  YYSYMBOL_60_ = 60,                       /* '{'  */
  YYSYMBOL_61_ = 61,                       /* '}'  */
  YYSYMBOL_62_ = 62,                       /* '^'  */
  YYSYMBOL_63_ = 63,                       /* '~'  */
  YYSYMBOL_64_ = 64,                       /* '!'  */
  YYSYMBOL_65_ = 65,                       /* '@'  */
  YYSYMBOL_opINTNAME = 66,                 /* opINTNAME  */
  YYSYMBOL_opINTNAMER = 67,                /* opINTNAMER  */
  YYSYMBOL_opMINUSMINUS = 68,              /* opMINUSMINUS  */
  YYSYMBOL_opPLUSPLUS = 69,                /* opPLUSPLUS  */
  YYSYMBOL_STMT_SEP = 70,                  /* STMT_SEP  */
  YYSYMBOL_opSHL = 71,                     /* opSHL  */
  YYSYMBOL_opSHR = 72,                     /* opSHR  */
  YYSYMBOL_opPLASN = 73,                   /* opPLASN  */
  YYSYMBOL_opMIASN = 74,                   /* opMIASN  */
  YYSYMBOL_opMLASN = 75,                   /* opMLASN  */
  YYSYMBOL_opDVASN = 76,                   /* opDVASN  */
  YYSYMBOL_opMODASN = 77,                  /* opMODASN  */
  YYSYMBOL_opANDASN = 78,                  /* opANDASN  */
  YYSYMBOL_opXORASN = 79,                  /* opXORASN  */
  YYSYMBOL_opORASN = 80,                   /* opORASN  */
  YYSYMBOL_opSLASN = 81,                   /* opSLASN  */
  YYSYMBOL_opSRASN = 82,                   /* opSRASN  */
  YYSYMBOL_opCAT = 83,                     /* opCAT  */
  YYSYMBOL_opEQ = 84,                      /* opEQ  */
  YYSYMBOL_opNE = 85,                      /* opNE  */
  YYSYMBOL_opGE = 86,                      /* opGE  */
  YYSYMBOL_opLE = 87,                      /* opLE  */
  YYSYMBOL_opAND = 88,                     /* opAND  */
  YYSYMBOL_opOR = 89,                      /* opOR  */
  YYSYMBOL_opSTREQ = 90,                   /* opSTREQ  */
  YYSYMBOL_opCOLONCOLON = 91,              /* opCOLONCOLON  */
  YYSYMBOL_92_ = 92,                       /* '['  */
  YYSYMBOL_opMDASN = 93,                   /* opMDASN  */
  YYSYMBOL_opNDASN = 94,                   /* opNDASN  */
  YYSYMBOL_opNTASN = 95,                   /* opNTASN  */
  YYSYMBOL_96_ = 96,                       /* '?'  */
  YYSYMBOL_opSTRNE = 97,                   /* opSTRNE  */
  YYSYMBOL_UNARY = 98,                     /* UNARY  */
  YYSYMBOL_99_ = 99,                       /* ']'  */
  YYSYMBOL_YYACCEPT = 100,                 /* $accept  */
  YYSYMBOL_start = 101,                    /* start  */
  YYSYMBOL_decl_list = 102,                /* decl_list  */
  YYSYMBOL_decl = 103,                     /* decl  */
  YYSYMBOL_package_decl = 104,             /* package_decl  */
  YYSYMBOL_fn_decl_list = 105,             /* fn_decl_list  */
  YYSYMBOL_statement_list = 106,           /* statement_list  */
  YYSYMBOL_stmt = 107,                     /* stmt  */
  YYSYMBOL_fn_decl_stmt = 108,             /* fn_decl_stmt  */
  YYSYMBOL_var_list_decl = 109,            /* var_list_decl  */
  YYSYMBOL_var_list = 110,                 /* var_list  */
  YYSYMBOL_datablock_decl = 111,           /* datablock_decl  */
  YYSYMBOL_object_decl = 112,              /* object_decl  */
  YYSYMBOL_parent_block = 113,             /* parent_block  */
  YYSYMBOL_object_name = 114,              /* object_name  */
  YYSYMBOL_object_args = 115,              /* object_args  */
  YYSYMBOL_object_declare_block = 116,     /* object_declare_block  */
  YYSYMBOL_object_decl_list = 117,         /* object_decl_list  */
  YYSYMBOL_stmt_block = 118,               /* stmt_block  */
  YYSYMBOL_switch_stmt = 119,              /* switch_stmt  */
  YYSYMBOL_case_block = 120,               /* case_block  */
  YYSYMBOL_case_expr = 121,                /* case_expr  */
  YYSYMBOL_if_stmt = 122,                  /* if_stmt  */
  YYSYMBOL_while_stmt = 123,               /* while_stmt  */
  YYSYMBOL_for_stmt = 124,                 /* for_stmt  */
  YYSYMBOL_foreach_stmt = 125,             /* foreach_stmt  */
  YYSYMBOL_expression_stmt = 126,          /* expression_stmt  */
  YYSYMBOL_expr = 127,                     /* expr  */
  YYSYMBOL_slot_acc = 128,                 /* slot_acc  */
  YYSYMBOL_intslot_acc = 129,              /* intslot_acc  */
  YYSYMBOL_class_name_expr = 130,          /* class_name_expr  */
  YYSYMBOL_assign_op_struct = 131,         /* assign_op_struct  */
  YYSYMBOL_stmt_expr = 132,                /* stmt_expr  */
  YYSYMBOL_funcall_expr = 133,             /* funcall_expr  */
  YYSYMBOL_assert_expr = 134,              /* assert_expr  */
  YYSYMBOL_expr_list_decl = 135,           /* expr_list_decl  */
  YYSYMBOL_expr_list = 136,                /* expr_list  */
  YYSYMBOL_slot_assign_list_opt = 137,     /* slot_assign_list_opt  */
  YYSYMBOL_slot_assign_list = 138,         /* slot_assign_list  */
  YYSYMBOL_slot_assign = 139,              /* slot_assign  */
  YYSYMBOL_aidx_expr = 140                 /* aidx_expr  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3058

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  100
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  41
/* YYNRULES -- Number of rules.  */
#define YYNRULES  164
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  387

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   329


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    64,     2,     2,     2,    54,    53,     2,
      55,    56,    46,    44,    57,    45,    51,    47,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    58,    59,
      48,    50,    49,    96,    65,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    92,     2,    99,    62,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    60,    52,    61,    63,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    93,    94,    95,    97,    98
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   166,   166,   172,   173,   178,   180,   182,   187,   192,
     194,   200,   201,   206,   207,   208,   209,   210,   211,   212,
     214,   216,   218,   220,   222,   224,   226,   231,   233,   239,
     240,   245,   247,   252,   257,   259,   261,   263,   265,   267,
     273,   274,   280,   281,   287,   288,   294,   295,   297,   299,
     304,   306,   311,   313,   318,   320,   325,   327,   329,   334,
     336,   341,   343,   348,   350,   355,   357,   359,   361,   363,
     365,   367,   369,   374,   376,   381,   386,   388,   390,   392,
     394,   396,   398,   400,   402,   404,   406,   408,   410,   412,
     414,   416,   418,   420,   422,   424,   426,   428,   430,   432,
     434,   436,   438,   440,   442,   444,   446,   448,   450,   452,
     454,   456,   458,   460,   462,   464,   466,   497,   499,   504,
     506,   511,   513,   518,   520,   522,   524,   526,   528,   530,
     532,   534,   536,   538,   540,   545,   547,   549,   551,   553,
     555,   557,   559,   561,   563,   568,   570,   572,   582,   584,
     590,   591,   596,   598,   604,   605,   610,   612,   617,   619,
     621,   623,   625,   630,   632
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  static const char *const yy_sname[] =
  {
  "end of file", "error", "invalid token", "rwDEFINE", "rwENDDEF",
  "rwDECLARE", "rwDECLARESINGLETON", "rwBREAK", "rwELSE", "rwCONTINUE",
  "rwGLOBAL", "rwIF", "rwNIL", "rwRETURN", "rwWHILE", "rwDO", "rwENDIF",
  "rwENDWHILE", "rwENDFOR", "rwDEFAULT", "rwFOR", "rwFOREACH",
  "rwFOREACHSTR", "rwIN", "rwDATABLOCK", "rwSWITCH", "rwCASE",
  "rwSWITCHSTR", "rwCASEOR", "rwPACKAGE", "rwNAMESPACE", "rwCLASS",
  "rwASSERT", "ILLEGAL_TOKEN", "CHRCONST", "INTCONST", "TTAG", "VAR",
  "IDENT", "TYPEIDENT", "DOCBLOCK", "STRATOM", "TAGATOM", "FLTCONST",
  "'+'", "'-'", "'*'", "'/'", "'<'", "'>'", "'='", "'.'", "'|'", "'&'",
  "'%'", "'('", "')'", "','", "':'", "';'", "'{'", "'}'", "'^'", "'~'",
  "'!'", "'@'", "opINTNAME", "opINTNAMER", "opMINUSMINUS", "opPLUSPLUS",
  "STMT_SEP", "opSHL", "opSHR", "opPLASN", "opMIASN", "opMLASN", "opDVASN",
  "opMODASN", "opANDASN", "opXORASN", "opORASN", "opSLASN", "opSRASN",
  "opCAT", "opEQ", "opNE", "opGE", "opLE", "opAND", "opOR", "opSTREQ",
  "opCOLONCOLON", "'['", "opMDASN", "opNDASN", "opNTASN", "'?'", "opSTRNE",
  "UNARY", "']'", "$accept", "start", "decl_list", "decl", "package_decl",
  "fn_decl_list", "statement_list", "stmt", "fn_decl_stmt",
  "var_list_decl", "var_list", "datablock_decl", "object_decl",
  "parent_block", "object_name", "object_args", "object_declare_block",
  "object_decl_list", "stmt_block", "switch_stmt", "case_block",
  "case_expr", "if_stmt", "while_stmt", "for_stmt", "foreach_stmt",
  "expression_stmt", "expr", "slot_acc", "intslot_acc", "class_name_expr",
  "assign_op_struct", "stmt_expr", "funcall_expr", "assert_expr",
  "expr_list_decl", "expr_list", "slot_assign_list_opt",
  "slot_assign_list", "slot_assign", "aidx_expr", YY_NULLPTR
  };
  return yy_sname[yysymbol];
}
#endif

#define YYPACT_NINF (-286)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-153)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -286,    27,   404,  -286,    -5,   -29,   -29,     2,    31,    39,
      46,    42,   510,    44,    47,    48,   -29,    51,    52,    57,
      56,  -286,    36,   -38,   -44,  -286,  -286,  -286,  -286,  1066,
    1066,  1066,  1066,  1066,  1066,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,    60,  2686,   266,  -286,
      72,  -286,  -286,   -27,  -286,  1066,    81,    82,  -286,  -286,
    1066,  -286,  -286,  -286,  1282,  -286,  1066,  -286,  -286,   128,
     730,   112,   134,   118,  1066,  1066,   116,  1066,  1066,  1066,
    -286,  -286,  1066,  1066,  1066,  1066,  1066,  1066,  1066,  1066,
    1066,  1066,  1066,  -286,  1066,   145,   182,   182,  1336,   182,
     182,  2686,    87,   137,  -286,  1066,  1066,  1066,  1066,  1066,
    1066,   158,  1066,  1066,  1066,  1066,  1066,   -29,   -29,  1066,
    1066,  1066,  1066,  1066,  1066,  1066,  1066,  1066,  1066,  1066,
    1066,   772,  -286,   166,   174,  1390,  1090,  1066,  1444,  -286,
    1498,   571,   159,   814,  1552,   190,   198,  1066,  1606,  1660,
     219,  1174,  1228,  2740,  2740,  2740,  2740,  2740,  2740,  2740,
    2740,  2740,  2740,  2740,  2686,   -43,   168,   170,  -286,  -286,
    1066,   193,   193,   182,   182,  2939,  2939,   -37,  2852,  2881,
     182,   144,  2986,  -286,  -286,   133,   133,  2910,  2910,  2939,
    2939,  2823,  2794,  2986,  1118,  1714,  2986,  1066,  2740,  -286,
     171,   169,   188,  -286,  1066,   187,  2686,   187,   510,   510,
    -286,  -286,  1066,   856,  1768,   898,  1066,  1066,  1822,   192,
     196,    13,  -286,  -286,   217,  1066,  -286,  1066,  2944,  -286,
    1066,  2686,  1066,  1066,  -286,  1066,   -32,   201,   225,   166,
     165,  1876,   228,   210,   210,   261,  -286,  1930,   510,  1984,
     940,   982,  2038,  2092,  2146,   216,   248,   248,   218,  -286,
     222,  2200,  2686,  1066,  -286,   227,   236,   -42,   311,  -286,
    -286,  -286,   238,   187,  -286,  1066,   239,   244,   510,  -286,
    -286,   510,   510,  2254,   510,  2308,  1024,   510,   510,   215,
    1066,   220,   223,  -286,  -286,  -286,  2740,  -286,  -286,  -286,
     616,   242,   210,   137,   243,   245,  -286,  -286,  -286,   510,
    -286,   510,   510,  2362,  -286,  -286,   117,    22,  2686,  -286,
    -286,  -286,  -286,   250,   199,   199,  -286,  -286,  -286,   510,
     254,   -33,   270,   251,   117,  -286,  1066,  -286,   661,   255,
     252,   253,    40,   199,   256,  -286,  1066,  1066,  1066,   -30,
     260,  -286,  2686,   465,  -286,   199,  -286,  -286,   263,    40,
    -286,  2416,  2470,   -36,  1066,  1066,  -286,   265,  -286,   264,
    -286,  -286,  -286,   276,  2524,   -34,  -286,  -286,  1066,  -286,
     279,   706,  2578,  1066,  -286,  2632,  -286
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     2,     1,     0,     0,     0,   108,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   107,    88,   113,   111,    26,   112,   105,   106,     0,
       0,     0,     0,     0,   150,     4,     7,     5,     6,    17,
     137,    18,    13,    14,    15,    16,     0,     0,   109,   110,
      76,   135,   136,     0,   121,     0,     0,     0,    19,    20,
       0,   108,    88,    21,     0,    76,     0,    11,    53,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     124,   123,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   140,   150,     0,    86,    87,     0,   104,
     103,   152,     0,   151,    23,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   142,    29,     0,     0,    42,    42,     0,    22,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   138,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   163,     0,     0,     0,    77,   116,
       0,    82,    83,    84,    85,    90,    91,   117,    81,    80,
      79,    78,   102,   119,   120,    97,    98,    94,    95,    92,
      93,    99,    96,   100,     0,     0,   101,     0,   143,    31,
       0,    30,     0,   122,    42,    40,    43,    40,     0,     0,
      52,    12,     0,     0,     0,     0,     0,     0,    40,     0,
       0,     0,     9,   148,     0,     0,    24,     0,   114,   145,
     150,   153,   150,     0,   115,     0,     0,     0,     0,    29,
       0,    43,     0,    44,    44,    61,    63,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    10,
       0,     0,   164,     0,   141,     0,     0,     0,    89,   144,
      11,    32,     0,    40,    41,     0,     0,     0,     0,    64,
      72,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     8,   149,    25,   139,   146,   147,   118,
       0,     0,    44,    45,    35,    39,    62,    71,    70,     0,
      68,     0,     0,     0,    73,    74,   154,     0,    59,    54,
      55,    27,    11,     0,    46,    46,    69,    67,    66,     0,
       0,     0,     0,     0,   155,   156,     0,    11,     0,    37,
       0,     0,    48,    47,     0,    65,     0,     0,     0,     0,
       0,   157,    60,    56,    28,    46,    50,    34,     0,    49,
      38,     0,     0,     0,     0,     0,    33,     0,    58,     0,
      51,   160,   158,     0,     0,     0,    11,    36,     0,   159,
       0,    57,     0,     0,   161,     0,   162
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -286,  -286,  -286,  -286,  -286,  -286,  -262,    -1,  -145,    91,
    -286,  -286,  -123,  -194,  -131,  -225,  -259,   -12,     9,  -286,
    -253,  -286,  -286,  -286,  -286,  -286,  -286,    38,  -286,  -286,
      16,   -46,    -2,  -286,  -286,   -60,  -190,  -286,    17,  -285,
    -230
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,     2,    35,    36,   221,   141,    68,    38,   200,
     201,    39,    40,   243,   205,   276,   341,   342,    69,    41,
     291,   317,    42,    43,    44,    45,    46,    47,    48,    49,
      56,    93,    65,    51,    52,   102,   103,   333,   343,   335,
     165
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      50,    37,   132,   267,   292,   222,   207,   236,   300,    54,
      50,    94,    79,   244,   227,   227,     4,   347,   232,   277,
     364,   227,    57,   227,   255,   170,    55,     3,   133,   269,
      80,    81,    73,    53,   166,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,     5,     6,    95,    64,   351,
     336,     5,     6,    61,    92,   233,   228,   299,   351,   348,
     338,    58,   365,   373,   134,   380,   344,    96,    97,    98,
      99,   100,   101,   240,   258,   353,   259,   323,    20,   302,
     337,    21,    62,    23,    24,   303,    78,    26,    27,    28,
      59,    29,    30,   135,    60,    76,   369,    66,   138,    70,
     368,    31,    71,    72,   140,    63,    74,    75,   144,    32,
      33,    77,   148,   149,   381,   151,   152,   153,   363,   104,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   -75,   101,   183,   184,   375,   136,   137,    34,    50,
     211,   330,   142,   171,   172,   173,   174,   175,   176,   145,
     178,   179,   180,   181,   182,   331,   332,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   198,
     265,   146,   266,   147,   206,   206,   150,   105,   106,   107,
     108,   214,   264,   167,   111,   218,   169,   114,   105,   106,
     107,   108,   109,   110,   170,   111,   177,   113,   114,   117,
     118,   340,   340,   199,     5,     6,    50,    50,   231,   116,
     117,   118,   202,   216,   212,   119,   120,   245,   246,   358,
     340,   217,     4,   330,   229,   230,   238,   237,   121,   122,
     123,   124,   340,   111,   127,   101,   358,   331,   332,   107,
     108,   130,   241,   239,   111,   242,    50,   114,   117,   118,
     247,   249,   256,   252,   253,   254,   257,   280,   260,   117,
     118,   270,   271,   261,   273,   262,   274,   275,   101,   278,
     101,   164,   289,   268,   290,   316,    50,   293,   294,    50,
      50,   319,    50,   297,   320,    50,    50,   306,   283,   285,
     307,   308,   298,   310,   301,   304,   314,   315,    50,   211,
     305,   296,   322,   324,   346,   325,   339,    50,   349,    50,
      50,   356,   350,   101,   357,   355,   131,   360,   326,   366,
     327,   328,   370,   376,   313,   377,   378,    50,   318,   383,
     272,   359,     0,   334,    80,    81,    50,   211,   345,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,     0,
       0,    50,   211,     0,     0,   105,   106,   107,   108,   109,
     110,     0,   111,   112,   113,   114,     0,     0,     0,     0,
       0,     0,     0,   115,   352,     0,   116,   117,   118,    50,
     211,     0,   119,   120,   361,   362,   164,     0,     0,     0,
       0,     0,     0,     0,     0,   121,   122,   123,   124,   125,
     126,   127,   374,   164,     0,     0,     0,     4,   130,     5,
       6,     7,     0,     8,     0,     9,   382,    10,    11,    12,
       0,   385,     0,     0,    13,    14,    15,     0,    16,    17,
       0,    18,     0,    19,     0,     0,    20,     0,     0,    21,
      22,    23,    24,     0,    25,    26,    27,    28,     0,    29,
      30,     0,     0,     0,     0,     0,     0,     0,     0,    31,
       0,     0,     0,     0,     0,     0,     0,    32,    33,     0,
       5,     6,     7,     0,     8,     0,     9,     0,    10,    11,
      12,     0,     0,     0,   367,    13,    14,    15,     0,    16,
      17,   290,    18,     0,     0,     0,    34,    20,     0,     0,
      21,    22,    23,    24,     0,    25,    26,    27,    28,     0,
      29,    30,     0,     0,     0,     5,     6,     7,     0,     8,
      31,     9,     0,    10,    11,    12,     0,     0,    32,    33,
      13,    14,    15,     0,    16,    17,     0,    18,     0,     0,
       0,     0,    20,     0,     0,    21,    22,    23,    24,     0,
      25,    26,    27,    28,     0,    29,    30,    34,     0,     0,
       0,     0,     0,     0,     0,    31,     0,     0,     0,     0,
      67,     0,     0,    32,    33,     0,     5,     6,     7,     0,
       8,     0,     9,     0,    10,    11,    12,     0,     0,     0,
       0,    13,    14,    15,     0,    16,    17,     0,    18,     0,
       0,     0,    34,    20,     0,     0,    21,    22,    23,    24,
       0,    25,    26,    27,    28,     0,    29,    30,     0,     0,
       0,     5,     6,     7,     0,     8,    31,     9,     0,    10,
      11,    12,   210,     0,    32,    33,    13,    14,    15,     0,
      16,    17,     0,    18,     0,     0,     0,     0,    20,     0,
       0,    21,    22,    23,    24,     0,    25,    26,    27,    28,
       0,    29,    30,    34,     0,     0,     5,     6,     7,     0,
       8,    31,     9,     0,    10,    11,    12,   321,     0,    32,
      33,    13,    14,    15,     0,    16,    17,     0,    18,     0,
       0,     0,     0,    20,     0,     0,    21,    22,    23,    24,
       0,    25,    26,    27,    28,     0,    29,    30,    34,     0,
       0,     5,     6,     7,     0,     8,    31,     9,     0,    10,
      11,    12,   354,     0,    32,    33,    13,    14,    15,     0,
      16,    17,     0,    18,     0,     5,     6,    61,    20,     0,
       0,    21,    22,    23,    24,     0,    25,    26,    27,    28,
       0,    29,    30,    34,     0,     0,     0,     0,     0,     0,
       0,    31,    20,     0,     0,    21,    62,    23,    24,    32,
      33,    26,    27,    28,     0,    29,    30,     5,     6,    61,
       0,     0,     0,     0,     0,    31,     0,     0,     0,   143,
       0,     0,     0,    32,    33,     0,     0,     0,    34,     0,
       0,     0,     0,     0,    20,     0,     0,    21,    62,    23,
      24,     0,     0,    26,    27,    28,     0,    29,    30,     5,
       6,    61,    34,     0,     0,     0,     0,    31,     0,     0,
       0,     0,   197,     0,     0,    32,    33,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    20,     0,     0,    21,
      62,    23,    24,     0,     0,    26,    27,    28,     0,    29,
      30,     5,     6,    61,    34,     0,     0,     0,     0,    31,
       0,     0,     0,   213,     0,     0,     0,    32,    33,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    20,     0,
       0,    21,    62,    23,    24,     0,     0,    26,    27,    28,
       0,    29,    30,     5,     6,    61,    34,     0,     0,     0,
       0,    31,   248,     0,     0,     0,     0,     0,     0,    32,
      33,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      20,     0,     0,    21,    62,    23,    24,     0,     0,    26,
      27,    28,     0,    29,    30,     5,     6,    61,    34,     0,
       0,     0,     0,    31,     0,     0,     0,   251,     0,     0,
       0,    32,    33,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    20,     0,     0,    21,    62,    23,    24,     0,
       0,    26,    27,    28,     0,    29,    30,     5,     6,    61,
      34,     0,     0,     0,     0,    31,   282,     0,     0,     0,
       0,     0,     0,    32,    33,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    20,     0,     0,    21,    62,    23,
      24,     0,     0,    26,    27,    28,     0,    29,    30,     5,
       6,    61,    34,     0,     0,     0,     0,    31,   284,     0,
       0,     0,     0,     0,     0,    32,    33,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    20,     0,     0,    21,
      62,    23,    24,     0,     0,    26,    27,    28,     0,    29,
      30,     5,     6,    61,    34,     0,     0,     0,     0,    31,
     312,     0,     0,     0,     0,     0,     0,    32,    33,     0,
       0,     0,     0,     0,     0,     5,     6,    61,    20,     0,
       0,    21,    62,    23,    24,     0,     0,    26,    27,    28,
       0,    29,    30,     0,     0,     0,    34,     0,     0,     0,
       0,    31,    20,     0,     0,    21,    62,    23,    24,    32,
      33,    26,    27,    28,     0,    29,    30,     0,     0,     0,
       0,     0,     0,     0,     0,    31,     0,     0,     0,     0,
       0,     0,     0,    32,    33,     0,     0,     0,    34,     0,
       0,     0,   105,   106,   107,   108,   109,   110,     0,   111,
     112,   113,   114,     0,     0,     0,     0,     0,     0,     0,
     115,     0,   204,   116,   117,   118,     0,     0,     0,   119,
     120,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   121,   122,   123,   124,   125,   126,   127,     0,
     128,     0,     0,     0,   129,   130,     0,   234,   105,   106,
     107,   108,   109,   110,     0,   111,   112,   113,   114,     0,
     223,   224,     0,     0,     0,     0,   115,     0,     0,   116,
     117,   118,     0,     0,     0,   119,   120,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   121,   122,
     123,   124,   125,   126,   127,     0,   128,     0,     0,     0,
     129,   130,   105,   106,   107,   108,   109,   110,     0,   111,
     112,   113,   114,     0,     0,   225,     0,   226,     0,     0,
     115,     0,     0,   116,   117,   118,     0,     0,     0,   119,
     120,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   121,   122,   123,   124,   125,   126,   127,     0,
     128,     0,     0,     0,   129,   130,   105,   106,   107,   108,
     109,   110,     0,   111,   112,   113,   114,     0,     0,     0,
       0,   139,     0,     0,   115,     0,     0,   116,   117,   118,
       0,     0,     0,   119,   120,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   121,   122,   123,   124,
     125,   126,   127,     0,   128,     0,     0,     0,   129,   130,
     105,   106,   107,   108,   109,   110,     0,   111,   112,   113,
     114,     0,   168,     0,     0,     0,     0,     0,   115,     0,
       0,   116,   117,   118,     0,     0,     0,   119,   120,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     121,   122,   123,   124,   125,   126,   127,     0,   128,     0,
       0,     0,   129,   130,   105,   106,   107,   108,   109,   110,
       0,   111,   112,   113,   114,     0,   203,     0,     0,     0,
       0,     0,   115,     0,     0,   116,   117,   118,     0,     0,
       0,   119,   120,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   121,   122,   123,   124,   125,   126,
     127,     0,   128,     0,     0,     0,   129,   130,   105,   106,
     107,   108,   109,   110,     0,   111,   112,   113,   114,     0,
     208,     0,     0,     0,     0,     0,   115,     0,     0,   116,
     117,   118,     0,     0,     0,   119,   120,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   121,   122,
     123,   124,   125,   126,   127,     0,   128,     0,     0,     0,
     129,   130,   105,   106,   107,   108,   109,   110,     0,   111,
     112,   113,   114,     0,   209,     0,     0,     0,     0,     0,
     115,     0,     0,   116,   117,   118,     0,     0,     0,   119,
     120,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   121,   122,   123,   124,   125,   126,   127,     0,
     128,     0,     0,     0,   129,   130,   105,   106,   107,   108,
     109,   110,     0,   111,   112,   113,   114,     0,     0,     0,
       0,   215,     0,     0,   115,     0,     0,   116,   117,   118,
       0,     0,     0,   119,   120,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   121,   122,   123,   124,
     125,   126,   127,     0,   128,     0,     0,     0,   129,   130,
     105,   106,   107,   108,   109,   110,     0,   111,   112,   113,
     114,     0,   219,     0,     0,     0,     0,     0,   115,     0,
       0,   116,   117,   118,     0,     0,     0,   119,   120,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     121,   122,   123,   124,   125,   126,   127,     0,   128,     0,
       0,     0,   129,   130,   105,   106,   107,   108,   109,   110,
       0,   111,   112,   113,   114,     0,   220,     0,     0,     0,
       0,     0,   115,     0,     0,   116,   117,   118,     0,     0,
       0,   119,   120,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   121,   122,   123,   124,   125,   126,
     127,     0,   128,     0,     0,     0,   129,   130,   105,   106,
     107,   108,   109,   110,     0,   111,   112,   113,   114,     0,
       0,     0,   235,     0,     0,     0,   115,     0,     0,   116,
     117,   118,     0,     0,     0,   119,   120,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   121,   122,
     123,   124,   125,   126,   127,     0,   128,     0,     0,     0,
     129,   130,   105,   106,   107,   108,   109,   110,     0,   111,
     112,   113,   114,     0,     0,     0,     0,   250,     0,     0,
     115,     0,     0,   116,   117,   118,     0,     0,     0,   119,
     120,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   121,   122,   123,   124,   125,   126,   127,     0,
     128,     0,     0,     0,   129,   130,   105,   106,   107,   108,
     109,   110,     0,   111,   112,   113,   114,     0,     0,     0,
     242,     0,     0,     0,   115,     0,     0,   116,   117,   118,
       0,     0,     0,   119,   120,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   121,   122,   123,   124,
     125,   126,   127,     0,   128,     0,     0,     0,   129,   130,
     105,   106,   107,   108,   109,   110,     0,   111,   112,   113,
     114,     0,     0,  -152,     0,     0,     0,     0,   115,     0,
       0,   116,   117,   118,     0,     0,     0,   119,   120,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     121,   122,   123,   124,   125,   126,   127,     0,   128,     0,
       0,     0,   129,   130,   105,   106,   107,   108,   109,   110,
       0,   111,   112,   113,   114,     0,   279,     0,     0,     0,
       0,     0,   115,     0,     0,   116,   117,   118,     0,     0,
       0,   119,   120,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   121,   122,   123,   124,   125,   126,
     127,     0,   128,     0,     0,     0,   129,   130,   105,   106,
     107,   108,   109,   110,     0,   111,   112,   113,   114,     0,
     281,     0,     0,     0,     0,     0,   115,     0,     0,   116,
     117,   118,     0,     0,     0,   119,   120,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   121,   122,
     123,   124,   125,   126,   127,     0,   128,     0,     0,     0,
     129,   130,   105,   106,   107,   108,   109,   110,     0,   111,
     112,   113,   114,     0,     0,     0,     0,   286,     0,     0,
     115,     0,     0,   116,   117,   118,     0,     0,     0,   119,
     120,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   121,   122,   123,   124,   125,   126,   127,     0,
     128,     0,     0,     0,   129,   130,   105,   106,   107,   108,
     109,   110,     0,   111,   112,   113,   114,     0,   287,     0,
       0,     0,     0,     0,   115,     0,     0,   116,   117,   118,
       0,     0,     0,   119,   120,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   121,   122,   123,   124,
     125,   126,   127,     0,   128,     0,     0,     0,   129,   130,
     105,   106,   107,   108,   109,   110,     0,   111,   112,   113,
     114,     0,   288,     0,     0,     0,     0,     0,   115,     0,
       0,   116,   117,   118,     0,     0,     0,   119,   120,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     121,   122,   123,   124,   125,   126,   127,     0,   128,     0,
       0,     0,   129,   130,   105,   106,   107,   108,   109,   110,
       0,   111,   112,   113,   114,     0,     0,     0,     0,   295,
       0,     0,   115,     0,     0,   116,   117,   118,     0,     0,
       0,   119,   120,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   121,   122,   123,   124,   125,   126,
     127,     0,   128,     0,     0,     0,   129,   130,   105,   106,
     107,   108,   109,   110,     0,   111,   112,   113,   114,     0,
     309,     0,     0,     0,     0,     0,   115,     0,     0,   116,
     117,   118,     0,     0,     0,   119,   120,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   121,   122,
     123,   124,   125,   126,   127,     0,   128,     0,     0,     0,
     129,   130,   105,   106,   107,   108,   109,   110,     0,   111,
     112,   113,   114,     0,   311,     0,     0,     0,     0,     0,
     115,     0,     0,   116,   117,   118,     0,     0,     0,   119,
     120,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   121,   122,   123,   124,   125,   126,   127,     0,
     128,     0,     0,     0,   129,   130,   105,   106,   107,   108,
     109,   110,     0,   111,   112,   113,   114,     0,   329,     0,
       0,     0,     0,     0,   115,     0,     0,   116,   117,   118,
       0,     0,     0,   119,   120,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   121,   122,   123,   124,
     125,   126,   127,     0,   128,     0,     0,     0,   129,   130,
     105,   106,   107,   108,   109,   110,     0,   111,   112,   113,
     114,     0,     0,     0,     0,   371,     0,     0,   115,     0,
       0,   116,   117,   118,     0,     0,     0,   119,   120,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     121,   122,   123,   124,   125,   126,   127,     0,   128,     0,
       0,     0,   129,   130,   105,   106,   107,   108,   109,   110,
       0,   111,   112,   113,   114,     0,     0,     0,     0,   372,
       0,     0,   115,     0,     0,   116,   117,   118,     0,     0,
       0,   119,   120,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   121,   122,   123,   124,   125,   126,
     127,     0,   128,     0,     0,     0,   129,   130,   105,   106,
     107,   108,   109,   110,     0,   111,   112,   113,   114,     0,
       0,     0,     0,   379,     0,     0,   115,     0,     0,   116,
     117,   118,     0,     0,     0,   119,   120,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   121,   122,
     123,   124,   125,   126,   127,     0,   128,     0,     0,     0,
     129,   130,   105,   106,   107,   108,   109,   110,     0,   111,
     112,   113,   114,     0,     0,     0,     0,   384,     0,     0,
     115,     0,     0,   116,   117,   118,     0,     0,     0,   119,
     120,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   121,   122,   123,   124,   125,   126,   127,     0,
     128,     0,     0,     0,   129,   130,   105,   106,   107,   108,
     109,   110,     0,   111,   112,   113,   114,     0,     0,     0,
       0,   386,     0,     0,   115,     0,     0,   116,   117,   118,
       0,     0,     0,   119,   120,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   121,   122,   123,   124,
     125,   126,   127,     0,   128,     0,     0,     0,   129,   130,
     105,   106,   107,   108,   109,   110,     0,   111,   112,   113,
     114,     0,     0,     0,     0,     0,     0,     0,   115,     0,
       0,   116,   117,   118,     0,     0,     0,   119,   120,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     121,   122,   123,   124,   125,   126,   127,     0,   128,     0,
       0,     0,   129,   130,   105,   106,   107,   108,   109,   110,
       0,   111,   112,   113,   114,     0,     0,     0,     0,     0,
       0,     0,   115,     0,     0,   116,   117,   118,     0,     0,
       0,   119,   120,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   121,   122,   123,   124,   125,   126,
     127,     0,     0,     0,     0,     0,   129,   130,   105,   106,
     107,   108,   109,   110,     0,   111,   112,   113,   114,     0,
       0,     0,     0,     0,     0,     0,   115,     0,     0,   116,
     117,   118,     0,     0,     0,   119,   120,   105,   106,   107,
     108,   109,   110,     0,   111,   112,   113,   114,   121,   122,
     123,   124,   125,     0,   127,   115,     0,     0,   116,   117,
     118,   130,     0,     0,   119,   120,   105,   106,   107,   108,
     109,   110,     0,   111,     0,   113,   114,   121,   122,   123,
     124,     0,     0,   127,   115,     0,     0,   116,   117,   118,
     130,     0,     0,   119,   120,   105,   106,   107,   108,   109,
     110,     0,   111,     0,     0,   114,   121,   122,   123,   124,
       0,     0,   127,     0,     0,     0,   116,   117,   118,   130,
       0,     0,   119,   120,   105,   106,   107,   108,   109,   110,
       0,   111,     0,     0,   114,   121,   122,   123,   124,     0,
       0,   127,     0,     0,     0,   116,   117,   118,   130,     0,
       0,   119,   120,   105,   106,   107,   108,     0,     0,     0,
     111,     0,     0,   114,   263,     0,   123,   124,     0,     0,
     127,     0,     0,     0,   116,   117,   118,   130,     0,     0,
     119,   120,    80,    81,     0,     0,     0,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,     0,     0,   127,
     105,   106,   107,   108,     0,     0,   130,   111,     0,     0,
     114,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   117,   118,     0,     0,     0,   119,   120
};

static const yytype_int16 yycheck[] =
{
       2,     2,    48,   233,   257,   150,   137,   197,   270,    38,
      12,    55,    50,   207,    57,    57,     3,    50,    55,   244,
      50,    57,     6,    57,   218,    57,    55,     0,    55,    61,
      68,    69,    16,    38,    94,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,     5,     6,    91,    10,   334,
      28,     5,     6,     7,    92,    92,    99,    99,   343,    92,
     322,    59,    92,    99,    91,    99,   325,    29,    30,    31,
      32,    33,    34,   204,    61,   337,   221,   302,    32,   273,
      58,    35,    36,    37,    38,   275,    50,    41,    42,    43,
      59,    45,    46,    55,    55,    38,   355,    55,    60,    55,
     353,    55,    55,    55,    66,    59,    55,    55,    70,    63,
      64,    55,    74,    75,   376,    77,    78,    79,   348,    59,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    59,    94,   117,   118,   365,    55,    55,    92,   141,
     141,    24,    14,   105,   106,   107,   108,   109,   110,    37,
     112,   113,   114,   115,   116,    38,    39,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     230,    37,   232,    55,   136,   137,    60,    44,    45,    46,
      47,   143,   228,    38,    51,   147,    99,    54,    44,    45,
      46,    47,    48,    49,    57,    51,    38,    53,    54,    66,
      67,   324,   325,    37,     5,     6,   208,   209,   170,    65,
      66,    67,    38,    23,    55,    71,    72,   208,   209,   342,
     343,    23,     3,    24,    56,    55,    57,    56,    84,    85,
      86,    87,   355,    51,    90,   197,   359,    38,    39,    46,
      47,    97,   204,    55,    51,    58,   248,    54,    66,    67,
     212,   213,    60,   215,   216,   217,    60,   248,    41,    66,
      67,    60,    37,   225,    99,   227,    38,    57,   230,     8,
     232,   233,    56,   235,    26,    60,   278,    59,    56,   281,
     282,    61,   284,    56,    61,   287,   288,   278,   250,   251,
     281,   282,    56,   284,    56,    56,   287,   288,   300,   300,
      56,   263,    60,    60,    50,    60,    56,   309,    38,   311,
     312,    59,    61,   275,    61,    60,    50,    61,   309,    59,
     311,   312,    59,    58,   286,    61,    50,   329,   290,    50,
     239,   343,    -1,   316,    68,    69,   338,   338,   329,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    -1,
      -1,   353,   353,    -1,    -1,    44,    45,    46,    47,    48,
      49,    -1,    51,    52,    53,    54,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    62,   336,    -1,    65,    66,    67,   381,
     381,    -1,    71,    72,   346,   347,   348,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    84,    85,    86,    87,    88,
      89,    90,   364,   365,    -1,    -1,    -1,     3,    97,     5,
       6,     7,    -1,     9,    -1,    11,   378,    13,    14,    15,
      -1,   383,    -1,    -1,    20,    21,    22,    -1,    24,    25,
      -1,    27,    -1,    29,    -1,    -1,    32,    -1,    -1,    35,
      36,    37,    38,    -1,    40,    41,    42,    43,    -1,    45,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,    -1,
       5,     6,     7,    -1,     9,    -1,    11,    -1,    13,    14,
      15,    -1,    -1,    -1,    19,    20,    21,    22,    -1,    24,
      25,    26,    27,    -1,    -1,    -1,    92,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,    43,    -1,
      45,    46,    -1,    -1,    -1,     5,     6,     7,    -1,     9,
      55,    11,    -1,    13,    14,    15,    -1,    -1,    63,    64,
      20,    21,    22,    -1,    24,    25,    -1,    27,    -1,    -1,
      -1,    -1,    32,    -1,    -1,    35,    36,    37,    38,    -1,
      40,    41,    42,    43,    -1,    45,    46,    92,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,
      60,    -1,    -1,    63,    64,    -1,     5,     6,     7,    -1,
       9,    -1,    11,    -1,    13,    14,    15,    -1,    -1,    -1,
      -1,    20,    21,    22,    -1,    24,    25,    -1,    27,    -1,
      -1,    -1,    92,    32,    -1,    -1,    35,    36,    37,    38,
      -1,    40,    41,    42,    43,    -1,    45,    46,    -1,    -1,
      -1,     5,     6,     7,    -1,     9,    55,    11,    -1,    13,
      14,    15,    61,    -1,    63,    64,    20,    21,    22,    -1,
      24,    25,    -1,    27,    -1,    -1,    -1,    -1,    32,    -1,
      -1,    35,    36,    37,    38,    -1,    40,    41,    42,    43,
      -1,    45,    46,    92,    -1,    -1,     5,     6,     7,    -1,
       9,    55,    11,    -1,    13,    14,    15,    61,    -1,    63,
      64,    20,    21,    22,    -1,    24,    25,    -1,    27,    -1,
      -1,    -1,    -1,    32,    -1,    -1,    35,    36,    37,    38,
      -1,    40,    41,    42,    43,    -1,    45,    46,    92,    -1,
      -1,     5,     6,     7,    -1,     9,    55,    11,    -1,    13,
      14,    15,    61,    -1,    63,    64,    20,    21,    22,    -1,
      24,    25,    -1,    27,    -1,     5,     6,     7,    32,    -1,
      -1,    35,    36,    37,    38,    -1,    40,    41,    42,    43,
      -1,    45,    46,    92,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    55,    32,    -1,    -1,    35,    36,    37,    38,    63,
      64,    41,    42,    43,    -1,    45,    46,     5,     6,     7,
      -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,    -1,    59,
      -1,    -1,    -1,    63,    64,    -1,    -1,    -1,    92,    -1,
      -1,    -1,    -1,    -1,    32,    -1,    -1,    35,    36,    37,
      38,    -1,    -1,    41,    42,    43,    -1,    45,    46,     5,
       6,     7,    92,    -1,    -1,    -1,    -1,    55,    -1,    -1,
      -1,    -1,    60,    -1,    -1,    63,    64,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,    -1,    35,
      36,    37,    38,    -1,    -1,    41,    42,    43,    -1,    45,
      46,     5,     6,     7,    92,    -1,    -1,    -1,    -1,    55,
      -1,    -1,    -1,    59,    -1,    -1,    -1,    63,    64,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,
      -1,    35,    36,    37,    38,    -1,    -1,    41,    42,    43,
      -1,    45,    46,     5,     6,     7,    92,    -1,    -1,    -1,
      -1,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      32,    -1,    -1,    35,    36,    37,    38,    -1,    -1,    41,
      42,    43,    -1,    45,    46,     5,     6,     7,    92,    -1,
      -1,    -1,    -1,    55,    -1,    -1,    -1,    59,    -1,    -1,
      -1,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    32,    -1,    -1,    35,    36,    37,    38,    -1,
      -1,    41,    42,    43,    -1,    45,    46,     5,     6,     7,
      92,    -1,    -1,    -1,    -1,    55,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    63,    64,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    32,    -1,    -1,    35,    36,    37,
      38,    -1,    -1,    41,    42,    43,    -1,    45,    46,     5,
       6,     7,    92,    -1,    -1,    -1,    -1,    55,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    64,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,    -1,    35,
      36,    37,    38,    -1,    -1,    41,    42,    43,    -1,    45,
      46,     5,     6,     7,    92,    -1,    -1,    -1,    -1,    55,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,    -1,
      -1,    -1,    -1,    -1,    -1,     5,     6,     7,    32,    -1,
      -1,    35,    36,    37,    38,    -1,    -1,    41,    42,    43,
      -1,    45,    46,    -1,    -1,    -1,    92,    -1,    -1,    -1,
      -1,    55,    32,    -1,    -1,    35,    36,    37,    38,    63,
      64,    41,    42,    43,    -1,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    63,    64,    -1,    -1,    -1,    92,    -1,
      -1,    -1,    44,    45,    46,    47,    48,    49,    -1,    51,
      52,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      62,    -1,    92,    65,    66,    67,    -1,    -1,    -1,    71,
      72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    86,    87,    88,    89,    90,    -1,
      92,    -1,    -1,    -1,    96,    97,    -1,    99,    44,    45,
      46,    47,    48,    49,    -1,    51,    52,    53,    54,    -1,
      56,    57,    -1,    -1,    -1,    -1,    62,    -1,    -1,    65,
      66,    67,    -1,    -1,    -1,    71,    72,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,
      86,    87,    88,    89,    90,    -1,    92,    -1,    -1,    -1,
      96,    97,    44,    45,    46,    47,    48,    49,    -1,    51,
      52,    53,    54,    -1,    -1,    57,    -1,    59,    -1,    -1,
      62,    -1,    -1,    65,    66,    67,    -1,    -1,    -1,    71,
      72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    86,    87,    88,    89,    90,    -1,
      92,    -1,    -1,    -1,    96,    97,    44,    45,    46,    47,
      48,    49,    -1,    51,    52,    53,    54,    -1,    -1,    -1,
      -1,    59,    -1,    -1,    62,    -1,    -1,    65,    66,    67,
      -1,    -1,    -1,    71,    72,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    86,    87,
      88,    89,    90,    -1,    92,    -1,    -1,    -1,    96,    97,
      44,    45,    46,    47,    48,    49,    -1,    51,    52,    53,
      54,    -1,    56,    -1,    -1,    -1,    -1,    -1,    62,    -1,
      -1,    65,    66,    67,    -1,    -1,    -1,    71,    72,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    85,    86,    87,    88,    89,    90,    -1,    92,    -1,
      -1,    -1,    96,    97,    44,    45,    46,    47,    48,    49,
      -1,    51,    52,    53,    54,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    62,    -1,    -1,    65,    66,    67,    -1,    -1,
      -1,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    86,    87,    88,    89,
      90,    -1,    92,    -1,    -1,    -1,    96,    97,    44,    45,
      46,    47,    48,    49,    -1,    51,    52,    53,    54,    -1,
      56,    -1,    -1,    -1,    -1,    -1,    62,    -1,    -1,    65,
      66,    67,    -1,    -1,    -1,    71,    72,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,
      86,    87,    88,    89,    90,    -1,    92,    -1,    -1,    -1,
      96,    97,    44,    45,    46,    47,    48,    49,    -1,    51,
      52,    53,    54,    -1,    56,    -1,    -1,    -1,    -1,    -1,
      62,    -1,    -1,    65,    66,    67,    -1,    -1,    -1,    71,
      72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    86,    87,    88,    89,    90,    -1,
      92,    -1,    -1,    -1,    96,    97,    44,    45,    46,    47,
      48,    49,    -1,    51,    52,    53,    54,    -1,    -1,    -1,
      -1,    59,    -1,    -1,    62,    -1,    -1,    65,    66,    67,
      -1,    -1,    -1,    71,    72,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    86,    87,
      88,    89,    90,    -1,    92,    -1,    -1,    -1,    96,    97,
      44,    45,    46,    47,    48,    49,    -1,    51,    52,    53,
      54,    -1,    56,    -1,    -1,    -1,    -1,    -1,    62,    -1,
      -1,    65,    66,    67,    -1,    -1,    -1,    71,    72,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    85,    86,    87,    88,    89,    90,    -1,    92,    -1,
      -1,    -1,    96,    97,    44,    45,    46,    47,    48,    49,
      -1,    51,    52,    53,    54,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    62,    -1,    -1,    65,    66,    67,    -1,    -1,
      -1,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    86,    87,    88,    89,
      90,    -1,    92,    -1,    -1,    -1,    96,    97,    44,    45,
      46,    47,    48,    49,    -1,    51,    52,    53,    54,    -1,
      -1,    -1,    58,    -1,    -1,    -1,    62,    -1,    -1,    65,
      66,    67,    -1,    -1,    -1,    71,    72,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,
      86,    87,    88,    89,    90,    -1,    92,    -1,    -1,    -1,
      96,    97,    44,    45,    46,    47,    48,    49,    -1,    51,
      52,    53,    54,    -1,    -1,    -1,    -1,    59,    -1,    -1,
      62,    -1,    -1,    65,    66,    67,    -1,    -1,    -1,    71,
      72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    86,    87,    88,    89,    90,    -1,
      92,    -1,    -1,    -1,    96,    97,    44,    45,    46,    47,
      48,    49,    -1,    51,    52,    53,    54,    -1,    -1,    -1,
      58,    -1,    -1,    -1,    62,    -1,    -1,    65,    66,    67,
      -1,    -1,    -1,    71,    72,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    86,    87,
      88,    89,    90,    -1,    92,    -1,    -1,    -1,    96,    97,
      44,    45,    46,    47,    48,    49,    -1,    51,    52,    53,
      54,    -1,    -1,    57,    -1,    -1,    -1,    -1,    62,    -1,
      -1,    65,    66,    67,    -1,    -1,    -1,    71,    72,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    85,    86,    87,    88,    89,    90,    -1,    92,    -1,
      -1,    -1,    96,    97,    44,    45,    46,    47,    48,    49,
      -1,    51,    52,    53,    54,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    62,    -1,    -1,    65,    66,    67,    -1,    -1,
      -1,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    86,    87,    88,    89,
      90,    -1,    92,    -1,    -1,    -1,    96,    97,    44,    45,
      46,    47,    48,    49,    -1,    51,    52,    53,    54,    -1,
      56,    -1,    -1,    -1,    -1,    -1,    62,    -1,    -1,    65,
      66,    67,    -1,    -1,    -1,    71,    72,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,
      86,    87,    88,    89,    90,    -1,    92,    -1,    -1,    -1,
      96,    97,    44,    45,    46,    47,    48,    49,    -1,    51,
      52,    53,    54,    -1,    -1,    -1,    -1,    59,    -1,    -1,
      62,    -1,    -1,    65,    66,    67,    -1,    -1,    -1,    71,
      72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    86,    87,    88,    89,    90,    -1,
      92,    -1,    -1,    -1,    96,    97,    44,    45,    46,    47,
      48,    49,    -1,    51,    52,    53,    54,    -1,    56,    -1,
      -1,    -1,    -1,    -1,    62,    -1,    -1,    65,    66,    67,
      -1,    -1,    -1,    71,    72,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    86,    87,
      88,    89,    90,    -1,    92,    -1,    -1,    -1,    96,    97,
      44,    45,    46,    47,    48,    49,    -1,    51,    52,    53,
      54,    -1,    56,    -1,    -1,    -1,    -1,    -1,    62,    -1,
      -1,    65,    66,    67,    -1,    -1,    -1,    71,    72,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    85,    86,    87,    88,    89,    90,    -1,    92,    -1,
      -1,    -1,    96,    97,    44,    45,    46,    47,    48,    49,
      -1,    51,    52,    53,    54,    -1,    -1,    -1,    -1,    59,
      -1,    -1,    62,    -1,    -1,    65,    66,    67,    -1,    -1,
      -1,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    86,    87,    88,    89,
      90,    -1,    92,    -1,    -1,    -1,    96,    97,    44,    45,
      46,    47,    48,    49,    -1,    51,    52,    53,    54,    -1,
      56,    -1,    -1,    -1,    -1,    -1,    62,    -1,    -1,    65,
      66,    67,    -1,    -1,    -1,    71,    72,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,
      86,    87,    88,    89,    90,    -1,    92,    -1,    -1,    -1,
      96,    97,    44,    45,    46,    47,    48,    49,    -1,    51,
      52,    53,    54,    -1,    56,    -1,    -1,    -1,    -1,    -1,
      62,    -1,    -1,    65,    66,    67,    -1,    -1,    -1,    71,
      72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    86,    87,    88,    89,    90,    -1,
      92,    -1,    -1,    -1,    96,    97,    44,    45,    46,    47,
      48,    49,    -1,    51,    52,    53,    54,    -1,    56,    -1,
      -1,    -1,    -1,    -1,    62,    -1,    -1,    65,    66,    67,
      -1,    -1,    -1,    71,    72,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    86,    87,
      88,    89,    90,    -1,    92,    -1,    -1,    -1,    96,    97,
      44,    45,    46,    47,    48,    49,    -1,    51,    52,    53,
      54,    -1,    -1,    -1,    -1,    59,    -1,    -1,    62,    -1,
      -1,    65,    66,    67,    -1,    -1,    -1,    71,    72,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    85,    86,    87,    88,    89,    90,    -1,    92,    -1,
      -1,    -1,    96,    97,    44,    45,    46,    47,    48,    49,
      -1,    51,    52,    53,    54,    -1,    -1,    -1,    -1,    59,
      -1,    -1,    62,    -1,    -1,    65,    66,    67,    -1,    -1,
      -1,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    86,    87,    88,    89,
      90,    -1,    92,    -1,    -1,    -1,    96,    97,    44,    45,
      46,    47,    48,    49,    -1,    51,    52,    53,    54,    -1,
      -1,    -1,    -1,    59,    -1,    -1,    62,    -1,    -1,    65,
      66,    67,    -1,    -1,    -1,    71,    72,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,
      86,    87,    88,    89,    90,    -1,    92,    -1,    -1,    -1,
      96,    97,    44,    45,    46,    47,    48,    49,    -1,    51,
      52,    53,    54,    -1,    -1,    -1,    -1,    59,    -1,    -1,
      62,    -1,    -1,    65,    66,    67,    -1,    -1,    -1,    71,
      72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    86,    87,    88,    89,    90,    -1,
      92,    -1,    -1,    -1,    96,    97,    44,    45,    46,    47,
      48,    49,    -1,    51,    52,    53,    54,    -1,    -1,    -1,
      -1,    59,    -1,    -1,    62,    -1,    -1,    65,    66,    67,
      -1,    -1,    -1,    71,    72,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    86,    87,
      88,    89,    90,    -1,    92,    -1,    -1,    -1,    96,    97,
      44,    45,    46,    47,    48,    49,    -1,    51,    52,    53,
      54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    -1,
      -1,    65,    66,    67,    -1,    -1,    -1,    71,    72,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    85,    86,    87,    88,    89,    90,    -1,    92,    -1,
      -1,    -1,    96,    97,    44,    45,    46,    47,    48,    49,
      -1,    51,    52,    53,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    62,    -1,    -1,    65,    66,    67,    -1,    -1,
      -1,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    86,    87,    88,    89,
      90,    -1,    -1,    -1,    -1,    -1,    96,    97,    44,    45,
      46,    47,    48,    49,    -1,    51,    52,    53,    54,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    62,    -1,    -1,    65,
      66,    67,    -1,    -1,    -1,    71,    72,    44,    45,    46,
      47,    48,    49,    -1,    51,    52,    53,    54,    84,    85,
      86,    87,    88,    -1,    90,    62,    -1,    -1,    65,    66,
      67,    97,    -1,    -1,    71,    72,    44,    45,    46,    47,
      48,    49,    -1,    51,    -1,    53,    54,    84,    85,    86,
      87,    -1,    -1,    90,    62,    -1,    -1,    65,    66,    67,
      97,    -1,    -1,    71,    72,    44,    45,    46,    47,    48,
      49,    -1,    51,    -1,    -1,    54,    84,    85,    86,    87,
      -1,    -1,    90,    -1,    -1,    -1,    65,    66,    67,    97,
      -1,    -1,    71,    72,    44,    45,    46,    47,    48,    49,
      -1,    51,    -1,    -1,    54,    84,    85,    86,    87,    -1,
      -1,    90,    -1,    -1,    -1,    65,    66,    67,    97,    -1,
      -1,    71,    72,    44,    45,    46,    47,    -1,    -1,    -1,
      51,    -1,    -1,    54,    50,    -1,    86,    87,    -1,    -1,
      90,    -1,    -1,    -1,    65,    66,    67,    97,    -1,    -1,
      71,    72,    68,    69,    -1,    -1,    -1,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    -1,    -1,    90,
      44,    45,    46,    47,    -1,    -1,    97,    51,    -1,    -1,
      54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    66,    67,    -1,    -1,    -1,    71,    72
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   101,   102,     0,     3,     5,     6,     7,     9,    11,
      13,    14,    15,    20,    21,    22,    24,    25,    27,    29,
      32,    35,    36,    37,    38,    40,    41,    42,    43,    45,
      46,    55,    63,    64,    92,   103,   104,   107,   108,   111,
     112,   119,   122,   123,   124,   125,   126,   127,   128,   129,
     132,   133,   134,    38,    38,    55,   130,   130,    59,    59,
      55,     7,    36,    59,   127,   132,    55,    60,   107,   118,
      55,    55,    55,   130,    55,    55,    38,    55,    50,    50,
      68,    69,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    92,   131,    55,    91,   127,   127,   127,   127,
     127,   127,   135,   136,    59,    44,    45,    46,    47,    48,
      49,    51,    52,    53,    54,    62,    65,    66,    67,    71,
      72,    84,    85,    86,    87,    88,    89,    90,    92,    96,
      97,    50,   131,    55,    91,   127,    55,    55,   127,    59,
     127,   106,    14,    59,   127,    37,    37,    55,   127,   127,
      60,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   140,   135,    38,    56,    99,
      57,   127,   127,   127,   127,   127,   127,    38,   127,   127,
     127,   127,   127,   130,   130,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,    60,   127,    37,
     109,   110,    38,    56,    92,   114,   127,   114,    56,    56,
      61,   107,    55,    59,   127,    59,    23,    23,   127,    56,
      56,   105,   108,    56,    57,    57,    59,    57,    99,    56,
      55,   127,    55,    92,    99,    58,   136,    56,    57,    55,
     114,   127,    58,   113,   113,   118,   118,   127,    56,   127,
      59,    59,   127,   127,   127,   113,    60,    60,    61,   108,
      41,   127,   127,    50,   131,   135,   135,   140,   127,    61,
      60,    37,   109,    99,    38,    57,   115,   115,     8,    56,
     118,    56,    56,   127,    56,   127,    59,    56,    56,    56,
      26,   120,   120,    59,    56,    59,   127,    56,    56,    99,
     106,    56,   113,   136,    56,    56,   118,   118,   118,    56,
     118,    56,    56,   127,   118,   118,    60,   121,   127,    61,
      61,    61,    60,   115,    60,    60,   118,   118,   118,    56,
      24,    38,    39,   137,   138,   139,    28,    58,   106,    56,
     112,   116,   117,   138,   116,   118,    50,    50,    92,    38,
      61,   139,   127,   106,    61,    60,    59,    61,   112,   117,
      61,   127,   127,   140,    50,    92,    59,    19,   120,   116,
      59,    59,    59,    99,   127,   140,    58,    61,    50,    59,
      99,   106,   127,    50,    59,   127,    59
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   100,   101,   102,   102,   103,   103,   103,   104,   105,
     105,   106,   106,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   108,   108,   109,
     109,   110,   110,   111,   112,   112,   112,   112,   112,   112,
     113,   113,   114,   114,   115,   115,   116,   116,   116,   116,
     117,   117,   118,   118,   119,   119,   120,   120,   120,   121,
     121,   122,   122,   123,   123,   124,   124,   124,   124,   124,
     124,   124,   124,   125,   125,   126,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   128,   128,   129,
     129,   130,   130,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   133,   133,   133,   134,   134,
     135,   135,   136,   136,   137,   137,   138,   138,   139,   139,
     139,   139,   139,   140,   140
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     1,     6,     1,
       2,     0,     2,     1,     1,     1,     1,     1,     1,     2,
       2,     2,     3,     2,     4,     6,     1,     8,    10,     0,
       1,     1,     3,    10,    10,     7,    12,     9,    10,     7,
       0,     2,     0,     1,     0,     2,     0,     1,     1,     2,
       2,     3,     3,     1,     7,     7,     4,     7,     5,     1,
       3,     5,     7,     5,     6,     9,     8,     8,     7,     8,
       7,     7,     6,     7,     7,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     1,     5,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     4,     3,     3,     6,     3,
       3,     1,     3,     1,     1,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     1,     1,     1,     3,     6,
       2,     5,     2,     3,     5,     4,     6,     6,     4,     6,
       0,     1,     1,     3,     0,     1,     1,     2,     4,     5,
       4,     7,     8,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




/* The kind of the lookahead of this context.  */
static yysymbol_kind_t
yypcontext_token (const yypcontext_t *yyctx) YY_ATTRIBUTE_UNUSED;

static yysymbol_kind_t
yypcontext_token (const yypcontext_t *yyctx)
{
  return yyctx->yytoken;
}

/* The location of the lookahead of this context.  */
static YYLTYPE *
yypcontext_location (const yypcontext_t *yyctx) YY_ATTRIBUTE_UNUSED;

static YYLTYPE *
yypcontext_location (const yypcontext_t *yyctx)
{
  return yyctx->yylloc;
}

/* User defined function to report a syntax error.  */
static int
yyreport_syntax_error (const yypcontext_t *yyctx);

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* start: decl_list  */
#line 167 "CMDgram.y"
      { }
#line 2241 "CMDgram.c"
    break;

  case 3: /* decl_list: %empty  */
#line 172 "CMDgram.y"
      { (yyval.stmt) = nil; }
#line 2247 "CMDgram.c"
    break;

  case 4: /* decl_list: decl_list decl  */
#line 174 "CMDgram.y"
      { if(!Script::gStatementList) { Script::gStatementList = (yyvsp[0].stmt); } else { Script::gStatementList->append((yyvsp[0].stmt)); } }
#line 2253 "CMDgram.c"
    break;

  case 5: /* decl: stmt  */
#line 179 "CMDgram.y"
      { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2259 "CMDgram.c"
    break;

  case 6: /* decl: fn_decl_stmt  */
#line 181 "CMDgram.y"
      { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2265 "CMDgram.c"
    break;

  case 7: /* decl: package_decl  */
#line 183 "CMDgram.y"
     { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2271 "CMDgram.c"
    break;

  case 8: /* package_decl: rwPACKAGE IDENT '{' fn_decl_list '}' ';'  */
#line 188 "CMDgram.y"
      { (yyval.stmt) = (yyvsp[-2].stmt); for(StmtNode *walk = ((yyvsp[-2].stmt));walk;walk = walk->getNext() ) walk->setPackage((yyvsp[-4].s).value); }
#line 2277 "CMDgram.c"
    break;

  case 9: /* fn_decl_list: fn_decl_stmt  */
#line 193 "CMDgram.y"
      { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2283 "CMDgram.c"
    break;

  case 10: /* fn_decl_list: fn_decl_list fn_decl_stmt  */
#line 195 "CMDgram.y"
      { (yyval.stmt) = (yyvsp[-1].stmt); ((yyvsp[-1].stmt))->append((yyvsp[0].stmt));  }
#line 2289 "CMDgram.c"
    break;

  case 11: /* statement_list: %empty  */
#line 200 "CMDgram.y"
      { (yyval.stmt) = nil; }
#line 2295 "CMDgram.c"
    break;

  case 12: /* statement_list: statement_list stmt  */
#line 202 "CMDgram.y"
      { if(!(yyvsp[-1].stmt)) { (yyval.stmt) = (yyvsp[0].stmt); } else { ((yyvsp[-1].stmt))->append((yyvsp[0].stmt)); (yyval.stmt) = (yyvsp[-1].stmt); } }
#line 2301 "CMDgram.c"
    break;

  case 19: /* stmt: rwBREAK ';'  */
#line 213 "CMDgram.y"
      { (yyval.stmt) = BreakStmtNode::alloc( (yyvsp[-1].i).lineNumber ); }
#line 2307 "CMDgram.c"
    break;

  case 20: /* stmt: rwCONTINUE ';'  */
#line 215 "CMDgram.y"
      { (yyval.stmt) = ContinueStmtNode::alloc( (yyvsp[-1].i).lineNumber ); }
#line 2313 "CMDgram.c"
    break;

  case 21: /* stmt: rwRETURN ';'  */
#line 217 "CMDgram.y"
      { (yyval.stmt) = ReturnStmtNode::alloc( (yyvsp[-1].i).lineNumber, NULL ); }
#line 2319 "CMDgram.c"
    break;

  case 22: /* stmt: rwRETURN expr ';'  */
#line 219 "CMDgram.y"
      { (yyval.stmt) = ReturnStmtNode::alloc( (yyvsp[-2].i).lineNumber, (yyvsp[-1].expr) ); }
#line 2325 "CMDgram.c"
    break;

  case 23: /* stmt: expression_stmt ';'  */
#line 221 "CMDgram.y"
      { (yyval.stmt) = (yyvsp[-1].stmt); }
#line 2331 "CMDgram.c"
    break;

  case 24: /* stmt: TTAG '=' expr ';'  */
#line 223 "CMDgram.y"
      { (yyval.stmt) = TTagSetStmtNode::alloc( (yyvsp[-3].s).lineNumber, (yyvsp[-3].s).value, (yyvsp[-1].expr), NULL ); }
#line 2337 "CMDgram.c"
    break;

  case 25: /* stmt: TTAG '=' expr ',' expr ';'  */
#line 225 "CMDgram.y"
      { (yyval.stmt) = TTagSetStmtNode::alloc( (yyvsp[-5].s).lineNumber, (yyvsp[-5].s).value, (yyvsp[-3].expr), (yyvsp[-1].expr) ); }
#line 2343 "CMDgram.c"
    break;

  case 26: /* stmt: DOCBLOCK  */
#line 227 "CMDgram.y"
      { (yyval.stmt) = StrConstNode::alloc( (yyvsp[0].str).lineNumber, (yyvsp[0].str).value, false, true ); }
#line 2349 "CMDgram.c"
    break;

  case 27: /* fn_decl_stmt: rwDEFINE IDENT '(' var_list_decl ')' '{' statement_list '}'  */
#line 232 "CMDgram.y"
      { (yyval.stmt) = FunctionDeclStmtNode::alloc( (yyvsp[-7].i).lineNumber, (yyvsp[-6].s).value, NULL, (yyvsp[-4].var), (yyvsp[-1].stmt) ); }
#line 2355 "CMDgram.c"
    break;

  case 28: /* fn_decl_stmt: rwDEFINE IDENT opCOLONCOLON IDENT '(' var_list_decl ')' '{' statement_list '}'  */
#line 234 "CMDgram.y"
     { (yyval.stmt) = FunctionDeclStmtNode::alloc( (yyvsp[-9].i).lineNumber, (yyvsp[-6].s).value, (yyvsp[-8].s).value, (yyvsp[-4].var), (yyvsp[-1].stmt) ); }
#line 2361 "CMDgram.c"
    break;

  case 29: /* var_list_decl: %empty  */
#line 239 "CMDgram.y"
     { (yyval.var) = NULL; }
#line 2367 "CMDgram.c"
    break;

  case 30: /* var_list_decl: var_list  */
#line 241 "CMDgram.y"
     { (yyval.var) = (yyvsp[0].var); }
#line 2373 "CMDgram.c"
    break;

  case 31: /* var_list: VAR  */
#line 246 "CMDgram.y"
      { (yyval.var) = VarNode::alloc( (yyvsp[0].s).lineNumber, (yyvsp[0].s).value, NULL ); }
#line 2379 "CMDgram.c"
    break;

  case 32: /* var_list: var_list ',' VAR  */
#line 248 "CMDgram.y"
      { (yyval.var) = (yyvsp[-2].var); ((StmtNode*)((yyvsp[-2].var)))->append((StmtNode*)VarNode::alloc( (yyvsp[0].s).lineNumber, (yyvsp[0].s).value, NULL ) ); }
#line 2385 "CMDgram.c"
    break;

  case 33: /* datablock_decl: rwDATABLOCK class_name_expr '(' expr parent_block ')' '{' slot_assign_list_opt '}' ';'  */
#line 253 "CMDgram.y"
      { (yyval.stmt) = ObjectDeclNode::alloc( (yyvsp[-9].i).lineNumber, (yyvsp[-8].expr), (yyvsp[-6].expr), NULL, (yyvsp[-5].s).value, (yyvsp[-2].slist), NULL, true, false, false); }
#line 2391 "CMDgram.c"
    break;

  case 34: /* object_decl: rwDECLARE class_name_expr '(' object_name parent_block object_args ')' '{' object_declare_block '}'  */
#line 258 "CMDgram.y"
      { (yyval.od) = ObjectDeclNode::alloc( (yyvsp[-9].i).lineNumber, (yyvsp[-8].expr), (yyvsp[-6].expr), (yyvsp[-4].expr), (yyvsp[-5].s).value, (yyvsp[-1].odcl).slots, (yyvsp[-1].odcl).decls, false, false, false); }
#line 2397 "CMDgram.c"
    break;

  case 35: /* object_decl: rwDECLARE class_name_expr '(' object_name parent_block object_args ')'  */
#line 260 "CMDgram.y"
      { (yyval.od) = ObjectDeclNode::alloc( (yyvsp[-6].i).lineNumber, (yyvsp[-5].expr), (yyvsp[-3].expr), (yyvsp[-1].expr), (yyvsp[-2].s).value, NULL, NULL, false, false, false); }
#line 2403 "CMDgram.c"
    break;

  case 36: /* object_decl: rwDECLARE class_name_expr '(' '[' object_name ']' parent_block object_args ')' '{' object_declare_block '}'  */
#line 262 "CMDgram.y"
      { (yyval.od) = ObjectDeclNode::alloc( (yyvsp[-11].i).lineNumber, (yyvsp[-10].expr), (yyvsp[-7].expr), (yyvsp[-4].expr), (yyvsp[-5].s).value, (yyvsp[-1].odcl).slots, (yyvsp[-1].odcl).decls, false, true, false); }
#line 2409 "CMDgram.c"
    break;

  case 37: /* object_decl: rwDECLARE class_name_expr '(' '[' object_name ']' parent_block object_args ')'  */
#line 264 "CMDgram.y"
      { (yyval.od) = ObjectDeclNode::alloc( (yyvsp[-8].i).lineNumber, (yyvsp[-7].expr), (yyvsp[-4].expr), (yyvsp[-1].expr), (yyvsp[-2].s).value, NULL, NULL, false, true, false); }
#line 2415 "CMDgram.c"
    break;

  case 38: /* object_decl: rwDECLARESINGLETON class_name_expr '(' object_name parent_block object_args ')' '{' object_declare_block '}'  */
#line 266 "CMDgram.y"
      { (yyval.od) = ObjectDeclNode::alloc( (yyvsp[-9].i).lineNumber, (yyvsp[-8].expr), (yyvsp[-6].expr), (yyvsp[-4].expr), (yyvsp[-5].s).value, (yyvsp[-1].odcl).slots, (yyvsp[-1].odcl).decls, false, false, true); }
#line 2421 "CMDgram.c"
    break;

  case 39: /* object_decl: rwDECLARESINGLETON class_name_expr '(' object_name parent_block object_args ')'  */
#line 268 "CMDgram.y"
      { (yyval.od) = ObjectDeclNode::alloc( (yyvsp[-6].i).lineNumber, (yyvsp[-5].expr), (yyvsp[-3].expr), (yyvsp[-1].expr), (yyvsp[-2].s).value, NULL, NULL, false, false, true); }
#line 2427 "CMDgram.c"
    break;

  case 40: /* parent_block: %empty  */
#line 273 "CMDgram.y"
      { (yyval.s).value = NULL; }
#line 2433 "CMDgram.c"
    break;

  case 41: /* parent_block: ':' IDENT  */
#line 275 "CMDgram.y"
      { (yyval.s) = (yyvsp[0].s); }
#line 2439 "CMDgram.c"
    break;

  case 42: /* object_name: %empty  */
#line 280 "CMDgram.y"
      { (yyval.expr) = StrConstNode::alloc( CodeBlock::smCurrentParser->getCurrentLine(), "", false); }
#line 2445 "CMDgram.c"
    break;

  case 43: /* object_name: expr  */
#line 282 "CMDgram.y"
      { (yyval.expr) = (yyvsp[0].expr); }
#line 2451 "CMDgram.c"
    break;

  case 44: /* object_args: %empty  */
#line 287 "CMDgram.y"
      { (yyval.expr) = NULL; }
#line 2457 "CMDgram.c"
    break;

  case 45: /* object_args: ',' expr_list  */
#line 289 "CMDgram.y"
      { (yyval.expr) = (yyvsp[0].expr); }
#line 2463 "CMDgram.c"
    break;

  case 46: /* object_declare_block: %empty  */
#line 294 "CMDgram.y"
      { (yyval.odcl).slots = NULL; (yyval.odcl).decls = NULL; }
#line 2469 "CMDgram.c"
    break;

  case 47: /* object_declare_block: slot_assign_list  */
#line 296 "CMDgram.y"
      { (yyval.odcl).slots = (yyvsp[0].slist); (yyval.odcl).decls = NULL; }
#line 2475 "CMDgram.c"
    break;

  case 48: /* object_declare_block: object_decl_list  */
#line 298 "CMDgram.y"
      { (yyval.odcl).slots = NULL; (yyval.odcl).decls = (yyvsp[0].od); }
#line 2481 "CMDgram.c"
    break;

  case 49: /* object_declare_block: slot_assign_list object_decl_list  */
#line 300 "CMDgram.y"
      { (yyval.odcl).slots = (yyvsp[-1].slist); (yyval.odcl).decls = (yyvsp[0].od); }
#line 2487 "CMDgram.c"
    break;

  case 50: /* object_decl_list: object_decl ';'  */
#line 305 "CMDgram.y"
      { (yyval.od) = (yyvsp[-1].od); }
#line 2493 "CMDgram.c"
    break;

  case 51: /* object_decl_list: object_decl_list object_decl ';'  */
#line 307 "CMDgram.y"
      { (yyvsp[-2].od)->append((yyvsp[-1].od)); (yyval.od) = (yyvsp[-2].od); }
#line 2499 "CMDgram.c"
    break;

  case 52: /* stmt_block: '{' statement_list '}'  */
#line 312 "CMDgram.y"
      { (yyval.stmt) = (yyvsp[-1].stmt); }
#line 2505 "CMDgram.c"
    break;

  case 53: /* stmt_block: stmt  */
#line 314 "CMDgram.y"
      { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2511 "CMDgram.c"
    break;

  case 54: /* switch_stmt: rwSWITCH '(' expr ')' '{' case_block '}'  */
#line 319 "CMDgram.y"
      { (yyval.stmt) = (yyvsp[-1].ifnode); (yyvsp[-1].ifnode)->propagateSwitchExpr((yyvsp[-4].expr), false); }
#line 2517 "CMDgram.c"
    break;

  case 55: /* switch_stmt: rwSWITCHSTR '(' expr ')' '{' case_block '}'  */
#line 321 "CMDgram.y"
      { (yyval.stmt) = (yyvsp[-1].ifnode); (yyvsp[-1].ifnode)->propagateSwitchExpr((yyvsp[-4].expr), true); }
#line 2523 "CMDgram.c"
    break;

  case 56: /* case_block: rwCASE case_expr ':' statement_list  */
#line 326 "CMDgram.y"
      { (yyval.ifnode) = IfStmtNode::alloc( (yyvsp[-3].i).lineNumber, (yyvsp[-2].expr), (yyvsp[0].stmt), NULL, false); }
#line 2529 "CMDgram.c"
    break;

  case 57: /* case_block: rwCASE case_expr ':' statement_list rwDEFAULT ':' statement_list  */
#line 328 "CMDgram.y"
      { (yyval.ifnode) = IfStmtNode::alloc( (yyvsp[-6].i).lineNumber, (yyvsp[-5].expr), (yyvsp[-3].stmt), (yyvsp[0].stmt), false); }
#line 2535 "CMDgram.c"
    break;

  case 58: /* case_block: rwCASE case_expr ':' statement_list case_block  */
#line 330 "CMDgram.y"
      { (yyval.ifnode) = IfStmtNode::alloc( (yyvsp[-4].i).lineNumber, (yyvsp[-3].expr), (yyvsp[-1].stmt), (yyvsp[0].ifnode), true); }
#line 2541 "CMDgram.c"
    break;

  case 59: /* case_expr: expr  */
#line 335 "CMDgram.y"
      { (yyval.expr) = (yyvsp[0].expr);}
#line 2547 "CMDgram.c"
    break;

  case 60: /* case_expr: case_expr rwCASEOR expr  */
#line 337 "CMDgram.y"
      { ((yyvsp[-2].expr))->append((yyvsp[0].expr)); (yyval.expr)=(yyvsp[-2].expr); }
#line 2553 "CMDgram.c"
    break;

  case 61: /* if_stmt: rwIF '(' expr ')' stmt_block  */
#line 342 "CMDgram.y"
      { (yyval.stmt) = IfStmtNode::alloc((yyvsp[-4].i).lineNumber, (yyvsp[-2].expr), (yyvsp[0].stmt), NULL, false); }
#line 2559 "CMDgram.c"
    break;

  case 62: /* if_stmt: rwIF '(' expr ')' stmt_block rwELSE stmt_block  */
#line 344 "CMDgram.y"
      { (yyval.stmt) = IfStmtNode::alloc((yyvsp[-6].i).lineNumber, (yyvsp[-4].expr), (yyvsp[-2].stmt), (yyvsp[0].stmt), false); }
#line 2565 "CMDgram.c"
    break;

  case 63: /* while_stmt: rwWHILE '(' expr ')' stmt_block  */
#line 349 "CMDgram.y"
      { (yyval.stmt) = LoopStmtNode::alloc((yyvsp[-4].i).lineNumber, nil, (yyvsp[-2].expr), nil, (yyvsp[0].stmt), false); }
#line 2571 "CMDgram.c"
    break;

  case 64: /* while_stmt: rwDO stmt_block rwWHILE '(' expr ')'  */
#line 351 "CMDgram.y"
      { (yyval.stmt) = LoopStmtNode::alloc((yyvsp[-3].i).lineNumber, nil, (yyvsp[-1].expr), nil, (yyvsp[-4].stmt), true); }
#line 2577 "CMDgram.c"
    break;

  case 65: /* for_stmt: rwFOR '(' expr ';' expr ';' expr ')' stmt_block  */
#line 356 "CMDgram.y"
      { (yyval.stmt) = LoopStmtNode::alloc((yyvsp[-8].i).lineNumber, (yyvsp[-6].expr), (yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].stmt), false); }
#line 2583 "CMDgram.c"
    break;

  case 66: /* for_stmt: rwFOR '(' expr ';' expr ';' ')' stmt_block  */
#line 358 "CMDgram.y"
      { (yyval.stmt) = LoopStmtNode::alloc((yyvsp[-7].i).lineNumber, (yyvsp[-5].expr), (yyvsp[-3].expr), NULL, (yyvsp[0].stmt), false); }
#line 2589 "CMDgram.c"
    break;

  case 67: /* for_stmt: rwFOR '(' expr ';' ';' expr ')' stmt_block  */
#line 360 "CMDgram.y"
      { (yyval.stmt) = LoopStmtNode::alloc((yyvsp[-7].i).lineNumber, (yyvsp[-5].expr), NULL, (yyvsp[-2].expr), (yyvsp[0].stmt), false); }
#line 2595 "CMDgram.c"
    break;

  case 68: /* for_stmt: rwFOR '(' expr ';' ';' ')' stmt_block  */
#line 362 "CMDgram.y"
      { (yyval.stmt) = LoopStmtNode::alloc((yyvsp[-6].i).lineNumber, (yyvsp[-4].expr), NULL, NULL, (yyvsp[0].stmt), false); }
#line 2601 "CMDgram.c"
    break;

  case 69: /* for_stmt: rwFOR '(' ';' expr ';' expr ')' stmt_block  */
#line 364 "CMDgram.y"
      { (yyval.stmt) = LoopStmtNode::alloc((yyvsp[-7].i).lineNumber, NULL, (yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].stmt), false); }
#line 2607 "CMDgram.c"
    break;

  case 70: /* for_stmt: rwFOR '(' ';' expr ';' ')' stmt_block  */
#line 366 "CMDgram.y"
      { (yyval.stmt) = LoopStmtNode::alloc((yyvsp[-6].i).lineNumber, NULL, (yyvsp[-3].expr), NULL, (yyvsp[0].stmt), false); }
#line 2613 "CMDgram.c"
    break;

  case 71: /* for_stmt: rwFOR '(' ';' ';' expr ')' stmt_block  */
#line 368 "CMDgram.y"
      { (yyval.stmt) = LoopStmtNode::alloc((yyvsp[-6].i).lineNumber, NULL, NULL, (yyvsp[-2].expr), (yyvsp[0].stmt), false); }
#line 2619 "CMDgram.c"
    break;

  case 72: /* for_stmt: rwFOR '(' ';' ';' ')' stmt_block  */
#line 370 "CMDgram.y"
      { (yyval.stmt) = LoopStmtNode::alloc((yyvsp[-5].i).lineNumber, NULL, NULL, NULL, (yyvsp[0].stmt), false); }
#line 2625 "CMDgram.c"
    break;

  case 73: /* foreach_stmt: rwFOREACH '(' VAR rwIN expr ')' stmt_block  */
#line 375 "CMDgram.y"
      { (yyval.stmt) = IterStmtNode::alloc( (yyvsp[-6].i).lineNumber, (yyvsp[-4].s).value, (yyvsp[-2].expr), (yyvsp[0].stmt), false ); }
#line 2631 "CMDgram.c"
    break;

  case 74: /* foreach_stmt: rwFOREACHSTR '(' VAR rwIN expr ')' stmt_block  */
#line 377 "CMDgram.y"
      { (yyval.stmt) = IterStmtNode::alloc( (yyvsp[-6].i).lineNumber, (yyvsp[-4].s).value, (yyvsp[-2].expr), (yyvsp[0].stmt), true ); }
#line 2637 "CMDgram.c"
    break;

  case 75: /* expression_stmt: stmt_expr  */
#line 382 "CMDgram.y"
      { (yyval.stmt) = (yyvsp[0].expr); }
#line 2643 "CMDgram.c"
    break;

  case 76: /* expr: stmt_expr  */
#line 387 "CMDgram.y"
      { (yyval.expr) = (yyvsp[0].expr); }
#line 2649 "CMDgram.c"
    break;

  case 77: /* expr: '(' expr ')'  */
#line 389 "CMDgram.y"
      { (yyval.expr) = (yyvsp[-1].expr); }
#line 2655 "CMDgram.c"
    break;

  case 78: /* expr: expr '^' expr  */
#line 391 "CMDgram.y"
      { (yyval.expr) = IntBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2661 "CMDgram.c"
    break;

  case 79: /* expr: expr '%' expr  */
#line 393 "CMDgram.y"
      { (yyval.expr) = IntBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2667 "CMDgram.c"
    break;

  case 80: /* expr: expr '&' expr  */
#line 395 "CMDgram.y"
      { (yyval.expr) = IntBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2673 "CMDgram.c"
    break;

  case 81: /* expr: expr '|' expr  */
#line 397 "CMDgram.y"
      { (yyval.expr) = IntBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2679 "CMDgram.c"
    break;

  case 82: /* expr: expr '+' expr  */
#line 399 "CMDgram.y"
      { (yyval.expr) = FloatBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2685 "CMDgram.c"
    break;

  case 83: /* expr: expr '-' expr  */
#line 401 "CMDgram.y"
      { (yyval.expr) = FloatBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2691 "CMDgram.c"
    break;

  case 84: /* expr: expr '*' expr  */
#line 403 "CMDgram.y"
      { (yyval.expr) = FloatBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2697 "CMDgram.c"
    break;

  case 85: /* expr: expr '/' expr  */
#line 405 "CMDgram.y"
      { (yyval.expr) = FloatBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2703 "CMDgram.c"
    break;

  case 86: /* expr: '-' expr  */
#line 407 "CMDgram.y"
      { (yyval.expr) = FloatUnaryExprNode::alloc( (yyvsp[-1].i).lineNumber, (yyvsp[-1].i).value, (yyvsp[0].expr)); }
#line 2709 "CMDgram.c"
    break;

  case 87: /* expr: '*' expr  */
#line 409 "CMDgram.y"
      { (yyval.expr) = TTagDerefNode::alloc( (yyvsp[-1].i).lineNumber, (yyvsp[0].expr) ); }
#line 2715 "CMDgram.c"
    break;

  case 88: /* expr: TTAG  */
#line 411 "CMDgram.y"
      { (yyval.expr) = TTagExprNode::alloc( (yyvsp[0].s).lineNumber, (yyvsp[0].s).value ); }
#line 2721 "CMDgram.c"
    break;

  case 89: /* expr: expr '?' expr ':' expr  */
#line 413 "CMDgram.y"
      { (yyval.expr) = ConditionalExprNode::alloc( (yyvsp[-4].expr)->dbgLineNumber, (yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2727 "CMDgram.c"
    break;

  case 90: /* expr: expr '<' expr  */
#line 415 "CMDgram.y"
      { (yyval.expr) = IntBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2733 "CMDgram.c"
    break;

  case 91: /* expr: expr '>' expr  */
#line 417 "CMDgram.y"
      { (yyval.expr) = IntBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2739 "CMDgram.c"
    break;

  case 92: /* expr: expr opGE expr  */
#line 419 "CMDgram.y"
      { (yyval.expr) = IntBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2745 "CMDgram.c"
    break;

  case 93: /* expr: expr opLE expr  */
#line 421 "CMDgram.y"
      { (yyval.expr) = IntBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2751 "CMDgram.c"
    break;

  case 94: /* expr: expr opEQ expr  */
#line 423 "CMDgram.y"
      { (yyval.expr) = IntBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2757 "CMDgram.c"
    break;

  case 95: /* expr: expr opNE expr  */
#line 425 "CMDgram.y"
      { (yyval.expr) = IntBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2763 "CMDgram.c"
    break;

  case 96: /* expr: expr opOR expr  */
#line 427 "CMDgram.y"
      { (yyval.expr) = IntBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2769 "CMDgram.c"
    break;

  case 97: /* expr: expr opSHL expr  */
#line 429 "CMDgram.y"
      { (yyval.expr) = IntBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2775 "CMDgram.c"
    break;

  case 98: /* expr: expr opSHR expr  */
#line 431 "CMDgram.y"
      { (yyval.expr) = IntBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2781 "CMDgram.c"
    break;

  case 99: /* expr: expr opAND expr  */
#line 433 "CMDgram.y"
      { (yyval.expr) = IntBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2787 "CMDgram.c"
    break;

  case 100: /* expr: expr opSTREQ expr  */
#line 435 "CMDgram.y"
      { (yyval.expr) = StreqExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-2].expr), (yyvsp[0].expr), true); }
#line 2793 "CMDgram.c"
    break;

  case 101: /* expr: expr opSTRNE expr  */
#line 437 "CMDgram.y"
      { (yyval.expr) = StreqExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-2].expr), (yyvsp[0].expr), false); }
#line 2799 "CMDgram.c"
    break;

  case 102: /* expr: expr '@' expr  */
#line 439 "CMDgram.y"
      { (yyval.expr) = StrcatExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].i).value); }
#line 2805 "CMDgram.c"
    break;

  case 103: /* expr: '!' expr  */
#line 441 "CMDgram.y"
      { (yyval.expr) = IntUnaryExprNode::alloc((yyvsp[-1].i).lineNumber, (yyvsp[-1].i).value, (yyvsp[0].expr)); }
#line 2811 "CMDgram.c"
    break;

  case 104: /* expr: '~' expr  */
#line 443 "CMDgram.y"
      { (yyval.expr) = IntUnaryExprNode::alloc((yyvsp[-1].i).lineNumber, (yyvsp[-1].i).value, (yyvsp[0].expr)); }
#line 2817 "CMDgram.c"
    break;

  case 105: /* expr: TAGATOM  */
#line 445 "CMDgram.y"
      { (yyval.expr) = StrConstNode::alloc( (yyvsp[0].str).lineNumber, (yyvsp[0].str).value, true); }
#line 2823 "CMDgram.c"
    break;

  case 106: /* expr: FLTCONST  */
#line 447 "CMDgram.y"
      { (yyval.expr) = FloatNode::alloc( (yyvsp[0].f).lineNumber, (yyvsp[0].f).value ); }
#line 2829 "CMDgram.c"
    break;

  case 107: /* expr: INTCONST  */
#line 449 "CMDgram.y"
      { (yyval.expr) = IntNode::alloc( (yyvsp[0].i).lineNumber, (yyvsp[0].i).value ); }
#line 2835 "CMDgram.c"
    break;

  case 108: /* expr: rwBREAK  */
#line 451 "CMDgram.y"
      { (yyval.expr) = ConstantNode::alloc( (yyvsp[0].i).lineNumber, StringTable->insert("break")); }
#line 2841 "CMDgram.c"
    break;

  case 109: /* expr: slot_acc  */
#line 453 "CMDgram.y"
      { (yyval.expr) = SlotAccessNode::alloc( (yyvsp[0].slot).lineNumber, (yyvsp[0].slot).object, (yyvsp[0].slot).array, (yyvsp[0].slot).slotName ); }
#line 2847 "CMDgram.c"
    break;

  case 110: /* expr: intslot_acc  */
#line 455 "CMDgram.y"
      { (yyval.expr) = InternalSlotAccessNode::alloc( (yyvsp[0].intslot).lineNumber, (yyvsp[0].intslot).object, (yyvsp[0].intslot).slotExpr, (yyvsp[0].intslot).recurse); }
#line 2853 "CMDgram.c"
    break;

  case 111: /* expr: IDENT  */
#line 457 "CMDgram.y"
      { (yyval.expr) = ConstantNode::alloc( (yyvsp[0].s).lineNumber, (yyvsp[0].s).value ); }
#line 2859 "CMDgram.c"
    break;

  case 112: /* expr: STRATOM  */
#line 459 "CMDgram.y"
      { (yyval.expr) = StrConstNode::alloc( (yyvsp[0].str).lineNumber, (yyvsp[0].str).value, false); }
#line 2865 "CMDgram.c"
    break;

  case 113: /* expr: VAR  */
#line 461 "CMDgram.y"
      { (yyval.expr) = (ExprNode*)VarNode::alloc( (yyvsp[0].s).lineNumber, (yyvsp[0].s).value, NULL); }
#line 2871 "CMDgram.c"
    break;

  case 114: /* expr: VAR '[' aidx_expr ']'  */
#line 463 "CMDgram.y"
      { (yyval.expr) = (ExprNode*)VarNode::alloc( (yyvsp[-3].s).lineNumber, (yyvsp[-3].s).value, (yyvsp[-1].expr) ); }
#line 2877 "CMDgram.c"
    break;

  case 115: /* expr: expr '[' expr ']'  */
#line 465 "CMDgram.y"
      { (yyval.expr) = VectorIndexNode::alloc((yyvsp[-3].expr)->dbgLineNumber, (yyvsp[-3].expr), (yyvsp[-1].expr)); }
#line 2883 "CMDgram.c"
    break;

  case 116: /* expr: '[' expr_list_decl ']'  */
#line 467 "CMDgram.y"
      {
         Vector<ExprNode*> elems;
         if ((yyvsp[-1].expr)) {
            // expr_list already chains ExprNodes using append(),
            // so walk and collect them
            for (ExprNode* e = (yyvsp[-1].expr); e; e = (ExprNode*)e->getNext())
               elems.push_back(e);
         }
         (yyval.expr) = VectorExprNode::alloc((yylsp[-2]).first_line, elems);
      }
#line 2898 "CMDgram.c"
    break;

  case 117: /* slot_acc: expr '.' IDENT  */
#line 498 "CMDgram.y"
      { (yyval.slot).lineNumber = (yyvsp[-2].expr)->dbgLineNumber; (yyval.slot).object = (yyvsp[-2].expr); (yyval.slot).slotName = (yyvsp[0].s).value; (yyval.slot).array = NULL; }
#line 2904 "CMDgram.c"
    break;

  case 118: /* slot_acc: expr '.' IDENT '[' aidx_expr ']'  */
#line 500 "CMDgram.y"
      { (yyval.slot).lineNumber = (yyvsp[-5].expr)->dbgLineNumber; (yyval.slot).object = (yyvsp[-5].expr); (yyval.slot).slotName = (yyvsp[-3].s).value; (yyval.slot).array = (yyvsp[-1].expr); }
#line 2910 "CMDgram.c"
    break;

  case 119: /* intslot_acc: expr opINTNAME class_name_expr  */
#line 505 "CMDgram.y"
     { (yyval.intslot).lineNumber = (yyvsp[-2].expr)->dbgLineNumber; (yyval.intslot).object = (yyvsp[-2].expr); (yyval.intslot).slotExpr = (yyvsp[0].expr); (yyval.intslot).recurse = false; }
#line 2916 "CMDgram.c"
    break;

  case 120: /* intslot_acc: expr opINTNAMER class_name_expr  */
#line 507 "CMDgram.y"
     { (yyval.intslot).lineNumber = (yyvsp[-2].expr)->dbgLineNumber; (yyval.intslot).object = (yyvsp[-2].expr); (yyval.intslot).slotExpr = (yyvsp[0].expr); (yyval.intslot).recurse = true; }
#line 2922 "CMDgram.c"
    break;

  case 121: /* class_name_expr: IDENT  */
#line 512 "CMDgram.y"
      { (yyval.expr) = ConstantNode::alloc( (yyvsp[0].s).lineNumber, (yyvsp[0].s).value ); }
#line 2928 "CMDgram.c"
    break;

  case 122: /* class_name_expr: '(' expr ')'  */
#line 514 "CMDgram.y"
      { (yyval.expr) = (yyvsp[-1].expr); }
#line 2934 "CMDgram.c"
    break;

  case 123: /* assign_op_struct: opPLUSPLUS  */
#line 519 "CMDgram.y"
      { (yyval.asn).lineNumber = (yyvsp[0].i).lineNumber; (yyval.asn).token = opPLUSPLUS; (yyval.asn).expr = FloatNode::alloc( (yyvsp[0].i).lineNumber, 1 ); }
#line 2940 "CMDgram.c"
    break;

  case 124: /* assign_op_struct: opMINUSMINUS  */
#line 521 "CMDgram.y"
      { (yyval.asn).lineNumber = (yyvsp[0].i).lineNumber; (yyval.asn).token = opMINUSMINUS; (yyval.asn).expr = FloatNode::alloc( (yyvsp[0].i).lineNumber, 1 ); }
#line 2946 "CMDgram.c"
    break;

  case 125: /* assign_op_struct: opPLASN expr  */
#line 523 "CMDgram.y"
      { (yyval.asn).lineNumber = (yyvsp[-1].i).lineNumber; (yyval.asn).token = '+'; (yyval.asn).expr = (yyvsp[0].expr); }
#line 2952 "CMDgram.c"
    break;

  case 126: /* assign_op_struct: opMIASN expr  */
#line 525 "CMDgram.y"
      { (yyval.asn).lineNumber = (yyvsp[-1].i).lineNumber; (yyval.asn).token = '-'; (yyval.asn).expr = (yyvsp[0].expr); }
#line 2958 "CMDgram.c"
    break;

  case 127: /* assign_op_struct: opMLASN expr  */
#line 527 "CMDgram.y"
      { (yyval.asn).lineNumber = (yyvsp[-1].i).lineNumber; (yyval.asn).token = '*'; (yyval.asn).expr = (yyvsp[0].expr); }
#line 2964 "CMDgram.c"
    break;

  case 128: /* assign_op_struct: opDVASN expr  */
#line 529 "CMDgram.y"
      { (yyval.asn).lineNumber = (yyvsp[-1].i).lineNumber; (yyval.asn).token = '/'; (yyval.asn).expr = (yyvsp[0].expr); }
#line 2970 "CMDgram.c"
    break;

  case 129: /* assign_op_struct: opMODASN expr  */
#line 531 "CMDgram.y"
      { (yyval.asn).lineNumber = (yyvsp[-1].i).lineNumber; (yyval.asn).token = '%'; (yyval.asn).expr = (yyvsp[0].expr); }
#line 2976 "CMDgram.c"
    break;

  case 130: /* assign_op_struct: opANDASN expr  */
#line 533 "CMDgram.y"
      { (yyval.asn).lineNumber = (yyvsp[-1].i).lineNumber; (yyval.asn).token = '&'; (yyval.asn).expr = (yyvsp[0].expr); }
#line 2982 "CMDgram.c"
    break;

  case 131: /* assign_op_struct: opXORASN expr  */
#line 535 "CMDgram.y"
      { (yyval.asn).lineNumber = (yyvsp[-1].i).lineNumber; (yyval.asn).token = '^'; (yyval.asn).expr = (yyvsp[0].expr); }
#line 2988 "CMDgram.c"
    break;

  case 132: /* assign_op_struct: opORASN expr  */
#line 537 "CMDgram.y"
      { (yyval.asn).lineNumber = (yyvsp[-1].i).lineNumber; (yyval.asn).token = '|'; (yyval.asn).expr = (yyvsp[0].expr); }
#line 2994 "CMDgram.c"
    break;

  case 133: /* assign_op_struct: opSLASN expr  */
#line 539 "CMDgram.y"
      { (yyval.asn).lineNumber = (yyvsp[-1].i).lineNumber; (yyval.asn).token = opSHL; (yyval.asn).expr = (yyvsp[0].expr); }
#line 3000 "CMDgram.c"
    break;

  case 134: /* assign_op_struct: opSRASN expr  */
#line 541 "CMDgram.y"
      { (yyval.asn).lineNumber = (yyvsp[-1].i).lineNumber; (yyval.asn).token = opSHR; (yyval.asn).expr = (yyvsp[0].expr); }
#line 3006 "CMDgram.c"
    break;

  case 135: /* stmt_expr: funcall_expr  */
#line 546 "CMDgram.y"
      { (yyval.expr) = (yyvsp[0].expr); }
#line 3012 "CMDgram.c"
    break;

  case 136: /* stmt_expr: assert_expr  */
#line 548 "CMDgram.y"
      { (yyval.expr) = (yyvsp[0].expr); }
#line 3018 "CMDgram.c"
    break;

  case 137: /* stmt_expr: object_decl  */
#line 550 "CMDgram.y"
      { (yyval.expr) = (yyvsp[0].od); }
#line 3024 "CMDgram.c"
    break;

  case 138: /* stmt_expr: VAR '=' expr  */
#line 552 "CMDgram.y"
      { (yyval.expr) = AssignExprNode::alloc( (yyvsp[-2].s).lineNumber, (yyvsp[-2].s).value, NULL, (yyvsp[0].expr)); }
#line 3030 "CMDgram.c"
    break;

  case 139: /* stmt_expr: VAR '[' aidx_expr ']' '=' expr  */
#line 554 "CMDgram.y"
      { (yyval.expr) = AssignExprNode::alloc( (yyvsp[-5].s).lineNumber, (yyvsp[-5].s).value, (yyvsp[-3].expr), (yyvsp[0].expr)); }
#line 3036 "CMDgram.c"
    break;

  case 140: /* stmt_expr: VAR assign_op_struct  */
#line 556 "CMDgram.y"
      { (yyval.expr) = AssignOpExprNode::alloc( (yyvsp[-1].s).lineNumber, (yyvsp[-1].s).value, NULL, (yyvsp[0].asn).expr, (yyvsp[0].asn).token); }
#line 3042 "CMDgram.c"
    break;

  case 141: /* stmt_expr: VAR '[' aidx_expr ']' assign_op_struct  */
#line 558 "CMDgram.y"
      { (yyval.expr) = AssignOpExprNode::alloc( (yyvsp[-4].s).lineNumber, (yyvsp[-4].s).value, (yyvsp[-2].expr), (yyvsp[0].asn).expr, (yyvsp[0].asn).token); }
#line 3048 "CMDgram.c"
    break;

  case 142: /* stmt_expr: slot_acc assign_op_struct  */
#line 560 "CMDgram.y"
      { (yyval.expr) = SlotAssignOpNode::alloc( (yyvsp[-1].slot).lineNumber, (yyvsp[-1].slot).object, (yyvsp[-1].slot).slotName, (yyvsp[-1].slot).array, (yyvsp[0].asn).token, (yyvsp[0].asn).expr); }
#line 3054 "CMDgram.c"
    break;

  case 143: /* stmt_expr: slot_acc '=' expr  */
#line 562 "CMDgram.y"
      { (yyval.expr) = SlotAssignNode::alloc( (yyvsp[-2].slot).lineNumber, (yyvsp[-2].slot).object, (yyvsp[-2].slot).array, (yyvsp[-2].slot).slotName, (yyvsp[0].expr)); }
#line 3060 "CMDgram.c"
    break;

  case 144: /* stmt_expr: slot_acc '=' '{' expr_list '}'  */
#line 564 "CMDgram.y"
      { (yyval.expr) = SlotAssignNode::alloc( (yyvsp[-4].slot).lineNumber, (yyvsp[-4].slot).object, (yyvsp[-4].slot).array, (yyvsp[-4].slot).slotName, (yyvsp[-1].expr)); }
#line 3066 "CMDgram.c"
    break;

  case 145: /* funcall_expr: IDENT '(' expr_list_decl ')'  */
#line 569 "CMDgram.y"
     { (yyval.expr) = FuncCallExprNode::alloc( (yyvsp[-3].s).lineNumber, (yyvsp[-3].s).value, NULL, (yyvsp[-1].expr), false); }
#line 3072 "CMDgram.c"
    break;

  case 146: /* funcall_expr: IDENT opCOLONCOLON IDENT '(' expr_list_decl ')'  */
#line 571 "CMDgram.y"
     { (yyval.expr) = FuncCallExprNode::alloc( (yyvsp[-5].s).lineNumber, (yyvsp[-3].s).value, (yyvsp[-5].s).value, (yyvsp[-1].expr), false); }
#line 3078 "CMDgram.c"
    break;

  case 147: /* funcall_expr: expr '.' IDENT '(' expr_list_decl ')'  */
#line 573 "CMDgram.y"
      { (yyvsp[-5].expr)->append((yyvsp[-1].expr)); (yyval.expr) = FuncCallExprNode::alloc( (yyvsp[-5].expr)->dbgLineNumber, (yyvsp[-3].s).value, NULL, (yyvsp[-5].expr), true); }
#line 3084 "CMDgram.c"
    break;

  case 148: /* assert_expr: rwASSERT '(' expr ')'  */
#line 583 "CMDgram.y"
      { (yyval.expr) = AssertCallExprNode::alloc( (yyvsp[-3].i).lineNumber, (yyvsp[-1].expr), NULL ); }
#line 3090 "CMDgram.c"
    break;

  case 149: /* assert_expr: rwASSERT '(' expr ',' STRATOM ')'  */
#line 585 "CMDgram.y"
      { (yyval.expr) = AssertCallExprNode::alloc( (yyvsp[-5].i).lineNumber, (yyvsp[-3].expr), (yyvsp[-1].str).value ); }
#line 3096 "CMDgram.c"
    break;

  case 150: /* expr_list_decl: %empty  */
#line 590 "CMDgram.y"
      { (yyval.expr) = NULL; }
#line 3102 "CMDgram.c"
    break;

  case 151: /* expr_list_decl: expr_list  */
#line 592 "CMDgram.y"
      { (yyval.expr) = (yyvsp[0].expr); }
#line 3108 "CMDgram.c"
    break;

  case 152: /* expr_list: expr  */
#line 597 "CMDgram.y"
      { (yyval.expr) = (yyvsp[0].expr); }
#line 3114 "CMDgram.c"
    break;

  case 153: /* expr_list: expr_list ',' expr  */
#line 599 "CMDgram.y"
      { ((yyvsp[-2].expr))->append((yyvsp[0].expr)); (yyval.expr) = (yyvsp[-2].expr); }
#line 3120 "CMDgram.c"
    break;

  case 154: /* slot_assign_list_opt: %empty  */
#line 604 "CMDgram.y"
      { (yyval.slist) = NULL; }
#line 3126 "CMDgram.c"
    break;

  case 155: /* slot_assign_list_opt: slot_assign_list  */
#line 606 "CMDgram.y"
      { (yyval.slist) = (yyvsp[0].slist); }
#line 3132 "CMDgram.c"
    break;

  case 156: /* slot_assign_list: slot_assign  */
#line 611 "CMDgram.y"
      { (yyval.slist) = (yyvsp[0].slist); }
#line 3138 "CMDgram.c"
    break;

  case 157: /* slot_assign_list: slot_assign_list slot_assign  */
#line 613 "CMDgram.y"
      { (yyvsp[-1].slist)->append((yyvsp[0].slist)); (yyval.slist) = (yyvsp[-1].slist); }
#line 3144 "CMDgram.c"
    break;

  case 158: /* slot_assign: IDENT '=' expr ';'  */
#line 618 "CMDgram.y"
      { (yyval.slist) = SlotAssignNode::alloc( (yyvsp[-3].s).lineNumber, NULL, NULL, (yyvsp[-3].s).value, (yyvsp[-1].expr)); }
#line 3150 "CMDgram.c"
    break;

  case 159: /* slot_assign: TYPEIDENT IDENT '=' expr ';'  */
#line 620 "CMDgram.y"
      { (yyval.slist) = SlotAssignNode::alloc( (yyvsp[-4].i).lineNumber, NULL, NULL, (yyvsp[-3].s).value, (yyvsp[-1].expr), (yyvsp[-4].i).value); }
#line 3156 "CMDgram.c"
    break;

  case 160: /* slot_assign: rwDATABLOCK '=' expr ';'  */
#line 622 "CMDgram.y"
      { (yyval.slist) = SlotAssignNode::alloc( (yyvsp[-3].i).lineNumber, NULL, NULL, StringTable->insert("datablock"), (yyvsp[-1].expr)); }
#line 3162 "CMDgram.c"
    break;

  case 161: /* slot_assign: IDENT '[' aidx_expr ']' '=' expr ';'  */
#line 624 "CMDgram.y"
      { (yyval.slist) = SlotAssignNode::alloc( (yyvsp[-6].s).lineNumber, NULL, (yyvsp[-4].expr), (yyvsp[-6].s).value, (yyvsp[-1].expr)); }
#line 3168 "CMDgram.c"
    break;

  case 162: /* slot_assign: TYPEIDENT IDENT '[' aidx_expr ']' '=' expr ';'  */
#line 626 "CMDgram.y"
      { (yyval.slist) = SlotAssignNode::alloc( (yyvsp[-7].i).lineNumber, NULL, (yyvsp[-4].expr), (yyvsp[-6].s).value, (yyvsp[-1].expr), (yyvsp[-7].i).value); }
#line 3174 "CMDgram.c"
    break;

  case 163: /* aidx_expr: expr  */
#line 631 "CMDgram.y"
      { (yyval.expr) = (yyvsp[0].expr); }
#line 3180 "CMDgram.c"
    break;

  case 164: /* aidx_expr: aidx_expr ',' expr  */
#line 633 "CMDgram.y"
      { (yyval.expr) = CommaCatExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3186 "CMDgram.c"
    break;


#line 3190 "CMDgram.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        if (yyreport_syntax_error (&yyctx) == 2)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 635 "CMDgram.y"


int
yyreport_syntax_error (const yypcontext_t *ctx)
{
   int ret = 0;
   String output;
   const YYLTYPE *loc = yypcontext_location (ctx);
   output += "syntax error: ";

   yysymbol_kind_t nxt = yypcontext_token(ctx);
   if (nxt != YYSYMBOL_YYEMPTY)
      output += String::ToString("unexpected: %s at column: %d", yysymbol_name(nxt), loc->first_column);

   enum { TOKENMAX = 10 };
   yysymbol_kind_t expected[TOKENMAX];

   int exp = yypcontext_expected_tokens(ctx, expected, TOKENMAX);
   if (exp < 0)
      ret = exp;
   else
   {
      for (int i = 0; i < exp; ++i)
         output += String::ToString("%s %s", i == 0 ? ": expected" : "or", yysymbol_name(expected[i]));
   }

   if (lines.size() > 0) 
   {
      output += "\n";
      for (int i = 0; i < lines.size(); i++)
      {
         int line = lines.size() - i;
         output += String::ToString("%5d | ", loc->first_line - (line-1)) + lines[i] + "\n";
      }
      output += String::ToString("%5s | %*s", "", loc->first_column, "^");
   }

   yyerror("%s", output.c_str());

   return ret;
}
