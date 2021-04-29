# If you want to use this on your own machine, change CLASSDIR and/or INCLUDE and LIBS so
# that they point to the correct directories/library.

CLASSDIR = ./Libfdr
INCLUDE = -I$(CLASSDIR)/include
CFLAGS = $(INCLUDE)
LIBS = $(CLASSDIR)/lib/libfdr.a

CC = gcc
EXECUTABLES = \
    bin/main \


all: $(EXECUTABLES)

clean:
	rm -f bin/*

bin/main: src/main.c 
	$(CC) $(CFLAGS) -o bin/main src/main.c $(LIBS)
