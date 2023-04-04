
BINIRY=bin
CFLAGS=-Wall -std=c99

all: main.o core.so
	gcc $(CFLAGS) -o $(BINIRY) main.o

main.o: main.c
	gcc $(CFLAGS) main.c -c

core.so: module.o
	gcc $(CFLAGS) -fPIC -nostdlib -shared -o core.so module.o

module.o: module.c
	gcc $(CFLAGS) module.c -c

run: all
	./bin

clean:
	rm -f *.o *.so ${BINIRY}


