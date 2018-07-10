/*************************************************************************
    > File Name: main.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年07月09日 星期一 17时07分21秒
 ************************************************************************/

#include<iostream>
#include "ast.h"
using namespace std;

typedef struct yy_buffer_state * YY_BUFFER_STATE;
extern int yyparse();
extern YY_BUFFER_STATE yy_scan_string (const char *yy_str  );
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);

extern ASTBlock *programBlock;
int main()
{
    char string[] = "id = 10 + 999;";
    YY_BUFFER_STATE buffer = yy_scan_string(string);
    yyparse();
    yy_delete_buffer(buffer);

    programBlock->outputDebug();
    delete programBlock;
	return 0;
}
