#include <iostream>

#include "interpreter.h"
#include "opcode.h"

Object* _opArithmetical(const Object* a, const Object* b)
{
    return nullptr;
}

Object* _opLogic(const Object* a, const Object* b)
{
    return nullptr;
}

Object* _opBitset(const Object* a, const Object* b)
{
    return nullptr;
}

void Interpreter::execute(const ObjectCode* codeobject)
{
    Frame frame;
    frame.variables.resize(codeobject->variables.size(), nullptr);

    size_t ptr = 0;
    while (ptr < codeobject->codes.size())
    {
        OP_TYPE op = (OP_TYPE)codeobject->codes[ptr++];
        PARAM_VALUE_TYPE param1 = this->pickParam(codeobject, ptr);
        PARAM_VALUE_TYPE param2 = this->pickParam(codeobject, ptr);
        PARAM_VALUE_TYPE param3 = 0;

        Object* value2  = nullptr;
        if (IS_CONST_PARAM(param2))
        {
            value2 = codeobject->consts[TS_CONST_PARAM(param2)];
        }
        else
        {
            KASA_ASSERT(frame.variables[param2], (codeobject->variables[param2]->toString() + " has not been init.").c_str());
            value2 = frame.variables[param2];
        }

        Object* value3  = nullptr;
        if (IS_TRI_PARAM(op))
        {
             // get the third param.
            param3 = this->pickParam(codeobject, ptr);

            if (IS_CONST_PARAM(param3))
            {
                value3 = codeobject->consts[TS_CONST_PARAM(param3)];
            }
            else
            {
                KASA_ASSERT(frame.variables[param3], (codeobject->variables[param3]->toString() + " has not been init.").c_str());
                value3 = frame.variables[param3];
            }
        }

        std::cout << "params: " << (int)param1 << " " << (int)param2 << " " << (int)param3 << std::endl;

        switch(op)
        {
        case OP_LOAD_CONST:
            frame.variables[param1] = value2;
            std::cout << codeobject->variables[param1]->toString() << " : " << frame.variables[param1]->toString() << std::endl;
            break;
        case OP_ADD:
        case OP_MUL:
        case OP_SUB:
        case OP_DIV:
            // frame.variables[param1] = value2.opAdd(value3);
            // std::cout << codeobject->variables[param1]->toString() << " : " << frame.variables[param1]->toString() << std::endl;
            break;
        }
    }
}