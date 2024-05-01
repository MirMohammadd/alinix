#include "dialogconf.h"
#include <curses.h>

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
        }         else
        {
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        }// Needs to be printed
        ++y;
    }
    wrefresh(menu_win);
}

void printTitle(){
    attron(A_BOLD);
    attron(COLOR_PAIR(2)); // Set color pair 2 (you can define more pairs if needed)
    mvprintw(0, (COLS - 6) / 2, "Alinix Kernel Configuration settings");
    attroff(COLOR_PAIR(2));
    attroff(A_BOLD);
}

int main()
{
    WINDOW *menu_win;
    int highlight = 1;
    int choice = 0;
    int c;

    initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK); // Define color pair 1 as red text on black background
    init_pair(2, COLOR_CYAN, COLOR_BLACK); // Define color pair 2 as cyan text on black background
    clear();
    noecho();
    cbreak();
    startX = (COLS - WIDTH) / 2;
    startY = (LINES - HEIGHT) / 2;

    printTitle();

    menu_win = newwin(HEIGHT, WIDTH, startY, startX);
    keypad(menu_win, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL); // Enable mouse support
    mvprintw(LINES - 2, 0, "Use arrow keys to go up and down, Press enter to select a choice");
    refresh();
    printMenu(menu_win, highlight);

    while (1)
    {
        c = wgetch(menu_win);
        switch (c)
        {
        case KEY_MOUSE: // Handle mouse events
        {
            MEVENT event;
            if (getmouse(&event) == OK)
            {
                for (int i = 0; i < n_choices; ++i)
                {
                    if (event.y == startY + i + 2 && event.x >= startX + 2 && event.x <= startX + WIDTH - 3)
                    {
                        highlight = i + 1;
                        choice = highlight;
                        break;
                    }
                }
            }
            break;
        }
        case KEY_UP:
            if (highlight == 1)
                highlight = n_choices;
            else
                --highlight;
            break;
        case KEY_DOWN:
            if (highlight == n_choices)
                highlight = 1;
            else
                ++highlight;
            break;
        case 10:
            choice = highlight;
            break;
        default:
            mvprintw(LINES - 1, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
            refresh();
            break;
        }
        printMenu(menu_win, highlight);
        if (choice != 0) /* User did a choice come out of the infinite loop */
            break;
    }

    mvprintw(LINES - 1, 0, "You chose choice %d with choice string %s\n", choice, choices[choice - 1]);
    clrtoeol();
    refresh();
    endwin();
    return 0;
}