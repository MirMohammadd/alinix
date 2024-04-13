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

int enableRawMode(int fd){
    struct termios raw;

    if (E.rawmode) return 0;
    if (tcsetattr(fd,TCSAFLUSH,&raw) < 0) goto fatal;
    E.rawmode = 1;
    return 0;

    fatal:
        errno = ENOTTY;
        return -1;
}