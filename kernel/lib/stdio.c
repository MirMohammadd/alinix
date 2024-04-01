#include <libc/stdarg.h>


int printf (const char *format, ...)
{
    va_list ap;
    int len=0;
    	
    /* Start variabile argument's list */
    va_start (ap, format);
	char buffer[1024];

	len = vsprintf(buffer, format, ap);
	_kputs(buffer);
    va_end (ap); // end of arguments

    return len;
}