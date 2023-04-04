
CC = clang
CFLAGS = -Wall -std=c99 -O2 -pipe -march=native
LIBS =

PREF_SRC = ./src/
PREF_OBJ = ./obj/

TARGET=target
SRC = $(wildcard $(PREF_SRC)*.c)
OBJ = $(patsubst $(PREF_SRC)%.c, $(PREF_OBJ)%.o, $(SRC))

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIBS)

$(PREF_OBJ)%.o: $(PREF_SRC)%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	-rm $(TARGET) $(PREF_OBJ)*.o

