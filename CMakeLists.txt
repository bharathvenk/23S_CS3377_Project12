cmake_minimum_required(VERSION 3.17)
project(23S_CS3377_Project1)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS -pthread)

add_executable(21S_CS3377_Project main.cpp Project1SimpleFileModifier.cpp Project1SimpleFileModifier.h Util.h FileModifyException.h Util.cpp FileChecker.cpp FileChecker.h)