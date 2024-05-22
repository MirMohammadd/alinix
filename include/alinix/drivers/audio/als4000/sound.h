#ifndef __SOUND_DRIVER_SOUND_H
#define __SOUND_DRIVER_SOUND_H


enum Device
{
  Master,     /* Master volume */
  Dac,        /* DSP, digitized sound */
  Fm,         /* Fm synthesized sound */
  Cd,         /* Compact */
  Line,       /* Line in */
  Mic,        /* Microphone */
  Speaker,    /* Pc speaker */
  Treble,     /* Treble */
  Bass        /* Bass */
};

enum InputState
{
  ON, OFF
};

/* Volume levels range from 0 to 31, bass & treble range from 0 to 15 */
struct volume_level
{
  enum Device	device; 
  int 	 	left;   	
  int 	 	right;
};

struct inout_ctrl
{
  enum Device   	device;
  enum InputState 	left;
  enum InputState 	right;
};

#endif