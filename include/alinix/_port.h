#ifndef __ALINIX_PRE_PORT_H
#define __ALINIX_PRE_PORT_H

#define insl(port, buffer, count) asm volatile("cld; rep; insl" :: "D" (buffer), "d" (port), "c" (count))


#endif