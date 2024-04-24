#ifndef __ALINIX_KERNEL_NET_PERF_H
#define __ALINIX_KERNEL_NET_PERF_H


void perf_print(unsigned long c1l, unsigned long c1h,
		unsigned long c2l, unsigned long c2h,
		char *key);


#define PERF_START  { \
                         unsigned long __c1l, __c1h, __c2l, __c2h; \
                         __asm__(".byte 0x0f, 0x31" : "=a" (__c1l), "=d" (__c1h))
#define PERF_STOP(x)   __asm__(".byte 0x0f, 0x31" : "=a" (__c2l), "=d" (__c2h)); \
                       perf_print(__c1l, __c1h, __c2l, __c2h, x);}

#endif