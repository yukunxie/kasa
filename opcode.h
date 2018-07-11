#ifndef __OPCODE_H__
#define __OPCODE_H__

enum OP_TYPE
{
    OP_NULL,

    OP_LOAD_CONST,
    OP_MOVE,
    OP_TWO_PARAM,  // 两个参数  op a, b

    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_TRI_PARAM,  // 三个参数 op a, b, c

    OP_COUNT
};

#define IS_TWO_PARAM(opcode) (OP_NULL < opcode && opcode < OP_TWO_PARAM)
#define IS_TRI_PARAM(opcode) (OP_TWO_PARAM < opcode && opcode < OP_TRI_PARAM)

#endif