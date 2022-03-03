CC = gcc
STRIP = strip

CFLAGS = -Wall

.PHONY: all

all: symlink

symlink:
	$(CC) $(CFLAGS) symlink.c -o $@
	$(STRIP) $@

clean:
	rm symlink