
CC=clang
CFLAGS=-Wall -std=c99 -O2 -pipe -march=native
LDFLAGS=

SOURCES=main.c
OBJECTS=$(SOURCES:.c=.o)
TARGET=moni

all: $(OBJECTS)
	$(CC) $(LDFLAGS) target/*.o -o target/$(TARGET)

main.o: main.c
	$(CC) $(CFLAGS) -c -o target/main.o main.c

run: all
	./target/$(TARGET)

clean:
	-rm target/$(TARGET)
	-rm target/*.o

install:
	cp ./target/$(TARGET) $(HOME)/.local/bin/
