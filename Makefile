CC = cc

CPPFLAGS = 

CFLAGS ?= -g
CFLAGS += -std=c99 -pedantic
CFLAGS += -Wall 

LDFLAGS = 

all: vtcolors vttest

vtcolors: vtcolors.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

tags:
	ctags -R .

clean:
	@-rm vtcolors vttest *.o *~ core tags


.PHONY: all tags clean
