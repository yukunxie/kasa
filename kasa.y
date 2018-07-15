%{
	#include "ast.h"
    #include <cstdio>
    #include <cstdlib>
	#include <iostream>
	
	ASTModule *programBlock = new ASTModule(); /* the top level root node of our final AST */

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
	ASTChunk *chunk;
	ASTExpression *expr;
	ASTExpression *stmt;
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
%token <token> TEXPREND
%token <token> TFUNCTION TPRINT

/* Define the type of node our nonterminal symbols represent.
   The types refer to the %union declaration above. Ex: when
   we call an ident (defined by union type ident) we are really
   calling an (NIdentifier*). It makes the compiler happy.
 */
%type <ident> ident
%type <expr> numeric expr id_or_expr ex_expr
%type <varvec> func_decl_args
%type <exprvec> call_args
%type <chunk> program stmts chunk
%type <stmt> stmt func_decl
%type <token> comparison

/* Operator precedence for mathematical operators */
%left TPLUS TMINUS
%left TMUL TDIV

%start program

%%

program : stmts {programBlock->pushBack($1); }
		//| chunk { programBlock = $1; }
		;

ident : TIDENTIFIER { $$ = new ASTIdentifier(*$1); delete $1; }
	  	;
		
stmts : stmt { $$ = new ASTChunk(); $$->pushBack($<stmt>1); }
	  	| stmts stmt { $1->pushBack($<stmt>2); }
		;

stmt : ex_expr TEXPREND { $$ = new ASTExpressionStatement($1); }
		| chunk {$$ = $1;}
		| func_decl {$$ = $1;}
		;

func_decl : TFUNCTION ident '(' func_decl_args ')' chunk { $$ = new ASTFunctionDeclaration($2, $4, $6);}
		  ;

func_decl_args : /*blank*/  { $$ = new VariableList(); }
		  | ident { $$ = new VariableList(); $$->push_back($<ident>1); }
		  | func_decl_args TCOMMA ident { $1->push_back($<ident>3); }
		  ;

chunk : TLBRACE stmts TRBRACE { $$ = $2; }
	  	| TLBRACE TRBRACE { $$ = new ASTChunk(); }
	  	;

numeric : TINTEGER { $$ = new ASTInteger(atoi($1->c_str())); delete $1; }
		| TDOUBLE { $$ = new ASTDecimal(atof($1->c_str())); delete $1; }
		;

ex_expr: ident TEQUAL id_or_expr { $$ = new ASTAssignment($<ident>1, $3); }
		| expr {$$ = $1;}
		;

id_or_expr : expr { $$ = $1; }
		| ident  { $$ = $1; }
		;

expr :    numeric { $$ = $1; }
        | id_or_expr TMUL id_or_expr { $$ = new ASTBinaryOp($2, $1, $3); }
        | id_or_expr TDIV id_or_expr { $$ = new	ASTBinaryOp($2, $1, $3); }
        | id_or_expr TPLUS id_or_expr { $$ = new ASTBinaryOp($2, $1, $3); }
        | id_or_expr TMINUS id_or_expr { $$ = new ASTBinaryOp($2, $1, $3); }
 	 	| id_or_expr comparison id_or_expr { $$ = new ASTBinaryOp($2, $1, $3); }
     	| '(' id_or_expr ')' { $$ = $2; }
		| ident '(' call_args ')' { $$ = new ASTMethodCall($1, $3); }
	 	;

call_args : /*blank*/  { $$ = new ExpressionList(); }
		  | expr { $$ = new ExpressionList(); $$->push_back($1); }
		  | call_args TCOMMA expr  { $1->push_back($3); }
		  ;

comparison : TCEQ 
		| TCNE 
		| TCLT 
		| TCLE 
		| TCGT 
		| TCGE
		;
%%