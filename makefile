CC=gcc
FLAGS=-Wall -g

all: frequency

frequency: main.o 
	$(CC) $(FLAGS) main.o -o frequency
main.o: main.c
	$(CC) $(FLAGS) -c main.c -o main.o

.PHONY:clean all

clean:
	rm -f *.o frequency
