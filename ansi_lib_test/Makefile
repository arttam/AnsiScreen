CC=clang++
CFLAGS=-c -Wall -std=c++17
LFLAGS=-L../ansi_console_lib/lib -lansiscreen -Wl,-rpath='$$ORIGIN/../../ansi_console_lib/lib/'
SRC=$(wildcard src/*.cpp)
OBJ=$(addprefix obj/, $(notdir $(SRC:.cpp=.o)))

ac: $(OBJ)
	$(CC) $(LFLAGS) -o bin/$@ $^

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJ) bin/ac

run: ac
	bin/ac /home/art/Projects/ansi_lib_test/src/ast.cpp

