#ifndef __ALINIX__LOG_H
#define __ALINIX__LOG_H

#include <alinix/types.h>

#define LOG_SHOW_MS 1


//? Use typedef?
enum LogLevel
{
    Info,
    Warning,
    Error
};

void Log(enum LogLevel level, const char* __restrict__ format, ...);
void Print(const char* data, uint32_t length);

#endif /*__ALINIX__LOG_H*/