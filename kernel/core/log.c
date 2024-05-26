/**
 ** This file is part of AliNix.

**AliNix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**AliNix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with AliNix. If not, see <https://www.gnu.org/licenses/>.
*/

/**
 * @abstraction:
 *  - Provides logging functionality while booting.
*/
#include <alinix/log.h>
#include <alinix/bootconsole.h>
#include <alinix/serialport.h>
#include <alinix/system.h>
#include <alinix/pit.h>
#include <alinix/module.h>


MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Provides logging functionality while booting.")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("0.1")


char* logLevelMessage[3] = {
    "[Info]",
    "[Warning]",
    "[Error]"
};

uint32_t GetMSSinceBoot()
{
    return 0;
}

void Log(enum LogLevel level, const char* __restrict__ format, ...)
{
    uint8_t prevColor =ForegroundColor;
    if(screenMode == TextMode)
    {
        #if LOG_SHOW_MS
        Write("["); Write(IntToString(GetMSSinceBoot())); Write("] ");
        #endif
        switch (level)
        {
            case Info:
                ForegroundColor = VGA_COLOR_BLACK;
                break;
            case Warning:
                ForegroundColor = VGA_COLOR_BROWN;
                break;
            case Error:
                ForegroundColor = VGA_COLOR_RED;
                break;
        }
        Write(logLevelMessage[level]); Write(": ");
    }
    else if(Initialized && (gdbEnabled == false))
    {
        #if LOG_SHOW_MS
        WriteStr("["); WriteStr(IntToString(GetMSSinceBoot())); WriteStr("] ");
        #endif
        WriteStr(logLevelMessage[level]); WriteStr(": ");
    }

    va_list parameters;
	va_start(parameters, format);
 
	while (*format != '\0') { 
		if (format[0] != '%' || format[1] == '%') {
			if (format[0] == '%')
				format++;
			uint32_t amount = 1;
			while (format[amount] && format[amount] != '%')
				amount++;
			Print(format, amount);
			format += amount;
			continue;
		}
 
		const char* format_begun_at = format++;
 
		if (*format == 'c') {
			format++;
			char c = (char) va_arg(parameters, int /* char promotes to int */);
			Print(&c, sizeof(c));
		} else if (*format == 's') {
			format++;
			const char* str = va_arg(parameters, const char*);
			uint32_t len = strlen(str);
			Print(str, len);
         } else if(*format == 'd') {
            format++;
            int n = va_arg(parameters, int);
            int numChars = 0;
            if (n < 0) { n = -n; numChars++; Print("-", 1); }

            int temp = n;
            do
            {
                numChars++;
                temp /= 10;
            } while (temp);

            Print(IntToString(n), numChars);
        } else if(*format == 'b') {
            format++;
            uint8_t n = va_arg(parameters, int);
            char* str = IntToHexString(n);
            Print("0x", 2); Print(str, sizeof(uint8_t)<<1);
            free(str);
        } else if(*format == 'w') {
            format++;
            uint16_t n = va_arg(parameters, int);
            char* str = IntToHexString(n);
            Print("0x", 2); Print(str, sizeof(uint16_t)<<1);
            free(str);
        } else if(*format == 'x') {
            format++;
            uint32_t n = va_arg(parameters, int);
            char* str = IntToHexString(n);
            Print("0x", 2); Print(str, sizeof(uint32_t)<<1);
            free(str);
        } else {
			format = format_begun_at;
			uint32_t len = strlen(format);
			Print(format, len);
			format += len;
		}
	}
 
	va_end(parameters);

    Print("\n", 1);

    if(screenMode == TextMode)
        ForegroundColor = prevColor;
}