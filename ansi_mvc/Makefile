CC=clang++
CFLAGS=-c -Wall -std=c++17 -fPIC
LFLAGS=-shared -fPIC
LDBFLAGS=-shared -fPIC -lsqlite3
# Sources
VIEWSRC=$(wildcard src/view/*.cpp)
MODELSRC=$(wildcard src/model/*.cpp)
CONTROLLERSRC=$(wildcard src/controller/*.cpp)
RDBSRC=$(wildcard src/rdb/*.cpp)
# Object files
VIEWOBJ=$(addprefix obj/, $(notdir $(VIEWSRC:.cpp=.o)))
MODELOBJ=$(addprefix obj/, $(notdir $(MODELSRC:.cpp=.o)))
CONTROLLEROBJ=$(addprefix obj/, $(notdir $(CONTROLLERSRC:.cpp=.o)))
RDBOBJ=$(addprefix obj/, $(notdir $(RDBSRC:.cpp=.o)))

all: libansiview.so libansimodel.so libansicontroller.so librdbmodel.so

showvar:
	$(info $$CC is ${CC})
	$(info $$MODELSRC = ${MODELSRC})
	$(info $$RDBSRC = ${RDBSRC})
	$(info $$RDBOBJ = ${RDBOBJ})


# Libaries output
libansiview.so: $(VIEWOBJ) | lib
	$(CC) $(LFLAGS) -o lib/$@ $^

libansimodel.so: $(MODELOBJ) | lib
	$(CC) $(LFLAGS) -o lib/$@ $^

libansicontroller.so: $(CONTROLLEROBJ) | lib
	$(CC) $(LFLAGS) -o lib/$@ $^

librdbmodel.so: $(RDBOBJ) | lib
	$(CC) $(LDBFLAGS) -o lib/$@ $^

# Object files
$(VIEWOBJ): $(VIEWSRC) | obj
	$(CC) $(CFLAGS) $< -o $@

$(MODELOBJ): $(MODELSRC) | obj
	$(CC) $(CFLAGS) $< -o $@

$(CONTROLLEROBJ): $(CONTROLLERSRC) | obj
	$(CC) $(CFLAGS) $< -o $@

$(RDBOBJ): $(RDBSRC) | obj
	$(CC) $(CFLAGS) $< -o $@
	
# Service tasks
clean:
	rm -f $(VIEWOBJ) $(MODELOBJ) $(CONTROLLEROBJ) $(RDBOBJ) lib/libansi*.so

obj:
	mkdir obj

lib:
	mkdir lib
