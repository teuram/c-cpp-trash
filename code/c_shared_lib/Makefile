
BINIRY=bin
CFLAGS=-Wall -std=c99

all: main.o libadd.so
	gcc $(CFLAGS) -o $(BINIRY) main.o -L. -ladd

main.o:
	gcc $(CFLAGS) main.c -c

libadd.so: add.o
	gcc $(CFLAGS) -shared -o libadd.so add.o

add.o:
	gcc $(CFLAGS) add.c -c

clean:
	rm -f *.o *.so ${BINIRY}


