#!/bin/bash

# Display the initial dialog for feature selection
options=$(dialog --no-shadow --backtitle "Kernel Configuration" --title "Heisen Kernel Configuration" --clear --stdout --checklist "Select features to enable:" 20 60 10 \
    1 "General setup" on \
    2 "EHCI" off \
    3 "UHCI" off \
    4 "OHCI" off \
    5 "64 bit compile" off \
    6 "32 bit compile" off \
    7 "Run QEMU" off \
    8 "Clean the work (Remove all the object, iso and binary files)" on)

# Check if option 8 ("Clean the work") is selected
if echo "$options" | grep -q "8"; then
    echo "Cleaning the files ..."
    # Add your commands to clean the files here
    echo "Files cleaned."
else
    echo "Option 8 is not selected."
fi

# Check if "General setup" is selected
if echo "$options" | grep -q "1"; then
    echo "General setup is selected."
    # Display a message box for basic setup configuration

    # Ask user whether to compile Heisen Kernel with GCC cross compiler
    compile_options=$(dialog --no-shadow --backtitle "Basic setup" --title "Select compilation options" --clear --stdout --checklist "Choose compilation options:" 10 40 2 \
    "1" "Compile with GCC cross compiler pack (i686-elf-gcc)" on \
    "2" "Other compilation option" off \
    "3" "Clean the work (Remove all the object, iso and binary files)" off)

    # Check the exit status of the previous dialog
    if echo "$compile_options" | grep -q "1"; then
        echo "Heisen Kernel will be compiled with GCC cross compiler."
        # Add your commands to compile the kernel here
        echo "$(make qemu)"
    fi
    
    if echo "$compile_options" | grep -q "3"; then
        echo "$(make clean)"
        echo "Cleaning the files ..."
        # Add your commands to clean the files here
        echo "Files cleaned."
    else
        echo "Option 3 is not selected."
    fi
else
    echo "General setup is not selected."
fi
