#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

/* Special keys */
#define CODE_BREAK      0x80

#define KEY_ESCAPE     0x1
#define KEY_SPACE      0x39
#define KEY_ENTER      0x1c
#define KEY_BACKSPACE  0xe
#define KEY_TAB        0xf
#define KEY_UPARROW    0x48
#define KEY_DOWNARROW  0x50
#define KEY_LEFTARROW  0x4B
#define KEY_RIGHTARROW 0x4D
#define KEY_PGUP       0x49
#define KEY_PGDOWN     0x51
#define EXTENDED       0xE0
#define EXTENDED_2     0x2A


#define KEY_LSHIFT     0x2a
#define KEY_RSHIFT     0x36
#define KEY_CTRL       0x1d
#define KEY_ALT        0x38
#define KEY_ALTGR      0x39

#define NUM_LED        0x45
#define SCROLL_LED     0x46
#define CAPS_LED       0x3a

#define BUFSIZE        256

#define ENABLED		   1
#define DISABLED       0

/* Procedures */


void keyboard_isr (void);
void keyboard_enable (void);
void keyboard_disable (void);
void _ksetleds (int, int, int);
int  set_shadow(int);
int  get_shadow();
int  _kgetch (void);

#endif