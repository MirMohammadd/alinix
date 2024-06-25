/**
 * @author Ali Mirmohammad
 * @file intel_hdmi_audio.c
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
 * 	- Kernel intel for drivers audio files.
*/
#include <alinix/sound/x86/intel_hdmi_audio.h>
#include <alinix/kernel.h>
#include <alinix/sound/pcm.h>
#include <alinix/uapi/sound/asound.h>
#include "intel_hdmi_lpe_audio.h"
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Intel HDMI Audio Driver")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("1.0")


#define AUD_SAMPLE_RATE_32	32000
#define AUD_SAMPLE_RATE_44_1	44100
#define AUD_SAMPLE_RATE_48	48000
#define AUD_SAMPLE_RATE_88_2	88200
#define AUD_SAMPLE_RATE_96	96000
#define AUD_SAMPLE_RATE_176_4	176400
#define AUD_SAMPLE_RATE_192	192000

#define HAD_MIN_RATE		AUD_SAMPLE_RATE_32
#define HAD_MAX_RATE		AUD_SAMPLE_RATE_192

#define DIS_SAMPLE_RATE_25_2	25200
#define DIS_SAMPLE_RATE_27	27000
#define DIS_SAMPLE_RATE_54	54000
#define DIS_SAMPLE_RATE_74_25	74250
#define DIS_SAMPLE_RATE_148_5	148500
#define HAD_REG_WIDTH		0x08
#define HAD_MAX_DIP_WORDS		16

/* DP Link Rates */
#define DP_2_7_GHZ			270000
#define DP_1_62_GHZ			162000


static const int eld_speaker_allocation_bits[] = {
	[0] = FL | FR,
	[1] = LFE,
	[2] = FC,
	[3] = RL | RR,
	[4] = RC,
	[5] = FLC | FRC,
	[6] = RLC | RRC,
	/* the following are not defined in ELD yet */
	[7] = 0,
};

static struct cea_channel_speaker_allocation channel_allocations[] = {
/*                        channel:   7     6    5    4    3     2    1    0  */
{ .ca_index = 0x00,  .speakers = {   0,    0,   0,   0,   0,    0,  FR,  FL } },
				/* 2.1 */
{ .ca_index = 0x01,  .speakers = {   0,    0,   0,   0,   0,  LFE,  FR,  FL } },
				/* Dolby Surround */
{ .ca_index = 0x02,  .speakers = {   0,    0,   0,   0,  FC,    0,  FR,  FL } },
				/* surround40 */
{ .ca_index = 0x08,  .speakers = {   0,    0,  RR,  RL,   0,    0,  FR,  FL } },
				/* surround41 */
{ .ca_index = 0x09,  .speakers = {   0,    0,  RR,  RL,   0,  LFE,  FR,  FL } },
				/* surround50 */
{ .ca_index = 0x0a,  .speakers = {   0,    0,  RR,  RL,  FC,    0,  FR,  FL } },
				/* surround51 */
{ .ca_index = 0x0b,  .speakers = {   0,    0,  RR,  RL,  FC,  LFE,  FR,  FL } },
				/* 6.1 */
{ .ca_index = 0x0f,  .speakers = {   0,   RC,  RR,  RL,  FC,  LFE,  FR,  FL } },
				/* surround71 */
{ .ca_index = 0x13,  .speakers = { RRC,  RLC,  RR,  RL,  FC,  LFE,  FR,  FL } },

{ .ca_index = 0x03,  .speakers = {   0,    0,   0,   0,  FC,  LFE,  FR,  FL } },
{ .ca_index = 0x04,  .speakers = {   0,    0,   0,  RC,   0,    0,  FR,  FL } },
{ .ca_index = 0x05,  .speakers = {   0,    0,   0,  RC,   0,  LFE,  FR,  FL } },
{ .ca_index = 0x06,  .speakers = {   0,    0,   0,  RC,  FC,    0,  FR,  FL } },
{ .ca_index = 0x07,  .speakers = {   0,    0,   0,  RC,  FC,  LFE,  FR,  FL } },
{ .ca_index = 0x0c,  .speakers = {   0,   RC,  RR,  RL,   0,    0,  FR,  FL } },
{ .ca_index = 0x0d,  .speakers = {   0,   RC,  RR,  RL,   0,  LFE,  FR,  FL } },
{ .ca_index = 0x0e,  .speakers = {   0,   RC,  RR,  RL,  FC,    0,  FR,  FL } },
{ .ca_index = 0x10,  .speakers = { RRC,  RLC,  RR,  RL,   0,    0,  FR,  FL } },
{ .ca_index = 0x11,  .speakers = { RRC,  RLC,  RR,  RL,   0,  LFE,  FR,  FL } },
{ .ca_index = 0x12,  .speakers = { RRC,  RLC,  RR,  RL,  FC,    0,  FR,  FL } },
{ .ca_index = 0x14,  .speakers = { FRC,  FLC,   0,   0,   0,    0,  FR,  FL } },
{ .ca_index = 0x15,  .speakers = { FRC,  FLC,   0,   0,   0,  LFE,  FR,  FL } },
{ .ca_index = 0x16,  .speakers = { FRC,  FLC,   0,   0,  FC,    0,  FR,  FL } },
{ .ca_index = 0x17,  .speakers = { FRC,  FLC,   0,   0,  FC,  LFE,  FR,  FL } },
{ .ca_index = 0x18,  .speakers = { FRC,  FLC,   0,  RC,   0,    0,  FR,  FL } },
{ .ca_index = 0x19,  .speakers = { FRC,  FLC,   0,  RC,   0,  LFE,  FR,  FL } },
{ .ca_index = 0x1a,  .speakers = { FRC,  FLC,   0,  RC,  FC,    0,  FR,  FL } },
{ .ca_index = 0x1b,  .speakers = { FRC,  FLC,   0,  RC,  FC,  LFE,  FR,  FL } },
{ .ca_index = 0x1c,  .speakers = { FRC,  FLC,  RR,  RL,   0,    0,  FR,  FL } },
{ .ca_index = 0x1d,  .speakers = { FRC,  FLC,  RR,  RL,   0,  LFE,  FR,  FL } },
{ .ca_index = 0x1e,  .speakers = { FRC,  FLC,  RR,  RL,  FC,    0,  FR,  FL } },
{ .ca_index = 0x1f,  .speakers = { FRC,  FLC,  RR,  RL,  FC,  LFE,  FR,  FL } },
};

static const struct channel_map_table map_tables[] = {
	{ SNDRV_CHMAP_FL,       0x00,   FL },
	{ SNDRV_CHMAP_FR,       0x01,   FR },
	{ SNDRV_CHMAP_RL,       0x04,   RL },
	{ SNDRV_CHMAP_RR,       0x05,   RR },
	{ SNDRV_CHMAP_LFE,      0x02,   LFE },
	{ SNDRV_CHMAP_FC,       0x03,   FC },
	{ SNDRV_CHMAP_RLC,      0x06,   RLC },
	{ SNDRV_CHMAP_RRC,      0x07,   RRC },
	{} /* terminator */
};

/* hardware capability structure */
static const struct snd_pcm_hardware had_pcm_hardware = {
    .info =     (SNDRV_PCM_INFO_INTERLEAVED |
                 SNDRV_PCM_INFO_MMAP |
                 SNDRV_PCM_INFO_MMAP_VALID |
                 SNDRV_PCM_INFO_NO_PERIOD_WAKEUP),
    // .formats =  SNDRV_PCM_FMTBIT_S16_LE |
    //             SNDRV_PCM_FMTBIT_S24_LE |
    //             SNDRV_PCM_FMTBIT_S32_LE,
    .rates =    SNDRV_PCM_RATE_32000 |
                SNDRV_PCM_RATE_44100 |
                SNDRV_PCM_RATE_48000 |
                SNDRV_PCM_RATE_88200 |
                SNDRV_PCM_RATE_96000 |
                SNDRV_PCM_RATE_176400 |
                SNDRV_PCM_RATE_192000,
    .rate_min = HAD_MIN_RATE,
    .rate_max = HAD_MAX_RATE,
    .channels_min = HAD_MIN_CHANNEL,
    .channels_max = HAD_MAX_CHANNEL,
    .buffer_bytes_max = HAD_MAX_BUFFER,
    .period_bytes_min = HAD_MIN_PERIOD_BYTES,
    .period_bytes_max = HAD_MAX_PERIOD_BYTES,
    .periods_min = HAD_MIN_PERIODS,
    .periods_max = HAD_MAX_PERIODS,
    .fifo_size = HAD_FIFO_SIZE,
};

