LIBDIR = ./libfdr
INCLUDE = -I ./
CFLAGS = $(INCLUDE)
LIBS = $(LIBDIR)/libfdr.a

CC = gcc
EXECUTABLES = \
    kripto \

all: $(EXECUTABLES)

run: clean kripto komut

komut: 
	./kripto -e ornek_metin encripted 
	./kripto -d encripted decripted

clean:
	rm -f *.o kripto
	
cleanall:
	rm -f *.o .kilit kripto encripted decripted ornek_metin *.txt

kripto: main.c
	$(CC) $(CFLAGS) -o kilit.o -c kilit.c
	$(CC) $(CFLAGS) -o mrbdr.o -c mrbdr.c
	$(CC) $(CFLAGS) -o kripto kilit.o mrbdr.o main.c $(LIBS)
