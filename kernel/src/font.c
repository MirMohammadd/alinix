#include <alinix/gui/fonts/font.h>

void BoundingBox(const char* string, int* retW, int* retH, const void* data, const int* offsetTable)
{
    if(string == NULL || retW == NULL || retH == NULL)
        return; // Error with arguments

    if(data == NULL)
        return; // Not initialized

    // Reset variables
    *retW = 0;
    *retH = 0;

    int xOffset = 0;
    int yOffset = 0;
    while(*string)
    {
        // Get the character we need to draw for this string
        char c = *string++;

        // Set initial values for first character
        if(xOffset == 0 && yOffset == 0)
            yOffset = ((const uint8_t*)(data + offsetTable[0]))[1];

        // Check for newline
        if(c == '\n') {
            if(xOffset > *retW)
                *retW = xOffset;

            xOffset = 0;

            // Add the height of the space character. TODO: Update this!
            yOffset += ((const uint8_t*)(data + offsetTable[0]))[1] + 1;
            continue;
        }

        // Load data for this char from the font
        const uint8_t* charData = (const uint8_t*)(data + offsetTable[(int)c - 32]);
        xOffset += charData[0];
    }

    // Update return values
    // retW might already be correctly set by another line of text
    if(xOffset > *retW)
        *retW = xOffset;

    *retH = yOffset;
}
