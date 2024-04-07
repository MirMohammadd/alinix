#!/bin/bash



# Display the initial dialog for feature selection
dialog --no-shadow --backtitle "Kernel Configuration" --title "Heisen Kernel Configuration" --clear --stdout --checklist "Select features to enable:" 20 60 10 \
    1 "General setup" on \
    2 "EHCI" off \
    3 "UHCI" off \
    4 "OHCI" off \
    > .config

# Check if "General setup" is selected
if grep -q "1" .config; then
    # Display a message box for basic setup configuration
    dialog --no-shadow --backtitle "Basic setup" --msgbox "Basic setup Config" 10 40

    # Ask user whether to compile Heisen Kernel with GCC cross compiler
    dialog --no-shadow --backtitle "Basic setup" --title "Compile Heisen Kernel with GCC cross compiler" --clear --stdout --yesno "Do you want to compile Heisen Kernel with GCC cross compiler?" 10 40

    # Check the exit status of the previous dialog
    if [ $? -eq 0 ]; then
        echo "Heisen Kernel will be compiled with GCC cross compiler."
        echo "$(make qemu)"
        # Add your commands to compile the kernel here
    else
        echo "Heisen Kernel will not be compiled with GCC cross compiler."
    fi
fi
