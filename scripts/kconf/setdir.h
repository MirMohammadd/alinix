#ifndef SETDIR_H
#define SETDIR_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>


static int is_dir(char* dir) {
    char *directory_path = dir;

    if (access(directory_path, F_OK) == 0) {
        return 1;
    } else {
        return 0;
    }


}


bool set_dir(char* dir) {
    if (is_dir(dir)) {
        chdir(dir);
        return true;
    } else {
        return false;
    }
}
#endif