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



