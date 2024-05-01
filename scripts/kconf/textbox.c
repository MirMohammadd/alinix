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

