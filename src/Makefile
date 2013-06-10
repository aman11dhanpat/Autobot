CC=gcc
CFLAGS=-Wall -I.

all:

irc_manager.o: irc_manager.c irc_manager.h
	$(CC) $(CFLAGS) -c -o irc_manager.o irc_manager.c

connection_manager.o: connection_manager.c connection_manager.h
	$(CC) $(CFLAGS) -c -o connection_manager.o connection_manager.c

clean:
	rm -rvf *.o
