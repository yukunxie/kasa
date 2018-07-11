#ifndef __OBJECT_CODE_H__
#define __OBJECT_CODE_H__

#include <vector>
#include <string>

#include "object.h"

class ObjectCode: public Object
{
public:
    std::vector<std::string> variables;
    std::vector<int> consts;
    std::vector<unsigned char> codes;
};

#endif