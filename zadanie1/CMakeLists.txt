cmake_minimum_required(VERSION 3.6)
project(zadanie1)

set(CMAKE_C_STANDARD 99)
SET(CMAKE_C_FLAGS "-Wall -O0")

set(SOURCE_FILES main.c)
add_executable(zadanie1 ${SOURCE_FILES})