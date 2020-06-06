# The C compiler to use
CC=gcc
# The flags used when compiling
CFLAGS=-g -Wall

all: scanEx
	@echo "Generation complete!" && rm *.o

scanEx: scan.o parser.o
	$(CC) $(CFLAGS) -o scan scan.o parser.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm scan