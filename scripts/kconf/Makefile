CC = gcc
CFLAGS = -Wall
LDFLAGS = -lncurses

SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)
EXE = myprogram

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(EXE)
