#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include <vector>
#include "kasa_assert.h"
#include "kasa_log.h"
#include "object_code.h"

struct Frame
{
    std::vector<Object *> variables;
};

class Interpreter
{
  public:
    void execute(const ObjectCode *codeobject);
};

#endif