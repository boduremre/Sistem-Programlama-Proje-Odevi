LIBDIR = ./libfdr
INCLUDE = -I ./include
LIBFDRINCLUDE = -I $(LIBDIR)/include
CFLAGS = $(INCLUDE) $(LIBFDRINCLUDE)
LIBS = $(LIBDIR)/lib/libfdr.a

CC = gcc
EXECUTABLES = \
    kripto \

all: $(EXECUTABLES)

clean:
	rm -f ./lib/*.o sifrelenmis cozulmus kripto

kripto: src/main.c
	$(CC) $(CFLAGS) -o ./lib/kilit.o -c ./src/kilit.c
	$(CC) $(CFLAGS) -o ./lib/mrbdr.o -c ./src/mrbdr.c
	$(CC) $(CFLAGS) -o kripto ./lib/kilit.o ./lib/mrbdr.o src/main.c $(LIBS)
