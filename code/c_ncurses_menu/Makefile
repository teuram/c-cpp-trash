
OBJECT_FILES_OUTPUT=./target
TARGET_OUTPUT=${OBJECT_FILES_OUTPUT}/bin/target
CFLAGS=-Wall
LDLIBS=-lncurses


all: main.o
	gcc $(CFLAGS) ${LDLIBS} -o ${TARGET_OUTPUT} ${OBJECT_FILES_OUTPUT}/*.o

main.o: main.c
	gcc $(CFLAGS) -c main.c -o ${OBJECT_FILES_OUTPUT}/main.o

run: all
	${TARGET_OUTPUT}

clean:
	rm -f ${OBJECT_FILES_OUTPUT}/*.o 
	rm -f ${TARGET_OUTPUT}


