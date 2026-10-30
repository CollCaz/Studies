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
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbol_table.h" // Include our new symbol table header
/* AST Node Structure */
typedef struct ASTNode {
    char *node_type;
    char *value;
    int num_children;
    struct ASTNode **children;
    Type *type; // Add this field to carry type information
} ASTNode;

/* Function Prototypes */
ASTNode* create_node(const char *node_type, const char *value, int num_children, ...);
void print_ast(ASTNode *node, int level);
void free_ast(ASTNode *node);
Type* get_base_type_from_specifiers(ASTNode* specifiers_node);
char* get_declarator_name(ASTNode* declarator_node);
Type* build_declarator_type(Type* base_type, ASTNode* declarator_node);


/* External declarations from the lexer */
extern int yylex();
extern int line_count;
extern char* yytext;
extern FILE* yyin;

void yyerror(const char *s);

/* Root of the AST */
ASTNode *ast_root = NULL;
int is_typedef_declaration = 0; // Flag to track typedef context


#line 109 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_INT_CONST = 4,                  /* INT_CONST  */
  YYSYMBOL_FLOAT_CONST = 5,                /* FLOAT_CONST  */
  YYSYMBOL_CHAR_CONST = 6,                 /* CHAR_CONST  */
  YYSYMBOL_STRING_LITERAL = 7,             /* STRING_LITERAL  */
  YYSYMBOL_TYPENAME = 8,                   /* TYPENAME  */
  YYSYMBOL_KEYWORD_BREAK = 9,              /* KEYWORD_BREAK  */
  YYSYMBOL_KEYWORD_CASE = 10,              /* KEYWORD_CASE  */
  YYSYMBOL_KEYWORD_CONST = 11,             /* KEYWORD_CONST  */
  YYSYMBOL_KEYWORD_CONTINUE = 12,          /* KEYWORD_CONTINUE  */
  YYSYMBOL_KEYWORD_DEFAULT = 13,           /* KEYWORD_DEFAULT  */
  YYSYMBOL_KEYWORD_DO = 14,                /* KEYWORD_DO  */
  YYSYMBOL_KEYWORD_ELSE = 15,              /* KEYWORD_ELSE  */
  YYSYMBOL_KEYWORD_ENUM = 16,              /* KEYWORD_ENUM  */
  YYSYMBOL_KEYWORD_IF = 17,                /* KEYWORD_IF  */
  YYSYMBOL_KEYWORD_RESTRICT = 18,          /* KEYWORD_RESTRICT  */
  YYSYMBOL_KEYWORD_RETURN = 19,            /* KEYWORD_RETURN  */
  YYSYMBOL_KEYWORD_SIZEOF = 20,            /* KEYWORD_SIZEOF  */
  YYSYMBOL_KEYWORD_STRUCT = 21,            /* KEYWORD_STRUCT  */
  YYSYMBOL_KEYWORD_SWITCH = 22,            /* KEYWORD_SWITCH  */
  YYSYMBOL_KEYWORD_TYPEDEF = 23,           /* KEYWORD_TYPEDEF  */
  YYSYMBOL_KEYWORD_UNION = 24,             /* KEYWORD_UNION  */
  YYSYMBOL_KEYWORD_VOLATILE = 25,          /* KEYWORD_VOLATILE  */
  YYSYMBOL_KEYWORD_WHILE = 26,             /* KEYWORD_WHILE  */
  YYSYMBOL_KEYWORD_FOR = 27,               /* KEYWORD_FOR  */
  YYSYMBOL_OP_INCREMENT = 28,              /* OP_INCREMENT  */
  YYSYMBOL_OP_DECREMENT = 29,              /* OP_DECREMENT  */
  YYSYMBOL_OP_SHIFT_LEFT = 30,             /* OP_SHIFT_LEFT  */
  YYSYMBOL_OP_SHIFT_RIGHT = 31,            /* OP_SHIFT_RIGHT  */
  YYSYMBOL_OP_LE = 32,                     /* OP_LE  */
  YYSYMBOL_OP_GE = 33,                     /* OP_GE  */
  YYSYMBOL_OP_EQ = 34,                     /* OP_EQ  */
  YYSYMBOL_OP_NE = 35,                     /* OP_NE  */
  YYSYMBOL_OP_AND = 36,                    /* OP_AND  */
  YYSYMBOL_OP_OR = 37,                     /* OP_OR  */
  YYSYMBOL_OP_ADD_ASSIGN = 38,             /* OP_ADD_ASSIGN  */
  YYSYMBOL_OP_SUB_ASSIGN = 39,             /* OP_SUB_ASSIGN  */
  YYSYMBOL_OP_MUL_ASSIGN = 40,             /* OP_MUL_ASSIGN  */
  YYSYMBOL_OP_DIV_ASSIGN = 41,             /* OP_DIV_ASSIGN  */
  YYSYMBOL_OP_MOD_ASSIGN = 42,             /* OP_MOD_ASSIGN  */
  YYSYMBOL_KEYWORD_CHAR = 43,              /* KEYWORD_CHAR  */
  YYSYMBOL_KEYWORD_DOUBLE = 44,            /* KEYWORD_DOUBLE  */
  YYSYMBOL_KEYWORD_FLOAT = 45,             /* KEYWORD_FLOAT  */
  YYSYMBOL_KEYWORD_INT = 46,               /* KEYWORD_INT  */
  YYSYMBOL_KEYWORD_LONG = 47,              /* KEYWORD_LONG  */
  YYSYMBOL_KEYWORD_SHORT = 48,             /* KEYWORD_SHORT  */
  YYSYMBOL_KEYWORD_SIGNED = 49,            /* KEYWORD_SIGNED  */
  YYSYMBOL_KEYWORD_UNSIGNED = 50,          /* KEYWORD_UNSIGNED  */
  YYSYMBOL_KEYWORD_VOID = 51,              /* KEYWORD_VOID  */
  YYSYMBOL_LOWER_THAN_ELSE = 52,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_53_ = 53,                       /* ';'  */
  YYSYMBOL_54_ = 54,                       /* ','  */
  YYSYMBOL_55_ = 55,                       /* '='  */
  YYSYMBOL_56_ = 56,                       /* '('  */
  YYSYMBOL_57_ = 57,                       /* ')'  */
  YYSYMBOL_58_ = 58,                       /* '['  */
  YYSYMBOL_59_ = 59,                       /* ']'  */
  YYSYMBOL_60_ = 60,                       /* '*'  */
  YYSYMBOL_61_ = 61,                       /* '{'  */
  YYSYMBOL_62_ = 62,                       /* '}'  */
  YYSYMBOL_63_ = 63,                       /* ':'  */
  YYSYMBOL_64_ = 64,                       /* '|'  */
  YYSYMBOL_65_ = 65,                       /* '^'  */
  YYSYMBOL_66_ = 66,                       /* '&'  */
  YYSYMBOL_67_ = 67,                       /* '<'  */
  YYSYMBOL_68_ = 68,                       /* '>'  */
  YYSYMBOL_69_ = 69,                       /* '+'  */
  YYSYMBOL_70_ = 70,                       /* '-'  */
  YYSYMBOL_71_ = 71,                       /* '/'  */
  YYSYMBOL_72_ = 72,                       /* '%'  */
  YYSYMBOL_73_ = 73,                       /* '~'  */
  YYSYMBOL_74_ = 74,                       /* '!'  */
  YYSYMBOL_YYACCEPT = 75,                  /* $accept  */
  YYSYMBOL_program = 76,                   /* program  */
  YYSYMBOL_external_declaration = 77,      /* external_declaration  */
  YYSYMBOL_function_definition = 78,       /* function_definition  */
  YYSYMBOL_declaration = 79,               /* declaration  */
  YYSYMBOL_declaration_specifiers = 80,    /* declaration_specifiers  */
  YYSYMBOL_storage_class_specifier = 81,   /* storage_class_specifier  */
  YYSYMBOL_type_specifier = 82,            /* type_specifier  */
  YYSYMBOL_type_specifier_node = 83,       /* type_specifier_node  */
  YYSYMBOL_init_declarator_list = 84,      /* init_declarator_list  */
  YYSYMBOL_init_declarator = 85,           /* init_declarator  */
  YYSYMBOL_declarator = 86,                /* declarator  */
  YYSYMBOL_type_name = 87,                 /* type_name  */
  YYSYMBOL_abstract_declarator = 88,       /* abstract_declarator  */
  YYSYMBOL_direct_abstract_declarator = 89, /* direct_abstract_declarator  */
  YYSYMBOL_assignment_expression_opt = 90, /* assignment_expression_opt  */
  YYSYMBOL_parameter_type_list_opt = 91,   /* parameter_type_list_opt  */
  YYSYMBOL_unary_expression = 92,          /* unary_expression  */
  YYSYMBOL_pointer = 93,                   /* pointer  */
  YYSYMBOL_struct_or_union_specifier = 94, /* struct_or_union_specifier  */
  YYSYMBOL_struct_or_union = 95,           /* struct_or_union  */
  YYSYMBOL_struct_declaration_list = 96,   /* struct_declaration_list  */
  YYSYMBOL_struct_declaration = 97,        /* struct_declaration  */
  YYSYMBOL_specifier_qualifier_list = 98,  /* specifier_qualifier_list  */
  YYSYMBOL_struct_declarator_list = 99,    /* struct_declarator_list  */
  YYSYMBOL_struct_declarator = 100,        /* struct_declarator  */
  YYSYMBOL_type_qualifier = 101,           /* type_qualifier  */
  YYSYMBOL_enum_specifier = 102,           /* enum_specifier  */
  YYSYMBOL_enumerator_list = 103,          /* enumerator_list  */
  YYSYMBOL_enumerator = 104,               /* enumerator  */
  YYSYMBOL_initializer = 105,              /* initializer  */
  YYSYMBOL_initializer_list = 106,         /* initializer_list  */
  YYSYMBOL_direct_declarator = 107,        /* direct_declarator  */
  YYSYMBOL_parameter_type_list = 108,      /* parameter_type_list  */
  YYSYMBOL_parameter_list = 109,           /* parameter_list  */
  YYSYMBOL_parameter_declaration = 110,    /* parameter_declaration  */
  YYSYMBOL_compound_statement = 111,       /* compound_statement  */
  YYSYMBOL_block_item_list = 112,          /* block_item_list  */
  YYSYMBOL_block_item = 113,               /* block_item  */
  YYSYMBOL_statement = 114,                /* statement  */
  YYSYMBOL_expression_statement = 115,     /* expression_statement  */
  YYSYMBOL_expression_opt = 116,           /* expression_opt  */
  YYSYMBOL_iteration_statement = 117,      /* iteration_statement  */
  YYSYMBOL_selection_statement = 118,      /* selection_statement  */
  YYSYMBOL_labeled_statement = 119,        /* labeled_statement  */
  YYSYMBOL_jump_statement = 120,           /* jump_statement  */
  YYSYMBOL_expression = 121,               /* expression  */
  YYSYMBOL_assignment_expression = 122,    /* assignment_expression  */
  YYSYMBOL_assignment_operator = 123,      /* assignment_operator  */
  YYSYMBOL_conditional_expression = 124,   /* conditional_expression  */
  YYSYMBOL_logical_or_expression = 125,    /* logical_or_expression  */
  YYSYMBOL_logical_and_expression = 126,   /* logical_and_expression  */
  YYSYMBOL_inclusive_or_expression = 127,  /* inclusive_or_expression  */
  YYSYMBOL_exclusive_or_expression = 128,  /* exclusive_or_expression  */
  YYSYMBOL_and_expression = 129,           /* and_expression  */
  YYSYMBOL_equality_expression = 130,      /* equality_expression  */
  YYSYMBOL_relational_expression = 131,    /* relational_expression  */
  YYSYMBOL_shift_expression = 132,         /* shift_expression  */
  YYSYMBOL_additive_expression = 133,      /* additive_expression  */
  YYSYMBOL_multiplicative_expression = 134, /* multiplicative_expression  */
  YYSYMBOL_cast_expression = 135,          /* cast_expression  */
  YYSYMBOL_unary_operator = 136,           /* unary_operator  */
  YYSYMBOL_postfix_expression = 137,       /* postfix_expression  */
  YYSYMBOL_argument_expression_list = 138, /* argument_expression_list  */
  YYSYMBOL_primary_expression = 139        /* primary_expression  */
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
#define YYFINAL  32
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1028

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  75
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  65
/* YYNRULES -- Number of rules.  */
#define YYNRULES  187
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  308

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   307


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
       2,     2,     2,    74,     2,     2,     2,    72,    66,     2,
      56,    57,    60,    69,    54,    70,     2,    71,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    63,    53,
      67,    55,    68,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    58,     2,    59,    65,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    61,    64,    62,    73,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   100,   100,   101,   105,   106,   110,   124,   150,   151,
     152,   153,   154,   155,   159,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   175,   176,   177,   178,   182,   183,
     187,   191,   195,   196,   200,   201,   205,   206,   207,   211,
     212,   213,   214,   215,   219,   220,   224,   225,   232,   233,
     234,   235,   236,   237,   246,   247,   251,   253,   255,   260,
     261,   265,   266,   270,   274,   275,   276,   277,   281,   282,
     286,   290,   291,   292,   296,   297,   298,   299,   300,   304,
     305,   309,   310,   314,   315,   319,   320,   324,   325,   326,
     327,   328,   329,   333,   337,   338,   342,   343,   347,   350,
     356,   357,   361,   362,   366,   367,   368,   369,   370,   371,
     375,   376,   380,   381,   385,   386,   387,   388,   392,   393,
     394,   398,   399,   400,   404,   405,   406,   407,   411,   412,
     416,   417,   421,   421,   421,   422,   422,   422,   426,   430,
     431,   435,   436,   440,   441,   445,   446,   450,   451,   455,
     456,   457,   461,   462,   463,   464,   465,   469,   470,   471,
     475,   476,   477,   481,   482,   483,   484,   488,   492,   492,
     492,   492,   492,   492,   496,   497,   498,   499,   500,   501,
     505,   506,   510,   511,   512,   513,   514,   515
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
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER",
  "INT_CONST", "FLOAT_CONST", "CHAR_CONST", "STRING_LITERAL", "TYPENAME",
  "KEYWORD_BREAK", "KEYWORD_CASE", "KEYWORD_CONST", "KEYWORD_CONTINUE",
  "KEYWORD_DEFAULT", "KEYWORD_DO", "KEYWORD_ELSE", "KEYWORD_ENUM",
  "KEYWORD_IF", "KEYWORD_RESTRICT", "KEYWORD_RETURN", "KEYWORD_SIZEOF",
  "KEYWORD_STRUCT", "KEYWORD_SWITCH", "KEYWORD_TYPEDEF", "KEYWORD_UNION",
  "KEYWORD_VOLATILE", "KEYWORD_WHILE", "KEYWORD_FOR", "OP_INCREMENT",
  "OP_DECREMENT", "OP_SHIFT_LEFT", "OP_SHIFT_RIGHT", "OP_LE", "OP_GE",
  "OP_EQ", "OP_NE", "OP_AND", "OP_OR", "OP_ADD_ASSIGN", "OP_SUB_ASSIGN",
  "OP_MUL_ASSIGN", "OP_DIV_ASSIGN", "OP_MOD_ASSIGN", "KEYWORD_CHAR",
  "KEYWORD_DOUBLE", "KEYWORD_FLOAT", "KEYWORD_INT", "KEYWORD_LONG",
  "KEYWORD_SHORT", "KEYWORD_SIGNED", "KEYWORD_UNSIGNED", "KEYWORD_VOID",
  "LOWER_THAN_ELSE", "';'", "','", "'='", "'('", "')'", "'['", "']'",
  "'*'", "'{'", "'}'", "':'", "'|'", "'^'", "'&'", "'<'", "'>'", "'+'",
  "'-'", "'/'", "'%'", "'~'", "'!'", "$accept", "program",
  "external_declaration", "function_definition", "declaration",
  "declaration_specifiers", "storage_class_specifier", "type_specifier",
  "type_specifier_node", "init_declarator_list", "init_declarator",
  "declarator", "type_name", "abstract_declarator",
  "direct_abstract_declarator", "assignment_expression_opt",
  "parameter_type_list_opt", "unary_expression", "pointer",
  "struct_or_union_specifier", "struct_or_union",
  "struct_declaration_list", "struct_declaration",
  "specifier_qualifier_list", "struct_declarator_list",
  "struct_declarator", "type_qualifier", "enum_specifier",
  "enumerator_list", "enumerator", "initializer", "initializer_list",
  "direct_declarator", "parameter_type_list", "parameter_list",
  "parameter_declaration", "compound_statement", "block_item_list",
  "block_item", "statement", "expression_statement", "expression_opt",
  "iteration_statement", "selection_statement", "labeled_statement",
  "jump_statement", "expression", "assignment_expression",
  "assignment_operator", "conditional_expression", "logical_or_expression",
  "logical_and_expression", "inclusive_or_expression",
  "exclusive_or_expression", "and_expression", "equality_expression",
  "relational_expression", "shift_expression", "additive_expression",
  "multiplicative_expression", "cast_expression", "unary_operator",
  "postfix_expression", "argument_expression_list", "primary_expression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-231)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     966,  -231,  -231,    12,  -231,  -231,  -231,  -231,  -231,  -231,
    -231,  -231,  -231,  -231,  -231,  -231,  -231,  -231,   911,  -231,
    -231,  -231,    21,   966,  -231,   966,  -231,    15,   966,  -231,
     -38,    37,  -231,  -231,  -231,    21,     5,    47,  -231,    11,
      13,    89,  -231,  -231,    27,   977,  -231,    37,    54,   -29,
    -231,    35,  -231,  -231,    21,   559,   242,  -231,    89,   922,
     602,   977,   977,   768,  -231,    21,   977,   -11,   689,     8,
    -231,  -231,  -231,    64,  -231,  -231,  -231,  -231,  -231,   708,
     689,   689,   689,  -231,   689,  -231,  -231,  -231,  -231,  -231,
      65,  -231,  -231,  -231,    92,   100,    79,    85,    96,    22,
      30,    49,    45,   -26,  -231,   689,    26,  -231,   106,   120,
     689,   121,   112,   530,   122,   631,   123,   124,   125,  -231,
    -231,  -231,    21,  -231,   314,  -231,  -231,  -231,  -231,  -231,
    -231,  -231,    71,  -231,  -231,    21,   119,   129,  -231,  -231,
     118,   813,  -231,  -231,  -231,  -231,   101,  -231,  -231,     9,
    -231,  -231,  -231,  -231,  -231,   458,  -231,  -231,  -231,   -27,
      -2,  -231,  -231,  -231,  -231,  -231,  -231,  -231,   689,   689,
     689,   689,   689,   689,   689,   689,   689,   689,   689,   689,
     689,   689,   689,   689,   689,   689,   689,  -231,  -231,  -231,
     650,   689,   530,  -231,   127,  -231,   530,   158,   689,  -231,
     103,   689,   689,   386,  -231,  -231,  -231,   689,  -231,  -231,
     966,  -231,  -231,  -231,    21,  -231,   128,    52,  -231,   689,
    -231,  -231,   100,    79,    85,    96,    22,    30,    30,    49,
      49,    49,    49,    45,    45,   -26,   -26,  -231,  -231,  -231,
    -231,  -231,   -15,    24,  -231,   530,  -231,   130,    10,  -231,
      32,    42,   689,   134,   138,  -231,  -231,  -231,  -231,   858,
     689,  -231,    90,    93,  -231,   689,  -231,  -231,  -231,   689,
     530,   530,   530,   135,   689,   136,   140,  -231,   141,  -231,
     966,   689,    90,  -231,    87,   180,  -231,  -231,   689,   146,
    -231,  -231,  -231,   145,   144,   151,   530,   150,   689,  -231,
    -231,  -231,  -231,   530,   152,  -231,   530,  -231
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    25,    71,     0,    73,    59,    14,    60,    72,    16,
      21,    20,    18,    19,    17,    22,    23,    15,     0,     2,
       4,     5,     0,     8,    24,     9,    26,     0,    10,    27,
      78,     0,     1,     3,    87,     0,    54,     0,    28,    30,
       0,    33,    11,    12,    58,     0,    13,     0,    81,     0,
      79,     0,    55,     7,     0,     0,     0,     6,    32,     0,
       0,     0,    64,     0,    61,     0,    65,     0,     0,     0,
      75,    88,    29,    30,   182,   183,   184,   185,   186,     0,
       0,     0,     0,   169,     0,   168,   170,   171,   172,   173,
     167,    31,    83,   130,   138,   139,   141,   143,   145,   147,
     149,   152,   157,   160,   163,     0,    48,   174,   182,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   110,
      98,   102,     0,   105,     0,   100,   103,   104,   107,   106,
     109,   108,     0,   128,    90,    97,     0,    93,    94,    92,
       0,     0,    66,    57,    62,    70,     0,    68,    67,     0,
      74,   167,    82,    77,    80,     0,    52,    49,    50,     0,
       0,    85,   136,   137,   133,   134,   135,   132,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    51,   177,   178,
       0,     0,     0,   126,     0,   127,     0,     0,     0,   124,
       0,     0,     0,   113,    99,   101,   111,     0,    96,    89,
       0,    91,    56,    63,     0,    76,     0,    34,   187,     0,
      84,   131,   140,   142,   144,   146,   148,   150,   151,   155,
     156,   153,   154,   158,   159,   161,   162,   164,   165,   166,
     175,   180,     0,     0,   121,     0,   123,     0,     0,   125,
       0,     0,   113,     0,   112,   129,    95,    69,    53,    47,
      45,    35,    37,    36,    86,     0,   176,   179,   122,     0,
       0,     0,     0,     0,   113,     0,     0,    46,     0,    44,
      47,    45,    38,   181,     0,   118,   120,   114,   113,     0,
      39,    43,    41,     0,     0,     0,     0,     0,   113,    42,
      40,   115,   119,     0,     0,   117,     0,   116
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -231,  -231,   193,  -231,   -50,     3,  -231,  -231,   -25,  -231,
     159,   -18,  -231,   -47,   -48,   -67,   -64,    58,   -35,  -231,
    -231,   156,   -56,   -53,  -231,     6,   -13,  -231,   172,   -59,
    -231,  -231,   181,   163,  -231,    62,   184,  -231,   133,  -105,
    -231,  -230,  -231,  -231,  -231,  -231,   -80,   -55,  -231,   -49,
    -231,    56,   104,   102,   105,   107,   -16,   -45,   -20,   -12,
     -91,  -231,  -231,  -231,  -231
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    18,    19,    20,    21,   135,    23,    24,    25,    37,
      38,    73,   216,   261,   262,   278,   276,    90,    40,    26,
      27,    63,    64,    65,   146,   147,    28,    29,    49,    50,
      91,   160,    41,   277,   137,   138,   123,   124,   125,   126,
     127,   253,   128,   129,   130,   131,   132,   133,   168,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   242,   107
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      92,    52,   159,    22,    39,   140,   121,   144,   197,   142,
     154,    48,    48,   148,   187,    30,    34,    51,    44,   152,
      62,    22,   273,    47,    34,    69,    42,   207,    43,   161,
     218,    46,    66,    70,   184,   200,    62,    62,    62,   265,
      48,    62,   266,   149,   289,   185,   186,   145,    66,    66,
      66,   150,   219,    66,   188,   189,   174,   175,   297,   122,
     220,   194,   176,   177,   207,    36,    55,   270,   304,    35,
     153,   215,    56,    31,   121,   159,    45,    35,   207,   180,
     181,    36,   190,   267,   191,   144,   207,   244,    61,   271,
     154,   246,    71,   237,   238,   239,   207,   178,   179,   272,
      53,    54,   217,   162,   163,   164,   165,   166,   259,    68,
     260,   243,    36,   221,   182,   183,    62,   208,   248,    55,
     167,   250,   251,   254,   206,   207,   151,   122,    66,   169,
      62,   229,   230,   231,   232,   241,   170,   156,   157,   158,
     268,   207,    66,   171,   295,    59,   280,    60,   281,   259,
     172,   260,   255,   252,   213,   214,   249,   207,   227,   228,
     233,   234,   173,   151,   264,   285,   286,   287,   151,   192,
     235,   236,   254,   193,   195,   196,   209,   211,   198,   201,
     202,   203,   263,   210,   247,   258,   269,   274,   288,   284,
     245,   302,   207,   290,   254,   296,   145,   291,   305,   298,
     292,   307,   299,   300,   301,   279,   122,   303,   254,   306,
     283,    33,   275,    72,   294,   282,   293,   141,   254,    67,
     257,    58,   136,    57,   263,   222,   279,   151,   151,   151,
     151,   151,   151,   151,   151,   151,   151,   151,   151,   151,
     151,   151,   151,   151,   151,   108,    75,    76,    77,    78,
       1,   109,   110,     2,   111,   112,   113,   205,     3,   114,
       4,   115,    79,     5,   116,     6,     7,     8,   117,   118,
      80,    81,   256,   224,   223,     0,     0,   225,     0,     0,
     226,     0,     0,     0,     0,     9,    10,    11,    12,    13,
      14,    15,    16,    17,     0,   119,     0,     0,    82,     0,
       0,     0,    83,    56,   120,     0,     0,     0,    85,     0,
       0,    86,    87,     0,     0,    88,    89,   108,    75,    76,
      77,    78,     1,   109,   110,     2,   111,   112,   113,     0,
       3,   114,     4,   115,    79,     5,   116,     6,     7,     8,
     117,   118,    80,    81,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     9,    10,    11,
      12,    13,    14,    15,    16,    17,     0,   119,     0,     0,
      82,     0,     0,     0,    83,    56,   204,     0,     0,     0,
      85,     0,     0,    86,    87,     0,     0,    88,    89,    74,
      75,    76,    77,    78,     1,     0,     0,     2,     0,     0,
       0,     0,     3,     0,     4,     0,    79,     5,     0,     6,
       7,     8,     0,     0,    80,    81,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     9,
      10,    11,    12,    13,    14,    15,    16,    17,     0,     0,
       0,     0,    82,     0,     0,     0,    83,     0,     0,     0,
       0,     0,    85,     0,     0,    86,    87,     0,     0,    88,
      89,    74,    75,    76,    77,    78,     1,     0,     0,     2,
       0,     0,     0,     0,     3,     0,     4,     0,    79,     5,
       0,     0,     7,     8,     0,     0,    80,    81,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     9,    10,    11,    12,    13,    14,    15,    16,    17,
       0,     0,     0,     0,    82,     0,     0,     0,    83,     0,
       0,     0,     0,     0,    85,     0,     0,    86,    87,     0,
       0,    88,    89,   108,    75,    76,    77,    78,     0,   109,
     110,     0,   111,   112,   113,     0,     0,   114,     0,   115,
      79,     0,   116,     0,     0,     0,   117,   118,    80,    81,
       0,     0,    74,    75,    76,    77,    78,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    79,
       0,     0,     0,   119,     0,     0,    82,    80,    81,     0,
      83,    56,     0,     0,     0,     0,    85,     0,     0,    86,
      87,     0,     0,    88,    89,    74,    75,    76,    77,    78,
       0,     0,     0,     0,     0,    82,     0,     0,     0,    83,
      84,     0,    79,     0,     0,    85,     0,     0,    86,    87,
      80,    81,    88,    89,    74,    75,    76,    77,    78,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    79,     0,    74,    75,    76,    77,    78,    82,    80,
      81,   139,    83,     0,     0,     0,     0,     0,    85,     0,
      79,    86,    87,     0,     0,    88,    89,     0,    80,    81,
       0,     0,     0,     0,   199,     0,     0,    82,     0,     0,
       0,    83,    74,    75,    76,    77,    78,    85,     0,     0,
      86,    87,     0,     0,    88,    89,    82,   240,     0,    79,
      83,    74,    75,    76,    77,    78,    85,    80,    81,    86,
      87,     0,     0,    88,    89,     0,     0,     0,    79,     0,
       0,     0,     0,     0,     0,     0,    80,    81,     0,     0,
       0,     0,     0,     0,     0,    82,     0,     0,     0,    83,
       0,     0,     0,     0,     0,    85,     0,     0,    86,    87,
       0,     0,    88,    89,   155,     0,     0,     0,    83,     0,
       0,     0,     0,     0,    85,     0,     1,    86,    87,     2,
       0,    88,    89,     0,     3,     0,     4,     0,     0,     5,
       0,     0,     7,     8,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     9,    10,    11,    12,    13,    14,    15,    16,    17,
       0,     1,     0,     0,     2,     0,     0,     0,     0,     3,
     143,     4,     0,     0,     5,     0,     0,     7,     8,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     9,    10,    11,    12,
      13,    14,    15,    16,    17,     0,     1,     0,     0,     2,
       0,     0,     0,     0,     3,   212,     4,     0,     0,     5,
       0,     6,     7,     8,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     9,    10,    11,    12,    13,    14,    15,    16,    17,
       0,    32,     0,     0,   259,     0,   260,     0,    36,     1,
       0,     0,     2,     0,     0,     0,     0,     3,     0,     4,
       1,     0,     5,     2,     6,     7,     8,     0,     3,     0,
       4,     0,     0,     5,     0,     6,     7,     8,     0,     0,
       0,     0,     0,     0,     9,    10,    11,    12,    13,    14,
      15,    16,    17,     0,     0,     9,    10,    11,    12,    13,
      14,    15,    16,    17,     1,     0,     0,     2,     0,   134,
       0,     0,     3,     0,     4,     1,     0,     5,     2,     6,
       7,     8,     0,     3,     0,     4,     0,     0,     5,     0,
       0,     7,     8,     0,     0,     0,     0,     0,     0,     9,
      10,    11,    12,    13,    14,    15,    16,    17,     0,     0,
       9,    10,    11,    12,    13,    14,    15,    16,    17
};

static const yytype_int16 yycheck[] =
{
      55,    36,    82,     0,    22,    60,    56,    63,   113,    62,
      69,     3,     3,    66,   105,     3,     3,    35,     3,    68,
      45,    18,   252,    61,     3,    54,    23,    54,    25,    84,
      57,    28,    45,    62,    60,   115,    61,    62,    63,    54,
       3,    66,    57,    54,   274,    71,    72,    65,    61,    62,
      63,    62,    54,    66,    28,    29,    34,    35,   288,    56,
      62,   110,    32,    33,    54,    60,    55,    57,   298,    56,
      62,    62,    61,    61,   124,   155,    61,    56,    54,    30,
      31,    60,    56,    59,    58,   141,    54,   192,    61,    57,
     149,   196,    57,   184,   185,   186,    54,    67,    68,    57,
      53,    54,   155,    38,    39,    40,    41,    42,    56,    55,
      58,   191,    60,   168,    69,    70,   141,   135,   198,    55,
      55,   201,   202,   203,    53,    54,    68,   124,   141,    37,
     155,   176,   177,   178,   179,   190,    36,    79,    80,    81,
     245,    54,   155,    64,    57,    56,    56,    58,    58,    56,
      65,    58,   207,   203,    53,    54,    53,    54,   174,   175,
     180,   181,    66,   105,   219,   270,   271,   272,   110,    63,
     182,   183,   252,    53,    53,    63,    57,    59,    56,    56,
      56,    56,   217,    54,    26,    57,    56,    53,    53,   269,
      63,   296,    54,    57,   274,    15,   214,    57,   303,    53,
      59,   306,    57,    59,    53,   260,   203,    57,   288,    57,
     265,    18,   259,    54,   281,   263,   280,    61,   298,    47,
     214,    40,    59,    39,   259,   169,   281,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,   124,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,   210,   171,   170,    -1,    -1,   172,    -1,    -1,
     173,    -1,    -1,    -1,    -1,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    -1,    53,    -1,    -1,    56,    -1,
      -1,    -1,    60,    61,    62,    -1,    -1,    -1,    66,    -1,
      -1,    69,    70,    -1,    -1,    73,    74,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    -1,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    -1,    53,    -1,    -1,
      56,    -1,    -1,    -1,    60,    61,    62,    -1,    -1,    -1,
      66,    -1,    -1,    69,    70,    -1,    -1,    73,    74,     3,
       4,     5,     6,     7,     8,    -1,    -1,    11,    -1,    -1,
      -1,    -1,    16,    -1,    18,    -1,    20,    21,    -1,    23,
      24,    25,    -1,    -1,    28,    29,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    -1,    -1,
      -1,    -1,    56,    -1,    -1,    -1,    60,    -1,    -1,    -1,
      -1,    -1,    66,    -1,    -1,    69,    70,    -1,    -1,    73,
      74,     3,     4,     5,     6,     7,     8,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    16,    -1,    18,    -1,    20,    21,
      -1,    -1,    24,    25,    -1,    -1,    28,    29,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    60,    -1,
      -1,    -1,    -1,    -1,    66,    -1,    -1,    69,    70,    -1,
      -1,    73,    74,     3,     4,     5,     6,     7,    -1,     9,
      10,    -1,    12,    13,    14,    -1,    -1,    17,    -1,    19,
      20,    -1,    22,    -1,    -1,    -1,    26,    27,    28,    29,
      -1,    -1,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    20,
      -1,    -1,    -1,    53,    -1,    -1,    56,    28,    29,    -1,
      60,    61,    -1,    -1,    -1,    -1,    66,    -1,    -1,    69,
      70,    -1,    -1,    73,    74,     3,     4,     5,     6,     7,
      -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    60,
      61,    -1,    20,    -1,    -1,    66,    -1,    -1,    69,    70,
      28,    29,    73,    74,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    20,    -1,     3,     4,     5,     6,     7,    56,    28,
      29,    59,    60,    -1,    -1,    -1,    -1,    -1,    66,    -1,
      20,    69,    70,    -1,    -1,    73,    74,    -1,    28,    29,
      -1,    -1,    -1,    -1,    53,    -1,    -1,    56,    -1,    -1,
      -1,    60,     3,     4,     5,     6,     7,    66,    -1,    -1,
      69,    70,    -1,    -1,    73,    74,    56,    57,    -1,    20,
      60,     3,     4,     5,     6,     7,    66,    28,    29,    69,
      70,    -1,    -1,    73,    74,    -1,    -1,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    60,
      -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,    69,    70,
      -1,    -1,    73,    74,    56,    -1,    -1,    -1,    60,    -1,
      -1,    -1,    -1,    -1,    66,    -1,     8,    69,    70,    11,
      -1,    73,    74,    -1,    16,    -1,    18,    -1,    -1,    21,
      -1,    -1,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      -1,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    16,
      62,    18,    -1,    -1,    21,    -1,    -1,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    -1,     8,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    16,    62,    18,    -1,    -1,    21,
      -1,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      -1,     0,    -1,    -1,    56,    -1,    58,    -1,    60,     8,
      -1,    -1,    11,    -1,    -1,    -1,    -1,    16,    -1,    18,
       8,    -1,    21,    11,    23,    24,    25,    -1,    16,    -1,
      18,    -1,    -1,    21,    -1,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    -1,    -1,    43,    44,    45,    46,    47,
      48,    49,    50,    51,     8,    -1,    -1,    11,    -1,    57,
      -1,    -1,    16,    -1,    18,     8,    -1,    21,    11,    23,
      24,    25,    -1,    16,    -1,    18,    -1,    -1,    21,    -1,
      -1,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    -1,    -1,
      43,    44,    45,    46,    47,    48,    49,    50,    51
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     8,    11,    16,    18,    21,    23,    24,    25,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    76,    77,
      78,    79,    80,    81,    82,    83,    94,    95,   101,   102,
       3,    61,     0,    77,     3,    56,    60,    84,    85,    86,
      93,   107,    80,    80,     3,    61,    80,    61,     3,   103,
     104,    86,    93,    53,    54,    55,    61,   111,   107,    56,
      58,    61,    83,    96,    97,    98,   101,   103,    55,    54,
      62,    57,    85,    86,     3,     4,     5,     6,     7,    20,
      28,    29,    56,    60,    61,    66,    69,    70,    73,    74,
      92,   105,   122,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   139,     3,     9,
      10,    12,    13,    14,    17,    19,    22,    26,    27,    53,
      62,    79,    80,   111,   112,   113,   114,   115,   117,   118,
     119,   120,   121,   122,    57,    80,   108,   109,   110,    59,
     122,    96,    98,    62,    97,    86,    99,   100,    98,    54,
      62,    92,   124,    62,   104,    56,    92,    92,    92,   121,
     106,   122,    38,    39,    40,    41,    42,    55,   123,    37,
      36,    64,    65,    66,    34,    35,    32,    33,    67,    68,
      30,    31,    69,    70,    60,    71,    72,   135,    28,    29,
      56,    58,    63,    53,   124,    53,    63,   114,    56,    53,
     121,    56,    56,    56,    62,   113,    53,    54,    86,    57,
      54,    59,    62,    53,    54,    62,    87,    98,    57,    54,
      62,   122,   126,   127,   128,   129,   130,   131,   131,   132,
     132,   132,   132,   133,   133,   134,   134,   135,   135,   135,
      57,   122,   138,   121,   114,    63,   114,    26,   121,    53,
     121,   121,    79,   116,   121,   122,   110,   100,    57,    56,
      58,    88,    89,    93,   122,    54,    57,    59,   114,    56,
      57,    57,    57,   116,    53,    88,    91,   108,    90,   122,
      56,    58,    89,   122,   121,   114,   114,   114,    53,   116,
      57,    57,    59,    91,    90,    57,    15,   116,    53,    57,
      59,    53,   114,    57,   116,   114,    57,   114
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    75,    76,    76,    77,    77,    78,    79,    80,    80,
      80,    80,    80,    80,    81,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    83,    83,    83,    83,    84,    84,
      85,    85,    86,    86,    87,    87,    88,    88,    88,    89,
      89,    89,    89,    89,    90,    90,    91,    91,    92,    92,
      92,    92,    92,    92,    93,    93,    94,    94,    94,    95,
      95,    96,    96,    97,    98,    98,    98,    98,    99,    99,
     100,   101,   101,   101,   102,   102,   102,   102,   102,   103,
     103,   104,   104,   105,   105,   106,   106,   107,   107,   107,
     107,   107,   107,   108,   109,   109,   110,   110,   111,   111,
     112,   112,   113,   113,   114,   114,   114,   114,   114,   114,
     115,   115,   116,   116,   117,   117,   117,   117,   118,   118,
     118,   119,   119,   119,   120,   120,   120,   120,   121,   121,
     122,   122,   123,   123,   123,   123,   123,   123,   124,   125,
     125,   126,   126,   127,   127,   128,   128,   129,   129,   130,
     130,   130,   131,   131,   131,   131,   131,   132,   132,   132,
     133,   133,   133,   134,   134,   134,   134,   135,   136,   136,
     136,   136,   136,   136,   137,   137,   137,   137,   137,   137,
     138,   138,   139,   139,   139,   139,   139,   139
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     3,     3,     1,     1,
       1,     2,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     3,     2,     1,     1,     2,     1,     1,     2,     3,
       4,     3,     4,     3,     1,     0,     1,     0,     1,     2,
       2,     2,     2,     4,     1,     2,     5,     4,     2,     1,
       1,     1,     2,     3,     1,     1,     2,     2,     1,     3,
       1,     1,     1,     1,     5,     4,     6,     5,     2,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     4,
       3,     4,     3,     1,     1,     3,     2,     1,     2,     3,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     0,     5,     7,     9,     8,     5,     7,
       5,     3,     4,     3,     2,     3,     2,     2,     1,     3,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     1,     3,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     4,     2,     2,     4,
       1,     3,     1,     1,     1,     1,     1,     3
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
  case 2: /* program: external_declaration  */
#line 100 "parser.y"
                           { ast_root = create_node("Program", NULL, 1, (yyvsp[0].node)); }
#line 1621 "parser.tab.c"
    break;

  case 3: /* program: program external_declaration  */
#line 101 "parser.y"
                                   { (yyval.node) = create_node("Program", NULL, 2, (yyvsp[-1].node), (yyvsp[0].node)); ast_root = (yyval.node); }
#line 1627 "parser.tab.c"
    break;

  case 4: /* external_declaration: function_definition  */
#line 105 "parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 1633 "parser.tab.c"
    break;

  case 5: /* external_declaration: declaration  */
#line 106 "parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 1639 "parser.tab.c"
    break;

  case 6: /* function_definition: declaration_specifiers declarator compound_statement  */
#line 111 "parser.y"
      {
        char* func_name = get_declarator_name((yyvsp[-1].node));
        if (func_name) {
            Type* return_type = get_base_type_from_specifiers((yyvsp[-2].node));
            Type* func_type = create_function_type(return_type, NULL);
            insert_symbol(func_name, func_type, SYM_FUNCTION);
            free(func_name);
        }
        (yyval.node) = create_node("FunctionDefinition", NULL, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
      }
#line 1654 "parser.tab.c"
    break;

  case 7: /* declaration: declaration_specifiers init_declarator_list ';'  */
#line 125 "parser.y"
      { 
        // This is now the central point for variable insertion.
        // We have both the type specifiers ($1) and the list of declarators ($2).
        Type* base_type = get_base_type_from_specifiers((yyvsp[-2].node));
        ASTNode* declarator_list = (yyvsp[-1].node);
        // The list is built backwards, so we traverse it to insert symbols.
        while(declarator_list) {
            ASTNode* declarator = declarator_list->children[0];
            char* name = get_declarator_name(declarator);
            if (name) {
                insert_symbol(name, base_type, is_typedef_declaration ? SYM_TYPENAME : SYM_VARIABLE);
                free(name);
            }
            if (declarator_list->num_children > 1) {
                declarator_list = declarator_list->children[1];
            } else {
                break;
            }
        }
        // Note: We don't free base_type here because multiple variables might share it.
        (yyval.node) = create_node("Declaration", NULL, 2, (yyvsp[-2].node), (yyvsp[-1].node));
      }
#line 1681 "parser.tab.c"
    break;

  case 8: /* declaration_specifiers: storage_class_specifier  */
#line 150 "parser.y"
                              { (yyval.node) = (yyvsp[0].node); }
#line 1687 "parser.tab.c"
    break;

  case 9: /* declaration_specifiers: type_specifier_node  */
#line 151 "parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 1693 "parser.tab.c"
    break;

  case 10: /* declaration_specifiers: type_qualifier  */
#line 152 "parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 1699 "parser.tab.c"
    break;

  case 11: /* declaration_specifiers: storage_class_specifier declaration_specifiers  */
#line 153 "parser.y"
                                                     { is_typedef_declaration = 1; (yyval.node) = create_node("DeclarationSpecifiers", NULL, 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1705 "parser.tab.c"
    break;

  case 12: /* declaration_specifiers: type_specifier_node declaration_specifiers  */
#line 154 "parser.y"
                                                 { is_typedef_declaration = 0; (yyval.node) = create_node("DeclarationSpecifiers", NULL, 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1711 "parser.tab.c"
    break;

  case 13: /* declaration_specifiers: type_qualifier declaration_specifiers  */
#line 155 "parser.y"
                                            { (yyval.node) = create_node("DeclarationSpecifiers", NULL, 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1717 "parser.tab.c"
    break;

  case 14: /* storage_class_specifier: KEYWORD_TYPEDEF  */
#line 159 "parser.y"
                      { (yyval.node) = create_node("StorageClassSpecifier", "typedef", 0); }
#line 1723 "parser.tab.c"
    break;

  case 15: /* type_specifier: KEYWORD_VOID  */
#line 163 "parser.y"
                     { (yyval.str) = (yyvsp[0].str); }
#line 1729 "parser.tab.c"
    break;

  case 16: /* type_specifier: KEYWORD_CHAR  */
#line 164 "parser.y"
                     { (yyval.str) = (yyvsp[0].str); }
#line 1735 "parser.tab.c"
    break;

  case 17: /* type_specifier: KEYWORD_SHORT  */
#line 165 "parser.y"
                     { (yyval.str) = (yyvsp[0].str); }
#line 1741 "parser.tab.c"
    break;

  case 18: /* type_specifier: KEYWORD_INT  */
#line 166 "parser.y"
                     { (yyval.str) = (yyvsp[0].str); }
#line 1747 "parser.tab.c"
    break;

  case 19: /* type_specifier: KEYWORD_LONG  */
#line 167 "parser.y"
                     { (yyval.str) = (yyvsp[0].str); }
#line 1753 "parser.tab.c"
    break;

  case 20: /* type_specifier: KEYWORD_FLOAT  */
#line 168 "parser.y"
                     { (yyval.str) = (yyvsp[0].str); }
#line 1759 "parser.tab.c"
    break;

  case 21: /* type_specifier: KEYWORD_DOUBLE  */
#line 169 "parser.y"
                     { (yyval.str) = (yyvsp[0].str); }
#line 1765 "parser.tab.c"
    break;

  case 22: /* type_specifier: KEYWORD_SIGNED  */
#line 170 "parser.y"
                     { (yyval.str) = (yyvsp[0].str); }
#line 1771 "parser.tab.c"
    break;

  case 23: /* type_specifier: KEYWORD_UNSIGNED  */
#line 171 "parser.y"
                       { (yyval.str) = (yyvsp[0].str); }
#line 1777 "parser.tab.c"
    break;

  case 24: /* type_specifier_node: type_specifier  */
#line 175 "parser.y"
                     { (yyval.node) = create_node("TypeSpecifier", (yyvsp[0].str), 0); }
#line 1783 "parser.tab.c"
    break;

  case 25: /* type_specifier_node: TYPENAME  */
#line 176 "parser.y"
               { (yyval.node) = create_node("TypeName", (yyvsp[0].str), 0); }
#line 1789 "parser.tab.c"
    break;

  case 26: /* type_specifier_node: struct_or_union_specifier  */
#line 177 "parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1795 "parser.tab.c"
    break;

  case 27: /* type_specifier_node: enum_specifier  */
#line 178 "parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 1801 "parser.tab.c"
    break;

  case 28: /* init_declarator_list: init_declarator  */
#line 182 "parser.y"
                      { (yyval.node) = create_node("InitDeclaratorList", NULL, 1, (yyvsp[0].node)); }
#line 1807 "parser.tab.c"
    break;

  case 29: /* init_declarator_list: init_declarator_list ',' init_declarator  */
#line 183 "parser.y"
                                               { (yyval.node) = create_node("InitDeclaratorList", NULL, 2, (yyvsp[0].node), (yyvsp[-2].node)); }
#line 1813 "parser.tab.c"
    break;

  case 30: /* init_declarator: declarator  */
#line 187 "parser.y"
                 {
        // Simply pass the declarator up. Insertion is handled in the 'declaration' rule.
        (yyval.node) = (yyvsp[0].node);
    }
#line 1822 "parser.tab.c"
    break;

  case 31: /* init_declarator: declarator '=' initializer  */
#line 191 "parser.y"
                                 { (yyval.node) = create_node("InitDeclarator", "=", 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1828 "parser.tab.c"
    break;

  case 32: /* declarator: pointer direct_declarator  */
#line 195 "parser.y"
                                { (yyval.node) = create_node("PointerDeclarator", NULL, 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1834 "parser.tab.c"
    break;

  case 33: /* declarator: direct_declarator  */
#line 196 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1840 "parser.tab.c"
    break;

  case 34: /* type_name: specifier_qualifier_list  */
#line 200 "parser.y"
                               { (yyval.node) = create_node("TypeName", NULL, 1, (yyvsp[0].node)); }
#line 1846 "parser.tab.c"
    break;

  case 35: /* type_name: specifier_qualifier_list abstract_declarator  */
#line 201 "parser.y"
                                                   { (yyval.node) = create_node("TypeName", NULL, 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1852 "parser.tab.c"
    break;

  case 36: /* abstract_declarator: pointer  */
#line 205 "parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 1858 "parser.tab.c"
    break;

  case 37: /* abstract_declarator: direct_abstract_declarator  */
#line 206 "parser.y"
                                 { (yyval.node) = (yyvsp[0].node); }
#line 1864 "parser.tab.c"
    break;

  case 38: /* abstract_declarator: pointer direct_abstract_declarator  */
#line 207 "parser.y"
                                         { (yyval.node) = create_node("PointerAbstractDeclarator", NULL, 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1870 "parser.tab.c"
    break;

  case 39: /* direct_abstract_declarator: '(' abstract_declarator ')'  */
#line 211 "parser.y"
                                  { (yyval.node) = create_node("ParenthesizedAbstractDeclarator", NULL, 1, (yyvsp[-1].node)); }
#line 1876 "parser.tab.c"
    break;

  case 40: /* direct_abstract_declarator: direct_abstract_declarator '[' assignment_expression_opt ']'  */
#line 212 "parser.y"
                                                                   { (yyval.node) = create_node("AbstractArraySuffix", NULL, 2, (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 1882 "parser.tab.c"
    break;

  case 41: /* direct_abstract_declarator: '[' assignment_expression_opt ']'  */
#line 213 "parser.y"
                                        { (yyval.node) = create_node("AbstractArraySuffix", NULL, 1, (yyvsp[-1].node)); }
#line 1888 "parser.tab.c"
    break;

  case 42: /* direct_abstract_declarator: direct_abstract_declarator '(' parameter_type_list_opt ')'  */
#line 214 "parser.y"
                                                                 { (yyval.node) = create_node("AbstractFunctionSuffix", NULL, 2, (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 1894 "parser.tab.c"
    break;

  case 43: /* direct_abstract_declarator: '(' parameter_type_list_opt ')'  */
#line 215 "parser.y"
                                      { (yyval.node) = create_node("AbstractFunctionSuffix", NULL, 1, (yyvsp[-1].node)); }
#line 1900 "parser.tab.c"
    break;

  case 44: /* assignment_expression_opt: assignment_expression  */
#line 219 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 1906 "parser.tab.c"
    break;

  case 45: /* assignment_expression_opt: %empty  */
#line 220 "parser.y"
                  { (yyval.node) = create_node("EmptyExpression", NULL, 0); }
#line 1912 "parser.tab.c"
    break;

  case 46: /* parameter_type_list_opt: parameter_type_list  */
#line 224 "parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 1918 "parser.tab.c"
    break;

  case 47: /* parameter_type_list_opt: %empty  */
#line 225 "parser.y"
                  { (yyval.node) = create_node("EmptyParameterList", NULL, 0); }
#line 1924 "parser.tab.c"
    break;

  case 48: /* unary_expression: postfix_expression  */
#line 232 "parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 1930 "parser.tab.c"
    break;

  case 49: /* unary_expression: OP_INCREMENT unary_expression  */
#line 233 "parser.y"
                                    { (yyval.node) = create_node("PrefixIncrement", "++", 1, (yyvsp[0].node)); }
#line 1936 "parser.tab.c"
    break;

  case 50: /* unary_expression: OP_DECREMENT unary_expression  */
#line 234 "parser.y"
                                    { (yyval.node) = create_node("PrefixDecrement", "--", 1, (yyvsp[0].node)); }
#line 1942 "parser.tab.c"
    break;

  case 51: /* unary_expression: unary_operator cast_expression  */
#line 235 "parser.y"
                                     { (yyval.node) = create_node("UnaryOp", (yyvsp[-1].str), 1, (yyvsp[0].node)); }
#line 1948 "parser.tab.c"
    break;

  case 52: /* unary_expression: KEYWORD_SIZEOF unary_expression  */
#line 236 "parser.y"
                                      { (yyval.node) = create_node("SizeofUnaryExpr", NULL, 1, (yyvsp[0].node)); }
#line 1954 "parser.tab.c"
    break;

  case 53: /* unary_expression: KEYWORD_SIZEOF '(' type_name ')'  */
#line 237 "parser.y"
                                       { (yyval.node) = create_node("SizeofTypeExpr", NULL, 1, (yyvsp[-1].node)); }
#line 1960 "parser.tab.c"
    break;

  case 54: /* pointer: '*'  */
#line 246 "parser.y"
          { (yyval.node) = create_node("Pointer", "*", 0); }
#line 1966 "parser.tab.c"
    break;

  case 55: /* pointer: '*' pointer  */
#line 247 "parser.y"
                  { (yyval.node) = create_node("Pointer", "*", 1, (yyvsp[0].node)); }
#line 1972 "parser.tab.c"
    break;

  case 56: /* struct_or_union_specifier: struct_or_union IDENTIFIER '{' struct_declaration_list '}'  */
#line 252 "parser.y"
        { (yyval.node) = create_node("StructSpecifier", (yyvsp[-3].str), 2, (yyvsp[-4].node), (yyvsp[-1].node)); }
#line 1978 "parser.tab.c"
    break;

  case 57: /* struct_or_union_specifier: struct_or_union '{' struct_declaration_list '}'  */
#line 254 "parser.y"
        { (yyval.node) = create_node("StructSpecifier", "anonymous", 2, (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 1984 "parser.tab.c"
    break;

  case 58: /* struct_or_union_specifier: struct_or_union IDENTIFIER  */
#line 256 "parser.y"
        { (yyval.node) = create_node("StructSpecifier", (yyvsp[0].str), 1, (yyvsp[-1].node)); }
#line 1990 "parser.tab.c"
    break;

  case 59: /* struct_or_union: KEYWORD_STRUCT  */
#line 260 "parser.y"
                     { (yyval.node) = create_node("StructToken", "struct", 0); }
#line 1996 "parser.tab.c"
    break;

  case 60: /* struct_or_union: KEYWORD_UNION  */
#line 261 "parser.y"
                     { (yyval.node) = create_node("UnionToken", "union", 0); }
#line 2002 "parser.tab.c"
    break;

  case 61: /* struct_declaration_list: struct_declaration  */
#line 265 "parser.y"
                         { (yyval.node) = create_node("StructDeclarationList", NULL, 1, (yyvsp[0].node)); }
#line 2008 "parser.tab.c"
    break;

  case 62: /* struct_declaration_list: struct_declaration_list struct_declaration  */
#line 266 "parser.y"
                                                 { (yyval.node) = create_node("StructDeclarationList", NULL, 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2014 "parser.tab.c"
    break;

  case 63: /* struct_declaration: specifier_qualifier_list struct_declarator_list ';'  */
#line 270 "parser.y"
                                                          { (yyval.node) = create_node("StructDeclaration", NULL, 2, (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 2020 "parser.tab.c"
    break;

  case 64: /* specifier_qualifier_list: type_specifier_node  */
#line 274 "parser.y"
                          { (yyval.node) = create_node("SpecifierQualifierList", NULL, 1, (yyvsp[0].node)); }
#line 2026 "parser.tab.c"
    break;

  case 65: /* specifier_qualifier_list: type_qualifier  */
#line 275 "parser.y"
                     { (yyval.node) = create_node("SpecifierQualifierList", NULL, 1, (yyvsp[0].node)); }
#line 2032 "parser.tab.c"
    break;

  case 66: /* specifier_qualifier_list: type_specifier_node specifier_qualifier_list  */
#line 276 "parser.y"
                                                   { (yyval.node) = create_node("SpecifierQualifierList", NULL, 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2038 "parser.tab.c"
    break;

  case 67: /* specifier_qualifier_list: type_qualifier specifier_qualifier_list  */
#line 277 "parser.y"
                                              { (yyval.node) = create_node("SpecifierQualifierList", NULL, 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2044 "parser.tab.c"
    break;

  case 68: /* struct_declarator_list: struct_declarator  */
#line 281 "parser.y"
                        { (yyval.node) = create_node("StructDeclaratorList", NULL, 1, (yyvsp[0].node)); }
#line 2050 "parser.tab.c"
    break;

  case 69: /* struct_declarator_list: struct_declarator_list ',' struct_declarator  */
#line 282 "parser.y"
                                                   { (yyval.node) = create_node("StructDeclaratorList", NULL, 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2056 "parser.tab.c"
    break;

  case 70: /* struct_declarator: declarator  */
#line 286 "parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 2062 "parser.tab.c"
    break;

  case 71: /* type_qualifier: KEYWORD_CONST  */
#line 290 "parser.y"
                    { (yyval.node) = create_node("TypeQualifier", "const", 0); }
#line 2068 "parser.tab.c"
    break;

  case 72: /* type_qualifier: KEYWORD_VOLATILE  */
#line 291 "parser.y"
                       { (yyval.node) = create_node("TypeQualifier", "volatile", 0); }
#line 2074 "parser.tab.c"
    break;

  case 73: /* type_qualifier: KEYWORD_RESTRICT  */
#line 292 "parser.y"
                       { (yyval.node) = create_node("TypeQualifier", "restrict", 0); }
#line 2080 "parser.tab.c"
    break;

  case 74: /* enum_specifier: KEYWORD_ENUM IDENTIFIER '{' enumerator_list '}'  */
#line 296 "parser.y"
                                                      { (yyval.node) = create_node("EnumSpecifier", (yyvsp[-3].str), 1, (yyvsp[-1].node)); }
#line 2086 "parser.tab.c"
    break;

  case 75: /* enum_specifier: KEYWORD_ENUM '{' enumerator_list '}'  */
#line 297 "parser.y"
                                           { (yyval.node) = create_node("EnumSpecifier", "anonymous", 1, (yyvsp[-1].node)); }
#line 2092 "parser.tab.c"
    break;

  case 76: /* enum_specifier: KEYWORD_ENUM IDENTIFIER '{' enumerator_list ',' '}'  */
#line 298 "parser.y"
                                                          { (yyval.node) = create_node("EnumSpecifier", (yyvsp[-4].str), 1, (yyvsp[-2].node)); }
#line 2098 "parser.tab.c"
    break;

  case 77: /* enum_specifier: KEYWORD_ENUM '{' enumerator_list ',' '}'  */
#line 299 "parser.y"
                                               { (yyval.node) = create_node("EnumSpecifier", "anonymous", 1, (yyvsp[-2].node)); }
#line 2104 "parser.tab.c"
    break;

  case 78: /* enum_specifier: KEYWORD_ENUM IDENTIFIER  */
#line 300 "parser.y"
                              { (yyval.node) = create_node("EnumSpecifier", (yyvsp[0].str), 0); }
#line 2110 "parser.tab.c"
    break;

  case 79: /* enumerator_list: enumerator  */
#line 304 "parser.y"
                 { (yyval.node) = create_node("EnumeratorList", NULL, 1, (yyvsp[0].node)); }
#line 2116 "parser.tab.c"
    break;

  case 80: /* enumerator_list: enumerator_list ',' enumerator  */
#line 305 "parser.y"
                                     { (yyval.node) = create_node("EnumeratorList", NULL, 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2122 "parser.tab.c"
    break;

  case 81: /* enumerator: IDENTIFIER  */
#line 309 "parser.y"
                 { (yyval.node) = create_node("Enumerator", (yyvsp[0].str), 0); }
#line 2128 "parser.tab.c"
    break;

  case 82: /* enumerator: IDENTIFIER '=' conditional_expression  */
#line 310 "parser.y"
                                            { (yyval.node) = create_node("Enumerator", (yyvsp[-2].str), 1, (yyvsp[0].node)); }
#line 2134 "parser.tab.c"
    break;

  case 83: /* initializer: assignment_expression  */
#line 314 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2140 "parser.tab.c"
    break;

  case 84: /* initializer: '{' initializer_list '}'  */
#line 315 "parser.y"
                               { (yyval.node) = create_node("InitializerList", NULL, 1, (yyvsp[-1].node)); }
#line 2146 "parser.tab.c"
    break;

  case 85: /* initializer_list: assignment_expression  */
#line 319 "parser.y"
                            { (yyval.node) = create_node("InitValues", NULL, 1, (yyvsp[0].node)); }
#line 2152 "parser.tab.c"
    break;

  case 86: /* initializer_list: initializer_list ',' assignment_expression  */
#line 320 "parser.y"
                                                 { (yyval.node) = create_node("InitValues", NULL, 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2158 "parser.tab.c"
    break;

  case 87: /* direct_declarator: IDENTIFIER  */
#line 324 "parser.y"
                 { (yyval.node) = create_node("Identifier", (yyvsp[0].str), 0); }
#line 2164 "parser.tab.c"
    break;

  case 88: /* direct_declarator: '(' declarator ')'  */
#line 325 "parser.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 2170 "parser.tab.c"
    break;

  case 89: /* direct_declarator: direct_declarator '(' parameter_type_list ')'  */
#line 326 "parser.y"
                                                    { (yyval.node) = create_node("FunctionDeclarator", NULL, 2, (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 2176 "parser.tab.c"
    break;

  case 90: /* direct_declarator: direct_declarator '(' ')'  */
#line 327 "parser.y"
                                { (yyval.node) = create_node("FunctionDeclarator", "()", 1, (yyvsp[-2].node)); }
#line 2182 "parser.tab.c"
    break;

  case 91: /* direct_declarator: direct_declarator '[' assignment_expression ']'  */
#line 328 "parser.y"
                                                      { (yyval.node) = create_node("ArrayDeclarator", NULL, 2, (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 2188 "parser.tab.c"
    break;

  case 92: /* direct_declarator: direct_declarator '[' ']'  */
#line 329 "parser.y"
                                { (yyval.node) = create_node("ArrayDeclarator", "unspecified_size", 1, (yyvsp[-2].node)); }
#line 2194 "parser.tab.c"
    break;

  case 93: /* parameter_type_list: parameter_list  */
#line 333 "parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2200 "parser.tab.c"
    break;

  case 94: /* parameter_list: parameter_declaration  */
#line 337 "parser.y"
                            { (yyval.node) = create_node("ParameterList", NULL, 1, (yyvsp[0].node)); }
#line 2206 "parser.tab.c"
    break;

  case 95: /* parameter_list: parameter_list ',' parameter_declaration  */
#line 338 "parser.y"
                                               { (yyval.node) = create_node("ParameterList", NULL, 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2212 "parser.tab.c"
    break;

  case 96: /* parameter_declaration: declaration_specifiers declarator  */
#line 342 "parser.y"
                                        { (yyval.node) = create_node("ParameterDeclaration", NULL, 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2218 "parser.tab.c"
    break;

  case 97: /* parameter_declaration: declaration_specifiers  */
#line 343 "parser.y"
                             { (yyval.node) = create_node("ParameterDeclaration", NULL, 1, (yyvsp[0].node)); }
#line 2224 "parser.tab.c"
    break;

  case 98: /* compound_statement: '{' '}'  */
#line 347 "parser.y"
              { 
        (yyval.node) = create_node("CompoundStatement", "{}", 0); 
      }
#line 2232 "parser.tab.c"
    break;

  case 99: /* compound_statement: '{' block_item_list '}'  */
#line 350 "parser.y"
                              { 
        (yyval.node) = create_node("CompoundStatement", NULL, 1, (yyvsp[-1].node)); 
      }
#line 2240 "parser.tab.c"
    break;

  case 100: /* block_item_list: block_item  */
#line 356 "parser.y"
                 { (yyval.node) = create_node("BlockItemList", NULL, 1, (yyvsp[0].node)); }
#line 2246 "parser.tab.c"
    break;

  case 101: /* block_item_list: block_item_list block_item  */
#line 357 "parser.y"
                                 { (yyval.node) =  (yyvsp[0].node); }
#line 2252 "parser.tab.c"
    break;

  case 102: /* block_item: declaration  */
#line 361 "parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 2258 "parser.tab.c"
    break;

  case 103: /* block_item: statement  */
#line 362 "parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 2264 "parser.tab.c"
    break;

  case 104: /* statement: expression_statement  */
#line 366 "parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2270 "parser.tab.c"
    break;

  case 105: /* statement: compound_statement  */
#line 367 "parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2276 "parser.tab.c"
    break;

  case 106: /* statement: selection_statement  */
#line 368 "parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2282 "parser.tab.c"
    break;

  case 107: /* statement: iteration_statement  */
#line 369 "parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2288 "parser.tab.c"
    break;

  case 108: /* statement: jump_statement  */
#line 370 "parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2294 "parser.tab.c"
    break;

  case 109: /* statement: labeled_statement  */
#line 371 "parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2300 "parser.tab.c"
    break;

  case 110: /* expression_statement: ';'  */
#line 375 "parser.y"
          { (yyval.node) = create_node("EmptyStatement", ";", 0); }
#line 2306 "parser.tab.c"
    break;

  case 111: /* expression_statement: expression ';'  */
#line 376 "parser.y"
                     { (yyval.node) = create_node("ExpressionStatement", NULL, 1, (yyvsp[-1].node)); }
#line 2312 "parser.tab.c"
    break;

  case 112: /* expression_opt: expression  */
#line 380 "parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 2318 "parser.tab.c"
    break;

  case 113: /* expression_opt: %empty  */
#line 381 "parser.y"
                  { (yyval.node) = create_node("EmptyExpression", NULL, 0); }
#line 2324 "parser.tab.c"
    break;

  case 114: /* iteration_statement: KEYWORD_WHILE '(' expression ')' statement  */
#line 385 "parser.y"
                                                 { (yyval.node) = create_node("WhileStatement", NULL, 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2330 "parser.tab.c"
    break;

  case 115: /* iteration_statement: KEYWORD_DO statement KEYWORD_WHILE '(' expression ')' ';'  */
#line 386 "parser.y"
                                                                { (yyval.node) = create_node("DoWhileStatement", NULL, 2, (yyvsp[-5].node), (yyvsp[-2].node)); }
#line 2336 "parser.tab.c"
    break;

  case 116: /* iteration_statement: KEYWORD_FOR '(' expression_opt ';' expression_opt ';' expression_opt ')' statement  */
#line 387 "parser.y"
                                                                                         { (yyval.node) = create_node("ForStatement", NULL, 4, (yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2342 "parser.tab.c"
    break;

  case 117: /* iteration_statement: KEYWORD_FOR '(' declaration expression_opt ';' expression_opt ')' statement  */
#line 388 "parser.y"
                                                                                  { (yyval.node) = create_node("ForDeclStatement", NULL, 4, (yyvsp[-5].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2348 "parser.tab.c"
    break;

  case 118: /* selection_statement: KEYWORD_IF '(' expression ')' statement  */
#line 392 "parser.y"
                                               { (yyval.node) = create_node("IfStatement", NULL, 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2354 "parser.tab.c"
    break;

  case 119: /* selection_statement: KEYWORD_IF '(' expression ')' statement KEYWORD_ELSE statement  */
#line 393 "parser.y"
                                                                     { (yyval.node) = create_node("IfElseStatement", NULL, 3, (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2360 "parser.tab.c"
    break;

  case 120: /* selection_statement: KEYWORD_SWITCH '(' expression ')' statement  */
#line 394 "parser.y"
                                                  { (yyval.node) = create_node("SwitchStatement", NULL, 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2366 "parser.tab.c"
    break;

  case 121: /* labeled_statement: IDENTIFIER ':' statement  */
#line 398 "parser.y"
                               { (yyval.node) = create_node("LabeledStatement", (yyvsp[-2].str), 1, (yyvsp[0].node)); }
#line 2372 "parser.tab.c"
    break;

  case 122: /* labeled_statement: KEYWORD_CASE conditional_expression ':' statement  */
#line 399 "parser.y"
                                                        { (yyval.node) = create_node("CaseStatement", NULL, 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2378 "parser.tab.c"
    break;

  case 123: /* labeled_statement: KEYWORD_DEFAULT ':' statement  */
#line 400 "parser.y"
                                    { (yyval.node) = create_node("DefaultStatement", NULL, 1, (yyvsp[0].node)); }
#line 2384 "parser.tab.c"
    break;

  case 124: /* jump_statement: KEYWORD_RETURN ';'  */
#line 404 "parser.y"
                         { (yyval.node) = create_node("Return", NULL, 0); }
#line 2390 "parser.tab.c"
    break;

  case 125: /* jump_statement: KEYWORD_RETURN expression ';'  */
#line 405 "parser.y"
                                    { (yyval.node) = create_node("Return", NULL, 1, (yyvsp[-1].node)); }
#line 2396 "parser.tab.c"
    break;

  case 126: /* jump_statement: KEYWORD_BREAK ';'  */
#line 406 "parser.y"
                        { (yyval.node) = create_node("BreakStatement", NULL, 0); }
#line 2402 "parser.tab.c"
    break;

  case 127: /* jump_statement: KEYWORD_CONTINUE ';'  */
#line 407 "parser.y"
                           { (yyval.node) = create_node("ContinueStatement", NULL, 0); }
#line 2408 "parser.tab.c"
    break;

  case 128: /* expression: assignment_expression  */
#line 411 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2414 "parser.tab.c"
    break;

  case 129: /* expression: expression ',' assignment_expression  */
#line 412 "parser.y"
                                           { (yyval.node) = create_node("BinaryOp", ",", 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2420 "parser.tab.c"
    break;

  case 130: /* assignment_expression: conditional_expression  */
#line 416 "parser.y"
                             { (yyval.node) = (yyvsp[0].node); }
#line 2426 "parser.tab.c"
    break;

  case 131: /* assignment_expression: unary_expression assignment_operator assignment_expression  */
#line 417 "parser.y"
                                                                 { (yyval.node) = create_node("Assignment", (yyvsp[-1].str), 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2432 "parser.tab.c"
    break;

  case 132: /* assignment_operator: '='  */
#line 421 "parser.y"
          { (yyval.str) = "="; }
#line 2438 "parser.tab.c"
    break;

  case 133: /* assignment_operator: OP_MUL_ASSIGN  */
#line 421 "parser.y"
                                        { (yyval.str) = "*="; }
#line 2444 "parser.tab.c"
    break;

  case 134: /* assignment_operator: OP_DIV_ASSIGN  */
#line 421 "parser.y"
                                                                       { (yyval.str) = "/="; }
#line 2450 "parser.tab.c"
    break;

  case 135: /* assignment_operator: OP_MOD_ASSIGN  */
#line 422 "parser.y"
                    { (yyval.str) = "%="; }
#line 2456 "parser.tab.c"
    break;

  case 136: /* assignment_operator: OP_ADD_ASSIGN  */
#line 422 "parser.y"
                                                   { (yyval.str) = "+="; }
#line 2462 "parser.tab.c"
    break;

  case 137: /* assignment_operator: OP_SUB_ASSIGN  */
#line 422 "parser.y"
                                                                                  { (yyval.str) = "-="; }
#line 2468 "parser.tab.c"
    break;

  case 138: /* conditional_expression: logical_or_expression  */
#line 426 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2474 "parser.tab.c"
    break;

  case 139: /* logical_or_expression: logical_and_expression  */
#line 430 "parser.y"
                             { (yyval.node) = (yyvsp[0].node); }
#line 2480 "parser.tab.c"
    break;

  case 140: /* logical_or_expression: logical_or_expression OP_OR logical_and_expression  */
#line 431 "parser.y"
                                                         { (yyval.node) = create_node("BinaryOp", "||", 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2486 "parser.tab.c"
    break;

  case 141: /* logical_and_expression: inclusive_or_expression  */
#line 435 "parser.y"
                              { (yyval.node) = (yyvsp[0].node); }
#line 2492 "parser.tab.c"
    break;

  case 142: /* logical_and_expression: logical_and_expression OP_AND inclusive_or_expression  */
#line 436 "parser.y"
                                                            { (yyval.node) = create_node("BinaryOp", "&&", 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2498 "parser.tab.c"
    break;

  case 143: /* inclusive_or_expression: exclusive_or_expression  */
#line 440 "parser.y"
                              { (yyval.node) = (yyvsp[0].node); }
#line 2504 "parser.tab.c"
    break;

  case 144: /* inclusive_or_expression: inclusive_or_expression '|' exclusive_or_expression  */
#line 441 "parser.y"
                                                          { (yyval.node) = create_node("BinaryOp", "|", 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2510 "parser.tab.c"
    break;

  case 145: /* exclusive_or_expression: and_expression  */
#line 445 "parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2516 "parser.tab.c"
    break;

  case 146: /* exclusive_or_expression: exclusive_or_expression '^' and_expression  */
#line 446 "parser.y"
                                                 { (yyval.node) = create_node("BinaryOp", "^", 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2522 "parser.tab.c"
    break;

  case 147: /* and_expression: equality_expression  */
#line 450 "parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 2528 "parser.tab.c"
    break;

  case 148: /* and_expression: and_expression '&' equality_expression  */
#line 451 "parser.y"
                                             { (yyval.node) = create_node("BinaryOp", "&", 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2534 "parser.tab.c"
    break;

  case 149: /* equality_expression: relational_expression  */
#line 455 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2540 "parser.tab.c"
    break;

  case 150: /* equality_expression: equality_expression OP_EQ relational_expression  */
#line 456 "parser.y"
                                                      { (yyval.node) = create_node("BinaryOp", "==", 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2546 "parser.tab.c"
    break;

  case 151: /* equality_expression: equality_expression OP_NE relational_expression  */
#line 457 "parser.y"
                                                      { (yyval.node) = create_node("BinaryOp", "!=", 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2552 "parser.tab.c"
    break;

  case 152: /* relational_expression: shift_expression  */
#line 461 "parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 2558 "parser.tab.c"
    break;

  case 153: /* relational_expression: relational_expression '<' shift_expression  */
#line 462 "parser.y"
                                                 { (yyval.node) = create_node("BinaryOp", "<", 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2564 "parser.tab.c"
    break;

  case 154: /* relational_expression: relational_expression '>' shift_expression  */
#line 463 "parser.y"
                                                 { (yyval.node) = create_node("BinaryOp", ">", 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2570 "parser.tab.c"
    break;

  case 155: /* relational_expression: relational_expression OP_LE shift_expression  */
#line 464 "parser.y"
                                                   { (yyval.node) = create_node("BinaryOp", "<=", 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2576 "parser.tab.c"
    break;

  case 156: /* relational_expression: relational_expression OP_GE shift_expression  */
#line 465 "parser.y"
                                                   { (yyval.node) = create_node("BinaryOp", ">=", 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2582 "parser.tab.c"
    break;

  case 157: /* shift_expression: additive_expression  */
#line 469 "parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 2588 "parser.tab.c"
    break;

  case 158: /* shift_expression: shift_expression OP_SHIFT_LEFT additive_expression  */
#line 470 "parser.y"
                                                         { (yyval.node) = create_node("BinaryOp", "<<", 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2594 "parser.tab.c"
    break;

  case 159: /* shift_expression: shift_expression OP_SHIFT_RIGHT additive_expression  */
#line 471 "parser.y"
                                                          { (yyval.node) = create_node("BinaryOp", ">>", 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2600 "parser.tab.c"
    break;

  case 160: /* additive_expression: multiplicative_expression  */
#line 475 "parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 2606 "parser.tab.c"
    break;

  case 161: /* additive_expression: additive_expression '+' multiplicative_expression  */
#line 476 "parser.y"
                                                        { (yyval.node) = create_node("BinaryOp", "+", 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2612 "parser.tab.c"
    break;

  case 162: /* additive_expression: additive_expression '-' multiplicative_expression  */
#line 477 "parser.y"
                                                        { (yyval.node) = create_node("BinaryOp", "-", 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2618 "parser.tab.c"
    break;

  case 163: /* multiplicative_expression: cast_expression  */
#line 481 "parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 2624 "parser.tab.c"
    break;

  case 164: /* multiplicative_expression: multiplicative_expression '*' cast_expression  */
#line 482 "parser.y"
                                                    { (yyval.node) = create_node("BinaryOp", "*", 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2630 "parser.tab.c"
    break;

  case 165: /* multiplicative_expression: multiplicative_expression '/' cast_expression  */
#line 483 "parser.y"
                                                    { (yyval.node) = create_node("BinaryOp", "/", 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2636 "parser.tab.c"
    break;

  case 166: /* multiplicative_expression: multiplicative_expression '%' cast_expression  */
#line 484 "parser.y"
                                                    { (yyval.node) = create_node("BinaryOp", "%", 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2642 "parser.tab.c"
    break;

  case 167: /* cast_expression: unary_expression  */
#line 488 "parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 2648 "parser.tab.c"
    break;

  case 168: /* unary_operator: '&'  */
#line 492 "parser.y"
          { (yyval.str) = "&"; }
#line 2654 "parser.tab.c"
    break;

  case 169: /* unary_operator: '*'  */
#line 492 "parser.y"
                              { (yyval.str) = "*"; }
#line 2660 "parser.tab.c"
    break;

  case 170: /* unary_operator: '+'  */
#line 492 "parser.y"
                                                  { (yyval.str) = "+"; }
#line 2666 "parser.tab.c"
    break;

  case 171: /* unary_operator: '-'  */
#line 492 "parser.y"
                                                                      { (yyval.str) = "-"; }
#line 2672 "parser.tab.c"
    break;

  case 172: /* unary_operator: '~'  */
#line 492 "parser.y"
                                                                                          { (yyval.str) = "~"; }
#line 2678 "parser.tab.c"
    break;

  case 173: /* unary_operator: '!'  */
#line 492 "parser.y"
                                                                                                              { (yyval.str) = "!"; }
#line 2684 "parser.tab.c"
    break;

  case 174: /* postfix_expression: primary_expression  */
#line 496 "parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 2690 "parser.tab.c"
    break;

  case 175: /* postfix_expression: postfix_expression '(' ')'  */
#line 497 "parser.y"
                                 { (yyval.node) = create_node("FunctionCall", NULL, 1, (yyvsp[-2].node)); }
#line 2696 "parser.tab.c"
    break;

  case 176: /* postfix_expression: postfix_expression '(' argument_expression_list ')'  */
#line 498 "parser.y"
                                                          { (yyval.node) = create_node("FunctionCall", NULL, 2, (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 2702 "parser.tab.c"
    break;

  case 177: /* postfix_expression: postfix_expression OP_INCREMENT  */
#line 499 "parser.y"
                                      { (yyval.node) = create_node("PostfixIncrement", "++", 1, (yyvsp[-1].node)); }
#line 2708 "parser.tab.c"
    break;

  case 178: /* postfix_expression: postfix_expression OP_DECREMENT  */
#line 500 "parser.y"
                                      { (yyval.node) = create_node("PostfixDecrement", "--", 1, (yyvsp[-1].node)); }
#line 2714 "parser.tab.c"
    break;

  case 179: /* postfix_expression: postfix_expression '[' expression ']'  */
#line 501 "parser.y"
                                            { (yyval.node) = create_node("ArrayAccess", NULL, 2, (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 2720 "parser.tab.c"
    break;

  case 180: /* argument_expression_list: assignment_expression  */
#line 505 "parser.y"
                            { (yyval.node) = create_node("ArgumentList", NULL, 1, (yyvsp[0].node)); }
#line 2726 "parser.tab.c"
    break;

  case 181: /* argument_expression_list: argument_expression_list ',' assignment_expression  */
#line 506 "parser.y"
                                                         { (yyval.node) = create_node("ArgumentList", NULL, 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2732 "parser.tab.c"
    break;

  case 182: /* primary_expression: IDENTIFIER  */
#line 510 "parser.y"
                 { (yyval.node) = create_node("Identifier", (yyvsp[0].str), 0); }
#line 2738 "parser.tab.c"
    break;

  case 183: /* primary_expression: INT_CONST  */
#line 511 "parser.y"
                { (yyval.node) = create_node("IntConstant", (yyvsp[0].str), 0); }
#line 2744 "parser.tab.c"
    break;

  case 184: /* primary_expression: FLOAT_CONST  */
#line 512 "parser.y"
                  { (yyval.node) = create_node("FloatConstant", (yyvsp[0].str), 0); }
#line 2750 "parser.tab.c"
    break;

  case 185: /* primary_expression: CHAR_CONST  */
#line 513 "parser.y"
                 { (yyval.node) = create_node("CharConstant", (yyvsp[0].str), 0); }
#line 2756 "parser.tab.c"
    break;

  case 186: /* primary_expression: STRING_LITERAL  */
#line 514 "parser.y"
                     { (yyval.node) = create_node("StringLiteral", (yyvsp[0].str), 0); }
#line 2762 "parser.tab.c"
    break;

  case 187: /* primary_expression: '(' expression ')'  */
#line 515 "parser.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 2768 "parser.tab.c"
    break;


#line 2772 "parser.tab.c"

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

#line 520 "parser.y"


/* C Code Section */
#include <stdarg.h>


/**
 * @brief Extracts the base type name from a declaration_specifiers AST node.
 * This is a simplified implementation and assumes the first type specifier is the primary one.
 * e.g., "unsigned int" will return "int". A more robust implementation would combine them.
 */
Type* get_base_type_from_specifiers(ASTNode* specifiers_node) {
    if (!specifiers_node) return create_base_type("int"); // Default to int

    // Traverse the list of specifiers to find a type specifier
    ASTNode* current = specifiers_node;
    while(current) {
        if (strcmp(current->node_type, "TypeSpecifier") == 0) {
            return create_base_type(current->value);
        }
        // If it's a list, check the first child, then move to the next
        if (current->num_children > 0) {
             if (strcmp(current->children[0]->node_type, "TypeSpecifier") == 0) {
                return create_base_type(current->children[0]->value);
            }
        }
        if (current->num_children > 1) {
            current = current->children[1];
        } else {
            break;
        }
    }
    return create_base_type("int"); // Default if no type found
}

/**
 * @brief Extracts the function name from a declarator AST node.
 */
char* get_declarator_name(ASTNode* declarator_node) {
    if (!declarator_node) return NULL;

    // Case 1: It's a simple identifier (e.g., "int x;")
    if (strcmp(declarator_node->node_type, "Identifier") == 0) {
        return strdup(declarator_node->value);
    }

    // Case 2: It's a function declarator (e.g., "int main(void)")
    if (strcmp(declarator_node->node_type, "FunctionDeclarator") == 0 && declarator_node->num_children > 0) {
        ASTNode* direct_declarator = declarator_node->children[0];
        if (strcmp(direct_declarator->node_type, "Identifier") == 0) {
            return strdup(direct_declarator->value);
        }
    }

    return NULL;
}

/**
 * @brief Recursively builds a complex type from a base type and a declarator AST node.
 * This handles pointers, arrays, and functions.
 */
Type* build_declarator_type(Type* base_type, ASTNode* declarator_node) {
    if (!declarator_node) return base_type;

    if (strcmp(declarator_node->node_type, "PointerDeclarator") == 0) {
        // This is a pointer. The base_type is what the pointer *points to*.
        // We need to find the innermost declarator to apply the base type,
        // then wrap it with pointer types on the way out.
        Type* inner_type = build_declarator_type(base_type, declarator_node->children[1]);
        
        // Now, wrap with pointer types for each '*' in the 'pointer' part of the AST.
        ASTNode* pointer_part = declarator_node->children[0];
        while (pointer_part) {
            inner_type = create_pointer_type(inner_type);
            pointer_part = (pointer_part->num_children > 0) ? pointer_part->children[0] : NULL;
        }
        return inner_type;
    }
    // Base case: we've reached the identifier. The type is just the base type.
    return base_type;
}

ASTNode* create_node(const char *node_type, const char *value, int num_children, ...) {
    ASTNode *node = (ASTNode*) malloc(sizeof(ASTNode));
    if (!node) {
        yyerror("Out of memory");
        exit(1);
    }
    node->node_type = strdup(node_type);
    node->value = value ? strdup(value) : NULL;
    node->num_children = num_children;
    if (num_children > 0) {
        node->children = (ASTNode**) malloc(num_children * sizeof(ASTNode*));
        va_list ap;
        va_start(ap, num_children);
        for (int i = 0; i < num_children; i++) {
            node->children[i] = va_arg(ap, ASTNode*);
        }
        va_end(ap);
    } else {
        node->children = NULL;
    }
    return node;
}

void print_ast(ASTNode *node, int level) {
    if (!node) return;
    for (int i = 0; i < level; i++) printf("  ");
    printf("%s", node->node_type);
    if (node->value) {
        printf(" (%s)", node->value);
    }
    printf("\n");

    for (int i = 0; i < node->num_children; i++) {
        print_ast(node->children[i], level + 1);
    }
}

void free_ast(ASTNode *node) {
    if (!node) return;
    for (int i = 0; i < node->num_children; i++) {
        free_ast(node->children[i]);
    }
    free(node->node_type);
    if (node->value) free(node->value);
    if (node->children) free(node->children);
    free(node);
}

void yyerror(const char *s) {
    fprintf(stderr, "Parse error on line %d near '%s': %s\n", line_count, yytext, s);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <sourcefile.c>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Cannot open input file");
        return 1;
    }

    yyin = file;
    init_symbol_table(); // Initialize the symbol table
    yyparse();
    fclose(file);

    if (ast_root) {
        printf("\n--- Abstract Syntax Tree ---\n");
        print_ast(ast_root, 0);
        printf("----------------------------\n");
        free_ast(ast_root);
    } else {
        printf("Parsing failed, no AST generated.\n");
    }
    print_symbol_table(); // Print symbol table contents

    return 0;
}
