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
#ifndef _STATUS_H_
#define _STATUS_H_

/**
 * @file status.h
 * @author Konstantin Tcholokachvili
 * @date 2007, 2011, 2013
 * @license MIT License
 * 
 * Values which are returned from kernel functions
 */
 
 
#define KERNEL_OK                           0   
#define KERNEL_INVALID_VALUE                1   
#define KERNEL_OPERATION_NOT_SUPPORTED      2   
#define KERNEL_NO_MEMORY                    3
#define KERNEL_BUSY                         4
#define KERNEL_INTERRUPTED                  5	
#define KERNEL_PERMISSION_ERROR             6
#define KERNEL_UNRESOLVED_VIRTUAL_ADDRESS   7
#define KERNEL_INTERNAL_FATAL_ERROR         255 

#endif // _STATUS_H_
