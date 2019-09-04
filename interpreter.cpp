#include <iostream>

#include "interpreter.h"
#include "opcode.h"

#define DECLARE_BINARY_OP_TEMPLATE(Op)                              \
template<typename _Tp1, typename _Tp2>                              \
decltype(auto) operator Op(const _Tp1&a, const _Tp2& b)              \
{                                                                   \
    auto value = a.getValue() Op b.getValue();                       \
    return CreateObjectHelper<decltype(value)>::createObject(value);\
}

template<typename _Tp>
struct CreateObjectHelper
{
    static Object* createObject(const _Tp& value)
    {
        return new (typename ObjectTypeTriats<_Tp>::ObjectType)(value);
    }
};

// declare binary opertion on objects.
DECLARE_BINARY_OP_TEMPLATE(+)
DECLARE_BINARY_OP_TEMPLATE(-)
DECLARE_BINARY_OP_TEMPLATE(*)
DECLARE_BINARY_OP_TEMPLATE(/)
DECLARE_BINARY_OP_TEMPLATE(<)
DECLARE_BINARY_OP_TEMPLATE(<=)
DECLARE_BINARY_OP_TEMPLATE(>=)
DECLARE_BINARY_OP_TEMPLATE(>)
DECLARE_BINARY_OP_TEMPLATE(==)
DECLARE_BINARY_OP_TEMPLATE(!=)

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

#define LOAD_VALUE_BY_PARAM(param, value)                          \
do{                                                         \
    if (IS_CONST_PARAM(param))                              \
    {                                                       \
    value = codeobject->g_consts[TS_CONST_PARAM(param)];   \
    }                                                       \
    else                                                    \
    {                                                       \
    value = frame->variables[param];                       \
    }                                                       \
} while (0)

void Interpreter::execute(Frame *frame, const ObjectCode* codeobject)
{
    size_t ptr = 0;

    Frame *next_frame = nullptr;
    ObjectCode* next_codeobject = nullptr;

    while (ptr < codeobject->g_codes.size())
    {
        OP_TYPE op = codeobject->pickOP(ptr);
        PARAM_VALUE_TYPE param1 = 0;
        PARAM_VALUE_TYPE param2 = 0;
        PARAM_VALUE_TYPE param3 = 0;
        
        Object* value1  = nullptr;
        Object* value2  = nullptr;
        Object* value3  = nullptr;
        
        if (IS_ONE_PARAM(op) || IS_TWO_PARAM(op) || IS_TRI_PARAM(op))
        {
            param1 = codeobject->pickParam(ptr);
        }
        
        if (IS_TWO_PARAM(op) || IS_TRI_PARAM(op))
        {
            param2 = codeobject->pickParam(ptr);
            LOAD_VALUE_BY_PARAM(param2, value2);
        }
        
        if (IS_TRI_PARAM(op))
        {
            param3 = codeobject->pickParam(ptr);
            LOAD_VALUE_BY_PARAM(param3, value3);
        }

        std::cout << "op: " << op << std::endl;
        switch(op)
        {
            case OP_RETURN:
            {
                return;
            }
            case OP_RETURN_PARAM_SETUP:
            {
                LOAD_VALUE_BY_PARAM(param1, value1);
                frame->retVariables.push_back(value1);
                break;
            }
            
            case OP_LOAD_CONST:
            {
                while(frame->variables.size() <= param1) frame->variables.push_back(nullptr);
                frame->variables[param1] = value2;
                LOG_INFO("address=%s", value2->getTypeName().c_str());
                //std::cout << "load const:" << param1 << " " << codeobject->g_variables[param1]->toString() << " : " << frame.variables[param1]->toString() << std::endl;
                break;
            }
            
            case OP_ADD:
            case OP_MUL:
            case OP_SUB:
            case OP_DIV:
            {
                while(frame->variables.size() <= param1) frame->variables.push_back(nullptr);
                frame->variables[param1] = _opArithmetical(op, value2, value3);// value2.opAdd(value3);
                //std::cout << "xxx" << value2->toString() << ":" << value3->toString() << " " << param1 << " " << frame.variables[param1]->toString() << std::endl;
                //std::cout << *codeobject->g_variables[param1]<< std::endl;
                break;
            }
            case OP_SETUP_FUNC:
            {
                next_codeobject = (ObjectCode*)(frame->variables[param1]);
                if (next_frame)delete next_frame;
                next_frame = new Frame;
                //std::cout << "op_setup_func " << param1 << std::endl;;
                break;
            }

            case OP_CALL:
            {
                Interpreter _tmp;
                _tmp.execute(next_frame, next_codeobject);
#if NDEBUG
                std::cout << "return values: " << next_frame->retVariables.size() << std::endl;
                for (int i = 0; i < next_frame->retVariables.size(); ++i)
                {
                    printf("\t>>> [%d] = %s\n", i, next_frame->retVariables[i]->toString().c_str());
                }
#endif
                break;
            }

            case OP_SETUP_PARAM:
            {
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
            
            default:
            {
                std::cout << "unprocessed opcode: " << op << std::endl;
                break;
            }
        }
    }
}
