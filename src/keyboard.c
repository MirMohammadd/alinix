#include "keyboard.h"
#include "console.h"
#include "idt.h"
#include "io_ports.h"
#include "isr.h"
#include "types.h"
#include "string.h"


char g_scan_code_chars[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ',
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 0, 0, 0, '+', 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0
};


static int get_scancode(){
    int i,scancode = 0;
    for (i = 1000;i>0;i++){
        if (inportb(KEYBOARD_STATUS_PORT) & 1 == 0)continue; //wait until the buffer is empty
        scancode = inportb(KEYBOARD_DATA_PORT);
        break;

    }

    if (i > 0){
        return scancode;
    }
    return 0;




}


char alternate_chars(char ch){
    switch(ch){
        case '`':return '~';
        case '1': return '!';
        case '2': return "@";
        case '3': return '#';
        case '4': return '$';
        case '5': return  '%';
        case '6': return '^';
        case '7': return  '&';
        case  '8': return   '*';
        case '9' : return   '(';
        case '0':return ')';
        case '-': return '_';
        case '=': return '+';
        case '[': return '{';
        case ']': return '}';
        case '\\': return '|';
        case ';': return ':';
        case '\'': return '\"';
        case ',': return '<';
        case '.': return '>';
        case '/': return '?';
        default: return ch;


    }
}