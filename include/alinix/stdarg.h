#ifndef __ALINIX_KERNEL_STD_ARG_H
#define __ALINIX_KERNEL_STD_ARG_H

typedef __builtin_va_list va_list;
typedef char *va_list;

#define	STACKITEM	int

#define	VA_SIZE(TYPE)					\
	((sizeof(TYPE) + sizeof(STACKITEM) - 1)	\
		& ~(sizeof(STACKITEM) - 1))

#define	va_start(AP, LASTARG)	\
	(AP=((va_list)&(LASTARG) + VA_SIZE(LASTARG)))

#define va_end(AP)

#define va_arg(AP, TYPE)	\
	(AP += VA_SIZE(TYPE), *((TYPE *)(AP - VA_SIZE(TYPE))))


int printf (const char *format, ...);
int vsnprintf(char *buf,size_t size,const char* fmt,va_list ap);

#endif