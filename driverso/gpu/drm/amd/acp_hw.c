#include <heisen/mm.h>
#include <heisen/slab.h>
#include <heisen/device.h>
#include <heisen/delay.h>
#include <heisen/errno.h>

#include "acp_gfx_if.h"

#define ACP_MODE_I2S	0
#define ACP_MODE_AZ	1

#define mmACP_AZALIA_I2S_SELECT 0x51d4

int amd_acp_hw_init(struct cgs_device *cgs_device,
		    unsigned acp_version_major, unsigned acp_version_minor)
{
	unsigned int acp_mode = ACP_MODE_I2S;

	if ((acp_version_major == 2) && (acp_version_minor == 2))
		acp_mode = cgs_read_register(cgs_device,
					mmACP_AZALIA_I2S_SELECT);

	if (acp_mode != ACP_MODE_I2S)
		return -ENODEV;

	return 0;
}