# Alinix Kernel Project, Licenced under GNU affero GPL, see file LICENSE for more information

CONFIG = ../../makefile.config
include ${CONFIG}

LIBINCLUDE := ../../lib/include
LIBDIR := ../../lib
DEBUG := -g
LIBDRIVEINCLUDE = ../../libdrive/include

G++PARAMS := -m32 $(DEBUG)  -I ../include -I $(LIBINCLUDE) $(OPTIMIZE_FLAGS) -I $(LIBDRIVEINCLUDE) -I ../kernel/include -Wall -I ../lib/include -I ../libdrive/include -fno-omit-frame-pointer -I ../libdrive/include -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-exceptions -fno-rtti -fno-leading-underscore -Wno-write-strings -fpermissive -Wno-unknown-pragmas
GCCPARAMS := -m32 $(DEBUG) -I $(LIBINCLUDE) $(OPTIMIZE_FLAGS) -I $(LIBDRIVEINCLUDE) -I ../kernel/include -Wall -I ../lib/include -I ../libdrive/include -fno-omit-frame-pointer -nostdlib -fno-builtin -fleading-underscore -Wno-unknown-pragmas
LDPARAMS := -m elf_i386

USB_DIR := system

SRCFILES := $(shell find $(USB_DIR) -type f \( -name \*.cpp -o -name \*.s -o -name \*.asm -o -name \*.c \)) # Find all the files in usb3 that end with .cpp/.s/.asm/.c
OBJFILES := $(patsubst %.cpp,%.o,$(patsubst %.s,%.o,$(patsubst %.asm,%.o,$(patsubst %.c,%.o,$(SRCFILES))))) # Replace the .cpp/.s/.asm/.c extension with .o

APPOUT := ../isofiles/drivers

.PHONY: all clean

all: $(APPOUT) linker.ld $(OBJFILES)
	for app in $(OBJFILES) ; do \
		app_name=$$(basename $$app .o); \
		app_bin=$(APPOUT)/$$app_name.bin; \
		app_dir=$$(dirname $$app_bin); \
		mkdir -p $$app_dir; \
		echo building $$app_name.bin to $$app_bin; \
		i686-elf-ld $(LDPARAMS) -T linker.ld -o $$app_bin $$app -L$(LIBDIR); \
		nm -a $$app_bin | sort -d > $(APPOUT)/$$app_name.sym; \
		cd system && make && cd ..
	done


clean:
	rm -rf $(OBJFILES)

%.o: %.cpp
	mkdir -p $(@D)
	i686-elf-g++ $(G++PARAMS) -c -o $@ $<

%.o: %.c
	mkdir -p $(@D)
	i686-elf-gcc $(GCCPARAMS) -c -o $@ $<

%.o: %.asm
	mkdir -p $(@D)
	nasm -f elf32 -O0 $< -o $@

%.o: %.s
	mkdir -p $(@D)
	i686-elf-as --32 -o $@ $<
