#include "editor.h"
#include <types.h>

void disableRawMode(int fd){
    if (E.rawmode){
        tcsetattr(fd,TCSAFLUSH,&orig_termios);
        E.rawmode = 0;
    }
}

void editorAtExit(void){
    disableRawMode(STDIN_FILENO);
}