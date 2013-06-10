CC=gcc
CFLAGS=-Wall -I.

all:basic_client

basic_client: basic_client.c irc_manager.o connection_manager.o
	$(CC) $(CFLAGS) -o basic_client basic_client.c irc_manager.o connection_manager.o

irc_manager.o: irc_manager.c irc_manager.h
	$(CC) $(CFLAGS) -c -o irc_manager.o irc_manager.c

connection_manager.o: connection_manager.c connection_manager.h
	$(CC) $(CFLAGS) -c -o connection_manager.o connection_manager.c

clean:
	rm -rvf *.o
