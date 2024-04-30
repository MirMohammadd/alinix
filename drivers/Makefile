# AliNix kernel Makefile for the drivers directory

INCLUDEDIRS := ../include

G++PARAMS := -m32 -g -D Alinix -I ../arch/mips/include -I $(INCLUDEDIRS) -I arch/mips/include -Wall -fno-omit-frame-pointer -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-exceptions -fno-rtti -fno-leading-underscore -Wno-write-strings -fpermissive -Wno-unknown-pragmas
GCCPARAMS := -m32 -g -D Alinix -I -I ../arch/mips/include $(INCLUDEDIRS) -I arch/mips/include -Wall -fno-omit-frame-pointer -nostdlib -fno-builtin -Wno-unknown-pragmas
ASPARAMS := --32
LDFLAGS := -m elf_i386

SRC_DIR = . 

SRCFILES := $(shell find $(SRC_DIR) -type f \( -name \*.cpp -o -name \*.s -o -name \*.asm -o -name \*.c \)) #Find all the files in usb3 that end with .cpp/.s/.asm/.c
OBJFILES := $(patsubst %.cpp,%.o,$(patsubst %.s,%.o,$(patsubst %.asm,%.o,$(patsubst %.c,%.o,$(SRCFILES))))) #Replace the .cpp/.s/.asm/.c extension with .o

TARGET = ../Alinix.bin
BINDIR = ../kernel/obj
OBJDIR = ../kernel/obj

CC = gcc
CFLAGS = -m32 -g -D Alinix -I ../arch/mips/include -I $(INCLUDEDIRS) -I arch/mips/include -Wall -fno-omit-frame-pointer -nostdlib -fno-builtin -Wno-unknown-pragmas

.PHONY: all clean

LINKER_SCRIPT = ../kernel/linker.ld

all: $(TARGET)

$(TARGET): $(OBJFILES)
	mkdir -p $(@D)
	i686-elf-ld $(LDFLAGS) -T $(LINKER_SCRIPT) $< -o $@ $(OBJDIR)

$(OBJDIR)/%.o: %.c
	i686-elf-gcc $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)/*.o $(BINDIR)/$(TARGET)
