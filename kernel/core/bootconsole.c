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
 *  - Provides utility for booting console.
*/

#include <alinix/bootconsole.h>
#include <alinix/serialport.h>

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
void WriteLine(char* str)
{
    Write(str);
    Write("\n");
}

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
uint16_t* GetBuffer()
{
    return videoMemory;
}

void SetX(int x)
{
    XOffset = x;
}
void SetY(int y)
{
    YOffset = y;
}