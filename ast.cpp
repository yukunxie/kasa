#include "ast.h"

ASTIdentifier::~ASTIdentifier()
{
}

ASTInteger::~ASTInteger()
{
}

ASTDecimal::~ASTDecimal()
{
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

ASTBlock::~ASTBlock()
{
    for (auto it : m_block)
    {
        delete it;
    }
    m_block.clear();
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

ASTExpressionStatement::~ASTExpressionStatement()
{
    if (m_expression)
    {
        delete m_expression;
    }
    m_expression = nullptr;
}