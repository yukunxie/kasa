#include "ast.h"
#include "interpreter.h"
#include "kasa_parser.hpp"

#include <stdio.h>
#include <unordered_map>


std::unordered_map<int, OP_TYPE> TOKEN_TO_OP_TYPE_MAP = 
{
    {yytokentype::TPLUS, OP_TYPE::OP_ADD},
    {yytokentype::TMINUS, OP_TYPE::OP_SUB},
    {yytokentype::TMUL, OP_TYPE::OP_MUL},
    {yytokentype::TDIV, OP_TYPE::OP_DIV},
};

ASTIdentifier::~ASTIdentifier()
{
}

void ASTIdentifier::genCodes(ObjectCode *codeobject)
{
    m_index = codeobject->addVar(&m_value);
}

void ASTIdentifier::processVariableList(ASTBlock *block)
{
}

ASTInteger::~ASTInteger()
{
}

void ASTInteger::genCodes(ObjectCode *codeobject)
{
    auto index = codeobject->addConstVar(m_value);
    m_index = RT_CONST_PARAM(index);
    //printf("ASTInteger::genCodes %d, %d\n", index, m_index);
}

void ASTInteger::processVariableList(ASTBlock *block)
{
}

ASTDecimal::~ASTDecimal()
{
}

void ASTDecimal::processVariableList(ASTBlock *block)
{
    m_index = block->addConstVar(&m_value);
}

void ASTString::processVariableList(ASTBlock *block)
{
    m_index = block->addConstVar(&m_value);
}

ASTAssignment::~ASTAssignment()
{
    if (m_left)
    {
        delete m_left;
    }
    m_left = nullptr;

    if (m_right)
    {
        delete m_right;
    }
    m_right = nullptr;
}

void ASTAssignment::genCodes(ObjectCode *codeobject)
{
    m_right->genCodes(codeobject);
    m_left->genCodes(codeobject);
    // codeobject->addParamOP(OP_MOVE);
    // codeobject->addParamVarIndex(m_left->getIndex());
    // codeobject->addParamVarIndex(m_right->getIndex());
}

void ASTAssignment::processVariableList(ASTBlock *block)
{

    if (m_left)
    {
        m_left->processVariableList(block);
    }
    if (m_right)
    {
        m_right->processVariableList(block);
    }
}

ASTChunk::~ASTChunk()
{
    for (auto it : m_expressions)
    {
        delete it;
    }
    m_expressions.clear();
}

void ASTChunk::genCodes(ObjectCode *codeobject)
{
    std::cout << "thunk amount:" <<  m_expressions.size() << std::endl;
    int idx = 0;
    for (auto it : m_expressions)
    {
        std::cout << "thunk index:" << idx++ << std::endl;
        it->genCodes(codeobject);
    }
}

void ASTChunk::processVariableList(ASTBlock *block)
{
    for (auto it : m_expressions)
    {
        it->processVariableList(block);
    }
}

ASTBinaryOp::~ASTBinaryOp()
{
    if (m_left)
    {
        delete m_left;
    }
    m_left = nullptr;

    if (m_right)
    {
        delete m_right;
    }
    m_right = nullptr;
}

void ASTBinaryOp::genCodes(ObjectCode *codeobject)
{
    m_left->genCodes(codeobject);
    m_right->genCodes(codeobject);

    // trans lex token to opcode operator type
    const OP_TYPE op = TOKEN_TO_OP_TYPE_MAP[m_op];
    codeobject->addParamOP(op);

    m_index =  codeobject->g_variables.size();
    codeobject->addParamVarIndex(m_index);
    codeobject->addParamVarIndex(m_left->getIndex());
    codeobject->addParamVarIndex(m_right->getIndex()); 

    //std::cout << "m_op " << op << std::endl;

    printf("genCodes: m_op=%d, m_index=%d, left_idx=%u, r_idx=%u type=%s\n", op, m_index, m_left->getIndex(), m_right->getIndex(), m_left->getTypeName().c_str());
}

void ASTBinaryOp::processVariableList(ASTBlock *block)
{
    if (m_left)
    {
        m_left->processVariableList(block);
    }
    if (m_right)
    {
        m_right->processVariableList(block);
    }
}

ASTExpressionStatement::~ASTExpressionStatement()
{
    if (m_expression)
    {
        delete m_expression;
    }
    m_expression = nullptr;
}

void ASTExpressionStatement::genCodes(ObjectCode *codeobject)
{
    m_expression->genCodes(codeobject);
}

void ASTExpressionStatement::processVariableList(ASTBlock *block)
{
    m_expression->processVariableList(block);
}

void ASTBlock::genCodes(ObjectCode *codeobject)
{   
    m_codeObject = new ObjectCode();
    // process consts
    processVariableList(this);

    for (auto it : m_chunks)
    {
        it->genCodes(m_codeObject);
    }

    Interpreter interpreter;
    interpreter.execute(m_codeObject);
}