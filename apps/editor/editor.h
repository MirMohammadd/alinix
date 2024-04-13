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

#else 
#include <types.h>
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
        #define KILO_QUERY_LEN 256
        #define KILO_QUIT_TIMES 3

        // #define FIND_RESTORE_HL do { \
        //     if (saved_hl) { \
        //         memcpy(E.row[saved_hl_line].hl,saved_hl, E.row[saved_hl_line].rsize); \
        //         free(saved_hl); \
        //         saved_hl = NULL; \
        //     } \
        // } while (0)

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

        }erow;

        typedef struct hlcolor{
            int r,g,b;
        }hlcolor;

        struct editorConfig {
        int cx,cy;  /* Cursor x and y position in characters */
        int rowoff;     /* Offset of row displayed. */
        int coloff;     /* Offset of column displayed. */
        int screenrows; /* Number of rows that we can show */
        int screencols; /* Number of cols that we can show */
        int numrows;    /* Number of rows */
        int rawmode;    /* Is terminal raw mode enabled? */
        erow *row;      /* Rows */
        int dirty;      /* File modified but not saved. */
        char *filename; /* Currently open filename */
        char statusmsg[80];
        time_t statusmsg_time;
        struct editorSyntax *syntax;    /* Current syntax highlight, or NULL. */
    };
    static struct editorConfig E;

    enum KEY_ACTION{
        KEY_NULL = 0,
        CTRL_C = 3,
        CTRL_D = 4,         /* Ctrl-d */
        CTRL_F = 6,         /* Ctrl-f */
        CTRL_H = 8,         /* Ctrl-h */
        TAB = 9,            /* Tab */
        CTRL_L = 12,        /* Ctrl+l */
        ENTER = 13,         /* Enter */
        CTRL_Q = 17,        /* Ctrl-q */
        CTRL_S = 19,        /* Ctrl-s */
        CTRL_U = 21,        /* Ctrl-u */
        ESC = 27,           /* Escape */
        BACKSPACE =  127,   /* Backspace */
        /* The following are just soft codes, not really reported by the
         * terminal directly. */
        ARROW_LEFT = 1000,
        ARROW_RIGHT,
        ARROW_UP,
        ARROW_DOWN,
        DEL_KEY,
        HOME_KEY,
        END_KEY,
        PAGE_UP,
        PAGE_DOWN
    };

        void editorSetStatusMessage(const char *fmt, ...);
        struct editorSyntax HLDB[] = {
            {
                /* C / C++ */
                C_HL_extensions,
                C_HL_keywords,
                "//","/*","*/",
                HL_HIGHLIGHT_STRINGS | HL_HIGHLIGHT_NUMBERS
            }
        };
        #define HLDB_ENTRIES (sizeof(HLDB)/sizeof(HLDB[0]))
        

        static struct termios orig_termios;
        struct abuf {
        char *b;
        int len;
        };

#define ABUF_INIT {NULL,0}

        void disableRawMode(int fd);
        void editorAtExit(void);
        int enableRawMode(int fd);
        int editorReadKey(int fd);
        int getCursorPosition(int ifd, int ofd, int *rows, int *cols);
        int getWindowSize(int ifd, int ofd, int *rows, int *cols);
        int is_separator(int c);
        int editorRowHasOpenComment(erow *row);
        void editorUpdateSyntax(erow *row);
        int editorSyntaxToColor(int hl);
        void editorSelectSyntaxHighlight(char *filename);
        void editorUpdateRow(erow *row);
        void editorInsertRow(int at, char *s, size_t len);
        void editorFreeRow(erow *row);
        void editorDelRow(int at);
        char *editorRowsToString(int *buflen) ;
        void editorRowInsertChar(erow *row, int at, int c);
        void editorRowAppendString(erow *row, char *s, size_t len);
        void editorRowDelChar(erow *row, int at);
        void editorInsertChar(int c);
        void editorInsertNewline(void);
        void editorDelChar();
        int editorOpen(char *filename);
        int editorSave(void);
        void abAppend(struct abuf *ab, const char *s, int len);
        void abFree(struct abuf *ab);
        void editorRefreshScreen(void);
        void editorSetStatusMessage(const char *fmt, ...);
        void editorFind(int fd);
        void editorMoveCursor(int key);
        void editorProcessKeypress(int fd);
        int editorFileWasModified(void) ;
        void updateWindowSize(void);
        void handleSigWinCh(int unused __attribute__((unused)));
        void initEditor(void);
        int main(int argc, char **argv);


}

#endif /* !_ALINIX_KERNEL_EDITOR_H */