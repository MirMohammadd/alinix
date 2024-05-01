#ifndef __SCRIPTS_K_CONF_DIALOG_H
#define __SCRIPTS_K_CONF_DIALOG_H

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>


#define KEY_ESC 27

#define item_foreach() \
	for (item_cur = item_head ? item_head: item_cur; \
	     item_cur && (item_cur != &item_nil); item_cur = item_cur->next)

#define MIN(x,y) (x < y ?x:y)
#define MAX(x,y) (x > y ? x : y)
#define MAX_LEN 2048
#define WIDTH 30
#define HEIGHT 10
#define TAB 9


int startx = 0;
int starty = 0;


/* minimum (re)size values */
#define CHECKLIST_HEIGTH_MIN 6	/* For dialog_checklist() */
#define CHECKLIST_WIDTH_MIN 6
#define INPUTBOX_HEIGTH_MIN 2	/* For dialog_inputbox() */
#define INPUTBOX_WIDTH_MIN 2
#define MENUBOX_HEIGTH_MIN 15	/* For dialog_menu() */
#define MENUBOX_WIDTH_MIN 65
#define TEXTBOX_HEIGTH_MIN 8	/* For dialog_textbox() */
#define TEXTBOX_WIDTH_MIN 8
#define YESNO_HEIGTH_MIN 4	/* For dialog_yesno() */
#define YESNO_WIDTH_MIN 4
#define WINDOW_HEIGTH_MIN 19	/* For init_dialog() */
#define WINDOW_WIDTH_MIN 80
#define ERRDISPLAYTOOSMALL (KEY_MAX + 1)



struct dialog_color {
	chtype atr;	/* Color attribute */
	int fg;		/* foreground */
	int bg;		/* background */
	int hl;		/* highlight this item */
};


char* choices[] = {
    "Compile Alinix Kernel with GCC cross compiler",
    "Exit"
};

struct subtitle_list{
    struct subtitle_list *next;
    const char *text;
};

struct dialog_info {
	const char *backtitle;
	struct subtitle_list *subtitles;
	struct dialog_color screen;
	struct dialog_color shadow;
	struct dialog_color dialog;
	struct dialog_color title;
	struct dialog_color border;
	struct dialog_color button_active;
	struct dialog_color button_inactive;
	struct dialog_color button_key_active;
	struct dialog_color button_key_inactive;
	struct dialog_color button_label_active;
	struct dialog_color button_label_inactive;
	struct dialog_color inputbox;
	struct dialog_color inputbox_border;
	struct dialog_color searchbox;
	struct dialog_color searchbox_title;
	struct dialog_color searchbox_border;
	struct dialog_color position_indicator;
	struct dialog_color menubox;
	struct dialog_color menubox_border;
	struct dialog_color item;
	struct dialog_color item_selected;
	struct dialog_color tag;
	struct dialog_color tag_selected;
	struct dialog_color tag_key;
	struct dialog_color tag_key_selected;
	struct dialog_color check;
	struct dialog_color check_selected;
	struct dialog_color uarrow;
	struct dialog_color darrow;
};


void inline setTitle(){
    attron(A_BOLD);
    attron(COLOR_PAIR(2)); // Set color pair 2 (you can define more pairs if needed)
    mvprintw(0, (COLS - 6) / 2, "Alinix");
    attroff(COLOR_PAIR(2));
    attroff(A_BOLD);
}
#define MAXITEMSTR 200

struct dialog_item {
	char str[MAXITEMSTR];	/* prompt displayed */
	char tag;
	void *data;	/* pointer to menu item - used by menubox+checklist */
	int selected;	/* Set to 1 by dialog_*() function if selected. */
};

struct dialog_list {
	struct dialog_item node;
	struct dialog_list *next;
};

int init_dialog(const char *backtitle);
void set_dialog_backtitle(const char *backtitle);
void set_dialog_subtitles(struct subtitle_list *subtitles);
void end_dialog(int x, int y);
void attr_clear(WINDOW * win, int height, int width, chtype attr);
void dialog_clear(void);
void print_autowrap(WINDOW * win, const char *prompt, int width, int y, int x);
void print_button(WINDOW * win, const char *label, int y, int x, int selected);
void print_title(WINDOW *dialog, const char *title, int width);
void draw_box(WINDOW * win, int y, int x, int height, int width, chtype box,
	      chtype border);
void draw_shadow(WINDOW * win, int y, int x, int height, int width);

int first_alpha(const char *string, const char *exempt);
int dialog_yesno(const char *title, const char *prompt, int height, int width);
int dialog_msgbox(const char *title, const char *prompt, int height,
		  int width, int pause);
int dialog_textbox(const char *title, const char *tbuf, int initial_height,
		   int initial_width, int *_vscroll, int *_hscroll,
		   int (*extra_key_cb)(int, size_t, size_t, void *), void *data);
int dialog_menu(const char *title, const char *prompt,
		const void *selected, int *s_scroll);
int dialog_checklist(const char *title, const char *prompt, int height,
		     int width, int list_height);
int dialog_inputbox(const char *title, const char *prompt, int height,
		    int width, const char *init);



extern struct dialog_info dlg;
extern char dialog_input_result[];
extern int saved_x, saved_y;	



#endif // __SCRIPTS_K_CONF_DIALOG_H