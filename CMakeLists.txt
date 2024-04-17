cmake_minimum_required(VERSION 3.1)
project(AlinixKernel LANGUAGES C CXX ASM)

set(CMAKE_C_COMPILER i686-elf-gcc)
set(CMAKE_CXX_COMPILER i686-elf-g++)
set(CMAKE_ASM_COMPILER i686-elf-as)
set(CMAKE_LINKER i686-elf-ld)
set(CMAKE_OBJCOPY i686-elf-objcopy)
set(CMAKE_OBJDUMP i686-elf-objdump)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32 -g -DCACTUSOSKERNEL -Wall -fno-omit-frame-pointer -nostdlib -fno-builtin -Wno-unknown-pragmas")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32 -g -DCACTUSOSKERNEL -Wall -fno-omit-frame-pointer -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-exceptions -fno-rtti -fno-leading-underscore -Wno-write-strings -fpermissive -Wno-unknown-pragmas")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} --32")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m elf_i386")

set(INCLUDEDIRS include)
include_directories(${INCLUDEDIRS})

file(GLOB_RECURSE KRNLFILES
    "kernel/*.cpp"
    "kernel/*.s"
    "kernel/*.asm"
    "kernel/*.c"
)

add_executable(HeisenOs.bin 
    kernel/src/kernek.c
)


foreach(KRNLFILE ${KRNLFILES})
    get_filename_component(FILE_NAME ${KRNLFILE} NAME)
    string(REPLACE "." ";" FILE_NAME_LIST ${FILE_NAME})
    list(GET FILE_NAME_LIST 0 FILE_BASE)
    set(FILE_OBJ "${FILE_BASE}.o")
    set(FILE_OBJ_PATH "kernel/obj/${FILE_OBJ}")
    add_custom_command(
        OUTPUT ${FILE_OBJ_PATH}
        COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/kernel/obj/
        COMMAND ${CMAKE_CXX_COMPILER} ${CMAKE_CXX_FLAGS} -c -o ${FILE_OBJ_PATH} ${KRNLFILE}
        DEPENDS ${KRNLFILE}
        COMMENT "Building object file ${FILE_OBJ_PATH}"
    )
    list(APPEND KRNL_OBJS ${FILE_OBJ_PATH})
endforeach()

add_custom_target(kernel_objs DEPENDS ${KRNL_OBJS})

add_executable(HeisenOs.bin ${KRNL_OBJS})
set_target_properties(HeisenOs.bin PROPERTIES LINK_FLAGS "-T kernel/linker.ld")

add_custom_command(
    OUTPUT HeisenOs.iso
    COMMAND cd kernel/ && ${CMAKE_MAKE_PROGRAM}
    COMMAND cd apps/ && ${CMAKE_MAKE_PROGRAM}
    COMMAND bchunk HeisenOs.bin HeisenOs.cue HeisenOs
    COMMAND cp -r isofiles/. iso
    COMMAND mkdir iso/boot
    COMMAND mkdir iso/boot/grub
    COMMAND cp HeisenOs.bin iso/boot/HeisenOs.bin
    COMMAND cp grub.cfg iso/boot/grub/grub.cfg
    COMMAND grub-mkrescue --output=HeisenOs.iso iso
    COMMAND rm -rf iso
    DEPENDS HeisenOs.bin
    COMMENT "Creating ISO image"
)

add_custom_target(HeisenOs.iso DEPENDS HeisenOs.iso)

add_custom_target(clean_all
    COMMAND rm -rf ${CMAKE_CURRENT_BINARY_DIR}/kernel/obj
    COMMAND rm -f HeisenOs.bin HeisenOs01.iso
    COMMAND cd lib/ && ${CMAKE_MAKE_PROGRAM} clean
    COMMAND cd apps/ && ${CMAKE_MAKE_PROGRAM} clean
    COMMAND rm -rf isofiles/apps/*.bin
    COMMAND rm -rf isofiles/apps/*.sym
    COMMAND rm -rf drivers/apps/*.bin
    COMMAND rm -rf drivers/apps/*.sym
)

add_custom_target(qemu
    COMMAND qemu-system-i386 -cdrom HeisenOs01.iso -serial stdio
)

add_custom_target(qemuDBG
    COMMAND qemu-system-i386 -cdrom HeisenOs.iso -serial stdio -s -S
)

add_custom_target(qemuGDB
    COMMAND qemu-system-i386 -cdrom HeisenOs.iso -serial stdio -s -S &
    COMMAND gdb -ex 'file HeisenOs.bin' -ex 'target remote localhost:1234' -q
)

add_custom_target(run
    COMMAND vboxmanage startvm "CactusOS" -E VBOX_GUI_DBG_AUTO_SHOW=true -E VBOX_GUI_DBG_ENABLED=true &
    COMMAND rm "CactusOS.log"
    COMMAND echo "" > "CactusOS.log"
    COMMAND tail -f "CactusOS.log"
)

add_custom_target(serialDBG
    COMMAND gcc -o tools/serialDebugger/a.out tools/serialDebugger/main.c
    COMMAND sudo ./tools/serialDebugger/a.out
)

add_custom_target(kdbg
    COMMAND qemu-system-i386 -cdrom HeisenOs.iso -serial stdio -s -S &
    COMMAND kdbg -r localhost:1234 HeisenOs.bin
)

add_custom_target(grub-core
    COMMAND grub-mkimage -o isofiles/setup/core.img -O i386-pc -p="(hd0,msdos1)/boot/grub" --config=grubcore.cfg -v configfile biosdisk part_msdos fat normal multiboot echo
)

add_custom_target(fastApps
    COMMAND rm -rf isofiles/apps/*.bin
    COMMAND cd lib/ && ${CMAKE_MAKE_PROGRAM} clean && ${CMAKE_MAKE_PROGRAM}
    COMMAND cd apps/ && ${CMAKE_MAKE_PROGRAM} clean && ${CMAKE_MAKE_PROGRAM}
    COMMAND rm HeisenOs.iso
)

add_custom_target(turboApps
    COMMAND rm -rf isofiles/apps/*.bin
    COMMAND cd apps/ && ${CMAKE_MAKE_PROGRAM} clean && ${CMAKE_MAKE_PROGRAM}
    COMMAND rm HeisenOs.iso
)

add_custom_target(installUSB
    COMMAND rm -rf /media/remco/ISOIMAGE/apps/*.bin
    COMMAND cp -r isofiles/apps/* /media/remco/ISOIMAGE/apps/
    COMMAND cp isofiles/debug.sym /media/remco/ISOIMAGE/debug.sym
    COMMAND cp HeisenOs.bin /media/remco/ISOIMAGE/boot/HeisenOs.bin
    COMMAND umount /media/remco/ISOIMAGE
)

add_custom_target(debug
    COMMAND pyuic5 tools/advancedDebugger/mainGUI.ui -o tools/advancedDebugger/mainWindow.py
    COMMAND qemu-system-i386 -cdrom HeisenOs.iso -serial pty &
    COMMAND /usr/bin/python3 tools/advancedDebugger/main.py
)

add_custom_target(filelist
    COMMAND echo "Source Files:"
    COMMAND echo ${KRNLFILES}
    COMMAND echo "Object Files:"
    COMMAND echo ${KRNL_OBJS}
)

add_custom_target(version
    COMMAND echo "Version: ${VERSION}.${PATCHLEVEL}.${SUBLEVEL}"
)

