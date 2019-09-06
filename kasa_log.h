/* @Copyright (c) 2019 by Yukun Xie
 *
 * ./kasa_log.h
 *
 * This file is part of the "KASA" project (Copyright (c) 2019 by Yukun Xie)
 * See "LICENSE.txt" for license information.
 */

#ifndef __KASA_LOG_H__
#define __KASA_LOG_H__

#include <iostream>
#include <stdio.h>

void _log(int level, const char *format, va_list args);

void LOG(int level, const char *format, ...);
void LOG_INFO(const char *format, ...);
void LOG_WARNING(const char *format, ...);
void LOG_ERROR(const char *format, ...);


#endif
