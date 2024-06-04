/**
 * @author Ali Mirmohammad
 * @file textgui.c
 * *************************************IMPORTANT ALINIX LICENSE TERM********************************************
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
 *  - TextGUI utility implemented here.
*/
#include <alinix/textgui.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("TextGUI utility")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("0.1")


volatile uint16_t* videoMemory = (uint16_t*)0xC00B8000;

/**
 * Disable the text cursor on the screen.
 *
 * This function disables the text cursor by setting the appropriate values on the VGA controller.
 * It performs the following steps:
 *
 * 1. Writes the value 0x0A to the VGA controller's register 0x3D4 to select the cursor start register.
 * 2. Writes the value 0x20 to the VGA controller's register 0x3D5 to disable the cursor.
 *
 * @return void
 */
void DisableCursor()
{
    outportb(0x3D4, 0x0A);
	outportb(0x3D5, 0x20);
}
/**
 * Set the color and character of a pixel on the screen at the specified coordinates.
 *
 * This function sets the color and character of a pixel on the screen at the specified coordinates.
 * It performs the following steps:
 *
 * 1. Calculates the attribute value by combining the background color and foreground color.
 * 2. Sets the pixel on the screen at the specified coordinates with the provided character and attribute.
 *
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param color The color of the pixel.
 * @param character The character to display at the pixel.
 * @param background The background color of the pixel.
 *
 * @return void
 */
void SetPixel(int x, int y, char color, uint16_t character, char background)
{
    uint16_t attrib = (background << 4) | (color & 0x0F);
    *(videoMemory + (y * VGA_WIDTH + x)) = character | (attrib << 8);
}
/**
 * Clear the entire screen with a specified color.
 *
 * This function clears the entire screen by setting each pixel to the specified color.
 * It performs the following steps:
 *
 * 1. Iterates over each row of the screen.
 * 2. Iterates over each column of the current row.
 * 3. Calls the `SetPixel` function to set the pixel at the current coordinates to the specified color.
 *
 * @param color The color to use for clearing the screen.
 *
 * @return void
 */
void ClearScreen(char color)
{
    for(int y = 0; y < VGA_HEIGHT; y++)
        for(int x = 0; x < VGA_WIDTH; x++)
        // TODO check here
            SetPixel(x, y, color, ' ',VGA_COLOR_BLACK);
}
/**
 * Display a status bar with text and progress indication.
 *
 * This function displays a status bar on the screen with the provided text and progress indication.
 * It performs the following steps:
 *
 * 1. Clears the previous status bar by setting all pixels in the last row of the screen to the background color.
 * 2. Draws the provided text at the starting position on the status bar.
 * 3. Calculates the width of the progress bar based on the provided percentage.
 * 4. Draws the progress bar by filling the appropriate number of pixels with a progress character.
 * 5. Draws the closing bracket of the progress bar.
 *
 * @param text The text to display on the status bar.
 * @param percentage The percentage of progress completed [0-100].
 *
 * @return void
 */
void StatusBar(char* text, int percentage)
{
    /**
     * @param text: Text to display
     * @param percentage: Percentage of progress completed [0-100]
    */
    for(int x = 0; x < VGA_WIDTH; x++)
        SetPixel(x, VGA_HEIGHT - 1, TEXT_COLOR, ' ', VGA_COLOR_LIGHT_GREY);
    
    DrawString(text, 0, VGA_HEIGHT - 1, TEXT_COLOR, VGA_COLOR_LIGHT_GREY);

    const int barWidth = 20; //Amount of characters for status bar
    const int startX = VGA_WIDTH - barWidth - 1; //Start of progress bar
    int width = ((double)percentage / 100.0) * (double)barWidth;

    SetPixel(startX, VGA_HEIGHT - 1, VGA_COLOR_BLACK, '[', VGA_COLOR_LIGHT_GREY);
    for(int i = 0; i < width; i++)
        SetPixel(startX + i + 1, VGA_HEIGHT - 1, VGA_COLOR_BLACK, '#', VGA_COLOR_LIGHT_GREY);
    
    SetPixel(startX + barWidth, VGA_HEIGHT - 1, VGA_COLOR_BLACK, ']', VGA_COLOR_LIGHT_GREY);
}
/**
 * Draw a string of text on the screen.
 *
 * This function draws a string of text on the screen at the specified coordinates with the given color and background.
 * It iterates over each character in the text string and performs the following actions:
 * - If the character is a newline ('\n'), the cursor position is reset to the starting x-coordinate and the y-coordinate is incremented by 1.
 * - Otherwise, the `SetPixel` function is called to draw the character at the current cursor position with the specified color and background.
 *   The cursor position is then incremented by 1 in the x-coordinate direction.
 *
 * @param text The text string to draw.
 * @param x The x-coordinate of the starting position.
 * @param y The y-coordinate of the starting position.
 * @param color The color of the text.
 * @param background The background color of the text.
 *
 * @return void
 */
void TextDrawString(char* text, int x, int y, char color, char background)
{
    int px = x;
    int py = y;
    for(int i = 0; text[i] != '\0'; ++i) {
        switch(text[i]) {
            case '\n':
                px = x;
                py += 1;
                break;
            default:
                SetPixel(px, py, color, text[i], background);
                px++;
                break;
        }
    }
}