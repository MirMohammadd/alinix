/**
 * @author Ali Mirmohammad
 * @file chan_alsaradio.c
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
 *  - Kernel audio files driver.
*/
#include <alinix/init.h>
#include <alinix/kernel.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Kernel audio files driver")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("0.1")



#define DEBUG_CAPTURES	 		1

#define RX_CAP_RAW_FILE			"/tmp/rx_cap_in.pcm"
#define TX_CAP_RAW_FILE			"/tmp/tx_cap_in.pcm"

#define	MIXER_PARAM_MIC_PLAYBACK_SW 	"Mic Playback Switch"
#define MIXER_PARAM_MIC_PLAYBACK_VOL 	"Mic Playback Volume"
#define	MIXER_PARAM_MIC_CAPTURE_SW 	"Mic Capture Switch"
#define	MIXER_PARAM_MIC_CAPTURE_VOL 	"Mic Capture Volume"
#define	MIXER_PARAM_MIC_BOOST 		"Auto Gain Control"
#define	MIXER_PARAM_SPKR_PLAYBACK_SW 	"Speaker Playback Switch"
#define	MIXER_PARAM_SPKR_PLAYBACK_VOL 	"Speaker Playback Volume"



#define	DELIMCHR ','
#define	QUOTECHR 34

#include "soundcard.h"

/* ALSA and serial stuff */
#define ALSA_INDEV		"default"
#define ALSA_OUTDEV		"default"
#define DESIRED_RATE		8000
#define SERIAL_DEV		"/dev/ttyS0"

/* Lets use 160 sample frames, just like GSM.  */
#define FRAME_SIZE 160
#define PERIOD_FRAMES 80		/* 80 Frames, at 2 bytes each */


#define MAX_BUFFER_SIZE 100

int sim_cor = 0;		/* used to simulate COR active */

/* ALSA and serial stuff end */

#define O_CLOSE	0x444

#define	NTAPS 31

