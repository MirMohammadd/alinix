#!/bin/bash

# Function to compile the kernel
compile_kernel() {
    # Add your kernel compilation commands here
    echo "$(make qemu >/dev/null 2>&1)"
}

# Function to clean the work directory
clean_work() {
    # Add your work directory cleaning commands here
    echo "$(make clean >/dev/null 2>&1)"
}

run_qemu(){
    echo "$(make qemu >/dev/null 2>&1)"
}

# Main function displaying dialog interface
main() {
    while true; do
        choice=$(dialog --clear \
                        --backtitle "Kernel Compilation Menu" \
                        --title "Main Menu" \
                        --menu "Choose an option:" \
                        15 50 3 \
                        1 "Compile the kernel" \
                        2 "Clean the work directory" \
                        3 "Run in QEMU" \
                        4 "Exit" \
                        2>&1 >/dev/tty)

        case "$choice" in
            1)
                compile_kernel
                ;;
            2)
                clean_work
                ;;

            3)
                run_qemu
                ;;
            4)
                echo "Exiting..."
                exit 0
                ;;
            *)
                echo "Invalid option. Please select again."
                ;;
        esac
    done
}

# Check if dialog is installed
if ! command -v dialog &> /dev/null; then
    echo "Dialog is not installed. Please install it to run this script."
    exit 1
fi

main
