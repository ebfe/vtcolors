CC = cc

CPPFLAGS = 

CFLAGS ?= -g
CFLAGS += -std=c99 -pedantic
CFLAGS += -Wall 

LDFLAGS = 

all: vtcolors 

vtcolors: vtcolors.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

tags:
	ctags -R .

clean:
	@-rm vtcolors *.o *~ core tags


.PHONY: all tags clean
