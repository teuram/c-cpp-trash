
TARGET=main
RARGS=code.m

CFLAGS=-Wall -std=c99

all: main.o stack.o lexer.o parser.o
	-gcc $(CFLAGS) target/*.o -o target/${TARGET}

run: all
	mkdir -p target
	./target/${TARGET} t ${RARGS}

main.o: main.c
	-gcc $(CFLAGS) -c -o target/main.o main.c

stack.o: stack.c
	-gcc $(CFLAGS) -c -o target/stack.o stack.c

lexer.o: lexer.c
	-gcc $(CFLAGS) -c -o target/lexer.o lexer.c

parser.o: parser.c
	-gcc $(CFLAGS) -c -o target/parser.o parser.c

clean:
	-rm target/${TARGET}
	-rm target/*.o

