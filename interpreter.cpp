#include <iostream>

#include "interpreter.h"
#include "opcode.h"

Object* operator + (const ObjectInteger& a, const ObjectInteger& b)
{
    int value = a.getValue() + b.getValue();
    return new ObjectInteger(value);
}

Object* operator - (const ObjectInteger& a, const ObjectInteger& b)
{
    int value = a.getValue() - b.getValue();
    return new ObjectInteger(value);
}

Object* operator * (const ObjectInteger& a, const ObjectInteger& b)
{
    int value = a.getValue() * b.getValue();
    return new ObjectInteger(value);
}

Object* operator / (const ObjectInteger& a, const ObjectInteger& b)
{
    KASA_ASSERT(b.getValue() != 0, "divisor can not be zero.");
    int value = a.getValue() / b.getValue();
    return new ObjectInteger(value);
}

Object* operator + (const ObjectDecimal& a, const ObjectDecimal& b)
{
    double value = a.getValue() + b.getValue();
    return new ObjectDecimal(value);
}

Object* operator - (const ObjectDecimal& a, const ObjectDecimal& b)
{
    double value = a.getValue() - b.getValue();
    return new ObjectDecimal(value);
}

Object* operator * (const ObjectDecimal& a, const ObjectDecimal& b)
{
    double value = a.getValue() * b.getValue();
    return new ObjectDecimal(value);
}

Object* operator / (const ObjectDecimal& a, const ObjectDecimal& b)
{
    KASA_ASSERT(b.getValue() != 0.0, "divisor can not be zero.");
    double value = a.getValue() / b.getValue();
    return new ObjectDecimal(value);
}

Object* operator + (const ObjectInteger& a, const ObjectDecimal& b)
{
    double value = a.getValue() + b.getValue();
    return new ObjectDecimal(value);
}

Object* operator - (const ObjectInteger& a, const ObjectDecimal& b)
{
    double value = a.getValue() - b.getValue();
    return new ObjectDecimal(value);
}

Object* operator * (const ObjectInteger& a, const ObjectDecimal& b)
{
    double value = a.getValue() * b.getValue();
    return new ObjectDecimal(value);
}

Object* operator / (const ObjectInteger& a, const ObjectDecimal& b)
{
    KASA_ASSERT(b.getValue() != 0.0, "divisor can not be zero.");
    double value = a.getValue() / b.getValue();
    return new ObjectDecimal(value);
}

Object* operator + (const ObjectDecimal& a, const ObjectInteger& b)
{
    double value = a.getValue() + b.getValue();
    return new ObjectDecimal(value);
}

Object* operator - (const ObjectDecimal& a, const ObjectInteger& b)
{
    double value = a.getValue() - b.getValue();
    return new ObjectDecimal(value);
}

Object* operator * (const ObjectDecimal& a, const ObjectInteger& b)
{
    double value = a.getValue() * b.getValue();
    return new ObjectDecimal(value);
}

Object* operator / (const ObjectDecimal& a, const ObjectInteger& b)
{
    KASA_ASSERT(b.getValue() != 0.0, "divisor can not be zero.");
    double value = a.getValue() / b.getValue();
    return new ObjectDecimal(value);
}


Object* _opArithmetical(OP_TYPE op, const Object* a, const Object* b)
{
    Object* result = nullptr;
    switch(op)
    {
    case OP_ADD:
        if (a->getType() == TYPE_INT && a->getType() == TYPE_INT)
        {
            return *(ObjectInteger*)a + *(ObjectInteger*)b;
        }
        else if (a->getType() == TYPE_INT && a->getType() == TYPE_DECIMAL)
        {
            return *(ObjectInteger*)a + *(ObjectDecimal*)b;
        }
        else if (a->getType() == TYPE_DECIMAL && a->getType() == TYPE_INT)
        {
            return *(ObjectDecimal*)a + *(ObjectInteger*)b ;
        }
        else if (a->getType() == TYPE_DECIMAL && a->getType() == TYPE_DECIMAL)
        {
            return *(ObjectDecimal*)a + *(ObjectDecimal*)b ;
        }
        else
        {
            std::cout << "unsupport add opertion for type:" << a->getTypeName() << "+" << b->getTypeName() << std::endl;
            return nullptr;
        }
        break;
    }
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
            //std::cout << codeobject->variables[param1]->toString() << " : " << frame.variables[param1]->toString() << std::endl;
            break;
        case OP_ADD:
        case OP_MUL:
        case OP_SUB:
        case OP_DIV:
            std::cout << "xxx" << value2 << ":" << value3 << " " << param1 << " " << frame.variables.size() << std::endl;
            frame.variables[param1] = _opArithmetical(op, value2, value3);// value2.opAdd(value3);
            std::cout << *codeobject->variables[param1]<< std::endl;
            break;
        }
    }
}