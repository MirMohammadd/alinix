# RISC-V notes

RISC-V port is only in early development.

## Conigure and Build

make riscv64-medany-linux
make

## Run in QEMU

qemu-system-riscv64 -machine virt -bios fudge -serial stdio
qemu-system-x86_64 -kernel alinix.bin
qemu-system-x86_64 -kernel cactusos.bin
