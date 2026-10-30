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

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
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
    IDENTIFIER = 258,              /* IDENTIFIER  */
    INT_CONST = 259,               /* INT_CONST  */
    FLOAT_CONST = 260,             /* FLOAT_CONST  */
    CHAR_CONST = 261,              /* CHAR_CONST  */
    STRING_LITERAL = 262,          /* STRING_LITERAL  */
    TYPENAME = 263,                /* TYPENAME  */
    KEYWORD_BREAK = 264,           /* KEYWORD_BREAK  */
    KEYWORD_CASE = 265,            /* KEYWORD_CASE  */
    KEYWORD_CONST = 266,           /* KEYWORD_CONST  */
    KEYWORD_CONTINUE = 267,        /* KEYWORD_CONTINUE  */
    KEYWORD_DEFAULT = 268,         /* KEYWORD_DEFAULT  */
    KEYWORD_DO = 269,              /* KEYWORD_DO  */
    KEYWORD_ELSE = 270,            /* KEYWORD_ELSE  */
    KEYWORD_ENUM = 271,            /* KEYWORD_ENUM  */
    KEYWORD_IF = 272,              /* KEYWORD_IF  */
    KEYWORD_RESTRICT = 273,        /* KEYWORD_RESTRICT  */
    KEYWORD_RETURN = 274,          /* KEYWORD_RETURN  */
    KEYWORD_SIZEOF = 275,          /* KEYWORD_SIZEOF  */
    KEYWORD_STRUCT = 276,          /* KEYWORD_STRUCT  */
    KEYWORD_SWITCH = 277,          /* KEYWORD_SWITCH  */
    KEYWORD_TYPEDEF = 278,         /* KEYWORD_TYPEDEF  */
    KEYWORD_UNION = 279,           /* KEYWORD_UNION  */
    KEYWORD_VOLATILE = 280,        /* KEYWORD_VOLATILE  */
    KEYWORD_WHILE = 281,           /* KEYWORD_WHILE  */
    KEYWORD_FOR = 282,             /* KEYWORD_FOR  */
    OP_INCREMENT = 283,            /* OP_INCREMENT  */
    OP_DECREMENT = 284,            /* OP_DECREMENT  */
    OP_SHIFT_LEFT = 285,           /* OP_SHIFT_LEFT  */
    OP_SHIFT_RIGHT = 286,          /* OP_SHIFT_RIGHT  */
    OP_LE = 287,                   /* OP_LE  */
    OP_GE = 288,                   /* OP_GE  */
    OP_EQ = 289,                   /* OP_EQ  */
    OP_NE = 290,                   /* OP_NE  */
    OP_AND = 291,                  /* OP_AND  */
    OP_OR = 292,                   /* OP_OR  */
    OP_ADD_ASSIGN = 293,           /* OP_ADD_ASSIGN  */
    OP_SUB_ASSIGN = 294,           /* OP_SUB_ASSIGN  */
    OP_MUL_ASSIGN = 295,           /* OP_MUL_ASSIGN  */
    OP_DIV_ASSIGN = 296,           /* OP_DIV_ASSIGN  */
    OP_MOD_ASSIGN = 297,           /* OP_MOD_ASSIGN  */
    KEYWORD_CHAR = 298,            /* KEYWORD_CHAR  */
    KEYWORD_DOUBLE = 299,          /* KEYWORD_DOUBLE  */
    KEYWORD_FLOAT = 300,           /* KEYWORD_FLOAT  */
    KEYWORD_INT = 301,             /* KEYWORD_INT  */
    KEYWORD_LONG = 302,            /* KEYWORD_LONG  */
    KEYWORD_SHORT = 303,           /* KEYWORD_SHORT  */
    KEYWORD_SIGNED = 304,          /* KEYWORD_SIGNED  */
    KEYWORD_UNSIGNED = 305,        /* KEYWORD_UNSIGNED  */
    KEYWORD_VOID = 306,            /* KEYWORD_VOID  */
    LOWER_THAN_ELSE = 307          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 40 "parser.y"

    char *str;
    struct ASTNode *node;

#line 121 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
