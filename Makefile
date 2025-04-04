CC=gcc
CFLAGS=-Wall -pthread

all: matriz

matriz: main.o mm_clasica.o
	$(CC) $(CFLAGS) -o matriz main.o mm_clasica.o

main.o: main.c mm_clasica.h
	$(CC) $(CFLAGS) -c main.c

mm_clasica.o: mm_clasica.c mm_clasica.h
	$(CC) $(CFLAGS) -c mm_clasica.c

clean:
	rm -f *.o matriz

