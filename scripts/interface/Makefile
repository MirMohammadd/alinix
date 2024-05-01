OBJS	= dialog.o
SOURCE	= dialog.c
HEADER	= 
OUT	= menuconfig
CC	 = gcc
FLAGS	 = -g -c -Wall -lncurses
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS) -lncurses

dialog.o: dialog.c
	$(CC) $(FLAGS) dialog.c -lncurses


clean:
	rm -f $(OBJS) $(OUT)