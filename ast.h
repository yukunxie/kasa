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
#include "object.h"

#define DEBUG_OUTPUT 1

class ASTBlock;
class ASTChunk;

class AST
{	
public:
	virtual ~AST()
	{
	}

	virtual std::string getTypeName() 
	{
		return "AST";
	}

	virtual void debug() 
	{}
	
	void outputDebug() 
	{
#if DEBUG_OUTPUT
		debug();
#endif 
	}

	virtual void processVariableList(ASTBlock * block)
	{
	}
};

class ASTExpression : public AST {
};

class ASTStatement : public AST {
};

class ASTIdentifier: public ASTExpression
{
public:
	ASTIdentifier( std::string& value): m_value(value)
	{}
	ASTIdentifier( std::string&& value): m_value(value)
	{}
	~ASTIdentifier();

	virtual std::string getTypeName() 
	{
		return "ASTIdentifier";
	}

	virtual void debug() 
	{
		std::cout << getTypeName() << " : " << m_value << std::endl;
	}

	virtual void processVariableList(ASTBlock * block);

protected:
	 std::string m_value;
	int m_variableIndex = -1;
};

class ASTInteger: public ASTExpression
{
public:
	ASTInteger( int& value): m_value(value)
	{}
	ASTInteger( int&& value): m_value(value)
	{}
	~ASTInteger();

	virtual std::string getTypeName() 
	{
		return "ASTInteger";
	}

	virtual void debug() 
	{
		std::cout << getTypeName() << " : " << m_value << std::endl;
	}

	virtual void processVariableList(ASTBlock * block);

protected:
	 int m_value;
};

class ASTDecimal: public ASTExpression
{
public:
	ASTDecimal( double& value): m_value(value)
	{}
	ASTDecimal( double&& value): m_value(value)
	{}
	~ASTDecimal();

	virtual std::string getTypeName() 
	{
		return "ASTDecimal";
	}

	virtual void debug() 
	{
		std::cout << getTypeName() << " : " << m_value << std::endl;
	}

	virtual void processVariableList(ASTBlock * block);

protected:
	 double m_value;
};

class ASTString: public ASTExpression
{
public:
	ASTString( std::string& value): m_value(value)
	{}
	ASTString( std::string&& value): m_value(value)
	{}

	virtual std::string getTypeName() 
	{
		return "ASTString";
	}

	virtual void debug() 
	{
		std::cout << getTypeName() << " : " << m_value << std::endl;
	}


protected:
	 std::string m_value;
};

class ASTAssignment: public ASTExpression
{	
public:
	ASTAssignment( AST* left,  AST* right):
		m_left(left), 
		m_right(right)
	{}
	~ASTAssignment();

	virtual std::string getTypeName() 
	{
		return "ASTAssignment";
	}

	virtual void debug() 
	{
		std::cout << getTypeName() << " >>> "<< std::endl;
		m_left->debug();
		m_right->debug();
	}

	virtual void processVariableList(ASTBlock * block);

protected:
	 AST* m_left;
	 AST* m_right;
};

class ASTBinaryOp: public ASTExpression
{
public:
	ASTBinaryOp(int op,  AST* left,  AST* right):
		m_op(op),
		m_left(left), 
		m_right(right)
	{}
	~ASTBinaryOp();

	virtual std::string getTypeName() 
	{
		return "ASTBinaryOp";
	}

	virtual void debug() 
	{
		std::cout << getTypeName() << " >>> " << std::endl; 
		m_left->debug();
		std::cout << "op" << " " << m_op << std::endl;
		m_right->debug();
	}

	virtual void processVariableList(ASTBlock * block);

protected:
	int m_op;
	 AST* m_left;
	 AST* m_right;
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
	
	void pushBack( ASTExpression* node)
	{
		m_expressions.push_back(node);
	}

	virtual std::string getTypeName() 
	{
		return "ASTChunk";
	}

	virtual void debug() 
	{
		for (auto it : m_expressions)
		{
			it->debug();
		}
		
	}

	virtual void processVariableList(ASTBlock * block);

protected:
	std::vector<AST*> m_expressions;
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
	
	void pushBack(ASTChunk* chunk)
	{
		m_chunks.push_back(chunk);
	}

	virtual std::string getTypeName() 
	{
		return "ASTBlock";
	}

	virtual void debug() 
	{
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

	int getVariableIndex( std::string& name)
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

	int addVariable( std::string& name)
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

	virtual void processVariableList(ASTBlock * block) 
	{
		for (auto it : m_chunks)
		{
			it->processVariableList(this);
		}
	}

protected:
	std::vector<ASTChunk*> m_chunks;
	ASTBlock* m_parentBlock;
	std::vector<std::string> m_variables;
};

class ASTExpressionStatement : public ASTExpression 
{
public:
	virtual void debug() 
	{
		m_expression->debug();
	}

	ASTExpressionStatement( ASTExpression* expression) : 
		m_expression(expression) 
	{ }
	~ASTExpressionStatement();

	virtual std::string getTypeName() 
	{
		return "ASTExpressionStatement";
	}

	virtual void processVariableList(ASTBlock * block);

protected:
	 ASTExpression* m_expression;
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
