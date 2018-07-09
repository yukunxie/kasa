#ifndef __AST_H__
#define __AST_H__

#include <string>
#include <vector>
#include <iostream>

class AST
{
public:
	virtual ~AST(){};
};

class ASTExpression : public AST {
};

class ASTStatement : public AST {
};

class ASTIdentifier: public AST
{
private:
	const std::string m_sValue;
public:
	ASTIdentifier(const std::string& value): m_sValue(value)
	{}
	ASTIdentifier(const std::string&& value): m_sValue(value)
	{}
};

class ASTInteger: public ASTExpression
{
private:
	const int m_iValue;
public:
	ASTInteger(const int& value): m_iValue(value)
	{}
	ASTInteger(const int&& value): m_iValue(value)
	{}
};

class ASTDecimal: public ASTExpression
{
private:
	const double m_fValue;
public:
	ASTDecimal(const double& value): m_fValue(value)
	{}
	ASTDecimal(const double&& value): m_fValue(value)
	{}
};

class ASTAssignment: public ASTExpression
{
private:
	const AST* m_left;
	const AST* m_right;
public:
	ASTAssignment(const AST* left, const AST* right):
		m_left(left), 
		m_right(right)
	{}
};

class ASTBinaryOp: public ASTExpression
{
private:
	int m_op;
	const AST* m_left;
	const AST* m_right;
public:
	ASTBinaryOp(int op, const AST* left, const AST* right):
		m_op(op),
		m_left(left), 
		m_right(right)
	{}
};

class ASTBlock: public ASTExpression
{
private:
	std::vector<const AST*> m_block;
public:
	ASTBlock()
	{}
	
	void pushBack(const AST* node)
	{
		m_block.push_back(node);
	}

	~ASTBlock()
	{
		std::cout << m_block.size() << std::endl;
	}
};

class ASTExpressionStatement : public ASTStatement 
{
private:
	const ASTExpression* m_expression;
public:
	ASTExpressionStatement(const ASTExpression* expression) : 
		m_expression(expression) 
	{ }
};

#endif
