cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_COMPILER /usr/bin/g++-11)

project(ANSIConsole LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(ansi_console_lib)

add_executable(ANSIConsoleTest ansi_lib_test/src/ast.cpp)
target_include_directories(ANSIConsoleTest PUBLIC ${CMAKE_SOURCE_DIR}/ansi_console_lib/src)
target_link_libraries(ANSIConsoleTest ANSIConsoleLib)
