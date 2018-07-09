#ifndef __AST_H__
#define __AST_H__

#include <string>

class AST
{
public:
	virtual ~AST(){};
}

class ASTIdentifier: public AST
{
private:
	std::string m_sValue;
public:
	ASTInteger(const std::string& value): m_sValue(value)
	{}
	ASTInteger(const std::string&& value): m_sValue(value)
	{}
	~ASTIdentifier(){};
}

class ASTInteger: public AST
{
private:
	int m_iValue;
public:
	ASTInteger(const int& value): m_iValue(value)
	{}
	ASTInteger(const int&& value): m_iValue(value)
	{}
	~ASTInteger(){};
}

class ASTDecimal: public AST
{
private:
	double m_fValue;
public:
	ASTDecimal(const double& value): m_fValue(value)
	{}
	ASTDecimal(const double&& value): m_fValue(value)
	{}
	~ASTDecimal(){};
}

class ASTAssignment: public AST
{
private:
	AST* m_left;
	AST* m_right;
public:
	ASTAssignment(const AST* left, const AST* right):
		m_left(left), 
		m_right(right)
	{}
	~ASTAssignment(){};
}

class ASTBinaryOp: public AST
{
private:
	unsigned char m_op;
	AST* m_left;
	AST* m_right;
public:
	ASTBinaryOp(unsigned char op, const AST* left, const AST* right):
		m_op(op),
		m_left(left), 
		m_right(right)
	{}
	~ASTBinaryOp(){};
}

#endif

