cmake_minimum_required(VERSION 3.12)
project(WebServer)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)
add_subdirectory(test)

enable_testing()
add_test(NAME UniTest COMMAND unitest)

