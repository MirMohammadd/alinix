#include "dialog.h"


void printMenu(WINDOW *menu_win, int highlight){
    int x,y,i;

    x = 2;
    y = 2;

    box(menu_win,0,0);

    for (i = 0;i <= n_choices;++i){
        if (highlight == i+1){
            wattron(menu_win, A_REVERSE);
            wattron(menu_win, COLOR_PAIR(1)); // Set color pair 1 (you can define more pairs if needed)
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, COLOR_PAIR(1));
            wattroff(menu_win, A_REVERSE);
        } // Needs to be printed
    }
}