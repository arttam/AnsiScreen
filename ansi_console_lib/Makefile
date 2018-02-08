CC=clang++
CFLAGS=-c -Wall -std=c++17 -fPIC
LFLABS=-shared -fPIC
SRC=$(wildcard src/*.cpp)
OBJ=$(addprefix obj/, $(notdir $(SRC:.cpp=.o)))

libansiscreen.so: $(OBJ)
	$(CC) $(LFLABS) -o lib/$@ $^

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJ) lib/libansiscreen.so

