CC=gcc
CFLAGS=-Wall -I.

BIN_FILES=basic_client

OBJ_FILES=\
	  connection_manager.o\
	  irc_manager.o\
	  logger.o

all: $(BIN_FILES)

basic_client: basic_client.c irc_manager.o connection_manager.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rvf $(BIN_FILES) $(OBJ_FILES)
