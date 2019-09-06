/* @Copyright (c) 2019 by Yukun Xie
 *
 * ./main.cpp
 *
 * This file is part of the "KASA" project (Copyright (c) 2019 by Yukun Xie)
 * See "LICENSE.txt" for license information.
 */

/*************************************************************************
    > File Name: main.cpp
    > Author: yukunxie
    > Mail: jinyun2007@126.com
    > Created Time: 2018年07月09日 星期一 17时07分21秒
 ************************************************************************/
#include <fstream>
#include <string>
#include <string.h>
#include <iostream>
#include "ast.h"
#include "object.h"
#include "opcode.h"
#include "kasa_log.h"
#include "kasa_assert.h"
#include "interpreter.h"
#include "object_code.h"
using namespace std;

typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern int yyparse();
extern YY_BUFFER_STATE yy_scan_string(const char *yy_str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);

extern ASTModule *programBlock;
int main()
{
    LOG_INFO("%s, %d, %f", "xxxxxlog", 78787, 0.001);
    //KASA_ASSERT(false, "aaaaaaaaaaaaaaaa");
    // ObjectString a("a");
    // ObjectString b("b");
    // cout << "eq " << (a.cmpEQ(&b)) << endl;
    // char buffer[100];
    // memset(buffer, 0, sizeof(buffer));
    // size_t size = b.serialize(buffer, sizeof(buffer));
    // cout << size << " " << buffer << endl;

    // size += a.serialize(buffer + size, sizeof(buffer) - size);
    // cout << size << " " << buffer << endl;

    // ObjectInteger i('abcd');
    // size += i.serialize(buffer + size, sizeof(buffer) - size);
    // cout << size << " " << buffer << endl;

    // cout << a << " " << b << " " << i << " " << b.getType() << endl;

    std::ifstream ifs("/Users/realxie/Desktop/Realxie/kasa/test1.ks");
    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

	std::cout << "code:" << content << std::endl;

    //char string[] = "{a = (b / 10); c = a + b;}";
    YY_BUFFER_STATE code = yy_scan_string(content.c_str());
    yyparse();
    yy_delete_buffer(code);

    programBlock->genCodes(nullptr);

	Interpreter it;
	Frame frame;
	it.execute(&frame, programBlock->getCodeObject());
    
    //programBlock->processVariableList(nullptr);
    delete programBlock;

    // ObjectCode codeobject;
    // codeobject.addVar(new ObjectString("a"));
    // codeobject.addVar(new ObjectString("b"));
    // codeobject.addConstVar(new ObjectInteger(99));
    // codeobject.addConstVar(new ObjectInteger(77));
    // codeobject.addConstVar(new ObjectInteger(88));

    // codeobject.addParamOP(OP_LOAD_CONST);
    // codeobject.addParamVarIndex(1);
    // codeobject.addParamConstIndex(0);

    // cout << "kkkkkkkkkk" << RT_CONST_PARAM(0) << " " << TS_CONST_PARAM(RT_CONST_PARAM(0)) << " " << CONST_IDX_START << endl;

    // codeobject.addParamOP(OP_ADD);
    // codeobject.addParamVarIndex(0);
    // codeobject.addParamVarIndex(1);
    // codeobject.addParamConstIndex(2);

    // Interpreter interpreter;
    // interpreter.execute(&codeobject);
    return 0;
}
