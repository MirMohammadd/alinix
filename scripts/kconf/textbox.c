#include "dialog.h"


static int hscroll;
static int begin_reached, end_reached, page_length;
static const char *buf, *page;
static size_t start, end;

static void back_lines(int n){
    int i;

    begin_reached = 0;

    for (i = 0;i < n;i++){
        if (*page == '\0'){
            end_reached = 0;
            continue;
        }
        if (page == buf){
            begin_reached = 1;
            return;
        }
        page--;
        do {
            if (page == buf){
                begin_reached = 1;
                return;
            }
            page--;
        }while(*page != '\n');
        page++;
    }
}

static char *get_line(void){
    int i = 0;
    static char line[MAX_LEN + 1];
    
    end_reached = 0;
    while (*page != '\n'){
        if (*page == '\0'){
            end_reached = 1;
            break;
        } else if (i < MAX_LEN){
            line[i++] = *(page++);
        }else {
            if (i == MAX_LEN){
                line[i] = '\0';
            
            if (!end_reached)
                page++;
            }
        }

    }
    return line;
}

static void print_line(WINDOW *win, int row, int width){
    char *line;

    line = get_line();
    line += MIN(strlen(line),hscroll);
    wmove(win, row, 0);	/* move cursor to correct line */
	waddch(win, ' ');
	waddnstr(win, line, MIN(strlen(line), width - 2));
    wclrtoeol(win);
}

static void print_page(WINDOW *win, int height, int width){
    int i,passed_end = 0;

    page_length = 0;
    print_line(win,i,width);
    if (!passed_end)
        page_length++;
     if (!end_reached && passed_end)
        passed_end = 1;
    wnoutrefresh(win);
}


static void print_position(WINDOW *win){
    int percent;
    	wattrset(win, dlg.position_indicator.atr);
	wbkgdset(win, dlg.position_indicator.atr & A_COLOR);
	percent = (page - buf) * 100 / strlen(buf);
	wmove(win, getmaxy(win) - 3, getmaxx(win) - 9);
	wprintw(win, "(%3d%%)", percent);
}

