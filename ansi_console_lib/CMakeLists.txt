project (ANSIConsoleLib)

file (GLOB LIB_SRC 
   src/ansi_screen.cpp
   src/region.cpp)

add_library(${PROJECT_NAME} SHARED ${LIB_SRC})
