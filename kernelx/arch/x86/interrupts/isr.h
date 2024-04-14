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

#ifndef _ISR_H_
#define _ISR_H_

/**
 * @file isr.h
 * @author Konstantin Tcholokachvili
 * @date 2013
 * @license MIT License
 *
 * Exceptions handling
 */

#include <arch/x86/registers.h>

/** Setup interruption service request handling */
void x86_isr_setup(void);

/** Interruption service request handler */
void x86_isr_handler(struct regs *r);

#endif // _ISR_H_
