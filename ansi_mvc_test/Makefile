CC=clang++
CFLAGS=-c -Wall -std=c++17
LFLAGS=-L../ansi_mvc/lib -lansicontroller -lansimodel -lansiview -lrdbmodel -Wl,-rpath='$$ORIGIN/../../ansi_mvc/lib/'
SRC=$(wildcard src/*.cpp)
OBJ=$(addprefix obj/, $(notdir $(SRC:.cpp=.o)))

all: clean mvc

mvc: $(OBJ) | bin
	$(CC) $(LFLAGS) -o bin/$@ $^

obj/%.o: src/%.cpp | obj
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ) bin/mvc

run: mvc
	bin/mvc 

obj:
	mkdir obj

bin:
	mkdir bin
