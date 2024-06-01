/**
 * @author Ali Mirmohammad
 * @file intel_hdmi_lpe_audio.h
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
 *  - Kernel header file for intel audio.
*/
#ifndef __ALINIX_KERNEL_INTEL_HDMI_IPE_AUDIO_H
#define __ALINIX_KERNEL_INTEL_HDMI_IPE_AUDIO_H



#define HAD_MIN_CHANNEL		2
#define HAD_MAX_CHANNEL		8
#define HAD_NUM_OF_RING_BUFS	4

/* max 20bit address, aligned to 64 */
#define HAD_MAX_BUFFER		((1024 * 1024 - 1) & ~0x3f)
#define HAD_DEFAULT_BUFFER	(600 * 1024) /* default prealloc size */
#define HAD_MAX_PERIODS		256	/* arbitrary, but should suffice */
#define HAD_MIN_PERIODS		1
#define HAD_MAX_PERIOD_BYTES	((HAD_MAX_BUFFER / HAD_MIN_PERIODS) & ~0x3f)
#define HAD_MIN_PERIOD_BYTES	1024	/* might be smaller */
#define HAD_FIFO_SIZE		0 /* fifo not being used */
#define MAX_SPEAKERS		8

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

/* Maud Values */
#define AUD_SAMPLE_RATE_32_DP_2_7_MAUD_VAL		1988
#define AUD_SAMPLE_RATE_44_1_DP_2_7_MAUD_VAL		2740
#define AUD_SAMPLE_RATE_48_DP_2_7_MAUD_VAL		2982
#define AUD_SAMPLE_RATE_88_2_DP_2_7_MAUD_VAL		5480
#define AUD_SAMPLE_RATE_96_DP_2_7_MAUD_VAL		5965
#define AUD_SAMPLE_RATE_176_4_DP_2_7_MAUD_VAL		10961
#define HAD_MAX_RATE_DP_2_7_MAUD_VAL			11930
#define AUD_SAMPLE_RATE_32_DP_1_62_MAUD_VAL		3314
#define AUD_SAMPLE_RATE_44_1_DP_1_62_MAUD_VAL		4567
#define AUD_SAMPLE_RATE_48_DP_1_62_MAUD_VAL		4971
#define AUD_SAMPLE_RATE_88_2_DP_1_62_MAUD_VAL		9134
#define AUD_SAMPLE_RATE_96_DP_1_62_MAUD_VAL		9942
#define AUD_SAMPLE_RATE_176_4_DP_1_62_MAUD_VAL		18268
#define HAD_MAX_RATE_DP_1_62_MAUD_VAL			19884

#endif // __ALINIX_KERNEL_INTEL_HDMI_IPE_AUDIO_H