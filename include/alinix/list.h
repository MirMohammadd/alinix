#ifndef __ALINIX_KERNEL_LIST_H
#define __ALINIX_KERNEL_LIST_H

#include <alinix/types.h>

struct list_head {
	struct list_head *next, *prev;
};


static inline bool __list_add_valid(struct list_head *new,
					     struct list_head *prev,
					     struct list_head *next){
        bool ret = true;

        if (next->prev == prev && prev->next == next && new != prev && new != next){
            return true;
        }
        ret = false;
        
    
    return ret;
}




#endif // __ALINIX_KERNEL_LIST_H