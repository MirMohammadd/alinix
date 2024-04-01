OBJS	= main.o
SOURCE	= main.cc
HEADER	= 
OUT	= 
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cc
	$(CC) $(FLAGS) main.cc -lcppunit


clean:
	rm -f $(OBJS) $(OUT)