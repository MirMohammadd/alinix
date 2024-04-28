#ifndef __ALINIX_KERNEL_GRAPHICS_MODEL_H
#define __ALINIX_KERNEL_GRAPHICS_MODEL_H

#include <alinix/types.h>
#include <alinix/bytes.h>

/* Graphics Model */

#define DISPLAY_CS(state)					(state ? mPORTGSetBits(BIT_13) : mPORTGClearBits(BIT_13))		//0 = Select Controller
#define DISPLAY_REGISTER_SELECT(state)		(state ? mPORTBSetBits(BIT_10) : mPORTBClearBits(BIT_10))		//0 = Command, 1 = Data
#define	DISPLAY_RESET(state)				(state ? mPORTASetBits(BIT_10) : mPORTAClearBits(BIT_10))		//0 = Reset Controller

#define	DISPLAY_WRITE_DATA(data)									//Write 16bit word to controller

//----------------------------------------------
//----- DEFINE TARGET COMPILER & PROCESSOR -----
//----------------------------------------------
//(ONLY 1 SHOULD BE INCLUDED, COMMENT OUT OTHERS)
#define	DISPLAY_USING_MICROCHIP_C32_COMPILER
//<< add other compiler types here


//-------------------------
//----- DISPLAY SETUP -----
//-------------------------
#define	DISPLAY_WIDTH_PIXELS			320			//Width is the X coordinate
#define	DISPLAY_HEIGHT_PIXELS			240			//Height is the Y coordinate


//------------------------
//----- USER OPTIONS -----
//------------------------
#define	DISPLAY_BUS_INTERFACE_IS_BIG_ENDIAN		//Comment out if little endian selected using SSD1926 pin CNF4 (CNF4=H=BigEndian)


//########################################


void display_set_register (uint16_t address, uint8_t value);
void display_tcon_ctrl(uint8_t mask, uint8_t level);
void display_model_initialise(NO_ARGS);
void display_delay_ms (uint16_t delay_ms);

#endif