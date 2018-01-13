cmake_minimum_required(VERSION 2.8.9)
project(C-Data-Structures)

set(CMAKE_C_COMPILER clang)
set(CMAKE_C_FLAGS "-std=c99 -Wall")

include_directories(header)
file(GLOB SOURCES "src/*.c")

add_executable(cds ${SOURCES})
