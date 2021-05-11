# If you want to use this on your own machine, change CLASSDIR and/or INCLUDE and LIBS so
# that they point to the correct directories/library.

CLASSDIR = ./libfdr
INCLUDE = -I $(CLASSDIR)/include
CFLAGS = $(INCLUDE)
LIBS = $(CLASSDIR)/lib/libfdr.a

CC = gcc
EXECUTABLES = \
    kripto \

all: $(EXECUTABLES)

clean:
	rm -f kripto encripted decripted

kripto: src/main.c
	$(CC) $(CFLAGS) -o kripto src/main.c $(LIBS)
