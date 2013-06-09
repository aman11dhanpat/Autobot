CC=gcc
CFLAGS=-Wall -I.

all:

connection_manager.o: connection_manager.c connection_manager.h
	$(CC) $(CFLAGS) -c -o connection_manager.o connection_manager.c

clean:
	rm -rvf *.o
