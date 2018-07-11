#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include <vector>
#include "kasa_assert.h"
#include "object_code.h"

struct Frame
{
    std::vector<Object*> variables;
};

class Interpreter 
{
public:
    void execute(const ObjectCode* codeobject);

protected:
    PARAM_VALUE_TYPE pickParam(const ObjectCode* codeobject, size_t& codeptr)
    {
        KASA_ASSERT(codeobject->codes.size() >= codeptr + 2, "invalid codeobject");
        // little endian
        PARAM_VALUE_TYPE value = (PARAM_VALUE_TYPE)codeobject->codes[codeptr++] + (((PARAM_VALUE_TYPE)codeobject->codes[codeptr++]) << 8);
        return value;
    }
};

#endif