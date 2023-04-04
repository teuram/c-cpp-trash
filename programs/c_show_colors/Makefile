
BINIRY=show-colors

CFLAGS=-Wall -std=c99

all: main.o
	gcc $(CFLAGS) *.o -o $(BINIRY)

main.o:
	gcc $(CFLAGS) main.c -c

clean:
	rm -f *.o $(BINIRY)

install:
	cp ${OUT} ${HOME}/.local/bin/
	exit

