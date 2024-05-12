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
#include <alinix/drivers/e1000/hw.h>
#include <alinix/kernel.h>
#include <alinix/drivers/e1000/e1k_utils.h>
#include <alinix/init.h>

#define NB_MAX_DESC 256

#define DEVICE_NAME "Alinix e1000 network driver"
#define MAJOR_NUM 100
#define DEVICE_FILE_NAME "char_dev"


static uint8_t * map_mmio(void);
static void e1k_configure(void);
static void send_data(void);

uint8_t * bar0, * tx_buffer;
struct e1000_desc * tx_ring;

static int device_open(struct inode *inode, struct file *file){

}



