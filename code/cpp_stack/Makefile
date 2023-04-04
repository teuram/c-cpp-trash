
CC = g++
CFLAGS = -std=c++11 -Wall -O2 -pipe -march=native
LIBS =

PREF_SRC = ./src/
PREF_OBJ = ./obj/

TARGET=target
SRC = $(wildcard $(PREF_SRC)*.cpp)
OBJ = $(patsubst $(PREF_SRC)%.cpp, $(PREF_OBJ)%.o, $(SRC))

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET) $(LIBS)

$(PREF_OBJ)%.o: $(PREF_SRC)%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	-rm $(TARGET) $(PREF_OBJ)*.o

