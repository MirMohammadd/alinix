# Define the source and object directories for security files
SRCDIR := src/security
OBJDIR := ../kernel/obj/security

# Define the compiler and its parameters
CC := i686-elf-gcc
CFLAGS := -Wall -Wextra -I include -I ../include

# Find all .c files in the security directory
SRCS := $(wildcard $(SRCDIR)/*.c)

# Create a list of object files corresponding to the source files
OBJS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

# Rule to compile all .c files in the security directory to .o files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(@D)
	@echo "COMPILING $@"
	i686-elf-gcc $(CFLAGS) -c -o $@ $<

# Target to compile all security files
security_files: $(OBJS)
