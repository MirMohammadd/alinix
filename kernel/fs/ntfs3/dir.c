#include "ntfs_fs.h"
#include <alinix/types.h>
#include <alinix/nls.h>


/* Convert little endian UTF-16 to NLS string. */
int ntfs_utf16_to_nls(struct ntfs_sb_info *sbi, const  *name, u32 len,
		      u8 *buf, int buf_len){
        

    int ret,warn;
    u8 *op;
            }