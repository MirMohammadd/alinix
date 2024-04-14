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

#ifndef _PIT_H_
#define _PIT_H_

/**
 * @file pit.h
 * @author Konstantin Tcholokachvili
 * @date 2013, 2014
 * @license MIT License
 *
 * @see [en] i82C54's datasheet
 * @see [en] http://www.osdever.net/bkerndev/Docs/pit.htm
 * @see [en] http://www.jamesmolloy.co.uk/tutorial_html/5.-IRQs and the PIT.html
 *
 * Programmable Interrupt Timer
 */

#include <lib/types.h>

/** 
 * Changes timer interrupt frequency from the default one (18.222 Hz)
 * 
 * @param frequency Frequency at which interrupts whill be raised
 * @return status Status indicating the success of operation
 */
ret_t x86_pit_set_frequency(uint32_t frequency);

/**
* Timer's interrupt handler called periodically
*
* @param id
*/
void timer_interrupt_handler(int number);

#endif // _PIT_H_

