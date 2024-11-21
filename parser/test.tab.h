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

#ifndef YY_YY_TEST_TAB_H_INCLUDED
# define YY_YY_TEST_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
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
    NUM_INTEIRO = 258,             /* NUM_INTEIRO  */
    NUM_PONTO_FLUTUANTE = 259,     /* NUM_PONTO_FLUTUANTE  */
    NUM_NOTACAO_CIENTIFICA = 260,  /* NUM_NOTACAO_CIENTIFICA  */
    ID = 261,                      /* ID  */
    MAIS = 262,                    /* MAIS  */
    MENOS = 263,                   /* MENOS  */
    VEZES = 264,                   /* VEZES  */
    DOIS_PONTOS = 265,             /* DOIS_PONTOS  */
    VIRGULA = 266,                 /* VIRGULA  */
    MENOR = 267,                   /* MENOR  */
    MAIOR = 268,                   /* MAIOR  */
    IGUAL = 269,                   /* IGUAL  */
    DIFERENTE = 270,               /* DIFERENTE  */
    MENOR_IGUAL = 271,             /* MENOR_IGUAL  */
    DIVIDE = 272,                  /* DIVIDE  */
    MAIOR_IGUAL = 273,             /* MAIOR_IGUAL  */
    E = 274,                       /* E  */
    OU = 275,                      /* OU  */
    NAO = 276,                     /* NAO  */
    ABRE_PARENTESE = 277,          /* ABRE_PARENTESE  */
    FECHA_PARENTESE = 278,         /* FECHA_PARENTESE  */
    ABRE_COLCHETE = 279,           /* ABRE_COLCHETE  */
    FECHA_COLCHETE = 280,          /* FECHA_COLCHETE  */
    SE = 281,                      /* SE  */
    ENTAO = 282,                   /* ENTAO  */
    SENAO = 283,                   /* SENAO  */
    FIM = 284,                     /* FIM  */
    REPITA = 285,                  /* REPITA  */
    ATE = 286,                     /* ATE  */
    ATRIBUICAO = 287,              /* ATRIBUICAO  */
    LEIA = 288,                    /* LEIA  */
    ESCREVA = 289,                 /* ESCREVA  */
    RETORNA = 290,                 /* RETORNA  */
    INTEIRO = 291,                 /* INTEIRO  */
    FLUTUANTE = 292                /* FLUTUANTE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 26 "test.y"

    char value[500];
    struct node* node;

#line 106 "test.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_TEST_TAB_H_INCLUDED  */
