CC=clang++
CFLAGS=-c -Wall -std=c++17 -fPIC
LFLAGS=-shared -fPIC
# Sources
VIEWSRC=$(wildcard src/view/*.cpp)
MODELSRC=$(wildcard src/model/*.cpp)
CONTROLLERSRC=$(wildcard src/controller/*.cpp)
# Object files
VIEWOBJ=$(addprefix obj/, $(notdir $(VIEWSRC:.cpp=.o)))
MODELOBJ=$(addprefix obj/, $(notdir $(MODELSRC:.cpp=.o)))
CONTROLLEROBJ=$(addprefix obj/, $(notdir $(CONTROLLERSRC:.cpp=.o)))

all: libansiview.so libansimodel.so libansicontroller.so

showvar:
	$(info $$CC is ${CC})
	$(info $$VIEWSRC = ${VIEWSRC})
	$(info $$VIEWOBJ = ${VIEWOBJ})
	$(info $$CONTROLLERSRC = ${CONTROLLERSRC})
	$(info $$CONTROLLEROBJ = ${CONTROLLEROBJ})
	$(info $$MODELSRC = ${MODELSRC})

# Libaries output
libansiview.so: $(VIEWOBJ) | lib
	$(CC) $(LFLAGS) -o lib/$@ $^

libansimodel.so: $(MODELOBJ) | lib
	$(CC) $(LFLAGS) -o lib/$@ $^

libansicontroller.so: $(CONTROLLEROBJ) | lib
	$(CC) $(LFLAGS) -o lib/$@ $^

# Object files
$(VIEWOBJ): $(VIEWSRC) | obj
	$(CC) $(CFLAGS) $< -o $@

$(MODELOBJ): $(MODELSRC) | obj
	$(CC) $(CFLAGS) $< -o $@

$(CONTROLLEROBJ): $(CONTROLLERSRC) | obj
	$(CC) $(CFLAGS) $< -o $@
	
# Service tasks
clean:
	rm -f $(VIEWOBJ) $(MODELOBJ) $(CONTROLLEROBJ) lib/libansi*.so

obj:
	mkdir obj

lib:
	mkdir lib
