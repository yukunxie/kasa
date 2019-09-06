/* @Copyright (c) 2019 by Yukun Xie
 *
 * ./kasa_assert.cpp
 *
 * This file is part of the "KASA" project (Copyright (c) 2019 by Yukun Xie)
 * See "LICENSE.txt" for license information.
 */

#include "kasa_assert.h"

void outputAssertMessage(const char* msg, const char* filename, const char* funcname, int lineno)
{
    printf("assert fail in %s-%s:%d %s\n\r", filename, funcname, lineno, msg);
}
