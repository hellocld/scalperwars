CC = gcc
CFLAGS = -g -Wall

game: src/scalperwars.c
	$(CC) $(CFLAGS) src/scalperwars.c -o bin/scalperwars

