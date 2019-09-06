/* @Copyright (c) 2019 by Yukun Xie
 *
 * ./kasa_assert.h
 *
 * This file is part of the "KASA" project (Copyright (c) 2019 by Yukun Xie)
 * See "LICENSE.txt" for license information.
 */

#ifndef __KASA_ASSERT_H__
#define __KASA_ASSERT_H__

#include <iostream>
#include <stdio.h>

void outputAssertMessage(const char *msg, const char *filename, const char *funcname, int lineno);

#define KASA_ASSERT(cond, message)                                      \
    do                                                                  \
    {                                                                   \
        if (!(cond))                                                    \
        {                                                               \
            outputAssertMessage(message, __FILE__, __func__, __LINE__); \
            volatile int *p = (int *)0;                                 \
            *p = 0;                                                     \
        }                                                               \
    } while (0);

#endif
