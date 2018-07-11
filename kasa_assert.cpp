#include "kasa_assert.h"

void outputAssertMessage(const char* msg, const char* filename, const char* funcname, int lineno)
{
    printf("assert fail in %s-%s:%d %s\n\r", filename, funcname, lineno, msg);
}