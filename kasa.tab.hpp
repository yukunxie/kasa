/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TIDENTIFIER = 258,
     TINTEGER = 259,
     TDOUBLE = 260,
     TCEQ = 261,
     TCNE = 262,
     TCLT = 263,
     TCLE = 264,
     TCGT = 265,
     TCGE = 266,
     TEQUAL = 267,
     TLBRACE = 268,
     TRBRACE = 269,
     TCOMMA = 270,
     TDOT = 271,
     TPLUS = 272,
     TMINUS = 273,
     TMUL = 274,
     TDIV = 275,
     TRETURN = 276,
     TEXTERN = 277,
     TFOR = 278,
     TWHILE = 279,
     TIF = 280,
     TELSE = 281,
     TEXPREND = 282,
     TFUNCTION = 283,
     TPRINT = 284
   };
#endif
/* Tokens.  */
#define TIDENTIFIER 258
#define TINTEGER 259
#define TDOUBLE 260
#define TCEQ 261
#define TCNE 262
#define TCLT 263
#define TCLE 264
#define TCGT 265
#define TCGE 266
#define TEQUAL 267
#define TLBRACE 268
#define TRBRACE 269
#define TCOMMA 270
#define TDOT 271
#define TPLUS 272
#define TMINUS 273
#define TMUL 274
#define TDIV 275
#define TRETURN 276
#define TEXTERN 277
#define TFOR 278
#define TWHILE 279
#define TIF 280
#define TELSE 281
#define TEXPREND 282
#define TFUNCTION 283
#define TPRINT 284




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 34 "kasa.y"
{
	AST *ast;
	ASTChunk *chunk;
	ASTExpression *expr;
	ASTReturnExpression *returnExpr;
	ASTExpression *stmt;
	ASTIdentifier *ident;
	std::vector<ASTIdentifier*> *varvec;
	std::vector<ASTExpression*> *exprvec;
	std::string *string;
	int token;
}
/* Line 1529 of yacc.c.  */
#line 120 "kasa.tab.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE yylloc;
