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

void dialog_clear(void){
    int lines,columns;
    lines = getmaxy(stdscr);
    columns = getmaxx(stdscr);

    attr_clear(stdscr,lines,columns,dlg.screen.atr);
    	if (dlg.backtitle != NULL) {
		int i, len = 0, skip = 0;
		struct subtitle_list *pos;

		wattrset(stdscr, dlg.screen.atr);
		mvwaddstr(stdscr, 0, 1, (char *)dlg.backtitle);

		for (pos = dlg.subtitles; pos != NULL; pos = pos->next) {
			/* 3 is for the arrow and spaces */
			len += strlen(pos->text) + 3;
		}

		wmove(stdscr, 1, 1);
		if (len > columns - 2) {
			const char *ellipsis = "[...] ";
			waddstr(stdscr, ellipsis);
			skip = len - (columns - 2 - strlen(ellipsis));
		}

		for (pos = dlg.subtitles; pos != NULL; pos = pos->next) {
			if (skip == 0)
				waddch(stdscr, ACS_RARROW);
			else
				skip--;

			if (skip == 0)
				waddch(stdscr, ' ');
			else
				skip--;

			if (skip < strlen(pos->text)) {
				waddstr(stdscr, pos->text + skip);
				skip = 0;
			} else
				skip -= strlen(pos->text);

			if (skip == 0)
				waddch(stdscr, ' ');
			else
				skip--;
		}

		for (i = len + 1; i < columns - 1; i++)
			waddch(stdscr, ACS_HLINE);
	}
	wnoutrefresh(stdscr);
}


int init_dialog(const char *backtitle)
{
	int height, width;

	initscr();		/* Init curses */

	/* Get current cursor position for signal handler in mconf.c */
	getyx(stdscr, saved_y, saved_x);

	getmaxyx(stdscr, height, width);
	if (height < WINDOW_HEIGTH_MIN || width < WINDOW_WIDTH_MIN) {
		endwin();
		return -ERRDISPLAYTOOSMALL;
	}

	dlg.backtitle = backtitle;
	color_setup(getenv("MENUCONFIG_COLOR"));

	keypad(stdscr, TRUE);
	cbreak();
	noecho();
	dialog_clear();

	return 0;
}



void set_dialog_back_title(const char*backtitle){
    dlg.backtitle = backtitle;
}
void set_dialog_subtitles(struct subtitle_list *subtitles)
{
	dlg.subtitles = subtitles;
}


void end_dialog(int x,int y){
    move(x,y);
    refresh();
    endwin();
}

void print_title(WINDOW *dialog, const char *title, int width){
    if (title){
        int tlen = MIN(width -2,strlen(title));
        wattrset(dialog, dlg.title.atr);
		mvwaddch(dialog, 0, (width - tlen) / 2 - 1, ' ');
		mvwaddnstr(dialog, 0, (width - tlen)/2, title, tlen);
		waddch(dialog, ' ');
    }
}

void print_autowrap(WINDOW * win, const char *prompt, int width, int y, int x)
{
	int newl, cur_x, cur_y;
	int prompt_len, room, wlen;
	char tempstr[MAX_LEN + 1], *word, *sp, *sp2, *newline_separator = 0;

	strcpy(tempstr, prompt);

	prompt_len = strlen(tempstr);

	if (prompt_len <= width - x * 2) {	/* If prompt is short */
		wmove(win, y, (width - prompt_len) / 2);
		waddstr(win, tempstr);
	} else {
		cur_x = x;
		cur_y = y;
		newl = 1;
		word = tempstr;
		while (word && *word) {
			sp = strpbrk(word, "\n ");
			if (sp && *sp == '\n')
				newline_separator = sp;

			if (sp)
				*sp++ = 0;

			/* Wrap to next line if either the word does not fit,
			   or it is the first word of a new sentence, and it is
			   short, and the next word does not fit. */
			room = width - cur_x;
			wlen = strlen(word);
			if (wlen > room ||
			    (newl && wlen < 4 && sp
			     && wlen + 1 + strlen(sp) > room
			     && (!(sp2 = strpbrk(sp, "\n "))
				 || wlen + 1 + (sp2 - sp) > room))) {
				cur_y++;
				cur_x = x;
			}
			wmove(win, cur_y, cur_x);
			waddstr(win, word);
			getyx(win, cur_y, cur_x);

			/* Move to the next line if the word separator was a newline */
			if (newline_separator) {
				cur_y++;
				cur_x = x;
				newline_separator = 0;
			} else
				cur_x++;

			if (sp && *sp == ' ') {
				cur_x++;	/* double space */
				while (*++sp == ' ') ;
				newl = 1;
			} else
				newl = 0;
			word = sp;
		}
	}
}

/*
 * Print a button
 */
void print_button(WINDOW * win, const char *label, int y, int x, int selected)
{
	int i, temp;

	wmove(win, y, x);
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

/*
 * Draw a rectangular box with line drawing characters
 */
void
draw_box(WINDOW * win, int y, int x, int height, int width,
	 chtype box, chtype border)
{
	int i, j;

	wattrset(win, 0);
	for (i = 0; i < height; i++) {
		wmove(win, y + i, x);
		for (j = 0; j < width; j++)
			if (!i && !j)
				waddch(win, border | ACS_ULCORNER);
			else if (i == height - 1 && !j)
				waddch(win, border | ACS_LLCORNER);
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

/*
 * Draw shadows along the right and bottom edge to give a more 3D look
 * to the boxes
 */
void draw_shadow(WINDOW * win, int y, int x, int height, int width)
{
	int i;

	if (has_colors()) {	/* Whether terminal supports color? */
		wattrset(win, dlg.shadow.atr);
		wmove(win, y + height, x + 2);
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

/*
 * ncurses uses ESC to detect escaped char sequences. This resutl in
 * a small timeout before ESC is actually delivered to the application.
 * lxdialog suggest <ESC> <ESC> which is correctly translated to two
 * times esc. But then we need to ignore the second esc to avoid stepping
 * out one menu too much. Filter away all escaped key sequences since
 * keypad(FALSE) turn off ncurses support for escape sequences - and that's
 * needed to make notimeout() do as expected.
 */
int on_key_esc(WINDOW *win)
{
	int key;
	int key2;
	int key3;

	nodelay(win, TRUE);
	keypad(win, FALSE);
	key = wgetch(win);
	key2 = wgetch(win);
	do {
		key3 = wgetch(win);
	} while (key3 != ERR);
	nodelay(win, FALSE);
	keypad(win, TRUE);
	if (key == KEY_ESC && key2 == ERR)
		return KEY_ESC;
	else if (key != ERR && key != KEY_ESC && key2 == ERR)
		ungetch(key);

	return -1;
}

/* redraw screen in new size */
int on_key_resize(void)
{
	dialog_clear();
	return KEY_RESIZE;
}

struct dialog_list *item_cur;
struct dialog_list item_nil;
struct dialog_list *item_head;

void item_reset(void)
{
	struct dialog_list *p, *next;

	for (p = item_head; p; p = next) {
		next = p->next;
		free(p);
	}
	item_head = NULL;
	item_cur = &item_nil;
}

void item_make(const char *fmt, ...)
{
	va_list ap;
	struct dialog_list *p = malloc(sizeof(*p));

	if (item_head)
		item_cur->next = p;
	else
		item_head = p;
	item_cur = p;
	memset(p, 0, sizeof(*p));

	va_start(ap, fmt);
	vsnprintf(item_cur->node.str, sizeof(item_cur->node.str), fmt, ap);
	va_end(ap);
}

void item_add_str(const char *fmt, ...)
{
	va_list ap;
	size_t avail;

	avail = sizeof(item_cur->node.str) - strlen(item_cur->node.str);

	va_start(ap, fmt);
	vsnprintf(item_cur->node.str + strlen(item_cur->node.str),
		  avail, fmt, ap);
	item_cur->node.str[sizeof(item_cur->node.str) - 1] = '\0';
	va_end(ap);
}

void item_set_tag(char tag)
{
	item_cur->node.tag = tag;
}
void item_set_data(void *ptr)
{
	item_cur->node.data = ptr;
}

void item_set_selected(int val)
{
	item_cur->node.selected = val;
}

int item_activate_selected(void)
{
	item_foreach()
		if (item_is_selected())
			return 1;
	return 0;
}

void *item_data(void)
{
	return item_cur->node.data;
}

char item_tag(void)
{
	return item_cur->node.tag;
}

int item_count(void)
{
	int n = 0;
	struct dialog_list *p;

	for (p = item_head; p; p = p->next)
		n++;
	return n;
}

void item_set(int n)
{
	int i = 0;
	item_foreach()
		if (i++ == n)
			return;
}

int item_n(void)
{
	int n = 0;
	struct dialog_list *p;

	for (p = item_head; p; p = p->next) {
		if (p == item_cur)
			return n;
		n++;
	}
	return 0;
}

const char *item_str(void)
{
	return item_cur->node.str;
}

int item_is_selected(void)
{
	return (item_cur->node.selected != 0);
}

int item_is_tag(char tag)
{
	return (item_cur->node.tag == tag);
}
