#ifndef __SCRIPTS_INTERNAL_DIALOG_H
#define __SCRIPTS_INTERNAL_DIALOG_H


#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#define WIDTH 30
#define HEIGHT 10



static int startX = 0;
static int startY = 0;


static const char* choices[] = {
    "Compile with GCC cross compiler",
    "Exit"
};


static int n_choices = sizeof(choices) / sizeof(char *);

void printMenu(WINDOW *menu_win, int highlight);
void printTitle();
int getInterfaceScreenSize();

#endif // __SCRIPTS_INTERNAL_DIALOG_H