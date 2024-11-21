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




/* First part of user prologue.  */
#line 1 "test.y"

#include <stdio.h>
#include "tree.h"

int yylex();
int yyerror(char* s);
void adjustConsole();
int handleArguments(int argc, char* argv[]);
void redirectStdin(const char* fileName);

Node* syntax_tree = NULL;

#line 84 "test.tab.c"

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

#include "test.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUM_INTEIRO = 3,                /* NUM_INTEIRO  */
  YYSYMBOL_NUM_PONTO_FLUTUANTE = 4,        /* NUM_PONTO_FLUTUANTE  */
  YYSYMBOL_NUM_NOTACAO_CIENTIFICA = 5,     /* NUM_NOTACAO_CIENTIFICA  */
  YYSYMBOL_ID = 6,                         /* ID  */
  YYSYMBOL_MAIS = 7,                       /* MAIS  */
  YYSYMBOL_MENOS = 8,                      /* MENOS  */
  YYSYMBOL_VEZES = 9,                      /* VEZES  */
  YYSYMBOL_DOIS_PONTOS = 10,               /* DOIS_PONTOS  */
  YYSYMBOL_VIRGULA = 11,                   /* VIRGULA  */
  YYSYMBOL_MENOR = 12,                     /* MENOR  */
  YYSYMBOL_MAIOR = 13,                     /* MAIOR  */
  YYSYMBOL_IGUAL = 14,                     /* IGUAL  */
  YYSYMBOL_DIFERENTE = 15,                 /* DIFERENTE  */
  YYSYMBOL_MENOR_IGUAL = 16,               /* MENOR_IGUAL  */
  YYSYMBOL_DIVIDE = 17,                    /* DIVIDE  */
  YYSYMBOL_MAIOR_IGUAL = 18,               /* MAIOR_IGUAL  */
  YYSYMBOL_E = 19,                         /* E  */
  YYSYMBOL_OU = 20,                        /* OU  */
  YYSYMBOL_NAO = 21,                       /* NAO  */
  YYSYMBOL_ABRE_PARENTESE = 22,            /* ABRE_PARENTESE  */
  YYSYMBOL_FECHA_PARENTESE = 23,           /* FECHA_PARENTESE  */
  YYSYMBOL_ABRE_COLCHETE = 24,             /* ABRE_COLCHETE  */
  YYSYMBOL_FECHA_COLCHETE = 25,            /* FECHA_COLCHETE  */
  YYSYMBOL_SE = 26,                        /* SE  */
  YYSYMBOL_ENTAO = 27,                     /* ENTAO  */
  YYSYMBOL_SENAO = 28,                     /* SENAO  */
  YYSYMBOL_FIM = 29,                       /* FIM  */
  YYSYMBOL_REPITA = 30,                    /* REPITA  */
  YYSYMBOL_ATE = 31,                       /* ATE  */
  YYSYMBOL_ATRIBUICAO = 32,                /* ATRIBUICAO  */
  YYSYMBOL_LEIA = 33,                      /* LEIA  */
  YYSYMBOL_ESCREVA = 34,                   /* ESCREVA  */
  YYSYMBOL_RETORNA = 35,                   /* RETORNA  */
  YYSYMBOL_INTEIRO = 36,                   /* INTEIRO  */
  YYSYMBOL_FLUTUANTE = 37,                 /* FLUTUANTE  */
  YYSYMBOL_YYACCEPT = 38,                  /* $accept  */
  YYSYMBOL_programa = 39,                  /* programa  */
  YYSYMBOL_lista_declaracoes = 40,         /* lista_declaracoes  */
  YYSYMBOL_declaracao = 41,                /* declaracao  */
  YYSYMBOL_declaracao_variaveis = 42,      /* declaracao_variaveis  */
  YYSYMBOL_inicializacao_variaveis = 43,   /* inicializacao_variaveis  */
  YYSYMBOL_lista_variaveis = 44,           /* lista_variaveis  */
  YYSYMBOL_var = 45,                       /* var  */
  YYSYMBOL_indice = 46,                    /* indice  */
  YYSYMBOL_tipo = 47,                      /* tipo  */
  YYSYMBOL_declaracao_funcao = 48,         /* declaracao_funcao  */
  YYSYMBOL_cabecalho = 49,                 /* cabecalho  */
  YYSYMBOL_lista_parametros = 50,          /* lista_parametros  */
  YYSYMBOL_parametro = 51,                 /* parametro  */
  YYSYMBOL_corpo = 52,                     /* corpo  */
  YYSYMBOL_acao = 53,                      /* acao  */
  YYSYMBOL_se = 54,                        /* se  */
  YYSYMBOL_repita = 55,                    /* repita  */
  YYSYMBOL_atribuicao = 56,                /* atribuicao  */
  YYSYMBOL_leia = 57,                      /* leia  */
  YYSYMBOL_escreva = 58,                   /* escreva  */
  YYSYMBOL_retorna = 59,                   /* retorna  */
  YYSYMBOL_expressao = 60,                 /* expressao  */
  YYSYMBOL_expressao_logica = 61,          /* expressao_logica  */
  YYSYMBOL_expressao_simples = 62,         /* expressao_simples  */
  YYSYMBOL_expressao_aditiva = 63,         /* expressao_aditiva  */
  YYSYMBOL_expressao_multiplicativa = 64,  /* expressao_multiplicativa  */
  YYSYMBOL_expressao_unaria = 65,          /* expressao_unaria  */
  YYSYMBOL_operador_relacional = 66,       /* operador_relacional  */
  YYSYMBOL_operador_soma = 67,             /* operador_soma  */
  YYSYMBOL_operador_logico = 68,           /* operador_logico  */
  YYSYMBOL_operador_negacao = 69,          /* operador_negacao  */
  YYSYMBOL_operador_multiplicacao = 70,    /* operador_multiplicacao  */
  YYSYMBOL_fator = 71,                     /* fator  */
  YYSYMBOL_numero = 72,                    /* numero  */
  YYSYMBOL_chamada_funcao = 73,            /* chamada_funcao  */
  YYSYMBOL_lista_argumentos = 74,          /* lista_argumentos  */
  YYSYMBOL_vazio = 75                      /* vazio  */
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
typedef yytype_uint8 yy_state_t;

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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  17
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   193

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  79
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  131

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   292


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
      35,    36,    37
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    36,    36,    44,    48,    55,    59,    63,    70,    77,
      84,    88,    95,    99,   106,   113,   123,   127,   134,   138,
     145,   159,   163,   167,   174,   182,   193,   197,   204,   208,
     212,   216,   220,   224,   228,   235,   243,   255,   265,   272,
     283,   294,   305,   309,   316,   320,   327,   331,   338,   342,
     349,   353,   360,   364,   368,   375,   376,   377,   378,   379,
     380,   384,   385,   389,   390,   394,   398,   399,   403,   410,
     414,   418,   425,   429,   433,   440,   452,   456,   460,   467
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NUM_INTEIRO",
  "NUM_PONTO_FLUTUANTE", "NUM_NOTACAO_CIENTIFICA", "ID", "MAIS", "MENOS",
  "VEZES", "DOIS_PONTOS", "VIRGULA", "MENOR", "MAIOR", "IGUAL",
  "DIFERENTE", "MENOR_IGUAL", "DIVIDE", "MAIOR_IGUAL", "E", "OU", "NAO",
  "ABRE_PARENTESE", "FECHA_PARENTESE", "ABRE_COLCHETE", "FECHA_COLCHETE",
  "SE", "ENTAO", "SENAO", "FIM", "REPITA", "ATE", "ATRIBUICAO", "LEIA",
  "ESCREVA", "RETORNA", "INTEIRO", "FLUTUANTE", "$accept", "programa",
  "lista_declaracoes", "declaracao", "declaracao_variaveis",
  "inicializacao_variaveis", "lista_variaveis", "var", "indice", "tipo",
  "declaracao_funcao", "cabecalho", "lista_parametros", "parametro",
  "corpo", "acao", "se", "repita", "atribuicao", "leia", "escreva",
  "retorna", "expressao", "expressao_logica", "expressao_simples",
  "expressao_aditiva", "expressao_multiplicativa", "expressao_unaria",
  "operador_relacional", "operador_soma", "operador_logico",
  "operador_negacao", "operador_multiplicacao", "fator", "numero",
  "chamada_funcao", "lista_argumentos", "vazio", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-72)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      12,    39,   -72,   -72,    30,    12,   -72,   -72,   -72,    33,
      44,   -72,   -72,   -72,    16,   127,    13,   -72,   -72,   127,
      55,    73,   -72,    70,     6,    57,   -72,   -72,   -72,   -72,
      42,   -72,   -72,   -72,   127,    33,   -72,    58,    48,   153,
      64,     7,   -72,    54,    54,   -72,   -72,   -72,   127,   -72,
      60,    74,   -72,    80,    16,   -72,    62,   127,    65,   -72,
     -72,   -72,   127,   -72,   -72,   -72,   -72,   -72,   -72,   127,
     127,   -72,   -72,   127,   -72,   -72,   -72,    71,    73,   -72,
      57,    86,   -72,   -72,   -72,     9,   -72,   -72,   153,    64,
       7,   -72,   -72,   -72,   127,   -72,   -72,    76,    77,    78,
     -72,    85,   -72,   -72,   -72,   -72,   -72,   -72,   -72,   127,
     -72,    82,   121,    73,   127,   127,   -72,   -72,   127,    81,
      87,    88,     5,   -72,   -72,   -72,   -72,   -72,   -72,   156,
     -72
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    12,    16,    17,     0,     2,     4,     6,     7,     0,
       0,     5,    19,     9,    79,     0,    13,     1,     3,     0,
       0,     0,    18,     0,     0,    22,    23,    72,    73,    74,
      12,    61,    62,    65,     0,    69,    43,     0,    42,    44,
      46,    48,    50,     0,     0,    52,    71,    70,     0,    38,
      12,     8,    11,     0,     0,    79,     0,    79,     0,    15,
      63,    64,     0,    55,    56,    57,    58,    59,    60,     0,
       0,    66,    67,     0,    69,    53,    54,     0,     0,    24,
      21,     0,    27,    25,    77,     0,    78,    68,    45,    47,
      49,    51,    14,    10,     0,    20,    79,     0,     0,     0,
      29,     0,    26,    30,    31,    32,    33,    34,    28,     0,
      75,     0,     0,     0,     0,     0,    76,    79,     0,     0,
       0,     0,     0,    37,    39,    40,    41,    79,    35,     0,
      36
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -72,   -72,   -72,    96,    14,   -72,   -72,     0,   -72,     1,
     -72,    95,   -72,    63,   -71,   -72,   -72,   -72,    23,   -72,
     -72,   -72,   -12,   -72,    52,    49,    66,    67,   -72,   -38,
     -72,   -72,   -72,    31,   -72,   -72,   -72,   -10
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,   100,     8,    51,    35,    16,   101,
      11,    12,    24,    25,    81,   102,   103,   104,    36,   105,
     106,   107,   108,    38,    39,    40,    41,    42,    69,    43,
      62,    44,    73,    45,    46,    47,    85,    82
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
       9,    10,    70,    37,    26,     9,    10,    49,    27,    28,
      29,    30,    31,    32,     7,    23,    71,    54,     1,     7,
     109,    52,    58,    13,    72,   112,    33,    34,    13,    55,
      17,    94,   110,   127,   128,    96,    77,    48,    97,    98,
      99,     2,     3,    74,    74,    84,   122,    86,     2,     3,
      20,    70,     2,     3,    21,    23,   129,    27,    28,    29,
      30,    14,    74,    15,    57,    19,    15,    60,    61,    74,
      74,    31,    32,    74,    75,    76,    34,    14,    93,    50,
      53,    56,   111,    59,    15,    78,    79,    83,    87,    27,
      28,    29,    30,    31,    32,    21,    92,   116,   113,   114,
     115,    18,   120,   121,   124,    22,   123,    33,    34,   117,
     125,   126,    94,   119,    88,    95,    96,    80,    89,    97,
      98,    99,     2,     3,    27,    28,    29,    30,    31,    32,
      27,    28,    29,    30,    31,    32,    90,     0,     0,     0,
      91,     0,    33,    34,     0,     0,     0,    94,    33,    34,
       0,    96,   118,     0,    97,    98,    99,     2,     3,    27,
      28,    29,    30,    31,    32,    63,    64,    65,    66,    67,
       0,    68,     0,     0,     0,     0,     0,    33,    34,     0,
       0,     0,    94,     0,     0,   130,    96,     0,     0,    97,
      98,    99,     2,     3
};

static const yytype_int8 yycheck[] =
{
       0,     0,    40,    15,    14,     5,     5,    19,     3,     4,
       5,     6,     7,     8,     0,    14,     9,    11,     6,     5,
      11,    21,    34,     0,    17,    96,    21,    22,     5,    23,
       0,    26,    23,    28,    29,    30,    48,    24,    33,    34,
      35,    36,    37,    43,    44,    57,   117,    57,    36,    37,
       6,    89,    36,    37,    10,    54,   127,     3,     4,     5,
       6,    22,    62,    24,    22,    32,    24,    19,    20,    69,
      70,     7,     8,    73,    43,    44,    22,    22,    78,     6,
      10,    24,    94,    25,    24,    11,     6,    25,    23,     3,
       4,     5,     6,     7,     8,    10,    25,   109,    22,    22,
      22,     5,   114,   115,    23,    10,   118,    21,    22,    27,
      23,    23,    26,   113,    62,    29,    30,    54,    69,    33,
      34,    35,    36,    37,     3,     4,     5,     6,     7,     8,
       3,     4,     5,     6,     7,     8,    70,    -1,    -1,    -1,
      73,    -1,    21,    22,    -1,    -1,    -1,    26,    21,    22,
      -1,    30,    31,    -1,    33,    34,    35,    36,    37,     3,
       4,     5,     6,     7,     8,    12,    13,    14,    15,    16,
      -1,    18,    -1,    -1,    -1,    -1,    -1,    21,    22,    -1,
      -1,    -1,    26,    -1,    -1,    29,    30,    -1,    -1,    33,
      34,    35,    36,    37
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,    36,    37,    39,    40,    41,    42,    43,    45,
      47,    48,    49,    56,    22,    24,    46,     0,    41,    32,
       6,    10,    49,    47,    50,    51,    75,     3,     4,     5,
       6,     7,     8,    21,    22,    45,    56,    60,    61,    62,
      63,    64,    65,    67,    69,    71,    72,    73,    24,    60,
       6,    44,    45,    10,    11,    23,    24,    22,    60,    25,
      19,    20,    68,    12,    13,    14,    15,    16,    18,    66,
      67,     9,    17,    70,    45,    71,    71,    60,    11,     6,
      51,    52,    75,    25,    60,    74,    75,    23,    62,    63,
      64,    65,    25,    45,    26,    29,    30,    33,    34,    35,
      42,    47,    53,    54,    55,    57,    58,    59,    60,    11,
      23,    60,    52,    22,    22,    22,    60,    27,    31,    45,
      60,    60,    52,    60,    23,    23,    23,    28,    29,    52,
      29
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    38,    39,    40,    40,    41,    41,    41,    42,    43,
      44,    44,    45,    45,    46,    46,    47,    47,    48,    48,
      49,    50,    50,    50,    51,    51,    52,    52,    53,    53,
      53,    53,    53,    53,    53,    54,    54,    55,    56,    57,
      58,    59,    60,    60,    61,    61,    62,    62,    63,    63,
      64,    64,    65,    65,    65,    66,    66,    66,    66,    66,
      66,    67,    67,    68,    68,    69,    70,    70,    71,    71,
      71,    71,    72,    72,    72,    73,    74,    74,    74,    75
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     3,     1,
       3,     1,     1,     2,     4,     3,     1,     1,     2,     1,
       6,     3,     1,     1,     3,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     5,     7,     4,     3,     4,
       4,     4,     1,     1,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     4,     3,     1,     1,     0
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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* programa: lista_declaracoes  */
#line 36 "test.y"
                      {
        (yyval.node) = node_create("programa");
        node_add_child((yyval.node), (yyvsp[0].node));
        syntax_tree = (yyval.node);
    }
#line 1258 "test.tab.c"
    break;

  case 3: /* lista_declaracoes: lista_declaracoes declaracao  */
#line 44 "test.y"
                                 {
        (yyval.node) = node_create("lista_declaracoes");
        node_add_children((yyval.node), 2, (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1267 "test.tab.c"
    break;

  case 4: /* lista_declaracoes: declaracao  */
#line 48 "test.y"
                 {
        (yyval.node) = node_create("lista_declaracoes");
        node_add_child((yyval.node), (yyvsp[0].node));
    }
#line 1276 "test.tab.c"
    break;

  case 5: /* declaracao: declaracao_funcao  */
#line 55 "test.y"
                      {
        (yyval.node) = node_create("declaracao");
        node_add_child((yyval.node), (yyvsp[0].node));
    }
#line 1285 "test.tab.c"
    break;

  case 6: /* declaracao: declaracao_variaveis  */
#line 59 "test.y"
                           {
        (yyval.node) = node_create("declaracao");
        node_add_child((yyval.node), (yyvsp[0].node));
    }
#line 1294 "test.tab.c"
    break;

  case 7: /* declaracao: inicializacao_variaveis  */
#line 63 "test.y"
                              {
        (yyval.node) = node_create("declaracao");
        node_add_child((yyval.node), (yyvsp[0].node));
    }
#line 1303 "test.tab.c"
    break;

  case 8: /* declaracao_variaveis: tipo DOIS_PONTOS lista_variaveis  */
#line 70 "test.y"
                                     {
        (yyval.node) = node_create("declaracao_variaveis");
        node_add_children((yyval.node), 3, (yyvsp[-2].node), node_create_leaf("DOIS_PONTOS", ":"), (yyvsp[0].node));
    }
#line 1312 "test.tab.c"
    break;

  case 9: /* inicializacao_variaveis: atribuicao  */
#line 77 "test.y"
               {
        (yyval.node) = node_create("inicializacao_variaveis");
        node_add_child((yyval.node), (yyvsp[0].node));
    }
#line 1321 "test.tab.c"
    break;

  case 10: /* lista_variaveis: lista_variaveis VIRGULA var  */
#line 84 "test.y"
                                {
        (yyval.node) = node_create("lista_variaveis");
        node_add_children((yyval.node), 3, (yyvsp[-2].node), node_create_leaf("VIRGULA", ","), (yyvsp[0].node));
    }
#line 1330 "test.tab.c"
    break;

  case 11: /* lista_variaveis: var  */
#line 88 "test.y"
          {
        (yyval.node) = node_create("lista_variaveis");
        node_add_child((yyval.node), (yyvsp[0].node));
    }
#line 1339 "test.tab.c"
    break;

  case 12: /* var: ID  */
#line 95 "test.y"
       {
        (yyval.node) = node_create("var");
        node_add_child((yyval.node), node_create_leaf("ID", (yyvsp[0].value)));
    }
#line 1348 "test.tab.c"
    break;

  case 13: /* var: ID indice  */
#line 99 "test.y"
                {
        (yyval.node) = node_create("var");
        node_add_children((yyval.node), 2, node_create_leaf("ID", (yyvsp[-1].value)), (yyvsp[0].node));
    }
#line 1357 "test.tab.c"
    break;

  case 14: /* indice: indice ABRE_COLCHETE expressao FECHA_COLCHETE  */
#line 106 "test.y"
                                                  {
        (yyval.node) = node_create("indice");
        node_add_children((yyval.node), 4, 
            (yyvsp[-3].node), node_create_leaf("ABRE_COLCHETE", "["),
            (yyvsp[-1].node), node_create_leaf("FECHA_COLCHETE", "]")
        );
    }
#line 1369 "test.tab.c"
    break;

  case 15: /* indice: ABRE_COLCHETE expressao FECHA_COLCHETE  */
#line 113 "test.y"
                                             {
        (yyval.node) = node_create("indice");
        node_add_children((yyval.node), 
            3, node_create_leaf("ABRE_COLCHETE", "["), 
            (yyvsp[-1].node), node_create_leaf("FECHA_COLCHETE", "]")
        );
    }
#line 1381 "test.tab.c"
    break;

  case 16: /* tipo: INTEIRO  */
#line 123 "test.y"
            {
        (yyval.node) = node_create("tipo");
        node_add_child((yyval.node), node_create_leaf("INTEIRO", "inteiro"));
    }
#line 1390 "test.tab.c"
    break;

  case 17: /* tipo: FLUTUANTE  */
#line 127 "test.y"
                {
        (yyval.node) = node_create("tipo");
        node_add_child((yyval.node), node_create_leaf("FLUTUANTE", "flutuante"));
    }
#line 1399 "test.tab.c"
    break;

  case 18: /* declaracao_funcao: tipo cabecalho  */
#line 134 "test.y"
                   {
        (yyval.node) = node_create("declaracao_funcao");
        node_add_children((yyval.node), 2, (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1408 "test.tab.c"
    break;

  case 19: /* declaracao_funcao: cabecalho  */
#line 138 "test.y"
                {
        (yyval.node) = node_create("declaracao_funcao");
        node_add_child((yyval.node), (yyvsp[0].node));
    }
#line 1417 "test.tab.c"
    break;

  case 20: /* cabecalho: ID ABRE_PARENTESE lista_parametros FECHA_PARENTESE corpo FIM  */
#line 145 "test.y"
                                                                 {
        (yyval.node) = node_create("cabecalho");
        node_add_children((yyval.node), 6,
            node_create_leaf("ID", (yyvsp[-5].value)),
            node_create_leaf("ABRE_PARENTESE", "("),
            (yyvsp[-3].node),
            node_create_leaf("FECHA_PARENTESE", ")"),
            (yyvsp[-1].node),
            node_create_leaf("FIM", "fim")
        );
    }
#line 1433 "test.tab.c"
    break;

  case 21: /* lista_parametros: lista_parametros VIRGULA parametro  */
#line 159 "test.y"
                                       {
        (yyval.node) = node_create("lista_parametros");
        node_add_children((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1442 "test.tab.c"
    break;

  case 22: /* lista_parametros: parametro  */
#line 163 "test.y"
                {
        (yyval.node) = node_create("lista_parametros");
        node_add_child((yyval.node), (yyvsp[0].node));
    }
#line 1451 "test.tab.c"
    break;

  case 23: /* lista_parametros: vazio  */
#line 167 "test.y"
            {
        (yyval.node) = node_create("lista_parametros");
        node_add_child((yyval.node), (yyvsp[0].node));
    }
#line 1460 "test.tab.c"
    break;

  case 24: /* parametro: tipo DOIS_PONTOS ID  */
#line 174 "test.y"
                        {
        (yyval.node) = node_create("parametro");
        node_add_children((yyval.node), 3,
            (yyvsp[-2].node),
            node_create_leaf("DOIS_PONTOS", ":"),
            node_create_leaf("ID", (yyvsp[0].value))
        );
    }
#line 1473 "test.tab.c"
    break;

  case 25: /* parametro: parametro ABRE_COLCHETE FECHA_COLCHETE  */
#line 182 "test.y"
                                             {
        (yyval.node) = node_create("parametro");
        node_add_children((yyval.node), 3,
            (yyvsp[-2].node),
            node_create_leaf("ABRE_COLCHETE", "["),
            node_create_leaf("FECHA_COLCHETE", "]")
        );
    }
#line 1486 "test.tab.c"
    break;

  case 26: /* corpo: corpo acao  */
#line 193 "test.y"
               {
        (yyval.node) = node_create("corpo");
        node_add_children((yyval.node), 2, (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1495 "test.tab.c"
    break;

  case 27: /* corpo: vazio  */
#line 197 "test.y"
            {
        (yyval.node) = node_create("corpo");
        node_add_child((yyval.node), (yyvsp[0].node));
    }
#line 1504 "test.tab.c"
    break;

  case 28: /* acao: expressao  */
#line 204 "test.y"
              {
        (yyval.node) = node_create("acao");
        node_add_child((yyval.node), (yyvsp[0].node));
    }
#line 1513 "test.tab.c"
    break;

  case 29: /* acao: declaracao_variaveis  */
#line 208 "test.y"
                           {
        (yyval.node) = node_create("acao");
        node_add_child((yyval.node), (yyvsp[0].node));
    }
#line 1522 "test.tab.c"
    break;

  case 30: /* acao: se  */
#line 212 "test.y"
         {
        (yyval.node) = node_create("acao");
        node_add_child((yyval.node), (yyvsp[0].node));
    }
#line 1531 "test.tab.c"
    break;

  case 31: /* acao: repita  */
#line 216 "test.y"
             {
        (yyval.node) = node_create("acao");
        node_add_child((yyval.node), (yyvsp[0].node));
    }
#line 1540 "test.tab.c"
    break;

  case 32: /* acao: leia  */
#line 220 "test.y"
           {
        (yyval.node) = node_create("acao");
        node_add_child((yyval.node), (yyvsp[0].node));
    }
#line 1549 "test.tab.c"
    break;

  case 33: /* acao: escreva  */
#line 224 "test.y"
              {
        (yyval.node) = node_create("acao");
        node_add_child((yyval.node), (yyvsp[0].node));
    }
#line 1558 "test.tab.c"
    break;

  case 34: /* acao: retorna  */
#line 228 "test.y"
              {
        (yyval.node) = node_create("acao");
        node_add_child((yyval.node), (yyvsp[0].node));
    }
#line 1567 "test.tab.c"
    break;

  case 35: /* se: SE expressao ENTAO corpo FIM  */
#line 235 "test.y"
                                {
        (yyval.node) = node_create("se");
        node_add_children((yyval.node), 5,
            node_create_leaf("SE", "se"), (yyvsp[-3].node),
            node_create_leaf("ENTAO", "entao"), (yyvsp[-1].node),
            node_create_leaf("FIM", "fim")
        );
    }
#line 1580 "test.tab.c"
    break;

  case 36: /* se: SE expressao ENTAO corpo SENAO corpo FIM  */
#line 243 "test.y"
                                               {
        (yyval.node) = node_create("se");
        node_add_children((yyval.node), 7,
            node_create_leaf("SE", "se"), (yyvsp[-5].node),
            node_create_leaf("ENTAO", "entao"),(yyvsp[-3].node),
            node_create_leaf("SENAO", "senao"), (yyvsp[-1].node),
            node_create_leaf("FIM", "fim")
        );
    }
#line 1594 "test.tab.c"
    break;

  case 37: /* repita: REPITA corpo ATE expressao  */
#line 255 "test.y"
                               {
        (yyval.node) = node_create("repita");
        node_add_children((yyval.node), 4,
            node_create_leaf("REPITA", "repita"), (yyvsp[-2].node),
            node_create_leaf("ATE", "ate"), (yyvsp[0].node)
        );
    }
#line 1606 "test.tab.c"
    break;

  case 38: /* atribuicao: var ATRIBUICAO expressao  */
#line 265 "test.y"
                             {
        (yyval.node) = node_create("atribuicao");
        node_add_children((yyval.node), 3, (yyvsp[-2].node), node_create_leaf("ATRIBUICAO", ":="), (yyvsp[0].node));
    }
#line 1615 "test.tab.c"
    break;

  case 39: /* leia: LEIA ABRE_PARENTESE var FECHA_PARENTESE  */
#line 272 "test.y"
                                            {
        (yyval.node) = node_create("leia");
        node_add_children((yyval.node), 4,
            node_create_leaf("LEIA", "leia"),
            node_create_leaf("ABRE_PARENTESE", "("), (yyvsp[-1].node),
            node_create_leaf("FECHA_PARENTESE", ")")
        );
    }
#line 1628 "test.tab.c"
    break;

  case 40: /* escreva: ESCREVA ABRE_PARENTESE expressao FECHA_PARENTESE  */
#line 283 "test.y"
                                                     {
        (yyval.node) = node_create("escreva");
        node_add_children((yyval.node), 4,
            node_create_leaf("ESCREVA", "escreva"),
            node_create_leaf("ABRE_PARENTESE", "("), (yyvsp[-1].node),
            node_create_leaf("FECHA_PARENTESE", ")")
        );
    }
#line 1641 "test.tab.c"
    break;

  case 41: /* retorna: RETORNA ABRE_PARENTESE expressao FECHA_PARENTESE  */
#line 294 "test.y"
                                                     {
        (yyval.node) = node_create("retorna");
        node_add_children((yyval.node), 4,
            node_create_leaf("RETORNA", "retorna"),
            node_create_leaf("ABRE_PARENTESE", "("), (yyvsp[-1].node),
            node_create_leaf("FECHA_PARENTESE", ")")
        );
    }
#line 1654 "test.tab.c"
    break;

  case 42: /* expressao: expressao_logica  */
#line 305 "test.y"
                    {
        (yyval.node) = node_create("expressao");
        node_add_child((yyval.node), (yyvsp[0].node));
    }
#line 1663 "test.tab.c"
    break;

  case 43: /* expressao: atribuicao  */
#line 309 "test.y"
                 {
        (yyval.node) = node_create("expressao");
        node_add_child((yyval.node), (yyvsp[0].node));
    }
#line 1672 "test.tab.c"
    break;

  case 44: /* expressao_logica: expressao_simples  */
#line 316 "test.y"
                      {
        (yyval.node) = node_create("expressao_logica");
        node_add_child((yyval.node), (yyvsp[0].node));
    }
#line 1681 "test.tab.c"
    break;

  case 45: /* expressao_logica: expressao_logica operador_logico expressao_simples  */
#line 320 "test.y"
                                                         {
        (yyval.node) = node_create("expressao_logica");
        node_add_children((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));    
    }
#line 1690 "test.tab.c"
    break;

  case 46: /* expressao_simples: expressao_aditiva  */
#line 327 "test.y"
                      {
        (yyval.node) = node_create("expressao_simples");
        node_add_child((yyval.node), (yyvsp[0].node));
    }
#line 1699 "test.tab.c"
    break;

  case 47: /* expressao_simples: expressao_simples operador_relacional expressao_aditiva  */
#line 331 "test.y"
                                                              {
        (yyval.node) = node_create("expressao_simples");
        node_add_children((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1708 "test.tab.c"
    break;

  case 48: /* expressao_aditiva: expressao_multiplicativa  */
#line 338 "test.y"
                             {
        (yyval.node) = node_create("expressao_aditiva");
        node_add_child((yyval.node), (yyvsp[0].node));
    }
#line 1717 "test.tab.c"
    break;

  case 49: /* expressao_aditiva: expressao_aditiva operador_soma expressao_multiplicativa  */
#line 342 "test.y"
                                                               {
        (yyval.node) = node_create("expressao_aditiva");
        node_add_children((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1726 "test.tab.c"
    break;

  case 50: /* expressao_multiplicativa: expressao_unaria  */
#line 349 "test.y"
                     {
        (yyval.node) = node_create("expressao_multiplicativa");
        node_add_child((yyval.node), (yyvsp[0].node));
    }
#line 1735 "test.tab.c"
    break;

  case 51: /* expressao_multiplicativa: expressao_multiplicativa operador_multiplicacao expressao_unaria  */
#line 353 "test.y"
                                                                       {
        (yyval.node) = node_create("expressao_multiplicativa");
        node_add_children((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1744 "test.tab.c"
    break;

  case 52: /* expressao_unaria: fator  */
#line 360 "test.y"
          {
        (yyval.node) = node_create("expressao_unaria");
        node_add_child((yyval.node), (yyvsp[0].node));
    }
#line 1753 "test.tab.c"
    break;

  case 53: /* expressao_unaria: operador_soma fator  */
#line 364 "test.y"
                          {
        (yyval.node) = node_create("expressao_unaria");
        node_add_children((yyval.node), 2, (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1762 "test.tab.c"
    break;

  case 54: /* expressao_unaria: operador_negacao fator  */
#line 368 "test.y"
                             {
        (yyval.node) = node_create("expressao_unaria");
        node_add_children((yyval.node), 2, (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1771 "test.tab.c"
    break;

  case 55: /* operador_relacional: MENOR  */
#line 375 "test.y"
          { (yyval.node) = node_create_leaf("MENOR", "<"); }
#line 1777 "test.tab.c"
    break;

  case 56: /* operador_relacional: MAIOR  */
#line 376 "test.y"
            { (yyval.node) = node_create_leaf("MAIOR", ">"); }
#line 1783 "test.tab.c"
    break;

  case 57: /* operador_relacional: IGUAL  */
#line 377 "test.y"
            { (yyval.node) = node_create_leaf("IGUAL", "="); }
#line 1789 "test.tab.c"
    break;

  case 58: /* operador_relacional: DIFERENTE  */
#line 378 "test.y"
                { (yyval.node) = node_create_leaf("DIFERENTE", "<>"); }
#line 1795 "test.tab.c"
    break;

  case 59: /* operador_relacional: MENOR_IGUAL  */
#line 379 "test.y"
                  { (yyval.node) = node_create_leaf("MENOR_IGUAL", "<="); }
#line 1801 "test.tab.c"
    break;

  case 60: /* operador_relacional: MAIOR_IGUAL  */
#line 380 "test.y"
                  { (yyval.node) = node_create_leaf("MAIOR_IGUAL", ">="); }
#line 1807 "test.tab.c"
    break;

  case 61: /* operador_soma: MAIS  */
#line 384 "test.y"
         { (yyval.node) = node_create_leaf("MAIS", "+"); }
#line 1813 "test.tab.c"
    break;

  case 62: /* operador_soma: MENOS  */
#line 385 "test.y"
            { (yyval.node) = node_create_leaf("MENOS", "-"); }
#line 1819 "test.tab.c"
    break;

  case 63: /* operador_logico: E  */
#line 389 "test.y"
      { (yyval.node) = node_create_leaf("E", "&&"); }
#line 1825 "test.tab.c"
    break;

  case 64: /* operador_logico: OU  */
#line 390 "test.y"
         { (yyval.node) = node_create_leaf("OU", "||"); }
#line 1831 "test.tab.c"
    break;

  case 65: /* operador_negacao: NAO  */
#line 394 "test.y"
        { (yyval.node) = node_create_leaf("NAO", "!"); }
#line 1837 "test.tab.c"
    break;

  case 66: /* operador_multiplicacao: VEZES  */
#line 398 "test.y"
          { (yyval.node) = node_create_leaf("VEZES", "*"); }
#line 1843 "test.tab.c"
    break;

  case 67: /* operador_multiplicacao: DIVIDE  */
#line 399 "test.y"
             { (yyval.node) = node_create_leaf("DIVIDE", "/"); }
#line 1849 "test.tab.c"
    break;

  case 68: /* fator: ABRE_PARENTESE expressao FECHA_PARENTESE  */
#line 403 "test.y"
                                             {
        (yyval.node) = node_create("fator");
        node_add_children((yyval.node), 3,
            node_create_leaf("ABRE_PARENTESE", "("), (yyvsp[-1].node),
            node_create_leaf("FECHA_PARENTESE", ")")
        );
    }
#line 1861 "test.tab.c"
    break;

  case 69: /* fator: var  */
#line 410 "test.y"
          {
        (yyval.node) = node_create("fator");
        node_add_child((yyval.node), (yyvsp[0].node));
    }
#line 1870 "test.tab.c"
    break;

  case 70: /* fator: chamada_funcao  */
#line 414 "test.y"
                     {
        (yyval.node) = node_create("fator");
        node_add_child((yyval.node), (yyvsp[0].node));
    }
#line 1879 "test.tab.c"
    break;

  case 71: /* fator: numero  */
#line 418 "test.y"
             {
        (yyval.node) = node_create("fator");
        node_add_child((yyval.node), (yyvsp[0].node));
    }
#line 1888 "test.tab.c"
    break;

  case 72: /* numero: NUM_INTEIRO  */
#line 425 "test.y"
                {
        (yyval.node) = node_create("numero");
        node_add_child((yyval.node), node_create_leaf("NUM_INTEIRO", (yyvsp[0].value)));
    }
#line 1897 "test.tab.c"
    break;

  case 73: /* numero: NUM_PONTO_FLUTUANTE  */
#line 429 "test.y"
                          {
        (yyval.node) = node_create("numero");
        node_add_child((yyval.node), node_create_leaf("NUM_PONTO_FLUTUANTE", (yyvsp[0].value)));
    }
#line 1906 "test.tab.c"
    break;

  case 74: /* numero: NUM_NOTACAO_CIENTIFICA  */
#line 433 "test.y"
                             {
        (yyval.node) = node_create("numero");
        node_add_child((yyval.node), node_create_leaf("NUM_NOTACAO_CIENTIFICA", (yyvsp[0].value)));
    }
#line 1915 "test.tab.c"
    break;

  case 75: /* chamada_funcao: ID ABRE_PARENTESE lista_argumentos FECHA_PARENTESE  */
#line 440 "test.y"
                                                       {
        (yyval.node) = node_create("chamada_funcao");
        node_add_children((yyval.node), 4,
            node_create_leaf("ID", (yyvsp[-3].value)),
            node_create_leaf("ABRE_PARENTESE", "("),
            (yyvsp[-1].node),
            node_create_leaf("FECHA_PARENTESE", ")")
        );
    }
#line 1929 "test.tab.c"
    break;

  case 76: /* lista_argumentos: lista_argumentos VIRGULA expressao  */
#line 452 "test.y"
                                       {
        (yyval.node) = node_create("lista_argumentos");
        node_add_children((yyval.node), 3, (yyvsp[-2].node), node_create_leaf("VIRGULA", ","), (yyvsp[0].node));
    }
#line 1938 "test.tab.c"
    break;

  case 77: /* lista_argumentos: expressao  */
#line 456 "test.y"
                {
        (yyval.node) = node_create("lista_argumentos");
        node_add_child((yyval.node), (yyvsp[0].node));
    }
#line 1947 "test.tab.c"
    break;

  case 78: /* lista_argumentos: vazio  */
#line 460 "test.y"
            {
        (yyval.node) = node_create("lista_argumentos");
        node_add_child((yyval.node), (yyvsp[0].node));
    }
#line 1956 "test.tab.c"
    break;

  case 79: /* vazio: %empty  */
#line 467 "test.y"
    { (yyval.node) = node_create("vazio"); }
#line 1962 "test.tab.c"
    break;


#line 1966 "test.tab.c"

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
      yyerror (YY_("syntax error"));
    }

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
                      yytoken, &yylval);
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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 470 "test.y"


int yyerror(char* s){
    printf("Syntax error on line %s\n", s);
    return 0;
}

/*
bool stringHasPoint(const char* str){
    if(strstr(str, ".") == NULL) return false;
    return true;
}

bool hasTppExtension(const char* str){
    char buffer[256];  
    strncpy(buffer, str, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';

    char *token = strtok(buffer, ".");
    char *last_token = NULL;

    while (token != NULL) {
        last_token = token;
        token = strtok(NULL, ".");
    }

    return (last_token != NULL && strcmp(last_token, "tpp") == 0);
}

bool stringIsK(const char* str){
    return !strcmp(str, "-k");
}


int handleArguments(int argc, char* argv[]) {
    int fileIdx = -1;
    bool check_tpp = false;
    for(int i = 1; i < argc; i++) {
        char* arg = argv[i];

        if(stringIsK(arg)){
            check_key = true;
            continue;
        }

        if(stringHasPoint(arg)){
            fileIdx = i;
        }
    }

    if(fileIdx == -1) yyfatal_error(Error::ERR_LEX_USE);
    if(!hasTppExtension(argv[fileIdx])) yyfatal_error(Error::ERR_LEX_NOT_TPP);
    
    return fileIdx;
}

void adjustConsole() {
    #ifdef WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif
}

void redirectStdin(const char* fileName) {
    std::ifstream file(fileName);
    if(!file.good()) yyfatal_error(Error::ERR_LEX_FILE_NOT_EXISTS); 
    freopen(fileName, "r", stdin);
}
*/
