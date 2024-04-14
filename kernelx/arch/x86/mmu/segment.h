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
