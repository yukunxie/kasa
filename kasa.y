%{
	#include "ast.h"
    #include <cstdio>
    #include <cstdlib>
	#include <iostream>
	
	ASTBlock *programBlock; /* the top level root node of our final AST */

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
/*%union {
	Node *node;
	NBlock *block;
	NExpression *expr;
	NStatement *stmt;
	NIdentifier *ident;
	std::vector<NIdentifier*> *varvec;
	std::vector<NExpression*> *exprvec;
	std::string *string;
	int token;
}*/

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
%type <varvec> func_decl_args
%type <exprvec> call_args
%type <block> program stmts block
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

block : TLBRACE stmts TRBRACE { $$ = $2; }
	  | TLBRACE TRBRACE { $$ = new NBlock(); }
	  ;

ident : TIDENTIFIER { $$ = new ASTIdentifier(*$1); delete $1; }
	  ;

numeric : TINTEGER { $$ = new NInteger(atol($1->c_str())); delete $1; }
		| TDOUBLE { $$ = new NDouble(atof($1->c_str())); delete $1; }
		;
	
expr : ident TEQUAL expr { $$ = new NAssignment(*$<ident>1, *$3); }
	 | ident '(' call_args ')' { $$ = new NMethodCall(*$1, *$3); delete $3; }
	 | ident { $<ident>$ = $1; }
	 | numeric
         | expr TMUL expr { $$ = new NBinaryOperator(*$1, $2, *$3); }
         | expr TDIV expr { $$ = new NBinaryOperator(*$1, $2, *$3); }
         | expr TPLUS expr { $$ = new NBinaryOperator(*$1, $2, *$3); }
         | expr TMINUS expr { $$ = new NBinaryOperator(*$1, $2, *$3); }
 	 | expr comparison expr { $$ = new NBinaryOperator(*$1, $2, *$3); }
     | '(' expr ')' { $$ = $2; }
	 ;
	
if_stmt : TIF '(' expr ')' block {$$ = new NIfElseStatement($3, $5, NULL);}
		| TIF '(' expr ')' block TELSE block {$$ = new NIfElseStatement($3, $5, $7);}
		;
call_args : /*blank*/  { $$ = new ExpressionList(); }
		  | expr { $$ = new ExpressionList(); $$->push_back($1); }
		  | call_args TCOMMA expr  { $1->push_back($3); }
		  ;

comparison : TCEQ | TCNE | TCLT | TCLE | TCGT | TCGE;

%%