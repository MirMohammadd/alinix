#ifndef _ALINIX_KERNEL_EDITOR_H
#define _ALINIX_KERNEL_EDITOR_H

/**
 * @ref https://github.com/HeisenbergCipherCracker/kilo/blob/master/kilo.c
*/

#ifdef __STD_INCLUDE__
#include <termios.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdarg.h>
#include <fcntl.h>
#include <signal.h>
#endif /* __STD_INCLUDE__ */


namespace LIBHeisenKernel
{
    namespace editor
    {
        /**
         * @brief Defining the macros here
        */
        #define HL_NORMAL 0
        #define HL_NONPRINT 1
        #define HL_COMMENT 2   /* Single line comment. */
        #define HL_MLCOMMENT 3 /* Multi-line comment. */
        #define HL_KEYWORD1 4
        #define HL_KEYWORD2 5
        #define HL_STRING 6
        #define HL_NUMBER 7
        #define HL_MATCH 8      /* Search match. */

        #define HL_HIGHLIGHT_STRINGS (1<<0)
        #define HL_HIGHLIGHT_NUMBERS (1<<1)

        /**
         * @brief Defining the structures here
        */
        

        struct editorSyntax{
            char **filematch;
            char **keywords;
            char single_comment_start[2];
            char multiline_comment_start[3];
            char multiline_comment_end[3];
            int flags;
        };
        /* This structure represents a single line of the file we are editing. */
        typedef struct erow{
            int idx; /*Row index in the editor.*/
            int size; /*Row length in characters.*/
            int rsize; /*Row length in display cells.*/
            char *render; /*Row content.*/
            char *highlight; /*Row syntax highlighting.*/
            unsigned char *hl;  /* Syntax highlight type for each character in render.*/
            int hl_oc;   

        };
    }
}

#endif /* !_ALINIX_KERNEL_EDITOR_H */