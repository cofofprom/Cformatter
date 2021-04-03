cmake_minimum_required(VERSION 3.17)
project(Cformatter C)

set(CMAKE_C_STANDARD 11)

add_executable(Cformatter main.c cmake-build-debug/MaxLoopNesting/MaxLoopNesting.h cmake-build-debug/MaxLoopNesting/MaxLoopNesting.c cmake-build-debug/StringTools/StringTools.c cmake-build-debug/StringTools/StringTools.h)