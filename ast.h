/*header
    > File Name: ast.h
    > Create Time: 2018-07-10 星期二 09时45分23秒
    > Athor: xieyukun
*/
#ifndef __AST_H__
#define __AST_H__

#include <string>
#include <vector>
#include <iostream>

#define DEBUG_OUTPUT 1

class AST
{	
public:
	virtual ~AST()
	{
	}

	virtual std::string getTypeName() const
	{
		return "AST";
	}

	virtual void debug() const
	{}
	
	void outputDebug() const
	{
#if DEBUG_OUTPUT
		debug();
#endif 
	}
};

class ASTExpression : public AST {
};

class ASTStatement : public AST {
};

class ASTIdentifier: public ASTExpression
{
public:
	ASTIdentifier(const std::string& value): m_value(value)
	{}
	ASTIdentifier(const std::string&& value): m_value(value)
	{}
	~ASTIdentifier();

	virtual std::string getTypeName() const
	{
		return "ASTIdentifier";
	}

	virtual void debug() const
	{
		std::cout << getTypeName() << " : " << m_value << std::endl;
	}

private:
	const std::string m_value;
};

class ASTInteger: public ASTExpression
{
public:
	ASTInteger(const int& value): m_value(value)
	{}
	ASTInteger(const int&& value): m_value(value)
	{}
	~ASTInteger();

	virtual std::string getTypeName() const
	{
		return "ASTInteger";
	}

	virtual void debug() const
	{
		std::cout << getTypeName() << " : " << m_value << std::endl;
	}

private:
	const int m_value;
};

class ASTDecimal: public ASTExpression
{
public:
	ASTDecimal(const double& value): m_value(value)
	{}
	ASTDecimal(const double&& value): m_value(value)
	{}
	~ASTDecimal();

	virtual std::string getTypeName() const
	{
		return "ASTDecimal";
	}

	virtual void debug() const
	{
		std::cout << getTypeName() << " : " << m_value << std::endl;
	}

private:
	const double m_value;
};

class ASTString: public ASTExpression
{
public:
	ASTString(const std::string& value): m_value(value)
	{}
	ASTString(const std::string&& value): m_value(value)
	{}

	virtual std::string getTypeName() const
	{
		return "ASTString";
	}

	virtual void debug() const
	{
		std::cout << getTypeName() << " : " << m_value << std::endl;
	}


private:
	const std::string m_value;
};

class ASTAssignment: public ASTExpression
{	
public:
	ASTAssignment(const AST* left, const AST* right):
		m_left(left), 
		m_right(right)
	{}
	~ASTAssignment();

	virtual std::string getTypeName() const
	{
		return "ASTAssignment";
	}

	virtual void debug() const
	{
		std::cout << getTypeName() << " >>> "<< std::endl;
		m_left->debug();
		m_right->debug();
	}

private:
	const AST* m_left;
	const AST* m_right;
};

class ASTBinaryOp: public ASTExpression
{
public:
	ASTBinaryOp(int op, const AST* left, const AST* right):
		m_op(op),
		m_left(left), 
		m_right(right)
	{}
	~ASTBinaryOp();

	virtual std::string getTypeName() const
	{
		return "ASTBinaryOp";
	}

	virtual void debug() const
	{
		std::cout << getTypeName() << " >>> " << std::endl; 
		m_left->debug();
		std::cout << "op" << " " << m_op << std::endl;
		m_right->debug();
	}

private:
	int m_op;
	const AST* m_left;
	const AST* m_right;
};

class ASTBlock: public ASTExpression
{
public:
	ASTBlock()
	{}

	~ASTBlock();
	
	void pushBack(const AST* node)
	{
		m_block.push_back(node);
	}

	virtual std::string getTypeName() const
	{
		return "ASTBlock";
	}

	virtual void debug() const
	{
		for (auto it : m_block)
		{
			it->debug();
		}
	}

private:
	std::vector<const AST*> m_block;
};

class ASTExpressionStatement : public ASTExpression 
{
public:
	virtual void debug() const
	{
		m_expression->debug();
	}

	ASTExpressionStatement(const ASTExpression* expression) : 
		m_expression(expression) 
	{ }
	~ASTExpressionStatement();

	virtual std::string getTypeName() const
	{
		return "ASTExpressionStatement";
	}

private:
	const ASTExpression* m_expression;
};

#endif
