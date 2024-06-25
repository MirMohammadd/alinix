/**
 * @author Ali Mirmohammad
 * @file bootconsole.c
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
 *  - Provides utility for booting console.
*/

#include <alinix/bootconsole.h>
#include <alinix/serialport.h>
#include <alinix/module.h>


MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Provides utility for booting console.")
MODULE_LICENSE("AGPLv3")
MODULE_VERSION("1.0")


/*/////////////////
// Static variable initialisations
/*/////////////////
int XOffset = 0;
int YOffset = 0;
// static uint8_t BackgroundColor = VGA_COLOR_BLACK; //Default console background color
// static uint8_t ForegroundColor = VGA_COLOR_WHITE; //Default console foreground color
// bool BootConsoleWriteToSerial = false;
bool BootConsoleWriteToSerial;
/*/////////////////
// Variables
/*/////////////////
static uint16_t* videoMemory = (uint16_t*)0xC00B8000;


/*/////////////////
// Private functions
/*/////////////////
/**
 * @brief Scrolls the contents of the video memory up by one line.
 *
 * This function scrolls the contents of the video memory up by one line, effectively moving each line up by one position.
 * It does this by copying the contents of each line to the line above it.
 * The bottom line of the video memory is cleared with a space character and the current text attributes.
 */
void Scroll()
{
    for(int i = 0; i < 24; i++){
        for (int m = 0; m < 80; m++){
            videoMemory[i * 80 + m] = videoMemory[(i + 1) * 80 + m];
        }
    }

    for(int x = 0; x < 80; x++)
    {
        uint16_t attrib = (BackgroundColor << 4) | (ForegroundColor & 0x0F);
        volatile uint16_t * where;
        where = (volatile uint16_t *)videoMemory + (24 * VGA_WIDTH + x) ;
        *where = ' ' | (attrib << 8);
    }
}



/*/////////////////
// Public functions
/*/////////////////
/**
 * @brief Initializes the console for console output.
 *
 * This function initializes the console for console output. It sets the `BootConsoleWriteToSerial` flag based on the value of the `enableSerial` parameter.
 * If `enableSerial` is true, it initializes the serial port and writes a log message to indicate the start of the serial log.
 *
 * @param enableSerial A boolean value indicating whether to enable serial output.
 */
void ConsoleInit(bool enableSerial)
{
    BootConsoleWriteToSerial = enableSerial;
    if(enableSerial)
    {
        Init(COM1);
        WriteLine("Start of serial log for Alinix");
    }
}

// void Write(char c)
// {
//     static char* str = " ";
//     str[0] = c;
//     Write(str);
// }

/**
 * @brief Writes a string to the console.
 *
 * This function writes a string to the console. It first checks if serial output is enabled (`BootConsoleWriteToSerial` flag is true). If so, it calls the `WriteStr` function to write the string to the serial port.
 * The function then iterates over each character in the string and performs the following actions:
 * - If the character is a newline (`'\n'`), it resets the XOffset to 0 and increments the YOffset.
 * - If the character is a tab (`'\t'`), it writes four spaces to simulate a tab.
 * - For any other character, it writes the character to the video memory at the current XOffset and YOffset, with the current text attributes. It then increments the XOffset.
 * If the XOffset exceeds 80, it resets the XOffset to 0 and increments the YOffset.
 * If the YOffset exceeds 25, it performs a scroll operation to move the contents of the video memory up by one line and resets the XOffset and YOffset.
 *
 * @param str The string to write to the console.
 */
void Write(char* str)
{
    if (BootConsoleWriteToSerial)
        WriteStr(str);
        

    for(int i = 0; str[i] != '\0'; ++i)
    {
        switch(str[i])
        {
            case '\n':
                XOffset = 0;
                YOffset++;
                break;
            case '\t':
                Write("    "); //4 spaces for tab
                break;
            default:
                uint16_t attrib = (BackgroundColor << 4) | (ForegroundColor & 0x0F);
                volatile uint16_t * where;
                where = (volatile uint16_t *)videoMemory + (YOffset * 80 + XOffset) ;
                *where = str[i] | (attrib << 8);
                XOffset++;
                break;
        }

        if(XOffset >= 80)
        {
            XOffset = 0;
            YOffset++;
        }

        if(YOffset >= 25)
        {
            Scroll();
            XOffset = 0;
            YOffset = 24;
        }
    }
}
/**
 * @brief Writes a string to the console followed by a newline character.
 *
 * This function writes a string to the console followed by a newline character. It calls the `Write` function to write the string to the console and then writes a newline character.
 *
 * @param str The string to write to the console.
 */
void WriteLine(char* str)
{
    Write(str);
    Write("\n");
}
/**
 * @brief Clears the console by filling it with spaces using the current text attributes.
 *
 * This function clears the console by filling it with spaces using the current text attributes.
 * It iterates over each position in the video memory and writes a space character with the current text attributes.
 * After clearing the console, it resets the XOffset and YOffset to 0.
 */
void ConsoleClear()
{
    for(int y = 0; y < VGA_HEIGHT; y++)
        for(int x = 0; x < VGA_WIDTH; x++) {
                uint16_t attrib = (BackgroundColor << 4) | (ForegroundColor & 0x0F);
                volatile uint16_t * where;
                where = (volatile uint16_t *)videoMemory + (y * VGA_WIDTH + x) ;
                *where = ' ' | (attrib << 8);
        }

    XOffset = 0;
    YOffset = 0;
}

/**
 * @brief Returns a pointer to the video memory buffer.
 *
 * This function returns a pointer to the video memory buffer. The video memory buffer contains the contents of the console screen.
 * The returned pointer can be used to directly access and modify the contents of the console screen.
 *
 * @return A pointer to the video memory buffer.
 */
uint16_t* GetBuffer()
{
    return videoMemory;
}


/**
 * @brief Sets the XOffset to the specified value.
 *
 * This function sets the XOffset to the specified value. The XOffset represents the horizontal position of the cursor on the console screen.
 *
 * @param x The value to set the XOffset to.
 */
void SetX(int x)
{
    XOffset = x;
}
/**
 * @brief Sets the YOffset to the specified value.
 *
 * This function sets the YOffset to the specified value. The YOffset represents the vertical position of the cursor on the console screen.
 *
 * @param y The value to set the YOffset to.
 */
void SetY(int y)
{
    YOffset = y;
}