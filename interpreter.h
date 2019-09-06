/* @Copyright (c) 2019 by Yukun Xie
 *
 * ./interpreter.h
 *
 * This file is part of the "KASA" project (Copyright (c) 2019 by Yukun Xie)
 * See "LICENSE.txt" for license information.
 */

#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include <vector>
#include "kasa_assert.h"
#include "kasa_log.h"
#include "object_code.h"

struct Frame
{
    std::vector<Object *> variables;
    std::vector<Object *> retVariables;
};

class Interpreter
{
  public:
    void execute(Frame *frame, const ObjectCode *codeobject);
};

#endif
