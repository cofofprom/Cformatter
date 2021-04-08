cmake_minimum_required(VERSION 3.16)
project(Cformatter C)

#Включает все-все warning'и
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(CMAKE_C_STANDARD 11)

add_executable(Cformatter main.c)

#Экзешники для тестов, доки: https://github.com/keithn/seatest
add_executable(cmdparserTests tests/cmdparser/cmdparserTests.c seatest/seatest.c CmdParser/cmdparser.c StringArray/stringarray.c)
add_executable(stringarrayTests tests/stringarray/stringarrayTests.c seatest/seatest.c StringArray/stringarray.c)