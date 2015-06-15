/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 6 "compilador.y" /* yacc.c:339  */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "compilador.h"
#include "tab_simb.h"
#include "pilha.h"
#include "pilha_tipos.h"
#include "trataerro.h"





int numVars, nivel_lexico, deslocamento, totalVars, indice_param, cont_rotulo, teste = 0;

char *rotulo_mepa, *rotulo_mepa_aux;
char buffer[256]; //Usada no gera_código

Simbolo *simb, *simb_aux, *proc_atual;
Tab_simb *tab_s;
PilhaT pilha_tipos, pilha_amem_dmem, pilha_rotulos, pilha_simbolos;
bool chamada_de_proc;
Tipo aux_tipo;

#define geraCodigoCRxx(instrucao, simbolo) \
  sprintf(buffer, "%s %d, %d", instrucao, simbolo->nivel_lexico, simbolo->deslocamento); \
  geraCodigo(NULL, buffer );

#define geraCodigoCV(simbolo) \
  if (chamada_de_proc) { teste++;\
    if (proc_atual != NULL) { \
      if ((proc_atual->lista_param[indice_param].passagem == REF) && (simbolo->passagem == VALOR)) { geraCodigoCRxx("CREN", simbolo); } \
      else { geraCodigoCRxx("CRVL", simbolo); } }\
    else { geraCodigoCRxx("CRVL", simbolo); } } \
  else if (simbolo->passagem == VALOR) { \
  	sprintf(buffer, "CRVL %d, %d", simbolo->nivel_lexico, simbolo->deslocamento); \
  	geraCodigo(NULL, buffer); } \
    else { geraCodigoCRxx("CRVI", simbolo); }

#line 109 "compilador.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "compilador.tab.h".  */
#ifndef YY_YY_COMPILADOR_TAB_H_INCLUDED
# define YY_YY_COMPILADOR_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    PROGRAM = 258,
    ABRE_PARENTESES = 259,
    FECHA_PARENTESES = 260,
    VIRGULA = 261,
    PONTO_E_VIRGULA = 262,
    DOIS_PONTOS = 263,
    PONTO = 264,
    T_BEGIN = 265,
    T_END = 266,
    VAR = 267,
    IDENT = 268,
    ATRIBUICAO = 269,
    MAIS = 270,
    MENOS = 271,
    MULT = 272,
    ABRE_COLCHETES = 273,
    FECHA_COLCHETES = 274,
    LABEL = 275,
    TYPE = 276,
    ARRAY = 277,
    OF = 278,
    GOTO = 279,
    IF = 280,
    THEN = 281,
    ELSE = 282,
    WHILE = 283,
    DO = 284,
    OR = 285,
    DIV = 286,
    AND = 287,
    NOT = 288,
    IGUAL = 289,
    DIF = 290,
    MENOR_IGUAL = 291,
    MAIOR_IGUAL = 292,
    MENOR = 293,
    MAIOR = 294,
    INTEGER = 295,
    BOOLEAN = 296,
    TRUE = 297,
    FALSE = 298,
    NUMERO = 299,
    READ = 300,
    WRITE = 301,
    PROCEDURE = 302,
    FUNCTION = 303,
    LOWER_THAN_ELSE = 304
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_COMPILADOR_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 210 "compilador.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
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
#define YYLAST   169

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  61
/* YYNRULES -- Number of rules.  */
#define YYNRULES  106
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  183

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   304

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    68,    68,    73,    68,    88,    92,    88,    96,    97,
      99,   100,   105,   108,   108,   110,   113,   113,   114,   114,
     118,   117,   128,   129,   132,   136,   142,   143,   148,   148,
     157,   157,   168,   171,   174,   175,   171,   188,   187,   191,
     195,   194,   196,   196,   197,   200,   202,   205,   207,   214,
     216,   217,   220,   221,   224,   225,   226,   231,   232,   233,
     234,   235,   240,   244,   249,   253,   261,   262,   262,   269,
     271,   269,   277,   279,   277,   292,   292,   298,   301,   306,
     306,   308,   309,   312,   312,   313,   317,   318,   319,   320,
     321,   322,   323,   325,   326,   327,   328,   332,   333,   334,
     335,   338,   339,   340,   344,   345,   349
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PROGRAM", "ABRE_PARENTESES",
  "FECHA_PARENTESES", "VIRGULA", "PONTO_E_VIRGULA", "DOIS_PONTOS", "PONTO",
  "T_BEGIN", "T_END", "VAR", "IDENT", "ATRIBUICAO", "MAIS", "MENOS",
  "MULT", "ABRE_COLCHETES", "FECHA_COLCHETES", "LABEL", "TYPE", "ARRAY",
  "OF", "GOTO", "IF", "THEN", "ELSE", "WHILE", "DO", "OR", "DIV", "AND",
  "NOT", "IGUAL", "DIF", "MENOR_IGUAL", "MAIOR_IGUAL", "MENOR", "MAIOR",
  "INTEGER", "BOOLEAN", "TRUE", "FALSE", "NUMERO", "READ", "WRITE",
  "PROCEDURE", "FUNCTION", "LOWER_THAN_ELSE", "$accept", "programa", "$@1",
  "$@2", "bloco", "$@3", "$@4", "rotulos", "lista_nums",
  "parte_declara_vars", "var", "$@5", "declara_vars", "$@6", "$@7",
  "declara_var", "$@8", "tipo", "lista_id_var", "lista_idents",
  "procs_funcs", "$@9", "$@10", "bloco_proc_func", "$@11", "$@12", "$@13",
  "params_proc_func", "$@14", "lista_dec_param", "$@15", "$@16",
  "parametros_dec", "lista_id_par", "comando_composto", "comandos_",
  "comandos", "comando", "comando_sem_rotulo", "lista_param_leit",
  "lista_param_impr", "comando_condicional", "$@17", "if_simples", "$@18",
  "$@19", "comando_repetitivo", "$@20", "$@21", "atrib_proc", "$@22",
  "exec_ou_atrib", "exec_proc", "$@23", "lista_de_parametros", "$@24",
  "expressao", "expressao_simples", "termo", "fator", "ident_ou_func", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304
};
# endif

#define YYPACT_NINF -145

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-145)))

#define YYTABLE_NINF -45

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -145,     8,    24,  -145,     3,  -145,    29,    58,  -145,    35,
      80,    66,    16,  -145,    53,    89,    87,    94,    96,  -145,
    -145,  -145,  -145,    53,  -145,  -145,    13,  -145,    91,    92,
      93,    95,  -145,    92,  -145,  -145,     4,  -145,  -145,    97,
    -145,    98,    33,   105,   105,     1,  -145,  -145,  -145,  -145,
    -145,    65,   103,   104,  -145,  -145,  -145,   106,   109,   111,
    -145,   107,   110,  -145,  -145,  -145,    74,  -145,  -145,   112,
     113,    77,    16,    33,    11,     0,     0,     6,   108,   114,
    -145,     1,  -145,  -145,  -145,   117,   115,  -145,  -145,    22,
    -145,    87,  -145,   116,   119,     0,  -145,  -145,     0,  -145,
    -145,  -145,  -145,    47,    -8,  -145,  -145,  -145,  -145,  -145,
      86,  -145,    88,  -145,     1,    77,  -145,    72,   118,    33,
    -145,    16,  -145,     0,  -145,     2,    99,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   100,
    -145,   120,  -145,   121,  -145,  -145,    33,  -145,  -145,    13,
    -145,    90,  -145,  -145,     1,    -8,    -8,    -8,    23,    23,
      23,    23,    23,    23,  -145,  -145,  -145,     1,  -145,  -145,
    -145,  -145,  -145,  -145,  -145,  -145,    97,     0,   123,  -145,
    -145,    13,  -145
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     0,     3,     0,     0,    27,     0,
       0,     0,     9,    26,     0,     0,    15,    11,     0,     4,
      13,     5,    12,     0,     8,    18,    32,    10,    14,     0,
       0,     0,     6,     0,    25,    19,     0,    28,    30,     0,
      17,     0,     0,    39,    39,    51,     7,    24,    22,    23,
      20,    42,     0,     0,    75,    69,    72,     0,     0,     0,
      55,     0,    50,    53,    56,    58,    66,    59,    57,     0,
      37,     0,     9,     0,    82,     0,     0,     0,     0,     0,
      49,     0,    67,    21,    40,     0,     0,   106,    43,     0,
      48,    15,    29,     0,    79,     0,    76,    78,     0,   104,
     105,   103,    70,    92,    96,   100,   101,    73,    54,    63,
       0,    65,     0,    52,     0,     0,    38,     0,     0,     0,
      33,     9,    81,     0,    77,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      60,     0,    61,     0,    68,    41,     0,    47,    46,    32,
      31,     0,    85,   102,     0,    93,    94,    95,    90,    91,
      89,    88,    87,    86,    97,    98,    99,     0,    62,    64,
      45,    34,    80,    83,    71,    74,     0,     0,     0,    84,
      35,    32,    36
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -145,  -145,  -145,  -145,  -145,  -145,  -145,   124,   122,    25,
    -145,  -145,  -145,  -145,  -145,   102,  -145,   -70,  -145,  -145,
    -144,  -145,  -145,     5,  -145,  -145,  -145,   125,  -145,  -145,
    -145,  -145,    17,    52,   -39,  -145,  -145,   -79,    62,  -145,
    -145,  -145,  -145,  -145,  -145,  -145,  -145,  -145,  -145,  -145,
    -145,  -145,  -145,  -145,  -145,  -145,   -75,   -76,   -63,   -69,
     -65
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     6,    15,    26,    39,    91,    18,    21,
      22,    25,    28,    33,    29,    35,    69,    50,    36,     9,
      32,    43,    44,    92,   149,   176,   181,    52,    85,    70,
     115,    71,    88,    89,    60,    61,    62,    63,    64,   110,
     112,    65,   114,    66,    75,   126,    67,    76,   139,    68,
      74,    96,    97,   123,   151,   177,   102,   103,   104,   105,
     106
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      46,   107,   113,    93,    98,   171,    90,   153,     3,   136,
      41,    45,    42,    87,    54,    94,     5,   127,   128,    54,
     124,    90,   125,   137,   138,    95,    55,     4,   118,    56,
     119,    55,   129,     7,    56,   144,    14,   182,   127,   128,
      10,    11,    99,   100,   101,    57,    58,    59,   152,   148,
      90,    58,    59,   129,   158,   159,   160,   161,   162,   163,
      30,    31,   127,   128,   155,   156,   157,   164,   165,   166,
     -44,     8,   -44,    48,    49,   174,   170,   129,   118,    13,
     146,   130,   131,   132,   133,   134,   135,    12,   175,    86,
      87,   140,   141,   142,   143,   172,   173,    17,    19,    20,
      23,    82,   179,    24,   -16,    34,    37,    45,    38,    51,
      72,    47,    73,    78,    77,    79,   120,    81,    80,    83,
      84,   109,   116,   121,   122,   154,   150,   111,    87,   167,
     180,   147,   145,   168,   169,    40,    16,   178,   117,   108,
       0,     0,     0,     0,     0,    27,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    53
};

static const yytype_int16 yycheck[] =
{
      39,    76,    81,    73,     4,   149,    71,     5,     0,    17,
       6,    10,     8,    13,    13,     4,    13,    15,    16,    13,
      95,    86,    98,    31,    32,    14,    25,     3,     6,    28,
       8,    25,    30,     4,    28,   114,    20,   181,    15,    16,
       5,     6,    42,    43,    44,    44,    45,    46,   123,   119,
     115,    45,    46,    30,   130,   131,   132,   133,   134,   135,
      47,    48,    15,    16,   127,   128,   129,   136,   137,   138,
       5,    13,     7,    40,    41,   154,   146,    30,     6,    13,
       8,    34,    35,    36,    37,    38,    39,     7,   167,    12,
      13,     5,     6,     5,     6,     5,     6,    44,     9,    12,
       6,    27,   177,     7,    13,    13,    13,    10,    13,     4,
       7,    13,     8,     4,     8,     4,    91,     7,    11,     7,
       7,    13,     5,     7,     5,    26,   121,    13,    13,    29,
       7,    13,   115,    13,    13,    33,    12,   176,    86,    77,
      -1,    -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    51,    52,     0,     3,    13,    53,     4,    13,    69,
       5,     6,     7,    13,    20,    54,    57,    44,    58,     9,
      12,    59,    60,     6,     7,    61,    55,    58,    62,    64,
      47,    48,    70,    63,    13,    65,    68,    13,    13,    56,
      65,     6,     8,    71,    72,    10,    84,    13,    40,    41,
      67,     4,    77,    77,    13,    25,    28,    44,    45,    46,
      84,    85,    86,    87,    88,    91,    93,    96,    99,    66,
      79,    81,     7,     8,   100,    94,    97,     8,     4,     4,
      11,     7,    27,     7,     7,    78,    12,    13,    82,    83,
     110,    57,    73,    67,     4,    14,   101,   102,     4,    42,
      43,    44,   106,   107,   108,   109,   110,   106,    88,    13,
      89,    13,    90,    87,    92,    80,     5,    83,     6,     8,
      59,     7,     5,   103,   106,   107,    95,    15,    16,    30,
      34,    35,    36,    37,    38,    39,    17,    31,    32,    98,
       5,     6,     5,     6,    87,    82,     8,    13,    67,    74,
      73,   104,   106,     5,    26,   108,   108,   108,   107,   107,
     107,   107,   107,   107,   109,   109,   109,    29,    13,    13,
      67,    70,     5,     6,    87,    87,    75,   105,    84,   106,
       7,    76,    70
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    50,    52,    53,    51,    55,    56,    54,    57,    57,
      58,    58,    59,    61,    60,    60,    63,    62,    64,    62,
      66,    65,    67,    67,    68,    68,    69,    69,    71,    70,
      72,    70,    70,    74,    75,    76,    73,    78,    77,    77,
      80,    79,    81,    79,    79,    82,    82,    83,    83,    84,
      85,    85,    86,    86,    87,    87,    87,    88,    88,    88,
      88,    88,    89,    89,    90,    90,    91,    92,    91,    94,
      95,    93,    97,    98,    96,   100,    99,   101,   101,   103,
     102,   102,   102,   105,   104,   104,   106,   106,   106,   106,
     106,   106,   106,   107,   107,   107,   107,   108,   108,   108,
     108,   109,   109,   109,   109,   109,   110
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,    10,     0,     0,     6,     3,     0,
       3,     1,     1,     0,     3,     0,     0,     3,     0,     2,
       0,     5,     1,     1,     3,     1,     3,     1,     0,     6,
       0,     8,     0,     0,     0,     0,     9,     0,     4,     0,
       0,     4,     0,     2,     0,     4,     3,     3,     1,     3,
       1,     0,     3,     1,     3,     1,     1,     1,     1,     1,
       4,     4,     3,     1,     3,     1,     1,     0,     4,     0,
       0,     6,     0,     0,     6,     0,     3,     2,     1,     0,
       4,     2,     0,     0,     4,     1,     3,     3,     3,     3,
       3,     3,     1,     3,     3,     3,     1,     3,     3,     3,
       1,     1,     3,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 68 "compilador.y" /* yacc.c:1646  */
    { 
             	geraCodigo (NULL, "INPP");
			 	nivel_lexico = deslocamento = 0;
			 	tab_s = iniciaTabelaSimbolo(tab_s);
             }
#line 1433 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 73 "compilador.y" /* yacc.c:1646  */
    { simb = insereSimbolo(tab_s, token, PROG, 0);}
#line 1439 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 76 "compilador.y" /* yacc.c:1646  */
    {	numVars = *(int *)desempilha(&pilha_amem_dmem);
    			if (numVars) {
					sprintf ( buffer, "DMEM %d", totalVars);
					geraCodigo(NULL, buffer);
				}
                geraCodigo (NULL, "PARA");
				//aux = imprimeTabSimbolos(tab_s);
             }
#line 1452 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 88 "compilador.y" /* yacc.c:1646  */
    { empilhaVars(deslocamento, &pilha_amem_dmem);
                                            geraRotulo(&rotulo_mepa, &cont_rotulo, &pilha_rotulos);
                                            sprintf(buffer, "DSVS %s", rotulo_mepa);
                                            geraCodigo(NULL, buffer); }
#line 1461 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 92 "compilador.y" /* yacc.c:1646  */
    { geraCodigo (desempilha(&pilha_rotulos), "NADA"); }
#line 1467 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 108 "compilador.y" /* yacc.c:1646  */
    { deslocamento=0; }
#line 1473 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 113 "compilador.y" /* yacc.c:1646  */
    { numVars=0; }
#line 1479 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 114 "compilador.y" /* yacc.c:1646  */
    { numVars=0; }
#line 1485 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 118 "compilador.y" /* yacc.c:1646  */
    {
			 	sprintf ( buffer, "AMEM %d", numVars);
				totalVars += numVars;
				inserePassagemParam(tab_s, VALOR, numVars);
				geraCodigo(NULL, buffer);
				
			 }
#line 1497 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 128 "compilador.y" /* yacc.c:1646  */
    { aux_tipo = insereTipo(tab_s, T_INT);}
#line 1503 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 129 "compilador.y" /* yacc.c:1646  */
    { aux_tipo = insereTipo(tab_s, T_BOOL);}
#line 1509 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 133 "compilador.y" /* yacc.c:1646  */
    { numVars++; 
			  simb = insereSimbolo(tab_s, token, VAR_S, nivel_lexico);
			  simb->deslocamento = deslocamento++; }
#line 1517 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 137 "compilador.y" /* yacc.c:1646  */
    { numVars++;
			  simb = insereSimbolo(tab_s, token, VAR_S, nivel_lexico);
			  simb->deslocamento = deslocamento++; }
#line 1525 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 148 "compilador.y" /* yacc.c:1646  */
    { geraRotulo(&rotulo_mepa, &cont_rotulo, &pilha_rotulos);
											  sprintf(buffer, "ENPR %d", ++nivel_lexico);
/*Gera o rotulo, empilha, faz ENPR*/		  geraCodigo(desempilha(&pilha_rotulos), buffer);
/*Desempilha, atribui o rot pro simb*/		  simb = insereSimbolo(tab_s, token, PROC, nivel_lexico);
											  simb->rotulo = rotulo_mepa;
											  empilha(&pilha_simbolos, simb);
											  simb->qtd_parametros = numVars = 0;
											}
#line 1538 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 157 "compilador.y" /* yacc.c:1646  */
    { geraRotulo(&rotulo_mepa, &cont_rotulo, &pilha_rotulos);
											  sprintf(buffer, "ENPR %d", ++nivel_lexico);
											  geraCodigo(desempilha(&pilha_rotulos), buffer);
											  simb = insereSimbolo(tab_s, token, FUNC, nivel_lexico);
											  simb->rotulo = rotulo_mepa;
											  empilha(&pilha_simbolos, simb);
											  simb->qtd_parametros = numVars = 0;
											}
#line 1551 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 171 "compilador.y" /* yacc.c:1646  */
    { empilhaVars(deslocamento); geraRotulo(&rotulo_mepa, &cont_rotulo, &pilha_rotulos);
                                                  sprintf(buffer, "DSVS %s", rotulo_mepa);
                                                  geraCodigo(NULL, buffer); }
#line 1559 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 174 "compilador.y" /* yacc.c:1646  */
    { geraCodigo(desempilha(&pilha_rotulos), "NADA"); }
#line 1565 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 175 "compilador.y" /* yacc.c:1646  */
    { numVars = *(int *)desempilha(&pilha_amem_dmem);
              									  if (numVars){
              									  	sprintf(buffer,"DMEM %d", numVars );
              									  	geraCodigo(NULL, buffer);
              									  }
              									  simb = desempilha(&pilha_simbolos); removeFPSimbolos(tab_s, simb);	
              									  sprintf(buffer, "RTPR %d, %d", nivel_lexico--, simb->qtd_parametros);
                                                  geraCodigo(NULL, buffer ); 
                                                }
#line 1579 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 188 "compilador.y" /* yacc.c:1646  */
    { setaDeslocamentoParam(tab_s, simb->qtd_parametros); 
              						  simb->end_retorno = -4 - simb->qtd_parametros; }
#line 1586 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 195 "compilador.y" /* yacc.c:1646  */
    { numVars=0; }
#line 1592 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 196 "compilador.y" /* yacc.c:1646  */
    { numVars=0; }
#line 1598 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 200 "compilador.y" /* yacc.c:1646  */
    { inserePassagemParam(tab_s, REF, numVars); 		//Define passagem de parametro na ts 
													insereParamLista(simb, aux_tipo, REF, numVars);}
#line 1605 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 202 "compilador.y" /* yacc.c:1646  */
    { inserePassagemParam(tab_s, VALOR, numVars); 
													insereParamLista(simb, aux_tipo, VALOR, numVars);}
#line 1612 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 205 "compilador.y" /* yacc.c:1646  */
    { simb->qtd_parametros++; numVars++; 
													simb_aux = insereSimbolo(tab_s, token, PF, nivel_lexico); simb_aux->pai = simb;}
#line 1619 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 207 "compilador.y" /* yacc.c:1646  */
    { simb->qtd_parametros++; numVars++; 
													simb_aux = insereSimbolo(tab_s, token, PF, nivel_lexico); simb_aux->pai = simb;}
#line 1626 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 240 "compilador.y" /* yacc.c:1646  */
    { geraCodigo (NULL, "LEIT"); simb = procuraSimbolo(tab_s, token, nivel_lexico); 
													geraCodigoARMZ(simb);

												  }
#line 1635 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 244 "compilador.y" /* yacc.c:1646  */
    { geraCodigo (NULL, "LEIT"); simb = procuraSimbolo(tab_s, token, nivel_lexico); 
													geraCodigoARMZ(simb);
    											   }
#line 1643 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 249 "compilador.y" /* yacc.c:1646  */
    { simb = procuraSimbolo(tab_s, token, nivel_lexico);
												   geraCodigoCV(simb);
												   geraCodigo (NULL, "IMPR");
        										 }
#line 1652 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 253 "compilador.y" /* yacc.c:1646  */
    { simb = procuraSimbolo(tab_s, token, nivel_lexico);
												   geraCodigoCV(simb);
												   geraCodigo (NULL, "IMPR");
        										 }
#line 1661 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 261 "compilador.y" /* yacc.c:1646  */
    { geraCodigo (desempilha(&pilha_rotulos), "NADA"); }
#line 1667 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 262 "compilador.y" /* yacc.c:1646  */
    { rotulo_mepa=desempilha(&pilha_rotulos);
                                sprintf(buffer, "DSVS %s", rotulo_mepa_aux);
                                geraCodigo(NULL, buffer);
                                geraCodigo(rotulo_mepa, "NADA"); }
#line 1676 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 266 "compilador.y" /* yacc.c:1646  */
    { geraCodigo(desempilha(&pilha_rotulos), "NADA"); }
#line 1682 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 269 "compilador.y" /* yacc.c:1646  */
    { geraRotulo(&rotulo_mepa_aux, &cont_rotulo, &pilha_rotulos);
                  			  geraRotulo(&rotulo_mepa, &cont_rotulo, &pilha_rotulos); }
#line 1689 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 271 "compilador.y" /* yacc.c:1646  */
    { sprintf(buffer, "DSVF %s", rotulo_mepa);
      								geraCodigo(NULL, buffer); }
#line 1696 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 277 "compilador.y" /* yacc.c:1646  */
    { geraRotulo(&rotulo_mepa, &cont_rotulo, &pilha_rotulos);
                            		  geraCodigo (rotulo_mepa, "NADA"); }
#line 1703 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 279 "compilador.y" /* yacc.c:1646  */
    { geraRotulo(&rotulo_mepa, &cont_rotulo, &pilha_rotulos);
              						  sprintf(buffer, "DSVF %s", rotulo_mepa);
                            		  geraCodigo(NULL, buffer); }
#line 1711 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 282 "compilador.y" /* yacc.c:1646  */
    { rotulo_mepa_aux=desempilha(&pilha_rotulos);
                            		  rotulo_mepa=desempilha(&pilha_rotulos);
                            		  sprintf(buffer, "DSVS %s", rotulo_mepa);
                            		  geraCodigo(NULL, buffer);
                            		  geraCodigo (rotulo_mepa_aux, "NADA"); }
#line 1721 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 292 "compilador.y" /* yacc.c:1646  */
    { simb_aux = procuraSimbolo(tab_s, token, nivel_lexico); 
							  empilhaTipo(&pilha_tipos, simb_aux->tipo); proc_atual=simb_aux; 
							}
#line 1729 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 298 "compilador.y" /* yacc.c:1646  */
    { comparaTipo(&pilha_tipos, ATRIB, T_INT);
												  geraCodigoARMZ(simb_aux);
												}
#line 1737 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 301 "compilador.y" /* yacc.c:1646  */
    { sprintf(buffer, "CHPR %s, %d", simb_aux->rotulo, nivel_lexico);
												  geraCodigo(NULL, buffer); }
#line 1744 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 306 "compilador.y" /* yacc.c:1646  */
    { chamada_de_proc = true; indice_param=0; }
#line 1750 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 307 "compilador.y" /* yacc.c:1646  */
    { chamada_de_proc = false; }
#line 1756 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 312 "compilador.y" /* yacc.c:1646  */
    { chamada_de_proc = true; ++indice_param; }
#line 1762 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 317 "compilador.y" /* yacc.c:1646  */
    { comparaTipo(&pilha_tipos, COMPAR, T_BOOL); geraCodigo(NULL, "CMMA"); }
#line 1768 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 318 "compilador.y" /* yacc.c:1646  */
    { comparaTipo(&pilha_tipos, COMPAR, T_BOOL); geraCodigo(NULL, "CMME"); }
#line 1774 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 319 "compilador.y" /* yacc.c:1646  */
    { comparaTipo(&pilha_tipos, COMPAR, T_BOOL); geraCodigo(NULL, "CMAG"); }
#line 1780 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 320 "compilador.y" /* yacc.c:1646  */
    { comparaTipo(&pilha_tipos, COMPAR, T_BOOL); geraCodigo(NULL, "CMEG"); }
#line 1786 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 321 "compilador.y" /* yacc.c:1646  */
    { comparaTipo(&pilha_tipos, COMPAR, T_BOOL); geraCodigo(NULL, "CMIG"); }
#line 1792 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 322 "compilador.y" /* yacc.c:1646  */
    { comparaTipo(&pilha_tipos, COMPAR, T_BOOL); geraCodigo(NULL, "CMDG"); }
#line 1798 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 325 "compilador.y" /* yacc.c:1646  */
    { comparaTipo(&pilha_tipos, CALC, T_INT); geraCodigo(NULL, "SOMA"); }
#line 1804 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 326 "compilador.y" /* yacc.c:1646  */
    { comparaTipo(&pilha_tipos, CALC, T_INT); geraCodigo(NULL, "SUBT"); }
#line 1810 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 327 "compilador.y" /* yacc.c:1646  */
    { comparaTipo(&pilha_tipos, COMPAR, T_BOOL); geraCodigo(NULL, "DISJ"); }
#line 1816 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 332 "compilador.y" /* yacc.c:1646  */
    { comparaTipo(&pilha_tipos, CALC, T_INT); geraCodigo(NULL, "MULT"); }
#line 1822 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 333 "compilador.y" /* yacc.c:1646  */
    { comparaTipo(&pilha_tipos, CALC, T_INT); geraCodigo(NULL, "DIVI"); }
#line 1828 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 334 "compilador.y" /* yacc.c:1646  */
    { comparaTipo(&pilha_tipos, COMPAR, T_BOOL); geraCodigo(NULL, "CONJ"); }
#line 1834 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 340 "compilador.y" /* yacc.c:1646  */
    { sprintf(buffer, "CRCT %d", atoi(token));
											  geraCodigo(NULL, buffer);
											  empilhaTipo(&pilha_tipos, T_INT);
											}
#line 1843 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 344 "compilador.y" /* yacc.c:1646  */
    { geraCodigo (NULL, "CRCT 1"); empilhaTipo(&pilha_tipos, T_BOOL); }
#line 1849 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 345 "compilador.y" /* yacc.c:1646  */
    { geraCodigo (NULL, "CRCT 0"); empilhaTipo(&pilha_tipos, T_BOOL); }
#line 1855 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 349 "compilador.y" /* yacc.c:1646  */
    { simb = procuraSimbolo(tab_s, token, nivel_lexico); 
											  geraCodigoCV(simb); empilhaTipo(&pilha_tipos, simb->tipo);
}
#line 1863 "compilador.tab.c" /* yacc.c:1646  */
    break;


#line 1867 "compilador.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 355 "compilador.y" /* yacc.c:1906  */


main (int argc, char** argv) {
   FILE* fp;
   extern FILE* yyin;

   if (argc<2 || argc>2) {
         printf("usage compilador <arq>a %d\n", argc);
         return(-1);
      }

   fp=fopen (argv[1], "r");
   if (fp == NULL) {
      printf("usage compilador <arq>b\n");
      return(-1);
   }


/* -------------------------------------------------------------------
 *  Inicia a Tabela de Símbolos
 * ------------------------------------------------------------------- */
  inicializaPilha(&pilha_rotulos);
  inicializaPilha(&pilha_tipos);
  inicializaPilha(&pilha_simbolos);

   yyin=fp;
   yyparse();

   return 0;
}

