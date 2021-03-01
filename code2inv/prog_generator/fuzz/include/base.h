#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define assume(s) \
    if (!s)       \
        exit(0);

// List the variable values, args : vars as format
#define __assert(buffer, cond, errorcode) \
    if (!cond)                            \
    {                                     \
        printf("Model %s\n", buffer);     \
        exit(errorcode);                  \
    }

// Random but weighted choices
int choices[] = {1, -1, 1, -1, 1, 1, -1, 1, -2, -1, 0, 0, 0, 1, 1, -1, 1, 0, 1, -1, 1, 1, 2, 1};

int unknown()
{
    int nums = sizeof(choices) / sizeof(choices[0]);
    return choices[(rand() % nums) - 1];
}

void logModel(char *buffer, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vsprintf(buffer, fmt, args);
    va_end(args);
}
