/* @Copyright (c) 2019 by Yukun Xie
 *
 * ./ast.h
 *
 * This file is part of the "KASA" project (Copyright (c) 2019 by Yukun Xie)
 * See "LICENSE.txt" for license information.
 */

/*header
    > File Name: ast.h
    > Create Time: 2018-07-10 星期二 09时45分23秒
    > Athor: xieyukun
*/
#ifndef __AST_H__
#define __AST_H__

#include <utility>
#include <string>
#include <vector>
#include <iostream>
#include "object.h"
#include "object_code.h"

#define DEBUG_OUTPUT 1

class ASTBlock;
class ASTChunk;
class ASTIdentifier;
class ASTStatement;
class ASTExpression;
typedef std::vector<ASTStatement *> StatementList;
typedef std::vector<ASTExpression *> ExpressionList;
typedef std::vector<ASTIdentifier *> VariableList;

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
	{
	}

	void outputDebug()
	{
#if DEBUG_OUTPUT
		debug();
#endif
	}

	virtual int getIndex()
	{
		return m_index;
	}

	virtual void processVariableList(ASTBlock *block)
	{
	}

	virtual void genCodes(ObjectCode *codeobject){};

protected:
	int m_index = -1;
};

class ASTExpression : public AST
{
};

class ASTStatement : public AST
{
};

class ASTIdentifier : public ASTExpression
{
public:
	ASTIdentifier(const std::string &value)
	{
		m_value = new ObjectString(value);
	}

	ASTIdentifier(const std::string &&value)
	{
		m_value = new ObjectString(std::forward<const std::string>(value));
	}

	~ASTIdentifier();

	ObjectString* getValue()
	{
		return m_value;
	}

	virtual std::string getTypeName()
	{
		return "ASTIdentifier";
	}

	virtual void debug()
	{
		std::cout << getTypeName() << " : " << m_value->toString() << std::endl;
	}

	virtual void genCodes(ObjectCode *codeobject);
	virtual void processVariableList(ASTBlock *block);

protected:
	ObjectString *m_value;
	int m_variableIndex = -1;
};

class ASTInteger : public ASTExpression
{
public:
	ASTInteger(const int &value)
	{
		m_value = new ObjectInteger(value);
	}

	ASTInteger(const int &&value)
	{
		m_value = new ObjectInteger(std::forward<const int>(value));
	}

	~ASTInteger();

	virtual std::string getTypeName()
	{
		return "ASTInteger";
	}

	virtual void debug()
	{
		std::cout << getTypeName() << " : " << m_value << std::endl;
	}
	virtual void genCodes(ObjectCode *codeobject);
	virtual void processVariableList(ASTBlock *block);

protected:
	ObjectInteger *m_value;
};

class ASTDecimal : public ASTExpression
{
public:
	ASTDecimal(const double &value) : m_value(value)
	{
	}

	ASTDecimal(const double &&value) : m_value(std::forward<const double>(value))
	{
	}
	~ASTDecimal();

	virtual std::string getTypeName()
	{
		return "ASTDecimal";
	}

	virtual void debug()
	{
		std::cout << getTypeName() << " : " << m_value << std::endl;
	}

	virtual void processVariableList(ASTBlock *block);

protected:
	ObjectDecimal m_value;
};

class ASTString : public ASTExpression
{
public:
	ASTString(const std::string &value) : m_value(value)
	{
	}
	ASTString(const std::string &&value) : m_value(std::forward<const std::string>(value))
	{
	}

	virtual std::string getTypeName()
	{
		return "ASTString";
	}

	virtual void debug()
	{
		std::cout << getTypeName() << " : " << m_value << std::endl;
	}

	virtual void processVariableList(ASTBlock *block);

protected:
	ObjectString m_value;
};

class ASTAssignment : public ASTExpression
{
public:
	ASTAssignment(AST *left, AST *right) : m_left(left),
																				 m_right(right)
	{
	}
	~ASTAssignment();

	virtual std::string getTypeName()
	{
		return "ASTAssignment";
	}

	virtual void debug()
	{
		std::cout << getTypeName() << " >>> " << std::endl;
		m_left->debug();
		m_right->debug();
	}

	virtual void genCodes(ObjectCode *codeobject);
	virtual void processVariableList(ASTBlock *block);

protected:
	AST *m_left;
	AST *m_right;
};

class ASTBinaryOp : public ASTExpression
{
public:
	ASTBinaryOp(int op, AST *left, AST *right) : m_op(op),
																							 m_left(left),
																							 m_right(right)
	{
	}
	~ASTBinaryOp();

	virtual std::string getTypeName()
	{
		return "ASTBinaryOp";
	}

	virtual void debug()
	{
		std::cout << getTypeName() << " >>> " << std::endl;
		m_left->debug();
		std::cout << "op"
							<< " " << m_op << std::endl;
		m_right->debug();
	}

	virtual void genCodes(ObjectCode *codeobject);
	virtual void processVariableList(ASTBlock *block);

protected:
	int m_op;
	AST *m_left;
	AST *m_right;
};

class ASTReturnExpression : public ASTExpression
{
public:
    virtual void genCodes(ObjectCode *codeobject) override;
    void appendExrepssion(ASTExpression* expr);
    
protected:
    ExpressionList m_exprs;
};

/**
 * a code block in a block
*/
class ASTChunk : public ASTExpression
{
public:
	ASTChunk()
	{
	}

	~ASTChunk();

	void pushBack(ASTExpression *node)
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
	virtual void genCodes(ObjectCode *codeobject);
	virtual void processVariableList(ASTBlock *block);

protected:
	std::vector<AST *> m_expressions;
};

class ASTBlock : public AST
{
public:
	ASTBlock()
	{
        m_codeObject = new ObjectCode();
	}

	~ASTBlock()
	{
		for (auto it : m_chunks)
		{
			delete it;
		}
	};

	void addGlobalVars(VariableList * vars);

	void pushBack(ASTChunk *chunk)
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

	virtual void genCodes(ObjectCode *codeobject);

	ASTBlock *getParentBlock()
	{
		return m_parentBlock;
	}

	void setParentBlock(ASTBlock *block)
	{
		m_parentBlock = block;
	}

	int getVarIndex(const ObjectString *variable)
	{
		return m_codeObject->getVarIndex(variable);
	}

	int addVar(ObjectString *variable)
	{
		return m_codeObject->addVar(variable);
	}

	int getConstVarIndex(const Object *constVar)
	{
		return m_codeObject->getConstVarIndex(constVar);
	}

	int addConstVar(Object *constVar)
	{
		return m_codeObject->addConstVar(constVar);
	}

	virtual void processVariableList(ASTBlock *block)
	{
		for (auto it : m_chunks)
		{
			it->processVariableList(this);
		}
	}

	ObjectCode* getCodeObject()
	{
		return m_codeObject;
	}

protected:
	std::vector<ASTChunk *> m_chunks;
	ASTBlock *m_parentBlock;
	ObjectCode *m_codeObject;
};

class ASTExpressionStatement : public ASTExpression
{
public:
	virtual void debug()
	{
		m_expression->debug();
	}

	ASTExpressionStatement(ASTExpression *expression) : m_expression(expression)
	{
	}
	~ASTExpressionStatement();

	virtual std::string getTypeName()
	{
		return "ASTExpressionStatement";
	}

	virtual void genCodes(ObjectCode *codeobject);
	virtual void processVariableList(ASTBlock *block);

protected:
	ASTExpression *m_expression;
};

class ASTFunctionDeclaration : public ASTExpression
{
public:
	ASTFunctionDeclaration(ASTIdentifier *name, VariableList *arguments, ASTChunk *chunk) : m_name(name),
												m_arguments(arguments)
	{
		m_block = new ASTBlock();
		m_block->pushBack(chunk);
	}

	virtual std::string getTypeName()
	{
		return "ASTFunctionDeclaration";
	}

	virtual void genCodes(ObjectCode *codeobject);
	

protected:
	ASTIdentifier *m_name;
	VariableList *m_arguments;
	ASTBlock *m_block;
};

class ASTMethodCall : public ASTExpression {
public:
	ASTMethodCall(ASTIdentifier  *name, ExpressionList *expressions):
		m_name(name),
		m_expressions(expressions)
	{}

	virtual void genCodes(ObjectCode *codeobject);

protected:
	ASTIdentifier  *m_name;
	ExpressionList *m_expressions;
    
};

/**
 * module is a file.
*/
class ASTModule : public ASTBlock
{
public:
	ASTModule()
	{
	}

	~ASTModule(){};
};

#endif
