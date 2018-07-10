/*************************************************************************
    > File Name: main.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年07月09日 星期一 17时07分21秒
 ************************************************************************/
#include <fstream>
#include <string>
#include<iostream>
#include "ast.h"
using namespace std;

typedef struct yy_buffer_state * YY_BUFFER_STATE;
extern int yyparse();
extern YY_BUFFER_STATE yy_scan_string (const char *yy_str  );
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);

extern ASTModule *programBlock;
int main()
{
    std::ifstream ifs("test.ks");
    std::string content( (std::istreambuf_iterator<char>(ifs) ), (std::istreambuf_iterator<char>()));

    //char string[] = "{a = (b / 10); c = a + b;}";
    YY_BUFFER_STATE buffer = yy_scan_string(content.c_str());
    yyparse();
    yy_delete_buffer(buffer);

    programBlock->processVariableList(nullptr);
    delete programBlock;
	return 0;
}
