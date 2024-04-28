#ifndef __ALINIX_KERNEL_UAPI_CONST_H
#define __ALINIX_KERNEL_UAPI_CONST_H

#ifdef __ASSEMBLY__
#define _AC(X,Y)	X
#define _AT(T,X)	X
#else
#define __AC(X,Y)	(X##Y)
#define _AC(X,Y)	__AC(X,Y)
#define _AT(T,X)	((T)(X))
#endif

#define _UL(x)		(_AC(x, UL))
#define _ULL(x)		(_AC(x, ULL))

#endif /*__ALINIX_KERNEL_UAPI_CONST_H*/