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

class ASTBlock;
class ASTChunk;

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

protected:
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

protected:
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

protected:
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


protected:
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

protected:
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

protected:
	int m_op;
	const AST* m_left;
	const AST* m_right;
};

/**
 * a code block in a block
*/
class ASTChunk: public ASTExpression
{
public:
	ASTChunk()
	{
	}

	~ASTChunk();
	
	void pushBack(const ASTExpression* node)
	{
		m_expressions.push_back(node);
	}

	virtual std::string getTypeName() const
	{
		return "ASTChunk";
	}

	virtual void debug() const
	{
		// std::cout << "chunk expression size:" << m_expressions.size() << std::endl;
		// for (auto it : m_expressions)
		// {
		// 	std::cout << "ttttt: " << it->getTypeName() << std::endl;
		// }
		// std::cout << "xxxxxxxxxxxxxxxxxx" << std::endl;

		for (auto it : m_expressions)
		{
			it->debug();
		}
		
	}

protected:
	std::vector<const AST*> m_expressions;
};

class ASTBlock: public AST
{
public:
	ASTBlock()
	{}

	~ASTBlock()
	{
		for (auto it : m_chunks)
		{
			delete it;
		}
	};
	
	void pushBack(const ASTChunk* chunk)
	{
		m_chunks.push_back(chunk);
	}

	virtual std::string getTypeName() const
	{
		return "ASTBlock";
	}

	virtual void debug() const
	{
		std::cout << "chunk size:" << m_chunks.size() << std::endl;

		for (auto it : m_chunks)
		{
			it->debug();
		}
	}

	ASTBlock* getParentBlock()
	{
		return m_parentBlock;
	}

	void setParentBlock(ASTBlock* block)
	{
		m_parentBlock = block;
	}

	int getVariableIndex(const std::string& name)
	{
		for (size_t i = 0, size = m_variables.size(); i < size; ++i)
		{
			if (m_variables[i] == name)
			{
				return (int)i;
			}
		}
		return -1;
	}

	int addVariable(const std::string& name, const AST* variable)
	{
		for (size_t i = 0, size = m_variables.size(); i < size; ++i)
		{
			if (m_variables[i] == name)
			{
				return i;
			}
		}
		m_variables.emplace_back(name);
		return (int)m_variables.size() - 1;
	}

protected:
	std::vector<const ASTChunk*> m_chunks;
	ASTBlock* m_parentBlock;
	std::vector<std::string> m_variables;
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

protected:
	const ASTExpression* m_expression;
};

/**
 * module is a file.
*/
class ASTModule: public ASTBlock
{
public:
	ASTModule()
	{}

	~ASTModule()
	{
	};
};

#endif
