#ifndef __ALINIX_KERNEL_TEXTGUI_H
#define __ALINIX_KERNEL_TEXTGUI_H

#include <alinix/bootconsole.h>
#include <alinix/enums.h>
#include <alinix/types.h>


#define TEXT_COLOR VGA_COLOR_WHITE

        static void DisableCursor();
        static void SetPixel(int x, int y, char color,uint16_t character = ' ', char background = VGA_COLOR_BLUE);
        static void ClearScreen(char color = VGA_COLOR_BLACK);
        static void StatusBar(char* text, int percentage = 0);
        static void DrawString(char* text, int x, int y, char color = TEXT_COLOR, char background = VGA_COLOR_BLUE);
#endif /*__ALINIX_KERNEL_TEXTGUI_H*/