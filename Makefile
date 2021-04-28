# Bu bir makefile
# Yorum satırı

CC = gcc
OBJ = main.o fields.o

all: main


main: main.o fields.o
	$(CC) $(OBJ) -o $@

main.o: main.c
	$(CC) -c $<
#	gcc -c main.c

fields.o: fields.c fields.h
	$(CC) -c $<
# 	gcc main.o fields.o -o main

clean:
	rm *.o

vclean:
	rm -rf *.o
	rm main
