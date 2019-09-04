#ifndef __OPCODE_H__
#define __OPCODE_H__

enum OP_TYPE
{
    OP_NULL,
    OP_RETURN, // exit the function.
    OP_EMPTY_PARAM_END,
    
    OP_RETURN_PARAM_SETUP, // setup a return parameter
    OP_ONE_PARAM_END,
    
    OP_SETUP_FUNC,
    OP_SETUP_PARAM,
    OP_CALL,
    OP_LOAD_CONST,
    OP_MOVE,
    OP_TWO_PARAM_END, // 两个参数  op a, b
    
    // 三个参数 op a, b, c
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,

    OP_COUNT
};

#define IS_NULL_PARAM(opcode) (opcode < OP_EMPTY_PARAM_END)
#define IS_ONE_PARAM(opcode) (OP_EMPTY_PARAM_END < opcode && opcode < OP_ONE_PARAM_END)
#define IS_TWO_PARAM(opcode) (OP_ONE_PARAM_END < opcode && opcode < OP_TWO_PARAM_END)
#define IS_TRI_PARAM(opcode) (OP_TWO_PARAM_END < opcode && opcode < OP_COUNT)

#endif
