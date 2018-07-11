#include <iostream>

#include "interpreter.h"
#include "opcode.h"



void Interpreter::execute(const ObjectCode* codeobject)
{
    Frame frame;
    frame.variables.resize(codeobject->variables.size(), 0);

    size_t ptr = 0;
    while (ptr < codeobject->codes.size())
    {
        OP_TYPE op = (OP_TYPE)codeobject->codes[ptr++];
        unsigned char param1 = codeobject->codes[ptr++];
        unsigned char param2 = codeobject->codes[ptr++];
        unsigned char param3 = 0;
        if (IS_TRI_PARAM(op))
        {
            param3 = codeobject->codes[ptr++];
        }

        int value2  = 0;
        if (param2 >= 128)
        {
            value2 = codeobject->consts[param2 - 128];
        }
        else
        {
            value2 = frame.variables[param2];
        }

        int value3  = 0;
        if (IS_TRI_PARAM(op))
        {
            if (param3 >= 128)
            {
                value3 = codeobject->consts[param3 - 128];
            }
            else
            {
                value3 = frame.variables[param3];
            }
        }

        std::cout << "params: " << (int)param1 << " " << (int)param2 << " " << (int)param3 << std::endl;

        switch(op)
        {
        case OP_LOAD_CONST:
            frame.variables[param1] = value2;
            std::cout << codeobject->variables[param1] << " : " << frame.variables[param1] << std::endl;
            break;
        case OP_ADD:
        case OP_MUL:
        case OP_SUB:
        case OP_DIV:
            frame.variables[param1] = value2 + value3;
            std::cout << codeobject->variables[param1] << " : " << frame.variables[param1] << std::endl;
            break;
        }
    }
}