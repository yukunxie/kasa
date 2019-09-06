/* @Copyright (c) 2019 by Yukun Xie
 *
 * %./object_func.cpp
 *
 * This file is part of the "KASA" project (Copyright (c) 2019 by Yukun Xie)
 * See "LICENSE.txt" for license information.
 */

#include "object_func.h"

int ObjectCode::getVarIndex(const ObjectString *variable)
{
	for (size_t i = 0, size = g_variables.size(); i < size; ++i)
	{
		if (g_variables[i]->cmpEQ(variable))
		{
			return (int)i;
		}
	}
	return -1;
}

int ObjectCode::addVar(ObjectString *variable)
{
	auto idx = getVarIndex(variable);
	if (idx >= 0)
	{
		return idx;
	}
	g_variables.push_back(variable);
	return (int)g_variables.size() - 1;
}

int ObjectCode::getConstVarIndex(const Object *constVar)
{
	for (size_t i = 0, size = g_consts.size(); i < size; ++i)
	{
		if (g_consts[i]->cmpEQ(constVar))
		{
			return (int)i;
		}
	}
	return -1;
}

int ObjectCode::addConstVar(Object *constVar)
{
	auto idx = getConstVarIndex(constVar);
	if (idx >= 0)
	{
		return idx;
	}
	g_consts.push_back(constVar);
	return (int)g_consts.size() - 1;
}

void ObjectCode::addParamOP(unsigned char opcode)
{
	this->g_codes.push_back(opcode);
}

// void ObjectCode::addParamConstIndex(int index)
// {
// 	index = RT_CONST_PARAM(index);
// 	this->g_codes.push_back(index & 0xFF);
// 	this->g_codes.push_back(index >> 8);
// }

void ObjectCode::addParamVarIndex(int index)
{
	if (IS_CONST_PARAM(index))
	{
		this->g_codes.push_back(index & 0xFF);
		this->g_codes.push_back(index >> 8);
	}
	else
	{
		this->g_codes.push_back(index & 0xFF);
		this->g_codes.push_back(index >> 8);
	}
}

OP_TYPE ObjectCode::pickOP(size_t &codeptr) const
{
	KASA_ASSERT(g_codes.size() >= codeptr + 1, "invalid codeobject");
	// little endian
	OP_TYPE value = (OP_TYPE)g_codes[codeptr++];
	return value;
}

PARAM_VALUE_TYPE ObjectCode::pickParam(size_t &codeptr) const
{
	KASA_ASSERT(g_codes.size() >= codeptr + 2, "invalid codeobject");
	// little endian
	PARAM_VALUE_TYPE value = (PARAM_VALUE_TYPE)g_codes[codeptr++] + (((PARAM_VALUE_TYPE)g_codes[codeptr++]) << 8);
	return value;
}
