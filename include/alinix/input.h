#ifndef __ALINIX_KERNEL_INPUT_H
#define __ALINIX_KERNEL_INPUT_H

#include <alinix/types.h>
#include <alinix/device.h>
#include <alinix/mutex_types.h>
#include <alinix/spinlock_types.h>
#include <alinix/timer_types.h>
#include <alinix/event-code.h>


struct input_handler;

struct input_keymap_entry {
#define INPUT_KEYMAP_BY_INDEX	(1 << 0)
	u8  flags;
	u8  len;
	u16 index;
	u32 keycode;
	u8  scancode[32];
};

struct input_value {
	u16 type;
	u16 code;
	sint32_t value;
};

enum input_clock_type {
	INPUT_CLK_REAL = 0,
	INPUT_CLK_MONO,
	INPUT_CLK_BOOT,
	INPUT_CLK_MAX
};

struct input_id {
	u16 bustype;
	u16 vendor;
	u16 product;
	u16 version;
};


struct input_dev {
	const char *name;
	const char *phys;
	const char *uniq;
	struct input_id id;

	unsigned long propbit[INPUT_PROP_CNT];

	unsigned long evbit[EV_CNT];
	unsigned long keybit[KEY_CNT];
	unsigned long relbit[REL_CNT];
	unsigned long absbit[ABS_CNT];
	unsigned long mscbit[MSC_CNT];
	unsigned long ledbit[LED_CNT];
	unsigned long sndbit[SND_CNT];
	unsigned long ffbit[SND_CNT];
	unsigned long swbit[SW_CNT];

	unsigned int hint_events_per_packet;

	unsigned int keycodemax;
	unsigned int keycodesize;
	void *keycode;

	int (*setkeycode)(struct input_dev *dev,
			  const struct input_keymap_entry *ke,
			  unsigned int *old_keycode);
	int (*getkeycode)(struct input_dev *dev,
			  struct input_keymap_entry *ke);

	struct ff_device *ff;

	struct input_dev_poller *poller;

	unsigned int repeat_key;
	struct timer_list timer;

	int rep[REP_CNT];

	struct input_mt *mt;

	struct input_absinfo *absinfo;

	unsigned long key[(KEY_CNT)];
	unsigned long led[(LED_CNT)];
	unsigned long snd[(SND_CNT)];
	unsigned long sw[(SW_CNT)];

	int (*open)(struct input_dev *dev);
	void (*close)(struct input_dev *dev);
	int (*flush)(struct input_dev *dev);
	int (*event)(struct input_dev *dev, unsigned int type, unsigned int code, int value);

	struct input_handle  *grab;

	spinlock_t event_lock;
	struct mutex mutex;

	unsigned int users;
	bool going_away;

	struct device dev;

	struct list_head	h_list;
	struct list_head	node;

	unsigned int num_vals;
	unsigned int max_vals;
	struct input_value *vals;

	bool devres_managed;

	ktime_t timestamp[INPUT_CLK_MAX];

	bool inhibited;
};

struct input_handler {

	// void *private;

	void (*event)(struct input_handle *handle, unsigned int type, unsigned int code, int value);
	void (*events)(struct input_handle *handle,
		       const struct input_value *vals, unsigned int count);
	bool (*filter)(struct input_handle *handle, unsigned int type, unsigned int code, int value);
	bool (*match)(struct input_handler *handler, struct input_dev *dev);
	int (*connect)(struct input_handler *handler, struct input_dev *dev, const struct input_device_id *id);
	void (*disconnect)(struct input_handle *handle);
	void (*start)(struct input_handle *handle);

	bool legacy_minors;
	int minor;
	const char *name;

	const struct input_device_id *id_table;

	struct list_head	h_list;
	struct list_head	node;
};



#endif