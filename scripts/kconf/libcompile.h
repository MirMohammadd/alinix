#ifndef LIBCOMPILE_H
#define LIBCOMPILE_H

#include <stdio.h>
#include "setdir.h"

void compile_this_dos(){
    /*This should the first repository to be compiled.*/
    if (!set_dir("ThisDos"))
        return;
    system("make");
    system("make install");
}



#endif