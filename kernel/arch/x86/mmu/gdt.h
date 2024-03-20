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
#ifndef _GDT_H_
#define _GDT_H_

/**
 * @file gdt.h
 * @author Konstantin Tcholokachvili
 * @date 2013
 * @see IA-32 Intel Architecture Software Developer's Manual, Volume 3 [Chapter 3]
 * @note The chosen segmentation mechanism model is Basic Flat Model as
 * paging allows closer control
 *
 * GDT setup
 */

#include <lib/types.h>

/** Setup GDT by initializing the GDTR register */
void x86_gdt_setup(void);


#endif // _GDT_H_
