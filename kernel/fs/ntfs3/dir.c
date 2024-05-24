/**
 ** This file is part of AliNix.

**AliNix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**AliNix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with AliNix. If not, see <https://www.gnu.org/licenses/>.
*/

/**
 * @abstraction:
 *  - NTFS3 driver implemented here.
*/

#include "ntfs_fs.h"
#include <alinix/types.h>
#include <alinix/nls.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("NTFS3 driver")
MODULE_LICENSE("AGPL-3.0")


/* Convert little endian UTF-16 to NLS string. */
int ntfs_utf16_to_nls(struct ntfs_sb_info *sbi, const  *name, u32 len,
		      u8 *buf, int buf_len){
        

    int ret,warn;
    u8 *op;
            }