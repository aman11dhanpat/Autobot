CC=gcc
CFLAGS=-Wall -I.

BIN_FILES=

OBJ_FILES=\
	  connection_manager.o\
	  irc_manager.o\
	  logger.o

all: $(BIN_FILES)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rvf $(BIN_FILES) $(OBJ_FILES)
