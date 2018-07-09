%{
	#include "ast.h"
    #include <cstdio>
    #include <cstdlib>
	#include <iostream>
	
	ASTBlock *programBlock = nullptr; /* the top level root node of our final AST */

	extern int yylex();
	extern int yycolumn;
	extern int yylineno;
	extern int yyleng;
	
	// customized lexer infomation
	typedef struct YYLTYPE  
	{  
		int first_line;  
		int first_column;  
		int last_line;  
		int last_column;  
	} YYLTYPE;
	#define YYLTYPE_IS_DECLARED 1

	void yyerror(const char *s) 
	{	
		std::cout << "Error-> (" << yylineno << ":"<<yycolumn - yyleng << "-" << yycolumn << ")"  << s << std::endl;
		std::exit(1); 
	}
%}

%locations

/* Represents the many different ways we can access our data */
%union {
	AST *ast;
	ASTBlock *block;
	ASTExpression *expr;
	ASTStatement *stmt;
	ASTIdentifier *ident;
	std::vector<ASTIdentifier*> *varvec;
	std::vector<ASTExpression*> *exprvec;
	std::string *string;
	int token;
}

/* Define our terminal symbols (tokens). This should
   match our tokens.l lex file. We also define the node type
   they represent.
 */
%token <string> TIDENTIFIER TINTEGER TDOUBLE
%token <token> TCEQ TCNE TCLT TCLE TCGT TCGE TEQUAL
%token <token> TLBRACE TRBRACE TCOMMA TDOT
%token <token> TPLUS TMINUS TMUL TDIV
%token <token> TRETURN TEXTERN
%token <token> TFOR TWHILE TIF TELSE

/* Define the type of node our nonterminal symbols represent.
   The types refer to the %union declaration above. Ex: when
   we call an ident (defined by union type ident) we are really
   calling an (NIdentifier*). It makes the compiler happy.
 */
%type <ident> ident
%type <expr> numeric expr 
%type <block> program stmts block
%type <stmt> stmt 
%type <token> comparison

/* Operator precedence for mathematical operators */
%left TPLUS TMINUS
%left TMUL TDIV

%start program

%%

program : stmts { programBlock = $1; }
		;
		
stmts : stmt { $$ = new ASTBlock(); $$->pushBack($<stmt>1); }
	  	| stmts stmt { $1->pushBack($<stmt>2); }
		;

stmt : expr { $$ = new ASTExpressionStatement($1); }
		;

block : TLBRACE stmts TRBRACE { $$ = $2; }
	  	| TLBRACE TRBRACE { $$ = new ASTBlock(); }
	  	;

ident : TIDENTIFIER { $$ = new ASTIdentifier(*$1); delete $1; }
	  	;

numeric : TINTEGER { $$ = new ASTInteger(atoi($1->c_str())); delete $1; }
		| TDOUBLE { $$ = new ASTDecimal(atof($1->c_str())); delete $1; }
		;
	
expr : ident TEQUAL expr { $$ = new ASTAssignment($<ident>1, $3); }
	 	| numeric
        | expr TMUL expr { $$ = new ASTBinaryOp($2, $1, $3); }
        | expr TDIV expr { $$ = new	ASTBinaryOp($2, $1, $3); }
        | expr TPLUS expr { $$ = new ASTBinaryOp($2, $1, $3); }
        | expr TMINUS expr { $$ = new ASTBinaryOp($2, $1, $3); }
 	 	| expr comparison expr { $$ = new ASTBinaryOp($2, $1, $3); }
     	| '(' expr ')' { $$ = $2; }
	 	;

comparison : TCEQ 
		| TCNE 
		| TCLT 
		| TCLE 
		| TCGT 
		| TCGE
		;
%%