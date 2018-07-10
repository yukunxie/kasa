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

ASTChunk::~ASTChunk()
{
    for (auto it : m_expressions)
    {
        delete it;
    }
    m_expressions.clear();
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