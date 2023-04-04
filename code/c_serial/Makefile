
OBJECT_FILES_OUTPUT=./target
TARGET_OUTPUT=${OBJECT_FILES_OUTPUT}/bin/target
CFLAGS=-Wall

all: main.o
	gcc $(CFLAGS) -o ${TARGET_OUTPUT} ${OBJECT_FILES_OUTPUT}/main.o

main.o: main.c
	gcc $(CFLAGS) -c main.c -o ${OBJECT_FILES_OUTPUT}/main.o

run: all
	${TARGET_OUTPUT}

clean:
	rm -f *.o ${TARGET_OUTPUT}


