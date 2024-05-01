#include "dialog.h"

void print_button(WINDOW * win, const char *label, int y, int x, int selected){
    int i,temp;

    wmove(win,y,x);
    	wattrset(win, selected ? dlg.button_active.atr
		 : dlg.button_inactive.atr);
	waddstr(win, "<");
	temp = strspn(label, " ");
	label += temp;
	wattrset(win, selected ? dlg.button_label_active.atr
		 : dlg.button_label_inactive.atr);
	for (i = 0; i < temp; i++)
		waddch(win, ' ');
	wattrset(win, selected ? dlg.button_key_active.atr
		 : dlg.button_key_inactive.atr);
	waddch(win, label[0]);
	wattrset(win, selected ? dlg.button_label_active.atr
		 : dlg.button_label_inactive.atr);
	waddstr(win, (char *)label + 1);
	wattrset(win, selected ? dlg.button_active.atr
		 : dlg.button_inactive.atr);
	waddstr(win, ">");
	wmove(win, y, x + temp + 1);
}

void
draw_box(WINDOW * win, int y, int x, int height, int width,
	 chtype box, chtype border){
        int i,j;
        wattrset(win,0);
        for (i = 0;i < height;i++){
            wmove(win, y + i, x);
            for (j = 0; j < width; j++)
                if (!i && !j)
                    waddch(win, border | ACS_ULCORNER);
                else if (!i && j == width - 1)
                    waddch(win, box | ACS_URCORNER);
                else if (i == height - 1 && j == width - 1)
                    waddch(win, box | ACS_LRCORNER);
                else if (!i)
                    waddch(win, border | ACS_HLINE);
                else if (i == height - 1)
                    waddch(win, box | ACS_HLINE);
                else if (!j)
                    waddch(win, border | ACS_VLINE);
                else if (j == width - 1)
                    waddch(win, box | ACS_VLINE);
                else
                    waddch(win, box | ' ');
        }

     }

void draw_shadow(WINDOW * win, int y, int x, int height, int width){
    int i;
    if (has_colors()){
        wattrset(win, dlg.shadow.atr);
        wmove(win,y+height,x+2);
        for (i = 0; i < width; i++)
			waddch(win, winch(win) & A_CHARTEXT);
		for (i = y + 1; i < y + height + 1; i++) {
			wmove(win, i, x + width);
			waddch(win, winch(win) & A_CHARTEXT);
			waddch(win, winch(win) & A_CHARTEXT);
		}
		wnoutrefresh(win);
	}
    }

/*
 *  Return the position of the first alphabetic character in a string.
 */
int first_alpha(const char *string, const char *exempt)
{
	int i, in_paren = 0, c;

	for (i = 0; i < strlen(string); i++) {
		c = tolower(string[i]);

		if (strchr("<[(", c))
			++in_paren;
		if (strchr(">])", c) && in_paren > 0)
			--in_paren;

		if ((!in_paren) && isalpha(c) && strchr(exempt, c) == 0)
			return i;
	}

	return 0;
}

int on_key_esc(WINDOW *win){
    int key,key2,key3;

    nodelay(win,TRUE);
    keypad(win,FALSE);

    key = wgetch(win);
    key2 = wgetch(win);
    do {
        key3 = wgetch(win);
    }while(key3 != ERR);

    nodelay(win, FALSE);
	keypad(win, TRUE);
	if (key == KEY_ESC && key2 == ERR)
		return KEY_ESC;
	else if (key != ERR && key != KEY_ESC && key2 == ERR)
		ungetch(key);

	return -1;
}