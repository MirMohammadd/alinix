#ifndef __ALINIX_KERNEL_TEXTGUI_H
#define __ALINIX_KERNEL_TEXTGUI_H

#include <alinix/bootconsole.h>
#include <alinix/enums.h>
#include <alinix/types.h>


#define TEXT_COLOR VGA_COLOR_WHITE

void DisableCursor();
void SetPixel(int x, int y, char color,uint16_t character, char background);
void ClearScreen(char color );
void StatusBar(char* text, int percentage);
void DrawString(char* text, int x, int y, char color , char background );
#endif /*__ALINIX_KERNEL_TEXTGUI_H*/