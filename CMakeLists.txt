cmake_minimum_required(VERSION 3.17)
project(Cformatter C)

set(CMAKE_C_STANDARD 11)

add_executable(Cformatter main.c MaxLoopNesting/MaxLoopNesting.h MaxLoopNesting/MaxLoopNesting.c StringTools/StringTools.c StringTools/StringTools.h)