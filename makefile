
CC = gcc

CFLAGS = -Wall

rwmain: main.o readerwriter.o
	$(CC) $(CFLAGS) -l pthread -o rwmain main.c readerwriter.c
clean:
	rm *.o