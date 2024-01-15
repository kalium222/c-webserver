# Specify the minimum version of CMake
cmake_minimum_required(VERSION 3.12)

# Project name
project(WebServer)

# Set the C standard to C11
set(CMAKE_C_STANDARD 11)

# Specify the C compiler (replace gcc with your desired compiler)
set(CMAKE_C_COMPILER gcc)

# Optional: Generate compile_commands.json file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add your source files
add_executable(server main.c socket_helper.c socket_helper.h model.c model.h)
