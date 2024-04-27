/**
 * @author Ali Mirmohammad
 * @file vsprintf.c
 * *************************************IMPORTANT ALINIX LICENSE TERM********************************************
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

#include <alinix/types.h>
#include <alinix/stdarg.h>
#include <alinix/compiler.h>
#include <alinix/limits.h>
#include <alinix/operator.h>




#define ZEROPAD	1		/* pad with zero */
#define SIGN	2		/* unsigned/signed long */
#define PLUS	4		/* show plus */
#define SPACE	8		/* space if plus */
#define LEFT	16		/* left justified */
#define SMALL	32		/* Must be 32 == 0x20 */
#define SPECIAL	64		/* 0x */
#define WIDE	128		/* UTF-16 string */

#define PUTC(c) \
do {				\
	if (pos < size)		\
		buf[pos] = (c);	\
	++pos;			\
} while (0);

PRIVATE size_t utf16s_utf8nlen(const uint16_t *s16, int maxlen);
static
char *number(char *end, unsigned long long num, int base, char locase)
{
	/*
	 * locase = 0 or 0x20. ORing digits or letters with 'locase'
	 * produces same digits or (maybe lowercased) letters
	 */

	/* we are called with base 8, 10 or 16, only, thus don't need "G..."  */
	static const char digits[16] = "0123456789ABCDEF"; /* "GHIJKLMNOPQRSTUVWXYZ"; */

	switch (base) {
	case 10:
		if (num != 0)
			end = put_dec(end, num);
		break;
	case 8:
		for (; num != 0; num >>= 3)
			*--end = '0' + (num & 07);
		break;
	case 16:
		for (; num != 0; num >>= 4)
			*--end = digits[num & 0xf] | locase;
		break;
	default:
		unreachable();
	}

	return end;
}

static
uint32_t utf16_to_utf32(const uint16_t **s16)
{
	uint16_t c0, c1;

	c0 = *(*s16)++;
	/* not a surrogate */
	if ((c0 & 0xf800) != 0xd800)
		return c0;
	/* invalid: low surrogate instead of high */
	if (c0 & 0x0400)
		return 0xfffd;
	c1 = **s16;
	/* invalid: missing low surrogate */
	if ((c1 & 0xfc00) != 0xdc00)
		return 0xfffd;
	/* valid surrogate pair */
	++(*s16);
	return (0x10000 - (0xd800 << 10) - 0xdc00) + (c0 << 10) + c1;
}

static
unsigned long long get_number(int sign, int qualifier, va_list *ap)
{
	if (sign) {
		switch (qualifier) {
		case 'L':
			return va_arg(*ap, long long);
		case 'l':
			return va_arg(*ap, long);
		case 'h':
			return (short)va_arg(*ap, int);
		case 'H':
			return (signed char)va_arg(*ap, int);
		default:
			return va_arg(*ap, int);
		};
	} else {
		switch (qualifier) {
		case 'L':
			return va_arg(*ap, unsigned long long);
		case 'l':
			return va_arg(*ap, unsigned long);
		case 'h':
			return (unsigned short)va_arg(*ap, int);
		case 'H':
			return (unsigned char)va_arg(*ap, int);
		default:
			return va_arg(*ap, unsigned int);
		}
	}
}

size_t strnlen(const char * s, size_t count)
{
	const char *sc;

	for (sc = s; count-- && *sc != '\0'; ++sc)
		/* nothing */;
	return sc - s;
}

static inline int isdigit(int ch)
{
	return (ch >= '0') && (ch <= '9');
}


static
int skip_atoi(const char **s)
{
	int i = 0;

	while (isdigit(**s))
		i = i * 10 + *((*s)++) - '0';
	return i;
}


PRIVATE
int get_int(const char **fmt, va_list *ap)
{
	if (isdigit(**fmt))
		return skip_atoi(fmt);
	if (**fmt == '*') {
		++(*fmt);
		/* it's the next argument */
		return va_arg(*ap, int);
	}
	return 0;
}

static
char get_sign(long long *num, int flags)
{
	if (!(flags & SIGN))
		return 0;
	if (*num < 0) {
		*num = -(*num);
		return '-';
	}
	if (flags & PLUS)
		return '+';
	if (flags & SPACE)
		return ' ';
	return 0;
}

PRIVATE
int get_flags(const char **fmt){
    int flags = 0;

	do {
		switch (**fmt) {
		case '-':
			flags |= LEFT;
			break;
		case '+':
			flags |= PLUS;
			break;
		case ' ':
			flags |= SPACE;
			break;
		case '#':
			flags |= SPECIAL;
			break;
		case '0':
			flags |= ZEROPAD;
			break;
		default:
			return flags;
		}
		++(*fmt);
	} while (1);
}

int vsnprintf(char *buf, size_t size, const char *fmt, va_list ap){
    /*Maximum pace needed to print 64 bit number in octal*/
    char tmp[(sizeof(unsigned long long) * 8+2) / 3];
    char *tmp_end = &tmp[sizeof(tmp) / sizeof(tmp)[0]];
    long long num;
    int base;
    const char *s;
    size_t len,pos;
    char sign;
    int flags;		/* flags to number() */

	int field_width;	/* width of output field */
	int precision;		/* min. # of digits for integers; max
				   number of chars for from string */
	int qualifier;		/* 'h', 'hh', 'l' or 'll' for integer fields */

	va_list args;


    for (pos = 0;*fmt;++fmt){
        if (*fmt != '%' || *++fmt == '%') {
			PUTC(*fmt);
			continue;
		}
        flags = get_flags(&fmt);

    }

    field_width = get_int(&fmt,&args);

    if (field_width < 0){
        field_width = -field_width; //? Change to (unsigned)?
        flags |= LEFT;

    }
    if (flags & LEFT){
        flags &= ~ZEROPAD;
    precision = -1;
    if (*fmt == '.') {
        ++fmt;
        precision = get_int(&fmt, &args);
        if (precision >= 0)
            flags &= ~ZEROPAD;
    }
    qualifier = -1;
    if (*fmt == "h" || *fmt == "l"){
        qualifier = *fmt;
        ++fmt;
        if (qualifier == *fmt){
            qualifier -= 'a'-'A';
            ++fmt;
        }
    }
    sign = 0;

    switch(*fmt){
        case 'c':
            flags &= LEFT;
            s = tmp;
            if (qualifier == 'l'){
                ((uint16_t *)tmp)[0] = (uint16_t)va_arg(args, unsigned int);
                ((uint16_t *)tmp)[1] = L'\0';
				precision = INT_MAX;
				goto wstring;
            }else {
				tmp[0] = (unsigned char)va_arg(args, int);
				precision = len = 1;
			}
            goto output;
        
        case 's':
            flags  &= LEFT;
            if (precision < 0){
                precision = INT_MAX;

            }
            s = va_arg(args,void *);

            if (!s){
                s = precision < 6 ? "" : "(null)";
            }
            else if (qualifier == 'l'){
            wstring:
				flags |= WIDE;
				precision = len = utf16s_utf8nlen((const uint16_t *)s, precision);
				goto output;
            }
            precision = len = strnlen(s, precision);
			goto output;
        
        case 'o':
            base = 8;
            break;
        case 'p':
            if (precision < 0)
				precision = 2 * sizeof(void *);
			fallthrough;
        case 'x':
			flags |= SMALL;
			fallthrough;
		case 'X':
			base = 16;
			break;

		case 'd':
		case 'i':
			flags |= SIGN;
			fallthrough;
		case 'u':
			flags &= ~SPECIAL;
			base = 10;
			break;
        default:
			/*
			 * Bail out if the conversion specifier is invalid.
			 * There's probably a typo in the format string and the
			 * remaining specifiers are unlikely to match up with
			 * the arguments.
			 */
			goto fail;

    }
    if (*fmt == 'p'){
        num = (unsigned long)va_arg(args, void *);
    }else {
        num = get_number(flags & SIGN, qualifier, &args);
    }
    sign = get_sign(&num,flags);
    if (sign)
        --field_width;
    s = number(tmp_end, num, base, flags & SMALL);
    len = tmp_end - s;
    /* default precision is 1 */
    if (precision < 0)
        precision = 1;
    /* precision is minimum number of digits to print */
    if (precision < len)
        precision = len;
    
    if (flags & SPECIAL){
        if (base == 8 && precision == len)
            ++precision;
        if (base == 16 && precision > 0)
            field_width -= 2;
        else
            flags &= ~SPECIAL;

        if ((flags & ZEROPAD) && field_width > precision)
			precision = field_width;
    }
output:
		/* Calculate the padding necessary */
		field_width -= precision;
		/* Leading padding with ' ' */
		if (!(flags & LEFT))
			while (field_width-- > 0)
				PUTC(' ');
		/* sign */
		if (sign)
			PUTC(sign);
		/* 0x/0X for hexadecimal */
		if (flags & SPECIAL) {
			PUTC('0');
			PUTC( 'X' | (flags & SMALL));
		}
		/* Zero padding and excess precision */
		while (precision-- > len)
			PUTC('0');
		/* Actual output */
		if (flags & WIDE) {
			const uint16_t *ws = (const uint16_t *)s;

			while (len-- > 0) {
				uint32_t c32 = utf16_to_utf32(&ws);
				uint8_t *s8;
				size_t clen;

				if (c32 < 0x80) {
					PUTC(c32);
					continue;
				}
                

				/* Number of trailing octets */
				clen = 1 + (c32 >= 0x800) + (c32 >= 0x10000);

				len -= clen;
				s8 = (uint8_t *)&buf[pos];

				/* Avoid writing partial character */
				PUTC('\0');
				pos += clen;
				if (pos >= size)
					continue;

				/* Set high bits of leading octet */
				*s8 = (0xf00 >> 1) >> clen;
				/* Write trailing octets in reverse order */
				for (s8 += clen; clen; --clen, c32 >>= 6)
					*s8-- = 0x80 | (c32 & 0x3f);
				/* Set low bits of leading octet */
				*s8 |= c32;
			}
		} else {
			while (len-- > 0)
				PUTC(*s++);
		}
		/* Trailing padding with ' ' */
		while (field_width-- > 0)
			PUTC(' ');
	}

fail:
	va_end(args);

	if (size)
		buf[min(pos, size-1)] = '\0';

	return pos;
}

PRIVATE
size_t utf16s_utf8nlen(const uint16_t *s16,  int maxlen)
{
	size_t len, clen;

	for (len = 0; len < maxlen && *s16; len += clen) {
		uint16_t c0 = *s16++;

		/* First, get the length for a BMP character */
		clen = 1 + (c0 >= 0x80) + (c0 >= 0x800);
		if (len + clen > maxlen)
			break;
		/*
		 * If this is a high surrogate, and we're already at maxlen, we
		 * can't include the character if it's a valid surrogate pair.
		 * Avoid accessing one extra word just to check if it's valid
		 * or not.
		 */
		if ((c0 & 0xfc00) == 0xd800) {
			if (len + clen == maxlen)
				break;
			if ((*s16 & 0xfc00) == 0xdc00) {
				++s16;
				++clen;
			}
		}
	}

	return len;
}