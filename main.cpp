/*************************************************************************
    > File Name: main.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年07月09日 星期一 17时07分21秒
 ************************************************************************/

#include<iostream>
#include "ast.h"
using namespace std;

extern int yyparse();
extern ASTBlock *programBlock;
int main()
{
    cout << programBlock << endl;
    yyparse();
    cout << programBlock << endl;
    delete programBlock;
	return 0;
}
