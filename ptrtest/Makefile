CC=g++
CFLAGS=-c -Wall -std=c++14 
SRC=$(wildcard src/*.cpp)
OBJ=$(addprefix obj/, $(notdir $(SRC:.cpp=.o)))

all: clean tester
	echo "Rebuided"

tester: $(OBJ) | bin
	$(CC) $(LFLABS) -o bin/$@ $^

obj/%.o: src/%.cpp | obj
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJ) bin/tester

obj:
	mkdir obj

bin:
	mkdir bin

run: 
	bin/tester
