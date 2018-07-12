#include "ast.h"

ASTIdentifier::~ASTIdentifier()
{
}

void ASTIdentifier::processVariableList(ASTBlock *block)
{
    m_index = block->addVar(&m_value);
}

ASTInteger::~ASTInteger()
{
}

void ASTInteger::processVariableList(ASTBlock *block)
{
    m_index = block->addConstVar(&m_value);
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

void ASTExpressionStatement::processVariableList(ASTBlock *block)
{
    m_expression->processVariableList(block);
}

void ASTBlock::genCodes(ObjectCode *codeobject)
{
    m_codeObject = new ObjectCode();

    for (auto it : m_chunks)
    {
        it->genCodes(codeobject);
    }
}