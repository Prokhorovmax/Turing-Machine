cmake_minimum_required(VERSION 3.9)
project(TuringMachine C)

set(CMAKE_C_STANDARD 99)

add_executable(TuringMachine input.c start.c process.c output.c utility.c turingmachine.h)