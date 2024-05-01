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