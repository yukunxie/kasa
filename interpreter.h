#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include <vector>

#include "object_code.h"

struct Frame
{
    std::vector<int> variables;
};

class Interpreter 
{
public:
    void execute(const ObjectCode* codeobject);
};

#endif