/*************************************************************************
    > File Name: main.cpp
    > Author: yukunxie
    > Mail: jinyun2007@126.com
    > Created Time: 2018年07月09日 星期一 17时07分21秒
 ************************************************************************/
#include <fstream>
#include <string>
#include <string.h>
#include<iostream>
#include "ast.h"
#include "object.h"
#include "kasa_assert.h"
using namespace std;

typedef struct yy_buffer_state * YY_BUFFER_STATE;
extern int yyparse();
extern YY_BUFFER_STATE yy_scan_string (const char *yy_str  );
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);


extern ASTModule *programBlock;
int main()
{
    //KASA_ASSERT(false, "aaaaaaaaaaaaaaaa");
    ObjectString a("123");
    ObjectString b("123 " );
    cout << "eq " << (a.cmpEQ(&b)) << endl;
    char buffer[100];
    memset(buffer, 0, sizeof(buffer));
    size_t size = b.serialize(buffer, sizeof(buffer));
    cout << size << " " << buffer << endl;

    size += a.serialize(buffer+ size, sizeof(buffer) - size);
    cout << size << " " << buffer << endl;

    ObjectInteger i('abcd');
    size += i.serialize(buffer+ size, sizeof(buffer) - size);
    cout << size << " " << buffer << endl;


    cout << a << " " << b << " " << i << " " << b.getType()<< endl;
    std::ifstream ifs("test.ks");
    std::string content( (std::istreambuf_iterator<char>(ifs) ), (std::istreambuf_iterator<char>()));

    //char string[] = "{a = (b / 10); c = a + b;}";
    YY_BUFFER_STATE code = yy_scan_string(content.c_str());
    yyparse();
    yy_delete_buffer(code);

    programBlock->processVariableList(nullptr);
    delete programBlock;
	return 0;
}
