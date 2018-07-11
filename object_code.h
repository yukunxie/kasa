#ifndef __OBJECT_CODE_H__
#define __OBJECT_CODE_H__

#include <vector>
#include <string>
#include "object.h"

typedef unsigned short PARAM_VALUE_TYPE;
static const PARAM_VALUE_TYPE CONST_IDX_START = 1 << (sizeof(PARAM_VALUE_TYPE) * 8 - 1);

#define IS_CONST_PARAM(param) (param >= CONST_IDX_START)
#define TS_CONST_PARAM(param) (param - CONST_IDX_START)
#define RT_CONST_PARAM(param) (param + CONST_IDX_START)

class ObjectCode: public Object
{
public:
    std::vector<ObjectString*> variables;
    std::vector<Object*> consts;
    std::vector<unsigned char> codes;
};

#endif