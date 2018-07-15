#include "kasa_log.h"
#include <ctime>
#include <chrono>

void _log(const char *type, const char *format, va_list args)
{
    char buffer[2048];
	//va_list list;
	//va_start(list, format);
	int nByteWritten = vsnprintf(buffer, sizeof(buffer) - 3, format, args);
    buffer[nByteWritten] = '\0';
	//va_end(list);

    std::time_t t = std::time(NULL);
    char timeinfo[24];
    std::strftime(timeinfo, sizeof(timeinfo), "%F#%T", std::localtime(&t));

    printf("[%s] %s %s\n", type, timeinfo, buffer);
}

void LOG(int level, const char *format, ...)
{
    va_list list;
	va_start(list, format);
	_log("LOG", format, list);
	va_end(list);
}

void LOG_INFO(const char *format, ...)
{
    va_list list;
	va_start(list, format);
	_log("INFO", format, list);
	va_end(list);
    
}

void LOG_WARNING(const char *format, ...)
{
    va_list list;
	va_start(list, format);
	_log("WARNING", format, list);
	va_end(list);
}

void LOG_ERROR(const char *format, ...)
{
    va_list list;
	va_start(list, format);
	_log("ERROR", format, list);
	va_end(list);
}