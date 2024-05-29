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

/**
 * @abstraction:
 * 	- Implement the graphic models.
*/
#include <alinix/types.h>
#include <alinix/graphics/model.h>
#include <alinix/kernel.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Graphic models")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("0.1")

#define	INSTRUCTION_CLOCK_FREQUENCY	80000000
#define WORD_VAL uint32_t


uint8_t tcon_value;

/**
 * @brief Sets a register in the display device with the provided address and value.
 * 
 * This function selects the appropriate register in the display device based on the address provided.
 * If the least significant bit of the address is set (1), the function writes the value directly to the display register.
 * If the least significant bit of the address is not set (0), the function left-shifts the value by 8 bits before writing it to the display register.
 * 
 * @param address The address of the register to be set (16-bit unsigned integer).
 * @param value The value to be written to the register (8-bit unsigned integer).
 */

void display_set_register(uint16_t address,uint8_t value){
    DISPLAY_REGISTER_SELECT(0);
    DISPLAY_CS(0);

    DISPLAY_REGISTER_SELECT(1);			//Select data

    if(address & 0x0001)
	    {
			DISPLAY_WRITE_DATA(value);
		}
    else
	    {
			DISPLAY_WRITE_DATA(value << 8);
		}
}

/**
 * @brief Controls the Timing Controller (TCON) settings for the display device.
 * 
 * This function adjusts the TCON settings based on the provided mask and level values.
 * If the level is 0, the function clears the bits specified by the mask in the TCON value.
 * If the level is non-zero, the function sets the bits specified by the mask in the TCON value.
 * After adjusting the TCON value, it calls the display_set_register function to update the TCON register in the display device.
 * 
 * @param mask The bitmask indicating which bits to modify in the TCON value (8-bit unsigned integer).
 * @param level The level (0 or non-zero) that determines whether to clear or set the masked bits in the TCON value (8-bit unsigned integer).
 */

void display_tcon_ctrl(uint8_t mask, uint8_t level){
    if (level == 0)
        tcon_value &= ~mask;

    else 
        tcon_value |= mask;
    display_set_register(0xAC, tcon_value);
}

/**
 * @brief  Initiates various display model settings and configurations
 * 
 * This function will initiate the display mode by setting up various registers with specific values to configure the display device.
 * Performs various tasks to setup the pixels and timing settings, and pixel output  mode. 
 * It also enables RGB saving and power-saving configurations .
 * @arg  none
 * 
*/

void display_model_initialise(NO_ARGS){
    uint16_t data;
    DISPLAY_RESET(0);
	DISPLAY_CS(1);
    display_delay_ms(10);
    DISPLAY_RESET(1);
    display_delay_ms(100);


    display_set_register(0x0126, 0x0a);						//PLL Clock Setting Register 0 - Set N = 10
	display_set_register(0x0127, 200);						//PLL Clock Setting Register 1 - Set M = 200
	display_set_register(0x012b, 0xae);						//PLL Clock Setting Register 2 - Set to 0xAE
	display_set_register(0x0126, 0x8a);						//PLL Clock Setting Register 0 - Enable PLL

	//----- VIDEO BUFFER MEMORY CLOCK SETUP -----
	//Memory frequency = PLL frequency / (MCLK + 1)
	display_set_register(0x0004, 0);						//MCLK Divider, 0 = 80MHz

    //----- PIXEL OUTPUT CLOCK SETUP (LCD_SHIFT SIGNAL) -----
	//PCLK frequency = MCLK frequency * (PCLK Frequency Ratio + 1) / 0x100000
	display_set_register(0x0158, 0x00);						//PCLK Frequency Ratio Register 0
	display_set_register(0x0159, 0x00);						//PCLK Frequency Ratio Register 1
	display_set_register(0x015a, 0x02);	

        display_set_register(0x0010, 0x61);						//Panel Type Register - non CSTN LCD panel, color LCD panel, 18bit Data Width, TFT LCD Panel Type


	//-------------------------------------------
	//----- SETUP THE DISPLAY DRIVE SIGNALS -----
	//-------------------------------------------
	//To get a new display to work set the rotation to 0 (in the Special Effects Register) and work through each of these settings.
	
	//See "Panel Timing Parameters" and "Panel Configuration Registers" section of "SSD1926 Application Note" for details of how the following registers setup the display

	//----- HORIZONTAL TOTAL HT -----
	//Total horizontal pixel clock periods
	//This register must be programmed such that the following condition is fulfilled: HDPS + HDP < HT
	//Horizontal Total ((REG[12h] bits7:0) x 8) + (REG[13h] bits2:0) + 1
	display_set_register(0x0013, ((281 - 1) & 0x0007));		//Horizontal Total Register 0 (bits2:0)
	display_set_register(0x0012, ((281 - 1) >> 3));	

    display_set_register(0x0014, ((240 - 8) / 8));			//Horizontal Display Period Register

	//----- HORIZONTAL DISPLAY PERIOD START HDPS -----
	//Number of null clocks from start of new line before horizontal data is displayed
	//Horizontal Display Period Start Position ((REG[17h] bits2:0, REG[16h] bits7:0))
	display_set_register(0x0016, (30 & 0x0ff)); 			//Horizontal Display Period Start Position Register 0
	display_set_register(0x0017, (30 >> 8));				//Horizontal Display Period Start Position Register 1

	//----- HORIZONTAL SYNC SIGNAL START HPS -----
	//LLINE Pulse Start Position (REG[23h] bits 2-0, REG[22h] bits 7-0) + 1
	display_set_register(0x0022, (0 & 0x0ff)); 				//LLINE Pulse Start Position Register 0
	display_set_register(0x0023, (0 >> 8));					//LLINE Pulse Start Position Register 1

	//----- HORIZONTAL SYNCRONIZATION PULSE WIDTH HPW -----
	//LLINE Pulse Width (REG[20h] bits6:0) + 1
	display_set_register(0x0020, 24);	

    	display_set_register(0x0018, (326 & 0x0ff));			//Vertical Total Register 0
	display_set_register(0x0019, (326 >> 8));				//Vertical Total Register 1

	//----- VERTICAL DISPLAY PERIOD VDP -----
	//Set to your screen's vertical pixel resolution
	//Vertical Display Period ((REG[1Dh] bits1:0, REG[1Ch] bits7:0) + 1) x HT
	display_set_register(0x001c, ((320 - 1) & 0x0ff)); 		//Vertical Display Period Register 0
	display_set_register(0x001d, ((320 - 1) >> 8)); 			//Vertical Display Period Register 1

	//----- VERTICAL DISPLAY PERIOD START VDPS -----
	//Vertical Display Period Start Position (REG[1Fh] bits2:0, REG[1Eh] bits7:0) x HT
	display_set_register(0x001e, (4 & 0x0ff)); 			//Vertical Display Period Start Position Register 0
	display_set_register(0x001f, (4 >> 8));				//Vertical Display Period Start Position Register 1

	//----- VERTICAL SYNC SIGNAL START VPS -----
	//LFRAME Pulse Start Position (REG[27h] bits2:0, REG[26h] bits7:0) x HT + (REG[31h] bits2:0, REG[30h] bits7:0)
	display_set_register(0x0026, (0 & 0x0ff));				//Vertical Display Period Start Position Register 0
	display_set_register(0x0027, (0 >> 8));					//Vertical Display Period Start Position Register 1

	//----- VERTICAL SYNCRONIZATION PULSE WIDTH VPW -----
	//LFRAME Pulse Width ((REG[24h] bits2:0) + 1) x HT + (REG[35h] bits2:0, REG[34h] bits7:0) � (REG[31h] bits2:0, REG[30h] bits7:0)
	display_set_register(0x0024, 3);

    	display_set_register(0x0071, 0x41);						//Special Effects Register: DisplayDataByteSwap= , rotation= � (rotation 90� and 180� require your hoz and vertical parameters to be swapped)



	//----- MAIN WINDOW DISPLAY START ADDRESS -----
	//Note that this is a double-word (32-bit) address. An entry of 00000h into these registers represents the first double-word of display memory, an entry of 00001h represents the second
	//double-word of the display memory, and so on.
	//bits16:0 = Image address � 4 (for Display Rotate Mode 0�)
    display_set_register(0x0074, (159 & 0x0000ff));			//Main Window Display Start Address Register 0
    display_set_register(0x0075, (159 & 0x00ff00) >> 8);		//Main Window Display Start Address Register 1
    display_set_register(0x0076, (159 >> 16));	
    	display_set_register(0x0078, ((320 / (32 / 16)) & 0x00ff));		//Main Window Line Address Offset Register 0
	display_set_register(0x0079, ((320 / (32 / 16)) >> 8));			//Main Window Line Address Offset Register 1

	//----- DISPLAY MODE REGISTER -----
	display_set_register(0x0070, 0x04);						//Display Mode Register - Enabled, dithering enabled, display color normal, 16 bits per pixel

	//----- RGB SETTINGS REGISTER -----
	display_set_register(0x01a4, 0xc0);						//RGB Setting Register - RGB (not YUV)

	//----- POWER SAVING CONFIGURATION REGISTER -----
	display_set_register(0x00a0, 0x00);						//Power Saving Configuration Register - On

	//----- LSHIFT POLARITY REGISTER -----
	display_set_register(0x0038, 0x01);						//LSHIFT Polarity Register:
															//0x01 = LSHIFT signal is falling trigger (data changes on falling edge of LSHIFT clock line)
															//0x00 = LSHIFT signal is rising trigger (data changes on rising edge of LSHIFT clock line)



	//----- LCD POWER CONTROL REGISTER -----
	display_set_register(0xad, 0x80);	
    	display_set_register(0xA8, 31);		//(BL | DC | CS | SDO | SCL)
	display_tcon_ctrl(0x08, 1);
	display_tcon_ctrl(0x01, 1);
	display_tcon_ctrl(0x04, 1);
	display_tcon_ctrl(0x02, 1);
	display_tcon_ctrl(0x10, 1);
    
	display_gpio_tcon(0x0028, 0x0006);
	display_gpio_tcon(0x0000, 0x0001);
	display_delay_ms(15);

	display_gpio_tcon(0x002B, 0x9532);
	display_gpio_tcon(0x0003, 0xAAAC);
	display_gpio_tcon(0x000C, 0x0002);
	display_gpio_tcon(0x000D, 0x000A);
	display_gpio_tcon(0x000E, 0x2C00);
	display_gpio_tcon(0x001E, 0x00AA);
	display_gpio_tcon(0x0025, 0x8000);
	display_delay_ms(15);

	display_gpio_tcon(0x0001, 0x2B3F);
	display_gpio_tcon(0x0002, 0x0600);
	display_gpio_tcon(0x0010, 0x0000);
	display_delay_ms(20);

	display_gpio_tcon(0x0005, 0x0000);
	display_gpio_tcon(0x0006, 0x0000);
	
	display_gpio_tcon(0x0016, 0xEF1C);
	display_gpio_tcon(0x0017, 0x0003);
	display_gpio_tcon(0x0007, 0x0233);
	display_gpio_tcon(0x000B, 0x5312);
	display_gpio_tcon(0x000F, 0x0000);
	display_delay_ms(20);

	display_gpio_tcon(0x0041, 0x0000);
	display_gpio_tcon(0x0042, 0x0000);
	display_gpio_tcon(0x0048, 0x0000);
	display_gpio_tcon(0x0049, 0x013F);
	display_gpio_tcon(0x0044, 0xEF00);
	display_gpio_tcon(0x0045, 0x0000);
	display_gpio_tcon(0x0046, 0x013F);
	display_gpio_tcon(0x004A, 0x0000);
	display_gpio_tcon(0x004B, 0x0000);
	display_delay_ms(20);

	display_gpio_tcon(0x0030, 0x0707);
	display_gpio_tcon(0x0031, 0x0704);
	display_gpio_tcon(0x0032, 0x0204);
	display_gpio_tcon(0x0033, 0x0201);
	display_gpio_tcon(0x0034, 0x0203);
	display_gpio_tcon(0x0035, 0x0204);
	display_gpio_tcon(0x0036, 0x0204);
	display_gpio_tcon(0x0037, 0x0502);
	display_gpio_tcon(0x003A, 0x0302);
	display_gpio_tcon(0x003B, 0x0500);
	display_delay_ms(20);
}

/**
 * @brief Sparks the delay which pause the execution for miliseconds.
 * @note Loops through until reaches the delay millisecond.
 * @param  ms Delay time in milliseconds(Should unsigned integer 16 bit).
 */
void display_delay_ms (uint16_t delay_ms){
    uint32_t count;

    while (delay_ms){
        count = (INSTRUCTION_CLOCK_FREQUENCY / 1000) /3;

        while(count){
            count--;
        }
    delay_ms--;
    }
}

void display_gpio_tcon(uint16_t index, uint16_t value)
{
    display_tcon_ctrl(0x01, 0);

    // Index
    display_tcon_ctrl(0x08, 0);
    // display_tcon_write_byte(((WORD_VAL)).v[1]);
    // display_tcon_write_byte(((WORD_VAL) ).v[0]);

    display_tcon_ctrl(0x01, 1);
    display_tcon_delay();
    display_tcon_ctrl(0x01, 0);

    // Data
    display_tcon_ctrl(0x08, 1);
    // display_tcon_write_byte(((WORD_VAL)).v[1]);
    // display_tcon_write_byte(((WORD_VAL)).v[0]);
    display_tcon_ctrl(0x01, 1);
    display_tcon_delay();
}

/**
 * @brief Settles value to the  required GPIO pin of TCON register.
 * @param gpio_pin The desired GPIO pin for which you want to set the value.
 * @note Do not make this function static.
*/

void display_write_pixel (uint16_t x_coord, uint16_t y_coord, uint32_t color)
{
	uint32_t address = 1;
	WORD_VAL w_temp;
	struct DWORD_VAL input_color;
	uint16_t output_color;
	
	//The driver always works with coordinate 0,0 in top left corner.
	//This function converts the required coordinates to the display address and then writes the pixel.
	//Adjust this function as requried for new screen models and orientations.
	//
	//SSD1926 with QVGA LCD
	//color is 16 bit:- 5Red|6Green|5Blue
	//Address 0 = top left corner.
	//2 address locations per pixel

	if (x_coord >= DISPLAY_WIDTH_PIXELS)
		return;
	if (y_coord >= DISPLAY_HEIGHT_PIXELS)
		return;

	#ifdef DISPLAY_BUS_INTERFACE_IS_BIG_ENDIAN
		//color is 16 bit:- 5Red|6Green|5Blue (big endian bus to SSD1926)
		input_color.Val = color;
		output_color = 0xff >> 3;		//Blue
		output_color |=  3;		//Green
		// output_color |= (uint16_t)(input_color.v[2] & 0xf8) << 8;		//Red
	#else
		//color is 16 bit:- 3GreenL|5Blue|5Red|3GreenH (little endian bus to SSD1926)
		input_color.Val = color;
		output_color = (uint16_t)(input_color.v[0] & 0xf8) << 5;		//Blue
		output_color |= (uint16_t)(input_color.v[1] & 0xe0) >> 5;		//Green bits 5:3
		output_color |= (uint16_t)(input_color.v[1] & 0x1c) << 11;	//Green bits 2:0
		output_color |= (uint16_t)(input_color.v[2] & 0xf8);			//Red
	#endif /*DISPLAY_BUS_INTERFACE_IS_BIG_ENDIAN*/


	//----- DO X COORD -----
	address += (x_coord << 1);

	//----- DO Y COORD -----
	address += ((uint32_t)y_coord * DISPLAY_WIDTH_PIXELS) << 1;

	//----- SET ADDRESS -----
	DISPLAY_REGISTER_SELECT(0);		//Select Command

	#ifdef DISPLAY_BUS_INTERFACE_IS_BIG_ENDIAN
		//Write M/R#, AB18:8 (SSD1926 in big endian mode)
		//Bit15 represent the M/R#, Bit15 = 1 means memory access, Bit15 = 0 means register access.
		//Bit14:11 = 0.
		//Bit10:0 represent the the address AB18:8.
		DISPLAY_WRITE_DATA(w_temp.Val);
		
		//Write AB7:0 | Mode_SL (SSD1926 in big endian mode)
		//Bit15:8 represent the address AB7:0 and Bit7:0 represent Mode_SL.
		//Mode_SL to select byte or word access during 16 bit mode. 0x00 means Byte access, 0x01 means word access.
		DISPLAY_WRITE_DATA(w_temp.Val);
	#else
		//Write AB15:8, M/R#, AB18:16 (SSD1926 in little endian mode)
		//Bit7 represent the M/R# (1 means memory access, 0 means register access)
		//Bit6:3 = 0
		//Bit2:0 | 15:8 represent the the address AB18:8
		w_temp.v[1] = ((DWORD_VAL) address).v[1];
		w_temp.v[0] = ((DWORD_VAL) address).v[2] | 0x80;
		DISPLAY_WRITE_DATA(w_temp.Val);
		
		//Write Mode_SL | AB7:0 (SSD1926 in little endian mode)
		//Bit7:0 represent the address AB7:0 and Bit15:8 represent Mode_SL (0x00 means Byte access, 0x01 means word access)
		w_temp.v[1] = 0x01;
		w_temp.v[0] = ((DWORD_VAL) address).v[0];
		DISPLAY_WRITE_DATA(w_temp.Val);
	#endif /*DISPLAY_BUS_INTERFACE_IS_BIG_ENDIAN*/

	DISPLAY_REGISTER_SELECT(1);		//Select Data
	
	//----- WRITE PIXEL -----
	DISPLAY_WRITE_DATA(output_color);
}
	

/**
 * @brief Functions that writes pixels to TCON pins
*/
void display_tcon_write_byte(uint8_t value)
{
    uint8_t    mask;

    mask = 0x80;
    while(mask)
    {
        display_tcon_ctrl(0x02, 0);
        display_tcon_delay();
        if(mask & value)
        {
            display_tcon_ctrl(0x04, 1);
        }
        else
        {
            display_tcon_ctrl(0x04, 0);
        }

        display_tcon_ctrl(0x02, 1);
        mask >>= 1;
    }
}

/**
 * @brief Implements delay on TCON screen.
 * @param none.
 * @return none.
*/
void display_tcon_delay(void)
{
    uint16_t timeOut;
    
    timeOut = 200;
    while(timeOut--)
    	;
}

