#ifndef __SCRIPTS_KCONF_UTIL_H
#define __SCRIPTS_KCONF_UTIL_H

#include "dialog.h"
int on_key_resize(void);
void item_set_tag(char tag);
int on_key_esc(WINDOW *win);
void item_set_data(void *ptr);
int item_activate_selected(void);
void *item_data(void);
int item_n(void);
int item_is_tag(char tag);
char item_tag(void);
int item_count(void);
void item_reset(void);
void item_set_selected(int val);
void item_make(const char *fmt, ...);
void item_add_str(const char *fmt, ...);

int item_is_selected(void);
#endif /*__SCRIPTS_KCONF_UTIL_H*/