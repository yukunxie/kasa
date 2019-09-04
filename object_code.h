#ifndef __OBJECT_CODE_H__
#define __OBJECT_CODE_H__

#include <vector>
#include <string>
#include "object.h"
#include "opcode.h"

typedef unsigned short PARAM_VALUE_TYPE;
constexpr PARAM_VALUE_TYPE CONST_IDX_START = 1 << (sizeof(PARAM_VALUE_TYPE) * 8 - 1);

#define IS_CONST_PARAM(param) (param >= CONST_IDX_START)
#define TS_CONST_PARAM(param) (param - CONST_IDX_START)
#define RT_CONST_PARAM(param) (param + CONST_IDX_START)

class ObjectCode : public Object
{
public:
    virtual std::string getTypeName() const
    {
      return "ObjectCode";
    }
    int getVarIndex(const ObjectString *variable);
    int addVar(ObjectString *variable);
    int getConstVarIndex(const Object *constVar);
    int addConstVar(Object *constVar);

    void addParamOP(unsigned char opcode);
    void addParamVarIndex(int index);

    OP_TYPE pickOP(size_t &codeptr) const;
    PARAM_VALUE_TYPE pickParam(size_t &codeptr) const;

public:
  std::vector<ObjectString *> g_variables;
  std::vector<Object *> g_consts;
  std::vector<unsigned char> g_codes;
};

#endif
