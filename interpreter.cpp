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
    case OP_SUB:
        if (a->getType() == TYPE_INT && a->getType() == TYPE_INT)
        {
            return *(ObjectInteger*)a - *(ObjectInteger*)b;
        }
        else if (a->getType() == TYPE_INT && a->getType() == TYPE_DECIMAL)
        {
            return *(ObjectInteger*)a - *(ObjectDecimal*)b;
        }
        else if (a->getType() == TYPE_DECIMAL && a->getType() == TYPE_INT)
        {
            return *(ObjectDecimal*)a - *(ObjectInteger*)b ;
        }
        else if (a->getType() == TYPE_DECIMAL && a->getType() == TYPE_DECIMAL)
        {
            return *(ObjectDecimal*)a - *(ObjectDecimal*)b ;
        }
        else
        {
            std::cout << "unsupport add opertion for type:" << a->getTypeName() << "-" << b->getTypeName() << std::endl;
            return nullptr;
        }
        break;
    case OP_MUL:
        if (a->getType() == TYPE_INT && a->getType() == TYPE_INT)
        {
            return *(ObjectInteger*)a * *(ObjectInteger*)b;
        }
        else if (a->getType() == TYPE_INT && a->getType() == TYPE_DECIMAL)
        {
            return *(ObjectInteger*)a * *(ObjectDecimal*)b;
        }
        else if (a->getType() == TYPE_DECIMAL && a->getType() == TYPE_INT)
        {
            return *(ObjectDecimal*)a * *(ObjectInteger*)b ;
        }
        else if (a->getType() == TYPE_DECIMAL && a->getType() == TYPE_DECIMAL)
        {
            return *(ObjectDecimal*)a * *(ObjectDecimal*)b ;
        }
        else
        {
            std::cout << "unsupport add opertion for type:" << a->getTypeName() << "-" << b->getTypeName() << std::endl;
            return nullptr;
        }
        break;
    case OP_DIV:
        if (a->getType() == TYPE_INT && a->getType() == TYPE_INT)
        {
            return *(ObjectInteger*)a / *(ObjectInteger*)b;
        }
        else if (a->getType() == TYPE_INT && a->getType() == TYPE_DECIMAL)
        {
            return *(ObjectInteger*)a / *(ObjectDecimal*)b;
        }
        else if (a->getType() == TYPE_DECIMAL && a->getType() == TYPE_INT)
        {
            return *(ObjectDecimal*)a / *(ObjectInteger*)b ;
        }
        else if (a->getType() == TYPE_DECIMAL && a->getType() == TYPE_DECIMAL)
        {
            return *(ObjectDecimal*)a / *(ObjectDecimal*)b ;
        }
        else
        {
            std::cout << "unsupport add opertion for type:" << a->getTypeName() << "-" << b->getTypeName() << std::endl;
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

void Interpreter::execute(Frame *frame, const ObjectCode* codeobject)
{
    size_t ptr = 0;

    Frame *next_frame = nullptr;
    ObjectCode* next_codeobject = nullptr;

    while (ptr < codeobject->g_codes.size())
    {
        OP_TYPE op = codeobject->pickOP(ptr);
        PARAM_VALUE_TYPE param1 = codeobject->pickParam(ptr);
        PARAM_VALUE_TYPE param2 = codeobject->pickParam(ptr);
        PARAM_VALUE_TYPE param3 = 0;

        Object* value2  = nullptr;
        if (IS_CONST_PARAM(param2))
        {
            value2 = codeobject->g_consts[TS_CONST_PARAM(param2)];
        }
        else
        {
            //std::cout << param2 <<  " xxxx " << frame.variables[param2] << std::endl;
            KASA_ASSERT(frame->variables.size() > param2 && frame->variables[param2], (codeobject->g_variables[param2]->toString() + " has not been init.").c_str());
            value2 = frame->variables[param2];
        }

        Object* value3  = nullptr;
        if (IS_TRI_PARAM(op))
        {
             // get the third param.
            param3 = codeobject->pickParam(ptr);

            if (IS_CONST_PARAM(param3))
            {
                value3 = codeobject->g_consts[TS_CONST_PARAM(param3)];
            }
            else
            {
                KASA_ASSERT(frame->variables[param3], (codeobject->g_variables[param3]->toString() + " has not been init.").c_str());
                value3 = frame->variables[param3];
            }
        }

        //std::cout << "params: " << (int)param1 << " " << (int)param2 << " " << (int)param3 << std::endl;

        std::cout << "op: " << op << std::endl;
        switch(op)
        {
        case OP_LOAD_CONST:
            while(frame->variables.size() <= param1) frame->variables.push_back(nullptr);
            frame->variables[param1] = value2;
            LOG_INFO("address=%s", value2->getTypeName().c_str());
            //std::cout << "load const:" << param1 << " " << codeobject->g_variables[param1]->toString() << " : " << frame.variables[param1]->toString() << std::endl;
            break;
        case OP_ADD:
        case OP_MUL:
        case OP_SUB:
        case OP_DIV:
             while(frame->variables.size() <= param1) frame->variables.push_back(nullptr);
            frame->variables[param1] = _opArithmetical(op, value2, value3);// value2.opAdd(value3);
            //std::cout << "xxx" << value2->toString() << ":" << value3->toString() << " " << param1 << " " << frame.variables[param1]->toString() << std::endl;
            //std::cout << *codeobject->g_variables[param1]<< std::endl;
            break;
        case OP_SETUP_FUNC:
            next_codeobject = (ObjectCode*)(frame->variables[param1]);
            if (next_frame)delete next_frame;
            next_frame = new Frame;
            //std::cout << "op_setup_func " << param1 << std::endl;;
            break;

        case OP_CALL:
            Interpreter _tmp;
            std::cout << "xxxxkkkk" << std::endl;
            _tmp.execute(next_frame, next_codeobject);
            std::cout << "op_setup_param:" << next_codeobject->g_codes.size()<< std::endl;;
            break;

        case OP_SETUP_PARAM:
			if (IS_CONST_PARAM(param2))
			{
				auto value = codeobject->g_consts[TS_CONST_PARAM(param2)];
				next_frame->variables.push_back(value);
			}
			else
			{
				next_frame->variables.push_back(frame->variables[param2]);
			}
            break;
        }
    }
}