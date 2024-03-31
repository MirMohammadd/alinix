/**
 * MIT License
 *
 * Copyright (c) 2024 Heisenberg
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * @author Heisenberg

 */
#ifndef IO_H 
#define IO_H



#ifndef NULL
#define NULL 0
#endif 


typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef signed char sint8;
typedef signed short sint16;
typedef signed int sint32;
typedef unsigned char           uint8_t;  
typedef unsigned long long int  uint64_t;	/**< 64 bits unsigned */
typedef unsigned long int       uint32_t; 	/**< 32 bits unsigned */
typedef unsigned short int      uint16_t; 	/**< 16 bits unsigned */
typedef unsigned char           uint8_t;  	/**< 8  bits unsigned */
typedef unsigned char           uchar_t;  	/**< 8  bits unsigned */
typedef uint8 byte;
typedef uint16 word;
typedef uint32 dword;
typedef unsigned long long uint64;
typedef long long int64;
typedef int64 qword;
typedef uint32 size_t; 
typedef signed long int         int32_t; 	/**< 32 bits signed */
typedef uint32 fd_t;
typedef enum {
    FALSE,
    TRUE
} BOOL;

#endif
