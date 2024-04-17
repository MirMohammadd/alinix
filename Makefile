# Makefile of Alinix kernel
# inspired by https://github.com/Remco123/CactusOS
##########
# .s files are GAS assembly
# .asm files are nasm assembly
##########
#####################
#xHCI
# nec-usb-xhci
# qemu-xhci
#EHCI
# usb-ehci
# ich9-usb-ehci1
#UHCI
# ich9-usb-uhci1
# ich9-usb-uhci2
# ich9-usb-uhci3
# piix3-usb-uhci
# piix4-usb-uhci
# vt82c686b-usb-uhci
#OHCI
# sysbus-ohci
# pci-ohci
#######################

VERSION = 1
PATCHLEVEL = 4
SUBLEVEL = 4

# Check if the make version is exactly 3.80
ifeq ($(MAKE_VERSION),3.80)
    $(error This makefile requires GNU Make version 3.80. Your Make version is $(MAKE_VERSION))
endif

INCLUDEDIRS := include
QEMUOPTIONS := -boot d -device VGA,edid=on,xres=1024,yres=768 -trace events=../qemuTrace.txt -d cpu_reset #-readconfig qemu-usb-config.cfg -drive if=none,id=stick,file=disk.img -device usb-storage,bus=ehci.0,drive=stick

G++PARAMS := -m32 -g -D CACTUSOSKERNEL -I $(INCLUDEDIRS) -Wall -fno-omit-frame-pointer -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-exceptions -fno-rtti -fno-leading-underscore -Wno-write-strings -fpermissive -Wno-unknown-pragmas
GCCPARAMS := -m32 -g -D CACTUSOSKERNEL -I $(INCLUDEDIRS) -Wall -fno-omit-frame-pointer -nostdlib -fno-builtin -Wno-unknown-pragmas
ASPARAMS := --32
LDPARAMS := -m elf_i386

KRNLSRCDIR := kernel
KRNLOBJDIR := kernel/obj

KRNLFILES := $(shell find $(KRNLSRCDIR) -type f \( -name \*.cpp -o -name \*.s -o -name \*.asm -o -name \*.c \)) #Find all the files that end with .cpp/.s/.asm/.c
KRNLOBJS := $(patsubst $(KRNLSRCDIR)/%,$(KRNLOBJDIR)/%,$(patsubst %.cpp,%.o,$(patsubst %.s,%.o,$(patsubst %.asm,%.o,$(patsubst %.c,%.o,$(KRNLFILES)))))) #Replace the .cpp/.s/.asm/.c extension with .o

####################################
#C++ source files
####################################
$(KRNLOBJDIR)/%.o: $(KRNLSRCDIR)/%.cpp
	mkdir -p $(@D)
	i686-elf-g++ $(G++PARAMS) -c -o $@ $<

####################################
#C source files
####################################
$(KRNLOBJDIR)/%.o: $(KRNLSRCDIR)/%.c
	mkdir -p $(@D)
	i686-elf-gcc $(GCCPARAMS) -c -o $@ $<

####################################
#GDB Stub
####################################
$(KRNLOBJDIR)/gdb/i386-stub.o: $(KRNLSRCDIR)/gdb/i386-stub.c
	mkdir -p $(@D)
	i686-elf-gcc $(GCCPARAMS) -fleading-underscore -c -o $@ $<

####################################
#GAS assembly files
####################################
$(KRNLOBJDIR)/%.o: $(KRNLSRCDIR)/%.s
	mkdir -p $(@D)
	i686-elf-as $(ASPARAMS) -o $@ $<

####################################
#NASM assembly files
####################################
$(KRNLOBJDIR)/%.o: $(KRNLSRCDIR)/%.asm
	mkdir -p $(@D)
	nasm -f elf32 -O0 $< -o $@

HeisenOs.bin: kernel/linker.ld $(KRNLOBJS)
	i686-elf-ld $(LDPARAMS) -T $< -o $@ $(KRNLOBJS)

HeisenOs.iso: HeisenOs.bin
	bchunk HeisenOs.bin HeisenOs.cue HeisenOs
