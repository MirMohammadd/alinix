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
#ifndef _SEGMENT_H_
#define _SEGMENT_H_

/**
 * @file segment.h
 * @author Konstantin Tcholokachvili
 * @date 2013
 * @license MIT License
 * 
 * x86 Segment
 */

/** Unused by the processor */
#define NULL_SEGMENT        0
#define KERNEL_CODE_SEGMENT 1
#define KERNEL_DATA_SEGMENT 2

/**
 * Builds a value for a segment register
 */
#define X86_BUILD_SEGMENT_REGISTER_VALUE(segment_index) \
	( (0) /* Descriptor Priviledge Level 0 */           \
	| (0) /* Not in LDT */                              \
	| ((segment_index) << 3) )
	

#endif // _SEGMENT_H_
