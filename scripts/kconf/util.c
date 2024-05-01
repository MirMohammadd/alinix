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

