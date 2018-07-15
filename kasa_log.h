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