# Makefile of HeisenOs project, Linked under the MIT license
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

# Check if the make version is exactly 3.80
ifeq ($(MAKE_VERSION),3.80)
    $(error This makefile requires GNU Make version 3.80. Your Make version is $(MAKE_VERSION))
endif


INCLUDEDIRS := kernelz/include
QEMUOPTIONS := -boot d -device VGA,edid=on,xres=1024,yres=768  #-readconfig qemu-usb-config.cfg -drive if=none,id=stick,file=disk.img -device usb-storage,bus=ehci.0,drive=stick

G++PARAMS := -m32 -g -D CACTUSOSKERNEL -I $(INCLUDEDIRS) -Wall -fno-omit-frame-pointer -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-exceptions -fno-rtti -fno-leading-underscore -Wno-write-strings -fpermissive -Wno-unknown-pragmas
GCCPARAMS := -m32 -g -D CACTUSOSKERNEL -I $(INCLUDEDIRS) -Wall -fno-omit-frame-pointer -nostdlib -fno-builtin -Wno-unknown-pragmas
ASPARAMS := --32
LDPARAMS := -m elf_i386

KRNLSRCDIR := kernelz/src
KRNLOBJDIR := kernelz/obj

KRNLFILES := $(shell find $(KRNLSRCDIR) -type f \( -name \*.cpp -o -name \*.s -o -name \*.asm -o -name \*.c \)) #Find all the files that end with .cpp/.s/.asm/.c
KRNLOBJS := $(patsubst %.cpp,%.o,$(patsubst %.s,%.o,$(patsubst %.asm,%.o,$(patsubst %.c,%.o,$(KRNLFILES))))) #Replace the .cpp/.s/.asm/.c extension with .o
KRNLOBJS := $(subst $(KRNLSRCDIR),$(KRNLOBJDIR),$(KRNLOBJS)) #Replace the kernelz/src part with kernelz/obj


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



HeisenOs.bin: kernelz/linker.ld $(KRNLOBJS)
	i686-elf-ld $(LDPARAMS) -T $< -o $@ $(KRNLOBJS)

HeisenOs.iso: HeisenOs.bin
	cd lib/ && $(MAKE)
	cd apps/ && $(MAKE)
	bchunk HeisenOs.bin HeisenOs.cue HeisenOs
	
	# nm -a HeisenOs.bin | sort -d > isofiles/debug.sym || true
	# cp -r isofiles/. iso
	# mkdir iso/boot
	# mkdir iso/boot/grub
	# cp HeisenOs.bin iso/boot/HeisenOs.bin
	# cp grub.cfg iso/boot/grub/grub.cfg
	# grub-mkrescue --output=HeisenOs.iso iso
	# rm -rf iso

.PHONY: clean qemu kdbg run filelist serialDBG qemuDBG fastApps
clean:
	rm -rf $(KRNLOBJDIR) HeisenOs.bin HeisenOs01.iso
	cd lib/ && $(MAKE) clean
	cd apps/ && $(MAKE) clean
	rm -rf isofiles/apps/*.bin
	rm -rf isofiles/apps/*.sym

qemu: HeisenOs.iso
	qemu-system-i386 -cdrom HeisenOs01.iso -serial stdio $(QEMUOPTIONS)

qemuDBG: HeisenOs.iso
	qemu-system-i386 -cdrom HeisenOs.iso -serial stdio $(QEMUOPTIONS) -s -S &

qemuGDB: HeisenOs.iso
	qemu-system-i386 -cdrom HeisenOs.iso $(QEMUOPTIONS) -serial pty &
	gdb -ex 'file HeisenOs.bin' -ex 'target remote /dev/pts/1' -q

run: HeisenOs.iso
	vboxmanage startvm "CactusOS" -E VBOX_GUI_DBG_AUTO_SHOW=true -E VBOX_GUI_DBG_ENABLED=true &
	rm "CactusOS.log"
	echo "" > "CactusOS.log"
	tail -f "CactusOS.log"

serialDBG:
	gcc -o tools/serialDebugger/a.out tools/serialDebugger/main.c
	sudo ./tools/serialDebugger/a.out

kdbg: HeisenOs.iso
	qemu-system-i386 $(QEMUOPTIONS) -cdrom HeisenOs.iso -serial stdio -s -S &
	kdbg -r localhost:1234 HeisenOs.bin

grub-core:
	grub-mkimage -o isofiles/setup/core.img -O i386-pc -p="(hd0,msdos1)/boot/grub" --config=grubcore.cfg -v configfile biosdisk part_msdos fat normal multiboot echo

# Only rebuild LIBCactusOS and the apps without recompiling the kernelz
fastApps:
	rm -rf isofiles/apps/*.bin
	cd lib/ && $(MAKE) clean && $(MAKE)
	cd apps/ && $(MAKE) clean && $(MAKE)
	rm HeisenOs.iso

turboApps:
	rm -rf isofiles/apps/*.bin
	cd apps/ && $(MAKE) clean && $(MAKE)
	rm HeisenOs.iso

installUSB: HeisenOs.iso HeisenOs.bin isofiles/debug.sym isofiles/apps
	rm -rf /media/remco/ISOIMAGE/apps/*.bin
	cp -r isofiles/apps/* /media/remco/ISOIMAGE/apps/
	cp isofiles/debug.sym /media/remco/ISOIMAGE/debug.sym
	cp HeisenOs.bin /media/remco/ISOIMAGE/boot/HeisenOs.bin
	umount /media/remco/ISOIMAGE

debug: HeisenOs.iso
	pyuic5 tools/advancedDebugger/mainGUI.ui -o tools/advancedDebugger/mainWindow.py
	qemu-system-i386 -cdrom HeisenOs.iso $(QEMUOPTIONS) -serial pty &
	/usr/bin/python3 tools/advancedDebugger/main.py


filelist:
	@echo "Source Files:"
	@echo -$(KRNLFILES)
	@echo "Object Files:"
	@echo -$(KRNLOBJS)