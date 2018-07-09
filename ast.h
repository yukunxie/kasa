#ifndef __AST_H__
#define __AST_H__

#include <string>

class AST
{
public:
	virtual ~AST(){};
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
	~ASTIdentifier(){};
};

class ASTInteger: public AST
{
private:
	const int m_iValue;
public:
	ASTInteger(const int& value): m_iValue(value)
	{}
	ASTInteger(const int&& value): m_iValue(value)
	{}
	~ASTInteger(){};
};

class ASTDecimal: public AST
{
private:
	const double m_fValue;
public:
	ASTDecimal(const double& value): m_fValue(value)
	{}
	ASTDecimal(const double&& value): m_fValue(value)
	{}
	~ASTDecimal(){};
};

class ASTAssignment: public AST
{
private:
	const AST* m_left;
	const AST* m_right;
public:
	ASTAssignment(const AST* left, const AST* right):
		m_left(left), 
		m_right(right)
	{}
	~ASTAssignment(){};
};

class ASTBinaryOp: public AST
{
private:
	unsigned char m_op;
	const AST* m_left;
	const AST* m_right;
public:
	ASTBinaryOp(unsigned char op, const AST* left, const AST* right):
		m_op(op),
		m_left(left), 
		m_right(right)
	{}
	~ASTBinaryOp(){};
};

#endif

